// rebuntu::system::observation::model — Facts & Observations Model (Phase 7.1)
//
// This module formalizes Observation and Fact semantics:
//   - Observation: Source-bound evidence obtained at a time
//   - Fact: Typed claim derived from one or more observations under explicit rules
//
// Architecture:
//   Observation -> raw acquisition from native Linux sources
//       -> source-specific parsing
//       -> typed normalization
//       -> Observation record (with provenance, timestamps)
//   Fact: Derived from Observations via deterministic rules
//       -> typed claim with evidence references
//       -> current-state projection
//
// Key Distinctions:
//   - Observation is temporal (acquired_at, may become stale)
//   - Fact is typed and semantically meaningful ("process sleeping", not "R")
//   - Evidence chain: observation -> fact -> verification
//   - Direct facts come from single observations
//   - Derived facts come from computation over multiple observations

#pragma once

#include <chrono>
#include <cstdint>
#include <map>
#include <optional>
#include <string>
#include <vector>

namespace rebuntu::system::observation {

// ============================================================================
// Quality — Confidence in the observation source and value
// ============================================================================
//
// This is NOT a numeric confidence percentage. It indicates the reliability
// of the source and whether the value was directly observed or derived.

enum class Quality {
    unknown,      // No valid evidence, UNKNOWN state
    partial,      // Partial observation, some data missing
    observed,     // Directly observed from native source
    authoritative,// Canonical source, no reasonable doubt
};

inline std::string to_string(Quality q) {
    switch (q) {
        case Quality::unknown:     return "unknown";
        case Quality::partial:     return "partial";
        case Quality::observed:    return "observed";
        case Quality::authoritative: return "authoritative";
    }
    return "unknown";
}

// ============================================================================
// Provenance — Evidence trail for an observation/fact
// ============================================================================
//
// Records WHO provided the data, WHAT quality we consider it, and WHEN
// it was acquired. This enables traceability back to source.

struct Provenance {
    std::string provider;                      // Source: "procfs", "sysfs", "systemd-dbus"
    Quality quality{Quality::unknown};         // Reliability of this source
    
    // Timestamps - distinguish event time from acquisition time
    std::chrono::system_clock::time_point acquired_at{};  // When we read it
    std::optional<std::chrono::system_clock::time_point> event_time{}; // When event occurred (if source provides)
    
    // Sampling metadata for rate-derived metrics
    std::optional<std::chrono::milliseconds> sample_window_ms{}; // For rates/deltas
    
    // Source locator - where exactly in the native interface
    std::string source_locator{};  // e.g., "/proc/123/stat", "netlink RTM_GETLINK"
    
    // Derivation metadata (for Facts)
    bool is_derived{false};        // Was this computed from multiple observations?
    std::optional<std::vector<std::string>> source_observation_ids{};  // If derived, which obs IDs?
};

// ============================================================================
// LifecycleState — Subject lifecycle dimension
// ============================================================================

enum class LifecycleState {
    unknown,
    uninitialized,  // Not yet initialized
    initializing,   // In the process of initializing
    initialized,    // Initialized but not yet active
    running,        // Actively executing or available
    stopping,       // Stopping (graceful)
    stopped,        // Stopped
    failed,         // Failed to start or crashed
    completed,      // Completed its task successfully
    cancelled,      // Cancelled before completion
    timed_out,      // Timed out during execution
};

inline std::string to_string(LifecycleState s) {
    switch (s) {
        case LifecycleState::unknown:       return "unknown";
        case LifecycleState::uninitialized: return "uninitialized";
        case LifecycleState::initializing:  return "initializing";
        case LifecycleState::initialized:   return "initialized";
        case LifecycleState::running:       return "running";
        case LifecycleState::stopping:      return "stopping";
        case LifecycleState::stopped:       return "stopped";
        case LifecycleState::failed:        return "failed";
        case LifecycleState::completed:     return "completed";
        case LifecycleState::cancelled:     return "cancelled";
        case LifecycleState::timed_out:     return "timed-out";
    }
    return "unknown";
}

// ============================================================================
// WorkState — Subject work/activity dimension
// ============================================================================

enum class WorkState {
    unknown,
    busy,           // Actively processing
    waiting,        // Waiting for I/O or lock
    idling,         // Available but no work
    sleeping,       // Suspended (process state)
    resting,        // Low-power mode (device)
    paused,         // Temporarily suspended
};

inline std::string to_string(WorkState s) {
    switch (s) {
        case WorkState::unknown: return "unknown";
        case WorkState::busy:    return "busy";
        case WorkState::waiting: return "waiting";
        case WorkState::idling:  return "idling";
        case WorkState::sleeping:return "sleeping";
        case WorkState::resting: return "resting";
        case WorkState::paused:  return "paused";
    }
    return "unknown";
}

// ============================================================================
// ControlState — Subject control/permission dimension
// ============================================================================

enum class ControlState {
    unknown,
    enabled,        // Can accept commands/activation
    disabled,       // Cannot accept commands
    paused,         // Running but paused
    locked,         // Cannot be modified
    frozen,         // State frozen (e.g., for checkpoint)
};

inline std::string to_string(ControlState s) {
    switch (s) {
        case ControlState::unknown: return "unknown";
        case ControlState::enabled: return "enabled";
        case ControlState::disabled:return "disabled";
        case ControlState::paused:  return "paused";
        case ControlState::locked:  return "locked";
        case ControlState::frozen:  return "frozen";
    }
    return "unknown";
}

// ============================================================================
// ReadinessState — Subject readiness to accept work
// ============================================================================

enum class ReadinessState {
    unknown,
    ready,          // Ready to accept work
    not_ready,      // Not ready yet (initializing, degraded, etc.)
    unavailable,    // Temporarily unavailable (maintenance, upgrade)
};

inline std::string to_string(ReadinessState s) {
    switch (s) {
        case ReadinessState::unknown:   return "unknown";
        case ReadinessState::ready:     return "ready";
        case ReadinessState::not_ready: return "not-ready";
        case ReadinessState::unavailable:return "unavailable";
    }
    return "unknown";
}

// ============================================================================
// HealthState — Subject health/status dimension
// ============================================================================

enum class HealthState {
    unknown,
    healthy,        // Normal operation
    degraded,       // Some functionality impaired but operational
    unhealthy,      // Not functioning properly
    offline,        // No health data available (device absent, etc.)
};

inline std::string to_string(HealthState s) {
    switch (s) {
        case HealthState::unknown:  return "unknown";
        case HealthState::healthy:  return "healthy";
        case HealthState::degraded: return "degraded";
        case HealthState::unhealthy:return "unhealthy";
        case HealthState::offline:  return "offline";
    }
    return "unknown";
}

// ============================================================================
// RecoveryState — Subject recovery action dimension
// ============================================================================

enum class RecoveryState {
    unknown,
    normal,         // Normal recovery behavior
    recovering,     // Currently recovering from failure
    repairing,      // Attempting to repair
    failover,       // In failover mode
    rollback,       // Rolling back changes
};

inline std::string to_string(RecoveryState s) {
    switch (s) {
        case RecoveryState::unknown:   return "unknown";
        case RecoveryState::normal:    return "normal";
        case RecoveryState::recovering:return "recovering";
        case RecoveryState::repairing: return "repairing";
        case RecoveryState::failover:  return "failover";
        case RecoveryState::rollback:  return "rollback";
    }
    return "unknown";
}

// ============================================================================
// SubjectIdentity — Stable identity for an observation subject
// ============================================================================
//
// A subject is the entity being observed (process, service, device, etc.).
// Its identity must be stable-enough across observations to enable tracking.

struct SubjectIdentity {
    std::string domain;          // "process", "service", "device", "filesystem", etc.
    std::string subject_kind;    // More specific: "linux-process", "systemd-service", "pci-device"
    
    // Primary identifier (domain-specific)
    std::string primary_id;
    
    // Alternative identities (aliases)
    std::vector<std::string> aliases{};
    
    // Stable metadata for identity resolution
    std::optional<std::string> serial_number{};
    std::optional<std::string> uuid{};
    std::optional<std::string> hardware_address{};  // MAC, etc.
    
    bool is_valid() const {
        return !domain.empty() && !primary_id.empty();
    }
};

inline bool operator==(const SubjectIdentity& a, const SubjectIdentity& b) {
    return a.domain == b.domain && a.primary_id == b.primary_id;
}

inline bool operator!=(const SubjectIdentity& a, const SubjectIdentity& b) {
    return !(a == b);
}

// ============================================================================
// UnknownReason — Why a value is UNKNOWN
// ============================================================================

enum class UnknownReason {
    not_applicable,      // Metric doesn't apply to this subject type
    unavailable,         // Source available but data not accessible now
    permission_denied,   // Lack of privilege
    acquisition_failed,  // I/O error or other acquisition failure
    malformed_data,      // Parsed data was invalid/corrupt
    unsupported,         // Provider doesn't support this metric
    timeout,             // Acquisition exceeded time limit
    cancelled,           // Operation was cancelled
};

inline std::string to_string(UnknownReason r) {
    switch (r) {
        case UnknownReason::not_applicable:    return "not-applicable";
        case UnknownReason::unavailable:       return "unavailable";
        case UnknownReason::permission_denied: return "permission-denied";
        case UnknownReason::acquisition_failed:return "acquisition-failed";
        case UnknownReason::malformed_data:    return "malformed-data";
        case UnknownReason::unsupported:       return "unsupported";
        case UnknownReason::timeout:           return "timeout";
        case UnknownReason::cancelled:         return "cancelled";
    }
    return "unknown";
}

// ============================================================================
// Observation — Raw observation from a native Linux source
// ============================================================================

struct Observation {
    // Identity
    std::string id{};  // Unique observation ID (for tracing)
    
    SubjectIdentity subject;
    
    // Field identification
    std::string domain;       // e.g., "process", "service", "cpu"
    std::string field_name;   // e.g., "state", "memory.rss_kb", "temperature_celsius"
    
    // Value - the actual observation result
    enum class ValueType {
        string,
        integer,
        boolean,
        timestamp,
        enumeration,  // One of a known set of values
        metric,       // Numeric with unit
        compound,     // Structured value (multiple fields)
        unknown_value,// Observation failed, use error_reason instead
    };
    
    ValueType value_type{ValueType::unknown_value};
    
    std::optional<std::string> string_value{};
    std::optional<int64_t> integer_value{};
    std::optional<bool> boolean_value{};
    std::optional<std::chrono::system_clock::time_point> timestamp_value{};
    std::optional<std::string> enumeration_value{};  // One of known enum values
    std::optional<double> metric_value{};            // Numeric value with unit
    std::map<std::string, std::string> compound_values{};  // Key-value pairs
    
    std::optional<std::string> unit{};  // For metrics: "bytes", "seconds", "celsius", etc.
    
    // Provenance
    Provenance provenance{};
    
    // Error state - when observation failed
    std::optional<UnknownReason> error_reason{};
    std::optional<std::string> error_message{};
    
    // Fallback information (when multiple sources were tried)
    bool primary_source{true};  // Was this from the preferred source?
};

// ============================================================================
// FactType — Categories of facts
// ============================================================================

enum class FactType {
    lifecycle_state,
    work_state,
    control_state,
    readiness_state,
    health_state,
    recovery_state,
    
    boolean_property,     // Has some property (exists, mounted, enabled)
    numeric_metric,       // Numeric measurement (temperature, memory usage)
    text_property,        // String-valued property (name, version)
    enumeration_property, // One of known values
};

inline std::string to_string(FactType t) {
    switch (t) {
        case FactType::lifecycle_state:  return "lifecycle-state";
        case FactType::work_state:       return "work-state";
        case FactType::control_state:    return "control-state";
        case FactType::readiness_state:  return "readiness-state";
        case FactType::health_state:     return "health-state";
        case FactType::recovery_state:   return "recovery-state";
        case FactType::boolean_property: return "boolean-property";
        case FactType::numeric_metric:   return "numeric-metric";
        case FactType::text_property:    return "text-property";
        case FactType::enumeration_property: return "enumeration-property";
    }
    return "unknown";
}

// ============================================================================
// ValuePresence — Whether a fact's value exists
// ============================================================================

enum class ValuePresence {
    present,     // Value exists and is known
    absent,      // Subject doesn't have this property (e.g., process exited)
    unknown,     // Cannot determine (acquisition failed)
};

inline std::string to_string(ValuePresence p) {
    switch (p) {
        case ValuePresence::present: return "present";
        case ValuePresence::absent:  return "absent";
        case ValuePresence::unknown: return "unknown";
    }
    return "unknown";
}

// ============================================================================
// Fact — Typed claim derived from observations
// ============================================================================

struct Fact {
    std::string id{};  // Unique fact ID
    
    SubjectIdentity subject;
    
    FactType type{FactType::boolean_property};
    std::string field_name{};
    
    ValuePresence presence{ValuePresence::unknown};
    
    std::optional<bool> boolean_value{};
    std::optional<int64_t> integer_value{};
    std::optional<double> numeric_value{};
    std::optional<std::string> string_value{};
    std::optional<std::string> enumeration_value{};  // One of known values
    
    // Evidence references
    std::vector<std::string> supporting_observation_ids{};  // Which observations support this fact?
    
    bool is_derived{false};      // Was this computed from multiple observations?
    std::optional<std::string> derivation_rule{};  // Description of the rule (for debugging)
    
    // Validity period - when this fact can be considered current
    std::chrono::system_clock::time_point established_at{};
    std::optional<std::chrono::system_clock::time_point> expires_at{};  // When it may become stale
    
    Quality quality{Quality::unknown};
    
    // Freshness - how current this fact is considered
    enum class Freshness {
        fresh,       // Within acceptable TTL
        stale,       // Exceeded TTL but still accepted (with caution)
        expired,     // Significantly beyond TTL
    };
    
    Freshness freshness{Freshness::fresh};
};

inline std::string to_string(Fact::Freshness f) {
    switch (f) {
        case Fact::Freshness::fresh:   return "fresh";
        case Fact::Freshness::stale:   return "stale";
        case Fact::Freshness::expired: return "expired";
    }
    return "unknown";
}

// ============================================================================
// Contradiction — When multiple sources disagree
// ============================================================================

struct Contradiction {
    std::string field_name{};  // Which field has conflicting values?
    
    struct Conflict {
        std::string source_provider{};
        std::string source_locator{};
        std::optional<std::string> value{};
        Quality quality{Quality::unknown};
    };
    
    std::vector<Conflict> conflicts{};
    std::optional<int> authoritative_source_index{};  // If resolved, which source was chosen?
    std::optional<std::string> resolution_reason{};   // Why this one was chosen
};

// ============================================================================
// Snapshot — Coherent projection of observations/facts for a subject
// ============================================================================

struct Snapshot {
    std::string id{};  // Unique snapshot ID
    
    SubjectIdentity subject;
    
    std::chrono::system_clock::time_point captured_at{};
    
    // All observations that contributed to this view
    std::vector<Observation> observations{};
    
    // Derived facts
    std::vector<Fact> facts{};
    
    // Contradictions encountered
    std::vector<Contradiction> contradictions{};
    
    // Capture statistics
    size_t observation_count{0};
    size_t fact_count{0};
    size_t error_count{0};  // Observations with errors
    
    bool is_complete{false};  // Were all expected fields observed?
};

// ============================================================================
// SemanticStatus — Operation outcome semantics
// ============================================================================

enum class SemanticStatus {
    success,       // Operation completed successfully
    partial_success, // Some observations succeeded, some failed
    failure,       // Operation did not achieve its goal
    cancelled,     // Operation was cancelled
    timed_out,     // Operation exceeded time limit
    unknown,       // Cannot determine outcome (no evidence)
};

inline std::string to_string(SemanticStatus s) {
    switch (s) {
        case SemanticStatus::success:      return "success";
        case SemanticStatus::partial_success: return "partial-success";
        case SemanticStatus::failure:      return "failure";
        case SemanticStatus::cancelled:    return "cancelled";
        case SemanticStatus::timed_out:    return "timed-out";
        case SemanticStatus::unknown:      return "unknown";
    }
    return "unknown";
}

// ============================================================================
// Result — Observation operation outcome
// ============================================================================

struct Result {
    SemanticStatus status{SemanticStatus::unknown};
    
    std::optional<std::string> error_code{};
    std::optional<std::string> error_message{};
    
    std::vector<Snapshot> snapshots{};  // Observations grouped by subject
    
    // Timing
    std::chrono::system_clock::time_point started_at{};
    std::chrono::system_clock::time_point completed_at{};
};

// ============================================================================
// ObservationBounds — Resource limits for observation operations
// ============================================================================

struct ObservationBounds {
    size_t max_observations_per_request = 1000;
    std::chrono::milliseconds timeout_ms{30000};  // Total observation timeout
    
    // Per-source limits
    size_t max_processes = 1000;
    size_t max_services = 500;
    size_t max_devices = 1000;
};

// ============================================================================
// Factory functions for common observation types
// ============================================================================

inline Observation make_observation(
    SubjectIdentity subject,
    std::string domain,
    std::string field_name,
    std::optional<std::string> value = {},
    Provenance provenance = {}
) {
    Observation obs;
    obs.subject = std::move(subject);
    obs.domain = std::move(domain);
    obs.field_name = std::move(field_name);
    
    if (value.has_value()) {
        obs.value_type = Observation::ValueType::string;
        obs.string_value = value;
    } else {
        obs.value_type = Observation::ValueType::unknown_value;
    }
    
    obs.provenance = std::move(provenance);
    return obs;
}

inline Observation make_error_observation(
    SubjectIdentity subject,
    std::string domain,
    std::string field_name,
    UnknownReason reason,
    std::string message = {},
    Provenance provenance = {}
) {
    Observation obs;
    obs.subject = std::move(subject);
    obs.domain = std::move(domain);
    obs.field_name = std::move(field_name);
    
    obs.value_type = Observation::ValueType::unknown_value;
    obs.error_reason = reason;
    if (!message.empty()) {
        obs.error_message = std::move(message);
    }
    
    obs.provenance = std::move(provenance);
    return obs;
}

inline Fact make_direct_fact(
    Observation observation,
    FactType type,
    std::string field_name,
    ValuePresence presence
) {
    Fact fact;
    fact.id = "fact_" + observation.id;  // Derive from observation id
    fact.subject = observation.subject;
    fact.type = type;
    fact.field_name = std::move(field_name);
    fact.presence = presence;
    fact.supporting_observation_ids.push_back(observation.id);
    fact.established_at = observation.provenance.acquired_at;
    
    // Copy values if present
    if (observation.string_value.has_value()) {
        fact.string_value = observation.string_value;
    }
    if (observation.integer_value.has_value()) {
        fact.integer_value = observation.integer_value;
    }
    if (observation.metric_value.has_value()) {
        fact.numeric_value = observation.metric_value;
    }
    if (observation.boolean_value.has_value()) {
        fact.boolean_value = observation.boolean_value;
    }
    
    return fact;
}

inline Fact make_derived_fact(
    SubjectIdentity subject,
    FactType type,
    std::string field_name,
    const std::vector<std::string>& source_observation_ids,
    std::string derivation_rule,
    ValuePresence presence
) {
    Fact fact;
    fact.id = "derived_" + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::system_clock::now().time_since_epoch()).count());
    fact.subject = subject;
    fact.type = type;
    fact.field_name = std::move(field_name);
    fact.presence = presence;
    fact.supporting_observation_ids = source_observation_ids;
    fact.is_derived = true;
    fact.derivation_rule = std::move(derivation_rule);
    fact.established_at = std::chrono::system_clock::now();
    
    return fact;
}

}  // namespace rebuntu::system::observation

// Hash specializations for use in standard containers
namespace std {

template <>
struct hash<rebuntu::system::observation::SubjectIdentity> {
    size_t operator()(const rebuntu::system::observation::SubjectIdentity& id) const noexcept {
        size_t h1 = std::hash<std::string>{}(id.domain);
        size_t h2 = std::hash<std::string>{}(id.primary_id);
        return h1 ^ (h2 << 1);
    }
};

template <>
struct hash<rebuntu::system::observation::Observation> {
    size_t operator()(const rebuntu::system::observation::Observation& obs) const noexcept {
        size_t h = std::hash<std::string>{}(obs.id);
        h ^= std::hash<std::string>{}(obs.subject.domain) << 1;
        h ^= std::hash<std::string>{}(obs.field_name) << 2;
        return h;
    }
};

}  // namespace std