// rebuntu - Phase 5.48 Hotplug Device State Management Unit Tests
//
// Unit tests for the hotplug observer module.

#include "adapters/hotplug/types.hpp"
#include <iostream>

using namespace rebuntu::adapters::hotplug;

void test_factory_creates_instance() {
    std::cout << "[TEST] Factory creates instance...";
    
    auto observer = make_hotplug_observer();
    if (observer == nullptr) {
        std::cerr << " [FAIL - null pointer]\n";
        return;
    }
    
    std::cout << " [PASS]\n";
}

void test_device_identity_key() {
    std::cout << "[TEST] DeviceIdentity key generation...";
    
    DeviceIdentity id;
    id.sysfs_path = "/sys/class/input/event0";
    id.kind = DeviceKind::kInput;
    
    auto key = id.key();
    
    if (key.empty()) {
        std::cerr << " [FAIL - empty key]\n";
        return;
    }
    
    if (key.find("sys:/sys/class/input/event0") == std::string::npos) {
        std::cerr << " [FAIL - wrong key format: " << key << "]\n";
        return;
    }
    
    std::cout << " [PASS]\n";
}

void test_device_identity_valid() {
    std::cout << "[TEST] DeviceIdentity is_valid check...";
    
    DeviceIdentity id1;
    if (id1.is_valid()) {
        std::cerr << " [FAIL - invalid identity reported as valid]\n";
        return;
    }
    
    DeviceIdentity id2;
    id2.sysfs_path = "/sys/class/input/event0";
    if (!id2.is_valid()) {
        std::cerr << " [FAIL - valid identity reported as invalid]\n";
        return;
    }
    
    std::cout << " [PASS]\n";
}

void test_device_identity_equality() {
    std::cout << "[TEST] DeviceIdentity equality comparison...";
    
    DeviceIdentity id1, id2;
    id1.sysfs_path = "/sys/class/input/event0";
    id1.kind = DeviceKind::kInput;
    id2.sysfs_path = "/sys/class/input/event0";
    id2.kind = DeviceKind::kInput;
    
    if (!(id1 == id2)) {
        std::cerr << " [FAIL - equal identities not equal]\n";
        return;
    }
    
    // Different sysfs paths
    id2.sysfs_path = "/sys/class/input/event1";
    if (id1 == id2) {
        std::cerr << " [FAIL - different identities reported as equal]\n";
        return;
    }
    
    std::cout << " [PASS]\n";
}

void test_device_kind_to_string() {
    std::cout << "[TEST] DeviceKind to_string conversion...";
    
    if (to_string(DeviceKind::kInput) != "input") {
        std::cerr << " [FAIL - wrong string for kInput]\n";
        return;
    }
    if (to_string(DeviceKind::kAudio) != "audio") {
        std::cerr << " [FAIL - wrong string for kAudio]\n";
        return;
    }
    if (to_string(DeviceKind::kDisplay) != "display") {
        std::cerr << " [FAIL - wrong string for kDisplay]\n";
        return;
    }
    if (to_string(DeviceKind::kStorage) != "storage") {
        std::cerr << " [FAIL - wrong string for kStorage]\n";
        return;
    }
    if (to_string(DeviceKind::kNetwork) != "network") {
        std::cerr << " [FAIL - wrong string for kNetwork]\n";
        return;
    }
    if (to_string(DeviceKind::kOther) != "other") {
        std::cerr << " [FAIL - wrong string for kOther]\n";
        return;
    }
    
    std::cout << " [PASS]\n";
}

void test_device_state_to_string() {
    std::cout << "[TEST] DeviceState to_string conversion...";
    
    if (to_string(DeviceState::kUnknown) != "unknown") {
        std::cerr << " [FAIL - wrong string for kUnknown]\n";
        return;
    }
    if (to_string(DeviceState::kPresent) != "present") {
        std::cerr << " [FAIL - wrong string for kPresent]\n";
        return;
    }
    if (to_string(DeviceState::kRemoved) != "removed") {
        std::cerr << " [FAIL - wrong string for kRemoved]\n";
        return;
    }
    if (to_string(DeviceState::kStale) != "stale") {
        std::cerr << " [FAIL - wrong string for kStale]\n";
        return;
    }
    
    std::cout << " [PASS]\n";
}

void test_hotplug_options_make_default() {
    std::cout << "[TEST] HotplugOptions make_default sets values...";
    
    auto options = HotplugOptions::make_default();
    
    if (options.freshness_threshold_ms.count() == 0) {
        std::cerr << " [FAIL - freshness_threshold_ms is 0]\n";
        return;
    }
    
    if (!options.kinds.discover_input) {
        std::cerr << " [FAIL - discover_input not enabled by default]\n";
        return;
    }
    
    std::cout << " [PASS]\n";
}

int main() {
    std::cout << "\n=== Hotplug Observer Tests ===\n\n";
    
    test_factory_creates_instance();
    test_device_identity_key();
    test_device_identity_valid();
    test_device_identity_equality();
    test_device_kind_to_string();
    test_device_state_to_string();
    test_hotplug_options_make_default();
    
    std::cout << "\n=== All Tests Complete ===\n\n";
    return 0;
}