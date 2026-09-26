# Rebuntu Procfs Process Discovery Adapter (Phase 5.24)

## Overview

This module implements Rebuntu's procfs-based process discovery adapter:
- Reads process information from `/proc/[pid]/`
- Observes: PID + boot context, executable metadata, parent relationship
- Provides bounded resource facts where available
- **PID alone is NOT durable identity**; requires boot/start timestamp context

## Native Interfaces Used

- `/proc/[pid]/stat` — process state and timing information (PPID, start time, etc.)
- `/proc/[pid]/cmdline` — command line arguments
- `/proc/[pid]/exe` — symbolic link to executable path
- `/proc/[pid]/status` — additional process metadata

## Key Distinctions

1. **ProcessIdentity** = `(boot_timestamp, pid)` pair for durable identity
   - Boot context ensures PID reuse is handled correctly
   - Two processes with the same PID but different boot timestamps are distinct

2. **Executable path may change** during process lifetime (e.g., exec)

3. **Resource facts are bounded** and may be unavailable if:
   - The process terminates during observation
   - Insufficient permissions to read the process info

## API Reference

### ProcessIdentity

```cpp
struct ProcessIdentity {
    int64_t boot_timestamp_ms{-1};  // Boot time in ms since system boot
    int pid{0};                      // Process ID
    
    bool is_valid() const;           // Check if identity is valid
};
```

### ProcessState

Process states from Linux:
- `kRunning`, `kSleeping`, `kDiskSleep`, `kZombie`
- `kStopped`, `kTracing`, `kDead`, `kWakekill`
- `kParked`, `kIdle`

### ProcessDiscoveryAdapter Interface

```cpp
class ProcessDiscoveryAdapter {
public:
    virtual ~ProcessDiscoveryAdapter() = default;
    
    // Observe all processes currently visible from procfs
    virtual ProcessDiscoveryResult observe_all_processes() = 0;
    
    // Observe a specific process by its stable identity (boot + PID)
    virtual std::optional<ProcessObservation> observe_process(
        const ProcessIdentity& identity) = 0;
    
    // Get freshness information about the last observation
    virtual std::chrono::system_clock::time_point get_last_observation_time() const = 0;
    
    // Force refresh: discard cached state and re-observe from procfs
    virtual ProcessDiscoveryResult force_refresh() = 0;
};
```

### Factory Function

```cpp
std::unique_ptr<ProcessDiscoveryAdapter> make_procfs_process_discovery_adapter();
```

## Usage Example

```cpp
#include "adapters/procfs/process/types.hpp"

using namespace rebuntu::adapters::procfs::process;

auto adapter = make_procfs_process_discovery_adapter();

// Discover all processes
auto result = adapter->observe_all_processes();

if (result.status == core::SemanticStatus::kSuccess) {
    for (const auto& proc : result.processes) {
        std::cout << "PID: " << proc.identity.pid 
                  << ", State: " << to_string(proc.state)
                  << ", Executable: " << proc.executable.executable_path
                  << "\n";
    }
}

// Observe specific process by identity
ProcessIdentity pid{.boot_timestamp_ms = 123456789, .pid = 1234};
auto observation = adapter->observe_process(pid);
```

## Implementation Details

The implementation reads from `/proc` filesystem using native Linux syscalls:
- `opendir()` / `readdir()` to scan `/proc`
- `readlink()` to read executable symlinks
- File parsing for stat/cmdline/status files

The adapter calculates process uptime by combining:
1. Current system time (from `clock_gettime()`)
2. System uptime (from `/proc/uptime`)
3. Process start time in clock ticks (from `/proc/[pid]/stat`)

## Limitations

1. **Bounded observations**: Some fields may be unavailable if the process terminates during observation
2. **Permission requirements**: Reading certain processes requires appropriate permissions
3. **Timestamp precision**: Boot timestamp is at millisecond resolution
4. **No caching**: Each `force_refresh()` performs a full scan of `/proc`

## Testing

Build the library with:
```bash
make rebuntu-procfs-process