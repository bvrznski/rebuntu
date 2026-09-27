// rebuntu::interfaces::cross_domain_references — Cross-Domain Entity References (Phase 5.46)
//
// This module defines minimal typed references allowing observations to relate
// entities across different domains:
//   - process↔cgroup: Process can belong to a cgroup, cgroup contains processes
//   - device↔driver: Device is managed by a driver, driver manages devices
//   - filesystem↔block device: Filesystem resides on a block device
//   - service↔process: Service runs as one or more processes
//   - interface↔address: Network interface has zero or more IP addresses
//
// Key Invariants:
//   - REFERENCES ARE TYPED: Each reference carries explicit domain information
//   - REFERENCE VALIDITY IS BOUNDED: References may become invalid between use
//   - ABSENCE IS UNKNOWN: Missing reference data is not proof of absence
//   - NO INFERENCES: References represent observed relationships, not computed ones
//
// Design Principles:
//   1. Typed references with domain qualifiers to prevent ambiguous cross-domain links
//   2. Observational provenance tracking for reference validity
//   3. Cancellation and freshness awareness in reference acquisition
//   4. No knowledge graph - only direct relationship types defined

#pragma once

#include <system/core/contracts.hpp>
#include <string>
#include <string_view>
#include <chrono>
#include <vector>
#include <memory>
#include <optional>
#include <functional>

namespace rebuntu::interfaces {

// ============================================================================
// CrossDomainEntityId — Entity identity that spans domains
//
// Unlike local identities (e.g., ProcessIdentity which is boot+pid),
// this carries domain context to enable cross-domain referencing.
//
// Example: A process in a cgroup:
//   - Local: ProcessIdentity(boot_timestamp, pid)
//   - Cross-domain: CrossDomainEntityId("process", "1234@boot-789")
//   - Cross-domain: CrossDomainEntityId("cgroup", "/system.slice/foo")
//
// Domain naming conventions:
//   - process: Linux process (PID + boot context)
//   - cgroup: Control group hierarchy path
//   - device: sysfs device path or udev ID
//   - driver: kernel driver name
//   - filesystem: mount point or fs UUID/label
//   - block_device: sysfs path or /dev node
//   - service: systemd unit name + type
//   - interface: WARNING: Interface names like "eth0" are NOT durable identities!
//
//     Interface names can change due to:
//       - Reboot (kernel re-enumeration order changes)
//       - Hotplug events (USB NICs, PCI devices)  
//       - udev rules changes
//       - Interface rename operations
//
//     For stable identity across reboots/hotplug, use ifindex@mac_address format.
//   - address: IP address with family qualifier
// ============================================================================
struct CrossDomainEntityId {
    std::string domain;        // e.g., "process", "cgroup", "device"
    std::string identifier;    // Domain-specific ID (must be unique within domain)
    
    // Default constructor (empty ID)
    CrossDomainEntityId() = default;
    
    // Constructors for common cases
    explicit CrossDomainEntityId(std::string d, std::string id)
        : domain(std::move(d)), identifier(std::move(id)) {}
    
    // Convenience constructors for known domains
    static CrossDomainEntityId process(std::string pid_with_boot);
    static CrossDomainEntityId cgroup(std::string path);
    static CrossDomainEntityId device(std::string sysfs_path);
    static CrossDomainEntityId driver(std::string name);
    static CrossDomainEntityId filesystem(std::string mount_point_or_uuid);
    static CrossDomainEntityId block_device(std::string dev_node_or_sysfs);
    static CrossDomainEntityId service(std::string unit_name, std::string type = "service");
    // network_interface: uses interface name (e.g., "eth0") - NOT durable across reboots/hotplug
    static CrossDomainEntityId network_interface(std::string name);
    // network_interface_stable: uses ifindex@mac_address format for stable identity
    static CrossDomainEntityId network_interface_stable(int32_t ifindex, std::string mac_address);
    static CrossDomainEntityId ip_address(std::string addr, std::string family = "ipv4");
    
    bool is_valid() const {
        return !domain.empty() && !identifier.empty();
    }
};

inline bool operator==(const CrossDomainEntityId& a, const CrossDomainEntityId& b) {
    return a.domain == b.domain && a.identifier == b.identifier;
}

inline bool operator!=(const CrossDomainEntityId& a, const CrossDomainEntityId& b) {
    return !(a == b);
}

// Hash support for use in unordered containers
struct CrossDomainEntityIdHash {
    size_t operator()(const CrossDomainEntityId& id) const noexcept {
        size_t h1 = std::hash<std::string>{}(id.domain);
        size_t h2 = std::hash<std::string>{}(id.identifier);
        return h1 ^ (h2 << 1);
    }
};

// ============================================================================
// RelationshipType — Types of cross-domain relationships
//
// These are the relationship types that can exist between entities:
//   - belongs_to: Entity is contained by/managed by another entity
//   - manages: Entity has ownership/control over another entity  
//   - depends_on: Entity requires another entity to function
//   - runs_on: Service/process executes on a host/system
//   - resides_on: Filesystem exists on a block device
//   - assigned_to: Address is configured on an interface
// ============================================================================
enum class RelationshipType {
    kBelongsTo,          // Entity belongs to container/owner (e.g., process in cgroup)
    kManages,            // Entity manages/controls another (e.g., driver manages device)
    kDependsOn,          // Entity depends on another for functionality
    kRunsOn,             // Process/service runs on host/system
    kResidesOn,          // Filesystem resides on block device
    kAssignedTo,         // IP address assigned to network interface
    kMemberOf,           // Entity is member of collection (e.g., process in cgroup)
};

inline std::string_view to_string(RelationshipType t) {
    switch (t) {
        case RelationshipType::kBelongsTo:   return "belongs-to";
        case RelationshipType::kManages:     return "manages";
        case RelationshipType::kDependsOn:   return "depends-on";
        case RelationshipType::kRunsOn:      return "runs-on";
        case RelationshipType::kResidesOn:   return "resides-on";
        case RelationshipType::kAssignedTo:  return "assigned-to";
        case RelationshipType::kMemberOf:    return "member-of";
    }
    return "unknown";
}

// ============================================================================
// EntityReference — A typed reference to another entity
//
// This is the core type for cross-domain referencing:
//   - target: The CrossDomainEntityId being referenced
//   - relationship: How this entity relates to the target
//   - provenance: Where this relationship was observed
//   - freshness: When the relationship was last verified
//
// Example: A process belonging to a cgroup:
//   EntityReference{
//       target = CrossDomainEntityId("cgroup", "/system.slice/foo"),
//       relationship = RelationshipType::kBelongsTo,
//       provenance = "procfs:/proc/1234/cgroup",
//       freshness = observed_timestamp
//   }
//
// Example: A service running as a process:
//   EntityReference{
//       target = CrossDomainEntityId("process", "1234@boot-789"),
//       relationship = RelationshipType::kRunsOn,
//       provenance = "systemd:MainPID",
//       freshness = observed_timestamp
//   }
// ============================================================================
struct EntityReference {
    CrossDomainEntityId target;           // The entity being referenced
    
    RelationshipType relationship{};      // How this entity relates to the target
    
    // Provenance tracking for verification
    std::string provenance_source;        // Where this reference was observed
    std::chrono::system_clock::time_point observed_at{};
    
    // Validity information (bounded acquisition, may be unknown)
    bool is_valid() const {
        return target.is_valid() && !provenance_source.empty();
    }
};

// ============================================================================
// CrossDomainReference — A complete cross-domain reference with source context
//
// This extends EntityReference with:
//   - source: The entity that holds the reference (the "from" side)
//   - references: List of related entities and their relationships
//
// Example: Process observation with cgroup references:
//   CrossDomainReference{
//       source = CrossDomainEntityId("process", "1234@boot-789"),
//       references = {
//           EntityReference{CrossDomainEntityId("cgroup", "/system.slice/foo"), kBelongsTo, ...},
//           EntityReference{CrossDomainEntityId("process", "1@boot-0"), kRunsOn, ...}  // parent
//       }
//   }
// ============================================================================
struct CrossDomainReference {
    CrossDomainEntityId source;           // The entity that owns these references
    
    // All cross-domain relationships for this entity
    std::vector<EntityReference> references;
    
    // Provenance of the entire reference set
    std::string observation_source{};
    std::chrono::system_clock::time_point observed_at{};
    
    bool is_valid() const {
        return source.is_valid() && !observation_source.empty();
    }
};

// ============================================================================
// CrossDomainQuery — Request to discover cross-domain relationships
//
// Parameters for querying cross-domain references:
//   - source_entity: Which entity to query (if known)
//   - target_domain: Filter by relationship domain (optional)
//   - relationship_type: Filter by relationship type (optional)
//   - freshness_threshold: How stale is acceptable?
// ============================================================================
struct CrossDomainQuery {
    std::string id;                       // Query ID for tracking
    
    std::chrono::system_clock::time_point created_at{};
    
    // Which entity to query (optional if target_domain + identifier provided)
    std::optional<CrossDomainEntityId> source_entity;
    
    // Filter options
    std::optional<std::string> target_domain;      // e.g., "cgroup", "device"
    std::optional<RelationshipType> relationship_type;
    
    // Freshness and budget constraints
    std::chrono::milliseconds freshness_threshold_ms{60000};  // Max age of reference
    size_t max_references = 1000;                  // Max results to return
    
    static CrossDomainQuery make(std::string id) {
        CrossDomainQuery q;
        q.id = std::move(id);
        q.created_at = std::chrono::system_clock::now();
        return q;
    }
};

// ============================================================================
// CrossDomainReferenceResult — Result of cross-domain reference query
//
// Contains all discovered relationships for an entity with proper provenance.
// ============================================================================
struct CrossDomainReferenceResult {
    core::SemanticStatus status{core::SemanticStatus::kUnknown};
    std::string description{};
    
    // Query that produced this result
    std::string query_id;
    
    // Source entity (if found)
    std::optional<CrossDomainEntityId> source_entity;
    
    // Discovered references
    std::vector<EntityReference> references;
    
    // Reference statistics
    size_t total_references = 0;
    size_t by_relationship_type[7]{};  // One slot per RelationshipType enum value
    
    // Timing
    std::chrono::system_clock::time_point observed_at{};
    std::chrono::milliseconds elapsed_ms{0};
    
    // Errors encountered during discovery (non-fatal)
    std::vector<std::pair<CrossDomainEntityId, core::Error>> errors;
    
    std::optional<core::Error> fatal_error;
};

// ============================================================================
// CrossDomainReferenceProvider — Interface for cross-domain reference discovery
//
// Provides bounded, cancellable, freshness-aware cross-domain relationship
// observation without inference or knowledge graph construction.
// ============================================================================
class CrossDomainReferenceProvider {
public:
    virtual ~CrossDomainReferenceProvider() = default;
    
    // Query references for a specific entity
    virtual CrossDomainReferenceResult query(const CrossDomainQuery& query) = 0;
    
    // Get all references for an entity (convenience wrapper)
    virtual CrossDomainReferenceResult get_all_references(
        const CrossDomainEntityId& entity_id) = 0;
    
    // Check if a reference exists between two entities
    virtual bool has_reference(
        const CrossDomainEntityId& from,
        const CrossDomainEntityId& to,
        RelationshipType type) = 0;
    
    // Get references by relationship type
    virtual std::vector<EntityReference> get_references_by_type(
        const CrossDomainEntityId& entity_id,
        RelationshipType type) = 0;
    
    // Get freshness of reference data
    virtual std::chrono::system_clock::time_point get_last_observation_time() const = 0;
};

// ============================================================================
// Factory function
// ============================================================================
std::unique_ptr<CrossDomainReferenceProvider> make_cross_domain_reference_provider();

}  // namespace rebuntu::interfaces

namespace std {

template <> struct hash<rebuntu::interfaces::CrossDomainEntityId> {
    size_t operator()(const rebuntu::interfaces::CrossDomainEntityId& id) const noexcept {
        return rebuntu::interfaces::CrossDomainEntityIdHash{}(id);
    }
};

}  // namespace std