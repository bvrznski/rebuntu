// rebuntu::adapters::netlink::link — Netlink Link/Interface Discovery Adapter (Phase 5.21)
//
// This module implements Rebuntu's netlink-based network interface observation adapter:
//   - Observes: interface name, index, MAC address, link state, IP addresses
//   - Identifies stable native attributes via sysfs and udev properties
//   - Tracks provenance and freshness of observations
//
// Native Interfaces Used:
//   - rtnetlink (/proc/net/rtnetlink) — Linux kernel network interface management
//   - /sys/class/net/ — sysfs network device attributes
//   - udev properties — persistent device identifiers
//
// Key Distinctions:
//   - Interface index = kernel's runtime stable identifier (ifindex)
//   - MAC address = hardware-based identifier (can be changed)
//   - Interface name = "eth0", "wlan0", etc. (not durable across reboots)
//   - Link state = up/down/unknown/dormant
//   - IP addresses = IPv4 and IPv6 addresses assigned to interface

#pragma once

#include <system/core/contracts.hpp>
#include <cstdint>
#include <optional>
#include <string>
#include <chrono>
#include <vector>
#include <memory>
#include <unordered_map>

namespace rebuntu::adapters::netlink::link {

// ============================================================================
// LinkState — Network interface link state
//
// Represents the physical/link layer status of a network interface.
// ============================================================================
enum class LinkState {
    kUnknown,      // State cannot be determined
    kNotPresent,   // Interface does not exist (removed)
    kDown,         // Interface is administratively down or physically disconnected
    kLowerLayerDown,  // Underlying interfaces are down
    kDormant,      // Interface is up but waiting for external events
    kUp,           // Interface is operational and can send/receive packets
};

inline std::string to_string(LinkState s) {
    switch (s) {
        case LinkState::kUnknown:       return "unknown";
        case LinkState::kNotPresent:    return "not-present";
        case LinkState::kDown:          return "down";
        case LinkState::kLowerLayerDown:return "lower-layer-down";
        case LinkState::kDormant:       return "dormant";
        case LinkState::kUp:            return "up";
    }
    return "unknown";
}

// ============================================================================
// AddressFamily — IP address family
//
// Represents the protocol family of an IP address.
// ============================================================================
enum class AddressFamily {
    kUnspecified,  // No family specified
    kInet,         // IPv4 (AF_INET)
    kInet6,        // IPv6 (AF_INET6)
};

inline std::string to_string(AddressFamily f) {
    switch (f) {
        case AddressFamily::kUnspecified: return "unspecified";
        case AddressFamily::kInet:        return "inet";
        case AddressFamily::kInet6:       return "inet6";
    }
    return "unknown";
}

// ============================================================================
// NetworkInterfaceIdentity — Stable identity for a network interface
//
// A network interface is uniquely identified by the combination of:
//   - ifindex = kernel's runtime stable identifier (unique during runtime)
//   - mac_address = hardware-based identifier (persistent across reboots, if not changed)
//
// Note: Interface names and IP addresses are attributes, NOT durable identity.
// ============================================================================
struct NetworkInterfaceIdentity {
    int32_t ifindex{-1};                    // Interface index from kernel
    std::string mac_address;                // Hardware MAC address (e.g., "00:11:22:33:44:55")
};

inline bool operator==(const NetworkInterfaceIdentity& a, const NetworkInterfaceIdentity& b) {
    return a.ifindex == b.ifindex && a.mac_address == b.mac_address;
}

// ============================================================================
// IPAddress — IP address with prefix length
//
// Represents an IPv4 or IPv6 address with its subnet mask as prefix length.
// ============================================================================
struct IPAddress {
    AddressFamily family{AddressFamily::kUnspecified};
    std::string address;                    // Human-readable address (e.g., "192.168.1.100")
    uint8_t prefix_length{0};               // CIDR prefix length (e.g., 24 for /24)
    
    bool is_ipv4() const { return family == AddressFamily::kInet; }
    bool is_ipv6() const { return family == AddressFamily::kInet6; }
};

// ============================================================================
// NetworkInterfaceObservation — Complete observation of a network interface
//
// Combines link-level attributes with IP address information and metadata.
// ============================================================================
struct NetworkInterfaceObservation {
    NetworkInterfaceIdentity identity;
    
    std::string name;                       // Interface name (e.g., "eth0", "wlan0")
    LinkState state{LinkState::kUnknown};   // Current link state
    uint32_t mtu{0};                        // Maximum Transmission Unit
    
    // Hardware/Physical attributes
    std::string driver;                     // Kernel driver name
    std::string parent_bus_path;            // Bus path for device (e.g., "pci-0000:00:19.0")
    
    // IP addresses assigned to this interface
    std::vector<IPAddress> ipv4_addresses;
    std::vector<IPAddress> ipv6_addresses;
    
    // Flags
    bool is_loopback{false};                // Loopback interface (lo)
    bool is_up{false};                      // Interface is administratively up
    bool is_broadcast{false};               // Supports broadcast
    bool is_point_to_point{false};          // Point-to-point link
    bool is_multicast{true};                // Supports multicast
    
    // Provenance tracking
    std::chrono::system_clock::time_point observed_at{};
    std::string source{"netlink"};          // "netlink" for rtnetlink queries
};

// ============================================================================
// NetworkInterfaceTopology — Relationship topology of network interfaces
//
// Represents how interfaces relate to each other and their hardware.
// ============================================================================
struct NetworkInterfaceTopology {
    // All observed interfaces indexed by ifindex
    std::unordered_map<int32_t, NetworkInterfaceObservation> interfaces_by_index;
    
    // Interface name -> ifindex mapping (for lookup by name)
    std::unordered_map<std::string, int32_t> index_by_name;
    
    // Statistics
    size_t total_interfaces{0};
    size_t up_interfaces{0};
    size_t down_interfaces{0};
    size_t loopback_count{0};
    
    std::chrono::system_clock::time_point captured_at{};
    std::chrono::milliseconds capture_duration_ms{0};
};

// ============================================================================
// NetworkInterfaceDiscoveryResult — Result of network interface discovery
// ============================================================================
struct NetworkInterfaceDiscoveryResult {
    core::SemanticStatus status;
    std::string description;
    
    // Raw observations (individual interfaces)
    std::vector<NetworkInterfaceObservation> interfaces;
    
    // Topology graph derived from relationships
    std::optional<NetworkInterfaceTopology> topology;
    
    // Provenance
    std::chrono::system_clock::time_point observed_at{};
    std::chrono::milliseconds elapsed_ms{0};
    
    size_t total_interfaces{0};
    size_t observation_failures{0};         // Number of interfaces where observation failed
    
    // Provider provenance - where this data came from
    std::string provider_source{"netlink"};  // Source: "netlink"
    
    std::optional<core::Error> error;
};

// ============================================================================
// NetworkInterfaceDiscoveryAdapter — Interface for netlink link discovery
//
// This adapter observes network interfaces via rtnetlink and sysfs:
//   - Queries interface attributes via netlink RTM_GETLINK messages
//   - Queries address information via netlink RTM_GETADDR messages
//   - Enriches with sysfs udev properties for stable identifiers
// ============================================================================
class NetworkInterfaceDiscoveryAdapter {
public:
    virtual ~NetworkInterfaceDiscoveryAdapter() = default;
    
    // Observe all network interfaces
    virtual NetworkInterfaceDiscoveryResult observe_interfaces() = 0;
    
    // Get the full topology of network interfaces
    virtual NetworkInterfaceTopology get_topology() = 0;
    
    // Resolve a specific interface by ifindex
    virtual std::optional<NetworkInterfaceObservation> resolve_by_index(int32_t ifindex) = 0;
    
    // Resolve a specific interface by name (less reliable than ifindex)
    virtual std::optional<NetworkInterfaceObservation> resolve_by_name(std::string_view name) = 0;
    
    // Get freshness: timestamp of the last observation
    // Returns epoch time point if no observation has been performed yet
    virtual std::chrono::system_clock::time_point get_last_observation_time() const = 0;
    
    // Force refresh: discard cached state and re-observe from native sources
    // This is idempotent and safe to call multiple times
    // Returns fresh observations with new timestamps
    virtual NetworkInterfaceDiscoveryResult force_refresh() = 0;
};

// ============================================================================
// Factory function
// ============================================================================
std::unique_ptr<NetworkInterfaceDiscoveryAdapter> make_netlink_link_adapter();

}  // namespace rebuntu::adapters::netlink::link