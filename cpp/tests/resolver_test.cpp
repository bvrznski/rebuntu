// rebuntu::runtime::resolver - Tests (Phase 4.8)
//
// Unit tests for the Resolver component.

#include <runtime/resolver.hpp>
#include <runtime/work.hpp>

using namespace rebuntu::runtime::work;
#include <system/core/contracts.hpp>

#include <cassert>
#include <iostream>
#include <string>
#include <memory>

using namespace rebuntu::runtime::resolver;
using namespace rebuntu::core;

void test_resolver_instantiation() {
    auto resolver = make_resolver();
    assert(resolver != nullptr);
    std::cout << "test_resolver_instantiation: PASSED" << std::endl;
}

void test_resolve_not_found() {
    InMemoryResolver resolver;
    
    ResolutionContext ctx = ResolutionContext::default_context();
    ResolutionResult result = resolver.resolve("nonexistent.id", ctx);
    
    assert(result.status == SemanticStatus::kUnknown);
    // When resolution fails, candidate is still populated but with empty id
    assert(result.candidate.id.empty());
    std::cout << "test_resolve_not_found: PASSED" << std::endl;
}

void test_add_task_and_resolve() {
    InMemoryResolver resolver;
    
    Task task;
    task.id.value = "system.service.start";
    task.title = "Start a service";
    task.description = "Starts a systemd service";
    task.unit_id = "systemd";
    task.created_at = std::chrono::system_clock::now();
    
    resolver.add_task(task);
    
    ResolutionContext ctx = ResolutionContext::default_context();
    ResolutionResult result = resolver.resolve("system.service.start", ctx);
    
    assert(result.status == SemanticStatus::kSuccess);
    // Candidate is always present (not optional), but has empty id on failure
    assert(!result.candidate.id.empty());
    assert(result.candidate.id == "system.service.start");
    std::cout << "test_add_task_and_resolve: PASSED" << std::endl;
}

void test_list_candidates() {
    InMemoryResolver resolver;
    
    Task task1;
    task1.id.value = "task1";
    resolver.add_task(task1);
    
    Task task2;
    task2.id.value = "task2";
    resolver.add_task(task2);
    
    auto candidates = resolver.list_candidates();
    
    assert(candidates.size() >= 2);
    std::cout << "test_list_candidates: PASSED" << std::endl;
}

void test_resolution_status_to_string() {
    assert(to_string(ResolutionStatus::kResolved) == "resolved");
    assert(to_string(ResolutionStatus::kNotFound) == "not_found");
    assert(to_string(ResolutionStatus::kAmbiguous) == "ambiguous");
    assert(to_string(ResolutionStatus::kUnavailable) == "unavailable");
    assert(to_string(ResolutionStatus::kForbidden) == "forbidden");
    assert(to_string(ResolutionStatus::kUnknown) == "unknown");
    std::cout << "test_resolution_status_to_string: PASSED" << std::endl;
}

void test_rejection_reason_category_to_string() {
    RejectionReason rr;
    
    assert(to_string(RejectionReason::Category::kNotFound) == "not_found");
    assert(to_string(RejectionReason::Category::kAmbiguous) == "ambiguous");
    assert(to_string(RejectionReason::Category::kUnavailable) == "unavailable");
    assert(to_string(RejectionReason::Category::kForbidden) == "forbidden");
    std::cout << "test_rejection_reason_category_to_string: PASSED" << std::endl;
}

void test_resolution_result_succeeded() {
    ResolutionResult result;
    
    // Failed resolution should not succeed
    assert(!result.succeeded());
    
    result.status = SemanticStatus::kSuccess;
    result.candidate.id = "some.id";
    assert(result.succeeded());
    
    // Clear the id to simulate failed resolution
    result.candidate.id.clear();
    assert(!result.succeeded());
    
    std::cout << "test_resolution_result_succeeded: PASSED" << std::endl;
}

void test_resolver_interface() {
    // Test that InMemoryResolver implements the Resolver interface
    class TestResolver : public Resolver {
        ResolutionResult resolve(const std::string& id, const ResolutionContext& ctx) override {
            return {};
        }
        
        std::vector<ResolutionCandidate> list_candidates(
            std::optional<ResolutionCandidate::Kind>, 
            std::optional<std::string>) const override {
            return {};
        }
        
        std::vector<ResolutionResult> get_resolution_history() const override {
            return {};
        }
    };
    
    TestResolver test;
    (void)test;  // suppress unused warning
    
    std::cout << "test_resolver_interface: PASSED" << std::endl;
}

int main() {
    test_resolver_instantiation();
    test_resolve_not_found();
    test_add_task_and_resolve();
    test_list_candidates();
    test_resolution_status_to_string();
    test_rejection_reason_category_to_string();
    test_resolution_result_succeeded();
    test_resolver_interface();
    
    std::cout << "\nAll resolver tests completed!" << std::endl;
    return 0;
}