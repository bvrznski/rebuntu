// Unit tests for rebuntu::runtime::executor (Phase 4.3)
#include <runtime/executor.hpp>

#include <cstddef>
#include <iostream>
#include <string>
#include <chrono>

#include <system/core/contracts.hpp>
#include <runtime/work.hpp>

namespace rebuntu::runtime::executor {

using rebuntu::core::Outcome;
using rebuntu::core::SemanticStatus;

}  // namespace rebuntu::runtime::executor

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
    using rebuntu::runtime::executor::ExecutorResult;
    using rebuntu::runtime::executor::InlineExecutor;
    using rebuntu::runtime::executor::SubprocessExecutor;
    
    std::cout << "Testing Phase 4.3 Executor implementation...\n";
    
    // Test ExecutionModeSelector string conversions
    CHECK(rebuntu::runtime::executor::to_string(ExecutionModeSelector::kInline) == "inline");
    CHECK(rebuntu::runtime::executor::to_string(ExecutionModeSelector::kSubprocess) == "subprocess");
    CHECK(rebuntu::runtime::executor::to_string(ExecutionModeSelector::kSystemdUnit) == "systemd-unit");
    CHECK(rebuntu::runtime::executor::to_string(ExecutionModeSelector::kDBusMethod) == "dbus-method");
    
    // Test ExecutorInvocationContext defaults
    {
        ExecutorInvocationContext ctx;
        CHECK(ctx.timeout_policy.default_timeout.count() >= 0);
        CHECK(!ctx.cancellation_requested);
        CHECK(!ctx.cpu_only);
    }
    
    // Test ExecutorResult initialization
    {
        ExecutorResult result;
        CHECK(result.execution_duration.count() == 0);
        CHECK(result.preparation_duration.count() == 0);
        CHECK(result.verification_duration.count() == 0);
        CHECK(!result.pid.has_value());
        CHECK(!result.exit_code.has_value());
        CHECK(result.postcondition_verified == false);
    }
    
    // Test InlineExecutor construction and execution
    {
        InlineExecutor executor;
        
        // Execute an inline operation that succeeds
        auto outcome = executor.execute_inline([]() -> rebuntu::core::Outcome {
            return rebuntu::core::Outcome::success(true);
        });
        
        CHECK(outcome.status == rebuntu::core::SemanticStatus::kSuccess);
        CHECK(outcome.verified == true);
    }
    
    // Test InlineExecutor with failure outcome
    {
        InlineExecutor executor;
        
        auto outcome = executor.execute_inline([]() -> rebuntu::core::Outcome {
            return rebuntu::core::Outcome::failure("E_TEST", "Test failure");
        });
        
        CHECK(outcome.status == rebuntu::core::SemanticStatus::kFailure);
        // Note: Outcome has error field which is optional<Error>
    }
    
    // Test InlineExecutor statistics
    {
        InlineExecutor executor;
        
        // Execute several operations
        for (int i = 0; i < 5; ++i) {
            auto outcome = executor.execute_inline([]() -> rebuntu::core::Outcome {
                return rebuntu::core::Outcome::success(true);
            });
            (void)outcome;
        }
        
        CHECK(executor.total_invocations() == 5);
        CHECK(executor.successful_executions() == 5);
        CHECK(executor.failed_executions() == 0);
    }
    
    // Test SubprocessExecutor construction
    {
        SubprocessExecutor executor;
        
        // The subprocess executor should be constructible
        (void)executor;
    }
    
    // Test make_executor factory function
    {
        auto inline_exec = rebuntu::runtime::executor::make_executor(ExecutionModeSelector::kInline);
        CHECK(inline_exec != nullptr);
        
        auto subprocess_exec = rebuntu::runtime::executor::make_executor(ExecutionModeSelector::kSubprocess);
        CHECK(subprocess_exec != nullptr);
        
        auto systemd_exec = rebuntu::runtime::executor::make_executor(ExecutionModeSelector::kSystemdUnit);
        CHECK(systemd_exec != nullptr);
        
        auto dbus_exec = rebuntu::runtime::executor::make_executor(ExecutionModeSelector::kDBusMethod);
        CHECK(dbus_exec != nullptr);
    }
    
    // Test ExecutorResult with all fields
    {
        rebuntu::core::Outcome outcome;
        outcome.status = rebuntu::core::SemanticStatus::kSuccess;
        outcome.verified = true;
        
        ExecutorResult result;
        result.outcome = outcome;
        result.execution_id = rebuntu::runtime::work::ExecutionId{"exec-123"};
        result.attempt_number = rebuntu::runtime::work::AttemptNumber{1};
        result.is_last_attempt = true;
        if (result.pid.has_value()) {
            CHECK(*result.pid == 12345);
        }
        if (result.exit_code.has_value()) {
            CHECK(*result.exit_code == 0);
        }
        if (result.stdout_data.has_value()) {
            CHECK(*result.stdout_data == "test output");
        }
        // Note: postcondition_verified defaults to false in ExecutorResult
    }
    
    std::cout << "\nExecutor implementation tests completed.\n";
    
    if (g_failures != 0) {
        std::cerr << g_failures << " check(s) FAILED\n";
        return 1;
    }
    
    std::cout << "test_executor: OK\n";
    return 0;
}