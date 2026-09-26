// rebuntu::modules::gpu_health_monitor — GPU Health Monitor Types (Phase 5.10)
//
// This header defines core types for GPU health monitoring in Rebuntu:
//   - Device presence and identity (UUID, PCI bus ID)
//   - Driver state and reachability
//   - Utilization (memory, graphics, encoder, decoder)
//   - Temperature, power draw, clocks
//   - ECC errors where supported
//   - Display ownership
//   - Reset events and Xid-like evidence
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

namespace rebuntu::modules::gpu_health_monitor {

// ============================================================================
// GPUState — Current state of a GPU device
// ============================================================================

enum class GPUState {
    kUnknown,          // State unknown (missing evidence)
    kAbsent,           // Device not present or driver unreachable
    kIdle,             // Present but idle (P8/P10 power state)
    kActive,           // Actively processing work
    kThrottled,        // Throttling due to thermal/power constraints
    kDegraded,         // Some functionality impaired
    kFault,            // Fault condition detected
};

inline std::string to_string(GPUState s) {
    switch (s) {
        case GPUState::kUnknown:    return "unknown";
        case GPUState::kAbsent:     return "absent";
        case GPUState::kIdle:       return "idle";
        case GPUState::kActive:     return "active";
        case GPUState::kThrottled:  return "throttled";
        case GPUState::kDegraded:   return "degraded";
        case GPUState::kFault:      return "fault";
    }
    return "unknown";
}

// ============================================================================
// GPUIdentity — Stable identifier for a GPU device
// ============================================================================

struct GPUIdentity {
    std::string uuid;                  // NVIDIA UUID or equivalent
    std::string pci_bus_id;            // PCI bus location (e.g., "0000:01:00.0")
    int device_index = -1;             // Enumerated index (not stable across reboots)
    
    std::string brand;                 // e.g., "NVIDIA Tesla", "NVIDIA GeForce"
    std::string product_name;          // e.g., "RTX 3080", "A100"
    std::string architecture;          // e.g., "Ampere", "Turing", "Volta"
    
    int sm_major = 0;                  // Streaming Multiprocessor version (major)
    int sm_minor = 0;                  // Streaming Multiprocessor version (minor)
    
    uint64_t total_memory_bytes = 0;   // Total GPU memory
    uint64_t free_memory_bytes = 0;    // Currently free GPU memory
    
    bool is_integrated = false;        // Integrated GPU vs discrete
};

// ============================================================================
// GPUPower — Power-related metrics
// ============================================================================

struct GPUPower {
    double power_watts = 0.0;          // Current power draw
    double average_power_watts = 0.0;  // Average over window
    
    std::optional<double> max_power_limit_watts;
    std::optional<double> min_power_limit_watts;
    
    bool is_ppt_limit_active = false;   // Power tracking limit active
    bool is_tdc_limit_active = false;   // Thermal design current limit active
};

// ============================================================================
// GPUTemperature — Temperature readings
// ============================================================================

struct GPUTemperature {
    double gpu_celsius = 0.0;          // GPU core temperature
    
    std::optional<double> memory_celsius;
    std::optional<double> board_celsius;
    
    int fan_rpm = 0;                   // Revolutions per minute
    int fan_percent = 0;               // Percentage of max speed (0-100)
};

// ============================================================================
// GPUClocks — Clock frequency readings
// ============================================================================

struct GPUClocks {
    int graphics_clock_mhz = 0;        // Graphics clock frequency
    int memory_clock_mhz = 0;          // Memory clock frequency
    
    std::optional<int> sm_clock_mhz;   // Streaming multiprocessor clock
    std::optional<int> encoder_clock_mhz;
    std::optional<int> decoder_clock_mhz;
    
    bool power_limit_throttled = false;
    bool thermal_limit_throttled = false;
    bool slow_memory_throttled = false;
};

// ============================================================================
// GPUUtilization — Utilization percentages
// ============================================================================

struct GPUUtilization {
    int graphics_percent = 0;          // Graphics engine utilization (0-100)
    int memory_percent = 0;            // Memory controller utilization (0-100)
    
    std::optional<int> encoder_percent;
    std::optional<int> decoder_percent;
};

// ============================================================================
// GPUECC — Error Correction Code state (if supported)
// ============================================================================

struct GPUECC {
    bool is_supported = false;
    bool is_active = false;
    
    uint64_t l1_cache_errors_corrected = 0;
    uint64_t l1_cache_errors_uncorrected = 0;
    
    uint64_t l2_cache_errors_corrected = 0;
    uint64_t l2_cache_errors_uncorrected = 0;
    
    uint64_t device_memory_errors_corrected = 0;
    uint64_t device_memory_errors_uncorrected = 0;
    
    uint64_t register_file_errors_corrected = 0;
    uint64_t register_file_errors_uncorrected = 0;
};

// ============================================================================
// GPUDisplay — Display ownership state
// ============================================================================

struct GPUDisplay {
    bool is_display_active = false;     // Is this GPU driving a display?
    int active_display_count = 0;       // Number of active displays
};

// ============================================================================
// GPUFaultEvent — Fault or reset event
// ============================================================================

enum class GPUFaultType {
    kXidError,         // NVIDIA Xid error
    kBusError,         // PCI/E bus error
    kMemoryError,      // Memory corruption detected
    kThermalShutdown,  // Thermal shutdown triggered
    kPowerFailure,     // Power delivery failure
    kUnknownFault,     // Unknown fault type
};

struct GPUFaultEvent {
    GPUFaultType fault_type = GPUFaultType::kUnknownFault;
    
    std::string event_id;              // Unique identifier for this event
    int xid_code = 0;                  // Xid error code where applicable
    
    std::chrono::system_clock::time_point timestamp;
    
    std::optional<std::string> description;
};

// ============================================================================
// GPUProviderState — Provider availability state
// ============================================================================

enum class GPUProviderState {
    kUnknown,          // State unknown
    kNotInstalled,     // No GPU provider available (no NVIDIA drivers)
    kUnreachable,      // Provider installed but unreachable (driver load issue)
    kAvailable,        // Provider available and functional
};

inline std::string to_string(GPUProviderState s) {
    switch (s) {
        case GPUProviderState::kUnknown:     return "unknown";
        case GPUProviderState::kNotInstalled:return "not_installed";
        case GPUProviderState::kUnreachable: return "unreachable";
        case GPUProviderState::kAvailable:   return "available";
    }
    return "unknown";
}

// ============================================================================
// GPUGlobalState — Global GPU subsystem state
// ============================================================================

struct GPUGlobalState {
    GPUProviderState provider_state = GPUProviderState::kUnknown;
    
    std::vector<GPUIdentity> devices;  // All detected GPU devices
    
    int total_device_count = 0;
    int available_device_count = 0;
};

// ============================================================================
// GPUSystemWideState — Derived system-wide state
// ============================================================================

struct GPUSystemWideState {
    bool any_fault = false;
    int throttled_device_count = 0;
    int degraded_device_count = 0;
};

// ============================================================================
// GPUDeviceEvidence — Provenance-bearing observation for a single device
// ============================================================================

struct GPUDeviceEvidence {
    std::string source;                // Source path or provider name
    std::string raw_data;              // Raw data from native source (may be truncated)
    
    std::chrono::system_clock::time_point acquired_at;
    std::optional<std::chrono::milliseconds> acquisition_duration_ms;
    
    bool is_complete = true;           // false if source was incomplete/truncated
    std::string error_message;         // Empty string if no error
    
    std::string evidence_id;
};

// ============================================================================
// GPUDeviceAssessment — Complete assessment of a single GPU device
// ============================================================================

struct GPUDeviceAssessment {
    GPUIdentity identity;
    GPUState state = GPUState::kUnknown;
    
    // Current readings (optional where not always available)
    GPUPower power;                    // Power data (defaults to 0 if unavailable)
    GPUTemperature temperature;        // Temperature data
    GPUClocks clocks;                  // Clock data
    GPUUtilization utilization;        // Utilization data
    GPUECC ecc;                        // ECC data
    GPUDisplay display;                // Display state
    
    std::vector<std::string> fault_event_ids;
    
    std::vector<std::string> evidence_ids;
    std::chrono::system_clock::time_point assessed_at;
};

// ============================================================================
// GPUAssessment — Complete assessment of all GPUs
// ============================================================================

struct GPUAssessment {
    GPUGlobalState global_state;
    
    // Individual device assessments (only present if known)
    std::vector<GPUDeviceAssessment> devices;
    
    // Derived state
    GPUSystemWideState system_wide_state;
    
    std::vector<std::string> evidence_ids;
    std::chrono::system_clock::time_point assessed_at;
};

// ============================================================================
// GPUEvent — Event generated by the GPU monitor
// ============================================================================

enum class GPUEventType {
    kDeviceAdded,
    kDeviceRemoved,
    kUtilizationWarning,
    kUtilizationCritical,
    kTemperatureWarning,
    kTemperatureCritical,
    kThrottlingStarted,
    kThrottlingStopped,
    kPowerLimitActive,
    kECCErrorCorrected,
    kECCErrorUncorrected,
    kXidError,
    kDisplayChanged,
};

struct GPUEvent {
    GPUEventType event_type = GPUEventType::kDeviceAdded;
    
    std::string event_id;
    std::chrono::system_clock::time_point timestamp;
    
    // Subject (which device or subsystem)
    std::string gpu_uuid;              // Device UUID where applicable (empty if global)
    
    double value_at_event = 0.0;       // Measurement value at event
    std::string threshold_type;        // e.g., "warning", "critical"
    double threshold_value = 0.0;      // Threshold that was crossed
    
    std::vector<std::string> evidence_ids;
    std::string description;
};

// ============================================================================
// GPUMonitorResult — Result of a GPU monitoring assessment
// ============================================================================

struct GPUMonitorResult {
    enum class Outcome {
        kSuccess,        // All assessments produced valid data
        kPartial,        // Some assessments failed (e.g., no GPUs present)
        kUnknown,        // No data available from any source
        kFailure,        // Provider/acquisition error occurred
    } outcome = Outcome::kUnknown;
    
    GPUAssessment assessment;          // Assessment data (defaults to initial state if unavailable)
    
    std::vector<GPUDeviceEvidence> evidences;
    
    std::vector<GPUEvent> events;
    
    std::chrono::system_clock::time_point assessed_at;
    std::optional<std::chrono::milliseconds> assessment_duration_ms;
    
    std::vector<std::string> uncertainty_notes;  // Notes about incomplete data
};

// ============================================================================
// GPUProvider — Interface for GPU health data providers
// ============================================================================

class GPUProvider {
public:
    virtual ~GPUProvider() = default;
    
    // Get provider identification info
    virtual std::string provider_name() const = 0;
    virtual std::string provider_version() const = 0;
    
    // Check if provider is available
    virtual bool is_available() const = 0;
    
    // Get global GPU state
    virtual GPUGlobalState get_global_state() = 0;
    
    // Get individual device assessment (may return nullopt if device not found)
    virtual std::optional<GPUDeviceAssessment> get_device_assessment(
        const std::string& gpu_uuid,
        std::chrono::system_clock::time_point now
    ) = 0;
    
    // Get all device assessments
    virtual std::vector<GPUDeviceAssessment> get_all_device_assessments(
        std::chrono::system_clock::time_point now
    ) = 0;
};

// ============================================================================
// GPUMonitorMetrics — Runtime metrics for the monitor
// ============================================================================

struct GPUMonitorMetrics {
    std::chrono::system_clock::time_point started_at;
    
    size_t observations = 0;
    size_t device_assessments = 0;
    
    struct SourceMetrics {
        size_t acquisitions = 0;
        size_t failures = 0;
        std::chrono::milliseconds total_acquisition_time{0};
    };
    std::map<std::string, SourceMetrics> source_metrics;
};

// ============================================================================
// GPUMonitorConfig — Configuration for the GPU monitor
// ============================================================================

struct GPUMonitorConfig {
    std::chrono::milliseconds observation_interval_ms{5000};
    
    int utilization_warning_percent = 70;
    int utilization_critical_percent = 90;
    
    int temperature_warning_celsius = 75;
    int temperature_critical_celsius = 90;
    
    size_t max_evidence_per_assessment = 16;
    std::chrono::hours evidence_retention_hours{24};
};

// ============================================================================
// Factory functions for creating result objects
// ============================================================================

GPUDeviceAssessment make_initial_gpu_device_assessment(const GPUIdentity& identity);
GPUAssessment make_initial_gpu_assessment();
GPUMonitorResult make_gpu_monitor_result(GPUMonitorResult::Outcome outcome);

}  // namespace rebuntu::modules::gpu_health_monitor
