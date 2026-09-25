// rebuntu::modules::cpu_memory_thermal_monitor — CPU / Memory / Thermal Monitor (Phase 5.9)
//
// This module provides comprehensive resource monitoring for Rebuntu:
//   - CPU utilization, load average, run queue pressure
//   - Memory availability, swap activity, PSI (Pressure Stall Information)
//   - OOM events, thermal temperature, thermal throttling
//   - Resource state: normal, pressured, constrained, unknown
//
// Design Philosophy:
//   * Monitoring ≠ Recovery (this module observes, does not repair)
//   * UNKNOWN != false (missing telemetry must be reported honestly)
//   * Evidence-based assessment, not heuristic scores

#pragma once

#include <memory>
#include <chrono>
#include <string>
#include <vector>
#include <map>
#include <optional>

// Rebuntu core contracts first
#include <system/core/contracts.hpp>

#include "types.hpp"

namespace rebuntu::modules::cpu_memory_thermal_monitor {

// ============================================================================
// ResourceMonitor — Main resource monitoring engine
//
// This class collects and assesses CPU, memory, and thermal state from
// native Linux sources (procfs, sysfs) into a comprehensive resource status.
// ============================================================================

class ResourceMonitor {
public:
    explicit ResourceMonitor(ResourceMonitorConfig config);
    ~ResourceMonitor();
    
    // Lifecycle management
    core::Outcome start();
    core::Outcome stop();
    bool is_running() const { return running_; }
    
    // Configuration
    const ResourceMonitorConfig& config() const { return config_; }
    void set_config(const ResourceMonitorConfig& config);
    
    // Main assessment entry point
    ResourceMonitorResult assess_resources(
        std::chrono::system_clock::time_point assessment_time = std::chrono::system_clock::now());
    
    // Get current assessments
    CPUAssessment get_cpu_assessment() const { return cpu_assessment_; }
    MemoryAssessment get_memory_assessment() { return memory_assessment_; }
    ThermalAssessment get_thermal_assessment() { return thermal_assessment_; }
    
    // Get internal events (e.g., for triggering diagnostics)
    std::vector<ResourceEvent> get_pending_events();
    void acknowledge_event(const std::string& event_id);
    
    // Metrics
    ResourceMonitorMetrics metrics() const;
    
private:
    ResourceMonitorConfig config_;
    bool running_ = false;
    
    // Current assessment state
    CPUAssessment cpu_assessment_;
    MemoryAssessment memory_assessment_;
    ThermalAssessment thermal_assessment_;
    
    // Historical windows for trend analysis (circular buffers)
    struct HistoryWindow {
        std::chrono::system_clock::time_point window_start;
        std::vector<CPUResource> cpu_samples;
        std::vector<MemoryResource> memory_samples;
        std::chrono::minutes window_minutes{5};
    };
    std::optional<HistoryWindow> history_window_;
    
    // Event registry (bounded)
    struct EventRegistry {
        std::map<std::string, ResourceEvent> pending_events;
        std::set<std::string> acknowledged_ids;
        size_t next_id_counter = 0;
    };
    std::unique_ptr<EventRegistry> events_;
    
    // Metrics
    ResourceMonitorMetrics metrics_;
    
    // Assessment methods (private)
    CPUAssessment assess_cpu(std::chrono::system_clock::time_point now);
    MemoryAssessment assess_memory(std::chrono::system_clock::time_point now);
    ThermalAssessment assess_thermal(std::chrono::system_clock::time_point now);
    
    // Event generation helpers
    void generate_events(const ResourceMonitorResult& result);
    
    // Native acquisition methods (implemented in .cpp)
    std::optional<CPUResource> acquire_cpu_resource();
    std::optional<MemoryResource> acquire_memory_resource();
    std::optional<ThermalResource> acquire_thermal_resource();
};

// ============================================================================
// Factory function
// ============================================================================

std::unique_ptr<ResourceMonitor> make_resource_monitor(
    const ResourceMonitorConfig& config = ResourceMonitorConfig{});

}  // namespace rebuntu::modules::cpu_memory_thermal_monitor