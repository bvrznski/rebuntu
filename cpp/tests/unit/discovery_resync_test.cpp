// rebuntu::interfaces::discovery_resync unit tests (Phase 5.40)
//
// Basic compilation test for the discovery resynchronization interface.
// Tests verify that the interface compiles and basic functionality is available.

#include <interfaces/discovery_resync.hpp>
#include <iostream>

using namespace rebuntu::interfaces;

void test_discovery_provider_id_construction() {
    std::cout << "[TEST] DiscoveryProviderId construction...";
    
    // Test default constructor
    DiscoveryProviderId id1;
    if (id1.value != "") {
        throw std::runtime_error("Default ID should be empty");
    }
    
    // Test construction from string
    DiscoveryProviderId id2("test-provider");
    if (id2.value != "test-provider") {
        throw std::runtime_error("Constructed ID should match input");
    }
    
    std::cout << " PASSED" << std::endl;
}

void test_discovery_provider_id_equality() {
    std::cout << "[TEST] DiscoveryProviderId equality...";
    
    DiscoveryProviderId id1("provider");
    DiscoveryProviderId id2("provider");
    DiscoveryProviderId id3("other");
    
    if (!(id1 == id2)) {
        throw std::runtime_error("Equal IDs should be equal");
    }
    if (id1 == id3) {
        throw std::runtime_error("Different IDs should not be equal");
    }
    
    std::cout << " PASSED" << std::endl;
}

void test_make_discovery_resync_controller() {
    std::cout << "[TEST] Factory creates controller...";
    
    auto controller = make_discovery_resync_controller();
    if (!controller) {
        throw std::runtime_error("Factory should return non-null controller");
    }
    
    // Test that the interface can be called
    ResyncBudget budget;
    auto outcome = controller->configure(budget);
    if (!outcome.is_completed()) {
        throw std::runtime_error("Configure should complete successfully");
    }
    
    std::cout << " PASSED" << std::endl;
}

void test_start_stop_controller() {
    std::cout << "[TEST] Start/stop controller...";
    
    auto controller = make_discovery_resync_controller();
    
    auto start_outcome = controller->start();
    if (!start_outcome.is_completed()) {
        throw std::runtime_error("Start should complete successfully");
    }
    
    auto stop_outcome = controller->stop();
    if (!stop_outcome.is_completed()) {
        throw std::runtime_error("Stop should complete successfully");
    }
    
    std::cout << " PASSED" << std::endl;
}

void test_provider_state_default() {
    std::cout << "[TEST] Provider state default...";
    
    auto controller = make_discovery_resync_controller();
    
    DiscoveryProviderId id("test-provider");
    auto state = controller->provider_state(id);
    
    // Default state should be kInitializing
    if (state != DiscoveryProviderState::kInitializing) {
        throw std::runtime_error("Default provider state should be kInitializing");
    }
    
    std::cout << " PASSED" << std::endl;
}

void test_resync_request() {
    std::cout << "[TEST] ResyncRequest creation...";
    
    auto request = ResyncRequest::make("test-request-123");
    if (request.id != "test-request-123") {
        throw std::runtime_error("Request ID should match");
    }
    
    // Default trigger reason should be kManualRequest
    if (request.trigger_reason != ResyncTriggerReason::kManualRequest) {
        throw std::runtime_error("Default trigger reason should be kManualRequest");
    }
    
    std::cout << " PASSED" << std::endl;
}

void test_resync_result() {
    std::cout << "[TEST] ResyncResult default...";
    
    ResyncResult result;
    
    // Default status is kUnknown (value 3 from SemanticStatus enum)
    if (result.status != rebuntu::core::SemanticStatus::kUnknown) {
        throw std::runtime_error("Default result status should be kUnknown");
    }
    
    // Default elapsed time should be 0
    if (result.elapsed_ms.count() != 0) {
        throw std::runtime_error("Default elapsed time should be 0");
    }
    
    std::cout << " PASSED" << std::endl;
}

int main() {
    std::cout << "Running discovery_resync interface tests..." << std::endl;
    
    try {
        test_discovery_provider_id_construction();
        test_discovery_provider_id_equality();
        test_make_discovery_resync_controller();
        test_start_stop_controller();
        test_provider_state_default();
        test_resync_request();
        test_resync_result();
        
        std::cout << "All tests PASSED" << std::endl;
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "TEST FAILED: " << e.what() << std::endl;
        return 1;
    }
}