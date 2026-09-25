// rebuntu::modules::stability_monitor — System Stability Assessment Types (Phase 5.5)
//
// This header defines the core types for stability monitoring in Rebuntu:
//   - Stability state: stable, degraded, unstable, unknown
//   - Assessment dimensions: subsystems, failures, resources, evidence
//   - Temporal behavior: hysteresis, flapping prevention
//
// Design Philosophy:
//   * Stability is a structured assessment, not one magic score
//   * Monitoring ≠ recovery (this module observes, does not repair)
//   * UNKNOWN ≠ false (missing telemetry must be reported honestly)

#pragma once

#include <system/core/contracts.hpp>
#include <runtime/contracts.hpp>

#include <chrono>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <optional>
#include <iosfwd>

namespace rebuntu::modules::stability_monitor {

// ============================================================================
// StabilityState — Overall stability assessment
// ============================================================================

enum class StabilityState {
    kUnknown,      // Not enough evidence to assess stability
    kStable,       // Operating within normal parameters
    kDegraded,     // Operational but with reduced capability or elevated risk
    kUnstable,     // Multiple failures or critical subsystems affected
};

inline std::string to_string(StabilityState s) {
    switch (s) {
        case StabilityState::kUnknown:   return "unknown";
        case StabilityState::kStable:    return "stable";
        case StabilityState::kDegraded:  return "degraded";
        case StabilityState::kUnstable:  return "unstable";
    }
    return "unknown";
}

// ============================================================================
// Subsystem — A system component being monitored
// ============================================================================

enum class Subsystem {
    kSystemdServices,   // systemd service lifecycle
    kKernelEvents,      // kernel log events and warnings
    kCpuResource,       // CPU utilization and load
    kMemoryResource,    // Memory pressure and OOM risk
    kDiskResource,      // Disk I/O, capacity, filesystem health
    kNetwork,           // Network connectivity and errors
    kThermal,           // Thermal throttling and temperatures
    kDeviceHealth,      // Device error rates and failures
};

inline std::string to_string(Subsystem s) {
    switch (s) {
        case Subsystem::kSystemdServices:  return "systemd-services";
        case Subsystem::kKernelEvents:     return "kernel-events";
        case Subsystem::kCpuResource:      return "cpu-resource";
        case Subsystem::kMemoryResource:   return "memory-resource";
        case Subsystem::kDiskResource:     return "disk-resource";
        case Subsystem::kNetwork:          return "network";
        case Subsystem::kThermal:          return "thermal";
        case Subsystem::kDeviceHealth:     return "device-health";
    }
    return "unknown";
}

// ============================================================================
// FailureClass — Categories of failures that indicate instability
// ============================================================================

enum class FailureClass {
    kNone,                    // No failure detected
    kServiceFailure,          // Systemd unit entered failed state
    kServiceCrashLoop,        // Service in restart loop
    kOOM,                     // Out-of-memory event
    kKernelWarning,           // Kernel warning message
    kKernelError,             // Kernel error/panic message
    kGPUFault,                // GPU driver fault/reset
    kBlockIOWrite,            // Block device write I/O error
    kFileSystemRemount,       // Filesystem remounted read-only
    kDeviceDisconnect,        // Device disconnect/unplug
    kThermalEvent,            // Thermal throttling/warning
    kHardwareFailure,         // Hardware failure (SMART, ECC, etc.)
};

inline std::string to_string(FailureClass fc) {
    switch (fc) {
        case FailureClass::kNone:           return "none";
        case FailureClass::kServiceFailure: return "service-failure";
        case FailureClass::kServiceCrashLoop: return "service-crash-loop";
        case FailureClass::kOOM:            return "oom-event";
        case FailureClass::kKernelWarning:  return "kernel-warning";
        case FailureClass::kKernelError:    return "kernel-error";
        case FailureClass::kGPUFault:       return "gpu-fault";
        case FailureClass::kBlockIOWrite:   return "block-io-write-error";
        case FailureClass::kFileSystemRemount: return "filesystem-remount-read-only";
        case FailureClass::kDeviceDisconnect: return "device-disconnect";
        case FailureClass::kThermalEvent:   return "thermal-event";
        case FailureClass::kHardwareFailure: return "hardware-failure";
    }
    return "unknown";
}

// ============================================================================
// StabilityDimension — A specific aspect of stability within a subsystem
// ============================================================================

struct StabilityDimension {
    std::string name;           // Dimension identifier (e.g., "restart_rate", "error_count")
    StabilityState state = StabilityState::kUnknown;
    
    // Evidence supporting this dimension's assessment
    std::vector<rebuntu::core::Evidence> evidence;
    
    // Temporal window for this assessment (when the observation applies)
    std::optional<std::chrono::system_clock::time_point> observation_start;
    std::optional<std::chrono::system_clock::time_point> observation_end;
    
    // Counters/accumulators
    int count = 0;              // Event count in window
    double rate_per_minute = 0.0; // Rate calculation where applicable
    
    // Threshold info (for debugging/explanation)
    std::optional<int> threshold_count;
    std::optional<double> threshold_rate;
    
    // Assessment explanation (human-readable for debugging)
    std::string assessment_reason;
};

// ============================================================================
// SubsystemAssessment — Complete stability assessment for one subsystem
// ============================================================================

struct SubsystemAssessment {
    Subsystem subsystem = Subsystem::kSystemdServices;
    StabilityState state = StabilityState::kUnknown;
    
    // Dimensions within this subsystem (e.g., restart_rate, failure_count, etc.)
    std::vector<StabilityDimension> dimensions;
    
    // Primary failure class if any
    std::optional<std::string> primary_failure_class;
    
    // List of affected subjects (service names, device paths, etc.)
    std::set<std::string> affected_subjects;
    
    // Timestamp of this assessment
    std::chrono::system_clock::time_point assessed_at;
};

// ============================================================================
// StabilityAssessment — Complete system stability assessment
// ============================================================================

struct StabilityAssessment {
    // Overall state
    StabilityState state = StabilityState::kUnknown;
    
    // Per-subsystem assessments
    std::map<Subsystem, SubsystemAssessment> subsystems;
    
    // Aggregate metrics
    int total_subsystems_assessed = 0;
    int subsystems_with_issues = 0;
    int total_events_observed = 0;
    
    // Assessment metadata
    std::chrono::system_clock::time_point assessed_at;
    std::optional<std::string> boot_id;          // Boot context for cross-boot correlation
    std::optional<std::string> machine_id;       // Machine identity
    
    // Evaluation window (when the assessment applies)
    std::optional<std::chrono::system_clock::time_point> evaluation_window_start;
    std::optional<std::chrono::system_clock::time_point> evaluation_window_end;
    
    // Uncertainty information
    bool evidence_complete = true;               // false if data was truncated/partial
    std::vector<std::string> uncertainty_notes;  // Notes about what's unknown
    
    // Correlation notes (what events are related across subsystems)
    struct Correlation {
        std::set<Subsystem> involved_subsystems;
        std::optional<std::chrono::system_clock::time_point> common_time_window;
        std::string description;  // Human-readable correlation explanation
    };
    std::vector<Correlation> correlations;
    
    // Hysteresis state (for preventing flapping)
    bool hysteresis_active = false;
    std::optional<std::chrono::system_clock::time_point> hysteresis_started_at;
};

// ============================================================================
// EventWindow — Temporal grouping for event analysis
// ============================================================================

struct EventWindow {
    std::string id;                          // Unique window ID (boot + time range)
    
    std::chrono::system_clock::time_point start_time;
    std::chrono::system_clock::time_point end_time;
    
    Subsystem subsystem = Subsystem::kSystemdServices;
    
    // Events in this window
    struct Event {
        std::string id;
        rebuntu::core::Evidence evidence;
        std::optional<std::string> subject;     // Affected service/device/etc.
        std::optional<std::string> event_class; // e.g., "failure", "warning", "info"
        std::chrono::system_clock::time_point timestamp;
    };
    std::vector<Event> events;
    
    // Aggregated metrics for this window
    int failure_count = 0;
    int warning_count = 0;
    double rate_per_minute = 0.0;
};

// ============================================================================
// StabilityMonitorConfig — Configuration for the stability monitor
// ============================================================================

struct StabilityMonitorConfig {
    // Assessment windows (durations)
    std::chrono::minutes event_window_minutes{10};     // Window for counting events
    std::chrono::minutes degradation_window_minutes{5}; // How long degraded before assessing
    
    // Thresholds (configurable limits)
    int service_restart_threshold = 5;                  // Restarts in window → degraded
    std::chrono::minutes service_restart_window_minutes{2};
    
    int kernel_error_rate_threshold = 10;              // Errors per window → degraded
    int disk_io_error_threshold = 3;                   // Disk I/O errors → unstable
    
    // Hysteresis (prevents flapping between states)
    std::chrono::minutes hysteresis_interval_minutes{5};
    
    // Resource thresholds
    double cpu_utilization_warning_percent = 80.0;
    double memory_pressure_warning_percent = 85.0;
    double disk_capacity_warning_percent = 90.0;
    
    // Evidence retention
    size_t max_evidence_per_assessment = 16;
    std::chrono::hours evidence_retention_hours{24};
    
    // Native source configuration
    bool enable_systemd_monitoring = true;
    bool enable_kernel_monitoring = true;
    bool enable_resource_monitoring = true;
    
    // Output
    bool include_uncertainty_notes = true;
};

// ============================================================================
// InternalAlert — Alert generated by the stability monitor
// ============================================================================

struct InternalAlert {
    std::string id;                          // Unique alert ID
    
    std::chrono::system_clock::time_point created_at;
    
    // Alert classification
    enum class Severity { kInfo, kLow, kMedium, kHigh, kCritical } severity = Severity::kInfo;
    
    FailureClass failure_class = FailureClass::kNone;
    
    // Affected subject(s)
    std::vector<std::string> affected_subjects;
    
    // Evidence chain
    std::vector<rebuntu::core::Evidence> evidence;
    
    // Assessment context
    std::optional<std::string> boot_id;
    std::optional<std::chrono::system_clock::time_point> correlation_time_window;
    
    // Hysteresis state (prevents duplicate alerts)
    bool is_new_occurrence = true;           // false if in hysteresis window
    
    // Deduplication info
    std::optional<std::string> deduplicated_from_id;  // If this was a duplicate
    
    // Assessment explanation (human-readable)
    std::string summary;
    
    // Actions that may be needed
    struct RecommendedAction {
        std::string category;   // "diagnostic", "monitor", "investigate"
        std::string description;
    };
    std::vector<RecommendedAction> recommended_actions;
};

// ============================================================================
// ResourceStatus — Status of a system resource
// ============================================================================

struct ResourceStatus {
    Subsystem subsystem = Subsystem::kCpuResource;
    
    // Current measurement
    double value = 0.0;
    
    // Thresholds
    std::optional<double> warning_threshold;
    std::optional<double> critical_threshold;
    
    // State
    StabilityState state = StabilityState::kUnknown;
    
    // Time window for this measurement
    std::chrono::system_clock::time_point measured_at;
    std::optional<std::chrono::duration<double>> sample_duration;
    
    // Historical context (for trend analysis)
    struct HistoricalPoint {
        std::chrono::system_clock::time_point timestamp;
        double value;
    };
    std::vector<HistoricalPoint> recent_history;  // Last N samples
    
    // Assessment reason
    std::string assessment_reason;
};

// ============================================================================
// Factory functions for creating result objects
// ============================================================================

StabilityAssessment make_initial_assessment(
    const StabilityMonitorConfig& config = StabilityMonitorConfig{});

// ============================================================================
// Ostream operators for easy debugging
// ============================================================================

inline std::ostream& operator<<(std::ostream& os, StabilityState s) {
    return os << to_string(s);
}

inline std::ostream& operator<<(std::ostream& os, Subsystem s) {
    return os << to_string(s);
}

inline std::ostream& operator<<(std::ostream& os, FailureClass fc) {
    return os << to_string(fc);
}

}  // namespace rebuntu::modules::stability_monitor