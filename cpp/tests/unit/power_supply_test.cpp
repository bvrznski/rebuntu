// rebuntu - Phase 5.34 Power Supply Observation Unit Tests
//
// Unit tests for the sysfs power supply adapter.

#include "../src/adapters/sysfs/power/types.hpp"
#include <iostream>
#include <thread>

using namespace rebuntu::adapters::sysfs::power;

namespace core = rebuntu::core;

void test_factory_creates_adapter() {
    std::cout << "[TEST] Factory creates adapter instance...";
    
    auto adapter = make_sysfs_power_adapter();
    if (adapter == nullptr) {
        std::cerr << " [FAIL - null pointer]\n";
        return;
    }
    
    std::cout << " [PASS]\n";
}

void test_observe_supplies() {
    std::cout << "[TEST] Observe power supplies...";
    
    auto adapter = make_sysfs_power_adapter();
    auto result = adapter->observe_supplies();
    
    if (result.status != core::SemanticStatus::kSuccess) {
        std::cerr << " [FAIL - status: " << to_string(result.status) 
                  << ", description: " << result.description << "]\n";
        return;
    }
    
    std::cout << " [PASS - found " << result.supplies.size() << " supply(ies)]\n";
}

void test_topology() {
    std::cout << "[TEST] Topology structure...";
    
    auto adapter = make_sysfs_power_adapter();
    auto topology = adapter->get_topology();
    
    // Should at least have the topology object
    bool has_valid_supplies = topology.supplies_by_name.size() > 0;
    
    if (!has_valid_supplies) {
        std::cout << " [SKIP - no power supplies on this system]\n";
        return;
    }
    
    std::cout << " [PASS]\n";
}

void test_battery_status_enum() {
    std::cout << "[TEST] BatteryStatus to_string conversion...";
    
    bool all_valid = true;
    struct TestCase { BatteryStatus state; const char* expected; };
    std::vector<TestCase> tests = {
        {BatteryStatus::kUnknown, "unknown"},
        {BatteryStatus::kFull, "full"},
        {BatteryStatus::kCharging, "charging"},
        {BatteryStatus::kDischarging, "discharging"},
        {BatteryStatus::kNotCharging, "not_charging"},
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

void test_power_supply_type_enum() {
    std::cout << "[TEST] PowerSupplyType to_string conversion...";
    
    bool all_valid = true;
    struct TestCase { PowerSupplyType type; const char* expected; };
    std::vector<TestCase> tests = {
        {PowerSupplyType::kUnknown, "unknown"},
        {PowerSupplyType::kBattery, "battery"},
        {PowerSupplyType::kAc, "ac"},
        {PowerSupplyType::kUsb, "usb"},
        {PowerSupplyType::kWireless, "wireless"},
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
    
    auto adapter = make_sysfs_power_adapter();
    auto result1 = adapter->observe_supplies();
    
    // Small delay to ensure different timestamps
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    
    auto result2 = adapter->observe_supplies();
    
    if (result1.observed_at == result2.observed_at) {
        std::cerr << " [FAIL - observations should have different timestamps]\n";
        return;
    }
    
    std::cout << " [PASS]\n";
}

int main() {
    std::cout << "\n=== Power Supply Observation Tests ===\n\n";
    
    test_factory_creates_adapter();
    test_observe_supplies();
    test_topology();
    test_battery_status_enum();
    test_power_supply_type_enum();
    test_isolation();
    
    std::cout << "\n=== All Tests Complete ===\n\n";
    return 0;
}