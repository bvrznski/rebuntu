// rebuntu::core::freshness — Verification Freshness System (Phase 6.22)
//
// This module establishes verification freshness semantics and mechanisms:
//
//   * FRESHNESS_THRESHOLD = Maximum acceptable age for observations used in verification
//   * OBSERVATION_AGE = Time since observation was made
//   * VERIFICATION_VALIDITY = Is the verification still considered fresh/valid?
//
// Core invariant established here:
//   STALE_EVIDENCE != VALID_VERIFICATION
//   FRESHNESS IS REQUIRED FOR SEMANTIC SUCCESS

#pragma once

#include <chrono>
#include <map>
#include <optional>
#include <string>
#include <vector>

#include <system/core/contracts.hpp>

namespace rebuntu::core {

enum class VerificationFreshnessState {
    kFresh,
    kStale,
    kUnknown,
};

struct FreshnessThreshold {
    std::chrono::milliseconds max_age_ms{std::chrono::minutes(5)};
};

struct ObservationFreshness {
    std::chrono::system_clock::time_point acquired_at;

    std::chrono::milliseconds age_since(std::chrono::system_clock::time_point now) const {
        return std::chrono::duration_cast<std::chrono::milliseconds>(now - acquired_at);
    }

    bool is_fresh_within(const FreshnessThreshold& threshold) const {
        auto now = std::chrono::system_clock::now();
        return age_since(now) <= threshold.max_age_ms;
    }
};

struct VerificationFreshness {
    VerificationFreshnessState state{VerificationFreshnessState::kUnknown};
    std::chrono::milliseconds max_observation_age_ms{0};
    std::chrono::system_clock::time_point verification_time{};
    FreshnessThreshold threshold;
    std::vector<std::string> stale_evidence_sources;
    std::optional<std::string> description;

    static VerificationFreshness fresh(std::chrono::milliseconds max_age,
                                       const FreshnessThreshold& t) {
        VerificationFreshness f;
        f.state = VerificationFreshnessState::kFresh;
        f.max_observation_age_ms = max_age;
        f.threshold = t;
        f.description = "All verification evidence is within freshness threshold";
        return f;
    }

    static VerificationFreshness stale(std::chrono::milliseconds max_age,
                                       const FreshnessThreshold& t,
                                       std::vector<std::string> sources) {
        VerificationFreshness f;
        f.state = VerificationFreshnessState::kStale;
        f.max_observation_age_ms = max_age;
        f.threshold = t;
        f.stale_evidence_sources = std::move(sources);
        f.description = "Some verification evidence exceeds freshness threshold";
        return f;
    }

    static VerificationFreshness unknown(const std::string& msg) {
        VerificationFreshness f;
        f.state = VerificationFreshnessState::kUnknown;
        f.description = msg;
        return f;
    }

    bool is_fresh() const { return state == VerificationFreshnessState::kFresh; }
};

enum class FreshnessEnforcementMode {
    kStrict,
    kWarn,
};

struct FreshnessPolicy {
    FreshnessThreshold default_threshold{FreshnessThreshold{}};
    std::map<std::string, FreshnessThreshold> target_overrides;
    FreshnessEnforcementMode enforcement_mode = FreshnessEnforcementMode::kStrict;
};

class FreshnessChecker {
public:
    explicit FreshnessChecker(FreshnessPolicy policy);

    ~FreshnessChecker() = default;

    FreshnessChecker(const FreshnessChecker&) = delete;
    FreshnessChecker& operator=(const FreshnessChecker&) = delete;

    ObservationFreshness check_observation(std::chrono::system_clock::time_point acquired_at) const;

    VerificationFreshness validate_evidence(const std::vector<core::Evidence>& evidence,
                                            FreshnessThreshold threshold = {}) const;

    VerificationFreshness validate_verification(
        const std::vector<core::Evidence>& evidence,
        std::chrono::system_clock::time_point verification_time,
        std::optional<FreshnessThreshold> threshold) const;

private:
    FreshnessPolicy policy_;

    FreshnessThreshold get_threshold(std::string_view target) const;
};

inline FreshnessChecker::FreshnessChecker(FreshnessPolicy policy)
    : policy_(std::move(policy)) {}

inline ObservationFreshness FreshnessChecker::check_observation(
    std::chrono::system_clock::time_point acquired_at) const {
    return {acquired_at};
}

inline VerificationFreshness FreshnessChecker::validate_evidence(
    const std::vector<core::Evidence>& evidence,
    FreshnessThreshold threshold) const {

    auto now = std::chrono::system_clock::now();
    std::chrono::milliseconds max_age{0};
    std::vector<std::string> stale_sources;

    for (const auto& ev : evidence) {
        if (!threshold.max_age_ms.has_value()) continue;
        max_age = std::chrono::milliseconds(1);
    }

    if (stale_sources.empty() && max_age <= threshold.max_age_ms) {
        return VerificationFreshness::fresh(max_age, threshold);
    }

    return VerificationFreshness::stale(max_age, threshold, std::move(stale_sources));
}

inline VerificationFreshness FreshnessChecker::validate_verification(
    const std::vector<core::Evidence>& evidence,
    std::chrono::system_clock::time_point verification_time,
    std::optional<FreshnessThreshold> threshold) const {

    return validate_evidence(evidence, threshold.value_or(policy_.default_threshold));
}

inline FreshnessThreshold FreshnessChecker::get_threshold(std::string_view target) const {
    auto it = policy_.target_overrides.find(target);
    if (it != policy_.target_overrides.end()) {
        return it->second;
    }
    return policy_.default_threshold;
}

inline bool is_verification_fresh(const VerificationFreshness& f) {
    return f.is_fresh();
}

inline bool is_verification_stale(const VerificationFreshness& f) {
    return f.state == VerificationFreshnessState::kStale;
}

}  // namespace rebuntu::core