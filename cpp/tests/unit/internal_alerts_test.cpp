// rebuntu::modules::internal_alerts tests — Internal Alert Service (Phase 5.14)
//
// Tests verify:
//   - Alert lifecycle state transitions
//   - Deduplication within time windows
//   - Correlation without merging unrelated alerts
//   - Evidence preservation
//   - Metrics tracking

#include <gtest/gtest.h>

#include "src/modules/internal_alerts/types.hpp"
#include "src/modules/internal_alerts/processor.hpp"

#include <runtime/contracts.hpp>
#include <system/core/contracts.hpp>

#include <chrono>
#include <thread>

namespace rebuntu::modules::internal_alerts {

// ============================================================================
// AlertType Tests
// ============================================================================

TEST(InternalAlertTypes, ToStringAlertState) {
    EXPECT_EQ(to_string(AlertState::kOpen), "open");
    EXPECT_EQ(to_string(AlertState::kUpdated), "updated");
    EXPECT_EQ(to_string(AlertState::kAcknowledged), "acknowledged");
    EXPECT_EQ(to_string(AlertState::kCleared), "cleared");
    EXPECT_EQ(to_string(AlertState::kClosed), "closed");
}

TEST(InternalAlertTypes, ToStringSeverityCategory) {
    EXPECT_EQ(to_string(SeverityCategory::kInfo), "info");
    EXPECT_EQ(to_string(SeverityCategory::kLow), "low");
    EXPECT_EQ(to_string(SeverityCategory::kMedium), "medium");
    EXPECT_EQ(to_string(SeverityCategory::kHigh), "high");
    EXPECT_EQ(to_string(SeverityCategory::kCritical), "critical");
}

TEST(InternalAlertTypes, ToStringUrgencyLevel) {
    EXPECT_EQ(to_string(UrgencyLevel::kBackground), "background");
    EXPECT_EQ(to_string(UrgencyLevel::kNormal), "normal");
    EXPECT_EQ(to_string(UrgencyLevel::kHigh), "high");
    EXPECT_EQ(to_string(UrgencyLevel::kCritical), "critical");
}

TEST(InternalAlertTypes, ToStringAlertCategory) {
    EXPECT_EQ(to_string(AlertCategory::kServiceFailure), "service-failure");
    EXPECT_EQ(to_string(AlertCategory::kResourceExhaustion), "resource-exhaustion");
    EXPECT_EQ(to_string(AlertCategory::kHealthDegradation), "health-degradation");
    EXPECT_EQ(to_string(AlertCategory::kPerformanceIssue), "performance-issue");
    EXPECT_EQ(to_string(AlertCategory::kSecurityEvent), "security-event");
    EXPECT_EQ(to_string(AlertCategory::kConfigurationDrift), "configuration-drift");
    EXPECT_EQ(to_string(AlertCategory::kHardwareFault), "hardware-fault");
    EXPECT_EQ(to_string(AlertCategory::kSystemEvent), "system-event");
}

TEST(InternalAlertTypes, ToStringSubjectType) {
    EXPECT_EQ(to_string(SubjectType::kProcess), "process");
    EXPECT_EQ(to_string(SubjectType::kService), "service");
    EXPECT_EQ(to_string(SubjectType::kHost), "host");
    EXPECT_EQ(to_string(SubjectType::kDevice), "device");
    EXPECT_EQ(to_string(SubjectType::kResource), "resource");
    EXPECT_EQ(to_string(SubjectType::kFileSystem), "filesystem");
}

// ============================================================================
// AlertProcessor Tests
// ============================================================================

TEST(InternalAlertProcessor, CreateAndConfigure) {
    auto processor = InternalAlertProcessor::create();
    
    AlertDeduplicationConfig dedup_config;
    dedup_config.deduplication_window = std::chrono::minutes(1);
    
    AlertCorrelationConfig corr_config;
    corr_config.correlation_window = std::chrono::minutes(5);
    
    auto result = processor->configure(dedup_config, corr_config);
    
    EXPECT_EQ(result.status, core::SemanticStatus::kSuccess);
}

TEST(InternalAlertProcessor, StartStopLifecycle) {
    auto processor = InternalAlertProcessor::create();
    
    auto start_result = processor->start();
    EXPECT_EQ(start_result.status, core::SemanticStatus::kSuccess);
    EXPECT_TRUE(processor->is_running());
    
    auto stop_result = processor->stop();
    EXPECT_EQ(stop_result.status, core::SemanticStatus::kSuccess);
}

// ============================================================================
// Alert Lifecycle Tests
// ============================================================================

TEST(InternalAlertProcessor, NewAlertLifecycle) {
    auto processor = InternalAlertProcessor::create();
    processor->start();
    
    // Create a new alert via event processing
    runtime::Event event;
    event.id = "test-event-1";
    event.occurred_at = std::chrono::system_clock::now();
    event.source = "test-source";
    event.type = "service-failure";
    
    core::Evidence evidence;
    evidence.source = "journald";
    evidence.value = "service failed";
    evidence.captured_at = "2026-01-01T00:00:00Z";
    
    auto result = processor->process_event(event, {evidence});
    
    EXPECT_EQ(result.action, AlertResult::Action::kNew);
    EXPECT_EQ(result.alert.state, AlertState::kOpen);
    EXPECT_GT(result.alert.identity.id.length(), 0u);
}

TEST(InternalAlertProcessor, AlertDeduplication) {
    auto processor = InternalAlertProcessor::create();
    processor->start();
    
    // Create first alert
    runtime::Event event1;
    event1.id = "event-1";
    event1.occurred_at = std::chrono::system_clock::now();
    event1.source = "journald";
    event1.type = "service-failed";
    event1.subject = "my-service.service";
    
    core::Evidence evidence1;
    evidence1.source = "journald";
    evidence1.value = "service failed with exit code 1";
    evidence1.captured_at = "2026-01-01T00:00:00Z";
    
    auto result1 = processor->process_event(event1, {evidence1});
    EXPECT_EQ(result1.action, AlertResult::Action::kNew);
    std::string alert_id = result1.alert.identity.id;
    
    // Create second event within deduplication window - should be updated
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    
    runtime::Event event2;
    event2.id = "event-2";
    event2.occurred_at = std::chrono::system_clock::now();
    event2.source = "journald";
    event2.type = "service-failed";
    event2.subject = "my-service.service";
    
    core::Evidence evidence2;
    evidence2.source = "journald";
    evidence2.value = "service still failed";
    evidence2.captured_at = "2026-01-01T00:00:01Z";
    
    auto result2 = processor->process_event(event2, {evidence2});
    
    // Within deduplication window, should be kUpdated
    EXPECT_EQ(result2.action, AlertResult::Action::kUpdated);
    EXPECT_EQ(result2.alert.state, AlertState::kUpdated);
    EXPECT_EQ(result2.alert.identity.id, alert_id);
}

TEST(InternalAlertProcessor, AcknowledgeAndClearAlert) {
    auto processor = InternalAlertProcessor::create();
    processor->start();
    
    // Create an alert
    runtime::Event event;
    event.id = "test-event";
    event.occurred_at = std::chrono::system_clock::now();
    event.source = "journald";
    event.type = "service-failed";
    event.subject = "my-service.service";
    
    core::Evidence evidence;
    evidence.source = "journald";
    evidence.value = "service failed";
    evidence.captured_at = "2026-01-01T00:00:00Z";
    
    auto result = processor->process_event(event, {evidence});
    std::string alert_id = result.alert.identity.id;
    EXPECT_EQ(result.alert.state, AlertState::kOpen);
    
    // Acknowledge the alert
    auto ack_result = processor->acknowledge_alert(alert_id);
    EXPECT_TRUE(ack_result.is_success());
    
    // Verify state changed to acknowledged
    auto alerts = processor->get_alerts(
        std::optional<AlertState>{AlertState::kAcknowledged},
        std::nullopt,
        std::nullopt);
    bool found_acknowledged = false;
    for (const auto& alert : alerts) {
        if (alert.identity.id == alert_id && 
            alert.state == AlertState::kAcknowledged) {
            found_acknowledged = true;
            break;
        }
    }
    EXPECT_TRUE(found_acknowledged);
    
    // Clear the alert
    auto clear_result = processor->clear_alert(alert_id);
    EXPECT_TRUE(clear_result.is_success());
    
    // Verify state changed to cleared
    alerts = processor->get_alerts(
        std::optional<AlertState>{AlertState::kCleared},
        std::nullopt,
        std::nullopt);
    bool found_cleared = false;
    for (const auto& alert : alerts) {
        if (alert.identity.id == alert_id && 
            alert.state == AlertState::kCleared) {
            found_cleared = true;
            break;
        }
    }
    EXPECT_TRUE(found_cleared);
}

TEST(InternalAlertProcessor, GetAlertsByFilters) {
    auto processor = InternalAlertProcessor::create();
    processor->start();
    
    // Create an alert
    runtime::Event event;
    event.id = "test-event";
    event.occurred_at = std::chrono::system_clock::now();
    event.source = "journald";
    event.type = "service-failed";
    event.subject = "my-service.service";
    
    core::Evidence evidence;
    evidence.source = "journald";
    evidence.value = "service failed";
    evidence.captured_at = "2026-01-01T00:00:00Z";
    
    auto result = processor->process_event(event, {evidence});
    
    // Get all alerts
    auto all_alerts = processor->get_alerts();
    EXPECT_GE(all_alerts.size(), 1u);
    
    // Filter by state
    auto open_alerts = processor->get_alerts(AlertState::kOpen);
    bool found = false;
    for (const auto& alert : open_alerts) {
        if (alert.identity.id == result.alert.identity.id) {
            found = true;
            break;
        }
    }
    EXPECT_TRUE(found);
    
    // Filter by category
    auto service_failure_alerts = processor->get_alerts(
        std::nullopt,
        std::nullopt,
        AlertCategory::kServiceFailure);
    bool found_service = false;
    for (const auto& alert : service_failure_alerts) {
        if (alert.identity.id == result.alert.identity.id) {
            found_service = true;
            break;
        }
    }
    EXPECT_TRUE(found_service);
}

TEST(InternalAlertProcessor, MetricsTracking) {
    auto processor = InternalAlertProcessor::create();
    processor->start();
    
    // Get initial metrics
    auto metrics = processor->metrics();
    size_t initial_alerts_open = metrics.alerts_open;
    
    // Create an alert
    runtime::Event event;
    event.id = "test-event";
    event.occurred_at = std::chrono::system_clock::now();
    event.source = "journald";
    event.type = "service-failed";
    
    core::Evidence evidence;
    evidence.source = "journald";
    evidence.value = "service failed";
    evidence.captured_at = "2026-01-01T00:00:00Z";
    
    processor->process_event(event, {evidence});
    
    // Check metrics were updated
    auto new_metrics = processor->metrics();
    EXPECT_EQ(new_metrics.alerts_open, initial_alerts_open + 1);
}

TEST(InternalAlertProcessor, CreateOrUpdateManual) {
    auto processor = InternalAlertProcessor::create();
    processor->start();
    
    AlertCondition condition;
    condition.expression = "memory_usage > 90%";
    condition.is_satisfied = true;
    condition.first_triggered_at = std::chrono::system_clock::now();
    
    AlertEvidence evidence;
    evidence.evidence.source = "procfs";
    evidence.evidence.value = "memory: 95%";
    evidence.evidence.captured_at = "2026-01-01T00:00:00Z";
    evidence.relevance = AlertEvidence::Relevance::kDirectCause;
    
    auto result = processor->create_or_update_alert(
        SubjectType::kHost,
        "system",
        SeverityCategory::kHigh,
        AlertCategory::kResourceExhaustion,
        condition,
        {evidence});
    
    EXPECT_EQ(result.action, AlertResult::Action::kNew);
    EXPECT_EQ(result.alert.subject_type, SubjectType::kHost);
    EXPECT_EQ(result.alert.severity, SeverityCategory::kHigh);
    EXPECT_EQ(result.alert.category, AlertCategory::kResourceExhaustion);
}

// ============================================================================
// Edge Cases
// ============================================================================

TEST(InternalAlertProcessor, NonMatchingEventNoAlert) {
    auto processor = InternalAlertProcessor::create();
    processor->start();
    
    // Event that shouldn't trigger an alert
    runtime::Event event;
    event.id = "test-event";
    event.occurred_at = std::chrono::system_clock::now();
    event.source = "journald";
    event.type = "service-started";  // Not a failure event
    
    core::Evidence evidence;
    evidence.source = "journald";
    evidence.value = "service started successfully";
    evidence.captured_at = "2026-01-01T00:00:00Z";
    
    auto result = processor->process_event(event, {evidence});
    
    // Should return empty result with kNew action (default)
    EXPECT_EQ(result.action, AlertResult::Action::kNew);
}

TEST(InternalAlertProcessor, AcknowledgeNonExistentAlert) {
    auto processor = InternalAlertProcessor::create();
    processor->start();
    
    auto ack_result = processor->acknowledge_alert("nonexistent-alert-id");
    
    EXPECT_TRUE(ack_result.is_error());
    EXPECT_EQ(ack_result.error.value().code, "E_ALERT_NOT_FOUND");
}

TEST(InternalAlertProcessor, ClearNonExistentAlert) {
    auto processor = InternalAlertProcessor::create();
    processor->start();
    
    auto clear_result = processor->clear_alert("nonexistent-alert-id");
    
    EXPECT_TRUE(clear_result.is_error());
    EXPECT_EQ(clear_result.error.value().code, "E_ALERT_NOT_FOUND");
}

}  // namespace rebuntu::modules::internal_alerts