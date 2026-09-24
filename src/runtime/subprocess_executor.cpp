// rebuntu::runtime::SubprocessExecutor — Subprocess Execution (Phase 0.13)
//
// Implements subprocess execution using fork/execve with native Linux primitives.
// This is the canonical subprocess executor for Rebuntu.

#include <runtime/subprocess_executor.hpp>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

namespace rebuntu::runtime {

SubprocessExecutor::SubprocessExecutor() = default;

core::Outcome SubprocessExecutor::execute_subprocess(
    const std::string& executable,
    const std::vector<std::string>& argv,
    std::optional<std::string> cwd,
    std::map<std::string, std::string> env,
    std::chrono::milliseconds timeout) {
    
    (void)env;  // Environment not yet implemented in minimal proof
    (void)timeout;  // Timeout not yet implemented in minimal proof
    
    // Fork a child process
    pid_t pid = fork();
    
    if (pid == -1) {
        return core::Outcome::failure("E_FORK_FAILED", "fork() failed");
    }
    
    if (pid == 0) {
        // Child process - execute the command
        
        // Change to working directory if provided
        if (cwd.has_value()) {
            chdir(cwd->c_str());
        }
        
        // Build argv array
        std::vector<char*> c_argv;
        c_argv.push_back(const_cast<char*>(executable.c_str()));
        for (const auto& arg : argv) {
            c_argv.push_back(const_cast<char*>(arg.c_str()));
        }
        c_argv.push_back(nullptr);
        
        // Execute the program
        execve(executable.c_str(), c_argv.data(), nullptr);
        
        // If we get here, execve failed
        _exit(127);
    }
    
    // Parent process - wait for child
    int status = 0;
    pid_t waited_pid = waitpid(pid, &status, 0);
    
    if (waited_pid == -1) {
        return core::Outcome::failure("E_WAIT_FAILED", "waitpid() failed");
    }
    
    int exit_code = 0;
    bool terminated_by_signal = false;
    
    if (WIFEXITED(status)) {
        exit_code = WEXITSTATUS(status);
    } else if (WIFSIGNALED(status)) {
        exit_code = -1;
        terminated_by_signal = true;
    }
    
    // Return appropriate outcome based on exit code
    if (exit_code == 0) {
        return core::Outcome::success();
    }
    
    return core::Outcome::failure(
        "E_SUBPROCESS_FAILED",
        "subprocess exited with code " + std::to_string(exit_code));
}

}  // namespace rebuntu::runtime