// rebuntu::modules::hang_stall_jam — Stall Detector Implementation (Phase 5.11)
//
// This module provides evidence-based detection of hangs, stalls and jams across
// processes/services and runtime work units in Rebuntu.

#include "stall_detector.hpp"

#include <system/core/contracts.hpp>
#include <runtime/contracts.hpp>

#include <chrono>
#include <sstream>
#include <iomanip>

namespace rebuntu::modules::hang_stall_jam {

// ============================================================================
// StallDetector — Implementation
// ============================================================================

StallDetector::StallDetector(StallDetectorConfig config)
    : config_(std::move(config)),
      events_(std::make_unique<EventRegistry>()),
      alerts_(std::make_unique<AlertRegistry>()) {
    // started_at is initialized in StallDetectorMetrics default constructor
}

StallDetector::~StallDetector() {
    stop();
}

core::Outcome StallDetector::start() {
    std::lock_guard<std::mutex> lock(mutex_);
    
    if (running_) {
        return core::Outcome::failure("E_ALREADY_STARTED", "Stall detector is already started");
    }
    
    running_ = true;
    
    return core::Outcome::success();
}

core::Outcome StallDetector::stop() {
    std::lock_guard<std::mutex> lock(mutex_);
    
    if (!running_) {
        return core::Outcome::completed();
    }
    
    running_ = false;
    
    // Clear all subject states to release memory
    subject_states_.clear();
    
    return core::Outcome::success();
}

void StallDetector::set_config(const StallDetectorConfig& config) {
    std::lock_guard<std::mutex> lock(mutex_);
    config_ = config;
}

core::Outcome StallDetector::add_process_heartbeat(
    const std::string& pid,
    int64_t sequence,
    std::chrono::steady_clock::time_point timestamp,
    std::chrono::system_clock::time_point observed_at) {
    
    std::lock_guard<std::mutex> lock(mutex_);
    
    metrics_.observations_received++;
    metrics_.assessments_by_subject_type[SubjectType::kProcess]++;
    
    auto& state = subject_states_[pid];
    state.type = SubjectType::kProcess;
    state.recent_evidence.push_back({
        EvidenceType::kHeartbeat,
        sequence,
        timestamp,
        observed_at
    });
    
    // Trim old evidence if needed
    while (state.recent_evidence.size() > config_.max_evidence_per_subject) {
        state.recent_evidence.erase(state.recent_evidence.begin());
    }
    
    // Update progress window
    auto now_steady = std::chrono::steady_clock::now();
    if (!state.current_window.has_value()) {
        state.current_window.emplace();
        state.current_window->window_start = timestamp;
    }
    
    if (state.current_window) {
        state.current_window->evidence_counts[EvidenceType::kHeartbeat]++;
        state.current_window->last_observation[EvidenceType::kHeartbeat] = timestamp;
    }
    
    // Evaluate stall state
    StallState old_state = get_subject_stall_state(pid, SubjectType::kProcess);
    evaluate_and_generate_events(state, old_state, old_state, observed_at);
    
    metrics_.assessments_performed++;
    
    return core::Outcome::completed();
}

core::Outcome StallDetector::add_service_progress(
    const std::string& unit_name,
    EvidenceType evidence_type,
    int64_t sequence,
    std::chrono::steady_clock::time_point timestamp,
    std::chrono::system_clock::time_point observed_at) {
    
    std::lock_guard<std::mutex> lock(mutex_);
    
    metrics_.observations_received++;
    metrics_.assessments_by_subject_type[SubjectType::kService]++;
    
    auto& state = subject_states_[unit_name];
    state.type = SubjectType::kService;
    state.recent_evidence.push_back({
        evidence_type,
        sequence,
        timestamp,
        observed_at
    });
    
    // Trim old evidence if needed
    while (state.recent_evidence.size() > config_.max_evidence_per_subject) {
        state.recent_evidence.erase(state.recent_evidence.begin());
    }
    
    // Update progress window
    auto now_steady = std::chrono::steady_clock::now();
    if (!state.current_window.has_value()) {
        state.current_window.emplace();
        state.current_window->window_start = timestamp;
    }
    
    if (state.current_window) {
        state.current_window->evidence_counts[evidence_type]++;
        state.current_window->last_observation[evidence_type] = timestamp;
    }
    
    // Evaluate stall state
    StallState old_state = get_subject_stall_state(unit_name, SubjectType::kService);
    evaluate_and_generate_events(state, old_state, old_state, observed_at);
    
    metrics_.assessments_performed++;
    
    return core::Outcome::completed();
}

core::Outcome StallDetector::add_work_unit_progress(const WorkUnitProgress& progress) {
    std::lock_guard<std::mutex> lock(mutex_);
    
    metrics_.observations_received++;
    metrics_.assessments_by_subject_type[SubjectType::kRuntimeWorkUnit]++;
    
    auto& state = subject_states_[progress.work_unit_id];
    state.type = SubjectType::kRuntimeWorkUnit;
    state.recent_evidence.push_back({
        EvidenceType::kHeartbeat,
        progress.current_sequence,
        progress.last_heartbeat,
        std::chrono::system_clock::now()
    });
    
    // Trim old evidence if needed
    while (state.recent_evidence.size() > config_.max_evidence_per_subject) {
        state.recent_evidence.erase(state.recent_evidence.begin());
    }
    
    // Evaluate stall state
    StallState old_state = get_subject_stall_state(
        progress.work_unit_id, SubjectType::kRuntimeWorkUnit);
    evaluate_and_generate_events(state, old_state, old_state, 
                                 std::chrono::system_clock::now());
    
    metrics_.assessments_performed++;
    
    return core::Outcome::completed();
}

StallAssessment StallDetector::assess_stall_state(
    const std::string& subject_id,
    SubjectType subject_type,
    std::chrono::system_clock::time_point assessment_time) {
    
    std::lock_guard<std::mutex> lock(mutex_);
    
    metrics_.assessments_performed++;
    
    auto it = subject_states_.find(subject_id);
    if (it == subject_states_.end()) {
        // No evidence yet - return default state
        StallAssessment result;
        result.subject_type = subject_type;
        result.subject_id = subject_id;
        result.state = StallState::kNormal;
        result.assessed_at = assessment_time;
        result.is_complete = false;  // Not enough data yet
        result.uncertainty_notes.push_back("No progress evidence received yet");
        return result;
    }
    
    const auto& state = it->second;
    StallAssessment result;
    result.subject_type = subject_type;
    result.subject_id = subject_id;
    result.assessed_at = assessment_time;
    
    // Get current stall state
    result.state = get_subject_stall_state(subject_id, subject_type);
    
    // Build progress window analysis
    if (state.current_window) {
        result.active_window.emplace();
        result.active_window->window_start = state.current_window->window_start;
        
        for (const auto& [type, count] : state.current_window->evidence_counts) {
            // Use find instead of operator[] to avoid const-correctness issues
            auto obs_it = state.current_window->last_observation.find(type);
            result.active_window->observed_progress.push_back({
                type,
                count,
                obs_it != state.current_window->last_observation.end() ? 
                    obs_it->second : std::chrono::steady_clock::time_point{}
            });
        }
    }
    
    // Analyze signals
    if (!state.recent_evidence.empty()) {
        std::chrono::steady_clock::time_point latest_time = 
            state.recent_evidence.back().monotonic_time;
        
        auto now_steady = std::chrono::steady_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(
            now_steady - latest_time);
        
        // Check for missing heartbeats
        if (elapsed > config_.stall_suspicion_window) {
            result.signal_analyses.push_back({
                EvidenceType::kHeartbeat,
                0,  // expected count
                static_cast<int64_t>(state.recent_evidence.size()),
                false,  // doesn't meet threshold
                "No heartbeat observed for " + std::to_string(elapsed.count()) + "ms"
            });
            
            result.suspicion_reasons.push_back({
                EvidenceType::kHeartbeat,
                elapsed,
                "Progress evidence has not been received within the suspicion window"
            });
        }
    }
    
    // Set completeness
    if (state.recent_evidence.size() >= config_.max_evidence_per_subject) {
        result.is_complete = false;
        result.uncertainty_notes.push_back("Evidence was trimmed due to retention limit");
    }
    
    return result;
}

StallState StallDetector::get_subject_stall_state(
    const std::string& subject_id,
    SubjectType subject_type) const {
    
    auto it = subject_states_.find(subject_id);
    if (it == subject_states_.end()) {
        return StallState::kNormal;  // No evidence yet
    }
    
    const auto& state = it->second;
    
    if (!state.recent_evidence.empty()) {
        auto now_steady = std::chrono::steady_clock::now();
        
        // Get the most recent monotonic timestamp
        auto latest_time = state.recent_evidence.back().monotonic_time;
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(
            now_steady - latest_time);
        
        if (elapsed > config_.corroborated_stall_window) {
            return StallState::kCorroboratedStall;
        } else if (elapsed > config_.stall_suspicion_window) {
            return StallState::kSuspectedStall;
        }
    }
    
    return StallState::kNormal;
}

std::vector<StallEvent> StallDetector::get_pending_events() {
    std::lock_guard<std::mutex> lock(mutex_);
    
    std::vector<StallEvent> result;
    for (const auto& event : events_->pending_events) {
        if (events_->acknowledged_ids.find(event.event_id) == 
            events_->acknowledged_ids.end()) {
            result.push_back(event);
        }
    }
    
    return result;
}

void StallDetector::acknowledge_event(const std::string& event_id) {
    std::lock_guard<std::mutex> lock(mutex_);
    events_->acknowledged_ids.insert(event_id);
}

std::vector<InternalAlert> StallDetector::get_alerts() {
    std::lock_guard<std::mutex> lock(mutex_);
    
    std::vector<InternalAlert> result;
    for (const auto& [id, alert] : alerts_->active_alerts) {
        if (!alert.is_new_occurrence || 
            (alert.hysteresis_window_start.has_value() && 
             std::chrono::system_clock::now() - *alert.hysteresis_window_start > 
             config_.stall_suspicion_window)) {
            result.push_back(alert);
        }
    }
    
    return result;
}

StallDetectorMetrics StallDetector::metrics() const {
    std::lock_guard<std::mutex> lock(mutex_);
    return metrics_;
}

// ============================================================================
// Helper Methods
// ============================================================================

void StallDetector::update_state_timeline(
    SubjectState& state,
    StallState new_state,
    std::chrono::system_clock::time_point timestamp) {
    
    if (!state.state_timeline.empty()) {
        auto last_state = state.state_timeline.back().second;
        if (last_state == new_state) {
            return;  // No change
        }
    }
    
    state.state_timeline.emplace_back(timestamp, new_state);
    state.last_state_change_monotonic = std::chrono::steady_clock::now();
}

bool StallDetector::should_suspect_stall(
    const SubjectState& state,
    std::chrono::steady_clock::time_point now) const {
    
    if (state.recent_evidence.empty()) {
        return false;  // No evidence yet
    }
    
    auto latest_time = state.recent_evidence.back().monotonic_time;
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(
        now - latest_time);
    
    return elapsed > config_.stall_suspicion_window;
}

bool StallDetector::should_corroborate_stall(
    const SubjectState& state,
    std::chrono::steady_clock::time_point now) const {
    
    if (state.recent_evidence.empty()) {
        return false;  // No evidence yet
    }
    
    auto latest_time = state.recent_evidence.back().monotonic_time;
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(
        now - latest_time);
    
    return elapsed > config_.corroborated_stall_window;
}

void StallDetector::evaluate_and_generate_events(
    SubjectState& state,
    StallState previous_state,
    StallState current_state,
    std::chrono::system_clock::time_point assessment_time) {
    
    if (previous_state == current_state) {
        return;  // No state change
    }
    
    StallEvent event;
    event.event_id = generate_event_id();
    event.timestamp = assessment_time;
    event.subject_type = state.type;
    event.subject_id = get_subject_id_from_state(state);
    event.previous_state = previous_state;
    event.current_state = current_state;
    
    // Generate appropriate event type based on transition
    if (current_state == StallState::kSuspectedStall && 
        previous_state == StallState::kNormal) {
        event.event_type = StallEvent::EventType::kSuspectedStall;
        event.description = "Subject suspected of being stalled";
    } else if (current_state == StallState::kCorroboratedStall &&
               previous_state != StallState::kCorroboratedStall) {
        event.event_type = StallEvent::EventType::kCorroboratedStall;
        event.description = "Subject confirmed as stalled (multiple signals)";
    } else if (current_state == StallState::kNormal &&
               previous_state != StallState::kNormal) {
        event.event_type = StallEvent::EventType::kRecoveredFromStall;
        event.description = "Subject recovered from stall state";
    }
    
    events_->pending_events.push_back(event);
    metrics_.events_generated++;
}

std::string StallDetector::generate_event_id() {
    std::ostringstream oss;
    oss << "stall-evt-" << events_->next_event_id++;
    return oss.str();
}

std::string StallDetector::generate_alert_id() {
    std::ostringstream oss;
    oss << "stall-alert-" << alerts_->next_alert_id++;
    return oss.str();
}

std::string StallDetector::get_subject_id_from_state(const SubjectState& state) const {
    // Find the subject ID from subject_states_ map
    for (const auto& [id, s] : subject_states_) {
        if (&s == &state) {
            return id;
        }
    }
    return "<unknown>";
}

// ============================================================================
// Factory Functions
// ============================================================================

std::unique_ptr<StallDetector> make_stall_detector(
    const StallDetectorConfig& config) {
    return std::make_unique<StallDetector>(config);
}

}  // namespace rebuntu::modules::hang_stall_jam