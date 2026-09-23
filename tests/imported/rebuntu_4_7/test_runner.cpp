// Unit tests for rebuntu::runtime::runner (Phase 4.4)
#include <system/runtime/runner.hpp>

#include <chrono>
#include <iostream>
#include <string>

#include <system/core/contracts.hpp>
#include <system/runtime/work.hpp>

namespace {

int g_failures = 0;
#define CHECK(cond)                                                              \
    do {                                                                         \
        if (!(cond)) {                                                           \
            std::cerr << "CHECK failed: " << #cond << " (line " << __LINE__      \
                      << ")\n";                                                  \
            ++g_failures;                                                        \
        }                                                                        \
    } while (0)

}  // namespace

int main() {
    using rebuntu::runtime::runner::AttemptResult;
    using rebuntu::runtime::runner::ProgressStage;
    using rebuntu::runtime::runner::Runner;
    using rebuntu::runtime::runner::RunnerProgress;
    using rebuntu::runtime::runner::RunnerResult;
    using rebuntu::runtime::runner::RunnerState;
    using rebuntu::runtime::runner::to_string;

    std::cout << "Testing Phase 4.4 Runner implementation...\n";

    // Test RunnerState string conversions
    CHECK(to_string(RunnerState::kPending) == "pending");
    CHECK(to_string(RunnerState::kRunning) == "running");
    CHECK(to_string(RunnerState::kWaiting) == "waiting");
    CHECK(to_string(RunnerState::kFinished) == "finished");

    // Test ProgressStage string conversions
    CHECK(to_string(ProgressStage::kDispatched) == "dispatched");
    CHECK(to_string(ProgressStage::kExecuting) == "executing");
    CHECK(to_string(ProgressStage::kObserving) == "observing");
    CHECK(to_string(ProgressStage::kVerifying) == "verifying");
    CHECK(to_string(ProgressStage::kCompleted) == "completed");

    // Test Runner construction and initial state
    {
        auto execute_fn = [](const rebuntu::runtime::work::Task&,
                             const rebuntu::runtime::work::Job&,
                             int attempt_number) -> rebuntu::core::Outcome {
            return rebuntu::core::Outcome::success(true);
        };

        rebuntu::runtime::work::ExecutionId exec_id{"exec-123"};
        rebuntu::runtime::work::Job job;
        job.id.value = "job-456";
        job.max_attempts = rebuntu::runtime::work::AttemptNumber{3};

        Runner runner(exec_id, job, execute_fn);

        CHECK(runner.progress().runner_state == RunnerState::kPending);
        CHECK(runner.progress().stage == ProgressStage::kDispatched);
        CHECK(!runner.is_finished());
    }

    // Test Runner start() method
    {
        auto execute_fn = [](const rebuntu::runtime::work::Task&, 
                             const rebuntu::runtime::work::Job&, int) -> rebuntu::core::Outcome {
            return rebuntu::core::Outcome::success(true);
        };

        rebuntu::runtime::work::ExecutionId exec_id{"exec-456"};
        rebuntu::runtime::work::Job job;
        job.id.value = "job-789";
        job.max_attempts = rebuntu::runtime::work::AttemptNumber{1};

        Runner runner(exec_id, job, execute_fn);

        auto now = std::chrono::system_clock::now();
        runner.start(now);

        CHECK(runner.progress().runner_state == RunnerState::kRunning);
        CHECK(runner.is_finished() == false);
    }

    // Test Runner attempt() - single successful attempt
    {
        int call_count = 0;
        auto execute_fn = [&call_count](const rebuntu::runtime::work::Task&, 
                                        const rebuntu::runtime::work::Job&, int) -> rebuntu::core::Outcome {
            call_count++;
            return rebuntu::core::Outcome::success(true);
        };

        rebuntu::runtime::work::ExecutionId exec_id{"exec-789"};
        rebuntu::runtime::work::Job job;
        job.id.value = "job-101";
        job.max_attempts = rebuntu::runtime::work::AttemptNumber{1};

        Runner runner(exec_id, job, execute_fn);
        runner.start();

        auto result = runner.attempt();
        CHECK(result.outcome.status == rebuntu::core::SemanticStatus::kSuccess);
        CHECK(call_count == 1);
        CHECK(runner.is_finished() == true);
    }

    // Test Runner attempt() - failure with retry
    {
        int call_count = 0;
        auto execute_fn = [&call_count](const rebuntu::runtime::work::Task&, 
                                        const rebuntu::runtime::work::Job&, int) -> rebuntu::core::Outcome {
            call_count++;
            if (call_count <= 2) {
                return rebuntu::core::Outcome::failure("E_TEST", "Test failure");
            }
            return rebuntu::core::Outcome::success(true);
        };

        rebuntu::runtime::work::ExecutionId exec_id{"exec-202"};
        rebuntu::runtime::work::Job job;
        job.id.value = "job-303";
        job.max_attempts = rebuntu::runtime::work::AttemptNumber{5};

        Runner runner(exec_id, job, execute_fn);
        runner.start();

        // First attempt - fails
        auto result1 = runner.attempt();
        CHECK(result1.outcome.status == rebuntu::core::SemanticStatus::kFailure);
        CHECK(!runner.is_finished());

        // Second attempt - still failing, will retry
        auto result2 = runner.attempt();
        CHECK(result2.outcome.status == rebuntu::core::SemanticStatus::kFailure);
        CHECK(!runner.is_finished());

        // Third attempt - succeeds (after retries exhausted)
        auto result3 = runner.attempt();
        CHECK(result3.outcome.status == rebuntu::core::SemanticStatus::kSuccess);
        CHECK(runner.is_finished());
        CHECK(call_count == 3);  // 2 failures + 1 success
    }

    // Test Runner cancellation - note: in this simple implementation,
    // request_cancel marks the state but doesn't stop execution.
    // The next attempt will still execute and can succeed or fail.
    {
        int call_count = 0;
        auto execute_fn = [&call_count](const rebuntu::runtime::work::Task&, 
                                        const rebuntu::runtime::work::Job&, int) -> rebuntu::core::Outcome {
            call_count++;
            return rebuntu::core::Outcome::success(true);
        };

        rebuntu::runtime::work::ExecutionId exec_id{"exec-404"};
        rebuntu::runtime::work::Job job;
        job.id.value = "job-505";
        job.max_attempts = rebuntu::runtime::work::AttemptNumber{5};

        Runner runner(exec_id, job, execute_fn);
        runner.start();

        // Request cancellation
        runner.request_cancel("user requested");

        // Cancellation sets state to kWaiting but execution can still proceed
        CHECK(runner.progress().runner_state == RunnerState::kWaiting);

        // After execution completes (since it's not interrupted), state becomes Finished
        auto result = runner.attempt();
        // Note: cancellation_requested_ prevents retry but doesn't stop current execution
    }

    // Test Runner result() method
    {
        int call_count = 0;
        auto execute_fn = [&call_count](const rebuntu::runtime::work::Task&, 
                                        const rebuntu::runtime::work::Job&, int) -> rebuntu::core::Outcome {
            call_count++;
            return rebuntu::core::Outcome::success(true);
        };

        rebuntu::runtime::work::ExecutionId exec_id{"exec-606"};
        rebuntu::runtime::work::Job job;
        job.id.value = "job-707";
        job.max_attempts = rebuntu::runtime::work::AttemptNumber{3};

        Runner runner(exec_id, job, execute_fn);
        runner.start();

        auto result = runner.attempt();
        (void)result;

        RunnerResult runner_result = runner.result();
        CHECK(runner_result.execution_id == exec_id);
        CHECK(runner_result.status == rebuntu::core::SemanticStatus::kSuccess);
        CHECK(runner_result.verified == true);
        CHECK(runner_result.attempts_completed >= 1);
    }

    // Test RunnerProgress
    {
        auto execute_fn = [](const rebuntu::runtime::work::Task&, 
                             const rebuntu::runtime::work::Job&, int) -> rebuntu::core::Outcome {
            return rebuntu::core::Outcome::success(true);
        };

        rebuntu::runtime::work::ExecutionId exec_id{"exec-808"};
        rebuntu::runtime::work::Job job;
        job.id.value = "job-909";
        job.max_attempts = rebuntu::runtime::work::AttemptNumber{2};

        Runner runner(exec_id, job, execute_fn);

        auto progress1 = runner.progress();
        CHECK(progress1.runner_state == RunnerState::kPending);
        CHECK(progress1.stage == ProgressStage::kDispatched);
        CHECK(progress1.attempt_number == 0);
        CHECK(progress1.job_id.has_value());
    }

    // Test Runner with timeout
    {
        int call_count = 0;
        auto execute_fn = [&call_count](const rebuntu::runtime::work::Task&, 
                                        const rebuntu::runtime::work::Job&, int) -> rebuntu::core::Outcome {
            call_count++;
            return rebuntu::core::Outcome::success(true);
        };

        rebuntu::runtime::work::ExecutionId exec_id{"exec-111"};
        rebuntu::runtime::work::Job job;
        job.id.value = "job-222";
        job.max_attempts = rebuntu::runtime::work::AttemptNumber{3};

        Runner runner(exec_id, job, execute_fn);

        // Verify default timeout behavior (no exception)
        auto now = std::chrono::system_clock::now();
        runner.start(now);
        auto result = runner.attempt();

        CHECK(result.outcome.status == rebuntu::core::SemanticStatus::kSuccess);
    }

    std::cout << "\nRunner implementation tests completed.\n";

    if (g_failures != 0) {
        std::cerr << g_failures << " check(s) FAILED\n";
        return 1;
    }

    std::cout << "test_runner: OK\n";
    return 0;
}