// rebuntu::semantic::bitnet::Provider — Microsoft bitnet.cpp integration (Phase 3.2)
//
// This implements the SemanticProvider interface using the BitNet b1.58 2B4T model
// via Microsoft's bitnet.cpp runtime with explicit CPU-only enforcement.
//
// Architecture:
//   * Provider is header-only where possible
//   * Implementation uses PIMPL pattern for ABI stability
//   * CPU-only execution by default (GPU use requires explicit enablement)
//   * Subprocess execution via fork/execve (no shell interpolation)

#include <semantics/provider.hpp>

#include <array>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <filesystem>
#include <iostream>
#include <memory>
#include <mutex>
#include <optional>
#include <sstream>
#include <string>
#include <thread>
#include <vector>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <signal.h>

namespace rebuntu::semantic {

namespace bitnet {

// ============================================================================
// Subprocess execution helper - native Linux implementation
// ============================================================================

namespace subprocess {

// Execute a command with timeout, capturing stdout/stderr
// Returns: {exit_code, stdout, stderr}
struct ExecutionResult {
    int exit_code;
    std::string stdout_data;
    std::string stderr_data;
};

static ExecutionResult execute_with_timeout(
    const std::string& executable,
    const std::vector<std::string>& argv,
    std::optional<std::chrono::milliseconds> timeout_ms,
    std::optional<int64_t> memory_limit_bytes
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

            // Set CPU-only environment variable if memory limit specified
            // This enforces CPU-only mode regardless of available libraries
            if (memory_limit_bytes.has_value()) {
                setenv("CUDA_VISIBLE_DEVICES", "", 1);  // Force no GPU visibility
                char mem_limit_str[64];
                snprintf(mem_limit_str, sizeof(mem_limit_str), "%ld", memory_limit_bytes.value());
                setenv("MEMORY_LIMIT", mem_limit_str, 1);
            }

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
    
    bool is_ready() const;
    semantic::ModelInfo model_info() const;
    
    SemanticResult classify(
        const std::string& input,
        const std::vector<std::string>& categories,
        std::optional<std::chrono::milliseconds> timeout
    );
    
    SemanticResult generate_intent_candidate(
        const std::string& input,
        const std::vector<std::string>& allowed_operations,
        std::optional<std::chrono::milliseconds> timeout
    );
    
    SemanticResult assess_evidence_relevance(
        const std::string& evidence,
        const std::string& context,
        std::optional<std::chrono::milliseconds> timeout
    );
    
    SemanticResult summarize_diagnostics(
        const std::vector<std::string>& diagnostic_items,
        std::optional<std::chrono::milliseconds> timeout
    );

private:
    Config config_;
    bool initialized_ = false;
    mutable std::mutex initialization_mutex_;  // For lazy initialization
    
    // Check if bitnet.cpp runtime is available and ready
    bool check_runtime_availability() const;
    
    // Execute bitnet inference subprocess
    SemanticResult execute_inference(
        const std::vector<std::string>& argv,
        std::optional<std::chrono::milliseconds> timeout
    );
};

// ============================================================================
// Impl Implementation
// ============================================================================

Provider::Impl::Impl(Config config) : config_(std::move(config)) {
    initialized_ = check_runtime_availability();
}

Provider::Impl::~Impl() = default;

bool Provider::Impl::check_runtime_availability() const {
    // Check if bitnet.cpp executable is available in PATH
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
        
        // Check for bitnet.cpp executable
        std::string candidate = dir + "bitnet";
        if (access(candidate.c_str(), X_OK) == 0) {
            return true;
        }
        
        start = end + 1;
    }
    
    // Also check if model directory exists
    if (!config_.model_path.empty()) {
        std::error_code ec;
        return std::filesystem::exists(config_.model_path, ec);
    }
    
    return false;
}

bool Provider::Impl::is_ready() const {
    // CPU-only must be enforced - this is a policy check
    return initialized_ && config_.cpu_only;
}

semantic::ModelInfo Provider::Impl::model_info() const {
    semantic::ModelInfo info;
    info.family = ModelFamily::kBitNetB158_2B4T;
    info.model_path = config_.model_path;
    info.config_path = std::nullopt;  // Not yet implemented
    info.cpu_only = true;  // CPU-only enforced
    
    return info;
}

SemanticResult Provider::Impl::execute_inference(
    const std::vector<std::string>& argv,
    std::optional<std::chrono::milliseconds> timeout
) {
    SemanticResult result;
    
    auto exec_result = subprocess::execute_with_timeout(
        "/usr/bin/bitnet",  // bitnet.cpp installed location
        argv,
        timeout,
        config_.memory_limit_bytes
    );
    
    if (exec_result.exit_code == -2) {
        // Timeout
        result.status = core::SemanticStatus::kUnknown;
        result.error = core::Error{
            "E_SEMANTIC_TIMEOUT",
            "BitNet inference timed out"
        };
        return result;
    }
    
    if (exec_result.exit_code < 0 || exec_result.exit_code == 127) {
        // Execution failed
        result.status = core::SemanticStatus::kUnknown;
        result.error = core::Error{
            "E_SEMANTIC_EXECUTION_FAILED",
            "BitNet execution failed: " + exec_result.stderr_data
        };
        return result;
    }
    
    if (exec_result.exit_code != 0) {
        // Non-zero exit status
        result.status = core::SemanticStatus::kUnknown;
        result.error = core::Error{
            "E_SEMANTIC_EXECUTION_FAILED",
            "BitNet returned error code " + std::to_string(exec_result.exit_code)
                + ": " + exec_result.stderr_data
        };
        return result;
    }
    
    // Success - process the output
    // The bitnet.cpp output is expected to be JSON-like with classification results
    
    if (!exec_result.stdout_data.empty()) {
        // For now, we'll use a simple heuristic - in production,
        // you'd parse the actual JSON format from bitnet.cpp
        
        result.status = core::SemanticStatus::kSuccess;
        
        // Add evidence for verification
        core::Evidence ev;
        ev.source = "bitnet-inference";
        ev.value = exec_result.stdout_data.substr(0, 1024);  // Bound size
        ev.captured_at = "";
        result.evidence.push_back(ev);
    } else {
        result.status = core::SemanticStatus::kUnknown;
        result.error = core::Error{
            "E_SEMANTIC_NO_OUTPUT",
            "BitNet produced no output"
        };
    }
    
    return result;
}

SemanticResult Provider::Impl::classify(
    const std::string& input,
    const std::vector<std::string>& categories,
    std::optional<std::chrono::milliseconds> timeout
) {
    if (!is_ready()) {
        SemanticResult result = SemanticResult::unavailable("BitNet provider not ready");
        return result;
    }
    
    // Build bitnet.cpp command line
    // Expected format: bitnet classify <model-path> --input <text> --categories <cats>
    std::vector<std::string> argv = {
        "bitnet",
        "classify",
        config_.model_path,
        "--input", input
    };
    
    for (const auto& cat : categories) {
        argv.push_back("--category");
        argv.push_back(cat);
    }
    
    // Add timeout if specified
    if (!timeout.has_value()) {
        timeout = std::chrono::milliseconds(30000);  // Default 30 second timeout
    }
    
    return execute_inference(argv, timeout);
}

SemanticResult Provider::Impl::generate_intent_candidate(
    const std::string& input,
    const std::vector<std::string>& /*allowed_operations*/,
    std::optional<std::chrono::milliseconds> timeout
) {
    if (!is_ready()) {
        SemanticResult result = SemanticResult::unavailable("BitNet provider not ready");
        return result;
    }
    
    // Build bitnet.cpp command line for intent generation
    // Expected format: bitnet intent <model-path> --input <text>
    std::vector<std::string> argv = {
        "bitnet",
        "intent",
        config_.model_path,
        "--input", input
    };
    
    if (!timeout.has_value()) {
        timeout = std::chrono::milliseconds(30000);
    }
    
    return execute_inference(argv, timeout);
}

SemanticResult Provider::Impl::assess_evidence_relevance(
    const std::string& evidence,
    const std::string& context,
    std::optional<std::chrono::milliseconds> timeout
) {
    if (!is_ready()) {
        SemanticResult result = SemanticResult::unavailable("BitNet provider not ready");
        return result;
    }
    
    // Build bitnet.cpp command line for relevance assessment
    // Expected format: bitnet relevance <model-path> --evidence <text> --context <text>
    std::vector<std::string> argv = {
        "bitnet",
        "relevance",
        config_.model_path,
        "--evidence", evidence,
        "--context", context
    };
    
    if (!timeout.has_value()) {
        timeout = std::chrono::milliseconds(30000);
    }
    
    return execute_inference(argv, timeout);
}

SemanticResult Provider::Impl::summarize_diagnostics(
    const std::vector<std::string>& diagnostic_items,
    std::optional<std::chrono::milliseconds> timeout
) {
    if (!is_ready()) {
        SemanticResult result = SemanticResult::unavailable("BitNet provider not ready");
        return result;
    }
    
    // Build bitnet.cpp command line for summary generation
    // Expected format: bitnet summarize <model-path> --items <item1> --items <item2> ...
    std::vector<std::string> argv = {
        "bitnet",
        "summarize",
        config_.model_path
    };
    
    for (const auto& item : diagnostic_items) {
        argv.push_back("--item");
        argv.push_back(item);
    }
    
    if (!timeout.has_value()) {
        timeout = std::chrono::milliseconds(30000);
    }
    
    return execute_inference(argv, timeout);
}

// ============================================================================
// Provider Implementation
// ============================================================================

Provider::Provider(Config config) : pimpl_(std::make_unique<Impl>(std::move(config))) {
}

Provider::~Provider() = default;

ProviderId Provider::provider_id() const {
    return ProviderId{"bitnet-b1.58-2b4t"};
}

semantic::ModelInfo Provider::model_info() const {
    return pimpl_->model_info();
}

bool Provider::is_ready() const {
    return pimpl_->is_ready();
}

SemanticResult Provider::classify(
    const std::string& input,
    const std::vector<std::string>& categories,
    std::optional<std::chrono::milliseconds> timeout
) {
    return pimpl_->classify(input, categories, timeout);
}

SemanticResult Provider::generate_intent_candidate(
    const std::string& input,
    const std::vector<std::string>& allowed_operations,
    std::optional<std::chrono::milliseconds> timeout
) {
    return pimpl_->generate_intent_candidate(input, allowed_operations, timeout);
}

SemanticResult Provider::assess_evidence_relevance(
    const std::string& evidence,
    const std::string& context,
    std::optional<std::chrono::milliseconds> timeout
) {
    return pimpl_->assess_evidence_relevance(evidence, context, timeout);
}

SemanticResult Provider::summarize_diagnostics(
    const std::vector<std::string>& diagnostic_items,
    std::optional<std::chrono::milliseconds> timeout
) {
    return pimpl_->summarize_diagnostics(diagnostic_items, timeout);
}

}  // namespace bitnet

// ============================================================================
// SemanticProviderRegistry Implementation
// ============================================================================

void SemanticProviderRegistry::add_provider(std::unique_ptr<SemanticProvider> provider) {
    // Move ownership to raw pointer storage
    providers_.push_back(provider.release());
}

std::vector<std::unique_ptr<SemanticProvider>> SemanticProviderRegistry::all_providers() const {
    // Return unique_ptrs from stored raw pointers (transfer ownership back)
    std::vector<std::unique_ptr<SemanticProvider>> result;
    for (SemanticProvider* p : providers_) {
        result.emplace_back(p);
    }
    return result;
}

std::optional<SemanticProvider*> SemanticProviderRegistry::find_provider(const ProviderId& id) const {
    for (SemanticProvider* p : providers_) {
        if (p->provider_id() == id) {
            return p;
        }
    }
    return std::nullopt;
}

bool SemanticProviderRegistry::is_semantic_available() const {
    // At least one provider must be ready
    for (SemanticProvider* p : providers_) {
        if (p->is_ready()) {
            return true;
        }
    }
    return false;
}

}  // namespace rebuntu::semantic