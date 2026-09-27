// rebuntu - Phase 5.21 Network Interface Discovery Unit Tests
//
// Unit tests for the netlink link discovery adapter.

#include "../src/adapters/netlink/link/types.hpp"
#include <iostream>
#include <thread>

using namespace rebuntu::adapters::netlink::link;

namespace core = rebuntu::core;

void test_factory_creates_adapter() {
    std::cout << "[TEST] Factory creates adapter instance...";
    
    auto adapter = make_netlink_link_adapter();
    if (adapter == nullptr) {
        std::cerr << " [FAIL - null pointer]\n";
        return;
    }
    
    std::cout << " [PASS]\n";
}

void test_observe_interfaces() {
    std::cout << "[TEST] Observe network interfaces...";
    
    auto adapter = make_netlink_link_adapter();
    auto result = adapter->observe_interfaces();
    
    if (result.status != core::SemanticStatus::kSuccess) {
        std::cerr << " [FAIL - status: " << to_string(result.status) 
                  << ", description: " << result.description << "]\n";
        return;
    }
    
    // At minimum we should have the loopback interface
    if (result.interfaces.empty()) {
        std::cerr << " [FAIL - no interfaces found]\n";
        return;
    }
    
    std::cout << " [PASS - found " << result.interfaces.size() << " interface(s)]\n";
}

void test_interface_identity() {
    std::cout << "[TEST] Interface identity fields...";
    
    auto adapter = make_netlink_link_adapter();
    auto result = adapter->observe_interfaces();
    
    if (result.interfaces.empty()) {
        std::cerr << " [FAIL - no interfaces to test]\n";
        return;
    }
    
    bool all_valid = true;
    for (const auto& iface : result.interfaces) {
        // Check that identity has valid ifindex
        if (iface.identity.ifindex <= 0) {
            std::cerr << " [FAIL - invalid ifindex for " << iface.name << "]\n";
            all_valid = false;
        }
        
        // MAC address should be empty in this implementation (no netlink RTM_GETADDR)
        // or valid format if present
    }
    
    if (all_valid) {
        std::cout << " [PASS]\n";
    } else {
        std::cerr << " [FAIL - invalid identity fields]\n";
    }
}

void test_topology() {
    std::cout << "[TEST] Topology structure...";
    
    auto adapter = make_netlink_link_adapter();
    auto topology = adapter->get_topology();
    
    if (topology.total_interfaces == 0) {
        std::cerr << " [FAIL - no interfaces in topology]\n";
        return;
    }
    
    // Check that we can look up by ifindex
    bool lookup_works = false;
    for (const auto& pair : topology.interfaces_by_index) {
        auto obs = adapter->resolve_by_index(pair.first);
        if (obs.has_value()) {
            lookup_works = true;
            break;
        }
    }
    
    if (!lookup_works) {
        std::cerr << " [FAIL - resolve_by_index failed]\n";
        return;
    }
    
    std::cout << " [PASS]\n";
}

void test_link_state_enum() {
    std::cout << "[TEST] LinkState to_string conversion...";
    
    bool all_valid = true;
    struct TestCase { LinkState state; const char* expected; };
    std::vector<TestCase> tests = {
        {LinkState::kUnknown, "unknown"},
        {LinkState::kNotPresent, "not-present"},
        {LinkState::kDown, "down"},
        {LinkState::kLowerLayerDown, "lower-layer-down"},
        {LinkState::kDormant, "dormant"},
        {LinkState::kUp, "up"},
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

void test_address_family_enum() {
    std::cout << "[TEST] AddressFamily to_string conversion...";
    
    bool all_valid = true;
    struct TestCase { AddressFamily family; const char* expected; };
    std::vector<TestCase> tests = {
        {AddressFamily::kUnspecified, "unspecified"},
        {AddressFamily::kInet, "inet"},
        {AddressFamily::kInet6, "inet6"},
    };
    
    for (const auto& tc : tests) {
        if (to_string(tc.family) != tc.expected) {
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
    
    auto adapter = make_netlink_link_adapter();
    auto result1 = adapter->observe_interfaces();
    
    // Small delay to ensure different timestamps
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    
    auto result2 = adapter->observe_interfaces();
    
    if (result1.observed_at == result2.observed_at) {
        std::cerr << " [FAIL - observations should have different timestamps]\n";
        return;
    }
    
    std::cout << " [PASS]\n";
}

void test_freshness_tracking() {
    std::cout << "[TEST] Freshness tracking (get_last_observation_time/force_refresh)...";
    auto adapter = make_netlink_link_adapter();
    
    // Initial observation should set the time
    auto result1 = adapter->observe_interfaces();
    auto first_time = adapter->get_last_observation_time();
    
    if (first_time.time_since_epoch().count() <= 0) {
        std::cerr << " [FAIL - invalid initial observation time]\n";
        return;
    }
    
    // Force refresh should update the time
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    auto result2 = adapter->force_refresh();
    auto second_time = adapter->get_last_observation_time();
    
    if (second_time <= first_time) {
        std::cerr << " [FAIL - observation time should be updated after force_refresh]\n";
        return;
    }
    
    // Force refresh should produce fresh observations
    if (!result2.interfaces.empty() && result2.observed_at > result1.observed_at) {
        std::cout << " [PASS]\n";
    } else {
        std::cerr << " [FAIL - force_refresh did not update observation timestamp]\n";
        return;
    }
}

int main() {
    std::cout << "\n=== Network Interface Discovery Tests ===\n\n";
    
    test_factory_creates_adapter();
    test_observe_interfaces();
    test_interface_identity();
    test_topology();
    test_link_state_enum();
    test_address_family_enum();
    test_isolation();
    test_freshness_tracking();
    
    std::cout << "\n=== All Tests Complete ===\n\n";
    return 0;
}