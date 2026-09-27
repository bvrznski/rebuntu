// rebuntu - Phase 6.1 Typed Command Model Unit Tests
//
// Unit tests for the typed command model module.

#include <system/command/model.hpp>
#include <system/core/contracts.hpp>
#include <iostream>

using namespace rebuntu::command;

void test_semantic_kind_to_string() {
    std::cout << "[TEST] SemanticKind to_string...";
    
    if (to_string(SemanticKind::QUERY) != "query") {
        std::cerr << " [FAIL - QUERY string mismatch]\n";
        return;
    }
    if (to_string(SemanticKind::OBSERVE) != "observe") {
        std::cerr << " [FAIL - OBSERVE string mismatch]\n";
        return;
    }
    if (to_string(SemanticKind::CONFIGURE) != "configure") {
        std::cerr << " [FAIL - CONFIGURE string mismatch]\n";
        return;
    }
    
    std::cout << " [PASS]\n";
}

void test_scope_context_to_string() {
    std::cout << "[TEST] ScopeContext to_string...";
    
    if (to_string(ScopeContext::USER) != "user") {
        std::cerr << " [FAIL - USER string mismatch]\n";
        return;
    }
    if (to_string(ScopeContext::SYSTEM) != "system") {
        std::cerr << " [FAIL - SYSTEM string mismatch]\n";
        return;
    }
    if (to_string(ScopeContext::SESSION) != "session") {
        std::cerr << " [FAIL - SESSION string mismatch]\n";
        return;
    }
    
    std::cout << " [PASS]\n";
}

void test_side_effect_class_to_string() {
    std::cout << "[TEST] SideEffectClass to_string...";
    
    if (to_string(SideEffectClass::NONE) != "none") {
        std::cerr << " [FAIL - NONE string mismatch]\n";
        return;
    }
    if (to_string(SideEffectClass::OBSERVATION) != "observation") {
        std::cerr << " [FAIL - OBSERVATION string mismatch]\n";
        return;
    }
    if (to_string(SideEffectClass::MUTATING) != "mutating") {
        std::cerr << " [FAIL - MUTATING string mismatch]\n";
        return;
    }
    
    std::cout << " [PASS]\n";
}

void test_target_reference_creation() {
    std::cout << "[TEST] TargetReference creation...";
    
    TargetReference ref;
    ref.kind = "package";
    ref.id = "apt:curl";
    ref.name = "curl";
    ref.path = "/usr/bin/curl";
    
    if (ref.kind != "package") {
        std::cerr << " [FAIL - kind not set]\n";
        return;
    }
    if (!ref.id.has_value() || *ref.id != "apt:curl") {
        std::cerr << " [FAIL - id not set correctly]\n";
        return;
    }
    
    std::cout << " [PASS]\n";
}

void test_argument_creation() {
    std::cout << "[TEST] Argument creation...";
    
    auto required = Argument::required_arg("package", "curl");
    auto optional = Argument::optional_arg("version", "7.68.0");
    
    if (!required.required) {
        std::cerr << " [FAIL - required flag not set]\n";
        return;
    }
    if (optional.required) {
        std::cerr << " [FAIL - optional flag incorrectly set]\n";
        return;
    }
    
    std::cout << " [PASS]\n";
}

void test_qualifier_creation() {
    std::cout << "[TEST] Qualifier creation...";
    
    auto flag = Qualifier::flag("dry_run");
    auto with_value = Qualifier::with_value("timeout", "30s");
    
    if (with_value.value.has_value()) {
        std::cout << " [PASS]\n";
        return;
    }
    
    std::cerr << " [FAIL - value qualifier not set correctly]\n";
}

void test_execution_policy() {
    std::cout << "[TEST] ExecutionPolicy creation...";
    
    auto policy = ExecutionPolicy::default_policy();
    
    if (policy.dry_run) {
        std::cerr << " [FAIL - dry_run should be false by default]\n";
        return;
    }
    if (!policy.verify) {
        std::cerr << " [FAIL - verify should be true by default]\n";
        return;
    }
    
    auto dry_run_policy = ExecutionPolicy::dry_run_only();
    if (!dry_run_policy.dry_run) {
        std::cerr << " [FAIL - dry_run_only should enable dry_run]\n";
        return;
    }
    
    std::cout << " [PASS]\n";
}

void test_command_intent_creation() {
    std::cout << "[TEST] CommandIntent creation...";
    
    CommandIntent intent;
    intent.id = "test-intent-123";
    intent.semantic_kind = SemanticKind::QUERY;
    intent.verb = "status";
    intent.scope = ScopeContext::SYSTEM;
    
    if (intent.id != "test-intent-123") {
        std::cerr << " [FAIL - id not set]\n";
        return;
    }
    if (intent.semantic_kind != SemanticKind::QUERY) {
        std::cerr << " [FAIL - semantic_kind not set]\n";
        return;
    }
    
    std::cout << " [PASS]\n";
}

void test_resolution_status_to_string() {
    std::cout << "[TEST] ResolutionStatus to_string...";
    
    if (to_string(ResolutionStatus::kSuccess) != "success") {
        std::cerr << " [FAIL - kSuccess string mismatch]\n";
        return;
    }
    if (to_string(ResolutionStatus::kAmbiguous) != "ambiguous") {
        std::cerr << " [FAIL - kAmbiguous string mismatch]\n";
        return;
    }
    
    std::cout << " [PASS]\n";
}

void test_capability_reference() {
    std::cout << "[TEST] CapabilityReference creation...";
    
    auto cap = CapabilityReference::make("package", "install");
    
    if (cap.domain != "package") {
        std::cerr << " [FAIL - domain not set]\n";
        return;
    }
    if (cap.operation != "install") {
        std::cerr << " [FAIL - operation not set]\n";
        return;
    }
    
    std::cout << " [PASS]\n";
}

void test_command_resolution() {
    std::cout << "[TEST] CommandResolution creation...";
    
    auto cap = CapabilityReference::make("package", "install");
    auto resolution = CommandResolution::success(cap);
    
    if (resolution.status != ResolutionStatus::kSuccess) {
        std::cerr << " [FAIL - status not success]\n";
        return;
    }
    if (!resolution.capability.has_value()) {
        std::cerr << " [FAIL - capability not set]\n";
        return;
    }
    
    auto unknown_verb = CommandResolution::unknown_verb("nonexistent");
    if (unknown_verb.status != ResolutionStatus::kUnknownVerb) {
        std::cerr << " [FAIL - unknown verb status incorrect]\n";
        return;
    }
    
    std::cout << " [PASS]\n";
}

void test_command_builder() {
    std::cout << "[TEST] CommandBuilder...";
    
    CommandBuilder builder;
    auto intent = builder
        .with_kind(SemanticKind::CREATE)
        .with_verb("install")
        .with_subject("package", "apt:curl", "curl", "/usr/bin/curl")
        .with_argument("version", "7.68.0")
        .with_qualifier("dry_run")
        .with_scope(ScopeContext::SYSTEM)
        .build();
    
    if (intent.semantic_kind != SemanticKind::CREATE) {
        std::cerr << " [FAIL - semantic_kind not set via builder]\n";
        return;
    }
    if (intent.verb != "install") {
        std::cerr << " [FAIL - verb not set via builder]\n";
        return;
    }
    if (intent.scope != ScopeContext::SYSTEM) {
        std::cerr << " [FAIL - scope not set via builder]\n";
        return;
    }
    
    std::cout << " [PASS]\n";
}

void test_command_result() {
    using namespace rebuntu::core;
    
    std::cout << "[TEST] CommandResult creation...";
    
    auto success = CommandResult::success(true, true);
    if (success.status != SemanticStatus::kSuccess) {
        std::cerr << " [FAIL - status not set]\n";
        return;
    }
    if (!success.is_success()) {
        std::cerr << " [FAIL - is_success should be true]\n";
        return;
    }
    
    auto no_change = CommandResult::no_change();
    if (no_change.changed) {
        std::cerr << " [FAIL - no_change should have changed=false]\n";
        return;
    }
    
    auto failure = CommandResult::failure("E_TEST", "test error");
    if (failure.status != SemanticStatus::kFailure) {
        std::cerr << " [FAIL - failure status not set]\n";
        return;
    }
    
    std::cout << " [PASS]\n";
}

int main() {
    std::cout << "=== Phase 6.1 Typed Command Model Unit Tests ===\n\n";
    
    test_semantic_kind_to_string();
    test_scope_context_to_string();
    test_side_effect_class_to_string();
    test_target_reference_creation();
    test_argument_creation();
    test_qualifier_creation();
    test_execution_policy();
    test_command_intent_creation();
    test_resolution_status_to_string();
    test_capability_reference();
    test_command_resolution();
    test_command_builder();
    test_command_result();
    
    std::cout << "\n=== All tests completed ===\n";
    return 0;
}