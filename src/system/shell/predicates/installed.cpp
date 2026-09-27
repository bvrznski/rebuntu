// rebuntu::shell::predicates::installed — Installed Predicate Implementation

#include "installed.hpp"
#include <adapters/package_managers/dpkg/types.hpp>
#include <adapters/package_managers/dpkg/implementation.cpp>

namespace rebuntu::shell::predicates {

PredicateResult installed_predicate(const std::string& package_name) {
    // Create dpkg adapter for package inventory
    auto adapter = rebuntu::adapters::package_managers::dpkg::make_dpkg_package_inventory_adapter();
    
    if (!adapter) {
        return PredicateResult::unknown("failed to create dpkg adapter");
    }
    
    // Query the package
    auto result = adapter->observe_all_packages();
    
    // Search for the package in results
    for (const auto& pkg : result.packages) {
        if (pkg.identity.name == package_name) {
            PredicateResult r;
            r.status = core::SemanticStatus::kSuccess;
            r.is_true = true;
            
            // Add evidence
            core::Evidence e;
            e.source = "dpkg";
            e.value = package_name + ":installed:" + pkg.version;
            r.evidence.push_back(std::move(e));
            
            return r;
        }
    }
    
    // Package not found
    PredicateResult r;
    r.status = core::SemanticStatus::kFailure;  // Condition not met
    r.is_true = false;
    r.evidence.emplace_back();
    r.evidence.back().source = "dpkg";
    r.evidence.back().value = package_name + ":not_found";
    return r;
}

}  // namespace rebuntu::shell::predicates