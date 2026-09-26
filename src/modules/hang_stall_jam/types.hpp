// rebuntu::modules::hang_stall_jam — Hang / Stall / Jam Detection Types (Phase 5.11)
//
// This header defines core types for detecting hangs, stalls and jams across processes,
// services, and runtime work in Rebuntu:
//   - Process stall states: normal, suspected_stall, corroborated_stall
//   - Work progress evidence: heartbeat counters, queue consumption, I/O completion
//   - Temporal windows using monotonic time
//   - Multi-signal suspicion without automatic termination
//
// Design Philosophy:
//   * Progress evidence before stall classification
//   * Monotonic time for elapsed window decisions
//   * Observation ≠ inference (separate detection from interpretation)
//   * Monitoring ≠ recovery (this module observes, does not repair/kill)

#pragma once

#include <system/core/contracts.hpp>
#include <runtime/contracts.hpp>

#include <chrono>
#include <cstdint>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <optional>
#include <iosfwd>

namespace rebuntu::modules::hang_stall_jam {

// ============================================================================
// StallState — Progress state of an entity
// ============================================================================

enum class StallState {
    kNormal,          // Making progress normally
    kSuspectedStall,  // May be stalled (some signals present)
    kCorroboratedStall, // Likely stalled (multiple corroborating signals)
};

inline std::string to_string(StallState s) {
    switch (s) {
        case StallState::kNormal:          return "normal";
        case StallState::kSuspectedStall:  return "suspected_stall";
        case StallState::kCorroboratedStall: return "corroborated_stall";
    }
    return "unknown";
}

// ============================================================================
// SubjectType — Type of subject being monitored for stalls
// ============================================================================

enum class SubjectType {
    kProcess,         // A process (by PID)
    kService,         // A systemd service (by unit name)
    kRuntimeWorkUnit, // Internal runtime work unit
};

inline std::string to_string(SubjectType t) {
    switch (t) {
        case SubjectType::kProcess:       return "process";
        case SubjectType::kService:       return "service";
        case SubjectType::kRuntimeWorkUnit: return "runtime_work_unit";
    }
    return "unknown";
}

// ============================================================================
// EvidenceType — Type of progress evidence we can observe
// ============================================================================

enum class EvidenceType {
    kHeartbeat,           // Heartbeat counter increment
    kQueueConsumption,    // Queue item consumption
    kIoCompletion,        // I/O operation completion
    kTaskProgress,        // Task milestone reached
    kWorkUnitStateChange, // Work unit state transition
};

inline std::string to_string(EvidenceType t) {
    switch (t) {
        case EvidenceType::kHeartbeat:          return "heartbeat";
        case EvidenceType::kQueueConsumption:   return "queue_consumption";
        case EvidenceType::kIoCompletion:       return "io_completion";
        case EvidenceType::kTaskProgress:       return "task_progress";
        case EvidenceType::kWorkUnitStateChange:return "work_unit_state_change";
    }
    return "unknown";
}

// ============================================================================
// StallSignal — A single signal contributing to stall suspicion
// ============================================================================

struct StallSignal {
    EvidenceType type = EvidenceType::kHeartbeat;
    
    // When this signal was observed
    std::chrono::system_clock::time_point observed_at;
    std::optional<std::chrono::steady_clock::time_point> monotonic_timestamp;
    
    // Subject identity
    std::string subject_id;  // PID, unit name, or work unit ID
    
    // Signal details
    std::optional<int64_t> last_sequence;      // Last seen sequence (e.g., heartbeat counter)
    std::optional<std::chrono::milliseconds> elapsed_since_last;
    
    // Evidence quality metadata
    bool is_trusted = true;           // Source is reliable
    bool may_be_truncated = false;    // Data may be incomplete
};

// ============================================================================
// ProgressWindow — Temporal window for progress analysis
// ============================================================================

struct ProgressWindow {
    std::chrono::steady_clock::time_point window_start;
    std::optional<std::chrono::steady_clock::time_point> window_end;  // nullopt = still active
    
    // Expected progress during this window
    struct ExpectedProgress {
        EvidenceType evidence_type;
        int64_t min_expected_count;
        std::optional<int64_t> max_expected_count;  // nullopt = no upper bound
    };
    std::vector<ExpectedProgress> expected_progress;
    
    // Actual progress observed
    struct ObservedProgress {
        EvidenceType evidence_type;
        int64_t actual_count;
        std::chrono::steady_clock::time_point last_observation;
    };
    std::vector<ObservedProgress> observed_progress;
};

// ============================================================================
// StallEvidence — Complete evidence set for a stall assessment
// ============================================================================

struct StallEvidence {
    SubjectType subject_type = SubjectType::kProcess;
    std::string subject_id;  // PID, unit name, or work unit ID
    
    // State timeline
    std::vector<std::pair<std::chrono::system_clock::time_point, StallState>> state_changes;
    
    // Evidence windows
    std::optional<ProgressWindow> current_window;
    
    // Signal history (most recent first)
    std::vector<StallSignal> recent_signals;
    
    // Assessment metadata
    std::chrono::system_clock::time_point assessed_at;
    std::optional<std::string> boot_id;  // For cross-boot evidence isolation
    
    // Uncertainty notes
    bool evidence_complete = true;
    std::vector<std::string> uncertainty_notes;
};

// ============================================================================
// StallDetectorConfig — Configuration for the stall detector
// ============================================================================

struct StallDetectorConfig {
    // Temporal windows
    std::chrono::milliseconds stall_suspicion_window{1000};  // 1 second window
    std::chrono::milliseconds corroborated_stall_window{3000};  // 3 seconds
    
    // Thresholds
    int heartbeat_missing_threshold = 5;      // Missed heartbeats to suspect stall
    int progress_noop_threshold = 3;          // No progress steps for this many windows
    
    // Evidence thresholds (counts in window)
    std::optional<int> min_queue_consumption_threshold;
    std::optional<int64_t> min_io_completion_threshold;
    
    // Signal correlation settings
    bool require_corroborating_signals = true;
    int corroborating_signal_count = 2;
    
    // Evidence retention
    size_t max_evidence_per_subject = 64;
    std::chrono::hours evidence_retention_hours{24};
    
    // Native source configuration
    bool enable_process_monitoring = true;
    bool enable_service_monitoring = true;
    bool enable_runtime_work_monitoring = true;
};

// ============================================================================
// StallAssessment — Complete stall assessment for a subject
// ============================================================================

struct StallAssessment {
    SubjectType subject_type = SubjectType::kProcess;
    std::string subject_id;  // PID, unit name, or work unit ID
    
    StallState state = StallState::kNormal;
    
    // Assessment details
    std::chrono::system_clock::time_point assessed_at;
    std::optional<std::chrono::duration<double>> assessment_duration_ms;
    
    // Progress evidence in current window
    std::optional<ProgressWindow> active_window;
    
    // Signal analysis
    struct SignalAnalysis {
        EvidenceType type;
        int64_t expected_count = 0;
        int64_t actual_count = 0;
        bool meets_threshold = false;
        std::string reason;
    };
    std::vector<SignalAnalysis> signal_analyses;
    
    // Suspicion reasoning
    struct SuspicionReason {
        EvidenceType signal_type;
        std::chrono::milliseconds elapsed_since_last;
        std::string explanation;
    };
    std::vector<SuspicionReason> suspicion_reasons;
    
    // Corroborating evidence from other sources
    std::vector<StallEvidence> corroborating_evidence;
    
    // Evidence IDs for lookup
    std::vector<std::string> evidence_ids;
    
    bool is_complete = true;
    std::vector<std::string> uncertainty_notes;
};

// ============================================================================
// StallEvent — Event generated when stall state changes
// ============================================================================

struct StallEvent {
    enum class EventType {
        kSuspectedStall,            // State changed to suspected stall
        kCorroboratedStall,         // State upgraded to corroborated
        kRecoveredFromStall,        // Recovered from any stall state
        kProgressObserved,          // Progress evidence received
        kSignalReceived,            // Raw signal received (before assessment)
    } event_type = EventType::kProgressObserved;
    
    std::string event_id;  // Unique identifier
    
    std::chrono::system_clock::time_point timestamp;
    
    SubjectType subject_type = SubjectType::kProcess;
    std::string subject_id;
    
    StallState previous_state = StallState::kNormal;
    StallState current_state = StallState::kNormal;
    
    // Evidence supporting this event
    std::vector<rebuntu::core::Evidence> evidence;
    
    // Human-readable description
    std::string description;
};

// ============================================================================
// WorkUnitProgress — Progress tracking for runtime work units
// ============================================================================

struct WorkUnitProgress {
    std::string work_unit_id;  // Runtime work unit identifier
    
    // Heartbeat/progress sequence
    int64_t current_sequence = 0;
    std::chrono::steady_clock::time_point last_heartbeat;
    
    // Step tracking (for multi-step operations)
    struct StepProgress {
        std::string step_name;
        bool completed = false;
        std::optional<std::chrono::milliseconds> duration_ms;
    };
    std::vector<StepProgress> steps;
    
    // Current step index
    size_t current_step_index = 0;
};

// ============================================================================
// InternalAlert — Alert for internal monitoring systems
// ============================================================================

struct InternalAlert {
    std::string id;  // Unique alert ID
    
    std::chrono::system_clock::time_point created_at;
    std::optional<std::chrono::system_clock::time_point> last_updated_at;
    
    enum class Severity { kInfo, kLow, kMedium, kHigh } severity = Severity::kInfo;
    
    StallState stall_state = StallState::kNormal;
    
    SubjectType subject_type = SubjectType::kProcess;
    std::string subject_id;
    
    // Evidence chain
    std::vector<rebuntu::core::Evidence> evidence;
    
    // Assessment context
    std::optional<std::string> boot_id;
    
    // Deduplication (to prevent alert storms)
    bool is_new_occurrence = true;
    std::optional<std::chrono::system_clock::time_point> hysteresis_window_start;
    
    // Reasoning for the alert
    struct AlertReason {
        EvidenceType signal_type;
        std::string explanation;
    };
    std::vector<AlertReason> reasons;
    
    // Recommended actions (diagnostic only, no automatic recovery)
    struct RecommendedAction {
        std::string category;  // "diagnostic", "monitor", "investigate"
        std::string description;
    };
    std::vector<RecommendedAction> recommended_actions;
};

// ============================================================================
// StallDetectorMetrics — Runtime metrics for the stall detector
// ============================================================================

struct StallDetectorMetrics {
    size_t assessments_performed = 0;
    size_t observations_received = 0;
    size_t events_generated = 0;
    
    // By subject type
    std::map<SubjectType, size_t> assessments_by_subject_type;
    std::map<SubjectType, size_t> events_by_subject_type;
    
    // State counts
    size_t subjects_in_normal_state = 0;
    size_t subjects_in_suspected_stall = 0;
    size_t subjects_in_corroborated_stall = 0;
    
    // Signal types
    std::map<EvidenceType, size_t> signal_counts;
    
    // Performance
    std::optional<std::chrono::milliseconds> last_assessment_duration_ms;
    
    // Start time for this metrics instance
    std::chrono::system_clock::time_point started_at = 
        std::chrono::system_clock::now();
};

// ============================================================================
// Factory functions for creating result objects
// ============================================================================

inline StallEvidence make_initial_evidence(
    SubjectType subject_type,
    const std::string& subject_id) {
    StallEvidence evidence;
    evidence.subject_type = subject_type;
    evidence.subject_id = subject_id;
    evidence.assessed_at = std::chrono::system_clock::now();
    return evidence;
}

inline WorkUnitProgress make_initial_work_unit_progress(const std::string& work_unit_id) {
    WorkUnitProgress progress;
    progress.work_unit_id = work_unit_id;
    progress.current_sequence = 0;
    progress.last_heartbeat = std::chrono::steady_clock::now();
    return progress;
}

}  // namespace rebuntu::modules::hang_stall_jam

// ============================================================================
// Ostream operators for easy debugging
// ============================================================================

inline std::ostream& operator<<(std::ostream& os, 
                                rebuntu::modules::hang_stall_jam::StallState s) {
    return os << rebuntu::modules::hang_stall_jam::to_string(s);
}

inline std::ostream& operator<<(std::ostream& os,
                                rebuntu::modules::hang_stall_jam::SubjectType t) {
    return os << rebuntu::modules::hang_stall_jam::to_string(t);
}

inline std::ostream& operator<<(std::ostream& os,
                                rebuntu::modules::hang_stall_jam::EvidenceType t) {
    return os << rebuntu::modules::hang_stall_jam::to_string(t);
}
