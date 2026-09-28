// rebuntu - Phase 6.42 Typed Batch Command Boundary Unit Tests
//
// Unit tests for the typed batch command module.

#include <system/command/batch.hpp>
#include <iostream>
#include <chrono>
#include <cstring>

void test_batch_mode_to_string() {
    std::cout << "[TEST] BatchMode to_string...";
    
    using namespace rebuntu::command;
    
    if (to_string(rebuntu::command::BatchMode::kSequentialStrict) != "sequential_strict") {
        std::cerr << " [FAIL - kSequentialStrict string mismatch]\n";
        return;
    }
    if (to_string(rebuntu::command::BatchMode::kSequentialBestEffort) != "sequential_best_effort") {
        std::cerr << " [FAIL - kSequentialBestEffort string mismatch]\n";
        return;
    }
    if (to_string(rebuntu::command::BatchMode::kParallelIndependent) != "parallel_independent") {
        std::cerr << " [FAIL - kParallelIndependent string mismatch]\n";
        return;
    }
    
    std::cout << " [PASS]\n";
}

void test_batch_result_status_to_string() {
    std::cout << "[TEST] BatchResultStatus to_string...";
    
    using namespace rebuntu::command;
    
    if (to_string(rebuntu::command::BatchResultStatus::kUnknown) != "unknown") {
        std::cerr << " [FAIL - kUnknown string mismatch]\n";
        return;
    }
    if (to_string(rebuntu::command::BatchResultStatus::kAllSuccess) != "all_success") {
        std::cerr << " [FAIL - kAllSuccess string mismatch]\n";
        return;
    }
    if (to_string(rebuntu::command::BatchResultStatus::kPartialSuccess) != "partial_success") {
        std::cerr << " [FAIL - kPartialSuccess string mismatch]\n";
        return;
    }
    if (to_string(rebuntu::command::BatchResultStatus::kAllFailed) != "all_failed") {
        std::cerr << " [FAIL - kAllFailed string mismatch]\n";
        return;
    }
    
    std::cout << " [PASS]\n";
}

void test_command_execution_record() {
    std::cout << "[TEST] CommandExecutionRecord creation...";
    
    using namespace rebuntu::command;
    using namespace rebuntu::core;
    
    CommandExecutionRecord record;
    record.id = "cmd-123";
    record.index = 0;
    record.status = SemanticStatus::kSuccess;
    record.changed = true;
    record.verified = true;
    record.elapsed_ms = std::chrono::milliseconds(100);
    
    if (record.id != "cmd-123") {
        std::cerr << " [FAIL - id not set]\n";
        return;
    }
    if (record.index != 0) {
        std::cerr << " [FAIL - index not set]\n";
        return;
    }
    if (!is_success(record)) {
        std::cerr << " [FAIL - is_success should be true]\n";
        return;
    }
    
    // Test failure case
    CommandExecutionRecord failed_record;
    failed_record.status = SemanticStatus::kFailure;
    if (is_success(failed_record)) {
        std::cerr << " [FAIL - is_success should be false for failed record]\n";
        return;
    }
    
    std::cout << " [PASS]\n";
}

void test_batch_result_factory_methods() {
    std::cout << "[TEST] BatchResult factory methods...";
    
    using namespace rebuntu::command;
    using namespace rebuntu::core;
    
    // Create a success result
    std::vector<CommandExecutionRecord> success_records = {
        []() { 
            CommandExecutionRecord r;
            r.id = "cmd-1";
            r.status = SemanticStatus::kSuccess;
            r.verified = true;
            r.elapsed_ms = std::chrono::milliseconds(50);
            return r;
        }(),
        []() {
            CommandExecutionRecord r;
            r.id = "cmd-2";
            r.status = SemanticStatus::kSuccess;
            r.verified = true;
            r.elapsed_ms = std::chrono::milliseconds(60);
            return r;
        }()
    };
    
    auto success_result = BatchResult::success(rebuntu::command::BatchMode::kSequentialBestEffort, success_records);
    
    if (success_result.aggregate_status != rebuntu::command::BatchResultStatus::kAllSuccess) {
        std::cerr << " [FAIL - success result status incorrect]\n";
        return;
    }
    if (!success_result.is_success()) {
        std::cerr << " [FAIL - is_success should be true for all-success batch]\n";
        return;
    }
    if (success_result.total_duration_ms != std::chrono::milliseconds(110)) {
        std::cerr << " [FAIL - total duration calculation incorrect]\n";
        return;
    }
    
    // Test unknown result
    auto unknown_result = BatchResult::unknown(rebuntu::command::BatchMode::kParallelIndependent);
    if (unknown_result.aggregate_status != rebuntu::command::BatchResultStatus::kUnknown) {
        std::cerr << " [FAIL - unknown status not set correctly]\n";
        return;
    }
    
    std::cout << " [PASS]\n";
}

void test_batch_intent_creation() {
    std::cout << "[TEST] BatchIntent creation...";
    
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
    
    auto batch = BatchIntent::make(rebuntu::command::BatchMode::kSequentialBestEffort, {intent1, intent2});
    
    if (batch.mode != rebuntu::command::BatchMode::kSequentialBestEffort) {
        std::cerr << " [FAIL - mode not set correctly]\n";
        return;
    }
    if (batch.intents.size() != 2) {
        std::cerr << " [FAIL - wrong number of intents]\n";
        return;
    }
    
    // Test add_intent
    CommandIntent intent3;
    intent3.id = "intent-3";
    batch.add_intent(std::move(intent3));
    
    if (batch.intents.size() != 3) {
        std::cerr << " [FAIL - add_intent not working]\n";
        return;
    }
    
    // Test that source_context is accessible
    batch.source_context = "test-source";
    if (!batch.source_context.has_value() || *batch.source_context != "test-source") {
        std::cerr << " [FAIL - source_context not accessible]\n";
        return;
    }
    
    std::cout << " [PASS]\n";
}

void test_batch_builder() {
    std::cout << "[TEST] BatchBuilder...";
    
    using namespace rebuntu::command;
    
    auto batch = BatchBuilder(rebuntu::command::BatchMode::kParallelIndependent)
        .add_intent(CommandIntent{})
        .with_source_context("test-context")
        .build();
    
    if (batch.mode != rebuntu::command::BatchMode::kParallelIndependent) {
        std::cerr << " [FAIL - mode not set via builder]\n";
        return;
    }
    if (!batch.source_context.has_value()) {
        std::cerr << " [FAIL - source_context not set via builder]\n";
        return;
    }
    if (*batch.source_context != "test-context") {
        std::cerr << " [FAIL - source_context value incorrect]\n";
        return;
    }
    
    // Test multiple intents
    auto batch2 = BatchBuilder(rebuntu::command::BatchMode::kSequentialStrict)
        .add_intent(CommandIntent{})
        .add_intents({CommandIntent{}, CommandIntent{}})
        .build();
    
    if (batch2.intents.size() != 3) {
        std::cerr << " [FAIL - add_intents not working]\n";
        return;
    }
    
    std::cout << " [PASS]\n";
}

void test_error_codes_exist() {
    std::cout << "[TEST] Error codes exist...";
    
    using namespace rebuntu::command;
    
    // Compare string content using strcmp since these are char arrays
    if (strcmp(error::kBatchEmpty, "E_BATCH_EMPTY") != 0) {
        std::cerr << " [FAIL - kBatchEmpty incorrect]\n";
        return;
    }
    if (strcmp(error::kBatchPartialSuccess, "E_BATCH_PARTIAL") != 0) {
        std::cerr << " [FAIL - kBatchPartialSuccess incorrect]\n";
        return;
    }
    if (strcmp(error::kBatchAllFailed, "E_BATCH_ALL_FAILED") != 0) {
        std::cerr << " [FAIL - kBatchAllFailed incorrect]\n";
        return;
    }
    
    std::cout << " [PASS]\n";
}

void test_batch_result_has_failures() {
    std::cout << "[TEST] BatchResult has_failures...";
    
    using namespace rebuntu::command;
    using namespace rebuntu::core;
    
    // All success should have no failures
    auto success_records = std::vector<CommandExecutionRecord>{
        []() {
            CommandExecutionRecord r;
            r.status = SemanticStatus::kSuccess;
            r.verified = true;
            return r;
        }()
    };
    auto success_result = BatchResult::success(rebuntu::command::BatchMode::kSequentialStrict, success_records);
    
    if (success_result.has_failures()) {
        std::cerr << " [FAIL - success batch should not have failures]\n";
        return;
    }
    
    // Partial success with one failure
    auto partial_records = std::vector<CommandExecutionRecord>{
        []() {
            CommandExecutionRecord r;
            r.status = SemanticStatus::kSuccess;
            r.verified = true;
            return r;
        }(),
        []() {
            CommandExecutionRecord r;
            r.status = SemanticStatus::kFailure;
            r.error = Error{"E_FAIL", "test failure"};
            return r;
        }()
    };
    auto partial_result = BatchResult::partial_success(rebuntu::command::BatchMode::kSequentialStrict, partial_records);
    
    if (!partial_result.has_failures()) {
        std::cerr << " [FAIL - partial batch should have failures]\n";
        return;
    }
    
    // Test that error is accessible
    if (partial_result.records[1].error->code != "E_FAIL") {
        std::cerr << " [FAIL - error not accessible in record]\n";
        return;
    }
    
    std::cout << " [PASS]\n";
}

int main() {
    std::cout << "=== Phase 6.42 Typed Batch Command Boundary Unit Tests ===\n\n";
    
    test_batch_mode_to_string();
    test_batch_result_status_to_string();
    test_command_execution_record();
    test_batch_result_factory_methods();
    test_batch_intent_creation();
    test_batch_builder();
    test_error_codes_exist();
    test_batch_result_has_failures();
    
    std::cout << "\n=== All tests completed ===\n";
    return 0;
}