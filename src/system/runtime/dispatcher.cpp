// rebuntu::runtime::dispatcher — Execution Dispatcher implementation (Phase 4.5)
//
// The Dispatcher routes typed resolved requests/work items to the appropriate
// execution path without owning policy, scheduling, or actual execution.
//
// Responsibilities:
//   - Map capability IDs to appropriate execution mechanisms (modes)
//   - Detect duplicate handler registrations and ambiguous matches
//   - Select execution mode based on task characteristics and context
//   - Make dispatch decisions with bounded error reporting
//
// The Dispatcher does NOT own:
//   - Policy decisions (authorization, scheduling)
//   - Execution itself (delegates to Executor/Runner)
//   - State persistence

#include <system/runtime/dispatcher.hpp>

#include <algorithm>
#include <string>
#include <vector>
#include <optional>

namespace rebuntu::runtime::dispatcher {

ExecutionModeSelection Dispatcher::select_execution_mode(
    const runtime::work::Task& task,
    const DispatcherContext& ctx) const {
    
    ExecutionModeSelection selection;
    selection.mode = runtime::work::ExecutionMode::kInline;
    selection.reason = "default_inline";
    
    // Priority-based mode selection
    if (task.mode != runtime::work::ExecutionMode::kInline) {
        selection.mode = task.mode;
        selection.reason = "explicit_task_mode";
        return selection;
    }
    
    // Check for subprocess-compatible tasks
    // (tasks that don't require special privileges and can fork)
    if (ctx.subprocess_available && !task.unit_id.empty()) {
        selection.mode = runtime::work::ExecutionMode::kSubprocess;
        selection.reason = "subprocess_available";
        return selection;
    }
    
    // Check for systemd unit availability
    if (ctx.systemd_unit_available) {
        selection.mode = runtime::work::ExecutionMode::kSystemdUnit;
        selection.reason = "systemd_unit_available";
        return selection;
    }
    
    // Fallback to inline execution
    selection.mode = runtime::work::ExecutionMode::kInline;
    selection.reason = "fallback_inline";
    
    return selection;
}

DispatcherDecision Dispatcher::dispatch(
    const runtime::work::Job& job,
    const DispatcherContext& ctx) {
    
    // Check if dispatcher is backpressured (queue full)
    if (is_backpressured()) {
        return DispatcherDecision::reject(
            "E_DISPATCHER_BACKPRESSURE",
            "Dispatcher queue at capacity: " + std::to_string(pending_work_count_) +
                " >= " + std::to_string(max_concurrent_executions_)
        );
    }
    
    // Validate job has required fields
    if (job.id.value.empty()) {
        return DispatcherDecision::reject(
            "E_DISPATCHER_INVALID_JOB",
            "Job missing execution ID"
        );
    }
    
    if (job.task_id.empty()) {
        return DispatcherDecision::reject(
            "E_DISPATCHER_INVALID_TASK",
            "Job references empty task_id"
        );
    }
    
    // Select execution mode for this job
    runtime::work::Task dummy_task;  // Task info would come from registry in real impl
    auto mode_selection = select_execution_mode(dummy_task, ctx);
    
    // Make dispatch decision
    if (mode_selection.mode != runtime::work::ExecutionMode::kInline) {
        increment_pending();
    }
    
    DispatcherDecision result;
    result.accepted = true;
    result.selection = std::move(mode_selection);
    
    return result;
}

void Dispatcher::increment_pending() {
    pending_work_count_++;
}

void Dispatcher::decrement_pending() {
    if (pending_work_count_ > 0) {
        pending_work_count_--;
    }
}

}  // namespace rebuntu::runtime::dispatcher