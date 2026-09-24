// Rebuntu Lifecycle Contracts (Phase 1.11)
// =========================================

#pragma once

#include <cstddef>
#include <cstdint>
#include <map>
#include <optional>
#include <string>
#include <string_view>
#include <vector>

// For uid_t
#include <sys/types.h>

namespace rebuntu::lifecycle {

enum class LifecycleOperation {
    kReconfigure,  // Change configuration without reinstalling
    kRepair,       // Restore Rebuntu-owned artifacts to correct state
    kUpgrade,      // Version-aware migration between schema versions
    kUninstall,    // Remove Rebuntu-owned artifacts
    kPurge,        // Remove everything including user config
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

enum class ArtifactOwnership {
    kRebuntuOwned,  // Rebuntu owns this artifact
    kUserConfig,    // User configuration that should be preserved
};

struct LifecycleContext {
    bool dry_run = false;           // Don't actually mutate anything
    std::string version;            // Target version for upgrade
    uid_t effective_uid = 0;
    bool is_root = false;
};

struct LifecycleResult {
    LifecycleOperation operation;
    
    enum class Status {
        kSuccess,
        kBlocked,         // Blocked by preconditions (e.g., not root)
        kPartial,         // Some actions succeeded, some failed
        kFailure,         // All actions failed
    } status = Status::kSuccess;
    
    struct Action {
        LifecycleOperation type;
        std::string target;
        ArtifactOwnership ownership;
        bool success = false;
        std::optional<std::string> error_message;
        
        Action() = default;
        Action(LifecycleOperation t, std::string tar, ArtifactOwnership own, bool s, 
               std::optional<std::string> err)
            : type(t), target(std::move(tar)), ownership(own), success(s), error_message(std::move(err)) {}
    };
    
    std::vector<Action> actions;
    
    // Verification evidence
    bool verified = false;
    std::optional<std::string> verification_details;
};

// Lifecycle operations (Phase 1.11)
LifecycleResult reconfigure(const LifecycleContext& ctx, const std::map<std::string, std::string>& config);
LifecycleResult repair(const LifecycleContext& ctx, const std::vector<std::string>& paths = {});
LifecycleResult upgrade(const LifecycleContext& ctx, const std::string& target_version);
LifecycleResult uninstall(const LifecycleContext& ctx);
LifecycleResult purge(const LifecycleContext& ctx);

// Utility functions
bool is_rebuntu_owned_path(const std::string& path);
std::vector<std::string> get_rebuntu_paths();

}  // namespace rebuntu::lifecycle