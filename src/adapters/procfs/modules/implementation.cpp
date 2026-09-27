// rebuntu::adapters::procfs::modules — Kernel Module Observation Implementation (Phase 5.32)
//
// This module implements the procfs-based kernel module observation adapter:
//   - Reads module information from /proc/modules
//   - Observes: name, size, usage count, dependencies, state
//   - Tracks live module metadata

#include "adapters/procfs/modules/types.hpp"

#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <filesystem>
#include <chrono>
#include <optional>


namespace rebuntu::adapters::procfs::modules {

// ============================================================================
// Helper: Parse a line from /proc/modules
//
// Format (from man 5 proc):
//   module_name size usage_count dependencies refcnt state owner
//
// Example:
//   nf_conntrack_netlink 57344 0 - Live 0x0000000000000000
//   veth 45056 0 - Live 0x0000000000000000
//   vhost_net 32768 1 vhost, Live 0x0000000000000000
// ============================================================================

static std::optional<ModuleObservation> parse_module_line(const std::string& line) {
    if (line.empty()) {
        return std::nullopt;
    }
    
    ModuleObservation observation;
    
    // Split the line by spaces
    std::istringstream iss(line);
    std::vector<std::string> fields;
    std::string field;
    
    while (iss >> field) {
        fields.push_back(field);
    }
    
    // Minimum expected: module_name size usage_count dependencies state address
    if (fields.size() < 5) {
        return std::nullopt;
    }
    
    // Field 0: module name
    observation.identity.name = fields[0];
    
    // Field 1: size in bytes (decimal)
    try {
        observation.size_bytes = std::stoul(fields[1]);
    } catch (...) {
        observation.size_bytes = 0;
    }
    
    // Field 2: usage count (decimal, may be negative if not tracked)
    try {
        observation.usage_count = std::stoi(fields[2]);
    } catch (...) {
        observation.usage_count = 0;
    }
    
    // Field 3: dependencies (comma-separated list or "-" for none)
    if (fields[3] != "-") {
        std::istringstream dep_iss(fields[3]);
        std::string dep;
        while (std::getline(dep_iss, dep, ',')) {
            observation.usage.used_by.push_back(dep);
        }
    }
    
    // Field 4: state (typically "Live" for healthy modules)
    if (fields[4] == "Live") {
        observation.state = ModuleState::kLoaded;
        if (observation.usage_count > 0) {
            observation.state = ModuleState::kActive;
        }
    } else if (fields[4] == "Error") {
        observation.state = ModuleState::kError;
    } else {
        // For unknown states, mark as loaded
        observation.state = ModuleState::kLoaded;
    }
    
    // Set provenance
    observation.observed_at = std::chrono::system_clock::now();
    observation.source = "procfs";
    
    return observation;
}

// ============================================================================
// ProcfsModulesAdapter Implementation
// ============================================================================

class ProcfsModulesAdapter : public ModuleAdapter {
public:
    ProcfsModulesAdapter() = default;
    ~ProcfsModulesAdapter() override = default;
    
    ModuleObservationResult observe_modules() override {
        ModuleObservationResult result;
        result.observed_at = std::chrono::system_clock::now();
        
        auto start_time = std::chrono::steady_clock::now();
        
        std::ifstream file("/proc/modules");
        if (!file.is_open()) {
            result.status = core::SemanticStatus::kFailure;
            result.description = "Failed to open /proc/modules";
            result.error = core::Error{"E_MODULES_UNAVAILABLE", "Cannot read kernel module list"};
            return result;
        }
        
        std::vector<std::optional<ModuleObservation>> temp_modules;
        std::unordered_map<std::string, size_t> name_to_index;
        
        std::string line;
        while (std::getline(file, line)) {
            auto module = parse_module_line(line);
            if (module) {
                // Track dependency relationships
                for (const auto& dep : module->usage.used_by) {
                    dependents_[dep].push_back(module->identity.name);
                }
                
                temp_modules.push_back(std::move(*module));
            }
        }
        
        file.close();
        
        // Build the result
        for (const auto& module : temp_modules) {
            if (module) {
                result.modules.push_back(std::move(*module));
                name_to_index[result.modules.back().identity.name] = result.modules.size() - 1;
            }
        }
        
        // Build topology graph
        result.topology = build_topology_graph(result.modules);
        
        auto end_time = std::chrono::steady_clock::now();
        result.elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(
            end_time - start_time);
        
        result.total_modules = result.modules.size();
        result.provider_source = "procfs";
        result.status = core::SemanticStatus::kSuccess;
        result.description = "Successfully observed kernel modules";
        
        return result;
    }
    
    ModuleTopology get_topology() override {
        auto result = observe_modules();
        if (result.topology) {
            return *std::move(result.topology);
        }
        return ModuleTopology{};
    }
    
    std::optional<ModuleObservation> resolve_module(std::string_view name) override {
        // For now, just search the observed modules
        auto all_modules = observe_modules();
        
        if (all_modules.status != core::SemanticStatus::kSuccess) {
            return std::nullopt;
        }
        
        for (const auto& module : all_modules.modules) {
            if (module.identity.name == name) {
                return module;
            }
        }
        
        return std::nullopt;
    }

private:
    // Map for building dependency relationships
    std::unordered_map<std::string, std::vector<std::string>> dependents_;
    
    ModuleTopology build_topology_graph(const std::vector<ModuleObservation>& modules) {
        ModuleTopology topology;
        topology.captured_at = std::chrono::system_clock::now();
        
        auto start_time = std::chrono::steady_clock::now();
        
        // Index modules by name
        for (const auto& m : modules) {
            topology.modules_by_name[m.identity.name] = m;
        }
        
        // Build dependents map from observed dependencies
        for (const auto& [name, module] : topology.modules_by_name) {
            for (const auto& dep : module.usage.used_by) {
                dependents_[dep].push_back(name);
            }
        }
        
        // Copy to topology's dependents map
        topology.dependents = dependents_;
        
        // Count statistics
        for (const auto& [name, m] : topology.modules_by_name) {
            if (m.usage_count > 0) {
                topology.active_modules++;
            }
            if (!m.usage.used_by.empty()) {
                topology.referenced_modules++;
            }
            topology.total_modules++;
        }
        
        auto end_time = std::chrono::steady_clock::now();
        topology.capture_duration_ms = std::chrono::duration_cast<std::chrono::milliseconds>(
            end_time - start_time);
        
        return topology;
    }
};

// ============================================================================
// Factory function
// ============================================================================

std::unique_ptr<ModuleAdapter> make_procfs_modules_adapter() {
    return std::make_unique<ProcfsModulesAdapter>();
}

}  // namespace rebuntu::adapters::procfs::modules