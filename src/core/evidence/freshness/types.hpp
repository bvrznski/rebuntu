// rebuntu::core::evidence::freshness — Freshness Policy & Staleness Detection (Phase 7.4)
//
// This module establishes the canonical freshness vocabulary:
//   - FreshnessTTL: How long an observation is considered valid
//   - ObservationTimepoints: Acquisition time, event time, sample window
//   - Staleness: When an observation exceeds its TTL
//   - FieldSpecificFreshness: Different TTLs per observation field
//
// Key Distinctions:
//   - Event Time: When the actual event occurred (if source provides it)
//   - Acquisition Time: When Rebuntu read the data from the source
//   - Sample Window: For rate metrics, the time period over which the rate was calculated
//   - Freshness TTL: How long this observation is considered "current enough"
//
// Design Principle:
//   A single global TTL is NEVER appropriate. Static CPU topology can remain fresh
//   for hours, while process existence changes every millisecond.

#pragma once

#include <chrono>
#include <cstdint>
#include <map>
#include <optional>
#include <string>
#include <string_view>
#include <vector>

namespace rebuntu::core::evidence::freshness {

// -----------------------------------------------------------------------------
// ClockSource — Which clock was used for timestamping
// -----------------------------------------------------------------------------
enum class ClockSource {
    kWallClock,      // System wall-clock (system_clock)
    kMonotonic,      // Monotonic clock (steady_clock) - best for durations
    kBootTime,       // Boot time including suspend
};

inline std::string_view to_string(ClockSource s) {
    switch (s) {
        case ClockSource::kWallClock:   return "wall_clock";
        case ClockSource::kMonotonic:   return "monotonic";
        case ClockSource::kBootTime:    return "boot_time";
    }
    return "unknown";
}

// -----------------------------------------------------------------------------
// FreshnessTTL — Time-to-live for an observation
//
// Represents the maximum age an observation can have and still be considered
// "current". Different domains and fields have different freshness requirements:
//   - CPU topology: hours/days (static)
//   - Process list: seconds (changes rapidly)
//   - Thermal readings: seconds (changes rapidly)
//   - Filesystem usage: minutes/hours (changes slowly)
//
// Note: This is NOT a cache TTL. It's a semantic freshness boundary.
// -----------------------------------------------------------------------------
struct FreshnessTTL {
    std::chrono::milliseconds value;
    
    static constexpr FreshnessTTL from_seconds(int64_t s) {
        return FreshnessTTL{std::chrono::seconds(s)};
    }
    static constexpr FreshnessTTL from_minutes(int64_t m) {
        return FreshnessTTL{std::chrono::minutes(m)};
    }
    static constexpr FreshnessTTL from_hours(int64_t h) {
        return FreshnessTTL{std::chrono::hours(h)};
    }
    
    bool is_expired(std::chrono::system_clock::time_point now,
                    std::chrono::system_clock::time_point observed_at) const {
        auto age = now - observed_at;
        return age > value;
    }
    
    // Is this TTL effectively "no freshness check" (infinite)?
    bool is_indefinite() const { return value.count() < 0; }
};

inline constexpr FreshnessTTL operator""_ttl_s(unsigned long long s) {
    return FreshnessTTL::from_seconds(s);
}
inline constexpr FreshnessTTL operator""_ttl_m(unsigned long long m) {
    return FreshnessTTL::from_minutes(m);
}

// -----------------------------------------------------------------------------
// ObservationTimepoints — Timestamps associated with an observation
//
// A complete observation record includes multiple timestamps:
//   - event_time: When the actual event occurred (if source provides it)
//   - acquisition_time: When Rebuntu observed/read the data
//   - sample_start/stop: For rate metrics, the window over which rate was calculated
// -----------------------------------------------------------------------------
struct ObservationTimepoints {
    // Event time: When the actual event/state change occurred at the source
    std::optional<std::chrono::system_clock::time_point> event_time;
    
    // Acquisition time: When Rebuntu read this from the source
    std::optional<std::chrono::system_clock::time_point> acquisition_time;
    
    // Sample window (for rate metrics)
    std::optional<std::chrono::milliseconds> sample_window_ms;
};

// -----------------------------------------------------------------------------
// StalenessReason — Why an observation is stale
//
// Multiple reasons can cause staleness:
//   - TTL_EXCEEDED: Observation age > FreshnessTTL
//   - SOURCE_UNAVAILABLE: Source no longer responds (can't verify freshness)
//   - PARTIAL_OBSERVATION: Some fields missing, overall result incomplete
// -----------------------------------------------------------------------------
enum class StalenessReason {
    kNone,               // Observation is fresh (not stale at all)
    kTTLSuperseded,      // TTL has been exceeded
    kSourceUnavailable,  // Source not available for freshness check
    kPartial,            // Only partial data available
};

inline std::string_view to_string(StalenessReason r) {
    switch (r) {
        case StalenessReason::kNone:             return "fresh";
        case StalenessReason::kTTLSuperseded:    return "ttl-exceeded";
        case StalenessReason::kSourceUnavailable:return "source-unavailable";
        case StalenessReason::kPartial:          return "partial-observation";
    }
    return "unknown";
}

// -----------------------------------------------------------------------------
// FieldFreshnessPolicy — Per-field freshness configuration
//
// Different fields in an observation may have different freshness requirements:
//   - A GPU device's PCI address is effectively static (indefinite TTL)
//   - The same GPU's temperature changes rapidly (short TTL)
//   - Usage statistics require sample window context
//
// This allows fine-grained control over what constitutes "current" for each field.
// -----------------------------------------------------------------------------
struct FieldFreshnessPolicy {
    std::optional<FreshnessTTL> ttl;
    
    // Is this field required to be fresh for the observation to be valid?
    bool is_critical{false};
    
    // If source unavailable, should we fall back to stale value or report unknown?
    bool allow_stale_on_unavailable{true};
};

// -----------------------------------------------------------------------------
// FreshnessResult — Overall freshness status of an observation
//
// Combines all freshness information:
//   - Is the observation fresh or stale?
//   - If stale: Why? (TTL exceeded, source unavailable, etc.)
//   - Per-field staleness breakdown
//   - Age calculation for diagnostic purposes
// -----------------------------------------------------------------------------
struct FreshnessResult {
    // Overall status
    StalenessReason overall_reason{StalenessReason::kNone};
    
    // When the observation was made
    std::optional<std::chrono::system_clock::time_point> observed_at;
    
    // How old is this observation?
    std::optional<std::chrono::milliseconds> age_ms;
    
    // What TTL was it compared against (if any)?
    std::optional<FreshnessTTL> applied_ttl;
    
    // Per-field freshness (for structured observations with multiple fields)
    std::map<std::string, StalenessReason> field_reasons;
};

// -----------------------------------------------------------------------------
// FreshnessContext — Context for freshness evaluation
//
// Used when evaluating whether an observation is fresh enough:
//   - The observation's timestamp(s)
//   - The requested TTL/policy
//   - The current "now" time for comparison
// -----------------------------------------------------------------------------
struct FreshnessContext {
    std::chrono::system_clock::time_point now;
    
    // What freshness policy applies to this observation?
    std::optional<FreshnessTTL> requested_ttl;
    
    // When was the observation actually made?
    std::optional<std::chrono::system_clock::time_point> observed_at;
};

// -----------------------------------------------------------------------------
// FreshnessEvaluator — Evaluates whether observations meet freshness requirements
//
// This is a stateless utility for checking freshness:
//   - Compare acquisition time against TTL
//   - Calculate age in milliseconds
//   - Determine staleness reason
//   - Evaluate per-field freshness policies
// -----------------------------------------------------------------------------
class FreshnessEvaluator {
public:
    // Check if an observation is fresh given its timestamp and a TTL
    static FreshnessResult check_freshness(
        std::optional<std::chrono::system_clock::time_point> observed_at,
        std::optional<FreshnessTTL> ttl,
        std::chrono::system_clock::time_point now = std::chrono::system_clock::now()
    );
    
    // Check if a field meets its freshness policy
    static StalenessReason check_field_freshness(
        std::optional<std::chrono::system_clock::time_point> observed_at,
        const FieldFreshnessPolicy& policy,
        std::chrono::system_clock::time_point now = std::chrono::system_clock::now()
    );
    
    // Calculate age in milliseconds from a timestamp
    static std::optional<std::chrono::milliseconds> calculate_age(
        std::chrono::system_clock::time_point observed_at,
        std::chrono::system_clock::time_point now = std::chrono::system_clock::now()
    );
};

// -----------------------------------------------------------------------------
// StalenessMarker — Marks observations as stale or fresh
//
// Used by adapters to mark their results:
//   - If observation is fresh: mark as valid
//   - If stale: mark with reason and provide option to return anyway
// -----------------------------------------------------------------------------
template<typename T>
struct FreshnessMarked {
    // The actual value if available
    std::optional<T> value;
    
    // Is this value fresh?
    bool is_fresh{false};
    
    // Why might it be stale (or is it fresh)?
    StalenessReason staleness_reason{StalenessReason::kNone};
    
    // When was the observation made?
    std::chrono::system_clock::time_point observed_at{};
};

}  // namespace rebuntu::core::evidence::freshness

// -----------------------------------------------------------------------------
// Standard hash specializations
// -----------------------------------------------------------------------------
namespace std {

template<>
struct hash<rebuntu::core::evidence::freshness::FreshnessTTL> {
    size_t operator()(const rebuntu::core::evidence::freshness::FreshnessTTL& ttl) const noexcept {
        return std::hash<int64_t>{}(ttl.value.count());
    }
};

}  // namespace std
