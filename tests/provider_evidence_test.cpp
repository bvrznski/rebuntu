// Test for provider_evidence.hpp - Task 6.52 Provider Result Distrust

#include <adapters/provider_evidence.hpp>
#include <system/core/contracts.hpp>
#include <cassert>
#include <iostream>
#include <string>

using namespace rebuntu::adapters;
using namespace rebuntu::core;

void test_provider_evidence_state() {
    auto evidence = ProviderEvidence::state(
        "service:apache2",
        "running",
        "systemd"
    );
    
    assert(evidence.subject == "service:apache2");
    assert(evidence.observation == "running");
    assert(evidence.source == "systemd");
    assert(evidence.category == ProviderEvidence::Category::kState);
    std::cout << "test_provider_evidence_state: PASS\n";
}

void test_provider_evidence_property() {
    auto evidence = ProviderEvidence::property(
        "service:ssh",
        "enabled",
        "systemd"
    );
    
    assert(evidence.subject == "service:ssh");
    assert(evidence.observation == "enabled");
    assert(evidence.category == ProviderEvidence::Category::kProperty);
    std::cout << "test_provider_evidence_property: PASS\n";
}

void test_provider_evidence_permission() {
    auto evidence_granted = ProviderEvidence::permission(
        "/etc/passwd",
        true,
        "kernel"
    );
    
    assert(evidence_granted.observation == "access_granted");
    
    auto evidence_denied = ProviderEvidence::permission(
        "/root/.ssh/authorized_keys",
        false,
        "kernel"
    );
    
    assert(evidence_denied.observation == "access_denied");
    std::cout << "test_provider_evidence_permission: PASS\n";
}

void test_provider_evidence_presence() {
    auto evidence_exists = ProviderEvidence::presence(
        "/etc/hosts",
        true,
        "filesystem"
    );
    
    assert(evidence_exists.observation == "exists");
    
    auto evidence_not_found = ProviderEvidence::presence(
        "/nonexistent/file",
        false,
        "filesystem"
    );
    
    assert(evidence_not_found.observation == "not_found");
    std::cout << "test_provider_evidence_presence: PASS\n";
}

void test_provider_result_success() {
    struct TestData { int value; };
    
    auto result = ProviderResult<TestData>::success(
        TestData{42},
        {},
        std::chrono::milliseconds(10)
    );
    
    assert(result.status == SemanticStatus::kSuccess);
    assert(result.has_value());
    assert((*result.value).value == 42);
    assert(result.elapsed_ms.count() == 10);
    assert(result.evidence.empty());
    std::cout << "test_provider_result_success: PASS\n";
}

void test_provider_result_completed() {
    auto result = ProviderResult<int>::completed(
        100,
        {},
        std::chrono::milliseconds(5)
    );
    
    assert(result.status == SemanticStatus::kCompleted);
    assert(result.has_value());
    assert(*result.value == 100);
    std::cout << "test_provider_result_completed: PASS\n";
}

void test_provider_result_failure() {
    auto result = ProviderResult<void>::failure(
        "E_PERMISSION",
        "Access denied",
        {},
        std::chrono::milliseconds(2)
    );
    
    assert(result.status == SemanticStatus::kFailure);
    assert(!result.has_value());
    assert(!result.errors.empty());
    assert(result.errors.front().second.code == "E_PERMISSION");
    std::cout << "test_provider_result_failure: PASS\n";
}

void test_provider_result_unknown() {
    auto result = ProviderResult<std::string>::unknown(
        "Could not determine state",
        {},
        std::chrono::milliseconds(15)
    );
    
    assert(result.status == SemanticStatus::kUnknown);
    assert(!result.has_value());
    assert(!result.errors.empty());
    std::cout << "test_provider_result_unknown: PASS\n";
}

void test_provider_result_cancelled() {
    auto result = ProviderResult<void>::cancelled(
        "Operation was cancelled",
        std::chrono::milliseconds(3)
    );
    
    assert(result.status == SemanticStatus::kCancelled);
    std::cout << "test_provider_result_cancelled: PASS\n";
}

void test_evidence_to_string() {
    auto evidence = ProviderEvidence::state(
        "service:test",
        "running",
        "systemd"
    );
    
    std::string s = to_string(evidence);
    assert(!s.empty());
    assert(s.find("service:test") != std::string::npos);
    std::cout << "test_evidence_to_string: PASS\n";
}

void test_result_to_string() {
    auto result = ProviderResult<int>::success(
        42,
        {},
        std::chrono::milliseconds(5)
    );
    
    std::string s = to_string(result);
    assert(!s.empty());
    // Note: core::to_string(SemanticStatus) returns lowercase like "success"
    assert(s.find("success") != std::string::npos);
    std::cout << "test_result_to_string: PASS\n";
}

void test_evidence_add() {
    ProviderResult<int> result;
    auto evidence1 = ProviderEvidence::state("svc:a", "running", "systemd");
    auto evidence2 = ProviderEvidence::property("svc:a", "enabled", "systemd");
    
    result.add_evidence(std::move(evidence1));
    result.add_evidence(std::move(evidence2));
    
    assert(result.evidence.size() == 2);
    std::cout << "test_evidence_add: PASS\n";
}

int main() {
    test_provider_evidence_state();
    test_provider_evidence_property();
    test_provider_evidence_permission();
    test_provider_evidence_presence();
    test_provider_result_success();
    test_provider_result_completed();
    test_provider_result_failure();
    test_provider_result_unknown();
    test_provider_result_cancelled();
    test_evidence_to_string();
    test_result_to_string();
    test_evidence_add();
    
    std::cout << "\n=== All provider_evidence tests passed! ===\n";
    return 0;
}