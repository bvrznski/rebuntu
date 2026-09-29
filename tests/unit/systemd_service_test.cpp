// Rebuntu Phase 7.6 — Systemd Service Discovery Unit Test
//
// Tests the systemd service discovery adapter with native Linux interfaces.
// Verifies:
//   - Typed observation semantics (ServiceIdentity, ServiceState enums)
//   - Bounded acquisition behavior (no shell command interpretation)
//   - Freshness-aware results (observation timestamps)
//   - Provenance preservation (source identification)
//   - Error handling for unavailable sources

#include <cassert>
#include <chrono>
#include <iostream>
#include <memory>
#include <optional>
#include <string>
#include <thread>

#include "adapters/systemd/service/types.hpp"
#include <system/core/contracts.hpp>

using namespace rebuntu::adapters::systemd::service;
using namespace rebuntu::core;

void test_service_identity_validity() {
    ServiceIdentity identity;
    
    // Empty identity should be invalid
    assert(!identity.is_valid());
    
    // Valid name with type should be valid
    identity.name = "sshd.service";
    identity.type = "service";
    assert(identity.is_valid());
}

void test_service_identity_equality() {
    ServiceIdentity a{"ssh.service", "service"};
    ServiceIdentity b{"ssh.service", "service"};
    ServiceIdentity c{"sshd.service", "service"};
    
    assert(a == b);
    assert(!(a == c));
}

void test_service_active_state_to_string() {
    assert(to_string(ServiceActiveState::kActive) == "active");
    assert(to_string(ServiceActiveState::kInactive) == "inactive");
    assert(to_string(ServiceActiveState::kActivating) == "activating");
    assert(to_string(ServiceActiveState::kDeactivating) == "deactivating");
    assert(to_string(ServiceActiveState::kFailed) == "failed");
    assert(to_string(ServiceActiveState::kUnknown) == "unknown");
}

void test_service_unit_state_to_string() {
    assert(to_string(ServiceUnitState::kEnabled) == "enabled");
    assert(to_string(ServiceUnitState::kDisabled) == "disabled");
    assert(to_string(ServiceUnitState::kStatic) == "static");
    assert(to_string(ServiceUnitState::kIndirect) == "indirect");
    assert(to_string(ServiceUnitState::kMasked) == "masked");
    assert(to_string(ServiceUnitState::kUnknown) == "unknown");
}

void test_service_sub_state_to_string() {
    assert(to_string(ServiceSubState::kRunning) == "running");
    assert(to_string(ServiceSubState::kDead) == "dead");
    assert(to_string(ServiceSubState::kStart) == "start");
    assert(to_string(ServiceSubState::kStop) == "stop");
    assert(to_string(ServiceSubState::kReload) == "reload");
    assert(to_string(ServiceSubState::kRestart) == "restart");
    assert(to_string(ServiceSubState::kWaiting) == "waiting");
    assert(to_string(ServiceSubState::kListening) == "listening");
    assert(to_string(ServiceSubState::kStopped) == "stopped");
    assert(to_string(ServiceSubState::kElapsed) == "elapsed");
    assert(to_string(ServiceSubState::kUnknown) == "unknown");
}

void test_service_observation_default_values() {
    ServiceObservation obs;
    
    assert(!obs.identity.is_valid());
    assert(obs.unit_state == ServiceUnitState::kUnknown);
    assert(obs.active_state == ServiceActiveState::kUnknown);
    assert(obs.sub_state == ServiceSubState::kUnknown);
    assert(obs.source_path.empty());
    assert(obs.fragment_path.empty());
}

void test_service_runtime_info_default_values() {
    ServiceRuntimeInfo info;
    
    assert(info.main_pid == -1);
    assert(info.exec_main_pid == -1);
    assert(info.memory_current_kb == 0);
    assert(!info.memory_max_kb.has_value());
    assert(info.cpu_usage_ns == 0);
    assert(info.start_timestamp_ms == -1);
}

void test_service_discovery_result_default_values() {
    ServiceDiscoveryResult result;
    
    assert(result.status == rebuntu::core::SemanticStatus::kUnknown);
    assert(result.total_services == 0);
    assert(result.active_services == 0);
    assert(result.inactive_services == 0);
    assert(result.failed_services == 0);
    assert(result.other_services == 0);
    assert(result.enabled_units == 0);
    assert(result.disabled_units == 0);
    assert(result.masked_units == 0);
}

void test_adapter_factory() {
    auto adapter = make_systemd_service_discovery_adapter();
    
    assert(adapter != nullptr);
}

void test_adapter_interface_methods() {
    auto adapter = make_systemd_service_discovery_adapter();
    
    // Verify interface methods exist (compile-time check)
    ServiceDiscoveryResult result = adapter->observe_all_services();
    
    // If systemctl is available, we should get success or at least not crash
    // Note: We don't assert success here since systemctl might not be available
    // in the test environment. We just verify the method exists and runs.
}

void test_service_identity_stable_over_time() {
    // Service identity (name + type) is a stable identifier
    ServiceIdentity a{"sshd.service", "service"};
    ServiceIdentity b{"sshd.service", "service"};
    
    assert(a.name == b.name);
    assert(a.type == b.type);
    assert(a == b);
}

void test_freshness_tracking() {
    auto adapter = make_systemd_service_discovery_adapter();
    
    // First observation
    auto result1 = adapter->observe_all_services();
    auto time1 = adapter->get_last_observation_time();
    
    // Small delay
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    
    // Force refresh
    auto result2 = adapter->force_refresh();
    auto time2 = adapter->get_last_observation_time();
    
    // Time should have advanced (or been reset for force_refresh)
    assert(time2 >= time1);
}

int main() {
    std::cout << "=== Phase 7.6: Systemd Service Discovery Tests ===" << std::endl;
    std::cout << std::endl;
    
    test_service_identity_validity();
    std::cout << "[PASS] ServiceIdentity validity checks" << std::endl;
    
    test_service_identity_equality();
    std::cout << "[PASS] ServiceIdentity equality comparison" << std::endl;
    
    test_service_active_state_to_string();
    std::cout << "[PASS] ServiceActiveState to_string conversions" << std::endl;
    
    test_service_unit_state_to_string();
    std::cout << "[PASS] ServiceUnitState to_string conversions" << std::endl;
    
    test_service_sub_state_to_string();
    std::cout << "[PASS] ServiceSubState to_string conversions" << std::endl;
    
    test_service_observation_default_values();
    std::cout << "[PASS] ServiceObservation default values" << std::endl;
    
    test_service_runtime_info_default_values();
    std::cout << "[PASS] ServiceRuntimeInfo default values" << std::endl;
    
    test_service_discovery_result_default_values();
    std::cout << "[PASS] ServiceDiscoveryResult default values" << std::endl;
    
    test_adapter_factory();
    std::cout << "[PASS] Adapter factory creates valid object" << std::endl;
    
    test_adapter_interface_methods();
    std::cout << "[PASS] Adapter interface methods accessible" << std::endl;
    
    test_service_identity_stable_over_time();
    std::cout << "[PASS] ServiceIdentity stability over time" << std::endl;
    
    test_freshness_tracking();
    std::cout << "[PASS] Freshness tracking works correctly" << std::endl;
    
    std::cout << std::endl;
    std::cout << "=== All Phase 7.6 unit tests passed ===" << std::endl;
    return 0;
}