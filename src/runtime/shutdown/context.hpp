// rebuntu::runtime::shutdown::Context — Shutdown Context (Phase 4.19)
//
// Runtime shutdown context provides state and configuration for graceful
// shutdown of Rebuntu's execution runtime.
//
// Key responsibilities:
//   - Track active executions during shutdown
//   - Coordinate timeout-based termination policies
//   - Manage shutdown phases (stop admission -> drain -> terminate -> cleanup)

#pragma once

#include <runtime/contracts.hpp>
#include <runtime/cancellation/token.hpp>
#include <runtime/work.hpp>
#include <system/core/results.hpp>
#include <string_view>
#include <chrono>
#include <optional>
#include <string>
#include <vector>

namespace rebuntu::runtime::shutdown {

// ShutdownPhase: The sequence of shutdown operations
enum class ShutdownPhase {
    kIdle,              // Not yet started
    kStoppingAdmission, // Stop accepting new work
    kCancelling,        // Signal cancellation to all work
    kDraining,          // Wait for bounded drain period
    kTerminating,       // Force-terminate remaining work
    kCleaningUp,        // Release resources and persist evidence
    kComplete,          // Shutdown finished
};

inline std::string to_string(ShutdownPhase p) {
    switch (p) {
        case ShutdownPhase::kIdle:           return "idle";
        case ShutdownPhase::kStoppingAdmission: return "stopping_admission";
        case ShutdownPhase::kCancelling:     return "cancelling";
        case ShutdownPhase::kDraining:       return "draining";
        case ShutdownPhase::kTerminating:    return "terminating";
        case ShutdownPhase::kCleaningUp:     return "cleaning_up";
        case ShutdownPhase::kComplete:       return "complete";
    }
    return "unknown";
}

// ShutdownPolicy: Configurable behavior for shutdown
struct ShutdownPolicy {
    // Maximum time to wait for graceful shutdown (including drain)
    std::chrono::milliseconds total_timeout = std::chrono::seconds(30);
    
    // Time allocated for draining existing work after cancellation
    std::chrono::milliseconds drain_timeout = std::chrono::seconds(10);
    
    // Whether to attempt graceful termination before forced
    bool try_graceful_first = true;
    
    // Maximum retries when terminating individual components
    int max_termination_retries = 2;
};

// ActiveExecution: Tracks an execution in progress during shutdown
struct ActiveExecution {
    runtime::work::JobId job_id;
    runtime::work::ExecutionId exec_id;
    std::chrono::system_clock::time_point started_at;
    runtime::work::ExecutionMode mode;
    std::optional<int32_t> pid;  // Native process ID if applicable
};

// ShutdownContext: State for a shutdown operation
struct ShutdownContext {
    ShutdownPhase phase = ShutdownPhase::kIdle;
    
    ShutdownPolicy policy;
    
    std::chrono::system_clock::time_point start_time{};
    std::chrono::system_clock::time_point deadline{};
    
    // Cancellation token used to signal all work
    std::shared_ptr<runtime::CancellationToken> cancellation_token;
    
    // Active executions at shutdown start (snapshot)
    std::vector<ActiveExecution> active_executions;
    
    // Executions that completed during shutdown
    std::vector<std::pair<runtime::work::JobId, core::Outcome>> completed_executions;
    
    // Executions that were force-terminated
    std::vector<std::pair<runtime::work::JobId, core::Outcome>> terminated_executions;
    
    // Any error encountered during shutdown
    std::optional<core::Error> error{};
    
    // Native signal that triggered shutdown (if applicable)
    std::optional<int> triggering_signal{};  // e.g., SIGTERM=15, SIGINT=2
    
    // Cleanup status for various subsystems
    bool resources_released = false;
    bool evidence_persisted = false;
    
    // Timing information (populated during shutdown)
    std::chrono::milliseconds stopping_admission_time_ms{0};
    std::chrono::milliseconds draining_time_ms{0};
    std::chrono::milliseconds termination_time_ms{0};
    
    // Counters for tracking execution states
    size_t force_terminated = 0;
    size_t graceful_completions = 0;
    size_t timeout_expired = 0;
};

// ShutdownResult: Result of a shutdown operation
struct ShutdownResult {
    core::SemanticStatus status = core::SemanticStatus::kUnknown;
    
    // How many executions completed gracefully vs were terminated
    size_t graceful_completions = 0;
    size_t force_terminated = 0;
    size_t timeout_expired = 0;
    
    // Time spent in each phase (in milliseconds)
    std::chrono::milliseconds stopping_admission_time_ms{0};
    std::chrono::milliseconds draining_time_ms{0};
    std::chrono::milliseconds termination_time_ms{0};
    std::chrono::milliseconds total_shutdown_time_ms{0};
    
    // Final state of active executions at shutdown end
    std::vector<std::pair<runtime::work::JobId, runtime::work::JobState>> final_states;
};

namespace context {

// Factory: Create a new shutdown context with default policy
inline ShutdownContext make_default_context() {
    ShutdownContext ctx;
    ctx.policy = ShutdownPolicy{};
    ctx.cancellation_token = std::make_shared<runtime::CancellationToken>();
    return ctx;
}

// Factory: Create a shutdown context with custom policy
inline ShutdownContext make_custom_context(ShutdownPolicy policy) {
    ShutdownContext ctx;
    ctx.policy = std::move(policy);
    ctx.cancellation_token = std::make_shared<runtime::CancellationToken>();
    return ctx;
}

}  // namespace context

}  // namespace rebuntu::runtime::shutdown