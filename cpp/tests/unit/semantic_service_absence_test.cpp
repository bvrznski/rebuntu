// rebuntu::shell::boundary — Semantic Service Absence Behavior Test (Phase 6.51)
//
// Prove deterministic typed commands still function when all optional Python 
// semantic services are unavailable.
//
// Key Principle: DETERMINISTIC PARSING IS ALWAYS PRIMARY
//
// When semantic fallback is disabled or unavailable:
//   - Deterministic parsing always succeeds for well-formed typed commands
//   - No semantic service call is made if deterministic parsing works
//   - Commands work without any Python/semantic infrastructure

#include <system/shell/boundary/types.hpp>
#include <system/shell/boundary/integration.hpp>
#include <cassert>
#include <iostream>

using namespace rebuntu::shell;
using namespace rebuntu::shell::boundary;

void test_parser_without_semantic_service() {
    std::cout << "[TEST] Parser works without semantic service...\n";
    
    CommandRegistry registry;
    
    CommandMetadata meta{};
    meta.canonical_name = "test";
    meta.kind = IntentKind::kVerb;
    registry.register_command(std::move(meta));
    
    parser::ParseError error{};
    CommandIntent intent{};
    
    std::vector<std::string> argv = {"rebuntu", "test"};
    
    auto result = parser::parse_argv(argv, registry, intent, error);
    
    // Verify parsing succeeded (no error)
    assert(error.message.empty());
    assert(intent.verb == "test");
    std::cout << "  Parser succeeded without any semantic service [PASS]\n";
}

void test_fallback_boundary_disabled_mode() {
    std::cout << "[TEST] kDisabled mode with null provider...\n";
    
    auto boundary = SemanticBoundaryFactory::make_boundary(
        SemanticFallbackMode::kDisabled,
        nullptr
    );
    
    CommandRegistry registry;
    
    CommandMetadata meta{};
    meta.canonical_name = "test";
    meta.kind = IntentKind::kVerb;
    registry.register_command(std::move(meta));
    
    FallbackResult result = boundary->fallback_interpret("test item", registry);
    
    assert(result.status == SemanticFallbackStatus::kNoFallbackNeeded);
    assert(!result.evidence.semantic_service_used);
    std::cout << "  kDisabled mode returns kNoFallbackNeeded without semantic service [PASS]\n";
}

void test_deterministic_boundary_null_provider() {
    std::cout << "[TEST] DeterministicFallbackBoundary with null provider...\n";
    
    auto boundary = std::make_unique<DeterministicFallbackBoundary>(nullptr);
    
    CommandRegistry registry;
    
    CommandMetadata meta{};
    meta.canonical_name = "list";
    meta.kind = IntentKind::kVerb;
    registry.register_command(std::move(meta));
    
    FallbackResult result = boundary->fallback_interpret("list items", registry);
    
    assert(result.status == SemanticFallbackStatus::kNoFallbackNeeded);
    assert(!result.evidence.semantic_service_used);
    std::cout << "  DeterministicBoundary works with null provider [PASS]\n";
}

void test_unparseable_text_with_disabled_fallback() {
    std::cout << "[TEST] Unparseable text with disabled fallback...\n";
    
    auto boundary = SemanticBoundaryFactory::make_boundary(
        SemanticFallbackMode::kDisabled,
        nullptr
    );
    
    CommandRegistry registry;
    
    FallbackResult result = boundary->fallback_interpret("show me what you got", registry);
    
    assert(result.status == SemanticFallbackStatus::kFallbackRejected);
    std::cout << "  Unparseable text with disabled fallback returns kFallbackRejected [PASS]\n";
}

void test_deterministic_consistency() {
    std::cout << "[TEST] Deterministic behavior consistency...\n";
    
    auto boundary = std::make_unique<DeterministicFallbackBoundary>(nullptr);
    
    CommandRegistry registry;
    
    CommandMetadata meta{};
    meta.canonical_name = "status";
    meta.kind = IntentKind::kVerb;
    registry.register_command(std::move(meta));
    
    FallbackResult result1 = boundary->fallback_interpret("status system", registry);
    FallbackResult result2 = boundary->fallback_interpret("status system", registry);
    
    assert(result1.status == result2.status);
    assert(result1.evidence.semantic_service_used == result2.evidence.semantic_service_used);
    assert(result1.status == SemanticFallbackStatus::kNoFallbackNeeded);
    std::cout << "  Same input produces same output (deterministic) [PASS]\n";
}

int main(int argc, char** argv) {
    (void)argc;
    (void)argv;
    
    std::cout << "\nPhase 6.51: Semantic Service Absence Behavior Test\n";
    std::cout << "====================================================\n\n";
    
    test_parser_without_semantic_service();
    test_fallback_boundary_disabled_mode();
    test_deterministic_boundary_null_provider();
    test_unparseable_text_with_disabled_fallback();
    test_deterministic_consistency();
    
    std::cout << "\nAll tests passed!\n";
    std::cout << "\nPROOF: Deterministic typed commands function correctly when\n";
    std::cout << "all optional Python semantic services are unavailable.\n";
    return 0;
}