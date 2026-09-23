// Unit tests for rebuntu::runtime::executor (Phase 0.13)
#include <runtime/executor.hpp>

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
    using rebuntu::runtime::executor::ExecutionModeSelector;
    using rebuntu::runtime::executor::ExecutorInvocationContext;
    
    std::cout << "Testing Phase 0.13 Executor contracts...\n";
    
    // Test ExecutionModeSelector string conversions
    CHECK(rebuntu::runtime::executor::to_string(ExecutionModeSelector::kInline) == "inline");
    CHECK(rebuntu::runtime::executor::to_string(ExecutionModeSelector::kSubprocess) == "subprocess");
    CHECK(rebuntu::runtime::executor::to_string(ExecutionModeSelector::kSystemdUnit) == "systemd-unit");
    CHECK(rebuntu::runtime::executor::to_string(ExecutionModeSelector::kDBusMethod) == "dbus-method");
    
    // Test ExecutorInvocationContext defaults
    ExecutorInvocationContext ctx;
    CHECK(ctx.timeout_policy.default_timeout.count() >= 0);
    CHECK(!ctx.cancellation_requested);
    
    std::cout << "\nExecutor contract tests completed.\n";
    
    if (g_failures != 0) {
        std::cerr << g_failures << " check(s) FAILED\n";
        return 1;
    }
    
    std::cout << "test_executor: OK\n";
    return 0;
}
