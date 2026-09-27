// rebuntu::interfaces::inventory_index — Inventory Indexing System (Phase 5.45)
//
// This module establishes Rebuntu's inventory indexing system:
// how inventory entities can be efficiently located via derived indexes
// while maintaining the invariant that index absence is not proof of entity absence.
//
// Key Invariants:
//   - INDEXES ARE DERIVED: Indexes are rebuildable views from authoritative source data
//   - INDEXES ARE NON-AUTHORITATIVE: Source truth always overrides index state
//   - ABSENCE IS UNKNOWN: Missing index entry means "not found in index", not "does not exist"
//
// Design Principles:
//   1. Indexes are computed, not stored authoritative state
//   2. Queries must fallback to source truth when index is absent/stale
//   3. Index rebuilds are bounded operations with cancellation support
//   4. Freshness tracking ensures stale indexes are detected and rebuilt

#pragma once

#include <runtime/contracts.hpp>
#include <system/core/contracts.hpp>
#include <string>
#include <string_view>
#include <chrono>
#include <vector>
#include <memory>
#include <optional>
#include <unordered_map>
#include <functional>

namespace rebuntu::interfaces {

// ============================================================================
// EntityId — Unique identifier for an inventory entity
// ============================================================================
struct EntityId {
    std::string value;

    // Default constructor (empty ID)
    EntityId() = default;
    
    // Explicit constructor from string
    explicit EntityId(std::string v) : value(std::move(v)) {}
    
    // Implicit conversion to std::string_view for convenience
    explicit operator std::string_view() const { return value; }
};

inline bool operator==(const EntityId& a, const EntityId& b) {
    return a.value == b.value;
}

inline bool operator!=(const EntityId& a, const EntityId& b) {
    return !(a == b);
}

// ============================================================================
// IndexKind — Types of indexes supported
// ============================================================================
enum class IndexKind {
    kByName,          // Entity by name (case-sensitive)
    kByType,          // Entities by type/category
    kByLocation,      // Entities by location/path
    kByTag,           // Entities tagged with a key-value pair
    kByState,         // Entities filtered by operational state
};

inline std::string_view to_string(IndexKind k) {
    switch (k) {
        case IndexKind::kByName:     return "by-name";
        case IndexKind::kByType:     return "by-type";
        case IndexKind::kByLocation: return "by-location";
        case IndexKind::kByTag:      return "by-tag";
        case IndexKind::kByState:    return "by-state";
    }
    return "unknown";
}

// ============================================================================
// IndexEntry — A single index entry
//
// Note: This is derived data. It may be stale or absent without indicating
// actual entity absence.
// ============================================================================
struct IndexEntry {
    EntityId entity_id;
    
    // Index key (e.g., name, type, location)
    std::string index_key;
    
    // When this entry was added/updated in the index
    std::chrono::system_clock::time_point indexed_at{};
    
    // Source of truth timestamp for this entity
    std::chrono::system_clock::time_point source_valid_until{};
};

// ============================================================================
// IndexMetrics — Runtime metrics for indexing operations
// ============================================================================
struct IndexMetrics {
    // Index statistics
    size_t total_entries = 0;
    size_t index_count = 0;  // Number of distinct indexes
    
    // Build/refresh metrics
    std::chrono::milliseconds last_build_duration_ms{0};
    size_t entries_built = 0;
    size_t rebuilds_performed = 0;
    
    // Query metrics
    size_t queries_hitting_index = 0;
    size_t queries_fallback_to_source = 0;
    
    // Freshness tracking
    std::chrono::milliseconds max_staleness_ms{0};
};

// ============================================================================
// IndexState — Current state of an index
// ============================================================================
enum class IndexState {
    kInitializing,     // Index is being built for the first time
    kReady,            // Index is ready and fresh
    kStale,            // Index may be outdated (beyond freshness threshold)
    kRebuilding,       // Index is currently rebuilding
    kFailed,           // Index build failed
};

inline std::string_view to_string(IndexState s) {
    switch (s) {
        case IndexState::kInitializing: return "initializing";
        case IndexState::kReady:        return "ready";
        case IndexState::kStale:        return "stale";
        case IndexState::kRebuilding:   return "rebuilding";
        case IndexState::kFailed:       return "failed";
    }
    return "unknown";
}

// ============================================================================
// IndexBuildRequest — Request to build/rebuild an index
// ============================================================================
struct IndexBuildRequest {
    std::string id;                         // Unique request ID
    
    std::chrono::system_clock::time_point created_at{};
    
    // Which indexes to build (empty = all)
    std::optional<std::vector<IndexKind>> kinds;
    
    // Budget constraints
    size_t max_entries = 100000;            // Max entries to process
    std::chrono::milliseconds timeout_ms{60000};  // Build timeout
    
    static IndexBuildRequest make(std::string id) {
        IndexBuildRequest r;
        r.id = std::move(id);
        r.created_at = std::chrono::system_clock::now();
        return r;
    }
};

// ============================================================================
// IndexBuildResult — Result of an index build operation
// ============================================================================
struct IndexBuildResult {
    core::SemanticStatus status{core::SemanticStatus::kUnknown};
    std::string description;
    
    std::string build_request_id;
    
    // When the build started/completed
    std::chrono::system_clock::time_point started_at{};
    std::chrono::system_clock::time_point completed_at{};
    
    std::chrono::milliseconds elapsed_ms{0};
    
    // What was built
    size_t entries_built = 0;
    size_t indexes_rebuilt = 0;
    
    // Errors encountered (non-fatal, may indicate stale data)
    std::vector<std::pair<EntityId, core::Error>> errors;
    
    std::optional<core::Error> fatal_error;
};

// ============================================================================
// IndexQueryResult — Result of a query that may hit index and fallback
//
// This is the key type for Task 5.45: it distinguishes between:
//   - Found in index (may be stale)
//   - Not in index but found in source (fallback successful)
//   - Not in index and not in source (authoritative absence)
// ============================================================================
struct IndexQueryResult {
    // Overall outcome
    core::SemanticStatus status{core::SemanticStatus::kUnknown};
    
    // Was the entity found?
    bool found = false;
    
    // Where was it found? (index vs source truth)
    enum class Source {
        kIndex,              // Found in derived index only
        kSourceVerified,     // Not in index but verified via source lookup
    } source{Source::kIndex};
    
    // Entity ID if found
    std::optional<EntityId> entity_id;
    
    // Evidence that supports this result
    std::vector<core::Evidence> evidence;
    
    // Timing information
    std::chrono::milliseconds index_lookup_time_ms{0};
    std::chrono::milliseconds source_lookup_time_ms{0};
};

// ============================================================================
// InventoryIndexer — Interface for inventory indexing operations
//
// This provides:
//   - Index building/rebuilding (derived, non-authoritative)
//   - Query with automatic fallback to source truth
//   - Freshness tracking and staleness detection
// ============================================================================
class InventoryIndexer {
public:
    virtual ~InventoryIndexer() = default;
    
    // Lifecycle management
    virtual core::Outcome configure(
        std::chrono::milliseconds stale_threshold,
        size_t max_entries_per_index
    ) = 0;
    
    virtual core::Outcome start() = 0;
    virtual core::Outcome stop() = 0;
    
    // Index building/rebuilding
    virtual IndexBuildResult build(const IndexBuildRequest& request) = 0;
    
    // Check if an index is stale (beyond freshness threshold)
    virtual bool is_index_stale(IndexKind kind,
                               std::chrono::milliseconds threshold) const = 0;
    
    // Query the index with automatic fallback
    virtual IndexQueryResult query_by_id(const EntityId& id) = 0;
    
    virtual IndexQueryResult query_by_name(std::string_view name) = 0;
    
    virtual std::vector<IndexQueryResult> query_by_type(std::string_view type) = 0;
    
    // Get current index state
    virtual IndexState get_index_state(IndexKind kind) const = 0;
    
    // Get metrics for monitoring and debugging
    virtual IndexMetrics get_metrics() const = 0;
};

// ============================================================================
// Factory function
// ============================================================================
std::unique_ptr<InventoryIndexer> make_inventory_indexer();

}  // namespace rebuntu::interfaces

namespace std {

template <> struct hash<rebuntu::interfaces::EntityId> {
    size_t operator()(const rebuntu::interfaces::EntityId& id) const noexcept {
        return std::hash<std::string>{}(id.value);
    }
};

}  // namespace std