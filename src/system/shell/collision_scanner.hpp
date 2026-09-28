// rebuntu::shell::collision — Command Collision Detection Scanner (Phase 6.14)
//
// This module provides systematic collision detection against:
//   - Shell builtins
//   - System commands (PATH executables)
//   - User-defined aliases and functions
//   - Existing Rebuntu verbs
//
// Design Philosophy:
//   * Collision detection is separate from parsing (deterministic)
//   * No execution during scanning (read-only operations)
//   * Bounded discovery with timeout and limits
//   * Classification: FREE, REBUNTU, SHELL_BUILTIN, SYSTEM_COMMAND, USER_DEFINED

#pragma once

#include "types.hpp"
#include <string>
#include <string_view>
#include <vector>
#include <map>
#include <optional>
#include <chrono>
#include <filesystem>

namespace rebuntu::shell::collision {

// ============================================================================
// CollisionClass — Categorization of collision severity
// ============================================================================

enum class CollisionClass {
    kNone,              // No collision detected
    kShellBuiltin,      // Collides with shell builtin (e.g., 'cd', 'export')
    kSystemCommand,     // Collides with installed system command (e.g., 'find')
    kUserAlias,         // Collides with user-defined alias/function
    kAmbiguousPrefix,   // Multiple commands match abbreviation
    kReservedRebuntu,   // Reserved Rebuntu verb (cannot be used by user)
};

inline std::string to_string(CollisionClass c) {
    switch (c) {
        case CollisionClass::kNone:         return "none";
        case CollisionClass::kShellBuiltin: return "shell_builtin";
        case CollisionClass::kSystemCommand:return "system_command";
        case CollisionClass::kUserAlias:    return "user_alias";
        case CollisionClass::kAmbiguousPrefix:return "ambiguous_prefix";
        case CollisionClass::kReservedRebuntu:return "reserved_rebuntu";
    }
    return "unknown";
}

// ============================================================================
// CollisionInfo — Detailed information about a collision
// ============================================================================

struct CollisionInfo {
    std::string verb;              // The Rebuntu verb being checked
    CollisionClass class_;         // Category of collision
    
    // Source of the collision (if applicable)
    std::optional<std::string> source_path;  // Full path for system commands
    std::optional<std::string> alias_definition;  // For user aliases
    std::optional<std::string> function_source;   // For shell functions
    
    // Additional context
    bool is_rebuntu_internal{false};  // Is this a Rebuntu-internal verb?
};

// ============================================================================
// CollisionResult — Result of collision scanning for one verb
// ============================================================================

struct CollisionResult {
    std::string verb;
    
    CollisionClass class_{CollisionClass::kNone};
    std::optional<CollisionInfo> info;
    
    // Timing
    std::chrono::milliseconds scan_duration_ms{0};
};

// ============================================================================
// ScannerConfig — Configuration for the collision scanner
// ============================================================================

struct ScannerConfig {
    // Discovery bounds
    size_t max_path_searches{100};     // Max directories to search in PATH
    size_t max_aliases_to_check{50};   // Max aliases to scan
    size_t max_functions_to_check{50}; // Max functions to scan
    
    // Timeouts
    std::chrono::milliseconds timeout_ms{30000};  // Total discovery timeout
    
    // Options
    bool include_shell_builtins{true};
    bool include_system_commands{true};
    bool include_user_definitions{true};
    bool include_rebuntu_reserved{true};
};

inline ScannerConfig default_config() {
    return ScannerConfig{};
}

// ============================================================================
// ShellBuiltinRegistry — Known shell builtin commands
// ============================================================================

class ShellBuiltinRegistry {
public:
    // Get list of common POSIX/Bash builtins
    static std::vector<std::string> get_builtins();
    
    // Check if a word is a known shell builtin
    static bool is_builtin(std::string_view word);
    
private:
    static const std::vector<std::string> kBuiltins;
};

// ============================================================================
// SystemCommandScanner — Scans for system commands in PATH
// ============================================================================

class SystemCommandScanner {
public:
    explicit SystemCommandScanner(const ScannerConfig& config = default_config());
    
    // Scan for a command and return its location if found
    std::optional<std::string> find_command(std::string_view name) const;
    
    // Get list of all commands in PATH directories (bounded)
    std::vector<std::string> list_path_commands() const;
    
    // Check if command exists in PATH
    bool has_system_command(std::string_view name) const;

private:
    ScannerConfig config_;
    
    // List of PATH directories to search
    std::vector<std::filesystem::path> path_directories_;
};

// ============================================================================
// UserDefinitionScanner — Scans for user-defined aliases/functions
// ============================================================================

class UserDefinitionScanner {
public:
    explicit UserDefinitionScanner(const ScannerConfig& config = default_config());
    
    // Get list of user aliases (via 'alias' command)
    std::vector<std::string> get_user_aliases() const;
    
    // Get list of shell functions (via 'compgen -f')
    std::vector<std::string> get_shell_functions() const;
    
    // Check if a word is defined as an alias
    bool is_alias(std::string_view word) const;
    
    // Check if a word is defined as a function
    bool is_function(std::string_view word) const;

private:
    ScannerConfig config_;
};

// ============================================================================
// RebuntuReservedRegistry — Reserved Rebuntu verbs
// ============================================================================

class RebuntuReservedRegistry {
public:
    // Get list of reserved Rebuntu verbs
    static std::vector<std::string> get_reserved_verbs();
    
    // Check if a verb is reserved for Rebuntu internal use
    static bool is_reserved(std::string_view word);

private:
    static const std::vector<std::string> kReservedVerbs;
};

// ============================================================================
// CollisionScanner — Main collision detection engine
// ============================================================================

class CollisionScanner {
public:
    explicit CollisionScanner(const ScannerConfig& config = default_config());
    
    // Scan one verb and return collision info
    CollisionResult scan_verb(std::string_view verb) const;
    
    // Scan multiple verbs and return all collisions
    std::vector<CollisionResult> scan_verbs(
        const std::vector<std::string>& verbs) const;
    
    // Get collision report for a set of commands
    struct Report {
        std::vector<CollisionResult> results;
        size_t total_collisions{0};
        size_t shell_builtins{0};
        size_t system_commands{0};
        size_t user_definitions{0};
    };
    
    Report generate_report(const std::vector<std::string>& verbs) const;

private:
    ScannerConfig config_;
    ShellBuiltinRegistry builtin_registry_;
    SystemCommandScanner system_scanner_;
    UserDefinitionScanner user_scanner_;
};

// ============================================================================
// Utility functions
// ============================================================================

// Get collision status for a verb (shorthand)
CollisionClass get_collision_status(std::string_view verb);

// Format collision info as human-readable string
std::string format_collision_info(const CollisionInfo& info);

}  // namespace rebuntu::shell::collision

