// Unit tests for rebuntu::runtime::dispatcher (Phase 4.5)
#include <runtime/dispatcher.hpp>

#include <chrono>
#include <iostream>
#include <string>

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
    using rebuntu::runtime::dispatcher::Dispatcher;
    using rebuntu::runtime::dispatcher::DispatcherContext;
    using rebuntu::runtime::dispatcher::ExecutionModeSelection;
    using rebuntu::runtime::dispatcher::DispatcherDecision;
    using rebuntu::runtime::dispatcher::DispatcherRegistry;
    using rebuntu::runtime::work::ExecutionMode;
    using rebuntu::runtime::work::Job;
    using rebuntu::runtime::work::Task;

    std::cout << "Testing Phase 4.5 Dispatcher implementation...\n";

    // Test ExecutionModeSelection
    {
        ExecutionModeSelection sel;
        sel.mode = ExecutionMode::kSubprocess;
        sel.reason = "test_reason";
        
        CHECK(sel.mode == ExecutionMode::kSubprocess);
        CHECK(sel.reason == "test_reason");
    }

    // Test DispatcherContext
    {
        DispatcherContext ctx;
        
        CHECK(ctx.subprocess_available == true);
        CHECK(ctx.systemd_unit_available == false);
        CHECK(ctx.dbus_available == false);
        CHECK(ctx.pending_work_count == 0);
        CHECK(ctx.max_concurrent_executions == 100);
    }

    // Test DispatcherDecision - accept
    {
        ExecutionModeSelection sel;
        sel.mode = ExecutionMode::kInline;
        sel.reason = "test";
        
        auto decision = DispatcherDecision::accept(sel);
        
        CHECK(decision.accepted == true);
        CHECK(decision.selection.mode == ExecutionMode::kInline);
    }

    // Test DispatcherDecision - reject
    {
        auto decision = DispatcherDecision::reject("E_TEST", "test error");
        
        CHECK(decision.accepted == false);
        CHECK(decision.selection.reason == "rejected");
    }

    // Test DispatcherRegistry - basic registration
    {
        DispatcherRegistry registry;
        
        registry.register_mechanism("docker", ExecutionMode::kSubprocess);
        registry.register_mechanism("systemd", ExecutionMode::kSystemdUnit);
        
        auto docker_mode = registry.find_mechanism("docker");
        CHECK(docker_mode.has_value());
        CHECK(docker_mode.value() == ExecutionMode::kSubprocess);
        
        auto systemd_mode = registry.find_mechanism("systemd");
        CHECK(systemd_mode.has_value());
        CHECK(systemd_mode.value() == ExecutionMode::kSystemdUnit);
    }

    // Test DispatcherRegistry - substring matching
    {
        DispatcherRegistry registry;
        
        registry.register_mechanism("docker", ExecutionMode::kSubprocess);
        
        auto mode = registry.find_mechanism("docker-container-123");
        CHECK(mode.has_value());
        CHECK(mode.value() == ExecutionMode::kSubprocess);
    }

    // Test DispatcherRegistry - no match returns nullopt
    {
        DispatcherRegistry registry;
        
        auto mode = registry.find_mechanism("nonexistent");
        CHECK(!mode.has_value());
    }

    // Test DispatcherRegistry - all mechanisms
    {
        DispatcherRegistry registry;
        
        registry.register_mechanism("docker", ExecutionMode::kSubprocess);
        registry.register_mechanism("systemd", ExecutionMode::kSystemdUnit);
        
        auto all = registry.all();
        CHECK(all.size() == 2);
        
        bool found_docker = false;
        bool found_systemd = false;
        for (const auto& [name, mode] : all) {
            if (name == "docker" && mode == ExecutionMode::kSubprocess) {
                found_docker = true;
            }
            if (name == "systemd" && mode == ExecutionMode::kSystemdUnit) {
                found_systemd = true;
            }
        }
        
        CHECK(found_docker);
        CHECK(found_systemd);
    }

    // Test Dispatcher - construction and initial state
    {
        auto on_dispatch = [](const Job&) {};
        Dispatcher dispatcher(on_dispatch);
        
        CHECK(dispatcher.get_pending_count() == 0);
        CHECK(!dispatcher.is_backpressured());
    }

    // Test Dispatcher - increment/decrement pending
    {
        auto on_dispatch = [](const Job&) {};
        auto dispatcher = Dispatcher(on_dispatch);
        
        dispatcher.increment_pending();
        CHECK(dispatcher.get_pending_count() == 1);
        
        dispatcher.increment_pending();
        CHECK(dispatcher.get_pending_count() == 2);
        
        dispatcher.decrement_pending();
        CHECK(dispatcher.get_pending_count() == 1);
        
        dispatcher.decrement_pending();
        CHECK(dispatcher.get_pending_count() == 0);
        
        // Decrement below zero should not underflow
        dispatcher.decrement_pending();
        CHECK(dispatcher.get_pending_count() == 0);
    }

    // Test Dispatcher - dispatch with valid job
    {
        auto on_dispatch = [](const Job&) {};
        DispatcherContext ctx;
        
        Job job;
        job.id.value = "test-job-123";
        job.task_id = "test-task-456";
        
        Dispatcher dispatcher(on_dispatch);
        
        auto decision = dispatcher.dispatch(job, ctx);
        
        CHECK(decision.accepted == true);
    }

    // Test Dispatcher - dispatch with empty job ID
    {
        auto on_dispatch = [](const Job&) {};
        DispatcherContext ctx;
        
        Job job;
        job.id.value = "";  // Empty job ID
        job.task_id = "test-task-456";
        
        Dispatcher dispatcher(on_dispatch);
        
        auto decision = dispatcher.dispatch(job, ctx);
        
        CHECK(decision.accepted == false);
    }

    // Test Dispatcher - dispatch with empty task_id
    {
        auto on_dispatch = [](const Job&) {};
        DispatcherContext ctx;
        
        Job job;
        job.id.value = "test-job-123";
        job.task_id = "";  // Empty task_id
        
        Dispatcher dispatcher(on_dispatch);
        
        auto decision = dispatcher.dispatch(job, ctx);
        
        CHECK(decision.accepted == false);
    }

    // Test select_execution_mode - subprocess available
    {
        auto on_dispatch = [](const Job&) {};
        auto dispatcher = Dispatcher(on_dispatch);
        
        Task task;
        task.unit_id = "some-unit";
        
        DispatcherContext ctx;
        ctx.subprocess_available = true;
        
        auto mode = dispatcher.select_execution_mode(task, ctx);
        
        CHECK(mode.mode == ExecutionMode::kSubprocess);
    }

    // Test select_execution_mode - fallback to inline
    {
        auto on_dispatch = [](const Job&) {};
        auto dispatcher = Dispatcher(on_dispatch);
        
        Task task;
        task.unit_id = "";  // No unit
        
        DispatcherContext ctx;
        ctx.subprocess_available = false;
        ctx.systemd_unit_available = false;
        
        auto mode = dispatcher.select_execution_mode(task, ctx);
        
        CHECK(mode.mode == ExecutionMode::kInline);
        CHECK(mode.reason == "fallback_inline");
    }

    std::cout << "\nDispatcher implementation tests completed.\n";

    if (g_failures != 0) {
        std::cerr << g_failures << " check(s) FAILED\n";
        return 1;
    }

    std::cout << "test_dispatcher: OK\n";
    return 0;
}