// rebuntu::runtime::RetryMechanics — Retry Mechanics Implementation (Phase 6.24)
//
// This module implements retry mechanics with state re-observation.

#include "retry_mechanics.hpp"

namespace rebuntu::runtime {

// ============================================================================
// RetryMechanics - Non-inline implementation
// ============================================================================

core::Outcome RetryMechanics::execute_with_retry(
    ExecuteAttemptFn exec_fn,
    ObserveStateFn observe_fn,
    const runtime::RetryPolicy& policy,
    const core::OperationDefinition* op_def) {
    
    int attempt_number = 0;
    core::Outcome last_outcome;
    
    while (attempt_number < max_attempts_) {
        // Re-observe state before each retry (for partial effect detection)
        if (attempt_number > 0 && observe_fn) {
            RetryObservation obs = observe_fn();
            
            // If state has changed significantly, we might need to adjust our approach
            // For now, we just log this observation for the caller to handle
            
            (void)obs;  // Suppress unused variable warning
        }
        
        // Execute the attempt
        last_outcome = exec_fn(attempt_number + 1, policy);
        
        // Check if execution was successful
        if (last_outcome.status == core::SemanticStatus::kSuccess) {
            break;
        }
        
        // If we've reached max attempts, stop trying
        if (attempt_number >= max_attempts_ - 1) {
            break;
        }
        
        // Determine if we should retry based on idempotency
        RetryDecision decision = decide(last_outcome, attempt_number);
        
        switch (decision) {
            case RetryDecision::ABORT:
                return last_outcome;  // Return the last outcome as failure
                
            case RetryDecision::REVERSE:
                // TODO: Implement reverse operation before retrying
                // For now, skip to next iteration
                break;
                
            case RetryDecision::SKIP_RETRY:
                // Don't retry this operation based on current assessment
                return last_outcome;
                
            case RetryDecision::RETRY:
                // Continue to next attempt with delay
                break;
        }
        
        // Apply backoff delay before retry
        auto delay = next_retry_delay(attempt_number);
        if (delay > std::chrono::milliseconds(0)) {
            // TODO: Implement actual delay (sleep/yield)
            (void)delay;  // Suppress unused variable warning
        }
        
        attempt_number++;
    }
    
    return last_outcome;
}

}  // namespace rebuntu::runtime