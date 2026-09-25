// rebuntu - Phase 5.9 CPU / Memory / Thermal Monitor Unit Tests
//
// Unit tests for the CPU/Memory/Thermal monitor module.
// Verifies:
//   - Monitor creation and lifecycle (start/stop)
//   - Resource assessment returns valid results
//   - Metrics tracking works correctly

#include "src/modules/cpu_memory_thermal_monitor/monitor.hpp"
#include <cassert>
#include <iostream>
#include <thread>

void test_factory_creates_monitor() {
    std::cout << "[TEST] Factory creates monitor instance...";
    
    auto monitor = rebuntu::modules::cpu_memory_thermal_monitor::make_resource_monitor();
    assert(monitor != nullptr);
    assert(monitor->is_running() == false);
    
    std::cout << " [PASS]\n";
}

void test_monitor_lifecycle() {
    std::cout << "[TEST] Monitor lifecycle (start/stop)...";
    
    auto monitor = rebuntu::modules::cpu_memory_thermal_monitor::make_resource_monitor();
    
    // Start the monitor
    auto start_result = monitor->start();
    assert(start_result.status == rebuntu::core::SemanticStatus::kSuccess);
    assert(monitor->is_running() == true);
    
    // Stop the monitor
    auto stop_result = monitor->stop();
    assert(stop_result.status == rebuntu::core::SemanticStatus::kSuccess);
    assert(monitor->is_running() == false);
    
    std::cout << " [PASS]\n";
}

void test_assessment_returns_results() {
    std::cout << "[TEST] Assessment returns valid results...";
    
    auto monitor = rebuntu::modules::cpu_memory_thermal_monitor::make_resource_monitor();
    monitor->start();
    
    // Give it a moment
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    
    auto result = monitor->assess_resources();
    
    // Should have either success or partial (thermal might fail if no sensors)
    assert(result.outcome == rebuntu::modules::cpu_memory_thermal_monitor::ResourceMonitorResult::Outcome::kSuccess ||
           result.outcome == rebuntu::modules::cpu_memory_thermal_monitor::ResourceMonitorResult::Outcome::kPartial);
    
    // CPU assessment should be present
    assert(result.cpu_assessment.has_value());
    
    // Memory assessment should be present
    assert(result.memory_assessment.has_value());
    
    monitor->stop();
    
    std::cout << " [PASS]\n";
}

void test_metrics_tracking() {
    std::cout << "[TEST] Metrics tracking...";
    
    auto monitor = rebuntu::modules::cpu_memory_thermal_monitor::make_resource_monitor();
    monitor->start();
    
    // Get initial metrics
    auto initial_metrics = monitor->metrics();
    assert(initial_metrics.cpu_observations == 0);
    assert(initial_metrics.memory_observations == 0);
    assert(initial_metrics.thermal_observations == 0);
    
    // Perform assessments
    for (int i = 0; i < 3; i++) {
        monitor->assess_resources();
    }
    
    auto final_metrics = monitor->metrics();
    assert(final_metrics.cpu_observations >= 3);
    assert(final_metrics.memory_observations >= 3);
    // Thermal might fail if no sensors, so just check it was attempted
    assert(final_metrics.thermal_observations > 0 || 
           final_metrics.source_metrics.count("/sys/class/thermal") > 0);
    
    monitor->stop();
    
    std::cout << " [PASS]\n";
}

void test_config_can_be_modified() {
    std::cout << "[TEST] Config modification...";
    
    rebuntu::modules::cpu_memory_thermal_monitor::ResourceMonitorConfig config;
    config.cpu_utilization_warning_percent = 75.0;
    
    auto monitor = rebuntu::modules::cpu_memory_thermal_monitor::make_resource_monitor(config);
    
    const auto& modified_config = monitor->config();
    assert(modified_config.cpu_utilization_warning_percent == 75.0);
    
    std::cout << " [PASS]\n";
}

int main() {
    std::cout << "Phase 5.9 CPU / Memory / Thermal Monitor Unit Tests\n";
    std::cout << "====================================================\n\n";
    
    test_factory_creates_monitor();
    test_monitor_lifecycle();
    test_assessment_returns_results();
    test_metrics_tracking();
    test_config_can_be_modified();
    
    std::cout << "\nAll unit tests passed!\n";
    return 0;
}