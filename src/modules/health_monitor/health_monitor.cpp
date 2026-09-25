// rebuntu::modules::health_monitor — Process & Service Health Monitor Implementation (Phase 5.6)
//
// This module provides health monitoring for processes and systemd services:
//   - Process states: running, crashed, stalled, crash-looping, unknown
//   - Service states: active, inactive, failed, restarting, ready, healthy, unhealthy
//   - Health dimensions: lifecycle, readiness, operational, resource, behavioral

#include "health_monitor.hpp"

#include <algorithm>
#include <sstream>

namespace rebuntu::modules::health_monitor {

// ============================================================================
// Internal helper functions
// ============================================================================

static std::string generate_event_id() {
    static size_t counter = 0;
    return "health-event-" + std::to_string(counter++);
}

static ServiceHealthState determine_overall_health(
    const std::vector<DimensionAssessment>& assessments) {
    
    int healthy_count = 0;
    int degraded_count = 0;
    int unhealthy_count = 0;
    int unknown_count = 0;
    
    for (const auto& assessment : assessments) {
        switch (assessment.state) {
            case ServiceHealthState::kHealthy:      healthy_count++; break;
            case ServiceHealthState::kDegraded:     degraded_count++; break;
            case ServiceHealthState::kUnhealthy:    unhealthy_count++; break;
            case ServiceHealthState::kUnknown:      unknown_count++; break;
        }
    }
    
    // Overall state logic:
    // - If any dimension is UNHEALTHY, overall is UNHEALTHY
    // - If any dimension is DEGRADED (and no UNHEALTHY), overall is DEGRADED
    // - If all dimensions are UNKNOWN, overall is UNKNOWN
    // - Otherwise, overall is HEALTHY
    
    if (unhealthy_count > 0) {
        return ServiceHealthState::kUnhealthy;
    }
    
    if (degraded_count > 0) {
        return ServiceHealthState::kDegraded;
    }
    
    if (unknown_count == static_cast<int>(assessments.size()) && assessments.size() > 0) {
        return ServiceHealthState::kUnknown;
    }
    
    return ServiceHealthState::kHealthy;
}

// ============================================================================
// Factory functions
// ============================================================================

ProcessHealth make_initial_process_health(const std::string& pid) {
    ProcessHealth health;
    health.pid = pid;
    health.state = ProcessState::kUnknown;
    health.health_state = ServiceHealthState::kUnknown;
    health.observed_at = std::chrono::system_clock::now();
    return health;
}

ServiceHealth make_initial_service_health(const std::string& unit_name) {
    ServiceHealth health;
    health.unit_name = unit_name;
    health.is_active = false;
    health.is_failed = false;
    health.health_state = ServiceHealthState::kUnknown;
    health.assessed_at = std::chrono::system_clock::now();
    return health;
}

// ============================================================================
// HealthMonitor implementation
// ============================================================================

HealthMonitor::HealthMonitor(HealthMonitorConfig config)
    : config_(std::move(config)),
      events_(std::make_unique<EventRegistry>()) {
    metrics_.started_at = std::chrono::system_clock::now();
}

HealthMonitor::~HealthMonitor() {
    if (running_) {
        stop();
    }
}

core::Outcome HealthMonitor::start() {
    if (running_) {
        return core::Outcome::success();
    }
    
    running_ = true;
    return core::Outcome::success();
}

core::Outcome HealthMonitor::stop() {
    if (!running_) {
        return core::Outcome::completed();
    }
    
    running_ = false;
    return core::Outcome::success();
}

void HealthMonitor::set_config(const HealthMonitorConfig& config) {
    std::lock_guard<std::mutex> lock(mutex_);
    config_ = config;
}

core::Outcome HealthMonitor::add_process_observation(
    const ProcessHealth& health,
    std::chrono::system_clock::time_point observation_time) {
    
    std::lock_guard<std::mutex> lock(mutex_);
    
    metrics_.observations_received++;
    metrics_.process_assessments++;
    
    auto it = process_states_.find(health.pid);
    if (it == process_states_.end()) {
        // New process
        ProcessStateEntry entry;
        entry.last_health = health;
        entry.observed_at = observation_time;
        
        // Track crashes in window
        if (health.state == ProcessState::kZombie || 
            health.restart_count > 0) {
            entry.first_crash_time = observation_time;
            entry.crash_count_in_window = health.restart_count + 1;
        }
        
        process_states_[health.pid] = entry;
    } else {
        // Update existing process
        auto& entry = it->second;
        entry.last_health = health;
        entry.observed_at = observation_time;
        
        // Track crashes
        if (health.state == ProcessState::kZombie ||
            health.restart_count > 0) {
            entry.crash_count_in_window++;
            if (!entry.first_crash_time.has_value()) {
                entry.first_crash_time = observation_time;
            }
        }
    }
    
    return core::Outcome::success();
}

core::Outcome HealthMonitor::add_service_observation(
    const ServiceHealth& health,
    std::chrono::system_clock::time_point observation_time) {
    
    std::lock_guard<std::mutex> lock(mutex_);
    
    metrics_.observations_received++;
    metrics_.service_assessments++;
    
    auto it = service_states_.find(health.unit_name);
    if (it == service_states_.end()) {
        // New service
        ServiceStateEntry entry;
        entry.last_health = health;
        entry.observed_at = observation_time;
        
        if (health.is_restarting || health.restart_count > 0) {
            entry.first_restart_time = observation_time;
            entry.restart_count_in_window = health.restart_count + 1;
        }
        
        service_states_[health.unit_name] = entry;
    } else {
        // Update existing service
        auto& entry = it->second;
        entry.last_health = health;
        entry.observed_at = observation_time;
        
        if (health.is_restarting || health.restart_count > 0) {
            entry.restart_count_in_window++;
            if (!entry.first_restart_time.has_value()) {
                entry.first_restart_time = observation_time;
            }
        }
    }
    
    return core::Outcome::success();
}

ProcessHealth HealthMonitor::update_process_crash_behavior(const ProcessStateEntry& entry) {
    ProcessHealth updated = entry.last_health;
    
    auto window_end = std::chrono::system_clock::now();
    auto window_start = window_end - 
        std::chrono::minutes(config_.crash_loop_window_minutes);
    
    // Check if we have enough crashes in the window
    if (entry.first_crash_time.has_value()) {
        auto crash_time = entry.first_crash_time.value();
        
        // If crashes started within our window and count exceeds threshold
        if (crash_time >= window_start && 
            entry.crash_count_in_window >= config_.process_crash_threshold) {
            
            updated.crash_behavior = CrashBehavior::kCrashLooping;
        } else if (entry.crash_count_in_window > 0) {
            updated.crash_behavior = CrashBehavior::kIntermittent;
        }
    } else if (updated.restart_count > 0 && 
               entry.crash_count_in_window >= config_.process_crash_threshold) {
        updated.crash_behavior = CrashBehavior::kCrashLooping;
    } else if (updated.restart_count > 0) {
        updated.crash_behavior = CrashBehavior::kIntermittent;
    }
    
    return updated;
}

ServiceHealth HealthMonitor::update_service_crash_behavior(const ServiceStateEntry& entry) {
    ServiceHealth updated = entry.last_health;
    
    auto window_end = std::chrono::system_clock::now();
    auto window_start = window_end - 
        std::chrono::minutes(config_.crash_loop_window_minutes);
    
    if (entry.first_restart_time.has_value()) {
        auto restart_time = entry.first_restart_time.value();
        
        if (restart_time >= window_start && 
            entry.restart_count_in_window >= config_.service_restart_threshold) {
            
            updated.crash_behavior = CrashBehavior::kCrashLooping;
        } else if (entry.restart_count_in_window > 0) {
            updated.crash_behavior = CrashBehavior::kIntermittent;
        }
    } else if (updated.restart_count > 0 && 
               entry.restart_count_in_window >= config_.service_restart_threshold) {
        updated.crash_behavior = CrashBehavior::kCrashLooping;
    } else if (updated.restart_count > 0) {
        updated.crash_behavior = CrashBehavior::kIntermittent;
    }
    
    return updated;
}

HealthAssessment HealthMonitor::assess_process_health(
    const std::string& pid,
    std::chrono::system_clock::time_point assessment_time) {
    
    std::lock_guard<std::mutex> lock(mutex_);
    
    metrics_.assessments_performed++;
    
    HealthAssessment assessment;
    assessment.subject_type = SubjectType::kProcess;
    assessment.subject_id = pid;
    assessment.assessed_at = assessment_time;
    
    auto it = process_states_.find(pid);
    if (it == process_states_.end()) {
        // No observations yet
        assessment.overall_state = ServiceHealthState::kUnknown;
        assessment.is_complete = false;
        assessment.uncertainty_notes.push_back("No observations for process " + pid);
        
        return assessment;
    }
    
    const auto& entry = it->second;
    ProcessHealth health = update_process_crash_behavior(entry);
    
    // Assess lifecycle dimension
    DimensionAssessment lifecycle_assessment;
    lifecycle_assessment.dimension = HealthDimension::kLifecycle;
    
    switch (health.state) {
        case ProcessState::kRunning:
            lifecycle_assessment.state = ServiceHealthState::kHealthy;
            break;
        case ProcessState::kZombie:
            lifecycle_assessment.state = ServiceHealthState::kUnhealthy;
            break;
        default:
            lifecycle_assessment.state = ServiceHealthState::kDegraded;
    }
    lifecycle_assessment.reason = "Process state: " + to_string(health.state);
    
    // Assess behavioral dimension
    DimensionAssessment behavioral_assessment;
    behavioral_assessment.dimension = HealthDimension::kBehavioral;
    behavioral_assessment.state = (health.crash_behavior == CrashBehavior::kCrashLooping) ?
        ServiceHealthState::kUnhealthy : ServiceHealthState::kHealthy;
    behavioral_assessment.reason = "Crash behavior: " + to_string(health.crash_behavior);
    
    // Assess resource dimension
    DimensionAssessment resource_assessment;
    resource_assessment.dimension = HealthDimension::kResource;
    
    if (health.resources.cpu_percent > config_.cpu_utilization_warning_percent ||
        health.resources.memory_percent > config_.memory_utilization_warning_percent) {
        resource_assessment.state = ServiceHealthState::kDegraded;
        resource_assessment.reason = "Resource usage exceeded thresholds";
    } else {
        resource_assessment.state = ServiceHealthState::kHealthy;
        resource_assessment.reason = "Resource usage within bounds";
    }
    
    // Build assessment vector
    std::vector<DimensionAssessment> assessments;
    assessments.push_back(lifecycle_assessment);
    assessments.push_back(behavioral_assessment);
    assessments.push_back(resource_assessment);
    
    health.assessments = assessments;
    
    // Determine overall state
    assessment.overall_state = determine_overall_health(assessments);
    
    // Populate dimension results
    for (const auto& dim : assessments) {
        HealthAssessment::DimensionResult result;
        result.dimension = dim.dimension;
        result.state = dim.state;
        result.reason = dim.reason;
        if (dim.state != ServiceHealthState::kHealthy) {
            result.passed_threshold = true;
        }
        assessment.dimensions.push_back(result);
    }
    
    // Update the stored health with assessments
    process_states_[pid].last_health = health;
    
    return assessment;
}

HealthAssessment HealthMonitor::assess_service_health(
    const std::string& unit_name,
    std::chrono::system_clock::time_point assessment_time) {
    
    std::lock_guard<std::mutex> lock(mutex_);
    
    metrics_.assessments_performed++;
    
    HealthAssessment assessment;
    assessment.subject_type = SubjectType::kService;
    assessment.subject_id = unit_name;
    assessment.assessed_at = assessment_time;
    
    auto it = service_states_.find(unit_name);
    if (it == service_states_.end()) {
        // No observations yet
        assessment.overall_state = ServiceHealthState::kUnknown;
        assessment.is_complete = false;
        assessment.uncertainty_notes.push_back("No observations for service " + unit_name);
        
        return assessment;
    }
    
    const auto& entry = it->second;
    ServiceHealth health = update_service_crash_behavior(entry);
    
    // Assess lifecycle dimension
    DimensionAssessment lifecycle_assessment;
    lifecycle_assessment.dimension = HealthDimension::kLifecycle;
    
    if (health.is_failed) {
        lifecycle_assessment.state = ServiceHealthState::kUnhealthy;
        lifecycle_assessment.reason = "Service failed";
    } else if (!health.is_active) {
        lifecycle_assessment.state = ServiceHealthState::kDegraded;
        lifecycle_assessment.reason = "Service not active";
    } else if (health.health_state == ServiceHealthState::kHealthy) {
        lifecycle_assessment.state = ServiceHealthState::kHealthy;
        lifecycle_assessment.reason = "Service healthy and active";
    } else {
        lifecycle_assessment.state = ServiceHealthState::kDegraded;
        lifecycle_assessment.reason = "Service has issues but not failed";
    }
    
    // Assess readiness dimension
    DimensionAssessment readiness_assessment;
    readiness_assessment.dimension = HealthDimension::kReadiness;
    
    if (health.is_ready) {
        readiness_assessment.state = ServiceHealthState::kHealthy;
        readiness_assessment.reason = "Service ready to accept requests";
    } else {
        readiness_assessment.state = ServiceHealthState::kDegraded;
        readiness_assessment.reason = "Service not yet ready";
    }
    
    // Assess behavioral dimension
    DimensionAssessment behavioral_assessment;
    behavioral_assessment.dimension = HealthDimension::kBehavioral;
    behavioral_assessment.state = (health.crash_behavior == CrashBehavior::kCrashLooping) ?
        ServiceHealthState::kUnhealthy : ServiceHealthState::kHealthy;
    behavioral_assessment.reason = "Restart behavior: " + to_string(health.crash_behavior);
    
    // Assess resource dimension
    DimensionAssessment resource_assessment;
    resource_assessment.dimension = HealthDimension::kResource;
    
    if (health.resources.cpu_percent > config_.cpu_utilization_warning_percent ||
        health.resources.memory_percent > config_.memory_utilization_warning_percent) {
        resource_assessment.state = ServiceHealthState::kDegraded;
        resource_assessment.reason = "Resource usage exceeded thresholds";
    } else {
        resource_assessment.state = ServiceHealthState::kHealthy;
        resource_assessment.reason = "Resource usage within bounds";
    }
    
    std::vector<DimensionAssessment> assessments;
    assessments.push_back(lifecycle_assessment);
    assessments.push_back(readiness_assessment);
    assessments.push_back(behavioral_assessment);
    assessments.push_back(resource_assessment);
    
    health.assessments = assessments;
    
    // Determine overall state
    assessment.overall_state = determine_overall_health(assessments);
    
    // Populate dimension results
    for (const auto& dim : assessments) {
        HealthAssessment::DimensionResult result;
        result.dimension = dim.dimension;
        result.state = dim.state;
        result.reason = dim.reason;
        if (dim.state != ServiceHealthState::kHealthy) {
            result.passed_threshold = true;
        }
        assessment.dimensions.push_back(result);
    }
    
    service_states_[unit_name].last_health = health;
    
    return assessment;
}

ServiceHealthState HealthMonitor::get_process_health_state(const std::string& pid) const {
    std::lock_guard<std::mutex> lock(mutex_);
    
    auto it = process_states_.find(pid);
    if (it == process_states_.end()) {
        return ServiceHealthState::kUnknown;
    }
    
    // Return the current assessment (could be stale)
    return it->second.last_health.health_state;
}

ServiceHealthState HealthMonitor::get_service_health_state(const std::string& unit_name) const {
    std::lock_guard<std::mutex> lock(mutex_);
    
    auto it = service_states_.find(unit_name);
    if (it == service_states_.end()) {
        return ServiceHealthState::kUnknown;
    }
    
    return it->second.last_health.health_state;
}

std::vector<HealthEvent> HealthMonitor::get_pending_events() {
    std::lock_guard<std::mutex> lock(mutex_);
    
    std::vector<HealthEvent> result;
    
    for (const auto& event : events_->pending_events) {
        if (events_->acknowledged_ids.find(event.event_id) == 
            events_->acknowledged_ids.end()) {
            result.push_back(event);
        }
    }
    
    return result;
}

void HealthMonitor::acknowledge_event(const std::string& event_id) {
    std::lock_guard<std::mutex> lock(mutex_);
    events_->acknowledged_ids.insert(event_id);
}

HealthMonitorMetrics HealthMonitor::metrics() const {
    std::lock_guard<std::mutex> lock(mutex_);
    return metrics_;
}

// ============================================================================
// Factory function
// ============================================================================

std::unique_ptr<HealthMonitor> make_health_monitor(
    const HealthMonitorConfig& config) {
    return std::make_unique<HealthMonitor>(config);
}

}  // namespace rebuntu::modules::health_monitor