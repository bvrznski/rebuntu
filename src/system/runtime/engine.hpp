// rebuntu::runtime::engine — Runtime Engine (Phase 4.2)
//
// The Engine is a stable runtime facade/coordinator, NOT a God object.
// It owns:
//   - Accepting typed runtime requests
//   - Binding initialized runtime context
//   - Invoking canonical resolution/dispatch path
//   - Exposing controlled lifecycle entry/exit
//
// The Engine does NOT own:
//   - Filesystem domain logic
//   - Package management
//   - Direct subprocess construction
//   - Provider-specific code
//   - Policy implementation
//   - Workflow internals
//   - Global mutable registry ownership (unless explicitly assigned)

#pragma once

#include <system/runtime/contracts.hpp>
#include <system/runtime/work.hpp>
#include <system/runtime/initialization.hpp>
#include <system/runtime/workflow.hpp>
#include <system/core/contracts.hpp>
#include <system/lifecycle/contracts.hpp>

#include <string>
#include <memory>
#include <optional>
#include <string_view>
#include <mutex>
#include <filesystem>
#include <atomic>
#include <chrono>
#include <map>

namespace rebuntu::runtime::engine {

// ---------------------------------------------------------------------------
// EngineState
// The runtime state of the Engine itself (orthogonal to work item states).
// ---------------------------------------------------------------------------
enum class EngineState {
    kCreated,        // engine instance created but not initialized
    kInitializing,   // initialization in progress
    kReady,          // fully initialized and accepting requests
    kStopping,       // graceful shutdown initiated
    kStopped,        // fully stopped
    kFailed,         // terminated due to error/failure
};

inline std::string_view to_string(EngineState s) {
    switch (s) {
        case EngineState::kCreated:     return "created";
        case EngineState::kInitializing: return "initializing";
        case EngineState::kReady:       return "ready";
        case EngineState::kStopping:    return "stopping";
        case EngineState::kStopped:     return "stopped";
        case EngineState::kFailed:      return "failed";
    }
    return "unknown";
}

// ---------------------------------------------------------------------------
// Request
// A typed request accepted by the Engine.
// Distinct from runtime::Request (semantic/system-level).
// This is the external-facing interface type.
// ---------------------------------------------------------------------------
enum class RequestType {
    kExecuteWork,     // execute a Task/Job/Attempt work item
    kWorkflow,        // execute a Workflow definition
    kCancel,          // cancel an active execution
    kQueryState,      // query engine/work state without mutation
    kLifecycle,       // lifecycle operation (start/stop/shutdown)
};

inline std::string_view to_string(RequestType t) {
    switch (t) {
        case RequestType::kExecuteWork:  return "execute_work";
        case RequestType::kWorkflow:     return "workflow";
        case RequestType::kCancel:       return "cancel";
        case RequestType::kQueryState:   return "query_state";
        case RequestType::kLifecycle:    return "lifecycle";
    }
    return "unknown";
}

struct EngineRequest {
    std::string id;                        // unique request ID
    RequestType type;
    
    std::chrono::system_clock::time_point created_at;
    std::optional<std::chrono::milliseconds> timeout;
    std::optional<int> priority;
    
    // Optional target for the request
    std::optional<std::string> target_id;  // execution_id, workflow_id, etc.
};

// ---------------------------------------------------------------------------
// ExecuteWorkRequest
// A request to execute a work item (Task/Job).
// ---------------------------------------------------------------------------
struct ExecuteWorkRequest {
    runtime::work::Task task;
    runtime::work::Job job;
    
    runtime::ExecutionParameters parameters;
    
    // Execution mode override (optional)
    std::optional<runtime::work::ExecutionMode> preferred_mode;
};

// ---------------------------------------------------------------------------
// WorkflowRequest
// A request to execute a Workflow.
// ---------------------------------------------------------------------------
struct WorkflowRequest {
    runtime::workflow::WorkflowDefinition definition;
    
    // Runtime inputs for this execution
    std::map<std::string, std::string> inputs;
    
    runtime::TimeoutPolicy timeout_policy;
    runtime::RetryPolicy retry_policy;
};

// ---------------------------------------------------------------------------
// CancelRequest
// A request to cancel an active execution.
// ---------------------------------------------------------------------------
struct CancelRequest {
    std::string execution_id;
    std::optional<std::string> reason;
};

// ---------------------------------------------------------------------------
// QueryStateRequest
// A request to query engine or work state without mutation.
// ---------------------------------------------------------------------------
enum class QueryType {
    kEngineState,      // engine's own state
    kWorkItemState,    // state of a specific work item
    kPendingCount,     // how much work is pending
};

struct QueryStateRequest {
    QueryType type;
    
    // For kWorkItemState queries
    std::optional<std::string> target_id;
};

// ---------------------------------------------------------------------------
// LifecycleRequest
// A request to control engine lifecycle.
// ---------------------------------------------------------------------------
enum class LifecycleCommand {
    kStart,      // start/initialize the engine
    kStop,       // graceful shutdown
    kShutdown,   // immediate shutdown (forceful)
    kPause,      // pause accepting new work
    kResume,     // resume accepting new work
};

struct LifecycleRequest {
    LifecycleCommand command;
};

// ---------------------------------------------------------------------------
// EngineResult — Response to a request
// ---------------------------------------------------------------------------
template <typename T>
struct EngineResult : core::Outcome {
    std::string request_id;
    
    static EngineResult success(std::string req_id) {
        EngineResult r;
        r.request_id = std::move(req_id);
        r.status = core::SemanticStatus::kSuccess;
        r.verified = true;
        return r;
    }
    
    static EngineResult completed(std::string req_id) {
        EngineResult r;
        r.request_id = std::move(req_id);
        r.status = core::SemanticStatus::kCompleted;
        r.verified = false;
        return r;
    }
    
    static EngineResult failure(std::string req_id, std::string code, std::string message) {
        EngineResult r;
        r.request_id = std::move(req_id);
        r.status = core::SemanticStatus::kFailure;
        r.error = core::Error{std::move(code), std::move(message)};
        return r;
    }
    
    static EngineResult cancelled(std::string req_id, std::string message) {
        EngineResult r;
        r.request_id = std::move(req_id);
        r.status = core::SemanticStatus::kCancelled;
        r.error = core::Error{"E_CANCELLED", std::move(message)};
        return r;
    }
    
    static EngineResult unknown(std::string req_id, std::string message) {
        EngineResult r;
        r.request_id = std::move(req_id);
        r.status = core::SemanticStatus::kUnknown;
        r.error = core::Error{"E_UNKNOWN", std::move(message)};
        return r;
    }
};

// Use core::Result<T> directly to avoid nested type alias complexity

// ---------------------------------------------------------------------------
// EngineContext
// Context provided to the Engine at startup.
// ---------------------------------------------------------------------------
struct EngineContext {
    runtime::initialization::InitializationContext init_ctx;
    
    // Runtime configuration
    size_t max_concurrent_executions = 100;
    std::chrono::milliseconds default_timeout{30000};
    
    // Paths
    std::optional<std::filesystem::path> state_dir;        // persistent state
    std::optional<std::filesystem::path> data_dir;         // runtime data
    
    bool dry_run = false;
};

// ---------------------------------------------------------------------------
// EngineStatistics
// Runtime statistics about engine activity.
// ---------------------------------------------------------------------------
struct EngineStatistics {
    uint64_t requests_received = 0;
    uint64_t requests_completed = 0;
    uint64_t requests_failed = 0;
    
    uint64_t work_items_started = 0;
    uint64_t work_items_completed = 0;
    uint64_t work_items_cancelled = 0;
    
    std::chrono::milliseconds total_execution_time{0};
};

// ---------------------------------------------------------------------------
// Engine — The runtime facade/coordinator
//
// Responsibilities:
//   - Accept typed EngineRequest objects
//   - Maintain its own lifecycle state (EngineState)
//   - Defer actual execution to canonical executors (Executor/Runner)
//   - Expose controlled lifecycle entry/exit
// ---------------------------------------------------------------------------
class Engine {
public:
    explicit Engine(EngineContext ctx);
    
    ~Engine();
    
    // Lifecycle management — these ARE the canonical entry points
    core::Outcome initialize();
    core::Outcome shutdown();
    
    // Request acceptance (returns immediately, work may be queued)
    core::Result<std::string> execute_work(const ExecuteWorkRequest& req);
    core::Result<std::string> workflow(const WorkflowRequest& req);
    core::Result<bool> cancel(const CancelRequest& req);
    core::Result<runtime::EntityState> query_state(const QueryStateRequest& req);
    core::Result<bool> lifecycle(const LifecycleRequest& req);
    
    // Get current engine state (query-only, no mutation)
    EngineState get_state() const;
    core::Outcome get_health() const;
    bool is_ready() const;
    
    // Statistics (read-only snapshot)
    EngineStatistics get_statistics() const;

private:
    EngineContext ctx_;
    
    // Engine's own lifecycle state - using atomic for thread safety
    std::atomic<EngineState> state_{EngineState::kCreated};
    
    // Runtime statistics
    mutable std::mutex stats_mutex_;
    EngineStatistics stats_;
};

// ---------------------------------------------------------------------------
// EngineBuilder — Construct an Engine with flexible configuration
//
// NOT a registry or factory. A simple builder for a single Engine instance.
// ---------------------------------------------------------------------------
class EngineBuilder {
public:
    EngineBuilder();
    
    EngineBuilder& with_context(EngineContext ctx);
    EngineBuilder& with_max_concurrent(size_t count);
    EngineBuilder& with_default_timeout(std::chrono::milliseconds timeout);
    EngineBuilder& with_state_dir(std::filesystem::path path);
    EngineBuilder& with_data_dir(std::filesystem::path path);
    EngineBuilder& set_dry_run(bool value);
    
    std::unique_ptr<Engine> build();

private:
    EngineContext ctx_;
    bool context_set_ = false;
};

}  // namespace rebuntu::runtime::engine