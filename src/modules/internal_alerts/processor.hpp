// rebuntu::modules::internal_alerts::Processor — Internal Alert Processor (Phase 5.14)
//
// This module implements the canonical internal alert service for Rebuntu:
//   - Processes events and generates alerts from conditions
//   - Deduplicates repeated equivalent conditions within windows
//   - Correlates related alerts without merging unrelated subjects
//   - Tracks alert lifecycle state (open, updated, acknowledged, cleared, closed)
//
// Key Design Principles:
//   * Observation → Fact → Assertion/Condition → Alert (if condition satisfied)
//   * Deduplication window: prevent alert storms while allowing recurrence
//   * Correlation: group by subject/time without losing individual identity
//   * Evidence linkage: provenance-bearing observations

#pragma once

#include "types.hpp"

#include <runtime/contracts.hpp>
#include <system/core/contracts.hpp>

#include <chrono>
#include <cstdint>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <optional>
#include <mutex>
#include <atomic>

namespace rebuntu::modules::internal_alerts {

// ============================================================================
// InternalAlertProcessor — Implementation of AlertProcessor interface
// ============================================================================

class InternalAlertProcessor : public AlertProcessor {
public:
    // Factory function (friend to access constructor)
    static std::unique_ptr<InternalAlertProcessor> create(
        const AlertDeduplicationConfig& dedup_config = AlertDeduplicationConfig{},
        const AlertCorrelationConfig& corr_config = AlertCorrelationConfig{});
    
    virtual ~InternalAlertProcessor() override;
    
    // Configure the processor
    core::Outcome configure(
        const AlertDeduplicationConfig& dedup_config,
        const AlertCorrelationConfig& corr_config) override;
    
    // Start/stop lifecycle
    core::Outcome start() override;
    core::Outcome stop() override;
    bool is_running() const override;
    
    // Process an event and generate alerts if conditions are met
    AlertResult process_event(
        const runtime::Event& event,
        const std::vector<core::Evidence>& evidence) override;
    
    // Manually create/update an alert (e.g., from condition evaluation)
    AlertResult create_or_update_alert(
        SubjectType subject_type,
        const std::string& subject_id,
        SeverityCategory severity,
        AlertCategory category,
        AlertCondition condition,
        std::vector<AlertEvidence> evidence) override;
    
    // Acknowledge an alert
    core::Outcome acknowledge_alert(const std::string& alert_id) override;
    
    // Clear an alert (condition no longer satisfied)
    core::Outcome clear_alert(const std::string& alert_id) override;
    
    // Get current alerts by state/category/severity
    std::vector<InternalAlert> get_alerts(
        std::optional<AlertState> state_filter = std::nullopt,
        std::optional<SeverityCategory> severity_filter = std::nullopt,
        std::optional<AlertCategory> category_filter = std::nullopt) override;
    
    // Get metrics
    AlertMetrics metrics() const override;

public:
    InternalAlertProcessor(
        const AlertDeduplicationConfig& dedup_config,
        const AlertCorrelationConfig& corr_config);
private:
    // Generate a unique ID for an alert
    static std::string generate_alert_id();
    
    // Generate a deduplication key for an alert
    static std::string generate_dedupe_key(
        SubjectType subject_type,
        const std::string& subject_id,
        AlertCategory category);
    
    // Process the event to determine if it should trigger an alert
    bool should_create_alert(
        const runtime::Event& event,
        SeverityCategory& out_severity,
        AlertCategory& out_category) const;
    
    // Check if this is a recurrence within the deduplication window
    std::optional<std::string> find_existing_alert(
        const std::string& dedupe_key,
        std::chrono::system_clock::time_point event_time);
    
    // Update alert state based on condition status
    void update_alert_state(
        InternalAlert& alert,
        bool condition_now_satisfied,
        std::chrono::system_clock::time_point now);
    
    // Correlate this alert with others in the window
    std::vector<std::string> correlate_alerts(
        const InternalAlert& alert,
        std::chrono::system_clock::time_point event_time);
    
    // Clean up old alerts (beyond retention period)
    void cleanup_old_alerts(std::chrono::system_clock::time_point now);
    
    // Update metrics for an action
    void record_action(AlertResult::Action action, const InternalAlert& alert);
    
    // Config
    AlertDeduplicationConfig dedup_config_;
    AlertCorrelationConfig corr_config_;
    
    // State (protected by mutex)
    mutable std::mutex mutex_;
    
    // Active alerts by ID
    std::unordered_map<std::string, InternalAlert> alerts_by_id_;
    
    // Deduplication map: key → alert_id (for dedup within window)
    struct DedupeEntry {
        std::string alert_id;
        std::chrono::system_clock::time_point first_seen;
        std::chrono::system_clock::time_point last_occurrence;
        size_t occurrence_count;
    };
    std::unordered_map<std::string, DedupeEntry> dedupe_map_;
    
    // Correlation window entries
    struct CorrelationWindow {
        std::vector<std::string> alert_ids;
        std::chrono::system_clock::time_point start_time;
        std::chrono::system_clock::time_point end_time;
    };
    std::unordered_multimap<std::string, CorrelationWindow> correlation_windows_;
    
    // Metrics (atomic for lock-free reads)
    AlertMetrics metrics_;
};

}  // namespace rebuntu::modules::internal_alerts