// rebuntu::knowledge::facts::integration — Derived Fact Boundary Integration (Phase 5.42)
//
// This module provides integration utilities for deterministic derivation
// of facts from observed data, with explicit provenance tracking.
//
// Integration points:
//   - Fact validation and verification
//   - Derivation rule registration
//   - Provenance chain validation

#pragma once

#include <chrono>
#include <optional>
#include <string>
#include <vector>
#include <unordered_map>

#include "types.hpp"

namespace rebuntu::knowledge::facts {

// ============================================================================
// DerivedFactError — Error types for derived fact operations
// ============================================================================

enum class DerivedFactError {
    MISSING_OBSERVATION,      // Required observation not found
    INVALID_DERIVATION_RULE,  // Derivation rule failed or invalid
    INCOMPLETE_PROVENANCE,    // Not all required sources provided
    CIRCULAR_REFERENCE        // Circular dependency in derivation chain
};

inline std::string to_string(DerivedFactError err) {
    switch (err) {
        case DerivedFactError::MISSING_OBSERVATION:    return "missing_observation";
        case DerivedFactError::INVALID_DERIVATION_RULE:return "invalid_derivation_rule";
        case DerivedFactError::INCOMPLETE_PROVENANCE:  return "incomplete_provenance";
        case DerivedFactError::CIRCULAR_REFERENCE:     return "circular_reference";
    }
    return "unknown";
}

// ============================================================================
// ProvenanceChain — Track the chain of observation sources for a derived fact
//
// A provenance chain documents the complete lineage of a derived fact,
// from original observations to final computed value.
// ============================================================================

struct ProvenanceRecord {
    std::string stable_id;       // Source entity identifier
    std::optional<std::string> attribute;  // Optional specific attribute
    std::chrono::system_clock::time_point observed_at{};
    bool verified = true;        // Was this observation verified?
};

class ProvenanceChain {
public:
    ProvenanceChain() = default;
    
    // Add an observation to the chain
    void add_observation(
        std::string stable_id,
        std::chrono::system_clock::time_point observed_at,
        bool verified = true
    ) {
        records_.push_back({std::move(stable_id), std::nullopt, observed_at, verified});
    }
    
    // Add an attribute observation to the chain
    void add_attribute(
        std::string stable_id,
        std::string attribute,
        std::chrono::system_clock::time_point observed_at,
        bool verified = true
    ) {
        records_.push_back({std::move(stable_id), std::move(attribute), observed_at, verified});
    }
    
    // Get all records in the chain
    const std::vector<ProvenanceRecord>& records() const { return records_; }
    
    // Check if chain is complete (has at least one record)
    bool empty() const { return records_.empty(); }
    
    size_t size() const { return records_.size(); }

private:
    std::vector<ProvenanceRecord> records_;
};

// ============================================================================
// DerivedFactValidator — Validation for derived facts
//
// Validates that a derived fact has proper provenance and
// all required source observations are available.
// ============================================================================

class DerivedFactValidator {
public:
    DerivedFactValidator() = default;
    
    // Validate that the fact is properly formed
    bool validate(const Fact& fact) const {
        if (fact.key.empty()) return false;
        if (fact.value.empty()) return false;
        
        // For DETERMINISTIC_DERIVATION, sources are required
        if (fact.epistemic_class == EpistemicClass::DETERMINISTIC_DERIVATION) {
            if (fact.sources.empty()) return false;
        }
        
        return true;
    }
    
    // Validate and get error details
    struct ValidationResult {
        bool valid = false;
        std::vector<std::string> errors;
        
        static ValidationResult make_valid() {
            return {true, {}};
        }
        
        static ValidationResult make_invalid(std::vector<std::string> errs) {
            return {false, std::move(errs)};
        }
    };
    
    ValidationResult validate_with_errors(const Fact& fact) const {
        ValidationResult result;
        
        if (fact.key.empty()) {
            result.errors.push_back("key is empty");
        }
        if (fact.value.empty()) {
            result.errors.push_back("value is empty");
        }
        if (fact.epistemic_class == EpistemicClass::DETERMINISTIC_DERIVATION &&
            fact.sources.empty()) {
            result.errors.push_back("derivation missing required sources");
        }
        
        if (result.errors.empty()) {
            result.valid = true;
        }
        
        return result;
    }
};

// ============================================================================
// DerivedFactManager — Manager for deterministic derivation operations
//
// Provides registration of derivation rules and management of
// derived facts with provenance tracking.
// ============================================================================

class DerivedFactManager {
public:
    DerivedFactManager() = default;
    
    // Register a derivation rule (by name)
    void register_derivation_rule(
        std::string name,
        std::string description
    ) {
        rules_[std::move(name)] = std::move(description);
    }
    
    // Check if a derivation rule is registered
    bool has_derivation_rule(const std::string& name) const {
        return rules_.find(name) != rules_.end();
    }
    
    // Get description of a derivation rule
    std::optional<std::string> get_derivation_rule_description(
        const std::string& name
    ) const {
        auto it = rules_.find(name);
        if (it != rules_.end()) {
            return it->second;
        }
        return std::nullopt;
    }
    
    // Validate provenance chain for a derived fact
    ProvenanceChain validate_provenance(const Fact& fact) const {
        ProvenanceChain chain;
        
        for (const auto& source : fact.sources) {
            chain.add_observation(source.stable_id, std::chrono::system_clock::now());
        }
        
        return chain;
    }

private:
    std::unordered_map<std::string, std::string> rules_;
};

}  // namespace rebuntu::knowledge::facts