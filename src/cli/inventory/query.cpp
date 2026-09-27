// rebuntu::cli::inventory::query — CLI Inventory Query Implementation (Phase 5.60)
//
// This module provides the concrete implementation for querying inventory data:
//   - Fetches from observation providers (dpkg, systemd, procfs)
//   - Tracks freshness and source provenance
//   - Returns structured results with error handling
//

#include "query.hpp"
#include <adapters/package_managers/dpkg/types.hpp>

namespace rebuntu::cli::inventory {

namespace dpkg = rebuntu::adapters::package_managers::dpkg;

// ============================================================================
// InventoryQueryImpl — Concrete query implementation
// ============================================================================

class InventoryQueryImpl : public InventoryQuery {
public:
    ~InventoryQueryImpl() override = default;
    
    QueryResult query_all(const QueryOptions& options) override;
    
    std::optional<EntityInfo> query_by_id(
        const std::string& id,
        std::chrono::milliseconds freshness_threshold) override
    {
        (void)id;
        (void)freshness_threshold;
        return std::nullopt;
    }
    
    std::vector<InventoryKind> supported_kinds() const override {
        return {InventoryKind::kPackage, InventoryKind::kUnknown};
    }

private:
    QueryResult query_packages(const QueryOptions& options);
};

// ============================================================================
// Public interface
// ============================================================================

std::unique_ptr<InventoryQuery> make_inventory_query() {
    return std::make_unique<InventoryQueryImpl>();
}

// ============================================================================
// Implementation methods
// ============================================================================

QueryResult InventoryQueryImpl::query_all(const QueryOptions& options) {
    QueryResult result;
    
    auto start_time = std::chrono::system_clock::now();
    
    switch (options.kind) {
        case InventoryKind::kPackage:
            result = query_packages(options);
            break;
        case InventoryKind::kUnknown:
            result.status = core::SemanticStatus::kFailure;
            result.description = "inventory kind not specified";
            break;
        default: {
            std::string unknown_kind_str = to_string(options.kind);
            result.status = core::SemanticStatus::kFailure;
            result.description = "unsupported inventory kind: " + unknown_kind_str;
            break;
        }
    }
    
    auto end_time = std::chrono::system_clock::now();
    auto elapsed = end_time - start_time;
    result.elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed);
    
    return result;
}

QueryResult InventoryQueryImpl::query_packages(const QueryOptions& options) {
    QueryResult result;
    
    // Get the dpkg adapter
    auto adapter = dpkg::make_dpkg_package_inventory_adapter();
    if (!adapter) {
        result.status = core::SemanticStatus::kFailure;
        result.description = "failed to create dpkg adapter";
        return result;
    }
    
    // Perform the observation
    auto dpkg_result = adapter->observe_all_packages();
    
    // Map dpkg results to our EntityInfo format
    for (const auto& pkg : dpkg_result.packages) {
        EntityInfo info;
        info.id = pkg.identity.name + ":" + pkg.identity.architecture;
        info.name = pkg.identity.name;
        info.category = "package";
        
        // Add package attributes
        info.attributes.emplace_back("version", pkg.version);
        if (pkg.epoch.has_value()) {
            info.attributes.emplace_back("epoch", pkg.epoch.value());
        }
        if (!pkg.description.empty()) {
            info.attributes.emplace_back("description", pkg.description);
        } else {
            info.attributes.emplace_back("description", "N/A");
        }
        
        // Map install state to category-like value
        std::string state_str = dpkg::to_string(pkg.install_state);
        info.attributes.emplace_back("state", state_str);
        
        // Build freshness report
        auto now = std::chrono::system_clock::now();
        auto age_ms = std::chrono::duration_cast<std::chrono::milliseconds>(now - pkg.observed_at);
        
        FreshnessReport freshness;
        freshness.observed_at = pkg.observed_at;
        freshness.source = "dpkg";
        freshness.source_kind = FreshnessReport::Source::kSourceVerified;
        freshness.age_ms = age_ms;
        freshness.is_stale = (age_ms > options.freshness_threshold_ms);
        
        info.freshness = freshness;
        
        // Add to result
        if (options.max_results == 0 || result.entities.size() < options.max_results) {
            result.entities.push_back(std::move(info));
        }
    }
    
    // Use success factory to properly set counts and status
    return QueryResult::success(std::move(result.entities));
}

}  // namespace rebuntu::cli::inventory