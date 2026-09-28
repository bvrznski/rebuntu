// rebuntu::runtime::reconciliation — Operation Record Types (Phase 6.40)
//
// This module provides durable operation record types for crash reconciliation.
// After a restart/crash, pending operations can be discovered and reconciled
// by combining durable records with fresh Phase-5 observations.
//
// Key principles:
//   * OperationRecord: Durable persistence of in-progress operations
//   * CrashRecoveryState: Tracks which operations were interrupted
//   * ReconciliationPlan: Describes how to reconcile each pending operation

#pragma once

#include <runtime/contracts.hpp>
#include <runtime/work.hpp>
#include <system/core/contracts.hpp>
#include <chrono>
#include <filesystem>
#include <optional>
#include <string>
#include <string_view>
#include <vector>

namespace rebuntu::runtime::reconciliation {

// ============================================================================
// OperationRecordStatus — Durable status of an operation record
//
// This tracks the lifecycle stage of an operation record itself,
// independent of the semantic outcome.
// ============================================================================
enum class OperationRecordStatus {
    kPending,      // Operation in progress, not yet completed
    kCompleted,    // Operation finished (success or failure)
    kCancelled,    // Operation was cancelled
    kReconciled,   // Reconciliation attempted (may still need action)
};

inline std::string_view to_string(OperationRecordStatus s) {
    switch (s) {
        case OperationRecordStatus::kPending: return "pending";
        case OperationRecordStatus::kCompleted: return "completed";
        case OperationRecordStatus::kCancelled: return "cancelled";
        case OperationRecordStatus::kReconciled: return "reconciled";
    }
    return "unknown";
}

// ============================================================================
// ExecutionState — Durable execution state for an operation
//
// This captures the execution progress at the time of interruption,
// enabling reconciliation to resume from the correct point.
// ============================================================================
enum class ExecutionState {
    kCreated,        // Operation created but not yet dispatched
    kDispatched,     // Dispatched to executor
    kExecuting,      // Currently executing (was interrupted here)
    kObserving,      // Post-execution observation phase
    kVerifying,      // Verification phase
    kCompleted,      // Full completion with verification
};

inline std::string_view to_string(ExecutionState s) {
    switch (s) {
        case ExecutionState::kCreated: return "created";
        case ExecutionState::kDispatched: return "dispatched";
        case ExecutionState::kExecuting: return "executing";
        case ExecutionState::kObserving: return "observing";
        case ExecutionState::kVerifying: return "verifying";
        case ExecutionState::kCompleted: return "completed";
    }
    return "unknown";
}

// ============================================================================
// OperationRecord — Durable record of an operation in progress
//
// This is persisted to disk so that after a crash/restart, pending
// operations can be discovered and reconciled without blindly replaying.
//
// Each record contains:
//   - Metadata: ID, timestamps, caller context
//   - Operation definition: what was requested
//   - Execution state: where it was when interrupted
//   - Partial evidence: observations made so far
//   - Recovery info: what's needed to continue/completed
// ============================================================================
struct OperationRecord {
    // Unique identifier for this operation record
    std::string record_id;
    
    // Original request information
    std::string original_request_id;  // Request that triggered this operation
    
    // Timestamps
    std::chrono::system_clock::time_point created_at;
    std::optional<std::chrono::system_clock::time_point> interrupted_at;  // When crash occurred
    std::optional<std::chrono::system_clock::time_point> reconciled_at;   // When reconciliation attempted
    
    // Operation information
    std::string operation_id;         // e.g., "filesystem.copy", "service.restart"
    std::string subject_type;         // What the operation acts upon
    std::optional<std::string> subject;  // Specific target if applicable
    
    // Execution state at interruption time
    ExecutionState execution_state = ExecutionState::kCreated;
    
    // Execution metadata
    std::optional<work::JobId> job_id;
    std::optional<work::ExecutionId> execution_id;
    std::optional<int32_t> pid;       // Process ID if running in subprocess
    
    // Partial execution state (for retry/recovery)
    int steps_completed = 0;          // Number of steps completed before interruption
    int total_steps = 0;              // Total steps in the plan
    
    // Evidence collected so far (bounded, no secrets)
    std::vector<core::Evidence> evidence;
    
    // Partial execution info if applicable
    std::optional<core::PartialExecutionInfo> partial_execution_info;
    
    // Operation record status
    OperationRecordStatus record_status = OperationRecordStatus::kPending;
    
    // Recovery information
    enum class RecoveryAction {
        kNone,              // No action needed (already completed)
        kRetry,             // Retry from the beginning
        kResume,            // Resume from execution_state
        kRollback,          // Rollback partial changes
        kVerifyOnly,        // Only verify postconditions, no execution
    } recovery_action = RecoveryAction::kNone;
    
    std::optional<std::string> recovery_description;  // Human-readable explanation
    
    // Helper predicates
    
    bool is_pending() const {
        return record_status == OperationRecordStatus::kPending ||
               record_status == OperationRecordStatus::kReconciled;
    }
    
    bool was_interrupted() const {
        return interrupted_at.has_value();
    }
    
    bool has_partial_execution() const {
        return partial_execution_info.has_value() || steps_completed > 0;
    }
};

// ============================================================================
// PendingOperationSummary — Brief summary of a pending operation
//
// Used for reporting and quick inspection without loading full records.
// ============================================================================
struct PendingOperationSummary {
    std::string record_id;
    std::chrono::system_clock::time_point created_at;
    std::optional<std::chrono::system_clock::time_point> interrupted_at;
    
    std::string operation_id;
    std::optional<std::string> subject;
    
    ExecutionState execution_state = ExecutionState::kCreated;
    int steps_completed = 0;
    int total_steps = 0;
};

// ============================================================================
// PendingOperationInfo — Information about a pending operation from record storage
//
// This is what the detector produces when scanning for pending operations.
// It's slightly different from OperationRecord (which is the durable record format).
// ============================================================================
struct PendingOperationInfo {
    std::string record_id;            // Unique identifier
    std::chrono::system_clock::time_point created_at;
    std::optional<std::chrono::system_clock::time_point> interrupted_at;
    std::filesystem::path record_path;  // Path to the record file on disk
};

// ============================================================================
// CrashRecoveryState — Overall state of crash recovery system
//
// This tracks the current phase of the recovery process and any pending actions.
// ============================================================================
enum class CrashRecoveryState {
    kUnknown,          // Recovery status not yet determined
    kNotApplicable,    // System didn't experience an unclean shutdown
    kPendingReview,    // Pending operations found, awaiting review
    kInProcess,        // Reconciliation is currently in progress
    kComplete,         // All pending operations have been reconciled
};

inline std::string_view to_string(CrashRecoveryState s) {
    switch (s) {
        case CrashRecoveryState::kUnknown: return "unknown";
        case CrashRecoveryState::kNotApplicable: return "not_applicable";
        case CrashRecoveryState::kPendingReview: return "pending_review";
        case CrashRecoveryState::kInProcess: return "in_process";
        case CrashRecoveryState::kComplete: return "complete";
    }
    return "unknown";
}

// ============================================================================
// ReconciliationResult — Result of attempting to reconcile an operation
//
// This provides detailed feedback on what reconciliation did and why.
// ============================================================================
struct ReconciliationResult {
    std::string record_id;
    
    // What action was taken
    enum class ActionTaken {
        kNone,              // No action needed
        kRetried,           // Operation was retried from beginning
        kResumed,           // Operation resumed from interruption point
        kRolledBack,        // Partial changes were rolled back
        kVerified,          // Only postconditions verified (no execution)
        kSkipped,           // Skipped due to policy or user decision
    } action_taken = ActionTaken::kNone;
    
    // Outcome of the reconciliation attempt
    core::SemanticStatus outcome_status = core::SemanticStatus::kUnknown;
    
    // Whether verification was performed and passed
    bool verified = false;
    
    // Evidence from the reconciliation process
    std::vector<core::Evidence> evidence;
    
    // Error information if reconciliation failed
    std::optional<core::Error> error;
};

// ============================================================================
// ReconciliationReport — Summary of all reconciliation actions taken
//
// This is produced after a complete crash reconciliation pass.
// ============================================================================
struct ReconciliationReport {
    CrashRecoveryState recovery_state = CrashRecoveryState::kUnknown;
    
    int total_pending_found = 0;        // Total pending operations discovered
    int reconciled_successfully = 0;    // Operations reconciled with success outcome
    int reconciled_with_errors = 0;     // Operations reconciled but with errors
    int skipped = 0;                    // Operations that were skipped
    
    std::chrono::milliseconds total_duration_ms{0};
    
    std::vector<ReconciliationResult> results;
};

// ============================================================================
// RecoveryBounds — Resource limits for recovery operations
//
// Prevents recovery storms from overwhelming the system.
// ============================================================================
struct RecoveryBounds {
    size_t max_pending_operations = 100;    // Max pending ops to process
    size_t max_evidence_per_operation = 50; // Evidence limit per operation
    std::chrono::milliseconds timeout_ms{30000};  // Total recovery timeout
};

// ============================================================================
// RecoveryDecision — What action to take for a pending operation
//
// This is the output of the reconciliation analysis phase.
// ============================================================================
struct RecoveryDecision {
    enum class DecisionType {
        kNoAction,          // Operation already complete or irrelevant
        kRetryFromStart,    // Start over from step 1
        kResumeExecution,   // Continue from where it was interrupted
        kRollbackFirst,     // Must rollback before resuming
        kUserReview,        // Requires manual review (security-sensitive)
    };
    
    DecisionType decision = DecisionType::kNoAction;
    std::string reason;  // Human-readable explanation for the decision
    
    bool requires_action() const {
        return decision != DecisionType::kNoAction;
    }
};

}  // namespace rebuntu::runtime::reconciliation