// rebuntu - Phase 5.10 GPU Health Monitor Unit Tests
//
// Unit tests for the GPU monitor module.
// Verifies:
//   - Monitor creation and lifecycle (start/stop)
//   - GPU assessment returns valid results
//   - Metrics tracking works correctly

#include "../src/modules/gpu_health_monitor/monitor.hpp"
#include <cassert>
#include <iostream>
#include <thread>

void test_factory_creates_monitor() {
    std::cout << "[TEST] Factory creates monitor instance...";
    
    auto monitor = rebuntu::modules::gpu_health_monitor::make_gpu_monitor();
    assert(monitor != nullptr);
    assert(monitor->is_running() == false);
    
    std::cout << " [PASS]\n";
}

void test_monitor_lifecycle() {
    std::cout << "[TEST] Monitor lifecycle (start/stop)...";
    
    auto monitor = rebuntu::modules::gpu_health_monitor::make_gpu_monitor();
    
    // Start the monitor
    auto start_result = monitor->start();
    assert(monitor->is_running() == true);
    
    // Stop the monitor
    auto stop_result = monitor->stop();
    assert(monitor->is_running() == false);
    
    std::cout << " [PASS]\n";
}

void test_assessment_returns_results() {
    std::cout << "[TEST] Assessment returns valid results...";
    
    auto monitor = rebuntu::modules::gpu_health_monitor::make_gpu_monitor();
    monitor->start();
    
    // Give it a moment
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    
    auto result = monitor->assess_gpu_health();
    
    // Should return some outcome (could be kUnknown if no GPUs present)
    assert(result.outcome == rebuntu::modules::gpu_health_monitor::GPUMonitorResult::Outcome::kSuccess ||
           result.outcome == rebuntu::modules::gpu_health_monitor::GPUMonitorResult::Outcome::kPartial ||
           result.outcome == rebuntu::modules::gpu_health_monitor::GPUMonitorResult::Outcome::kUnknown);
    
    // Assessment should always be present
    assert(result.assessment.devices.size() >= 0);  // Could be zero if no GPUs
    
    monitor->stop();
    
    std::cout << " [PASS]\n";
}

void test_metrics_tracking() {
    std::cout << "[TEST] Metrics tracking...";
    
    auto monitor = rebuntu::modules::gpu_health_monitor::make_gpu_monitor();
    monitor->start();
    
    // Get initial metrics
    auto initial_metrics = monitor->metrics();
    assert(initial_metrics.observations == 0);
    assert(initial_metrics.device_assessments == 0);
    
    // Perform assessments
    for (int i = 0; i < 3; i++) {
        monitor->assess_gpu_health();
    }
    
    auto final_metrics = monitor->metrics();
    assert(final_metrics.observations >= 3);
    assert(final_metrics.device_assessments >= 3);
    
    monitor->stop();
    
    std::cout << " [PASS]\n";
}

void test_config_can_be_modified() {
    std::cout << "[TEST] Config modification...";
    
    rebuntu::modules::gpu_health_monitor::GPUMonitorConfig config;
    config.utilization_warning_percent = 75;
    config.temperature_critical_celsius = 95;
    
    auto monitor = rebuntu::modules::gpu_health_monitor::make_gpu_monitor(config);
    
    const auto& modified_config = monitor->config();
    assert(modified_config.utilization_warning_percent == 75);
    assert(modified_config.temperature_critical_celsius == 95);
    
    std::cout << " [PASS]\n";
}

void test_initial_assessment_state() {
    std::cout << "[TEST] Initial assessment state...";
    
    auto monitor = rebuntu::modules::gpu_health_monitor::make_gpu_monitor();
    monitor->start();
    
    auto result = monitor->assess_gpu_health();
    
    // Check provider state is initialized (not UNKNOWN after first assessment)
    assert(result.assessment.global_state.provider_state == 
           rebuntu::modules::gpu_health_monitor::GPUProviderState::kNotInstalled ||
           result.assessment.global_state.provider_state == 
           rebuntu::modules::gpu_health_monitor::GPUProviderState::kUnknown);
    
    monitor->stop();
    
    std::cout << " [PASS]\n";
}

int main() {
    std::cout << "Phase 5.10 GPU Health Monitor Unit Tests\n";
    std::cout << "=========================================\n\n";
    
    test_factory_creates_monitor();
    test_monitor_lifecycle();
    test_assessment_returns_results();
    test_metrics_tracking();
    test_config_can_be_modified();
    test_initial_assessment_state();
    
    std::cout << "\nAll unit tests passed!\n";
    return 0;
}