# Container Runtime Discovery Adapter (Phase 5.30)

This module implements Rebuntu's container/runtime boundary discovery system.

## Design Principles

### Evidence-Based Detection Only
We detect containers ONLY from reliable evidence sources:
- Filesystem markers (e.g., `/.dockerenv`, `/.podman-containers`)
- Environment variables (e.g., `container=...`, `PODMAN=1`)
- Cgroup entries (for membership evidence, not inference)
- DMI/product information (for virtualization hints)

### Critical: No Inference from Cgroup Paths
We do NOT equate cgroup path substrings with definitive container identity:
- ❌ `/docker/` substring ≠ Docker runtime (could be a non-container process in systemd slice named "docker")
- ✅ `/.dockerenv` file exists = verified Docker environment

### Observation != Inference != Recommendation
- **Observation** = raw data from native Linux source
- **Inference** = interpretation of observations (requires validation)
- **Recommendation** = action based on validated conclusion

## Native Interfaces Used

| Source | Purpose |
|--------|---------|
| `/proc/[pid]/cgroup` | Raw cgroup membership evidence |
| `/proc/[pid]/environ` | Environment variables for runtime detection |
| `/proc/self/mountinfo` | Filesystem mount evidence (reserved) |
| `/sys/class/dmi/id/*` | Virtualization detection via DMI |

## Key Types

### ContainerRuntimeType
Validated container runtime identity:
- `kNone` - Not in a container
- `kDocker` - Docker container runtime (validated)
- `kPodman` - Podman container runtime (validated)  
- `kLXC` - LXC container runtime (validated)
- `kSystemdNspawn` - systemd-nspawn container runtime (validated)

### EvidenceSource
Where evidence came from:
- `kProcCgroup` - `/proc/[pid]/cgroup`
- `kProcEnviron` - `/proc/[pid]/environ`
- `kProcMountinfo` - `/proc/self/mountinfo`
- `kSysClassDMI` - `/sys/class/dmi/id/*`
- `kFileSystemEntry` - File existence (e.g., `/.dockerenv`)

### ContainerEvidence
Raw observation with provenance:
```cpp
struct ContainerEvidence {
    EvidenceSource source;
    std::string key;       // What we observed
    std::string value;     // Observed value
    std::chrono::time_point observed_at;
};
```

## Usage

```cpp
#include <adapters/container/types.hpp>

auto adapter = rebuntu::adapters::container::make_container_discovery_adapter();
auto result = adapter->observe_container();

if (result.is_container) {
    std::cout << "Running in: " 
              << rebuntu::adapters::container::to_string(result.runtime_type)
              << "\n";
}
```

## Validation Rules

A runtime type is ONLY assigned when MULTIPLE evidence sources support it:
1. Filesystem marker exists
2. Environment variable indicates specific runtime
3. (Optional) Cgroup membership confirms

The `ValidationInfo` struct tracks which sources were validated.