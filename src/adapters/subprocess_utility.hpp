// rebuntu::adapters::SubprocessUtility — Bounded Subprocess Execution (Phase 6.67)
//
// This module provides a reusable subprocess execution utility for adapters
// that need to run external programs. All subprocess execution converges here:
//
//   Adapter → SubprocessUtility → fork/execve (no shell) → Linux
//
// Design Principles:
//   - Single source of truth: all adapter subprocess execution uses this utility
//   - Native Linux primitives: fork/execve, no shell interpretation
//   - Bounded output: prevents resource exhaustion from command stdout/stderr
//   - Timeout support: configurable operation timeouts via select()
//   - Cancellation-aware: cooperative cancellation via flag checking

#pragma once

#include <string>
#include <vector>
#include <optional>
#include <chrono>

namespace rebuntu::adapters {

class SubprocessUtility {
public:
    // Construct with a timeout for subprocess execution
    explicit SubprocessUtility(std::chrono::milliseconds default_timeout = std::chrono::seconds(30));
    
    ~SubprocessUtility() = default;
    
    // Execute a subprocess and capture output
    //
    // Returns:
    //   - success: exit_code == 0, stdout contains command output
    //   - failure: exit_code != 0 or process terminated by signal
    struct ExecutionResult {
        bool success;                          // True if exit code was 0
        int exit_code;                         // Raw exit code (0-255)
        std::string stdout_output;             // Captured standard output (bounded)
        std::string stderr_output;             // Captured standard error (bounded)
        std::chrono::milliseconds duration_ms; // Execution time
    };
    
    // Execute subprocess with timeout and bounded output
    //
    // argv is passed directly to execve - no shell interpretation.
    // stdout/stderr are captured and bounded to prevent resource exhaustion.
    ExecutionResult execute(
        const std::string& executable,
        const std::vector<std::string>& argv,
        std::optional<std::string> cwd = std::nullopt,
        std::chrono::milliseconds timeout = std::chrono::seconds(30));
    
    // Execute subprocess with stdin input (for pipe-style operations)
    //
    // stdin_input is written to the child process's stdin before reading stdout.
    ExecutionResult execute_with_stdin(
        const std::string& executable,
        const std::vector<std::string>& argv,
        const std::string& stdin_input,
        std::optional<std::string> cwd = std::nullopt,
        std::chrono::milliseconds timeout = std::chrono::seconds(30));

private:
    // Default timeout for operations that don't specify one
    std::chrono::milliseconds default_timeout_;
    
    // Execute subprocess with pipes for stdout/stderr capture (native implementation)
    ExecutionResult execute_with_pipes(
        const std::string& executable,
        const std::vector<std::string>& argv,
        std::optional<std::string> cwd,
        std::chrono::milliseconds timeout,
        std::optional<std::string> stdin_input);
};

}  // namespace rebuntu::adapters
