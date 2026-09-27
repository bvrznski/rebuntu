// rebuntu::shell::parser — Shell Command Parser with Qualifiers & Modifiers (Phase 6.4)
//
// This module provides deterministic parsing of shell commands into typed IR:
//
//   - Tokenization: Split input into lexical tokens
//   - Parsing: Map tokens to IntentKind (verb/predicate/query)
//   - Qualifier extraction: Parse execution and selection modifiers
//   - Resolution: Validate against known command vocabulary
//
// Key Principles:
//   * Parser NEVER executes any system operations
//   * Parser produces CommandIntent, not side effects
//   * Ambiguity is preserved for later resolution
//   * Qualifiers refine behavior without bypassing authorization

#pragma once

#include "types.hpp"
#include "qualifiers.hpp"
#include <string>
#include <vector>

namespace rebuntu::shell::parser {

// ============================================================================
// ParseError — Parsing failures with location information
// ============================================================================

struct ParseError {
    std::string message;
    int token_index{-1};  // Index of problematic token (if known)
};

// ============================================================================
// tokenize — Split input string into tokens respecting quotes
//
// Input: "install package 'my package'" 
// Output: ["install", "package", "my package"]
// ============================================================================

std::vector<std::string> tokenize(std::string_view input);

// ============================================================================
// parse_qualifiers — Extract qualifier options from argv
//
// Parses flags like --dry-run, --force, --all, etc. and populates a QualifierBundle.
// Returns the index after the last parsed option token.
// ============================================================================

size_t parse_qualifiers(
    const std::vector<std::string>& argv,
    size_t start_idx,
    QualifierRegistry& registry,
    QualifierBundle& out_bundle,
    ParseError& out_error
);

// ============================================================================
// apply_qualifiers_to_intent — Apply parsed qualifiers to CommandIntent
//
// Updates execution_policy and adds qualifiers to the intent's qualifier map.
// ============================================================================

void apply_qualifiers_to_intent(
    const QualifierBundle& bundle,
    CommandIntent& intent
);

// ============================================================================
// parse_argv — Parse command line arguments into CommandIntent
//
// argv is assumed to be already tokenized (no shell interpretation needed).
// The first element is the program name, commands follow.
// ============================================================================

CommandResult parse_argv(
    const std::vector<std::string>& argv,
    const CommandRegistry& registry,
    CommandIntent& out_intent,
    ParseError& out_error
);

// ============================================================================
// resolve — Resolve a parsed intent to canonical capabilities
//
// This phase:
//   - Validates intent against command registry
//   - Resolves ambiguous subjects/targets
//   - Maps verb/predicate to canonical operation/query
//
// Resolution never executes anything.
// ============================================================================

CommandResolution resolve(
    const CommandIntent& intent,
    const CommandRegistry& registry
);

}  // namespace rebuntu::shell::parser