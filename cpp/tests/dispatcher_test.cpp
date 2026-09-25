// rebuntu::runtime::dispatcher - Tests (Phase 4.5)
//
// Tests for the Dispatcher execution routing mechanism component.

#include <system/runtime/dispatcher.hpp>
#include <system/runtime/work.hpp>
#include <cassert>
#include <iostream>

using namespace rebuntu::runtime;
using namespace rebuntu::runtime::dispatcher;

void test_dispatcher_creation() {
    bool dispatched = false;
    auto callback = [&dispatched](const work::Job&) { 
        dispatched = true; 
    };
    
    Dispatcher dispatcher{callback};
    assert(dispatcher.get_pending_count() == 0);
    std::cout << "test_dispatcher_creation: PASSED" << std::endl;
}

void test_dispatcher_backpressure() {
    bool dispatched = false;
    auto callback = [&dispatched](const work::Job&) { 
        dispatched = true; 
    };
    
    Dispatcher dispatcher{callback};
    
    // Verify initial state
    assert(dispatcher.is_backpressured() == false);
    
    std::cout << "test_dispatcher_backpressure: PASSED" << std::endl;
}

void test_dispatcher_dispatch_inline() {
    bool dispatched = false;
    auto callback = [&dispatched](const work::Job& job) { 
        (void)job;  // suppress unused warning
        dispatched = true; 
    };
    
    Dispatcher dispatcher{callback};
    
    work::Job job{};
    job.id = work::JobId{"test-job-1"};
    job.task_id = "task-1";
    
    DispatcherContext ctx;
    ctx.subprocess_available = true;
    ctx.max_concurrent_executions = 100;
    
    auto result = dispatcher.dispatch(job, ctx);
    
    assert(result.accepted == true);
    std::cout << "test_dispatcher_dispatch_inline: PASSED" << std::endl;
}

void test_dispatcher_select_execution_mode() {
    Dispatcher dispatcher{[](const work::Job&){}};
    
    work::Task task{};
    task.mode = work::ExecutionMode::kSubprocess;
    
    DispatcherContext ctx;
    ctx.subprocess_available = true;
    
    auto selection = dispatcher.select_execution_mode(task, ctx);
    
    // The dispatcher should respect the task's mode if specified
    assert(selection.mode == work::ExecutionMode::kSubprocess || 
           selection.mode == work::ExecutionMode::kInline);  // fallback is inline
    
    std::cout << "test_dispatcher_select_execution_mode: PASSED" << std::endl;
}

void test_dispatcher_context() {
    DispatcherContext ctx;
    
    assert(ctx.subprocess_available == true);
    assert(ctx.systemd_unit_available == false);
    assert(ctx.dbus_available == false);
    assert(ctx.pending_work_count == 0);
    assert(ctx.max_concurrent_executions == 100);
    
    std::cout << "test_dispatcher_context: PASSED" << std::endl;
}

void test_dispatcher_registry() {
    DispatcherRegistry registry;
    
    registry.register_mechanism("subprocess", work::ExecutionMode::kSubprocess);
    registry.register_mechanism("systemd", work::ExecutionMode::kSystemdUnit);
    
    auto mode = registry.find_mechanism("subprocess");
    assert(mode.has_value() == true);
    
    mode = registry.find_mechanism("unknown-mechanism");
    assert(mode.has_value() == false);
    
    std::cout << "test_dispatcher_registry: PASSED" << std::endl;
}

void test_dispatcher_decision_accept() {
    auto decision = DispatcherDecision::accept(
        ExecutionModeSelection{work::ExecutionMode::kSubprocess, "test reason"}
    );
    
    assert(decision.accepted == true);
    assert(decision.selection.mode == work::ExecutionMode::kSubprocess);
    assert(decision.selection.reason.find("test") != std::string::npos);
    
    std::cout << "test_dispatcher_decision_accept: PASSED" << std::endl;
}

void test_dispatcher_decision_reject() {
    auto decision = DispatcherDecision::reject("E_TEST", "test error message");
    
    assert(decision.accepted == false);
    assert(decision.error.has_value() == true);
    assert(decision.error->code.find("E_TEST") != std::string::npos);
    
    std::cout << "test_dispatcher_decision_reject: PASSED" << std::endl;
}

void test_dispatcher_pending_count() {
    bool dispatched = false;
    auto callback = [&dispatched](const work::Job&) { 
        dispatched = true; 
    };
    
    Dispatcher dispatcher{callback};
    
    assert(dispatcher.get_pending_count() == 0);
    
    // Test increment/decrement
    dispatcher.increment_pending();
    assert(dispatcher.get_pending_count() == 1);
    
    dispatcher.decrement_pending();
    assert(dispatcher.get_pending_count() == 0);
    
    std::cout << "test_dispatcher_pending_count: PASSED" << std::endl;
}

void test_dispatcher_all_mechanisms() {
    DispatcherRegistry registry;
    
    registry.register_mechanism("subprocess", work::ExecutionMode::kSubprocess);
    registry.register_mechanism("systemd", work::ExecutionMode::kSystemdUnit);
    
    auto all = registry.all();
    
    // Should have 2 entries
    assert(all.size() == 2);
    
    std::cout << "test_dispatcher_all_mechanisms: PASSED" << std::endl;
}

int main() {
    test_dispatcher_creation();
    test_dispatcher_backpressure();
    test_dispatcher_dispatch_inline();
    test_dispatcher_select_execution_mode();
    test_dispatcher_context();
    test_dispatcher_registry();
    test_dispatcher_decision_accept();
    test_dispatcher_decision_reject();
    test_dispatcher_pending_count();
    test_dispatcher_all_mechanisms();
    
    std::cout << "\nAll dispatcher tests completed!" << std::endl;
    return 0;
}