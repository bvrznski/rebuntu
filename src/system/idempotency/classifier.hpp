// Rebuntu Idempotency Classification System (Phase 6.23)
//
// This module provides automatic idempotency classification for operations.
// It analyzes operation characteristics and classifies them as:
//   - IDEMPOTENT: Multiple executions have the same effect as one execution
//   - CONDITIONALLY_IDEMPOTENT: Idempotent only under certain conditions
//   - NON_IDEMPOTENT: Each execution has distinct effects
//
// The classification is used in retry/recovery mechanics to determine
// which operations are safe to retry.

#pragma once

#include <system/core/contracts.hpp>
#include <string>
#include <string_view>
#include <functional>

namespace rebuntu::idempotency {

// ============================================================================
// ClassificationResult — Result of an idempotency analysis
// ============================================================================

struct ClassificationResult {
    core::Idempotency idempotency = core::Idempotency::UNKNOWN;
    core::Reversibility reversibility = core::Reversibility::UNKNOWN;
    
    // Evidence for the classification decision
    std::vector<std::string> evidence;
    
    static ClassificationResult make_idempotent(const std::vector<std::string>& evidence = {}) {
        ClassificationResult r;
        r.idempotency = core::Idempotency::IDEMPOTENT;
        r.reversibility = core::Reversibility::REVERSIBLE;
        r.evidence = evidence;
        return r;
    }
    
    static ClassificationResult make_conditionally_idempotent(const std::vector<std::string>& evidence = {}) {
        ClassificationResult r;
        r.idempotency = core::Idempotency::CONDITIONALLY_IDEMPOTENT;
        r.reversibility = core::Reversibility::CONDITIONALLY_REVERSIBLE;
        r.evidence = evidence;
        return r;
    }
    
    static ClassificationResult make_non_idempotent(const std::vector<std::string>& evidence = {}) {
        ClassificationResult r;
        r.idempotency = core::Idempotency::NON_IDEMPOTENT;
        r.reversibility = core::Reversibility::IRREVERSIBLE;
        r.evidence = evidence;
        return r;
    }
    
    static ClassificationResult make_unknown(const std::string& reason) {
        ClassificationResult r;
        r.idempotency = core::Idempotency::UNKNOWN;
        r.reversibility = core::Reversibility::UNKNOWN;
        r.evidence.emplace_back("classification unknown: " + reason);
        return r;
    }
};

// ============================================================================
// RetrySafety — Classification of operation safety for retry
// ============================================================================

enum class RetrySafety {
    RETRY_SAFE,      // Safe to retry without side effects
    RETRY_CONDITIONAL,  // Safe only under certain conditions
    NOT_RETRY_SAFE,  // Should not be retried automatically
};

inline std::string_view to_string(RetrySafety s) {
    switch (s) {
        case RetrySafety::RETRY_SAFE: return "retry_safe";
        case RetrySafety::RETRY_CONDITIONAL: return "retry_conditional";
        case RetrySafety::NOT_RETRY_SAFE: return "not_retry_safe";
    }
    return "unknown";
}

// ============================================================================
// IdempotencyClassifier — Classifies operations for idempotency
//
// The classifier analyzes operation characteristics:
//   - Side effects (mutating vs observation)
//   - State changes (idempotent if no state change on repeat)
//   - External dependencies (network calls may be non-idempotent)
//   - System integration level (native mechanisms often more predictable)
// ============================================================================

class IdempotencyClassifier {
public:
    // Classify an operation based on its definition
    ClassificationResult classify(const core::OperationDefinition& op) const;
    
    // Get retry safety for an operation
    RetrySafety get_retry_safety(const core::OperationDefinition& op) const;
    
    // Check if operation is safe to retry (idempotent or conditionally idempotent)
    bool is_retry_safe(const core::OperationDefinition& op) const {
        return get_retry_safety(op) != RetrySafety::NOT_RETRY_SAFE;
    }

private:
    // Classification helpers
    bool has_side_effect(const core::OperationDefinition& op) const;
    bool is_mutation(const core::OperationDefinition& op) const;
    std::vector<std::string> analyze_evidence(const core::OperationDefinition& op) const;
    
    // Automatic classification based on operation characteristics
    core::Idempotency classify_idempotency(const core::OperationDefinition& op) const;
    core::Reversibility classify_reversibility(const core::OperationDefinition& op) const;
};

// ============================================================================
// RetryPolicyFromClassification — Create retry policy from classification
// ============================================================================

struct RetryPolicyFromClassification {
    // Based on idempotency classification, determine appropriate retry behavior
    
    static int max_retries_for_idempotent(const core::Idempotency& ip);
    
    static bool should_retry_on_timeout(core::Idempotency ip);
    
    static bool should_retry_on_error(core::Idempotency ip, const std::string& error_code);
};

// ============================================================================
// Classification utilities
// ============================================================================

// Classify an operation by its typical behavior patterns
ClassificationResult classify_by_pattern(const core::OperationDefinition& op);

// Get default classification for side effect kinds
core::Idempotency get_default_idempotency(core::SideEffectKind kind);
core::Reversibility get_default_reversibility(core::SideEffectKind kind);

}  // namespace rebuntu::idempotency