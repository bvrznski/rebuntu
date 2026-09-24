// Rebuntu Installation Contracts (Phase 1.0)
// ===========================================

#pragma once

#include <cstdint>
#include <optional>
#include <string>
#include <string_view>
#include <vector>

namespace rebuntu::install {

enum class InstallationState {
    kNotInstalled,
    kIncomplete,
    kInstalled,
    kDegraded,
};

inline std::string_view to_string(InstallationState s) {
    switch (s) {
        case InstallationState::kNotInstalled: return "not-installed";
        case InstallationState::kIncomplete:   return "incomplete";
        case InstallationState::kInstalled:    return "installed";
        case InstallationState::kDegraded:     return "degraded";
    }
    return "unknown";
}

enum class InstallationScope {
    kSystem,
    kUser,
};

inline std::string_view to_string(InstallationScope s) {
    switch (s) {
        case InstallationScope::kSystem: return "system";
        case InstallationScope::kUser:   return "user";
    }
    return "unknown";
}

enum class InstallArtifactType {
    kBinary,
    kConfig,
    kSystemdUnit,
    kLibrary,
    kDocumentation,
    kRuntimeStateDir,
};

inline std::string_view to_string(InstallArtifactType t) {
    switch (t) {
        case InstallArtifactType::kBinary:         return "binary";
        case InstallArtifactType::kConfig:         return "config";
        case InstallArtifactType::kSystemdUnit:    return "systemd-unit";
        case InstallArtifactType::kLibrary:        return "library";
        case InstallArtifactType::kDocumentation:  return "documentation";
        case InstallArtifactType::kRuntimeStateDir:return "runtime-state-dir";
    }
    return "unknown";
}

struct Artifact {
    InstallArtifactType type;
    std::string path;
    std::optional<std::string> owner;
    std::optional<uint32_t> mode;
    bool is_optional = false;
};

enum class InstallAction {
    kNothing,
    kCreated,
    kUpdated,
    kVerified,
};

struct InstallResult {
    InstallationState final_state = InstallationState::kNotInstalled;
    
    struct ActionTaken {
        InstallAction action;
        Artifact artifact;
    };
    std::vector<ActionTaken> actions;
    
    bool success = false;
    bool verified = false;
    
    std::optional<std::string> error_code;
    std::optional<std::string> error_message;
};

struct VerificationResult {
    bool is_installed = false;
    
    struct Check {
        std::string name;
        bool passed = false;
        std::optional<std::string> details;
    };
    std::vector<Check> checks;
    
    bool all_passed() const {
        for (const auto& c : checks) {
            if (!c.passed) return false;
        }
        return true;
    }
};

struct InstallContext {
    uid_t effective_uid = 0;
    bool is_root = false;
    InstallationScope default_scope = InstallationScope::kSystem;
    std::string install_root;
    bool skip_verification = false;
};

inline constexpr std::string_view kErrorNotAuthorized = "E_NOT_AUTHORIZED";
inline constexpr std::string_view kErrorDependencyMissing = "E_DEPENDENCY_MISSING";
inline constexpr std::string_view kErrorVerificationFailed = "E_VERIFICATION_FAILED";

}  // namespace rebuntu::install