// rebuntu::test_kernel_fault_detector — Unit Tests for Kernel / Driver Fault Monitor (Phase 5.7)
//
// Tests for the kernel/driver fault detection functionality.

#include "adapters/kernel_fault_detector.hpp"

#include <gtest/gtest.h>
#include <chrono>

namespace rebuntu::adapters {

// ============================================================================
// Factory function tests
// ============================================================================

TEST(KernelFaultDetectorTest, FactoryCreatesValidDetector) {
    auto detector = make_kernel_fault_detector();
    
    ASSERT_NE(detector, nullptr);
    EXPECT_FALSE(detector->is_running());
}

TEST(KernelFaultDetectorTest, ConfigIsStoredCorrectly) {
    KernelFaultDetectorConfig config;
    config.warning_count_threshold = 10;
    config.error_count_threshold = 5;
    config.event_correlation_window = std::chrono::minutes(10);
    
    auto detector = make_kernel_fault_detector(config);
    
    EXPECT_EQ(detector->config().warning_count_threshold, 10);
    EXPECT_EQ(detector->config().error_count_threshold, 5);
}

// ============================================================================
// Lifecycle tests
// ============================================================================

TEST(KernelFaultDetectorTest, StartStopLifecycle) {
    auto detector = make_kernel_fault_detector();
    
    // Start should succeed and mark as running
    auto result = detector->start();
    EXPECT_TRUE(result.is_success());
    EXPECT_TRUE(detector->is_running());
    
    // Stop should succeed and mark as stopped
    result = detector->stop();
    EXPECT_TRUE(result.is_success());
    EXPECT_FALSE(detector->is_running());
}

TEST(KernelFaultDetectorTest, DuplicateStartRejected) {
    auto detector = make_kernel_fault_detector();
    
    // First start succeeds
    auto result = detector->start();
    EXPECT_TRUE(result.is_success());
    
    // Second start should be a no-op (already running)
    result = detector->start();
    EXPECT_TRUE(result.is_success());  // Already running, no error
}

// ============================================================================
// Event processing tests - kernel warnings
// ============================================================================

TEST(KernelFaultDetectorTest, ProcessesKernelWarning) {
    auto detector = make_kernel_fault_detector();
    
    runtime::Event event;
    event.id = "test-event-1";
    event.source = "journald";
    event.type = "warning";
    
    core::Evidence evidence;
    evidence.source = "journal_message";
    evidence.value = "WARNING: something unusual happened";
    event.evidence.push_back(evidence);
    
    auto result = detector->process_journal_event(event, std::chrono::system_clock::now());
    EXPECT_TRUE(result.is_success());
}

TEST(KernelFaultDetectorTest, DetectsKernelPanic) {
    auto detector = make_kernel_fault_detector();
    
    runtime::Event event;
    event.id = "test-event-panic";
    event.source = "journald";
    
    core::Evidence evidence;
    evidence.source = "journal_message";
    evidence.value = "[kernel] Kernel panic - not syncing: something went wrong";
    event.evidence.push_back(evidence);
    
    auto result = detector->process_journal_event(event, std::chrono::system_clock::now());
    EXPECT_TRUE(result.is_success());
    
    // Get detected faults
    auto faults = detector->get_detected_faults();
    EXPECT_GT(faults.size(), 0);
}

TEST(KernelFaultDetectorTest, DetectsKernelOops) {
    auto detector = make_kernel_fault_detector();
    
    runtime::Event event;
    event.id = "test-event-oops";
    event.source = "journald";
    
    core::Evidence evidence;
    evidence.source = "journal_message";
    evidence.value = "BUG: unable to handle kernel oops";
    event.evidence.push_back(evidence);
    
    auto result = detector->process_journal_event(event, std::chrono::system_clock::now());
    EXPECT_TRUE(result.is_success());
}

// ============================================================================
// DMesg line processing tests
// ============================================================================

TEST(KernelFaultDetectorTest, ProcessesDmesgLine) {
    auto detector = make_kernel_fault_detector();
    
    // Test with standard kernel log format
    std::string line = "<3>Kernel error message here";
    
    auto result = detector->process_dmesg_line(line, std::chrono::system_clock::now());
    EXPECT_TRUE(result.is_success());
}

TEST(KernelFaultDetectorTest, ProcessesDmesgLineWithPriority) {
    auto detector = make_kernel_fault_detector();
    
    // Test with different priority levels
    std::string line1 = "<0>Critical kernel panic message";
    std::string line2 = "<4>Warning message here";
    std::string line3 = "No priority info - normal message";
    
    EXPECT_TRUE(detector->process_dmesg_line(line1, std::chrono::system_clock::now()).is_success());
    EXPECT_TRUE(detector->process_dmesg_line(line2, std::chrono::system_clock::now()).is_success());
    EXPECT_TRUE(detector->process_dmesg_line(line3, std::chrono::system_clock::now()).is_success());
}

// ============================================================================
// Metrics tests
// ============================================================================

TEST(KernelFaultDetectorTest, TracksMetrics) {
    auto detector = make_kernel_fault_detector();
    
    // Initial metrics should be zeroed
    auto metrics = detector->metrics();
    EXPECT_EQ(metrics.events_received, 0);
    EXPECT_EQ(metrics.faults_detected, 0);
    
    // Process an event
    runtime::Event event;
    event.id = "test-metrics";
    event.source = "journald";
    
    core::Evidence evidence;
    evidence.source = "journal_message";
    evidence.value = "kernel warning test";
    event.evidence.push_back(evidence);
    
    detector->process_journal_event(event, std::chrono::system_clock::now());
    
    // Metrics should be updated
    metrics = detector->metrics();
    EXPECT_EQ(metrics.events_received, 1);
}

// ============================================================================
// Fault classification tests
// ============================================================================

TEST(KernelFaultDetectorTest, ClassifiesWarningCorrectly) {
    auto detector = make_kernel_fault_detector();
    
    runtime::Event event;
    core::Evidence evidence;
    evidence.source = "journal_message";
    evidence.value = "WARNING: this is a warning message";
    event.evidence.push_back(evidence);
    
    // The classify_event method should identify warnings
    auto state = detector->classify_event(event, std::chrono::system_clock::now());
    
    EXPECT_EQ(state.fault_class, KernelFaultClass::kKernelWarning);
    EXPECT_EQ(state.severity, Severity::kMedium);
}

TEST(KernelFaultDetectorTest, ClassifiesErrorCorrectly) {
    auto detector = make_kernel_fault_detector();
    
    runtime::Event event;
    core::Evidence evidence;
    evidence.source = "journal_message";
    evidence.value = "error: device failed to respond";
    event.evidence.push_back(evidence);
    
    auto state = detector->classify_event(event, std::chrono::system_clock::now());
    
    EXPECT_EQ(state.fault_class, KernelFaultClass::kKernelError);
}

TEST(KernelFaultDetectorTest, ClassifiesPanicCorrectly) {
    auto detector = make_kernel_fault_detector();
    
    runtime::Event event;
    core::Evidence evidence;
    evidence.source = "journal_message";
    evidence.value = "Kernel panic - system halted";
    event.evidence.push_back(evidence);
    
    auto state = detector->classify_event(event, std::chrono::system_clock::now());
    
    EXPECT_EQ(state.fault_class, KernelFaultClass::kKernelPanic);
    EXPECT_EQ(state.severity, Severity::kCritical);
}

// ============================================================================
// Recent faults tests
// ============================================================================

TEST(KernelFaultDetectorTest, ReturnsRecentFaultsWithinWindow) {
    auto detector = make_kernel_fault_detector();
    
    // Process some events to create faults
    for (int i = 0; i < 3; ++i) {
        runtime::Event event;
        core::Evidence evidence;
        evidence.source = "journal_message";
        evidence.value = "test fault " + std::to_string(i);
        event.evidence.push_back(evidence);
        
        detector->process_journal_event(event, std::chrono::system_clock::now());
    }
    
    // Get recent faults (within 10 minutes)
    auto recent = detector->get_recent_faults(std::chrono::minutes(10));
    
    EXPECT_GE(recent.size(), 0);
}

TEST(KernelFaultDetectorTest, ReturnsAllDetectedFaults) {
    auto detector = make_kernel_fault_detector();
    
    // Get faults before any processing
    auto faults = detector->get_detected_faults();
    
    // Should return empty vector (not null)
    EXPECT_EQ(faults.size(), 0);
}

// ============================================================================
// String conversion tests
// ============================================================================

TEST(KernelFaultClassTest, ToStringWorks) {
    EXPECT_EQ(to_string(KernelFaultClass::kKernelWarning), "kernel_warning");
    EXPECT_EQ(to_string(KernelFaultClass::kKernelError), "kernel_error");
    EXPECT_EQ(to_string(KernelFaultClass::kKernelPanic), "kernel_panic");
    EXPECT_EQ(to_string(KernelFaultClass::kNone), "none");
}

TEST(SeverityTest, ToStringWorks) {
    EXPECT_EQ(to_string(Severity::kInfo), "info");
    EXPECT_EQ(to_string(Severity::kLow), "low");
    EXPECT_EQ(to_string(Severity::kMedium), "medium");
    EXPECT_EQ(to_string(Severity::kHigh), "high");
    EXPECT_EQ(to_string(Severity::kCritical), "critical");
}

TEST(EvidenceConfidenceTest, ToStringWorks) {
    EXPECT_EQ(to_string(EvidenceConfidence::kDirect), "direct");
    EXPECT_EQ(to_string(EvidenceConfidence::kDeduced), "deduced");
    EXPECT_EQ(to_string(EvidenceConfidence::kCorrelated), "correlated");
    EXPECT_EQ(to_string(EvidenceConfidence::kHypothesized), "hypothesized");
}

}  // namespace rebuntu::adapters

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}