// rebuntu::modules::hang_stall_jam — Stall Detector (Phase 5.11)
//
// This module provides evidence-based detection of hangs, stalls and jams across
// processes/services and runtime work units in Rebuntu.
//
// Design Philosophy:
//   * Progress evidence before stall classification
//   * Monotonic time for elapsed window decisions
//   * Observation ≠ inference (separate detection from interpretation)
//   * Monitoring ≠ recovery (this module observes, does not repair/kill)

#pragma once

#include <memory>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <optional>
#include <functional>
#include <mutex>

#include "types.hpp"

namespace rebuntu::modules::hang_stall_jam {

// ============================================================================
// StallDetector — Main stall detection engine
//
// This class combines progress observations from native Linux sources into
// stall assessments. It does NOT perform recovery actions.
// ============================================================================

class StallDetector {
public:
    explicit StallDetector(StallDetectorConfig config);
    ~StallDetector();
    
    // Lifecycle management
    core::Outcome start();
    core::Outcome stop();
    bool is_running() const { return running_; }
    
    // Configuration
    const StallDetectorConfig& config() const { return config_; }
    void set_config(const StallDetectorConfig& config);
    
    // Add progress evidence from various sources
    
    // Process/daemon heartbeat evidence (from procfs)
    core::Outcome add_process_heartbeat(
        const std::string& pid,
        int64_t sequence,
        std::chrono::steady_clock::time_point timestamp,
        std::chrono::system_clock::time_point observed_at);
    
    // Service progress evidence (from systemd/journald)
    core::Outcome add_service_progress(
        const std::string& unit_name,
        EvidenceType evidence_type,
        int64_t sequence,
        std::chrono::steady_clock::time_point timestamp,
        std::chrono::system_clock::time_point observed_at);
    
    // Runtime work unit progress
    core::Outcome add_work_unit_progress(const WorkUnitProgress& progress);
    
    // Perform stall assessment for a subject
    StallAssessment assess_stall_state(
        const std::string& subject_id,
        SubjectType subject_type,
        std::chrono::system_clock::time_point assessment_time = std::chrono::system_clock::now());
    
    // Get current stall state for a subject
    StallState get_subject_stall_state(
        const std::string& subject_id,
        SubjectType subject_type) const;
    
    // Get all pending events (e.g., for diagnostics)
    std::vector<StallEvent> get_pending_events();
    void acknowledge_event(const std::string& event_id);
    
    // Get internal alerts (for monitoring systems)
    std::vector<InternalAlert> get_alerts();
    
    // Metrics for monitoring the monitor itself
    StallDetectorMetrics metrics() const;

private:
    StallDetectorConfig config_;
    
    bool running_ = false;
    mutable std::mutex mutex_;
    
    // Internal tracking structures
    
    struct EvidenceEntry {
        EvidenceType type;
        int64_t sequence;
        std::chrono::steady_clock::time_point monotonic_time;
        std::chrono::system_clock::time_point observed_at;
    };
    
    struct WindowProgress {
        std::chrono::steady_clock::time_point window_start;
        std::map<EvidenceType, int64_t> evidence_counts;
        std::map<EvidenceType, std::chrono::steady_clock::time_point> last_observation;
    };
    
    struct SubjectState {
        SubjectType type = SubjectType::kProcess;
        
        // State timeline with timestamps
        std::vector<std::pair<std::chrono::system_clock::time_point, StallState>> state_timeline;
        
        // Progress evidence storage
        std::vector<EvidenceEntry> recent_evidence;
        
        // Current progress window
        std::optional<WindowProgress> current_window;
        
        // Last state change time (monotonic)
        std::optional<std::chrono::steady_clock::time_point> last_state_change_monotonic;
    };
    
    std::map<std::string, SubjectState> subject_states_;
    
    // Event tracking
    struct EventRegistry {
        std::vector<StallEvent> pending_events;
        std::set<std::string> acknowledged_ids;
        size_t next_event_id = 0;
    };
    std::unique_ptr<EventRegistry> events_;
    
    // Alert registry (for internal monitoring)
    struct AlertRegistry {
        std::map<std::string, InternalAlert> active_alerts;  // by subject_id
        size_t next_alert_id = 0;
    };
    std::unique_ptr<AlertRegistry> alerts_;
    
    // Metrics
    StallDetectorMetrics metrics_;
    
    // Helper methods
    
    void update_state_timeline(
        SubjectState& state,
        StallState new_state,
        std::chrono::system_clock::time_point timestamp);
    
    bool should_suspect_stall(const SubjectState& state, std::chrono::steady_clock::time_point now) const;
    
    bool should_corroborate_stall(const SubjectState& state, std::chrono::steady_clock::time_point now) const;
    
    void evaluate_and_generate_events(
        SubjectState& state,
        StallState previous_state,
        StallState current_state,
        std::chrono::system_clock::time_point assessment_time);
    
    std::string generate_event_id();
    std::string generate_alert_id();
    
    // Get subject ID from SubjectState (helper for event generation)
    std::string get_subject_id_from_state(const SubjectState& state) const;
};

// ============================================================================
// Factory functions
// ============================================================================

std::unique_ptr<StallDetector> make_stall_detector(
    const StallDetectorConfig& config = StallDetectorConfig{});

}  // namespace rebuntu::modules::hang_stall_jam