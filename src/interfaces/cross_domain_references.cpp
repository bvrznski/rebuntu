// rebuntu::interfaces::cross_domain_references — Cross-Domain Entity References Implementation (Phase 5.46)
//
// This module provides a concrete implementation of the cross-domain reference provider
// interface that follows Rebuntu's key invariants:
//
//   - REFERENCES ARE TYPED: Each reference carries explicit domain information
//   - REFERENCE VALIDITY IS BOUNDED: References may become invalid between use
//   - ABSENCE IS UNKNOWN: Missing reference data is not proof of absence
//
// ============================================================================
// NETWORK INTERFACE IDENTITY WARNING
// ============================================================================
//
// The network_interface() method accepts interface names (e.g., "eth0", "wlan0").
// These names are NOT durable identities and can change due to:
//
//   • Reboot - kernel re-enumeration order changes
//   • Hotplug events - USB NICs, PCI devices added/removed
//   • udev rules changes - different naming policies
//   • Interface rename operations - manual or automated
//
// For stable identity across system changes, use the ifindex@mac_address format:
//
//   CrossDomainEntityId network_interface_stable(int32_t ifindex, std::string mac) {
//       return CrossDomainEntityId{"interface", std::to_string(ifindex) + "@" + mac};
//   }
//
// The netlink adapter provides NetworkInterfaceIdentity with stable fields:
//   - ifindex: kernel's runtime identifier (unique during runtime)
//   - mac_address: hardware-based identifier (persistent across reboots)

#include <system/core/contracts.hpp>
#include <interfaces/cross_domain_references.hpp>

namespace rebuntu::interfaces {

// ============================================================================
// CrossDomainEntityId static methods
// ============================================================================

CrossDomainEntityId CrossDomainEntityId::process(std::string pid_with_boot) {
    return CrossDomainEntityId{"process", std::move(pid_with_boot)};
}

CrossDomainEntityId CrossDomainEntityId::cgroup(std::string path) {
    return CrossDomainEntityId{"cgroup", std::move(path)};
}

CrossDomainEntityId CrossDomainEntityId::device(std::string sysfs_path) {
    return CrossDomainEntityId{"device", std::move(sysfs_path)};
}

CrossDomainEntityId CrossDomainEntityId::driver(std::string name) {
    return CrossDomainEntityId{"driver", std::move(name)};
}

CrossDomainEntityId CrossDomainEntityId::filesystem(std::string mount_point_or_uuid) {
    return CrossDomainEntityId{"filesystem", std::move(mount_point_or_uuid)};
}

CrossDomainEntityId CrossDomainEntityId::block_device(std::string dev_node_or_sysfs) {
    return CrossDomainEntityId{"block_device", std::move(dev_node_or_sysfs)};
}

CrossDomainEntityId CrossDomainEntityId::service(std::string unit_name, std::string type) {
    return CrossDomainEntityId{"service", std::move(unit_name) + "@" + type};
}

CrossDomainEntityId CrossDomainEntityId::network_interface(std::string name) {
    // WARNING: Interface names are NOT durable identities.
    // See file header for details on identity stability issues.
    return CrossDomainEntityId{"interface", std::move(name)};
}

CrossDomainEntityId CrossDomainEntityId::network_interface_stable(int32_t ifindex, std::string mac_address) {
    // Stable network interface identity using ifindex@mac_address format.
    // This provides durability across reboots and hotplug events where
    // kernel re-enumeration may change interface names like "eth0" -> "eth1".
    return CrossDomainEntityId{"interface", std::to_string(ifindex) + "@" + std::move(mac_address)};
}

CrossDomainEntityId CrossDomainEntityId::ip_address(std::string addr, std::string family) {
    return CrossDomainEntityId{"address", std::move(addr) + "@" + family};
}

// ============================================================================
// CrossDomainReferenceProvider stub implementation
// (No behavioral implementation - this is a types-only module)
// ============================================================================

class CrossDomainReferenceProviderStub : public CrossDomainReferenceProvider {
public:
    CrossDomainReferenceProviderStub() = default;
    
    CrossDomainReferenceResult query(const CrossDomainQuery& query) override {
        CrossDomainReferenceResult result;
        result.status = core::SemanticStatus::kUnknown;
        result.description = "Cross-domain reference provider not implemented";
        return result;
    }
    
    CrossDomainReferenceResult get_all_references(
        const CrossDomainEntityId& entity_id) override {
        CrossDomainReferenceResult result;
        result.status = core::SemanticStatus::kUnknown;
        result.description = "Cross-domain reference provider not implemented";
        return result;
    }
    
    bool has_reference(
        const CrossDomainEntityId& from,
        const CrossDomainEntityId& to,
        RelationshipType type) override {
        return false;  // Unknown
    }
    
    std::vector<EntityReference> get_references_by_type(
        const CrossDomainEntityId& entity_id,
        RelationshipType type) override {
        return {};  // Empty - no references known
    }
    
    std::chrono::system_clock::time_point get_last_observation_time() const override {
        return std::chrono::system_clock::time_point{};
    }
};

// ============================================================================
// Factory function
// ============================================================================

std::unique_ptr<CrossDomainReferenceProvider> make_cross_domain_reference_provider() {
    return std::make_unique<CrossDomainReferenceProviderStub>();
}

}  // namespace rebuntu::interfaces