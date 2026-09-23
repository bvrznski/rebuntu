// rebuntu::environment::discovery — Host environment and pre-installation discovery (Phase 1.1)

#pragma once

#include <system/core/contracts.hpp>
#include <array>
#include <cstdio>
#include <filesystem>
#include <memory>
#include <optional>
#include <string>
#include <string_view>
#include <vector>

namespace rebuntu::environment::discovery {

enum class DiscoveryStatus {
    kKnown,
    kUnknown,
};

inline std::string_view to_string(DiscoveryStatus s) {
    switch (s) {
        case DiscoveryStatus::kKnown:   return "known";
        case DiscoveryStatus::kUnknown: return "unknown";
    }
    return "unknown";
}

struct HostFact {
    std::string source;
    std::string name;
    std::string value;
};

struct DistributionInfo {
    std::optional<std::string> id;
    std::optional<std::string> version;
    std::optional<std::string> codename;
    std::optional<std::string> pretty_name;
    
    DiscoveryStatus status = DiscoveryStatus::kUnknown;
};

struct KernelInfo {
    std::optional<std::string> release;
    std::optional<std::string> version;
    std::optional<std::string> architecture;
    
    DiscoveryStatus status = DiscoveryStatus::kUnknown;
};

enum class CpuArchitecture {
    kUnknown,
    kX86_64,
    kAarch64,
    kArm32,
    kRiscv64,
};

inline std::string_view to_string(CpuArchitecture a) {
    switch (a) {
        case CpuArchitecture::kUnknown:  return "unknown";
        case CpuArchitecture::kX86_64:   return "x86_64";
        case CpuArchitecture::kAarch64:  return "aarch64";
        case CpuArchitecture::kArm32:    return "arm32";
        case CpuArchitecture::kRiscv64:  return "riscv64";
    }
    return "unknown";
}

// CPU topology information (Phase 1.9)
struct CpuCoreInfo {
    int core_id = -1;
    int physical_core_id = -1;
    int socket_id = -1;
    bool is_hyperthread = false;
};

struct ArchitectureInfo {
    CpuArchitecture cpu = CpuArchitecture::kUnknown;
    
    std::optional<int> cpu_count;           // logical CPU count
    std::optional<int> physical_cpu_count;  // physical core count
    std::optional<int> socket_count;        // number of sockets/CPUs
    
    DiscoveryStatus status = DiscoveryStatus::kUnknown;
};

enum class RuntimeAvailability {
    kAvailable,
    kUnavailable,
    kVersionTooOld,
    kUnknown,
};

struct RuntimeInfo {
    std::optional<int> python_major;
    std::optional<int> python_minor;
    
    RuntimeAvailability python_status = RuntimeAvailability::kUnknown;
    
    DiscoveryStatus status = DiscoveryStatus::kUnknown;
};

enum class InitSystem {
    kNone,
    kSystemd,
    kOpenRC,
    kSysVInit,
    kUnknown,
};

inline std::string_view to_string(InitSystem s) {
    switch (s) {
        case InitSystem::kNone:      return "none";
        case InitSystem::kSystemd:   return "systemd";
        case InitSystem::kOpenRC:    return "openrc";
        case InitSystem::kSysVInit:  return "sysv_init";
        case InitSystem::kUnknown:   return "unknown";
    }
    return "unknown";
}

struct InitInfo {
    InitSystem init = InitSystem::kUnknown;
    
    std::optional<bool> systemd_system_available;
    std::optional<bool> systemd_user_available;
    
    DiscoveryStatus status = DiscoveryStatus::kUnknown;
};

enum class ElevationCapability {
    kNone,
    kSudoAvailable,
    kSudoUsable,
    kAlreadyElevated,
};

struct PrivilegeInfo {
    uid_t effective_uid = 0;
    
    bool is_root = false;
    
    ElevationCapability elevation = ElevationCapability::kNone;
    
    DiscoveryStatus status = DiscoveryStatus::kUnknown;
};

// Mount point information (Phase 1.9)
struct MountInfo {
    std::string device;
    std::string mount_point;
    std::string filesystem_type;
    uint64_t total_bytes = 0;
    uint64_t free_bytes = 0;
    bool is_read_only = false;
};

// Storage information (Phase 1.9)
struct StorageInfo {
    std::vector<MountInfo> mounts;
    
    DiscoveryStatus status = DiscoveryStatus::kUnknown;
};
struct FilesystemInfo {
    std::optional<std::string> home_dir;
    std::optional<std::string> xdg_config_home;
    std::optional<std::string> xdg_data_home;
    
    std::optional<std::string> system_bin_path;
    std::optional<std::string> user_bin_path;
    
    std::optional<uint64_t> free_space_bytes;
    
    DiscoveryStatus status = DiscoveryStatus::kUnknown;
};

enum class PackageManager {
    kNone,
    kApt,
    kDpkg,
    kSnap,
    kPip,
    kYum,
    kDnf,
    kZypper,
    kApk,
    kUnknown,
};

inline std::string_view to_string(PackageManager p) {
    switch (p) {
        case PackageManager::kNone:     return "none";
        case PackageManager::kApt:      return "apt";
        case PackageManager::kDpkg:     return "dpkg";
        case PackageManager::kSnap:     return "snap";
        case PackageManager::kPip:      return "pip";
        case PackageManager::kYum:      return "yum";
        case PackageManager::kDnf:      return "dnf";
        case PackageManager::kZypper:   return "zypper";
        case PackageManager::kApk:      return "apk";
        case PackageManager::kUnknown:  return "unknown";
    }
    return "unknown";
}

struct PackageManagerInfo {
    std::vector<PackageManager> available;
    
    DiscoveryStatus status = DiscoveryStatus::kUnknown;
};

enum class VirtualizationType {
    kNone,
    kDocker,
    kPodman,
    kLXC,
    kSystemdNspawn,
    kVMware,
    kVirtualBox,
    kKVM,
    kXen,
    kUnknown,
};

inline std::string_view to_string(VirtualizationType v) {
    switch (v) {
        case VirtualizationType::kNone:       return "none";
        case VirtualizationType::kDocker:     return "docker";
        case VirtualizationType::kPodman:     return "podman";
        case VirtualizationType::kLXC:        return "lxc";
        case VirtualizationType::kSystemdNspawn:return "systemd-nspawn";
        case VirtualizationType::kVMware:     return "vmware";
        case VirtualizationType::kVirtualBox: return "virtualbox";
        case VirtualizationType::kKVM:        return "kvm";
        case VirtualizationType::kXen:        return "xen";
        case VirtualizationType::kUnknown:    return "unknown";
    }
    return "unknown";
}

struct ContainerInfo {
    bool is_container = false;
    VirtualizationType virt_type = VirtualizationType::kUnknown;
    
    DiscoveryStatus status = DiscoveryStatus::kUnknown;
};

// Memory information (Phase 1.9)
struct MemoryInfo {
    std::optional<uint64_t> total_bytes;      // total system memory
    std::optional<uint64_t> free_bytes;       // currently free memory
    std::optional<uint64_t> available_bytes;  // available for new allocations
    
    DiscoveryStatus status = DiscoveryStatus::kUnknown;
};

// Network capability information (Phase 1.9)
struct NetworkInfo {
    std::optional<bool> has_ipv4;     // IPv4 connectivity available
    std::optional<bool> has_ipv6;     // IPv6 connectivity available
    std::optional<bool> has_wifi;     // Wi-Fi capability detected
    std::optional<bool> has_ethernet; // Wired Ethernet available
    
    DiscoveryStatus status = DiscoveryStatus::kUnknown;
};

// Desktop/session information (Phase 1.9)
enum class DesktopEnvironment {
    kNone,
    kGNOME,
    kKDE,
    kXFCE,
    kLXDE,
    kCinnamon,
    kMate,
    ki3,
    kSway,
    kWayland,   // Wayland session without specific DE
    kUnknown,
};

inline std::string_view to_string(DesktopEnvironment de) {
    switch (de) {
        case DesktopEnvironment::kNone:      return "none";
        case DesktopEnvironment::kGNOME:     return "gnome";
        case DesktopEnvironment::kKDE:       return "kde";
        case DesktopEnvironment::kXFCE:      return "xfce";
        case DesktopEnvironment::kLXDE:      return "lxde";
        case DesktopEnvironment::kCinnamon:  return "cinnamon";
        case DesktopEnvironment::kMate:      return "mate";
        case DesktopEnvironment::ki3:        return "i3";
        case DesktopEnvironment::kSway:      return "sway";
        case DesktopEnvironment::kWayland:   return "wayland";
        default:                             return "unknown";
    }
}

enum class DisplayServer {
    kNone,
    kX11,
    kWayland,
    kUnknown,
};

inline std::string_view to_string(DisplayServer ds) {
    switch (ds) {
        case DisplayServer::kNone:     return "none";
        case DisplayServer::kX11:      return "x11";
        case DisplayServer::kWayland:  return "wayland";
        default:                       return "unknown";
    }
}

struct SessionInfo {
    DesktopEnvironment desktop = DesktopEnvironment::kUnknown;
    DisplayServer display_server = DisplayServer::kUnknown;
    
    std::optional<std::string> session_type;  // "wayland", "x11", "tty"
    
    DiscoveryStatus status = DiscoveryStatus::kUnknown;
};

// GPU information (Phase 1.9)
enum class GpuType {
    kNone,
    kIntegrated,
    kDiscrete,
    kUnknown,
};

struct GpuDevice {
    std::string id;              // stable identifier
    GpuType type = GpuType::kUnknown;
    
    std::optional<std::string> vendor;     // e.g., "Intel", "NVIDIA", "AMD"
    std::optional<std::string> model;      // device name
    
    std::optional<uint64_t> memory_bytes;  // VRAM if available
};

struct GpuInfo {
    std::vector<GpuDevice> devices;
    
    DiscoveryStatus status = DiscoveryStatus::kUnknown;
};
// Shell information (Phase 1.9)
enum class ShellType {
    kNone,
    kBash,
    kZsh,
    kFish,
    kAsh,
    kDash,
    kCsSh,
    kPwSh,  // PowerShell
    kUnknown,
};

inline std::string_view to_string(ShellType s) {
    switch (s) {
        case ShellType::kNone:     return "none";
        case ShellType::kBash:     return "bash";
        case ShellType::kZsh:      return "zsh";
        case ShellType::kFish:     return "fish";
        case ShellType::kAsh:      return "ash";
        case ShellType::kDash:     return "dash";
        case ShellType::kCsSh:     return "csh";
        case ShellType::kPwSh:     return "powershell";
        default:                   return "unknown";
    }
}

struct ShellInfo {
    std::optional<ShellType> primary_shell;
    
    DiscoveryStatus status = DiscoveryStatus::kUnknown;
};

struct HostDiscoveryResult {
    DistributionInfo distribution;
    KernelInfo kernel;
    ArchitectureInfo architecture;
    RuntimeInfo runtime;
    InitInfo init_system;
    PrivilegeInfo privilege;
    FilesystemInfo filesystem;
    StorageInfo storage;
    MemoryInfo memory;
    NetworkInfo network;
    SessionInfo session;
    GpuInfo gpu;
    ShellInfo shell;
    PackageManagerInfo package_manager;
    ContainerInfo container;
    
    std::vector<HostFact> facts;
    DiscoveryStatus overall_status = DiscoveryStatus::kUnknown;
};

class HostDiscovery {
public:
    HostDiscovery();
    
    HostDiscoveryResult discover() const;
    
    DistributionInfo discover_distribution() const;
    KernelInfo discover_kernel() const;
    ArchitectureInfo discover_architecture() const;
    RuntimeInfo discover_runtime() const;
    InitInfo discover_init_system() const;
    PrivilegeInfo discover_privilege() const;
    FilesystemInfo discover_filesystem() const;
    StorageInfo discover_storage() const;
    MemoryInfo discover_memory() const;
    NetworkInfo discover_network() const;
    SessionInfo discover_session() const;
    GpuInfo discover_gpu() const;
    ShellInfo discover_shell() const;
    PackageManagerInfo discover_package_manager() const;
    ContainerInfo discover_container() const;

};

enum class PreconditionStatus {
    kSatisfied,
    kFailed,
    kWarning,
};

inline std::string_view to_string(PreconditionStatus s) {
    switch (s) {
        case PreconditionStatus::kSatisfied: return "satisfied";
        case PreconditionStatus::kFailed:    return "failed";
        case PreconditionStatus::kWarning:   return "warning";
    }
    return "unknown";
}

struct PreflightCheck {
    std::string name;
    PreconditionStatus status;
    std::optional<std::string> message;
    
    bool is_blocker() const { return status == PreconditionStatus::kFailed; }
};

struct PreflightResult {
    HostDiscoveryResult discovery;
    
    std::vector<PreflightCheck> checks;
    std::vector<std::string> blockers;
    std::vector<std::string> warnings;
    
    bool is_ready() const { return blockers.empty(); }
};

class PreflightEvaluator {
public:
    explicit PreflightEvaluator(const HostDiscoveryResult& discovery);
    
    PreflightResult evaluate() const;

private:
    const HostDiscoveryResult& discovery_;
    
    std::vector<PreflightCheck> check_distribution_supported() const;
    std::vector<PreflightCheck> check_runtime_available() const;
    std::vector<PreflightCheck> check_filesystem_writable() const;
    std::vector<PreflightCheck> check_package_manager_available() const;
    std::vector<PreflightCheck> check_memory_sufficient() const;
    std::vector<PreflightCheck> check_storage_sufficient() const;
};


// Precondition defaults for Phase 1.9 (Phase 0.8-style minimal checks)
inline bool is_precondition_blocker(PreconditionStatus s) {
    return s == PreconditionStatus::kFailed;
}

inline bool is_precondition_warning(PreconditionStatus s) {
    return s == PreconditionStatus::kWarning;
}

}  // namespace rebuntu::environment::discovery
