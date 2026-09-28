// Rebuntu Idempotency Classification System (Phase 6.23)
//
// This module provides automatic idempotency classification for operations.

#include "classifier.hpp"

namespace rebuntu::idempotency {

// ============================================================================
// IdempotencyClassifier Implementation
// ============================================================================

ClassificationResult IdempotencyClassifier::classify(const core::OperationDefinition& op) const {
    // Start with the operation's declared classification if available
    ClassificationResult result;
    
    // Use operation's explicit idempotency if set (not UNKNOWN)
    if (op.idempotency != core::Idempotency::UNKNOWN) {
        result.idempotency = op.idempotency;
    } else {
        // Auto-classify based on characteristics
        result.idempotency = classify_idempotency(op);
    }
    
    // Use operation's explicit reversibility if set (not UNKNOWN)
    if (op.reversibility != core::Reversibility::UNKNOWN) {
        result.reversibility = op.reversibility;
    } else {
        // Auto-classify reversibility
        result.reversibility = classify_reversibility(op);
    }
    
    // Add evidence
    result.evidence = analyze_evidence(op);
    
    return result;
}

core::Idempotency IdempotencyClassifier::classify_idempotency(const core::OperationDefinition& op) const {
    // Observation-only operations are always idempotent (read-only)
    if (op.side_effect == core::SideEffectKind::NONE ||
        op.side_effect == core::SideEffectKind::OBSERVATION) {
        return core::Idempotency::IDEMPOTENT;
    }
    
    // Destructive operations are typically non-idempotent
    if (op.side_effect == core::SideEffectKind::DESTRUCTIVE) {
        return core::Idempotency::NON_IDEMPOTENT;
    }
    
    // Privileged operations need careful analysis
    if (op.side_effect == core::SideEffectKind::PRIVILEGED) {
        // Check if it's a mutation that can be retried safely
        for (const auto& effect : op.expected_effects) {
            // Operations that modify existing resources are often conditionally idempotent
            if (effect.find("update") != std::string::npos ||
                effect.find("modify") != std::string::npos) {
                return core::Idempotency::CONDITIONALLY_IDEMPOTENT;
            }
        }
    }
    
    // Mutating operations without specific patterns are conditionally idempotent
    if (op.side_effect == core::SideEffectKind::MUTATING) {
        return core::Idempotency::CONDITIONALLY_IDEMPOTENT;
    }
    
    return core::Idempotency::UNKNOWN;
}

core::Reversibility IdempotencyClassifier::classify_reversibility(const core::OperationDefinition& op) const {
    // Observation operations don't need reversibility (no state change)
    if (op.side_effect == core::SideEffectKind::NONE ||
        op.side_effect == core::SideEffectKind::OBSERVATION) {
        return core::Reversibility::REVERSIBLE;  // N/A but marked as reversible
    }
    
    // Destructive operations are irreversible
    if (op.side_effect == core::SideEffectKind::DESTRUCTIVE) {
        return core::Reversibility::IRREVERSIBLE;
    }
    
    // Privileged operations may or may not be reversible
    if (op.side_effect == core::SideEffectKind::PRIVILEGED ||
        op.side_effect == core::SideEffectKind::MUTATING) {
        // Check for rollback plan in postconditions
        bool has_rollback = false;
        for (const auto& post : op.postconditions) {
            if (post.find("rollback") != std::string::npos ||
                post.find("restore") != std::string::npos ||
                post.find("undo") != std::string::npos) {
                has_rollback = true;
                break;
            }
        }
        
        // If we have a clear rollback mechanism, it's conditionally reversible
        if (has_rollback) {
            return core::Reversibility::CONDITIONALLY_REVERSIBLE;
        }
        
        // Some mutations can be reversed by applying the inverse operation
        // For example: create X -> delete X, set Y to A -> set Y to B
        bool can_reverse_by_inverse = false;
        for (const auto& post : op.postconditions) {
            if (post.find("create") != std::string::npos ||
                post.find("insert") != std::string::npos ||
                post.find("add") != std::string::npos) {
                can_reverse_by_inverse = true;
                break;
            }
        }
        
        if (can_reverse_by_inverse) {
            return core::Reversibility::CONDITIONALLY_REVERSIBLE;
        }
    }
    
    // Unknown reversibility
    return core::Reversibility::UNKNOWN;
}

std::vector<std::string> IdempotencyClassifier::analyze_evidence(const core::OperationDefinition& op) const {
    std::vector<std::string> evidence;
    
    // Analyze side effects
    switch (op.side_effect) {
        case core::SideEffectKind::NONE:
            evidence.emplace_back("no_side_effects: read-only operation");
            break;
        case core::SideEffectKind::OBSERVATION:
            evidence.emplace_back("side_effect=observation: query/inspection only");
            break;
        case core::SideEffectKind::MUTATING:
            evidence.emplace_back("side_effect=mutating: state-changing operation");
            break;
        case core::SideEffectKind::PRIVILEGED:
            evidence.emplace_back("side_effect=privileged: requires elevated privileges");
            break;
        case core::SideEffectKind::DESTRUCTIVE:
            evidence.emplace_back("side_effect=destructive: irreversible changes likely");
            break;
    }
    
    // Analyze postconditions
    for (const auto& post : op.postconditions) {
        if (post.find("create") != std::string::npos) {
            evidence.emplace_back("has_create_postcondition: operation creates new state");
        }
        if (post.find("delete") != std::string::npos ||
            post.find("remove") != std::string::npos) {
            evidence.emplace_back("has_delete_postcondition: operation may remove state");
        }
        if (post.find("update") != std::string::npos ||
            post.find("modify") != std::string::npos) {
            evidence.emplace_back("has_update_postcondition: operation modifies existing state");
        }
    }
    
    // Analyze preconditions
    for (const auto& pre : op.preconditions) {
        if (pre.find("exists") != std::string::npos) {
            evidence.emplace_back("requires_precondition_exists: operation depends on state existence");
        }
    }
    
    return evidence;
}

RetrySafety IdempotencyClassifier::get_retry_safety(const core::OperationDefinition& op) const {
    auto result = classify(op);
    
    // Idempotent operations are retry-safe
    if (result.idempotency == core::Idempotency::IDEMPOTENT) {
        return RetrySafety::RETRY_SAFE;
    }
    
    // Conditionally idempotent operations may be retry-safe under certain conditions
    if (result.idempotency == core::Idempotency::CONDITIONALLY_IDEMPOTENT) {
        return RetrySafety::RETRY_CONDITIONAL;
    }
    
    // Non-idempotent operations are not retry-safe
    if (result.idempotency == core::Idempotency::NON_IDEMPOTENT) {
        return RetrySafety::NOT_RETRY_SAFE;
    }
    
    // Unknown is treated as conditional (better to be safe than sorry)
    return RetrySafety::RETRY_CONDITIONAL;
}

// ============================================================================
// RetryPolicyFromClassification Implementation
// ============================================================================

int RetryPolicyFromClassification::max_retries_for_idempotent(const core::Idempotency& ip) {
    switch (ip) {
        case core::Idempotency::IDEMPOTENT:
            // Safe to retry multiple times for idempotent operations
            return 3;
        case core::Idempotency::CONDITIONALLY_IDEMPOTENT:
            // May have side effects - limited retries
            return 2;
        case core::Idempotency::NON_IDEMPOTENT:
            // Should not be retried automatically
            return 0;
        default:
            // Unknown - conservative approach
            return 1;
    }
}

bool RetryPolicyFromClassification::should_retry_on_timeout(core::Idempotency ip) {
    // Timeout is often a transient condition that can be safely retried
    // for idempotent operations
    switch (ip) {
        case core::Idempotency::IDEMPOTENT:
            return true;
        default:
            return false;
    }
}

bool RetryPolicyFromClassification::should_retry_on_error(core::Idempotency ip, const std::string& error_code) {
    // Network errors and temporary failures are often retryable
    bool is_transient = 
        error_code.find("E_TIMEOUT") != std::string::npos ||
        error_code.find("E_NETWORK") != std::string::npos ||
        error_code.find("E_CONNECTION") != std::string::npos;
    
    if (is_transient) {
        return ip == core::Idempotency::IDEMPOTENT;
    }
    
    // Permanent errors should not be retried
    bool is_permanent =
        error_code.find("E_INVALID") != std::string::npos ||
        error_code.find("E_NOT_FOUND") != std::string::npos ||
        error_code.find("E_PERMISSION") != std::string::npos;
    
    (void)is_permanent;  // Reserved for future logic
    return false;  // Don't retry permanent errors
}

// ============================================================================
// Classification utilities
// ============================================================================

ClassificationResult classify_by_pattern(const core::OperationDefinition& op) {
    IdempotencyClassifier classifier;
    return classifier.classify(op);
}

core::Idempotency get_default_idempotency(core::SideEffectKind kind) {
    switch (kind) {
        case core::SideEffectKind::NONE:
        case core::SideEffectKind::OBSERVATION:
            return core::Idempotency::IDEMPOTENT;
        case core::SideEffectKind::MUTATING:
            return core::Idempotency::CONDITIONALLY_IDEMPOTENT;
        case core::SideEffectKind::PRIVILEGED:
            return core::Idempotency::CONDITIONALLY_IDEMPOTENT;
        case core::SideEffectKind::DESTRUCTIVE:
            return core::Idempotency::NON_IDEMPOTENT;
    }
    return core::Idempotency::UNKNOWN;
}

core::Reversibility get_default_reversibility(core::SideEffectKind kind) {
    switch (kind) {
        case core::SideEffectKind::NONE:
        case core::SideEffectKind::OBSERVATION:
            return core::Reversibility::REVERSIBLE;  // N/A but safe
        case core::SideEffectKind::MUTATING:
            return core::Reversibility::CONDITIONALLY_REVERSIBLE;
        case core::SideEffectKind::PRIVILEGED:
            return core::Reversibility::CONDITIONALLY_REVERSIBLE;
        case core::SideEffectKind::DESTRUCTIVE:
            return core::Reversibility::IRREVERSIBLE;
    }
    return core::Reversibility::UNKNOWN;
}

}  // namespace rebuntu::idempotency