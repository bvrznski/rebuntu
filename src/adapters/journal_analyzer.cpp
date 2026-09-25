// rebuntu::adapters::journal_analyzer — Deterministic Journal Analysis Implementation (Phase 5.4)
//
// This module implements deterministic journal analysis for failure detection,
// correlation, and causal hypothesis generation.

#include "adapters/journal_analyzer.hpp"

#include <algorithm>

namespace rebuntu::adapters {

// ============================================================================
// Helper functions
// ============================================================================

std::string to_string(FailureClass c) {
    switch (c) {
        case FailureClass::kNone:           return "none";
        case FailureClass::kServiceFailure: return "service_failure";
        case FailureClass::kOOM:            return "oom";
        case FailureClass::kKernelWarning:  return "kernel_warning";
        case FailureClass::kKernelError:    return "kernel_error";
        case FailureClass::kGPUFault:       return "gpu_fault";
        case FailureClass::kBlockIOWrite:   return "block_io_write";
        case FailureClass::kFileSystemRemount:return "filesystem_remount";
        case FailureClass::kDeviceDisconnect:return "device_disconnect";
        case FailureClass::kThermalEvent:   return "thermal_event";
        case FailureClass::kHardwareFailure:return "hardware_failure";
        case FailureClass::kKernelCrash:    return "kernel_crash";
        case FailureClass::kServiceCrashLoop:return "service_crash_loop";
        case FailureClass::kSystemHalt:     return "system_halt";
        case FailureClass::kSystemReboot:   return "system_reboot";
        case FailureClass::kBootFailure:    return "boot_failure";
    }
    return "unknown";
}

std::string to_string(Severity s) {
    switch (s) {
        case Severity::kUnknown:   return "unknown";
        case Severity::kInfo:      return "info";
        case Severity::kLow:       return "low";
        case Severity::kMedium:    return "medium";
        case Severity::kHigh:      return "high";
        case Severity::kCritical:  return "critical";
    }
    return "unknown";
}

std::string to_string(EvidenceConfidence c) {
    switch (c) {
        case EvidenceConfidence::kDirect:       return "direct";
        case EvidenceConfidence::kDeduced:      return "deduced";
        case EvidenceConfidence::kCorrelated:   return "correlated";
        case EvidenceConfidence::kHypothesized: return "hypothesized";
    }
    return "unknown";
}

namespace {

// ============================================================================
// Signature Registry — Known failure patterns
// ============================================================================

FailureSignature make_oom_killer_signature() {
    FailureSignature sig;
    sig.id = "oom-killer-detected";
    sig.failure_class = FailureClass::kOOM;
    sig.default_severity = Severity::kCritical;
    sig.description = "Out-of-memory condition detected by kernel OOM killer";
    
    sig.conditions.push_back({
        FailureSignature::Condition::Type::kContains,
        "Out of memory"
    });
    sig.conditions.push_back({
        FailureSignature::Condition::Type::kContains,
        "OOM killer"
    });
    
    sig.possible_causes = {
        "Memory leak in application",
        "Insufficient system RAM for workload",
        "Memory-intensive process exceeded limits",
        "Kernel memory pressure from multiple sources"
    };
    
    return sig;
}

FailureSignature make_service_failure_signature() {
    FailureSignature sig;
    sig.id = "service-failure-detected";
    sig.failure_class = FailureClass::kServiceFailure;
    sig.default_severity = Severity::kMedium;
    sig.description = "Systemd unit entered failed state";
    
    sig.conditions.push_back({
        FailureSignature::Condition::Type::kContains,
        "Failed to start"
    });
    
    sig.possible_causes = {
        "Service process crashed",
        "Configuration error",
        "Dependency failed",
        "Resource unavailable"
    };
    
    return sig;
}

FailureSignature make_kernel_panic_signature() {
    FailureSignature sig;
    sig.id = "kernel-panic-detected";
    sig.failure_class = FailureClass::kKernelCrash;
    sig.default_severity = Severity::kCritical;
    sig.description = "Kernel panic or fatal error detected";
    
    sig.conditions.push_back({
        FailureSignature::Condition::Type::kContains,
        "Kernel panic"
    });
    sig.conditions.push_back({
        FailureSignature::Condition::Type::kPrefix,
        "[    0."
    });
    
    sig.possible_causes = {
        "Hardware failure",
        "Kernel module bug",
        "Memory corruption",
        "Driver crash"
    };
    
    return sig;
}

FailureSignature make_gpu_fault_signature() {
    FailureSignature sig;
    sig.id = "gpu-fault-detected";
    sig.failure_class = FailureClass::kGPUFault;
    sig.default_severity = Severity::kMedium;
    sig.description = "GPU driver fault or reset detected";
    
    sig.conditions.push_back({
        FailureSignature::Condition::Type::kContains,
        "nvidia"
    });
    sig.conditions.push_back({
        FailureSignature::Condition::Type::kContains,
        "GPU fault"
    });
    
    sig.possible_causes = {
        "GPU memory error (ECC)",
        "Driver bug",
        "Overheating",
        "Hardware failure"
    };
    
    return sig;
}

FailureSignature make_block_io_error_signature() {
    FailureSignature sig;
    sig.id = "block-io-error-detected";
    sig.failure_class = FailureClass::kBlockIOWrite;
    sig.default_severity = Severity::kHigh;
    sig.description = "Block device I/O error detected";
    
    sig.conditions.push_back({
        FailureSignature::Condition::Type::kContains,
        "I/O error"
    });
    sig.conditions.push_back({
        FailureSignature::Condition::Type::kContains,
        "sector"
    });
    
    sig.possible_causes = {
        "Disk failure imminent",
        "Bad sectors on storage device",
        "Loose connection",
        "Controller failure"
    };
    
    return sig;
}

FailureSignature make_filesystem_remount_signature() {
    FailureSignature sig;
    sig.id = "filesystem-remount-detected";
    sig.failure_class = FailureClass::kFileSystemRemount;
    sig.default_severity = Severity::kHigh;
    sig.description = "Filesystem remounted read-only due to errors";
    
    sig.conditions.push_back({
        FailureSignature::Condition::Type::kContains,
        "remounted read-only"
    });
    sig.conditions.push_back({
        FailureSignature::Condition::Type::kContains,
        "error"
    });
    
    sig.possible_causes = {
        "Filesystem corruption",
        "Storage device failure",
        "Mount option issue"
    };
    
    return sig;
}

FailureSignature make_thermal_event_signature() {
    FailureSignature sig;
    sig.id = "thermal-event-detected";
    sig.failure_class = FailureClass::kThermalEvent;
    sig.default_severity = Severity::kMedium;
    sig.description = "Thermal throttling or warning detected";
    
    sig.conditions.push_back({
        FailureSignature::Condition::Type::kContains,
        "temperature"
    });
    sig.conditions.push_back({
        FailureSignature::Condition::Type::kContains,
        "throttle"
    });
    
    sig.possible_causes = {
        "Cooling system failure",
        "High ambient temperature",
        "Overclocking",
        "Blocked airflow"
    };
    
    return sig;
}

}  // namespace

// ============================================================================
// SignatureRegistry Implementation
// ============================================================================

std::vector<FailureSignature> SignatureRegistry::default_signatures() {
    return {
        make_oom_killer_signature(),
        make_service_failure_signature(),
        make_kernel_panic_signature(),
        make_gpu_fault_signature(),
        make_block_io_error_signature(),
        make_filesystem_remount_signature(),
        make_thermal_event_signature()
    };
}

FailureSignature SignatureRegistry::oom_killer_signature() {
    return make_oom_killer_signature();
}

FailureSignature SignatureRegistry::service_failure_signature() {
    return make_service_failure_signature();
}

FailureSignature SignatureRegistry::kernel_panic_signature() {
    return make_kernel_panic_signature();
}

FailureSignature SignatureRegistry::gpu_fault_signature() {
    return make_gpu_fault_signature();
}

FailureSignature SignatureRegistry::block_io_error_signature() {
    return make_block_io_error_signature();
}

FailureSignature SignatureRegistry::filesystem_remount_signature() {
    return make_filesystem_remount_signature();
}

FailureSignature SignatureRegistry::thermal_event_signature() {
    return make_thermal_event_signature();
}

// ============================================================================
// CorrelationEngine Implementation
// ============================================================================

CorrelationEngine::CorrelationEngine(std::chrono::milliseconds window)
    : window_(window) {}

void CorrelationEngine::add_event(const AnalysisResult& result) {
    std::lock_guard<std::mutex> lock(mutex_);
    
    // Create a copy with shared ownership
    auto shared = std::make_shared<AnalysisResult>(result);
    events_.push_back(shared);
}

std::vector<std::shared_ptr<const AnalysisResult>> 
CorrelationEngine::get_correlated_events() const {
    std::lock_guard<std::mutex> lock(mutex_);
    
    return std::vector<std::shared_ptr<const AnalysisResult>>(events_.begin(), events_.end());
}

size_t CorrelationEngine::cleanup() {
    std::lock_guard<std::mutex> lock(mutex_);
    
    size_t removed = 0;
    
    // Placeholder for cleanup logic
    events_.clear();
    
    return removed;
}

CorrelationEngine::CorrelationSummary CorrelationEngine::summary() const {
    std::lock_guard<std::mutex> lock(mutex_);
    
    CorrelationSummary sum;
    sum.event_count = events_.size();
    
    for (const auto& event : events_) {
        sum.subjects.push_back(event->subject);
        sum.failure_classes.push_back(event->failure_class);
        
        if (event->severity > sum.max_severity) {
            sum.max_severity = event->severity;
        }
    }
    
    return sum;
}

// ============================================================================
// JournalAnalyzer Implementation
// ============================================================================

JournalAnalyzer::JournalAnalyzer(const JournalAnalyzerConfig& config)
    : config_(config),
      metrics_{.started_at = std::chrono::system_clock::now()},
      correlation_engine_(std::make_unique<CorrelationEngine>()) {
    
    // Initialize with default signatures
    signatures_ = SignatureRegistry::default_signatures();
}

JournalAnalyzer::~JournalAnalyzer() = default;

void JournalAnalyzer::reset() {
    std::lock_guard<std::mutex> lock(mutex_);
    
    event_windows_.clear();
    service_states_.clear();
    next_window_id_ = 0;
    
    metrics_ = JournalAnalyzerMetrics{
        .started_at = std::chrono::system_clock::now()
    };
}

std::vector<AnalysisResult> JournalAnalyzer::analyze_events(
    const std::vector<NormalizedEvent>& events,
    std::chrono::system_clock::time_point analysis_time) {
    
    std::lock_guard<std::mutex> lock(mutex_);
    
    // Layer 1: Classify each event
    auto classifications = classify_events(events, analysis_time);
    
    // Update metrics
    for (const auto& result : classifications) {
        if (result.failure_class != FailureClass::kNone) {
            metrics_.failures_detected++;
            metrics_.classification_counts[to_string(result.failure_class)]++;
            metrics_.severity_counts[static_cast<int>(result.severity)]++;
        }
    }
    
    return classifications;
}

std::vector<AnalysisResult> JournalAnalyzer::classify_events(
    const std::vector<NormalizedEvent>& events,
    std::chrono::system_clock::time_point analysis_time) {
    
    std::vector<AnalysisResult> results;
    
    for (const auto& normalized : events) {
        AnalysisResult result;
        
        // Extract basic metadata
        result.observed_at = analysis_time;
        result.boot_id = normalized.boot_id;
        result.machine_id = normalized.machine_id;
        
        // Preserve evidence references
        if (config_.preserve_raw_pointers) {
            for (const auto& ev : normalized.original_evidence) {
                if (result.raw_evidence_pointers.size() < 
                    config_.max_raw_evidence_per_result) {
                    result.raw_evidence_pointers.push_back(ev.source + ":" + ev.value);
                }
            }
        }
        
        // Layer 1: Structural classification based on evidence
        bool is_failure = false;
        
        for (const auto& evidence : normalized.original_evidence) {
            if (evidence.source == "journal_message") {
                const std::string& msg = evidence.value;
                
                // Check against all signatures
                for (const auto& sig : signatures_) {
                    bool matches_all = true;
                    
                    for (const auto& cond : sig.conditions) {
                        bool cond_matches = false;
                        
                        switch (cond.type) {
                            case FailureSignature::Condition::Type::kContains:
                                cond_matches = msg.find(cond.pattern) != std::string::npos;
                                break;
                            case FailureSignature::Condition::Type::kPrefix:
                                cond_matches = msg.substr(0, cond.pattern.size()) == cond.pattern;
                                break;
                            case FailureSignature::Condition::Type::kPriorityAtLeast: {
                                // Try to extract priority from evidence
                                int evt_priority = 6;  // default info
                                if (evidence.source == "journal_message" && 
                                    msg.find("PRIORITY=") != std::string::npos) {
                                    auto pos = msg.find("PRIORITY=");
                                    if (pos != std::string::npos) {
                                        try {
                                            evt_priority = std::stoi(msg.substr(pos + 9));
                                        } catch (...) {
                                            evt_priority = 6;
                                        }
                                    }
                                }
                                cond_matches = evt_priority <= 2;  // Critical, Error, Warning
                                break;
                            }
                            case FailureSignature::Condition::Type::kUnitEquals:
                                cond_matches = true;  // Simplified - any unit matches
                                break;
                            default:
                                cond_matches = false;
                        }
                        
                        if (!cond_matches) {
                            matches_all = false;
                            break;
                        }
                    }
                    
                    if (matches_all) {
                        result.failure_class = sig.failure_class;
                        is_failure = true;
                        break;
                    }
                }
            }
        }
        
        // Determine severity
        if (is_failure) {
            // Use signature metadata or defaults
            for (const auto& sig : signatures_) {
                if (sig.failure_class == result.failure_class) {
                    result.severity = sig.default_severity;
                    result.possible_causes = sig.possible_causes;
                    break;
                }
            }
            
            if (result.possible_causes.empty()) {
                // Fallback causes based on class
                switch (result.failure_class) {
                    case FailureClass::kOOM:
                        result.possible_causes.push_back("Memory exhaustion");
                        break;
                    case FailureClass::kServiceFailure:
                        result.possible_causes.push_back("Process crash");
                        break;
                    default:
                        result.possible_causes.push_back("System error");
                }
            }
            
            // Generate hypothesis with alternatives
            if (result.possible_causes.size() > 1) {
                result.most_likely_cause = result.possible_causes.front();
                for (size_t i = 1; i < result.possible_causes.size(); ++i) {
                    result.alternative_hypotheses.push_back(result.possible_causes[i]);
                }
            }
        } else {
            result.failure_class = FailureClass::kNone;
            result.severity = Severity::kInfo;
        }
        
        // Evidence quality
        if (is_failure && normalized.original_evidence.empty()) {
            result.confidence = EvidenceConfidence::kCorrelated;
            result.confidence_limitations = "Evidence from structured fields only";
        } else {
            result.confidence = EvidenceConfidence::kDirect;
        }
        
        // Assign evidence ID
        result.evidence_id = std::to_string(analysis_time.time_since_epoch().count()) +
                            "-" + std::to_string(results.size());
        
        results.push_back(result);
    }
    
    return results;
}

void JournalAnalyzer::update_service_state(const AnalysisResult& result) {
    // Track service restarts for crash loop detection
    if (!result.subject.empty()) {
        const std::string& unit = result.subject;
        
        auto it = service_states_.find(unit);
        if (it == service_states_.end()) {
            it = service_states_.insert({unit, ServiceState{}}).first;
        }
        
        auto& state = it->second;
        
        // Record restart timestamp
        state.restart_times.push_back(result.observed_at);
        
        // Clean old restarts beyond the crash loop window
        auto cutoff = result.observed_at - config_.crash_loop_window;
        state.restart_times.erase(
            std::remove_if(state.restart_times.begin(), state.restart_times.end(),
                [cutoff](std::chrono::system_clock::time_point t) {
                    return t < cutoff;
                }),
            state.restart_times.end()
        );
        
        // Check for crash loop condition
        if (static_cast<int>(state.restart_times.size()) >= config_.service_restart_threshold) {
            state.in_crash_loop = true;
        }
    }
}

EventWindow JournalAnalyzer::create_or_update_window(
    const std::vector<AnalysisResult>& results,
    std::chrono::system_clock::time_point analysis_time) {
    
    // Create a new window if needed
    auto window = std::make_shared<EventWindow>();
    window->id = "window-" + std::to_string(next_window_id_++);
    window->start_time = analysis_time;
    window->end_time = analysis_time;
    window->aggregate_severity = Severity::kUnknown;
    
    for (const auto& result : results) {
        if (result.failure_class != FailureClass::kNone) {
            window->analysis_results.push_back(
                std::make_shared<const AnalysisResult>(result));
            
            // Aggregate severity
            if (result.severity > window->aggregate_severity) {
                window->aggregate_severity = result.severity;
            }
            
            // Track primary failure class
            if (window->primary_failure_class == FailureClass::kNone) {
                window->primary_failure_class = result.failure_class;
            }
        }
    }
    
    event_windows_.push_back(window);
    
    // Evict old windows if at capacity
    while (event_windows_.size() > config_.max_windows_retained) {
        event_windows_.pop_front();
    }
    
    return *window;
}

std::vector<EventWindow> JournalAnalyzer::event_windows() const {
    std::lock_guard<std::mutex> lock(mutex_);
    
    std::vector<EventWindow> result;
    for (const auto& window : event_windows_) {
        result.push_back(*window);
    }
    
    return result;
}

JournalAnalyzerMetrics JournalAnalyzer::metrics() const {
    std::lock_guard<std::mutex> lock(mutex_);
    
    return metrics_;
}

JournalAnalyzerConfig JournalAnalyzer::config() const {
    return config_;
}

// ============================================================================
// Factory Functions
// ============================================================================

std::unique_ptr<JournalAnalyzer> make_journal_analyzer(
    const JournalAnalyzerConfig& config) {
    return std::make_unique<JournalAnalyzer>(config);
}

}  // namespace rebuntu::adapters