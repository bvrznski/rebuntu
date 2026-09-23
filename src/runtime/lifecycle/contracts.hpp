#include <cstdint>
// rebuntu::lifecycle — Lifecycle Operations Contracts (Phase 1.11)
//
// This establishes Rebuntu's canonical grammar for lifecycle operations:
//   * RECONFIGURE: Change configuration without reinstalling
//   * REPAIR: Restore Rebuntu-owned installation invariants
//   * UPGRADE: Version-aware migration between schema versions
//   * UNINSTALL/PURGE: Remove Rebuntu-owned artifacts
//
// Core principles:
//   * Owner distinction: Rebuntu-owned vs user-owned data
//   * Evidence-based verification: Execution success ≠ verified success
//   * Idempotency: Safe to run multiple times with same result
//   * Safety: No broad deletion, protect user data

#pragma once

#include <runtime/core/contracts.hpp>
#include <algorithm>
#include <map>
#include <optional>
#include <set>
#include <string>
#include <string_view>
#include <vector>

namespace rebuntu::lifecycle {

// ============================================================================
// Lifecycle Operation Types
// ============================================================================

enum class LifecycleOperation {
    kReconfigure,
    kRepair,
    kUpgrade,
    kUninstall,
    kPurge,
};

inline std::string_view to_string(LifecycleOperation op) {
    switch (op) {
        case LifecycleOperation::kReconfigure: return "reconfigure";
        case LifecycleOperation::kRepair:      return "repair";
        case LifecycleOperation::kUpgrade:     return "upgrade";
        case LifecycleOperation::kUninstall:   return "uninstall";
        case LifecycleOperation::kPurge:       return "purge";
    }
    return "unknown";
}

// ============================================================================
// Artifact Classification
// ============================================================================

enum class ArtifactOwnership {
    kRebuntuOwned,  // Managed by Rebuntu (can be modified/removed)
    kUserModified,  // User has modified this file
    kExternal,      // Managed by external system (systemd, package manager)
    kUnknown,       // Ownership cannot be determined
};

inline std::string_view to_string(ArtifactOwnership o) {
    switch (o) {
        case ArtifactOwnership::kRebuntuOwned: return "rebuntu-owned";
        case ArtifactOwnership::kUserModified: return "user-modified";
        case ArtifactOwnership::kExternal:     return "external";
        case ArtifactOwnership::kUnknown:      return "unknown";
    }
    return "unknown";
}

enum class ArtifactType {
    kBinary,
    kConfigFile,
    kStateFile,
    kCacheFile,
    kSystemdUnit,
    kShellIntegration,
    kDocumentation,
    kDirectory,
};

inline std::string_view to_string(ArtifactType t) {
    switch (t) {
        case ArtifactType::kBinary:         return "binary";
        case ArtifactType::kConfigFile:     return "config-file";
        case ArtifactType::kStateFile:      return "state-file";
        case ArtifactType::kCacheFile:      return "cache-file";
        case ArtifactType::kSystemdUnit:    return "systemd-unit";
        case ArtifactType::kShellIntegration: return "shell-integration";
        case ArtifactType::kDocumentation:  return "documentation";
        case ArtifactType::kDirectory:      return "directory";
    }
    return "unknown";
}

// ============================================================================
// Manifest Entry
// ============================================================================

struct ArtifactEntry {
    std::string path;                    // Absolute path to artifact
    ArtifactType type;                   // What kind of artifact
    ArtifactOwnership ownership;         // Who owns this artifact
    
    // Metadata for verification
    std::optional<std::string> expected_owner;
    std::optional<uint32_t> expected_mode;
    std::optional<std::string> checksum;  // For integrity checking
    
    // Lifecycle information
    std::string managed_by;              // Which phase/component manages this
    bool is_optional = false;            // Can be missing without failure
};

// ============================================================================
// Artifact Manifest
// ============================================================================

class ArtifactManifest {
public:
    void add_entry(ArtifactEntry entry) {
        entries_[entry.path] = std::move(entry);
    }
    
    bool contains(const std::string& path) const {
        return entries_.find(path) != entries_.end();
    }
    
    std::optional<ArtifactEntry> find(const std::string& path) const {
        auto it = entries_.find(path);
        if (it == entries_.end()) return std::nullopt;
        return it->second;
    }
    
    std::vector<ArtifactEntry> all() const {
        std::vector<ArtifactEntry> result;
        result.reserve(entries_.size());
        for (const auto& [path, entry] : entries_) {
            result.push_back(entry);
        }
        // Sort for determinism
        std::sort(result.begin(), result.end(),
                  [](const ArtifactEntry& a, const ArtifactEntry& b) {
                      return a.path < b.path;
                  });
        return result;
    }
    
    // Get all Rebuntu-owned artifacts (for uninstall)
    std::vector<ArtifactEntry> rebuntu_owned() const {
        std::vector<ArtifactEntry> result;
        for (const auto& [path, entry] : entries_) {
            if (entry.ownership == ArtifactOwnership::kRebuntuOwned) {
                result.push_back(entry);
            }
        }
        std::sort(result.begin(), result.end(),
                  [](const ArtifactEntry& a, const ArtifactEntry& b) {
                      return a.path < b.path;
                  });
        return result;
    }
    
    // Validate manifest entries
    std::vector<std::string> validate() const {
        std::vector<std::string> issues;
        std::set<std::string> seen_paths;
        
        for (const auto& [path, entry] : entries_) {
            if (seen_paths.contains(path)) {
                issues.push_back("duplicate manifest entry: " + path);
            }
            seen_paths.insert(path);
            
            if (path.empty()) {
                issues.push_back("artifact entry with empty path");
            }
        }
        
        return issues;
    }

private:
    std::map<std::string, ArtifactEntry> entries_;
};

// ============================================================================
// Lifecycle Context
// ============================================================================

struct LifecycleContext {
    // Scope
    enum class Scope {
        kSystem,   // System-wide operations
        kUser,     // Per-user operations
        kSession,  // Transient session-scoped (for testing)
    } scope = Scope::kSystem;
    
    // Paths
    std::string install_root;      // Root for relative paths
    std::string config_dir;
    std::string state_dir;
    std::string cache_dir;
    
    // Execution control
    bool dry_run = false;          // Don't actually mutate
    bool force = false;            // Skip safety checks (use with caution)
    bool preserve_user_data = true; // Never delete user data unless purge
    
    // Verification
    bool skip_verification = false;
    
    // Context for operation-specific behavior
    std::optional<std::string> target_version;  // For upgrades
};

// ============================================================================
// Result Types
// ============================================================================

enum class LifecycleStatus {
    kNotStarted,
    kInProgress,
    kCompleted,
    kFailed,
    kPartial,      // Some operations succeeded, some failed
    kCancelled,
};

inline std::string_view to_string(LifecycleStatus s) {
    switch (s) {
        case LifecycleStatus::kNotStarted: return "not_started";
        case LifecycleStatus::kInProgress: return "in_progress";
        case LifecycleStatus::kCompleted:  return "completed";
        case LifecycleStatus::kFailed:     return "failed";
        case LifecycleStatus::kPartial:    return "partial";
        case LifecycleStatus::kCancelled:  return "cancelled";
    }
    return "unknown";
}

struct ArtifactOperation {
    std::string path;
    enum class Action {
        kNoOp,
        kCreated,
        kUpdated,
        kVerified,
        kDeleted,
        kSkipped,      // Skipped due to ownership or safety
        kFailed,
    } action = Action::kNoOp;
    
    std::optional<std::string> error_code;
    std::optional<std::string> error_message;
};

struct LifecycleResult {
    LifecycleOperation operation;     // What operation was performed
    LifecycleStatus status;           // Overall result
    
    bool success = false;             // Operation completed without internal errors
    bool verified = false;            // Postconditions independently verified
    
    std::vector<ArtifactOperation> operations;
    
    // Summary of artifact states after operation
    std::set<std::string> created_paths;
    std::set<std::string> modified_paths;
    std::set<std::string> deleted_paths;
    std::set<std::string> skipped_paths;  // Skipped due to ownership/safety
    
    // Error information (if not success)
    std::optional<core::Error> error;
    
    // Verification evidence
    std::vector<core::Evidence> evidence;
};

inline std::string_view to_string(ArtifactOperation::Action action) {
    switch (action) {
        case ArtifactOperation::Action::kNoOp:     return "no_op";
        case ArtifactOperation::Action::kCreated:  return "created";
        case ArtifactOperation::Action::kUpdated:  return "updated";
        case ArtifactOperation::Action::kVerified: return "verified";
        case ArtifactOperation::Action::kDeleted:  return "deleted";
        case ArtifactOperation::Action::kSkipped:  return "skipped";
        case ArtifactOperation::Action::kFailed:   return "failed";
    }
    return "unknown";
}

// ============================================================================
// Repair-Specific Types
// ============================================================================

enum class RepairIssue {
    kMissingArtifact,
    kWrongPermissions,
    kWrongOwner,
    kCorruptContent,
    kBrokenDependency,
    kUserModified,      // User modified - do not repair silently
    kUnknownOwnership,
    kExternalManaged,   // Managed by external system
};

inline std::string_view to_string(RepairIssue issue) {
    switch (issue) {
        case RepairIssue::kMissingArtifact:     return "missing-artifact";
        case RepairIssue::kWrongPermissions:    return "wrong-permissions";
        case RepairIssue::kWrongOwner:          return "wrong-owner";
        case RepairIssue::kCorruptContent:      return "corrupt-content";
        case RepairIssue::kBrokenDependency:    return "broken-dependency";
        case RepairIssue::kUserModified:        return "user-modified";
        case RepairIssue::kUnknownOwnership:    return "unknown-ownership";
        case RepairIssue::kExternalManaged:     return "external-managed";
    }
    return "unknown";
}

struct RepairPlan {
    std::vector<std::string> paths_to_repair;
    std::vector<std::string> paths_to_verify;
    std::vector<std::string> paths_skipped;  // User modified, should not repair
    bool is_no_op = false;
};

// ============================================================================
// Upgrade-Specific Types
// ============================================================================

struct VersionInfo {
    std::string version;        // Current or target version (e.g., "1.0.0")
    int64_t schema_version = 0; // Schema/migration version
    
    // Migration information
    bool needs_migration = false;
    std::optional<std::string> migration_from;
};

struct UpgradePlan {
    VersionInfo source;
    VersionInfo target;
    
    bool requires_checkpoint = false;      // Should backup before upgrade
    std::vector<std::string> files_to_update;
    std::vector<std::string> schema_migrations;
    bool preserve_user_data = true;
    
    bool is_no_op = false;  // Already at target version
};

// ============================================================================
// Uninstall/Purge Types
// ============================================================================

enum class UninstallMode {
    kStandard,   // Remove Rebuntu-owned only, preserve user data
    kPurge,      // Remove everything including user configuration
};

inline std::string_view to_string(UninstallMode m) {
    switch (m) {
        case UninstallMode::kStandard: return "standard";
        case UninstallMode::kPurge:    return "purge";
    }
    return "unknown";
}

struct UninstallPlan {
    std::vector<std::string> paths_to_remove;
    std::vector<std::string> user_data_paths;  // User-owned, will be preserved
    bool has_user_data = false;
    
    bool is_safe() const { return !has_user_data || mode == UninstallMode::kPurge; }
    UninstallMode mode = UninstallMode::kStandard;
};

// ============================================================================
// Error Codes (Phase 1.11)
// ============================================================================

inline constexpr std::string_view kErrorArtifactNotFound = "E_ARTIFACT_NOT_FOUND";
inline constexpr std::string_view kErrorOwnershipConflict = "E_OWNERSHIP_CONFLICT";
inline constexpr std::string_view kErrorVerificationFailed = "E_VERIFICATION_FAILED";
inline constexpr std::string_view kErrorMigrationFailed = "E_MIGRATION_FAILED";
inline constexpr std::string_view kErrorUnauthorized = "E_UNAUTHORIZED";

// ============================================================================
// Lifecycle API (Phase 1.11)
// ============================================================================

// Build a default lifecycle context based on current host state
LifecycleContext build_default_context();

// Get the artifact manifest for the current installation
ArtifactManifest get_artifact_manifest(const LifecycleContext& ctx);

// RECONFIGURE: Change configuration without reinstalling
LifecycleResult reconfigure(const LifecycleContext& ctx, 
                            const std::map<std::string, std::string>& config);

// REPAIR: Restore Rebuntu-owned artifacts to correct state
LifecycleResult repair(const LifecycleContext& ctx,
                       const std::vector<std::string>& paths = {});

// UPGRADE: Migrate from current version to target version
LifecycleResult upgrade(const LifecycleContext& ctx,
                        const std::string& target_version);

// UNINSTALL: Remove Rebuntu-owned artifacts (preserve user data)
LifecycleResult uninstall(const LifecycleContext& ctx);

// PURGE: Remove everything including user configuration
LifecycleResult purge(const LifecycleContext& ctx);

}  // namespace rebuntu::lifecycle