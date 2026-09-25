// rebuntu::runtime::engine — Engine Facade (Phase 4.2)
//
// The Engine is a stable runtime facade/coordinator for accepting typed work
// into Rebuntu's execution machinery.
//
// Design Philosophy:
//   * Engine is NOT a God object containing execution, policy, scheduling,
//     state, service management, and domain logic
//   * Engine delegates to specialized components (Dispatcher, Runner, Executor)
//   * Engine binds runtime context and invokes canonical resolution/dispatch path
//   * Engine provides controlled lifecycle entry/exit points
//
// Canonical Runtime Flow:
//   REQUEST -> VALIDATION -> TARGET/CAPABILITY RESOLUTION -> AUTHORIZATION/POLICY
//     -> DISPATCH -> TASK/JOB REALIZATION -> EXECUTION -> ATTEMPT
//     -> NATIVE/PROVIDER ACTION -> OBSERVED RESULTING STATE -> POSTCONDITIONS
//     -> VERIFICATION -> EVIDENCE -> RESULT

#pragma once

#include <runtime/contracts.hpp>
#include <system/runtime/work.hpp>
#include <runtime/cancellation/token.hpp>
#include <memory>
#include <optional>
#include <string>
#include <vector>
#include <map>
#include <mutex>
#include <chrono>

namespace rebuntu::runtime::engine {

// EngineState: Lifecycle state of the Engine
enum class EngineState {
    kCreated,      // Engine instantiated but not initialized
    kInitializing, // Initialization in progress
    kReady,        // Ready to accept work
    kStopping,     // Shutdown initiated
    kStopped,      // Fully stopped
};

inline std::string engine_state_to_string(EngineState s) {
    switch (s) {
        case EngineState::kCreated:     return "created";
        case EngineState::kInitializing: return "initializing";
        case EngineState::kReady:       return "ready";
        case EngineState::kStopping:    return "stopping";
        case EngineState::kStopped:     return "stopped";
    }
    return "unknown";
}

// EngineContext: Runtime context bound by the Engine
//
// This is the execution environment that all submitted work inherits.
struct EngineContext {
    std::string engine_instance_id;           // Unique identifier for this Engine instance
    std::chrono::system_clock::time_point created_at;
    
    // Default policies for submitted work
    rebuntu::runtime::TimeoutPolicy default_timeout_policy;
    rebuntu::runtime::RetryPolicy default_retry_policy;
    
    // Execution constraints
    size_t max_concurrent_executions = 100;
    bool allow_concurrent_workflows = true;
};

// WorkSubmission: A typed request to execute work through the Engine
//
// This is the canonical entry point for all work into Rebuntu's runtime.
struct WorkSubmission {
    std::string id;                           // Unique submission ID
    std::chrono::system_clock::time_point submitted_at;
    
    // Target: what kind of work is this?
    enum class Kind {
        kTask,          // Execute a Task (parameterized operation)
        kWorkflow,      // Execute a Workflow (sequence of steps)
        kOperation,     // Execute an Operation (direct capability invocation)
    } kind = Kind::kTask;
    
    std::string target_id;                    // ID of the Task/Workflow/Operation
    std::vector<std::pair<std::string, std::string>> parameters;  // Input parameters
    
    // Execution control overrides (optional - uses EngineContext defaults if not set)
    std::optional<rebuntu::runtime::TimeoutPolicy> timeout_policy;
    std::optional<rebuntu::runtime::RetryPolicy> retry_policy;
    
    // Request metadata
    std::optional<std::string> caller_id;     // For authorization/audit
    std::optional<int> priority;              // Numeric priority (higher = more urgent)
    std::optional<std::string> correlation_id;  // Link to higher-level workflow
    
    // Verification requirements
    bool requires_verification = false;
};

// SubmissionResult: Result of a work submission
//
// This indicates whether the submission was accepted and provides tracking info.
struct SubmissionResult {
    core::SemanticStatus status;
    
    // If accepted, these identify the execution for status/result queries
    std::optional<work::JobId> job_id;         // For Task/Workflow submissions
    std::optional<work::ExecutionId> execution_id;
};

// EngineMetrics: Runtime metrics for monitoring
struct EngineMetrics {
    size_t submissions_received = 0;
    size_t submissions_accepted = 0;
    size_t submissions_rejected = 0;
    size_t active_executions = 0;
    size_t total_jobs_completed = 0;
    std::chrono::milliseconds total_execution_time_ms{0};
};

// EngineListener: Callback interface for engine events
//
// Used for monitoring/debugging without coupling to specific event systems.
class EngineListener {
public:
    virtual ~EngineListener() = default;
    
    // Called when a work submission is received
    virtual void on_submission_received(const WorkSubmission&) {}
    
    // Called when a work submission is accepted (queued)
    virtual void on_submission_accepted(const SubmissionResult&) {}
    
    // Called when a work submission is rejected
    virtual void on_submission_rejected(const WorkSubmission&, const core::Error&) {}
    
    // Called when an execution starts
    virtual void on_execution_started(work::ExecutionId exec_id) {}
    
    // Called when an execution completes
    virtual void on_execution_completed(work::ExecutionId exec_id, core::Outcome outcome) {}
};

// EngineResult: Result of engine operations (using Outcome from contracts)
using EngineResult = core::Outcome;

// Engine is the canonical runtime facade
//
// The Engine does NOT:
//   - Implement policy (authorization, scheduling, routing)
//   - Execute work directly (delegates to Executor)
//   - Track execution state machines (Runner handles that)
//   - Own native resources without RAII cleanup
//
// The Engine DOES:
//   - Provide a stable facade for typed work submission
//   - Bind runtime context and apply defaults
//   - Invoke canonical resolution/dispatch path
//   - Expose controlled lifecycle entry/exit points
//   - Aggregate metrics and events
class Engine {
public:
    using ListenerPtr = std::shared_ptr<EngineListener>;
    
    // Construct an Engine with default configuration
    explicit Engine();
    
    // Construct an Engine with custom context
    explicit Engine(EngineContext ctx);
    
    virtual ~Engine();
    
    // Initialize the engine (transition from kCreated to kReady)
    // Must be called before submitting work.
    EngineResult initialize();
    
    // Stop the engine (graceful shutdown)
    // Blocks until all active executions complete or timeout.
    EngineResult stop(std::optional<std::chrono::milliseconds> timeout = std::nullopt);
    
    // Submit a WorkSubmission for execution
    // Returns SubmissionResult indicating whether accepted and tracking IDs.
    SubmissionResult submit(const WorkSubmission& submission);
    
    // Query execution status by ID
    std::optional<work::JobState> get_job_state(work::JobId job_id) const;
    
    // Get current engine state
    EngineState state() const { return state_; }
    
    // Get metrics for monitoring
    EngineMetrics metrics() const;
    
    // Add a listener for engine events
    void add_listener(ListenerPtr listener);
    
    // Remove a listener
    void remove_listener(const ListenerPtr& listener);

private:
    EngineContext context_;
    EngineState state_ = EngineState::kCreated;
    
    std::vector<ListenerPtr> listeners_;
    mutable std::mutex listeners_mutex_{};
    
    EngineMetrics metrics_;
    mutable std::mutex metrics_mutex_{};
    
    // Active executions tracking (for shutdown coordination)
    size_t active_executions_ = 0;
    mutable std::mutex active_executions_mutex_{};
    
    // Job execution state storage
    std::map<work::JobId, work::JobState> job_states_;
    mutable std::mutex job_states_mutex_{};
};

// EngineBuilder: Fluent builder for Engine configuration
class EngineBuilder {
public:
    EngineBuilder();
    
    EngineBuilder& set_instance_id(std::string id);
    EngineBuilder& set_default_timeout(std::chrono::milliseconds ms);
    EngineBuilder& set_max_concurrent_executions(size_t count);
    
    std::unique_ptr<Engine> build();

private:
    EngineContext context_;
};

// Factory functions
inline std::unique_ptr<Engine> make_engine() {
    return std::make_unique<Engine>();
}

inline std::unique_ptr<Engine> make_engine_with_context(EngineContext ctx) {
    return std::make_unique<Engine>(std::move(ctx));
}

}  // namespace rebuntu::runtime::engine