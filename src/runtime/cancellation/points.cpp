// rebuntu::runtime::cancellation::points — Implementation (Phase 6.29)
//
// This module provides the implementation of the cancellation points system
// for Rebuntu operations.

#include "runtime/cancellation/points.hpp"
#include <mutex>

namespace rebuntu::runtime::cancellation {

void CancellationRegistry::register_operation(std::string op_id, CancellationSemantics semantics) {
    std::lock_guard<std::mutex> lock(mutex_);
    semantics_[std::move(op_id)] = std::move(semantics);
}

CancellationSemantics CancellationRegistry::get_semantics(const std::string& op_id) const {
    std::lock_guard<std::mutex> lock(mutex_);
    
    auto it = semantics_.find(op_id);
    if (it != semantics_.end()) {
        return it->second;
    }
    
    // Return default semantics for operations without specific registration
    return CancellationSemantics{
        .cancellable = true,
        .cancellable_points = {
            CancellationPoint::kPreconditionCheck,
            CancellationPoint::kExecutionStart,
            CancellationPoint::kExecutionPhase,
            CancellationPoint::kVerificationStart
        },
        .effect_at_point = {
            {CancellationPoint::kPreconditionCheck, CancellationEffect::kNone},
            {CancellationPoint::kPlanGeneration, CancellationEffect::kPartial},
            {CancellationPoint::kExecutionStart, CancellationEffect::kPartial},
            {CancellationPoint::kExecutionPhase, CancellationEffect::kUncertain},
            {CancellationPoint::kVerificationStart, CancellationEffect::kUncertain}
        },
        .default_policy = {
            .fail_fast = false,
            .cleanup_strategy = CancellationPolicy::CleanupStrategy::kManualVerify,
            .requires_verification = true,
            .post_cancel_action = CancellationPolicy::PostCancelAction::kAbandon,
            .verification_timeout_ms = std::chrono::milliseconds(5000)
        },
        .always_requires_verification = true
    };
}

bool CancellationRegistry::is_cancellable(const std::string& op_id) const {
    std::lock_guard<std::mutex> lock(mutex_);
    
    auto it = semantics_.find(op_id);
    if (it != semantics_.end()) {
        return it->second.cancellable;
    }
    
    // Default: all operations are cancellable unless explicitly marked otherwise
    return true;
}

}  // namespace rebuntu::runtime::cancellation