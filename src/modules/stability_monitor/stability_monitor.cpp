// rebuntu::modules::stability_monitor — System Stability Monitor Implementation (Phase 5.5)
//
// This module provides a foundational stability monitor that combines service/
// process/kernel/storage/resource observations into a conservative view of
// host stability.

#include "stability_monitor.hpp"

#include <algorithm>
#include <sstream>

namespace rebuntu::modules::stability_monitor {

// ============================================================================
// Internal helper functions
// ============================================================================

static std::string generate_alert_id() {
    static size_t counter = 0;
    return "alert-" + std::to_string(counter++);
}

static std::string format_time_window(
    std::chrono::system_clock::time_point start,
    std::chrono::system_clock::time_point end) {
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - start);
    return std::to_string(duration.count()) + "s";
}

// ============================================================================
// ObservationBuffer implementation
// ============================================================================

ObservationBuffer::ObservationBuffer()
    : window_start(std::chrono::system_clock::now()) {}

// ============================================================================
// StabilityMonitor implementation
// ============================================================================

StabilityMonitor::StabilityMonitor(StabilityMonitorConfig config)
    : config_(std::move(config)),
      buffer_(std::make_unique<ObservationBuffer>()),
      alerts_(std::make_unique<AlertRegistry>()) {
    metrics_.started_at = std::chrono::system_clock::now();
}

StabilityMonitor::~StabilityMonitor() {
    if (running_) {
        stop();
    }
}

core::Outcome StabilityMonitor::start() {
    if (running_) {
        return core::Outcome::success();
    }
    
    // Get boot ID from native source
    std::ifstream release_file("/proc/sys/kernel/random/boot_id");
    if (release_file.is_open()) {
        std::getline(release_file, boot_id_.value());
    }
    
    // Get machine ID from native source
    std::ifstream machine_file("/etc/machine-id");
    if (machine_file.is_open()) {
        std::getline(machine_file, machine_id_.value());
    }
    
    running_ = true;
    return core::Outcome::success();
}

core::Outcome StabilityMonitor::stop() {
    if (!running_) {
        return core::Outcome::completed();
    }
    
    running_ = false;
    return core::Outcome::success();
}

void StabilityMonitor::set_config(const StabilityMonitorConfig& config) {
    config_ = config;
}

StabilityAssessment StabilityMonitor::assess_stability(
    std::chrono::system_clock::time_point assessment_time) {
    
    // Build subsystem assessments
    auto systemd_assessment = assess_systemd_services();
    auto kernel_assessment = assess_kernel_events();
    auto resource_assessment = assess_resource_usage();
    
    // Collect all subsystem assessments
    std::map<Subsystem, SubsystemAssessment> all_subsystems;
    all_subsystems[Subsystem::kSystemdServices] = systemd_assessment;
    all_subsystems[Subsystem::kKernelEvents] = kernel_assessment;
    all_subsystems[Subsystem::kCpuResource] = resource_assessment;
    
    // Determine overall state
    StabilityState overall_state = determine_overall_state(all_subsystems);
    
    // Apply hysteresis to prevent flapping
    bool hysteresis_active = false;
    if (hysteresis_.active) {
        auto elapsed = assessment_time - hysteresis_.hysteresis_start.value();
        if (elapsed > std::chrono::minutes(config_.hysteresis_interval_minutes)) {
            hysteresis_.active = false;
            hysteresis_.previous_state = current_assessment_.state;
        } else {
            hysteresis_active = true;
        }
    }
    
    // Build assessment result
    StabilityAssessment result;
    result.state = overall_state;
    result.subsystems = all_subsystems;
    result.total_subsystems_assessed = static_cast<int>(all_subsystems.size());
    
    // Count subsystems with issues (degraded or unstable)
    for (const auto& [subsys, assessment] : all_subsystems) {
        if (assessment.state != StabilityState::kStable && 
            assessment.state != StabilityState::kUnknown) {
            result.subsystems_with_issues++;
        }
        for (const auto& dim : assessment.dimensions) {
            result.total_events_observed += dim.count;
        }
    }
    
    result.assessed_at = assessment_time;
    result.boot_id = boot_id_;
    result.machine_id = machine_id_;
    
    // Set evaluation window
    if (buffer_) {
        result.evaluation_window_start = buffer_->window_start;
        result.evaluation_window_end = assessment_time;
    }
    
    // Hysteresis state
    result.hysteresis_active = hysteresis_active;
    if (hysteresis_active) {
        result.hysteresis_started_at = hysteresis_.hysteresis_start;
    }
    
    current_assessment_ = result;
    metrics_.assessments_performed++;
    
    return result;
}

SubsystemAssessment StabilityMonitor::assess_systemd_services() {
    SubsystemAssessment assessment;
    assessment.subsystem = Subsystem::kSystemdServices;
    
    // Check service restart counts in the window
    if (buffer_ && buffer_->service_restart_counts.empty()) {
        assessment.state = StabilityState::kUnknown;
        return assessment;
    }
    
    int total_restarts = 0;
    for (const auto& [unit, count] : buffer_->service_restart_counts) {
        total_restarts += count;
        
        // Add affected subject
        assessment.affected_subjects.insert(unit);
        
        // Record restart as dimension
        StabilityDimension dim;
        dim.name = "restart_count";
        dim.count = count;
        dim.state = (count >= config_.service_restart_threshold) ? 
            StabilityState::kDegraded : StabilityState::kStable;
        dim.threshold_count = config_.service_restart_threshold;
        
        if (dim.state == StabilityState::kDegraded) {
            std::ostringstream reason;
            reason << unit << " restarted " << count << " times (threshold: " 
                   << config_.service_restart_threshold << ")";
            dim.assessment_reason = reason.str();
        }
        
        assessment.dimensions.push_back(dim);
    }
    
    // Determine state based on restart counts
    if (total_restarts == 0) {
        assessment.state = StabilityState::kStable;
    } else if (total_restarts < config_.service_restart_threshold * 
               std::max(1, static_cast<int>(buffer_->service_restart_counts.size()))) {
        assessment.state = StabilityState::kDegraded;
    } else {
        assessment.state = StabilityState::kUnstable;
    }
    
    // Record primary failure class
    if (!assessment.affected_subjects.empty()) {
        assessment.primary_failure_class = "service-failure";
    }
    
    return assessment;
}

SubsystemAssessment StabilityMonitor::assess_kernel_events() {
    SubsystemAssessment assessment;
    assessment.subsystem = Subsystem::kKernelEvents;
    
    // Check kernel events in buffer
    if (!buffer_ || buffer_->kernel_events.empty()) {
        assessment.state = StabilityState::kUnknown;
        return assessment;
    }
    
    int error_count = 0;
    for (const auto& evidence : buffer_->kernel_events) {
        // Count error-level events
        error_count++;
        
        StabilityDimension dim;
        dim.name = "kernel_event";
        dim.count = 1;
        dim.state = StabilityState::kStable;  // Each event is just observed
        
        // Extract failure class if present in evidence
        if (evidence.value.find("error") != std::string::npos) {
            dim.state = StabilityState::kDegraded;
            dim.assessment_reason = "Kernel error detected";
        }
        
        assessment.dimensions.push_back(dim);
    }
    
    // Determine state based on error count
    if (error_count == 0) {
        assessment.state = StabilityState::kStable;
    } else if (error_count < config_.kernel_error_rate_threshold) {
        assessment.state = StabilityState::kDegraded;
    } else {
        assessment.state = StabilityState::kUnstable;
    }
    
    return assessment;
}

SubsystemAssessment StabilityMonitor::assess_resource_usage() {
    SubsystemAssessment assessment;
    assessment.subsystem = Subsystem::kCpuResource;
    
    // For now, return UNKNOWN as we need actual procfs data
    assessment.state = StabilityState::kUnknown;
    assessment.uncertainty_notes.push_back("Resource monitoring data not yet acquired");
    
    return assessment;
}

StabilityState StabilityMonitor::determine_overall_state(
    const std::map<Subsystem, SubsystemAssessment>& subsystems) {
    
    // Count subsystems in each state
    int stable_count = 0;
    int degraded_count = 0;
    int unstable_count = 0;
    int unknown_count = 0;
    
    for (const auto& [subsys, assessment] : subsystems) {
        switch (assessment.state) {
            case StabilityState::kStable:      stable_count++; break;
            case StabilityState::kDegraded:    degraded_count++; break;
            case StabilityState::kUnstable:    unstable_count++; break;
            case StabilityState::kUnknown:     unknown_count++; break;
        }
    }
    
    // Overall state logic:
    // - If any subsystem is UNSTABLE, overall is UNSTABLE
    // - If any subsystem is DEGRADED (and no UNSTABLE), overall is DEGRADED
    // - If all systems are UNKNOWN, overall is UNKNOWN
    // - Otherwise, overall is STABLE
    
    if (unstable_count > 0) {
        return StabilityState::kUnstable;
    }
    
    if (degraded_count > 0) {
        return StabilityState::kDegraded;
    }
    
    if (unknown_count > 0 && degraded_count == 0 && unstable_count == 0) {
        // Only UNKNOWN if some data is missing
        return StabilityState::kUnknown;
    }
    
    return StabilityState::kStable;
}

void StabilityMonitor::add_service_state_observation(
    const std::string& unit_name,
    bool is_active,
    int restart_count,
    std::chrono::system_clock::time_point observation_time) {
    
    if (!buffer_) return;
    
    metrics_.observations_received++;
    
    // Update restart count in buffer
    buffer_->service_restart_counts[unit_name] = restart_count;
}

void StabilityMonitor::add_kernel_event_observation(
    const core::Evidence& evidence,
    FailureClass failure_class,
    std::optional<std::string> subject) {
    
    if (!buffer_) return;
    
    metrics_.observations_received++;
    
    // Store in buffer for later assessment
    buffer_->kernel_events.push_back(evidence);
}

void StabilityMonitor::add_resource_observation(
    Subsystem subsystem,
    double value,
    std::chrono::system_clock::time_point observation_time) {
    
    metrics_.observations_received++;
    // TODO: Implement resource observation storage and assessment
}

std::vector<InternalAlert> StabilityMonitor::get_pending_alerts() {
    std::vector<InternalAlert> alerts;
    
    // Generate alerts based on current state
    if (current_assessment_.state == StabilityState::kDegraded ||
        current_assessment_.state == StabilityState::kUnstable) {
        
        InternalAlert alert;
        alert.id = generate_alert_id();
        alert.created_at = std::chrono::system_clock::now();
        alert.severity = (current_assessment_.state == StabilityState::kUnstable) ?
            InternalAlert::Severity::kCritical : InternalAlert::Severity::kMedium;
        
        // Collect failure classes from subsystems
        for (const auto& [subsys, assessment] : current_assessment_.subsystems) {
            if (assessment.primary_failure_class.has_value()) {
                alert.affected_subjects.push_back(assessment.primary_failure_class.value());
            }
            for (const auto& dim : assessment.dimensions) {
                for (const auto& evidence : dim.evidence) {
                    alert.evidence.push_back(evidence);
                }
            }
        }
        
        std::ostringstream summary;
        summary << "System stability: " << to_string(current_assessment_.state);
        if (!current_assessment_.affected_subjects.empty()) {
            summary << " - affected subsystems: ";
            bool first = true;
            for (const auto& subject : current_assessment_.affected_subjects) {
                if (!first) summary << ", ";
                summary << subject;
                first = false;
            }
        }
        alert.summary = summary.str();
        
        alerts.push_back(alert);
    }
    
    return alerts;
}

void StabilityMonitor::acknowledge_alert(const std::string& alert_id) {
    if (alerts_) {
        alerts_->acknowledged_ids.insert(alert_id);
    }
}

StabilityMonitor::MonitorMetrics StabilityMonitor::metrics() const {
    return metrics_;
}

// ============================================================================
// Factory function
// ============================================================================

std::unique_ptr<StabilityMonitor> make_stability_monitor(
    const StabilityMonitorConfig& config) {
    return std::make_unique<StabilityMonitor>(config);
}

}  // namespace rebuntu::modules::stability_monitor