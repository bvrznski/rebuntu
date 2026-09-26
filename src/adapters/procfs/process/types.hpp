// rebuntu::adapters::procfs::process — Procfs Process Discovery Adapter (Phase 5.24)
//
// This module implements Rebuntu's procfs-based process discovery adapter:
//   - Reads process information from /proc/[pid]/
//   - Observes: PID + boot context, executable metadata, parent relationship
//   - Provides bounded resource facts where available
//   - PID alone is NOT durable identity; requires boot/start timestamp context
//
// Native Interfaces Used:
//   - /proc/[pid]/stat — process state and timing information (PPID, start time, etc.)
//   - /proc/[pid]/cmdline — command line arguments
//   - /proc/[pid]/exe — symbolic link to executable path
//   - /proc/[pid]/status — additional process metadata
//
// Key Distinctions:
//   - ProcessIdentity = (boot_timestamp, pid) pair for durable identity
//   - Boot context ensures PID reuse is handled correctly
//   - Executable path may change during process lifetime (e.g., exec)
//   - Resource facts are bounded and may be unavailable

#pragma once

#include <system/core/contracts.hpp>
#include <cstdint>
#include <memory>
#include <optional>
#include <string>
#include <chrono>
#include <vector>

namespace rebuntu::adapters::procfs::process {

// ============================================================================
// ProcessIdentity — Stable identity for a process
//
// A process is uniquely identified by the combination of:
//   - boot_timestamp: The system boot time when this process was started
//     (from /proc/[pid]/stat's starttime field, scaled by ticks_per_second)
//   - pid: The process ID
//
// This combination ensures that even if PID is reused, we can distinguish
// between different invocations of processes with the same executable.
// ============================================================================
struct ProcessIdentity {
    int64_t boot_timestamp_ms{-1};      // Boot time when process started (milliseconds since system boot)
    int pid{0};                         // Process ID (int instead of pid_t to avoid sys/types.h dependency)
    
    bool is_valid() const {
        return boot_timestamp_ms > 0 && pid > 0;
    }
};

inline bool operator==(const ProcessIdentity& a, const ProcessIdentity& b) {
    return a.boot_timestamp_ms == b.boot_timestamp_ms &&
           a.pid == b.pid;
}

// ============================================================================
// ProcessState — State of a process from Linux perspective
//
// Mirrors the state codes in /proc/[pid]/stat:
//   R: Running, S: Sleeping, D: Disk sleep, Z: Zombie, T: Stopped, X: Dead
// ============================================================================
enum class ProcessState {
    kUnknown,        // State unknown (cannot read)
    kRunning,        // R - Running or runnable
    kSleeping,       // S - Interruptible sleep
    kDiskSleep,      // D - Uninterruptible sleep (disk I/O)
    kZombie,         // Z - Zombie/defunct (terminated but not reaped)
    kStopped,        // T - Stopped (by signal or debugger)
    kTracing,        // t - Tracing stop (ptrace)
    kDead,           // X - Dead
    kWakekill,       // W - Wakekill (waking from sleep)
    kParked,         // P - Parked (arm64)
    kIdle,           // I - Idle kernel thread
};

inline std::string to_string(ProcessState s) {
    switch (s) {
        case ProcessState::kUnknown:    return "unknown";
        case ProcessState::kRunning:    return "running";
        case ProcessState::kSleeping:   return "sleeping";
        case ProcessState::kDiskSleep:  return "disk-sleep";
        case ProcessState::kZombie:     return "zombie";
        case ProcessState::kStopped:    return "stopped";
        case ProcessState::kTracing:    return "tracing-stop";
        case ProcessState::kDead:       return "dead";
        case ProcessState::kWakekill:   return "wakekill";
        case ProcessState::kParked:     return "parked";
        case ProcessState::kIdle:       return "idle";
    }
    return "unknown";
}

// ============================================================================
// ProcessResourceUsage — Bounded resource usage information for a process
//
// Obtained from /proc/[pid]/stat and /proc/[pid]/status.
// Values are bounded and may be unavailable if the process terminates
// during observation or lacks permissions.
// ============================================================================
struct ProcessResourceUsage {
    uint64_t vm_rss_kb{0};              // Resident set size (physical memory)
    uint64_t vm_swap_kb{0};             // Swapped volume (from Status:VmSwap)
    uint64_t vm_peak_kb{0};             // Peak virtual memory size
    uint64_t vm_size_kb{0};             // Total program size
    
    // CPU time (in clock ticks)
    uint64_t utime_ticks{0};            // User mode CPU time
    uint64_t stime_ticks{0};            // System mode CPU time
    uint64_t cutime_ticks{0};           // Children's user time
    uint64_t cstime_ticks{0};           // Children's system time
    
    // Priority and nice values
    int priority{0};
    int nice{0};
    
    // Thread count (bounded: may be unavailable)
    std::optional<int> thread_count;
};

// ============================================================================
// ProcessExecutableInfo — Executable metadata for a process
//
// Includes the executable path, command line arguments, and any symlink
// information from /proc/[pid]/exe.
// ============================================================================
struct ProcessExecutableInfo {
    std::string executable_path;        // Path from /proc/[pid]/exe
    std::vector<std::string> cmdline;   // Command line arguments (from /proc/[pid]/cmdline)
    bool has_executable_link{false};    // True if /proc/[pid]/exe exists and is readable
};

// ============================================================================
// ProcessParentRelationship — Parent-child relationship information
//
// The parent is identified by boot context + PID to ensure stable identity.
// ============================================================================
struct ProcessParentRelationship {
    std::optional<ProcessIdentity> ppid_with_boot;  // Parent's identity (may be unavailable)
    int64_t ppid_starttime_ms{-1};                   // Parent's start time if known
};

// ============================================================================
// ProcessObservation — Complete observation for a single process
//
// Combines all available information from procfs with proper provenance.
// ============================================================================
struct ProcessObservation {
    ProcessIdentity identity;           // Stable identity (boot + PID)
    
    ProcessState state{ProcessState::kUnknown};
    std::string state_description;      // Human-readable state (from /proc/stat)
    
    // Timing information
    int64_t start_time_ms{-1};          // Start time in ms since boot
    uint64_t uptime_seconds{0};         // Process uptime in seconds
    
    // Executable metadata
    ProcessExecutableInfo executable;
    
    // Parent relationship
    ProcessParentRelationship parent;
    
    // Resource usage (bounded, may be unavailable)
    ProcessResourceUsage resources;
    
    // Provenance tracking
    std::chrono::system_clock::time_point observed_at{};
    std::string source{"procfs"};       // "procfs" for /proc/[pid]/
};

// ============================================================================
// ProcessDiscoveryResult — Result of process discovery operation
//
// Contains all observations, statistics, and timing information.
// ============================================================================
struct ProcessDiscoveryResult {
    core::SemanticStatus status;
    std::string description;
    
    // All observed processes
    std::vector<ProcessObservation> processes;
    
    // Statistics
    size_t total_processes{0};
    size_t running_processes{0};
    size_t sleeping_processes{0};
    size_t zombie_processes{0};
    size_t other_processes{0};
    
    // Resource usage aggregates (where available)
    uint64_t total_rss_kb{0};           // Sum of resident set sizes
    std::optional<uint64_t> max_rss_kb; // Maximum RSS among processes
    
    // Timing
    std::chrono::system_clock::time_point observed_at{};
    std::chrono::milliseconds elapsed_ms{0};
    
    // Provider provenance
    std::string provider_source{"procfs"};
    
    // Errors encountered during discovery (non-fatal)
    std::vector<std::pair<int, core::Error>> errors;  // pid -> error mapping
    
    std::optional<core::Error> fatal_error;
};

// ============================================================================
// ProcessDiscoveryAdapter — Interface for procfs process discovery
//
// Provides bounded, cancellable, freshness-aware process observation:
//   - observe_all_processes: Discover all processes in the system
//   - observe_process: Observe a specific process by identity
//   - get_freshness: Check when last observation was performed
// ============================================================================
class ProcessDiscoveryAdapter {
public:
    virtual ~ProcessDiscoveryAdapter() = default;
    
    // Observe all processes currently visible from procfs
    // Returns observations sorted by PID for deterministic iteration
    virtual ProcessDiscoveryResult observe_all_processes() = 0;
    
    // Observe a specific process by its stable identity (boot + PID)
    // Returns std::nullopt if the process is not found or inaccessible
    virtual std::optional<ProcessObservation> observe_process(
        const ProcessIdentity& identity) = 0;
    
    // Get freshness information about the last observation
    // Returns the timestamp of the last complete observation, if any
    virtual std::chrono::system_clock::time_point get_last_observation_time() const = 0;
    
    // Force refresh: discard cached state and re-observe from procfs
    // This is idempotent and safe to call multiple times
    virtual ProcessDiscoveryResult force_refresh() = 0;
};

// ============================================================================
// Factory function
// ============================================================================
std::unique_ptr<ProcessDiscoveryAdapter> make_procfs_process_discovery_adapter();

}  // namespace rebuntu::adapters::procfs::process