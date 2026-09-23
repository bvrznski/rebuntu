// rebuntu::runtime::executor — Executor implementation (Phase 4.3)
//
// The Executor is responsible for realizing an already-resolved executable
// specification through the appropriate native/provider boundary, with:
//   - explicit execution context (cwd, environment, timeout, cancellation)
//   - result capture (stdout/stderr, exit code, timing)
//   - post-execution observation and verification handoff
//   - evidence production for audit trail

#include <system/runtime/executor.hpp>

#include <array>
#include <cstring>
#include <fcntl.h>
#include <memory>
#include <sys/wait.h>
#include <unistd.h>
#include <chrono>
#include <iostream>
#include <sstream>

namespace rebuntu::runtime::executor {

// Executor base class implementation
Executor::Executor(std::unique_ptr<Executor> parent)
    : execute_fn_(nullptr),
      stats_mutex_(),
      total_invocations_(0),
      successful_executions_(0),
      failed_executions_(0) {
    (void)parent;  // Optional parent for hierarchical executors
}

ExecutorResult Executor::execute(
    const work::Task& task,
    const work::Job& job,
    const ExecutorInvocationContext& ctx) {
    
    (void)task;  // Subclasses may use this
    (void)job;
    (void)ctx;   // Subclasses may use this
    
    total_invocations_++;
    
    auto start = std::chrono::steady_clock::now();
    
    ExecutorResult exec_result{
        .outcome = core::Outcome::completed(),
        .execution_id = work::ExecutionId{job.id.value + "-attempt-1"},
        .attempt_number = work::AttemptNumber{1},
        .is_last_attempt = true,
        .pid = std::nullopt,
        .exit_code = std::nullopt,
        .stdout_data = std::nullopt,
        .stderr_data = std::nullopt,
        .postcondition_verified = false
    };
    
    // Execute via the execute_fn_ if provided
    if (execute_fn_) {
        exec_result.outcome = execute_fn_(task, ctx);
    }
    
    auto end = std::chrono::steady_clock::now();
    exec_result.execution_duration = 
        std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    
    // Update statistics
    if (exec_result.outcome.status == core::SemanticStatus::kSuccess) {
        successful_executions_++;
    } else {
        failed_executions_++;
    }
    
    return exec_result;
}

// InlineExecutor implementation
InlineExecutor::InlineExecutor(
    std::function<core::Outcome(const work::Task&, const ExecutorInvocationContext&)> execute_fn)
    : Executor(nullptr) {
    if (execute_fn) {
        execute_fn_ = std::move(execute_fn);
    } else {
        // Default: success for inline execution
        execute_fn_ = [](const work::Task&, const ExecutorInvocationContext&) -> core::Outcome {
            return core::Outcome::completed();
        };
    }
}

InlineExecutor::~InlineExecutor() = default;

core::Outcome InlineExecutor::execute_inline(std::function<core::Outcome()> op) {
    total_invocations_++;
    
    auto start = std::chrono::steady_clock::now();
    
    core::Outcome outcome = op();
    
    auto end = std::chrono::steady_clock::now();
    
    if (outcome.status == core::SemanticStatus::kSuccess) {
        successful_executions_++;
    } else {
        failed_executions_++;
    }
    
    return outcome;
}

// ============================================================================
// SubprocessExecutor implementation
// ============================================================================

namespace subprocess_impl {

struct ExecutionResult {
    int exit_code;
    std::string stdout_data;
    std::string stderr_data;
};

static ExecutionResult execute_with_timeout(
    const std::string& executable,
    const std::vector<std::string>& argv,
    std::optional<std::chrono::system_clock::time_point> deadline,
    size_t max_output_bytes
) {
    ExecutionResult result{0, "", ""};
    
    // Create pipes for stdout and stderr
    int stdout_pipe[2];
    int stderr_pipe[2];
    
    if (pipe(stdout_pipe) < 0 || pipe(stderr_pipe) < 0) {
        result.exit_code = -1;
        result.stderr_data = "Failed to create pipes";
        return result;
    }
    
    pid_t pid = fork();
    
    if (pid == 0) {
        // Child process
        try {
            // Close read ends of pipes
            close(stdout_pipe[0]);
            close(stderr_pipe[0]);
            
            // Redirect stdout/stderr to write ends
            dup2(stdout_pipe[1], STDOUT_FILENO);
            dup2(stderr_pipe[1], STDERR_FILENO);
            
            // Close the write ends (now duplicated)
            close(stdout_pipe[1]);
            close(stderr_pipe[1]);
            
            // Prepare argv array
            std::vector<char*> c_argv;
            for (const auto& arg : argv) {
                c_argv.push_back(&const_cast<std::string&>(arg)[0]);
            }
            c_argv.push_back(nullptr);
            
            // Execute the program (no shell)
            execv(executable.c_str(), c_argv.data());
            
            // If execv returns, it failed
            _exit(127);
            
        } catch (...) {
            _exit(127);
        }
    } else if (pid > 0) {
        close(stdout_pipe[1]);
        close(stderr_pipe[1]);
        
        // Read from pipes
        std::array<char, 4096> buffer;
        ssize_t bytes_read;
        
        while ((bytes_read = read(stdout_pipe[0], buffer.data(), buffer.size())) > 0) {
            size_t new_len = result.stdout_data.length() + bytes_read;
            if (new_len <= max_output_bytes) {
                result.stdout_data.append(buffer.data(), bytes_read);
            } else {
                // Truncate if too large
                size_t to_take = max_output_bytes - result.stdout_data.length();
                if (to_take > 0) {
                    result.stdout_data.append(buffer.data(), to_take);
                }
                break;
            }
        }
        
        while ((bytes_read = read(stderr_pipe[0], buffer.data(), buffer.size())) > 0) {
            size_t new_len = result.stderr_data.length() + bytes_read;
            if (new_len <= max_output_bytes) {
                result.stderr_data.append(buffer.data(), bytes_read);
            } else {
                // Truncate if too large
                size_t to_take = max_output_bytes - result.stderr_data.length();
                if (to_take > 0) {
                    result.stderr_data.append(buffer.data(), to_take);
                }
                break;
            }
        }
        
        close(stdout_pipe[0]);
        close(stderr_pipe[0]);
        
        // Wait for child
        int status;
        waitpid(pid, &status, 0);
        
        if (WIFEXITED(status)) {
            result.exit_code = WEXITSTATUS(status);
        } else if (WIFSIGNALED(status)) {
            result.exit_code = -WTERMSIG(status);  // Negative signal number
        } else {
            result.exit_code = -1;
        }
        
    } else {
        // Fork failed
        close(stdout_pipe[0]);
        close(stderr_pipe[0]);
        close(stdout_pipe[1]);
        close(stderr_pipe[1]);
        
        result.exit_code = -1;
        result.stderr_data = "Failed to fork process";
    }
    
    return result;
}

}  // namespace subprocess_impl

SubprocessExecutor::SubprocessExecutor() : Executor(nullptr) {
}

SubprocessExecutor::~SubprocessExecutor() = default;

core::Outcome SubprocessExecutor::execute_subprocess(
    const std::string& executable,
    const std::vector<std::string>& argv,
    const ExecutorInvocationContext& ctx) {
    
    auto start = std::chrono::steady_clock::now();
    
    // Compute timeout deadline
    auto deadline = ctx.deadline;
    if (!deadline.has_value()) {
        auto now = std::chrono::system_clock::now();
        deadline = now + ctx.timeout_policy.default_timeout;
    }
    
    auto exec_result = subprocess_impl::execute_with_timeout(
        executable,
        argv,
        deadline,
        max_output_bytes_
    );
    
    auto end = std::chrono::steady_clock::now();
    
    core::Outcome outcome;
    
    if (exec_result.exit_code == 0) {
        // Success
        outcome = core::Outcome::success(true);
    } else if (exec_result.exit_code == -127) {
        // Exec failed
        outcome = core::Outcome::failure(
            "E_EXEC_FAILED",
            "Failed to execute subprocess: " + executable
        );
    } else if (exec_result.exit_code < 0 && exec_result.exit_code != -127) {
        // Process was terminated by signal
        int sig = -exec_result.exit_code;
        outcome = core::Outcome::failure(
            "E_SIGNAL_TERMINATED",
            "Process terminated by signal " + std::to_string(sig)
        );
    } else {
        // Non-zero exit code
        outcome = core::Outcome::failure(
            "E_EXIT_CODE_" + std::to_string(exec_result.exit_code),
            "Subprocess exited with code " + std::to_string(exec_result.exit_code) +
                ": " + exec_result.stderr_data
        );
    }
    
    // Add evidence if available
    if (!exec_result.stdout_data.empty()) {
        core::Evidence ev;
        ev.source = "subprocess-stdout";
        ev.value = exec_result.stdout_data.substr(0, 1024);
        ev.captured_at = std::to_string(std::chrono::system_clock::now().time_since_epoch().count());
        outcome.evidence.push_back(ev);
    }
    
    if (!exec_result.stderr_data.empty()) {
        core::Evidence ev;
        ev.source = "subprocess-stderr";
        ev.value = exec_result.stderr_data.substr(0, 1024);
        ev.captured_at = std::to_string(std::chrono::system_clock::now().time_since_epoch().count());
        outcome.evidence.push_back(ev);
    }
    
    return outcome;
}

// SystemdExecutor implementation
SystemdExecutor::SystemdExecutor() : Executor(nullptr) {
}

SystemdExecutor::~SystemdExecutor() = default;

core::Outcome SystemdExecutor::execute_systemd_unit(
    const std::string& unit_name,
    const ExecutorInvocationContext& ctx) {
    
    (void)ctx;  // Context for future timeout/cancellation
    
    core::Outcome outcome;
    
    // For now, return a placeholder that systemd integration is not yet implemented
    outcome = core::Outcome::unknown(
        "systemd unit execution not yet implemented: " + unit_name
    );
    
    return outcome;
}

// DBusExecutor implementation
DBusExecutor::DBusExecutor() : Executor(nullptr) {
}

DBusExecutor::~DBusExecutor() = default;

core::Outcome DBusExecutor::execute_dbus_method(
    const std::string& service,
    const std::string& object_path,
    const std::string& interface,
    const std::string& method_name,
    const std::vector<std::string>& args,
    const ExecutorInvocationContext& ctx) {
    
    (void)service;
    (void)object_path;
    (void)interface;
    (void)method_name;
    (void)args;
    (void)ctx;  // Context for future timeout/cancellation
    
    core::Outcome outcome;
    
    // For now, return a placeholder that D-Bus integration is not yet implemented
    outcome = core::Outcome::unknown(
        "D-Bus method execution not yet implemented: " + service + "." + method_name
    );
    
    return outcome;
}

// Factory function
std::unique_ptr<Executor> make_executor(ExecutionModeSelector selector) {
    switch (selector) {
        case ExecutionModeSelector::kInline:
            return std::make_unique<InlineExecutor>();
            
        case ExecutionModeSelector::kSubprocess:
            return std::make_unique<SubprocessExecutor>();
            
        case ExecutionModeSelector::kSystemdUnit:
            return std::make_unique<SystemdExecutor>();
            
        case ExecutionModeSelector::kDBusMethod:
            return std::make_unique<DBusExecutor>();
    }
    
    // Default to inline for unknown selectors
    return std::make_unique<InlineExecutor>();
}

}  // namespace rebuntu::runtime::executor