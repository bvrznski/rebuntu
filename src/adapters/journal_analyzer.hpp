// rebuntu::adapters::journal_analyzer — Deterministic Journal Analysis (Phase 5.4)
//
// This module provides deterministic-first journal analysis capable of:
//   - Grouping, correlating and classifying meaningful failures
//   - Identifying precursors to failures
//   - Generating causal candidates with evidence, confidence/uncertainty and alternatives
//   - Preserving raw evidence while adding structured analysis layers

#pragma once

#include "adapters/journal_normalizer.hpp"
#include <runtime/contracts.hpp>
#include <system/core/contracts.hpp>

#include <memory>
#include <string>
#include <vector>
#include <chrono>
#include <unordered_map>
#include <optional>
#include <mutex>
#include <deque>

namespace rebuntu::adapters {

// ============================================================================
// FailureClass — Categorical classification of failures
// ============================================================================

enum class FailureClass {
    kNone,                    // No failure detected
    kServiceFailure,          // Systemd unit entered failed state
    kOOM,                     // Out-of-memory event
    kKernelWarning,           // Kernel warning/error
    kKernelError,             // Kernel panic/fatal error
    kGPUFault,                // GPU driver fault/reset
    kBlockIOWrite,            // Block device write I/O error
    kFileSystemRemount,       // Filesystem remounted read-only
    kDeviceDisconnect,        // Device disconnect/unplug
    kThermalEvent,            // Thermal throttling/warning
    kHardwareFailure,         // Hardware failure (SMART, ECC, etc.)
    kKernelCrash,             // Kernel crash/dump
    kServiceCrashLoop,        // Service restart loop (excessive restarts)
    kSystemHalt,              // System halt/power-off event
    kSystemReboot,            // System reboot event
    kBootFailure,             // Boot process failure
};

std::string to_string(FailureClass c);

// ============================================================================
// Severity — Analysis severity level
// ============================================================================

enum class Severity {
    kUnknown,     // Not assessed yet
    kInfo,        // Informational only
    kLow,         // Minor issue, no action needed
    kMedium,      // Noticeable issue, monitor closely
    kHigh,        // Significant issue, investigate soon
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
// AnalysisResult — Output of journal analysis for a single event/window
// ============================================================================

struct AnalysisResult {
    // Classification
    FailureClass failure_class = FailureClass::kNone;
    Severity severity = Severity::kUnknown;
    
    // Evidence chain
    std::string evidence_id;              // Unique ID for this result's evidence
    std::vector<std::string> evidence_references;  // References to source events
    
    // Timing information
    std::chrono::system_clock::time_point observed_at;
    std::optional<std::chrono::system_clock::time_point> start_time;
    std::optional<std::chrono::duration<double>> duration;
    
    // Context
    std::string subject;     // What was affected (unit, device, etc.)
    std::string boot_id;                    // Boot context for correlation
    std::string machine_id;                 // Machine identity
    
    // Assessment with alternatives
    std::vector<std::string> possible_causes;
    std::optional<std::string> most_likely_cause;
    std::vector<std::string> alternative_hypotheses;
    
    // Confidence assessment (structured uncertainty, not fake numeric scores)
    EvidenceConfidence confidence = EvidenceConfidence::kDirect;
    std::optional<std::string> confidence_limitations;
    
    // Verification status
    bool verified = false;  // True only if postconditions were independently verified
    
    // Raw references for forensic recovery
    std::vector<std::string> raw_evidence_pointers;
};

// ============================================================================
// FailureSignature — Pattern defining a known failure type
// ============================================================================

struct FailureSignature {
    std::string id;                    // Unique identifier (e.g., "oom-killer-detected")
    
    FailureClass failure_class;        // What class of failure this represents
    
    struct Condition {
        enum class Type {
            kContains,           // Message contains substring
            kPrefix,             // Message starts with prefix
            kPriorityAtLeast,    // Priority <= threshold (0-7, 0=critical)
            kUnitEquals,         // Unit name equals value
        };
        
        Type type;
        std::string pattern;
    };
    
    std::vector<Condition> conditions;
    
    Severity default_severity;
    std::optional<std::chrono::milliseconds> cooldown_period;
    
    std::string description;
    std::vector<std::string> possible_causes;
};

// ============================================================================
// EventWindow — Temporal grouping of related events
// ============================================================================

struct EventWindow {
    std::string id;                          // Unique window ID (boot + time range)
    
    std::chrono::system_clock::time_point start_time;
    std::chrono::system_clock::time_point end_time;
    
    std::vector<std::shared_ptr<const AnalysisResult>> analysis_results;
    
    Severity aggregate_severity = Severity::kUnknown;
    FailureClass primary_failure_class = FailureClass::kNone;
    
    std::string boot_id;
    std::optional<std::string> previous_boot_correlated_event;
    
    bool is_complete() const { return end_time.time_since_epoch().count() != 0; }
};

// ============================================================================
// JournalAnalyzerMetrics — Runtime metrics for the analyzer
// ============================================================================

struct JournalAnalyzerMetrics {
    std::chrono::system_clock::time_point started_at;
    
    size_t events_analyzed = 0;
    size_t events_classified = 0;
    size_t failures_detected = 0;
    
    size_t windows_created = 0;
    size_t correlations_found = 0;
    
    std::unordered_map<std::string, size_t> classification_counts;
    std::unordered_map<int, size_t> severity_counts;
};

// ============================================================================
// JournalAnalyzerConfig — Configuration for journal analysis
// ============================================================================

struct JournalAnalyzerConfig {
    std::chrono::milliseconds event_correlation_window{std::chrono::minutes(5)};
    std::chrono::milliseconds failure_grouping_window{std::chrono::minutes(10)};
    
    size_t max_events_per_window = 1000;
    size_t max_windows_retained = 128;
    
    int service_restart_threshold = 5;
    std::chrono::milliseconds crash_loop_window{std::chrono::minutes(2)};
    
    bool preserve_raw_pointers = true;
    size_t max_raw_evidence_per_result = 16;
};

// ============================================================================
// CorrelationEngine — Event correlation and grouping
// ============================================================================

class CorrelationEngine {
public:
    explicit CorrelationEngine(std::chrono::milliseconds window = std::chrono::minutes(5));
    
    void add_event(const AnalysisResult& result);
    std::vector<std::shared_ptr<const AnalysisResult>> get_correlated_events() const;
    size_t cleanup();
    
    struct CorrelationSummary {
        size_t event_count = 0;
        std::vector<std::string> subjects;
        std::vector<FailureClass> failure_classes;
        Severity max_severity = Severity::kUnknown;
    };
    CorrelationSummary summary() const;

private:
    std::chrono::milliseconds window_;
    
    mutable std::mutex mutex_;
    std::deque<std::shared_ptr<const AnalysisResult>> events_;
};

// ============================================================================
// JournalAnalyzer — Main journal analysis engine
// ============================================================================

class JournalAnalyzer {
public:
    explicit JournalAnalyzer(const JournalAnalyzerConfig& config);
    ~JournalAnalyzer();
    
    std::vector<AnalysisResult> analyze_events(
        const std::vector<NormalizedEvent>& events,
        std::chrono::system_clock::time_point analysis_time);
    
    std::vector<EventWindow> event_windows() const;
    JournalAnalyzerMetrics metrics() const;
    JournalAnalyzerConfig config() const;
    void reset();

private:
    JournalAnalyzerConfig config_;
    
    mutable std::mutex mutex_;
    
    std::deque<std::shared_ptr<EventWindow>> event_windows_;
    
    struct ServiceState {
        std::vector<std::chrono::system_clock::time_point> restart_times;
        bool in_crash_loop = false;
    };
    std::unordered_map<std::string, ServiceState> service_states_;
    
    std::vector<FailureSignature> signatures_;
    
    JournalAnalyzerMetrics metrics_;
    
    size_t next_window_id_ = 0;
    
    std::unique_ptr<CorrelationEngine> correlation_engine_;
    
    std::vector<AnalysisResult> classify_events(
        const std::vector<NormalizedEvent>& events,
        std::chrono::system_clock::time_point analysis_time);
    
    void update_service_state(const AnalysisResult& result);
    
    EventWindow create_or_update_window(
        const std::vector<AnalysisResult>& results,
        std::chrono::system_clock::time_point analysis_time);
};

// ============================================================================
// SignatureRegistry — Known failure signature definitions
// ============================================================================

class SignatureRegistry {
public:
    static std::vector<FailureSignature> default_signatures();
    
    static FailureSignature oom_killer_signature();
    static FailureSignature service_failure_signature();
    static FailureSignature kernel_panic_signature();
    static FailureSignature gpu_fault_signature();
    static FailureSignature block_io_error_signature();
    static FailureSignature filesystem_remount_signature();
    static FailureSignature thermal_event_signature();
};

// ============================================================================
// Factory functions
// ============================================================================

std::unique_ptr<JournalAnalyzer> make_journal_analyzer(
    const JournalAnalyzerConfig& config = JournalAnalyzerConfig{});

}  // namespace rebuntu::adapters