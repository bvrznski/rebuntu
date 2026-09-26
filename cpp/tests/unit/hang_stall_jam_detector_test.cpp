// rebuntu - Phase 5.11 Hang / Stall / Jam Detector Unit Tests
//
// Unit tests for the stall detection module.

#include "../src/modules/hang_stall_jam/stall_detector.hpp"
#include <iostream>
#include <thread>

using namespace rebuntu::modules::hang_stall_jam;

void test_factory_creates_detector() {
    std::cout << "[TEST] Factory creates detector instance...";
    
    auto detector = make_stall_detector();
    if (detector == nullptr) {
        std::cerr << " [FAIL - null pointer]\n";
        return;
    }
    if (detector->is_running()) {
        std::cerr << " [FAIL - should not be running initially]\n";
        return;
    }
    
    std::cout << " [PASS]\n";
}

void test_detector_lifecycle() {
    std::cout << "[TEST] Detector lifecycle (start/stop)...";
    
    auto detector = make_stall_detector();
    
    // Start the detector
    auto start_result = detector->start();
    if (!start_result.is_completed()) {
        std::cerr << " [FAIL - start did not complete]\n";
        return;
    }
    if (!detector->is_running()) {
        std::cerr << " [FAIL - should be running after start]\n";
        return;
    }
    
    // Stop the detector
    auto stop_result = detector->stop();
    if (!stop_result.is_success()) {
        std::cerr << " [FAIL - stop did not succeed]\n";
        return;
    }
    if (detector->is_running()) {
        std::cerr << " [FAIL - should not be running after stop]\n";
        return;
    }
    
    std::cout << " [PASS]\n";
}

void test_add_process_heartbeat() {
    std::cout << "[TEST] Add process heartbeat...";
    
    auto detector = make_stall_detector();
    detector->start();
    
    auto now_steady = std::chrono::steady_clock::now();
    auto now_system = std::chrono::system_clock::now();
    
    auto result = detector->add_process_heartbeat("1234", 1, now_steady, now_system);
    if (!result.is_completed()) {
        std::cerr << " [FAIL - add_process_heartbeat did not complete]\n";
        return;
    }
    
    // Verify the observation was recorded
    auto assessment = detector->assess_stall_state("1234", SubjectType::kProcess, now_system);
    if (assessment.subject_id != "1234") {
        std::cerr << " [FAIL - wrong subject in assessment]\n";
        return;
    }
    
    detector->stop();
    std::cout << " [PASS]\n";
}

void test_assess_normal_process() {
    std::cout << "[TEST] Assess normal process...";
    
    auto detector = make_stall_detector(StallDetectorConfig{
        .stall_suspicion_window = std::chrono::milliseconds(500),
        .corroborated_stall_window = std::chrono::milliseconds(1500)
    });
    detector->start();
    
    auto now_system = std::chrono::system_clock::now();
    
    // Add multiple heartbeats in quick succession
    for (int i = 0; i < 5; ++i) {
        auto now_steady = std::chrono::steady_clock::now();
        detector->add_process_heartbeat("5678", i + 1, now_steady, now_system);
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
    
    // Assessment should show normal state (progress is occurring)
    auto assessment = detector->assess_stall_state("5678", SubjectType::kProcess, now_system);
    if (assessment.state != StallState::kNormal) {
        std::cerr << " [FAIL - expected kNormal but got: " 
                  << to_string(assessment.state) << "]\n";
        return;
    }
    
    detector->stop();
    std::cout << " [PASS]\n";
}

void test_metrics_tracking() {
    std::cout << "[TEST] Metrics tracking...";
    
    auto detector = make_stall_detector();
    detector->start();
    
    // Check initial metrics
    auto metrics = detector->metrics();
    if (metrics.assessments_performed != 0) {
        std::cerr << " [FAIL - initial assessments should be 0]\n";
        return;
    }
    if (metrics.observations_received != 0) {
        std::cerr << " [FAIL - initial observations should be 0]\n";
        return;
    }
    
    // Add some observations
    auto now_system = std::chrono::system_clock::now();
    for (int i = 0; i < 3; ++i) {
        auto now_steady = std::chrono::steady_clock::now();
        detector->add_process_heartbeat("999" + std::to_string(i), 
                                        i + 1, now_steady, now_system);
    }
    
    metrics = detector->metrics();
    if (metrics.observations_received != 3) {
        std::cerr << " [FAIL - expected 3 observations, got: " 
                  << metrics.observations_received << "]\n";
        return;
    }
    
    detector->stop();
    std::cout << " [PASS]\n";
}

void test_service_progress() {
    std::cout << "[TEST] Service progress monitoring...";
    
    auto detector = make_stall_detector();
    detector->start();
    
    auto now_steady = std::chrono::steady_clock::now();
    auto now_system = std::chrono::system_clock::now();
    
    auto result = detector->add_service_progress(
        "test-service.service", EvidenceType::kHeartbeat, 1, now_steady, now_system);
    
    if (!result.is_completed()) {
        std::cerr << " [FAIL - add_service_progress did not complete]\n";
        return;
    }
    
    auto assessment = detector->assess_stall_state(
        "test-service.service", SubjectType::kService, now_system);
    if (assessment.subject_id != "test-service.service") {
        std::cerr << " [FAIL - wrong subject in assessment]\n";
        return;
    }
    
    detector->stop();
    std::cout << " [PASS]\n";
}

void test_get_subject_state() {
    std::cout << "[TEST] Get subject stall state...";
    
    auto detector = make_stall_detector();
    detector->start();
    
    // New subject should be normal (no evidence yet)
    auto state = detector->get_subject_stall_state("new-123", SubjectType::kProcess);
    if (state != StallState::kNormal) {
        std::cerr << " [FAIL - new subject should be kNormal, got: " 
                  << to_string(state) << "]\n";
        return;
    }
    
    detector->stop();
    std::cout << " [PASS]\n";
}

int main() {
    std::cout << "\n=== Hang / Stall / Jam Detector Tests ===\n\n";
    
    test_factory_creates_detector();
    test_detector_lifecycle();
    test_add_process_heartbeat();
    test_assess_normal_process();
    test_metrics_tracking();
    test_service_progress();
    test_get_subject_state();
    
    std::cout << "\n=== All Tests Complete ===\n\n";
    return 0;
}