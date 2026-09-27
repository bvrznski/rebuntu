// rebuntu::adapters::procfs::modules — Kernel Module Observation Adapter (Phase 5.32)
//
// This module implements Rebuntu's procfs-based kernel module observation adapter:
//   - Reads loaded modules from /proc/modules
//   - Observes: module name, size, usage count, dependencies, state
//   - Tracks live module metadata including reference counts and usage
//   - Supports module topology (dependency relationships)
//
// Native Interfaces Used:
//   - /proc/modules — kernel module list with usage counts and dependencies
//   - /sys/kernel/irq/ — interrupt information per module (optional extension)
//   - /sys/module/*/refs — reference count for each module
//   - /sys/module/*/refcnt — additional refcount details (if available)
//
// Key Distinctions:
//   - Module identity = module name (unique, stable identifier)
//   - Loaded = currently in kernel memory (present in /proc/modules)
//   - Healthy = loaded AND not in error state
//   - Bound = has active usage (refcnt > 0 or dependencies on it)
//   - Functioning = bound AND not marked as problematic by kernel

#pragma once

#include <system/core/contracts.hpp>
#include <cstdint>
#include <optional>
#include <string>
#include <chrono>
#include <vector>
#include <unordered_map>
#include <memory>

namespace rebuntu::adapters::procfs::modules {

// ============================================================================
// ModuleState — Runtime state of a loaded kernel module
//
// Represents the kernel's view of a module's operational status:
//   - kLoaded: Module is in memory, but may not be functional
//   - kActive: Module is loaded and actively used by other components
//   - kReferenced: Module has references but may be inactive (e.g., waiting for cleanup)
//   - kError: Kernel detected an error condition with this module
// ============================================================================
enum class ModuleState {
    kLoaded,     // Module is in kernel memory
    kActive,     // Module is actively being used
    kReferenced, // Module has references but not necessarily active
    kError,      // Kernel reported an error for this module
};

inline std::string to_string(ModuleState s) {
    switch (s) {
        case ModuleState::kLoaded:     return "loaded";
        case ModuleState::kActive:     return "active";
        case ModuleState::kReferenced: return "referenced";
        case ModuleState::kError:      return "error";
    }
    return "unknown";
}

// ============================================================================
// ModuleIdentity — Stable identity for a kernel module
//
// A module is uniquely identified by its name.
// The major:minor device numbers are not used (modules don't have devices).
// ============================================================================
struct ModuleIdentity {
    std::string name;  // Module name as shown in /proc/modules (e.g., "veth", "nf_conntrack")
};

inline bool operator==(const ModuleIdentity& a, const ModuleIdentity& b) {
    return a.name == b.name;
}

// ============================================================================
// ModuleUsage — How other modules/components use this module
//
// Tracks reference counts and dependencies:
//   - used_by: List of modules that depend on this one
//   - refcnt: Current reference count (0 = not actively used)
// ============================================================================
struct ModuleUsage {
    std::vector<std::string> used_by;  // Modules that depend on this one (from /proc/modules field 3)
    int refcnt{0};                     // Reference count (from /proc/modules field 2, or -1 if not tracked)
};

// ============================================================================
// ModuleObservation — Complete observation of a kernel module
//
// Combines information from /proc/modules and optional sysfs details.
// ============================================================================
struct ModuleObservation {
    ModuleIdentity identity;
    
    // Basic size information
    unsigned long size_bytes{0};       // Module size in bytes (from /proc/modules field 2)
    
    // Usage statistics
    int usage_count{0};                // Number of components using this module (field 3)
    ModuleUsage usage;                 // Detailed usage info
    
    // State information
    ModuleState state{ModuleState::kLoaded};
    
    // Provenance tracking
    std::chrono::system_clock::time_point observed_at{};
    std::string source{"procfs"};      // "procfs" for /proc/modules
};

// ============================================================================
// ModuleTopology — Relationship topology of kernel modules
//
// Represents dependency relationships between modules:
//   - Nodes: individual modules (ModuleObservation)
//   - Edges: dependency relationships (A depends on B means B is used by A)
// ============================================================================
struct ModuleTopology {
    // All observed modules indexed by name
    std::unordered_map<std::string, ModuleObservation> modules_by_name;
    
    // Dependency graph: for each module, who depends on it
    std::unordered_map<std::string, std::vector<std::string>> dependents;  // module -> modules that use it
    
    // Statistics
    size_t total_modules{0};
    size_t active_modules{0};          // Modules with refcnt > 0
    size_t referenced_modules{0};      // Modules with usage_count > 0
    
    std::chrono::system_clock::time_point captured_at{};
    std::chrono::milliseconds capture_duration_ms{0};
};

// ============================================================================
// ModuleObservationResult — Result of kernel module observation
// ============================================================================
struct ModuleObservationResult {
    core::SemanticStatus status;
    std::string description;
    
    // Raw observations (individual modules)
    std::vector<ModuleObservation> modules;
    
    // Topology graph derived from dependencies
    std::optional<ModuleTopology> topology;
    
    std::chrono::system_clock::time_point observed_at{};
    std::chrono::milliseconds elapsed_ms{0};
    
    size_t total_modules{0};
    size_t modules_with_errors{0};     // Modules where observation failed
    
    // Provider provenance
    std::string provider_source{"procfs"};
    
    std::optional<core::Error> error;
};

// ============================================================================
// ModuleAdapter — Interface for procfs kernel module observation
// ============================================================================
class ModuleAdapter {
public:
    virtual ~ModuleAdapter() = default;
    
    // Observe all loaded kernel modules
    virtual ModuleObservationResult observe_modules() = 0;
    
    // Get the full topology of module dependencies
    virtual ModuleTopology get_topology() = 0;
    
    // Resolve a specific module by name
    virtual std::optional<ModuleObservation> resolve_module(std::string_view name) = 0;
};

// ============================================================================
// Factory function
// ============================================================================
std::unique_ptr<ModuleAdapter> make_procfs_modules_adapter();

}  // namespace rebuntu::adapters::procfs::modules