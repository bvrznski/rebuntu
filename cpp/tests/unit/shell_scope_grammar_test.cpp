// rebuntu - Phase 6.5 Scope Grammar Unit Tests
//
// Unit tests for scope grammar and explicit scope selection.

#include "../../../src/system/shell/types.hpp"
#include "../../../src/system/shell/parser.hpp"
#include "../../../src/system/shell/qualifiers.hpp"
#include "../../../src/system/core/contracts.hpp"

#include <iostream>
#include <vector>

using namespace rebuntu::shell;
using namespace rebuntu::shell::parser;

void test_scope_qualifier_registry() {
    std::cout << "[TEST] ScopeQualifierRegistry returns scope definitions...";
    
    auto defs = ScopeQualifierRegistry::get_scope_qualifiers();
    
    if (defs.empty()) {
        std::cerr << " [FAIL - no scope qualifiers defined]\n";
        return;
    }
    
    bool found_scope_def = false;
    for (const auto& def : defs) {
        if (def.name == "scope") {
            found_scope_def = true;
            break;
        }
    }
    
    if (!found_scope_def) {
        std::cerr << " [FAIL - 'scope' qualifier not found]\n";
        return;
    }
    
    std::cout << " [PASS]\n";
}

void test_parse_valid_scopes() {
    std::cout << "[TEST] Parse valid scope values...";
    
    struct TestCase {
        std::string input;
        ScopeContext expected;
    };
    
    std::vector<TestCase> cases = {
        {"user", ScopeContext::USER},
        {"system", ScopeContext::SYSTEM},
        {"session", ScopeContext::SESSION},
        {"runtime", ScopeContext::RUNTIME},
    };
    
    for (const auto& tc : cases) {
        auto result = rebuntu::shell::ScopeQualifierRegistry::parse_scope(tc.input);
        if (!result.has_value() || *result != tc.expected) {
            std::cerr << " [FAIL - parse '" << tc.input << "' should be "
                      << rebuntu::shell::ScopeQualifierRegistry::to_scope_string(tc.expected)
                      << ", got error]\n";
            return;
        }
    }
    
    std::cout << " [PASS]\n";
}

void test_parse_invalid_scopes() {
    std::cout << "[TEST] Parse invalid scope values...";
    
    std::vector<std::string> invalid = {"invalid", "", "foo", "global"};
    
    for (const auto& s : invalid) {
        auto result = rebuntu::shell::ScopeQualifierRegistry::parse_scope(s);
        if (result.has_value()) {
            std::cerr << " [FAIL - '" << s << "' should be invalid]\n";
            return;
        }
    }
    
    std::cout << " [PASS]\n";
}

void test_is_valid_scope_value() {
    std::cout << "[TEST] ScopeQualifierRegistry::is_valid_scope_value...";
    
    if (!rebuntu::shell::ScopeQualifierRegistry::is_valid_scope_value("user")) {
        std::cerr << " [FAIL - 'user' should be valid]\n";
        return;
    }
    if (!rebuntu::shell::ScopeQualifierRegistry::is_valid_scope_value("system")) {
        std::cerr << " [FAIL - 'system' should be valid]\n";
        return;
    }
    if (rebuntu::shell::ScopeQualifierRegistry::is_valid_scope_value("invalid")) {
        std::cerr << " [FAIL - 'invalid' should not be valid]\n";
        return;
    }
    
    std::cout << " [PASS]\n";
}

void test_parser_with_explicit_scope() {
    std::cout << "[TEST] Parser handles explicit --scope option...";
    
    CommandRegistry registry;
    registry.register_command({
        .canonical_name = "test",
        .kind = IntentKind::kVerb,
        .summary = "Test command"
    });
    
    // Test: rebuntu test --scope=user
    {
        std::vector<std::string> argv = {"rebuntu", "--scope=user", "test"};
        CommandIntent intent;
        parser::ParseError error;
        
        auto result = parser::parse_argv(argv, registry, intent, error);
        
        if (result.status != rebuntu::core::SemanticStatus::kSuccess) {
            std::cerr << " [FAIL - parse with --scope=user failed: " 
                      << error.message << "]\n";
            return;
        }
        
        if (intent.scope != ScopeContext::USER) {
            std::cerr << " [FAIL - intent scope should be USER, got "
                      << static_cast<int>(intent.scope) << "]\n";
            return;
        }
    }
    
    // Test: rebuntu test --scope=system
    {
        std::vector<std::string> argv = {"rebuntu", "--scope=system", "test"};
        CommandIntent intent;
        parser::ParseError error;
        
        auto result = parser::parse_argv(argv, registry, intent, error);
        
        if (result.status != rebuntu::core::SemanticStatus::kSuccess) {
            std::cerr << " [FAIL - parse with --scope=system failed: "
                      << error.message << "]\n";
            return;
        }
        
        if (intent.scope != ScopeContext::SYSTEM) {
            std::cerr << " [FAIL - intent scope should be SYSTEM, got "
                      << static_cast<int>(intent.scope) << "]\n";
            return;
        }
    }
    
    // Test: rebuntu test --scope=invalid (should fail)
    {
        std::vector<std::string> argv = {"rebuntu", "--scope=invalid", "test"};
        CommandIntent intent;
        parser::ParseError error;
        
        auto result = parser::parse_argv(argv, registry, intent, error);
        
        if (result.status == rebuntu::core::SemanticStatus::kSuccess) {
            std::cerr << " [FAIL - parse with invalid scope should fail]\n";
            return;
        }
    }
    
    std::cout << " [PASS]\n";
}

void test_scope_grammar_syntax() {
    std::cout << "[TEST] Scope grammar syntax validation...";
    
    // Valid syntax patterns
    struct TestCase {
        std::vector<std::string> argv;
        bool should_succeed;
    };
    
    std::vector<TestCase> cases = {
        {{"rebuntu", "test"}, true},                    // No scope (default)
        {{"rebuntu", "--scope=user", "test"}, true},   // Explicit user
        {{"rebuntu", "--scope=system", "test"}, true}, // Explicit system
        {{"rebuntu", "--scope=session", "test"}, true},// Explicit session
        {{"rebuntu", "--scope=runtime", "test"}, true},// Explicit runtime
    };
    
    CommandRegistry registry;
    registry.register_command({
        .canonical_name = "test",
        .kind = IntentKind::kVerb,
        .summary = "Test command"
    });
    
    for (const auto& tc : cases) {
        CommandIntent intent;
        parser::ParseError error;
        
        auto result = parser::parse_argv(tc.argv, registry, intent, error);
        
        bool succeeded = (result.status == rebuntu::core::SemanticStatus::kSuccess);
        
        if (succeeded != tc.should_succeed) {
            std::cerr << " [FAIL - argv: ";
            for (const auto& s : tc.argv) std::cerr << s << " ";
            std::cerr << "] should_succeed=" << tc.should_succeed 
                      << ", got=" << succeeded;
            if (!succeeded) std::cerr << " error: " << error.message;
            std::cerr << "\n";
            return;
        }
    }
    
    std::cout << " [PASS]\n";
}

int main() {
    std::cout << "Phase 6.5 Scope Grammar Unit Tests\n";
    std::cout << "====================================\n\n";
    
    test_scope_qualifier_registry();
    test_parse_valid_scopes();
    test_parse_invalid_scopes();
    test_is_valid_scope_value();
    test_parser_with_explicit_scope();
    test_scope_grammar_syntax();
    
    std::cout << "\nAll scope grammar tests completed!\n";
    return 0;
}