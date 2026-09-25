// rebuntu::modules::cpu_memory_thermal_monitor — CPU / Memory / Thermal Monitor Types (Phase 5.9)
//
// This header defines core types for CPU, memory, and thermal monitoring in Rebuntu:
//   - CPU utilization, load average, run queue pressure
//   - Memory availability, swap activity, PSI (Pressure Stall Information)
//   - OOM events, thermal temperature, thermal throttling
//   - Resource state: normal, pressured, constrained, unknown
//
// Design Philosophy:
//   * Monitoring ≠ Recovery (this module observes, does not repair)
//   * UNKNOWN != false (missing telemetry must be reported honestly)
//   * Evidence-based assessment, not heuristic scores
//   * Preserve raw evidence while adding structured analysis

#pragma once

#include <chrono>
#include <string>
#include <vector>
#include <map>
#include <optional>
#include <iosfwd>

namespace rebuntu::modules::cpu_memory_thermal_monitor {

// ============================================================================
// ResourceState — State of a resource subsystem
// ============================================================================

enum class ResourceState {
    kUnknown,        // State unknown (missing evidence)
    kNormal,         // Operating within normal parameters
    kPressured,      // Under pressure but not yet constrained
    kConstrained,    // Constrained by resource limits
    kCritical,       // Critical state requiring immediate attention
};

inline std::string to_string(ResourceState s) {
    switch (s) {
        case ResourceState::kUnknown:    return "unknown";
        case ResourceState::kNormal:     return "normal";
        case ResourceState::kPressured:  return "pressured";
        case ResourceState::kConstrained:return "constrained";
        case ResourceState::kCritical:   return "critical";
    }
    return "unknown";
}

// ============================================================================
// ThermalResource nested types - defined first for reuse in other structs
// ============================================================================

struct ThermalResource {
    // Temperature reading within a thermal zone
    struct TemperatureReading {
        std::string zone_name;            // e.g., "cpu", "gpu", "thermal_zone0"
        double temperature_celsius = 0.0;
        
        // Thresholds (optional)
        std::optional<double> warning_threshold_celsius;
        std::optional<double> critical_threshold_celsius;
        
        std::chrono::system_clock::time_point measured_at;
    };
    
    struct ThrottlingState {
        bool is_throttled = false;        // Currently throttling
        int throttle_count = 0;           // Number of throttle events
        std::chrono::system_clock::time_point last_throttle_at;
        
        std::optional<std::string> throttle_reason;
    };
    
    struct CoolingDevice {
        std::string name;                 // e.g., "acpi_thermal_rel"
        int max_state = 0;                // Maximum cooling state
        int current_state = 0;            // Current cooling state
        
        std::chrono::system_clock::time_point measured_at;
    };
    
    // Data fields
    std::vector<TemperatureReading> temperatures;
    std::optional<ThrottlingState> throttling;
    std::vector<CoolingDevice> cooling_devices;
    
    // Timestamp
    std::chrono::system_clock::time_point measured_at;
};

// ============================================================================
// CPUResource — CPU resource measurement
// ============================================================================

struct CPUResource {
    // Utilization percentages (0.0 - 100.0)
    double user_percent = 0.0;          // User space CPU %
    double system_percent = 0.0;        // System/kernel CPU %
    double idle_percent = 0.0;          // Idle CPU %
    double iowait_percent = 0.0;        // I/O wait %
    double interrupt_percent = 0.0;     // Hardware interrupts %
    double softirq_percent = 0.0;       // Software interrupts %
    
    // Load average (1, 5, 15 minute)
    double load_avg_1min = 0.0;
    double load_avg_5min = 0.0;
    double load_avg_15min = 0.0;
    
    // Run queue
    int running_processes = 0;          // Processes currently running
    int total_processes = 0;            // Total processes in run queue
    
    // CPU count info (may be incomplete)
    std::optional<int> logical_cpu_count;
    std::optional<int> physical_cpu_count;
    
    // Timestamp
    std::chrono::system_clock::time_point measured_at;
    
    // Measurement window for utilization
    std::optional<std::chrono::milliseconds> measurement_window_ms;
};

// ============================================================================
// MemoryResource — Memory resource measurement
// ============================================================================

struct MemoryResource {
    // Total memory
    uint64_t total_bytes = 0;           // Total RAM in bytes
    
    // Available memory
    uint64_t available_bytes = 0;       // Actually available for new allocations
    uint64_t free_bytes = 0;            // Completely unused memory
    uint64_t used_bytes = 0;            // Used by applications/cache
    
    // Buffer/cached memory
    uint64_t buffers_bytes = 0;         // Buffer memory (raw disk blocks)
    uint64_t cached_bytes = 0;          // Page cache memory
    
    // Swap
    uint64_t swap_total_bytes = 0;
    uint64_t swap_free_bytes = 0;
    uint64_t swap_used_bytes = 0;
    
    // Memory pressure indicators (from /proc/pressure)
    std::optional<double> memory_full_stall_percent_10s;   // Full stall % over 10s
    std::optional<double> memory_some_stall_percent_10s;   // Some stall % over 10s
    
    // Timestamp
    std::chrono::system_clock::time_point measured_at;
    
    // Measurement window
    std::optional<std::chrono::milliseconds> measurement_window_ms;
};

// ============================================================================
// PSIResource — Pressure Stall Information (from /proc/pressure)
// ============================================================================

struct PSIResource {
    struct MemoryPSI {
        double some_full_stall_percent_10s = 0.0;
        double some_partial_stall_percent_10s = 0.0;
        double full_stall_percent_10s = 0.0;
        
        std::chrono::system_clock::time_point measured_at;
    };
    
    struct CPUPSI {
        double some_full_stall_percent_10s = 0.0;
        double some_partial_stall_percent_10s = 0.0;
        
        std::chrono::system_clock::time_point measured_at;
    };
    
    struct IOPSI {
        double some_full_stall_percent_10s = 0.0;
        double some_partial_stall_percent_10s = 0.0;
        
        std::chrono::system_clock::time_point measured_at;
    };
    
    // Data fields
    std::optional<MemoryPSI> memory;
    std::optional<CPUPSI> cpu;
    std::optional<IOPSI> io;
};

// ============================================================================
// ResourceEvidence — Provenance-bearing observation for a resource
// ============================================================================

struct ResourceEvidence {
    std::string source;                 // Source path (/proc/stat, /sys/class/thermal/etc.)
    std::string raw_data;               // Raw data from native source (may be truncated)
    
    std::chrono::system_clock::time_point acquired_at;
    std::optional<std::chrono::milliseconds> acquisition_duration_ms;
    
    bool is_complete = true;            // false if source was incomplete/truncated
    std::optional<std::string> error_message;
    
    std::string evidence_id;
};

// ============================================================================
// CPUAssessment — Complete CPU subsystem assessment
// ============================================================================

struct CPUAssessment {
    ResourceState state = ResourceState::kUnknown;
    
    std::optional<CPUResource> current;
    std::optional<std::chrono::milliseconds> measurement_window_ms;
    
    struct HistoricalWindow {
        std::chrono::system_clock::time_point window_start;
        std::chrono::system_clock::time_point window_end;
        double avg_user_percent = 0.0;
        double max_user_percent = 0.0;
        int high_utilization_count = 0;
    };
    std::optional<HistoricalWindow> recent_history_5min;
    
    struct LoadAssessment {
        bool is_high_load = false;
        double load_per_cpu = 0.0;
        
        bool is_increasing = false;
        double load_trend_percent_change = 0.0;
    };
    std::optional<LoadAssessment> load;
    
    std::vector<std::string> evidence_ids;
    std::chrono::system_clock::time_point assessed_at;
};

// ============================================================================
// MemoryAssessment — Complete memory subsystem assessment
// ============================================================================

struct MemoryAssessment {
    ResourceState state = ResourceState::kUnknown;
    
    std::optional<MemoryResource> current;
    std::optional<std::chrono::milliseconds> measurement_window_ms;
    
    struct PressureAssessment {
        bool is_under_pressure = false;
        ResourceState pressure_state = ResourceState::kUnknown;
        
        std::optional<double> memory_full_stall_percent_10s;
        std::optional<double> memory_some_stall_percent_10s;
    };
    std::optional<PressureAssessment> pressure;
    
    struct SwapAssessment {
        bool is_swap_used = false;
        double swap_utilization_percent = 0.0;
        
        bool is_swapping_heavily = false;
    };
    std::optional<SwapAssessment> swap;
    
    struct OOMRisk {
        bool is_oom_active = false;
        int oom_kills_count = 0;
        
        std::optional<double> available_memory_percent;
        std::optional<std::string> risk_level;
    };
    std::optional<OOMRisk> oom_risk;
    
    struct HistoricalWindow {
        std::chrono::system_clock::time_point window_start;
        std::chrono::system_clock::time_point window_end;
        double avg_used_percent = 0.0;
        int memory_pressure_events = 0;
    };
    std::optional<HistoricalWindow> recent_history_5min;
    
    std::vector<std::string> evidence_ids;
    std::chrono::system_clock::time_point assessed_at;
};

// ============================================================================
// ThermalAssessment — Complete thermal subsystem assessment
// ============================================================================

struct ThermalAssessment {
    ResourceState state = ResourceState::kUnknown;
    
    // Use ThermalResource::TemperatureReading here - the type is defined above
    std::vector<ThermalResource::TemperatureReading> temperatures;
    
    struct ThrottlingAssessment {
        bool is_throttled = false;
        int throttle_count_in_window = 0;
        
        std::optional<std::chrono::milliseconds> throttle_window_ms;
    };
    std::optional<ThrottlingAssessment> throttling;
    
    struct CoolingAssessment {
        bool cooling_active = false;
        int max_cooling_state = 0;
        
        bool is_adequate = true;
    };
    std::optional<CoolingAssessment> cooling;
    
    struct HistoricalWindow {
        std::chrono::system_clock::time_point window_start;
        std::chrono::system_clock::time_point window_end;
        double avg_temperature_celsius = 0.0;
        double max_temperature_celsius = 0.0;
        int thermal_events = 0;
    };
    std::optional<HistoricalWindow> recent_history_5min;
    
    std::vector<std::string> evidence_ids;
    std::chrono::system_clock::time_point assessed_at;
};

// ============================================================================
// ResourceAssessment — Complete resource subsystem assessment (unified)
// ============================================================================

struct ResourceAssessment {
    enum class Subsystem {
        kCPU,
        kMemory,
        kThermal,
    } subsystem = Subsystem::kCPU;
    
    std::optional<CPUAssessment> cpu_assessment;
    std::optional<MemoryAssessment> memory_assessment;
    std::optional<ThermalAssessment> thermal_assessment;
    
    std::vector<std::string> evidence_ids;
    std::chrono::system_clock::time_point assessed_at;
};

// ============================================================================
// ResourceMonitorMetrics — Runtime metrics for the monitor
// ============================================================================

struct ResourceMonitorMetrics {
    std::chrono::system_clock::time_point started_at;
    
    size_t cpu_observations = 0;
    size_t memory_observations = 0;
    size_t thermal_observations = 0;
    size_t psi_observations = 0;
    
    struct SourceMetrics {
        size_t acquisitions = 0;
        size_t failures = 0;
        std::chrono::milliseconds total_acquisition_time{0};
    };
    std::map<std::string, SourceMetrics> source_metrics;
};

// ============================================================================
// ResourceMonitorConfig — Configuration for the resource monitor
// ============================================================================

struct ResourceMonitorConfig {
    std::chrono::milliseconds observation_interval_ms{5000};
    
    double cpu_utilization_warning_percent = 80.0;
    double cpu_utilization_critical_percent = 95.0;
    double load_per_cpu_warning = 1.0;
    
    double memory_pressure_warning_percent_10s = 1.0;
    double swap_utilization_warning_percent = 50.0;
    
    int temperature_warning_celsius = 75;
    int temperature_critical_celsius = 90;
    std::chrono::milliseconds thermal_window_ms{300000};
    
    size_t max_evidence_per_assessment = 16;
    std::chrono::hours evidence_retention_hours{24};
    
    bool enable_cpu_monitoring = true;
    bool enable_memory_monitoring = true;
    bool enable_thermal_monitoring = true;
    bool enable_psi_monitoring = true;
};

// ============================================================================
// ResourceEvent — Event generated by the resource monitor
// ============================================================================

enum class ResourceEventType {
    kCPUUtilizationWarning,
    kCPUUtilizationCritical,
    kMemoryPressureDetected,
    kSwapUtilizationWarning,
    kThermalWarning,
    kThermalCritical,
    kThrottlingStarted,
    kThrottlingStopped,
};

struct ResourceEvent {
    ResourceEventType event_type = ResourceEventType::kCPUUtilizationWarning;
    
    std::string event_id;
    std::chrono::system_clock::time_point timestamp;
    
    ResourceAssessment::Subsystem affected_subsystem = ResourceAssessment::Subsystem::kCPU;
    
    std::optional<std::string> subject;
    
    struct ValueAtEvent {
        double measurement_value = 0.0;
        std::string threshold_type;
        double threshold_value = 0.0;
    };
    ValueAtEvent value_at_event;
    
    std::vector<std::string> evidence_ids;
    std::string description;
};

// ============================================================================
// ResourceMonitorResult — Result of a resource monitoring assessment
// ============================================================================

struct ResourceMonitorResult {
    enum class Outcome {
        kSuccess,
        kPartial,
        kFailure,
        kUnknown,
    } outcome = Outcome::kUnknown;
    
    std::optional<CPUAssessment> cpu_assessment;
    std::optional<MemoryAssessment> memory_assessment;
    std::optional<ThermalAssessment> thermal_assessment;
    
    std::vector<ResourceEvidence> evidences;
    
    std::vector<ResourceEvent> events;
    
    std::chrono::system_clock::time_point assessed_at;
    std::optional<std::chrono::milliseconds> assessment_duration_ms;
    
    std::vector<std::string> uncertainty_notes;
};

// ============================================================================
// Factory functions for creating result objects
// ============================================================================

CPUAssessment make_initial_cpu_assessment();
MemoryAssessment make_initial_memory_assessment();
ThermalAssessment make_initial_thermal_assessment();

ResourceMonitorResult make_resource_monitor_result(ResourceMonitorResult::Outcome outcome);

}  // namespace rebuntu::modules::cpu_memory_thermal_monitor