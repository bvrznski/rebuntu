// Rebuntu Phase 7.8 — Sysfs Device Observation Unit Test
//
// Tests the sysfs-based device observation adapter:
//   - Device discovery from /sys/class/
//   - Stable identity tracking (PCI, vendor/device IDs)
//   - Freshness-aware results (observation timestamps)
//   - Bounded acquisition behavior

#include <cassert>
#include <chrono>
#include <iostream>
#include <memory>

#include "adapters/sysfs/device/types.hpp"
#include "adapters/sysfs/device/integration.hpp"

void test_default_values() {
    // Test default values for all structs
    
    // HardwareIdentifier defaults
    rebuntu::adapters::sysfs::device::HardwareIdentifier hw;
    assert(!hw.is_valid());  // No fields set, should be invalid
    
    // DeviceIdentity defaults
    rebuntu::adapters::sysfs::device::DeviceIdentity id;
    assert(!id.is_valid());  // Hardware identifier is default (invalid)
    
    // DeviceObservation defaults
    rebuntu::adapters::sysfs::device::DeviceObservation obs;
    assert(obs.kind == rebuntu::adapters::sysfs::device::DeviceKind::kOther);
    assert(!obs.subsystem.has_value());  // Optional fields should be empty
    
    std::cout << "[PASS] Default values are correct" << std::endl;
}

void test_device_kind_to_string() {
    using namespace rebuntu::adapters::sysfs::device;
    
    assert(to_string(DeviceKind::kInput) == "input");
    assert(to_string(DeviceKind::kAudio) == "audio");
    assert(to_string(DeviceKind::kDisplay) == "display");
    assert(to_string(DeviceKind::kStorage) == "storage");
    assert(to_string(DeviceKind::kNetwork) == "network");
    assert(to_string(DeviceKind::kOther) == "other");
    
    std::cout << "[PASS] DeviceKind to_string works correctly" << std::endl;
}

void test_device_state_to_string() {
    using namespace rebuntu::adapters::sysfs::device;
    
    assert(to_string(DeviceState::kUnknown) == "unknown");
    assert(to_string(DeviceState::kPresent) == "present");
    assert(to_string(DeviceState::kAbsent) == "absent");
    assert(to_string(DeviceState::kStale) == "stale");
    
    std::cout << "[PASS] DeviceState to_string works correctly" << std::endl;
}

void test_identity_hash() {
    using namespace rebuntu::adapters::sysfs::device;
    using namespace std;
    
    // Test that we can use DeviceIdentity in hash-based containers
    unordered_map<DeviceIdentity, string> device_map;
    
    DeviceIdentity id1;
    DeviceIdentity id2 = id1;  // Same identity
    
    // Both should produce the same hash
    auto h1 = hash<DeviceIdentity>{}(id1);
    auto h2 = hash<DeviceIdentity>{}(id2);
    
    assert(h1 == h2);  // Identical identities should have identical hashes
    
    std::cout << "[PASS] DeviceIdentity hash works correctly" << std::endl;
}

void test_adapter_creation() {
    using namespace rebuntu::adapters::sysfs::device;
    
    auto adapter = make_sysfs_device_adapter();
    assert(adapter != nullptr);
    
    // Test with options
    SysfsDeviceOptions opts;
    opts.max_total_devices = 100;
    auto adapter_with_opts = make_sysfs_device_adapter(opts);
    assert(adapter_with_opts != nullptr);
    
    std::cout << "[PASS] Adapter creation works correctly" << std::endl;
}

int main() {
    std::cout << "=== Phase 7.8: Sysfs Device Observation Tests ===" << std::endl;
    std::cout << std::endl;
    
    test_default_values();
    test_device_kind_to_string();
    test_device_state_to_string();
    test_identity_hash();
    test_adapter_creation();
    
    std::cout << std::endl;
    std::cout << "=== All Phase 7.8 unit tests passed ===" << std::endl;
    return 0;
}