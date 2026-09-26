// rebuntu::adapters::netlink::route — Netlink Route Observation Adapter (Phase 5.22)
//
// This module implements Rebuntu's netlink-based network route observation adapter:
//   - Observes: routing table entries, default routes, gateway addresses
//   - Identifies stable native attributes via kernel routing tables
//   - Tracks provenance and freshness of observations
//
// Native Interfaces Used:
//   - rtnetlink (/proc/net/rtnetlink) — Linux kernel routing table management
//   - /proc/net/route — procfs route table (IPv4)
//   - /proc/net/ipv6_route — procfs IPv6 route table

#pragma once

#include <system/core/contracts.hpp>
#include <cstdint>
#include <optional>
#include <string>
#include <chrono>
#include <vector>
#include <memory>

namespace rebuntu::adapters::netlink::route {

// ============================================================================
// RouteFamily — Network route family
//
// Represents the protocol family of a route.
// ============================================================================
enum class RouteFamily {
    kUnspecified,  // No family specified
    kInet,         // IPv4 (AF_INET)
    kInet6,        // IPv6 (AF_INET6)
};

inline std::string to_string(RouteFamily f) {
    switch (f) {
        case RouteFamily::kUnspecified: return "unspecified";
        case RouteFamily::kInet:        return "inet";
        case RouteFamily::kInet6:       return "inet6";
    }
    return "unknown";
}

// ============================================================================
// RouteType — Type of route entry
//
// Represents the classification of a routing table entry.
// ============================================================================
enum class RouteType {
    kUnknown,           // Type cannot be determined
    kUnicast,           // Route to a unicast address
    kLocal,             // Route to a local interface address
    kBroadcast,         // Route to a broadcast address
    kAnyCast,           // Route to an anycast address
    kMulticast,         // Route to a multicast address
    kBlackhole,         // Silent discard (black hole)
    kUnreachable,       // Destination unreachable
    kProhibit,          // Prohibited by administrator
    kThrow,             // Stop routing in this table
    kNAT,               // Network address translation
};

inline std::string to_string(RouteType t) {
    switch (t) {
        case RouteType::kUnknown:      return "unknown";
        case RouteType::kUnicast:      return "unicast";
        case RouteType::kLocal:        return "local";
        case RouteType::kBroadcast:    return "broadcast";
        case RouteType::kAnyCast:      return "anycast";
        case RouteType::kMulticast:    return "multicast";
        case RouteType::kBlackhole:    return "blackhole";
        case RouteType::kUnreachable:  return "unreachable";
        case RouteType::kProhibit:     return "prohibit";
        case RouteType::kThrow:        return "throw";
        case RouteType::kNAT:          return "nat";
    }
    return "unknown";
}

// ============================================================================
// RouteScope — Scope of route
//
// Represents the scope or reachability domain of a route.
// ============================================================================
enum class RouteScope {
    kNowhere,  // Destination does not exist
    kHost,     // Destination is a local interface address
    kLink,     // Destination is on the directly attached network
    kRealm,    // Reserved for kernel use
    kSite,     // Internal to this site
    kUniverse, // Global route (universe)
};

inline std::string to_string(RouteScope s) {
    switch (s) {
        case RouteScope::kNowhere:  return "nowhere";
        case RouteScope::kHost:     return "host";
        case RouteScope::kLink:     return "link";
        case RouteScope::kRealm:    return "realm";
        case RouteScope::kSite:     return "site";
        case RouteScope::kUniverse: return "universe";
    }
    return "unknown";
}

// ============================================================================
// RouteFlags — Route entry flags
//
// Binary flags describing route characteristics.
// ============================================================================
struct RouteFlags {
    uint32_t value{0};
    
    // Route is on-link (can reach next hop without routing)
    bool is_on_link() const { return (value & (1U << 1)) != 0; }
    
    // Route has been synthesized from per-namespace config
    bool is_permanent() const { return (value & (1U << 3)) != 0; }
};

inline std::string to_string(RouteFlags f) {
    std::string result;
    if (f.is_on_link()) result += "on-link,";
    if (f.is_permanent()) result += "permanent,";
    if (!result.empty()) result.pop_back();
    return result.empty() ? "none" : result;
}

// ============================================================================
// RouteIdentity — Stable identity for a route entry
//
// A route is uniquely identified by:
//   - destination network prefix + prefix length
//   - source network prefix (optional)
//   - output interface index (ifindex) (optional, for per-interface routes)
//
// Note: Routes may have multiple equivalent paths (ECMP).
// ============================================================================
struct RouteIdentity {
    std::string destination;        // Destination network (e.g., "0.0.0.0/0")
    int32_t destination_prefix_length{0};  // CIDR prefix length
    std::optional<std::string> source;       // Source network (optional)
    int32_t source_prefix_length{0};         // Source prefix length
    std::optional<int32_t> output_ifindex;   // Output interface index (if applicable)
};

inline bool operator==(const RouteIdentity& a, const RouteIdentity& b) {
    return a.destination == b.destination &&
           a.destination_prefix_length == b.destination_prefix_length &&
           a.source == b.source &&
           a.source_prefix_length == b.source_prefix_length &&
           a.output_ifindex == b.output_ifindex;
}

// ============================================================================
// NextHop — Next hop information for a route
//
// Defines the next hop in the path to the destination.
// ============================================================================
struct NextHop {
    std::optional<std::string> address;      // Gateway IP address (if applicable)
    int32_t ifindex{-1};                     // Output interface index
    uint32_t weight{1};                      // ECMP weight (1-256)
};

// ============================================================================
// RouteObservation — Complete observation of a route entry
//
// Represents a single routing table entry with all its attributes.
// ============================================================================
struct RouteObservation {
    RouteIdentity identity;
    
    std::string destination;        // Human-readable destination
    int32_t destination_prefix_length{0};
    std::optional<std::string> source_network;      // Source network (if applicable)
    int32_t source_prefix_length{0};                // Source prefix length
    
    // Routing attributes
    RouteFamily family{RouteFamily::kUnspecified};
    RouteType type{RouteType::kUnknown};
    RouteScope scope{RouteScope::kNowhere};
    uint8_t protocol{0};            // Kernel routing table protocol
    uint32_t priority{0};           // Route priority (metric)
    
    // Next hop information
    std::optional<std::string> gateway;     // Gateway IP address
    int32_t output_ifindex{-1};             // Output interface index
    
    // Statistics
    uint64_t bytes{0};              // Bytes sent via this route
    uint64_t packets{0};            // Packets sent via this route
    uint64_t calls{0};              // Number of lookups
    uint64_t errors{0};             // Number of errors
    
    // Flags
    RouteFlags flags;
    
    // Provenance tracking
    std::chrono::system_clock::time_point observed_at{};
    std::string source{"netlink"};  // "netlink" for procfs queries
};

// ============================================================================
// RoutingTable — Complete routing table observation
//
// Represents the entire routing table as observed at a point in time.
// ============================================================================
struct RoutingTable {
    // All routes organized by family
    std::vector<RouteObservation> ipv4_routes;
    std::vector<RouteObservation> ipv6_routes;
    
    // Statistics
    size_t total_routes{0};
    size_t ipv4_route_count{0};
    size_t ipv6_route_count{0};
    size_t default_routes{0};       // Routes with 0.0.0.0/0 or ::/0 destination
    
    std::chrono::system_clock::time_point captured_at{};
    std::chrono::milliseconds capture_duration_ms{0};
};

// ============================================================================
// RouteDiscoveryResult — Result of route discovery
// ============================================================================
struct RouteDiscoveryResult {
    core::SemanticStatus status;
    std::string description;
    
    // Raw observations (individual routes)
    std::vector<RouteObservation> routes;
    
    // Topology: complete routing table
    std::optional<RoutingTable> table;
    
    // Provenance
    std::chrono::system_clock::time_point observed_at{};
    std::chrono::milliseconds elapsed_ms{0};
    
    size_t total_routes{0};
    size_t observation_failures{0};  // Number of routes where observation failed
    
    // Provider provenance - where this data came from
    std::string provider_source{"netlink"};  // Source: "netlink"
    
    std::optional<core::Error> error;
};

// ============================================================================
// RouteDiscoveryAdapter — Interface for netlink route discovery
//
// This adapter observes routing tables via rtnetlink and procfs:
//   - Queries IPv4 routes via /proc/net/route or RTM_GETROUTE
//   - Queries IPv6 routes via /proc/net/ipv6_route or RTM_GETROUTE
//   - Enriches with interface information for output_ifindex resolution
// ============================================================================
class RouteDiscoveryAdapter {
public:
    virtual ~RouteDiscoveryAdapter() = default;
    
    // Observe all routing table entries
    virtual RouteDiscoveryResult observe_routes() = 0;
    
    // Get the complete routing table
    virtual RoutingTable get_routing_table() = 0;
    
    // Find routes matching a destination
    virtual std::vector<RouteObservation> find_routes_to(std::string_view destination) = 0;
    
    // Get default routes (0.0.0.0/0 and ::/0)
    virtual std::vector<RouteObservation> get_default_routes() = 0;
    
    // Find route by identity
    virtual std::optional<RouteObservation> resolve_route(const RouteIdentity& identity) = 0;
};

// ============================================================================
// Factory function
// ============================================================================
std::unique_ptr<RouteDiscoveryAdapter> make_netlink_route_adapter();

}  // namespace rebuntu::adapters::netlink::route