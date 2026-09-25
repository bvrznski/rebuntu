// rebuntu::runtime::coordination::Context — Execution coordination context (Phase 4.7)
//
// The Coordinator provides coordination primitives for multiple runtime actors:
//   - Dependency completion tracking (wait for multiple executions to complete)
//   - Shared resource exclusion (mutex-like coordination between executors)
//   - Bounded fan-in/fan-out patterns (collect results from multiple sources)
//   - Ordered handoff between execution instances
//
// Design principles:
//   * Coordinator is NOT an executor — it doesn't perform work directly
//   * Coordinator tracks cross-execution relationships and constraints
//   * Coordinator provides coordination primitives to other runtime components
//   * Coordinator integrates with native Linux mechanisms (locks, events, signals)

#pragma once

#include <system/core/contracts.hpp>
#include <runtime/cancellation/token.hpp>
#include <runtime/work.hpp>
#include <string>
#include <optional>
#include <chrono>
#include <vector>
#include <set>
#include <map>
#include <memory>

namespace rebuntu::runtime::coordination {

// ============================================================================
// Coordination Target
// ============================================================================

enum class CoordinationTarget {
    kExecution,       // A specific execution instance
    kJob,             // A job with potentially multiple attempts
    kWorkflow,        // A workflow execution with multiple steps
    kResource,        // A shared resource that needs exclusive access
    kDependency,      // A dependency that must complete before activation
};

inline std::string to_string(CoordinationTarget t) {
    switch (t) {
        case CoordinationTarget::kExecution: return "execution";
        case CoordinationTarget::kJob:       return "job";
        case CoordinationTarget::kWorkflow:  return "workflow";
        case CoordinationTarget::kResource:  return "resource";
        case CoordinationTarget::kDependency:return "dependency";
    }
    return "unknown";
}

// ============================================================================
// Coordination Request
// ============================================================================

struct CoordinationRequest {
    std::string id;                              // Unique request ID
    std::chrono::system_clock::time_point created_at;
    
    CoordinationTarget target_type;              // What kind of entity is being coordinated
    std::string target_id;                       // Identifier for the target
    
    enum Operation {
        kWaitFor,           // Wait for completion of other entities
        kAcquire,           // Acquire exclusive access to a resource
        kRelease,           // Release exclusive access to a resource
        kJoin,              // Join multiple execution results (fan-in)
        kHandoff,           // Order handoff from one executor to another
        kSignal,            // Signal completion to waiting parties
        kBarrier,           // Create barrier for synchronized activation
    } operation;
    
    std::optional<std::string> reason;           // Why this coordination was requested
    std::optional<std::chrono::milliseconds> timeout;  // Timeout for the coordination action
    
    // Additional context for the request
    std::vector<std::pair<std::string, std::string>> metadata;
    
    // Dependencies (for kWaitFor)
    std::vector<work::ExecutionId> dependency_ids;
};

// ============================================================================
// Factory functions for CoordinationRequest construction
// ============================================================================

inline CoordinationRequest make_wait_for_request(const work::ExecutionId& exec_id,
                                                  const std::vector<work::ExecutionId>& deps,
                                                  std::optional<std::string> reason = std::nullopt) {
    CoordinationRequest req;
    req.id = "coord_" + exec_id.value + "_" + std::to_string(
        std::chrono::system_clock::now().time_since_epoch().count());
    req.created_at = std::chrono::system_clock::now();
    req.target_type = CoordinationTarget::kExecution;
    req.target_id = exec_id.value;
    req.operation = CoordinationRequest::Operation::kWaitFor;
    req.reason = reason;
    req.dependency_ids = deps;
    return req;
}

inline CoordinationRequest make_acquire_request(const work::ExecutionId& exec_id,
                                                 const std::string& resource_id,
                                                 std::optional<std::chrono::milliseconds> timeout = std::nullopt) {
    CoordinationRequest req;
    req.id = "coord_" + exec_id.value + "_acq_" + resource_id + "_" + std::to_string(
        std::chrono::system_clock::now().time_since_epoch().count());
    req.created_at = std::chrono::system_clock::now();
    req.target_type = CoordinationTarget::kResource;
    req.target_id = resource_id;
    req.operation = CoordinationRequest::Operation::kAcquire;
    req.timeout = timeout;
    return req;
}

inline CoordinationRequest make_release_request(const work::ExecutionId& exec_id,
                                                 const std::string& resource_id) {
    CoordinationRequest req;
    req.id = "coord_" + exec_id.value + "_rel_" + resource_id + "_" + std::to_string(
        std::chrono::system_clock::now().time_since_epoch().count());
    req.created_at = std::chrono::system_clock::now();
    req.target_type = CoordinationTarget::kResource;
    req.target_id = resource_id;
    req.operation = CoordinationRequest::Operation::kRelease;
    return req;
}

// ============================================================================
// Coordination Result
// ============================================================================

enum class CoordinationResultStatus {
    kAccepted,        // Coordination request accepted for processing
    kPending,         // Request in progress (e.g., waiting for dependencies)
    kSuccess,         // Coordination operation completed successfully
    kFailed,          // Operation failed
    kTimedOut,        // Operation timed out before completion
    kNotFound,        // Target not found or no longer exists
    kDeadlock,        // Circular dependency detected
    kCancelled,       // Coordination was cancelled
};

inline std::string to_string(CoordinationResultStatus s) {
    switch (s) {
        case CoordinationResultStatus::kAccepted:  return "accepted";
        case CoordinationResultStatus::kPending:   return "pending";
        case CoordinationResultStatus::kSuccess:   return "success";
        case CoordinationResultStatus::kFailed:    return "failed";
        case CoordinationResultStatus::kTimedOut:  return "timed_out";
        case CoordinationResultStatus::kNotFound:  return "not_found";
        case CoordinationResultStatus::kDeadlock:  return "deadlock";
        case CoordinationResultStatus::kCancelled: return "cancelled";
    }
    return "unknown";
}

struct CoordinationResult {
    std::string request_id;                      // Original coordination request ID
    std::chrono::system_clock::time_point created_at;
    
    CoordinationResultStatus status;             // Current status of the operation
    
    std::optional<std::chrono::system_clock::time_point> completed_at;
    
    // Result details
    std::optional<std::string> error_code;
    std::optional<std::string> error_message;
    std::vector<core::Evidence> evidence;        // Evidence supporting the result
    
    // State information (where applicable)
    std::optional<std::string> resource_holder_id;  // Who currently holds a resource lock
};

// ============================================================================
// CoordinatorObserver
// ============================================================================

class CoordinatorObserver {
public:
    virtual ~CoordinatorObserver() = default;
    
    // Called when a coordination request is accepted
    virtual void on_request_accepted(const CoordinationRequest&) {}
    
    // Called when coordination state changes (e.g., pending -> success)
    virtual void on_state_changed(const std::string& request_id, CoordinationResultStatus new_status) {}
    
    // Called when a coordination completes (success or failure)
    virtual void on_coordination_completed(const std::string& request_id, const CoordinationResult&) {}
};

// ============================================================================
// Coordinator — Coordination management interface
//
// The Coordinator provides primitives for coordinating multiple runtime actors:
//   - Dependency completion tracking
//   - Resource exclusion/locks
//   - Fan-in (collect from multiple sources)
//   - Ordered handoff between executions
// ============================================================================

class Coordinator {
public:
    using ObserverPtr = std::shared_ptr<CoordinatorObserver>;
    
    virtual ~Coordinator() = default;
    
    // Submit a coordination request
    // Returns immediately with status; async results delivered via observer callbacks.
    virtual core::Outcome submit_coordination(const CoordinationRequest& request) = 0;
    
    // Query the status of a pending coordination request
    virtual std::optional<CoordinationResult> get_result(const std::string& request_id) const = 0;
    
    // Cancel a previously submitted coordination request (if possible)
    virtual core::Outcome cancel_coordination(const std::string& request_id) = 0;
    
    // Add an observer for coordination events
    virtual void add_observer(ObserverPtr observer) = 0;
    
    // Remove an observer
    virtual void remove_observer(const ObserverPtr& observer) = 0;
};

// ============================================================================
// CoordinatorBuilder — Fluent builder for Coordinator configuration
// ============================================================================

class CoordinatorBuilder {
public:
    using ObserverPtr = std::shared_ptr<CoordinatorObserver>;
    
    CoordinatorBuilder();
    
    CoordinatorBuilder& set_default_timeout(std::chrono::milliseconds ms);
    CoordinatorBuilder& add_observer(ObserverPtr observer);
    CoordinatorBuilder& set_max_concurrent_coordination(size_t count);
    
    std::unique_ptr<Coordinator> build();

private:
    std::chrono::milliseconds default_timeout_{30000};  // Default 30 seconds
    std::vector<ObserverPtr> observers_;
    size_t max_concurrent_coordination_ = 100;
};

// ============================================================================
// Factory functions
// ============================================================================

std::unique_ptr<Coordinator> make_coordinator();
std::unique_ptr<Coordinator> make_coordinator_with_timeout(std::chrono::milliseconds timeout);

}  // namespace rebuntu::runtime::coordination