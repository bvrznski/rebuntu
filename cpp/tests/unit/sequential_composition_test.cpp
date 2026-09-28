// rebuntu - Phase 6.43 Typed Sequential Composition Unit Tests
//
// Unit tests for the typed sequential composition module.

#include <system/command/sequential.hpp>
#include <iostream>
#include <chrono>
#include <cstring>

void test_sequential_mode_to_string() {
    std::cout << "[TEST] SequentialMode to_string...";
    
    using namespace rebuntu::command;
    
    if (to_string(rebuntu::command::SequentialMode::kStrict) != "strict") {
        std::cerr << " [FAIL - kStrict string mismatch]\n";
        return;
    }
    if (to_string(rebuntu::command::SequentialMode::kBestEffort) != "best_effort") {
        std::cerr << " [FAIL - kBestEffort string mismatch]\n";
        return;
    }
    
    std::cout << " [PASS]\n";
}

void test_step_result() {
    std::cout << "[TEST] StepResult creation...";
    
    using namespace rebuntu::command;
    using namespace rebuntu::core;
    
    StepResult result;
    result.index = 0;
    result.step_id = "step-1";
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
    StepResult failed_result;
    failed_result.status = SemanticStatus::kFailure;
    if (is_success(failed_result)) {
        std::cerr << " [FAIL - is_success should be false for failed result]\n";
        return;
    }
    
    std::cout << " [PASS]\n";
}

void test_sequential_result_factory_methods() {
    std::cout << "[TEST] SequentialResult factory methods...";
    
    using namespace rebuntu::command;
    using namespace rebuntu::core;
    
    // Create a success result
    std::vector<StepResult> success_results = {
        []() { 
            StepResult r;
            r.index = 0;
            r.step_id = "step-1";
            r.status = SemanticStatus::kSuccess;
            r.verified = true;
            r.elapsed_ms = std::chrono::milliseconds(50);
            return r;
        }(),
        []() {
            StepResult r;
            r.index = 1;
            r.step_id = "step-2";
            r.status = SemanticStatus::kSuccess;
            r.verified = true;
            r.elapsed_ms = std::chrono::milliseconds(60);
            return r;
        }()
    };
    
    auto success_result = SequentialResult::success(success_results);
    
    if (success_result.aggregate_status != rebuntu::core::SemanticStatus::kSuccess) {
        std::cerr << " [FAIL - success result status incorrect]\n";
        return;
    }
    if (!success_result.is_success()) {
        std::cerr << " [FAIL - is_success should be true for all-success sequence]\n";
        return;
    }
    if (success_result.total_duration_ms != std::chrono::milliseconds(110)) {
        std::cerr << " [FAIL - total duration calculation incorrect]\n";
        return;
    }
    
    // Test unknown result
    auto unknown_result = SequentialResult::unknown();
    if (unknown_result.aggregate_status != rebuntu::core::SemanticStatus::kUnknown) {
        std::cerr << " [FAIL - unknown status not set correctly]\n";
        return;
    }
    
    std::cout << " [PASS]\n";
}

void test_sequential_intent_creation() {
    std::cout << "[TEST] SequentialIntent creation...";
    
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
    
    auto seq = SequentialIntent::make(rebuntu::command::SequentialMode::kBestEffort, {intent1, intent2});
    
    if (seq.mode != rebuntu::command::SequentialMode::kBestEffort) {
        std::cerr << " [FAIL - mode not set correctly]\n";
        return;
    }
    if (seq.intents.size() != 2) {
        std::cerr << " [FAIL - wrong number of intents]\n";
        return;
    }
    
    // Test add_intent
    CommandIntent intent3;
    intent3.id = "intent-3";
    seq.add_intent(std::move(intent3));
    
    if (seq.intents.size() != 3) {
        std::cerr << " [FAIL - add_intent not working]\n";
        return;
    }
    
    // Test that source_context is accessible
    seq.source_context = std::optional<std::string>("test-source");
    if (!seq.source_context.has_value() || *seq.source_context != "test-source") {
        std::cerr << " [FAIL - source_context not accessible]\n";
        return;
    }
    
    std::cout << " [PASS]\n";
}

void test_sequential_builder() {
    std::cout << "[TEST] SequentialBuilder...";
    
    using namespace rebuntu::command;
    
    auto seq = SequentialBuilder(rebuntu::command::SequentialMode::kStrict)
        .add_intent(CommandIntent{})
        .with_source_context("test-context")
        .build();
    
    if (seq.mode != rebuntu::command::SequentialMode::kStrict) {
        std::cerr << " [FAIL - mode not set via builder]\n";
        return;
    }
    if (!seq.source_context.has_value()) {
        std::cerr << " [FAIL - source_context not set via builder]\n";
        return;
    }
    if (*seq.source_context != "test-context") {
        std::cerr << " [FAIL - source_context value incorrect]\n";
        return;
    }
    
    // Test multiple intents
    auto seq2 = SequentialBuilder(rebuntu::command::SequentialMode::kBestEffort)
        .add_intent(CommandIntent{})
        .add_intents({CommandIntent{}, CommandIntent{}})
        .build();
    
    if (seq2.intents.size() != 3) {
        std::cerr << " [FAIL - add_intents not working]\n";
        return;
    }
    
    std::cout << " [PASS]\n";
}

void test_error_codes_exist() {
    std::cout << "[TEST] Error codes exist...";
    
    using namespace rebuntu::command;
    
    // Compare string content using strcmp since these are char arrays
    if (strcmp(error::kSequenceEmpty, "E_SEQUENCE_EMPTY") != 0) {
        std::cerr << " [FAIL - kSequenceEmpty incorrect]\n";
        return;
    }
    if (strcmp(error::kSequencePartialSuccess, "E_SEQUENCE_PARTIAL") != 0) {
        std::cerr << " [FAIL - kSequencePartialSuccess incorrect]\n";
        return;
    }
    if (strcmp(error::kSequenceAllFailed, "E_SEQUENCE_ALL_FAILED") != 0) {
        std::cerr << " [FAIL - kSequenceAllFailed incorrect]\n";
        return;
    }
    
    std::cout << " [PASS]\n";
}

void test_sequential_result_has_failures() {
    std::cout << "[TEST] SequentialResult has_failures...";
    
    using namespace rebuntu::command;
    using namespace rebuntu::core;
    
    // All success should have no failures
    auto success_results = std::vector<StepResult>{
        []() {
            StepResult r;
            r.index = 0;
            r.status = SemanticStatus::kSuccess;
            r.verified = true;
            return r;
        }()
    };
    auto success_result = SequentialResult::success(success_results);
    
    if (success_result.has_failures()) {
        std::cerr << " [FAIL - success sequence should not have failures]\n";
        return;
    }
    
    // Partial success with one failure
    auto partial_results = std::vector<StepResult>{
        []() {
            StepResult r;
            r.index = 0;
            r.status = SemanticStatus::kSuccess;
            r.verified = true;
            return r;
        }(),
        []() {
            StepResult r;
            r.index = 1;
            r.status = SemanticStatus::kFailure;
            r.error = ::rebuntu::core::Error{"E_FAIL", "test failure"};
            return r;
        }()
    };
    auto partial_result = SequentialResult::partial_success(partial_results);
    
    if (!partial_result.has_failures()) {
        std::cerr << " [FAIL - partial sequence should have failures]\n";
        return;
    }
    
    // Test that error is accessible
    if (partial_result.steps[1].error->code != "E_FAIL") {
        std::cerr << " [FAIL - error not accessible in result]\n";
        return;
    }
    
    std::cout << " [PASS]\n";
}

int main() {
    std::cout << "=== Phase 6.43 Typed Sequential Composition Unit Tests ===\n\n";
    
    test_sequential_mode_to_string();
    test_step_result();
    test_sequential_result_factory_methods();
    test_sequential_intent_creation();
    test_sequential_builder();
    test_error_codes_exist();
    test_sequential_result_has_failures();
    
    std::cout << "\n=== All tests completed ===\n";
    return 0;
}