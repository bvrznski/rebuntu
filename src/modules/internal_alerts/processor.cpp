// rebuntu::modules::internal_alerts::Processor — Internal Alert Processor (Phase 5.14)
//
// This module implements the canonical internal alert service for Rebuntu:
//   - Processes events and generates alerts from conditions
//   - Deduplicates repeated equivalent conditions within windows
//   - Correlates related alerts without merging unrelated subjects
//   - Tracks alert lifecycle state (open, updated, acknowledged, cleared, closed)

#include "src/modules/internal_alerts/processor.hpp"

#include <algorithm>
#include <memory>
#include <random>
#include <sstream>
#include <thread>

namespace rebuntu::modules::internal_alerts {

// ============================================================================
// Factory function
// ============================================================================

std::unique_ptr<InternalAlertProcessor> InternalAlertProcessor::create(
    const AlertDeduplicationConfig& dedup_config,
    const AlertCorrelationConfig& corr_config) {
    return std::make_unique<InternalAlertProcessor>(dedup_config, corr_config);
}

// ============================================================================
// Constructors and destructors
// ============================================================================

InternalAlertProcessor::InternalAlertProcessor(
    const AlertDeduplicationConfig& dedup_config,
    const AlertCorrelationConfig& corr_config)
    : dedup_config_(dedup_config),
      corr_config_(corr_config) {
    metrics_.started_at = std::chrono::system_clock::now();
}

InternalAlertProcessor::~InternalAlertProcessor() = default;

// ============================================================================
// Lifecycle methods
// ============================================================================

core::Outcome InternalAlertProcessor::configure(
    const AlertDeduplicationConfig& dedup_config,
    const AlertCorrelationConfig& corr_config) {
    std::lock_guard<std::mutex> lock(mutex_);
    
    dedup_config_ = dedup_config;
    corr_config_ = corr_config;
    
    return core::Outcome::success();
}

core::Outcome InternalAlertProcessor::start() {
    std::lock_guard<std::mutex> lock(mutex_);
    metrics_.alerts_open = 0;
    metrics_.alerts_cleared = 0;
    metrics_.alerts_closed = 0;
    return core::Outcome::success();
}

core::Outcome InternalAlertProcessor::stop() {
    std::lock_guard<std::mutex> lock(mutex_);
    // Clean up any remaining alerts
    cleanup_old_alerts(std::chrono::system_clock::now());
    return core::Outcome::success();
}

bool InternalAlertProcessor::is_running() const {
    // For now, always return true (could be extended with a flag)
    return true;
}

// ============================================================================
// ID generation helpers
// ============================================================================

std::string InternalAlertProcessor::generate_alert_id() {
    static std::atomic<size_t> counter{0};
    
    auto now = std::chrono::system_clock::now();
    auto epoch = now.time_since_epoch();
    
    std::stringstream ss;
    ss << "alert-"
       << std::this_thread::get_id() << "-"
       << epoch.count() << "-"
       << counter++;
    
    return ss.str();
}

std::string InternalAlertProcessor::generate_dedupe_key(
    SubjectType subject_type,
    const std::string& subject_id,
    AlertCategory category) {
    std::stringstream ss;
    ss << to_string(category) << ":" 
       << to_string(subject_type) << ":"
       << subject_id;
    return ss.str();
}

// ============================================================================
// Event processing
// ============================================================================

bool InternalAlertProcessor::should_create_alert(
    const runtime::Event& event,
    SeverityCategory& out_severity,
    AlertCategory& out_category) const {
    // Determine if this event should trigger an alert based on its type
    // This is a simplified implementation - real logic would check conditions
    
    const std::string& event_type = event.type;
    
    // Check for failure-related event types
    if (event_type.find("failure") != std::string::npos ||
        event_type.find("failed") != std::string::npos ||
        event_type.find("crash") != std::string::npos) {
        out_severity = SeverityCategory::kHigh;
        out_category = AlertCategory::kServiceFailure;
        return true;
    }
    
    if (event_type.find("oom") != std::string::npos ||
        event_type.find("memory") != std::string::npos) {
        out_severity = SeverityCategory::kCritical;
        out_category = AlertCategory::kResourceExhaustion;
        return true;
    }
    
    if (event_type.find("health") != std::string::npos &&
        event_type.find("degraded") != std::string::npos) {
        out_severity = SeverityCategory::kMedium;
        out_category = AlertCategory::kHealthDegradation;
        return true;
    }
    
    // Default: not an alert
    return false;
}

std::optional<std::string> InternalAlertProcessor::find_existing_alert(
    const std::string& dedupe_key,
    std::chrono::system_clock::time_point event_time) {
    auto it = dedupe_map_.find(dedupe_key);
    if (it == dedupe_map_.end()) {
        return std::nullopt;
    }
    
    // Check if within deduplication window
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(
        event_time - it->second.last_occurrence).count();
    
    if (elapsed < dedup_config_.deduplication_window.count()) {
        return it->second.alert_id;
    }
    
    // Window expired, treat as new occurrence
    return std::nullopt;
}

void InternalAlertProcessor::update_alert_state(
    InternalAlert& alert,
    bool condition_now_satisfied,
    std::chrono::system_clock::time_point now) {
    if (condition_now_satisfied) {
        if (alert.state == AlertState::kCleared || 
            alert.state == AlertState::kClosed) {
            // Recurrence after clear - reopen
            alert.state = AlertState::kOpen;
            alert.occurrence_count++;
            alert.last_occurrence_at = now;
            alert.last_updated_at = now;
        } else if (alert.state == AlertState::kOpen) {
            // Still open - update timestamp
            alert.last_updated_at = now;
            alert.occurrence_count++;
            alert.last_occurrence_at = now;
        }
    } else {
        // Condition no longer satisfied
        alert.state = AlertState::kCleared;
        alert.cleared_at = now;
    }
}

std::vector<std::string> InternalAlertProcessor::correlate_alerts(
    const InternalAlert& alert,
    std::chrono::system_clock::time_point event_time) {
    std::vector<std::string> correlated_ids;
    
    // Find alerts in the same correlation window
    auto range = correlation_windows_.equal_range(alert.subject_id);
    for (auto it = range.first; it != range.second; ++it) {
        const auto& window = it->second;
        
        // Check if within time window
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(
            event_time - window.start_time).count();
        
        if (elapsed <= corr_config_.correlation_window.count()) {
            for (const auto& id : window.alert_ids) {
                if (id != alert.identity.id && 
                    std::find(correlated_ids.begin(), correlated_ids.end(), id) == correlated_ids.end()) {
                    correlated_ids.push_back(id);
                }
            }
        }
    }
    
    // Add this alert to the correlation window
    CorrelationWindow window;
    window.alert_ids.push_back(alert.identity.id);
    window.start_time = event_time;
    window.end_time = event_time + corr_config_.correlation_window;
    
    correlation_windows_.insert({alert.subject_id, window});
    
    // Clean up old windows (keep only recent)
    auto cutoff = event_time - corr_config_.correlation_window;
    for (auto it = correlation_windows_.begin(); it != correlation_windows_.end();) {
        if (it->second.end_time < cutoff) {
            it = correlation_windows_.erase(it);
        } else {
            ++it;
        }
    }
    
    return correlated_ids;
}

void InternalAlertProcessor::cleanup_old_alerts(std::chrono::system_clock::time_point now) {
    // Remove alerts that are closed and beyond retention period
    auto cutoff = now - dedup_config_.retention_after_clear;
    
    for (auto it = alerts_by_id_.begin(); it != alerts_by_id_.end();) {
        if (it->second.state == AlertState::kClosed || 
            it->second.cleared_at.value_or(std::chrono::system_clock::time_point{}) < cutoff) {
            // Update metrics
            if (it->second.state == AlertState::kOpen) {
                metrics_.alerts_open--;
            } else if (it->second.state == AlertState::kCleared) {
                metrics_.alerts_cleared--;
            }
            
            it = alerts_by_id_.erase(it);
        } else {
            ++it;
        }
    }
}

void InternalAlertProcessor::record_action(AlertResult::Action action, const InternalAlert& alert) {
    switch (action) {
        case AlertResult::Action::kNew:
            metrics_.alerts_open++;
            break;
        case AlertResult::Action::kUpdated:
            metrics_.deduplicated_alerts++;
            break;
        case AlertResult::Action::kAcknowledged:
            metrics_.alerts_acknowledged++;
            break;
        case AlertResult::Action::kCleared:
            metrics_.alerts_cleared++;
            if (metrics_.alerts_open > 0) {
                metrics_.alerts_open--;
            }
            break;
        case AlertResult::Action::kCorrelated:
            metrics_.correlated_alerts++;
            break;
        default:
            break;
    }
    
    // Update severity/category counts
    auto& sev_count = metrics_.alerts_by_severity[alert.severity];
    if (action == AlertResult::Action::kNew) {
        sev_count++;
    } else if (action == AlertResult::Action::kCleared) {
        sev_count--;
    }
    
    auto& cat_count = metrics_.alerts_by_category[alert.category];
    if (action == AlertResult::Action::kNew) {
        cat_count++;
    } else if (action == AlertResult::Action::kCleared) {
        cat_count--;
    }
}

// ============================================================================
// Main processing methods
// ============================================================================

AlertResult InternalAlertProcessor::process_event(
    const runtime::Event& event,
    const std::vector<core::Evidence>& evidence) {
    std::lock_guard<std::mutex> lock(mutex_);
    
    AlertResult result;
    SeverityCategory severity = SeverityCategory::kInfo;
    AlertCategory category = AlertCategory::kServiceFailure;
    
    if (!should_create_alert(event, severity, category)) {
        return result;  // Not an alert
    }
    
    // Determine subject from event
    SubjectType subject_type = SubjectType::kHost;
    std::string subject_id = "system";
    
    if (event.subject.has_value()) {
        subject_id = event.subject.value();
        
        // Try to infer subject type
        if (subject_id.find("service") != std::string::npos ||
            subject_id.find(".service") != std::string::npos) {
            subject_type = SubjectType::kService;
        } else if (subject_id.find("/") != std::string::npos) {
            subject_type = SubjectType::kFileSystem;
        }
    }
    
    // Generate deduplication key
    std::string dedupe_key = generate_dedupe_key(subject_type, subject_id, category);
    
    // Check for existing alert in window
    auto existing_id_opt = find_existing_alert(dedupe_key, event.occurred_at);
    
    if (existing_id_opt.has_value()) {
        // Update existing alert
        auto& existing_alert = alerts_by_id_[existing_id_opt.value()];
        
        result.action = AlertResult::Action::kUpdated;
        result.alert = existing_alert;
        result.alert.state = AlertState::kUpdated;
        result.alert.last_updated_at = event.occurred_at;
        result.alert.occurrence_count++;
        
        // Update evidence with new information
        for (const auto& ev : evidence) {
            AlertEvidence ae;
            ae.evidence = ev;
            ae.relevance = AlertEvidence::Relevance::kCorroborating;
            result.alert.evidence.push_back(ae);
        }
        
        record_action(result.action, result.alert);
    } else {
        // Create new alert
        std::string alert_id = generate_alert_id();
        std::string dedupe_key = generate_dedupe_key(subject_type, subject_id, category);
        
        AlertCondition condition;
        condition.expression = "event occurred: " + event.type;
        condition.is_satisfied = true;
        condition.first_triggered_at = event.occurred_at;
        
        InternalAlert alert;
        alert.identity.id = alert_id;
        alert.identity.dedupe_key = dedupe_key;
        alert.state = AlertState::kOpen;
        alert.created_at = event.occurred_at;
        alert.severity = severity;
        alert.category = category;
        alert.subject_type = subject_type;
        alert.subject_id = subject_id;
        alert.condition = condition;
        
        // Add evidence
        for (const auto& ev : evidence) {
            AlertEvidence ae;
            ae.evidence = ev;
            ae.relevance = AlertEvidence::Relevance::kDirectCause;
            alert.evidence.push_back(ae);
        }
        
        alert.occurrence_count = 1;
        alert.first_seen_at = event.occurred_at;
        alert.last_occurrence_at = event.occurred_at;
        
        // Add recommended actions
        InternalAlert::RecommendedAction ra;
        ra.category = "investigate";
        ra.description = "Investigate the " + to_string(category) + " condition for " + subject_id;
        alert.recommended_actions.push_back(ra);
        
        // Correlate with other alerts
        auto correlated_ids = correlate_alerts(alert, event.occurred_at);
        result.correlated_alert_ids = correlated_ids;
        
        result.action = AlertResult::Action::kNew;
        result.alert = alert;
        
        // Store in maps
        alerts_by_id_[alert_id] = alert;
        
        DedupeEntry entry;
        entry.alert_id = alert_id;
        entry.first_seen = event.occurred_at;
        entry.last_occurrence = event.occurred_at;
        entry.occurrence_count = 1;
        dedupe_map_[dedupe_key] = entry;
        
        record_action(result.action, result.alert);
    }
    
    return result;
}

AlertResult InternalAlertProcessor::create_or_update_alert(
    SubjectType subject_type,
    const std::string& subject_id,
    SeverityCategory severity,
    AlertCategory category,
    AlertCondition condition,
    std::vector<AlertEvidence> evidence) {
    std::lock_guard<std::mutex> lock(mutex_);
    
    AlertResult result;
    
    // Generate deduplication key
    std::string dedupe_key = generate_dedupe_key(subject_type, subject_id, category);
    
    auto now = std::chrono::system_clock::now();
    
    // Check for existing alert in window
    auto existing_id_opt = find_existing_alert(dedupe_key, now);
    
    if (existing_id_opt.has_value()) {
        // Update existing alert
        auto& alert = alerts_by_id_[existing_id_opt.value()];
        
        result.action = AlertResult::Action::kUpdated;
        result.alert = alert;
        result.alert.state = AlertState::kUpdated;
        result.alert.last_updated_at = now;
        result.alert.occurrence_count++;
        result.alert.condition = condition;
        
        // Add new evidence
        for (const auto& ae : evidence) {
            result.alert.evidence.push_back(ae);
        }
        
        record_action(result.action, result.alert);
    } else {
        // Create new alert
        std::string alert_id = generate_alert_id();
        
        InternalAlert alert;
        alert.identity.id = alert_id;
        alert.identity.dedupe_key = dedupe_key;
        alert.state = AlertState::kOpen;
        alert.created_at = now;
        alert.severity = severity;
        alert.category = category;
        alert.subject_type = subject_type;
        alert.subject_id = subject_id;
        alert.condition = condition;
        
        // Add evidence
        for (const auto& ae : evidence) {
            alert.evidence.push_back(ae);
        }
        
        alert.occurrence_count = 1;
        alert.first_seen_at = now;
        alert.last_occurrence_at = now;
        
        // Add recommended actions
        InternalAlert::RecommendedAction ra;
        ra.category = "investigate";
        ra.description = "Investigate the " + to_string(category) + " condition for " + subject_id;
        alert.recommended_actions.push_back(ra);
        
        result.action = AlertResult::Action::kNew;
        result.alert = alert;
        
        // Store in maps
        alerts_by_id_[alert_id] = alert;
        
        DedupeEntry entry;
        entry.alert_id = alert_id;
        entry.first_seen = now;
        entry.last_occurrence = now;
        entry.occurrence_count = 1;
        dedupe_map_[dedupe_key] = entry;
        
        record_action(result.action, result.alert);
    }
    
    return result;
}

core::Outcome InternalAlertProcessor::acknowledge_alert(const std::string& alert_id) {
    std::lock_guard<std::mutex> lock(mutex_);
    
    auto it = alerts_by_id_.find(alert_id);
    if (it == alerts_by_id_.end()) {
        return core::Outcome::failure("E_ALERT_NOT_FOUND", "Alert not found: " + alert_id);
    }
    
    it->second.state = AlertState::kAcknowledged;
    it->second.last_updated_at = std::chrono::system_clock::now();
    
    metrics_.alerts_acknowledged++;
    
    return core::Outcome::success();
}

core::Outcome InternalAlertProcessor::clear_alert(const std::string& alert_id) {
    std::lock_guard<std::mutex> lock(mutex_);
    
    auto it = alerts_by_id_.find(alert_id);
    if (it == alerts_by_id_.end()) {
        return core::Outcome::failure("E_ALERT_NOT_FOUND", "Alert not found: " + alert_id);
    }
    
    auto& alert = it->second;
    alert.state = AlertState::kCleared;
    alert.cleared_at = std::chrono::system_clock::now();
    alert.last_updated_at = alert.cleared_at;
    
    metrics_.alerts_cleared++;
    if (metrics_.alerts_open > 0) {
        metrics_.alerts_open--;
    }
    
    return core::Outcome::success();
}

std::vector<InternalAlert> InternalAlertProcessor::get_alerts(
    std::optional<AlertState> state_filter,
    std::optional<SeverityCategory> severity_filter,
    std::optional<AlertCategory> category_filter) {
    std::lock_guard<std::mutex> lock(mutex_);
    
    std::vector<InternalAlert> result;
    
    for (const auto& [id, alert] : alerts_by_id_) {
        if (state_filter.has_value() && alert.state != state_filter.value()) {
            continue;
        }
        if (severity_filter.has_value() && alert.severity != severity_filter.value()) {
            continue;
        }
        if (category_filter.has_value() && alert.category != category_filter.value()) {
            continue;
        }
        
        result.push_back(alert);
    }
    
    return result;
}

AlertMetrics InternalAlertProcessor::metrics() const {
    std::lock_guard<std::mutex> lock(mutex_);
    return metrics_;
}

}  // namespace rebuntu::modules::internal_alerts

// ============================================================================
// Factory function (free function)
// ============================================================================

std::unique_ptr<rebuntu::modules::internal_alerts::AlertProcessor>
make_alert_processor() {
    using namespace rebuntu::modules::internal_alerts;
    return InternalAlertProcessor::create();
}