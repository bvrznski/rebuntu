// rebuntu::modules::health_monitor::adapters — Journald Observer Adapter Implementation (Phase 5.6)

#include "journald_observer.hpp"

namespace rebuntu::modules::health_monitor::adapters {

JournaldObserver::JournaldObserver(HealthMonitorConfig config)
    : config_(std::move(config)) {}

JournaldObserver::~JournaldObserver() {
    if (running_) {
        stop();
    }
}

core::Outcome JournaldObserver::start() {
    if (running_) {
        return core::Outcome::success();
    }
    
    running_ = true;
    return core::Outcome::success();
}

core::Outcome JournaldObserver::stop() {
    if (!running_) {
        return core::Outcome::completed();
    }
    
    running_ = false;
    unit_states_.clear();
    return core::Outcome::success();
}

void JournaldObserver::set_health_callback(
    std::function<void(const ServiceHealth&)> callback) {
    health_callback_ = std::move(callback);
}

core::Outcome JournaldObserver::process_journal_event(
    const rebuntu::adapters::NormalizedEvent& event,
    std::chrono::system_clock::time_point observation_time) {
    
    if (!running_) {
        return core::Outcome();
    }
    
    // Extract systemd unit name from the normalized event
    const auto& raw_event = event.event;
    
    std::string unit_name;
    
    // Try to extract unit name from subject field
    if (raw_event.subject.has_value()) {
        unit_name = raw_event.subject.value();
    } else {
        return core::Outcome();  // Not a systemd-specific event
    }
    
    if (unit_name.empty()) {
        return core::Outcome();
    }
    
    // Process the systemd unit event
    return process_systemd_unit_event(event, observation_time);
}

core::Outcome JournaldObserver::process_systemd_unit_event(
    const rebuntu::adapters::NormalizedEvent& event,
    std::chrono::system_clock::time_point observation_time) {
    
    // Check for systemd-specific event types in the evidence
    bool is_failed = false;
    bool is_stopped = false;
    bool is_active = false;
    
    const auto& raw_event = event.event;
    
    for (const auto& ev : raw_event.evidence) {
        const std::string& message = ev.value;
        
        if (message.find("entered failed state") != std::string::npos ||
            message.find("Failed to start") != std::string::npos ||
            message.find("Main process exited with status") != std::string::npos) {
            is_failed = true;
        }
        
        if (message.find("Stopped") != std::string::npos &&
            message.find("Service") != std::string::npos) {
            is_stopped = true;
        }
        
        if (message.find("Started") != std::string::npos ||
            message.find("Running") != std::string::npos) {
            is_active = true;
        }
    }
    
    // Update unit state
    UnitState& state = unit_states_[raw_event.subject.value_or("")];
    
    if (is_failed) {
        state.failed_once = true;
    }
    
    if (is_stopped && !is_active) {
        // Service stopped unexpectedly
        state.restart_count++;
        if (!state.first_restart_time.has_value()) {
            state.first_restart_time = observation_time;
        }
    } else if (is_active && !is_stopped) {
        // Service started successfully, reset crash indicators
        state.failed_once = false;
        state.restart_count = 0;
        state.first_restart_time.reset();
    }
    
    // Check for crash loop condition
    bool is_crash_loop = is_in_crash_loop(state);
    
    // If we have a health callback, report the service health
    if (health_callback_ && raw_event.subject.has_value()) {
        ServiceHealth service_health;
        service_health.unit_name = raw_event.subject.value();
        
        if (is_failed) {
            service_health.health_state = ServiceHealthState::kUnhealthy;
            service_health.is_failed = true;
        } else if (!state.failed_once && state.restart_count == 0) {
            service_health.health_state = ServiceHealthState::kHealthy;
            service_health.is_active = is_active;
        } else if (is_crash_loop) {
            service_health.health_state = ServiceHealthState::kUnhealthy;
            service_health.crash_behavior = CrashBehavior::kCrashLooping;
            service_health.restart_count = state.restart_count;
        } else {
            service_health.health_state = ServiceHealthState::kDegraded;
            service_health.is_active = is_active;
            service_health.restart_count = state.restart_count;
            service_health.crash_behavior = CrashBehavior::kIntermittent;
        }
        
        health_callback_(service_health);
    }
    
    return core::Outcome();
}

bool JournaldObserver::is_in_crash_loop(const UnitState& state) const {
    if (!state.first_restart_time.has_value()) {
        return false;
    }
    
    auto now = std::chrono::system_clock::now();
    auto elapsed = now - state.first_restart_time.value();
    
    // Convert config minutes to duration for comparison
    auto window_duration = std::chrono::minutes(config_.crash_loop_window_minutes);
    
    return (elapsed <= window_duration) && 
           (state.restart_count >= config_.service_restart_threshold);
}

std::unique_ptr<JournaldObserver> make_journald_observer(
    const HealthMonitorConfig& config) {
    return std::make_unique<JournaldObserver>(config);
}

}  // namespace rebuntu::modules::health_monitor::adapters