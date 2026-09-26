// rebuntu::modules::reporting::Generator — Report Generator Implementation (Phase 5.15)
//
// This module implements Rebuntu's canonical reporting service:
//   - Generates structured diagnostic reports from assessment data
//   - Sends notifications via pluggable delivery mechanisms
//   - Rate limiting and deduplication of notifications

#pragma once

#include <modules/reporting/types.hpp>

#include <runtime/contracts.hpp>
#include <system/core/contracts.hpp>

#include <chrono>
#include <cstdint>
#include <string>
#include <vector>
#include <mutex>
#include <memory>

namespace rebuntu::modules::reporting {

// ============================================================================
// NotificationRateLimiter — Rate limiting and deduplication for notifications
// ============================================================================

class NotificationRateLimiter {
public:
    explicit NotificationRateLimiter(NotificationRateLimitConfig config);
    
    std::optional<std::string> can_send(const Notification& notification, std::chrono::system_clock::time_point now);
    void record_success(NotificationDestination destination, std::chrono::system_clock::time_point now);
    void record_failure(NotificationDestination destination, std::chrono::system_clock::time_point now);
    
    RateLimiterStatus get_status(NotificationDestination destination) const;
    void reset();

private:
    NotificationRateLimitConfig config_;
    mutable std::mutex mutex_;
};

// ============================================================================
// NotificationDelivery — Implementation of notification delivery mechanisms
// ============================================================================

class NotificationDelivery {
public:
    explicit NotificationDelivery(const NotificationDeliveryConfig& config);
    
    DeliveryResult send(const Notification& notification);

private:
    NotificationDeliveryConfig config_;
    mutable std::mutex mutex_;
};

// ============================================================================
// ReportGeneratorImpl — Implementation of ReportGenerator interface
// ============================================================================

class ReportGeneratorImpl : public ReportGenerator {
public:
    explicit ReportGeneratorImpl();
    ~ReportGeneratorImpl() override = default;
    
    core::Outcome configure(const ReportGeneratorOptions& options) override;
    core::Outcome start() override;
    core::Outcome stop() override;
    bool is_running() const override;
    
    std::optional<Report> generate_report(
        ReportKind kind,
        const AssessmentSummary& summary,
        const std::vector<core::Evidence>& evidence,
        const std::chrono::system_clock::time_point& created_at) override;
    
    DeliveryResult send_notification(const Notification& notification) override;
    
    ReportGeneratorMetrics metrics() const override;

private:
    static std::string generate_report_id();
    static std::string generate_notification_id();
    Notification create_notification_from_report(const Report& report);
    
    ReportGeneratorOptions options_;
    mutable std::mutex mutex_;
    
    bool is_started_ = false;
    std::chrono::system_clock::time_point started_at_;
    ReportGeneratorMetrics metrics_;
    std::unique_ptr<NotificationRateLimiter> rate_limiter_;
};

// ============================================================================
// ReportRendererImpl — Implementation of ReportRenderer interface
// ============================================================================

class ReportRendererImpl : public ReportRenderer {
public:
    explicit ReportRendererImpl();
    ~ReportRendererImpl() override;
    
    std::string render_human(const Report& report) override;
    std::string render_json(const Report& report) override;
    std::string render_summary(const Report& report) override;

private:
    std::string format_timestamp(std::chrono::system_clock::time_point tp);
    std::string indent(int level);
    std::string escape_json_string(const std::string& input);
};

// ============================================================================
// Factory functions
// ============================================================================

std::unique_ptr<ReportGenerator> make_report_generator();
std::unique_ptr<ReportRenderer> make_report_renderer();

}  // namespace rebuntu::modules::reporting