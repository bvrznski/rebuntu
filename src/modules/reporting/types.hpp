// rebuntu::modules::reporting — Reporting & Notification Types (Phase 5.15)
//
// This module defines the canonical reporting and notification service for Rebuntu:
//   - Report: Structured diagnostic assessment with evidence, timeline, uncertainty
//   - Assessment → Report → Renderer → Delivery/Notification pipeline
//   - Pluggable notification delivery mechanisms
//   - Rate limiting and deduplication of notifications

#pragma once

#include <runtime/contracts.hpp>
#include <system/core/contracts.hpp>

#include <chrono>
#include <cstdint>
#include <string>
#include <vector>
#include <unordered_map>
#include <optional>
#include <memory>

namespace rebuntu::modules::reporting {

// ============================================================================
// RateLimiterStatus — Status of rate limiter
// ============================================================================

struct RateLimiterStatus {
    size_t per_minute = 0;
    size_t per_hour = 0;
    size_t daily = 0;
};

// ============================================================================
// ReportKind — Types of reports
// ============================================================================

enum class ReportKind {
    kDiagnostic,
    kAlertSummary,
    kIncidentReport,
    kHealthSnapshot,
    kPeriodic,
};

inline std::string to_string(ReportKind kind) {
    switch (kind) {
        case ReportKind::kDiagnostic:   return "diagnostic";
        case ReportKind::kAlertSummary: return "alert-summary";
        case ReportKind::kIncidentReport: return "incident-report";
        case ReportKind::kHealthSnapshot: return "health-snapshot";
        case ReportKind::kPeriodic:     return "periodic";
    }
    return "unknown";
}

// ============================================================================
// EvidenceLink
// ============================================================================

struct EvidenceLink {
    std::string reference_id;
    std::string source;
    std::optional<std::string> record_id;
    
    enum class Role {
        kPrimaryCause,
        kContributing,
        kCorroborating,
        kContextual,
        kEvidenceBase,
    } role = Role::kContextual;
};

// ============================================================================
// TimelineEvent
// ============================================================================

struct TimelineEvent {
    std::chrono::system_clock::time_point timestamp;
    std::string event_type;
    std::string subject;
    std::optional<std::string> evidence_id;
    std::optional<std::string> assessment;
    std::vector<std::string> correlated_events;
};

// ============================================================================
// CausalAnalysis
// ============================================================================

struct CausalAnalysis {
    std::vector<TimelineEvent> observed_sequence;
    
    struct Correlation {
        std::string event_id_1;
        std::string event_id_2;
        std::chrono::milliseconds time_delta_ms;
        bool same_subject;
    };
    std::vector<Correlation> correlations;
    
    struct Hypothesis {
        std::string description;
        double support_score = 0.0;
        std::vector<std::string> supporting_evidence_ids;
        std::optional<std::string> alternative_hypothesis_id;
    };
    std::vector<Hypothesis> hypotheses;
    
    std::optional<std::string> most_likely_cause;
    std::vector<std::string> alternative_explanations;
    std::optional<std::string> uncertainty_notes;
};

// ============================================================================
// ImpactAnalysis
// ============================================================================

struct ImpactAnalysis {
    struct SubsystemImpact {
        std::string subsystem;
        
        enum class Severity {
            kNone,
            kMinor,
            kModerate,
            kSevere,
            kCritical,
        } severity = Severity::kNone;
        
        std::vector<std::string> affected_subjects;
    };
    std::vector<SubsystemImpact> subsystem_impacts;
    
    enum class UserImpact {
        kUnknown,
        kNone,
        kMinor,
        kModerate,
        kSevere,
        kCritical,
    } user_impact = UserImpact::kUnknown;
    
    std::optional<std::chrono::milliseconds> estimated_recovery_time_ms;
    std::optional<std::chrono::milliseconds> actual_duration_ms;
};

// ============================================================================
// AssessmentSummary
// ============================================================================

struct AssessmentSummary {
    std::string overview;
    std::vector<TimelineEvent> timeline_highlights;
    std::optional<std::string> most_likely_cause;
    ImpactAnalysis impact;
    
    enum class EvidenceQuality {
        kDirect,
        kDeduced,
        kCorrelated,
        kHypothesized,
    } evidence_quality = EvidenceQuality::kDirect;
    
    std::optional<std::string> uncertainty_notes;
    
    struct Recommendation {
        std::string category;
        std::string description;
        std::vector<std::string> related_alert_ids;
    };
    std::vector<Recommendation> recommendations;
};

// ============================================================================
// ReportMetadata
// ============================================================================

struct ReportMetadata {
    std::string id;
    std::chrono::system_clock::time_point created_at;
    std::optional<std::chrono::system_clock::time_point> since;
    std::optional<std::chrono::system_clock::time_point> until;
    std::string subject;
    ReportKind kind;
    std::optional<std::string> trigger_event_id;
    std::optional<std::string> trigger_reason;
    bool verified = false;
    size_t evidence_items_count = 0;
    size_t timeline_events_count = 0;
    std::optional<std::string> boot_id;
    std::optional<std::string> machine_id;
};

// ============================================================================
// ReportContent
// ============================================================================

struct ReportContent {
    AssessmentSummary assessment;
    std::vector<core::Evidence> evidence_chain;
    std::vector<EvidenceLink> evidence_links;
    std::vector<TimelineEvent> timeline;
    CausalAnalysis causal_analysis;
};

// ============================================================================
// Report
// ============================================================================

struct Report {
    ReportMetadata metadata;
    ReportContent content;
};

// ============================================================================
// NotificationType
// ============================================================================

enum class NotificationType {
    kAlert,
    kInfo,
    kWarning,
    kSuccess,
    kDebug,
};

inline std::string to_string(NotificationType t) {
    switch (t) {
        case NotificationType::kAlert:     return "alert";
        case NotificationType::kInfo:      return "info";
        case NotificationType::kWarning:   return "warning";
        case NotificationType::kSuccess:   return "success";
        case NotificationType::kDebug:     return "debug";
    }
    return "unknown";
}

// ============================================================================
// NotificationDestination
// ============================================================================

enum class NotificationDestination {
    kLog,
    kDBus,
    kStdout,
    kFile,
    kWebhook,
};

inline std::string to_string(NotificationDestination d) {
    switch (d) {
        case NotificationDestination::kLog:      return "log";
        case NotificationDestination::kDBus:     return "dbus";
        case NotificationDestination::kStdout:   return "stdout";
        case NotificationDestination::kFile:     return "file";
        case NotificationDestination::kWebhook:  return "webhook";
    }
    return "unknown";
}

// ============================================================================
// NotificationMetadata
// ============================================================================

struct NotificationMetadata {
    std::string id;
    std::chrono::system_clock::time_point created_at;
    NotificationType type;
    NotificationDestination destination;
    std::optional<std::string> subject;
    std::optional<std::string> recipient;
    std::optional<std::string> related_report_id;
    std::optional<std::string> related_alert_id;
};

// ============================================================================
// NotificationContent
// ============================================================================

struct NotificationContent {
    std::string summary;
    std::optional<std::string> detailed_message;
    std::optional<std::string> report_id;
    std::optional<std::string> recommended_action;
};

// ============================================================================
// Notification
// ============================================================================

struct Notification {
    NotificationMetadata metadata;
    NotificationContent content;
};

// ============================================================================
// NotificationRateLimitConfig
// ============================================================================

struct NotificationRateLimitConfig {
    struct DestinationLimits {
        NotificationDestination destination;
        size_t max_per_minute;
        size_t max_per_hour;
        size_t max_daily;
    };
    
    std::vector<DestinationLimits> destination_limits;
    size_t max_notifications_per_window = 100;
    std::chrono::minutes window_size_minutes{1};
    bool deduplicate_identical_content = true;
    std::chrono::minutes deduplication_window_minutes{5};
};

// ============================================================================
// DeliveryResult
// ============================================================================

struct DeliveryResult {
    enum class Status {
        kDelivered,
        kQueued,
        kFailed,
        kSuppressed,
        kTimeout,
    } status = Status::kFailed;
    
    std::chrono::system_clock::time_point attempted_at;
    std::optional<core::Error> error;
    std::optional<std::string> delivery_id;
};

// ============================================================================
// NotificationDeliveryConfig
// ============================================================================

struct NotificationDeliveryConfig {
    NotificationDestination destination;
    bool enabled = true;
    std::optional<std::string> file_path;
    std::optional<std::string> webhook_url;
    std::optional<int> dbus_priority;
    NotificationRateLimitConfig rate_limits;
    bool include_report_reference = true;
    bool include_evidence_summary = false;
};

// ============================================================================
// ReportGeneratorMetrics
// ============================================================================

struct ReportGeneratorMetrics {
    std::chrono::system_clock::time_point started_at;
    size_t reports_generated = 0;
    size_t notifications_sent = 0;
    size_t notifications_failed = 0;
    size_t notifications_suppressed = 0;
};

// ============================================================================
// ReportGeneratorOptions
// ============================================================================

struct ReportGeneratorOptions {
    std::chrono::minutes default_window_minutes{30};
    size_t max_evidence_per_report = 100;
    size_t max_timeline_events = 50;
    std::vector<NotificationDeliveryConfig> delivery_configs;
    NotificationRateLimitConfig rate_limits;
    bool generate_alert_summaries = true;
    bool generate_health_snapshots = false;
};

// ============================================================================
// ReportGenerator — Interface
// ============================================================================

class ReportGenerator {
public:
    virtual ~ReportGenerator() = default;
    
    virtual core::Outcome configure(const ReportGeneratorOptions& options) = 0;
    virtual core::Outcome start() = 0;
    virtual core::Outcome stop() = 0;
    virtual bool is_running() const = 0;
    
    virtual std::optional<Report> generate_report(
        ReportKind kind,
        const AssessmentSummary& summary,
        const std::vector<core::Evidence>& evidence,
        const std::chrono::system_clock::time_point& created_at) = 0;
    
    virtual DeliveryResult send_notification(const Notification& notification) = 0;
    virtual ReportGeneratorMetrics metrics() const = 0;
};

// ============================================================================
// ReportRenderer — Interface
// ============================================================================

class ReportRenderer {
public:
    virtual ~ReportRenderer() = default;
    
    virtual std::string render_human(const Report& report) = 0;
    virtual std::string render_json(const Report& report) = 0;
    virtual std::string render_summary(const Report& report) = 0;
};

// ============================================================================
// Factory functions
// ============================================================================

std::unique_ptr<ReportGenerator> make_report_generator();
std::unique_ptr<ReportRenderer> make_report_renderer();

// ============================================================================
// Ostream operators
// ============================================================================

inline std::ostream& operator<<(std::ostream& os, ReportKind k) {
    return os << to_string(k);
}

inline std::ostream& operator<<(std::ostream& os, NotificationType t) {
    return os << to_string(t);
}

inline std::ostream& operator<<(std::ostream& os, NotificationDestination d) {
    return os << to_string(d);
}

}  // namespace rebuntu::modules::reporting
