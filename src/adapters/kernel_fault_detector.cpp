// rebuntu::adapters::kernel_fault_detector — Kernel / Driver Fault Monitor Implementation (Phase 5.7)
//
// This module provides structured detection of kernel and driver faults.

#include "adapters/kernel_fault_detector.hpp"

#include <algorithm>
#include <cctype>
#include <sstream>

namespace rebuntu::adapters {

// ============================================================================
// KernelFaultClass string conversion
// ============================================================================

std::string to_string(KernelFaultClass c) {
    switch (c) {
        case KernelFaultClass::kNone:              return "none";
        case KernelFaultClass::kKernelWarning:     return "kernel_warning";
        case KernelFaultClass::kKernelError:       return "kernel_error";
        case KernelFaultClass::kKernelPanic:       return "kernel_panic";
        case KernelFaultClass::kKernelOops:        return "kernel_oops";
        case KernelFaultClass::kKernelBug:         return "kernel_bug";
        case KernelFaultClass::kKernelWarningStack:return "kernel_warning_stack";
        
        case KernelFaultClass::kDriverTimeout:     return "driver_timeout";
        case KernelFaultClass::kDriverReset:       return "driver_reset";
        case KernelFaultClass::kDriverHang:        return "driver_hang";
        case KernelFaultClass::kDriverUnresponsive:return "driver_unresponsive";
        
        case KernelFaultClass::kDeviceFailure:     return "device_failure";
        case KernelFaultClass::kDeviceDisconnect:  return "device_disconnect";
        case KernelFaultClass::kDeviceReconnect:   return "device_reconnect";
        case KernelFaultClass::kDeviceNotReady:    return "device_not_ready";
        
        case KernelFaultClass::kGPUSubsystemFault: return "gpu_subsystem_fault";
        case KernelFaultClass::kGPUReset:          return "gpu_reset";
        case KernelFaultClass::kGPUHang:           return "gpu_hang";
        case KernelFaultClass::kGPUTimeout:        return "gpu_timeout";
        case KernelFaultClass::kXidError:          return "xid_error";
        
        case KernelFaultClass::kOOMKilled:         return "oom_killed";
        case KernelFaultClass::kMemoryPressure:    return "memory_pressure";
        case KernelFaultClass::kPageAllocationFail:return "page_allocation_fail";
        
        case KernelFaultClass::kBlockIOError:      return "block_io_error";
        case KernelFaultClass::kFileSystemError:   return "filesystem_error";
        
        case KernelFaultClass::kThermalTrip:       return "thermal_trip";
        case KernelFaultClass::kThermalShutdown:   return "thermal_shutdown";
        case KernelFaultClass::kPowerLoss:         return "power_loss";
        
        case KernelFaultClass::kSystemHalt:        return "system_halt";
        case KernelFaultClass::kSystemReboot:      return "system_reboot";
        case KernelFaultClass::kBootFailure:       return "boot_failure";
    }
    return "unknown_fault_class";
}

// ============================================================================
// Severity string conversion
// ============================================================================

std::string to_string(Severity s) {
    switch (s) {
        case Severity::kUnknown:     return "unknown";
        case Severity::kInfo:        return "info";
        case Severity::kLow:         return "low";
        case Severity::kMedium:      return "medium";
        case Severity::kHigh:        return "high";
        case Severity::kCritical:    return "critical";
    }
    return "unknown_severity";
}

// ============================================================================
// EvidenceConfidence string conversion
// ============================================================================

std::string to_string(EvidenceConfidence c) {
    switch (c) {
        case EvidenceConfidence::kDirect:       return "direct";
        case EvidenceConfidence::kDeduced:      return "deduced";
        case EvidenceConfidence::kCorrelated:   return "correlated";
        case EvidenceConfidence::kHypothesized: return "hypothesized";
    }
    return "unknown_confidence";
}

// ============================================================================
// KernelFaultDetector implementation
// ============================================================================

KernelFaultDetector::KernelFaultDetector(const KernelFaultDetectorConfig& config)
    : config_(config),
      evidence_buffer_(std::make_unique<EvidenceBuffer>()),
      recurrence_tracker_(std::make_unique<RecurrenceTracker>()) {
    
    // Initialize metrics
    metrics_.started_at = std::chrono::system_clock::now();
    
    // Configure recurrence tracker
    recurrence_tracker_->window = config_.crash_loop_window;
}

KernelFaultDetector::~KernelFaultDetector() {
    stop();
}

core::Outcome KernelFaultDetector::start() {
    if (running_) {
        return core::Outcome::success();  // Already running
    }
    
    running_ = true;
    return core::Outcome::success();
}

core::Outcome KernelFaultDetector::stop() {
    if (!running_) {
        return core::Outcome::completed();
    }
    
    running_ = false;
    return core::Outcome::success();
}

core::Outcome KernelFaultDetector::process_journal_event(
    const runtime::Event& event,
    std::chrono::system_clock::time_point acquisition_time) {
    
    if (!running_) {
        return core::Outcome::failure("E_NOT_RUNNING", "Detector not running");
    }
    
    // Extract evidence from the journal event
    std::vector<FaultEvidence> evidences;
    
    for (const auto& e : event.evidence) {
        FaultEvidence fe;
        fe.source = "journald";
        fe.raw_message = e.value;
        fe.timestamp = acquisition_time;
        fe.priority = 6;  // Default INFO level if not specified
        evidences.push_back(std::move(fe));
    }
    
    metrics_.events_received++;
    metrics_.evidences_processed += evidences.size();
    
    // Update source metrics
    auto& src_metrics = metrics_.source_metrics["journald"];
    src_metrics.events_received++;
    
    // Classify each evidence and create fault records
    for (auto& fe : evidences) {
        auto state = classify_event(event, acquisition_time);
        
        if (state.fault_class != KernelFaultClass::kNone) {
            auto fault = create_fault_record(state, fe, evidences);
            
            // Check for recurrence
            aggregate_faults(acquisition_time);
            
            metrics_.faults_detected++;
            metrics_.fault_class_counts[to_string(fault.fault_class)]++;
            metrics_.severity_distribution[static_cast<int>(fault.severity)]++;
        }
    }
    
    return core::Outcome::success();
}

core::Outcome KernelFaultDetector::process_dmesg_line(
    const std::string& line,
    std::chrono::system_clock::time_point timestamp) {
    
    if (!running_) {
        return core::Outcome::failure("E_NOT_RUNNING", "Detector not running");
    }
    
    // Extract priority from dmesg line
    int priority = 6;  // Default INFO level
    
    // Check for kernel log prefix like "<1>", "<2>", etc.
    if (!line.empty() && line[0] == '<') {
        size_t end = line.find('>');
        if (end != std::string::npos) {
            try {
                priority = std::stoi(line.substr(1, end - 1));
            } catch (...) {
                priority = 6;
            }
        }
    }
    
    // Create evidence
    FaultEvidence fe;
    fe.source = "dmesg";
    fe.raw_message = line;
    fe.timestamp = timestamp;
    fe.priority = priority;
    
    metrics_.events_received++;
    metrics_.evidences_processed++;
    
    // Update source metrics
    auto& src_metrics = metrics_.source_metrics["dmesg"];
    src_metrics.events_received++;
    
    // Classify and create fault record if applicable
    auto state = classify_dmesg_line(line, timestamp);
    
    if (state.fault_class != KernelFaultClass::kNone) {
        std::vector<FaultEvidence> evidences{fe};
        auto fault = create_fault_record(state, fe, evidences);
        
        aggregate_faults(timestamp);
        
        metrics_.faults_detected++;
        metrics_.fault_class_counts[to_string(fault.fault_class)]++;
        metrics_.severity_distribution[static_cast<int>(fault.severity)]++;
    }
    
    return core::Outcome::success();
}

std::vector<KernelFault> KernelFaultDetector::get_detected_faults() const {
    std::lock_guard<std::mutex> lock(mutex_);
    return detected_faults_;
}

std::vector<KernelFault> KernelFaultDetector::get_recent_faults(
    std::chrono::minutes window) const {
    
    auto now = std::chrono::system_clock::now();
    auto cutoff = now - window;
    
    std::lock_guard<std::mutex> lock(mutex_);
    
    std::vector<KernelFault> recent;
    for (const auto& fault : detected_faults_) {
        if (fault.first_occurred_at >= cutoff) {
            recent.push_back(fault);
        }
    }
    
    return recent;
}

KernelFaultDetectorMetrics KernelFaultDetector::metrics() const {
    std::lock_guard<std::mutex> lock(mutex_);
    return metrics_;
}

// ============================================================================
// Classification methods
// ============================================================================

KernelFaultDetector::ClassificationState 
KernelFaultDetector::classify_event(
    const runtime::Event& event,
    [[maybe_unused]] std::chrono::system_clock::time_point acquisition_time) {
    
    ClassificationState state;
    
    // Look for kernel-related keywords in evidence
    for (const auto& e : event.evidence) {
        std::string msg_lower = e.value;
        std::transform(msg_lower.begin(), msg_lower.end(), msg_lower.begin(),
                       [](unsigned char c) { return std::tolower(c); });
        
        // Check for panic
        if (msg_lower.find("panic") != std::string::npos) {
            state.fault_class = KernelFaultClass::kKernelPanic;
            state.severity = Severity::kCritical;
            state.confidence = EvidenceConfidence::kDirect;
            break;
        }
        
        // Check for oops
        if (msg_lower.find("oops") != std::string::npos) {
            state.fault_class = KernelFaultClass::kKernelOops;
            state.severity = Severity::kHigh;
            state.confidence = EvidenceConfidence::kDirect;
            break;
        }
        
        // Check for warning
        if (msg_lower.find("warning") != std::string::npos) {
            state.fault_class = KernelFaultClass::kKernelWarning;
            state.severity = Severity::kMedium;
            state.confidence = EvidenceConfidence::kDirect;
        }
        
        // Check for error
        if (msg_lower.find("error") != std::string::npos && 
            msg_lower.find("failed") != std::string::npos) {
            state.fault_class = KernelFaultClass::kKernelError;
            state.severity = Severity::kHigh;
            state.confidence = EvidenceConfidence::kDirect;
        }
    }
    
    // Subject is extracted from evidence fields in FaultEvidence structure
    
    return state;
}

KernelFaultDetector::ClassificationState 
KernelFaultDetector::classify_dmesg_line(
    const std::string& line,
    [[maybe_unused]] std::chrono::system_clock::time_point timestamp) {
    
    ClassificationState state;
    std::string line_lower = line;
    std::transform(line_lower.begin(), line_lower.end(), line_lower.begin(),
                   [](unsigned char c) { return std::tolower(c); });
    
    // Check for panic
    if (line_lower.find("panic") != std::string::npos) {
        state.fault_class = KernelFaultClass::kKernelPanic;
        state.severity = Severity::kCritical;
        state.confidence = EvidenceConfidence::kDirect;
        return state;
    }
    
    // Check for oops
    if (line_lower.find("oops") != std::string::npos) {
        state.fault_class = KernelFaultClass::kKernelOops;
        state.severity = Severity::kHigh;
        state.confidence = EvidenceConfidence::kDirect;
        return state;
    }
    
    // Check for bug
    if (line_lower.find("bug") != std::string::npos) {
        state.fault_class = KernelFaultClass::kKernelBug;
        state.severity = Severity::kHigh;
        state.confidence = EvidenceConfidence::kDirect;
        return state;
    }
    
    // Check for warning
    if (line_lower.find("warning") != std::string::npos) {
        state.fault_class = KernelFaultClass::kKernelWarning;
        state.severity = Severity::kMedium;
        state.confidence = EvidenceConfidence::kDirect;
    }
    
    // Check for error/failed
    if (line_lower.find("error") != std::string::npos && 
        line_lower.find("failed") != std::string::npos) {
        state.fault_class = KernelFaultClass::kKernelError;
        state.severity = Severity::kHigh;
        state.confidence = EvidenceConfidence::kDirect;
    }
    
    return state;
}

KernelFault KernelFaultDetector::create_fault_record(
    const ClassificationState& state,
    const FaultEvidence& primary_evidence,
    std::vector<FaultEvidence> additional_evidences) {
    
    std::lock_guard<std::mutex> lock(mutex_);
    
    KernelFault fault;
    fault.fault_class = state.fault_class;
    fault.severity = state.severity;
    fault.evidences.push_back(primary_evidence);
    
    // Add additional evidences (up to limit)
    for (const auto& ae : additional_evidences) {
        if (fault.evidences.size() < config_.max_evidences_per_fault) {
            fault.evidences.push_back(ae);
        }
    }
    
    // Subject remains unset since runtime::Event doesn't have direct subject field
    (void)state;  // Suppress unused warning for now
    fault.detected_at = primary_evidence.timestamp;
    fault.first_occurred_at = primary_evidence.timestamp;
    fault.boot_id = primary_evidence.boot_id;
    
    // Generate evidence ID
    std::ostringstream oss;
    oss << "fault-" << std::chrono::duration_cast<std::chrono::milliseconds>(
        primary_evidence.timestamp.time_since_epoch()).count()
        << "-" << metrics_.faults_detected;
    fault.evidence_id = oss.str();
    
    fault.confidence = state.confidence;
    
    // Add possible causes
    if (!state.possible_causes.empty()) {
        fault.possible_causes = state.possible_causes;
    } else {
        // Add default causes based on fault class
        switch (state.fault_class) {
            case KernelFaultClass::kKernelWarning:
                fault.possible_causes.push_back("Driver issue");
                fault.possible_causes.push_back("Hardware warning");
                break;
            case KernelFaultClass::kKernelError:
                fault.possible_causes.push_back("Device failure");
                fault.possible_causes.push_back("Driver error");
                break;
            case KernelFaultClass::kKernelPanic:
                fault.possible_causes.push_back("Critical hardware failure");
                fault.possible_causes.push_back("Kernel bug");
                fault.possible_causes.push_back("Out of memory");
                break;
            default:
                fault.possible_causes.push_back("Unknown cause");
                break;
        }
    }
    
    // Deduplication: check if similar fault exists (based on fault class and time)
    bool is_duplicate = false;
    for (const auto& existing : detected_faults_) {
        if (existing.fault_class == fault.fault_class &&
            std::chrono::duration_cast<std::chrono::minutes>(
                fault.detected_at - existing.first_occurred_at).count() < 5) {
            is_duplicate = true;
            fault.occurrence_count = existing.occurrence_count + 1;
            fault.evidence_id = existing.evidence_id;
            break;
        }
    }
    
    // Add to detected faults (bounded)
    if (!is_duplicate && detected_faults_.size() < config_.max_faults_retained) {
        detected_faults_.push_back(fault);
    } else if (!is_duplicate) {
        // Remove oldest and add new
        if (!detected_faults_.empty()) {
            detected_faults_.erase(detected_faults_.begin());
            detected_faults_.push_back(fault);
        }
    }
    
    return fault;
}

void KernelFaultDetector::aggregate_faults(std::chrono::system_clock::time_point now) {
    // Aggregate faults within correlation window
    auto window_start = now - config_.event_correlation_window;
    
    std::vector<KernelFault> recent_faults;
    for (const auto& fault : detected_faults_) {
        if (fault.first_occurred_at >= window_start) {
            recent_faults.push_back(fault);
        }
    }
    
    // Group by fault class only (subject tracking removed for now)
    std::map<std::string, std::vector<KernelFault>> grouped;
    for (const auto& fault : recent_faults) {
        std::string key = to_string(fault.fault_class);
        grouped[key].push_back(fault);
    }
    
    // Update severity based on group size
    for (auto& [key, faults] : grouped) {
        if (static_cast<int>(faults.size()) >= config_.crash_loop_threshold) {
            // Mark as crash loop / repeated fault
            for (auto& fault : faults) {
                if (fault.severity < Severity::kHigh) {
                    fault.severity = Severity::kHigh;
                }
            }
        }
    }
}

// ============================================================================
// SignatureRegistry implementation
// ============================================================================

std::vector<std::string> SignatureRegistry::default_signatures() {
    return {
        "kernel_panic",
        "kernel_oops",
        "kernel_warning",
        "out_of_memory",
        "device_failure",
        "driver_timeout"
    };
}

bool SignatureRegistry::contains_kernel_prefix(const std::string& message) {
    std::string msg_lower = message;
    std::transform(msg_lower.begin(), msg_lower.end(), msg_lower.begin(),
                   [](unsigned char c) { return std::tolower(c); });
    
    static const std::vector<std::string> prefixes = {
        "kernel:", "kernel ", "kern:", "bug:", "warning:"
    };
    
    for (const auto& prefix : prefixes) {
        if (msg_lower.find(prefix) == 0) {
            return true;
        }
    }
    
    return false;
}

int SignatureRegistry::extract_priority(
    const std::unordered_map<std::string, std::string>& fields) {
    
    // Check for PRIORITY field from journal
    auto it = fields.find("PRIORITY");
    if (it != fields.end()) {
        try {
            return std::stoi(it->second);
        } catch (...) {
            // Fall through to default
        }
    }
    
    // Default to INFO level
    return 6;
}

// ============================================================================
// Factory functions
// ============================================================================

std::unique_ptr<KernelFaultDetector> make_kernel_fault_detector(
    const KernelFaultDetectorConfig& config) {
    return std::make_unique<KernelFaultDetector>(config);
}

}  // namespace rebuntu::adapters