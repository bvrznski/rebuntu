// rebuntu::runtime::executor — Executor implementation (Phase 4.3)
//
// The Executor is responsible for realizing an already-resolved executable
// specification through the appropriate native/provider boundary, with:
//   - explicit execution context (cwd, environment, timeout, cancellation)
//   - result capture (stdout/stderr, exit code, timing)
//   - post-execution observation and verification handoff
//   - evidence production for audit trail
//
// The Executor is NOT responsible for:
//   - semantic intent creation
//   - policy decisions (authorization, scheduling)
//   - execution context discovery (uses provided context)

#pragma once

#include <system/runtime/contracts.hpp>
#include <system/runtime/work.hpp>
#include <system/core/contracts.hpp>
#include <chrono>
#include <filesystem>
#include <functional>
#include <memory>
#include <optional>
#include <string>
#include <string_view>
#include <vector>

namespace rebuntu::runtime::executor {

// ExecutionModeSelector determines the native mechanism for execution.
// The Executor receives this as a hint and selects the appropriate implementation.
enum class ExecutionModeSelector {
    kInline,        // execute synchronously in current thread
    kSubprocess,    // fork/execve subprocess with stdin/stdout/stderr
    kSystemdUnit,   // delegate to systemd unit activation
    kDBusMethod,    // invoke via D-Bus method call
};

inline std::string_view to_string(ExecutionModeSelector m) {
    switch (m) {
        case ExecutionModeSelector::kInline: return "inline";
        case ExecutionModeSelector::kSubprocess: return "subprocess";
        case ExecutionModeSelector::kSystemdUnit: return "systemd-unit";
        case ExecutionModeSelector::kDBusMethod: return "dbus-method";
    }
    return "unknown";
}

// ExecutorInvocationContext provides the execution environment and constraints.
struct ExecutorInvocationContext {
    runtime::TimeoutPolicy timeout_policy;
    
    // Optional deadline override (if not set, use timeout_policy.default_timeout)
    std::optional<std::chrono::system_clock::time_point> deadline;
    
    // Cancellation request status
    bool cancellation_requested = false;
    
    // Execution context
    std::optional<std::filesystem::path> cwd;           // current working directory
    std::vector<std::string> environment;               // environment variables
    std::optional<int> stdin_fd;                        // optional stdin file descriptor
    std::optional<int> stdout_fd;                       // optional stdout file descriptor
    std::optional<int> stderr_fd;                       // optional stderr file descriptor
    
    // Resource constraints (future: CPU/GPU/memory limits)
    bool cpu_only = false;
    
    // Evidence base for this execution instance
    std::string execution_evidence_id;
};

// ExecutorResult represents the outcome of a single attempt.
struct ExecutorResult {
    core::Outcome outcome;
    
    work::ExecutionId execution_id;
    work::AttemptNumber attempt_number;
    bool is_last_attempt = true;
    
    // Timing breakdown
    std::chrono::milliseconds preparation_duration{0};
    std::chrono::milliseconds execution_duration{0};
    std::chrono::milliseconds verification_duration{0};
    
    // Execution-specific data (subprocess, etc.)
    std::optional<int32_t> pid;                         // process ID if applicable
    std::optional<int> exit_code;                       // native exit code
    std::optional<std::string> stdout_data;             // captured stdout
    std::optional<std::string> stderr_data;             // captured stderr
    
    // Post-execution verification result (if applicable)
    bool postcondition_verified = false;
};

// Executor is the canonical execution abstraction.
//
// Responsibilities:
//   - Execute work items via native provider mechanisms
//   - Handle timeout with cancellation escalation
//   - Capture evidence for audit trail
//   - Support inline, subprocess, systemd-unit, and dbus-mechanism execution
//
// The Executor receives an already-resolved executable specification (Task + Job)
// and executes it using the appropriate native mechanism.
class Executor {
public:
    // Execute function type: takes Task, context, returns Outcome with evidence.
    using ExecuteFn = std::function<core::Outcome(
        const work::Task&, 
        const ExecutorInvocationContext&
    )>;
    
    explicit Executor(std::unique_ptr<Executor> parent = nullptr);
    virtual ~Executor() = default;
    
    // Disable copy/move
    Executor(const Executor&) = delete;
    Executor& operator=(const Executor&) = delete;
    
    // Execute a work item (Task + Job) with the given context.
    // Returns ExecutorResult containing outcome and execution evidence.
    virtual ExecutorResult execute(
        const work::Task& task,
        const work::Job& job,
        const ExecutorInvocationContext& ctx);
    
    // Statistics
    int total_invocations() const { return total_invocations_; }
    int successful_executions() const { return successful_executions_; }
    int failed_executions() const { return failed_executions_; }

protected:
    ExecuteFn execute_fn_;
    
    // Execution counters (thread-safe via atomic if needed in future)
    mutable std::mutex stats_mutex_;
    int total_invocations_ = 0;
    int successful_executions_ = 0;
    int failed_executions_ = 0;
};

// InlineExecutor executes operations synchronously within the calling thread.
//
// This is appropriate for:
//   - read-only operations
//   - operations that don't require subprocess isolation
//   - fast, deterministic operations
class InlineExecutor : public Executor {
public:
    // Constructor with optional custom execute function
    explicit InlineExecutor(
        std::function<core::Outcome(const work::Task&, const ExecutorInvocationContext&)> 
            execute_fn = nullptr);
    
    ~InlineExecutor() override;
    
    // Execute a lambda synchronously in the calling thread.
    core::Outcome execute_inline(std::function<core::Outcome()> op);
};

// SubprocessExecutor executes operations via fork/execve with full control
// over process lifecycle, resource limits, and output capture.
//
// This is appropriate for:
//   - operations that need isolation from parent process
//   - operations that produce significant stdout/stderr
//   - operations that may block or take significant time
class SubprocessExecutor : public Executor {
public:
    explicit SubprocessExecutor();
    
    ~SubprocessExecutor() override;
    
    // Configure resource limits
    void set_max_output_bytes(size_t max) { max_output_bytes_ = max; }
    void set_default_timeout(std::chrono::milliseconds timeout) { default_timeout_ = timeout; }
    
    // Execute a subprocess with the given executable and arguments.
    core::Outcome execute_subprocess(
        const std::string& executable,
        const std::vector<std::string>& argv,
        const ExecutorInvocationContext& ctx);

private:
    size_t max_output_bytes_ = 1024 * 1024;  // 1 MB default
    std::chrono::milliseconds default_timeout_{30000};  // 30 seconds
};

// SystemdExecutor delegates execution to systemd unit activation.
//
// This is appropriate for:
//   - long-running services
//   - operations managed by systemd
//   - operations that should benefit from systemd's restart and supervision
class SystemdExecutor : public Executor {
public:
    explicit SystemdExecutor();
    
    ~SystemdExecutor() override;
    
    // Execute via systemd unit activation.
    core::Outcome execute_systemd_unit(
        const std::string& unit_name,
        const ExecutorInvocationContext& ctx);
};

// DBusExecutor invokes operations via D-Bus method calls.
//
// This is appropriate for:
//   - operations provided by other processes
//   - remote execution scenarios
//   - operations with well-defined D-Bus interfaces
class DBusExecutor : public Executor {
public:
    explicit DBusExecutor();
    
    ~DBusExecutor() override;
    
    // Execute via D-Bus method call.
    core::Outcome execute_dbus_method(
        const std::string& service,
        const std::string& object_path,
        const std::string& interface,
        const std::string& method_name,
        const std::vector<std::string>& args,
        const ExecutorInvocationContext& ctx);
};

// Factory function to create an appropriate executor based on execution mode.
std::unique_ptr<Executor> make_executor(ExecutionModeSelector selector);

}  // namespace rebuntu::runtime::executor