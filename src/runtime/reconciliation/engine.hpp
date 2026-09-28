// rebuntu::runtime::reconciliation::engine — Crash Reconciliation Engine (Phase 6.40)
//
// This module provides the reconciliation engine that:
//   1. Scans durable operation records for pending operations
//   2. Queries fresh Phase-5 observations about current system state
//   3. Determines recovery actions (retry/resume/rollback/verify-only)
//   4. Executes recovery through canonical operation machinery
//   5. Updates record status based on reconciliation outcome
//
// CRITICAL: Never blindly replay operations after restart.

#pragma once

#include <runtime/reconciliation/types.hpp>
#include <system/core/contracts.hpp>

// Forward declaration of PendingOperationInfo (defined in detector.hpp)
namespace rebuntu::runtime::reconciliation {
    struct PendingOperationInfo;
}

#include <chrono>
#include <filesystem>
#include <functional>
#include <optional>
#include <string>
#include <vector>
#include <memory>

namespace rebuntu::runtime::reconciliation {

// ============================================================================
// Reconciler — The reconciliation engine
//
// Integrates durable operation records with fresh Phase-5 observations to
// safely determine and execute recovery actions for interrupted operations.
// ============================================================================
class Reconciler {
public:
    // Configuration
    RecoveryBounds bounds;
    
    // Callback for executing a partial retry of an operation
    using RetryPartialFn = std::function<
        core::Outcome(const OperationRecord& record, int start_from_step)>;
    
    // Callback for executing full retry from step 0
    using RetryFullFn = std::function<core::Outcome(const OperationRecord& record)>;
    
    // Callback for rollback execution
    using RollbackFn = std::function<
        core::Outcome(const OperationRecord& record, const core::PartialExecutionInfo&)>;
    
    Reconciler(RecoveryBounds bounds = {})
        : bounds(bounds) {}
    
    // Register callback functions
    void set_retry_partial(RetryPartialFn fn);
    void set_retry_full(RetryFullFn fn);
    void set_rollback(RollbackFn fn);
    
    // Analyze an operation record and determine recovery action
    RecoveryDecision analyze(const OperationRecord& record,
                             const std::vector<core::Evidence>& fresh_evidence) const;
    
    // Execute the recovery for an operation based on its analysis
    ReconciliationResult execute_recovery(
        const OperationRecord& record,
        RecoveryDecision decision);
    
    // Process all pending operations with fresh observations
    ReconciliationReport process_pending(
        const std::vector<PendingOperationInfo>& pending_records,
        const std::function<std::vector<core::Evidence>()>& fresh_observations_fn);

private:
    RetryPartialFn retry_partial_fn_;
    RetryFullFn retry_full_fn_;
    RollbackFn rollback_fn_;
    
    // Helper: Determine recovery action based on state and evidence
    RecoveryDecision determine_recovery_action(
        const OperationRecord& record,
        const std::vector<core::Evidence>& fresh_evidence) const;
};

// ============================================================================
// ReconciliationBuilder — Fluent builder for reconciler configuration
// ============================================================================
class ReconciliationBuilder {
public:
    ReconciliationBuilder();
    
    ReconciliationBuilder& set_bounds(RecoveryBounds bounds);
    ReconciliationBuilder& with_retry_partial(Reconciler::RetryPartialFn fn);
    ReconciliationBuilder& with_retry_full(Reconciler::RetryFullFn fn);
    ReconciliationBuilder& with_rollback(Reconciler::RollbackFn fn);
    
    std::unique_ptr<Reconciler> build();

private:
    RecoveryBounds bounds_;
    Reconciler::RetryPartialFn retry_partial_fn_;
    Reconciler::RetryFullFn retry_full_fn_;
    Reconciler::RollbackFn rollback_fn_;
};

}  // namespace rebuntu::runtime::reconciliation