// rebuntu::runtime::cancellation::points — Cancellation Points (Phase 6.29)
//
// This module defines cancellation points and semantics for Rebuntu operations.
//
// Key principles:
//   - Cancellation is cooperative, not forced
//   - Cancellation does NOT imply rollback
//   - After cancellation: re-observe potentially affected state
//   - Cancellation is a signal, not an execution model change

#pragma once

#include <runtime/cancellation/error.hpp>
#include <system/core/contracts.hpp>
#include <mutex>
#include <chrono>
#include <optional>
#include <string>
#include <vector>
#include <map>
#include <functional>

namespace rebuntu::runtime::cancellation {

// ============================================================================
// CancellationPoint — Where cancellation can occur during operation execution
//
// Each point represents a logical boundary where:
//   - Precondition checking may be cancelled (before mutation)
//   - Execution phase may be cancelled (during native action)
//   - Verification phase may be cancelled (after execution, before final result)
// ============================================================================

enum class CancellationPoint {
    kNone,                      // No cancellation point (execution complete)
    kPreconditionCheck,         // Before any state mutation
    kPlanGeneration,            // During operation planning
    kExecutionStart,            // Just before native action begins
    kExecutionPhase,            // During native action execution
    kVerificationStart,         // Just before postcondition verification
    kVerificationPhase,         // During postcondition verification
};

inline std::string_view to_string(CancellationPoint p) {
    switch (p) {
        case CancellationPoint::kNone: return "none";
        case CancellationPoint::kPreconditionCheck: return "precondition_check";
        case CancellationPoint::kPlanGeneration: return "plan_generation";
        case CancellationPoint::kExecutionStart: return "execution_start";
        case CancellationPoint::kExecutionPhase: return "execution_phase";
        case CancellationPoint::kVerificationStart: return "verification_start";
        case CancellationPoint::kVerificationPhase: return "verification_phase";
    }
    return "unknown";
}

// ============================================================================
// CancellationEffect — What happens when cancelled at a given point
//
// Defines the observable effect of cancellation:
//   - kNone: No effect (operation not yet started)
//   - kPartial: Some work may have completed (idempotent or roll forward)
//   - kUncertain: State may be inconsistent, re-observation required
// ============================================================================

enum class CancellationEffect {
    kNone,          // Before any meaningful work (safe to retry)
    kPartial,       // Some progress made, idempotent operations are safe to retry
    kUncertain,     // State may be inconsistent, must re-observe before retry
};

inline std::string_view to_string(CancellationEffect e) {
    switch (e) {
        case CancellationEffect::kNone: return "none";
        case CancellationEffect::kPartial: return "partial";
        case CancellationEffect::kUncertain: return "uncertain";
    }
    return "unknown";
}

// ============================================================================
// VerificationStatus — Postcondition verification result
//
// Distinct from SemanticStatus:
//   - SemanticStatus = what semantic outcome occurred
//   - VerificationStatus = was the postcondition check successful?
// ============================================================================

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

// ============================================================================
// CancellationContext — Context at the point of cancellation
//
// Captures the state at cancellation for:
//   - Logging/debugging
//   - Retry decisions
//   - State verification requirements
// ============================================================================

struct CancellationContext {
    CancellationPoint point;                // Where in execution was cancelled?
    std::chrono::system_clock::time_point cancelled_at;
    
    // Execution metadata
    std::optional<std::string> task_id;
    std::optional<std::string> job_id;
    std::optional<std::string> execution_id;
    
    // State snapshot (what we know before cancellation)
    std::vector<core::Evidence> pre_observation;
    
    // Whether state may have been partially modified
    bool partial_state_change = false;
    
    // Required verification action after cancellation
    bool requires_reobservation = true;  // Always true for mutating operations
};

// ============================================================================
// CancellationPolicy — Policy for handling cancellation during operations
//
// Defines behavior when cancellation is requested:
//   - Should execution stop immediately?
//   - What cleanup (if any) should occur?
//   - How should verification be handled?
// ============================================================================

struct CancellationPolicy {
    // Behavior when cancellation is detected
    bool fail_fast = false;           // Stop immediately without cleanup?
    
    // Cleanup strategy
    enum class CleanupStrategy {
        kNone,            // No cleanup (leave state as-is)
        kIdempotentRetry, // Safe to retry idempotent operations
        kManualVerify,    // Must re-observe before determining next step
    } cleanup_strategy = CleanupStrategy::kManualVerify;
    
    // Verification requirements after cancellation
    bool requires_verification = true;  // Must verify postconditions?
    
    // What to do if verification fails after cancellation
    enum class PostCancelAction {
        kRetry,           // Try the operation again
        kRollForward,     // Attempt to complete the original intent
        kAbandon,         // Mark as failed, no further action
    } post_cancel_action = PostCancelAction::kAbandon;
    
    // Timeout for verification after cancellation
    std::chrono::milliseconds verification_timeout_ms{5000};
};

// ============================================================================
// CancellationResult — Result of an operation that was cancelled
//
// Combines the execution outcome with cancellation-specific metadata.
// ============================================================================

template <typename T>
struct CancellationResult {
    core::SemanticStatus status = core::SemanticStatus::kCancelled;
    
    // Original value if any (may be partial)
    std::optional<T> value;
    
    // Cancellation details
    CancellationPoint point_of_cancel;
    std::string cancellation_reason;
    CancellationContext context;
    CancellationPolicy policy;
    
    // Post-cancel state evidence
    std::vector<core::Evidence> post_cancel_evidence;
    
    // Verification status after cancellation
    VerificationStatus verification_status = VerificationStatus::kNotVerified;
    
    static CancellationResult cancelled_at(
        CancellationPoint point,
        std::string reason,
        const CancellationContext& ctx = {},
        const CancellationPolicy& pol = {}
    ) {
        CancellationResult r;
        r.status = core::SemanticStatus::kCancelled;
        r.point_of_cancel = point;
        r.cancellation_reason = std::move(reason);
        r.context = ctx;
        r.policy = pol;
        return r;
    }
    
    static CancellationResult completed_with_partial_state(
        T value,
        CancellationPoint point,
        std::string reason
    ) {
        CancellationResult r;
        r.status = core::SemanticStatus::kCompleted;
        r.value = std::move(value);
        r.point_of_cancel = point;
        r.cancellation_reason = std::move(reason);
        return r;
    }
};

// Specialization for void operations
template <>
struct CancellationResult<void> {
    core::SemanticStatus status = core::SemanticStatus::kCancelled;
    
    // Cancellation details
    CancellationPoint point_of_cancel;
    std::string cancellation_reason;
    CancellationContext context;
    CancellationPolicy policy;
    
    // Post-cancel state evidence
    std::vector<core::Evidence> post_cancel_evidence;
    
    // Verification status after cancellation
    VerificationStatus verification_status = VerificationStatus::kNotVerified;
    
    static CancellationResult<void> cancelled_at(
        CancellationPoint point,
        std::string reason,
        const CancellationContext& ctx = {},
        const CancellationPolicy& pol = {}
    ) {
        CancellationResult<void> r;
        r.point_of_cancel = point;
        r.cancellation_reason = std::move(reason);
        r.context = ctx;
        r.policy = pol;
        return r;
    }
    
    static CancellationResult<void> completed_with_partial_state(
        CancellationPoint point,
        std::string reason
    ) {
        CancellationResult<void> r;
        r.status = core::SemanticStatus::kCompleted;
        r.point_of_cancel = point;
        r.cancellation_reason = std::move(reason);
        return r;
    }
};

// ============================================================================
// CancellationSemantics — Documentation of cancellation behavior per operation
//
// Each operation type declares its cancellation semantics:
//   - Which points are cancellable?
//   - What's the effect at each point?
//   - What verification is required after cancellation?
// ============================================================================

struct CancellationSemantics {
    // Can this operation be cancelled?
    bool cancellable = true;
    
    // At which points can cancellation occur?
    std::vector<CancellationPoint> cancellable_points;
    
    // Effect at each cancellation point
    std::map<CancellationPoint, CancellationEffect> effect_at_point;
    
    // Default policy for this operation type
    CancellationPolicy default_policy;
    
    // Verification required after any cancellation
    bool always_requires_verification = true;
};

// ============================================================================
// OperationCancellation — Interface for operations to support cancellation
//
// This is the contract that all mutating Rebuntu Operations should implement.
// ============================================================================

class OperationCancellation {
public:
    virtual ~OperationCancellation() = default;
    
    // Check if this operation has been cancelled
    virtual bool is_cancelled() const = 0;
    
    // Get the cancellation point (if cancelled)
    virtual std::optional<CancellationPoint> cancel_point() const = 0;
    
    // Get the reason for cancellation
    virtual std::optional<std::string> cancel_reason() const = 0;
    
    // Register a callback to be invoked on cancellation
    using CancellationCallback = std::function<void(const CancellationContext&)>;
    virtual void on_cancel(CancellationCallback cb) = 0;
};

// ============================================================================
// CancellationRegistry — Registry of operation cancellation handlers
//
// Tracks which operations support cancellation and their semantics.
// ============================================================================

class CancellationRegistry {
public:
    // Register cancellation semantics for an operation type
    void register_operation(
        std::string op_id,
        CancellationSemantics semantics
    );
    
    // Get cancellation semantics for an operation (or default)
    CancellationSemantics get_semantics(const std::string& op_id) const;
    
    // Check if an operation supports cancellation
    bool is_cancellable(const std::string& op_id) const;

private:
    mutable std::mutex mutex_;
    std::map<std::string, CancellationSemantics> semantics_;
};

}  // namespace rebuntu::runtime::cancellation

// ============================================================================
// Helper utilities
// ============================================================================

namespace rebuntu::runtime::cancellation {

// Check if a cancellation point is after a given point (for ordering)
inline bool is_after(CancellationPoint earlier, CancellationPoint later) {
    return static_cast<int>(earlier) < static_cast<int>(later);
}

// Get the effect at the earliest cancelled point
inline CancellationEffect worst_effect_at(
    const std::map<CancellationPoint, CancellationEffect>& effects,
    CancellationPoint point
) {
    auto it = effects.find(point);
    if (it == effects.end()) {
        return CancellationEffect::kNone;
    }
    return it->second;
}

}  // namespace rebuntu::runtime::cancellation