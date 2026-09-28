// rebuntu::command::sequential — Typed Sequential Composition (Phase 6.43)
//
// This module provides minimal typed sequential composition where real callers
// require it:
//
//   * SequentialIntent: Composed intent with ordered steps
//   * SequentialResult: Per-step results with aggregate status
//   * Execution semantics: validate → authorize → execute → verify per step
//
// Design Philosophy:
//   * Sequential composition maintains validation/authorization/verification
//     semantics at each step
//   * Failure handling is explicit (strict vs best-effort)
//   * Each step's outcome is tracked independently
//   * Aggregate status reflects actual outcomes, not assumptions
//
// Key Principles:
//   * SequentialIntent wraps multiple CommandIntent objects with ordering
//   * Each step goes through the full intent → plan → execute → verify cycle
//   * Result tracking preserves per-step evidence for debugging/auditing
//   * No implicit ACID guarantees unless explicitly specified

#pragma once

#include "batch.hpp"
#include <chrono>
#include <optional>
#include <string>
#include <vector>

namespace rebuntu::command {

// ============================================================================
// SequentialMode — Execution semantics for sequential composition
//
// These control EXECUTION strategy, not atomicity/guarantees.
// ============================================================================

enum class SequentialMode {
    kStrict,     // Stop on first failure/verification failure
    kBestEffort, // Continue through failures, track per-step outcomes
};

inline std::string to_string(SequentialMode m) {
    switch (m) {
        case SequentialMode::kStrict:     return "strict";
        case SequentialMode::kBestEffort: return "best_effort";
    }
    return "unknown";
}

// ============================================================================
// StepResult — Result of executing a single step in sequential composition
//
// This is the authoritative source for per-step outcome.
// ============================================================================

struct StepResult {
    size_t index;                    // Position in sequence (0-based)
    std::string step_id;             // Original intent ID
    
    core::SemanticStatus status{core::SemanticStatus::kUnknown};
    bool changed{false};             // Did this step change state?
    bool verified{false};            // Was postcondition verification successful?
    
    std::vector<core::Evidence> evidence;
    std::optional<std::string> output_value;
    std::chrono::milliseconds elapsed_ms{0};
    
    // For failures
    std::optional<core::Error> error;
};

inline bool is_success(const StepResult& r) {
    return r.status == core::SemanticStatus::kSuccess && r.verified;
}

// ============================================================================
// SequentialResult — Result of executing a sequential composition
//
// This contains:
//   * Aggregate status (what actually happened)
//   * Individual per-step results (for transparency/debugging)
//   * Timing information for the entire sequence
// ============================================================================

struct SequentialResult {
    SequentialMode mode{SequentialMode::kStrict};
    
    // Aggregate outcome
    core::SemanticStatus aggregate_status{core::SemanticStatus::kUnknown};
    
    // Individual step outcomes
    std::vector<StepResult> steps;
    
    // Timing information for the entire sequence
    std::chrono::milliseconds total_duration_ms{0};
    
    // For verification tracking
    bool all_verified{false};
    
    // Factory methods for common cases
    
    static SequentialResult success(std::vector<StepResult> results) {
        SequentialResult r;
        r.mode = SequentialMode::kStrict;  // Default to strict on success
        r.aggregate_status = core::SemanticStatus::kSuccess;
        r.steps = std::move(results);
        r.all_verified = true;
        
        for (const auto& s : r.steps) {
            r.total_duration_ms += s.elapsed_ms;
            if (!s.verified) r.all_verified = false;
        }
        return r;
    }
    
    static SequentialResult partial_success(std::vector<StepResult> results) {
        SequentialResult r;
        r.mode = SequentialMode::kBestEffort;  // Best-effort allows partial success
        r.aggregate_status = core::SemanticStatus::kSuccess;
        r.steps = std::move(results);
        
        bool any_verified = false;
        for (const auto& s : r.steps) {
            r.total_duration_ms += s.elapsed_ms;
            if (s.verified) any_verified = true;
        }
        r.all_verified = any_verified;  // At least one verified
        
        return r;
    }
    
    static SequentialResult failure(std::string error_code, std::string message,
                                     size_t failed_at_index) {
        SequentialResult r;
        r.aggregate_status = core::SemanticStatus::kFailure;
        r.steps.emplace_back();
        auto& s = r.steps.back();
        s.status = core::SemanticStatus::kFailure;
        s.error = core::Error{std::move(error_code), std::move(message)};
        s.index = failed_at_index;
        return r;
    }
    
    static SequentialResult unknown() {
        SequentialResult r;
        r.aggregate_status = core::SemanticStatus::kUnknown;
        // steps is empty - no evidence available
        return r;
    }
    
    bool is_success() const {
        return aggregate_status == core::SemanticStatus::kSuccess && all_verified;
    }
    
    bool has_failures() const {
        for (const auto& s : steps) {
            if (!rebuntu::command::is_success(s)) return true;
        }
        return false;
    }
};

// ============================================================================
// SequentialIntent — Typed composition of multiple command intents
//
// This explicitly models a sequence of commands where each step:
//   * Retains its own validation/authorization/verification semantics
//   * May depend on previous steps' success (strict mode) or continue (best-effort)
//   * Has independent outcome tracking
// ============================================================================

struct SequentialIntent {
    std::string id;                              // Unique sequence ID
    
    // Execution strategy
    SequentialMode mode{SequentialMode::kStrict};  // How to execute the sequence
    
    // Commands in this sequence (ORDERED - matters for dependencies)
    std::vector<CommandIntent> intents;
    
    // Optional execution policy
    ExecutionPolicy execution_policy{};
    
    // Source information (for debugging/explain)
    std::optional<std::string> source_context;
    std::optional<int> source_line;
    
    // Factory method for creating a sequence from multiple intents
    static SequentialIntent make(SequentialMode m, std::vector<CommandIntent> ints) {
        SequentialIntent s;
        s.id = "seq-" + std::to_string(std::chrono::system_clock::now().time_since_epoch().count());
        s.mode = m;
        s.intents = std::move(ints);
        
        // Inherit execution policy from first intent if not explicitly set
        if (!ints.empty()) {
            s.execution_policy = ints[0].execution_policy;
        }
        
        return s;
    }
    
    // Add another intent to the sequence
    void add_intent(CommandIntent intent) {
        intents.push_back(std::move(intent));
    }
};

// ============================================================================
// SequentialBuilder — Fluent builder for creating sequential intents
// ============================================================================

class SequentialBuilder {
public:
    explicit SequentialBuilder(SequentialMode mode = SequentialMode::kStrict)
        : seq_(make_default_sequence(mode)) {}
    
    // Add a single intent to the sequence
    SequentialBuilder& add_intent(CommandIntent intent) {
        seq_.intents.push_back(std::move(intent));
        return *this;
    }
    
    // Add multiple intents at once
    SequentialBuilder& add_intents(std::vector<CommandIntent> intents) {
        for (auto& i : intents) {
            seq_.intents.push_back(std::move(i));
        }
        return *this;
    }
    
    // Set sequence-level execution policy
    SequentialBuilder& with_execution_policy(ExecutionPolicy policy) {
        seq_.execution_policy = std::move(policy);
        return *this;
    }
    
    // Set source context for debugging
    SequentialBuilder& with_source_context(std::string ctx) {
        seq_.source_context = std::move(ctx);
        return *this;
    }
    
    // Build the final sequence intent
    SequentialIntent build() {
        SequentialIntent result = std::move(seq_);
        // Reset to default for next use
        seq_ = make_default_sequence(seq_.mode);
        return result;
    }

private:
    static SequentialIntent make_default_sequence(SequentialMode mode) {
        SequentialIntent s;
        s.id = "seq-" + std::to_string(std::chrono::system_clock::now().time_since_epoch().count());
        s.mode = mode;
        return s;
    }
    
    SequentialIntent seq_;
};

// ============================================================================
// Error codes for sequential composition operations
// ============================================================================

namespace error {
    constexpr const char kSequenceEmpty[] = "E_SEQUENCE_EMPTY";           // No commands in sequence
    constexpr const char kSequencePartialSuccess[] = "E_SEQUENCE_PARTIAL"; // Some steps failed
    constexpr const char kSequenceAllFailed[] = "E_SEQUENCE_ALL_FAILED";   // All steps failed
    constexpr const char kSequenceTimeout[] = "E_SEQUENCE_TIMEOUT";        // Sequence execution timed out
    constexpr const char kSequenceCancelled[] = "E_SEQUENCE_CANCELLED";    // Sequence was cancelled
}

}  // namespace rebuntu::command