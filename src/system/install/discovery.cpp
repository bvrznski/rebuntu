// rebuntu::install::discovery — Host environment discovery (Phase 1.1)
//
// This module provides host fact collection and preflight evaluation for
// installation planning. Discovery produces observations/facts, not configuration.

#include <system/install/discovery.hpp>

#include <array>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <sstream>
#include <string>
#include <sys/utsname.h>
#include <sys/statvfs.h>
#include <sys/stat.h>
#include <unistd.h>

#include <optional>
#include <filesystem>

namespace fs = std::filesystem;

// Use Evidence from core evidence store (defined as rebuntu::core::Evidence)

namespace rebuntu {
namespace install {
namespace discovery {

// ============================================================================
// HostDiscovery implementation
// ============================================================================

HostDiscovery::HostDiscovery() {}

std::string HostDiscovery::discover_os_id() const {
    std::ifstream os_release("/etc/os-release");
    if (!os_release.is_open()) {
        return "unknown";
    }

    std::string line;
    while (std::getline(os_release, line)) {
        if (line.rfind("ID=", 0) == 0) {
            return line.substr(3);
        }
    }
    return "unknown";
}

std::string HostDiscovery::discover_os_version() const {
    std::ifstream os_release("/etc/os-release");
    if (!os_release.is_open()) {
        return "unknown";
    }

    std::string line;
    while (std::getline(os_release, line)) {
        if (line.rfind("VERSION_ID=", 0) == 0) {
            // Remove quotes if present
            std::string version = line.substr(11);
            if (!version.empty() && version.front() == '"') {
                version = version.substr(1, version.size() - 2);
            }
            return version;
        }
    }
    return "unknown";
}

std::string HostDiscovery::discover_kernel_version() const {
    struct utsname uname_buf {};
    if (uname(&uname_buf) != 0) {
        return "unknown";
    }
    return std::string(uname_buf.release);
}

std::string HostDiscovery::discover_architecture() const {
    struct utsname uname_buf {};
    if (uname(&uname_buf) != 0) {
        return "unknown";
    }
    return std::string(uname_buf.machine);
}

// Helper: Check if executable exists in PATH without shell execution
static bool command_exists_native(const std::string& cmd) {
    const char* path_env = std::getenv("PATH");
    if (!path_env) return false;
    
    std::string path_str(path_env);
    size_t start = 0;
    
    while (start < path_str.length()) {
        size_t end = path_str.find(':', start);
        if (end == std::string::npos) end = path_str.length();
        
        std::string dir = path_str.substr(start, end - start);
        if (!dir.empty() && dir.back() != '/') dir += '/';
        dir += cmd;
        
        // Use access() to check if executable exists and is runnable
        if (access(dir.c_str(), X_OK) == 0) return true;
        
        start = end + 1;
    }
    
    return false;
}

bool HostDiscovery::detect_systemd() const {
    // Check if systemd is available by testing for systemd-run or checking /run/systemd
    return fs::exists("/run/systemd/system") || command_exists_native("systemd-run");
}

void HostDiscovery::detect_filesystems(HostFacts& facts) const {
    // Check root filesystem
    struct statvfs root_stat {};
    if (statvfs("/", &root_stat) == 0) {
        HostFacts::FileSystemInfo info;
        info.mount_point = "/";
        info.total_bytes = static_cast<std::uintmax_t>(root_stat.f_blocks) * 
                          static_cast<std::uintmax_t>(root_stat.f_frsize);
        info.free_bytes = static_cast<std::uintmax_t>(root_stat.f_bfree) * 
                         static_cast<std::uintmax_t>(root_stat.f_frsize);
        info.is_writable = (access("/", W_OK) == 0);
        facts.root_filesystem = info;
    }

    // Check home filesystem if available
    const char* home = std::getenv("HOME");
    if (home && fs::exists(home)) {
        struct statvfs home_stat {};
        if (statvfs(home, &home_stat) == 0) {
            HostFacts::FileSystemInfo info;
            info.mount_point = home;
            info.total_bytes = static_cast<std::uintmax_t>(home_stat.f_blocks) * 
                              static_cast<std::uintmax_t>(home_stat.f_frsize);
            info.free_bytes = static_cast<std::uintmax_t>(home_stat.f_bfree) * 
                             static_cast<std::uintmax_t>(home_stat.f_frsize);
            info.is_writable = (access(home, W_OK) == 0);
            facts.home_filesystem = info;
        }
    }
}

void HostDiscovery::detect_package_managers(HostFacts& facts) const {
    // Check for apt
    if (command_exists_native("apt")) {
        HostFacts::PackageManager pm;
        pm.name = "apt";
        pm.available = true;
        facts.package_managers.push_back(pm);
    }

    // Check for dnf
    if (command_exists_native("dnf")) {
        HostFacts::PackageManager pm;
        pm.name = "dnf";
        pm.available = true;
        facts.package_managers.push_back(pm);
    }

    // Check for pacman
    if (command_exists_native("pacman")) {
        HostFacts::PackageManager pm;
        pm.name = "pacman";
        pm.available = true;
        facts.package_managers.push_back(pm);
    }
}

void HostDiscovery::detect_environment_type(HostFacts& facts) const {
    // Check for container environment
    if (fs::exists("/.dockerenv") ||
        fs::exists("/run/.containerenv") ||
        std::getenv("container")) {
        facts.environment_type = EnvironmentType::kContainer;
        
        // Try to detect specific runtime
        std::ifstream cgroup("/proc/1/cgroup");
        if (cgroup.is_open()) {
            std::string line;
            while (std::getline(cgroup, line)) {
                if (line.find("docker") != std::string::npos) {
                    facts.container_runtime = "docker";
                    break;
                } else if (line.find("podman") != std::string::npos) {
                    facts.container_runtime = "podman";
                    break;
                }
            }
        }
    } else if (fs::exists("/dev/kvm")) {
        // Likely a VM if /dev/kvm exists
        facts.environment_type = EnvironmentType::kVirtualMachine;
    } else {
        facts.environment_type = EnvironmentType::kPhysicalMachine;
    }
}

std::vector<PreflightCheckResult> HostDiscovery::evaluate_preflight_checks(
    const HostFacts& facts) const {
    
    std::vector<PreflightCheckResult> results;

    // Check supported distribution
    results.push_back(check_supported_distribution(facts));

    // Check root privileges (for system install)
    results.push_back(check_root_privileges(facts));

    // Check bin directory writable
    results.push_back(check_bin_directory_writable(facts));

    // Check state directory writable
    results.push_back(check_state_directory_writable(facts));

    // Check package manager available
    results.push_back(check_package_manager_available(facts));

    // Check home directory accessible (for user install)
    results.push_back(check_home_directory_accessible(facts));

    // Check free space
    results.push_back(check_free_space(facts));

    return results;
}

PreflightCheckResult HostDiscovery::check_supported_distribution(
    const HostFacts& facts) const {
    
    PreflightCheckResult result;
    result.name = "supported-distribution";
    result.source = "/etc/os-release";

    // Supported distributions
    static const std::array<std::string, 5> supported_ids = {{
        "ubuntu", "debian", "fedora", "arch", "centos"
    }};

    bool is_supported = false;
    for (const auto& id : supported_ids) {
        if (facts.os_id == id) {
            is_supported = true;
            break;
        }
    }

    result.passed = is_supported;
    result.level = PreflightCheckLevel::kBlocker;

    if (is_supported) {
        result.message = "Host distribution is supported: " + facts.os_id +
                        " " + facts.os_version;
    } else {
        result.message = "Host distribution may not be fully tested: " +
                        facts.os_id + " " + facts.os_version;
        // Not a hard blocker - just a warning
        result.level = PreflightCheckLevel::kWarning;
    }

    return result;
}

PreflightCheckResult HostDiscovery::check_root_privileges(
    const HostFacts& facts) const {
    
    PreflightCheckResult result;
    result.name = "root-privileges";
    result.source = "geteuid()";

    // For system install, root is required
    if (facts.effective_uid == 0) {
        result.passed = true;
        result.level = PreflightCheckLevel::kInfo;
        result.message = "Running with root privileges";
    } else {
        result.passed = false;
        result.level = PreflightCheckLevel::kWarning;
        result.message = "Not running as root - system installation may fail";
    }

    return result;
}

PreflightCheckResult HostDiscovery::check_bin_directory_writable(
    const HostFacts& facts) const {
    
    PreflightCheckResult result;
    result.name = "bin-directory-writable";
    result.source = "/usr/bin";

    // For root, /usr/bin should be writable
    if (facts.effective_uid == 0 && facts.root_filesystem.has_value()) {
        result.passed = facts.root_filesystem->is_writable;
        result.level = PreflightCheckLevel::kInfo;

        if (!result.passed) {
            result.message = "/usr/bin is not writable - system installation blocked";
            result.level = PreflightCheckLevel::kBlocker;
        }
    } else {
        // For user install, check ~/.local/bin
        const char* home = std::getenv("HOME");
        if (home && facts.effective_uid != 0) {
            std::string bin_path = std::string(home) + "/.local/bin";
            result.source = bin_path;
            struct stat st {};
            result.passed = (stat(bin_path.c_str(), &st) == 0);
            result.level = PreflightCheckLevel::kInfo;

            if (!result.passed) {
                // Can create the directory
                result.message = bin_path + " will be created";
                result.passed = true;
            }
        } else {
            result.passed = false;
            result.level = PreflightCheckLevel::kBlocker;
            result.message = "Cannot determine write location for binary installation";
        }
    }

    return result;
}

PreflightCheckResult HostDiscovery::check_state_directory_writable(
    const HostFacts& facts) const {
    
    PreflightCheckResult result;
    result.name = "state-directory-writable";
    result.source = "/var/lib/rebuntu";

    if (facts.effective_uid == 0 && facts.root_filesystem.has_value()) {
        result.passed = facts.root_filesystem->is_writable;
        result.level = PreflightCheckLevel::kInfo;

        if (!result.passed) {
            result.message = "/var/lib is not writable - state directory creation blocked";
            result.level = PreflightCheckLevel::kBlocker;
        }
    } else {
        // For user install, check ~/.local/state
        const char* home = std::getenv("HOME");
        if (home && facts.effective_uid != 0) {
            std::string state_path = std::string(home) + "/.local/state/rebuntu";
            result.source = state_path;
            struct stat st {};
            result.passed = (stat(state_path.c_str(), &st) == 0);
            result.level = PreflightCheckLevel::kInfo;

            if (!result.passed) {
                // Can create the directory
                result.message = state_path + " will be created";
                result.passed = true;
            }
        } else {
            result.passed = false;
            result.level = PreflightCheckLevel::kBlocker;
            result.message = "Cannot determine write location for state directory";
        }
    }

    return result;
}

PreflightCheckResult HostDiscovery::check_package_manager_available(
    const HostFacts& facts) const {
    
    PreflightCheckResult result;
    result.name = "package-manager-available";
    result.source = "which";

    if (facts.package_managers.empty()) {
        result.passed = false;
        result.level = PreflightCheckLevel::kWarning;
        result.message = "No package manager detected - binary installation only";
    } else {
        result.passed = true;
        result.level = PreflightCheckLevel::kInfo;

        std::ostringstream oss;
        oss << "Detected package managers: ";
        for (size_t i = 0; i < facts.package_managers.size(); ++i) {
            if (i > 0) oss << ", ";
            oss << facts.package_managers[i].name;
        }
        result.message = oss.str();
    }

    return result;
}

PreflightCheckResult HostDiscovery::check_home_directory_accessible(
    const HostFacts& facts) const {
    
    PreflightCheckResult result;
    result.name = "home-directory-accessible";
    result.source = "$HOME";

    const char* home = std::getenv("HOME");
    if (!home || std::string(home).empty()) {
        result.passed = false;
        result.level = PreflightCheckLevel::kBlocker;
        result.message = "$HOME is not set - cannot determine user install location";
    } else if (access(home, R_OK | X_OK) != 0) {
        result.passed = false;
        result.level = PreflightCheckLevel::kBlocker;
        result.message = "$HOME directory is not accessible: " + std::string(home);
    } else {
        result.passed = true;
        result.level = PreflightCheckLevel::kInfo;
        result.message = "Home directory accessible: " + std::string(home);
    }

    return result;
}

PreflightCheckResult HostDiscovery::check_free_space(
    const HostFacts& facts) const {
    
    PreflightCheckResult result;
    result.name = "sufficient-free-space";
    result.source = "/";

    // Require at least 50MB free space
    constexpr std::uintmax_t min_required_bytes = 50 * 1024 * 1024;

    std::optional<HostFacts::FileSystemInfo> target_fs;
    if (facts.effective_uid == 0 && facts.root_filesystem.has_value()) {
        target_fs = facts.root_filesystem;
    } else if (facts.home_filesystem.has_value()) {
        target_fs = facts.home_filesystem;
    }

    if (!target_fs.has_value()) {
        result.passed = false;
        result.level = PreflightCheckLevel::kWarning;
        result.message = "Cannot determine filesystem information";
        return result;
    }

    if (target_fs->free_bytes >= min_required_bytes) {
        result.passed = true;
        result.level = PreflightCheckLevel::kInfo;

        std::ostringstream oss;
        oss << "Sufficient free space available: "
            << (target_fs->free_bytes / 1024 / 1024) << " MB";
        result.message = oss.str();
    } else {
        result.passed = false;
        result.level = PreflightCheckLevel::kBlocker;

        std::ostringstream oss;
        oss << "Insufficient free space: "
            << (target_fs->free_bytes / 1024 / 1024) << " MB available, "
            << min_required_bytes / 1024 / 1024 << " MB required";
        result.message = oss.str();
    }

    return result;
}

DiscoveryResult HostDiscovery::discover() const {
    DiscoveryResult result;

    // Collect facts
    result.facts.os_id = discover_os_id();
    result.facts.os_version = discover_os_version();
    result.facts.kernel_version = discover_kernel_version();
    result.facts.architecture = discover_architecture();

    result.facts.effective_uid = geteuid();
    result.facts.effective_gid = getgid();
    result.facts.is_root = (result.facts.effective_uid == 0);

    const char* home = std::getenv("HOME");
    if (home) {
        result.facts.home_dir = home;
    }

    // Detect systemd availability
    result.facts.has_systemd = detect_systemd();

    // Detect filesystems
    detect_filesystems(result.facts);

    // Detect package managers
    detect_package_managers(result.facts);

    // Detect environment type
    detect_environment_type(result.facts);

    // Evaluate preflight checks
    result.preflight_checks = evaluate_preflight_checks(result.facts);

    // Determine overall status
    if (result.has_blockers()) {
        result.status = DiscoveryStatus::kBlocked;
    } else {
        bool has_warning = false;
        for (const auto& check : result.preflight_checks) {
            if (check.level == PreflightCheckLevel::kWarning) {
                has_warning = true;
                break;
            }
        }
        result.status = has_warning ? DiscoveryStatus::kWarningOnly
                                    : DiscoveryStatus::kReady;
    }

    // Evidence chain - currently stubbed, will be integrated with Phase 1.2 completion

    return result;
}

// ============================================================================
// PreflightEvaluator implementation
// ============================================================================

PreflightEvaluator::PreflightEvaluator() {}

std::vector<PreflightCheckResult> PreflightEvaluator::evaluate(
    const HostFacts& facts) const {
    
    std::vector<PreflightCheckResult> results;

    // Run standard preflight checks
    for (const auto& distro : supported_distros_) {
        if (facts.os_id == distro) {
            PreflightCheckResult check;
            check.name = "supported-distribution";
            check.passed = true;
            check.level = PreflightCheckLevel::kInfo;
            check.message = "Distribution " + facts.os_id + " is in supported list";
            results.push_back(check);
            break;
        }
    }

    // Check privileges
    if (facts.is_root) {
        PreflightCheckResult check;
        check.name = "root-privileges";
        check.passed = true;
        check.level = PreflightCheckLevel::kInfo;
        check.message = "Running with root privileges";
        results.push_back(check);
    }

    return results;
}

}  // namespace discovery
}  // namespace install
}  // namespace rebuntu