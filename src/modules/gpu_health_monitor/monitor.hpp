// rebuntu::modules::gpu_health_monitor — GPU Health Monitor (Phase 5.10)
//
// This module provides comprehensive GPU health monitoring for Rebuntu:
//   - Device presence and identity (UUID, PCI bus ID)
//   - Driver state and reachability
//   - Utilization (memory, graphics, encoder, decoder)
//   - Temperature, power draw, clocks
//   - ECC errors where supported
//   - Display ownership
//
// Design Philosophy:
//   * Monitoring ≠ Recovery (this module observes, does not repair)
//   * UNKNOWN != false (missing telemetry must be reported honestly)
//   * Evidence-based assessment, not heuristic scores
//   * Provider architecture for multiple backends

#pragma once

#include <memory>
#include <chrono>
#include <string>
#include <vector>
#include <map>
#include <set>

// Rebuntu core contracts first
#include <system/core/contracts.hpp>

#include "types.hpp"

namespace rebuntu::modules::gpu_health_monitor {

// ============================================================================
// GPUMonitor — Main GPU monitoring engine
//
// This class collects and assesses GPU state from native Linux sources.
// ============================================================================

class GPUMonitor {
public:
    explicit GPUMonitor(GPUMonitorConfig config);
    ~GPUMonitor();
    
    // Lifecycle management
    core::Outcome start();
    core::Outcome stop();
    bool is_running() const { return running_; }
    
    // Configuration
    const GPUMonitorConfig& config() const { return config_; }
    void set_config(const GPUMonitorConfig& config);
    
    // Main assessment entry point
    GPUMonitorResult assess_gpu_health(
        std::chrono::system_clock::time_point assessment_time = std::chrono::system_clock::now());
    
    // Get current assessments
    GPUAssessment get_assessment() const { return assessment_; }
    
    // Get pending events (e.g., for triggering diagnostics)
    std::vector<GPUEvent> get_pending_events();
    void acknowledge_event(const std::string& event_id);
    
    // Metrics
    GPUMonitorMetrics metrics() const;
    
private:
    GPUMonitorConfig config_;
    bool running_ = false;
    
    // Current assessment state
    GPUAssessment assessment_;
    
    // Event registry (bounded)
    struct EventRegistry {
        std::map<std::string, GPUEvent> pending_events;
        std::set<std::string> acknowledged_ids;
        size_t next_id_counter = 0;
    };
    std::unique_ptr<EventRegistry> events_;
    
    // Metrics
    GPUMonitorMetrics metrics_;
    
    // Assessment methods (private)
    GPUAssessment assess_gpu_health_internal(std::chrono::system_clock::time_point now);
    
    // Event generation helpers
    void generate_events(const GPUMonitorResult& result);
    
    // Native acquisition methods (private - stub implementations for now)
    std::optional<GPUIdentity> acquire_gpu_identity(int device_index);
    std::optional<GPUPower> acquire_power_data();
    std::optional<GPUTemperature> acquire_temperature_data();
    std::optional<GPUClocks> acquire_clocks_data();
    std::optional<GPUUtilization> acquire_utilization_data();
    std::optional<GPUECC> acquire_ecc_data();
    std::optional<GPUDisplay> acquire_display_data();
};

// ============================================================================
// Factory function
// ============================================================================

std::unique_ptr<GPUMonitor> make_gpu_monitor(
    const GPUMonitorConfig& config = GPUMonitorConfig{});

}  // namespace rebuntu::modules::gpu_health_monitor