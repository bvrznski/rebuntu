// rebuntu::modules::health_monitor — Process & Service Health Monitor (Phase 5.6)
//
// This module provides health monitoring for processes and systemd services:
//   - Process states: running, crashed, stalled, crash-looping, unknown
//   - Service states: active, inactive, failed, restarting, ready, healthy, unhealthy
//   - Health dimensions: lifecycle, readiness, operational, resource, behavioral
//
// Design Philosophy:
//   * Health ≠ State (a service can be active but unhealthy)
//   * Running ≠ Ready ≠ Healthy (distinct orthogonal dimensions)
//   * UNKNOWN ≠ false (missing telemetry must be reported honestly)
//   * Monitoring ≠ recovery (this module observes, does not repair)

#pragma once

#include <memory>
#include <string>
#include <vector>
#include <map>
#include <optional>
#include <functional>
#include <mutex>

#include "types.hpp"

namespace rebuntu::modules::health_monitor {

// ============================================================================
// HealthMonitor — Main health monitoring engine
//
// This class combines observations from native Linux sources (procfs, systemd)
// into comprehensive health assessments. It does NOT perform recovery actions.
// ============================================================================

class HealthMonitor {
public:
    explicit HealthMonitor(HealthMonitorConfig config);
    ~HealthMonitor();
    
    // Lifecycle management
    core::Outcome start();
    core::Outcome stop();
    bool is_running() const { return running_; }
    
    // Configuration
    const HealthMonitorConfig& config() const { return config_; }
    void set_config(const HealthMonitorConfig& config);
    
    // Add process observations from procfs
    core::Outcome add_process_observation(
        const ProcessHealth& health,
        std::chrono::system_clock::time_point observation_time);
    
    // Add service observations from systemd
    core::Outcome add_service_observation(
        const ServiceHealth& health,
        std::chrono::system_clock::time_point observation_time);
    
    // Perform health assessment for a subject
    HealthAssessment assess_process_health(
        const std::string& pid,
        std::chrono::system_clock::time_point assessment_time = std::chrono::system_clock::now());
    
    HealthAssessment assess_service_health(
        const std::string& unit_name,
        std::chrono::system_clock::time_point assessment_time = std::chrono::system_clock::now());
    
    // Get current health state for a subject
    ServiceHealthState get_process_health_state(const std::string& pid) const;
    ServiceHealthState get_service_health_state(const std::string& unit_name) const;
    
    // Get all pending events (e.g., for diagnostics)
    std::vector<HealthEvent> get_pending_events();
    void acknowledge_event(const std::string& event_id);
    
    // Metrics for monitoring the monitor itself
    HealthMonitorMetrics metrics() const;

private:
    HealthMonitorConfig config_;
    
    bool running_ = false;
    mutable std::mutex mutex_;
    
    // Process health tracking (by PID)
    struct ProcessStateEntry {
        ProcessHealth last_health;
        std::chrono::system_clock::time_point observed_at;
        std::vector<std::string> evidence_ids;
        int crash_count_in_window = 0;
        std::optional<std::chrono::system_clock::time_point> first_crash_time;
    };
    std::map<std::string, ProcessStateEntry> process_states_;
    
    // Service health tracking (by unit name)
    struct ServiceStateEntry {
        ServiceHealth last_health;
        std::chrono::system_clock::time_point observed_at;
        int restart_count_in_window = 0;
        std::optional<std::chrono::system_clock::time_point> first_restart_time;
    };
    std::map<std::string, ServiceStateEntry> service_states_;
    
    // Event tracking
    struct EventRegistry {
        std::vector<HealthEvent> pending_events;
        std::set<std::string> acknowledged_ids;
        size_t next_event_id = 0;
    };
    std::unique_ptr<EventRegistry> events_;
    
    // Metrics
    HealthMonitorMetrics metrics_;
    
    // Assessment helpers
    ProcessHealth update_process_crash_behavior(const ProcessStateEntry& entry);
    ServiceHealth update_service_crash_behavior(const ServiceStateEntry& entry);
    
    void generate_health_events(
        const std::string& subject_id,
        SubjectType subject_type,
        ServiceHealthState old_state,
        ServiceHealthState new_state,
        const HealthAssessment& assessment);
};

// ============================================================================
// Factory function
// ============================================================================

std::unique_ptr<HealthMonitor> make_health_monitor(
    const HealthMonitorConfig& config = HealthMonitorConfig{});

}  // namespace rebuntu::modules::health_monitor