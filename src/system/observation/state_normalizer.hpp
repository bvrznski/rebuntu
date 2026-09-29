// rebuntu::system::observation::state_normalizer — State Normalization System (Phase 7.3)
//
// This module implements canonical state normalization for Rebuntu:
//   - Normalizes heterogeneous provider/native observations into canonical representations
//   - Preserves source-specific evidence and values
//   - Defines when normalization is impossible (must remain provider-specific)
//   - Supports round-trip debugging with preserved provenance
//
// Design Principles:
//   - NORMALIZE TO CANONICAL, NOT FROM CANONICAL
//   - PRESERVE EVIDENCE BEFORE NORMALIZING
//   - PRESERVE UNKNOWN BEFORE GUESSING
//   - TIMESTAMP BEFORE CLAIMING CURRENTNESS
//   - DISTINGUISH OBSERVATION FROM FACT
//
// Key Semantics:
//   Observation: Raw, source-bound evidence obtained at a specific time
//   Fact: Typed claim derived from one or more observations under explicit rules
//   NormalizedValue: Canonical representation for canonical domains
//   RawValue: Original provider-specific value (preserved in evidence)

#pragma once

#include "types.hpp"
#include "bounds.hpp"

#include <chrono>
#include <memory>
#include <optional>
#include <set>
#include <string>
#include <vector>
#include <unordered_map>

namespace rebuntu::system::observation {

// ============================================================================
// StateNormalizationError — Error codes for state normalization
//
// Distinguishes between different kinds of failures WITHOUT turning UNKNOWN into false:
//   - Unknown = "I don't know" (not a negative observation)
//   - Unsupported = "This provider cannot provide this value"
//   - Stale = "Data exists but is old"
//   - Failure = "Something went wrong trying to acquire it"
// ============================================================================

enum class StateNormalizationError {
    kNoNormalizer,           // No normalizer exists for this domain/provider
    kUnknownValue,           // Value cannot be mapped to any canonical value (UNKNOWN, not false)
    kUnsupported,            // Provider doesn't support this field/value type
    kProviderSpecificOnly,   // Value must remain provider-specific (no canonical form)
    kParseFailure,           // Cannot parse raw value into known format
    kValidationFailure,      // Parsed value fails validation rules
    kStale,                  // Data exists but is older than freshness policy allows
    kTimeout,                // Normalization timed out
    kCancellation,           // Normalization was cancelled
};

inline std::string to_string(StateNormalizationError e) {
    switch (e) {
        case StateNormalizationError::kNoNormalizer:       return "no-normalizer";
        case StateNormalizationError::kUnknownValue:       return "unknown-value";
        case StateNormalizationError::kUnsupported:        return "unsupported";
        case StateNormalizationError::kProviderSpecificOnly:return "provider-specific-only";
        case StateNormalizationError::kParseFailure:       return "parse-failure";
        case StateNormalizationError::kValidationFailure:  return "validation-failure";
        case StateNormalizationError::kStale:              return "stale";
        case StateNormalizationError::kTimeout:            return "timeout";
        case StateNormalizationError::kCancellation:       return "cancellation";
    }
    return "unknown";
}

// ============================================================================
// NormalizationResult — Result of normalizing an observation
// ============================================================================

struct NormalizationResult {
    core::SemanticStatus status{core::SemanticStatus::kUnknown};
    
    // The normalized canonical value (if successful)
    std::optional<std::string> canonical_value;
    
    // Original raw value preserved for debugging/provenance
    std::optional<std::string> raw_value_preserved;
    
    // Source that provided this value
    std::string source{};
    
    // Evidence chain: all observations contributing to this normalization
    std::vector<ObservationIdentity> evidence_chain{};
    
    // Timing information
    std::chrono::milliseconds elapsed_ms{0};
    
    // Error details (for non-success status)
    StateNormalizationError error_code{StateNormalizationError::kNoNormalizer};
    std::string error_message{};
    
    // Additional context for debugging (e.g., normalization rules applied)
    std::vector<std::pair<std::string, std::string>> metadata{};
    
    static NormalizationResult success(
        std::string canonical,
        std::optional<std::string> raw = {},
        std::chrono::milliseconds elapsed = {}
    ) {
        NormalizationResult r;
        r.status = core::SemanticStatus::kSuccess;
        r.canonical_value = std::move(canonical);
        if (raw) r.raw_value_preserved = std::move(*raw);
        r.elapsed_ms = elapsed;
        return r;
    }
    
    static NormalizationResult provider_specific(
        std::string raw,
        std::string source,
        std::chrono::milliseconds elapsed = {}
    ) {
        NormalizationResult r;
        r.status = core::SemanticStatus::kCompleted;  // Not failure - just no normalization
        r.raw_value_preserved = std::move(raw);
        r.source = std::move(source);
        r.error_code = StateNormalizationError::kProviderSpecificOnly;
        r.elapsed_ms = elapsed;
        return r;
    }
    
    static NormalizationResult unknown(
        std::string message,
        std::chrono::milliseconds elapsed = {}
    ) {
        NormalizationResult r;
        r.status = core::SemanticStatus::kUnknown;
        r.error_code = StateNormalizationError::kUnknownValue;
        r.error_message = std::move(message);
        r.elapsed_ms = elapsed;
        return r;
    }
    
    static NormalizationResult parse_failure(
        std::string raw,
        std::string source,
        std::chrono::milliseconds elapsed = {}
    ) {
        NormalizationResult r;
        r.status = core::SemanticStatus::kFailure;
        r.raw_value_preserved = std::move(raw);
        r.source = std::move(source);
        r.error_code = StateNormalizationError::kParseFailure;
        r.error_message = "Failed to parse value from " + source;
        r.elapsed_ms = elapsed;
        return r;
    }
    
    static NormalizationResult validation_failure(
        std::string raw,
        std::string reason,
        std::chrono::milliseconds elapsed = {}
    ) {
        NormalizationResult r;
        r.status = core::SemanticStatus::kFailure;
        r.raw_value_preserved = std::move(raw);
        r.error_code = StateNormalizationError::kValidationFailure;
        r.error_message = std::move(reason);
        r.elapsed_ms = elapsed;
        return r;
    }
    
    static NormalizationResult cancelled(
        std::string message,
        std::chrono::milliseconds elapsed = {}
    ) {
        NormalizationResult r;
        r.status = core::SemanticStatus::kCancelled;
        r.error_code = StateNormalizationError::kCancellation;
        r.error_message = std::move(message);
        r.elapsed_ms = elapsed;
        return r;
    }
    
    static NormalizationResult timeout(
        std::string message,
        std::chrono::milliseconds elapsed = {}
    ) {
        NormalizationResult r;
        r.status = core::SemanticStatus::kFailure;
        r.error_code = StateNormalizationError::kTimeout;
        r.error_message = std::move(message);
        r.elapsed_ms = elapsed;
        return r;
    }
};

// ============================================================================
// StateNormalizer — Interface for normalizing observations
// ============================================================================

class StateNormalizer {
public:
    virtual ~StateNormalizer() = default;
    
    // Normalize an observation to canonical form
    // Returns NormalizationResult with either canonical_value or preserved evidence
    virtual NormalizationResult normalize(
        const Observation& observation,
        std::chrono::milliseconds timeout = std::chrono::seconds(10)
    ) = 0;
    
    // Check if a value can be normalized for this normalizer's domain
    virtual bool can_normalize(ObservationDomain domain, const std::string& value) const = 0;
    
    // Get the set of canonical values this normalizer supports
    virtual std::set<std::string> get_canonical_values() const = 0;
    
    // Get metadata about normalization rules applied
    virtual std::unordered_map<std::string, std::string> normalization_rules() const = 0;
};

// ============================================================================
// StateNormalizerRegistry — Registry of available normalizers
// ============================================================================

class StateNormalizerRegistry {
public:
    virtual ~StateNormalizerRegistry() = default;
    
    // Register a normalizer for an observation domain
    // Multiple normalizers can exist for the same domain (e.g., different providers)
    virtual core::Outcome register_normalizer(
        ObservationDomain domain,
        std::string provider_name,
        std::unique_ptr<StateNormalizer> normalizer
    ) = 0;
    
    // Get the appropriate normalizer for a domain/provider combination
    // Returns nullptr if no suitable normalizer exists
    virtual StateNormalizer* get_normalizer(
        ObservationDomain domain,
        const std::string& provider_name
    ) const = 0;
    
    // Try to normalize an observation using available normalizers
    // This is the primary entry point for Phase 7.3 consumers
    virtual NormalizationResult try_normalize(
        const Observation& observation,
        std::chrono::milliseconds timeout = std::chrono::seconds(10)
    ) = 0;
    
    // Get all registered normalizers for a domain
    virtual std::vector<std::string> get_normalizer_names(ObservationDomain domain) const = 0;
};

// ============================================================================
// Factory functions
// ============================================================================

std::unique_ptr<StateNormalizerRegistry> make_state_normalizer_registry();

}  // namespace rebuntu::system::observation
