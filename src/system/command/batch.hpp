// rebuntu::command::batch — Typed Batch Command Boundary (Phase 6.42)
//
// This module defines the canonical typed batch command representation:
//
//   * BatchIntent: Typed composition of multiple command intents
//   * BatchMode: Explicit specification of execution semantics
//   * BatchResult: Individual and aggregate results for batch operations
//
// Design Philosophy:
//   * Batches are explicit typed compositions, NOT implied behavior
//   * NO implicit ACID or all-or-nothing guarantees unless specified
//   * Each command in a batch has independent outcome tracking
//   * Batch-level semantics are declared, not inferred
//
// Key Principles:
//   * BatchIntent wraps multiple CommandIntent objects
//   * BatchMode specifies execution strategy (sequential/parallel, strict/best-effort)
//   * Individual results are tracked per-command for transparency
//   * Aggregate status reflects actual outcomes, NOT assumed behavior

#pragma once

#include "model.hpp"
#include <system/core/contracts.hpp>
#include <string>
#include <vector>
#include <chrono>

namespace rebuntu::command {

// ============================================================================
// BatchMode — Execution semantics for batch operations
//
// Distinct from atomicity: these control EXECUTION strategy, not guarantees.
// ============================================================================

enum class BatchMode {
    kSequentialStrict,     // Execute commands one-by-one, stop on first failure
    kSequentialBestEffort, // Execute commands one-by-one, continue through failures
    kParallelIndependent,  // Execute all in parallel, collect all results independently
};

inline std::string to_string(BatchMode m) {
    switch (m) {
        case BatchMode::kSequentialStrict:     return "sequential_strict";
        case BatchMode::kSequentialBestEffort: return "sequential_best_effort";
        case BatchMode::kParallelIndependent:  return "parallel_independent";
    }
    return "unknown";
}

// ============================================================================
// BatchResultStatus — Aggregate status of a batch execution
//
// These are OBSERVATIONAL states, NOT assumed outcomes:
//   * kAllSuccess = Every command succeeded (no failures observed)
//   * kPartialSuccess = Some commands succeeded, some failed
//   * kAllFailed = No commands succeeded (all failed or unknown)
//   * kUnknown = Could not determine individual outcomes
// ============================================================================

enum class BatchResultStatus {
    kUnknown,       // Status not yet determined (not started) or indeterminate
    kAllSuccess,    // All commands in batch completed successfully
    kPartialSuccess,// At least one succeeded AND at least one failed/unknown
    kAllFailed,     // No commands succeeded (all failed or unknown)
};

inline std::string to_string(BatchResultStatus s) {
    switch (s) {
        case BatchResultStatus::kUnknown:    return "unknown";
        case BatchResultStatus::kAllSuccess: return "all_success";
        case BatchResultStatus::kPartialSuccess:return "partial_success";
        case BatchResultStatus::kAllFailed:  return "all_failed";
    }
    return "unknown";
}

// ============================================================================
// CommandExecutionRecord — Result of executing a single command in a batch
//
// This is the authoritative source for per-command outcome.
// ============================================================================

struct CommandExecutionRecord {
    std::string id;                 // Original intent ID (for tracking)
    size_t index;                   // Position in batch (0-based)
    
    core::SemanticStatus status{core::SemanticStatus::kUnknown};
    bool changed{false};            // Did this command change state?
    bool verified{false};           // Was postcondition verification successful?
    
    std::vector<core::Evidence> evidence;
    std::optional<std::string> output_value;
    std::chrono::milliseconds elapsed_ms{0};
    
    // For failures
    std::optional<core::Error> error;
};

inline bool is_success(const CommandExecutionRecord& r) {
    return r.status == core::SemanticStatus::kSuccess && r.verified;
}

// ============================================================================
// BatchResult — Result of executing a batch command
//
// This contains:
//   * Aggregate status (what actually happened)
//   * Individual per-command results (for transparency/debugging)
//   * Timing information for the entire batch
// ============================================================================

struct BatchResult {
    BatchMode mode{BatchMode::kSequentialStrict};
    
    // Aggregate outcome
    BatchResultStatus aggregate_status{BatchResultStatus::kUnknown};
    
    // Individual command outcomes
    std::vector<CommandExecutionRecord> records;
    
    // Timing information for the entire batch
    std::chrono::milliseconds total_duration_ms{0};
    
    // For verification tracking (if applicable)
    bool all_verified{false};
    
    // Factory methods for common cases
    
    static BatchResult success(BatchMode m, std::vector<CommandExecutionRecord> recs) {
        BatchResult r;
        r.mode = m;
        r.aggregate_status = BatchResultStatus::kAllSuccess;
        r.records = std::move(recs);
        r.all_verified = true;
        for (const auto& rec : r.records) {
            r.total_duration_ms += rec.elapsed_ms;
            if (!rec.verified) r.all_verified = false;
        }
        return r;
    }
    
    static BatchResult partial_success(BatchMode m, std::vector<CommandExecutionRecord> recs) {
        BatchResult r;
        r.mode = m;
        r.aggregate_status = BatchResultStatus::kPartialSuccess;
        r.records = std::move(recs);
        
        // Calculate aggregate verification status
        bool any_verified = false;
        for (const auto& rec : r.records) {
            r.total_duration_ms += rec.elapsed_ms;
            if (rec.verified) any_verified = true;
        }
        r.all_verified = any_verified;  // At least one verified is "partially verified"
        
        return r;
    }
    
    static BatchResult all_failed(BatchMode m, std::vector<CommandExecutionRecord> recs) {
        BatchResult r;
        r.mode = m;
        r.aggregate_status = BatchResultStatus::kAllFailed;
        r.records = std::move(recs);
        
        for (const auto& rec : r.records) {
            r.total_duration_ms += rec.elapsed_ms;
        }
        return r;
    }
    
    static BatchResult unknown(BatchMode m) {
        BatchResult r;
        r.mode = m;
        r.aggregate_status = BatchResultStatus::kUnknown;
        // records is empty - no evidence available
        return r;
    }
    
    bool is_success() const {
        return aggregate_status == BatchResultStatus::kAllSuccess && all_verified;
    }
    
    bool has_failures() const {
        for (const auto& rec : records) {
            if (!rebuntu::command::is_success(rec)) return true;
        }
        return false;
    }
};

// ============================================================================
// BatchIntent — Typed composition of multiple command intents
//
// This explicitly models a batch as a collection of commands with declared
// execution semantics. The batch does NOT imply atomicity unless specified.
// ============================================================================

struct BatchIntent {
    std::string id;                              // Unique batch ID (UUID-like)
    
    // Execution strategy
    BatchMode mode{BatchMode::kSequentialStrict};  // How to execute the commands
    
    // Commands in this batch (NOT a set - order matters for sequential modes)
    std::vector<CommandIntent> intents;
    
    // Optional batch-level execution policy
    ExecutionPolicy execution_policy{};
    
    // Source information (for debugging/explain)
    std::optional<std::string> source_context;
    std::optional<int> source_line;
    
    // Factory method for creating a batch from multiple intents
    static BatchIntent make(BatchMode m, std::vector<CommandIntent> ints) {
        BatchIntent b;
        b.id = "batch-" + std::to_string(std::chrono::system_clock::now().time_since_epoch().count());
        b.mode = m;
        b.intents = std::move(ints);
        
        // Inherit execution policy from first intent if not explicitly set
        if (!b.intents.empty()) {
            b.execution_policy = b.intents[0].execution_policy;
        }
        
        return b;
    }
    
    // Add another intent to the batch
    void add_intent(CommandIntent intent) {
        intents.push_back(std::move(intent));
    }
};

// ============================================================================
// BatchBuilder — Fluent builder for creating batch intents
// ============================================================================

class BatchBuilder {
public:
    explicit BatchBuilder(BatchMode mode = BatchMode::kSequentialStrict)
        : batch_(make_default_batch(mode)) {}
    
    // Add a single intent to the batch
    BatchBuilder& add_intent(CommandIntent intent) {
        batch_.intents.push_back(std::move(intent));
        return *this;
    }
    
    // Add multiple intents at once
    BatchBuilder& add_intents(std::vector<CommandIntent> intents) {
        for (auto& i : intents) {
            batch_.intents.push_back(std::move(i));
        }
        return *this;
    }
    
    // Set batch-level execution policy
    BatchBuilder& with_execution_policy(ExecutionPolicy policy) {
        batch_.execution_policy = std::move(policy);
        return *this;
    }
    
    // Set source context for debugging
    BatchBuilder& with_source_context(std::string ctx) {
        batch_.source_context = std::move(ctx);
        return *this;
    }
    
    // Build the final batch intent
    BatchIntent build() {
        BatchIntent result = std::move(batch_);
        // Reset to default for next use
        batch_ = make_default_batch(batch_.mode);
        return result;
    }

private:
    static BatchIntent make_default_batch(BatchMode mode) {
        BatchIntent b;
        b.id = "batch-" + std::to_string(std::chrono::system_clock::now().time_since_epoch().count());
        b.mode = mode;
        return b;
    }
    
    BatchIntent batch_;
};

// ============================================================================
// Error codes for batch operations
// ============================================================================

namespace error {
    constexpr const char kBatchEmpty[] = "E_BATCH_EMPTY";           // No commands in batch
    constexpr const char kBatchPartialSuccess[] = "E_BATCH_PARTIAL"; // Some commands failed
    constexpr const char kBatchAllFailed[] = "E_BATCH_ALL_FAILED";   // All commands failed
    constexpr const char kBatchTimeout[] = "E_BATCH_TIMEOUT";        // Batch execution timed out
    constexpr const char kBatchCancelled[] = "E_BATCH_CANCELLED";    // Batch was cancelled
}

}  // namespace rebuntu::command