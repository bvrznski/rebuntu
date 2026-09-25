// rebuntu::runtime::catalog::integration — Registry/Catalog Runtime Integration (Phase 4.10)
//
// This header establishes how runtime catalogs/registries integrate with the execution
// system while preserving critical boundaries:
//
//   * Definitions vs Instances: Catalogs store immutable definitions; runtime stores live instances
//   * Ownership: Catalogs are read-only sources of truth for specs; runtime owns execution state
//   * Provenance: All catalog entries carry source metadata for traceability
//   * Collision handling: Explicit semantics, not silent last-wins behavior

#pragma once

#include <runtime/core/contracts.hpp>
#include <runtime/loader.hpp>
#include <runtime/resolver.hpp>
#include <interfaces/provider_registry.hpp>
#include <filesystem>
#include <memory>
#include <set>
#include <string>
#include <map>
#include <vector>
#include <chrono>

namespace rebuntu::runtime::catalog {

// ============================================================================
// CatalogId — Unique identifier for a catalog
// ============================================================================

struct CatalogId {
    std::string value;
    
    explicit CatalogId(std::string v) : value(std::move(v)) {}
    explicit operator std::string() const { return value; }
};

inline bool operator==(const CatalogId& a, const CatalogId& b) {
    return a.value == b.value;
}

inline bool operator!=(const CatalogId& a, const CatalogId& b) {
    return !(a == b);
}

inline bool operator<(const CatalogId& a, const CatalogId& b) {
    return a.value < b.value;
}

// ============================================================================
// CatalogEntry — A single entry in the catalog with provenance
// ============================================================================

struct CatalogEntry {
    std::string id;                      // Stable semantic identifier
    std::filesystem::path source_path;   // Where this definition was loaded from
    std::chrono::system_clock::time_point loaded_at;
    
    bool is_trusted = false;             // Whether source path is trusted
    
    // Reference to the actual definition (does NOT own it)
    const void* definition_ptr = nullptr;  // This would be cast to appropriate type
};

// ============================================================================
// CollisionAction — What to do when a duplicate catalog entry is found
// ============================================================================

enum class CollisionAction {
    kError,         // Fail on collision - explicit error required
    kSkip,          // Skip the duplicate silently
    kReplace,       // Replace existing with new (WARNING: can cause race conditions)
    kMerge,         // Merge metadata from both entries
};

inline std::string to_string(CollisionAction a) {
    switch (a) {
        case CollisionAction::kError:   return "error";
        case CollisionAction::kSkip:    return "skip";
        case CollisionAction::kReplace: return "replace";
        case CollisionAction::kMerge:   return "merge";
    }
    return "unknown";
}

// ============================================================================
// CatalogConfig — Configuration for catalog loading
// ============================================================================

struct CatalogConfig {
    std::vector<std::filesystem::path> search_paths;  // Directories to scan
    bool recursive = false;                            // Scan subdirectories?
    std::set<std::string> allowed_extensions = {".yaml", ".json", ".conf"};
    
    CollisionAction collision_action = CollisionAction::kError;
    size_t max_entries = 1000;                         // Safety limit
    
    bool strict_mode = true;                           // Fail on any issue?
};

// ============================================================================
// CatalogLoadResult — Result of loading catalog entries
// ============================================================================

struct CatalogLoadResult {
    core::SemanticStatus status;
    
    std::vector<CatalogEntry> loaded;
    std::vector<std::string> skipped;
    std::vector<core::Error> errors;
    
    bool is_success() const { return status == core::SemanticStatus::kSuccess; }
};

// ============================================================================
// Catalog — A read-only registry of definitions from trusted sources
//
// Key principles:
//   * Immutable once loaded (no runtime state modifications)
//   * Source-tracked for provenance
//   * Handles duplicates explicitly per collision_action config
// ============================================================================

class Catalog {
public:
    explicit Catalog(CatalogConfig config);
    ~Catalog() = default;
    
    // Load all entries from configured paths
    CatalogLoadResult load_all();
    
    // Find a specific entry by ID
    std::optional<CatalogEntry> find(const std::string& id) const;
    
    // List all loaded entries
    std::vector<CatalogEntry> list_all() const;
    
    // Get catalog metadata
    CatalogId id() const { return catalog_id_; }
    size_t entry_count() const { return entries_.size(); }
    
    // Validation - check for structural issues
    std::vector<std::string> validate() const;

private:
    CatalogConfig config_;
    CatalogId catalog_id_;
    
    // Map of ID -> CatalogEntry (does not own the definition)
    std::map<std::string, CatalogEntry> entries_;
    
    // Source tracking - map source path to IDs loaded from it
    std::map<std::filesystem::path, std::vector<std::string>> source_map_;
    
    // Track loaded entries for collision detection
    std::set<std::string> loaded_ids_;
};

// ============================================================================
// CatalogFactory — Factory for creating catalogs
// ============================================================================

class CatalogFactory {
public:
    static std::unique_ptr<Catalog> make_operations_catalog();
    static std::unique_ptr<Catalog> make_services_catalog();
    static std::unique_ptr<Catalog> make_units_catalog();
    
private:
    static CatalogConfig default_config();
};

// ============================================================================
// CatalogRegistry — Central catalog management
//
// This is the integration point between runtime execution and definition catalogs.
// It does NOT own definition data, only maintains references to loaded catalogs.
// ============================================================================

class CatalogRegistry {
public:
    CatalogRegistry() = default;
    ~CatalogRegistry() = default;
    
    // Register a catalog (takes ownership of Catalog)
    void register_catalog(std::unique_ptr<Catalog> catalog);
    
    // Get a catalog by ID
    std::optional<std::reference_wrapper<Catalog>> get_catalog(const CatalogId& id) const;
    
    // List all registered catalogs
    std::vector<CatalogId> list_catalogs() const;
    
    // Find an entry across all catalogs
    std::optional<CatalogEntry> find_entry(const std::string& id) const;

private:
    std::map<CatalogId, std::unique_ptr<Catalog>> catalogs_;
};

// ============================================================================
// Factory functions
// ============================================================================

std::unique_ptr<CatalogRegistry> make_catalog_registry();

}  // namespace rebuntu::runtime::catalog