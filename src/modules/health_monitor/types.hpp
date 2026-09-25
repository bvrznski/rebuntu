// rebuntu::modules::health_monitor — Process & Service Health Monitor Types (Phase 5.6)
//
// This header defines core types for process and service health monitoring in Rebuntu:
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

#include <system/core/contracts.hpp>
#include <runtime/contracts.hpp>

#include <chrono>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <optional>
#include <iosfwd>

namespace rebuntu::modules::health_monitor {

// ============================================================================
// ProcessState — State of a process from Linux perspective
// ============================================================================

enum class ProcessState {
    kUnknown,        // Process state unknown (missing evidence)
    kRunning,        // Process is currently running/active
    kStopped,        // Process stopped (signal, ptrace, etc.)
    kZombie,         // Zombie/defunct process (terminated but not reaped)
    kWaiting,        // Process waiting for event/I/O
    kIdle,           // Process idle/waiting for work
};

inline std::string to_string(ProcessState s) {
    switch (s) {
        case ProcessState::kUnknown:   return "unknown";
        case ProcessState::kRunning:   return "running";
        case ProcessState::kStopped:   return "stopped";
        case ProcessState::kZombie:    return "zombie";
        case ProcessState::kWaiting:   return "waiting";
        case ProcessState::kIdle:      return "idle";
    }
    return "unknown";
}

// ============================================================================
// ServiceHealthState — Health assessment of a systemd service
// ============================================================================

enum class ServiceHealthState {
    kUnknown,       // Health not assessed yet
    kHealthy,       // Service healthy and ready
    kDegraded,      // Service operational but with issues
    kUnhealthy,     // Service unhealthy (failed or not ready)
};

inline std::string to_string(ServiceHealthState s) {
    switch (s) {
        case ServiceHealthState::kUnknown:   return "unknown";
        case ServiceHealthState::kHealthy:   return "healthy";
        case ServiceHealthState::kDegraded:  return "degraded";
        case ServiceHealthState::kUnhealthy: return "unhealthy";
    }
    return "unknown";
}

// ============================================================================
// CrashBehavior — Pattern of process/service crashes
// ============================================================================

enum class CrashBehavior {
    kNone,              // No crash detected
    kSingleCrash,       // One-off crash (not a pattern)
    kIntermittent,      // Occasional crashes with recovery
    kCrashLooping,      // Repeated crash-restart cycle
    kStalled,           // Process alive but not making progress
};

inline std::string to_string(CrashBehavior c) {
    switch (c) {
        case CrashBehavior::kNone:         return "none";
        case CrashBehavior::kSingleCrash:  return "single_crash";
        case CrashBehavior::kIntermittent: return "intermittent";
        case CrashBehavior::kCrashLooping: return "crash_looping";
        case CrashBehavior::kStalled:      return "stalled";
    }
    return "unknown";
}

// ============================================================================
// HealthDimension — A specific aspect of health being monitored
// ============================================================================

enum class HealthDimension {
    kLifecycle,       // Lifecycle state (running/stopped/zombie)
    kReadiness,       // Can accept work (port open, dependencies ready)
    kOperational,     // Core functionality working
    kResource,        // Resource usage within bounds
    kBehavioral,      // Behavioral patterns (crashes, hangs, stalls)
};

inline std::string to_string(HealthDimension d) {
    switch (d) {
        case HealthDimension::kLifecycle:   return "lifecycle";
        case HealthDimension::kReadiness:   return "readiness";
        case HealthDimension::kOperational: return "operational";
        case HealthDimension::kResource:    return "resource";
        case HealthDimension::kBehavioral:  return "behavioral";
    }
    return "unknown";
}

// ============================================================================
// SubjectType — Type of subject being monitored
// ============================================================================

enum class SubjectType {
    kProcess,  // A process (by PID)
    kService   // A systemd service (by unit name)
};

inline std::string to_string(SubjectType t) {
    switch (t) {
        case SubjectType::kProcess: return "process";
        case SubjectType::kService: return "service";
    }
    return "unknown";
}

// ============================================================================
// HealthEventType — Type of health event
// ============================================================================

enum class HealthEventType {
    kProcessStateChange,
    kServiceHealthChange,
    kCrashDetected,
    kCrashLoopDetected,
    kStallDetected,
    kResourceWarning,
    kReadinessChange,
};

inline std::string to_string(HealthEventType t) {
    switch (t) {
        case HealthEventType::kProcessStateChange: return "process_state_change";
        case HealthEventType::kServiceHealthChange: return "service_health_change";
        case HealthEventType::kCrashDetected: return "crash_detected";
        case HealthEventType::kCrashLoopDetected: return "crash_loop_detected";
        case HealthEventType::kStallDetected: return "stall_detected";
        case HealthEventType::kResourceWarning: return "resource_warning";
        case HealthEventType::kReadinessChange: return "readiness_change";
    }
    return "unknown";
}

// ============================================================================
// HealthMonitorMetrics — Runtime metrics for the health monitor
// ============================================================================

struct HealthMonitorMetrics {
    size_t assessments_performed = 0;
    size_t observations_received = 0;
    size_t events_generated = 0;
    
    size_t process_assessments = 0;
    size_t service_assessments = 0;
    
    std::map<HealthEventType, size_t> event_counts;
    
    std::chrono::system_clock::time_point started_at;
};

// ============================================================================
// DimensionAssessment — Assessment of one health dimension
// ============================================================================

struct DimensionAssessment {
    HealthDimension dimension = HealthDimension::kLifecycle;
    ServiceHealthState state = ServiceHealthState::kUnknown;
    std::string reason;  // Human-readable explanation
};

// ============================================================================
// ProcessResourceUsage — Resource usage for a process
// ============================================================================

struct ProcessResourceUsage {
    double cpu_percent = 0.0;           // CPU utilization %
    double memory_percent = 0.0;        // Memory utilization %
    std::optional<uint64_t> memory_bytes;
    uint64_t open_file_descriptors = 0;
};

// ============================================================================
// ServiceResourceUsage — Resource usage for a systemd service
// ============================================================================

struct ServiceResourceUsage {
    double cpu_percent = 0.0;
    double memory_percent = 0.0;
    uint64_t tasks_count = 0;           // Number of threads/tasks
};

// ============================================================================
// ProcessHealth — Complete health assessment for a process
// ============================================================================

struct ProcessHealth {
    std::string pid;                          // Process ID as string (for evidence)
    std::optional<std::string> executable;    // Path to executable
    std::optional<std::string> cmdline;       // Command line (may be truncated)
    
    ProcessState state = ProcessState::kUnknown;
    ServiceHealthState health_state = ServiceHealthState::kUnknown;
    
    std::chrono::system_clock::time_point observed_at;
    std::optional<std::chrono::milliseconds> uptime_ms;
    std::optional<std::chrono::milliseconds> crash_duration_ms;
    
    int restart_count = 0;
    CrashBehavior crash_behavior = CrashBehavior::kNone;
    
    ProcessResourceUsage resources;
    
    std::vector<DimensionAssessment> assessments;
    
    std::vector<std::string> evidence_ids;
};

// ============================================================================
// ServiceHealth — Complete health assessment for a systemd service
// ============================================================================

struct ServiceHealth {
    std::string unit_name;                    // systemd unit name
    
    bool is_active = false;
    bool is_failed = false;
    bool is_restarting = false;
    std::optional<std::string> main_pid;
    
    std::optional<std::string> substate;
    
    ServiceHealthState health_state = ServiceHealthState::kUnknown;
    
    std::optional<ProcessHealth> process_health;
    
    int restart_count = 0;
    CrashBehavior crash_behavior = CrashBehavior::kNone;
    
    bool is_ready = false;
    std::optional<std::chrono::milliseconds> readiness_delay_ms;
    
    ServiceResourceUsage resources;
    
    std::vector<DimensionAssessment> assessments;
    
    std::chrono::system_clock::time_point assessed_at;
    std::optional<std::chrono::system_clock::time_point> last_state_change;
};

// ============================================================================
// ProcessStateEntry — Internal tracking for process state (used by HealthMonitor)
// ============================================================================

struct ProcessStateEntry {
    ProcessHealth last_health;
    std::chrono::system_clock::time_point observed_at;
    int crash_count_in_window = 0;
    std::optional<std::chrono::system_clock::time_point> first_crash_time;
};

// ============================================================================
// ServiceStateEntry — Internal tracking for service state (used by HealthMonitor)
// ============================================================================

struct ServiceStateEntry {
    ServiceHealth last_health;
    std::chrono::system_clock::time_point observed_at;
    int restart_count_in_window = 0;
    std::optional<std::chrono::system_clock::time_point> first_restart_time;
};

// ============================================================================
// HealthAssessment — Complete health assessment for a subject
// ============================================================================

struct HealthAssessment {
    SubjectType subject_type = SubjectType::kProcess;
    std::string subject_id;                   // PID or unit name
    
    ServiceHealthState overall_state = ServiceHealthState::kUnknown;
    
    struct DimensionResult {
        HealthDimension dimension = HealthDimension::kLifecycle;
        ServiceHealthState state = ServiceHealthState::kUnknown;
        bool passed_threshold = false;
        std::optional<double> value;
        std::string reason;
    };
    std::vector<DimensionResult> dimensions;
    
    std::chrono::system_clock::time_point assessed_at;
    std::optional<std::chrono::duration<double>> assessment_duration_ms;
    
    std::vector<rebuntu::core::Evidence> evidence;
    
    bool is_complete = true;
    std::vector<std::string> uncertainty_notes;
};

// ============================================================================
// HealthMonitorConfig — Configuration for the health monitor
// ============================================================================

struct HealthMonitorConfig {
    std::chrono::minutes crash_loop_window_minutes{2};
    
    int service_restart_threshold = 5;
    int process_crash_threshold = 3;
    
    double cpu_utilization_warning_percent = 80.0;
    double memory_utilization_warning_percent = 85.0;
    
    std::chrono::milliseconds readiness_timeout_ms{30000};
    
    bool enable_process_monitoring = true;
    bool enable_service_monitoring = true;
    bool enable_resource_monitoring = true;
    
    size_t max_evidence_per_assessment = 16;
    std::chrono::hours evidence_retention_hours{24};
    
    bool include_uncertainty_notes = true;
};

// ============================================================================
// HealthEvent — Event generated by the health monitor
// ============================================================================

struct HealthEvent {
    HealthEventType event_type = HealthEventType::kProcessStateChange;
    
    std::string event_id;
    
    std::chrono::system_clock::time_point timestamp;
    
    SubjectType subject_type = SubjectType::kProcess;
    std::string subject_id;
    
    std::optional<ServiceHealthState> old_state;
    ServiceHealthState new_state = ServiceHealthState::kUnknown;
    
    std::vector<rebuntu::core::Evidence> evidence;
    std::string description;
    
    std::optional<std::string> dedup_key;
};

// ============================================================================
// Factory functions
// ============================================================================

ProcessHealth make_initial_process_health(const std::string& pid);
ServiceHealth make_initial_service_health(const std::string& unit_name);

}  // namespace rebuntu::modules::health_monitor