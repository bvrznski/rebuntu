// rebuntu::shell::semi_natural — Semi-Natural Command Grammar (Phase 6.16)
//
// This module extends Rebuntu's shell grammar to support controlled
// semi-natural expressions while maintaining deterministic parsing.
//
// Design Philosophy:
//   * Shell is a PRESENTATION SURFACE, not an independent runtime
//   * Typed IR ensures deterministic parsing before execution
//   * Semi-natural sugar is canonicalized to the same IR as concise syntax
//   * Ambiguity in interpretation must be detected and reported
//
// Examples of supported semi-natural forms:
//   - "install package foo" → verb="install", subject="package", target="foo"
//   - "install foo" → verb="install", subject inferred, target="foo"
//   - "status service nginx" → verb="status", subject="service", target="nginx"
//   - "show status of service nginx" → canonicalizes to status command
//   - "restart nginx service" → verb="restart", subject="service", target="nginx"

#pragma once

#include "types.hpp"
#include <algorithm>

namespace rebuntu::shell {

// ============================================================================
// GrammarKind — Classification of grammar form
// ============================================================================

enum class GrammarKind {
    kConcise,           // Canonical form: "install package foo"
    kSemiNatural,       // Semi-natural form with modifiers: "status service nginx"
    kPredicateStyle,    // Predicate form: "installed foo", "running nginx"
};

inline std::string to_string(GrammarKind k) {
    switch (k) {
        case GrammarKind::kConcise: return "concise";
        case GrammarKind::kSemiNatural: return "semi-natural";
        case GrammarKind::kPredicateStyle: return "predicate-style";
    }
    return "unknown";
}

// ============================================================================
// ParseContext — Context for semi-natural grammar parsing
// ============================================================================

struct ParseContext {
    // Whether to use semantic fallback when deterministic parsing fails
    bool allow_semantic_fallback{false};
    
    // Maximum number of candidates to consider during disambiguation
    size_t max_candidates{10};
    
    // Whether to require explicit scope when ambiguous
    bool require_explicit_scope_when_ambiguous{true};
};

// ============================================================================
// GrammarRule — Rule for parsing a specific grammar form
// ============================================================================

struct GrammarRule {
    std::string name;              // Rule name for debugging
    GrammarKind kind;
    
    // Priority (higher = tried first)
    int priority{0};
    
    // Whether this rule requires all arguments
    bool require_all_arguments{false};
    
    // Subject inference rules when subject is omitted
    std::optional<std::string> default_subject_for_verb(std::string_view verb) const;
};

// ============================================================================
// ParseResult — Result of semi-natural grammar parsing
// ============================================================================

struct ParseResult {
    GrammarKind kind{GrammarKind::kConcise};
    
    // Parsed intent (may be same as input if already parsed)
    CommandIntent intent{};
    
    // Which rule(s) were used for parsing
    std::vector<std::string> rules_used;
    
    // Ambiguity information (if any)
    bool has_ambiguity{false};
    std::vector<CommandIntent> alternative_intents;
    
    // Parse diagnostics for explain/debug output
    std::vector<std::string> diagnostics;
};

// ============================================================================
// SemiNaturalParser — Parser for semi-natural grammar forms
// ============================================================================

class SemiNaturalParser {
public:
    explicit SemiNaturalParser(const CommandRegistry& registry);
    
    // Parse input tokens into a canonical intent
    ParseResult parse(const std::vector<std::string>& tokens) const;
    
    // Canonicalize a parsed intent (ensure it's in normalized form)
    CommandIntent canonicalize(const CommandIntent& intent) const;
    
    // Get grammar rules for documentation/explain
    std::vector<GrammarRule> get_rules() const;

private:
    const CommandRegistry* registry_;
    
    // Rule matching functions
    ParseResult parse_concise_(const std::vector<std::string>& tokens) const;
    ParseResult parse_semi_natural_(const std::vector<std::string>& tokens) const;
    ParseResult parse_predicate_style_(const std::string& input) const;
};

// ============================================================================
// GrammarAnalyzer — Analyze grammar properties
// ============================================================================

class GrammarAnalyzer {
public:
    // Determine if a phrase is deterministic or requires semantic fallback
    struct DeterminismAnalysis {
        bool is_deterministic{true};
        std::optional<std::string> reason_for_ambiguity;
        size_t candidate_count{1};  // Number of valid parses
    };
    
    static DeterminismAnalysis analyze_phrase(
        const std::vector<std::string>& tokens,
        const CommandRegistry& registry
    );
};

// ============================================================================
// SemiNaturalGrammarBuilder — Build grammar from verb mappings
// ============================================================================

class SemiNaturalGrammarBuilder {
public:
    // Add rules for a verb with optional subject inference
    void add_verb_rule(
        std::string verb,
        GrammarKind kind = GrammarKind::kSemiNatural,
        int priority = 0,
        std::optional<std::string> default_subject = std::nullopt
    );
    
    // Build the grammar rules
    std::vector<GrammarRule> build() const;
    
private:
    std::vector<GrammarRule> rules_;
};

}  // namespace rebuntu::shell