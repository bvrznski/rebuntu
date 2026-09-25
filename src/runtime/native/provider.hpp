// rebuntu::runtime::native::Provider — Native Provider Interface (Phase 4.0)
//
// NativeProvider defines the interface between Rebuntu runtime and Linux.
// This is where typed Rebuntu abstractions meet native system mechanisms.
//
// Implementation responsibility:
// - Rebuntu provides: Typed requests, timeout enforcement, cancellation propagation
// - Native provider provides: Actual process execution, kernel interfaces

#pragma once

#include <system/core/contracts.hpp>
#include <runtime/native/error.hpp>
#include <chrono>
#include <functional>
#include <optional>
#include <string>
#include <vector>

namespace rebuntu::runtime {

struct NativeExecutionParameters {
    std::optional<std::string> executable;
    std::vector<std::string> argv;
    std::optional<std::string> working_directory;
    std::map<std::string, std::string> environment;
    std::chrono::milliseconds timeout;
};

struct NativeExecutionResult {
    int exit_code;
    bool terminated_by_signal;
    int signal_number;
    std::string stdout_data;
    std::string stderr_data;
    std::chrono::milliseconds execution_duration;
};

class NativeProvider {
public:
    virtual ~NativeProvider() = default;
    
    // Execute a native command
    virtual NativeExecutionResult execute(
        const NativeExecutionParameters& params) = 0;
    
    // Get process state (pid must be valid)
    virtual std::optional<int> get_exit_code(int pid) = 0;
    
    // Check if process is still running
    virtual bool is_process_alive(int pid) = 0;
    
    // Terminate a process gracefully (SIGTERM)
    virtual void terminate(int pid) = 0;
    
    // Force kill a process (SIGKILL)
    virtual void kill(int pid) = 0;
};

namespace native {

// Inline provider for testing - executes immediately in-process
class InlineNativeProvider : public NativeProvider {
public:
    NativeExecutionResult execute(
        const NativeExecutionParameters& params) override {
        
        // For inline execution, we simulate the result
        // In real implementation, this would call actual system() or subprocess
        NativeExecutionResult result;
        result.exit_code = 0;  // Success (simulated)
        result.terminated_by_signal = false;
        result.signal_number = 0;
        result.stdout_data = "";
        result.stderr_data = "";
        result.execution_duration = std::chrono::milliseconds(1);
        
        return result;
    }
    
    std::optional<int> get_exit_code(int pid) override {
        // Inline provider doesn't track real PIDs
        (void)pid;
        return std::nullopt;
    }
    
    bool is_process_alive(int pid) override {
        (void)pid;
        return false;  // No real processes in inline mode
    }
    
    void terminate(int pid) override { (void)pid; }
    void kill(int pid) override { (void)pid; }
};

// Factory function for inline provider (testing)
inline std::unique_ptr<NativeProvider> make_inline_provider() {
    return std::make_unique<InlineNativeProvider>();
}

}  // namespace native
}  // namespace rebuntu::runtime

namespace rebuntu { namespace runtime { namespace native {
struct Error {};
}}}