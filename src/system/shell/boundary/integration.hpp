// rebuntu::shell::boundary — Semantic Boundary Implementation Interface (Phase 6.17)
//
// This module provides concrete implementations of the semantic interpretation boundary:
//
//   - SemanticBoundary: Abstract interface
//   - DeterministicFallbackBoundary: Fallback to semantic only when deterministic fails
//   - ExplicitModeSemanticBoundary: Semantic mode only when explicitly requested

#pragma once

#include "types.hpp"
#include "../parser.hpp"
#include <semantics/provider.hpp>
#include <string>
#include <vector>
#include <map>
#include <optional>
#include <chrono>
#include <memory>

using namespace std::chrono_literals;

namespace rebuntu::shell::boundary {

// ============================================================================
// DeterministicFallbackBoundary — Default implementation of SemanticBoundary
//
// This class:
//   1. First attempts deterministic parsing (always tried first)
//   2. Only falls back to semantic service when:
//      a) Deterministic parsing fails (unknown verb), AND
//      b) Fallback mode allows it (not kDisabled)
//   3. Validates all semantic candidates against canonical vocabulary
//
// Key invariant: MODEL OUTPUT != AUTHORITY
//   All semantic output must be validated before becoming intent.
// ============================================================================

class DeterministicFallbackBoundary : public SemanticBoundary {
public:
    explicit DeterministicFallbackBoundary(
        std::shared_ptr<rebuntu::semantic::SemanticProvider> provider = nullptr);
    
    ~DeterministicFallbackBoundary() override;
    
    // Configuration
    void set_fallback_mode(SemanticFallbackMode mode) override;
    SemanticFallbackMode fallback_mode() const override;
    
    void set_allowed_operations(const std::vector<std::string>& ops) override;
    
    void set_timeout(std::chrono::milliseconds timeout) override;
    std::chrono::milliseconds timeout() const override;
    
    // Attempt to interpret text using semantic fallback
    FallbackResult fallback_interpret(
        const std::string& raw_text,
        const CommandRegistry& registry
    ) override;
    
    // Validate that a semantic candidate is acceptable
    bool validate_candidate(
        const CommandIntent& intent,
        const CommandRegistry& registry
    ) override;
    
    // Get diagnostics for the last fallback attempt
    FallbackDiagnostics get_last_diagnostics() const;

private:
    std::shared_ptr<rebuntu::semantic::SemanticProvider> provider_;
    SemanticFallbackMode fallback_mode_{SemanticFallbackMode::kOnFailure};
    std::chrono::milliseconds timeout_ms_{30000};
    std::vector<std::string> allowed_operations_;
    FallbackDiagnostics last_diagnostics_;
};

// ============================================================================
// ExplicitModeSemanticBoundary — Semantic-only mode boundary
//
// This class requires explicit semantic mode activation (e.g., via flag).
// Deterministic parsing is NOT attempted first.
// ============================================================================

class ExplicitModeSemanticBoundary : public SemanticBoundary {
public:
    explicit ExplicitModeSemanticBoundary(
        std::shared_ptr<rebuntu::semantic::SemanticProvider> provider = nullptr);
    
    ~ExplicitModeSemanticBoundary() override;
    
    // Configuration
    void set_fallback_mode(SemanticFallbackMode mode) override;
    SemanticFallbackMode fallback_mode() const override;
    
    void set_allowed_operations(const std::vector<std::string>& ops) override;
    
    void set_timeout(std::chrono::milliseconds timeout) override;
    std::chrono::milliseconds timeout() const override;
    
    // Attempt to interpret text using semantic service (always semantic)
    FallbackResult fallback_interpret(
        const std::string& raw_text,
        const CommandRegistry& registry
    ) override;
    
    // Validate that a semantic candidate is acceptable
    bool validate_candidate(
        const CommandIntent& intent,
        const CommandRegistry& registry
    ) override;

private:
    std::shared_ptr<rebuntu::semantic::SemanticProvider> provider_;
    SemanticFallbackMode fallback_mode_{SemanticFallbackMode::kExplicitOnly};
    std::chrono::milliseconds timeout_ms_{30000};
    std::vector<std::string> allowed_operations_;
};

// ============================================================================
// SemanticBoundaryFactory — Factory to create appropriate boundary instance
// ============================================================================

class SemanticBoundaryFactory {
public:
    static std::unique_ptr<SemanticBoundary> make_boundary(
        SemanticFallbackMode mode,
        std::shared_ptr<rebuntu::semantic::SemanticProvider> provider = nullptr
    );
    
    static std::unique_ptr<SemanticBoundary> make_default_boundary(
        std::shared_ptr<rebuntu::semantic::SemanticProvider> provider = nullptr
    );
};

}  // namespace rebuntu::shell::boundary