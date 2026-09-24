// Test suite for Rebuntu runtime Runner (Phase 0.13)
#include <runtime/runner.hpp>
#include <runtime/core/contracts.hpp>
#include <runtime/work.hpp>
#include <iostream>

namespace rebuntu::runtime {
namespace runner {

// Test basic Runner functionality
int test_runner_basic() {
    int errors = 0;
    
    work::ExecutionId exec_id{"exec-001"};
    
    work::Task task{
        .id = work::TaskId{"task-test"},
        .title = "Test Task",
        .description = "A test task for Runner",
        .unit_id = "test-unit",
        .mode = work::ExecutionMode::kInline,
        .created_at = std::chrono::system_clock::now(),
    };
    
    work::Job job;
    job.id = work::JobId{"job-001"};
    job.task_id = task.id.value;
    job.created_at = std::chrono::system_clock::now();
    job.state = work::JobState::kCreated;
    
    int call_count = 0;
    auto execute_fn = [&call_count](const work::Task& task, const work::Job& job, 
                                    int attempt_number, const RunnerContext&) -> core::Outcome {
        (void)task; (void)job; (void)attempt_number;
        call_count++;
        return core::Outcome::success();
    };
    
    Runner runner(exec_id, std::move(job), execute_fn);
    
    if (runner.progress().runner_state != RunnerState::kPending) {
        std::cerr << "ERROR: Initial state should be kPending\n";
        errors++;
    }
    
    runner.start();
    
    if (runner.progress().runner_state != RunnerState::kRunning) {
        std::cerr << "ERROR: State after start should be kRunning\n";
        errors++;
    }
    
    auto result = runner.attempt();
    
    if (result.outcome.status != core::SemanticStatus::kSuccess) {
        std::cerr << "ERROR: Execution should succeed\n";
        errors++;
    }
    
    if (call_count != 1) {
        std::cerr << "ERROR: Execute function should be called once\n";
        errors++;
    }
    
    if (!runner.is_finished()) {
        std::cerr << "ERROR: Runner should be finished after single attempt\n";
        errors++;
    }
    
    auto runner_result = runner.result();
    if (runner_result.status != core::SemanticStatus::kSuccess) {
        std::cerr << "ERROR: Final status should be success\n";
        errors++;
    }
    
    return errors;
}

// Test cancellation
int test_runner_cancel() {
    int errors = 0;
    
    work::ExecutionId exec_id{"exec-002"};
    
    work::Task task{
        .id = work::TaskId{"task-cancel"},
        .title = "Cancel Test",
        .description = "Test cancellation",
        .unit_id = "test-unit",
        .mode = work::ExecutionMode::kInline,
        .created_at = std::chrono::system_clock::now(),
    };
    
    work::Job job;
    job.id = work::JobId{"job-002"};
    job.task_id = task.id.value;
    job.created_at = std::chrono::system_clock::now();
    job.state = work::JobState::kCreated;
    
    int call_count = 0;
    auto execute_fn = [&call_count](const work::Task& task, const work::Job& job,
                                    int attempt_number, const RunnerContext&) -> core::Outcome {
        (void)task; (void)job; (void)attempt_number;
        call_count++;
        return core::Outcome::success();
    };
    
    Runner runner(exec_id, std::move(job), execute_fn);
    runner.start();  // Must start before cancelling
    
    // Test that cancel before attempt works
    runner.request_cancel("test cancellation");
    std::cout << "After request_cancel, is_finished=" << runner.is_finished() << "\n";
    
    auto result = runner.attempt();
    std::cout << "Result status: " << core::to_string(result.outcome.status) 
              << ", is_last_attempt=" << result.is_last_attempt << "\n";
    
    if (call_count != 0) {
        std::cerr << "ERROR: Execute should not be called when cancelled\n";
        errors++;
    }
    
    if (result.outcome.status != core::SemanticStatus::kCancelled) {
        std::cerr << "ERROR: Outcome should be cancelled\n";
        errors++;
    }
    
    return errors;
}

// Test retry logic
int test_runner_retry() {
    int errors = 0;
    
    work::ExecutionId exec_id{"exec-003"};
    
    work::Task task{
        .id = work::TaskId{"task-retry"},
        .title = "Retry Test",
        .description = "Test retry logic",
        .unit_id = "test-unit",
        .mode = work::ExecutionMode::kInline,
        .created_at = std::chrono::system_clock::now(),
    };
    
    work::Job job;
    job.id = work::JobId{"job-003"};
    job.task_id = task.id.value;
    job.created_at = std::chrono::system_clock::now();
    job.state = work::JobState::kCreated;
    
    int attempt_count = 0;
    auto execute_fn = [&attempt_count](const work::Task& task, const work::Job& job,
                                       int attempt_number, const RunnerContext&) -> core::Outcome {
        (void)task; (void)job; (void)attempt_number;
        // Fail first attempt, succeed on second
        if (attempt_count == 0) {
            attempt_count++;
            return core::Outcome::failure("E_TEMP", "temporary failure");
        }
        attempt_count++;
        return core::Outcome::success();
    };
    
    // Set max_attempts to allow 1 retry (2 total attempts)
    job.retry_policy.max_attempts = 3;
    
    Runner runner(exec_id, std::move(job), execute_fn);
    runner.start();
    
    std::cout << "First attempt state before: " << to_string(runner.progress().runner_state) << "\n";
    
    auto result1 = runner.attempt();
    std::cout << "Result1 status: " << core::to_string(result1.outcome.status) 
              << ", is_last_attempt: " << result1.is_last_attempt
              << ", state after: " << to_string(runner.progress().runner_state) << "\n";
    
    if (result1.outcome.status != core::SemanticStatus::kFailure) {
        std::cerr << "ERROR: First attempt should fail\n";
        errors++;
    }
    
    std::cout << "Second attempt state before: " << to_string(runner.progress().runner_state) << "\n";
    
    auto result2 = runner.attempt();
    std::cout << "Result2 status: " << core::to_string(result2.outcome.status)
              << ", is_last_attempt: " << result2.is_last_attempt
              << ", state after: " << to_string(runner.progress().runner_state) << "\n";
    
    if (result2.outcome.status != core::SemanticStatus::kSuccess) {
        std::cerr << "ERROR: Retry should succeed\n";
        errors++;
    }
    
    return errors;
}

int main() {
    int total_errors = 0;
    
    std::cout << "Testing Runner basic functionality...\n";
    total_errors += test_runner_basic();
    
    std::cout << "Testing Runner cancellation...\n";
    total_errors += test_runner_cancel();
    
    std::cout << "Testing Runner retry logic...\n";
    total_errors += test_runner_retry();
    
    if (total_errors == 0) {
        std::cout << "All tests passed!\n";
    } else {
        std::cerr << total_errors << " test(s) failed.\n";
    }
    
    return total_errors;
}

}  // namespace runner
}  // namespace rebuntu::runtime

int main() {
    return rebuntu::runtime::runner::main();
}