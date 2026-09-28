// rebuntu - Phase 6.17 Semantic Boundary Unit Tests
//
// Unit tests for the semantic interpretation boundary:
//   - Deterministic parsing always wins when unambiguous
//   - Semantic fallback only used when deterministic fails
//   - All semantic candidates validated against canonical vocabulary

#include <system/shell/boundary/types.hpp>
#include <system/shell/boundary/integration.hpp>
#include <iostream>
#include <cassert>

using namespace rebuntu::shell;
using namespace rebuntu::shell::boundary;

void test_deterministic_wins() {
    std::cout << "[TEST] Deterministic parsing wins when unambiguous...\n";
    
    auto boundary = SemanticBoundaryFactory::make_default_boundary();
    
    CommandRegistry registry;
    CommandMetadata meta{};
    meta.canonical_name = "install";
    meta.kind = IntentKind::kVerb;
    registry.register_command(std::move(meta));
    
    FallbackResult result = boundary->fallback_interpret("install foo", registry);
    
    assert(result.status == SemanticFallbackStatus::kNoFallbackNeeded);
    std::cout << "  Deterministic parsing succeeded, no fallback needed [PASS]\n";
}

void test_fallback_disabled() {
    std::cout << "[TEST] Fallback disabled returns rejected...\n";
    
    auto boundary = std::make_unique<DeterministicFallbackBoundary>();
    boundary->set_fallback_mode(SemanticFallbackMode::kDisabled);
    
    CommandRegistry registry;
    
    // Unknown verb - deterministic parsing will fail
    FallbackResult result = boundary->fallback_interpret("unknownverb foo", registry);
    
    assert(result.status == SemanticFallbackStatus::kFallbackRejected);
    std::cout << "  Fallback disabled correctly rejected [PASS]\n";
}

void test_scope_validation() {
    std::cout << "[TEST] Scope validation...\n";
    
    auto boundary = std::make_unique<DeterministicFallbackBoundary>();
    
    CommandIntent intent{};
    intent.verb = "install";
    intent.scope = ScopeContext::USER;
    
    CommandRegistry registry;
    CommandMetadata meta{};
    meta.canonical_name = "install";
    meta.kind = IntentKind::kVerb;
    registry.register_command(std::move(meta));
    
    assert(boundary->validate_candidate(intent, registry));
    std::cout << "  Valid scope accepted [PASS]\n";
}

void test_invalid_scope_rejected() {
    std::cout << "[TEST] Invalid scope rejected...\n";
    
    auto boundary = std::make_unique<DeterministicFallbackBoundary>();
    
    CommandIntent intent{};
    intent.verb = "install";
    intent.scope = static_cast<ScopeContext>(999);
    
    CommandRegistry registry;
    CommandMetadata meta{};
    meta.canonical_name = "install";
    meta.kind = IntentKind::kVerb;
    registry.register_command(std::move(meta));
    
    assert(!boundary->validate_candidate(intent, registry));
    std::cout << "  Invalid scope rejected [PASS]\n";
}

void test_unknown_verb_rejected() {
    std::cout << "[TEST] Unknown verb rejected...\n";
    
    auto boundary = std::make_unique<DeterministicFallbackBoundary>();
    
    CommandIntent intent{};
    intent.verb = "unknown_verb";
    
    CommandRegistry registry;
    CommandMetadata meta{};
    meta.canonical_name = "install";
    meta.kind = IntentKind::kVerb;
    registry.register_command(std::move(meta));
    
    assert(!boundary->validate_candidate(intent, registry));
    std::cout << "  Unknown verb rejected [PASS]\n";
}

void test_explicit_mode() {
    std::cout << "[TEST] Explicit mode boundary...\n";
    
    auto boundary = std::make_unique<ExplicitModeSemanticBoundary>();
    
    assert(boundary->fallback_mode() == SemanticFallbackMode::kExplicitOnly);
    std::cout << "  Explicit mode returns kExplicitOnly [PASS]\n";
}

void test_factory_default() {
    std::cout << "[TEST] Factory default boundary...\n";
    
    auto boundary = SemanticBoundaryFactory::make_default_boundary();
    
    assert(boundary->fallback_mode() == SemanticFallbackMode::kOnFailure);
    std::cout << "  Default mode is kOnFailure [PASS]\n";
}

void test_factory_disabled() {
    std::cout << "[TEST] Factory disabled boundary...\n";
    
    auto boundary = SemanticBoundaryFactory::make_boundary(
        SemanticFallbackMode::kDisabled, nullptr
    );
    
    assert(boundary->fallback_mode() == SemanticFallbackMode::kDisabled);
    std::cout << "  Disabled mode correctly configured [PASS]\n";
}

int main(int argc, char** argv) {
    (void)argc;
    (void)argv;
    std::cout << "\nPhase 6.17: Shell Boundary Unit Tests\n";
    std::cout << "========================================\n\n";
    
    test_deterministic_wins();
    test_fallback_disabled();
    test_scope_validation();
    test_invalid_scope_rejected();
    test_unknown_verb_rejected();
    test_explicit_mode();
    test_factory_default();
    test_factory_disabled();
    
    std::cout << "\nAll tests passed!\n\n";
    return 0;
}