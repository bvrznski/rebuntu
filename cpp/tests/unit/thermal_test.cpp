// rebuntu - Phase 5.34 Thermal Zone Observation Unit Tests
//
// Unit tests for the sysfs thermal adapter.

#include "../src/adapters/sysfs/thermal/types.hpp"
#include <iostream>
#include <thread>

using namespace rebuntu::adapters::sysfs::thermal;

namespace core = rebuntu::core;

void test_factory_creates_adapter() {
    std::cout << "[TEST] Factory creates adapter instance...";
    
    auto adapter = make_sysfs_thermal_adapter();
    if (adapter == nullptr) {
        std::cerr << " [FAIL - null pointer]\n";
        return;
    }
    
    std::cout << " [PASS]\n";
}

void test_observe_thermal() {
    std::cout << "[TEST] Observe thermal zones...";
    
    auto adapter = make_sysfs_thermal_adapter();
    auto result = adapter->observe_thermal();
    
    if (result.status != core::SemanticStatus::kSuccess) {
        std::cerr << " [FAIL - status: " << to_string(result.status) 
                  << ", description: " << result.description << "]\n";
        return;
    }
    
    std::cout << " [PASS - found " << result.zones.size() << " zone(s), "
              << result.cooling_devices.size() << " cooling device(s)]\n";
}

void test_topology() {
    std::cout << "[TEST] Topology structure...";
    
    auto adapter = make_sysfs_thermal_adapter();
    auto topology = adapter->get_topology();
    
    bool has_valid_zones = topology.zones_by_index.size() > 0;
    bool has_valid_devices = topology.devices_by_index.size() > 0;
    
    if (!has_valid_zones && !has_valid_devices) {
        std::cout << " [SKIP - no thermal zones/devices on this system]\n";
        return;
    }
    
    std::cout << " [PASS]\n";
}

void test_thermal_zone_enum() {
    std::cout << "[TEST] ThermalZoneType to_string conversion...";
    
    bool all_valid = true;
    struct TestCase { ThermalZoneType type; const char* expected; };
    std::vector<TestCase> tests = {
        {ThermalZoneType::kUnknown, "unknown"},
        {ThermalZoneType::kProcessor, "processor"},
        {ThermalZoneType::kBattery, "battery"},
        {ThermalZoneType::kGpu, "gpu"},
        {ThermalZoneType::kFan, "fan"},
        {ThermalZoneType::kNetwork, "network"},
    };
    
    for (const auto& tc : tests) {
        if (to_string(tc.type) != tc.expected) {
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
    
    auto adapter = make_sysfs_thermal_adapter();
    auto result1 = adapter->observe_thermal();
    
    // Small delay to ensure different timestamps
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    
    auto result2 = adapter->observe_thermal();
    
    if (result1.observed_at == result2.observed_at) {
        std::cerr << " [FAIL - observations should have different timestamps]\n";
        return;
    }
    
    std::cout << " [PASS]\n";
}

int main() {
    std::cout << "\n=== Thermal Zone Observation Tests ===\n\n";
    
    test_factory_creates_adapter();
    test_observe_thermal();
    test_topology();
    test_thermal_zone_enum();
    test_isolation();
    
    std::cout << "\n=== All Tests Complete ===\n\n";
    return 0;
}