// Rebuntu Phase 6.20 — Exit Result Semantics Unit Test
//
// Tests the ExitResult structure and ExitReason enumeration:
//   - Normal exit (exit code 0)
//   - Nonzero exit (nonzero exit code)
//   - Signal termination (killed by signal)
//   - Timeout
//   - Cancellation
//   - Spawn failure
//   - Protocol failure

#include <cassert>
#include <chrono>
#include <iostream>
#include <string>

#include <system/core/contracts.hpp>

using namespace rebuntu::core;

void test_exit_reason_strings() {
    // Verify to_string returns correct values for each ExitReason
    assert(to_string(ExitReason::kNormalExit) == "normal_exit");
    assert(to_string(ExitReason::kNonzeroExit) == "nonzero_exit");
    assert(to_string(ExitReason::kSignalTermination) == "signal_termination");
    assert(to_string(ExitReason::kTimeout) == "timeout");
    assert(to_string(ExitReason::kCancellation) == "cancellation");
    assert(to_string(ExitReason::kSpawnFailure) == "spawn_failure");
    assert(to_string(ExitReason::kProtocolFailure) == "protocol_failure");
    assert(to_string(ExitReason::kUnknown) == "unknown_exit");
}

void test_exit_result_success() {
    // Test success case: normal exit with code 0
    auto result = ExitResult::success();
    
    assert(result.reason == ExitReason::kNormalExit);
    assert(result.exit_code == 0);
    assert(!result.signal_number.has_value());
    assert(result.is_success());
    assert(!result.was_signaled());
    assert(!result.timed_out());
    assert(!result.cancelled());
    assert(!result.spawn_failed());
}

void test_exit_result_nonzero_exit() {
    // Test nonzero exit (error code)
    auto result = ExitResult::nonzero_exit(1);
    
    assert(result.reason == ExitReason::kNonzeroExit);
    assert(result.exit_code == 1);
    assert(!result.is_success());
    assert(result.is_failure());
}

void test_exit_result_signal_termination() {
    // Test signal termination (e.g., SIGKILL, SIGTERM)
    auto result = ExitResult::signal_termination(9);  // SIGKILL
    
    assert(result.reason == ExitReason::kSignalTermination);
    assert(result.exit_code == -1);
    assert(result.signal_number.has_value());
    assert(result.signal_number.value() == 9);
    assert(result.was_signaled());
    assert(!result.is_success());
}

void test_exit_result_timeout() {
    // Test timeout
    auto duration = std::chrono::milliseconds(5000);
    auto result = ExitResult::timeout(duration, "operation exceeded time limit");
    
    assert(result.reason == ExitReason::kTimeout);
    assert(result.exit_code == -1);
    assert(result.timed_out());
    assert(!result.is_success());
}

void test_exit_result_cancellation() {
    // Test cancellation
    auto result = ExitResult::cancellation("user requested cancel");
    
    assert(result.reason == ExitReason::kCancellation);
    assert(result.exit_code == -1);
    assert(result.cancelled());
    assert(!result.is_success());
}

void test_exit_result_spawn_failure() {
    // Test spawn failure (failed to start process)
    auto result = ExitResult::spawn_failure("executable not found");
    
    assert(result.reason == ExitReason::kSpawnFailure);
    assert(result.exit_code == -1);
    assert(result.spawn_failed());
    assert(!result.is_success());
}

void test_exit_result_protocol_failure() {
    // Test protocol failure (IPC/serialization error)
    auto result = ExitResult::protocol_failure("invalid message format");
    
    assert(result.reason == ExitReason::kProtocolFailure);
    assert(result.exit_code == -1);
    assert(!result.is_success());
}

void test_exit_result_unknown() {
    // Test unknown termination reason
    auto result = ExitResult::unknown();
    
    assert(result.reason == ExitReason::kUnknown);
    assert(result.exit_code == -1);
    assert(!result.is_success());
}

void test_exit_result_with_duration() {
    // Test that execution duration is stored correctly
    auto duration = std::chrono::milliseconds(42);
    auto result = ExitResult::success(0, duration);
    
    assert(result.execution_duration_ms == duration);
}

void test_exit_result_output_capture() {
    // Test stdout/stderr capture fields
    ExitResult result;
    result.stdout_data = "command output";
    result.stderr_data = "error message";
    
    assert(result.stdout_data == "command output");
    assert(result.stderr_data == "error message");
}

int main() {
    std::cout << "=== Phase 6.20: Exit Result Semantics Tests ===" << std::endl;
    
    test_exit_reason_strings();
    std::cout << "[PASS] ExitReason string conversions" << std::endl;
    
    test_exit_result_success();
    std::cout << "[PASS] Success case (normal exit, code 0)" << std::endl;
    
    test_exit_result_nonzero_exit();
    std::cout << "[PASS] Nonzero exit (error code)" << std::endl;
    
    test_exit_result_signal_termination();
    std::cout << "[PASS] Signal termination" << std::endl;
    
    test_exit_result_timeout();
    std::cout << "[PASS] Timeout" << std::endl;
    
    test_exit_result_cancellation();
    std::cout << "[PASS] Cancellation" << std::endl;
    
    test_exit_result_spawn_failure();
    std::cout << "[PASS] Spawn failure" << std::endl;
    
    test_exit_result_protocol_failure();
    std::cout << "[PASS] Protocol failure" << std::endl;
    
    test_exit_result_unknown();
    std::cout << "[PASS] Unknown termination reason" << std::endl;
    
    test_exit_result_with_duration();
    std::cout << "[PASS] Execution duration tracking" << std::endl;
    
    test_exit_result_output_capture();
    std::cout << "[PASS] Output capture (stdout/stderr)" << std::endl;
    
    std::cout << "\n=== All Phase 6.20 tests passed ===" << std::endl;
    return 0;
}