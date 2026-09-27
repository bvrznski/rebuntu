// rebuntu::interfaces::inventory_index unit tests (Phase 5.45)
//
// Basic compilation test for the inventory indexing interface.
// Tests verify that the interface compiles and basic functionality is available.

#include <interfaces/inventory_index.hpp>
#include <iostream>

using namespace rebuntu::interfaces;

void test_entity_id_construction() {
    std::cout << "[TEST] EntityId construction...";
    
    // Test default constructor
    EntityId id1;
    if (id1.value != "") {
        throw std::runtime_error("Default ID should be empty");
    }
    
    // Test construction from string
    EntityId id2("test-entity");
    if (id2.value != "test-entity") {
        throw std::runtime_error("Constructed ID should match input");
    }
    
    std::cout << " PASSED" << std::endl;
}

void test_entity_id_equality() {
    std::cout << "[TEST] EntityId equality...";
    
    EntityId id1("entity");
    EntityId id2("entity");
    EntityId id3("other");
    
    if (!(id1 == id2)) {
        throw std::runtime_error("Equal IDs should be equal");
    }
    if (id1 == id3) {
        throw std::runtime_error("Different IDs should not be equal");
    }
    
    std::cout << " PASSED" << std::endl;
}

void test_make_inventory_indexer() {
    std::cout << "[TEST] Factory creates indexer...";
    
    auto indexer = make_inventory_indexer();
    if (!indexer) {
        throw std::runtime_error("Factory should return non-null indexer");
    }
    
    // Test that the interface can be called
    auto outcome = indexer->configure(std::chrono::milliseconds(60000), 10000);
    if (!outcome.is_completed()) {
        throw std::runtime_error("Configure should complete successfully");
    }
    
    std::cout << " PASSED" << std::endl;
}

void test_start_stop_indexer() {
    std::cout << "[TEST] Start/stop indexer...";
    
    auto indexer = make_inventory_indexer();
    
    auto start_outcome = indexer->start();
    if (!start_outcome.is_completed()) {
        throw std::runtime_error("Start should complete successfully");
    }
    
    auto stop_outcome = indexer->stop();
    if (!stop_outcome.is_completed()) {
        throw std::runtime_error("Stop should complete successfully");
    }
    
    std::cout << " PASSED" << std::endl;
}

void test_index_state_default() {
    std::cout << "[TEST] Index state default...";
    
    auto indexer = make_inventory_indexer();
    
    // Start first
    indexer->start();
    
    IndexState state = indexer->get_index_state(IndexKind::kByName);
    
    // Default state should be kInitializing (index hasn't been built yet)
    if (state != IndexState::kInitializing) {
        throw std::runtime_error("Default index state should be kInitializing");
    }
    
    std::cout << " PASSED" << std::endl;
}

void test_build_request() {
    std::cout << "[TEST] BuildRequest creation...";
    
    auto request = IndexBuildRequest::make("test-build-123");
    if (request.id != "test-build-123") {
        throw std::runtime_error("Request ID should match");
    }
    
    // Default max_entries should be 100000
    if (request.max_entries != 100000) {
        throw std::runtime_error("Default max_entries should be 100000");
    }
    
    std::cout << " PASSED" << std::endl;
}

void test_index_kind_to_string() {
    std::cout << "[TEST] IndexKind to_string...";
    
    if (to_string(IndexKind::kByName) != "by-name") {
        throw std::runtime_error("kByName should map to 'by-name'");
    }
    if (to_string(IndexKind::kByType) != "by-type") {
        throw std::runtime_error("kByType should map to 'by-type'");
    }
    
    std::cout << " PASSED" << std::endl;
}

int main() {
    std::cout << "Running inventory_index interface tests..." << std::endl;
    
    try {
        test_entity_id_construction();
        test_entity_id_equality();
        test_make_inventory_indexer();
        test_start_stop_indexer();
        test_index_state_default();
        test_build_request();
        test_index_kind_to_string();
        
        std::cout << "All tests PASSED" << std::endl;
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "TEST FAILED: " << e.what() << std::endl;
        return 1;
    }
}