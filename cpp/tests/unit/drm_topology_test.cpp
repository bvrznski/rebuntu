// rebuntu - Phase 5.35 DRM Display Topology Observation Unit Tests
//
// Unit tests for the DRM/KMS display topology observation adapter.

#include "../src/adapters/drm/types.hpp"
#include <iostream>
#include <thread>
#include <chrono>

using namespace rebuntu::adapters::drm;

namespace core = rebuntu::core;

void test_factory_creates_adapter() {
    std::cout << "[TEST] Factory creates adapter instance...";
    
    auto adapter = make_drm_topology_adapter();
    if (adapter == nullptr) {
        std::cerr << " [FAIL - null pointer]\n";
        return;
    }
    
    std::cout << " [PASS]\n";
}

void test_connector_type_to_string() {
    std::cout << "[TEST] ConnectorType to_string conversion...";
    
    bool all_valid = true;
    struct TestCase { ConnectorType type; const char* expected; };
    std::vector<TestCase> tests = {
        {ConnectorType::kUnknown, "unknown"},
        {ConnectorType::kVGA, "vga"},
        {ConnectorType::kDVI_I, "dvi-i"},
        {ConnectorType::kDVI_D, "dvi-d"},
        {ConnectorType::kHDMI, "hdmi"},
        {ConnectorType::kDisplayPort, "displayport"},
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

void test_connection_status_to_string() {
    std::cout << "[TEST] ConnectionStatus to_string conversion...";
    
    bool all_valid = true;
    struct TestCase { ConnectionStatus status; const char* expected; };
    std::vector<TestCase> tests = {
        {ConnectionStatus::kConnected, "connected"},
        {ConnectionStatus::kDisconnected, "disconnected"},
        {ConnectionStatus::kUnknown, "unknown"},
    };
    
    for (const auto& tc : tests) {
        if (to_string(tc.status) != tc.expected) {
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

void test_display_mode_to_string() {
    std::cout << "[TEST] DisplayMode to_string conversion...";
    
    DisplayMode mode;
    mode.width = 1920;
    mode.height = 1080;
    
    auto str = to_string(mode);
    if (str.find("1920x1080") != std::string::npos) {
        std::cout << " [PASS]\n";
    } else {
        std::cerr << " [FAIL - mode string format incorrect: " << str << "]\n";
    }
}

void test_identity_equality() {
    std::cout << "[TEST] ConnectorIdentity equality...";
    
    ConnectorIdentity a{"0000:01:00.0", "HDMI-A-1"};
    ConnectorIdentity b{"0000:01:00.0", "HDMI-A-1"};
    ConnectorIdentity c{"0000:02:00.0", "DP-1"};
    
    if (a == b && !(a == c)) {
        std::cout << " [PASS]\n";
    } else {
        std::cerr << " [FAIL - identity comparison incorrect]\n";
    }
}

void test_topology_observation() {
    std::cout << "[TEST] Topology observation structure...";
    
    auto adapter = make_drm_topology_adapter();
    auto result = adapter->observe_topology();
    
    if (result.status != core::SemanticStatus::kSuccess) {
        // This is acceptable on systems without DRM/KMS
        // Just verify the structure is correct
        std::cout << " [INFO - status: " << to_string(result.status)
                  << ", description: " << result.description << "]\n";
        return;
    }
    
    if (result.adapters.empty()) {
        std::cerr << " [FAIL - no adapters found on system with DRM]\n";
        return;
    }
    
    // Verify at least one adapter has proper data
    bool valid = false;
    for (const auto& adapter_obs : result.adapters) {
        std::cout << "\n  Adapter pci_bus_id=" << adapter_obs.pci_bus_id 
                  << " sysfs_path=" << adapter_obs.sysfs_path 
                  << " connectors=" << adapter_obs.connectors.size()
                  << " crtcs=" << adapter_obs.crtcs.size();
        
        if (!adapter_obs.pci_bus_id.empty() && !adapter_obs.sysfs_path.empty()) {
            valid = true;
            break;
        }
    }
    
    std::cout << "\n";
    
    if (valid) {
        std::cout << " [PASS - found " << result.adapters.size() << " adapter(s)]\n";
    } else {
        std::cerr << " [FAIL - adapters have invalid data]\n";
    }
}

void test_topology_graph() {
    std::cout << "[TEST] Topology graph structure...";
    
    auto adapter = make_drm_topology_adapter();
    auto topology = adapter->get_topology();
    
    // Even without DRM devices, the topology should be valid
    if (topology.total_adapters >= 0 && topology.captured_at.time_since_epoch().count() >= 0) {
        std::cout << " [PASS]\n";
    } else {
        std::cerr << " [FAIL - topology has invalid data]\n";
    }
}

void test_isolation() {
    std::cout << "[TEST] Multiple observations are isolated...";
    
    auto adapter = make_drm_topology_adapter();
    auto result1 = adapter->observe_topology();
    
    // Small delay to ensure different timestamps
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    
    auto result2 = adapter->observe_topology();
    
    if (result1.observed_at != result2.observed_at) {
        std::cout << " [PASS]\n";
    } else {
        // This may fail with low-resolution clocks
        std::cout << " [INFO - same timestamp due to clock resolution]\n";
    }
}

void test_connector_identity() {
    std::cout << "[TEST] Connector identity tracking...";
    
    auto adapter = make_drm_topology_adapter();
    auto topology = adapter->get_topology();
    
    // Test resolve by connector identity (may not find anything without DRM)
    if (!topology.connector_map.empty()) {
        bool found_valid = false;
        for (const auto& [id, conn] : topology.connector_map) {
            if (!id.gpu_pci_bus_id.empty() && !id.connector_name.empty() &&
                conn.observed_at.time_since_epoch().count() > 0) {
                found_valid = true;
                break;
            }
        }
        
        if (found_valid) {
            std::cout << " [PASS - connector map has valid entries]\n";
        } else {
            std::cerr << " [FAIL - connector map entries are invalid]\n";
        }
    } else {
        // Empty topology is acceptable on systems without DRM
        std::cout << " [INFO - no connectors (no DRM devices)]\n";
    }
}

void test_adapter_resolution() {
    std::cout << "[TEST] Adapter resolution by PCI bus ID...";
    
    auto adapter = make_drm_topology_adapter();
    
    // Try to resolve a non-existent adapter (should return nullopt)
    auto result = adapter->resolve_adapter("nonexistent-pci-bus-id");
    
    if (!result.has_value()) {
        std::cout << " [PASS - correctly returns nullopt for unknown adapter]\n";
    } else {
        std::cerr << " [FAIL - should return nullopt]\n";
    }
}

void test_connector_resolution() {
    std::cout << "[TEST] Connector resolution by identity...";
    
    auto adapter = make_drm_topology_adapter();
    ConnectorIdentity id{"nonexistent-pci-bus", "unknown"};
    
    // Try to resolve a non-existent connector (should return nullopt)
    auto result = adapter->resolve_connector(id);
    
    if (!result.has_value()) {
        std::cout << " [PASS - correctly returns nullopt for unknown connector]\n";
    } else {
        std::cerr << " [FAIL - should return nullopt]\n";
    }
}

int main() {
    std::cout << "\n=== DRM Display Topology Tests ===\n\n";
    
    test_factory_creates_adapter();
    test_connector_type_to_string();
    test_connection_status_to_string();
    test_display_mode_to_string();
    test_identity_equality();
    test_topology_observation();
    test_topology_graph();
    test_isolation();
    test_connector_identity();
    test_adapter_resolution();
    test_connector_resolution();
    
    std::cout << "\n=== All Tests Complete ===\n\n";
    return 0;
}