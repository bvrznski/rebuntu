// rebuntu::core::evidence::freshness — Freshness Policy Implementation (Phase 7.4)
//
// This module implements the canonical freshness evaluation utilities.

#include "core/evidence/freshness/types.hpp"

namespace rebuntu::core::evidence::freshness {

// -----------------------------------------------------------------------------
// FreshnessEvaluator implementation
// -----------------------------------------------------------------------------

FreshnessResult FreshnessEvaluator::check_freshness(
    std::optional<std::chrono::system_clock::time_point> observed_at,
    std::optional<FreshnessTTL> ttl,
    std::chrono::system_clock::time_point now
) {
    FreshnessResult result;
    
    // If we don't have an observation time, we can't determine freshness
    if (!observed_at.has_value()) {
        result.overall_reason = StalenessReason::kSourceUnavailable;
        return result;
    }
    
    result.observed_at = observed_at;
    
    // Calculate age
    auto age = calculate_age(*observed_at, now);
    if (age.has_value()) {
        result.age_ms = age;
    }
    
    // If no TTL is provided, consider it fresh (indefinite validity)
    if (!ttl.has_value()) {
        result.overall_reason = StalenessReason::kNone;
        return result;
    }
    
    result.applied_ttl = ttl;
    
    // Check if expired
    if (ttl->is_expired(now, *observed_at)) {
        result.overall_reason = StalenessReason::kTTLSuperseded;
    } else {
        result.overall_reason = StalenessReason::kNone;
    }
    
    return result;
}

StalenessReason FreshnessEvaluator::check_field_freshness(
    std::optional<std::chrono::system_clock::time_point> observed_at,
    const FieldFreshnessPolicy& policy,
    std::chrono::system_clock::time_point now
) {
    // If no observation time, can't determine freshness
    if (!observed_at.has_value()) {
        return StalenessReason::kSourceUnavailable;
    }
    
    // If TTL is set and exceeded, stale
    if (policy.ttl.has_value() && 
        policy.ttl->is_expired(now, *observed_at)) {
        return StalenessReason::kTTLSuperseded;
    }
    
    return StalenessReason::kNone;
}

std::optional<std::chrono::milliseconds> FreshnessEvaluator::calculate_age(
    std::chrono::system_clock::time_point observed_at,
    std::chrono::system_clock::time_point now
) {
    auto diff = now - observed_at;
    if (diff < std::chrono::milliseconds::zero()) {
        // Observation is in the future (clock adjustment)
        return std::chrono::milliseconds::zero();
    }
    return std::chrono::duration_cast<std::chrono::milliseconds>(diff);
}

}  // namespace rebuntu::core::evidence::freshness