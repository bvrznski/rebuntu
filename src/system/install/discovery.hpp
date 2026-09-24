// rebuntu::install::discovery — Host environment discovery (Phase 1.1)
//
// This module provides host fact collection and preflight evaluation for
// installation planning. Discovery produces observations/facts, not configuration.
#pragma once

#include <system/core/contracts.hpp>
#include <system/install/contracts.hpp>

#include <chrono>
#include <optional>
#include <string>
#include <vector>

namespace rebuntu {
namespace install {
namespace discovery {

// ============================================================================
// EnvironmentType — Host environment classification
// ============================================================================

enum class EnvironmentType {
    kPhysicalMachine,   // Native Linux installation
    kContainer,         // Running inside a container (Docker/Podman)
    kVirtualMachine,    // Running in a VM
    kUnknown
};

inline std::string to_string(EnvironmentType t) {
    switch (t) {
        case EnvironmentType::kPhysicalMachine: return "physical-machine";
        case EnvironmentType::kContainer:       return "container";
        case EnvironmentType::kVirtualMachine:  return "virtual-machine";
        default:                                return "unknown";
    }
}

// ============================================================================
// PreflightCheckResult::Level — Preflight check severity level
// ============================================================================

enum class PreflightCheckLevel {
    kInfo,       // Informational only
    kWarning,    // Issue but installation may proceed
    kBlocker     // Installation cannot proceed without resolution
};

inline std::string to_string(PreflightCheckLevel l) {
    switch (l) {
        case PreflightCheckLevel::kInfo:       return "info";
        case PreflightCheckLevel::kWarning:    return "warning";
        case PreflightCheckLevel::kBlocker:    return "blocker";
        default:                               return "unknown";
    }
}

// ============================================================================
// DiscoveryResult::Status — Discovery result status
// ============================================================================

enum class DiscoveryStatus {
    kReady,          // All blockers passed, ready for installation
    kWarningOnly,    // Some warnings but no blockers
    kBlocked         // Has blockers that must be resolved
};

inline std::string to_string(DiscoveryStatus s) {
    switch (s) {
        case DiscoveryStatus::kReady:      return "ready";
        case DiscoveryStatus::kWarningOnly:return "warning_only";
        case DiscoveryStatus::kBlocked:    return "blocked";
        default:                           return "unknown";
    }
}

// ============================================================================
// HostFacts — Machine-readable host environment observations
// ============================================================================

struct HostFacts {
    // OS/Distribution facts
    std::string os_id;                    // e.g., "ubuntu", "debian", "fedora"
    std::string os_name;                  // e.g., "Ubuntu"
    std::string os_version;               // e.g., "22.04"
    std::string os_version_codename;      // e.g., "jammy"

    // Kernel facts
    std::string kernel_version;           // e.g., "6.8.0-31-generic"
    std::string architecture;             // e.g., "x86_64", "aarch64"

    // Runtime facts
    std::optional<std::string> python_version;  // if available
    std::optional<std::string> cmake_version;   // if available

    // Init/service manager
    bool has_systemd = false;
    bool systemd_user_available = false;
    std::optional<std::string> systemd_version;

    // User context
    uid_t effective_uid = 0;
    gid_t effective_gid = 0;
    bool is_root = false;
    std::optional<std::string> home_dir;      // $HOME if available
    std::optional<std::string> xdg_config_home;
    std::optional<std::string> xdg_data_home;

    // Filesystem facts
    struct FileSystemInfo {
        std::string mount_point;
        std::uintmax_t total_bytes = 0;
        std::uintmax_t free_bytes = 0;
        bool is_writable = false;
    };

    std::optional<FileSystemInfo> root_filesystem;
    std::optional<FileSystemInfo> home_filesystem;

    // Package manager facts
    struct PackageManager {
        std::string name;           // e.g., "apt", "dnf", "pacman"
        std::optional<std::string> version;
        bool available = false;
    };
    std::vector<PackageManager> package_managers;

    EnvironmentType environment_type = EnvironmentType::kUnknown;
    std::optional<std::string> container_runtime;  // e.g., "docker", "podman"
};

// ============================================================================
// PreflightCheckResult — Result of a preflight evaluation
// ============================================================================

struct PreflightCheckResult {
    std::string name;              // Check identifier (e.g., "supported-distribution")
    bool passed = false;
    PreflightCheckLevel level = PreflightCheckLevel::kInfo;
    std::optional<std::string> message;
    std::optional<std::string> remediation;  // How to fix if failed

    // Source/provenance tracking
    std::string source;            // Where this check's data came from
    std::chrono::system_clock::time_point evaluated_at;
};

// ============================================================================
// DiscoveryResult — Complete host discovery and preflight evaluation result
// ============================================================================

struct DiscoveryResult {
    HostFacts facts;

    std::vector<PreflightCheckResult> preflight_checks;

    DiscoveryStatus status = DiscoveryStatus::kBlocked;

    // Evidence chain
    std::vector<core::Evidence> evidence;

    bool is_success() const {
        return status == DiscoveryStatus::kReady || status == DiscoveryStatus::kWarningOnly;
    }

    bool has_blockers() const {
        for (const auto& check : preflight_checks) {
            if (check.level == PreflightCheckLevel::kBlocker && !check.passed) {
                return true;
            }
        }
        return false;
    }
};

// ============================================================================
// HostDiscovery — Main discovery interface
// ============================================================================

class HostDiscovery {
public:
    HostDiscovery();

    // Perform complete host discovery
    DiscoveryResult discover() const;

private:
    // Fact collection methods (call native Linux facilities)
    std::string discover_os_id() const;
    std::string discover_os_version() const;
    std::string discover_kernel_version() const;
    std::string discover_architecture() const;
    bool detect_systemd() const;
    void detect_filesystems(HostFacts& facts) const;
    void detect_package_managers(HostFacts& facts) const;
    void detect_environment_type(HostFacts& facts) const;

    // Preflight check methods
    std::vector<PreflightCheckResult> evaluate_preflight_checks(
        const HostFacts& facts) const;

    PreflightCheckResult check_supported_distribution(
        const HostFacts& facts) const;

    PreflightCheckResult check_root_privileges(
        const HostFacts& facts) const;

    PreflightCheckResult check_bin_directory_writable(
        const HostFacts& facts) const;

    PreflightCheckResult check_state_directory_writable(
        const HostFacts& facts) const;

    PreflightCheckResult check_package_manager_available(
        const HostFacts& facts) const;

    PreflightCheckResult check_home_directory_accessible(
        const HostFacts& facts) const;

    PreflightCheckResult check_free_space(
        const HostFacts& facts) const;
};

// ============================================================================
// PreflightEvaluator — Simplified interface for preflight evaluation
// ============================================================================

class PreflightEvaluator {
public:
    explicit PreflightEvaluator();

    // Run all preflight evaluations for given host facts
    std::vector<PreflightCheckResult> evaluate(const HostFacts& facts) const;

private:
    std::vector<std::string> supported_distros_ = {"ubuntu", "debian", "fedora"};
};

}  // namespace discovery
}  // namespace install
}  // namespace rebuntu

