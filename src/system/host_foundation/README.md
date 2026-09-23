# rebuntu::host_foundation — Linux Host Foundation (Phase 2.0)

This module establishes Rebuntu's canonical host foundation contract that defines:

* **HOST_CAPABILITY** = What the Linux host can provide
* **REQUIRED_CAPABILITY** = What Rebuntu requires to operate
* **SUPPORT_DECISION** = Is this host supported for feature X?

## Key Principles

1. **Observation vs Policy**: `systemd present` is observed; `host supports X` is a derived decision based on policy
2. **UNKNOWN is valid**: Acquisition failure is not negative evidence - we preserve UNKNOWN state
3. **Graceful degradation**: Report which assumption is missing, don't fail with "unsupported Linux"

## Architecture

```
HostFoundation (observer)
    ↓ observes
FoundationObservation (what we found)
    ↓ evaluates
SupportDecision (is host supported?)
    → HostFoundationResult (complete assessment)
```

## Operational Modes

| Mode | Description |
|------|-------------|
| kMinimal | Basic CLI operations (no systemd required) |
| kServiceManaged | Service lifecycle via systemd |
| kFullFeature | All Rebuntu features including isolation |

## Usage Example

```cpp
using rebuntu::host_foundation::HostFoundation;

HostFoundation foundation;
auto result = foundation.assess();

if (result.overall_status == HostFoundationStatus::kReady) {
    // All foundations present, can use full feature set
} else if (result.overall_status == HostFoundationStatus::kPartial) {
    // Some features unavailable, check missing_critical_foundations
}
```

## Foundation Types

* kOsRelease - Distribution identification via `/etc/os-release`
* kKernel - Linux kernel availability
* kFilesystem - Unix ownership semantics
* kProcessModel - fork/exec/pipe system calls
* kSystemd - systemd manager for service lifecycle
* kRuntimeDirectories - XDG_RUNTIME_DIR or /run
* kUserNamespace - User namespace support
* kNativeIdentity - NSS facilities (getpwnam, etc.)
* kUmaskSupport - Permission control via umask(2)

## Implementation Notes

* C++20 with Linux native APIs only
* No external dependencies beyond standard library
* Reads `/etc/os-release`, `/proc/version`, `/proc/meminfo`, etc.
* Graceful handling of read-only filesystems, containers, minimal environments