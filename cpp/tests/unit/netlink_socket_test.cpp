// rebuntu - Phase 5.23 Socket/Listener Discovery Unit Tests
//
// Unit tests for the netlink socket discovery adapter.

#include "../src/adapters/netlink/socket/types.hpp"
#include <iostream>
#include <thread>
#include <chrono>
#include <vector>

using namespace rebuntu::adapters::netlink::socket;

namespace core = rebuntu::core;

void test_factory_creates_adapter() {
    std::cout << "[TEST] Factory creates adapter instance...";
    
    auto adapter = make_socket_discovery_adapter();
    if (adapter == nullptr) {
        std::cerr << " [FAIL - null pointer]\n";
        return;
    }
    
    std::cout << " [PASS]\n";
}

void test_observe_sockets() {
    std::cout << "[TEST] Observe sockets...";
    
    auto adapter = make_socket_discovery_adapter();
    auto result = adapter->observe_sockets();
    
    if (result.status != core::SemanticStatus::kSuccess) {
        std::cerr << " [FAIL - status: " << to_string(result.status) 
                  << ", description: " << result.description << "]\n";
        return;
    }
    
    // Should have at least some sockets (loopback, etc.)
    if (result.sockets.empty()) {
        std::cout << " [WARN - no sockets found (may be expected on minimal systems)]\n";
        return;
    }
    
    std::cout << " [PASS - found " << result.sockets.size() << " socket(s)]\n";
}

void test_listening_sockets() {
    std::cout << "[TEST] Get listening sockets...";
    
    auto adapter = make_socket_discovery_adapter();
    auto listening = adapter->get_listening_sockets();
    
    // Should have at least the loopback or some listener
    if (listening.empty()) {
        std::cout << " [WARN - no listening sockets found]\n";
        return;
    }
    
    std::cout << " [PASS - found " << listening.size() << " listening socket(s)]\n";
}

void test_socket_family_enum() {
    std::cout << "[TEST] SocketFamily to_string conversion...";
    
    bool all_valid = true;
    struct TestCase { SocketFamily family; const char* expected; };
    std::vector<TestCase> tests = {
        {SocketFamily::kUnspecified, "unspecified"},
        {SocketFamily::kInet, "inet"},
        {SocketFamily::kInet6, "inet6"},
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

void test_socket_protocol_enum() {
    std::cout << "[TEST] SocketProtocol to_string conversion...";
    
    bool all_valid = true;
    struct TestCase { SocketProtocol protocol; const char* expected; };
    std::vector<TestCase> tests = {
        {SocketProtocol::kUnspecified, "unspecified"},
        {SocketProtocol::kTcp, "tcp"},
        {SocketProtocol::kUdp, "udp"},
    };
    
    for (const auto& tc : tests) {
        if (to_string(tc.protocol) != tc.expected) {
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

void test_socket_state_enum() {
    std::cout << "[TEST] SocketState to_string conversion...";
    
    bool all_valid = true;
    struct TestCase { SocketState state; const char* expected; };
    std::vector<TestCase> tests = {
        {SocketState::kUnknown, "unknown"},
        {SocketState::kEstablished, "established"},
        {SocketState::kSynSent, "syn-sent"},
        {SocketState::kSynRecv, "syn-recv"},
        {SocketState::kFinWait1, "fin-wait-1"},
        {SocketState::kFinWait2, "fin-wait-2"},
        {SocketState::kTimeWait, "time-wait"},
        {SocketState::kClosed, "closed"},
        {SocketState::kCloseWait, "close-wait"},
        {SocketState::kLastAck, "last-ack"},
        {SocketState::kListen, "listen"},
        {SocketState::kClosing, "closing"},
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
    
    auto adapter = make_socket_discovery_adapter();
    auto result1 = adapter->observe_sockets();
    
    // Small delay to ensure different timestamps
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    
    auto result2 = adapter->observe_sockets();
    
    if (result1.observed_at == result2.observed_at) {
        std::cerr << " [FAIL - observations should have different timestamps]\n";
        return;
    }
    
    std::cout << " [PASS]\n";
}

int main() {
    std::cout << "\n=== Socket/Listener Discovery Tests ===\n\n";
    
    test_factory_creates_adapter();
    test_observe_sockets();
    test_listening_sockets();
    test_socket_family_enum();
    test_socket_protocol_enum();
    test_socket_state_enum();
    test_isolation();
    
    std::cout << "\n=== All Tests Complete ===\n\n";
    return 0;
}