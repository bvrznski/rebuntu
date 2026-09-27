// rebuntu::observation::system_observation_inventory_discovery::relationships —
// Relationship Evidence Types (Phase 5.47)
//
// This module defines typed relationships with evidence tracking:
//   - Typed relationships with explicit source and target entities
//   - Provenance tracking for each relationship observation
//   - Freshness information for validation
//   - Uncertainty indicators where applicable
//
// Key Invariants (Phase 5.47):
//   - RELATIONSHIP EVIDENCE IS TYPED: Each relationship carries explicit type info
//   - PROVENANCE PRESERVATION: Every observation retains its evidence source
//   - NO Causal INFERENCE: Relationships are observed, not computed from topology/timing
//   - UNCERTAINTY TRACKING: Unknown/missing data is tracked separately from absence

#pragma once

#include <system/core/contracts.hpp>
#include <string>
#include <chrono>
#include <vector>
#include <optional>
#include <memory>

namespace rebuntu::observation::system_observation_inventory_discovery::relationships {

// ============================================================================
// RelationshipType — Types of relationships between entities
//
// These represent observed relationships, NOT inferred ones.
// Each type has a specific semantic meaning in the system:
//   - belongs_to: Entity is contained/managed by another (e.g., process in cgroup)
//   - manages: Entity has ownership/control over another (e.g., driver manages device)
//   - depends_on: Entity requires another for functionality
//   - runs_on: Service/process executes on a host/system
//   - resides_on: Filesystem exists on a block device
//   - assigned_to: IP address configured on network interface
//   - parent_of: Parent-child relationship (e.g., process hierarchy)
// ============================================================================
enum class RelationshipType {
    kBelongsTo,        // Entity belongs to container/owner
    kManages,          // Entity manages/controls another
    kDependsOn,        // Entity depends on another for functionality
    kRunsOn,           // Process/service runs on host/system
    kResidesOn,        // Filesystem resides on block device
    kAssignedTo,       // IP address assigned to network interface
    kParentOf,         // Parent-child relationship (e.g., process hierarchy)
};

inline std::string to_string(RelationshipType t) {
    switch (t) {
        case RelationshipType::kBelongsTo:   return "belongs-to";
        case RelationshipType::kManages:     return "manages";
        case RelationshipType::kDependsOn:   return "depends-on";
        case RelationshipType::kRunsOn:      return "runs-on";
        case RelationshipType::kResidesOn:   return "resides-on";
        case RelationshipType::kAssignedTo:  return "assigned-to";
        case RelationshipType::kParentOf:    return "parent-of";
    }
    return "unknown";
}

// ============================================================================
// EntityIdentity — Identity of an entity in a domain
//
// Unlike CrossDomainEntityId, this is local to the observation context.
// ============================================================================
struct EntityIdentity {
    std::string domain;        // e.g., "process", "cgroup", "device"
    std::string identifier;    // Domain-specific identifier
    
    bool is_valid() const {
        return !domain.empty() && !identifier.empty();
    }
};

inline bool operator==(const EntityIdentity& a, const EntityIdentity& b) {
    return a.domain == b.domain && a.identifier == b.identifier;
}

// ============================================================================
// EvidenceSource — Where relationship evidence came from
//
// Tracks the native Linux source that provided this observation:
//   - procfs:/proc/[pid]/stat — Process info from procfs
//   - sysfs:/sys/class/... — Device info from sysfs
//   - udev:... — Udev database entry
//   - systemd:... — Systemd D-Bus state
// ============================================================================
struct EvidenceSource {
    std::string source_type;     // e.g., "procfs", "sysfs", "udev", "systemd"
    std::string path;            // Specific file/path where observed
    
    bool is_native() const {
        return source_type == "procfs" || source_type == "sysfs" || 
               source_type == "udev" || source_type == "systemd";
    }
};

inline std::string to_string(const EvidenceSource& src) {
    return src.source_type + ":" + src.path;
}

// ============================================================================
// RelationshipEvidence — Complete evidence for a relationship
//
// This is the core type for Task 5.47:
//   - source: The entity that has the relationship
//   - target: The entity being related to
//   - relationship_type: How they are related
//   - evidence_source: Where this was observed (native Linux source)
//   - observed_at: When the observation was made
//   - uncertainty: Whether there's any doubt about this relationship
//
// Example: Process 1234 belongs to cgroup /system.slice/foo.service
//   RelationshipEvidence{
//       source = EntityIdentity{"process", "1234@boot-789"},
//       target = EntityIdentity{"cgroup", "/system.slice/foo.service"},
//       relationship_type = RelationshipType::kBelongsTo,
//       evidence_source = EvidenceSource{"procfs", "/proc/1234/cgroup"},
//       observed_at = observation_timestamp,
//       uncertainty = kNone
//   }
// ============================================================================
struct RelationshipEvidence {
    EntityIdentity source;          // The entity with the relationship
    EntityIdentity target;          // What the source relates to
    
    RelationshipType relationship_type{};  // How they are related
    
    EvidenceSource evidence_source;  // Where this was observed (native Linux)
    
    std::chrono::system_clock::time_point observed_at{};
    std::optional<std::string> boot_context;  // Boot context for stability
    
    // Uncertainty tracking
    enum class UncertaintyLevel {
        kNone,          // Confirmed observation
        kBounded,       // Observation with known bounds on accuracy
        kPartial,       // Partial information (some fields unavailable)
        kUnknown,       // Cannot determine validity
    } uncertainty = UncertaintyLevel::kNone;
    
    std::optional<std::string> uncertainty_reason;  // Why uncertainty exists
    
    bool is_valid() const {
        return source.is_valid() && target.is_valid() &&
               !evidence_source.source_type.empty();
    }
};

// ============================================================================
// RelationshipDiscoveryResult — Result of relationship discovery
//
// Contains all discovered relationships with proper provenance.
// ============================================================================
struct RelationshipDiscoveryResult {
    core::SemanticStatus status{core::SemanticStatus::kUnknown};
    std::string description{};
    
    // All discovered relationships
    std::vector<RelationshipEvidence> relationships;
    
    // Statistics
    size_t total_relationships = 0;
    size_t by_type[7]{};  // One slot per RelationshipType enum value
    
    // Timing
    std::chrono::system_clock::time_point observed_at{};
    std::chrono::milliseconds elapsed_ms{0};
    
    // Errors encountered (non-fatal)
    std::vector<std::pair<EntityIdentity, core::Error>> errors;
    
    std::optional<core::Error> fatal_error;
};

// ============================================================================
// RelationshipEvidence helper functions
// ============================================================================
inline bool has_uncertainty(const RelationshipEvidence& evidence) {
    return evidence.uncertainty != RelationshipEvidence::UncertaintyLevel::kNone;
}

// ============================================================================
// RelationshipEvidenceProvider — Interface for relationship discovery
//
// Provides bounded, freshness-aware relationship observation.
// Key principle: Only report what is DIRECTLY OBSERVED.
// No inference from topology or timing.
// ============================================================================
class RelationshipEvidenceProvider {
public:
    virtual ~RelationshipEvidenceProvider() = default;
    
    // Query relationships for a specific entity
    virtual RelationshipDiscoveryResult query(const EntityIdentity& entity) = 0;
    
    // Get all relationships (across all entities)
    virtual RelationshipDiscoveryResult get_all_relationships() = 0;
    
    // Get relationships by type
    virtual std::vector<RelationshipEvidence> get_by_type(RelationshipType type) = 0;
    
    // Get freshness of relationship data
    virtual std::chrono::system_clock::time_point get_last_observation_time() const = 0;
};

// ============================================================================
// Factory function
// ============================================================================
std::unique_ptr<RelationshipEvidenceProvider> make_relationship_evidence_provider();

}  // namespace rebuntu::observation::system_observation_inventory_discovery::relationships

namespace std {

template <> struct hash<rebuntu::observation::system_observation_inventory_discovery::relationships::EntityIdentity> {
    size_t operator()(
        const rebuntu::observation::system_observation_inventory_discovery::relationships::EntityIdentity& id) const noexcept {
        size_t h1 = std::hash<std::string>{}(id.domain);
        size_t h2 = std::hash<std::string>{}(id.identifier);
        return h1 ^ (h2 << 1);
    }
};

}  // namespace std