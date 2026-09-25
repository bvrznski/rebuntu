// Integration tests for rebuntu::runtime execution runtime (Phase 0.13)
// Verifies DispatcherContext and basic integration

#include <runtime/dispatcher.hpp>

#include <cstddef>
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
    using rebuntu::runtime::dispatcher::ExecutionModeSelection;
    using rebuntu::runtime::dispatcher::DispatcherContext;
    
    std::cout << "Testing Phase 0.13 execution runtime integration...\n";
    
    // Test: ExecutionModeSelection structure
    {
        ExecutionModeSelection selection{
            .mode = rebuntu::runtime::work::ExecutionMode::kInline,
            .reason = "read-only operation"
        };
        
        CHECK(selection.mode == rebuntu::runtime::work::ExecutionMode::kInline);
        CHECK(selection.reason.find("read-only") != std::string::npos);
    }
    
    // Test: DispatcherContext defaults
    {
        DispatcherContext ctx;
        
        CHECK(ctx.subprocess_available == true);
        CHECK(!ctx.systemd_unit_available);
        CHECK(!ctx.dbus_available);
        CHECK(ctx.pending_work_count == 0);
        CHECK(ctx.max_concurrent_executions == 100);
    }
    
    // Test: DispatcherDecision accept/reject
    {
        auto accept = rebuntu::runtime::dispatcher::DispatcherDecision::accept(
            ExecutionModeSelection{rebuntu::runtime::work::ExecutionMode::kInline, "inline"});
        
        CHECK(accept.accepted == true);
        CHECK(!accept.error.has_value());
        
        auto reject = rebuntu::runtime::dispatcher::DispatcherDecision::reject("E_BUSY", "too many pending");
        
        CHECK(reject.accepted == false);
        CHECK(reject.error.has_value());
    }
    
    // Test: DispatcherRegistry
    {
        rebuntu::runtime::dispatcher::DispatcherRegistry registry;
        
        registry.register_mechanism("subprocess", rebuntu::runtime::work::ExecutionMode::kSubprocess);
        registry.register_mechanism("systemd", rebuntu::runtime::work::ExecutionMode::kSystemdUnit);
        
        auto found = registry.find_mechanism("subprocess");
        CHECK(found.has_value());
        CHECK(*found == rebuntu::runtime::work::ExecutionMode::kSubprocess);
    }
    
    std::cout << "\nExecution runtime integration tests completed.\n";
    
    if (g_failures != 0) {
        std::cerr << g_failures << " check(s) FAILED\n";
        return 1;
    }
    
    std::cout << "test_executor_integration: OK\n";
    return 0;
}
