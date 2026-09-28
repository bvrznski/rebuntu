// rebuntu::runtime::RetryMechanics — Retry Mechanics Integration (Phase 6.24)
//
// This module integrates idempotency classification with retry mechanics
// and provides state re-observation before retries where partial effects are possible.
//
// Key principles:
//   - Retry only operations whose idempotency semantics permit it
//   - Re-observe state before retries to detect partial effects
//   - Never retry non-idempotent operations without explicit authorization

#pragma once

#include <runtime/contracts.hpp>
#include <system/core/contracts.hpp>
#include <system/idempotency/classifier.hpp>
#include <vector>
#include <optional>
#include <chrono>
#include <string>

namespace rebuntu::runtime {

// ============================================================================
// RetryObservation — State observation result for retry decision
// ============================================================================

struct RetryObservation {
    bool state_changed = false;           // Did state change since last attempt?
    std::vector<core::Evidence> evidence; // Evidence supporting the observation
    
    static RetryObservation no_change() {
        RetryObservation r;
        r.state_changed = false;
        return r;
    }
    
    static RetryObservation changed(std::vector<core::Evidence> e = {}) {
        RetryObservation r;
        r.state_changed = true;
        r.evidence = std::move(e);
        return r;
    }
};

// ============================================================================
// RetryDecision — Decision about whether to retry
// ============================================================================

enum class RetryDecision {
    RETRY,           // Safe to retry
    SKIP_RETRY,      // Don't retry this operation
    REVERSE,         // Reverse partial effects before retrying
    ABORT,           // Abort the entire operation
};

inline const char* to_string(RetryDecision d) {
    switch (d) {
        case RetryDecision::RETRY: return "retry";
        case RetryDecision::SKIP_RETRY: return "skip_retry";
        case RetryDecision::REVERSE: return "reverse_before_retry";
        case RetryDecision::ABORT: return "abort";
    }
    return "unknown";
}

// ============================================================================
// RetryMechanics — Integrated retry logic with idempotency and state observation
// ============================================================================

class RetryMechanics {
public:
    // Execute attempt callback signature
    using ExecuteAttemptFn = std::function<
        core::Outcome(int attempt_number, const runtime::RetryPolicy&)>;
    
    // State observation callback signature (for re-observation before retry)
    using ObserveStateFn = std::function<RetryObservation()>;
    
    RetryMechanics(
        int max_attempts,
        std::chrono::milliseconds initial_delay,
        bool exponential_backoff = false);
    
    // Attempt execution with integrated retry logic
    core::Outcome execute_with_retry(
        ExecuteAttemptFn exec_fn,
        ObserveStateFn observe_fn,
        const runtime::RetryPolicy& policy,
        const core::OperationDefinition* op_def = nullptr);
    
    // Check if we should retry based on idempotency and state observation
    RetryDecision decide(const core::Outcome& outcome, int attempt_number,
                        const core::OperationDefinition* op_def = nullptr) const;
    
    // Get delay before next retry (0 if no more retries)
    std::chrono::milliseconds next_retry_delay(int attempt_number) const;

private:
    int max_attempts_;
    std::chrono::milliseconds initial_delay_;
    bool exponential_backoff_;
};

// ============================================================================
// RetryPolicyBuilder — Build retry policies from idempotency classification
// ============================================================================

class RetryPolicyBuilder {
public:
    // Create a retry policy from an operation definition using idempotency classification
    static runtime::RetryPolicy from_operation(
        const core::OperationDefinition& op,
        int base_max_attempts = 3);
    
    // Create a retry policy from idempotency classification
    static runtime::RetryPolicy from_idempotency(
        core::Idempotency ip,
        int max_attempts = 0);
    
    // Get default max retries based on idempotency
    static int max_retries_for_idempotency(core::Idempotency ip);

private:
    RetryPolicyBuilder() = delete;
};

}  // namespace rebuntu::runtime

// ============================================================================
// Inline implementations
// ============================================================================

namespace rebuntu::runtime {

inline RetryMechanics::RetryMechanics(
    int max_attempts,
    std::chrono::milliseconds initial_delay,
    bool exponential_backoff)
    : max_attempts_(max_attempts),
      initial_delay_(initial_delay),
      exponential_backoff_(exponential_backoff) {
}

inline RetryDecision RetryMechanics::decide(const core::Outcome& outcome, int attempt_number,
                                            const core::OperationDefinition* op_def) const {
    // Cannot retry beyond max attempts
    if (attempt_number >= max_attempts_) {
        return RetryDecision::ABORT;
    }
    
    // Success doesn't need retry
    if (outcome.status == core::SemanticStatus::kSuccess) {
        return RetryDecision::SKIP_RETRY;
    }
    
    // Cancellation shouldn't be retried
    if (outcome.status == core::SemanticStatus::kCancelled) {
        return RetryDecision::ABORT;
    }
    
    // For unknown/failure outcomes, check idempotency if available
    if (max_attempts_ <= 1) {
        // Single attempt only - no retry
        return RetryDecision::SKIP_RETRY;
    }
    
    // Check idempotency classification to determine if retry is permitted
    if (op_def != nullptr && op_def->idempotency != core::Idempotency::UNKNOWN) {
        switch (op_def->idempotency) {
            case core::Idempotency::NON_IDEMPOTENT:
                // Non-idempotent operations should not be retried automatically
                return RetryDecision::ABORT;
                
            case core::Idempotency::IDEMPOTENT:
            case core::Idempotency::CONDITIONALLY_IDEMPOTENT:
                // These may be safe to retry
                break;
                
            default:
                break;
        }
    }
    
    // Default: allow retry with re-observation (state will be checked by caller)
    return RetryDecision::RETRY;
}

inline std::chrono::milliseconds RetryMechanics::next_retry_delay(int attempt_number) const {
    if (attempt_number >= max_attempts_) {
        return std::chrono::milliseconds(0);
    }
    
    int retry_attempt = attempt_number + 1;  // 1-indexed for delay calculation
    
    if (!exponential_backoff_ || retry_attempt <= 1) {
        return initial_delay_;
    }
    
    // Exponential backoff: delay = initial * (backoff_multiplier ^ (attempt - 1))
    int64_t multiplier = static_cast<int64_t>(std::pow(2.0, retry_attempt - 1));
    auto delay = initial_delay_ * multiplier;
    
    return delay;
}

inline runtime::RetryPolicy RetryPolicyBuilder::from_operation(
    const core::OperationDefinition& op,
    int base_max_attempts) {
    
    runtime::RetryPolicy policy;
    
    // Determine max attempts based on idempotency classification
    if (op.idempotency != core::Idempotency::UNKNOWN) {
        switch (op.idempotency) {
            case core::Idempotency::IDEMPOTENT:
                policy.max_attempts = std::max(base_max_attempts, 3);
                break;
            case core::Idempotency::CONDITIONALLY_IDEMPOTENT:
                policy.max_attempts = std::max(base_max_attempts / 2, 1);
                break;
            case core::Idempotency::NON_IDEMPOTENT:
                policy.max_attempts = 1;  // Don't retry by default
                break;
            default:
                policy.max_attempts = base_max_attempts;
                break;
        }
    } else {
        policy.max_attempts = base_max_attempts;
    }
    
    // Set default delays (will be adjusted based on operation characteristics)
    policy.initial_delay = std::chrono::milliseconds(100);
    policy.exponential_backoff = true;
    policy.backoff_multiplier = 2.0;
    
    return policy;
}

inline runtime::RetryPolicy RetryPolicyBuilder::from_idempotency(
    core::Idempotency ip,
    int max_attempts) {
    
    runtime::RetryPolicy policy;
    
    switch (ip) {
        case core::Idempotency::IDEMPOTENT:
            policy.max_attempts = std::max(max_attempts, 3);
            break;
        case core::Idempotency::CONDITIONALLY_IDEMPOTENT:
            policy.max_attempts = std::max(max_attempts / 2, 1);
            break;
        case core::Idempotency::NON_IDEMPOTENT:
            policy.max_attempts = 1;  // Don't retry by default
            break;
        default:
            policy.max_attempts = max_attempts > 0 ? max_attempts : 3;
            break;
    }
    
    policy.initial_delay = std::chrono::milliseconds(100);
    policy.exponential_backoff = true;
    policy.backoff_multiplier = 2.0;
    
    return policy;
}

inline int RetryPolicyBuilder::max_retries_for_idempotency(core::Idempotency ip) {
    switch (ip) {
        case core::Idempotency::IDEMPOTENT:
            return 3;  // Safe to retry multiple times
        case core::Idempotency::CONDITIONALLY_IDEMPOTENT:
            return 2;  // Limited retries due to potential side effects
        case core::Idempotency::NON_IDEMPOTENT:
            return 0;  // Don't retry by default
        default:
            return 1;  // Conservative approach for unknown
    }
}

}  // namespace rebuntu::runtime