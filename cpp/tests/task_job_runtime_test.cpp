// rebuntu::runtime::task_job_runtime - Tests (Phase 4.13)
//
// Tests for the TaskJobRuntime component that executes Tasks as Jobs with:
//   - Attempt history preservation
//   - Retry logic
//   - Cancellation support

#include <runtime/task_job_runtime.hpp>
#include <runtime/core/results.hpp>
#include <runtime/work.hpp>
#include <cassert>
#include <iostream>
#include <chrono>

using namespace rebuntu::runtime;
using namespace rebuntu::runtime::work;
using namespace rebuntu::core;

void test_task_job_runtime_creation() {
    auto runtime = make_task_job_runtime();
    assert(runtime != nullptr);
    std::cout << "test_task_job_runtime_creation: PASSED" << std::endl;
}

void test_task_job_runtime_submit_success() {
    Task task{
        .id = TaskId{"task-test-success"},
        .title = "Test success task",
        .description = "Task that succeeds",
        .unit_id = "test.unit"
    };
    
    auto runtime = make_task_job_runtime();
    JobExecutionResult result = runtime->submit(task, {}, 1);
    
    assert(result.status == core::SemanticStatus::kSuccess || 
           result.status == core::SemanticStatus::kCompleted);
    std::cout << "test_task_job_runtime_submit_success: PASSED" << std::endl;
}

void test_task_job_runtime_attempt_history() {
    Task task{
        .id = TaskId{"task-test-history"},
        .title = "Test history task",
        .description = "Task that tests attempt history",
        .unit_id = "test.unit"
    };
    
    auto runtime = make_task_job_runtime();
    JobExecutionResult result = runtime->submit(task, {}, 3);
    
    // Should have at least 1 attempt
    assert(!result.history.attempts.empty());
    std::cout << "test_task_job_runtime_attempt_history: PASSED" << std::endl;
}

void test_task_job_runtime_cancel() {
    Task task{
        .id = TaskId{"task-test-cancel"},
        .title = "Test cancel task",
        .description = "Task for cancellation testing",
        .unit_id = "test.unit"
    };
    
    auto runtime = make_task_job_runtime();
    
    // Submit and get job ID
    JobExecutionResult result = runtime->submit(task, {}, 3);
    JobId job_id = result.job_id;
    
    // Cancel the execution
    bool cancelled = runtime->cancel(job_id);
    assert(cancelled == true);
    
    // Verify state was updated
    JobExecutionState state = runtime->get_state(job_id);
    assert(state == JobExecutionState::kCancelled);
    std::cout << "test_task_job_runtime_cancel: PASSED" << std::endl;
}

void test_task_job_runtime_get_result() {
    Task task{
        .id = TaskId{"task-test-get-result"},
        .title = "Test get result task",
        .description = "Task for result retrieval testing",
        .unit_id = "test.unit"
    };
    
    auto runtime = make_task_job_runtime();
    JobExecutionResult result = runtime->submit(task, {}, 1);
    
    // Get result by ID
    std::optional<JobExecutionResult> stored_result = runtime->get_result(result.job_id);
    assert(stored_result.has_value());
    assert(stored_result->job_id == result.job_id);
    std::cout << "test_task_job_runtime_get_result: PASSED" << std::endl;
}

void test_task_job_runtime_metrics() {
    Task task{
        .id = TaskId{"task-test-metrics"},
        .title = "Test metrics task",
        .description = "Task for metrics testing",
        .unit_id = "test.unit"
    };
    
    auto runtime = make_task_job_runtime();
    
    // Submit a job
    JobExecutionResult result1 = runtime->submit(task, {}, 1);
    
    // Check metrics
    JobRuntimeMetrics m = runtime->metrics();
    assert(m.jobs_submitted >= 1);
    std::cout << "test_task_job_runtime_metrics: PASSED" << std::endl;
}

void test_task_job_runtime_state_transitions() {
    Task task{
        .id = TaskId{"task-test-state"},
        .title = "Test state transitions",
        .description = "Task for state transition testing",
        .unit_id = "test.unit"
    };
    
    auto runtime = make_task_job_runtime();
    JobExecutionResult result = runtime->submit(task, {}, 1);
    
    // Result should have a completed state
    assert(result.state == JobExecutionState::kCompleted);
    std::cout << "test_task_job_runtime_state_transitions: PASSED" << std::endl;
}

int main() {
    test_task_job_runtime_creation();
    test_task_job_runtime_submit_success();
    test_task_job_runtime_attempt_history();
    test_task_job_runtime_cancel();
    test_task_job_runtime_get_result();
    test_task_job_runtime_metrics();
    test_task_job_runtime_state_transitions();
    
    std::cout << "\nAll task_job_runtime tests completed!" << std::endl;
    return 0;
}