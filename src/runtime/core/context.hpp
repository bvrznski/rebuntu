// rebuntu::runtime::core::context — Execution Context (Phase 4.0)
//
// RuntimeContext provides the execution environment for a single attempt:
// - Unique identity tracking
// - Cancellation propagation token
// - Timeout and retry configuration
// - Environment variables
// - Working directory
// - Evidence registry linkage

#pragma once

#include <runtime/core/contracts.hpp>
#include <runtime/cancellation/token.hpp>
#include <runtime/results.hpp>
#include <chrono>
#include <map>
#include <optional>
#include <memory>
#include <string>

namespace rebuntu::runtime {

// Forward declaration
class EvidenceRegistry;

struct RuntimeContext {
    // Identity - unique for each execution attempt
    work::ExecutionId execution_id;
    
    // Optional caller identity (for authorization/audit)
    std::optional<std::string> caller_id;
    
    // When this context was created (system clock for timestamps)
    std::chrono::system_clock::time_point created_at;
    
    // Timeout configuration - when to abort if not finished
    TimeoutPolicy timeout_policy;
    
    // Retry behavior - how many times to attempt before giving up
    RetryPolicy retry_policy;
    
    // Cancellation token for propagation through the stack
    CancellationToken cancellation_token;
    
    // Working directory for subprocess execution
    std::optional<std::string> working_directory;
    
    // Environment variables (inherit from parent if not set)
    std::map<std::string, std::string> environment;
    
    // Evidence registry - collects evidence during execution
    // Shared ownership allows multiple components to contribute
    std::shared_ptr<EvidenceRegistry> evidence_registry;
    
    // Priority for scheduling/queuing decisions
    WorkPriority priority = WorkPriority::kNormal;
    
    // Concurrency control - can multiple instances run simultaneously?
    bool allow_concurrent_execution = true;
    
    // Deadline derived from created_at + timeout_policy.default_timeout
    std::chrono::system_clock::time_point deadline() const {
        return created_at + timeout_policy.default_timeout;
    }
    
    // Is cancellation requested?
    bool is_cancelled() const {
        return cancellation_token.is_cancelled();
    }
    
    // Request cancellation (propagates to all registered callbacks)
    void request_cancel(std::optional<std::string> reason = std::nullopt) {
        cancellation_token.request_cancel(std::move(reason));
    }
};

namespace core {

// Factory function to create a fresh RuntimeContext
inline RuntimeContext make_context(
    work::ExecutionId exec_id,
    TimeoutPolicy timeout_policy = {},
    RetryPolicy retry_policy = {}) {
    
    RuntimeContext ctx;
    ctx.execution_id = std::move(exec_id);
    ctx.created_at = std::chrono::system_clock::now();
    ctx.timeout_policy = std::move(timeout_policy);
    ctx.retry_policy = std::move(retry_policy);
    
    // Create default evidence registry if none provided
    ctx.evidence_registry = std::make_shared<EvidenceRegistry>();
    
    return ctx;
}

// Factory function with caller ID (for audit/tracing)
inline RuntimeContext make_context_with_caller(
    work::ExecutionId exec_id,
    std::string caller_id,
    TimeoutPolicy timeout_policy = {},
    RetryPolicy retry_policy = {}) {
    
    auto ctx = make_context(std::move(exec_id), std::move(timeout_policy), 
                           std::move(retry_policy));
    ctx.caller_id = std::move(caller_id);
    return ctx;
}

// Create a child context (for nested/executed work)
inline RuntimeContext make_child_context(
    const RuntimeContext& parent,
    work::ExecutionId child_exec_id) {
    
    RuntimeContext child;
    child.execution_id = std::move(child_exec_id);
    child.created_at = std::chrono::system_clock::now();
    child.caller_id = parent.caller_id;  // Inherit caller
    child.timeout_policy = parent.timeout_policy;
    child.retry_policy = parent.retry_policy;
    child.cancellation_token = CancellationToken();  // New token for child
    
    // Share evidence registry (parent can aggregate)
    child.evidence_registry = parent.evidence_registry;
    
    child.working_directory = parent.working_directory;
    child.environment = parent.environment;  // Copy for modification
    child.priority = parent.priority;
    
    return child;
}

}  // namespace core
}  // namespace rebuntu::runtime