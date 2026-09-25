// rebuntu::semantic::subprocess — Subprocess Execution for bitnet.cpp (Phase 3.2)
//
// Implements subprocess execution with:
//   - Native Linux fork/execve
//   - Bounded stdout/stderr capture
//   - Timeout enforcement via SIGTERM/SIGKILL
//   - CPU-only enforcement via CUDA_VISIBLE_DEVICES=""

#include <system/semantic/subprocess.hpp>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <fcntl.h>
#include <cstring>
#include <cerrno>
#include <iostream>
#include <thread>
#include <poll.h>

namespace rebuntu::semantic {

SubprocessExecutor::SubprocessExecutor() = default;

void SubprocessExecutor::apply_cpu_only_env(std::map<std::string, std::string>& env) const {
    if (env.find("CUDA_VISIBLE_DEVICES") == env.end()) {
        env["CUDA_VISIBLE_DEVICES"] = "";
    }
}

bool SubprocessExecutor::setup_child_environment(SubprocessOptions& opts) const {
    // Apply CPU-only policy
    if (opts.cpu_only) {
        apply_cpu_only_env(opts.env);
    }
    
    // Add default environment variables that may be needed
    if (opts.env.find("PATH") == opts.env.end()) {
        opts.env["PATH"] = "/usr/local/bin:/usr/bin:/bin";
    }
    
    return true;
}

SubprocessResult SubprocessExecutor::execute(const SubprocessOptions& opts) {
    SubprocessOptions working_opts = opts;
    setup_child_environment(working_opts);
    
    // Create pipes for stdout/stderr capture
    int stdout_pipe[2];
    int stderr_pipe[2];
    
    if (working_opts.capture_stdout) {
        if (pipe(stdout_pipe) == -1) {
            return SubprocessResult::failure(errno, "Failed to create stdout pipe");
        }
    }
    
    if (working_opts.capture_stderr) {
        if (pipe(stderr_pipe) == -1) {
            if (working_opts.capture_stdout) {
                close(stdout_pipe[0]);
                close(stdout_pipe[1]);
            }
            return SubprocessResult::failure(errno, "Failed to create stderr pipe");
        }
    }
    
    // Fork the child process
    pid_t pid = fork();
    
    if (pid == -1) {
        if (working_opts.capture_stdout) {
            close(stdout_pipe[0]);
            close(stdout_pipe[1]);
        }
        if (working_opts.capture_stderr) {
            close(stderr_pipe[0]);
            close(stderr_pipe[1]);
        }
        return SubprocessResult::failure(errno, "Failed to fork child process");
    }
    
    if (pid == 0) {
        // Child process
        
        // Close unused pipe ends
        if (working_opts.capture_stdout) {
            close(stdout_pipe[0]);
        }
        if (working_opts.capture_stderr) {
            close(stderr_pipe[0]);
        }
        
        // Redirect stdout/stderr to pipes if enabled
        if (working_opts.capture_stdout && dup2(stdout_pipe[1], STDOUT_FILENO) == -1) {
            _exit(127);
        }
        if (working_opts.capture_stderr && dup2(stderr_pipe[1], STDERR_FILENO) == -1) {
            _exit(127);
        }
        
        // Change to working directory if provided
        if (working_opts.cwd.has_value()) {
            if (chdir(working_opts.cwd->c_str()) == -1) {
                _exit(127);
            }
        }
        
        // Build argv array
        std::vector<char*> c_argv;
        c_argv.reserve(working_opts.argv.size() + 1);
        for (const auto& arg : working_opts.argv) {
            c_argv.push_back(const_cast<char*>(arg.c_str()));
        }
        c_argv.push_back(nullptr);
        
        // Build envp array
        std::vector<std::string> env_strings;
        std::vector<char*> env_cstrs;
        env_strings.reserve(working_opts.env.size());
        env_cstrs.reserve(working_opts.env.size() + 1);
        
        for (const auto& [key, value] : working_opts.env) {
            env_strings.push_back(key + "=" + value);
        }
        for (auto& s : env_strings) {
            env_cstrs.push_back(&s[0]);
        }
        env_cstrs.push_back(nullptr);
        
        // Execute the program
        execve(working_opts.executable.c_str(), c_argv.data(), env_cstrs.data());
        
        // If we get here, execve failed
        _exit(127);
    }
    
    // Parent process - set up timeout handling and wait
    
    // Close write ends of pipes
    if (working_opts.capture_stdout) {
        close(stdout_pipe[1]);
    }
    if (working_opts.capture_stderr) {
        close(stderr_pipe[1]);
    }
    
    // Read from pipes in background threads would be ideal, but for simplicity
    // we'll read with a timeout using select()
    
    std::string stdout_data;
    std::string stderr_data;
    
    auto start_time = std::chrono::steady_clock::now();
    
    if (working_opts.capture_stdout && stdout_pipe[0] >= 0) {
        fd_set read_fds;
        FD_ZERO(&read_fds);
        FD_SET(stdout_pipe[0], &read_fds);
        
        struct timeval tv{};
        tv.tv_sec = working_opts.timeout.count() / 1000;
        tv.tv_usec = (working_opts.timeout.count() % 1000) * 1000;
        
        char buffer[256];
        ssize_t bytes_read;
        while ((bytes_read = select(stdout_pipe[0] + 1, &read_fds, nullptr, nullptr, &tv)) > 0) {
            if (FD_ISSET(stdout_pipe[0], &read_fds)) {
                ssize_t n = read(stdout_pipe[0], buffer, sizeof(buffer));
                if (n <= 0) break;
                
                // Bounded output
                size_t new_size = stdout_data.size() + static_cast<size_t>(n);
                if (new_size <= working_opts.max_output_bytes) {
                    stdout_data.append(buffer, n);
                }
            }
            
            FD_ZERO(&read_fds);
            FD_SET(stdout_pipe[0], &read_fds);
            tv.tv_sec = working_opts.timeout.count() / 1000;
            tv.tv_usec = (working_opts.timeout.count() % 1000) * 1000;
        }
        close(stdout_pipe[0]);
    }
    
    if (working_opts.capture_stderr && stderr_pipe[0] >= 0) {
        fd_set read_fds;
        FD_ZERO(&read_fds);
        FD_SET(stderr_pipe[0], &read_fds);
        
        struct timeval tv{};
        tv.tv_sec = working_opts.timeout.count() / 1000;
        tv.tv_usec = (working_opts.timeout.count() % 1000) * 1000;
        
        char buffer[256];
        ssize_t bytes_read;
        while ((bytes_read = select(stderr_pipe[0] + 1, &read_fds, nullptr, nullptr, &tv)) > 0) {
            if (FD_ISSET(stderr_pipe[0], &read_fds)) {
                ssize_t n = read(stderr_pipe[0], buffer, sizeof(buffer));
                if (n <= 0) break;
                
                // Bounded output
                size_t new_size = stderr_data.size() + static_cast<size_t>(n);
                if (new_size <= working_opts.max_output_bytes) {
                    stderr_data.append(buffer, n);
                }
            }
            
            FD_ZERO(&read_fds);
            FD_SET(stderr_pipe[0], &read_fds);
            tv.tv_sec = working_opts.timeout.count() / 1000;
            tv.tv_usec = (working_opts.timeout.count() % 1000) * 1000;
        }
        close(stderr_pipe[0]);
    }
    
    // Wait for process with timeout
    int status = 0;
    bool timed_out = false;
    pid_t waited_pid = 0;
    
    auto elapsed = std::chrono::steady_clock::now() - start_time;
    auto remaining_timeout = working_opts.timeout - elapsed;
    
    if (remaining_timeout <= std::chrono::milliseconds(0)) {
        // Timeout already exceeded, kill the process
        kill(pid, SIGTERM);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        kill(pid, SIGKILL);
        waitpid(pid, &status, WNOHANG);
        timed_out = true;
    } else {
        // Wait with timeout using sigaction or poll
        struct timespec ts{};
        ts.tv_sec = remaining_timeout.count() / 1000;
        ts.tv_nsec = (remaining_timeout.count() % 1000) * 1000000;
        
        waited_pid = waitpid(pid, &status, WNOHANG);
        if (waited_pid == 0) {
            // Process still running, use poll to wait with timeout
            auto poll_start = std::chrono::steady_clock::now();
            
            while (std::chrono::steady_clock::now() - poll_start < working_opts.timeout) {
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
                waited_pid = waitpid(pid, &status, WNOHANG);
                if (waited_pid != 0) break;
            }
            
            // Check if we timed out
            if (waited_pid == 0) {
                kill(pid, SIGTERM);
                std::this_thread::sleep_for(working_opts.grace_period);
                
                // Try to get status after SIGTERM
                waited_pid = waitpid(pid, &status, WNOHANG);
                
                if (waited_pid == 0) {
                    // Force kill
                    kill(pid, SIGKILL);
                    waitpid(pid, &status, 0);
                }
                timed_out = true;
            }
        }
    }
    
    int exit_code = 0;
    bool terminated_by_signal = false;
    
    if (WIFEXITED(status)) {
        exit_code = WEXITSTATUS(status);
    } else if (WIFSIGNALED(status)) {
        exit_code = -1;
        terminated_by_signal = true;
    }
    
    // Return result
    SubprocessResult result;
    result.exit_code = exit_code;
    result.timed_out = timed_out;
    result.terminated_by_signal = terminated_by_signal;
    result.stdout_data = std::move(stdout_data);
    result.stderr_data = std::move(stderr_data);
    
    return result;
}

}  // namespace rebuntu::semantic