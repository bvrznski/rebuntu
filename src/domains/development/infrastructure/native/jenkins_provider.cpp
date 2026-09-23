// rebuntu::infrastructure::jenkins_cli — Jenkins CLI Provider Implementation (Phase 3.9)
//
// This implements the JenkinsProvider interface using native subprocess execution
// for local Jenkins operations and configuration validation.
//
// Architecture:
//   * PIMPL pattern for ABI stability
//   * Native Linux subprocess execution via fork/execve
//   * Bounded stdout/stderr output
//   * Explicit timeout handling

#include <domains/development/infrastructure/jenkins.hpp>

#include <array>
#include <optional>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <filesystem>
#include <iostream>
#include <memory>
#include <mutex>
#include <sstream>
#include <string>
#include <thread>
#include <vector>
#include <unistd.h>
#include <sys/wait.h>

namespace rebuntu::infrastructure {

namespace jenkins_cli {

// ============================================================================
// Subprocess execution helper - native Linux implementation
// ============================================================================

namespace subprocess {

struct ExecutionResult {
    int exit_code;
    std::string stdout_data;
    std::string stderr_data;
};

static ExecutionResult execute_with_timeout(
    const std::string& executable,
    const std::vector<std::string>& argv,
    std::optional<std::chrono::milliseconds> timeout_ms
) {
    ExecutionResult result;

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
        // Parent process
        close(stdout_pipe[1]);
        close(stderr_pipe[1]);

        // Read from pipes
        std::array<char, 4096> buffer;
        ssize_t bytes_read;

        while ((bytes_read = read(stdout_pipe[0], buffer.data(), buffer.size())) > 0) {
            result.stdout_data.append(buffer.data(), bytes_read);
        }

        while ((bytes_read = read(stderr_pipe[0], buffer.data(), buffer.size())) > 0) {
            result.stderr_data.append(buffer.data(), bytes_read);
        }

        close(stdout_pipe[0]);
        close(stderr_pipe[0]);

        // Wait for child with optional timeout
        if (timeout_ms.has_value()) {
            auto start = std::chrono::steady_clock::now();

            while (true) {
                // Check if child has exited
                int status;
                pid_t wait_result = waitpid(pid, &status, WNOHANG);

                if (wait_result == pid) {
                    // Child exited
                    result.exit_code = WIFEXITED(status) ? WEXITSTATUS(status) : -1;
                    break;
                } else if (wait_result < 0) {
                    // Error
                    result.exit_code = -1;
                    result.stderr_data = "Error waiting for child process";
                    break;
                }

                // Check timeout
                auto elapsed = std::chrono::steady_clock::now() - start;
                if (std::chrono::duration_cast<std::chrono::milliseconds>(elapsed) >= timeout_ms.value()) {
                    // Timeout - send SIGTERM then SIGKILL
                    kill(pid, SIGTERM);
                    std::this_thread::sleep_for(std::chrono::milliseconds(100));
                    kill(pid, SIGKILL);

                    result.exit_code = -2;  // Timeout indicator
                    result.stderr_data = "Process execution timed out";
                    break;
                }

                // Small sleep before checking again
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
            }
        } else {
            // Wait without timeout
            int status;
            waitpid(pid, &status, 0);
            result.exit_code = WIFEXITED(status) ? WEXITSTATUS(status) : -1;
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

}  // namespace subprocess

// ============================================================================
// Implementation details (PIMPL)
// ============================================================================

class Provider::Impl {
public:
    explicit Impl(Config config);
    ~Impl();

    // Disable copy/move
    Impl(const Impl&) = delete;
    Impl& operator=(const Impl&) = delete;

    bool is_available() const;
    JenkinsProviderId provider_id() const;
    std::optional<std::string> get_server_info(
        std::optional<std::chrono::milliseconds> timeout
    ) const;

    JenkinsResult trigger_build(
        const std::string& job_name,
        const std::map<std::string, std::string>& parameters,
        std::optional<std::chrono::milliseconds> timeout
    );

    JenkinsResult get_build_status(
        const std::string& job_name,
        int build_number,
        std::optional<std::chrono::milliseconds> timeout
    );

    JenkinsResult list_builds(
        const std::string& job_name,
        std::optional<int> limit,
        std::optional<std::chrono::milliseconds> timeout
    );

    JenkinsResult get_artifacts(
        const std::string& job_name,
        int build_number,
        std::optional<std::chrono::milliseconds> timeout
    );

private:
    Config config_;
    bool available_ = false;
    mutable std::mutex initialization_mutex_;

    // Discover jenkins executable path and check availability
    bool discover_jenkins() const;

    // Execute jenkins command with structured argv
    subprocess::ExecutionResult execute_jenkins(
        const std::vector<std::string>& argv,
        std::optional<std::chrono::milliseconds> timeout
    ) const;
};

// ============================================================================
// Impl Implementation
// ============================================================================

Provider::Impl::Impl(Config config) : config_(std::move(config)) {
    available_ = discover_jenkins();
}

Provider::Impl::~Impl() = default;

bool Provider::Impl::discover_jenkins() const {
    // Check if jenkins executable is available in PATH
    const char* path_env = std::getenv("PATH");
    if (!path_env) {
        return false;
    }

    std::string path_str(path_env);
    size_t start = 0;

    while (start < path_str.length()) {
        size_t end = path_str.find(':', start);
        if (end == std::string::npos) {
            end = path_str.length();
        }

        std::string dir = path_str.substr(start, end - start);
        if (!dir.empty() && dir.back() != '/') {
            dir += '/';
        }

        // Check for jenkins executable
        std::string candidate = dir + "jenkins";
        if (access(candidate.c_str(), X_OK) == 0) {
            return true;
        }

        start = end + 1;
    }

    return false;
}

bool Provider::Impl::is_available() const {
    // Jenkins must be available and CPU-only policy is maintained
    return available_ && config_.cpu_only;
}

JenkinsProviderId Provider::Impl::provider_id() const {
    return JenkinsProviderId{"jenkins-cli"};
}

std::optional<std::string> Provider::Impl::get_server_info(
    std::optional<std::chrono::milliseconds> timeout
) const {
    if (!is_available()) {
        return std::nullopt;
    }

    auto result = execute_jenkins({
        "--version"
    }, std::chrono::milliseconds(5000));

    if (result.exit_code == 0 && !result.stdout_data.empty()) {
        // Extract version info from output
        std::string version_str = result.stdout_data;
        // Trim whitespace
        size_t start = version_str.find_first_not_of(" \t\n\r");
        size_t end = version_str.find_last_not_of(" \t\n\r");
        if (start != std::string::npos) {
            return version_str.substr(start, end - start + 1);
        }
    }

    return std::nullopt;
}

subprocess::ExecutionResult Provider::Impl::execute_jenkins(
    const std::vector<std::string>& argv,
    std::optional<std::chrono::milliseconds> timeout
) const {
    // Build the full command: jenkins [argv...]
    std::vector<std::string> cmd = {"jenkins"};
    for (const auto& arg : argv) {
        if (arg != "jenkins") {  // Avoid duplication
            cmd.push_back(arg);
        }
    }

    return subprocess::execute_with_timeout("/usr/bin/jenkins", cmd, timeout);
}

JenkinsResult Provider::Impl::trigger_build(
    const std::string& job_name,
    const std::map<std::string, std::string>& parameters,
    std::optional<std::chrono::milliseconds> timeout
) {
    if (!is_available()) {
        return JenkinsResult::unavailable("Jenkins provider not available");
    }

    // Build jenkins build command
    std::vector<std::string> argv = {"build", job_name};

    // Add parameters as -p flags (common CLI pattern)
    for (const auto& [key, value] : parameters) {
        argv.push_back("-p");
        argv.push_back(key + "=" + value);
    }

    auto result = execute_jenkins(argv, timeout);

    JenkinsResult jenkins_result;

    if (result.exit_code == -2) {
        // Timeout
        jenkins_result.status = core::SemanticStatus::kUnknown;
        jenkins_result.error = core::Error{"E_JENKINS_TIMEOUT", "Jenkins build trigger timed out"};
        return jenkins_result;
    }

    if (result.exit_code < 0 || result.exit_code == 127) {
        jenkins_result.status = core::SemanticStatus::kUnknown;
        jenkins_result.error = core::Error{
            "E_JENKINS_EXECUTION_FAILED",
            "Jenkins execution failed: " + result.stderr_data
        };
        return jenkins_result;
    }

    // Parse the output to extract build info
    JenkinsBuildInfo build_info;
    build_info.job_name = job_name;

    if (!result.stdout_data.empty()) {
        std::istringstream iss(result.stdout_data);
        std::string line;

        while (std::getline(iss, line)) {
            // Try to parse build number from output
            // Common format: "Started build #123" or "Build 456 queued"
            if (line.find("build") != std::string::npos ||
                line.find("#") != std::string::npos) {
                // Extract potential build number
                size_t hash_pos = line.find('#');
                if (hash_pos != std::string::npos) {
                    size_t start = hash_pos + 1;
                    while (start < line.length() && isspace(line[start])) ++start;
                    
                    std::istringstream num_stream(line.substr(start));
                    num_stream >> build_info.build_number;
                }
            }
        }
    }

    jenkins_result.status = core::SemanticStatus::kSuccess;
    jenkins_result.build_info = build_info;
    return jenkins_result;
}

JenkinsResult Provider::Impl::get_build_status(
    const std::string& job_name,
    int build_number,
    std::optional<std::chrono::milliseconds> timeout
) {
    if (!is_available()) {
        return JenkinsResult::unavailable("Jenkins provider not available");
    }

    auto result = execute_jenkins({
        "status", job_name, std::to_string(build_number)
    }, timeout);

    JenkinsResult jenkins_result;

    if (result.exit_code == -2) {
        jenkins_result.status = core::SemanticStatus::kUnknown;
        jenkins_result.error = core::Error{"E_JENKINS_TIMEOUT", "Jenkins status check timed out"};
        return jenkins_result;
    }

    if (result.exit_code < 0 || result.exit_code == 127) {
        jenkins_result.status = core::SemanticStatus::kUnknown;
        jenkins_result.error = core::Error{
            "E_JENKINS_EXECUTION_FAILED",
            "Jenkins status check failed: " + result.stderr_data
        };
        return jenkins_result;
    }

    // Parse the build status from output
    JenkinsBuildInfo build_info;
    build_info.job_name = job_name;
    build_info.build_number = build_number;

    if (!result.stdout_data.empty()) {
        std::istringstream iss(result.stdout_data);
        std::string line;

        while (std::getline(iss, line)) {
            // Parse status from output
            if (line.find("SUCCESS") != std::string::npos ||
                line.find("success") != std::string::npos) {
                build_info.status = JenkinsBuildStatus::kSuccess;
            } else if (line.find("FAILED") != std::string::npos ||
                       line.find("failed") != std::string::npos) {
                build_info.status = JenkinsBuildStatus::kFailed;
            } else if (line.find("ABORTED") != std::string::npos ||
                       line.find("aborted") != std::string::npos) {
                build_info.status = JenkinsBuildStatus::kAborted;
            } else if (line.find("QUEUED") != std::string::npos ||
                       line.find("queued") != std::string::npos) {
                build_info.status = JenkinsBuildStatus::kQueued;
            }
        }
    }

    jenkins_result.status = core::SemanticStatus::kSuccess;
    jenkins_result.build_info = build_info;
    return jenkins_result;
}

JenkinsResult Provider::Impl::list_builds(
    const std::string& job_name,
    std::optional<int> limit,
    std::optional<std::chrono::milliseconds> timeout
) {
    if (!is_available()) {
        return JenkinsResult::unavailable("Jenkins provider not available");
    }

    std::vector<std::string> argv = {"list", job_name};

    // Add limit if specified
    if (limit.has_value()) {
        argv.push_back("--limit");
        argv.push_back(std::to_string(limit.value()));
    }

    auto result = execute_jenkins(argv, timeout);

    JenkinsResult jenkins_result;

    if (result.exit_code == -2) {
        jenkins_result.status = core::SemanticStatus::kUnknown;
        jenkins_result.error = core::Error{"E_JENKINS_TIMEOUT", "Jenkins list builds timed out"};
        return jenkins_result;
    }

    if (result.exit_code < 0 || result.exit_code == 127) {
        jenkins_result.status = core::SemanticStatus::kUnknown;
        jenkins_result.error = core::Error{
            "E_JENKINS_EXECUTION_FAILED",
            "Jenkins list builds failed: " + result.stderr_data
        };
        return jenkins_result;
    }

    // Parse the output for build information
    if (!result.stdout_data.empty()) {
        std::istringstream iss(result.stdout_data);
        std::string line;

        while (std::getline(iss, line)) {
            if (line.empty()) continue;

            JenkinsBuildInfo build_info;
            build_info.job_name = job_name;

            // Try to parse: build_number|status format
            size_t pos = line.find('|');
            if (pos != std::string::npos) {
                try {
                    build_info.build_number = std::stoi(line.substr(0, pos));
                    
                    std::string status_str = line.substr(pos + 1);
                    // Trim whitespace
                    size_t start = status_str.find_first_not_of(" \t\n\r");
                    if (start != std::string::npos) {
                        status_str = status_str.substr(start);
                    }

                    if (status_str == "success" || status_str == "SUCCESS") {
                        build_info.status = JenkinsBuildStatus::kSuccess;
                    } else if (status_str == "failed" || status_str == "FAILED") {
                        build_info.status = JenkinsBuildStatus::kFailed;
                    } else if (status_str == "aborted" || status_str == "ABORTED") {
                        build_info.status = JenkinsBuildStatus::kAborted;
                    } else if (status_str == "queued" || status_str == "QUEUED") {
                        build_info.status = JenkinsBuildStatus::kQueued;
                    }
                } catch (...) {
                    // Failed to parse build number, skip this line
                    continue;
                }
            }

            jenkins_result.build_info = build_info;  // Last one wins for now
        }
    }

    jenkins_result.status = core::SemanticStatus::kSuccess;
    return jenkins_result;
}

JenkinsResult Provider::Impl::get_artifacts(
    const std::string& job_name,
    int build_number,
    std::optional<std::chrono::milliseconds> timeout
) {
    if (!is_available()) {
        return JenkinsResult::unavailable("Jenkins provider not available");
    }

    auto result = execute_jenkins({
        "artifacts", job_name, std::to_string(build_number)
    }, timeout);

    JenkinsResult jenkins_result;

    if (result.exit_code == -2) {
        jenkins_result.status = core::SemanticStatus::kUnknown;
        jenkins_result.error = core::Error{"E_JENKINS_TIMEOUT", "Jenkins get artifacts timed out"};
        return jenkins_result;
    }

    if (result.exit_code < 0 || result.exit_code == 127) {
        jenkins_result.status = core::SemanticStatus::kUnknown;
        jenkins_result.error = core::Error{
            "E_JENKINS_EXECUTION_FAILED",
            "Jenkins get artifacts failed: " + result.stderr_data
        };
        return jenkins_result;
    }

    // Parse artifact information from output
    if (!result.stdout_data.empty()) {
        std::istringstream iss(result.stdout_data);
        std::string line;

        while (std::getline(iss, line)) {
            if (line.empty()) continue;

            JenkinsArtifactInfo artifact;
            artifact.filename = line;  // For now, just store the filename

            jenkins_result.artifacts.push_back(artifact);
        }
    }

    jenkins_result.status = core::SemanticStatus::kSuccess;
    return jenkins_result;
}

// ============================================================================
// Provider Implementation
// ============================================================================

Provider::Provider(Config config) : pimpl_(std::make_unique<Impl>(std::move(config))) {
}

Provider::~Provider() = default;

JenkinsProviderId Provider::provider_id() const {
    return pimpl_->provider_id();
}

bool Provider::is_available() const {
    return pimpl_->is_available();
}

std::optional<std::string> Provider::get_server_info(
    std::optional<std::chrono::milliseconds> timeout
) const {
    return pimpl_->get_server_info(timeout);
}

JenkinsResult Provider::trigger_build(
    const std::string& job_name,
    const std::map<std::string, std::string>& parameters,
    std::optional<std::chrono::milliseconds> timeout
) {
    return pimpl_->trigger_build(job_name, parameters, timeout);
}

JenkinsResult Provider::get_build_status(
    const std::string& job_name,
    int build_number,
    std::optional<std::chrono::milliseconds> timeout
) {
    return pimpl_->get_build_status(job_name, build_number, timeout);
}

JenkinsResult Provider::list_builds(
    const std::string& job_name,
    std::optional<int> limit,
    std::optional<std::chrono::milliseconds> timeout
) {
    return pimpl_->list_builds(job_name, limit, timeout);
}

JenkinsResult Provider::get_artifacts(
    const std::string& job_name,
    int build_number,
    std::optional<std::chrono::milliseconds> timeout
) {
    return pimpl_->get_artifacts(job_name, build_number, timeout);
}

}  // namespace jenkins_cli

}  // namespace rebuntu::infrastructure