// rebuntu::core::evidence::fact — Evidence, Facts, and Current-State Semantics (Phase 7.4)
//
// This module establishes the canonical vocabulary for evidence and facts:
//   - Observation: Raw data acquired from a native source at a specific time
//   - Fact: Typed claim derived from observations under explicit rules
//   - CurrentState: Projection of facts as "current" state for consumers
//   - Provenance: Traceable chain from observation to fact
//
// Key Distinctions:
//   - Observation = raw evidence (source-bound, timestamped)
//   - Fact = derived claim (evaluated, typed, possibly verified)
//   - CurrentState = projection of facts as "now" for query consumers
//
// Semantics:
//   - Event Time: When the event/state actually occurred at source
//   - Acquisition Time: When Rebuntu read it from the source
//   - Staleness: Age vs TTL determines freshness
//   - UNKNOWN is valid (not FALSE, not NULL)

#pragma once

#include "core/evidence/freshness/types.hpp"
#include <chrono>
#include <cstdint>
#include <map>
#include <optional>
#include <string>
#include <string_view>
#include <vector>

namespace rebuntu::core::evidence::fact {

// -----------------------------------------------------------------------------
// EvidenceCategory — What kind of observation was made
// -----------------------------------------------------------------------------
enum class EvidenceCategory {
    kState,              // System state (running/stopped/unknown)
    kProperty,           // Attribute value (version, path, type)
    kMetric,             // Numeric measurement (usage, temperature, count)
    kPresence,           // Entity existence (exists/not_found)
    kConfiguration,      // Configuration value
    kRelationship,       // Relationship between entities
    kError,              // Error condition observed
    kUnknown,            // Unknown category
};

inline std::string to_string(EvidenceCategory c) {
    switch (c) {
        case EvidenceCategory::kState:         return "state";
        case EvidenceCategory::kProperty:      return "property";
        case EvidenceCategory::kMetric:        return "metric";
        case EvidenceCategory::kPresence:      return "presence";
        case EvidenceCategory::kConfiguration: return "configuration";
        case EvidenceCategory::kRelationship:  return "relationship";
        case EvidenceCategory::kError:         return "error";
    }
    return "unknown";
}

// -----------------------------------------------------------------------------
// SourceType — Where evidence came from (native Linux source)
// -----------------------------------------------------------------------------
enum class SourceType {
    kProcfs,             // /proc filesystem
    kSysfs,              // /sys filesystem
    kD_Bus,              // D-Bus interface
    kNetlink,            // Netlink/rtnetlink
    kUdev,               // udev properties
    kKernel,             // Kernel interfaces (/dev/*)
    kSystemd,            // systemd manager
   kJournald,           // journald structured logs
    kHardware,           // Hardware sensor/DMI/SMI
    kUnknown,            // Unknown source
};

inline std::string to_string(SourceType s) {
    switch (s) {
        case SourceType::kProcfs:     return "procfs";
        case SourceType::kSysfs:      return "sysfs";
        case SourceType::kD_Bus:      return "dbus";
        case SourceType::kNetlink:    return "netlink";
        case SourceType::kUdev:       return "udev";
        case SourceType::kKernel:     return "kernel";
        case SourceType::kSystemd:    return "systemd";
        case SourceType::kJournald:   return "journald";
        case SourceType::kHardware:   return "hardware";
        case SourceType::kUnknown:    return "unknown";
    }
    return "unknown";
}

// -----------------------------------------------------------------------------
// Observation — Raw evidence from a native source
//
// An observation is:
//   - Bound to a subject (what it's about)
//   - Timestamped (when acquired)
//   - Source-identified (where it came from)
//   - Value-carrying (the actual observed data)
//
// Note: Observations are NOT facts. They are the raw input.
// -----------------------------------------------------------------------------
struct Observation {
    // Unique identifier for this observation
    std::string observation_id;
    
    // What this observation is about
    std::string subject;          // e.g., "process:1234", "service:apache2"
    
    // Where it came from
    SourceType source_type{SourceType::kUnknown};
    std::string source_path;      // /proc/123/status, sysfs path, etc.
    
    // When it was acquired (Rebuntu's reading time)
    std::chrono::system_clock::time_point acquisition_time{};
    
    // Event time if provided by source (when event actually occurred)
    std::optional<std::chrono::system_clock::time_point> event_time;
    
    // Sample window for rate metrics
    std::optional<std::chrono::milliseconds> sample_window_ms;
    
    // The observation category
    EvidenceCategory category{EvidenceCategory::kUnknown};
    
    // The raw value (parsed from source)
    std::string raw_value;
    
    // Normalized value (canonical representation)
    std::string normalized_value;
    
    // Was this directly observed or derived?
    bool is_derived{false};
    
    // Derivation metadata if derived
    std::optional<std::string> derivation_method;
    std::vector<std::string> source_observations;  // IDs of observations this was derived from
    
    // Sampling information (for metrics)
    uint64_t sample_count{0};     // How many samples in this observation
};

// -----------------------------------------------------------------------------
// Fact — Typed claim derived from observations
//
// A fact is:
//   - A typed claim about the system
//   - Traceable to evidence (one or more observations)
//   - Evaluated against rules
//   - May be verified or unverified
//
// Facts are what consumers actually use, not raw observations.
// -----------------------------------------------------------------------------
enum class FactType {
    kState,               // State fact (process running, service active)
    kProperty,            // Property fact (version, path, type)
    kMetric,              // Metric fact (CPU usage 45.2%)
    kRelationship,        // Relationship fact (parent-child, depends-on)
    kCondition,           // Condition fact (is_ready: true)
};

inline std::string to_string(FactType t) {
    switch (t) {
        case FactType::kState:      return "state";
        case FactType::kProperty:   return "property";
        case FactType::kMetric:     return "metric";
        case FactType::kRelationship:return "relationship";
        case FactType::kCondition:  return "condition";
    }
    return "unknown";
}

struct FactValue {
    // The canonical value (typed)
    enum class Kind {
        kString,
        kBoolean,
        kInteger,
        kFloatingPoint,
        kTimestamp,
        kDuration,
        kUnknown,
    } kind{Kind::kUnknown};
    
    std::string as_string;
    bool as_boolean{false};
    int64_t as_integer{0};
    double as_floating_point{0.0};
    std::chrono::system_clock::time_point as_timestamp{};
    std::chrono::milliseconds as_duration_ms{0};
};

struct Fact {
    // Unique identifier for this fact
    std::string fact_id;
    
    // Subject of the claim
    std::string subject;
    
    // Type of fact
    FactType type{FactType::kState};
    
    // Canonical value/state
    FactValue value;
    
    // Supporting evidence (observations that produced this fact)
    std::vector<std::string> supporting_observations;
    
    // Was this directly observed or derived?
    bool is_derived{false};
    std::optional<std::string> derivation_method;
    
    // Freshness status
    freshness::FreshnessResult freshness;
    
    // Verification status (if applicable)
    enum class VerificationStatus {
        kNotVerified,       // Has not been verified
        kVerifiedPass,      // Verified and passed
        kVerifiedFail,      // Verified but failed
        kVerificationSkipped,// Verification not applicable
    } verification_status{VerificationStatus::kNotVerified};
};

// -----------------------------------------------------------------------------
// CurrentStateProjection — Current-state view of facts for consumers
//
// A current-state is:
//   - A bounded projection (time + domain scope)
//   - Contains fresh and stale facts
//   - Marks staleness explicitly
//   - May be partial (some sources unavailable)
// -----------------------------------------------------------------------------
struct CurrentStateProjection {
    // When this state snapshot was taken
    std::chrono::system_clock::time_point captured_at{};
    
    // Duration of capture
    std::chrono::milliseconds capture_duration_ms{0};
    
    // All facts in this projection
    std::vector<Fact> facts;
    
    // Statistics by freshness
    size_t fresh_facts{0};
    size_t stale_facts{0};
    size_t unknown_staleness_facts{0};
    
    // Sources that contributed (for provenance)
    std::vector<std::string> contributing_sources;
    
    // Partial capture indicators
    bool is_complete_capture{true};  // False if some sources were unavailable
    
    std::optional<freshness::StalenessReason> partial_reason;
};

// -----------------------------------------------------------------------------
// StateDimension — An orthogonal state dimension (Phase 0 grammar)
// -----------------------------------------------------------------------------
enum class StateDimension {
    kLifecycle,     // initialized/running/completed/failed
    kActivity,      // busy/idling/sleeping/waiting
    kControl,       // enabled/disabled/paused/frozen
    kReadiness,     // ready/not_ready/unknown
    kHealth,        // healthy/degraded/unhealthy/unknown
    kOutcome,       // completed/failed/cancelled/timed_out
};

inline std::string to_string(StateDimension d) {
    switch (d) {
        case StateDimension::kLifecycle:   return "lifecycle";
        case StateDimension::kActivity:    return "activity";
        case StateDimension::kControl:     return "control";
        case StateDimension::kReadiness:   return "readiness";
        case StateDimension::kHealth:      return "health";
        case StateDimension::kOutcome:     return "outcome";
    }
    return "unknown";
}

// -----------------------------------------------------------------------------
// StalenessPolicy — How to handle stale observations
// -----------------------------------------------------------------------------
enum class StalenessBehavior {
    kReject,              // Reject if stale (return UNKNOWN)
    kAcceptWithMarker,    // Accept but mark as stale
    kRefreshOnStale,      // Attempt refresh if stale
    kAllowUnknown,        // Allow UNKNOWN as valid response
};

struct StalenessPolicy {
    StalenessBehavior behavior{StalenessBehavior::kReject};
    
    // For kAcceptWithMarker: how much staleness to tolerate
    std::optional<freshness::FreshnessTTL> maximum_staleness;
    
    // Should we attempt automatic refresh on stale?
    bool allow_auto_refresh{false};
};

// -----------------------------------------------------------------------------
// ObservationBuilder — Fluent API for building observations
// -----------------------------------------------------------------------------
class ObservationBuilder {
public:
    static ObservationBuilder create(std::string subject) {
        return ObservationBuilder(std::move(subject));
    }
    
    ObservationBuilder& with_source(SourceType type, std::string path) {
        obs_.source_type = type;
        obs_.source_path = std::move(path);
        return *this;
    }
    
    ObservationBuilder& with_acquisition_time(std::chrono::system_clock::time_point t) {
        obs_.acquisition_time = t;
        return *this;
    }
    
    ObservationBuilder& with_event_time(std::chrono::system_clock::time_point t) {
        obs_.event_time = t;
        return *this;
    }
    
    ObservationBuilder& with_sample_window(std::chrono::milliseconds w) {
        obs_.sample_window_ms = w;
        return *this;
    }
    
    ObservationBuilder& as_derived(std::string method, std::vector<std::string> sources) {
        obs_.is_derived = true;
        obs_.derivation_method = std::move(method);
        obs_.source_observations = std::move(sources);
        return *this;
    }
    
    ObservationBuilder& with_category(EvidenceCategory c) {
        obs_.category = c;
        return *this;
    }
    
    ObservationBuilder& with_raw_value(std::string v) {
        obs_.raw_value = std::move(v);
        return *this;
    }
    
    ObservationBuilder& with_normalized_value(std::string v) {
        obs_.normalized_value = std::move(v);
        return *this;
    }
    
    Observation build() { return std::move(obs_); }

private:
    explicit ObservationBuilder(std::string subject)
        : obs_(Observation{}) {
        obs_.subject = std::move(subject);
    }
    
    Observation obs_;
};

}  // namespace rebuntu::core::evidence::fact

// -----------------------------------------------------------------------------
// Standard hash specializations
// -----------------------------------------------------------------------------
namespace std {

template<>
struct hash<rebuntu::core::evidence::fact::Fact> {
    size_t operator()(const rebuntu::core::evidence::fact::Fact& f) const noexcept {
        return std::hash<std::string>{}(f.fact_id);
    }
};

}  // namespace std