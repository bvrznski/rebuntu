// rebuntu::runtime — operational contracts (Phase 0.2)
//
// This file establishes Rebuntu's operational grammar: how entities
// are instantiated, activated, executed, controlled, and coordinated.
//
// Key distinctions established here:
//   * Specification vs Runtime Instance
//   * Execution vs Verification success
//   * State vs Status vs Health vs Readiness
//   * Request vs Event vs Signal vs Trigger
//   * Lifecycle dimensions (orthogonal: lifecycle, work, health, recovery)
//   * Evidence as first-class concept
//
// Phase 0.14 Update:
//   * Added ControlState dimension for administrative control
//   * Added ReadinessState dimension for explicit readiness states
//   * Added kJammed WorkState variant for detecting hung processes

#pragma once

#include <system/core/contracts.hpp>
#include <algorithm>
#include <cmath>
#include <chrono>
#include <optional>
#include <string>
#include <string_view>
#include <vector>

namespace rebuntu::runtime {

// ---------------------------------------------------------------------------
// Lifecycle State (orthogonal dimension)
// The lifecycle stage of an entity's existence.
// ---------------------------------------------------------------------------

enum class LifecycleState {
    kCreated,       // defined but not yet initialized
    kInitializing,  // initialization in progress
    kReady,         // initialized and ready for activation
    kActive,        // running/operational
    kStopping,      // shutdown initiated, pending cleanup
    kStopped,       // fully stopped
    kFailed,        // terminated due to error/failure
};

inline std::string_view to_string(LifecycleState s) {
    switch (s) {
        case LifecycleState::kCreated:     return "created";
        case LifecycleState::kInitializing: return "initializing";
        case LifecycleState::kReady:       return "ready";
        case LifecycleState::kActive:      return "active";
        case LifecycleState::kStopping:    return "stopping";
        case LifecycleState::kStopped:     return "stopped";
        case LifecycleState::kFailed:      return "failed";
    }
    return "unknown";
}

// ---------------------------------------------------------------------------
// Work State (orthogonal dimension)
// What the entity is currently doing.
// ---------------------------------------------------------------------------

enum class WorkState {
    kIdle,          // not actively working
    kProcessing,    // processing a task/request
    kWaiting,       // waiting for dependency/event
    kPaused,        // temporarily suspended
    kJammed,        // alive but failing to make forward progress (distinct from normal waiting)
};

inline std::string_view to_string(WorkState s) {
    switch (s) {
        case WorkState::kIdle:     return "idle";
        case WorkState::kProcessing: return "processing";
        case WorkState::kWaiting:  return "waiting";
        case WorkState::kPaused:   return "paused";
        case WorkState::kJammed:   return "jammed";
    }
    return "unknown";
}

// ---------------------------------------------------------------------------
// Control State (orthogonal dimension)
// Administrative control state imposed on the entity.
// ---------------------------------------------------------------------------

enum class ControlState {
    kEnabled,       // entity is enabled for operation
    kDisabled,      // administratively disabled
    kPaused,        // temporarily suspended by administrator
    kFrozen,        // completely frozen (all activity suspended)
    kLocked,        // locked (resource ownership conflict or security hold)
};

inline std::string_view to_string(ControlState s) {
    switch (s) {
        case ControlState::kEnabled:  return "enabled";
        case ControlState::kDisabled: return "disabled";
        case ControlState::kPaused:   return "paused_admin";
        case ControlState::kFrozen:   return "frozen";
        case ControlState::kLocked:   return "locked";
    }
    return "unknown";
}

// ---------------------------------------------------------------------------
// Readiness State (orthogonal dimension)
// Can the entity correctly accept/perform work now?
// ---------------------------------------------------------------------------

enum class ReadinessState {
    kReady,         // can accept/perform work
    kNotReady,      // cannot accept/perform work yet
};

inline std::string_view to_string(ReadinessState s) {
    switch (s) {
        case ReadinessState::kReady:     return "ready";
        case ReadinessState::kNotReady:  return "not_ready";
    }
    return "unknown";
}

// ---------------------------------------------------------------------------
// Health State (orthogonal dimension)
// The sustained qualitative state of the entity.
// ---------------------------------------------------------------------------

enum class HealthState {
    kUnknown,       // health has not been assessed
    kHealthy,       // operating normally
    kDegraded,      // operational but with reduced capability
    kUnhealthy,     // impaired or non-functional
};

inline std::string_view to_string(HealthState s) {
    switch (s) {
        case HealthState::kUnknown:   return "unknown";
        case HealthState::kHealthy:   return "healthy";
        case HealthState::kDegraded:  return "degraded";
        case HealthState::kUnhealthy: return "unhealthy";
    }
    return "unknown";
}

// ---------------------------------------------------------------------------
// Recovery State (orthogonal dimension)
// What recovery action, if any, is in progress.
// ---------------------------------------------------------------------------

enum class RecoveryState {
    kNone,          // no recovery in progress
    kRetrying,      // retry attempt in progress
    kRollingBack,   // rollback in progress
    kRestoring,     // restore from checkpoint in progress
    kReparing,      // repair operation in progress
    kFailingOver,   // failover to alternate in progress
};

inline std::string_view to_string(RecoveryState s) {
    switch (s) {
        case RecoveryState::kNone:       return "none";
        case RecoveryState::kRetrying:   return "retrying";
        case RecoveryState::kRollingBack: return "rolling_back";
        case RecoveryState::kRestoring:  return "restoring";
        case RecoveryState::kReparing:   return "repairing";
        case RecoveryState::kFailingOver: return "failing_over";
    }
    return "unknown";
}

// ---------------------------------------------------------------------------
// Request
// A semantic/system request for something to happen.
// Distinct from Call (invocation mechanism) and Command (user representation).
// ---------------------------------------------------------------------------

struct Request {
    std::string id;              // unique identifier for this request
    std::chrono::system_clock::time_point created_at;
    
    std::string operation;       // semantic operation requested
    std::optional<std::string> target;  // optional target of the operation
    
    std::vector<std::pair<std::string, std::string>> parameters;  // operation parameters
    
    std::optional<std::chrono::milliseconds> timeout;
    std::optional<int> priority;  // numeric priority (higher = more urgent)
    
    // Origin/context information
    std::optional<std::string> origin;      // who/what made the request
    std::optional<std::string> context;     // additional context
    
    // Constraints
    bool requires_verification = false;
    bool requires_authorization = false;
};

// ---------------------------------------------------------------------------
// Event
// An immutable statement that something occurred or was observed.
// Events may originate from Rebuntu, systemd, kernel, filesystem, network, etc.
// Distinct from Request (request for action) and Signal (control indication).
// ---------------------------------------------------------------------------

struct Event {
    std::string id;              // unique identifier
    std::chrono::system_clock::time_point occurred_at;
    
    std::string source;          // where the event came from
    std::string type;            // event type/category
    
    // Event data (bounded, evidence-backed)
    std::vector<core::Evidence> evidence;
    
    // Optional metadata
    std::optional<std::string> subject;   // what the event is about
    std::optional<int64_t> sequence;      // ordering hint for events from same source
    
    bool is_observable = true;  // false = internal/system-only event
};

// ---------------------------------------------------------------------------
// Signal
// A lightweight control/notification indication.
// Distinct from Event (which reports something happened).
// Note: This is NOT meant to replace Linux process signals; those remain native.
// ---------------------------------------------------------------------------

enum class SignalType {
    kNone,           // no signal
    kPause,          // pause execution
    kResume,         // resume execution
    kCancel,         // request cancellation
    kTerminate,      // immediate termination requested
    kReconfigure,    // reload configuration
    kHeartbeat,      // liveness heartbeat
};

inline std::string_view to_string(SignalType s) {
    switch (s) {
        case SignalType::kNone:        return "none";
        case SignalType::kPause:       return "pause";
        case SignalType::kResume:      return "resume";
        case SignalType::kCancel:      return "cancel";
        case SignalType::kTerminate:   return "terminate";
        case SignalType::kReconfigure: return "reconfigure";
        case SignalType::kHeartbeat:   return "heartbeat";
    }
    return "unknown";
}

struct Signal {
    SignalType type;
    std::optional<std::string> target;  // optional recipient
};

// ---------------------------------------------------------------------------
// Trigger
// An activation decision produced because activation criteria were satisfied.
// Distinct from Event (something happened) and Condition (proposition evaluated).
//
// Example: udev event + condition match → trigger: activate workflow
// ---------------------------------------------------------------------------

struct Trigger {
    std::string id;
    std::chrono::system_clock::time_point activated_at;
    
    std::string source_event_id;   // the event that triggered this
    
    std::optional<std::string> activation_kind;  // "workflow", "task", "service"
    std::optional<std::string> activation_target;  // identifier of what to activate
};

// ---------------------------------------------------------------------------
// Condition
// A proposition that may be evaluated over state/context.
// Used for activation, verification, policy, diagnostics, security, recovery.
//
// Examples:
//   - service.active == true
//   - mount.available == false  
//   - temperature > threshold
// ---------------------------------------------------------------------------

enum class ConditionOperator {
    kEquals,
    kNotEquals,
    kGreaterThan,
    kGreaterOrEqual,
    kLessThan,
    kLessOrEqual,
    kExists,
    kContains,
};

inline std::string_view to_string(ConditionOperator op) {
    switch (op) {
        case ConditionOperator::kEquals:         return "==";
        case ConditionOperator::kNotEquals:      return "!=";
        case ConditionOperator::kGreaterThan:    return ">";
        case ConditionOperator::kGreaterOrEqual: return ">=";
        case ConditionOperator::kLessThan:       return "<";
        case ConditionOperator::kLessOrEqual:    return "<=";
        case ConditionOperator::kExists:         return "exists";
        case ConditionOperator::kContains:       return "contains";
    }
    return "?";
}

struct ConditionOperand {
    std::string path;  // e.g., "service.active", "mount.available"
};

struct Condition {
    ConditionOperand lhs;
    ConditionOperator op;
    std::optional<ConditionOperand> rhs_value;  // optional for unary operators like exists
};

inline bool operator==(const Condition& a, const Condition& b) {
    if (a.lhs.path != b.lhs.path || a.op != b.op) return false;
    
    // Handle optional rhs_value
    bool a_has_rhs = a.rhs_value.has_value();
    bool b_has_rhs = b.rhs_value.has_value();
    if (a_has_rhs != b_has_rhs) return false;
    
    if (a_has_rhs && b_has_rhs) {
        return a.rhs_value->path == b.rhs_value->path;
    }
    return true;
}

// ---------------------------------------------------------------------------
// State snapshot (combining all dimensions)
// A complete view of an entity's current state across orthogonal dimensions.
//
// All five dimensions are independent:
//   lifecycle  = stage of existence (created -> failed)
//   work       = what it's doing now (idle, processing, waiting, paused, jammed)
//   control    = admin status (enabled, disabled, paused, frozen, locked)
//   readiness  = can it accept work (ready, not_ready)
//   health     = sustained quality (unknown, healthy, degraded, unhealthy)
//   recovery   = corrective action in progress (none, retrying, etc.)
// ---------------------------------------------------------------------------

struct EntityState {
    LifecycleState lifecycle;
    WorkState work;
    ControlState control;
    ReadinessState readiness;
    HealthState health;
    RecoveryState recovery;
    
    std::chrono::system_clock::time_point timestamp;
    
    // Optional attributes
    std::optional<std::string> instance_id;     // for runtime instances
    std::optional<std::string> definition_id;   // for specifications vs instances
    
    // Readiness predicate: can accept/perform work?
    bool ready() const {
        return (readiness == ReadinessState::kReady) && 
               (health == HealthState::kHealthy);
    }
    
    // Active predicate: is it currently executing?
    bool active() const {
        return lifecycle == LifecycleState::kActive;
    }
};

// ---------------------------------------------------------------------------
// InstanceIdentity
// Identity information for a runtime instance (vs its specification).
// ---------------------------------------------------------------------------

struct InstanceIdentity {
    std::string id;              // unique runtime instance ID
    std::optional<std::string> origin_id;  // the definition/specification that created this
    
    std::chrono::system_clock::time_point created_at;
    
    std::optional<std::string> parent_instance_id;  // for hierarchical instances
};

// ---------------------------------------------------------------------------
// ExecutionId
// A family of IDs to correlate execution events across components.
// ---------------------------------------------------------------------------

struct ExecutionIds {
    std::string request_id;      // original request that started this chain
    std::string execution_id;    // this specific execution instance
    std::optional<std::string> parent_execution_id;  // for nested/child executions
    
    static ExecutionIds make_root(std::string request_id, std::string exec_id = "") {
        if (exec_id.empty()) exec_id = request_id;
        return ExecutionIds{std::move(request_id), std::move(exec_id), std::nullopt};
    }
    
    static ExecutionIds make_child(const ExecutionIds& parent, std::string child_exec_id) {
        return ExecutionIds{parent.request_id, std::move(child_exec_id), parent.execution_id};
    }
};

// ---------------------------------------------------------------------------
// Schedule
// A specification for when activation should occur.
// Distinct from Scheduler (the mechanism that evaluates/manages schedules).
//
// Schedules may produce activation based on:
//   - absolute time
//   - interval/duration
//   - recurrence pattern
//   - calendar expression
// ---------------------------------------------------------------------------

enum class ScheduleKind {
    kOnce,          // single execution at absolute time
    kInterval,      // recurring at fixed intervals
    kCron,          // cron-style schedule (calendar-based)
};

inline std::string_view to_string(ScheduleKind k) {
    switch (k) {
        case ScheduleKind::kOnce:   return "once";
        case ScheduleKind::kInterval: return "interval";
        case ScheduleKind::kCron:   return "cron";
    }
    return "unknown";
}

struct Schedule {
    std::string id;
    
    ScheduleKind kind;
    
    // Timing specification
    std::optional<std::chrono::system_clock::time_point> absolute_time;  // for kOnce
    std::optional<std::chrono::milliseconds> interval;                   // for kInterval
    
    // Recurrence (for kCron and kInterval)
    std::optional<int32_t> max_executions;  // -1 = unlimited
    std::optional<std::string> cron_expr;   // standard cron format
    
    std::chrono::system_clock::time_point created_at;
    
    // Activation target
    std::string target_kind;     // "task", "workflow", etc.
    std::string target_id;       // identifier of what to activate
    
    bool enabled = true;
};

// ---------------------------------------------------------------------------
// Timeout policy
// Controls how timeouts are handled for operations/activations.
// ---------------------------------------------------------------------------

struct TimeoutPolicy {
    std::chrono::milliseconds default_timeout;
    
    std::optional<std::chrono::milliseconds> operation_timeout;
    std::optional<std::chrono::milliseconds> verification_timeout;
    
    // On timeout behavior
    bool cancel_on_timeout = true;       // whether to cancel or continue
    bool retry_on_timeout = false;       // whether to attempt retry
    
    bool has_operation_timeout() const {
        return operation_timeout.has_value();
    }
    
    bool has_verification_timeout() const {
        return verification_timeout.has_value();
    }
};

// ---------------------------------------------------------------------------
// RetryPolicy
// Controls how failures trigger retries.
// ---------------------------------------------------------------------------

struct RetryPolicy {
    int max_attempts = 1;           // total attempts including initial
    
    std::chrono::milliseconds initial_delay;
    std::optional<std::chrono::milliseconds> max_delay;
    
    bool exponential_backoff = false;
    double backoff_multiplier = 2.0;
    
    // Which errors trigger retry
    std::vector<std::string> retryable_error_codes;  // empty = retry all
    
    bool should_retry(int attempt_num, const core::Error* error) const {
        if (attempt_num >= max_attempts) return false;
        
        // Check error filter if specified
        if (!retryable_error_codes.empty() && error) {
            auto it = std::find(retryable_error_codes.begin(), 
                               retryable_error_codes.end(),
                               error->code);
            if (it == retryable_error_codes.end()) {
                return false;
            }
        }
        
        return true;
    }
    
    std::chrono::milliseconds compute_delay(int attempt_num) const {
        if (!exponential_backoff || attempt_num <= 0) {
            return initial_delay;
        }
        
        auto delay = initial_delay * static_cast<int64_t>(
            std::pow(backoff_multiplier, attempt_num - 1));
        
        if (max_delay.has_value() && delay > max_delay.value()) {
            delay = max_delay.value();
        }
        
        return std::chrono::milliseconds(delay);
    }
};

// ---------------------------------------------------------------------------
// ExecutionParameters
// Parameters that control how an execution runs.
// ---------------------------------------------------------------------------

struct ExecutionParameters {
    TimeoutPolicy timeout;
    RetryPolicy retry;
    
    // Resource constraints (future: CPU/GPU/memory limits)
    bool cpu_only = false;  // future: restrict to CPU-only execution
    
    // Concurrency
    bool allow_concurrent = true;  // allow multiple instances of same task
};

// ---------------------------------------------------------------------------
// ResultWithMetadata
// A Result that includes additional runtime metadata.
// ---------------------------------------------------------------------------

template <typename T>
struct ResultWithMetadata : core::Result<T> {
    ExecutionIds exec_ids;
    
    std::chrono::system_clock::time_point started_at;
    std::chrono::system_clock::time_point completed_at;
    
    std::optional<std::string> executor_id;  // which component executed it
    
    // Timing information
    std::chrono::milliseconds execution_duration{0};
    std::chrono::milliseconds verification_duration{0};
};

// ---------------------------------------------------------------------------
// WorkPriority
// Priority levels for work scheduling/queuing.
// ---------------------------------------------------------------------------

enum class WorkPriority {
    kCritical,   // immediate, bypass queues where possible
    kHigh,       // above normal priority
    kNormal,     // standard priority
    kLow,        // below normal priority
    kBackground, // lowest priority, runs when idle
};

inline std::string_view to_string(WorkPriority p) {
    switch (p) {
        case WorkPriority::kCritical:   return "critical";
        case WorkPriority::kHigh:       return "high";
        case WorkPriority::kNormal:     return "normal";
        case WorkPriority::kLow:        return "low";
        case WorkPriority::kBackground: return "background";
    }
    return "unknown";
}

// ---------------------------------------------------------------------------
// RequestStatus
// Lifecycle stages of a Request through the system.
// ---------------------------------------------------------------------------

enum class RequestStatus {
    kReceived,       // request accepted for processing
    kValidating,     // validation in progress
    kAuthorized,     // authorization passed
    kDispatched,     // dispatched to executor
    kExecuting,      // execution in progress
    kVerifying,      // verification in progress
    kCompleted,      // execution finished (may be unverified)
    kVerified,       // verification completed successfully
    kCancelled,      // explicitly cancelled
    kTimedOut,       // operation timed out
    kFailed,         // failed to complete
};

inline std::string_view to_string(RequestStatus s) {
    switch (s) {
        case RequestStatus::kReceived:   return "received";
        case RequestStatus::kValidating: return "validating";
        case RequestStatus::kAuthorized: return "authorized";
        case RequestStatus::kDispatched: return "dispatched";
        case RequestStatus::kExecuting:  return "executing";
        case RequestStatus::kVerifying:  return "verifying";
        case RequestStatus::kCompleted:  return "completed";
        case RequestStatus::kVerified:   return "verified";
        case RequestStatus::kCancelled:  return "cancelled";
        case RequestStatus::kTimedOut:   return "timed_out";
        case RequestStatus::kFailed:     return "failed";
    }
    return "unknown";
}

}  // namespace rebuntu::runtime

// ---------------------------------------------------------------------------
// Compatibility with core contracts
// ---------------------------------------------------------------------------

namespace rebuntu::core {

// Extension of SemanticStatus for runtime operations
inline constexpr SemanticStatus kExecutionSuccess = SemanticStatus::kSuccess;
inline constexpr SemanticStatus kExecutionCompleted = SemanticStatus::kCompleted;

}  // namespace rebuntu::core