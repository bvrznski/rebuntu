// rebuntu::adapters::netlink::socket — Netlink Socket/Listener Observation Implementation (Phase 5.23)
//
// This module implements Rebuntu's socket and listener observation adapter:
//   - Observes: listening TCP/UDP ports, connection states, local addresses
//   - Identifies sockets by inode and process association (when available)
//   - Tracks provenance and freshness of observations
//
// Native Interfaces Used:
//   - /proc/net/tcp — procfs TCP socket state table
//   - /proc/net/tcp6 — procfs IPv6 TCP socket state table
//   - /proc/net/udp — procfs UDP socket state table
//   - /proc/net/udp6 — procfs IPv6 UDP socket state table

#include "adapters/netlink/socket/types.hpp"

#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <filesystem>
#include <memory>
#include <unordered_map>

namespace rebuntu::adapters::netlink::socket {

// ============================================================================
// Helper: Parse IPv4 address from hex (e.g., "00000000:C13B")
// ============================================================================
static std::optional<LocalAddress> parse_local_address(std::string_view hex_field) {
    // Format: "IP:PORT" where IP is 8 hex chars for IPv4, 32 hex chars for IPv6
    size_t colon_pos = hex_field.find(':');
    if (colon_pos == std::string::npos) {
        return std::nullopt;
    }
    
    std::string ip_hex(hex_field.substr(0, colon_pos));
    std::string port_hex(hex_field.substr(colon_pos + 1));
    
    // Parse port
    uint32_t port_val = 0;
    std::stringstream ss;
    ss << std::hex << port_hex;
    ss >> port_val;
    uint16_t port = static_cast<uint16_t>(port_val);
    
    // Parse IPv4 address (8 hex chars)
    if (ip_hex.size() == 8) {
        uint32_t ip_val = 0;
        ss.clear();
        ss << std::hex << ip_hex;
        ss >> ip_val;
        
        char buf[16];
        uint8_t bytes[4];
        bytes[0] = ip_val & 0xFF;
        bytes[1] = (ip_val >> 8) & 0xFF;
        bytes[2] = (ip_val >> 16) & 0xFF;
        bytes[3] = (ip_val >> 24) & 0xFF;
        
        snprintf(buf, sizeof(buf), "%d.%d.%d.%d", bytes[0], bytes[1], bytes[2], bytes[3]);
        
        LocalAddress addr;
        addr.family = SocketFamily::kInet;
        addr.ip = buf;
        addr.port = port;
        return addr;
    }
    
    // IPv6 parsing would require more complex handling
    // For now, we skip it if not IPv4
    
    return std::nullopt;
}

// ============================================================================
// Helper: Parse socket state from hex (e.g., "0A" -> LISTEN)
// ============================================================================
static std::optional<SocketState> parse_socket_state(std::string_view hex_state) {
    static const std::unordered_map<std::string, SocketState> state_map = {
        {"01", SocketState::kEstablished},
        {"02", SocketState::kSynSent},
        {"03", SocketState::kSynRecv},
        {"04", SocketState::kFinWait1},
        {"05", SocketState::kFinWait2},
        {"06", SocketState::kTimeWait},
        {"07", SocketState::kClosed},
        {"08", SocketState::kCloseWait},
        {"09", SocketState::kLastAck},
        {"0A", SocketState::kListen},
        {"0B", SocketState::kClosing},
    };
    
    auto it = state_map.find(std::string(hex_state));
    if (it != state_map.end()) {
        return it->second;
    }
    return std::nullopt;
}

// ============================================================================
// Helper: Parse a line from /proc/net/tcp or similar
// ============================================================================
static std::optional<SocketObservation> parse_socket_line(
    const std::string& line,
    SocketFamily family,
    SocketProtocol protocol
) {
    // Format (TCP):
    // sl  local_address rem_address   st tx_queue rx_queue tr tm->when retrnsmt   uid  timeout inode
    // 25: 0100007F:A00D 00000000:0000 0A 00000000:00000000 00:00000000 00000000     0        0 58924 2 0000000000000000 100 0 0 10 0
    
    std::istringstream iss(line);
    std::string sl, local_addr, rem_addr, state_str;
    
    if (!(iss >> sl >> local_addr >> rem_addr >> state_str)) {
        return std::nullopt;
    }
    
    // Parse state
    auto state = parse_socket_state(state_str);
    
    // Parse local address
    auto local_addr_opt = parse_local_address(local_addr);
    if (!local_addr_opt) {
        return std::nullopt;
    }
    
    SocketObservation obs;
    obs.identity.family = family;
    obs.identity.protocol = protocol;
    obs.local_address = *local_addr_opt;
    obs.state = state;
    obs.source = "procfs";
    obs.observed_at = std::chrono::system_clock::now();
    
    // Extract inode (field 14 in the line)
    int field_num = 0;
    std::istringstream line_iss(line);
    std::string token;
    while (line_iss >> token) {
        if (++field_num == 14) {  // inode is the 14th field
            obs.identity.inode = std::stoll(token);
            break;
        }
    }
    
    return obs;
}

// ============================================================================
// Helper: Read and parse /proc/net/tcp or similar file
// ============================================================================
static std::vector<SocketObservation> read_socket_file(
    const std::filesystem::path& path,
    SocketFamily family,
    SocketProtocol protocol
) {
    std::vector<SocketObservation> sockets;
    
    if (!std::filesystem::exists(path)) {
        return sockets;
    }
    
    std::ifstream file(path);
    if (!file.is_open()) {
        return sockets;
    }
    
    std::string line;
    bool first_line = true;
    
    while (std::getline(file, line)) {
        // Skip header line
        if (first_line) {
            first_line = false;
            continue;
        }
        
        // Skip empty lines
        if (line.empty()) continue;
        
        auto obs = parse_socket_line(line, family, protocol);
        if (obs) {
            sockets.push_back(*obs);
        }
    }
    
    return sockets;
}

// ============================================================================
// SocketDiscoveryAdapter Implementation
// ============================================================================

class SocketDiscoveryAdapterImpl : public SocketDiscoveryAdapter {
public:
    SocketDiscoveryAdapterImpl() = default;
    ~SocketDiscoveryAdapterImpl() override = default;
    
    SocketObservationResult observe_sockets() override {
        SocketObservationResult result;
        result.observed_at = std::chrono::system_clock::now();
        
        auto start_time = std::chrono::steady_clock::now();
        
        // Read all socket files
        std::vector<SocketObservation> tcp_v4 = read_socket_file(
            "/proc/net/tcp", SocketFamily::kInet, SocketProtocol::kTcp);
        
        std::vector<SocketObservation> tcp_v6 = read_socket_file(
            "/proc/net/tcp6", SocketFamily::kInet6, SocketProtocol::kTcp);
        
        std::vector<SocketObservation> udp_v4 = read_socket_file(
            "/proc/net/udp", SocketFamily::kInet, SocketProtocol::kUdp);
        
        std::vector<SocketObservation> udp_v6 = read_socket_file(
            "/proc/net/udp6", SocketFamily::kInet6, SocketProtocol::kUdp);
        
        // Combine all sockets
        result.sockets.reserve(tcp_v4.size() + tcp_v6.size() + udp_v4.size() + udp_v6.size());
        result.sockets.insert(result.sockets.end(), tcp_v4.begin(), tcp_v4.end());
        result.sockets.insert(result.sockets.end(), tcp_v6.begin(), tcp_v6.end());
        result.sockets.insert(result.sockets.end(), udp_v4.begin(), udp_v4.end());
        result.sockets.insert(result.sockets.end(), udp_v6.begin(), udp_v6.end());
        
        // Build collection
        SocketCollection collection;
        collection.tcp_ipv4 = std::move(tcp_v4);
        collection.tcp_ipv6 = std::move(tcp_v6);
        collection.udp_ipv4 = std::move(udp_v4);
        collection.udp_ipv6 = std::move(udp_v6);
        
        // Count listening sockets
        for (const auto& sock : result.sockets) {
            if (sock.is_listening()) {
                collection.listening_sockets++;
            }
        }
        
        collection.total_sockets = result.sockets.size();
        collection.captured_at = std::chrono::system_clock::now();
        
        auto end_time = std::chrono::steady_clock::now();
        collection.capture_duration_ms = std::chrono::duration_cast<std::chrono::milliseconds>(
            end_time - start_time);
        
        result.collection = std::move(collection);
        result.total_sockets = result.sockets.size();
        result.provider_source = "procfs";
        result.status = core::SemanticStatus::kSuccess;
        result.description = "Successfully observed sockets";
        
        return result;
    }
    
    std::vector<SocketObservation> get_listening_sockets() override {
        auto result = observe_sockets();
        std::vector<SocketObservation> listening;
        
        for (const auto& sock : result.sockets) {
            if (sock.is_listening()) {
                listening.push_back(sock);
            }
        }
        
        return listening;
    }
    
    std::vector<SocketObservation> get_tcp_ipv4_sockets() override {
        auto collection = observe_sockets().collection;
        if (!collection) return {};
        return collection->tcp_ipv4;
    }
    
    std::vector<SocketObservation> get_tcp_ipv6_sockets() override {
        auto collection = observe_sockets().collection;
        if (!collection) return {};
        return collection->tcp_ipv6;
    }
    
    std::vector<SocketObservation> get_udp_ipv4_sockets() override {
        auto collection = observe_sockets().collection;
        if (!collection) return {};
        return collection->udp_ipv4;
    }
    
    std::vector<SocketObservation> get_udp_ipv6_sockets() override {
        auto collection = observe_sockets().collection;
        if (!collection) return {};
        return collection->udp_ipv6;
    }
    
    std::optional<SocketObservation> resolve_by_inode(int64_t inode) override {
        auto result = observe_sockets();
        
        for (const auto& sock : result.sockets) {
            if (sock.identity.inode == inode) {
                return sock;
            }
        }
        
        return std::nullopt;
    }

private:
    // Build index of sockets by inode
    void build_inode_index() {
        auto result = observe_sockets();
        for (const auto& sock : result.sockets) {
            inode_index_[sock.identity.inode] = sock;
        }
    }
    
    std::unordered_map<int64_t, SocketObservation> inode_index_;
};

// ============================================================================
// Factory function
// ============================================================================

std::unique_ptr<SocketDiscoveryAdapter> make_socket_discovery_adapter() {
    return std::make_unique<SocketDiscoveryAdapterImpl>();
}

}  // namespace rebuntu::adapters::netlink::socket