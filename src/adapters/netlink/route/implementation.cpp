// rebuntu::adapters::netlink::route — Netlink Route Observation Implementation (Phase 5.22)
//
// This module implements Rebuntu's netlink-based network route observation adapter:
//   - Observes: routing table entries, default routes, gateway addresses
//   - Identifies stable native attributes via procfs
//   - Tracks provenance and freshness of observations
//
// Native Interfaces Used:
//   - /proc/net/route — procfs IPv4 route table
//   - /proc/net/ipv6_route — procfs IPv6 route table

#include "adapters/netlink/route/types.hpp"

#include <algorithm>
#include <array>
#include <cctype>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>
#include <memory>
#include <unordered_map>
#include <iostream>

namespace rebuntu::adapters::netlink::route {

// ============================================================================
// Helper: Convert hex string to integer
// ============================================================================
static uint32_t parse_hex(const std::string& s) {
    uint32_t result = 0;
    std::istringstream iss(s);
    iss >> std::hex >> result;
    return result;
}

// ============================================================================
// Helper: Convert IP from hex (little-endian in procfs) to string
// ============================================================================
static std::string ipv4_hex_to_string(uint32_t addr) {
    // procfs stores IPv4 addresses in little-endian format
    std::array<uint8_t, 4> bytes;
    for (int i = 0; i < 4; ++i) {
        bytes[i] = (addr >> (i * 8)) & 0xFF;
    }
    
    std::ostringstream oss;
    oss << static_cast<int>(bytes[0]) << "."
        << static_cast<int>(bytes[1]) << "."
        << static_cast<int>(bytes[2]) << "."
        << static_cast<int>(bytes[3]);
    return oss.str();
}

// ============================================================================
// Helper: Parse CIDR prefix length from netmask
// ============================================================================
static int parse_prefix_length(uint32_t netmask) {
    if (netmask == 0) return 0;
    
    // Count leading 1-bits in the netmask
    int count = 0;
    for (int i = 31; i >= 0 && ((netmask >> i) & 1); --i) {
        ++count;
    }
    return count;
}

// ============================================================================
// Helper: Get output interface name by ifindex from sysfs
// ============================================================================
static std::string get_interface_name_by_index(int32_t ifindex) {
    std::filesystem::path net_path = "/sys/class/net";
    
    if (!std::filesystem::exists(net_path)) {
        return "";
    }
    
    for (const auto& entry : std::filesystem::directory_iterator(net_path)) {
        if (!entry.is_directory()) continue;
        
        std::filesystem::path index_path = entry.path() / "ifindex";
        if (std::filesystem::exists(index_path)) {
            std::ifstream file(index_path);
            int32_t idx = 0;
            file >> idx;
            if (idx == ifindex) {
                return entry.path().filename().string();
            }
        }
    }
    
    return "";
}

// ============================================================================
// Helper: Read all lines from a file
// ============================================================================
static std::vector<std::string> read_file_lines(const std::string& path) {
    std::vector<std::string> lines;
    std::ifstream file(path);
    
    if (!file.is_open()) {
        return lines;
    }
    
    std::string line;
    while (std::getline(file, line)) {
        // Skip empty lines and header
        if (!line.empty() && line[0] != 'I') {
            lines.push_back(line);
        }
    }
    
    return lines;
}

// ============================================================================
// IPv4 Route Parser — Parses /proc/net/route format
//
// Format (from procfs):
//   Iface   Destination Gateway     Flags   RefCnt  Use     Metric  Mask        MTU     Window  IRTT
//   eth0    00000000    0A0002FF    0003    0       0       100     00FFFFFF    0       0       0
//
// Fields (hex):
//   - Destination: destination IP (little-endian)
//   - Gateway: gateway IP (little-endian)
//   - Flags: route flags (bit 1=ONLINK, bit 3=PERMANENT)
//   - Mask: netmask for prefix length calculation
// ============================================================================
static std::vector<RouteObservation> parse_ipv4_routes() {
    std::vector<RouteObservation> routes;
    
    const std::string proc_path = "/proc/net/route";
    std::ifstream file(proc_path);
    
    if (!file.is_open()) {
        return routes;
    }
    
    std::string line;
    bool is_header = true;
    
    while (std::getline(file, line)) {
        // Skip empty lines
        if (line.empty()) continue;
        
        // Skip header line
        if (is_header) {
            is_header = false;
            continue;
        }
        
        std::istringstream iss(line);
        std::string iface, dest_hex, gateway_hex, flags_hex, refcnt, use, metric_mask, mask_hex;
        
        if (!(iss >> iface >> dest_hex >> gateway_hex >> flags_hex >> refcnt >> use >> metric_mask >> mask_hex)) {
            continue;
        }
        
        RouteObservation route;
        route.observed_at = std::chrono::system_clock::now();
        route.source = "netlink";
        
        // Parse destination
        uint32_t dest_addr = parse_hex(dest_hex);
        uint32_t netmask = parse_hex(mask_hex);
        
        route.destination = ipv4_hex_to_string(dest_addr);
        route.destination_prefix_length = parse_prefix_length(netmask);
        route.identity.destination = route.destination;
        route.identity.destination_prefix_length = route.destination_prefix_length;
        
        // Parse gateway
        if (!gateway_hex.empty() && gateway_hex != "00000000") {
            uint32_t gw_addr = parse_hex(gateway_hex);
            route.gateway = ipv4_hex_to_string(gw_addr);
        }
        
        // Parse flags
        uint32_t flags_val = parse_hex(flags_hex);
        route.flags.value = flags_val;
        
        // Route type based on destination
        if (dest_addr == 0 && netmask == 0) {
            route.type = RouteType::kUnicast;  // Default route
        } else if (netmask == 0xFFFFFFFF) {
            route.type = RouteType::kLocal;    // Host route
        } else {
            route.type = RouteType::kUnicast;
        }
        
        route.family = RouteFamily::kInet;
        route.scope = RouteScope::kUniverse;
        route.priority = 0;  // procfs doesn't provide priority
        
        // Parse output interface index from sysfs
        int32_t ifindex = -1;
        std::filesystem::path iface_path = "/sys/class/net/" + iface + "/ifindex";
        if (std::filesystem::exists(iface_path)) {
            std::ifstream idx_file(iface_path);
            idx_file >> ifindex;
        }
        route.output_ifindex = ifindex;
        
        routes.push_back(std::move(route));
    }
    
    return routes;
}

// ============================================================================
// IPv6 Route Parser — Parses /proc/net/ipv6_route format
//
// Format (from procfs):
//   src_addr  src_prefix_len  dst_addr  dst_prefix_len  next_hop  metric  refcnt  flags  dev
//   fe800000000000000000000000000000  40 00000000000000000000000000000000  00 00000000000000000000000000000000  00000100 00000001 00000011 lo
//
// Fields (hex, 32 hex chars = 128 bits for addresses):
//   - src_addr: source network (16 bytes)
//   - src_prefix_len: source prefix length (1 byte)
//   - dst_addr: destination network (16 bytes)
//   - dst_prefix_len: destination prefix length (1 byte)
//   - next_hop: next hop gateway (16 bytes, little-endian)
//   - metric: routing metric
//   - refcnt: reference count
//   - flags: route flags
//   - dev: output interface name
// ============================================================================
static std::vector<RouteObservation> parse_ipv6_routes() {
    std::vector<RouteObservation> routes;
    
    const std::string proc_path = "/proc/net/ipv6_route";
    std::ifstream file(proc_path);
    
    if (!file.is_open()) {
        return routes;
    }
    
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        
        // IPv6 route format: 9 space-separated fields
        std::istringstream iss(line);
        std::array<std::string, 9> fields;
        for (size_t i = 0; i < fields.size(); ++i) {
            if (!(iss >> fields[i])) break;
        }
        
        // Skip if we didn't get all required fields
        if (fields[8].empty()) continue;
        
        RouteObservation route;
        route.observed_at = std::chrono::system_clock::now();
        route.source = "netlink";
        
        // Parse source address and prefix
        std::string src_hex = fields[0];
        int src_prefix_len = 0;
        if (!fields[1].empty()) {
            try {
                src_prefix_len = static_cast<int>(std::stoul(fields[1], nullptr, 16));
            } catch (...) {
                src_prefix_len = 0;
            }
        }
        
        // Parse destination address and prefix
        std::string dst_hex = fields[2];
        route.destination_prefix_length = 0;
        if (!fields[3].empty()) {
            try {
                route.destination_prefix_length = static_cast<int>(std::stoul(fields[3], nullptr, 16));
            } catch (...) {
                route.destination_prefix_length = 0;
            }
        }
        route.identity.destination_prefix_length = route.destination_prefix_length;
        // Format: 8 groups of 4 hex digits separated by colons
        auto ipv6_hex_to_string = [](const std::string& hex) -> std::string {
            if (hex.empty() || hex.size() < 32) return "::";
            
            std::ostringstream oss;
            for (int i = 0; i < 8; ++i) {
                if (i > 0) oss << ":";
                // Extract 4 hex digits and convert to uint16_t
                uint16_t val = 0;
                for (int j = 0; j < 4 && (i * 4 + j) < static_cast<int>(hex.size()); ++j) {
                    char c = hex[i * 4 + j];
                    val <<= 4;
                    if (c >= '0' && c <= '9') val |= (c - '0');
                    else if (c >= 'a' && c <= 'f') val |= (c - 'a' + 10);
                    else if (c >= 'A' && c <= 'F') val |= (c - 'A' + 10);
                }
                oss << std::hex << val;
            }
            
            // Compress consecutive zeros
            std::string result = oss.str();
            size_t longest_zero_start = 0, longest_zero_len = 0;
            size_t curr_zero_start = 0, curr_zero_len = 0;
            
            for (size_t i = 0; i < result.size(); ++i) {
                if (result[i] == '0' || (i + 1 < result.size() && result[i+1] == ':')) {
                    if (curr_zero_len == 0) curr_zero_start = i;
                    while (i < result.size() && (result[i] == '0' || result[i] == ':')) {
                        ++curr_zero_len;
                        ++i;
                    }
                    if (curr_zero_len > longest_zero_len) {
                        longest_zero_start = curr_zero_start;
                        longest_zero_len = curr_zero_len;
                    }
                    curr_zero_len = 0;
                }
            }
            
            if (longest_zero_len >= 2) {
                result.erase(longest_zero_start, longest_zero_len);
                result.insert(longest_zero_start, "::");
            }
            
            return result;
        };
        
        route.destination = ipv6_hex_to_string(dst_hex);
        route.identity.destination = route.destination;
        route.identity.destination_prefix_length = route.destination_prefix_length;
        
        // Parse gateway (next_hop) - typically :: for local routes
        std::string nh_hex = fields[4];
        if (!nh_hex.empty() && nh_hex != "00000000000000000000000000000000") {
            route.gateway = ipv6_hex_to_string(nh_hex);
        }
        
        // Parse flags
        uint32_t flags_val = parse_hex(fields[7]);
        route.flags.value = flags_val;
        
        // Determine route type
        bool is_all_zeros = std::all_of(dst_hex.begin(), dst_hex.end(), [](char c) { return c == '0'; });
        if (is_all_zeros && route.destination_prefix_length == 0) {
            route.type = RouteType::kUnicast;  // Default route
        } else {
            route.type = RouteType::kUnicast;
        }
        
        route.family = RouteFamily::kInet6;
        route.scope = RouteScope::kUniverse;
        // Parse priority (metric)
        route.priority = 0;
        if (!fields[5].empty()) {
            try {
                route.priority = static_cast<uint32_t>(std::stoul(fields[5], nullptr, 16));
            } catch (...) {
                route.priority = 0;
            }
        }
        
        // Get output interface index
        int32_t ifindex = -1;
        std::string dev_name = fields[8];
        std::filesystem::path iface_path = "/sys/class/net/" + dev_name + "/ifindex";
        if (std::filesystem::exists(iface_path)) {
            std::ifstream idx_file(iface_path);
            idx_file >> ifindex;
        }
        route.output_ifindex = ifindex;
        
        routes.push_back(std::move(route));
    }
    
    return routes;
}

// ============================================================================
// RouteAdapter Implementation
// ============================================================================

class RouteAdapter : public RouteDiscoveryAdapter {
public:
    RouteAdapter() = default;
    ~RouteAdapter() override = default;
    
    RouteDiscoveryResult observe_routes() override {
        RouteDiscoveryResult result;
        result.observed_at = std::chrono::system_clock::now();
        
        auto start_time = std::chrono::steady_clock::now();
        
        // Parse IPv4 routes
        auto ipv4_routes = parse_ipv4_routes();
        
        // Parse IPv6 routes  
        auto ipv6_routes = parse_ipv6_routes();
        
        // Build complete routing table
        RoutingTable table;
        table.ipv4_routes = std::move(ipv4_routes);
        table.ipv6_routes = std::move(ipv6_routes);
        
        table.total_routes = table.ipv4_routes.size() + table.ipv6_routes.size();
        table.ipv4_route_count = table.ipv4_routes.size();
        table.ipv6_route_count = table.ipv6_routes.size();
        table.captured_at = result.observed_at;
        
        // Count default routes
        for (const auto& route : table.ipv4_routes) {
            if (route.destination_prefix_length == 0) {
                table.default_routes++;
            }
        }
        for (const auto& route : table.ipv6_routes) {
            if (route.destination_prefix_length == 0) {
                table.default_routes++;
            }
        }
        
        auto end_time = std::chrono::steady_clock::now();
        table.capture_duration_ms = std::chrono::duration_cast<std::chrono::milliseconds>(
            end_time - start_time);
        
        // Build result
        result.routes.reserve(table.total_routes);
        result.routes.insert(result.routes.end(), 
                           table.ipv4_routes.begin(), table.ipv4_routes.end());
        result.routes.insert(result.routes.end(),
                           table.ipv6_routes.begin(), table.ipv6_routes.end());
        
        result.table = std::move(table);
        result.total_routes = result.routes.size();
        result.provider_source = "netlink";
        result.status = core::SemanticStatus::kSuccess;
        result.description = "Successfully observed routing table entries";
        
        return result;
    }
    
    RoutingTable get_routing_table() override {
        auto result = observe_routes();
        if (result.table) {
            return *std::move(result.table);
        }
        return RoutingTable{};
    }
    
    std::vector<RouteObservation> find_routes_to(std::string_view destination) override {
        auto table = get_routing_table();
        
        std::vector<RouteObservation> matching;
        
        // Check IPv4 routes
        for (const auto& route : table.ipv4_routes) {
            if (route.destination == destination) {
                matching.push_back(route);
            }
        }
        
        // Check IPv6 routes
        for (const auto& route : table.ipv6_routes) {
            if (route.destination == destination) {
                matching.push_back(route);
            }
        }
        
        return matching;
    }
    
    std::vector<RouteObservation> get_default_routes() override {
        auto table = get_routing_table();
        
        std::vector<RouteObservation> defaults;
        
        // Check IPv4 default routes (0.0.0.0/0)
        for (const auto& route : table.ipv4_routes) {
            if (route.destination_prefix_length == 0 &&
                route.destination.find("0.0.0.0") == 0) {
                defaults.push_back(route);
            }
        }
        
        // Check IPv6 default routes (::/0)
        for (const auto& route : table.ipv6_routes) {
            if (route.destination_prefix_length == 0 &&
                route.destination.find("::") == 0) {
                defaults.push_back(route);
            }
        }
        
        return defaults;
    }
    
    std::optional<RouteObservation> resolve_route(const RouteIdentity& identity) override {
        auto table = get_routing_table();
        
        // Search in IPv4 routes
        for (const auto& route : table.ipv4_routes) {
            if (route.identity == identity) {
                return route;
            }
        }
        
        // Search in IPv6 routes
        for (const auto& route : table.ipv6_routes) {
            if (route.identity == identity) {
                return route;
            }
        }
        
        return std::nullopt;
    }

private:
    // Helper to parse hex string to integer
    static uint32_t parse_hex(const std::string& s) {
        uint32_t result = 0;
        if (!s.empty() && s[0] == '0' && (s[1] == 'x' || s[1] == 'X')) {
            // Already has 0x prefix
            std::istringstream iss(s.substr(2));
            iss >> std::hex >> result;
        } else {
            std::istringstream iss(s);
            iss >> std::hex >> result;
        }
        return result;
    }
    
    // Helper to parse IPv4 from hex
    static std::string ipv4_hex_to_string(uint32_t addr) {
        std::array<uint8_t, 4> bytes;
        for (int i = 0; i < 4; ++i) {
            bytes[i] = (addr >> (i * 8)) & 0xFF;
        }
        
        std::ostringstream oss;
        oss << static_cast<int>(bytes[0]) << "."
            << static_cast<int>(bytes[1]) << "."
            << static_cast<int>(bytes[2]) << "."
            << static_cast<int>(bytes[3]);
        return oss.str();
    }
    
    // Helper to parse CIDR prefix from netmask
    static int parse_prefix_length(uint32_t netmask) {
        if (netmask == 0) return 0;
        
        int count = 0;
        for (int i = 31; i >= 0 && ((netmask >> i) & 1); --i) {
            ++count;
        }
        return count;
    }
};

// ============================================================================
// Factory function
// ============================================================================

std::unique_ptr<RouteDiscoveryAdapter> make_netlink_route_adapter() {
    return std::make_unique<RouteAdapter>();
}

}  // namespace rebuntu::adapters::netlink::route