// rebuntu::runtime::controller — Runtime Control Operations (Phase 4.6)
//
// The Controller provides typed runtime control operations for entities
// managed by Rebuntu's execution machinery:
//   - Cancellation (request, confirm, cancel)
//   - Pause/Resume (temporarily suspend and resume)
//   - Freeze/Unfreeze (complete state suspension)
//   - Terminate/Kill (forceful termination)
//
// Architecture:
//   * Controller is NOT an executor — it doesn't perform work directly
//   * Controller sends control signals to targets; execution remains with Runner/Executor
//   * Controller tracks control operation results and evidence
//   * Controller integrates with CancellationToken for cancellation propagation
//
// Design principles:
//   * Use existing cancellation token infrastructure where applicable
//   * Native Linux mechanisms (systemd, D-Bus, signals) own their native state
//   * Controller provides typed interface, delegates to appropriate mechanism

#pragma once

#include <runtime/core/contracts.hpp>
#include <runtime/cancellation/token.hpp>
#include <runtime/contracts.hpp>
#include <string>
#include <optional>
#include <chrono>
#include <vector>
#include <memory>

namespace rebuntu::runtime::controller {

// ============================================================================
// Control Target
// ============================================================================

enum class ControlTarget {
    kExecution,       // A specific execution instance (Runner/Job)
    kWorkflow,        // A workflow execution with multiple steps
    kService,         // A service managed by Rebuntu
    kProcess,         // An external process
    kCustom,          // Custom target type
};

inline std::string to_string(ControlTarget t) {
    switch (t) {
        case ControlTarget::kExecution: return "execution";
        case ControlTarget::kWorkflow:  return "workflow";
        case ControlTarget::kService:   return "service";
        case ControlTarget::kProcess:   return "process";
        case ControlTarget::kCustom:    return "custom";
    }
    return "unknown";
}

// ============================================================================
// Control Request
// ============================================================================

struct ControlRequest {
    std::string id;                              // Unique request ID
    std::chrono::system_clock::time_point created_at;
    
    ControlTarget target_type;                   // What kind of entity is being controlled
    std::string target_id;                       // Identifier for the target
    
    enum class Operation {
        kCancel,          // Request cancellation (graceful)
        kPause,           // Pause execution temporarily
        kResume,          // Resume from paused state
        kFreeze,          // Freeze all activity (state preservation)
        kUnfreeze,        // Unfreeze after freeze
        kTerminate,       // Immediate termination requested
        kKill,            // Force kill (last resort)
        kRestart,         // Restart target
    } operation;
    
    std::optional<std::string> reason;           // Why this control was requested
    std::optional<std::chrono::milliseconds> timeout;  // Timeout for the control action
    
    // Additional context for the request
    std::vector<std::pair<std::string, std::string>> metadata;
};

// ============================================================================
// Factory functions for ControlRequest construction
// ============================================================================

inline ControlRequest make_cancel_request(const std::string& target_id,
                                          std::optional<std::string> reason = std::nullopt) {
    return ControlRequest{
        .id = "ctrl_" + target_id + "_" + std::to_string(
            std::chrono::system_clock::now().time_since_epoch().count()),
        .created_at = std::chrono::system_clock::now(),
        .target_type = ControlTarget::kExecution,
        .target_id = target_id,
        .operation = ControlRequest::Operation::kCancel,
        .reason = std::move(reason),
    };
}

inline ControlRequest make_pause_request(const std::string& target_id,
                                         std::optional<std::chrono::milliseconds> timeout = std::nullopt) {
    return ControlRequest{
        .id = "ctrl_" + target_id + "_" + std::to_string(
            std::chrono::system_clock::now().time_since_epoch().count()),
        .created_at = std::chrono::system_clock::now(),
        .target_type = ControlTarget::kExecution,
        .target_id = target_id,
        .operation = ControlRequest::Operation::kPause,
        .timeout = timeout,
    };
}

inline ControlRequest make_resume_request(const std::string& target_id) {
    return ControlRequest{
        .id = "ctrl_" + target_id + "_" + std::to_string(
            std::chrono::system_clock::now().time_since_epoch().count()),
        .created_at = std::chrono::system_clock::now(),
        .target_type = ControlTarget::kExecution,
        .target_id = target_id,
        .operation = ControlRequest::Operation::kResume,
    };
}

// ============================================================================
// Control Result
// ============================================================================

enum class ControlResultStatus {
    kAccepted,        // Control request accepted for processing
    kPending,         // Request in progress
    kSuccess,         // Control operation completed successfully
    kFailed,          // Operation failed
    kTimedOut,        // Operation timed out before completion
    kNotFound,        // Target not found or no longer exists
    kUnsupported,     // Target does not support this operation
    kUnauthorized,    // Caller not authorized for this control action
};

inline std::string to_string(ControlResultStatus s) {
    switch (s) {
        case ControlResultStatus::kAccepted:   return "accepted";
        case ControlResultStatus::kPending:    return "pending";
        case ControlResultStatus::kSuccess:    return "success";
        case ControlResultStatus::kFailed:     return "failed";
        case ControlResultStatus::kTimedOut:   return "timed_out";
        case ControlResultStatus::kNotFound:   return "not_found";
        case ControlResultStatus::kUnsupported:return "unsupported";
        case ControlResultStatus::kUnauthorized: return "unauthorized";
    }
    return "unknown";
}

struct ControlResult {
    std::string request_id;                      // Original control request ID
    std::chrono::system_clock::time_point created_at;
    
    ControlResultStatus status;                  // Current status of the operation
    
    std::optional<std::chrono::system_clock::time_point> completed_at;
    
    // Result details
    std::optional<std::string> error_code;
    std::optional<std::string> error_message;
    std::vector<core::Evidence> evidence;        // Evidence supporting the result
    
    // State information (where applicable)
    std::optional<LifecycleState> lifecycle_state;
    std::optional<WorkState> work_state;
    std::optional<ControlState> control_state;
    
    bool succeeded() const {
        return status == ControlResultStatus::kSuccess;
    }
};

// ============================================================================
// Controller
// ============================================================================

class Controller {
public:
    virtual ~Controller() = default;
    
    // Submit a control request
    // Returns a result that may be updated as the operation progresses.
    virtual core::Outcome submit_control(const ControlRequest& request) = 0;
    
    // Query the status of a pending control request
    virtual std::optional<ControlResult> get_result(const std::string& request_id) const = 0;
    
    // Cancel a previously submitted control request (if possible)
    virtual core::Outcome cancel_control(const std::string& request_id) = 0;
};

// ============================================================================
// ControlObserver
// ============================================================================

class ControlObserver {
public:
    virtual ~ControlObserver() = default;
    
    // Called when a control operation starts
    virtual void on_control_started(const ControlRequest&) {}
    
    // Called when a control result is updated
    virtual void on_result_updated(const ControlResult&) {}
    
    // Called when a control completes (success or failure)
    virtual void on_control_completed(const std::string& request_id, const ControlResult&) {}
};

// ============================================================================
// ControllerBuilder
// ============================================================================

class ControllerBuilder {
public:
    ControllerBuilder();
    
    ControllerBuilder& set_default_timeout(std::chrono::milliseconds ms);
    ControllerBuilder& add_observer(std::shared_ptr<ControlObserver> observer);
    ControllerBuilder& set_cancellation_token(CancellationToken token);
    
    std::unique_ptr<Controller> build();

private:
    std::chrono::milliseconds default_timeout_{30000};  // 30 seconds
    std::vector<std::shared_ptr<ControlObserver>> observers_;
    CancellationToken cancellation_token_;
};

// ============================================================================
// Factory functions
// ============================================================================

std::unique_ptr<Controller> make_controller();
std::unique_ptr<Controller> make_controller_with_timeout(
    std::chrono::milliseconds timeout);

}  // namespace rebuntu::runtime::controller