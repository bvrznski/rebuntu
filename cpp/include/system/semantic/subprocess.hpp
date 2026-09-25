// rebuntu::semantic::subprocess — Subprocess Execution for bitnet.cpp (Phase 3.2)
//
// Implements subprocess execution with:
//   - Native Linux fork/execve
//   - Bounded stdout/stderr capture
//   - Timeout enforcement via SIGTERM/SIGKILL
//   - CPU-only enforcement via CUDA_VISIBLE_DEVICES=""
//   - Proper process group handling

#pragma once

#include <string>
#include <vector>
#include <chrono>
#include <optional>
#include <map>

namespace rebuntu::semantic {

// ============================================================================
// SubprocessResult — Result of a subprocess execution
// ============================================================================

struct SubprocessResult {
    int exit_code = -1;
    bool timed_out = false;
    bool terminated_by_signal = false;
    std::string stdout_data;
    std::string stderr_data;
    
    // Static constructors
    static SubprocessResult success(std::string out, std::string err = {}) {
        SubprocessResult r;
        r.exit_code = 0;
        r.stdout_data = std::move(out);
        r.stderr_data = std::move(err);
        return r;
    }
    
    static SubprocessResult failure(int code, std::string err, std::string out = {}) {
        SubprocessResult r;
        r.exit_code = code;
        r.stderr_data = std::move(err);
        r.stdout_data = std::move(out);
        return r;
    }
    
    static SubprocessResult timeout() {
        SubprocessResult r;
        r.exit_code = -2;  // Convention: timeout
        r.timed_out = true;
        return r;
    }
};

// ============================================================================
// SubprocessOptions — Configuration for subprocess execution
// ============================================================================

struct SubprocessOptions {
    std::string executable;
    std::vector<std::string> argv;
    std::optional<std::string> cwd;
    std::map<std::string, std::string> env;  // Environment variables to add/override
    
    bool capture_stdout = true;
    bool capture_stderr = true;
    
    size_t max_output_bytes = 4096;  // Bounded output to prevent OOM
    std::chrono::milliseconds timeout = std::chrono::seconds(30);
    std::chrono::milliseconds grace_period = std::chrono::milliseconds(100);  // SIGTERM -> SIGKILL wait
    
    bool cpu_only = true;  // If true, sets CUDA_VISIBLE_DEVICES=""
    
    static SubprocessOptions make_default(const std::string& exe) {
        SubprocessOptions opts;
        opts.executable = exe;
        opts.argv.push_back(exe);
        return opts;
    }
};

// ============================================================================
// SubprocessExecutor — Execute subprocess with full control
// ============================================================================

class SubprocessExecutor {
public:
    SubprocessExecutor();
    ~SubprocessExecutor() = default;
    
    // Delete copy operations
    SubprocessExecutor(const SubprocessExecutor&) = delete;
    SubprocessExecutor& operator=(const SubprocessExecutor&) = delete;
    
    // Execute subprocess with all options
    SubprocessResult execute(const SubprocessOptions& opts);

private:
    bool setup_child_environment(SubprocessOptions& opts) const;
    void apply_cpu_only_env(std::map<std::string, std::string>& env) const;
};

}  // namespace rebuntu::semantic