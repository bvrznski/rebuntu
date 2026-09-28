// rebuntu::shell::semi_natural - Unit Tests (Phase 6.16)
//
// Test suite for the semi-natural command grammar parser.

#include <system/shell/types.hpp>
#include <system/shell/semi_natural.hpp>
#include <iostream>
#include <cassert>

using namespace rebuntu::shell;

void test_concise_grammar() {
    std::cout << "[TEST] Concise grammar parsing...\n";
    
    // Create a registry with some commands
    CommandRegistry registry;
    
    CommandMetadata install_meta;
    install_meta.canonical_name = "install";
    install_meta.kind = IntentKind::kVerb;
    install_meta.subject_type = "package";
    install_meta.summary = "Install a package";
    registry.register_command(std::move(install_meta));
    
    // Test: "install" "foo"
    std::vector<std::string> tokens = {"install", "foo"};
    SemiNaturalParser parser(registry);
    ParseResult result = parser.parse(tokens);
    
    assert(result.kind == GrammarKind::kConcise || result.kind == GrammarKind::kSemiNatural);
    assert(!result.diagnostics.empty() || !result.intent.verb.empty());
    
    std::cout << "  Verb: " << result.intent.verb << "\n";
    std::cout << "  Subject: " << (result.intent.subject.has_value() ? *result.intent.subject : "(none)") << "\n";
    if (result.intent.target.has_value()) {
        std::cout << "  Target: " << *result.intent.target << "\n";
    }
    std::cout << "[PASS] Concise grammar test\n\n";
}

void test_semi_natural_grammar() {
    std::cout << "[TEST] Semi-natural grammar parsing...\n";
    
    // Create a registry with service commands
    CommandRegistry registry;
    
    CommandMetadata status_meta;
    status_meta.canonical_name = "status";
    status_meta.kind = IntentKind::kQuery;
    status_meta.subject_type = "service";
    status_meta.summary = "Show service status";
    registry.register_command(std::move(status_meta));
    
    // Test: "status" "service" "nginx"
    std::vector<std::string> tokens = {"status", "service", "nginx"};
    SemiNaturalParser parser(registry);
    ParseResult result = parser.parse(tokens);
    
    assert(!result.intent.verb.empty());
    std::cout << "  Verb: " << result.intent.verb << "\n";
    if (result.intent.subject.has_value()) {
        std::cout << "  Subject: " << *result.intent.subject << "\n";
    }
    if (result.intent.target.has_value()) {
        std::cout << "  Target: " << *result.intent.target << "\n";
    }
    std::cout << "[PASS] Semi-natural grammar test\n\n";
}

void test_subject_inference() {
    std::cout << "[TEST] Subject inference...\n";
    
    GrammarRule rule;
    
    // Test verb to subject mapping
    auto package_subject = rule.default_subject_for_verb("install");
    assert(package_subject.has_value());
    assert(*package_subject == "package");
    
    auto service_subject = rule.default_subject_for_verb("start");
    assert(service_subject.has_value());
    assert(*service_subject == "service");
    
    std::cout << "  install -> " << *rule.default_subject_for_verb("install") << "\n";
    std::cout << "  start -> " << *rule.default_subject_for_verb("start") << "\n";
    std::cout << "[PASS] Subject inference test\n\n";
}

void test_determinism_analysis() {
    std::cout << "[TEST] Determinism analysis...\n";
    
    CommandRegistry registry;
    
    CommandMetadata install_meta;
    install_meta.canonical_name = "install";
    install_meta.kind = IntentKind::kVerb;
    install_meta.subject_type = "package";
    install_meta.summary = "Install a package";
    registry.register_command(std::move(install_meta));
    
    // Deterministic phrase
    std::vector<std::string> deterministic_tokens = {"install", "foo"};
    auto analysis = GrammarAnalyzer::analyze_phrase(deterministic_tokens, registry);
    
    assert(analysis.is_deterministic);
    std::cout << "  'install foo' is deterministic: " << analysis.is_deterministic << "\n";
    
    // Unknown verb
    std::vector<std::string> unknown_tokens = {"unknownverb", "foo"};
    auto analysis2 = GrammarAnalyzer::analyze_phrase(unknown_tokens, registry);
    
    assert(!analysis2.is_deterministic);
    std::cout << "  'unknownverb foo' is deterministic: " << analysis2.is_deterministic << "\n";
    if (analysis2.reason_for_ambiguity) {
        std::cout << "  Reason: " << *analysis2.reason_for_ambiguity << "\n";
    }
    std::cout << "[PASS] Determinism analysis test\n\n";
}

void test_parse_result() {
    std::cout << "[TEST] ParseResult structure...\n";
    
    ParseResult result;
    assert(result.kind == GrammarKind::kConcise);
    
    CommandIntent intent;
    intent.verb = "test";
    intent.kind = IntentKind::kVerb;
    
    result.intent = intent;
    result.diagnostics.push_back("Test diagnostic");
    
    assert(result.intent.verb == "test");
    assert(!result.diagnostics.empty());
    
    std::cout << "  ParseResult kind: " << to_string(result.kind) << "\n";
    std::cout << "  Verb: " << result.intent.verb << "\n";
    std::cout << "  Diagnostics: " << result.diagnostics.size() << " items\n";
    std::cout << "[PASS] ParseResult structure test\n\n";
}

void run_all_tests() {
    std::cout << "Phase 6.16 - Semi-Natural Grammar Parser Unit Tests\n";
    std::cout << "======================================================\n\n";
    
    test_concise_grammar();
    test_semi_natural_grammar();
    test_subject_inference();
    test_determinism_analysis();
    test_parse_result();
    
    std::cout << "======================================================\n";
    std::cout << "All tests completed successfully!\n";
}

int main() {
    run_all_tests();
    return 0;
}