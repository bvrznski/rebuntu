# src/system/environment — Host Environment Discovery

Host environment observation via native mechanisms: procfs, sysfs, cgroups v2.

## Phase 1.9 Implementation Status: CURRENT

The `rebuntu::environment::discovery` namespace provides comprehensive host
environment discovery for installation/setup purposes.

### Discovery Capabilities (Phase 1.9)

| Capability | Type | Description |
|------------|------|-------------|
| DistributionInfo | `discover_distribution()` | OS distribution from /etc/os-release |
| KernelInfo | `discover_kernel()` | Kernel version and architecture |
| ArchitectureInfo | `discover_architecture()` | CPU topology (count, sockets, cores) |
| MemoryInfo | `discover_memory()` | System memory totals from /proc/meminfo |
| StorageInfo | `discover_storage()` | Mount points from /proc/mounts |
| NetworkInfo | `discover_network()` | IPv4/IPv6, Wi-Fi, Ethernet detection |
| SessionInfo | `discover_session()` | Desktop session (X11/Wayland/GNOME/KDE) |
| GpuInfo | `discover_gpu()` | GPU devices via lshw/lspci |
| ShellInfo | `discover_shell()` | Primary shell detection |
| PackageManagerInfo | `discover_package_manager()` | Available package managers |
| ContainerInfo | `discover_container()` | Docker/Podman/LXC detection |

### Native Linux Sources

- `/etc/os-release` — Distribution identification
- `/proc/meminfo` — Memory statistics
- `/proc/cpuinfo` — CPU topology information
- `/proc/mounts` — Mount point listing
- `/sys/class/net/` — Network interface state
- `/proc/sys/net/ipv6/conf/all/disable_ipv6` — IPv6 status

### Preflight Evaluation

The `PreflightEvaluator` class evaluates system readiness:
- `check_distribution_supported()` — Known distribution check
- `check_runtime_available()` — Python runtime validation (minimum 3.8)
- `check_filesystem_writable()` — System directory access
- `check_memory_sufficient()` — Minimum 1 GiB memory
- `check_storage_sufficient()` — Minimum 5 GB free storage

### Discovery Status Semantics

- `kKnown` — Information successfully acquired from native sources
- `kUnknown` — Unable to determine state (not an error)

### Example Usage

```cpp
using namespace rebuntu::environment::discovery;

HostDiscovery discovery;
auto result = discovery.discover();

// Access new Phase 1.9 data
if (result.memory.total_bytes.has_value()) {
    std::cout << "Memory: " << result.memory.total_bytes.value() << " bytes\n";
}

if (!result.storage.mounts.empty()) {
    for (const auto& mount : result.storage.mounts) {
        std::cout << mount.mount_point << ": " 
                  << mount.free_bytes << " free\n";
    }
}
```

### Design Principles

- **No destructive operations** — Discovery is read-only
- **Graceful degradation** — Missing tools don't cause failures
- **Typed results** — No stringly-typed data
- **Evidence-based** — All values traceable to native sources