// rebuntu::modules::stability_monitor — System Stability Monitor (Phase 5.5)
//
// This module provides a foundational stability monitor that combines service/
// process/kernel/storage/resource observations into a conservative view of
// host stability.
//
// Design Philosophy:
//   * Monitoring ≠ recovery (this module observes, does not repair)
//   * UNKNOWN ≠ false (missing telemetry must be reported honestly)
//   * Evidence-based assessment, not heuristic scores

#pragma once

// Standard library headers
#include <chrono>
#include <memory>
#include <optional>
#include <string>
#include <vector>
#include <map>
#include <set>

// Rebuntu core contracts
#include <system/core/contracts.hpp>

// Our module types first (types must be declared before use)
namespace rebuntu::modules::stability_monitor {

    // Forward declarations
    struct StabilityAssessment;
    struct InternalAlert;
    struct SubsystemAssessment;

}

// Include our module header to get full type definitions
#include "types.hpp"

namespace rebuntu::modules::stability_monitor {

// ============================================================================
// StabilityMonitor — Main stability monitoring engine
//
// This class combines observations from various native Linux sources into a
// comprehensive stability assessment. It does NOT perform recovery actions;
// that belongs to Phase 12's recovery engine.
// ============================================================================

class StabilityMonitor {
public:
    explicit StabilityMonitor(StabilityMonitorConfig config);
    ~StabilityMonitor();
    
    // Lifecycle management
    rebuntu::core::Outcome start();
    rebuntu::core::Outcome stop();
    bool is_running() const { return running_; }
    
    // Configuration
    const StabilityMonitorConfig& config() const { return config_; }
    void set_config(const StabilityMonitorConfig& config);
    
    // Main assessment entry point - called periodically or on events
    StabilityAssessment assess_stability(
        std::chrono::system_clock::time_point assessment_time = std::chrono::system_clock::now());
    
    // Add observations from various sources
    void add_service_state_observation(
        const std::string& unit_name,
        bool is_active,
        int restart_count,
        std::chrono::system_clock::time_point observation_time);
    
    void add_kernel_event_observation(
        const rebuntu::core::Evidence& evidence,
        FailureClass failure_class = FailureClass::kNone,
        std::optional<std::string> subject = std::nullopt);
    
    void add_resource_observation(
        Subsystem subsystem,
        double value,
        std::chrono::system_clock::time_point observation_time);
    
    // Get current stability state
    StabilityState get_overall_state() const { return current_assessment_.state; }
    StabilityAssessment get_current_assessment() const { return current_assessment_; }
    
    // Get internal alerts (e.g., for triggering diagnostics)
    std::vector<InternalAlert> get_pending_alerts();
    void acknowledge_alert(const std::string& alert_id);
    
    // Metrics for monitoring the monitor itself
    struct MonitorMetrics {
        size_t assessments_performed = 0;
        size_t observations_received = 0;
        size_t alerts_generated = 0;
        std::chrono::system_clock::time_point started_at;
    };
    MonitorMetrics metrics() const;

private:
    StabilityMonitorConfig config_;
    
    bool running_ = false;
    std::optional<std::string> boot_id_;       // Filled by native source
    std::optional<std::string> machine_id_;    // Filled by native source
    
    // Observation buffers (bounded)
    struct ObservationBuffer {
        std::vector<rebuntu::core::Evidence> kernel_events;
        std::map<std::string, int> service_restart_counts;
        std::chrono::system_clock::time_point window_start;
    };
    std::unique_ptr<ObservationBuffer> buffer_;
    
    // Current assessment state
    StabilityAssessment current_assessment_;
    
    // Hysteresis state (prevents flapping)
    struct HysteresisState {
        std::optional<std::chrono::system_clock::time_point> hysteresis_start;
        StabilityState previous_state = StabilityState::kUnknown;
        bool active = false;
    };
    HysteresisState hysteresis_;
    
    // Internal alert tracking
    struct AlertRegistry {
        std::map<std::string, InternalAlert> pending_alerts;
        std::set<std::string> acknowledged_ids;
        size_t next_id_counter = 0;
    };
    std::unique_ptr<AlertRegistry> alerts_;
    
    // Metrics
    MonitorMetrics metrics_;
    
    // Assessment methods (private)
    SubsystemAssessment assess_systemd_services();
    SubsystemAssessment assess_kernel_events();
    SubsystemAssessment assess_resource_usage();
    StabilityState determine_overall_state(
        const std::map<Subsystem, SubsystemAssessment>& subsystems);
};

// ============================================================================
// Factory function
// ============================================================================

std::unique_ptr<StabilityMonitor> make_stability_monitor(
    const StabilityMonitorConfig& config = StabilityMonitorConfig{});

}  // namespace rebuntu::modules::stability_monitor