// rebuntu::modules::health_monitor::adapters — Journald Observer Adapter (Phase 5.6)
//
// Observes systemd unit state changes from journald and provides health signals
// to the HealthMonitor.

#pragma once

#include <modules/health_monitor/types.hpp>
#include <adapters/journal_normalizer.hpp>

#include <memory>
#include <string>
#include <chrono>
#include <functional>
#include <map>
#include <optional>

namespace rebuntu::modules::health_monitor::adapters {

// ============================================================================
// JournaldObserver — Observes systemd-related events from journald
//
// Listens for:
//   - UNIT_FAILED events (systemd unit entered failed state)
//   - UNIT_STOPPED events (unit stopped unexpectedly)
//   - SERVICE_RESTART events (excessive restarts indicate crash loop)
// ============================================================================

class JournaldObserver {
public:
    explicit JournaldObserver(HealthMonitorConfig config);
    ~JournaldObserver();
    
    core::Outcome start();
    core::Outcome stop();
    bool is_running() const { return running_; }
    
    void set_health_callback(std::function<void(const ServiceHealth&)> callback);
    
    // Process a normalized journal event and extract health signals
    core::Outcome process_journal_event(
        const rebuntu::adapters::NormalizedEvent& event,
        std::chrono::system_clock::time_point observation_time);

private:
    HealthMonitorConfig config_;
    bool running_ = false;
    std::function<void(const ServiceHealth&)> health_callback_;
    
    struct UnitState {
        int restart_count = 0;
        std::optional<std::chrono::system_clock::time_point> first_restart_time;
        bool failed_once = false;
    };
    std::map<std::string, UnitState> unit_states_;
    
    core::Outcome process_systemd_unit_event(
        const rebuntu::adapters::NormalizedEvent& event,
        std::chrono::system_clock::time_point observation_time);
    
    bool is_in_crash_loop(const UnitState& state) const;
};

std::unique_ptr<JournaldObserver> make_journald_observer(
    const HealthMonitorConfig& config);

}  // namespace rebuntu::modules::health_monitor::adapters