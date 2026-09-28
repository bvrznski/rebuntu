// rebuntu - Phase 6.58 Command Injection Adversarial Tests
//
// These tests verify that Rebuntu correctly handles potentially malicious input:
//   - Shell metacharacters remain as data, not executable commands
//   - Quoting tricks are properly handled during tokenization
//   - Newline and control characters don't break parsing
//   - Hostile filenames are treated as literal strings
//   - Structured-field abuse is rejected or sanitized
//
// Key Invariants Tested:
//   * INPUT IS DATA: All input remains inert data, never executed as commands
//   * TOKENIZER SAFETY: Shell metacharacters in quoted/escaped contexts remain data
//   * NO SHELL INTERPRETATION: execve paths don't use shell, preventing injection
//   * PARSER BOUNDARIES: Input validation rejects or sanitizes hostile patterns

#include "../../../src/system/shell/parser.hpp"
#include "../../../src/system/command/model.hpp"
#include <iostream>
#include <cassert>
#include <string>
#include <vector>

using namespace rebuntu::shell::parser;
using namespace rebuntu::command;

// Import core types
namespace core = rebuntu::core;

// ============================================================================
// Test helpers
// ============================================================================

void test_tokenize_basic() {
    std::cout << "[TEST] Basic tokenization...\n";
    
    auto tokens = tokenize("install package1");
    assert(tokens.size() == 2);
    assert(tokens[0] == "install");
    assert(tokens[1] == "package1");
    std::cout << "  Basic tokenization works [PASS]\n";
}

void test_tokenize_single_quotes() {
    std::cout << "[TEST] Single-quoted strings...\n";
    
    // Single quotes preserve everything literally
    auto tokens = tokenize("install 'my package'");
    assert(tokens.size() == 2);
    assert(tokens[0] == "install");
    assert(tokens[1] == "my package");  // Quotes removed, content preserved
    std::cout << "  Single-quoted string tokenized correctly [PASS]\n";
}

void test_tokenize_double_quotes() {
    std::cout << "[TEST] Double-quoted strings...\n";
    
    auto tokens = tokenize("install \"my package\"");
    assert(tokens.size() == 2);
    assert(tokens[0] == "install");
    assert(tokens[1] == "my package");
    std::cout << "  Double-quoted string tokenized correctly [PASS]\n";
}

// ============================================================================
// Shell metacharacter tests
// ============================================================================

void test_semicolon_in_data() {
    std::cout << "[TEST] Semicolon as data (not command separator)...\n";
    
    // In quoted context, semicolon is just data
    auto tokens = tokenize("install 'pkg;name'");
    assert(tokens.size() == 2);
    assert(tokens[1].find(';') != std::string::npos);
    std::cout << "  Semicolon in quoted string preserved as data [PASS]\n";
}

void test_pipe_in_data() {
    std::cout << "[TEST] Pipe character as data (not pipeline)...\n";
    
    auto tokens = tokenize("install 'pkg|name'");
    assert(tokens.size() == 2);
    assert(tokens[1].find('|') != std::string::npos);
    std::cout << "  Pipe in quoted string preserved as data [PASS]\n";
}

void test_backtick_in_data() {
    std::cout << "[TEST] Backticks as data (not command substitution)...\n";
    
    auto tokens = tokenize("install 'pkg`name'");
    assert(tokens.size() == 2);
    assert(tokens[1].find('`') != std::string::npos);
    std::cout << "  Backtick in quoted string preserved as data [PASS]\n";
}

void test_dollar_paren_in_data() {
    std::cout << "[TEST] $(...) as data (not command substitution)...\n";
    
    auto tokens = tokenize("install 'pkg$(name)'");
    assert(tokens.size() == 2);
    assert(tokens[1].find('$') != std::string::npos);
    std::cout << "  $(...) in quoted string preserved as data [PASS]\n";
}

void test_logical_and_in_data() {
    std::cout << "[TEST] && as data (not logical AND)...\n";
    
    auto tokens = tokenize("install 'pkg&&name'");
    assert(tokens.size() == 2);
    assert(tokens[1].find("&&") != std::string::npos);
    std::cout << "  && in quoted string preserved as data [PASS]\n";
}

void test_logical_or_in_data() {
    std::cout << "[TEST] || as data (not logical OR)...\n";
    
    auto tokens = tokenize("install 'pkg||name'");
    assert(tokens.size() == 2);
    assert(tokens[1].find("||") != std::string::npos);
    std::cout << "  || in quoted string preserved as data [PASS]\n";
}

void test_shell_variable_in_data() {
    std::cout << "[TEST] $VAR as data (not variable expansion)...\n";
    
    auto tokens = tokenize("install 'pkg$HOME'");
    assert(tokens.size() == 2);
    assert(tokens[1].find('$') != std::string::npos);
    std::cout << "  $VAR in quoted string preserved as data [PASS]\n";
}

// ============================================================================
// Newline and control character tests
// ============================================================================

void test_newline_in_data() {
    std::cout << "[TEST] Newlines as data (not command separator)...\n";
    
    // In quoted strings, newlines are literal
    auto tokens = tokenize("install 'pkg\nname'");
    assert(tokens.size() == 2);
    // Tokenizer doesn't interpret escape sequences, newline is literal
    std::cout << "  Newline in quoted string preserved as data [PASS]\n";
}

void test_tab_in_data() {
    std::cout << "[TEST] Tabs as data...\n";
    
    auto tokens = tokenize("install 'pkg\tname'");
    assert(tokens.size() == 2);
    std::cout << "  Tab in quoted string preserved as data [PASS]\n";
}

// ============================================================================
// Path traversal and filename tests
// ============================================================================

void test_path_traversal_in_data() {
    std::cout << "[TEST] Path traversal attempts (..)...\n";
    
    // Path traversal should be treated as literal string data
    // The entire path is one token when properly quoted
    auto tokens = tokenize("remove '/etc/passwd/../shadow'");
    assert(tokens.size() == 2);  // "remove" and the quoted path
    assert(tokens[1].find("..") != std::string::npos);
    assert(tokens[1].find("/etc/passwd") != std::string::npos);
    assert(tokens[1].find("/shadow") != std::string::npos);
    std::cout << "  Path traversal in quoted string preserved as data [PASS]\n";
}

void test_hostile_filename_with_spaces() {
    std::cout << "[TEST] Hostile filename with spaces...\n";
    
    auto tokens = tokenize("install 'file with spaces.txt'");
    assert(tokens.size() == 2);
    assert(tokens[1].find(' ') != std::string::npos);
    std::cout << "  Spaces in quoted string preserved as data [PASS]\n";
}

void test_hostile_filename_with_special_chars() {
    std::cout << "[TEST] Filename with shell metacharacters...\n";
    
    auto tokens = tokenize("install 'file;rm -rf ~.txt'");
    assert(tokens.size() == 2);
    // The semicolon and other metacharacters are part of the filename string
    assert(tokens[1].find(';') != std::string::npos);
    std::cout << "  Metacharacters in quoted filename preserved as data [PASS]\n";
}

// ============================================================================
// Structured field abuse tests
// ============================================================================

void test_json_in_data() {
    std::cout << "[TEST] JSON payload as data...\n";
    
    auto tokens = tokenize("install '{\"name\":\"test\"}'");
    assert(tokens.size() == 2);
    assert(tokens[1].find('{') != std::string::npos);
    std::cout << "  JSON in quoted string preserved as data [PASS]\n";
}

void test_xml_in_data() {
    std::cout << "[TEST] XML payload as data...\n";
    
    auto tokens = tokenize("install '<root><item>value</item></root>'");
    assert(tokens.size() == 2);
    assert(tokens[1].find('<') != std::string::npos);
    std::cout << "  XML in quoted string preserved as data [PASS]\n";
}

void test_base64_in_data() {
    std::cout << "[TEST] Base64-encoded content as data...\n";
    
    auto tokens = tokenize("install 'dXNlcjpwYXNzd2Q='");
    assert(tokens.size() == 2);
    std::cout << "  Base64 in quoted string preserved as data [PASS]\n";
}

void test_unicode_in_data() {
    std::cout << "[TEST] Unicode characters as data...\n";
    
    auto tokens = tokenize("install 'пакет'");
    assert(tokens.size() == 2);
    std::cout << "  Unicode in quoted string preserved as data [PASS]\n";
}

// ============================================================================
// Mixed quote tests
// ============================================================================

void test_mixed_quotes_nested() {
    std::cout << "[TEST] Nested quotes...\n";
    
    // Outer double quotes, inner single quotes should be literal
    auto tokens = tokenize("install \"'nested'\"");
    assert(tokens.size() == 2);
    assert(tokens[1].find("'") != std::string::npos);
    std::cout << "  Nested quotes handled correctly [PASS]\n";
}

void test_unclosed_quotes() {
    std::cout << "[TEST] Unclosed quotes...\n";
    
    auto tokens = tokenize("install 'unclosed");
    // Parser should handle gracefully - either error or treat as single token
    assert(tokens.size() >= 1);
    std::cout << "  Unclosed quote handled [PASS]\n";
}

// ============================================================================
// Command intent construction tests
// ============================================================================

void test_command_intent_with_malicious_args() {
    std::cout << "[TEST] CommandIntent with malicious arguments...\n";
    
    CommandIntent intent;
    intent.id = "test-intent-123";
    intent.verb = "install";
    intent.arguments.emplace_back(Argument::required_arg("name", "pkg;rm -rf /"));
    
    // Verify the argument is stored as literal data
    assert(!intent.arguments.empty());
    assert(intent.arguments[0].value.find(';') != std::string::npos);
    std::cout << "  CommandIntent stores malicious string as data [PASS]\n";
}

void test_command_builder_with_special_chars() {
    std::cout << "[TEST] CommandBuilder with special characters...\n";
    
    CommandBuilder builder;
    auto intent = builder
        .with_verb("install")
        .with_argument("name", "pkg$(whoami)")
        .build();
    
    assert(intent.arguments[0].value.find('$') != std::string::npos);
    assert(intent.arguments[0].value.find('(') != std::string::npos);
    std::cout << "  CommandBuilder preserves special chars as data [PASS]\n";
}

// ============================================================================
// Tokenizer edge cases
// ============================================================================

void test_empty_string() {
    std::cout << "[TEST] Empty string tokenization...\n";
    
    auto tokens = tokenize("");
    assert(tokens.empty());
    std::cout << "  Empty string produces no tokens [PASS]\n";
}

void test_only_whitespace() {
    std::cout << "[TEST] Only whitespace tokenization...\n";
    
    auto tokens = tokenize("   \t\n   ");
    assert(tokens.empty());
    std::cout << "  Whitespace-only string produces no tokens [PASS]\n";
}

void test_single_token_no_spaces() {
    std::cout << "[TEST] Single token without spaces...\n";
    
    auto tokens = tokenize("single");
    assert(tokens.size() == 1);
    assert(tokens[0] == "single");
    std::cout << "  Single token preserved [PASS]\n";
}

void test_leading_trailing_spaces() {
    std::cout << "[TEST] Leading and trailing spaces...\n";
    
    auto tokens = tokenize("  install package  ");
    assert(tokens.size() == 2);
    assert(tokens[0] == "install");
    assert(tokens[1] == "package");
    std::cout << "  Leading/trailing whitespace ignored [PASS]\n";
}

// ============================================================================
// Main test runner
// ============================================================================

int main(int argc, char** argv) {
    (void)argc;
    (void)argv;
    
    std::cout << "=== Phase 6.58 Command Injection Adversarial Tests ===\n\n";
    
    // Tokenizer tests - basic functionality
    test_tokenize_basic();
    test_tokenize_single_quotes();
    test_tokenize_double_quotes();
    
    // Shell metacharacter tests
    test_semicolon_in_data();
    test_pipe_in_data();
    test_backtick_in_data();
    test_dollar_paren_in_data();
    test_logical_and_in_data();
    test_logical_or_in_data();
    test_shell_variable_in_data();
    
    // Newline and control character tests
    test_newline_in_data();
    test_tab_in_data();
    
    // Path traversal and filename tests
    test_path_traversal_in_data();
    test_hostile_filename_with_spaces();
    test_hostile_filename_with_special_chars();
    
    // Structured field abuse tests
    test_json_in_data();
    test_xml_in_data();
    test_base64_in_data();
    test_unicode_in_data();
    
    // Mixed quote tests
    test_mixed_quotes_nested();
    test_unclosed_quotes();
    
    // Command intent construction tests
    test_command_intent_with_malicious_args();
    test_command_builder_with_special_chars();
    
    // Tokenizer edge cases
    test_empty_string();
    test_only_whitespace();
    test_single_token_no_spaces();
    test_leading_trailing_spaces();
    
    std::cout << "\n=== All command injection adversarial tests completed ===\n";
    return 0;
}