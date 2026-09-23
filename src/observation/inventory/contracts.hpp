// rebuntu::host_foundation — Linux Host Foundation Contracts (Phase 2.0)
//
// This establishes Rebuntu's canonical host foundation contract:
//   * HOST_CAPABILITY = What the Linux host can provide
//   * REQUIRED_CAPABILITY = What Rebuntu requires to operate
//   * SUPPORT_DECISION = Is this host supported for feature X?
//
// Core principles:
//   * Observation vs Policy: `systemd present` is observed; `host supports X`
//     is a derived decision based on policy
//   * UNKNOWN is valid: acquisition failure is not negative evidence
//   * Graceful degradation: report which assumption is missing, don't fail
//     with "unsupported Linux"

#pragma once

#include <runtime/core/contracts.hpp>
#include <algorithm>
#include <string>
#include <string_view>
#include <vector>
#include <optional>

namespace rebuntu::host_foundation {

// ============================================================================
// HostFoundationStatus - Overall host foundation readiness
// ============================================================================

enum class HostFoundationStatus {
    kReady,           // All required foundations are present and verified
    kPartial,         // Some foundations missing but Rebuntu can partially operate
    kUnsupported,     // Critical foundations missing; Rebuntu cannot operate
    kUnknown,         // Cannot determine foundation status (acquisition failed)
};

inline std::string_view to_string(HostFoundationStatus s) {
    switch (s) {
        case HostFoundationStatus::kReady:       return "ready";
        case HostFoundationStatus::kPartial:     return "partial";
        case HostFoundationStatus::kUnsupported: return "unsupported";
        case HostFoundationStatus::kUnknown:     return "unknown";
    }
    return "unknown";
}

// ============================================================================
// HostFoundationType - Categories of host foundation requirements
// ============================================================================

enum class HostFoundationType {
    kOsRelease,          // /etc/os-release for distro identification
    kKernel,             // Linux kernel with required features
    kFilesystem,         // Filesystem with Unix ownership semantics
    kProcessModel,       // Process model (fork/exec/pipe)
    kSystemd,            // systemd system manager (for service lifecycle)
    kRuntimeDirectories, // XDG_RUNTIME_DIR or equivalent /run
    kUserNamespace,      // User namespace support for isolation
    kNativeIdentity,     // getpwnam/getpwuid NSS facilities
    kUmaskSupport,       // umask(2) for permission control
};

inline std::string_view to_string(HostFoundationType t) {
    switch (t) {
        case HostFoundationType::kOsRelease:       return "os-release";
        case HostFoundationType::kKernel:          return "kernel";
        case HostFoundationType::kFilesystem:      return "filesystem";
        case HostFoundationType::kProcessModel:    return "process-model";
        case HostFoundationType::kSystemd:         return "systemd";
        case HostFoundationType::kRuntimeDirectories: return "runtime-directories";
        case HostFoundationType::kUserNamespace:   return "user-namespace";
        case HostFoundationType::kNativeIdentity:  return "native-identity";
        case HostFoundationType::kUmaskSupport:    return "umask-support";
    }
    return "unknown";
}

// ============================================================================
// FoundationObservation - What we observed about the host
// ============================================================================

enum class FoundationObservationStatus {
    kPresent,      // Resource is available
    kMissing,      // Resource is not present
    kUnknown,      // Could not determine (acquisition failed)
};

inline std::string_view to_string(FoundationObservationStatus s) {
    switch (s) {
        case FoundationObservationStatus::kPresent: return "present";
        case FoundationObservationStatus::kMissing: return "missing";
        case FoundationObservationStatus::kUnknown: return "unknown";
    }
    return "unknown";
}

struct FoundationObservation {
    HostFoundationType type;
    FoundationObservationStatus status;
    
    // Supporting evidence
    std::optional<std::string> source;      // e.g., "/etc/os-release", "/proc/version"
    std::optional<std::string> observed_value;  // e.g., "Ubuntu 22.04", "Linux 5.15"
    std::optional<std::string> error_message;   // if acquisition failed
    
    bool is_present() const { return status == FoundationObservationStatus::kPresent; }
    bool is_missing() const { return status == FoundationObservationStatus::kMissing; }
    bool is_unknown() const { return status == FoundationObservationStatus::kUnknown; }
};

// ============================================================================
// HostRequirements - What Rebuntu requires for different operational modes
// ============================================================================

enum class OperationalMode {
    kMinimal,         // Basic CLI operations (no systemd)
    kServiceManaged,  // Service lifecycle via systemd
    kFullFeature,     // All Rebuntu features
};

struct RequiredCapability {
    HostFoundationType type;
    bool required_for_mode(OperationalMode mode) const {
        switch (mode) {
            case OperationalMode::kMinimal:
                return type == HostFoundationType::kOsRelease ||
                       type == HostFoundationType::kKernel ||
                       type == HostFoundationType::kFilesystem ||
                       type == HostFoundationType::kProcessModel;
            case OperationalMode::kServiceManaged:
                return required_for_mode(OperationalMode::kMinimal) ||
                       type == HostFoundationType::kSystemd ||
                       type == HostFoundationType::kRuntimeDirectories;
            case OperationalMode::kFullFeature:
                return required_for_mode(OperationalMode::kServiceManaged) ||
                       type == HostFoundationType::kUserNamespace ||
                       type == HostFoundationType::kNativeIdentity;
        }
        return false;
    }
};

// ============================================================================
// SupportDecision - Is this host supported for a particular use case?
// ============================================================================

enum class SupportLevel {
    kFullySupported,   // All requirements met
    kPartiallySupported,  // Some functionality available
    kNotSupported,     // Cannot operate in this mode
    kUnknown,          // Cannot determine (acquisition failure)
};

inline std::string_view to_string(SupportLevel l) {
    switch (l) {
        case SupportLevel::kFullySupported:      return "fully-supported";
        case SupportLevel::kPartiallySupported:  return "partially-supported";
        case SupportLevel::kNotSupported:        return "not-supported";
        case SupportLevel::kUnknown:             return "unknown";
    }
    return "unknown";
}

struct SupportDecision {
    OperationalMode mode;
    SupportLevel level;
    
    // Detailed breakdown of which foundations are present/missing
    std::vector<FoundationObservation> observations;
    
    // If not fully supported, which critical foundations are missing?
    std::vector<std::string> missing_critical_foundations;
    
    bool is_fully_supported() const { return level == SupportLevel::kFullySupported; }
    bool is_partially_supported() const { return level == SupportLevel::kPartiallySupported; }
    bool is_not_supported() const { return level == SupportLevel::kNotSupported; }
    bool is_unknown() const { return level == SupportLevel::kUnknown; }
};

// ============================================================================
// HostFoundationResult - Complete host foundation assessment
// ============================================================================

struct HostFoundationResult {
    OperationalMode detected_mode;
    
    // All observations made during assessment
    std::vector<FoundationObservation> observations;
    
    // Overall status
    HostFoundationStatus overall_status = HostFoundationStatus::kUnknown;
    
    // Support decisions for different operational modes
    SupportDecision minimal_decision;
    SupportDecision service_managed_decision;
    SupportDecision full_feature_decision;
    
    // Error information (if assessment failed)
    std::optional<core::Error> error;
};

// ============================================================================
// HostFoundation — The canonical host foundation observer
// ============================================================================

class HostFoundation {
public:
    HostFoundation();
    
    // Main entry point: assess the entire host foundation
    HostFoundationResult assess() const;
    
    // Individual capability checks (can be used independently)
    FoundationObservation check_os_release() const;
    FoundationObservation check_kernel() const;
    FoundationObservation check_filesystem() const;
    FoundationObservation check_process_model() const;
    FoundationObservation check_systemd() const;
    FoundationObservation check_runtime_directories() const;
    FoundationObservation check_user_namespace() const;
    FoundationObservation check_native_identity() const;
    FoundationObservation check_umask_support() const;
    
private:
    mutable std::optional<std::string> os_release_cache_;
    mutable std::optional<std::string> kernel_version_cache_;
    mutable bool systemd_checked_ = false;
    mutable FoundationObservationStatus systemd_status_cache_ = FoundationObservationStatus::kUnknown;
    
    // Helper to read a single line from a file
    std::optional<std::string> read_file_line(const std::string& path) const;
    
    // Helper to check if a path exists (non-blocking)
    bool path_exists(const std::string& path) const;
};

// ============================================================================
// Support policy functions — When is a host considered supported?
// ============================================================================

// Is the host supported for service management via systemd?
SupportDecision evaluate_service_managed_support(
    const std::vector<FoundationObservation>& observations);

// Is the host supported for full features (requires user namespace)?
SupportDecision evaluate_full_feature_support(
    const std::vector<FoundationObservation>& observations);

}  // namespace rebuntu::host_foundation