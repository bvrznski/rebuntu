# rebuntu::adapters::procfs::modules — Kernel Module Observation Adapter (Phase 5.32)

This module implements Rebuntu's procfs-based kernel module observation adapter.

## Overview

The modules adapter observes loaded kernel modules through native Linux interfaces:

- **Loaded** = currently in kernel memory
- **Active** = loaded AND actively used by other components  
- **Referenced** = has dependencies or reference count > 0
- **Functioning** = active AND not in error state

## Native Interfaces Used

### Primary: /proc/modules
```
nf_conntrack_netlink 57344 0 - Live 0x0000000000000000
veth 45056 0 - Live 0x0000000000000000
vhost_net 32768 1 vhost, Live 0x0000000000000000
```

Format: `module_name size usage_count dependencies refcnt state owner`

## Key Distinctions

- **Module Identity** = module name (unique, stable identifier)
- **Size** = memory footprint in bytes
- **Usage Count** = number of components using this module
- **Dependencies** = which modules depend on this one (used_by field)
- **State** = kernel's view of module status

## API Overview

```cpp
namespace rebuntu::adapters::procfs::modules {

// Main observation result
struct ModuleObservationResult {
    core::SemanticStatus status;
    std::vector<ModuleObservation> modules;
    std::optional<ModuleTopology> topology;
};

// Individual module observation
struct ModuleObservation {
    ModuleIdentity identity;
    unsigned long size_bytes;
    int usage_count;
    ModuleUsage usage;      // detailed usage info
    ModuleState state;      // runtime state
};

// Topology graph of dependencies
struct ModuleTopology {
    std::unordered_map<std::string, ModuleObservation> modules_by_name;
    std::unordered_map<std::string, std::vector<std::string>> dependents;
    size_t total_modules, active_modules, referenced_modules;
};

class ModuleAdapter {
public:
    virtual ModuleObservationResult observe_modules() = 0;
    virtual ModuleTopology get_topology() = 0;
    virtual std::optional<ModuleObservation> resolve_module(std::string_view name) = 0;
};

std::unique_ptr<ModuleAdapter> make_procfs_modules_adapter();

}
```

## Usage Example

```cpp
auto adapter = rebuntu::adapters::procfs::modules::make_procfs_modules_adapter();
auto result = adapter->observe_modules();

if (result.status == core::SemanticStatus::kSuccess) {
    for (const auto& module : result.modules) {
        std::cout << "Module: " << module.identity.name
                  << ", Size: " << module.size_bytes
                  << ", Usage: " << module.usage_count << "\n";
    }
}
```

## Implementation Notes

- Reads are non-blocking and bounded by file size
- Topology is computed in-memory from observed dependencies
- State transitions (Loaded -> Active) reflect kernel's current view