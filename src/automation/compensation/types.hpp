// Rebuntu Automation — Compensation Semantics (Phase 6.26)
//
// Compensation semantics distinguish between:
// - Rollback: Return to exact prior known state
// - Compensation: Attempt to reach a valid/acceptable state (best-effort)
//
// Key principles:
// - Implement compensation only where truthful (based on actual observed state)
// - Best-effort compensation must not be called rollback
// - Verify compensation effects separately from original operation

#pragma once

#include <chrono>
#include <string>
#include <vector>
#include <optional>

namespace rebuntu::automation::compensation {

// ============================================================================
// CompensationStrategy — How to recover when an operation fails
// ============================================================================

enum class CompensationStrategy {
    kNone,              // No compensation possible or desired
    kRollback,          // True rollback: return to exact prior known state
    kCompensate,        // Best-effort compensation: reach a valid state
    kFallback           // Fallback mechanism (different path to same goal)
};

// ============================================================================
// RollbackKind — Distinguishes true rollback from best-effort compensation
// ============================================================================

enum class RollbackKind {
    kExact,             // Exact reversal of operation (deterministic undo)
    kCheckpointRestore, // Restore from known-good checkpoint
    kBestEffort         // Attempt to reach valid state (NOT a true rollback)
};

inline bool is_true_rollback(RollbackKind kind) {
    return kind == RollbackKind::kExact || kind == RollbackKind::kCheckpointRestore;
}

// ============================================================================
// CompensationEffect — What compensation action is required
// ============================================================================

struct CompensationEffect {
    std::string target;                 // What needs correction
    std::vector<std::string> actions;   // Actions to compensate
    std::optional<std::string> expected_state;  // Expected state after compensation
    
    static CompensationEffect for_target(std::string t, 
                                          std::vector<std::string> a) {
        return CompensationEffect{std::move(t), std::move(a), std::nullopt};
    }
    
    static CompensationEffect with_expected(std::string t,
                                             std::vector<std::string> a,
                                             std::string expected) {
        return CompensationEffect{
            std::move(t), 
            std::move(a), 
            std::move(expected)
        };
    }
};

// ============================================================================
// CompensationPlan — Typed plan for compensation actions
// ============================================================================

struct CompensationPlan {
    CompensationStrategy strategy = CompensationStrategy::kNone;
    RollbackKind rollback_kind = RollbackKind::kBestEffort;
    
    // For rollback strategies: what was the prior state?
    std::optional<std::string> prior_state_description;
    
    // Actions to execute for compensation
    std::vector<CompensationEffect> effects;
    
    // Verification requirements
    bool requires_verification = false;
    std::vector<std::string> verification_checks;
    
    static CompensationPlan none() {
        return CompensationPlan{};
    }
    
    static CompensationPlan exact_rollback(std::string prior_state) {
        CompensationPlan p;
        p.strategy = CompensationStrategy::kRollback;
        p.rollback_kind = RollbackKind::kExact;
        p.prior_state_description = std::move(prior_state);
        p.requires_verification = true;
        return p;
    }
    
    static CompensationPlan checkpoint_restore(std::string checkpoint_id) {
        CompensationPlan p;
        p.strategy = CompensationStrategy::kRollback;
        p.rollback_kind = RollbackKind::kCheckpointRestore;
        p.prior_state_description = std::move(checkpoint_id);
        p.requires_verification = true;
        return p;
    }
    
    static CompensationPlan compensate(std::vector<CompensationEffect> effects) {
        CompensationPlan p;
        p.strategy = CompensationStrategy::kCompensate;
        p.rollback_kind = RollbackKind::kBestEffort;  // Not a true rollback
        p.effects = std::move(effects);
        p.requires_verification = true;
        return p;
    }
    
    static CompensationPlan fallback() {
        CompensationPlan p;
        p.strategy = CompensationStrategy::kFallback;
        p.rollback_kind = RollbackKind::kBestEffort;
        return p;
    }
};

// ============================================================================
// CompensationResult — Outcome of compensation action
// ============================================================================

enum class CompensationOutcome {
    kSuccess,           // Compensation achieved target state
    kPartial,           // Some effects achieved, partial success
    kFailed,            // Compensation did not achieve target state
    kUnknown,           // Unknown whether compensation succeeded
    kNotAttempted       // Compensation was not attempted
};

struct CompensationResult {
    CompensationOutcome outcome = CompensationOutcome::kUnknown;
    
    // Timing information
    std::chrono::milliseconds duration_ms{0};
    
    // Verification status (separate from execution success)
    bool verified = false;
    std::vector<std::string> verification_details;
    
    // Evidence of what happened
    std::vector<std::string> evidence;
    
    // Error details if failed
    std::optional<std::string> error_message;
    
    static CompensationResult success(std::chrono::milliseconds duration,
                                       bool was_verified = true) {
        CompensationResult r;
        r.outcome = CompensationOutcome::kSuccess;
        r.duration_ms = duration;
        r.verified = was_verified;
        r.evidence.push_back("Compensation achieved target state");
        return r;
    }
    
    static CompensationResult partial(std::chrono::milliseconds duration,
                                       const std::vector<std::string>& details) {
        CompensationResult r;
        r.outcome = CompensationOutcome::kPartial;
        r.duration_ms = duration;
        r.verified = false;
        r.verification_details = details;
        return r;
    }
    
    static CompensationResult failed(std::chrono::milliseconds duration,
                                      std::string error) {
        CompensationResult r;
        r.outcome = CompensationOutcome::kFailed;
        r.duration_ms = duration;
        r.verified = false;
        r.error_message = std::move(error);
        return r;
    }
    
    static CompensationResult not_attempted() {
        CompensationResult r;
        r.outcome = CompensationOutcome::kNotAttempted;
        r.evidence.push_back("Compensation was not attempted");
        return r;
    }
};

// ============================================================================
// Verification — Separate verification of compensation effects
// ============================================================================

struct CompensationVerification {
    bool successful = false;
    std::chrono::milliseconds verification_duration_ms{0};
    std::vector<std::string> observations;
    std::optional<std::string> verification_error;
    
    static CompensationVerification success(std::chrono::milliseconds duration,
                                            const std::vector<std::string>& obs) {
        return CompensationVerification{
            true, duration, obs, std::nullopt
        };
    }
    
    static CompensationVerification failure(std::chrono::milliseconds duration,
                                             std::string error) {
        return CompensationVerification{
            false, duration, {}, std::move(error)
        };
    }
};

// ============================================================================
// VerificationContext — Context for verifying compensation effects
// ============================================================================

struct VerificationContext {
    // What state should we verify?
    std::string target_state;
    
    // Expected time for effect to manifest (for async operations)
    std::chrono::milliseconds max_wait_ms{1000};
    
    // How many verification attempts
    int max_attempts = 3;
};

}  // namespace rebuntu::automation::compensation