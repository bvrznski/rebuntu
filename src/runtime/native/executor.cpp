// rebuntu::runtime::executor — Executor implementation (Phase 0.13)

#include <runtime/executor.hpp>

namespace rebuntu::runtime::executor {

ExecutorResult Executor::execute(
    const work::Task& task,
    const work::Job& job,
    const ExecutorInvocationContext& ctx) {
    
    (void)task;  // unused in minimal proof
    (void)ctx;   // unused in minimal proof
    
    total_invocations_++;
    
    auto start = std::chrono::steady_clock::now();
    
    ExecutorResult exec_result{
        .outcome = execute_fn_(task, ctx),
        .execution_id = work::ExecutionId{job.id.value + "-attempt-1"},
        .attempt_number = work::AttemptNumber{1},
        .is_last_attempt = true,
    };
    
    auto end = std::chrono::steady_clock::now();
    exec_result.execution_duration = 
        std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    
    if (exec_result.outcome.status == core::SemanticStatus::kSuccess) {
        successful_executions_++;
    } else {
        failed_executions_++;
    }
    
    return exec_result;
}

InlineExecutor::InlineExecutor() : Executor(
    [](const work::Task&, const ExecutorInvocationContext&) -> core::Outcome {
        return core::Outcome::completed();
    }) {}

core::Outcome InlineExecutor::execute_inline(const work::Task&, std::function<core::Outcome()> op) {
    return op();
}

}  // namespace rebuntu::runtime::executor
