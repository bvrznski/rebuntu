// rebuntu::shell::boundary — Command Language Semantic Interpretation Boundary (Phase 6.17)
//
// This module defines the typed interface between deterministic shell parsing
// and optional semantic service fallback:
//
//   DETERMINISTIC PARSER PATH (always primary):
//     tokens -> parse_argv() -> CommandIntent -> resolve() -> Operation
//
//   SEMANTIC FALLBACK PATH (only when deterministic fails):
//     unparseable text -> SemanticBoundary::fallback_interpret()
//       -> IntentCandidate from semantic service
//       -> validated against canonical vocabulary
//       -> CommandIntent or rejection
//
// Key Principles:
//   * MODEL OUTPUT != AUTHORITY (always validated before use)
//   * Deterministic parsing always wins when unambiguous
//   * No executable shell fragments in IR
//   * Semantic candidates are typed, not free-text

#pragma once

#include "../types.hpp"
#include <semantics/provider.hpp>
#include <string>
#include <vector>
#include <map>
#include <optional>
#include <chrono>

namespace rebuntu::shell::boundary {

// ============================================================================
// SemanticFallbackMode — Controls when semantic service is invoked
// ============================================================================

enum class SemanticFallbackMode {
    kDisabled,          // Never use semantic fallback (strict deterministic only)
    kOnFailure,         // Use semantic only when deterministic parser fails
    kExplicitOnly,      // Use semantic only when explicitly requested
    kEnabled,           // Use semantic as advisory when deterministic ambiguous
};

inline std::string to_string(SemanticFallbackMode m) {
    switch (m) {
        case SemanticFallbackMode::kDisabled:   return "disabled";
        case SemanticFallbackMode::kOnFailure:  return "on_failure";
        case SemanticFallbackMode::kExplicitOnly: return "explicit_only";
        case SemanticFallbackMode::kEnabled:    return "enabled";
    }
    return "unknown";
}

// ============================================================================
// SemanticFallbackResult — Result of semantic interpretation attempt
// ============================================================================

enum class SemanticFallbackStatus {
    kNoFallbackNeeded,   // Deterministic parsing succeeded
    kFallbackSuccess,    // Semantic service produced valid candidate
    kFallbackRejected,   // Semantic service response invalid/untrusted
    kFallbackTimeout,    // Semantic service timeout
    kFallbackUnavailable,// Semantic service not available
    kFallbackAmbiguous,  // Multiple candidates with no clear winner
};

inline std::string to_string(SemanticFallbackStatus s) {
    switch (s) {
        case SemanticFallbackStatus::kNoFallbackNeeded:   return "no_fallback_needed";
        case SemanticFallbackStatus::kFallbackSuccess:    return "success";
        case SemanticFallbackStatus::kFallbackRejected:   return "rejected";
        case SemanticFallbackStatus::kFallbackTimeout:    return "timeout";
        case SemanticFallbackStatus::kFallbackUnavailable:return "unavailable";
        case SemanticFallbackStatus::kFallbackAmbiguous:  return "ambiguous";
    }
    return "unknown";
}

struct FallbackResult {
    SemanticFallbackStatus status{SemanticFallbackStatus::kNoFallbackNeeded};
    
    // If successful, the candidate intent from semantic service
    std::optional<CommandIntent> intent;
    
    // Diagnostic information
    std::string diagnostic;              // Human-readable explanation
    
    // Evidence for verification/debugging
    struct Evidence {
        std::chrono::milliseconds request_duration_ms{0};
        bool deterministic_parse_attempted{false};
        bool semantic_service_used{false};
    } evidence;
};

// ============================================================================
// SemanticBoundary — Interface between deterministic and semantic parsing
//
// This is a pure interface that must be composed with actual providers.
// ============================================================================

class SemanticBoundary {
public:
    virtual ~SemanticBoundary() = default;
    
    // Configuration
    virtual void set_fallback_mode(SemanticFallbackMode mode) = 0;
    virtual SemanticFallbackMode fallback_mode() const = 0;
    
    virtual void set_allowed_operations(const std::vector<std::string>& ops) = 0;
    virtual void set_timeout(std::chrono::milliseconds timeout) = 0;
    virtual std::chrono::milliseconds timeout() const = 0;
    
    // Attempt to interpret text using semantic fallback
    // Returns FallbackResult with status and optional intent
    virtual FallbackResult fallback_interpret(
        const std::string& raw_text,
        const CommandRegistry& registry
    ) = 0;
    
    // Validate that a semantic candidate is acceptable
    // This checks: verb in registry, valid subject, proper scope, etc.
    virtual bool validate_candidate(
        const CommandIntent& intent,
        const CommandRegistry& registry
    ) = 0;
};

// ============================================================================
// SemanticBoundaryConfig — Configuration for semantic boundary
// ============================================================================

struct SemanticBoundaryConfig {
    SemanticFallbackMode fallback_mode{SemanticFallbackMode::kOnFailure};
    std::chrono::milliseconds default_timeout{30000};  // 30 seconds
    
    // Constraints on semantic output
    size_t max_allowed_candidates{5};     // Maximum candidates from model
    bool require_verb_in_registry{true};   // Must verb be in registry?
    bool allow_subject_inference{false};   // Can model infer subject?
    
    // Safety thresholds
    double minimum_confidence_threshold{0.7};  // Minimum confidence for acceptance
    
    static SemanticBoundaryConfig make_default() {
        return SemanticBoundaryConfig{};
    }
};

// ============================================================================
// FallbackDiagnostics — Detailed information about fallback attempt
// ============================================================================

struct FallbackDiagnostics {
    std::string raw_input;
    
    bool deterministic_parse_attempted{false};
    std::optional<std::string> deterministic_error;  // What went wrong
    
    bool semantic_service_used{false};
    SemanticFallbackStatus semantic_status{SemanticFallbackStatus::kNoFallbackNeeded};
    std::optional<CommandIntent> semantic_intent;
    
    std::chrono::milliseconds total_duration_ms{0};
};

// ============================================================================
// BoundaryError — Error types for boundary operations
// ============================================================================

namespace error {
    constexpr const char* kSemanticTimeout = "E_SEMANTIC_TIMEOUT";
    constexpr const char* kSemanticUnavailable = "E_SEMANTIC_UNAVAILABLE";
    constexpr const char* kValidationError = "E_SEMANTIC_VALIDATION_ERROR";
    constexpr const char* kAmbiguousCandidate = "E_AMBIGUOUS_CANDIDATE";
}

}  // namespace rebuntu::shell::boundary