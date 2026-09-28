// Rebuntu Runtime — Cross-Operation Conflict Detection (Phase 6.32)
//
// Detect incompatible simultaneous operations using typed target/effect
// information without inventing a universal transaction manager.
//
// Key principles:
//   - Operations are tracked by their target resource and side effect kind
//   - Conflicts occur when mutating operations overlap on the same target
//   - Observation-only operations never conflict with each other or with reads
//   - No global mutex; conflicts detected per-target via typed metadata

#pragma once

#include <system/core/contracts.hpp>
#include <chrono>
#include <optional>
#include <set>
#include <string>
#include <vector>

namespace rebuntu::runtime::native_command_operation_execution {

// ============================================================================
// Type aliases for core types
// ============================================================================

using SideEffectKind = rebuntu::core::SideEffectKind;
using Idempotency = rebuntu::core::Idempotency;
using Reversibility = rebuntu::core::Reversibility;

// ============================================================================
// CrossOperationConflictDetection — Phase 6.32 subtask target
// ============================================================================

struct CrossOperationConflictDetection final {
    static constexpr const char* source_prompt = ".phases/phases/phase-06-native-command-operation-execution/prompts/6.32_cross-operation_conflict_detection.md";
    static constexpr const char* structural_status = "SKELETON_MATERIALIZED";
    
    // Target identity for tracking operations
    struct TargetIdentity {
        std::string target_id;      // stable identifier (path, service name, etc.)
        std::string subject_type;   // e.g., "filesystem.path", "service"
        
        bool operator<(const TargetIdentity& other) const {
            if (subject_type != other.subject_type) return subject_type < other.subject_type;
            return target_id < other.target_id;
        }
    };
    
    // Active operation record
    struct ActiveOperationRecord {
        std::string operation_id;       // which operation is running
        TargetIdentity target;          // what it's operating on
        SideEffectKind side_effect;
        
        std::chrono::system_clock::time_point started_at;
        std::optional<std::chrono::milliseconds> expected_duration_ms;
    };
    
    // Conflict information when detection finds incompatible operations
    struct ConflictInfo {
        std::string operation_a_id;     // first conflicting operation
        std::string operation_b_id;     // second conflicting operation
        
        TargetIdentity target;          // what they conflict on
        
        SideEffectKind effect_a;
        SideEffectKind effect_b;
        
        std::chrono::system_clock::time_point detected_at;
    };
    
    // Check if two operations would conflict based on their metadata
    static bool would_conflict(const ActiveOperationRecord& a, const ActiveOperationRecord& b) {
        // Different targets never conflict
        if (a.target.subject_type != b.target.subject_type || 
            a.target.target_id != b.target.target_id) {
            return false;
        }
        
        // Same target: check side effect combinations
        const auto eff_a = a.side_effect;
        const auto eff_b = b.side_effect;
        
        // NONE operations are always compatible
        if (eff_a == SideEffectKind::NONE || eff_b == SideEffectKind::NONE) {
            return false;
        }
        
        // OBSERVATION-only operations don't conflict with each other
        if (eff_a == SideEffectKind::OBSERVATION && eff_b == SideEffectKind::OBSERVATION) {
            return false;
        }
        
        // MUTATING/PRIVILEGED/DESTRUCTIVE + MUTATING/PRIVILEGED/DESTRUCTIVE on same target conflicts
        const auto is_mutating = [](SideEffectKind eff) {
            return eff == SideEffectKind::MUTATING ||
                   eff == SideEffectKind::PRIVILEGED ||
                   eff == SideEffectKind::DESTRUCTIVE;
        };
        
        if (is_mutating(eff_a) && is_mutating(eff_b)) {
            return true;
        }
        
        // Destructive + anything on same target conflicts
        if (eff_a == SideEffectKind::DESTRUCTIVE || eff_b == SideEffectKind::DESTRUCTIVE) {
            return true;
        }
        
        // OBSERVATION + MUTATING is compatible (observation doesn't change state)
        if ((eff_a == SideEffectKind::OBSERVATION && is_mutating(eff_b)) ||
            (eff_b == SideEffectKind::OBSERVATION && is_mutating(eff_a))) {
            return false;
        }
        
        // Default: assume compatible for mixed effects on same target
        return false;
    }
    
    // Check if an operation would conflict with any currently active operations
    static std::optional<ConflictInfo> check_conflict(
        const ActiveOperationRecord& candidate,
        const std::vector<ActiveOperationRecord>& active_operations
    ) {
        for (const auto& existing : active_operations) {
            if (would_conflict(candidate, existing)) {
                ConflictInfo conflict;
                conflict.operation_a_id = candidate.operation_id;
                conflict.operation_b_id = existing.operation_id;
                conflict.target = candidate.target;
                conflict.effect_a = candidate.side_effect;
                conflict.effect_b = existing.side_effect;
                conflict.detected_at = std::chrono::system_clock::now();
                return conflict;
            }
        }
        return std::nullopt;
    }
    
    // Get all targets currently being operated on
    static std::set<TargetIdentity> get_active_targets(
        const std::vector<ActiveOperationRecord>& active_operations
    ) {
        std::set<TargetIdentity> targets;
        for (const auto& op : active_operations) {
            if (op.side_effect != SideEffectKind::NONE &&
                op.side_effect != SideEffectKind::OBSERVATION) {
                targets.insert(op.target);
            }
        }
        return targets;
    }
    
    // Filter active operations to only those with mutating effects
    static std::vector<ActiveOperationRecord> get_mutating_operations(
        const std::vector<ActiveOperationRecord>& active_operations
    ) {
        std::vector<ActiveOperationRecord> result;
        for (const auto& op : active_operations) {
            if (op.side_effect == SideEffectKind::MUTATING ||
                op.side_effect == SideEffectKind::PRIVILEGED ||
                op.side_effect == SideEffectKind::DESTRUCTIVE) {
                result.push_back(op);
            }
        }
        return result;
    }
    
    // Check if a target has any active mutating operations
    static bool has_mutating_operation_on_target(
        const TargetIdentity& target,
        const std::vector<ActiveOperationRecord>& active_operations
    ) {
        for (const auto& op : active_operations) {
            if ((op.side_effect == SideEffectKind::MUTATING ||
                 op.side_effect == SideEffectKind::PRIVILEGED ||
                 op.side_effect == SideEffectKind::DESTRUCTIVE) &&
                op.target.subject_type == target.subject_type &&
                op.target.target_id == target.target_id) {
                return true;
            }
        }
        return false;
    }
};

// ============================================================================
// ExecutionConflictDetector — Runtime state for conflict detection
//
// Tracks active operations and detects conflicts before execution.
// Used by the executor to prevent incompatible simultaneous operations.
// ============================================================================

class ExecutionConflictDetector final {
public:
    using ActiveOperationRecord = CrossOperationConflictDetection::ActiveOperationRecord;
    
    // Record an operation as starting execution
    void begin_execution(
        std::string operation_id,
        const rebuntu::core::OperationDefinition& op_def,
        std::string target_id
    ) {
        ActiveOperationRecord record;
        record.operation_id = std::move(operation_id);
        record.target.subject_type = op_def.subject_type;
        record.target.target_id = std::move(target_id);
        record.side_effect = op_def.side_effect;
        record.started_at = std::chrono::system_clock::now();
        
        // Convert int64_t milliseconds to std::chrono::milliseconds
        if (op_def.max_execution_time_ms.has_value()) {
            record.expected_duration_ms = 
                std::chrono::milliseconds(static_cast<int64_t>(*op_def.max_execution_time_ms));
        }
        
        active_operations_.push_back(std::move(record));
    }
    
    // Record an operation as completed
    void end_execution(const std::string& operation_id, const std::string& target_id) {
        auto pred = [&operation_id, &target_id](const ActiveOperationRecord& rec) {
            return rec.operation_id == operation_id && rec.target.target_id == target_id;
        };
        active_operations_.erase(
            std::remove_if(active_operations_.begin(), active_operations_.end(), pred),
            active_operations_.end()
        );
    }
    
    // Check if an operation would conflict with currently active operations
    std::optional<CrossOperationConflictDetection::ConflictInfo> check_conflict(
        const std::string& operation_id,
        const rebuntu::core::OperationDefinition& op_def,
        const std::string& target_id
    ) {
        ActiveOperationRecord candidate;
        candidate.operation_id = operation_id;
        candidate.target.subject_type = op_def.subject_type;
        candidate.target.target_id = target_id;
        candidate.side_effect = op_def.side_effect;
        
        return CrossOperationConflictDetection::check_conflict(
            candidate, active_operations_);
    }
    
    // Get count of currently active operations
    std::size_t active_count() const {
        return active_operations_.size();
    }
    
    // Clear all active operations (for testing/reset)
    void clear() {
        active_operations_.clear();
    }
    
private:
    std::vector<ActiveOperationRecord> active_operations_;
};

} // namespace rebuntu::runtime::native_command_operation_execution