// rebuntu::runtime::controller — Runtime Controller (Phase 4.6)
//
// The Controller is responsible for runtime control operations:
//   * Cancellation requests
//   * Pause/Resume (where supported)
//   * Freeze/Unfreeze (where supported)
//   * Lifecycle control requests
//
// The Controller does NOT own:
//   * Execution implementation (owned by Executor)
//   * State management (owned by Engine/Runner)
//   * Policy decisions (authorization, scheduling)
//   * Resource cleanup (owned by Runner/Executor)
//
// Control operations are advisory unless otherwise specified.
// A target may not support all control operations.

#pragma once

#include <system/core/contracts.hpp>
#include <system/runtime/work.hpp>
#include <string>
#include <memory>
#include <optional>
#include <chrono>
#include <functional>
#include <vector>
#include <mutex>

namespace rebuntu::runtime::controller {

// ============================================================================
// ControlOperation
// The type of control operation requested.
// ============================================================================

enum class ControlOperation {
    kCancel,        // Request cancellation of active execution
    kPause,         // Temporarily suspend execution (where supported)
    kResume,        // Resume paused execution (where supported)
    kFreeze,        // Completely freeze all activity (where supported)
    kUnfreeze,      // Unfreeze from frozen state (where supported)
    kStop,          // Request graceful termination
    kTerminate,     // Request immediate termination
};

inline std::string_view to_string(ControlOperation op) {
    switch (op) {
        case ControlOperation::kCancel:     return "cancel";
        case ControlOperation::kPause:      return "pause";
        case ControlOperation::kResume:     return "resume";
        case ControlOperation::kFreeze:     return "freeze";
        case ControlOperation::kUnfreeze:   return "unfreeze";
        case ControlOperation::kStop:       return "stop";
        case ControlOperation::kTerminate:  return "terminate";
    }
    return "unknown";
}

// ============================================================================
// TargetType
// What kind of entity can be controlled.
// ============================================================================

enum class TargetType {
    kExecution,     // A specific execution instance
    kRunner,        // A runner managing multiple executions
    kWorkflow,      // A workflow execution
    kEngine,        // The runtime engine itself
};

inline std::string_view to_string(TargetType t) {
    switch (t) {
        case TargetType::kExecution: return "execution";
        case TargetType::kRunner:    return "runner";
        case TargetType::kWorkflow:  return "workflow";
        case TargetType::kEngine:    return "engine";
    }
    return "unknown";
}

// ============================================================================
// ControlRequest
// A request to perform a control operation on a target.
// ============================================================================

struct ControlRequest {
    ControlOperation operation;
    
    // Target identification
    TargetType target_type;
    std::string target_id;  // execution_id, runner_id, workflow_id, or engine
    
    // Optional metadata
    std::optional<std::string> reason;       // Why this control was requested
    std::optional<int> timeout_ms;           // Timeout for the operation itself
    
    // Timestamps (set by controller when received)
    std::chrono::system_clock::time_point created_at;
    
    static ControlRequest cancel_execution(std::string exec_id, std::string reason = "") {
        ControlRequest req;
        req.operation = ControlOperation::kCancel;
        req.target_type = TargetType::kExecution;
        req.target_id = std::move(exec_id);
        if (!reason.empty()) req.reason = std::move(reason);
        req.created_at = std::chrono::system_clock::now();
        return req;
    }
    
    static ControlRequest pause_runner(std::string runner_id, std::string reason = "") {
        ControlRequest req;
        req.operation = ControlOperation::kPause;
        req.target_type = TargetType::kRunner;
        req.target_id = std::move(runner_id);
        if (!reason.empty()) req.reason = std::move(reason);
        req.created_at = std::chrono::system_clock::now();
        return req;
    }
    
    static ControlRequest resume_runner(std::string runner_id) {
        ControlRequest req;
        req.operation = ControlOperation::kResume;
        req.target_type = TargetType::kRunner;
        req.target_id = std::move(runner_id);
        req.created_at = std::chrono::system_clock::now();
        return req;
    }
    
    static ControlRequest stop_engine(std::string reason = "") {
        ControlRequest req;
        req.operation = ControlOperation::kStop;
        req.target_type = TargetType::kEngine;
        if (!reason.empty()) req.reason = std::move(reason);
        req.created_at = std::chrono::system_clock::now();
        return req;
    }
};

// ============================================================================
// ControlResult
// The result of a control operation.
//
// Key distinction: A cancellation REQUEST does not prove the target CANCELLED.
// The result must be verified independently.
// ============================================================================

enum class ControlStatus {
    kAccepted,      // Request accepted (may still need to execute)
    kCompleted,     // Operation completed successfully
    kCancelled,     // Target was already cancelled
    kFailed,        // Operation failed
    kUnsupported,   // Target does not support this operation
    kUnknown,       // Could not determine result
};

inline std::string_view to_string(ControlStatus s) {
    switch (s) {
        case ControlStatus::kAccepted:    return "accepted";
        case ControlStatus::kCompleted:   return "completed";
        case ControlStatus::kCancelled:   return "cancelled";
        case ControlStatus::kFailed:      return "failed";
        case ControlStatus::kUnsupported: return "unsupported";
        case ControlStatus::kUnknown:     return "unknown";
    }
    return "unknown";
}

struct ControlResult {
    ControlOperation operation;
    std::string target_id;
    
    // Result status
    ControlStatus status;
    
    // Verification status
    bool verified = false;  // Was the outcome independently verified?
    
    // Timing information
    std::chrono::system_clock::time_point requested_at;
    std::optional<std::chrono::system_clock::time_point> completed_at;
    std::optional<std::chrono::milliseconds> duration_ms;
    
    // Error information (if not success)
    std::optional<core::Error> error;
    
    // Evidence for verification
    std::vector<core::Evidence> evidence;
    
    static ControlResult accepted(std::string target_id, ControlOperation op) {
        ControlResult r;
        r.operation = op;
        r.target_id = std::move(target_id);
        r.status = ControlStatus::kAccepted;
        r.requested_at = std::chrono::system_clock::now();
        return r;
    }
    
    static ControlResult completed(std::string target_id, ControlOperation op) {
        ControlResult r;
        r.operation = op;
        r.target_id = std::move(target_id);
        r.status = ControlStatus::kCompleted;
        r.verified = true;
        r.requested_at = std::chrono::system_clock::now();
        return r;
    }
    
    static ControlResult cancelled(std::string target_id, ControlOperation op) {
        ControlResult r;
        r.operation = op;
        r.target_id = std::move(target_id);
        r.status = ControlStatus::kCancelled;
        r.verified = true;
        r.requested_at = std::chrono::system_clock::now();
        return r;
    }
    
    static ControlResult failed(std::string target_id, ControlOperation op, 
                                std::string code, std::string message) {
        ControlResult r;
        r.operation = op;
        r.target_id = std::move(target_id);
        r.status = ControlStatus::kFailed;
        r.error = core::Error{std::move(code), std::move(message)};
        r.requested_at = std::chrono::system_clock::now();
        return r;
    }
    
    static ControlResult unsupported(std::string target_id, ControlOperation op) {
        ControlResult r;
        r.operation = op;
        r.target_id = std::move(target_id);
        r.status = ControlStatus::kUnsupported;
        r.requested_at = std::chrono::system_clock::now();
        return r;
    }
    
    static ControlResult unknown(std::string target_id, ControlOperation op,
                                 std::string message) {
        ControlResult r;
        r.operation = op;
        r.target_id = std::move(target_id);
        r.status = ControlStatus::kUnknown;
        r.error = core::Error{"E_UNKNOWN", std::move(message)};
        r.requested_at = std::chrono::system_clock::now();
        return r;
    }
    
    bool success() const {
        return status == ControlStatus::kCompleted || 
               status == ControlStatus::kAccepted ||
               status == ControlStatus::kCancelled;
    }
};

// ============================================================================
// Controller
// The canonical controller for runtime operations.
//
// Responsibilities:
//   * Accept control requests (cancel, pause, resume, etc.)
//   * Route to appropriate target (execution, runner, workflow, engine)
//   * Produce evidence of control actions taken
//   * Return result with verification status
//
// The Controller does NOT:
//   * Implement execution logic (owned by Executor)
//   * Manage state (owned by Engine/Runner)
//   * Make policy decisions (authorization, scheduling)
// ============================================================================

class Controller {
public:
    using ControlHandler = std::function<ControlResult(const ControlRequest&)>;
    
    explicit Controller();
    virtual ~Controller() = default;
    
    // Disable copy/move
    Controller(const Controller&) = delete;
    Controller& operator=(const Controller&) = delete;
    
    // Submit a control request (may be asynchronous)
    // Returns immediately with an accepted result; actual completion is verified.
    virtual ControlResult submit_control(const ControlRequest& req);
    
    // Execute a control request synchronously
    virtual ControlResult execute_control(const ControlRequest& req);
    
    // Request cancellation of a specific execution
    virtual ControlResult cancel_execution(std::string exec_id, std::string reason = "");
    
    // Request pause of a runner/workflow
    virtual ControlResult pause_target(std::string target_id, std::string type, std::string reason = "");
    
    // Request resume of a paused target
    virtual ControlResult resume_target(std::string target_id, std::string type);
    
    // Get control capabilities for a target type
    virtual std::vector<ControlOperation> get_capabilities(TargetType type) const;
    
    // Check if a specific operation is supported on a target
    virtual bool supports_operation(TargetType type, ControlOperation op) const;
    
    // Query the current state of a controlled entity
    virtual runtime::EntityState query_state(const std::string& target_id, TargetType type) const;

protected:
    // Subclass hooks for specific controller implementations
    virtual ControlResult handle_cancel(const ControlRequest& req);
    virtual ControlResult handle_pause(const ControlRequest& req);
    virtual ControlResult handle_resume(const ControlRequest& req);
    virtual ControlResult handle_freeze(const ControlRequest& req);
    virtual ControlResult handle_unfreeze(const ControlRequest& req);
    virtual ControlResult handle_stop(const ControlRequest& req);
    virtual ControlResult handle_terminate(const ControlRequest& req);

private:
    // Track control request history for verification
    mutable std::mutex mutex_;
};

// ============================================================================
// ExecutionController
// Controller specialized for execution instances.
// ============================================================================

class ExecutionController : public Controller {
public:
    explicit ExecutionController();
    ~ExecutionController() override;
    
    // Control a specific execution by ID
    ControlResult cancel_execution(std::string exec_id, std::string reason = "") override;
    ControlResult pause_target(std::string target_id, std::string type, std::string reason = "") override;
    ControlResult resume_target(std::string target_id, std::string type) override;
    
    // Query execution state
    runtime::EntityState query_state(const std::string& exec_id, TargetType type) const override;
    
    // Get capabilities for this controller
    std::vector<ControlOperation> get_capabilities(TargetType type) const override;

private:
    class Impl;
    std::unique_ptr<Impl> pimpl_;
};

// ============================================================================
// EngineController
// Controller specialized for engine lifecycle control.
// ============================================================================

class EngineController : public Controller {
public:
    explicit EngineController();
    ~EngineController() override;
    
    // Engine-specific control operations
    ControlResult shutdown_engine(std::string reason = "");
    ControlResult freeze_engine(std::string reason = "");
    ControlResult unfreeze_engine();
    
    runtime::EntityState query_state(const std::string& target_id, TargetType type) const override;

private:
    class Impl;
    std::unique_ptr<Impl> pimpl_;
};

// ============================================================================
// Factory functions
// ============================================================================

std::unique_ptr<Controller> make_default_controller();

}  // namespace rebuntu::runtime::controller