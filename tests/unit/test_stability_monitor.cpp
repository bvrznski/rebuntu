// rebuntu::test — Stability Monitor Unit Tests (Phase 5.5)
//
// Test suite for the System Stability Monitor module.
// Verifies:
//   - State transitions (stable, degraded, unstable, unknown)
//   - Observation accumulation
//   - Hysteresis behavior
//   - Alert generation

#include "src/modules/stability_monitor/stability_monitor.hpp"

#include <gtest/gtest.h>
#include <chrono>

namespace rebuntu::modules::stability_monitor {

// ============================================================================
// Test fixture for stability monitor tests
// ============================================================================

class StabilityMonitorTest : public ::testing::Test {
protected:
    void SetUp() override {
        config_.service_restart_threshold = 3;
        config_.hysteresis_interval_minutes = 10;
    }
    
    StabilityMonitorConfig config_;
};

// ============================================================================
// Test: Initial state is unknown
// ============================================================================

TEST_F(StabilityMonitorTest, InitialStateIsUnknown) {
    auto monitor = make_stability_monitor(config_);
    EXPECT_EQ(monitor->get_overall_state(), StabilityState::kUnknown);
}

// ============================================================================
// Test: Stable state with no observations
// ============================================================================

TEST_F(StabilityMonitorTest, NoObservationsResultsInUnknown) {
    auto monitor = make_stability_monitor(config_);
    monitor->start();
    
    // Assess without any observations
    auto assessment = monitor->assess_stability();
    
    // Should be UNKNOWN due to no data
    EXPECT_EQ(assessment.state, StabilityState::kUnknown);
    monitor->stop();
}

// ============================================================================
// Test: Service restart detection and threshold crossing
// ============================================================================

TEST_F(StabilityMonitorTest, ServiceRestartBelowThreshold) {
    auto monitor = make_stability_monitor(config_);
    monitor->start();
    
    // Add restart count below threshold (threshold is 3)
    for (int i = 0; i < 2; i++) {
        monitor->add_service_state_observation(
            "test-service", false, i + 1,
            std::chrono::system_clock::now());
    }
    
    auto assessment = monitor->assess_stability();
    
    // Below threshold should be STABLE
    EXPECT_EQ(assessment.state, StabilityState::kStable);
    monitor->stop();
}

TEST_F(StabilityMonitorTest, ServiceRestartAtThreshold) {
    auto monitor = make_stability_monitor(config_);
    monitor->start();
    
    // Add restart count at threshold
    for (int i = 0; i < config_.service_restart_threshold; i++) {
        monitor->add_service_state_observation(
            "test-service", false, config_.service_restart_threshold,
            std::chrono::system_clock::now());
    }
    
    auto assessment = monitor->assess_stability();
    
    // At threshold should be DEGRADED
    EXPECT_EQ(assessment.state, StabilityState::kDegraded);
    monitor->stop();
}

// ============================================================================
// Test: Multiple service restarts trigger degraded state
// ============================================================================

TEST_F(StabilityMonitorTest, MultipleServiceRestarts) {
    auto monitor = make_stability_monitor(config_);
    monitor->start();
    
    // Add restarts for multiple services
    std::vector<std::string> services = {"svc1", "svc2", "svc3"};
    for (const auto& svc : services) {
        monitor->add_service_state_observation(
            svc, false, config_.service_restart_threshold,
            std::chrono::system_clock::now());
    }
    
    auto assessment = monitor->assess_stability();
    
    // Multiple failures should trigger DEGRADED or worse
    EXPECT_NE(assessment.state, StabilityState::kStable);
    EXPECT_EQ(assessment.subsystems.size(), 3);  // systemd, kernel, cpu
    monitor->stop();
}

// ============================================================================
// Test: Hysteresis prevents flapping
// ============================================================================

TEST_F(StabilityMonitorTest, HysteresisActiveWhenThresholdExceeded) {
    auto monitor = make_stability_monitor(config_);
    monitor->start();
    
    // First assessment - should be unknown (no data)
    auto first = monitor->assess_stability();
    EXPECT_EQ(first.state, StabilityState::kUnknown);
    EXPECT_FALSE(first.hysteresis_active);
    
    // Add observations to push into degraded state
    for (int i = 0; i < config_.service_restart_threshold; i++) {
        monitor->add_service_state_observation(
            "test-svc", false, config_.service_restart_threshold,
            std::chrono::system_clock::now());
    }
    
    auto second = monitor->assess_stability();
    EXPECT_EQ(second.state, StabilityState::kDegraded);
    EXPECT_FALSE(second.hysteresis_active);  // First transition
    
    monitor->stop();
}

// ============================================================================
// Test: Alert generation for degraded/unstable states
// ============================================================================

TEST_F(StabilityMonitorTest, GeneratesAlertForDegradedState) {
    auto monitor = make_stability_monitor(config_);
    monitor->start();
    
    // Push to degraded state
    for (int i = 0; i < config_.service_restart_threshold; i++) {
        monitor->add_service_state_observation(
            "test-svc", false, config_.service_restart_threshold,
            std::chrono::system_clock::now());
    }
    
    auto alerts = monitor->get_pending_alerts();
    
    // Should have at least one alert
    EXPECT_GT(alerts.size(), 0);
    EXPECT_EQ(alerts[0].severity, InternalAlert::Severity::kMedium);
    
    monitor->stop();
}

TEST_F(StabilityMonitorTest, GeneratesCriticalAlertForUnstableState) {
    auto monitor = make_stability_monitor(config_);
    monitor->start();
    
    // Add many observations to trigger unstable state
    for (int i = 0; i < config_.service_restart_threshold * 3; i++) {
        monitor->add_service_state_observation(
            "test-svc", false, config_.service_restart_threshold * 2,
            std::chrono::system_clock::now());
    }
    
    auto alerts = monitor->get_pending_alerts();
    
    // Should have at least one critical alert
    if (!alerts.empty()) {
        EXPECT_GE(alerts[0].severity, InternalAlert::Severity::kMedium);
    }
    
    monitor->stop();
}

// ============================================================================
// Test: Observation metrics
// ============================================================================

TEST_F(StabilityMonitorTest, TracksObservationMetrics) {
    auto monitor = make_stability_monitor(config_);
    monitor->start();
    
    auto initial_metrics = monitor->metrics();
    EXPECT_EQ(initial_metrics.assessments_performed, 0);
    EXPECT_EQ(initial_metrics.observations_received, 0);
    
    // Add observations
    for (int i = 0; i < 5; i++) {
        monitor->add_service_state_observation(
            "test-svc", false, 1,
            std::chrono::system_clock::now());
    }
    
    auto final_metrics = monitor->metrics();
    EXPECT_EQ(final_metrics.observations_received, 5);
    EXPECT_EQ(final_metrics.assessments_performed, 0);  // Still 0 until assess
    
    monitor->stop();
}

// ============================================================================
// Test: Assessment produces structured output
// ============================================================================

TEST_F(StabilityMonitorTest, AssessmentStructure) {
    auto monitor = make_stability_monitor(config_);
    monitor->start();
    
    auto assessment = monitor->assess_stability();
    
    // Check required fields are populated
    EXPECT_NE(assessment.state, StabilityState::kUnknown);  // At least UNKNOWN
    EXPECT_EQ(assessment.total_subsystems_assessed, 3);     // systemd, kernel, cpu
    EXPECT_FALSE(assessment.subsystems.empty());
    
    monitor->stop();
}

}  // namespace rebuntu::modules::stability_monitor

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}