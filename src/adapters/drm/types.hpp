// rebuntu::adapters::drm — DRM/KMS Display Topology Observation Adapter (Phase 5.35)
//
// This module implements Rebuntu's DRM-based display topology observation adapter:
//   - Observes: GPU adapters, CRTCs, connectors, modes
//   - Identifies stable native attributes via DRM/KMS interfaces
//   - Tracks provenance and freshness of observations
//
// Native Interfaces Used:
//   - /dev/dri/card* — Direct Rendering Manager device nodes
//   - KMS API (DRM_IOCTL_MODE_GETCONNECTOR, etc.) — Display connector enumeration
//
// Key Distinctions:
//   - GPU adapter = DRM card device (card0, card1, etc.)
//   - CRTC = Cathode Ray Tube Controller (display pipe/scanout)
//   - Connector = Physical display output (HDMI, DP, LVDS, etc.)
//   - Mode = Display resolution and timing configuration
//   - Topology = Relationships between GPU -> CRTC -> Connector -> Monitor

#pragma once

#include <system/core/contracts.hpp>
#include <cstdint>
#include <optional>
#include <string>
#include <chrono>
#include <vector>
#include <memory>
#include <unordered_map>

namespace rebuntu::adapters::drm {

// ============================================================================
// ConnectorType — Physical display connector type
//
// Represents the physical interface type of a display connector.
// ============================================================================
enum class ConnectorType {
    kUnknown,       // Type cannot be determined
    kVGA,           // VGA (DE-15)
    kDVI_I,         // DVI-I (Integrated - supports analog and digital)
    kDVI_D,         // DVI-D (Digital only)
    kDVI_A,         // DVI-A (Analog only)
    kComposite,     // Composite video
    kSVideo,        // S-Video
    kLVDS,          // Low-Voltage Differential Signaling (LCD panels)
    kComponent,     // Component video
    kNV12,          // YCrCb 4:2:0
    kHDMI,          // HDMI (Digital audio+video)
    kDPI,           // Display Pixel Interface (MIPI)
    kDisplayPort,   // DisplayPort
    kWWAN,          // Wireless WAN
    kDB_9PinMini,   // DB-9 mini connector
    kRJ45,          // RJ-45 (Ethernet display)
    kEmbedded,      // Embedded DisplayPort (eDP)
    kDSI,           // Mobile Industry Processor Interface DSI
    kUSB,           // USB display interface
};

inline std::string to_string(ConnectorType t) {
    switch (t) {
        case ConnectorType::kUnknown:       return "unknown";
        case ConnectorType::kVGA:           return "vga";
        case ConnectorType::kDVI_I:         return "dvi-i";
        case ConnectorType::kDVI_D:         return "dvi-d";
        case ConnectorType::kDVI_A:         return "dvi-a";
        case ConnectorType::kComposite:     return "composite";
        case ConnectorType::kSVideo:        return "svideo";
        case ConnectorType::kLVDS:          return "lvds";
        case ConnectorType::kComponent:     return "component";
        case ConnectorType::kNV12:          return "nv12";
        case ConnectorType::kHDMI:          return "hdmi";
        case ConnectorType::kDPI:           return "dpi";
        case ConnectorType::kDisplayPort:   return "displayport";
        case ConnectorType::kWWAN:          return "wwan";
        case ConnectorType::kDB_9PinMini:   return "db-9pin-mini";
        case ConnectorType::kRJ45:          return "rj45";
        case ConnectorType::kEmbedded:      return "embedded-displayport";
        case ConnectorType::kDSI:           return "dsi";
        case ConnectorType::kUSB:           return "usb";
    }
    return "unknown";
}

// ============================================================================
// ConnectionStatus — Display connection state
//
// Represents the current connection state of a display connector.
// ============================================================================
enum class ConnectionStatus {
    kConnected,     // Display is physically connected
    kDisconnected,  // Display is not connected
    kUnknown,       // Connection status cannot be determined
};

inline std::string to_string(ConnectionStatus s) {
    switch (s) {
        case ConnectionStatus::kConnected:   return "connected";
        case ConnectionStatus::kDisconnected: return "disconnected";
        case ConnectionStatus::kUnknown:     return "unknown";
    }
    return "unknown";
}

// ============================================================================
// DisplayMode — Display resolution and timing configuration
//
// Represents a display mode (resolution, refresh rate, etc.).
// ============================================================================
struct DisplayMode {
    uint32_t width{0};           // Horizontal resolution in pixels
    uint32_t height{0};          // Vertical resolution in pixels
    uint32_t hdisplay{0};        // Active horizontal pixels
    uint32_t hsync_start{0};     // H sync start
    uint32_t hsync_end{0};       // H sync end
    uint32_t htotal{0};          // Total horizontal pixels
    uint32_t vdisplay{0};        // Active vertical lines
    uint32_t vsync_start{0};     // V sync start
    uint32_t vsync_end{0};       // V sync end
    uint32_t vtotal{0};          // Total vertical lines
    uint32_t clock_khz{0};       // Pixel clock in kHz
    
    double hsync_rate() const {  // Horizontal refresh rate in Hz
        if (htotal == 0 || vtotal == 0) return 0.0;
        return static_cast<double>(clock_khz * 1000) / (htotal * vtotal);
    }
    
    double vsync_rate() const {  // Vertical refresh rate in Hz
        if (vtotal == 0) return 0.0;
        return hsync_rate() / vtotal;
    }
};

inline std::string to_string(const DisplayMode& m) {
    return std::to_string(m.width) + "x" + std::to_string(m.height) +
           "@" + std::to_string(static_cast<int>(m.vsync_rate())) + "Hz";
}

// ============================================================================
// DisplayProperties — Additional connector properties
//
// Extended information about a display connector.
// ============================================================================
struct DisplayProperties {
    std::string manufacturer;     // Monitor manufacturer (EDID)
    std::string model;            // Monitor model (EDID)
    std::string serial_number;    // Monitor serial number (EDID)
    uint32_t width_mm{0};         // Physical width in mm
    uint32_t height_mm{0};        // Physical height in mm
    bool is_primary{false};       // Primary display for desktop
};

// ============================================================================
// ConnectorIdentity — Stable identity for a display connector
//
// A connector is uniquely identified by:
//   - card_index = GPU adapter index (card0=0, card1=1, etc.)
//   - connector_id = DRM's internal connector ID (unique per card)
// ============================================================================
struct ConnectorIdentity {
    int32_t card_index{-1};       // GPU adapter index
    uint32_t connector_id{0};     // DRM connector ID
};

inline bool operator==(const ConnectorIdentity& a, const ConnectorIdentity& b) {
    return a.card_index == b.card_index && a.connector_id == b.connector_id;
}

// ============================================================================
// ConnectorObservation — Complete observation of a display connector
//
// Combines connector attributes, connection status, and mode information.
// ============================================================================
struct ConnectorObservation {
    ConnectorIdentity identity;
    
    ConnectorType type{ConnectorType::kUnknown};
    std::string type_name;      // Raw DRM type name (e.g., "HDMIA", "LVDS")
    
    ConnectionStatus connection{ConnectionStatus::kUnknown};
    std::chrono::system_clock::time_point last_connection_change{};
    
    // Display properties
    DisplayProperties props;
    
    // Supported modes
    std::vector<DisplayMode> supported_modes;
    
    // Current mode (if connected and active)
    std::optional<DisplayMode> current_mode;
    
    // Provenance tracking
    std::chrono::system_clock::time_point observed_at{};
    std::string source{"drm"};  // "drm" for DRM/KMS queries
};

// ============================================================================
// CrtcObservation — Observation of a CRTC (display pipe)
//
// CRTCs represent display pipes that scan out content to connectors.
// ============================================================================
struct CrtcObservation {
    int32_t card_index{-1};
    uint32_t crtc_id{0};  // DRM CRTC ID
    
    std::optional<DisplayMode> mode;        // Current mode if active
    std::vector<uint32_t> connected_connectors;  // Connector IDs driven by this CRTC
    
    bool is_active{false};
};

// ============================================================================
// GpuAdapterObservation — Observation of a GPU adapter (DRM card)
//
// Represents a single DRM card device with its CRTCs and connectors.
// ============================================================================
struct GpuAdapterObservation {
    int32_t card_index{-1};      // Card index (0, 1, etc.)
    std::string card_path;       // Device path (e.g., "/dev/dri/card0")
    
    // CRTC information
    std::vector<CrtcObservation> crtcs;
    
    // Connector information
    std::vector<ConnectorObservation> connectors;
    
    // Statistics
    size_t active_crtcs{0};
    size_t connected_displays{0};
    
    // Provenance
    std::chrono::system_clock::time_point observed_at{};
    std::string source{"drm"};
};

// DisplayTopology — Complete display topology observation
//
// Represents the full GPU->CRTC->Connector->Monitor hierarchy.
// ============================================================================
struct DisplayTopology {
    // All observed GPU adapters
    std::unordered_map<int32_t, GpuAdapterObservation> adapters;
    
    // Connector identity -> observation mapping for quick lookup
    struct IdentityHash {
        size_t operator()(const ConnectorIdentity& id) const {
            return std::hash<int32_t>{}(id.card_index) ^ 
                   (std::hash<uint32_t>{}(id.connector_id) << 1);
        }
    };
    std::unordered_map<ConnectorIdentity, ConnectorObservation, IdentityHash> connector_map;
    
    // Statistics
    size_t total_adapters{0};
    size_t total_connectors{0};
    size_t connected_displays{0};
    size_t active_crtcs{0};
    
    std::chrono::system_clock::time_point captured_at{};
    std::chrono::milliseconds capture_duration_ms{0};
};

// ============================================================================
// DisplayTopologyResult — Result of display topology discovery
// ============================================================================
struct DisplayTopologyResult {
    core::SemanticStatus status;
    std::string description;
    
    // Raw observations (individual GPU adapters)
    std::vector<GpuAdapterObservation> adapters;
    
    // Full topology graph derived from relationships
    std::optional<DisplayTopology> topology;
    
    // Provenance
    std::chrono::system_clock::time_point observed_at{};
    std::chrono::milliseconds elapsed_ms{0};
    
    size_t total_adapters{0};
    size_t total_connectors{0};
    size_t connected_displays{0};
    size_t observation_failures{0};  // Number of adapters where observation failed
    
    // Provider provenance
    std::string provider_source{"drm"};
    
    std::optional<core::Error> error;
};

// DisplayTopologyAdapter — Interface for DRM/KMS display topology observation
//
// This adapter observes display topology via DRM/KMS:
//   - Queries GPU adapters from /dev/dri/card*
//   - Enumerates CRTCs and connectors using KMS ioctls
//   - Reads EDID data for monitor properties
// ============================================================================
class DisplayTopologyAdapter {
public:
    virtual ~DisplayTopologyAdapter() = default;
    
    // Observe all display topology
    virtual DisplayTopologyResult observe_topology() = 0;
    
    // Get the full topology graph
    virtual DisplayTopology get_topology() = 0;
    
    // Resolve a specific GPU adapter by index
    virtual std::optional<GpuAdapterObservation> resolve_adapter(int32_t card_index) = 0;
    
    // Resolve a specific connector by identity
    virtual std::optional<ConnectorObservation> resolve_connector(const ConnectorIdentity& id) = 0;
};

// ============================================================================
// Factory function
// ============================================================================
std::unique_ptr<DisplayTopologyAdapter> make_drm_topology_adapter();

}  // namespace rebuntu::adapters::drm