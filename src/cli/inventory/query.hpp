// rebuntu::cli::inventory::query — CLI Inventory Query Interface (Phase 5.60)
//
// This module defines the query interface for inventory inspection:
//   - Fetch entities from observation providers
//   - Track freshness and source provenance
//   - Return structured results with error handling
//

#pragma once

#include "types.hpp"
#include <memory>
#include <chrono>

namespace rebuntu::cli::inventory {

// ============================================================================
// QueryOptions — Configuration for inventory queries
// ============================================================================
struct QueryOptions {
    // Which kind of entities to query
    InventoryKind kind{InventoryKind::kUnknown};
    
    // Freshness threshold - entities older than this are marked stale
    std::chrono::milliseconds freshness_threshold_ms{std::chrono::minutes(5)};
    
    // Maximum number of results to return (0 = unlimited)
    size_t max_results{0};
    
    // Whether to include partial observations in the result
    bool include_partial{true};
};

// ============================================================================
// QueryError — Errors that can occur during inventory querying
// ============================================================================
struct QueryError {
    std::string code;        // Machine-readable error code
    std::string message;     // Human-readable description
};

// ============================================================================
// InventoryQuery — Interface for querying inventory data
//
// This interface abstracts the observation providers and provides:
//   - Typed entity queries with freshness tracking
//   - Source provenance for each observation
//   - Bounded operations with timeout/cancellation support
// ============================================================================
class InventoryQuery {
public:
    virtual ~InventoryQuery() = default;
    
    // Query all entities of a given kind
    virtual QueryResult query_all(const QueryOptions& options) = 0;
    
    // Query a specific entity by ID
    virtual std::optional<EntityInfo> query_by_id(
        const std::string& id,
        std::chrono::milliseconds freshness_threshold) = 0;
    
    // Get the list of supported inventory kinds
    virtual std::vector<InventoryKind> supported_kinds() const = 0;
};

// ============================================================================
// make_inventory_query — Factory function to create an InventoryQuery
//
// Creates a query instance backed by available observation providers.
// ============================================================================
std::unique_ptr<InventoryQuery> make_inventory_query();

}  // namespace rebuntu::cli::inventory