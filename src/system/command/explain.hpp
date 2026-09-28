// rebuntu::command::explain — Execution Plan Explain-Plan Output (Phase 6.28)
//
// This module provides structured operator-readable plan explanation showing:
//
//   * Exact target, operation
//   * Evidence sources and uncertainty
//   * Preconditions and expected effects
//   * Verification strategy
//   * Known irreversible/unknown aspects
//
// Key Principles:
//   * Explain-plan is separate from execution result
//   * Output is structured for programmatic consumption
//   * Human-readable rendering provided as optional layer
//   * Uncertainty is explicit, not hidden

#pragma once

#include "model.hpp"
#include <string>
#include <vector>
#include <map>
#include <optional>
#include <chrono>

namespace rebuntu::command::explain {

// ---------------------------------------------------------------------------
// ExplainFormat — Output format for explain-plan
// ---------------------------------------------------------------------------
enum class ExplainFormat {
    TEXT,      // Human-readable prose with structure markers
    JSON,      // Machine-readable JSON (structured output)
    TABLE,     // Tabular format for terminal display
};

inline std::string to_string(ExplainFormat f) {
    switch (f) {
        case ExplainFormat::TEXT:   return "text";
        case ExplainFormat::JSON:   return "json";
        case ExplainFormat::TABLE:  return "table";
    }
    return "unknown";
}

// ---------------------------------------------------------------------------
// PlanStepStatus — Status of a plan step in the execution trace
// ---------------------------------------------------------------------------
enum class PlanStepStatus {
    NOT_STARTED,     // Step not yet executed
    IN_PROGRESS,     // Step currently executing
    COMPLETED,       // Step completed (may or may not be verified)
    SKIPPED,         // Step skipped due to conditions
    FAILED,          // Step execution failed
    UNKNOWN,         // Status unknown
};

inline std::string to_string(PlanStepStatus s) {
    switch (s) {
        case PlanStepStatus::NOT_STARTED: return "not_started";
        case PlanStepStatus::IN_PROGRESS: return "in_progress";
        case PlanStepStatus::COMPLETED:   return "completed";
        case PlanStepStatus::SKIPPED:     return "skipped";
        case PlanStepStatus::FAILED:      return "failed";
        case PlanStepStatus::UNKNOWN:     return "unknown";
    }
    return "unknown";
}

// ---------------------------------------------------------------------------
// EvidenceItem — A single piece of evidence supporting the plan
// ---------------------------------------------------------------------------
struct EvidenceItem {
    std::string source;           // Where this evidence came from (procfs, systemd, etc.)
    std::string observation;      // The observed fact or value
    std::chrono::system_clock::time_point timestamp;
    bool is_known_state{false};   // true = known before execution
    bool is_required_for_success{true};
};

// ---------------------------------------------------------------------------
// Uncertainty — A known uncertainty in the plan
// ---------------------------------------------------------------------------
struct Uncertainty {
    std::string description;           // What is uncertain
    std::string severity{"medium"};    // low, medium, high
    std::vector<std::string> impact;   // How this affects the plan
    
    static Uncertainty make_low(std::string desc) {
        Uncertainty u;
        u.description = std::move(desc);
        u.severity = "low";
        return u;
    }
    
    static Uncertainty make_medium(std::string desc) {
        Uncertainty u;
        u.description = std::move(desc);
        u.severity = "medium";
        return u;
    }
    
    static Uncertainty make_high(std::string desc) {
        Uncertainty u;
        u.description = std::move(desc);
        u.severity = "high";
        return u;
    }
};

// ---------------------------------------------------------------------------
// VerificationStep — A verification step for post-execution validation
// ---------------------------------------------------------------------------
struct VerificationStep {
    std::string id;                   // Unique identifier for this check
    std::string description;          // Human-readable description
    std::string verification_type;    // e.g., "state_comparison", "predicate_check"
    std::optional<std::string> expected_state;
    std::optional<std::string> actual_state;
    PlanStepStatus status{PlanStepStatus::NOT_STARTED};
};

// ---------------------------------------------------------------------------
// IrreversibleAspect — A known irreversible aspect of the operation
// ---------------------------------------------------------------------------
struct IrreversibleAspect {
    std::string description;           // What is irreversible
    bool can_be_restored{false};       // Can a restore/recovery bring back original state?
    std::optional<std::string> recovery_method;
    
    static IrreversibleAspect permanent_change(std::string desc) {
        IrreversibleAspect i;
        i.description = std::move(desc);
        i.can_be_restored = false;
        return i;
    }
    
    static IrreversibleAspect reversible_with_restore(std::string desc, std::string method) {
        IrreversibleAspect i;
        i.description = std::move(desc);
        i.can_be_restored = true;
        i.recovery_method = std::move(method);
        return i;
    }
};

// ---------------------------------------------------------------------------
// PlanExplanation — Complete explain-plan output
// ---------------------------------------------------------------------------
struct PlanExplanation {
    // Basic identification
    std::string plan_id;              // Unique identifier for this plan
    std::chrono::system_clock::time_point created_at;
    
    // Target and operation
    std::string operation_name;       // e.g., "filesystem.copy", "service.restart"
    std::optional<std::string> subject_type;   // What the operation acts upon
    std::optional<std::string> target_id;      // Specific target if applicable
    
    // Input parameters
    std::map<std::string, std::string> input_parameters;
    
    // Preconditions: what must be true before execution
    std::vector<std::string> preconditions;
    std::vector<PlanStepStatus> preconditions_met;  // Status of each precondition check
    
    // Expected effects: what should change during execution
    std::vector<std::string> expected_effects;
    
    // Step-by-step execution plan
    struct PlanStep {
        size_t index;                   // 0-based index in the plan
        std::string id;                 // Unique step identifier
        SemanticKind kind;              // What type of operation this is
        std::string description;        // Human-readable summary
        CapabilityReference capability; // Canonical capability being invoked
        
        // Execution details
        std::vector<Argument> arguments;
        std::vector<Qualifier> qualifiers;
        
        // Dependencies on other steps
        std::vector<size_t> depends_on;  // Indices of prerequisite steps
        
        // Status tracking
        PlanStepStatus status{PlanStepStatus::NOT_STARTED};
        std::optional<std::chrono::milliseconds> duration_ms;
        
        // Evidence from this step (if executed)
        std::vector<EvidenceItem> evidence;
    };
    
    std::vector<PlanStep> steps;
    
    // Verification strategy: how success will be confirmed
    std::vector<VerificationStep> verification_steps;
    
    // Uncertainties in the plan
    std::vector<Uncertainty> uncertainties;
    
    // Irreversible aspects (changes that cannot be undone)
    std::vector<IrreversibleAspect> irreversible_aspects;
    
    // Evidence sources for state observation
    std::vector<std::string> evidence_sources;  // e.g., "procfs", "systemd", "sysfs"
    
    // Summary information
    bool requires_privilege{false};
    bool is_idempotent{false};           // Can be safely re-run
    size_t estimated_duration_ms{0};     // Estimated total execution time
    
    // Helper methods to build explanation - implemented after struct definition
    std::string to_text() const;
    std::string to_json() const;
    std::string to_table() const;
};


// ---------------------------------------------------------------------------
// ExplainRenderer — Renders explain-plan outputs in various formats
// ---------------------------------------------------------------------------
class ExplainRenderer {
public:
    static std::string render_text(const PlanExplanation& exp);
    static std::string render_json(const PlanExplanation& exp);
    static std::string render_table(const PlanExplanation& exp);
};

}  // namespace rebuntu::command::explain