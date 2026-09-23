// rebuntu::environment::capability_state — Linux Capabilities Contract (Phase 2.5)
//
// This establishes Rebuntu's canonical capability state model:
//
//   CAPABILITY = A unit of privilege that can be granted independently
//   SET        = Permitted, Effective, Inheritable, Bounding, Ambient
//   FILE_CAPS  = Extended attribute on file objects
//
// Architecture:
//   Interfaces      -> src/interfaces/
//   Adapters/Providers -> src/adapters/procfs/, src/adapters/systemd/
//   Semantics       -> src/system/environment/capability_state.hpp
//
// Phase 2.5 adds capability state observation and modeling.
//
// Linux capabilities are divided into five sets:
//   - CapPrm (Permitted): Capabilities the process may potentially use
//   - CapEff (Effective): Currently active capabilities
//   - CapInh (Inheritable): Capabilities inherited across execve
//   - CapBnd (Bounding): Upper limit on capabilities a process can acquire
//   - CapAmb (Ambient): Non-capable processes can gain these capabilities
//
// Reference: linux/capability.h

#pragma once

// Linux capability definitions from kernel headers
#include <linux/capability.h>

#include <cstdint>
#include <cstddef>
#include <string>
#include <vector>
#include <set>
#include <optional>
#include <array>
#include <ctime>

namespace rebuntu::environment::capability_state {

// ============================================================================
// Capability Enumeration - Linux capability constants
// ============================================================================

enum class Capability {
    kChown = 0,               // Override chown restrictions
    kDacOverride = 1,         // Bypass file permission checks
    kDacReadSearch = 2,       // Bypass read/search permission checks
    kFowner = 3,              // Bypass file owner checks for certain operations
    kFsetid = 4,              // Don't clear set-user-ID/set-group-ID bits on chown
    kKill = 5,                // Bypass signal permission checks
    kSetgid = 6,              // Manipulate group IDs
    kSetuid = 7,              // Manipulate user IDs
    kSetpcap = 8,             // Modify capability sets
    kLinuxImmutable = 9,      // Modify immutable file attributes
    kNetBindService = 10,     // Bind to low ports
    kNetBroadcast = 11,       // Send broadcast messages
    kNetAdmin = 12,           // Network administration
    kNetRaw = 13,             // Use raw sockets
    kIpclLock = 14,           // Lock shared memory segments
    kIpclOwner = 15,          // Bypass IPC ownership checks
    kSysModule = 16,          // Load/unload kernel modules
    kSysRawio = 17,           // Perform raw I/O operations
    kSysChroot = 18,          // Use chroot
    kSysPtrace = 19,          // Trace processes
    kSysPacct = 20,           // Configure process accounting
    kSysResource = 24,        // Override resource limits
    kSysTime = 25,            // Manipulate system clock
    kSysTtyConfig = 26,       // Configure TTY devices
    kMknod = 27,              // Create special files
    kLease = 28,              // Take leases on files
    kAuditWrite = 29,         // Write to audit log via netlink
    kAuditControl = 30,       // Configure audit system
    kSetFcap = 31,            // Set file capabilities
    kMacOverride = 32,        // Override MAC access
    kMacAdmin = 33,           // Configure MAC
    kSyslog = 34,             // Configure syslog behavior
    kWakeAlarm = 35,          // Wake system from sleep
    kBlockSuspend = 36,       // Prevent system suspension
    kAuditRead = 37,          // Read audit log via netlink
    kPerfmon = 38,            // Performance monitoring and observability
    kBpf = 39,                // BPF operations
    kCheckpointRestore = 40,  // Checkpoint/restore operations
    
    kLastCapability = kCheckpointRestore,
};

// Number of capabilities (CAP_LAST_CAP + 1)
inline constexpr size_t kNumCapabilities = 41;

// Convert capability enum to string representation
inline const char* to_string(Capability c) {
    switch (c) {
        case Capability::kChown:            return "chown";
        case Capability::kDacOverride:      return "dac_override";
        case Capability::kDacReadSearch:    return "dac_read_search";
        case Capability::kFowner:           return "fowner";
        case Capability::kFsetid:           return "fsetid";
        case Capability::kKill:             return "kill";
        case Capability::kSetgid:           return "setgid";
        case Capability::kSetuid:           return "setuid";
        case Capability::kSetpcap:          return "setpcap";
        case Capability::kLinuxImmutable:   return "linux_immutable";
        case Capability::kNetBindService:   return "net_bind_service";
        case Capability::kNetBroadcast:     return "net_broadcast";
        case Capability::kNetAdmin:         return "net_admin";
        case Capability::kNetRaw:           return "net_raw";
        case Capability::kIpclLock:         return "ipc_lock";
        case Capability::kIpclOwner:        return "ipc_owner";
        case Capability::kSysModule:        return "sys_module";
        case Capability::kSysRawio:         return "sys_rawio";
        case Capability::kSysChroot:        return "sys_chroot";
        case Capability::kSysPtrace:        return "sys_ptrace";
        case Capability::kSysPacct:         return "sys_pacct";
        case Capability::kSysResource:      return "sys_resource";
        case Capability::kSysTime:          return "sys_time";
        case Capability::kSysTtyConfig:     return "sys_tty_config";
        case Capability::kMknod:            return "mknod";
        case Capability::kLease:            return "lease";
        case Capability::kAuditWrite:       return "audit_write";
        case Capability::kAuditControl:     return "audit_control";
        case Capability::kSetFcap:          return "setfcap";
        case Capability::kMacOverride:      return "mac_override";
        case Capability::kMacAdmin:         return "mac_admin";
        case Capability::kSyslog:           return "syslog";
        case Capability::kWakeAlarm:        return "wake_alarm";
        case Capability::kBlockSuspend:     return "block_suspend";
        case Capability::kAuditRead:        return "audit_read";
        case Capability::kPerfmon:          return "perfmon";
        case Capability::kBpf:              return "bpf";
        case Capability::kCheckpointRestore:return "checkpoint_restore";
    }
    return "unknown";
}

// Convert string to capability enum
inline std::optional<Capability> from_string(const char* s) {
    if (s == nullptr) return std::nullopt;
    
    static const struct Mapping {
        const char* name;
        Capability cap;
    } mappings[] = {
        {"chown", Capability::kChown},
        {"dac_override", Capability::kDacOverride},
        {"dac_read_search", Capability::kDacReadSearch},
        {"fowner", Capability::kFowner},
        {"fsetid", Capability::kFsetid},
        {"kill", Capability::kKill},
        {"setgid", Capability::kSetgid},
        {"setuid", Capability::kSetuid},
        {"setpcap", Capability::kSetpcap},
        {"linux_immutable", Capability::kLinuxImmutable},
        {"net_bind_service", Capability::kNetBindService},
        {"net_broadcast", Capability::kNetBroadcast},
        {"net_admin", Capability::kNetAdmin},
        {"net_raw", Capability::kNetRaw},
        {"ipc_lock", Capability::kIpclLock},
        {"ipc_owner", Capability::kIpclOwner},
        {"sys_module", Capability::kSysModule},
        {"sys_rawio", Capability::kSysRawio},
        {"sys_chroot", Capability::kSysChroot},
        {"sys_ptrace", Capability::kSysPtrace},
        {"sys_pacct", Capability::kSysPacct},
        {"sys_resource", Capability::kSysResource},
        {"sys_time", Capability::kSysTime},
        {"sys_tty_config", Capability::kSysTtyConfig},
        {"mknod", Capability::kMknod},
        {"lease", Capability::kLease},
        {"audit_write", Capability::kAuditWrite},
        {"audit_control", Capability::kAuditControl},
        {"setfcap", Capability::kSetFcap},
        {"mac_override", Capability::kMacOverride},
        {"mac_admin", Capability::kMacAdmin},
        {"syslog", Capability::kSyslog},
        {"wake_alarm", Capability::kWakeAlarm},
        {"block_suspend", Capability::kBlockSuspend},
        {"audit_read", Capability::kAuditRead},
        {"perfmon", Capability::kPerfmon},
        {"bpf", Capability::kBpf},
        {"checkpoint_restore", Capability::kCheckpointRestore},
    };
    
    for (const auto& m : mappings) {
        if (std::string(m.name) == s) return m.cap;
    }
    return std::nullopt;
}

// ============================================================================
// CapabilitySet - A collection of capabilities
// ============================================================================

// Each capability set is represented as a bitmask. Linux uses 2 x 32-bit values
// for version 3 capabilities (CAPABILITY_U32S_3 = 2).
using CapabilityBitmask = std::array<uint32_t, 2>;

inline CapabilityBitmask make_empty_bitmask() {
    return CapabilityBitmask{0, 0};
}

inline CapabilityBitmask make_full_bitmask() {
    // Capabilities up to 40 fit in first word (bits 0-31) and part of second
    // We set bits 0-40
    return CapabilityBitmask{0xFFFFFFFFu, 0x1FFFFFu};
}

inline bool has_capability(const CapabilityBitmask& mask, Capability c) {
    size_t index = static_cast<size_t>(c) / 32;
    uint32_t bit = 1u << (static_cast<uint32_t>(c) % 32);
    return (mask[index] & bit) != 0;
}

inline void set_capability(CapabilityBitmask& mask, Capability c) {
    size_t index = static_cast<size_t>(c) / 32;
    uint32_t bit = 1u << (static_cast<uint32_t>(c) % 32);
    mask[index] |= bit;
}

inline void clear_capability(CapabilityBitmask& mask, Capability c) {
    size_t index = static_cast<size_t>(c) / 32;
    uint32_t bit = 1u << (static_cast<uint32_t>(c) % 32);
    mask[index] &= ~bit;
}

inline std::set<Capability> capabilities_from_bitmask(const CapabilityBitmask& mask) {
    std::set<Capability> result;
    for (size_t i = 0; i < kNumCapabilities; ++i) {
        if (has_capability(mask, static_cast<Capability>(i))) {
            result.insert(static_cast<Capability>(i));
        }
    }
    return result;
}

// ============================================================================
// CapabilitySetState - The five Linux capability sets
// ============================================================================

struct CapabilitySetState {
    // Permitted: capabilities the process may potentially use
    CapabilityBitmask permitted = make_empty_bitmask();
    
    // Effective: currently active capabilities
    CapabilityBitmask effective = make_empty_bitmask();
    
    // Inheritable: capabilities inherited across execve
    CapabilityBitmask inheritable = make_empty_bitmask();
    
    // Bounding: upper limit on capabilities a process can acquire
    CapabilityBitmask bounding = make_full_bitmask();
    
    // Ambient: non-capable processes can gain these (Linux 3.8+)
    CapabilityBitmask ambient = make_empty_bitmask();
};

// ============================================================================
// ProcessCapabilityState - Complete capability state for a process
// ============================================================================

struct ProcessCapabilityState {
    // The five capability sets
    CapabilitySetState sets;
    
    // Capability version (from kernel)
    uint32_t version = 0;
    
    // PID this state applies to (0 = current process)
    pid_t pid = 0;
};

// ============================================================================
// FileCapabilityState - Extended attribute on files
// ============================================================================

struct FileCapabilityState {
    // Capability data from file xattr
    CapabilityBitmask permitted;
    CapabilityBitmask inheritable;
    
    // Version of capability format
    uint32_t version = 0;
    
    // If present, maps to specific user namespace root
    std::optional<uint32_t> root_id;
};

// ============================================================================
// Observation Result Types
// ============================================================================

struct CapabilityObservation {
    std::string source;              // e.g., "procfs", "systemd"
    uint64_t observed_at;            // Timestamp (Unix epoch microseconds)
    std::optional<std::string> captured_value;  // Raw observed value if available
};

template <typename T>
struct CapabilityResult {
    enum class Status {
        kSuccess,
        kNotFound,           // Capability or source not found
        kPermissionDenied,   // Cannot read capability state
        kUnknown,            // Could not determine (acquisition failed)
    } status = Status::kUnknown;
    
    std::optional<T> value;
    std::string error_code;
    std::string error_message;
    std::vector<CapabilityObservation> evidence;
    
    bool is_success() const { return status == Status::kSuccess && value.has_value(); }
    bool is_not_found() const { return status == Status::kNotFound; }
    bool is_permission_denied() const { return status == Status::kPermissionDenied; }
    bool is_unknown() const { return status == Status::kUnknown; }
    
    static CapabilityResult<T> success(T v, std::string source) {
        CapabilityResult<T> r;
        r.status = Status::kSuccess;
        r.value = std::move(v);
        r.error_code = "";
        CapabilityObservation e;
        e.source = std::move(source);
        r.evidence.push_back(std::move(e));
        return r;
    }
    
    static CapabilityResult<T> not_found(std::string source, std::string msg) {
        CapabilityResult<T> r;
        r.status = Status::kNotFound;
        r.error_code = "E_NOT_FOUND";
        r.error_message = std::move(msg);
        CapabilityObservation e;
        e.source = std::move(source);
        r.evidence.push_back(std::move(e));
        return r;
    }
    
    static CapabilityResult<T> permission_denied(std::string source, std::string msg) {
        CapabilityResult<T> r;
        r.status = Status::kPermissionDenied;
        r.error_code = "E_PERMISSION_DENIED";
        r.error_message = std::move(msg);
        CapabilityObservation e;
        e.source = std::move(source);
        r.evidence.push_back(std::move(e));
        return r;
    }
    
    static CapabilityResult<T> unknown(std::string source, std::string msg) {
        CapabilityResult<T> r;
        r.status = Status::kUnknown;
        r.error_code = "E_UNKNOWN";
        r.error_message = std::move(msg);
        CapabilityObservation e;
        e.source = std::move(source);
        r.evidence.push_back(std::move(e));
        return r;
    }
};

// ============================================================================
// Observation API
// ============================================================================

// Discover current process capability state by reading /proc/self/status
ProcessCapabilityState discover_capability_state();

// Check if a specific capability is effective in current process
bool has_effective_capability(Capability c);

// Get all capabilities in the permitted set
std::set<Capability> get_permitted_set();

// Get all capabilities in the bounding set (what this process can acquire)
std::set<Capability> getBoundingSet();

// ============================================================================
// Helper API - Capability set operations
// ============================================================================

inline bool has_any_capability(const CapabilityBitmask& mask) {
    return mask[0] != 0 || mask[1] != 0;
}

inline bool is_subset_of(const CapabilityBitmask& a, const CapabilityBitmask& b) {
    return (a[0] & b[0]) == a[0] && (a[1] & b[1]) == a[1];
}

// Check if all capabilities in 'required' are present in 'available'
inline bool has_all_capabilities(const CapabilityBitmask& available,
                                  const std::set<Capability>& required) {
    for (auto c : required) {
        if (!has_capability(available, c)) return false;
    }
    return true;
}

// Check if any capability in 'required' is present in 'available'
inline bool has_any_capability(const CapabilityBitmask& available,
                                const std::set<Capability>& required) {
    for (auto c : required) {
        if (has_capability(available, c)) return true;
    }
    return false;
}

// ============================================================================
// File Capability Operations
// ============================================================================
//
// File capabilities are stored as extended attributes on files:
//   security.capability = file capability set
//
// These operations read/write file capabilities via the filesystem.
//

// Read file capabilities from a path (if any exist)
std::optional<FileCapabilityState> get_file_capabilities(const std::string& path);

// Set file capabilities on a path
bool set_file_capabilities(
    const std::string& path,
    const FileCapabilityState& state);

// ============================================================================
// Ambient Capability Management
// ============================================================================
//
// Ambient capabilities allow non-capable processes to gain capabilities.
// These are managed via prctl() system calls.
//

// Add capability to ambient set for current process
bool add_ambient_capability(Capability c);

// Remove capability from ambient set for current process
bool remove_ambient_capability(Capability c);

// Get all ambient capabilities for current process
std::set<Capability> get_ambient_set();

// ============================================================================
// systemd Service Capability Configuration Parsing
// ============================================================================
//
// systemd service files may specify capability controls via:
//   CapabilityBoundingSet=
//   AmbientCapabilities=
//   NoNewPrivileges=
//   DynamicUser=
//
// These are parsed from .service unit files in /etc/systemd/system/ and /usr/lib/systemd/system/
//

struct SystemdServiceCapabilityConfig {
    std::set<Capability> bounding_set;
    std::set<Capability> ambient_caps;
    bool no_new_privileges = false;
    bool dynamic_user = false;
};

// Parse capability configuration from a systemd .service file
std::optional<SystemdServiceCapabilityConfig> parse_systemd_service_capabilities(
    const std::string& service_path);

// Get capability config for a running service by name (queries via systemctl if available)
std::optional<SystemdServiceCapabilityConfig> get_systemd_service_capability_config(
    const std::string& service_name);

// ============================================================================
// Process Capability Management
// ============================================================================
//
// Operations to manipulate process capability sets via prctl.
//

// Drop specific capability from effective and permitted sets
bool drop_capability(Capability c);

// Add capability to effective set (requires it to be in permitted)
bool enable_effective_capability(Capability c);

// ============================================================================
// Authorization Policy Integration
// ============================================================================
//
// Capabilities can be used as authorization inputs for policy decisions:
//   - A service requiring CAP_NET_BIND_SERVICE may bind to ports < 1024
//   - A service requiring CAP_SYS_ADMIN needs full admin access
//   - Missing capabilities result in authorization denial
//

struct CapabilityAuthorizationDecision {
    enum class Decision {
        kAllow,
        kDeny,
        kInsufficientInformation,  // Unknown capability state
    } decision = Decision::kInsufficientInformation;
    
    std::set<Capability> required;
    std::set<Capability> available;
    std::string reason;
};

// Check if the current process is authorized for a set of capabilities
CapabilityAuthorizationDecision check_capability_authorization(
    const std::set<Capability>& required_caps);

// Get authorization result for service with given capability requirements
 CapabilityAuthorizationDecision check_service_authorization(
    const std::string& service_name,
    const std::set<Capability>& required_caps);

}  // namespace rebuntu::environment::capability_state
