// rebuntu - Phase 6.44 Typed Parallel Composition Unit Tests
//
// Unit tests for the typed parallel composition module.

#include <system/command/parallel.hpp>
#include <iostream>
#include <chrono>
#include <cstring>

void test_parallel_result_status_to_string() {
    std::cout << "[TEST] ParallelResultStatus to_string...";
    
    using namespace rebuntu::command;
    
    if (to_string(rebuntu::command::ParallelResultStatus::kUnknown) != "unknown") {
        std::cerr << " [FAIL - kUnknown string mismatch]\n";
        return;
    }
    if (to_string(rebuntu::command::ParallelResultStatus::kAllSuccess) != "all_success") {
        std::cerr << " [FAIL - kAllSuccess string mismatch]\n";
        return;
    }
    if (to_string(rebuntu::command::ParallelResultStatus::kPartialSuccess) != "partial_success") {
        std::cerr << " [FAIL - kPartialSuccess string mismatch]\n";
        return;
    }
    if (to_string(rebuntu::command::ParallelResultStatus::kAllFailed) != "all_failed") {
        std::cerr << " [FAIL - kAllFailed string mismatch]\n";
        return;
    }
    
    std::cout << " [PASS]\n";
}

void test_parallel_operation_result() {
    std::cout << "[TEST] ParallelOperationResult creation...";
    
    using namespace rebuntu::command;
    using namespace rebuntu::core;
    
    ParallelOperationResult result;
    result.index = 0;
    result.operation_id = "op-1";
    result.status = SemanticStatus::kSuccess;
    result.changed = true;
    result.verified = true;
    result.elapsed_ms = std::chrono::milliseconds(50);
    
    if (result.index != 0) {
        std::cerr << " [FAIL - index not set]\n";
        return;
    }
    if (!is_success(result)) {
        std::cerr << " [FAIL - is_success should be true]\n";
        return;
    }
    
    // Test failure case
    ParallelOperationResult failed_result;
    failed_result.status = SemanticStatus::kFailure;
    if (is_success(failed_result)) {
        std::cerr << " [FAIL - is_success should be false for failed result]\n";
        return;
    }
    
    std::cout << " [PASS]\n";
}

void test_parallel_result_factory_methods() {
    std::cout << "[TEST] ParallelResult factory methods...";
    
    using namespace rebuntu::command;
    using namespace rebuntu::core;
    
    // Create a success result
    std::vector<ParallelOperationResult> success_results = {
        []() { 
            ParallelOperationResult r;
            r.index = 0;
            r.operation_id = "op-1";
            r.status = SemanticStatus::kSuccess;
            r.verified = true;
            r.elapsed_ms = std::chrono::milliseconds(50);
            return r;
        }(),
        []() {
            ParallelOperationResult r;
            r.index = 1;
            r.operation_id = "op-2";
            r.status = SemanticStatus::kSuccess;
            r.verified = true;
            r.elapsed_ms = std::chrono::milliseconds(60);
            return r;
        }()
    };
    
    auto success_result = ParallelResult::success(success_results, 2);
    
    if (success_result.aggregate_status != rebuntu::command::ParallelResultStatus::kAllSuccess) {
        std::cerr << " [FAIL - success result status incorrect]\n";
        return;
    }
    if (!success_result.is_success()) {
        std::cerr << " [FAIL - is_success should be true for all-success parallel group]\n";
        return;
    }
    
    // Test unknown result
    auto unknown_result = ParallelResult::unknown();
    if (unknown_result.aggregate_status != rebuntu::command::ParallelResultStatus::kUnknown) {
        std::cerr << " [FAIL - unknown status not set correctly]\n";
        return;
    }
    
    std::cout << " [PASS]\n";
}

void test_parallel_intent_creation() {
    std::cout << "[TEST] ParallelIntent creation...";
    
    using namespace rebuntu::command;
    
    // Create individual intents
    CommandIntent intent1;
    intent1.id = "intent-1";
    intent1.semantic_kind = SemanticKind::QUERY;
    intent1.verb = "status";
    intent1.scope = ScopeContext::SYSTEM;
    
    CommandIntent intent2;
    intent2.id = "intent-2";
    intent2.semantic_kind = SemanticKind::OBSERVE;
    intent2.verb = "list";
    intent2.scope = ScopeContext::USER;
    
    auto parallel = ParallelIntent::make({intent1, intent2}, 4);
    
    if (parallel.max_concurrency != 4) {
        std::cerr << " [FAIL - max_concurrency not set correctly]\n";
        return;
    }
    if (parallel.intents.size() != 2) {
        std::cerr << " [FAIL - wrong number of intents]\n";
        return;
    }
    
    // Test add_intent
    CommandIntent intent3;
    intent3.id = "intent-3";
    parallel.add_intent(std::move(intent3));
    
    if (parallel.intents.size() != 3) {
        std::cerr << " [FAIL - add_intent not working]\n";
        return;
    }
    
    // Test that source_context is accessible
    parallel.source_context = std::optional<std::string>("test-source");
    if (!parallel.source_context.has_value() || *parallel.source_context != "test-source") {
        std::cerr << " [FAIL - source_context not accessible]\n";
        return;
    }
    
    std::cout << " [PASS]\n";
}

void test_parallel_builder() {
    std::cout << "[TEST] ParallelBuilder...";
    
    using namespace rebuntu::command;
    
    auto parallel = ParallelBuilder(2)
        .add_intent(CommandIntent{})
        .with_source_context("test-context")
        .build();
    
    if (parallel.max_concurrency != 2) {
        std::cerr << " [FAIL - max_concurrency not set via builder]\n";
        return;
    }
    if (!parallel.source_context.has_value()) {
        std::cerr << " [FAIL - source_context not set via builder]\n";
        return;
    }
    if (*parallel.source_context != "test-context") {
        std::cerr << " [FAIL - source_context value incorrect]\n";
        return;
    }
    
    // Test multiple intents
    auto parallel2 = ParallelBuilder(4)
        .add_intent(CommandIntent{})
        .add_intents({CommandIntent{}, CommandIntent{}})
        .build();
    
    if (parallel2.intents.size() != 3) {
        std::cerr << " [FAIL - add_intents not working]\n";
        return;
    }
    
    std::cout << " [PASS]\n";
}

void test_error_codes_exist() {
    std::cout << "[TEST] Error codes exist...";
    
    using namespace rebuntu::command;
    
    // Compare string content using strcmp since these are char arrays
    if (strcmp(error::kParallelEmpty, "E_PARALLEL_EMPTY") != 0) {
        std::cerr << " [FAIL - kParallelEmpty incorrect]\n";
        return;
    }
    if (strcmp(error::kParallelPartialSuccess, "E_PARALLEL_PARTIAL") != 0) {
        std::cerr << " [FAIL - kParallelPartialSuccess incorrect]\n";
        return;
    }
    if (strcmp(error::kParallelAllFailed, "E_PARALLEL_ALL_FAILED") != 0) {
        std::cerr << " [FAIL - kParallelAllFailed incorrect]\n";
        return;
    }
    
    std::cout << " [PASS]\n";
}

void test_parallel_result_has_failures() {
    std::cout << "[TEST] ParallelResult has_failures...";
    
    using namespace rebuntu::command;
    using namespace rebuntu::core;
    
    // All success should have no failures
    auto success_results = std::vector<ParallelOperationResult>{
        []() {
            ParallelOperationResult r;
            r.index = 0;
            r.status = SemanticStatus::kSuccess;
            r.verified = true;
            return r;
        }()
    };
    auto success_result = ParallelResult::success(success_results, 1);
    
    if (success_result.has_failures()) {
        std::cerr << " [FAIL - success parallel group should not have failures]\n";
        return;
    }
    
    // Partial success with one failure
    auto partial_results = std::vector<ParallelOperationResult>{
        []() {
            ParallelOperationResult r;
            r.index = 0;
            r.status = SemanticStatus::kSuccess;
            r.verified = true;
            return r;
        }(),
        []() {
            ParallelOperationResult r;
            r.index = 1;
            r.status = SemanticStatus::kFailure;
            r.error = Error{"E_FAIL", "test failure"};
            return r;
        }()
    };
    auto partial_result = ParallelResult::partial_success(partial_results, 2);
    
    if (!partial_result.has_failures()) {
        std::cerr << " [FAIL - partial parallel group should have failures]\n";
        return;
    }
    
    // Test that error is accessible
    if (partial_result.operations[1].error->code != "E_FAIL") {
        std::cerr << " [FAIL - error not accessible in result]\n";
        return;
    }
    
    std::cout << " [PASS]\n";
}

int main() {
    std::cout << "=== Phase 6.44 Typed Parallel Composition Unit Tests ===\n\n";
    
    test_parallel_result_status_to_string();
    test_parallel_operation_result();
    test_parallel_result_factory_methods();
    test_parallel_intent_creation();
    test_parallel_builder();
    test_error_codes_exist();
    test_parallel_result_has_failures();
    
    std::cout << "\n=== All tests completed ===\n";
    return 0;
}