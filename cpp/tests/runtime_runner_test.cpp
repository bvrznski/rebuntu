// rebuntu::runtime::runner - Tests (Phase 4.4)
//
// Tests for the Runner execution state machine component.

#include <runtime/runner.hpp>
#include <runtime/work.hpp>
#include <runtime/core/results.hpp>
#include <cassert>
#include <iostream>
#include <chrono>

using namespace rebuntu::runtime;
using namespace rebuntu::runtime::work;
using namespace rebuntu::runtime::runner;
using namespace rebuntu::core;

void test_runner_creation() {
    auto execute_fn = [](const Task&, const Job&, int, const RunnerContext&) {
        return rebuntu::core::ExecutionOutcome::success();
    };
    
    Runner runner{ExecutionId{"exec-1"}, Job{JobId{"job-1"}, "task-1", std::chrono::system_clock::now()}, execute_fn};
    assert(runner.progress().runner_state == RunnerState::kPending);
    std::cout << "test_runner_creation: PASSED" << std::endl;
}

void test_runner_start() {
    auto execute_fn = [](const Task&, const Job&, int, const RunnerContext&) {
        return rebuntu::core::ExecutionOutcome::success();
    };
    
    Runner runner{ExecutionId{"exec-2"}, Job{JobId{"job-2"}, "task-2", std::chrono::system_clock::now()}, execute_fn};
    runner.start();
    
    assert(runner.progress().runner_state == RunnerState::kRunning);
    std::cout << "test_runner_start: PASSED" << std::endl;
}

void test_runner_attempt_success() {
    int attempt_count = 0;
    auto execute_fn = [&attempt_count](const Task&, const Job&, int, const RunnerContext&) {
        attempt_count++;
        return rebuntu::core::ExecutionOutcome::success();
    };
    
    Runner runner{ExecutionId{"exec-3"}, Job{JobId{"job-3"}, "task-3", std::chrono::system_clock::now()}, execute_fn};
    runner.start();
    
    auto result = runner.attempt();
    
    assert(result.outcome.status == rebuntu::core::SemanticStatus::kSuccess);
    assert(result.is_last_attempt == true);  // No retry needed on success
    std::cout << "test_runner_attempt_success: PASSED" << std::endl;
}

void test_runner_retry_on_failure() {
    int attempt_count = 0;
    auto execute_fn = [&attempt_count](const Task&, const Job&, int, const RunnerContext&) {
        attempt_count++;
        if (attempt_count < 3) {
            return rebuntu::core::ExecutionOutcome::failure();
        }
        return rebuntu::core::ExecutionOutcome::success();
    };
    
    // Create a job with max 5 attempts
    Job job{JobId{"job-4"}, "task-4", std::chrono::system_clock::now()};
    job.retry_policy.max_attempts = 5;
    
    Runner runner{ExecutionId{"exec-4"}, job, execute_fn};
    runner.start();
    
    auto result = runner.attempt();
    assert(result.outcome.status == rebuntu::core::SemanticStatus::kFailure);
    assert(runner.progress().attempt_number == 1);
    
    // Should retry because max_attempts not reached and error is retryable
    if (!runner.is_finished()) {
        result = runner.attempt();
        assert(result.outcome.status == rebuntu::core::SemanticStatus::kFailure);
        assert(runner.progress().attempt_number == 2);
        
        if (!runner.is_finished()) {
            result = runner.attempt();
            assert(result.outcome.status == rebuntu::core::SemanticStatus::kSuccess);
            assert(runner.is_finished());
            assert(result.is_last_attempt == true);
        }
    }
    
    std::cout << "test_runner_retry_on_failure: PASSED" << std::endl;
}

void test_runner_max_attempts() {
    int attempt_count = 0;
    auto execute_fn = [&attempt_count](const Task&, const Job&, int, const RunnerContext&) {
        attempt_count++;
        return rebuntu::core::ExecutionOutcome::failure();
    };
    
    Job job{JobId{"job-5"}, "task-5", std::chrono::system_clock::now()};
    job.retry_policy.max_attempts = 3;
    
    Runner runner{ExecutionId{"exec-5"}, job, execute_fn};
    runner.start();
    
    // First attempt
    auto result = runner.attempt();
    assert(runner.progress().attempt_number == 1);
    assert(!runner.is_finished());  // Can still retry
    
    // Second attempt
    runner.attempt();
    assert(runner.progress().attempt_number == 2);
    assert(!runner.is_finished());  // Can still retry
    
    // Third and final attempt
    runner.attempt();
    assert(runner.progress().attempt_number == 3);
    assert(runner.is_finished());  // Now finished after max attempts (3)
    assert(runner.is_finished());
    std::cout << "test_runner_max_attempts: PASSED" << std::endl;
}

void test_runner_cancellation() {
    auto execute_fn = [](const Task&, const Job&, int, const RunnerContext& ctx) {
        if (ctx.cancellation_requested) {
            return rebuntu::core::ExecutionOutcome::cancelled("explicit cancellation");
        }
        return rebuntu::core::ExecutionOutcome::success();
    };
    
    Runner runner{ExecutionId{"exec-6"}, Job{JobId{"job-6"}, "task-6", std::chrono::system_clock::now()}, execute_fn};
    runner.start();
    
    // Request cancellation
    runner.request_cancel("test cancel");
    
    auto result = runner.attempt();
    assert(result.outcome.status == rebuntu::core::SemanticStatus::kCancelled);
    std::cout << "test_runner_cancellation: PASSED" << std::endl;
}

void test_runner_result() {
    int attempt_count = 0;
    auto execute_fn = [&attempt_count](const Task&, const Job&, int, const RunnerContext&) {
        attempt_count++;
        return rebuntu::core::ExecutionOutcome::success();
    };
    
    Runner runner{ExecutionId{"exec-7"}, Job{JobId{"job-7"}, "task-7", std::chrono::system_clock::now()}, execute_fn};
    runner.start();
    runner.attempt();
    
    auto result = runner.result();
    assert(result.succeeded());
    assert(result.status == rebuntu::core::SemanticStatus::kSuccess);
    assert(result.verified == true);
    std::cout << "test_runner_result: PASSED" << std::endl;
}

void test_runner_progress() {
    int attempt_count = 0;
    auto execute_fn = [&attempt_count](const Task&, const Job&, int, const RunnerContext&) {
        attempt_count++;
        return rebuntu::core::ExecutionOutcome::success();
    };
    
    Runner runner{ExecutionId{"exec-8"}, Job{JobId{"job-8"}, "task-8", std::chrono::system_clock::now()}, execute_fn};
    
    // Before start
    assert(runner.progress().runner_state == RunnerState::kPending);
    assert(runner.progress().attempt_number == 0);
    
    runner.start();
    assert(runner.progress().runner_state == RunnerState::kRunning);
    assert(runner.progress().attempt_number == 0);  // Not yet executed
    
    runner.attempt();
    assert(runner.progress().attempt_number == 1);
    
    assert(runner.is_finished());
    std::cout << "test_runner_progress: PASSED" << std::endl;
}

int main() {
    test_runner_creation();
    test_runner_start();
    test_runner_attempt_success();
    test_runner_retry_on_failure();
    test_runner_max_attempts();
    test_runner_cancellation();
    test_runner_result();
    test_runner_progress();
    
    std::cout << "\nAll runner tests completed!" << std::endl;
    return 0;
}