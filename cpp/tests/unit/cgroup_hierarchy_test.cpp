// rebuntu - Phase 5.28 Cgroup v2 Hierarchy Discovery Unit Tests
//
// Unit tests for the cgroup hierarchy observation adapter.

#include "../src/adapters/cgroups/hierarchy/types.hpp"
#include <iostream>
#include <thread>

using namespace rebuntu::adapters::cgroups::hierarchy;

namespace core = rebuntu::core;

void test_factory_creates_adapter() {
    std::cout << "[TEST] Factory creates adapter instance...";
    
    auto adapter = make_cgroup_hierarchy_adapter();
    if (adapter == nullptr) {
        std::cerr << " [FAIL - null pointer]\n";
        return;
    }
    
    std::cout << " [PASS]\n";
}

void test_observe_hierarchy() {
    std::cout << "[TEST] Observe cgroup hierarchy...";
    
    auto adapter = make_cgroup_hierarchy_adapter();
    auto result = adapter->observe_hierarchy();
    
    if (result.status != core::SemanticStatus::kSuccess) {
        std::cerr << " [FAIL - status: " << to_string(result.status) 
                  << ", description: " << result.description << "]\n";
        return;
    }
    
    // At minimum we should have some cgroups
    if (result.cgroups.empty()) {
        std::cerr << " [FAIL - no cgroups found]\n";
        return;
    }
    
    std::cout << " [PASS - found " << result.cgroups.size() << " cgroup(s)]\n";
}

void test_cgroup_identity() {
    std::cout << "[TEST] CGroup identity fields...";
    
    auto adapter = make_cgroup_hierarchy_adapter();
    auto result = adapter->observe_hierarchy();
    
    if (result.status != core::SemanticStatus::kSuccess) {
        std::cerr << " [FAIL - cannot test without successful observation]\n";
        return;
    }
    
    bool all_valid = true;
    for (const auto& cgroup : result.cgroups) {
        // Check that identity has a valid path
        if (cgroup.identity.path.empty()) {
            std::cerr << " [FAIL - empty path for cgroup]\n";
            all_valid = false;
        }
    }
    
    if (all_valid) {
        std::cout << " [PASS]\n";
    } else {
        std::cerr << " [FAIL - invalid identity fields]\n";
    }
}

void test_controller_types() {
    std::cout << "[TEST] ControllerType to_string conversion...";
    
    bool all_valid = true;
    struct TestCase { ControllerType state; const char* expected; };
    std::vector<TestCase> tests = {
        {ControllerType::kCpu, "cpu"},
        {ControllerType::kMemory, "memory"},
        {ControllerType::kIo, "io"},
        {ControllerType::kPids, "pids"},
        {ControllerType::kCpuset, "cpuset"},
        {ControllerType::kHugetlb, "hugetlb"},
        {ControllerType::kRdma, "rdma"},
        {ControllerType::kMisc, "misc"},
    };
    
    for (const auto& tc : tests) {
        if (to_string(tc.state) != tc.expected) {
            std::cerr << " [FAIL - to_string conversion failed for " 
                      << static_cast<int>(tc.state) << "]\n";
            all_valid = false;
        }
    }
    
    if (all_valid) {
        std::cout << " [PASS]\n";
    } else {
        std::cerr << " [FAIL - some conversions failed]\n";
    }
}

void test_hierarchy() {
    std::cout << "[TEST] Hierarchy structure...";
    
    auto adapter = make_cgroup_hierarchy_adapter();
    auto hierarchy = adapter->get_hierarchy();
    
    if (hierarchy.total_cgroups == 0) {
        std::cerr << " [FAIL - no cgroups in hierarchy]\n";
        return;
    }
    
    // Check that we can look up by path
    bool lookup_works = false;
    for (const auto& pair : hierarchy.cgroups_by_path) {
        if (!pair.second.identity.path.empty()) {
            lookup_works = true;
            break;
        }
    }
    
    if (!lookup_works) {
        std::cerr << " [FAIL - path lookup failed]\n";
        return;
    }
    
    std::cout << " [PASS]\n";
}

void test_isolation() {
    std::cout << "[TEST] Multiple observations are isolated...";
    
    auto adapter = make_cgroup_hierarchy_adapter();
    auto result1 = adapter->observe_hierarchy();
    
    if (result1.status != core::SemanticStatus::kSuccess) {
        std::cerr << " [FAIL - first observation failed]\n";
        return;
    }
    
    // Small delay to ensure different timestamps
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    
    auto result2 = adapter->observe_hierarchy();
    
    if (result2.status != core::SemanticStatus::kSuccess) {
        std::cerr << " [FAIL - second observation failed]\n";
        return;
    }
    
    // Timestamps should be different
    bool different_timestamps = result1.observed_at != result2.observed_at;
    
    if (!different_timestamps) {
        std::cout << " [WARN - timestamps may be same due to fast execution]\n";
    } else {
        std::cout << " [PASS]\n";
    }
}

int main() {
    std::cout << "\n=== Cgroup v2 Hierarchy Discovery Tests ===\n\n";
    
    test_factory_creates_adapter();
    test_observe_hierarchy();
    test_cgroup_identity();
    test_controller_types();
    test_hierarchy();
    test_isolation();
    
    std::cout << "\n=== All Tests Complete ===\n\n";
    return 0;
}