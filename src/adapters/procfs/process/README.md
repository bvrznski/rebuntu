# Rebuntu Procfs Process Discovery Adapter (Phase 5.24-5.25)

## Overview

This module implements Rebuntu's procfs-based process discovery adapter:
- Reads process information from `/proc/[pid]/`
- Observes: PID + boot context, executable metadata, parent relationship
- Provides bounded resource facts where available
- **PID alone is NOT durable identity**; requires boot/start timestamp context
- **Identity validation** prevents race conditions from PID reuse or process termination

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

4. **Identity Validation**: Process identity must be validated before attributing consequential facts
   - `validate_identity()` checks if process still exists and start timestamp matches
   - Prevents PID reuse attacks where new process gets same PID with different boot time
   - Returns typed outcomes: valid, not-found, reused, or unknown validation state

## API Reference

### ProcessIdentity

```cpp
struct ProcessIdentity {
    int64_t boot_timestamp_ms{-1};  // Boot time in ms since system boot
    int pid{0};                      // Process ID
    
    bool is_valid() const;           // Check if identity is valid
};
```

### IdentityValidation

Result of validating a process identity:

```cpp
enum class IdentityValidation {
    kValid,              // Process identity is valid and process exists
    kNotFound,           // Process /proc/[pid] does not exist (process terminated)
    kReused,             // PID was reused by a new process with different start time
    kUnknown,            // Could not determine validation state (acquisition failed)
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
    // Returns std::nullopt if the process is not found or inaccessible
    virtual std::optional<ProcessObservation> observe_process(
        const ProcessIdentity& identity) = 0;
    
    // Get freshness information about the last observation
    virtual std::chrono::system_clock::time_point get_last_observation_time() const = 0;
    
    // Force refresh: discard cached state and re-observe from procfs
    virtual ProcessDiscoveryResult force_refresh() = 0;
    
    // Validate a process identity by checking if the process still exists
    // and if its start timestamp matches (no PID reuse).
    // Returns IdentityValidation indicating whether the process can be safely
    // used for consequential operations.
    virtual IdentityValidation validate_identity(const ProcessIdentity& identity) = 0;
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

// Validate identity before consequential operations
IdentityValidation validation = adapter->validate_identity(pid);
switch (validation) {
    case IdentityValidation::kValid:
        // Safe to use this identity for consequential facts
        break;
    case IdentityValidation::kNotFound:
        // Process no longer exists - treat as unknown/missing evidence
        break;
    case IdentityValidation::kReused:
        // PID was reused by a different process - cannot trust old observations
        break;
    case IdentityValidation::kUnknown:
        // Could not determine validation state - be conservative
        break;
}
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

## Identity Race Safety

### Problem
When discovering processes and later attributing consequential facts:
1. A process may terminate between discovery and observation
2. Another process may get the same PID with a different start timestamp (PID reuse)
3. Using stale identity information leads to corrupted records

### Solution
The `validate_identity()` method performs a fresh check before any consequential operation:

1. **Process existence check**: Uses `stat(/proc/[pid])` to verify the directory still exists
2. **Timestamp revalidation**: Reads `/proc/[pid]/stat` and verifies the start timestamp matches
   - If timestamps differ, PID was reused by a new process
3. **Typed outcomes**: Returns specific validation states rather than returning null/unknown

### Validation Logic Flow

```
validate_identity(identity)
    ├─ is_valid(identity)? ─NO─> kUnknown
    └─ stat(/proc/[pid])? 
        ├─ fails ─> kNotFound (process terminated)
        └─ exists
            ├─ read /proc/[pid]/stat
            ├─ parse start time from stat
            └─ compare with stored boot_timestamp_ms?
                ├─ matches ─> kValid (safe to use)
                └─ differs ─> kReused (PID reused by different process)
```

## Limitations

1. **Bounded observations**: Some fields may be unavailable if the process terminates during observation
2. **Permission requirements**: Reading certain processes requires appropriate permissions
3. **Timestamp precision**: Boot timestamp is at millisecond resolution
4. **Race window**: There's still a small window between validation and actual use where process could terminate

## Testing

Build the library with:
```bash
make rebuntu-procfs-process
```

Run tests:
```bash
./rebuntu-procfs-process-test