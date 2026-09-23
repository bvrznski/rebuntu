#pragma once

#include <runtime/core/contracts.hpp>
#include <runtime/contracts.hpp>
#include <algorithm>
#include <chrono>
#include <optional>
#include <string>
#include <string_view>
#include <vector>

namespace rebuntu::runtime::results {

template <typename T = void>
struct Result {
    std::string definition_id;
    std::string execution_id;
    std::optional<std::string> attempt_id;
    std::chrono::system_clock::time_point started_at;
    std::chrono::system_clock::time_point finished_at;
    core::SemanticStatus outcome;
    std::optional<T> value;
    std::vector<core::Error> errors;
    bool verification_successful = false;
    std::chrono::milliseconds verification_duration_ms{0};
    struct Outputs { std::string stdout_data; std::string stderr_data; int exit_status = 0; };
    std::optional<Outputs> outputs;
    std::vector<core::Evidence> evidence;
    bool was_cancelled = false;
    bool timed_out = false;
    std::optional<std::string> cancellation_reason;
    std::optional<std::string> timeout_reason;
    int attempt_number = 1;
    
    static Result success(T v, const core::Evidence& ev = {}) {
        Result r; r.outcome = core::SemanticStatus::kSuccess; r.value = std::move(v);
        if (!ev.source.empty()) r.evidence.push_back(ev); return r;
    }
    static Result completed(T v) { Result r; r.outcome = core::SemanticStatus::kCompleted; 
        r.verification_successful = false; r.value = std::move(v); return r; }
    static Result failure(std::string code, std::string message) {
        Result r; r.outcome = core::SemanticStatus::kFailure;
        r.errors.push_back({std::move(code), std::move(message)}); return r;
    }
    static Result unknown(std::string message) { Result r;
        r.outcome = core::SemanticStatus::kUnknown; r.errors.push_back({"E_UNKNOWN", std::move(message)}); return r; }
    static Result cancelled(std::string reason) { Result r; r.outcome = core::SemanticStatus::kCancelled;
        r.was_cancelled = true; r.cancellation_reason = std::move(reason); return r; }
    static Result timed_out() { Result r; r.outcome = core::SemanticStatus::kFailure;
        r.timed_out = true; r.timeout_reason = "execution exceeded timeout"; return r; }
    bool succeeded() const { return outcome == core::SemanticStatus::kSuccess && verification_successful; }
    bool has_value() const { return value.has_value(); }
};

template <>
struct Result<void> {
    std::string definition_id; std::string execution_id;
    std::optional<std::string> attempt_id;
    std::chrono::system_clock::time_point started_at;
    std::chrono::system_clock::time_point finished_at;
    core::SemanticStatus outcome;
    std::vector<core::Error> errors;
    bool verification_successful = false;
    std::chrono::milliseconds verification_duration_ms{0};
    struct Outputs { std::string stdout_data; std::string stderr_data; int exit_status = 0; };
    std::optional<Outputs> outputs;
    std::vector<core::Evidence> evidence;
    bool was_cancelled = false;
    bool timed_out = false;
    std::optional<std::string> cancellation_reason;
    std::optional<std::string> timeout_reason;
    int attempt_number = 1;
    
    static Result success(const core::Evidence& ev = {}) {
        Result r; r.outcome = core::SemanticStatus::kSuccess;
        if (!ev.source.empty()) r.evidence.push_back(ev); return r;
    }
    static Result completed() { Result r; r.outcome = core::SemanticStatus::kCompleted;
        r.verification_successful = false; return r; }
    static Result failure(std::string code, std::string message) {
        Result r; r.outcome = core::SemanticStatus::kFailure;
        r.errors.push_back({std::move(code), std::move(message)}); return r; }
    static Result unknown(std::string message) { Result r;
        r.outcome = core::SemanticStatus::kUnknown; r.errors.push_back({"E_UNKNOWN", std::move(message)}); return r; }
    static Result cancelled(std::string reason) { Result r; r.outcome = core::SemanticStatus::kCancelled;
        r.was_cancelled = true; r.cancellation_reason = std::move(reason); return r; }
    static Result timed_out() { Result r; r.outcome = core::SemanticStatus::kFailure;
        r.timed_out = true; r.timeout_reason = "execution exceeded timeout"; return r; }
    bool succeeded() const { return outcome == core::SemanticStatus::kSuccess && verification_successful; }
};

using Outcome = core::Outcome;

enum class VerificationStatus {
    kVerified, kNotVerified, kVerificationFailed, kUnknown
};
inline std::string_view to_string(VerificationStatus s) {
    switch (s) {
        case VerificationStatus::kVerified: return "verified";
        case VerificationStatus::kNotVerified: return "not_verified";
        case VerificationStatus::kVerificationFailed: return "verification_failed";
        case VerificationStatus::kUnknown: return "unknown";
    } return "unknown";
}

using Error = core::Error;
using Evidence = core::Evidence;

enum class FailureClassification {
    kExecution, kVerification, kValidation, kAuthorization,
    kResource, kTimeout, kCancelled, kUnknown
};
inline std::string_view to_string(FailureClassification f) {
    switch (f) {
        case FailureClassification::kExecution: return "execution_failure";
        case FailureClassification::kVerification: return "verification_failure";
        case FailureClassification::kValidation: return "validation_failure";
        case FailureClassification::kAuthorization: return "authorization_failure";
        case FailureClassification::kResource: return "resource_failure";
        case FailureClassification::kTimeout: return "timeout_failure";
        case FailureClassification::kCancelled: return "cancelled_failure";
        case FailureClassification::kUnknown: return "unknown_failure";
    } return "unknown";
}

struct RetryAttempt {
    int attempt_number;
    std::string execution_id;
    Result<> result;
    std::chrono::milliseconds delay_before_attempt_ms{0};
};

struct RetryAggregation {
    std::vector<RetryAttempt> attempts;
    std::chrono::system_clock::time_point first_attempt_at;
    std::chrono::system_clock::time_point last_attempt_at;
    core::SemanticStatus final_outcome;
    bool succeeded() const { return final_outcome == core::SemanticStatus::kSuccess; }
    int total_attempts() const { return static_cast<int>(attempts.size()); }
};

enum class EvidenceRetention {
    kNone, kBrief, kStandard, kLong, kPermanent
};
enum class SecretRedactionPolicy {
    kStrict, kRedact, kTrustBoundary
};

template <typename T>
struct ResultWithMetadata : Result<T> {
    runtime::ExecutionIds exec_ids;
    std::optional<std::string> executor_id;
    std::chrono::milliseconds execution_duration_ms{0};
};

inline Error make_error(std::string code, std::string message,
                        std::optional<Error> cause = std::nullopt) {
    if (cause.has_value()) return {std::move(code), std::move(message) + ": caused by " + cause->code};
    return {std::move(code), std::move(message)};
}
inline bool is_verified_success(const Outcome& o) {
    return o.status == core::SemanticStatus::kSuccess && o.verified;
}
inline bool is_failure(const Outcome& o) {
    return o.status == core::SemanticStatus::kFailure || o.status == core::SemanticStatus::kUnknown;
}

}  // namespace rebuntu::runtime::results

namespace rebuntu::core {
inline constexpr SemanticStatus kResultSuccess = SemanticStatus::kSuccess;
inline constexpr SemanticStatus kResultCompleted = SemanticStatus::kCompleted;
}
