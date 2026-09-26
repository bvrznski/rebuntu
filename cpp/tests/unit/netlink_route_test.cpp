// rebuntu - Phase 5.22 Route Discovery Unit Tests
//
// Unit tests for the netlink route observation adapter.

#include "../src/adapters/netlink/route/types.hpp"
#include <iostream>
#include <thread>

using namespace rebuntu::adapters::netlink::route;

namespace core = rebuntu::core;

void test_factory_creates_adapter() {
    std::cout << "[TEST] Factory creates adapter instance...";
    
    auto adapter = make_netlink_route_adapter();
    if (adapter == nullptr) {
        std::cerr << " [FAIL - null pointer]\n";
        return;
    }
    
    std::cout << " [PASS]\n";
}

void test_observe_routes() {
    std::cout << "[TEST] Observe routing tables...";
    
    auto adapter = make_netlink_route_adapter();
    auto result = adapter->observe_routes();
    
    if (result.status != core::SemanticStatus::kSuccess) {
        std::cerr << " [FAIL - status: " << to_string(result.status) 
                  << ", description: " << result.description << "]\n";
        return;
    }
    
    // Check that we got some routes
    if (result.routes.empty()) {
        std::cerr << " [FAIL - no routes found]\n";
        return;
    }
    
    std::cout << " [PASS - found " << result.routes.size() << " route(s)]\n";
}

void test_routing_table_structure() {
    std::cout << "[TEST] Routing table structure...";
    
    auto adapter = make_netlink_route_adapter();
    auto table = adapter->get_routing_table();
    
    if (table.total_routes == 0) {
        std::cerr << " [FAIL - no routes in table]\n";
        return;
    }
    
    // Check that IPv4 and IPv6 counts add up
    size_t sum = table.ipv4_route_count + table.ipv6_route_count;
    if (sum != table.total_routes) {
        std::cerr << " [FAIL - route count mismatch: " 
                  << table.ipv4_route_count << " + " << table.ipv6_route_count 
                  << " != " << table.total_routes << "]\n";
        return;
    }
    
    std::cout << " [PASS - IPv4: " << table.ipv4_route_count
              << ", IPv6: " << table.ipv6_route_count
              << ", Total: " << table.total_routes << "]\n";
}

void test_default_routes() {
    std::cout << "[TEST] Get default routes...";
    
    auto adapter = make_netlink_route_adapter();
    auto defaults = adapter->get_default_routes();
    
    // On most systems there should be at least one default route
    if (defaults.empty()) {
        std::cerr << " [WARN - no default routes found]\n";
        return;
    }
    
    for (const auto& route : defaults) {
        std::cout << "  Default route: " << route.destination << "/"
                  << route.destination_prefix_length;
        if (route.gateway.has_value()) {
            std::cout << " via " << route.gateway.value();
        }
        std::cout << "\n";
    }
    
    std::cout << " [PASS - found " << defaults.size() << " default route(s)]\n";
}

void test_route_identity_equality() {
    std::cout << "[TEST] RouteIdentity equality operator...";
    
    RouteIdentity id1;
    id1.destination = "0.0.0.0/0";
    id1.destination_prefix_length = 0;
    
    RouteIdentity id2;
    id2.destination = "0.0.0.0/0";
    id2.destination_prefix_length = 0;
    
    if (id1 != id2) {
        std::cerr << " [FAIL - equal identities should compare equal]\n";
        return;
    }
    
    RouteIdentity id3;
    id3.destination = "192.168.1.0/24";
    id3.destination_prefix_length = 24;
    
    if (id1 == id3) {
        std::cerr << " [FAIL - different identities should not compare equal]\n";
        return;
    }
    
    std::cout << " [PASS]\n";
}

void test_to_string_functions() {
    std::cout << "[TEST] to_string conversion functions...";
    
    bool all_valid = true;
    
    // Test RouteFamily
    if (to_string(RouteFamily::kInet) != "inet") {
        std::cerr << " [FAIL - RouteFamily::kInet conversion]\n";
        all_valid = false;
    }
    
    // Test RouteType  
    if (to_string(RouteType::kUnicast) != "unicast") {
        std::cerr << " [FAIL - RouteType::kUnicast conversion]\n";
        all_valid = false;
    }
    
    // Test RouteScope
    if (to_string(RouteScope::kUniverse) != "universe") {
        std::cerr << " [FAIL - RouteScope::kUniverse conversion]\n";
        all_valid = false;
    }
    
    if (all_valid) {
        std::cout << " [PASS]\n";
    } else {
        std::cerr << " [FAIL - some conversions failed]\n";
    }
}

void test_isolation() {
    std::cout << "[TEST] Multiple observations are isolated...";
    
    auto adapter = make_netlink_route_adapter();
    auto result1 = adapter->observe_routes();
    
    // Small delay to ensure different timestamps
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    
    auto result2 = adapter->observe_routes();
    
    if (result1.observed_at == result2.observed_at) {
        std::cerr << " [FAIL - observations should have different timestamps]\n";
        return;
    }
    
    std::cout << " [PASS]\n";
}

int main() {
    std::cout << "\n=== Route Discovery Tests ===\n\n";
    
    test_factory_creates_adapter();
    test_observe_routes();
    test_routing_table_structure();
    test_default_routes();
    test_route_identity_equality();
    test_to_string_functions();
    test_isolation();
    
    std::cout << "\n=== All Tests Complete ===\n\n";
    return 0;
}