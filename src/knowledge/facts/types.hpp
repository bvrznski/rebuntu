// rebuntu::knowledge::facts::types — Derived Fact Boundary with DETERMINISTIC_DERIVATION (Phase 5.42)
//
// This module defines typed fact representations for deterministic derivations
// from observed facts only, with explicit provenance and epistemic classification.
//
// Design principles:
//   - Deterministic derivation: Facts derived from observations using well-defined rules
//   - Explicit provenance: Each derived fact identifies supporting observations
//   - Epistemic class DETERMINISTIC_DERIVATION for derived facts
//   - No inference, recommendation, or recovery without explicit observation basis

#pragma once

#include <chrono>
#include <optional>
#include <string>
#include <vector>

namespace rebuntu::knowledge::facts {

// ============================================================================
// EpistemicClass — Classification of knowledge origin
//
// Distinguishes between:
//   - OBSERVATION: Direct measurement from authoritative source (procfs, sysfs, udev)
//   - DETERMINISTIC_DERIVATION: Computed from observations using well-defined rules
//   - CONFIGURED: Explicitly set via configuration
//   - UNKNOWN: Source unknown or unavailable
// ============================================================================
//
// Implementation note: This classifies the SOURCE of knowledge,
// not its truth value. A derived fact can be correct if its
// derivation rules and inputs are correct.

enum class EpistemicClass {
    OBSERVATION,          // Directly observed from native Linux source
    DETERMINISTIC_DERIVATION,  // Deterministically computed from observations
    CONFIGURED,           // Explicitly configured by authority
    UNKNOWN               // Source unknown or unavailable
};

inline std::string to_string(EpistemicClass ec) {
    switch (ec) {
        case EpistemicClass::OBSERVATION:          return "observation";
        case EpistemicClass::DETERMINISTIC_DERIVATION:  return "deterministic_derivation";
        case EpistemicClass::CONFIGURED:           return "configured";
        case EpistemicClass::UNKNOWN:              return "unknown";
    }
    return "unknown";
}

// ============================================================================
// DerivedFactSource — Reference to an observation or derived fact
//
// A typed reference that identifies the source of a fact.
// This preserves provenance without creating shadow state.
// ============================================================================
//
// Design note:
//   - stable_id: Durable identity (e.g., "/sys/class/net/eth0/address")
//   - attribute: Specific attribute within the source
//   - derivation_rule: Rule used to derive this from observations

struct DerivedFactSource {
    std::string stable_id;      // Stable identifier for the source entity
    std::optional<std::string> attribute;  // Optional specific attribute
    std::optional<std::string> derivation_rule;  // Rule or computation name
    
    static DerivedFactSource make_observation(std::string id) {
        return {std::move(id), std::nullopt, std::nullopt};
    }
    
    static DerivedFactSource make_attribute(std::string id, std::string attr) {
        return {std::move(id), std::move(attr), std::nullopt};
    }
    
    static DerivedFactSource make_derivation(
        std::string id,
        std::string rule
    ) {
        return {std::move(id), std::nullopt, std::move(rule)};
    }
};

// ============================================================================
// Fact — Typed fact with epistemic classification and provenance
//
// A fact is a statement about the system state at a point in time.
// Derived facts must identify their supporting observations.
// ============================================================================
//
// Implementation notes:
//   - key: The fact identifier (e.g., "system.memory.total_bytes")
//   - value: The fact value
//   - epistemic_class: Classification of knowledge origin
//   - sources: References to supporting observations (required for derivations)
//   - observed_at: When the original observation(s) occurred

struct Fact {
    std::string key;                       // Fact identifier
    std::string value;                     // Fact value
    EpistemicClass epistemic_class{EpistemicClass::OBSERVATION};
    std::chrono::system_clock::time_point observed_at{};
    
    // Provenance: references to supporting observations
    // For DETERMINISTIC_DERIVATION, this is required
    std::vector<DerivedFactSource> sources;
    
    // Optional metadata for derived facts
    std::optional<std::string> derivation_rule;  // Name of the derivation rule
};

// ============================================================================
// DerivedFactBuilder — Builder for deterministic derivations
//
// Provides a fluent interface for constructing derived facts with
// proper provenance tracking and epistemic classification.
// ============================================================================
//
// Usage pattern:
//   Fact fact = DerivedFactBuilder()
//       .set_key("system.memory.used_bytes")
//       .set_value(to_string(used))
//       .set_derivation_rule("total - free - cached")
//       .add_source(observation1)
//       .add_source(observation2)
//       .build();

class DerivedFactBuilder {
public:
    DerivedFactBuilder() = default;
    
    // Set the fact key (required)
    DerivedFactBuilder& set_key(std::string key) {
        key_ = std::move(key);
        return *this;
    }
    
    // Set the fact value (required)
    DerivedFactBuilder& set_value(std::string value) {
        value_ = std::move(value);
        return *this;
    }
    
    // Set derivation rule name (required for DETERMINISTIC_DERIVATION)
    DerivedFactBuilder& set_derivation_rule(std::string rule) {
        derivation_rule_ = std::move(rule);
        return *this;
    }
    
    // Add a supporting observation source
    DerivedFactBuilder& add_source(DerivedFactSource source) {
        sources_.push_back(std::move(source));
        return *this;
    }
    
    // Set the observed_at timestamp (optional)
    DerivedFactBuilder& set_observed_at(std::chrono::system_clock::time_point tp) {
        observed_at_ = tp;
        return *this;
    }
    
    // Build the fact with DETERMINISTIC_DERIVATION epistemic class
    Fact build() const {
        Fact f;
        f.key = key_;
        f.value = value_;
        f.epistemic_class = EpistemicClass::DETERMINISTIC_DERIVATION;
        f.observed_at = observed_at_.value_or(std::chrono::system_clock::now());
        f.sources = sources_;
        if (derivation_rule_) {
            f.derivation_rule = derivation_rule_;
        }
        return f;
    }
    
    // Build with a specific epistemic class (for non-derivation cases)
    Fact build_with_class(EpistemicClass ec) const {
        Fact f;
        f.key = key_;
        f.value = value_;
        f.epistemic_class = ec;
        f.observed_at = observed_at_.value_or(std::chrono::system_clock::now());
        f.sources = sources_;
        if (derivation_rule_) {
            f.derivation_rule = derivation_rule_;
        }
        return f;
    }

private:
    std::string key_;
    std::string value_;
    std::optional<std::chrono::system_clock::time_point> observed_at_;
    std::vector<DerivedFactSource> sources_;
    std::optional<std::string> derivation_rule_;
};

}  // namespace rebuntu::knowledge::facts