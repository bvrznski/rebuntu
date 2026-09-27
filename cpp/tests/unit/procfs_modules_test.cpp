// rebuntu - Phase 5.32 Kernel Module Discovery Unit Tests
//
// Unit tests for the procfs module discovery adapter.

#include "../src/adapters/procfs/modules/types.hpp"
#include <iostream>
#include <thread>

using namespace rebuntu::adapters::procfs::modules;

namespace core = rebuntu::core;

void test_factory_creates_adapter() {
    std::cout << "[TEST] Factory creates adapter instance...";
    
    auto adapter = make_procfs_modules_adapter();
    if (adapter == nullptr) {
        std::cerr << " [FAIL - null pointer]\n";
        return;
    }
    
    std::cout << " [PASS]\n";
}

void test_observe_modules() {
    std::cout << "[TEST] Observe loaded kernel modules...";
    
    auto adapter = make_procfs_modules_adapter();
    auto result = adapter->observe_modules();
    
    if (result.status != core::SemanticStatus::kSuccess) {
        std::cerr << " [FAIL - status: " << to_string(result.status) 
                  << ", description: " << result.description << "]\n";
        return;
    }
    
    // Should observe at least some kernel modules
    if (result.modules.empty()) {
        std::cerr << " [FAIL - no modules found]\n";
        return;
    }
    
    std::cout << " [PASS - found " << result.modules.size() << " module(s)]\n";
}

void test_module_identity() {
    std::cout << "[TEST] Module identity fields...";
    
    auto adapter = make_procfs_modules_adapter();
    auto result = adapter->observe_modules();
    
    if (result.modules.empty()) {
        std::cerr << " [FAIL - no modules to test]\n";
        return;
    }
    
    bool all_valid = true;
    for (const auto& module : result.modules) {
        // Module name should not be empty
        if (module.identity.name.empty()) {
            std::cerr << " [FAIL - empty module name]\n";
            all_valid = false;
        }
        
        // Size should be non-negative
        if (module.size_bytes == 0) {
            std::cerr << " [WARN - zero size for " << module.identity.name << "]\n";
        }
    }
    
    if (all_valid) {
        std::cout << " [PASS]\n";
    } else {
        std::cerr << " [FAIL - invalid identity fields]\n";
    }
}

void test_topology() {
    std::cout << "[TEST] Topology structure...";
    
    auto adapter = make_procfs_modules_adapter();
    auto topology = adapter->get_topology();
    
    if (topology.total_modules == 0) {
        std::cerr << " [FAIL - no modules in topology]\n";
        return;
    }
    
    // Check that we can look up modules by name
    bool lookup_works = false;
    for (const auto& pair : topology.modules_by_name) {
        auto obs = adapter->resolve_module(pair.first);
        if (obs.has_value()) {
            lookup_works = true;
            break;
        }
    }
    
    if (!lookup_works) {
        std::cerr << " [FAIL - resolve_module failed]\n";
        return;
    }
    
    std::cout << " [PASS]\n";
}

void test_state_enum() {
    std::cout << "[TEST] ModuleState to_string conversion...";
    
    bool all_valid = true;
    struct TestCase { ModuleState state; const char* expected; };
    std::vector<TestCase> tests = {
        {ModuleState::kLoaded, "loaded"},
        {ModuleState::kActive, "active"},
        {ModuleState::kReferenced, "referenced"},
        {ModuleState::kError, "error"},
    };
    
    for (const auto& tc : tests) {
        if (to_string(tc.state) != tc.expected) {
            std::cerr << " [FAIL - to_string conversion failed]\n";
            all_valid = false;
        }
    }
    
    if (all_valid) {
        std::cout << " [PASS]\n";
    } else {
        std::cerr << " [FAIL - some conversions failed]\n";
    }
}

void test_isolation() {
    std::cout << "[TEST] Multiple observations are isolated...";
    
    auto adapter = make_procfs_modules_adapter();
    auto result1 = adapter->observe_modules();
    
    // Small delay to ensure different timestamps
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    
    auto result2 = adapter->observe_modules();
    
    if (result1.observed_at == result2.observed_at) {
        std::cerr << " [FAIL - observations should have different timestamps]\n";
        return;
    }
    
    std::cout << " [PASS]\n";
}

int main() {
    std::cout << "\n=== Kernel Module Discovery Tests ===\n\n";
    
    test_factory_creates_adapter();
    test_observe_modules();
    test_module_identity();
    test_topology();
    test_state_enum();
    test_isolation();
    
    std::cout << "\n=== All Tests Complete ===\n\n";
    return 0;
}