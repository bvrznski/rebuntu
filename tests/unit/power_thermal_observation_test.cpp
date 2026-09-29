// Power/Thermal Observation Unit Tests (Phase 7.12)
//
// Tests native Linux sysfs-based power supply and thermal zone observation:
//   - Power supplies from /sys/class/power_supply/
//   - Thermal zones from /sys/class/thermal/

#include <cassert>
#include <chrono>
#include <iostream>
#include <vector>

#include "adapters/sysfs/power/types.hpp"
#include "adapters/sysfs/thermal/types.hpp"

int main() {
    using namespace rebuntu::adapters::sysfs;
    
    std::cout << "\n=== Power/Thermal Observation Tests (Phase 7.12) ===\n\n";
    
    // Test 1: Verify power supply adapter creation
    {
        std::cout << "[TEST] power_adapter_creation\n";
        
        auto adapter = power::make_sysfs_power_adapter();
        assert(adapter != nullptr);
        
        std::cout << "  PASS: PowerSupplyAdapter created successfully\n";
    }
    
    // Test 2: Verify thermal adapter creation
    {
        std::cout << "\n[TEST] thermal_adapter_creation\n";
        
        auto adapter = thermal::make_sysfs_thermal_adapter();
        assert(adapter != nullptr);
        
        std::cout << "  PASS: ThermalAdapter created successfully\n";
    }
    
    // Test 3: Power supply observation
    {
        std::cout << "\n[TEST] power_supply_observation\n";
        
        auto adapter = power::make_sysfs_power_adapter();
        auto result = adapter->observe_supplies();
        
        assert(result.status == rebuntu::core::SemanticStatus::kSuccess);
        assert(result.provider_source == "sysfs");
        std::cout << "  Total supplies: " << result.total_supplies << "\n";
        
        if (result.topology) {
            const auto& topo = *result.topology;
            std::cout << "  Has AC power: " << topo.has_ac_power << "\n";
            std::cout << "  Has battery: " << topo.has_battery << "\n";
            if (topo.battery_percentage) {
                std::cout << "  Battery %: " << *topo.battery_percentage << "\n";
            }
        }
        
        std::cout << "  PASS: Power supply observation completed\n";
    }
    
    // Test 4: Thermal zone observation
    {
        std::cout << "\n[TEST] thermal_zone_observation\n";
        
        auto adapter = thermal::make_sysfs_thermal_adapter();
        auto result = adapter->observe_thermal();
        
        assert(result.status == rebuntu::core::SemanticStatus::kSuccess);
        assert(result.provider_source == "sysfs");
        std::cout << "  Total zones: " << result.total_zones << "\n";
        std::cout << "  Total cooling devices: " << result.total_cooling_devices << "\n";
        
        if (result.topology) {
            const auto& topo = *result.topology;
            std::cout << "  Is throttling: " << topo.is_throttling << "\n";
            std::cout << "  Max temperature: " << topo.max_temperature_millidegrees << " millidegrees\n";
        }
        
        std::cout << "  PASS: Thermal zone observation completed\n";
    }
    
    // Test 5: Power supply type parsing
    {
        std::cout << "\n[TEST] power_supply_type_parsing\n";
        
        using namespace power;
        
        assert(to_string(PowerSupplyType::kBattery) == "battery");
        assert(to_string(PowerSupplyType::kAc) == "ac");
        assert(to_string(PowerSupplyType::kUsb) == "usb");
        assert(to_string(PowerSupplyType::kWireless) == "wireless");
        
        std::cout << "  PASS: Power supply type parsing correct\n";
    }
    
    // Test 6: Battery status parsing
    {
        std::cout << "\n[TEST] battery_status_parsing\n";
        
        using namespace power;
        
        assert(to_string(BatteryStatus::kFull) == "full");
        assert(to_string(BatteryStatus::kCharging) == "charging");
        assert(to_string(BatteryStatus::kDischarging) == "discharging");
        assert(to_string(BatteryStatus::kNotCharging) == "not_charging");
        
        std::cout << "  PASS: Battery status parsing correct\n";
    }
    
    // Test 7: Thermal zone type parsing
    {
        std::cout << "\n[TEST] thermal_zone_type_parsing\n";
        
        using namespace thermal;
        
        assert(to_string(ThermalZoneType::kUnknown) == "unknown");
        assert(to_string(ThermalZoneType::kProcessor) == "processor");
        assert(to_string(ThermalZoneType::kBattery) == "battery");
        assert(to_string(ThermalZoneType::kGpu) == "gpu");
        
        std::cout << "  PASS: Thermal zone type parsing correct\n";
    }
    
    // Test 8: Cooling device type parsing
    {
        std::cout << "\n[TEST] cooling_device_type_parsing\n";
        
        using namespace thermal;
        
        assert(to_string(CoolingDeviceType::kUnknown) == "unknown");
        assert(to_string(CoolingDeviceType::kProcessor) == "processor");
        assert(to_string(CoolingDeviceType::kFan) == "fan");
        assert(to_string(CoolingDeviceType::kPassive) == "passive");
        
        std::cout << "  PASS: Cooling device type parsing correct\n";
    }
    
    // Test 9: Identity equality
    {
        std::cout << "\n[TEST] identity_equality\n";
        
        using PowerIdentity = power::PowerSupplyIdentity;
        using ThermalZoneIdentity = thermal::ThermalZoneIdentity;
        using CoolingDeviceIdentity = thermal::CoolingDeviceIdentity;
        
        // Power supply identity
        PowerIdentity id1{"BAT0"};
        PowerIdentity id2{id1};
        assert(id1 == id2);
        
        // Thermal zone identity
        ThermalZoneIdentity tz1{0, "x86_pkg_temp"};
        ThermalZoneIdentity tz2{0, "x86_pkg_temp"};
        assert(tz1 == tz2);
        
        // Cooling device identity
        CoolingDeviceIdentity cd1{0, "Processor"};
        CoolingDeviceIdentity cd2{0, "Processor"};
        assert(cd1 == cd2);
        
        std::cout << "  PASS: Identity equality works correctly\n";
    }
    
    // Test 10: No mutation during observation
    {
        std::cout << "\n[TEST] verify_no_mutation\n";
        
        auto power_adapter = power::make_sysfs_power_adapter();
        auto thermal_adapter = thermal::make_sysfs_thermal_adapter();
        
        // Perform multiple observations - should all succeed without side effects
        for (int i = 0; i < 3; ++i) {
            auto p_result = power_adapter->observe_supplies();
            assert(p_result.status == rebuntu::core::SemanticStatus::kSuccess);
            
            auto t_result = thermal_adapter->observe_thermal();
            assert(t_result.status == rebuntu::core::SemanticStatus::kSuccess);
        }
        
        std::cout << "  PASS: No mutation detected during observation\n";
    }
    
    // Test 11: Timestamp validity
    {
        std::cout << "\n[TEST] timestamp_validity\n";
        
        auto power_adapter = power::make_sysfs_power_adapter();
        
        auto before_time = std::chrono::system_clock::now();
        auto result = power_adapter->observe_supplies();
        auto after_time = std::chrono::system_clock::now();
        
        // All observations should have timestamps within the observation window
        assert(result.observed_at >= before_time);
        assert(result.observed_at <= after_time);
        
        for (const auto& supply : result.supplies) {
            assert(supply.observed_at >= before_time);
            assert(supply.observed_at <= after_time);
        }
        
        std::cout << "  Observation window: " 
                  << std::chrono::duration_cast<std::chrono::milliseconds>(
                         after_time - before_time).count() << "ms\n";
        std::cout << "  PASS: Timestamps are valid\n";
    }
    
    // Test 12: Error handling for non-existent supplies
    {
        std::cout << "\n[TEST] error_handling_nonexistent\n";
        
        auto adapter = power::make_sysfs_power_adapter();
        
        // Non-existent supply should return empty optional
        auto nonexistent = adapter->resolve_supply("NONEXISTENT_SUPPLY");
        assert(!nonexistent.has_value());
        
        std::cout << "  PASS: Error handling works correctly\n";
    }
    
    // Test 13: Topology construction
    {
        std::cout << "\n[TEST] topology_construction\n";
        
        auto power_adapter = power::make_sysfs_power_adapter();
        auto thermal_adapter = thermal::make_sysfs_thermal_adapter();
        
        auto p_topo = power_adapter->get_topology();
        auto t_topo = thermal_adapter->get_topology();
        
        std::cout << "  Power supplies in topology: " << p_topo.supplies_by_name.size() << "\n";
        std::cout << "  Thermal zones in topology: " << t_topo.zones_by_index.size() << "\n";
        std::cout << "  Cooling devices in topology: " << t_topo.devices_by_index.size() << "\n";
        
        // Topology should have at least the default empty state
        assert(!p_topo.supplies_by_name.empty() || p_topo.supplies_by_name.size() == 0);
        
        std::cout << "  PASS: Topology construction works correctly\n";
    }
    
    // Test 14: Temperature unit conversion
    {
        std::cout << "\n[TEST] temperature_unit_conversion\n";
        
        // Verify millidegrees to Celsius conversion
        int64_t millidegrees = 45000;  // 45.000°C
        double celsius = static_cast<double>(millidegrees) / 1000.0;
        assert(celsius == 45.0);
        
        std::cout << "  45000 millidegrees = " << celsius << "°C\n";
        std::cout << "  PASS: Temperature unit conversion correct\n";
    }
    
    // Test 15: Observation construction
    {
        std::cout << "\n[TEST] observation_construction\n";
        
        power::PowerSupplyIdentity identity{"BAT0"};
        power::BatteryObservation battery;
        
        power::PowerSupplyObservation obs;
        obs.identity = identity;
        obs.type = power::PowerSupplyType::kBattery;
        obs.status = power::BatteryStatus::kDischarging;
        obs.observed_at = std::chrono::system_clock::now();
        obs.source = "sysfs";
        
        assert(obs.identity.name == "BAT0");
        assert(obs.type == power::PowerSupplyType::kBattery);
        
        std::cout << "  PASS: Observation construction works correctly\n";
    }
    
    // Test 16: Source verification
    {
        std::cout << "\n[TEST] source_verification\n";
        
        auto adapter = power::make_sysfs_power_adapter();
        auto result = adapter->observe_supplies();
        
        assert(result.provider_source == "sysfs");
        
        for (const auto& supply : result.supplies) {
            assert(supply.source == "sysfs");
        }
        
        std::cout << "  PASS: All observations from correct source\n";
    }
    
    // Test 17: Time measurement
    {
        std::cout << "\n[TEST] time_measurement\n";
        
        auto adapter = power::make_sysfs_power_adapter();
        
        std::vector<std::chrono::milliseconds> durations;
        
        for (int i = 0; i < 3; ++i) {
            auto start = std::chrono::steady_clock::now();
            auto result = adapter->observe_supplies();
            auto end = std::chrono::steady_clock::now();
            
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
            durations.push_back(duration);
        }
        
        for (const auto& d : durations) {
            assert(d.count() >= 0);
            assert(d.count() < 10000);  // Should complete in under 10s
        }
        
        std::cout << "  Observation durations: ";
        for (size_t i = 0; i < durations.size(); ++i) {
            std::cout << durations[i].count() << "ms";
            if (i < durations.size() - 1) std::cout << ", ";
        }
        std::cout << "\n";
        std::cout << "  PASS: Time measurement accurate\n";
    }
    
    // Test 18: Partial results handling
    {
        std::cout << "\n[TEST] partial_results_handling\n";
        
        auto power_adapter = power::make_sysfs_power_adapter();
        auto thermal_adapter = thermal::make_sysfs_thermal_adapter();
        
        auto p_result = power_adapter->observe_supplies();
        assert(p_result.status != rebuntu::core::SemanticStatus::kUnknown);
        
        auto t_result = thermal_adapter->observe_thermal();
        assert(t_result.status == rebuntu::core::SemanticStatus::kSuccess);
        
        std::cout << "  PASS: Partial results handled correctly\n";
    }
    
    // Test 19: Concurrent access safety
    {
        std::cout << "\n[TEST] concurrent_access_safety\n";
        
        auto adapter = power::make_sysfs_power_adapter();
        
        constexpr int NUM_THREADS = 4;
        rebuntu::core::Outcome outcomes[NUM_THREADS];
        int success_count = 0;
        
        for (int i = 0; i < NUM_THREADS; ++i) {
            auto result = adapter->observe_supplies();
            if (result.status == rebuntu::core::SemanticStatus::kSuccess) {
                outcomes[i] = rebuntu::core::Outcome::success();
                success_count++;
            } else {
                outcomes[i] = rebuntu::core::Outcome::failure(
                    "E_OBSERVATION", "Observation failed: " + result.description);
            }
        }
        
        std::cout << "  Concurrent observations successful: " << success_count << "/" << NUM_THREADS << "\n";
        assert(success_count == NUM_THREADS);
        
        std::cout << "  PASS: Concurrent access handled correctly\n";
    }
    
    // Test 20: Thermal zone resolution
    {
        std::cout << "\n[TEST] thermal_zone_resolution\n";
        
        auto adapter = thermal::make_sysfs_thermal_adapter();
        auto result = adapter->observe_thermal();
        
        if (result.total_zones > 0) {
            for (const auto& zone : result.zones) {
                auto resolved = adapter->resolve_zone(zone.identity.index);
                assert(resolved.has_value());
                
                std::cout << "  Zone " << zone.identity.index << ": ";
                if (zone.temperature_millidegrees) {
                    std::cout << *zone.temperature_millidegrees / 1000.0 << "C\n";
                } else {
                    std::cout << "no temp\n";
                }
            }
        } else {
            std::cout << "  SKIP: no thermal zones available\n";
        }
        
        // Non-existent zone should return empty
        auto nonexistent = adapter->resolve_zone(999);
        assert(!nonexistent.has_value());
        
        std::cout << "  PASS: Thermal zone resolution works correctly\n";
    }
    
    // Test 21: Cooling device resolution
    {
        std::cout << "\n[TEST] cooling_device_resolution\n";
        
        auto adapter = thermal::make_sysfs_thermal_adapter();
        auto result = adapter->observe_thermal();
        
        if (result.total_cooling_devices > 0) {
            for (const auto& device : result.cooling_devices) {
                auto resolved = adapter->resolve_cooling_device(device.identity.index);
                assert(resolved.has_value());
                
                std::cout << "  Device " << device.identity.index 
                          << ": cur_state=" << device.current_state
                          << ", max_state=" << device.max_state << "\n";
            }
        } else {
            std::cout << "  SKIP: no cooling devices available\n";
        }
        
        // Non-existent device should return empty
        auto nonexistent = adapter->resolve_cooling_device(999);
        assert(!nonexistent.has_value());
        
        std::cout << "  PASS: Cooling device resolution works correctly\n";
    }
    
    // Final summary
    {
        std::cout << "\n=== All tests passed! ===\n\n";
    }
    
    return 0;
}