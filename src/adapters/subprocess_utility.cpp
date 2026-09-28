// rebuntu::adapters::SubprocessUtility — Bounded Subprocess Execution Implementation (Phase 6.67)
//
// This module provides a reusable subprocess execution utility for adapters.
// All subprocess execution converges here to avoid duplicate fork/execve patterns.

#include "subprocess_utility.hpp"

#include <cstdlib>
#include <string>
#include <vector>
#include <optional>
#include <chrono>

#include <array>
#include <cerrno>
#include <cstring>
#include <fcntl.h>
#include <poll.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

namespace rebuntu::adapters {

// Maximum output buffer size to prevent resource exhaustion
static constexpr size_t kMaxOutputSize = 16384;  // 16KB

SubprocessUtility::SubprocessUtility(std::chrono::milliseconds default_timeout)
    : default_timeout_(default_timeout) {}

SubprocessUtility::ExecutionResult SubprocessUtility::execute(
    const std::string& executable,
    const std::vector<std::string>& argv,
    std::optional<std::string> cwd,
    std::chrono::milliseconds timeout) {
    
    return execute_with_pipes(executable, argv, cwd, timeout, std::nullopt);
}

SubprocessUtility::ExecutionResult SubprocessUtility::execute_with_stdin(
    const std::string& executable,
    const std::vector<std::string>& argv,
    const std::string& stdin_input,
    std::optional<std::string> cwd,
    std::chrono::milliseconds timeout) {
    
    return execute_with_pipes(executable, argv, cwd, timeout, stdin_input);
}

SubprocessUtility::ExecutionResult SubprocessUtility::execute_with_pipes(
    const std::string& executable,
    const std::vector<std::string>& argv,
    std::optional<std::string> cwd,
    std::chrono::milliseconds timeout,
    std::optional<std::string> stdin_input) {
    
    auto start_time = std::chrono::steady_clock::now();
    
    ExecutionResult result{
        .success = false,
        .exit_code = -1,
        .stdout_output = "",
        .stderr_output = "",
        .duration_ms = std::chrono::milliseconds(0)
    };
    
    // Create pipes for stdout and stderr
    int stdout_pipe[2];
    int stderr_pipe[2];
    int stdin_pipe[2] = {-1, -1};
    
    if (pipe(stdout_pipe) != 0) {
        return result;
    }
    
    if (pipe(stderr_pipe) != 0) {
        close(stdout_pipe[0]);
        close(stdout_pipe[1]);
        return result;
    }
    
    // Create stdin pipe if input is provided
    std::optional<int> stdin_read_fd = std::nullopt;
    if (stdin_input.has_value() && !stdin_input->empty()) {
        if (pipe(stdin_pipe) != 0) {
            close(stdout_pipe[0]);
            close(stdout_pipe[1]);
            close(stderr_pipe[0]);
            close(stderr_pipe[1]);
            return result;
        }
        stdin_read_fd = stdin_pipe[0];
    }
    
    pid_t pid = fork();
    
    if (pid == -1) {
        // Fork failed
        close(stdout_pipe[0]);
        close(stdout_pipe[1]);
        close(stderr_pipe[0]);
        close(stderr_pipe[1]);
        if (stdin_read_fd.has_value()) close(stdin_pipe[0]);
        return result;
    }
    
    if (pid == 0) {
        // Child process
        
        // Close unused pipe ends
        close(stdout_pipe[0]);
        close(stderr_pipe[0]);
        
        // Redirect stdout to pipe
        dup2(stdout_pipe[1], STDOUT_FILENO);
        
        // Redirect stderr to pipe
        dup2(stderr_pipe[1], STDERR_FILENO);
        
        // Redirect stdin from pipe if provided
        if (stdin_read_fd.has_value()) {
            close(stdin_pipe[1]);  // Close write end in child
            dup2(stdin_pipe[0], STDIN_FILENO);
            close(stdin_pipe[0]);
        }
        
        // Change working directory if provided
        if (cwd.has_value()) {
            if (chdir(cwd->c_str()) != 0) {
                _exit(127);
            }
        }
        
        // Build argv array
        std::vector<char*> c_argv;
        c_argv.push_back(const_cast<char*>(executable.c_str()));
        for (const auto& arg : argv) {
            c_argv.push_back(const_cast<char*>(arg.c_str()));
        }
        c_argv.push_back(nullptr);
        
        // Execute the program
        execv(executable.c_str(), c_argv.data());
        
        // If we get here, exec failed
        _exit(127);
    }
    
    // Parent process
    
    // Close write ends of output pipes (child will close its write ends on exit)
    close(stdout_pipe[1]);
    close(stderr_pipe[1]);
    
    // Close stdin write end if created
    if (stdin_read_fd.has_value()) {
        close(stdin_pipe[0]);  // Read end
        // Write to child stdin and then close
        ssize_t written = write(stdin_pipe[1], stdin_input->c_str(), stdin_input->length());
        (void)written;  // Ignore partial writes - child may not read all
        close(stdin_pipe[1]);
    }
    
    // Read stdout with timeout
    std::string stdout_output;
    {
        fd_set read_fds;
        FD_ZERO(&read_fds);
        FD_SET(stdout_pipe[0], &read_fds);
        
        struct timeval tv;
        long timeout_ms = timeout.count() > 0 ? timeout.count() : default_timeout_.count();
        tv.tv_sec = timeout_ms / 1000;
        tv.tv_usec = (timeout_ms % 1000) * 1000;
        
        char buffer[4096];
        ssize_t bytes_read;
        
        while ((bytes_read = select(stdout_pipe[0] + 1, &read_fds, nullptr, nullptr, &tv)) > 0) {
            if (FD_ISSET(stdout_pipe[0], &read_fds)) {
                ssize_t n = read(stdout_pipe[0], buffer, sizeof(buffer));
                if (n <= 0) break;
                
                // Bounded output to prevent resource exhaustion
                if (stdout_output.length() + n > kMaxOutputSize) {
                    size_t remaining = kMaxOutputSize - stdout_output.length();
                    stdout_output.append(buffer, remaining);
                    break;
                }
                
                stdout_output.append(buffer, n);
            }
            
            // Reset timeout for next iteration
            tv.tv_sec = timeout_ms / 1000;
            tv.tv_usec = (timeout_ms % 1000) * 1000;
            FD_ZERO(&read_fds);
            FD_SET(stdout_pipe[0], &read_fds);
        }
    }
    
    // Read stderr with same timeout
    std::string stderr_output;
    {
        fd_set read_fds;
        FD_ZERO(&read_fds);
        FD_SET(stderr_pipe[0], &read_fds);
        
        struct timeval tv;
        long timeout_ms = timeout.count() > 0 ? timeout.count() : default_timeout_.count();
        tv.tv_sec = timeout_ms / 1000;
        tv.tv_usec = (timeout_ms % 1000) * 1000;
        
        char buffer[4096];
        ssize_t bytes_read;
        
        while ((bytes_read = select(stderr_pipe[0] + 1, &read_fds, nullptr, nullptr, &tv)) > 0) {
            if (FD_ISSET(stderr_pipe[0], &read_fds)) {
                ssize_t n = read(stderr_pipe[0], buffer, sizeof(buffer));
                if (n <= 0) break;
                
                // Bounded output
                if (stderr_output.length() + n > kMaxOutputSize) {
                    size_t remaining = kMaxOutputSize - stderr_output.length();
                    stderr_output.append(buffer, remaining);
                    break;
                }
                
                stderr_output.append(buffer, n);
            }
            
            tv.tv_sec = timeout_ms / 1000;
            tv.tv_usec = (timeout_ms % 1000) * 1000;
            FD_ZERO(&read_fds);
            FD_SET(stderr_pipe[0], &read_fds);
        }
    }
    
    close(stdout_pipe[0]);
    close(stderr_pipe[0]);
    
    // Wait for process to complete
    int status = 0;
    pid_t waited_pid = waitpid(pid, &status, 0);
    
    if (waited_pid == -1) {
        result.exit_code = -1;
    } else {
        if (WIFEXITED(status)) {
            result.exit_code = WEXITSTATUS(status);
            result.success = (result.exit_code == 0);
        } else if (WIFSIGNALED(status)) {
            result.exit_code = -1;  // Terminated by signal
        }
    }
    
    auto end_time = std::chrono::steady_clock::now();
    result.duration_ms = std::chrono::duration_cast<std::chrono::milliseconds>(
        end_time - start_time);
    
    result.stdout_output = std::move(stdout_output);
    result.stderr_output = std::move(stderr_output);
    
    return result;
}

}  // namespace rebuntu::adapters