// rebuntu::adapters::netlink::socket — Netlink Socket/Listener Observation Adapter (Phase 5.23)
//
// This module implements Rebuntu's socket and listener observation adapter:
//   - Observes: listening TCP/UDP ports, connection states, local addresses
//   - Identifies sockets by inode and process association (when available)
//   - Tracks provenance and freshness of observations
//   - Preserves uncertainty about namespace/process association
//
// Native Interfaces Used:
//   - /proc/net/tcp — procfs TCP socket state table
//   - /proc/net/tcp6 — procfs IPv6 TCP socket state table
//   - /proc/net/udp — procfs UDP socket state table
//   - /proc/net/udp6 — procfs IPv6 UDP socket state table
//
// Key Distinctions:
//   - Socket inode = kernel's runtime identifier for a socket
//   - Local address:port = binding location (e.g., "0.0.0.0:22" or "[::]:443")
//   - State = connection state (LISTEN, ESTABLISHED, etc.)
//   - Process association = optional (requires /proc/PID/fd lookup)

#pragma once

#include <system/core/contracts.hpp>
#include <cstdint>
#include <optional>
#include <string>
#include <chrono>
#include <vector>
#include <memory>

namespace rebuntu::adapters::netlink::socket {

// ============================================================================
// SocketFamily — Network socket family
//
// Represents the protocol family of a socket.
// ============================================================================
enum class SocketFamily {
    kUnspecified,  // No family specified
    kInet,         // IPv4 (AF_INET)
    kInet6,        // IPv6 (AF_INET6)
};

inline std::string to_string(SocketFamily f) {
    switch (f) {
        case SocketFamily::kUnspecified: return "unspecified";
        case SocketFamily::kInet:        return "inet";
        case SocketFamily::kInet6:       return "inet6";
    }
    return "unknown";
}

// ============================================================================
// SocketProtocol — Transport protocol
//
// Represents the transport-layer protocol of a socket.
// ============================================================================
enum class SocketProtocol {
    kUnspecified,  // No protocol specified
    kTcp,          // TCP (Transmission Control Protocol)
    kUdp,          // UDP (User Datagram Protocol)
};

inline std::string to_string(SocketProtocol p) {
    switch (p) {
        case SocketProtocol::kUnspecified: return "unspecified";
        case SocketProtocol::kTcp:         return "tcp";
        case SocketProtocol::kUdp:         return "udp";
    }
    return "unknown";
}

// ============================================================================
// SocketState — TCP connection state (for TCP sockets)
//
// Represents the state of a TCP socket. UDP sockets don't have states.
// ============================================================================
enum class SocketState {
    kUnknown,      // State cannot be determined
    kEstablished,  // ESTABLISHED - Connection established
    kSynSent,      // SYN-SENT - Waiting for remote connection confirmation
    kSynRecv,      // SYN-RECV - Waiting for confirmation of our connection request
    kFinWait1,     // FIN-WAIT-1 - Waiting for remote termination
    kFinWait2,     // FIN-WAIT-2 - Ready to receive remote termination
    kTimeWait,     // TIME-WAIT - Connection closed, waiting for remaining packets
    kClosed,       // CLOSED - Socket not in use
    kCloseWait,    // CLOSE-WAIT - Waiting for local user to close
    kLastAck,      // LAST-ACK - Waiting for final confirmation
    kListen,       // LISTEN - Listening for incoming connections
    kClosing,      // CLOSING - Both sides closing simultaneously
};

inline std::string to_string(SocketState s) {
    switch (s) {
        case SocketState::kUnknown:   return "unknown";
        case SocketState::kEstablished: return "established";
        case SocketState::kSynSent:   return "syn-sent";
        case SocketState::kSynRecv:   return "syn-recv";
        case SocketState::kFinWait1:  return "fin-wait-1";
        case SocketState::kFinWait2:  return "fin-wait-2";
        case SocketState::kTimeWait:  return "time-wait";
        case SocketState::kClosed:    return "closed";
        case SocketState::kCloseWait: return "close-wait";
        case SocketState::kLastAck:   return "last-ack";
        case SocketState::kListen:    return "listen";
        case SocketState::kClosing:   return "closing";
    }
    return "unknown";
}

// ============================================================================
// LocalAddress — Local socket binding address
//
// Represents the local IP address and port to which a socket is bound.
// ============================================================================
struct LocalAddress {
    SocketFamily family{SocketFamily::kUnspecified};
    std::string ip;                // Human-readable IP (e.g., "0.0.0.0", "::1")
    uint16_t port{0};              // Port number
};

inline bool operator==(const LocalAddress& a, const LocalAddress& b) {
    return a.family == b.family && a.ip == b.ip && a.port == b.port;
}

// ============================================================================
// SocketIdentity — Stable identity for a socket
//
// A socket is uniquely identified by:
//   - inode = kernel's runtime identifier for the socket
//   - family + protocol = socket type
//   - local_address = binding location
//
// Note: PID/process association is NOT part of identity as it may be unknown.
// ============================================================================
struct SocketIdentity {
    int64_t inode{0};              // Socket inode from /proc/net/*
    SocketFamily family{SocketFamily::kUnspecified};
    SocketProtocol protocol{SocketProtocol::kUnspecified};
};

inline bool operator==(const SocketIdentity& a, const SocketIdentity& b) {
    return a.inode == b.inode &&
           a.family == b.family &&
           a.protocol == b.protocol;
}

// ============================================================================
// SocketObservation — Complete observation of a socket
//
// Represents a single socket with its attributes.
// ============================================================================
struct SocketObservation {
    SocketIdentity identity;
    
    // Local binding information
    LocalAddress local_address;
    
    // For TCP sockets:
    std::optional<std::string> remote_address;  // Remote IP:port for connected sockets
    std::optional<SocketState> state;           // Connection state (nullopt for UDP)
    
    // Process association (if available)
    std::optional<int64_t> process_id;          // PID of process owning socket
    std::optional<std::string> process_name;    // Process name (from /proc/PID/comm)
    
    // Statistics
    uint32_t tx_queue{0};         // Transmit queue size
    uint32_t rx_queue{0};         // Receive queue size
    
    // Provenance tracking
    std::chrono::system_clock::time_point observed_at{};
    std::string source{"procfs"};  // "procfs" for procfs queries
    
    // Flags
    bool is_listening() const {
        return state && *state == SocketState::kListen;
    }
};

// ============================================================================
// SocketCollection — Collected socket observations
//
// Represents a complete snapshot of socket state at a point in time.
// ============================================================================
struct SocketCollection {
    // All sockets organized by family and protocol
    std::vector<SocketObservation> tcp_ipv4;
    std::vector<SocketObservation> tcp_ipv6;
    std::vector<SocketObservation> udp_ipv4;
    std::vector<SocketObservation> udp_ipv6;
    
    // Statistics
    size_t total_sockets{0};
    size_t listening_sockets{0};   // Sockets in LISTEN state
    
    std::chrono::system_clock::time_point captured_at{};
    std::chrono::milliseconds capture_duration_ms{0};
};

// ============================================================================
// SocketObservationResult — Result of socket observation
// ============================================================================
struct SocketObservationResult {
    core::SemanticStatus status;
    std::string description;
    
    // Raw observations (all sockets)
    std::vector<SocketObservation> sockets;
    
    // Collection: organized view
    std::optional<SocketCollection> collection;
    
    // Provenance
    std::chrono::system_clock::time_point observed_at{};
    std::chrono::milliseconds elapsed_ms{0};
    
    size_t total_sockets{0};
    size_t observation_failures{0};  // Number of sockets where observation failed
    
    // Provider provenance - where this data came from
    std::string provider_source{"procfs"};  // Source: "procfs"
    
    std::optional<core::Error> error;
};

// ============================================================================
// SocketDiscoveryAdapter — Interface for socket/listener discovery
//
// This adapter observes sockets via procfs:
//   - Queries TCP/UDP sockets (IPv4 and IPv6)
//   - Identifies listening ports
//   - Tracks process association when available
//   - Preserves uncertainty about namespace/process information
// ============================================================================
class SocketDiscoveryAdapter {
public:
    virtual ~SocketDiscoveryAdapter() = default;
    
    // Observe all sockets
    virtual SocketObservationResult observe_sockets() = 0;
    
    // Get listening sockets (servers waiting for connections)
    virtual std::vector<SocketObservation> get_listening_sockets() = 0;
    
    // Get sockets by protocol and family
    virtual std::vector<SocketObservation> get_tcp_ipv4_sockets() = 0;
    virtual std::vector<SocketObservation> get_tcp_ipv6_sockets() = 0;
    virtual std::vector<SocketObservation> get_udp_ipv4_sockets() = 0;
    virtual std::vector<SocketObservation> get_udp_ipv6_sockets() = 0;
    
    // Find socket by inode
    virtual std::optional<SocketObservation> resolve_by_inode(int64_t inode) = 0;
};

// ============================================================================
// Factory function
// ============================================================================
std::unique_ptr<SocketDiscoveryAdapter> make_socket_discovery_adapter();

}  // namespace rebuntu::adapters::netlink::socket