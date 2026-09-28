// rebuntu::cli::parser — Command Parser Boundary (Task 6.46)
//
// This module defines the canonical command parser boundary:
//
//   - CLI input (argv/text) is parsed ONLY at this interface edge
//   - Output: typed shell::CommandIntent structures for domain execution
//   - Domain code receives NO strings to re-parse
//
// Design Principles:
//   * Parser is stateless and deterministic
//   * Text-to-structured conversion happens ONCE at the boundary
//   * All downstream consumers receive strongly-typed structures

#pragma once

#include <string>
#include <vector>

namespace rebuntu::shell {
struct CommandIntent;
enum class IntentKind : int;
enum class ScopeContext : int;
}  // namespace rebuntu::shell

namespace rebuntu::cli::parser {

// ============================================================================
// ParseError — Parser failures with source context
// ============================================================================

struct ParseError {
    std::string message;
    int token_index{-1};  // Index of problematic token (if known)
};

// ============================================================================
// parse_argv — Parse command line arguments into typed CommandIntent
//
// This is the parser boundary: raw argv → typed structure.
// 
// Input:  argv from main() - text tokens only
// Output: shell::CommandIntent or ParseError (no string re-parsing in domain code)
// ============================================================================

rebuntu::shell::CommandIntent parse_argv(
    const std::vector<std::string>& argv,
    ParseError& out_error
);

// ============================================================================
// tokenize — Split command line input into tokens
//
// Input:  Raw command line string
// Output: Token vector (no parsing, just lexical separation)
// ============================================================================

std::vector<std::string> tokenize(std::string_view input);

}  // namespace rebuntu::cli::parser
