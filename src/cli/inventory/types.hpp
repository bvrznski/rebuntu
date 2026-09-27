// rebuntu::cli::inventory — CLI Inventory Inspection Types (Phase 5.60)
//
// This module defines types for inventory inspection CLI commands:
//   - QueryResult: Result of an inventory query with freshness/source info
//   - EntityInfo: Information about a discovered entity
//   - FreshnessReport: Timing and source information about observations
//
// Key Distinctions:
//   - Observation vs Inference: Only native Linux data, no speculation
//   - Freshness-aware: Track observation timestamps for staleness detection
//   - Source-preserving: Provenance tracking for each observation
//

#pragma once

#include <system/core/contracts.hpp>
#include <string>
#include <vector>
#include <chrono>
#include <optional>
#include <string_view>

namespace rebuntu::cli::inventory {

// ============================================================================
// FreshnessReport — Timing and source information about an observation
//
// This carries evidence of WHEN something was observed and FROM WHERE,
// distinguishing between:
//   - Fresh: Observed recently, within acceptable staleness threshold
//   - Stale: May be outdated (beyond freshness threshold)
//   - Unknown: Could not determine when observed (acquisition failure)
//
// ============================================================================
struct FreshnessReport {
    // When the observation was made
    std::chrono::system_clock::time_point observed_at{};
    
    // Source of the observation ("dpkg", "procfs", "sysfs", etc.)
    std::string source{"unknown"};
    
    // Was this found in a derived index or queried from source?
    enum class Source {
        kIndex,              // Found in derived index (may be stale)
        kSourceVerified,     // Not in index but verified via source lookup
        kCached,             // Retrieved from cache
        kUnknown,            // Source unknown / acquisition failed
    } source_kind{Source::kUnknown};
    
    // How long ago was this observed? (computed at query time)
    std::chrono::milliseconds age_ms{0};
    
    // Was the observation beyond the freshness threshold?
    bool is_stale{false};
    
    static FreshnessReport fresh(std::string src, std::chrono::system_clock::time_point when) {
        FreshnessReport r;
        r.observed_at = when;
        r.source = std::move(src);
        r.source_kind = Source::kSourceVerified;
        r.age_ms = std::chrono::milliseconds(0);
        r.is_stale = false;
        return r;
    }
    
    static FreshnessReport stale(std::string src, std::chrono::system_clock::time_point when) {
        FreshnessReport r;
        r.observed_at = when;
        r.source = std::move(src);
        r.source_kind = Source::kSourceVerified;
        r.age_ms = std::chrono::milliseconds(0);  // Set at query time
        r.is_stale = true;
        return r;
    }
    
    static FreshnessReport from_index(std::string src, std::chrono::system_clock::time_point when) {
        FreshnessReport r;
        r.observed_at = when;
        r.source = std::move(src);
        r.source_kind = Source::kIndex;
        r.is_stale = false;  // Set at query time
        return r;
    }
    
    static FreshnessReport unknown() {
        FreshnessReport r;
        r.observed_at = std::chrono::system_clock::time_point{};
        r.source = "unknown";
        r.source_kind = Source::kUnknown;
        r.is_stale = false;
        return r;
    }
};

// ============================================================================
// EntityInfo — Information about a discovered inventory entity
//
// This is the primary output of an inventory query, containing:
//   - Identity: How to uniquely identify this entity
//   - Attributes: Key-value metadata about the entity
//   - Freshness: When it was last observed and from where
//
// ============================================================================
struct EntityInfo {
    // Entity identity (stable identifier, not transient properties)
    std::string id;
    
    // Human-readable name if available
    std::optional<std::string> name;
    
    // Category/type of this entity
    std::optional<std::string> category;
    
    // Additional attributes as key-value pairs
    std::vector<std::pair<std::string, std::string>> attributes;
    
    // Observation metadata
    FreshnessReport freshness{};
    
    // Error information if observation failed (UNKNOWN != PASS)
    std::optional<core::Error> error;
};

// ============================================================================
// QueryResult — Result of an inventory query
//
// This is the top-level result type for all inventory CLI commands:
//   - status: Overall outcome (SUCCESS/FAILURE/UNKNOWN/CANCELLED)
//   - entities: List of discovered entities (may be partial)
//   - freshness_threshold_ms: The threshold used to determine staleness
//
// ============================================================================
struct QueryResult {
    core::SemanticStatus status{core::SemanticStatus::kUnknown};
    std::string description{};
    
    // Entities found by this query
    std::vector<EntityInfo> entities;
    
    // Statistics about the query result
    size_t total_found = 0;        // Total entities found (may include partial)
    size_t fresh_count = 0;        // Entities within freshness threshold
    size_t stale_count = 0;        // Entities beyond freshness threshold
    
    // The freshness threshold that was applied
    std::chrono::milliseconds freshness_threshold_ms{std::chrono::minutes(5)};
    
    // Total query elapsed time
    std::chrono::milliseconds elapsed_ms{0};
    
    static QueryResult success(std::vector<EntityInfo> entities) {
        QueryResult r;
        r.status = core::SemanticStatus::kSuccess;
        r.entities = std::move(entities);
        
        for (const auto& e : r.entities) {
            if (e.freshness.source_kind != FreshnessReport::Source::kUnknown && !e.freshness.is_stale) {
                r.fresh_count++;
            } else if (e.freshness.source_kind != FreshnessReport::Source::kUnknown && e.freshness.is_stale) {
                r.stale_count++;
            }
        }
        r.total_found = r.entities.size();
        
        return r;
    }
    
    static QueryResult failure(std::string /*code*/, std::string message) {
        QueryResult r;
        r.status = core::SemanticStatus::kFailure;
        r.description = std::move(message);
        return r;
    }
    
    static QueryResult unknown(std::string message) {
        QueryResult r;
        r.status = core::SemanticStatus::kUnknown;
        r.description = std::move(message);
        return r;
    }
};

// ============================================================================
// InventoryKind — Types of inventory entities that can be queried
//
// Note: This is NOT a runtime bus or event system. It is a data structure
// for structuring queries.
//
// ============================================================================
enum class InventoryKind {
    kUnknown,
    
    // System components
    kPackage,      // dpkg package inventory (installed packages)
    kService,      // systemd service units
    kProcess,      // running processes
    
    // Hardware inventory
    kStorage,      // Block devices and filesystems
    kNetwork,      // Network interfaces
    kGpu,          // Graphics processing units
    
    // Configuration
    kUser,         // System users
    kGroup,        // System groups
};

inline const char* to_string(InventoryKind k) {
    switch (k) {
        case InventoryKind::kPackage:   return "package";
        case InventoryKind::kService:   return "service";
        case InventoryKind::kProcess:   return "process";
        case InventoryKind::kStorage:   return "storage";
        case InventoryKind::kNetwork:   return "network";
        case InventoryKind::kGpu:       return "gpu";
        case InventoryKind::kUser:      return "user";
        case InventoryKind::kGroup:     return "group";
        default:                        return "unknown";
    }
}

inline std::string to_lowercase(std::string s) {
    for (auto& c : s) {
        // tolower takes int but returns int, so we need proper casting
        unsigned char uc = static_cast<unsigned char>(c);
        c = static_cast<char>(std::tolower(uc));
    }
    return s;
}

}  // namespace rebuntu::cli::inventory

namespace std {

template <> struct hash<rebuntu::cli::inventory::FreshnessReport> {
    size_t operator()(const rebuntu::cli::inventory::FreshnessReport& r) const noexcept {
        size_t h = std::hash<std::string>{}(r.source);
        h ^= std::hash<uint64_t>{}(std::chrono::duration_cast<std::chrono::milliseconds>(
            r.observed_at.time_since_epoch()).count());
        return h;
    }
};

template <> struct hash<rebuntu::cli::inventory::EntityInfo> {
    size_t operator()(const rebuntu::cli::inventory::EntityInfo& e) const noexcept {
        return std::hash<std::string>{}(e.id);
    }
};

}  // namespace std