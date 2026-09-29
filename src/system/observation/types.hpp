// rebuntu::system::observation — Canonical Observation Architecture (Phase 7.0)
//
// This module defines the canonical observation architecture for Rebuntu:
//   - Observation: Raw, source-bound evidence obtained at a specific time
//   - Fact: Typed claim derived from one or more observations under explicit rules
//   - CurrentState: Composed snapshot of observations/facts for a bounded subject/domain/time

#pragma once

#include <chrono>
#include <optional>
#include <string>
#include <vector>
#include <set>
#include <memory>

// core/contracts.hpp provides core::Error and core::Outcome which are used by types below
#include <system/core/contracts.hpp>

// bounds.hpp is in rebuntu::observation namespace and we need ObservationBounds type
#include "bounds.hpp"

namespace rebuntu::system::observation {

// Forward declarations for local types
struct Snapshot;
struct ObservationIdentity;

// ============================================================================
// ObservationDomain — Canonical domains for system observation
// ============================================================================

enum class ObservationDomain {
    kUnknown,
    kProcess,
    kService,
    kFilesystem,
    kNetwork,
    kCPU,
    kMemory,
    kDevice,
    kGPU,
    kPower,
    kThermal,
    kSession,
};

inline std::string to_string(ObservationDomain d) {
    switch (d) {
        case ObservationDomain::kUnknown:   return "unknown";
        case ObservationDomain::kProcess:   return "process";
        case ObservationDomain::kService:   return "service";
        case ObservationDomain::kFilesystem:return "filesystem";
        case ObservationDomain::kNetwork:   return "network";
        case ObservationDomain::kCPU:       return "cpu";
        case ObservationDomain::kMemory:    return "memory";
        case ObservationDomain::kDevice:    return "device";
        case ObservationDomain::kGPU:       return "gpu";
        case ObservationDomain::kPower:     return "power";
        case ObservationDomain::kThermal:   return "thermal";
        case ObservationDomain::kSession:   return "session";
    }
    return "unknown";
}

// ============================================================================
// ObservationIdentity — Stable identity for an observed entity
// ============================================================================

struct ObservationIdentity {
    std::string domain_id;
    ObservationDomain domain{ObservationDomain::kUnknown};
    std::optional<std::string> name;
    
    bool is_valid() const {
        return !domain_id.empty() && domain != ObservationDomain::kUnknown;
    }
};

inline bool operator==(const ObservationIdentity& a, const ObservationIdentity& b) {
    return a.domain_id == b.domain_id && a.domain == b.domain;
}

inline bool operator<(const ObservationIdentity& a, const ObservationIdentity& b) {
    if (a.domain != b.domain) return a.domain < b.domain;
    return a.domain_id < b.domain_id;
}

// ============================================================================
// ObservationQuality — Confidence level for an observation
// ============================================================================

enum class ObservationQuality {
    kUnknown,
    kPartial,
    kObserved,
    kAuthoritative,
};

inline std::string to_string(ObservationQuality q) {
    switch (q) {
        case ObservationQuality::kUnknown:     return "unknown";
        case ObservationQuality::kPartial:     return "partial";
        case ObservationQuality::kObserved:    return "observed";
        case ObservationQuality::kAuthoritative:return "authoritative";
    }
    return "unknown";
}

// ============================================================================
// FreshnessPolicy — How freshness is determined and enforced
// ============================================================================

struct FreshnessPolicy {
    std::chrono::milliseconds max_age_ms{std::chrono::seconds(30)};
    bool allow_stale{false};
    bool fail_on_stale{false};
};

// ============================================================================
// Observation — Raw, source-bound evidence obtained at a specific time
// ============================================================================

struct Observation {
    ObservationIdentity subject;
    std::string field;
    std::optional<std::string> raw_value;
    std::optional<std::string> normalized_value;
    std::string source;
    std::chrono::system_clock::time_point acquired_at{};
    std::optional<std::chrono::system_clock::time_point> event_time;
    std::optional<std::chrono::steady_clock::time_point> monotonic_sample;
    ObservationQuality quality{ObservationQuality::kUnknown};
    std::optional<core::Error> error;
    std::optional<std::string> source_locator;
    
    static Observation make_state(
        ObservationIdentity subject,
        std::string field,
        std::string value,
        std::string source,
        std::chrono::system_clock::time_point acquired_at = {}
    ) {
        Observation o;
        o.subject = std::move(subject);
        o.field = std::move(field);
        o.raw_value = std::move(value);
        o.source = std::move(source);
        if (acquired_at == std::chrono::system_clock::time_point{}) {
            o.acquired_at = std::chrono::system_clock::now();
        } else {
            o.acquired_at = acquired_at;
        }
        return o;
    }
    
    static Observation make_property(
        ObservationIdentity subject,
        std::string field,
        std::optional<std::string> value,
        std::string source,
        std::chrono::system_clock::time_point acquired_at = {}
    ) {
        Observation o;
        o.subject = std::move(subject);
        o.field = std::move(field);
        o.raw_value = std::move(value);
        o.source = std::move(source);
        if (acquired_at == std::chrono::system_clock::time_point{}) {
            o.acquired_at = std::chrono::system_clock::now();
        } else {
            o.acquired_at = acquired_at;
        }
        return o;
    }
    
    static Observation make_error(
        ObservationIdentity subject,
        std::string field,
        core::Error error,
        std::string source
    ) {
        Observation o;
        o.subject = std::move(subject);
        o.field = std::move(field);
        o.error = std::move(error);
        o.source = std::move(source);
        o.acquired_at = std::chrono::system_clock::now();
        return o;
    }
};

inline std::string to_string(const Observation& o) {
    std::string result = "Observation{subject=" + o.subject.domain_id +
                        ", field=" + o.field +
                        ", source=" + o.source +
                        ", acquired_at=" + std::to_string(
                            std::chrono::duration_cast<std::chrono::seconds>(
                                o.acquired_at.time_since_epoch()).count());
    
    if (o.raw_value.has_value()) {
        result += ", raw_value=\"" + *o.raw_value + "\"";
    }
    
    if (o.normalized_value.has_value()) {
        result += ", normalized_value=\"" + *o.normalized_value + "\"";
    }
    
    result += "}";
    return result;
}

// ============================================================================
// TruthValue — Boolean-like truth assessment
// ============================================================================

enum class TruthValue {
    kTrue,
    kFalse,
    kUnknown,
};

inline std::string to_string(TruthValue v) {
    switch (v) {
        case TruthValue::kTrue:   return "true";
        case TruthValue::kFalse:  return "false";
        case TruthValue::kUnknown:return "unknown";
    }
    return "unknown";
}

// ============================================================================
// Fact — Typed claim derived from observations under explicit rules
// ============================================================================

struct Fact {
    ObservationIdentity subject;
    std::string predicate;
    std::optional<std::string> canonical_value;
    TruthValue truth{TruthValue::kUnknown};
    std::vector<ObservationIdentity> supporting_observations;
    bool direct_observation{true};
    std::optional<std::chrono::system_clock::time_point> valid_from;
    std::optional<std::chrono::system_clock::time_point> valid_until;
    ObservationQuality quality{ObservationQuality::kUnknown};
};

// ============================================================================
// SnapshotState — State of a snapshot composition
// ============================================================================

enum class SnapshotState {
    kUnknown,
    kComplete,
    kPartial,
    kEmpty,
};

inline std::string to_string(SnapshotState s) {
    switch (s) {
        case SnapshotState::kUnknown: return "unknown";
        case SnapshotState::kComplete:return "complete";
        case SnapshotState::kPartial: return "partial";
        case SnapshotState::kEmpty:   return "empty";
    }
    return "unknown";
}

// ============================================================================
// Truncation — Bounds enforcement status
// ============================================================================

struct Truncation {
    bool was_truncated = false;
    std::optional<size_t> records_dropped;
    std::optional<std::string> reason;
    
    static Truncation no_truncation() { return {}; }
    static Truncation with_reason(const std::string& r) {
        Truncation t; t.was_truncated = true; t.reason = r; return t;
    }
};

// ============================================================================
// Snapshot — Current-state projection from observations/facts
// ============================================================================

struct Snapshot {
    std::string snapshot_id;
    std::chrono::system_clock::time_point snapshot_time{};
    std::optional<std::chrono::system_clock::time_point> start_time;
    std::optional<std::chrono::milliseconds> elapsed_ms;
    std::set<ObservationDomain> observed_domains;
    std::vector<std::string> domains_failed;
    std::vector<Observation> observations;
    std::vector<Fact> facts;
    SnapshotState state{SnapshotState::kUnknown};
    ObservationQuality overall_quality{ObservationQuality::kUnknown};
    std::vector<std::pair<ObservationDomain, core::Error>> errors;
    Truncation truncation;
    
    static Snapshot make(const std::string& id = "") {
        Snapshot s;
        if (id.empty()) {
            auto now = std::chrono::system_clock::now();
            auto epoch = std::chrono::duration_cast<std::chrono::milliseconds>(
                now.time_since_epoch()).count();
            s.snapshot_id = "snapshot_" + std::to_string(epoch);
        } else {
            s.snapshot_id = id;
        }
        s.snapshot_time = std::chrono::system_clock::now();
        return s;
    }
    
    static Snapshot make_empty(const std::string& reason = "") {
        Snapshot s = make();
        s.state = SnapshotState::kEmpty;
        if (!reason.empty()) {
            s.errors.emplace_back(ObservationDomain::kUnknown,
                core::Error{"E_SNAPSHOT_EMPTY", reason});
        }
        return s;
    }
    
    void add_observation(Observation o) {
        observations.push_back(std::move(o));
        observed_domains.insert(observations.back().subject.domain);
    }
    
    void add_fact(Fact f) {
        facts.push_back(std::move(f));
        if (facts.back().direct_observation && !facts.back().supporting_observations.empty()) {
            observed_domains.insert(facts.back().supporting_observations.front().domain);
        }
    }
    
    void mark_failed(ObservationDomain d, core::Error e) {
        domains_failed.push_back(to_string(d));
        errors.emplace_back(d, std::move(e));
    }
};

// ============================================================================
// SnapshotBuilder — Interface for constructing snapshots incrementally
// ============================================================================

class SnapshotBuilder {
public:
    virtual ~SnapshotBuilder() = default;
    
    virtual core::Outcome start(const std::string& id = "") = 0;
    virtual core::Outcome configure_bounds(
        const rebuntu::observation::ObservationBounds& bounds) = 0;
    virtual core::Outcome add_observation(Observation o) = 0;
    virtual core::Outcome add_fact(Fact f) = 0;
    virtual core::Outcome mark_domain_complete(ObservationDomain d) = 0;
    virtual core::Outcome mark_domain_failed(ObservationDomain d, core::Error e) = 0;
    virtual core::Outcome set_snapshot_state(SnapshotState s) = 0;
    virtual std::optional<Snapshot> build() = 0;
};

// ============================================================================
// ObservationAdapter — Interface for domain-specific observation sources
// ============================================================================

class ObservationAdapter {
public:
    virtual ~ObservationAdapter() = default;
    
    virtual ObservationDomain domain() const = 0;
    virtual core::Outcome observe(
        std::optional<ObservationIdentity> subject,
        std::vector<Observation>& out_observations) = 0;
    virtual std::pair<bool, std::chrono::milliseconds> is_fresh(
        const Observation& o,
        const FreshnessPolicy& policy) = 0;
    virtual core::Outcome invalidate() = 0;
};

// ============================================================================
// CurrentStateView — Interface for current-state snapshot composition
// ============================================================================

class CurrentStateView {
public:
    virtual ~CurrentStateView() = default;
    
    virtual std::optional<Snapshot> get_snapshot(
        const std::set<ObservationDomain>& domains,
        const rebuntu::observation::ObservationBounds& bounds) = 0;
    virtual std::vector<Fact> get_facts(const ObservationIdentity& subject) = 0;
    virtual bool is_fresh(
        const ObservationIdentity& subject,
        const FreshnessPolicy& policy) = 0;
    virtual std::optional<std::chrono::system_clock::time_point> 
    last_snapshot_time() const = 0;
};

// ============================================================================
// Factory functions
// ============================================================================

std::unique_ptr<SnapshotBuilder> make_snapshot_builder();
std::unique_ptr<CurrentStateView> make_current_state_view();

}  // namespace rebuntu::system::observation