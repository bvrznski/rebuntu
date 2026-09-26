// rebuntu::modules::internal_alerts — Internal Alert Service Types (Phase 5.14)
//
// This module defines the canonical internal alert service for Rebuntu:
//   - InternalAlert: Structured operational signal from evidence-backed conditions
//   - AlertDeduplication: Deduplication of repeated equivalent conditions
//   - AlertCorrelation: Correlating related alerts without merging unrelated subjects
//   - EvidenceLinkage: Linking alerts to provenance-bearing observations
//
// Key Principles:
//   * Internal alert != user notification (no UI, no human-facing panic messages)
//   * Alert = structured reduction of facts/assertions/conditions, not raw event stream
//   * Deduplicatable, correlatable, stateful where necessary
//   * Evidence-linked and severity-aware without fake numeric precision
//   * Feed later reporting, automation and recovery phases
//
// Design Philosophy:
//   * Observation → Fact → Assertion/Condition → Alert (if condition satisfied)
//   * Alert lifecycle: OPEN → UPDATED → ACKNOWLEDGED → CLEARED → CLOSED
//   * Deduplication prevents alert storms while preserving recurrence after clear
//   * Correlation groups related alerts without merging unrelated subjects

#pragma once

#include <runtime/contracts.hpp>
#include <system/core/contracts.hpp>

#include <chrono>
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <optional>

namespace rebuntu::modules::internal_alerts {

// ============================================================================
// AlertState — Lifecycle state of an alert
// ============================================================================
//
// The alert lifecycle reflects the operational status:
//   - OPEN: Condition satisfied, needs attention
//   - UPDATED: Condition still satisfied (recurrence without clear)
//   - ACKNOWLEDGED: Human/automation has seen this alert
//   - CLEARED: Condition no longer satisfied
//   - CLOSED: Alert lifecycle complete (cleared + retention period passed)

enum class AlertState {
    kOpen,         // Condition is currently satisfied
    kUpdated,      // Recurrence of same condition (deduplication window)
    kAcknowledged, // Has been acknowledged by human/automation
    kCleared,      // Condition no longer satisfied
    kClosed,       // Lifecycle complete (retention period passed)
};

inline std::string to_string(AlertState s) {
    switch (s) {
        case AlertState::kOpen:         return "open";
        case AlertState::kUpdated:      return "updated";
        case AlertState::kAcknowledged: return "acknowledged";
        case AlertState::kCleared:      return "cleared";
        case AlertState::kClosed:       return "closed";
    }
    return "unknown";
}

// ============================================================================
// SeverityCategory — Severity level (qualitative, not numeric)
// ============================================================================
//
// These are categorical severity levels. Do NOT convert to 0-100 scores.
// Use structured uncertainty where needed.

enum class SeverityCategory {
    kInfo,     // Informational only, no action needed
    kLow,      // Minor issue, monitor closely
    kMedium,   // Noticeable issue, investigate soon
    kHigh,     // Significant issue, investigate promptly
    kCritical, // Critical failure, immediate action required
};

inline std::string to_string(SeverityCategory s) {
    switch (s) {
        case SeverityCategory::kInfo:     return "info";
        case SeverityCategory::kLow:      return "low";
        case SeverityCategory::kMedium:   return "medium";
        case SeverityCategory::kHigh:     return "high";
        case SeverityCategory::kCritical: return "critical";
    }
    return "unknown";
}

// ============================================================================
// UrgencyLevel — How quickly attention is needed
// ============================================================================
//
// Distinct from severity:
//   - Severity = how bad the issue is if unaddressed
//   - Urgency = how soon must we respond

enum class UrgencyLevel {
    kBackground,  // Can wait for natural monitoring cycle
    kNormal,      // Address in next monitoring window
    kHigh,        // Address within minutes
    kCritical,    // Immediate attention required
};

inline std::string to_string(UrgencyLevel u) {
    switch (u) {
        case UrgencyLevel::kBackground: return "background";
        case UrgencyLevel::kNormal:      return "normal";
        case UrgencyLevel::kHigh:       return "high";
        case UrgencyLevel::kCritical:   return "critical";
    }
    return "unknown";
}

// ============================================================================
// AlertCategory — Category/classification of the alert
// ============================================================================
//
// Categorize alerts by what kind of condition triggered them.

enum class AlertCategory {
    kServiceFailure,      // Service entered failed state or crash loop
    kResourceExhaustion,  // Resource limit exceeded (memory, CPU, disk)
    kHealthDegradation,   // Component health degraded but not failed
    kPerformanceIssue,    // Performance below acceptable threshold
    kSecurityEvent,       // Security-relevant event (unauthorized access, etc.)
    kConfigurationDrift,  // Configuration deviated from expected state
    kHardwareFault,       // Hardware fault or predicted failure
    kSystemEvent,         // System-level event (reboot, crash, panic)
};

inline std::string to_string(AlertCategory c) {
    switch (c) {
        case AlertCategory::kServiceFailure:     return "service-failure";
        case AlertCategory::kResourceExhaustion: return "resource-exhaustion";
        case AlertCategory::kHealthDegradation:  return "health-degradation";
        case AlertCategory::kPerformanceIssue:   return "performance-issue";
        case AlertCategory::kSecurityEvent:      return "security-event";
        case AlertCategory::kConfigurationDrift: return "configuration-drift";
        case AlertCategory::kHardwareFault:      return "hardware-fault";
        case AlertCategory::kSystemEvent:        return "system-event";
    }
    return "unknown";
}

// ============================================================================
// SubjectType — Type of subject being alerted on
// ============================================================================

enum class SubjectType {
    kProcess,          // A process (by PID)
    kService,          // A systemd service (by unit name)
    kHost,             // The entire host/system
    kDevice,           // A device (by sysfs path or udev ID)
    kResource,         // A resource category (memory, CPU, disk space)
    kFileSystem,       // A filesystem/mount point
};

inline std::string to_string(SubjectType t) {
    switch (t) {
        case SubjectType::kProcess:     return "process";
        case SubjectType::kService:     return "service";
        case SubjectType::kHost:        return "host";
        case SubjectType::kDevice:      return "device";
        case SubjectType::kResource:    return "resource";
        case SubjectType::kFileSystem:  return "filesystem";
    }
    return "unknown";
}

// ============================================================================
// AlertIdentity — Unique identifier for an alert
// ============================================================================

struct AlertIdentity {
    std::string id;                              // Unique alert ID (UUID)
    
    // Canonical key for deduplication (same key = same alert type + subject)
    std::string dedupe_key;
    
    // Original source event that triggered this alert (if any)
    std::optional<std::string> trigger_event_id;
};

// ============================================================================
// AlertEvidence — Evidence linked to an alert
// ============================================================================

struct AlertEvidence {
    core::Evidence evidence;           // The provenance-bearing observation
    
    // Context about how this evidence relates to the alert
    enum class Relevance {
        kDirectCause,      // This evidence directly caused the condition
        kContributing,     // This evidence contributed to the condition
        kCorroborating,    // This evidence corroborates another signal
        kContextual,       // This evidence provides context but not causation
    } relevance = Relevance::kContextual;
};

// ============================================================================
// AlertCondition — The condition that triggered the alert
// ============================================================================

struct AlertCondition {
    std::string expression;            // Human-readable condition (e.g., "restart_count > 5")
    
    bool is_satisfied = false;         // Current evaluation status
    
    std::vector<std::string> matching_facts;  // Which facts made this true
    
    // Temporal information
    std::chrono::system_clock::time_point first_triggered_at;
    std::optional<std::chrono::system_clock::time_point> last_retriggered_at;
};

// ============================================================================
// InternalAlert — The main alert type (Phase 5.14)
// ============================================================================

struct InternalAlert {
    AlertIdentity identity;            // Unique ID + dedupe key
    
    // Lifecycle state
    AlertState state = AlertState::kOpen;
    
    std::chrono::system_clock::time_point created_at;
    std::optional<std::chrono::system_clock::time_point> last_updated_at;
    std::optional<std::chrono::system_clock::time_point> cleared_at;
    std::optional<std::chrono::system_clock::time_point> closed_at;
    
    // Alert characteristics
    SeverityCategory severity = SeverityCategory::kInfo;
    UrgencyLevel urgency = UrgencyLevel::kNormal;
    AlertCategory category = AlertCategory::kServiceFailure;
    
    // Subject of the alert
    SubjectType subject_type = SubjectType::kHost;
    std::string subject_id;            // e.g., service name, PID, device path
    
    // Condition that triggered this alert
    AlertCondition condition;
    
    // Evidence chain (provenance-bearing)
    std::vector<AlertEvidence> evidence;
    
    // Correlation metadata
    std::optional<std::string> boot_id;            // Boot context for cross-boot isolation
    std::optional<std::string> parent_alert_id;    // If this is a follow-up to another alert
    
    // Deduplication tracking
    size_t occurrence_count = 1;                     // How many times this occurred
    std::chrono::system_clock::time_point first_seen_at;
    std::optional<std::chrono::system_clock::time_point> last_occurrence_at;
    
    // Recommended actions (diagnostic only, no automatic execution)
    struct RecommendedAction {
        std::string category;  // "investigate", "monitor", "document"
        std::string description;
        std::vector<std::string> related_alert_ids;  // Related alerts to check
    };
    std::vector<RecommendedAction> recommended_actions;
    
    // Source of the alert (where it came from)
    std::optional<std::string> source_component;     // e.g., "journal-analyzer", "health-monitor"
};

// ============================================================================
// AlertDeduplicationConfig — Configuration for deduplication
// ============================================================================

struct AlertDeduplicationConfig {
    // How long to wait before considering a recurrence as new (rather than updated)
    std::chrono::milliseconds deduplication_window{std::chrono::minutes(5)};
    
    // Maximum occurrences to track per alert type
    size_t max_occurrences_per_dedupe_key = 1000;
    
    // How long to keep alerts in memory after they're cleared
    std::chrono::hours retention_after_clear{24};
};

// ============================================================================
// AlertCorrelationConfig — Configuration for correlation
// ============================================================================

struct AlertCorrelationConfig {
    // Temporal window for correlating related alerts
    std::chrono::milliseconds correlation_window{std::chrono::minutes(10)};
    
    // Maximum correlated alerts per alert
    size_t max_correlated_per_alert = 50;
    
    // Whether to correlate by subject (same service/device/host)
    bool correlate_by_subject = true;
    
    // Whether to correlate by time window (close in time)
    bool correlate_by_time = true;
};

// ============================================================================
// AlertMetrics — Runtime metrics for the alert service
// ============================================================================

struct AlertMetrics {
    std::chrono::system_clock::time_point started_at;
    
    // Alert counts by state
    size_t alerts_open = 0;
    size_t alerts_updated = 0;
    size_t alerts_acknowledged = 0;
    size_t alerts_cleared = 0;
    size_t alerts_closed = 0;
    
    // Counts by severity
    std::unordered_map<SeverityCategory, size_t> alerts_by_severity;
    
    // Counts by category
    std::unordered_map<AlertCategory, size_t> alerts_by_category;
    
    // Deduplication stats
    size_t deduplicated_alerts = 0;
    size_t new_occurrences = 0;
    
    // Correlation stats
    size_t correlated_alerts = 0;
    
    // Performance
    std::optional<std::chrono::milliseconds> last_process_duration_ms;
};

// ============================================================================
// AlertResult — Result of processing an alert event
// ============================================================================

struct AlertResult {
    enum class Action {
        kNew,              // New alert created
        kUpdated,          // Existing alert updated (recurrence within window)
        kAcknowledged,     // Alert acknowledged
        kCleared,          // Alert cleared (condition no longer satisfied)
        kCorrelated,       // Alert correlated with others
        kSuppressed,       // Alert suppressed (e.g., too frequent)
    } action = Action::kNew;
    
    InternalAlert alert;  // The resulting alert state
    
    std::optional<std::string> dedupe_key_changed_reason;  // If key changed
    std::vector<std::string> correlated_alert_ids;         // Alert IDs this was correlated with
};

// ============================================================================
// AlertProcessor — Interface for processing alerts
// ============================================================================

class AlertProcessor {
public:
    virtual ~AlertProcessor() = default;
    
    // Configure the processor
    virtual core::Outcome configure(
        const AlertDeduplicationConfig& dedup_config,
        const AlertCorrelationConfig& corr_config) = 0;
    
    // Start/stop lifecycle
    virtual core::Outcome start() = 0;
    virtual core::Outcome stop() = 0;
    virtual bool is_running() const = 0;
    
    // Process an event and generate alerts if conditions are met
    virtual AlertResult process_event(
        const runtime::Event& event,
        const std::vector<core::Evidence>& evidence) = 0;
    
    // Manually create/update an alert (e.g., from condition evaluation)
    virtual AlertResult create_or_update_alert(
        SubjectType subject_type,
        const std::string& subject_id,
        SeverityCategory severity,
        AlertCategory category,
        AlertCondition condition,
        std::vector<AlertEvidence> evidence) = 0;
    
    // Acknowledge an alert
    virtual core::Outcome acknowledge_alert(const std::string& alert_id) = 0;
    
    // Clear an alert (condition no longer satisfied)
    virtual core::Outcome clear_alert(const std::string& alert_id) = 0;
    
    // Get current alerts by state/category/severity
    virtual std::vector<InternalAlert> get_alerts(
        std::optional<AlertState> state_filter = std::nullopt,
        std::optional<SeverityCategory> severity_filter = std::nullopt,
        std::optional<AlertCategory> category_filter = std::nullopt) = 0;
    
    // Get metrics
    virtual AlertMetrics metrics() const = 0;
};

// ============================================================================
// Factory functions
// ============================================================================

std::unique_ptr<AlertProcessor> make_alert_processor();

}  // namespace rebuntu::modules::internal_alerts

// ============================================================================
// Ostream operators for easy debugging
// ============================================================================

inline std::ostream& operator<<(std::ostream& os,
                                rebuntu::modules::internal_alerts::AlertState s) {
    return os << rebuntu::modules::internal_alerts::to_string(s);
}

inline std::ostream& operator<<(std::ostream& os,
                                rebuntu::modules::internal_alerts::SeverityCategory s) {
    return os << rebuntu::modules::internal_alerts::to_string(s);
}

inline std::ostream& operator<<(std::ostream& os,
                                rebuntu::modules::internal_alerts::UrgencyLevel u) {
    return os << rebuntu::modules::internal_alerts::to_string(u);
}

inline std::ostream& operator<<(std::ostream& os,
                                rebuntu::modules::internal_alerts::AlertCategory c) {
    return os << rebuntu::modules::internal_alerts::to_string(c);
}

inline std::ostream& operator<<(std::ostream& os,
                                rebuntu::modules::internal_alerts::SubjectType t) {
    return os << rebuntu::modules::internal_alerts::to_string(t);
}