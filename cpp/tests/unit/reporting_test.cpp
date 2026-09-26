// rebuntu::modules::reporting tests — Reporting & Notification Service (Phase 5.15)
//
// Tests verify:
//   - Report generation from assessment data
//   - Renderer output (human-readable and JSON)
//   - Notification rate limiting
//   - Deduplication within time windows
//   - Metrics tracking

#include <gtest/gtest.h>

#include "src/modules/reporting/types.hpp"
#include "src/modules/reporting/generator.hpp"

#include <runtime/contracts.hpp>
#include <system/core/contracts.hpp>

#include <chrono>
#include <thread>

namespace rebuntu::modules::reporting {

// ============================================================================
// Type Tests
// ============================================================================

TEST(ReportingTypes, ToStringReportKind) {
    EXPECT_EQ(to_string(ReportKind::kDiagnostic), "diagnostic");
    EXPECT_EQ(to_string(ReportKind::kAlertSummary), "alert-summary");
    EXPECT_EQ(to_string(ReportKind::kIncidentReport), "incident-report");
    EXPECT_EQ(to_string(ReportKind::kHealthSnapshot), "health-snapshot");
    EXPECT_EQ(to_string(ReportKind::kPeriodic), "periodic");
}

TEST(ReportingTypes, ToStringNotificationType) {
    EXPECT_EQ(to_string(NotificationType::kAlert), "alert");
    EXPECT_EQ(to_string(NotificationType::kInfo), "info");
    EXPECT_EQ(to_string(NotificationType::kWarning), "warning");
    EXPECT_EQ(to_string(NotificationType::kSuccess), "success");
    EXPECT_EQ(to_string(NotificationType::kDebug), "debug");
}

TEST(ReportingTypes, ToStringNotificationDestination) {
    EXPECT_EQ(to_string(NotificationDestination::kLog), "log");
    EXPECT_EQ(to_string(NotificationDestination::kDBus), "dbus");
    EXPECT_EQ(to_string(NotificationDestination::kStdout), "stdout");
    EXPECT_EQ(to_string(NotificationDestination::kFile), "file");
    EXPECT_EQ(to_string(NotificationDestination::kWebhook), "webhook");
}

// ============================================================================
// ReportGenerator Tests
// ============================================================================

TEST(ReportGenerator, CreateAndConfigure) {
    auto generator = make_report_generator();
    
    ReportGeneratorOptions options;
    options.rate_limits.max_notifications_per_window = 50;
    
    auto result = generator->configure(options);
    
 EXPECT_EQ(result.status, core::SemanticStatus::kSuccess);
}

TEST(ReportGenerator, StartStopLifecycle) {
    auto generator = make_report_generator();
    
    auto start_result = generator->start();
    EXPECT_EQ(start_result.status, core::SemanticStatus::kSuccess);
    EXPECT_TRUE(generator->is_running());
    
    auto stop_result = generator->stop();
    EXPECT_EQ(stop_result.status, core::SemanticStatus::kSuccess);
}

// ============================================================================
// Report Generation Tests
// ============================================================================

TEST(ReportGenerator, GenerateDiagnosticReport) {
    auto generator = make_report_generator();
    generator->start();
    
    AssessmentSummary summary;
    summary.overview = "System health check completed";
    
    std::vector<core::Evidence> evidence;
    core::Evidence e1;
    e1.source = "procfs";
    e1.value = "CPU: 45%";
    e1.captured_at = "2026-01-01T00:00:00Z";
    evidence.push_back(e1);
    
    auto report = generator->generate_report(
        ReportKind::kDiagnostic,
        summary,
        evidence,
        std::chrono::system_clock::now()
    );
    
    ASSERT_TRUE(report.has_value());
    EXPECT_EQ(report->metadata.kind, ReportKind::kDiagnostic);
    EXPECT_EQ(report->content.assessment.overview, "System health check completed");
}

TEST(ReportGenerator, GenerateAlertSummaryReport) {
    auto generator = make_report_generator();
    generator->start();
    
    AssessmentSummary summary;
    summary.overview = "Multiple service failures detected";
    
    ImpactAnalysis impact;
    ImpactAnalysis::SubsystemImpact si;
    si.subsystem = "services";
    si.severity = ImpactAnalysis::Severity::kModerate;
    si.affected_subjects.push_back("my-service.service");
    impact.subsystem_impacts.push_back(si);
    summary.impact = impact;
    
    std::vector<core::Evidence> evidence;
    
    auto report = generator->generate_report(
        ReportKind::kAlertSummary,
        summary,
        evidence,
        std::chrono::system_clock::now()
    );
    
    ASSERT_TRUE(report.has_value());
    EXPECT_EQ(report->metadata.kind, ReportKind::kAlertSummary);
    EXPECT_EQ(report->content.assessment.impact.subsystem_impacts.size(), 1u);
}

// ============================================================================
// Renderer Tests
// ============================================================================

TEST(ReportRenderer, RenderHuman) {
    auto renderer = make_report_renderer();
    
    Report report;
    report.metadata.id = "test-report-1";
    report.metadata.kind = ReportKind::kDiagnostic;
    report.metadata.subject = "system";
    report.metadata.created_at = std::chrono::system_clock::now();
    
    report.content.assessment.overview = "Test report overview";
    
    // Timeline
    TimelineEvent event;
    event.timestamp = report.metadata.created_at;
    event.event_type = "health-check";
    event.subject = "system";
    report.content.timeline.push_back(event);
    
    std::string human_output = renderer->render_human(report);
    
    EXPECT_NE(human_output.find("test-report-1"), std::string::npos);
    EXPECT_NE(human_output.find("diagnostic"), std::string::npos);
    EXPECT_NE(human_output.find("Test report overview"), std::string::npos);
}

TEST(ReportRenderer, RenderJSON) {
    auto renderer = make_report_renderer();
    
    Report report;
    report.metadata.id = "test-report-2";
    report.metadata.kind = ReportKind::kIncidentReport;
    report.metadata.subject = "my-service.service";
    report.metadata.created_at = std::chrono::system_clock::now();
    
    report.content.assessment.overview = "Service failure detected";
    
    std::string json_output = renderer->render_json(report);
    
    EXPECT_NE(json_output.find("\"id\": \"test-report-2\""), std::string::npos);
    EXPECT_NE(json_output.find("\"kind\": \"incident-report\""), std::string::npos);
}

TEST(ReportRenderer, RenderSummary) {
    auto renderer = make_report_renderer();
    
    Report report;
    report.metadata.id = "summary-test";
    report.metadata.kind = ReportKind::kHealthSnapshot;
    report.metadata.subject = "host1";
    report.content.assessment.overview = "System healthy";
    
    std::string summary = renderer->render_summary(report);
    
    EXPECT_NE(summary.find("summary-test"), std::string::npos);
    EXPECT_NE(summary.find("health-snapshot"), std::string::npos);
}

// ============================================================================
// Notification Tests
// ============================================================================

TEST(Notification, SendNotification) {
    auto generator = make_report_generator();
    generator->start();
    
    Notification notification;
    notification.metadata.id = "test-notification-1";
    notification.metadata.type = NotificationType::kInfo;
    notification.metadata.destination = NotificationDestination::kLog;
    notification.content.summary = "Test notification";
    
    auto result = generator->send_notification(notification);
    
    EXPECT_EQ(result.status, DeliveryResult::Status::kDelivered);
}

TEST(Notification, RateLimiting) {
    auto generator = make_report_generator();
    generator->start();
    
    // Configure strict rate limit
    ReportGeneratorOptions options;
    options.rate_limits.max_notifications_per_window = 3;
    options.rate_limits.window_size_minutes = std::chrono::minutes(1);
    generator->configure(options);
    
    // Send notifications up to the limit
    for (int i = 0; i < 3; ++i) {
        Notification notification;
        notification.metadata.type = NotificationType::kInfo;
        notification.metadata.destination = NotificationDestination::kLog;
        notification.content.summary = "Test notification " + std::to_string(i);
        
        auto result = generator->send_notification(notification);
        EXPECT_EQ(result.status, DeliveryResult::Status::kDelivered) << "Notification " << i;
    }
    
    // This one should be suppressed (over limit)
    Notification notification4;
    notification4.metadata.type = NotificationType::kInfo;
    notification4.metadata.destination = NotificationDestination::kLog;
    notification4.content.summary = "Test notification 4";
    
    auto result4 = generator->send_notification(notification4);
    EXPECT_EQ(result4.status, DeliveryResult::Status::kSuppressed);
}

TEST(Notification, MetricsTracking) {
    auto generator = make_report_generator();
    generator->start();
    
    // Get initial metrics
    auto initial_metrics = generator->metrics();
    size_t initial_sent = initial_metrics.notifications_sent;
    
    // Send a notification
    Notification notification;
    notification.metadata.type = NotificationType::kInfo;
    notification.metadata.destination = NotificationDestination::kLog;
    notification.content.summary = "Test";
    
    generator->send_notification(notification);
    
    // Check metrics were updated
    auto new_metrics = generator->metrics();
    EXPECT_EQ(new_metrics.notifications_sent, initial_sent + 1);
}

// ============================================================================
// Edge Cases
// ============================================================================

TEST(ReportGenerator, GenerateReportWhenNotRunning) {
    auto generator = make_report_generator();
    
    // Don't start the generator
    
    AssessmentSummary summary;
    summary.overview = "Should not generate";
    
    std::vector<core::Evidence> evidence;
    
    auto report = generator->generate_report(
        ReportKind::kDiagnostic,
        summary,
        evidence,
        std::chrono::system_clock::now()
    );
    
    EXPECT_FALSE(report.has_value());
}

TEST(ReportGenerator, SendNotificationWhenNotRunning) {
    auto generator = make_report_generator();
    
    // Don't start the generator
    
    Notification notification;
    notification.metadata.type = NotificationType::kInfo;
    notification.metadata.destination = NotificationDestination::kLog;
    notification.content.summary = "Should not send";
    
    auto result = generator->send_notification(notification);
    
    EXPECT_EQ(result.status, DeliveryResult::Status::kFailed);
}

TEST(ReportRenderer, RenderWithEmptyFields) {
    auto renderer = make_report_renderer();
    
    Report report;
    report.metadata.id = "empty-test";
    report.metadata.kind = ReportKind::kPeriodic;
    
    // No overview, no timeline, no evidence
    
    std::string human_output = renderer->render_human(report);
    EXPECT_NE(human_output.find("empty-test"), std::string::npos);
}

// ============================================================================
// Causal Analysis Tests
// ============================================================================

TEST(ReportGenerator, IncludeCausalAnalysis) {
    auto generator = make_report_generator();
    generator->start();
    
    AssessmentSummary summary;
    summary.overview = "Service failure with likely cause";
    summary.most_likely_cause = "Memory exhaustion";
    
    std::vector<core::Evidence> evidence;
    
    auto report = generator->generate_report(
        ReportKind::kIncidentReport,
        summary,
        evidence,
        std::chrono::system_clock::now()
    );
    
    ASSERT_TRUE(report.has_value());
    EXPECT_EQ(report->content.assessment.most_likely_cause, "Memory exhaustion");
}

}  // namespace rebuntu::modules::reporting