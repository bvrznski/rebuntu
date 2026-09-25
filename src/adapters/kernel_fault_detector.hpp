// rebuntu::adapters::kernel_fault_detector — Kernel / Driver Fault Monitor (Phase 5.7)
//
// This module provides structured detection of kernel and driver faults:
//   - Kernel warnings, errors, oopses, panics
//   - Driver resets, hangs, timeouts
//   - Device failures and disconnections
//   - GPU-specific fault evidence (NVIDIA Xid, etc.)
//
// Design Philosophy:
//   * Monitoring ≠ recovery (this module observes, does not repair)
//   * UNKNOWN != false (missing evidence must be reported honestly)
//   * Evidence-based classification, not heuristic scores
//   * Preserve raw evidence while adding structured analysis

#pragma once

#include <memory>
#include <string>
#include <vector>
#include <chrono>
#include <unordered_map>
#include <optional>
#include <mutex>
#include <deque>

#include <runtime/contracts.hpp>
#include <system/core/contracts.hpp>

namespace rebuntu::adapters {

// ============================================================================
// KernelFaultClass — Categories of kernel/driver faults
// ============================================================================

enum class KernelFaultClass {
    kNone,                  // No fault detected
    kKernelWarning,         // Kernel warning message (printk with KERN_WARNING)
    kKernelError,           // Kernel error message (KERN_ERR)
    kKernelPanic,           // Kernel panic - system halt imminent or occurred
    kKernelOops,            // Kernel oops - unexpected exception
    kKernelBug,             // BUG() or WARN() triggered
    kKernelWarningStack,    // Stack trace伴随 warning
    
    // Driver-level faults
    kDriverTimeout,         // Driver operation timed out
    kDriverReset,           // Driver automatically reset
    kDriverHang,            // Driver appears hung/stalled
    kDriverUnresponsive,    // Driver not responding to commands
    
    // Device-specific faults
    kDeviceFailure,         // General device failure
    kDeviceDisconnect,      // Device physically disconnected
    kDeviceReconnect,       // Device reconnected after disconnection
    kDeviceNotReady,        // Device reported not ready
    
    // GPU-specific faults (provider-agnostic interface)
    kGPUSubsystemFault,     // GPU subsystem fault
    kGPUReset,              // GPU reset occurred
    kGPUHang,               // GPU appears hung
    kGPUTimeout,            // GPU operation timed out
    kXidError,              // NVIDIA XID error (provider-specific interpretation)
    
    // Memory/Resource faults
    kOOMKilled,             // Process killed by OOM killer
    kMemoryPressure,        // System under memory pressure
    kPageAllocationFail,    // Page allocation failed
    
    // Storage faults
    kBlockIOError,          // Block device I/O error
    kFileSystemError,       // Filesystem error (corruption, remount RO)
    
    // Thermal/Power faults
    kThermalTrip,           // Thermal trip point reached
    kThermalShutdown,       // System thermal shutdown
    kPowerLoss,             // Power loss event
    
    // System events
    kSystemHalt,            // System halt
    kSystemReboot,          // System reboot (clean or dirty)
    kBootFailure,           // Boot process failure
};

std::string to_string(KernelFaultClass c);

// ============================================================================
// Severity — Fault severity level
// ============================================================================

enum class Severity {
    kUnknown,     // Not assessed yet
    kInfo,        // Informational only
    kLow,         // Minor issue, monitor closely
    kMedium,      // Noticeable issue, investigate soon
    kHigh,        // Significant issue, urgent attention needed
    kCritical,    // Critical failure, immediate action required
};

std::string to_string(Severity s);

// ============================================================================
// EvidenceConfidence — Quality assessment of evidence
// ============================================================================

enum class EvidenceConfidence {
    kDirect,       // Direct observation from native source
    kDeduced,      // Deterministic deduction from observations
    kCorrelated,   // Correlation with other events (caution: not causation)
    kHypothesized, // Plausible hypothesis without direct evidence
};

std::string to_string(EvidenceConfidence c);

// ============================================================================
// FaultEvidence — Evidence of a kernel fault
// ============================================================================

struct FaultEvidence {
    std::string source;               // Source identifier (journald, dmesg, etc.)
    std::string raw_message;          // Original message text
    std::optional<std::string> unit;  // Related systemd unit if applicable
    
    // Timing
    using time_point = std::chrono::system_clock::time_point;
    time_point timestamp;
    std::optional<time_point> monotonic_time;  // Will be converted from system_clock for compatibility
    
    // Priority from journal (0-7, 0=critical)
    int priority = 6;  // Default INFO level
    
    // Structured fields
    std::unordered_map<std::string, std::string> fields;
    
    // Boot context
    std::string boot_id;
    std::optional<std::string> previous_boot_id;
};

// ============================================================================
// KernelFault — Detected kernel fault with full evidence chain
// ============================================================================

struct KernelFault {
    // Classification
    KernelFaultClass fault_class = KernelFaultClass::kNone;
    Severity severity = Severity::kUnknown;
    
    // Evidence
    std::string evidence_id;           // Unique ID for this fault's evidence
    std::vector<FaultEvidence> evidences;
    
    // Subject identification
    std::optional<std::string> subject;  // Affected service/device/unit
    std::optional<std::string> device_path;
    std::optional<int> pid;              // PID if process-related
    
    // Timing
    std::chrono::system_clock::time_point detected_at;
    std::optional<std::chrono::duration<double>> duration;
    
    // Context
    std::string boot_id;
    std::optional<std::string> machine_id;
    
    // Assessment
    std::vector<std::string> possible_causes;
    std::optional<std::string> most_likely_cause;
    std::vector<std::string> alternative_hypotheses;
    
    EvidenceConfidence confidence = EvidenceConfidence::kDirect;
    std::optional<std::string> confidence_limitations;
    
    // Verification
    bool verified = false;  // True only if postconditions independently verified
    
    // Recurrence tracking
    int occurrence_count = 1;
    std::chrono::system_clock::time_point first_occurred_at;
};

// ============================================================================
// KernelFaultDetectorConfig — Configuration for fault detection
// ============================================================================

struct KernelFaultDetectorConfig {
    // Time windows
    std::chrono::milliseconds event_correlation_window{std::chrono::minutes(5)};
    std::chrono::milliseconds fault_grouping_window{std::chrono::minutes(10)};
    
    // Thresholds
    int warning_count_threshold = 5;       // Warnings in window → elevated severity
    int error_count_threshold = 2;         // Errors in window → high severity
    
    // Recurrence detection
    std::chrono::milliseconds crash_loop_window{std::chrono::minutes(2)};
    int crash_loop_threshold = 3;          // Same fault type in window → crash loop
    
    // Evidence retention
    size_t max_evidences_per_fault = 16;
    size_t max_faults_retained = 256;
    
    // Source filtering
    bool enable_journald_source = true;
    bool enable_dmesg_source = false;      // Often requires special permissions
    
    // Output options
    bool preserve_raw_messages = true;
};

// ============================================================================
// KernelFaultDetectorMetrics — Runtime metrics for the detector
// ============================================================================

struct KernelFaultDetectorMetrics {
    std::chrono::system_clock::time_point started_at;
    
    size_t events_received = 0;
    size_t faults_detected = 0;
    size_t evidences_processed = 0;
    
    // Fault class counts
    std::unordered_map<std::string, size_t> fault_class_counts;
    
    // Severity distribution
    std::unordered_map<int, size_t> severity_distribution;
    
    // Source breakdown
    struct SourceMetrics {
        size_t events_received = 0;
        size_t faults_detected = 0;
    };
    std::unordered_map<std::string, SourceMetrics> source_metrics;
};

// ============================================================================
// KernelFaultDetector — Main kernel/driver fault detection engine
// ============================================================================

class KernelFaultDetector {
public:
    explicit KernelFaultDetector(const KernelFaultDetectorConfig& config);
    ~KernelFaultDetector();
    
    // Lifecycle management
    core::Outcome start();
    core::Outcome stop();
    bool is_running() const { return running_; }
    
    // Process events from various sources
    core::Outcome process_journal_event(
        const runtime::Event& event,
        std::chrono::system_clock::time_point acquisition_time);
    
    core::Outcome process_dmesg_line(
        const std::string& line,
        std::chrono::system_clock::time_point timestamp);
    
    // Get detected faults
    std::vector<KernelFault> get_detected_faults() const;
    std::vector<KernelFault> get_recent_faults(std::chrono::minutes window) const;
    
    // Get metrics
    KernelFaultDetectorMetrics metrics() const;
    
    // Configuration
    const KernelFaultDetectorConfig& config() const { return config_; }

private:
    KernelFaultDetectorConfig config_;
    bool running_ = false;
    mutable std::mutex mutex_;
    
    // Fault evidence storage (bounded)
    struct EvidenceBuffer {
        std::deque<FaultEvidence> recent_evidences;
        size_t total_count = 0;
    };
    std::unique_ptr<EvidenceBuffer> evidence_buffer_;
    
    // Detected faults
    std::vector<KernelFault> detected_faults_;
    
    // Fault classification helpers
    struct ClassificationState {
        KernelFaultClass fault_class = KernelFaultClass::kNone;
        Severity severity = Severity::kUnknown;
        std::optional<std::string> subject;
        std::vector<std::string> possible_causes;
        EvidenceConfidence confidence = EvidenceConfidence::kDirect;
    };
    
    // Event processing
    ClassificationState classify_event(
        const runtime::Event& event,
        std::chrono::system_clock::time_point acquisition_time);
    
    ClassificationState classify_dmesg_line(
        const std::string& line,
        std::chrono::system_clock::time_point timestamp);
    
    KernelFault create_fault_record(
        const ClassificationState& state,
        const FaultEvidence& primary_evidence,
        std::vector<FaultEvidence> additional_evidences = {});
    
    // Fault aggregation and deduplication
    void aggregate_faults(std::chrono::system_clock::time_point now);
    
    // Recurrence tracking
    struct RecurrenceTracker {
        struct FaultRecord {
            KernelFaultClass fault_class;
            std::optional<std::string> subject;
            std::chrono::system_clock::time_point timestamp;
            int count = 1;
        };
        
        std::vector<FaultRecord> recent_faults;
        std::chrono::milliseconds window;
    };
    std::unique_ptr<RecurrenceTracker> recurrence_tracker_;
    
    // Metrics tracking
    KernelFaultDetectorMetrics metrics_;
};

// ============================================================================
// SignatureRegistry — Known kernel/driver fault signatures
// ============================================================================

class SignatureRegistry {
public:
    static std::vector<std::string> default_signatures();
    
    // Helper functions for signature matching
    static bool contains_kernel_prefix(const std::string& message);
    static int extract_priority(const std::unordered_map<std::string, std::string>& fields);
};

// ============================================================================
// Factory functions
// ============================================================================

std::unique_ptr<KernelFaultDetector> make_kernel_fault_detector(
    const KernelFaultDetectorConfig& config = KernelFaultDetectorConfig{});

}  // namespace rebuntu::adapters