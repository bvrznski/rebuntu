// rebuntu::host_foundation — Linux Host Foundation Implementation (Phase 2.0)
//
// This implements the canonical host foundation observer that:
//   * Observes what the Linux host provides
//   * Reports which foundations are present/missing
//   * Evaluates support decisions for different operational modes

#include <system/host_foundation/contracts.hpp>

#include <array>
#include <cstdio>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>
#include <sys/stat.h>

namespace fs = std::filesystem;

// ============================================================================
// Helper functions
// ============================================================================

static std::optional<std::string> read_file_line(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        return std::nullopt;
    }
    
    std::string line;
    if (std::getline(file, line)) {
        // Trim trailing whitespace
        while (!line.empty() && 
               (line.back() == '\n' || line.back() == '\r' || line.back() == ' ')) {
            line.pop_back();
        }
        return line;
    }
    
    return std::nullopt;
}

// ============================================================================
// HostFoundation implementation
// ============================================================================

namespace rebuntu::host_foundation {

HostFoundation::HostFoundation() {}

std::optional<std::string> HostFoundation::read_file_line(const std::string& path) const {
    return ::read_file_line(path);
}

bool HostFoundation::path_exists(const std::string& path) const {
    std::error_code ec;
    return fs::exists(fs::path(path), ec);
}

// Check /etc/os-release for distribution identification
FoundationObservation HostFoundation::check_os_release() const {
    FoundationObservation obs;
    obs.type = HostFoundationType::kOsRelease;
    
    auto content = read_file_line("/etc/os-release");
    if (content.has_value()) {
        // Verify it contains expected fields
        bool has_id = false;
        bool has_version = false;
        
        std::istringstream iss(content.value());
        std::string line;
        while (std::getline(iss, line)) {
            if (line.find("ID=") == 0) {
                has_id = true;
            } else if (line.find("VERSION_ID=") == 0) {
                has_version = true;
            }
        }
        
        if (has_id || content->find("ubuntu") != std::string::npos ||
            content->find("debian") != std::string::npos) {
            obs.status = FoundationObservationStatus::kPresent;
            obs.source = "/etc/os-release";
            obs.observed_value = content.value();
        } else {
            // File exists but doesn't look like os-release
            obs.status = FoundationObservationStatus::kUnknown;
            obs.error_message = "os-release file does not contain expected fields";
        }
    } else if (path_exists("/etc/os-release")) {
        obs.status = FoundationObservationStatus::kUnknown;
        obs.error_message = "Could not read /etc/os-release";
    } else {
        // On some minimal systems, os-release might be absent
        obs.status = FoundationObservationStatus::kMissing;
    }
    
    return obs;
}

// Check kernel version and basic Linux features
FoundationObservation HostFoundation::check_kernel() const {
    FoundationObservation obs;
    obs.type = HostFoundationType::kKernel;
    
    // Read /proc/version which contains kernel info
    auto version_line = read_file_line("/proc/version");
    if (version_line.has_value()) {
        // Should contain "Linux version" or similar
        if (version_line->find("Linux") != std::string::npos) {
            obs.status = FoundationObservationStatus::kPresent;
            obs.source = "/proc/version";
            obs.observed_value = version_line.value();
        } else {
            obs.status = FoundationObservationStatus::kUnknown;
            obs.error_message = "Could not identify kernel from /proc/version";
        }
    } else if (path_exists("/proc/version")) {
        obs.status = FoundationObservationStatus::kUnknown;
        obs.error_message = "Could not read /proc/version";
    } else {
        // No /proc - very unusual on Linux
        obs.status = FoundationObservationStatus::kMissing;
    }
    
    return obs;
}

// Check filesystem supports Unix ownership semantics
FoundationObservation HostFoundation::check_filesystem() const {
    FoundationObservation obs;
    obs.type = HostFoundationType::kFilesystem;
    
    // Check if we can access /etc/passwd (indicates POSIX filesystem)
    if (path_exists("/etc/passwd")) {
        // Try to read it to verify ownership semantics
        auto content = read_file_line("/etc/passwd");
        if (content.has_value()) {
            // Should contain ':' separated fields with uid/gid
            size_t colon_count = 0;
            for (char c : content.value()) {
                if (c == ':') colon_count++;
            }
            if (colon_count >= 6) {
                obs.status = FoundationObservationStatus::kPresent;
                obs.source = "/etc/passwd";
                obs.observed_value = "POSIX filesystem detected";
            } else {
                obs.status = FoundationObservationStatus::kUnknown;
                obs.error_message = "/etc/passwd exists but format is unexpected";
            }
        } else if (path_exists("/etc/passwd")) {
            // File exists but unreadable - might be permission issue
            uid_t uid = geteuid();
            if (uid == 0) {
                obs.status = FoundationObservationStatus::kUnknown;
                obs.error_message = "/etc/passwd exists but cannot be read";
            } else {
                obs.status = FoundationObservationStatus::kMissing;
            }
        } else {
            obs.status = FoundationObservationStatus::kUnknown;
            obs.error_message = "Could not verify /etc/passwd content";
        }
    } else if (path_exists("/etc/group")) {
        // Fallback: check group file instead
        auto content = read_file_line("/etc/group");
        if (content.has_value()) {
            obs.status = FoundationObservationStatus::kPresent;
            obs.source = "/etc/group";
            obs.observed_value = "POSIX filesystem detected via /etc/group";
        } else {
            obs.status = FoundationObservationStatus::kUnknown;
            obs.error_message = "Cannot verify POSIX filesystem";
        }
    } else {
        // No POSIX user files - likely not a standard Linux system
        obs.status = FoundationObservationStatus::kMissing;
    }
    
    return obs;
}

// Check process model (fork/exec/pipe availability)
FoundationObservation HostFoundation::check_process_model() const {
    FoundationObservation obs;
    obs.type = HostFoundationType::kProcessModel;
    
    // On Linux, fork/exec are always available in userspace
    // We verify by checking for /proc which implies standard process model
    if (path_exists("/proc")) {
        obs.status = FoundationObservationStatus::kPresent;
        obs.source = "/proc";
        obs.observed_value = "Standard Linux process model available";
    } else {
        // No /proc means non-standard or very minimal environment
        obs.status = FoundationObservationStatus::kMissing;
    }
    
    return obs;
}

// Check systemd availability (for service management)
FoundationObservation HostFoundation::check_systemd() const {
    FoundationObservation obs;
    obs.type = HostFoundationType::kSystemd;
    
    if (systemd_checked_) {
        // Use cached result
        obs.status = systemd_status_cache_;
        obs.source = "cached";
        return obs;
    }
    
    // Check for systemctl command using the helper method
    std::optional<std::string> systemctl_content;
    {
        std::ifstream file("/usr/bin/systemctl");
        if (file.is_open()) {
            std::string line;
            if (std::getline(file, line)) {
                systemctl_content = line;
            }
        }
    }
    
    if (systemctl_content.has_value()) {
        obs.status = FoundationObservationStatus::kPresent;
        obs.source = "/usr/bin/systemctl";
        obs.observed_value = "systemctl available";
        systemd_status_cache_ = FoundationObservationStatus::kPresent;
    } else {
        // Check D-Bus for systemd
        if (path_exists("/run/dbus")) {
            obs.status = FoundationObservationStatus::kUnknown;
            obs.error_message = "D-Bus present but systemctl not found";
            systemd_status_cache_ = FoundationObservationStatus::kUnknown;
        } else {
            obs.status = FoundationObservationStatus::kMissing;
            obs.error_message = "systemctl not available";
            systemd_status_cache_ = FoundationObservationStatus::kMissing;
        }
    }
    
    systemd_checked_ = true;
    return obs;
}

// Check runtime directories availability
FoundationObservation HostFoundation::check_runtime_directories() const {
    FoundationObservation obs;
    obs.type = HostFoundationType::kRuntimeDirectories;
    
    // Check XDG_RUNTIME_DIR first
    auto xdg_runtime = std::getenv("XDG_RUNTIME_DIR");
    if (xdg_runtime != nullptr && path_exists(xdg_runtime)) {
        obs.status = FoundationObservationStatus::kPresent;
        obs.source = "XDG_RUNTIME_DIR";
        obs.observed_value = xdg_runtime;
        return obs;
    }
    
    // Fallback to /run
    if (path_exists("/run")) {
        struct stat st;
        if (stat("/run", &st) == 0 && S_ISDIR(st.st_mode)) {
            obs.status = FoundationObservationStatus::kPresent;
            obs.source = "/run";
            obs.observed_value = "fallback runtime directory";
            return obs;
        }
    }
    
    // Try /var/run as fallback
    if (path_exists("/var/run")) {
        struct stat st;
        if (stat("/var/run", &st) == 0 && S_ISDIR(st.st_mode)) {
            obs.status = FoundationObservationStatus::kPresent;
            obs.source = "/var/run";
            obs.observed_value = "fallback runtime directory (/var/run)";
            return obs;
        }
    }
    
    // No runtime directory found
    obs.status = FoundationObservationStatus::kMissing;
    obs.error_message = "No runtime directory available (XDG_RUNTIME_DIR, /run, or /var/run)";
    return obs;
}

// Check user namespace support (for isolation features)
FoundationObservation HostFoundation::check_user_namespace() const {
    FoundationObservation obs;
    obs.type = HostFoundationType::kUserNamespace;
    
    // User namespaces are supported in Linux >= 3.8
    // We check via /proc/sys/kernel/unprivileged_userns_clone or similar
    
    auto clone_file = read_file_line("/proc/sys/kernel/unprivileged_userns_clone");
    if (clone_file.has_value()) {
        obs.status = FoundationObservationStatus::kPresent;
        obs.source = "/proc/sys/kernel/unprivileged_userns_clone";
        obs.observed_value = "user namespace cloning enabled";
        return obs;
    }
    
    // Check /proc/sys/user/max_user_namespaces
    auto max_ns = read_file_line("/proc/sys/user/max_user_namespaces");
    if (max_ns.has_value()) {
        obs.status = FoundationObservationStatus::kPresent;
        obs.source = "/proc/sys/user/max_user_namespaces";
        obs.observed_value = "user namespace support detected";
        return obs;
    }
    
    // No explicit user namespace configuration found
    // This might still be supported but not explicitly enabled
    obs.status = FoundationObservationStatus::kUnknown;
    obs.error_message = "Cannot determine user namespace availability";
    return obs;
}

// Check native identity facilities (getpwnam, getpwuid via NSS)
FoundationObservation HostFoundation::check_native_identity() const {
    FoundationObservation obs;
    obs.type = HostFoundationType::kNativeIdentity;
    
    // Check for /etc/nsswitch.conf which indicates NSS availability
    auto nsswitch = read_file_line("/etc/nsswitch.conf");
    if (nsswitch.has_value()) {
        // Look for 'files' or 'compat' entries for passwd
        if (nsswitch->find("passwd:") != std::string::npos) {
            obs.status = FoundationObservationStatus::kPresent;
            obs.source = "/etc/nsswitch.conf";
            obs.observed_value = "NSS configured";
            return obs;
        }
    }
    
    // Even without nsswitch.conf, glibc typically has files support built-in
    // We verify by checking if /etc/passwd is readable
    auto passwd_content = read_file_line("/etc/passwd");
    if (passwd_content.has_value()) {
        // If we can read it, native identity facilities should be available
        obs.status = FoundationObservationStatus::kPresent;
        obs.source = "/etc/passwd";
        obs.observed_value = "Native identity readable via files";
        return obs;
    }
    
    // No way to verify native identity facilities
    obs.status = FoundationObservationStatus::kUnknown;
    obs.error_message = "Cannot verify native identity facilities";
    return obs;
}

// Check umask support
FoundationObservation HostFoundation::check_umask_support() const {
    FoundationObservation obs;
    obs.type = HostFoundationType::kUmaskSupport;
    
    // umask(2) is a standard POSIX system call available on all Linux systems
    // We verify by checking /proc/sys/kernel/ngroups_max which exists on modern kernels
    auto ngroups_max = read_file_line("/proc/sys/kernel/ngroups_max");
    if (ngroups_max.has_value()) {
        obs.status = FoundationObservationStatus::kPresent;
        obs.source = "/proc/sys/kernel/ngroups_max";
        obs.observed_value = "umask support available";
        return obs;
    }
    
    // If /proc exists, umask is supported
    if (path_exists("/proc")) {
        obs.status = FoundationObservationStatus::kPresent;
        obs.source = "/proc";
        obs.observed_value = "umask support assumed available";
        return obs;
    }
    
    obs.status = FoundationObservationStatus::kMissing;
    obs.error_message = "Cannot verify umask support";
    return obs;
}

// Main assessment entry point
HostFoundationResult HostFoundation::assess() const {
    HostFoundationResult result;
    
    // Collect all observations
    result.observations.push_back(check_os_release());
    result.observations.push_back(check_kernel());
    result.observations.push_back(check_filesystem());
    result.observations.push_back(check_process_model());
    result.observations.push_back(check_systemd());
    result.observations.push_back(check_runtime_directories());
    result.observations.push_back(check_user_namespace());
    result.observations.push_back(check_native_identity());
    result.observations.push_back(check_umask_support());
    
    // Determine overall status
    int present_count = 0;
    int missing_count = 0;
    int unknown_count = 0;
    
    for (const auto& obs : result.observations) {
        switch (obs.status) {
            case FoundationObservationStatus::kPresent:
                present_count++;
                break;
            case FoundationObservationStatus::kMissing:
                missing_count++;
                break;
            case FoundationObservationStatus::kUnknown:
                unknown_count++;
                break;
        }
    }
    
    // Core foundations: os-release, kernel, filesystem, process model
    bool core_present = present_count >= 4;
    
    if (core_present && missing_count == 0) {
        result.overall_status = HostFoundationStatus::kReady;
    } else if (core_present) {
        result.overall_status = HostFoundationStatus::kPartial;
    } else {
        result.overall_status = HostFoundationStatus::kUnsupported;
    }
    
    // If we have at least some observations, determine detected mode
    if (!result.observations.empty()) {
        // Default to minimal mode if basic foundations are present
        bool systemd_present = false;
        for (const auto& obs : result.observations) {
            if (obs.type == HostFoundationType::kSystemd && obs.is_present()) {
                systemd_present = true;
                break;
            }
        }
        
        if (systemd_present) {
            result.detected_mode = OperationalMode::kServiceManaged;
        } else if (core_present) {
            result.detected_mode = OperationalMode::kMinimal;
        }
    }
    
    // Evaluate support decisions
    result.minimal_decision = evaluate_service_managed_support(result.observations);
    result.service_managed_decision = evaluate_service_managed_support(result.observations);
    result.full_feature_decision = evaluate_full_feature_support(result.observations);
    
    return result;
}

// Support decision helpers
SupportDecision evaluate_service_managed_support(
    const std::vector<FoundationObservation>& observations) {
    
    SupportDecision decision;
    decision.mode = OperationalMode::kServiceManaged;
    
    // Service-managed mode requires:
    // - os-release (for identification)
    // - kernel (Linux)
    // - filesystem (POSIX semantics)
    // - process model (fork/exec)
    // - systemd or equivalent
    // - runtime directories
    
    std::vector<std::string> missing;
    
    for (const auto& obs : observations) {
        switch (obs.type) {
            case HostFoundationType::kOsRelease:
            case HostFoundationType::kKernel:
            case HostFoundationType::kFilesystem:
            case HostFoundationType::kProcessModel:
                if (!obs.is_present()) missing.push_back(std::string{to_string(obs.type)});
                break;
            case HostFoundationType::kSystemd:
                // systemd is required for service-managed mode
                if (!obs.is_present()) {
                    missing.push_back("systemd");
                }
                break;
            case HostFoundationType::kRuntimeDirectories:
                // runtime directories required
                if (!obs.is_present()) {
                    missing.push_back("runtime-directories");
                }
                break;
            default:
                // Other foundations are optional for service-managed mode
                break;
        }
    }
    
    decision.observations = observations;
    decision.missing_critical_foundations = std::move(missing);
    
    if (decision.missing_critical_foundations.empty()) {
        decision.level = SupportLevel::kFullySupported;
    } else {
        decision.level = SupportLevel::kNotSupported;
    }
    
    return decision;
}

SupportDecision evaluate_full_feature_support(
    const std::vector<FoundationObservation>& observations) {
    
    SupportDecision decision;
    decision.mode = OperationalMode::kFullFeature;
    
    // Full feature mode requires all service-managed requirements plus:
    // - user namespace support (for isolation)
    // - native identity facilities
    
    std::vector<std::string> missing;
    
    for (const auto& obs : observations) {
        switch (obs.type) {
            case HostFoundationType::kUserNamespace:
                if (!obs.is_present() && !obs.is_unknown()) {
                    missing.push_back(std::string{to_string(obs.type)});
                }
                break;
            case HostFoundationType::kNativeIdentity:
                if (!obs.is_present() && !obs.is_unknown()) {
                    missing.push_back(std::string{to_string(obs.type)});
                }
                break;
            default:
                // Other requirements are handled by service-managed evaluation
                break;
        }
    }
    
    decision.observations = observations;
    decision.missing_critical_foundations = std::move(missing);
    
    if (decision.missing_critical_foundations.empty()) {
        decision.level = SupportLevel::kFullySupported;
    } else {
        decision.level = SupportLevel::kPartiallySupported;
    }
    
    return decision;
}

}  // namespace rebuntu::host_foundation