// rebuntu::semantic::service - Phase 3.3 Native Semantic Service tests
//
// Tests for:
//   - Lifecycle state transitions (unavailable -> activating -> ready)
//   - Readiness state management
//   - Health state tracking
//   - Mock service controller operations
//   - Timeout and cancellation support

#include <system/semantic/service.hpp>
#include <cassert>
#include <iostream>
#include <string>
#include <thread>
#include <chrono>

void test_enum_to_string() {
    using namespace rebuntu::semantic;
    
    // LifecycleState
    assert(to_string(LifecycleState::kUnavailable) == "unavailable");
    assert(to_string(LifecycleState::kActivating) == "activating");
    assert(to_string(LifecycleState::kReady) == "ready");
    assert(to_string(LifecycleState::kDraining) == "draining");
    assert(to_string(LifecycleState::kTerminating) == "terminating");
    
    // ReadinessState
    assert(to_string(ReadinessState::kNotReady) == "not_ready");
    assert(to_string(ReadinessState::kReady) == "ready");
    assert(to_string(ReadinessState::kDraining) == "draining");
    
    // HealthState
    assert(to_string(HealthState::kUnknown) == "unknown");
    assert(to_string(HealthState::kHealthy) == "healthy");
    assert(to_string(HealthState::kDegraded) == "degraded");
    assert(to_string(HealthState::kUnhealthy) == "unhealthy");
}

void test_service_state_defaults() {
    using namespace rebuntu::semantic;
    
    ServiceState state;
    assert(state.lifecycle == LifecycleState::kUnavailable);
    assert(state.readiness == ReadinessState::kNotReady);
    assert(state.health == HealthState::kUnknown);
    assert(!state.state_detail.has_value());
}

void test_service_metrics_defaults() {
    using namespace rebuntu::semantic;
    
    ServiceMetrics metrics;
    assert(metrics.total_requests == 0);
    assert(metrics.successful_requests == 0);
    assert(metrics.failed_requests == 0);
    assert(metrics.timed_out_requests == 0);
}

void test_semantic_request_defaults() {
    using namespace rebuntu::semantic;
    
    SemanticRequest req;
    assert(req.type == SemanticRequestType::kClassify);
    assert(req.input_text.empty());
    assert(!req.query_context.has_value());
    assert(req.timeout == std::chrono::seconds(30));
}

void test_service_result_constructors() {
    using namespace rebuntu::semantic;
    
    Evidence ev{"test", "source", {}, "value"};
    
    // Success
    ServiceResult r1 = ServiceResult::success("output", ev);
    assert(r1.succeeded == true);
    assert(r1.output.has_value());
    assert(!r1.evidence.empty());
    
    // Failure
    ServiceResult r2 = ServiceResult::failure("error", ev);
    assert(r2.succeeded == false);
    assert(r2.error_message.has_value());
    
    // Timeout
    ServiceResult r3 = ServiceResult::timeout();
    assert(r3.succeeded == false);
    assert(r3.error_message.has_value());
    assert(r3.error_message.value() == "semantic request timed out");
}

void test_mock_controller_lifecycle() {
    using namespace rebuntu::semantic;
    
    auto controller = make_mock_controller();
    
    // Initial state
    assert(controller->lifecycle_state() == LifecycleState::kUnavailable);
    assert(controller->readiness_state() == ReadinessState::kNotReady);
    
    // Start the service
    bool started = controller->start();
    assert(started == true);
    
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    
    // After start - should be ready
    assert(controller->lifecycle_state() == LifecycleState::kReady);
    assert(controller->readiness_state() == ReadinessState::kReady);
    
    // Get full state
    ServiceState state = controller->get_state();
    assert(state.lifecycle == LifecycleState::kReady);
    assert(state.readiness == ReadinessState::kReady);
    
    // State detail should be available
    auto detail = controller->state_detail();
    assert(detail.has_value());
    assert(!detail.value().empty());
    
    // Stop the service
    bool stopped = controller->stop();
    assert(stopped == true);
    
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    
    // After stop - should be unavailable
    assert(controller->lifecycle_state() == LifecycleState::kUnavailable);
    assert(controller->readiness_state() == ReadinessState::kNotReady);
}

void test_mock_controller_restart() {
    using namespace rebuntu::semantic;
    
    auto controller = make_mock_controller();
    
    // Start
    controller->start();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    
    // Restart
    bool restarted = controller->restart();
    assert(restarted == true);
    
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    
    // After restart - should be ready again
    assert(controller->lifecycle_state() == LifecycleState::kReady);
    assert(controller->readiness_state() == ReadinessState::kReady);
}

void test_mock_controller_health() {
    using namespace rebuntu::semantic;
    
    auto controller = make_mock_controller();
    
    // Initially unknown health
    assert(controller->health_state() == HealthState::kUnknown);
    
    // Start service
    controller->start();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    
    // After start should be healthy
    assert(controller->health_state() == HealthState::kHealthy);
}

void test_mock_controller_cancel_operations() {
    using namespace rebuntu::semantic;
    
    auto controller = make_mock_controller();
    
    // Cancel operations (should work even when not started)
    controller->cancel_all_operations();
}

void test_metrics_tracking() {
    using namespace rebuntu::semantic;
    
    auto controller = make_mock_controller();
    
    ServiceMetrics initial_metrics = controller->metrics();
    size_t initial_total = initial_metrics.total_requests;
    
    controller->start();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    
    // Make a request and check metrics are updated
    ServiceResult r = controller->classify("test");
    assert(r.succeeded == true);
    
    ServiceMetrics after_metrics = controller->metrics();
    assert(after_metrics.total_requests > initial_total);
}

int main(int argc, char** argv) {
    (void)argc;
    (void)argv;
    
    std::cout << "Running Phase 3.3 Native Semantic Service tests...\n";
    
    test_enum_to_string();
    std::cout << "  test_enum_to_string... PASS\n";
    
    test_service_state_defaults();
    std::cout << "  test_service_state_defaults... PASS\n";
    
    test_service_metrics_defaults();
    std::cout << "  test_service_metrics_defaults... PASS\n";
    
    test_semantic_request_defaults();
    std::cout << "  test_semantic_request_defaults... PASS\n";
    
    test_service_result_constructors();
    std::cout << "  test_service_result_constructors... PASS\n";
    
    test_mock_controller_lifecycle();
    std::cout << "  test_mock_controller_lifecycle... PASS\n";
    
    test_mock_controller_restart();
    std::cout << "  test_mock_controller_restart... PASS\n";
    
    test_mock_controller_health();
    std::cout << "  test_mock_controller_health... PASS\n";
    
    test_mock_controller_cancel_operations();
    std::cout << "  test_mock_controller_cancel_operations... PASS\n";
    
    test_metrics_tracking();
    std::cout << "  test_metrics_tracking... PASS\n";
    
    std::cout << "All Phase 3.3 service tests PASSED!\n";
    return 0;
}