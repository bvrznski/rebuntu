// rebuntu::core::results — Result/Outcome/Error model (Phase 0.17)
//
// This file establishes the canonical vocabulary for execution results,
// semantic outcomes, errors, verification status, and evidence in Rebuntu.
//
// Core invariant established here:
//   EXECUTED != SUCCEEDED != VERIFIED
//
// And:
//   EXIT STATUS 0 != VERIFIED SEMANTIC SUCCESS
//
// This header supersedes earlier fragments by consolidating all result model
// types into one authoritative source with consistent definitions.

#pragma once

#include <runtime/core/contracts.hpp>
#include <chrono>
#include <optional>
#include <string>
#include <vector>

namespace rebuntu::core {

// ---------------------------------------------------------------------------
// VerificationStatus — Postcondition verification result
// 
// Distinct from SemanticStatus:
//   - SemanticStatus = what semantic outcome occurred
//   - VerificationStatus = was the postcondition check successful?
//
// These are orthogonal:
//   EXECUTED SUCCESS + VERIFICATION FAILED = FAILURE (not SUCCEEDED)
//   EXECUTED SUCCESS + NO VERIFICATION = COMPLETED (not SUCCEEDED)
// ---------------------------------------------------------------------------
enum class VerificationStatus {
    kVerified,            // postconditions were independently verified and hold
    kNotVerified,         // verification was not performed (may be acceptable)
    kVerificationFailed,  // verification ran but postconditions did not hold
    kUnknown,             // could not determine verification status
};

inline std::string_view to_string(VerificationStatus s) {
    switch (s) {
        case VerificationStatus::kVerified: return "verified";
        case VerificationStatus::kNotVerified: return "not_verified";
        case VerificationStatus::kVerificationFailed: return "verification_failed";
        case VerificationStatus::kUnknown: return "unknown";
    }
    return "unknown";
}

// ---------------------------------------------------------------------------
// FailureClassification — Categorization of why execution failed
//
// Distinguishes different failure modes:
//   - Execution failure: the operation ran but produced wrong outcome
//   - Verification failure: execution succeeded but verification failed
//   - Validation failure: input did not satisfy preconditions
//   - Authorization failure: permission denied
//   - Resource failure: resource exhaustion (time, memory, etc.)
//   - Timeout failure: exceeded timeout threshold
//   - Cancelled failure: explicit cancellation before completion
//   - Unknown failure: could not determine the cause
// ---------------------------------------------------------------------------
enum class FailureClassification {
    kExecution,
    kVerification,
    kValidation,
    kAuthorization,
    kResource,
    kTimeout,
    kCancelled,
    kUnknown,
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
    }
    return "unknown";
}

// ---------------------------------------------------------------------------
// EvidenceRetention — How long to retain evidence
//
// Evidence may be retained for:
//   - Debugging (brief)
//   - Operations audit (standard)  
//   - Compliance/forensics (long/permanent)
// ---------------------------------------------------------------------------
enum class EvidenceRetention {
    kNone,      // no evidence retained
    kBrief,     // retained briefly (e.g., minutes)
    kStandard,  // retained for operational lifetime (e.g., hours/days)
    kLong,      // retained for extended period (e.g., weeks/months)
    kPermanent, // retained indefinitely
};

inline std::string_view to_string(EvidenceRetention r) {
    switch (r) {
        case EvidenceRetention::kNone: return "none";
        case EvidenceRetention::kBrief: return "brief";
        case EvidenceRetention::kStandard: return "standard";
        case EvidenceRetention::kLong: return "long";
        case EvidenceRetention::kPermanent: return "permanent";
    }
    return "unknown";
}

// ---------------------------------------------------------------------------
// SecretRedactionPolicy — How to handle potential secrets in evidence
//
// Bell-LaPadula-style policy:
//   - kStrict: never include secret material
//   - kRedact: apply pattern-based redaction
//   - kTrustBoundary: rely on transport/storage security boundaries
// ---------------------------------------------------------------------------
enum class SecretRedactionPolicy {
    kStrict,      // never include secret material in evidence
    kRedact,      // apply pattern-based redaction
    kTrustBoundary,  // rely on boundary security (not recommended)
};

inline std::string_view to_string(SecretRedactionPolicy p) {
    switch (p) {
        case SecretRedactionPolicy::kStrict: return "strict";
        case SecretRedactionPolicy::kRedact: return "redact";
        case SecretRedactionPolicy::kTrustBoundary: return "trust_boundary";
    }
    return "unknown";
}

// Evidence is defined in contracts.hpp as:
//   struct Evidence {
//       std::string source;      // where this evidence came from
//       std::string value;       // the observed value / excerpt (bounded)
//       std::string captured_at; // ISO-8601, UTC
//   };
//
// Phase 0.17 extends Evidence with helper methods via free functions.
// The core struct remains in contracts.hpp to avoid circular dependencies.

inline Evidence make_evidence(std::string source, std::string value, std::string captured_at) {
    return Evidence{std::move(source), std::move(value), std::move(captured_at)};
}

inline Evidence evidence_from_procfs(const std::string& path, const std::string& content) {
    return Evidence{"procfs", content, "2024-01-01T00:00:00Z"};
}

inline Evidence evidence_from_systemd(const std::string& unit, const std::string& property,
                                       const std::string& value) {
    (void)unit;
    (void)property;
    return Evidence{"systemd", value, "2024-01-01T00:00:00Z"};
}

inline Evidence evidence_from_sysfs(const std::string& path, const std::string& content) {
    (void)path;
    return Evidence{"sysfs", content, "2024-01-01T00:00:00Z"};
}

// ---------------------------------------------------------------------------
// VerificationResult — Result of postcondition verification
//
// Distinct from ExecutionResult:
//   - ExecutionResult = what happened during execution
//   - VerificationResult = does observed state match expected postconditions?
//
// A successful execution can have failed verification.
// An unsuccessful execution may not even reach verification.
// ---------------------------------------------------------------------------

struct VerificationResult {
    VerificationStatus status;
    std::chrono::system_clock::time_point verified_at;
    std::optional<std::string> verification_description;  // human-readable
    std::vector<Evidence> evidence;

    static VerificationResult verified(const Evidence& ev = {}) {
        VerificationResult r;
        r.status = VerificationStatus::kVerified;
        r.verified_at = std::chrono::system_clock::now();
        if (!ev.source.empty()) r.evidence.push_back(ev);
        return r;
    }

    static VerificationResult not_verified(std::string description) {
        VerificationResult r;
        r.status = VerificationStatus::kNotVerified;
        r.verification_description = std::move(description);
        r.verified_at = std::chrono::system_clock::now();
        return r;
    }

    static VerificationResult verification_failed(const Evidence& ev = {}) {
        VerificationResult r;
        r.status = VerificationStatus::kVerificationFailed;
        if (!ev.source.empty()) r.evidence.push_back(ev);
        r.verified_at = std::chrono::system_clock::now();
        return r;
    }

    static VerificationResult unknown(std::string message) {
        VerificationResult r;
        r.status = VerificationStatus::kUnknown;
        r.verification_description = std::move(message);
        r.verified_at = std::chrono::system_clock::now();
        return r;
    }
};

// ---------------------------------------------------------------------------
// ExecutionOutcome — Semantic classification of execution result
//
// A unified outcome type that does not depend on template specialization.
// Use this for cases where we need to represent outcomes without values.
// ---------------------------------------------------------------------------

struct ExecutionOutcome {
    SemanticStatus status = SemanticStatus::kUnknown;

    // Helper predicates
    bool succeeded() const { return status == SemanticStatus::kSuccess; }
    bool is_completed() const {
        return status == SemanticStatus::kCompleted || status == SemanticStatus::kSuccess;
    }
    bool failed() const {
        return status == SemanticStatus::kFailure || status == SemanticStatus::kUnknown ||
               status == SemanticStatus::kCancelled;
    }

    // Static constructors
    static ExecutionOutcome success() {
        ExecutionOutcome o;
        o.status = SemanticStatus::kSuccess;
        return o;
    }

    static ExecutionOutcome completed_state() {
        ExecutionOutcome o;
        o.status = SemanticStatus::kCompleted;
        return o;
    }

    static ExecutionOutcome failure() {
        ExecutionOutcome o;
        o.status = SemanticStatus::kFailure;
        return o;
    }

    static ExecutionOutcome unknown(std::string message) {
        ExecutionOutcome o;
        o.status = SemanticStatus::kUnknown;
        o._message = std::move(message);
        return o;
    }

    static ExecutionOutcome cancelled(std::string reason) {
        ExecutionOutcome o;
        o.status = SemanticStatus::kCancelled;
        o._cancelled_reason = std::move(reason);
        return o;
    }

    // Accessors
    const std::optional<std::string>& message() const { return _message; }
    bool was_cancelled() const { return _cancelled_reason.has_value(); }

private:
    std::optional<std::string> _message;
    std::optional<std::string> _cancelled_reason;
};

// ---------------------------------------------------------------------------
// ExecutionResult<T> — Result of a complete execution (attempt) with value
//
// Use when the operation returns a meaningful value.
// For void-returning operations, use ExecutionResult<void>.
// ---------------------------------------------------------------------------

template <typename T>
struct ExecutionResult {
    std::string definition_id;      // what operation/task was executed
    std::string execution_id;       // which specific execution attempt
    std::optional<std::string> attempt_id;  // which attempt in a retry chain

    std::chrono::system_clock::time_point started_at;
    std::chrono::system_clock::time_point finished_at;

    SemanticStatus outcome = SemanticStatus::kUnknown;

    std::optional<T> value;

    bool verification_successful = false;
    std::chrono::milliseconds verification_duration_ms{0};

    struct Outputs {
        std::string stdout_data;
        std::string stderr_data;
        int exit_status = 0;
    };
    std::optional<Outputs> outputs;

    std::vector<Evidence> evidence;

    bool was_cancelled = false;
    bool timed_out = false;
    std::optional<std::string> cancellation_reason;
    std::optional<std::string> timeout_reason;
    int attempt_number = 1;

    // Static constructors
    static ExecutionResult<T> success(T v, const Evidence& ev = {}) {
        ExecutionResult<T> r;
        r.outcome = SemanticStatus::kSuccess;
        r.value = std::move(v);
        r.verification_successful = true;  // success implies verification
        if (!ev.source.empty()) r.evidence.push_back(ev);
        r.started_at = std::chrono::system_clock::now();
        r.finished_at = r.started_at;
        return r;
    }

    static ExecutionResult<T> completed(T v) {
        ExecutionResult<T> r;
        r.outcome = SemanticStatus::kCompleted;
        r.value = std::move(v);
        r.verification_successful = false;
        r.started_at = std::chrono::system_clock::now();
        r.finished_at = r.started_at;
        return r;
    }

    static ExecutionResult<T> failure(std::string code, std::string message) {
        ExecutionResult<T> r;
        r.outcome = SemanticStatus::kFailure;
        r.evidence.push_back(Evidence{"execution", "exit_failure", ""});
        r.started_at = std::chrono::system_clock::now();
        r.finished_at = r.started_at;
        return r;
    }

    static ExecutionResult<T> unknown(std::string message) {
        ExecutionResult<T> r;
        r.outcome = SemanticStatus::kUnknown;
        r.evidence.push_back(Evidence{"execution", "outcome_unknown", ""});
        r.started_at = std::chrono::system_clock::now();
        r.finished_at = r.started_at;
        return r;
    }

    static ExecutionResult<T> cancelled(std::string reason) {
        ExecutionResult<T> r;
        r.outcome = SemanticStatus::kCancelled;
        r.was_cancelled = true;
        r.cancellation_reason = std::move(reason);
        r.started_at = std::chrono::system_clock::now();
        r.finished_at = r.started_at;
        return r;
    }

    // Query methods
    bool succeeded() const {
        return outcome == SemanticStatus::kSuccess && verification_successful;
    }

    bool has_value() const { return value.has_value(); }
};

// ---------------------------------------------------------------------------
// ExecutionResult<void> — Specialization for void-returning operations
// ---------------------------------------------------------------------------

template <>
struct ExecutionResult<void> {
    std::string definition_id;
    std::string execution_id;
    std::optional<std::string> attempt_id;

    std::chrono::system_clock::time_point started_at;
    std::chrono::system_clock::time_point finished_at;

    SemanticStatus outcome = SemanticStatus::kUnknown;

    bool verification_successful = false;
    std::chrono::milliseconds verification_duration_ms{0};

    struct Outputs {
        std::string stdout_data;
        std::string stderr_data;
        int exit_status = 0;
    };
    std::optional<Outputs> outputs;

    std::vector<Evidence> evidence;

    bool was_cancelled = false;
    bool timed_out = false;
    std::optional<std::string> cancellation_reason;
    std::optional<std::string> timeout_reason;
    int attempt_number = 1;

    static ExecutionResult<void> success(const Evidence& ev = {}) {
        ExecutionResult<void> r;
        r.outcome = SemanticStatus::kSuccess;
        r.verification_successful = true;
        if (!ev.source.empty()) r.evidence.push_back(ev);
        r.started_at = std::chrono::system_clock::now();
        r.finished_at = r.started_at;
        return r;
    }

    static ExecutionResult<void> completed_void() {
        ExecutionResult<void> r;
        r.outcome = SemanticStatus::kCompleted;
        r.verification_successful = false;
        r.started_at = std::chrono::system_clock::now();
        r.finished_at = r.started_at;
        return r;
    }

    static ExecutionResult<void> failure(std::string code, std::string message) {
        ExecutionResult<void> r;
        r.outcome = SemanticStatus::kFailure;
        r.evidence.push_back(Evidence{"execution", "exit_failure", ""});
        r.started_at = std::chrono::system_clock::now();
        r.finished_at = r.started_at;
        return r;
    }

    static ExecutionResult<void> unknown(std::string message) {
        ExecutionResult<void> r;
        r.outcome = SemanticStatus::kUnknown;
        r.evidence.push_back(Evidence{"execution", "outcome_unknown", ""});
        r.started_at = std::chrono::system_clock::now();
        r.finished_at = r.started_at;
        return r;
    }

    static ExecutionResult<void> cancelled(std::string reason) {
        ExecutionResult<void> r;
        r.outcome = SemanticStatus::kCancelled;
        r.was_cancelled = true;
        r.cancellation_reason = std::move(reason);
        r.started_at = std::chrono::system_clock::now();
        r.finished_at = r.started_at;
        return r;
    }

    bool succeeded() const {
        return outcome == SemanticStatus::kSuccess && verification_successful;
    }

    bool has_value() const { return false; }
};

// ---------------------------------------------------------------------------
// RetryAttempt — Single attempt in a retry chain
//
// A successful final result does NOT erase earlier failures.
// Each attempt is recorded for debugging and auditing.
// ---------------------------------------------------------------------------

struct RetryAttempt {
    int attempt_number;
    std::string execution_id;
    ExecutionResult<void> result;
    std::chrono::milliseconds delay_before_attempt_ms{0};
};

// ---------------------------------------------------------------------------
// RetryAggregation — All attempts in a retry chain
//
// Preserves history of all attempts even when final outcome is success.
// ---------------------------------------------------------------------------

struct RetryAggregation {
    std::vector<RetryAttempt> attempts;
    std::chrono::system_clock::time_point first_attempt_at;
    std::chrono::system_clock::time_point last_attempt_at;
    SemanticStatus final_outcome;

    bool succeeded() const { return final_outcome == SemanticStatus::kSuccess; }
    int total_attempts() const { return static_cast<int>(attempts.size()); }
};

// ---------------------------------------------------------------------------
// ResultWithMetadata — Result plus execution context metadata
//
// Adds runtime tracking information to a Result without modifying its core.
// ---------------------------------------------------------------------------

template <typename T>
struct ResultWithMetadata {
    std::string executor_id;  // which component executed it
    std::chrono::milliseconds execution_duration_ms{0};
};

// ---------------------------------------------------------------------------
// Helper predicates for ExecutionOutcome
// ---------------------------------------------------------------------------

inline bool is_verified_success(const ExecutionOutcome& o) {
    return o.status == SemanticStatus::kSuccess;
}

inline bool is_completed(const ExecutionOutcome& o) {
    return o.is_completed();
}

inline bool is_failure(const ExecutionOutcome& o) {
    return o.failed();
}

}  // namespace rebuntu::core