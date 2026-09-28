// rebuntu::command::parallel — Typed Parallel Composition (Phase 6.44)
//
// This module provides parallel execution for proven-independent operations
// with bounded concurrency:
//
//   * ParallelIntent: Composed intent with multiple independent operations
//   * ParallelResult: Per-operation results with aggregate status
//   * Bounded concurrency: limited worker pool to prevent resource storms
//   * Partial failure handling: track individual failures while continuing others
//
// Design Philosophy:
//   * Parallel composition is ONLY for proven-independent operations
//   * Each operation executes in its own context (no shared mutable state)
//   * Results are preserved per-operation for debugging/auditing
//   * Aggregate status reflects actual outcomes, not assumptions
//   * Bounded concurrency prevents resource exhaustion
//
// Key Principles:
//   * ParallelIntent wraps multiple CommandIntent objects for concurrent execution
//   * Each operation goes through full validation → authorization → execution → verify
//   * Independent operations don't depend on each other's results
//   * Partial failures are tracked and reported separately
//   * Timeout/cancellation applies uniformly to all parallel operations

#pragma once

#include "batch.hpp"
#include "model.hpp"
#include <system/core/contracts.hpp>
#include <chrono>
#include <optional>
#include <string>
#include <vector>

namespace rebuntu::command {

// ============================================================================
// ParallelResultStatus — Aggregate status of a parallel execution
//
// These are OBSERVATIONAL states:
//   * kAllSuccess = Every operation succeeded
//   * kPartialSuccess = Some operations succeeded, some failed
//   * kAllFailed = No operations succeeded (all failed or unknown)
//   * kUnknown = Could not determine individual outcomes
// ============================================================================

enum class ParallelResultStatus {
    kUnknown,       // Status not yet determined or indeterminate
    kAllSuccess,    // All operations completed successfully
    kPartialSuccess,// At least one succeeded AND at least one failed/unknown
    kAllFailed,     // No operations succeeded (all failed or unknown)
};

inline std::string to_string(ParallelResultStatus s) {
    switch (s) {
        case ParallelResultStatus::kUnknown:    return "unknown";
        case ParallelResultStatus::kAllSuccess: return "all_success";
        case ParallelResultStatus::kPartialSuccess: return "partial_success";
        case ParallelResultStatus::kAllFailed:  return "all_failed";
    }
    return "unknown";
}

// ============================================================================
// ParallelOperationResult — Result of executing a single operation in parallel
//
// This is the authoritative source for per-operation outcome.
// ============================================================================

struct ParallelOperationResult {
    size_t index;                    // Position in parallel group (0-based)
    std::string operation_id;        // Original intent ID
    
    core::SemanticStatus status{core::SemanticStatus::kUnknown};
    bool changed{false};             // Did this operation change state?
    bool verified{false};            // Was postcondition verification successful?
    
    std::vector<core::Evidence> evidence;
    std::optional<std::string> output_value;
    std::chrono::milliseconds elapsed_ms{0};
    
    // For failures
    std::optional<core::Error> error;
};

inline bool is_success(const ParallelOperationResult& r) {
    return r.status == core::SemanticStatus::kSuccess && r.verified;
}

// ============================================================================
// ParallelResult — Result of executing a parallel composition
//
// This contains:
//   * Aggregate status (what actually happened)
//   * Individual per-operation results (for transparency/debugging)
//   * Timing information for the entire parallel execution
// ============================================================================

struct ParallelResult {
    // Execution strategy (from intent)
    BatchMode mode{BatchMode::kParallelIndependent};
    
    // Aggregate outcome
    ParallelResultStatus aggregate_status{ParallelResultStatus::kUnknown};
    
    // Individual operation outcomes
    std::vector<ParallelOperationResult> operations;
    
    // Timing information for the entire parallel execution
    std::chrono::milliseconds total_duration_ms{0};
    
    // Maximum concurrency used (actual threads/worker count)
    size_t actual_concurrency{1};
    
    // For verification tracking
    bool all_verified{false};
    
    // Factory methods for common cases
    
    static ParallelResult success(std::vector<ParallelOperationResult> results, 
                                   size_t concurrency = 1) {
        ParallelResult r;
        r.mode = BatchMode::kParallelIndependent;
        r.aggregate_status = ParallelResultStatus::kAllSuccess;
        r.operations = std::move(results);
        r.actual_concurrency = concurrency;
        r.all_verified = true;
        
        for (const auto& op : r.operations) {
            r.total_duration_ms += op.elapsed_ms;
            if (!op.verified) r.all_verified = false;
        }
        // For parallel execution, use the max duration as total
        if (!r.operations.empty()) {
            std::chrono::milliseconds max_duration{0};
            for (const auto& op : r.operations) {
                if (op.elapsed_ms > max_duration) {
                    max_duration = op.elapsed_ms;
                }
            }
            r.total_duration_ms = max_duration;
        }
        return r;
    }
    
    static ParallelResult partial_success(std::vector<ParallelOperationResult> results,
                                           size_t concurrency = 1) {
        ParallelResult r;
        r.mode = BatchMode::kParallelIndependent;
        r.aggregate_status = ParallelResultStatus::kPartialSuccess;
        r.operations = std::move(results);
        r.actual_concurrency = concurrency;
        
        bool any_verified = false;
        for (const auto& op : r.operations) {
            r.total_duration_ms += op.elapsed_ms;
            if (op.verified) any_verified = true;
        }
        // Use max duration for parallel
        if (!r.operations.empty()) {
            std::chrono::milliseconds max_duration{0};
            for (const auto& op : r.operations) {
                if (op.elapsed_ms > max_duration) {
                    max_duration = op.elapsed_ms;
                }
            }
            r.total_duration_ms = max_duration;
        }
        r.all_verified = any_verified;  // At least one verified
        
        return r;
    }
    
    static ParallelResult all_failed(std::vector<ParallelOperationResult> results,
                                      size_t concurrency = 1) {
        ParallelResult r;
        r.mode = BatchMode::kParallelIndependent;
        r.aggregate_status = ParallelResultStatus::kAllFailed;
        r.operations = std::move(results);
        r.actual_concurrency = concurrency;
        
        for (const auto& op : r.operations) {
            r.total_duration_ms += op.elapsed_ms;
        }
        // Use max duration for parallel
        if (!r.operations.empty()) {
            std::chrono::milliseconds max_duration{0};
            for (const auto& op : r.operations) {
                if (op.elapsed_ms > max_duration) {
                    max_duration = op.elapsed_ms;
                }
            }
            r.total_duration_ms = max_duration;
        }
        
        return r;
    }
    
    static ParallelResult unknown() {
        ParallelResult r;
        r.mode = BatchMode::kParallelIndependent;
        r.aggregate_status = ParallelResultStatus::kUnknown;
        // operations is empty - no evidence available
        return r;
    }
    
    bool is_success() const {
        return aggregate_status == ParallelResultStatus::kAllSuccess && all_verified;
    }
    
    bool has_failures() const {
        for (const auto& op : operations) {
            if (!rebuntu::command::is_success(op)) return true;
        }
        return false;
    }
};

// ============================================================================
// ParallelIntent — Typed composition of multiple independent command intents
//
// This explicitly models a parallel execution of commands where:
//   * Each operation is independent (no dependencies on other operations)
//   * All operations execute concurrently within bounded concurrency limits
//   * Each operation has independent validation/authorization/verification
//   * Results are tracked individually for transparency/debugging
// ============================================================================

struct ParallelIntent {
    std::string id;                              // Unique parallel group ID
    
    // Execution policy (applies to all operations)
    ExecutionPolicy execution_policy{};
    
    // Commands in this parallel group (ORDERED - though execution is concurrent)
    std::vector<CommandIntent> intents;
    
    // Maximum concurrency limit (number of simultaneous operations)
    // If 0, use system hardware_concurrency
    size_t max_concurrency{0};
    
    // Source information (for debugging/explain)
    std::optional<std::string> source_context;
    std::optional<int> source_line;
    
    // Factory method for creating a parallel group from multiple intents
    static ParallelIntent make(std::vector<CommandIntent> ints,
                               size_t max_concurrency = 0) {
        ParallelIntent p;
        p.id = "parallel-" + std::to_string(std::chrono::system_clock::now().time_since_epoch().count());
        p.intents = std::move(ints);
        p.max_concurrency = max_concurrency;
        
        // Inherit execution policy from first intent if not explicitly set
        if (!ints.empty()) {
            p.execution_policy = ints[0].execution_policy;
        }
        
        return p;
    }
    
    // Add another intent to the parallel group
    void add_intent(CommandIntent intent) {
        intents.push_back(std::move(intent));
    }
};

// ============================================================================
// ParallelBuilder — Fluent builder for creating parallel intent groups
// ============================================================================

class ParallelBuilder {
public:
    explicit ParallelBuilder(size_t max_concurrency = 0)
        : parallel_(make_default_parallel(max_concurrency)) {}
    
    // Add a single intent to the parallel group
    ParallelBuilder& add_intent(CommandIntent intent) {
        parallel_.intents.push_back(std::move(intent));
        return *this;
    }
    
    // Add multiple intents at once
    ParallelBuilder& add_intents(std::vector<CommandIntent> intents) {
        for (auto& i : intents) {
            parallel_.intents.push_back(std::move(i));
        }
        return *this;
    }
    
    // Set maximum concurrency limit
    ParallelBuilder& with_max_concurrency(size_t limit) {
        parallel_.max_concurrency = limit;
        return *this;
    }
    
    // Set execution policy (applies to all operations)
    ParallelBuilder& with_execution_policy(ExecutionPolicy policy) {
        parallel_.execution_policy = std::move(policy);
        return *this;
    }
    
    // Set source context for debugging
    ParallelBuilder& with_source_context(std::string ctx) {
        parallel_.source_context = std::move(ctx);
        return *this;
    }
    
    // Build the final parallel intent group
    ParallelIntent build() {
        ParallelIntent result = std::move(parallel_);
        // Reset to default for next use
        parallel_ = make_default_parallel(parallel_.max_concurrency);
        return result;
    }

private:
    static ParallelIntent make_default_parallel(size_t max_concurrency) {
        ParallelIntent p;
        p.id = "parallel-" + std::to_string(std::chrono::system_clock::now().time_since_epoch().count());
        p.max_concurrency = max_concurrency;
        return p;
    }
    
    ParallelIntent parallel_;
};

// ============================================================================
// Error codes for parallel composition operations
// ============================================================================

namespace error {
    constexpr const char kParallelEmpty[] = "E_PARALLEL_EMPTY";           // No commands in parallel group
    constexpr const char kParallelPartialSuccess[] = "E_PARALLEL_PARTIAL"; // Some operations failed
    constexpr const char kParallelAllFailed[] = "E_PARALLEL_ALL_FAILED";   // All operations failed
    constexpr const char kParallelTimeout[] = "E_PARALLEL_TIMEOUT";        // Execution timed out
    constexpr const char kParallelCancelled[] = "E_PARALLEL_CANCELLED";    // Execution was cancelled
}

}  // namespace rebuntu::command