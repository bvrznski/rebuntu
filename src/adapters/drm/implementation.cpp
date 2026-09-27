// rebuntu::adapters::drm — DRM/KMS Display Topology Implementation (Phase 5.35)
//
// This module implements Rebuntu's DRM-based display topology observation:
//   - Observes: GPU adapters, CRTCs, connectors, modes
//   - Uses sysfs discovery for compatibility with standard system headers
//   - Tracks provenance and freshness of observations

#include "adapters/drm/types.hpp"

#include <algorithm>
#include <cerrno>
#include <cstring>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>

#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <filesystem>

namespace rebuntu::adapters::drm {

// ============================================================================
// Helper: Parse EDID data for monitor properties
// ============================================================================
static DisplayProperties parse_edid(const std::vector<uint8_t>& edid) {
    DisplayProperties props;
    
    if (edid.size() < 72) {
        return props;  // Not enough data
    }
    
    // Extract manufacturer from bytes 8-9 (3 character code)
    uint16_t manu_id = (static_cast<uint16_t>(edid[8]) << 8) | edid[9];
    
    // Convert manufacturer ID to string
    char manu[4] = {0};
    manu[0] = ((manu_id >> 10) & 0x1F) + 'A' - 1;
    manu[1] = ((manu_id >> 5) & 0x1F) + 'A' - 1;
    manu[2] = (manu_id & 0x1F) + 'A' - 1;
    props.manufacturer = std::string(manu);
    
    // Product code in bytes 10-11
    uint16_t product_code = static_cast<uint16_t>(edid[10]) | (static_cast<uint16_t>(edid[11]) << 8);
    props.model = "Model-" + std::to_string(product_code);
    
    // Serial number in bytes 12-15
    uint32_t serial = static_cast<uint32_t>(edid[12]) | (static_cast<uint32_t>(edid[13]) << 8) |
                     (static_cast<uint32_t>(edid[14]) << 16) | (static_cast<uint32_t>(edid[15]) << 24);
    props.serial_number = std::to_string(serial);
    
    return props;
}

// ============================================================================
// Helper: Convert DRM connector type enum to string
// ============================================================================
static std::string connector_type_to_string(uint32_t type) {
    switch (type) {
        case 0:  return "VGA";
        case 1:  return "DVI-I";
        case 2:  return "DVI-D";
        case 3:  return "DVI-A";
        case 4:  return "Composite";
        case 5:  return "S-Video";
        case 6:  return "LVDS";
        case 7:  return "Component";
        case 8:  return "9PinDIN";
        case 9:  return "DisplayPort";
        case 10: return "HDMIA";
        case 12: return "eDP";
        case 13: return "Virtual";
        case 14: return "DSI";
        default: return "Unknown";
    }
}

// ============================================================================
// Helper: Parse connector type name to our enum
// ============================================================================
static ConnectorType parse_connector_type(const std::string& type_name) {
    if (type_name == "VGA")         return ConnectorType::kVGA;
    if (type_name == "DVI-I" || type_name == "DVI")  return ConnectorType::kDVI_I;
    if (type_name == "DVI-D")       return ConnectorType::kDVI_D;
    if (type_name == "DVI-A")       return ConnectorType::kDVI_A;
    if (type_name == "Composite")   return ConnectorType::kComposite;
    if (type_name == "S-Video")     return ConnectorType::kSVideo;
    if (type_name == "LVDS")        return ConnectorType::kLVDS;
    if (type_name == "Component")   return ConnectorType::kComponent;
    if (type_name == "9PinDIN" || type_name == "DB-9PinMini")  return ConnectorType::kDB_9PinMini;
    if (type_name == "DisplayPort" || type_name == "DP")       return ConnectorType::kDisplayPort;
    if (type_name == "HDMI" || type_name == "HDMIA")           return ConnectorType::kHDMI;
    if (type_name == "eDP" || type_name == "Embedded-DisplayPort")  return ConnectorType::kEmbedded;
    if (type_name == "DSI")         return ConnectorType::kDSI;
    return ConnectorType::kUnknown;
}

// ============================================================================
// Helper: Get connection status from sysfs
// ============================================================================
static ConnectionStatus get_connection_status_from_sysfs(const std::filesystem::path& connector_path) {
    std::filesystem::path path = connector_path / "status";
    
    if (!std::filesystem::exists(path)) {
        return ConnectionStatus::kUnknown;
    }
    
    std::ifstream file(path);
    if (!file.is_open()) {
        return ConnectionStatus::kUnknown;
    }
    
    std::string status;
    std::getline(file, status);
    
    // Trim whitespace
    size_t start = status.find_first_not_of(" \t\r\n");
    size_t end = status.find_last_not_of(" \t\r\n");
    if (start != std::string::npos && end != std::string::npos) {
        status = status.substr(start, end - start + 1);
    }
    
    if (status == "connected")     return ConnectionStatus::kConnected;
    if (status == "disconnected")  return ConnectionStatus::kDisconnected;
    
    return ConnectionStatus::kUnknown;
}

// ============================================================================
// Helper: Get connector type from sysfs directory name
// ============================================================================
static std::string get_connector_type_from_sysfs(const std::filesystem::path& path) {
    std::string name = path.filename().string();
    
    // Look for type prefix in directory name (e.g., "HDMI-A-1", "DP-1")
    if (name.find("VGA") == 0)           return "VGA";
    if (name.find("DVI") == 0)           return "DVI-I";
    if (name.find("HDMI") == 0)          return "HDMI";
    if (name.find("DP") == 0 || name.find("DisplayPort") == 0)  return "DisplayPort";
    if (name.find("LVDS") == 0)          return "LVDS";
    if (name.find("eDP") == 0)           return "eDP";
    if (name.find("DSI") == 0)           return "DSI";
    
    return "";
}

// ============================================================================
// Helper: Read EDID from sysfs
// ============================================================================
static std::vector<uint8_t> read_edid_from_sysfs(const std::filesystem::path& connector_path) {
    std::vector<uint8_t> edid;
    
    // Try to get EDID from the connector's edid file
    std::filesystem::path edid_path = connector_path / "edid";
    if (!std::filesystem::exists(edid_path)) {
        return edid;
    }
    
    std::ifstream file(edid_path, std::ios::binary);
    if (!file.is_open()) {
        return edid;
    }
    
    // EDID is typically 128 bytes
    char buf[128];
    file.read(buf, sizeof(buf));
    size_t bytes_read = file.gcount();
    
    if (bytes_read > 0) {
        edid.assign(buf, buf + bytes_read);
    }
    
    return edid;
}

// ============================================================================
// Helper: Read PCI bus ID from sysfs for a DRM card
// A card's PCI bus location (e.g., "0000:01:00.0") is its durable identity.
// ============================================================================
static std::optional<std::string> read_pci_bus_id_from_card(const std::filesystem::path& card_path) {
    // Try to get PCI bus ID from the device's uevent file
    std::filesystem::path uevent_path = card_path / "device" / "uevent";
    
    if (!std::filesystem::exists(uevent_path)) {
        return std::nullopt;
    }
    
    std::ifstream file(uevent_path);
    if (!file.is_open()) {
        return std::nullopt;
    }
    
    std::string line;
    while (std::getline(file, line)) {
        if (line.starts_with("PCI_SLOT_NAME=")) {
            return line.substr(strlen("PCI_SLOT_NAME="));
        }
    }
    
    return std::nullopt;
}

// ============================================================================
// Helper: Query CRTCs from sysfs
// CRTCs are identified by their parent GPU's PCI bus ID + CRTC ID.
// ============================================================================
static std::vector<CrtcObservation> query_crtcs_from_sysfs(const std::string& pci_bus_id, const std::filesystem::path& card_path) {
    std::vector<CrtcObservation> crtcs;
    
    // CRTC info is available via /sys/class/drm/card*/crtc-*
    std::filesystem::path crtc_path = card_path;
    
    if (!std::filesystem::exists(crtc_path)) {
        return crtcs;
    }
    
    // List all crtc-* directories
    for (const auto& entry : std::filesystem::directory_iterator(crtc_path)) {
        const auto& path = entry.path();
        std::string name = path.filename().string();
        
        if (name.find("crtc-") != 0) continue;
        
        // Extract crtc_id from directory name
        uint32_t crtc_id = static_cast<uint32_t>(std::hash<std::string>{}(name) % 1000);
        
        CrtcObservation obs;
        obs.gpu_pci_bus_id = pci_bus_id;  // Use stable PCI bus ID
        obs.crtc_id = crtc_id;
        
        // Check if this CRTC has a mode (is active)
        std::filesystem::path modes_path = path / "modes";
        if (std::filesystem::exists(modes_path)) {
            std::ifstream file(modes_path);
            if (file.is_open()) {
                obs.is_active = true;
                
                // Get first mode as current
                std::string mode_line;
                if (std::getline(file, mode_line)) {
                    DisplayMode mode;
                    // Parse resolution from mode line (e.g., "1920x1080")
                    size_t x_pos = mode_line.find('x');
                    if (x_pos != std::string::npos) {
                        try {
                            mode.width = std::stoi(mode_line.substr(0, x_pos));
                            mode.height = std::stoi(mode_line.substr(x_pos + 1));
                            mode.hdisplay = mode.width;
                            mode.vdisplay = mode.height;
                            obs.mode = mode;
                        } catch (...) {
                            // Ignore parse errors
                        }
                    }
                }
            }
        }
        
        crtcs.push_back(obs);
    }
    
    return crtcs;
}

// ============================================================================
// Helper: Query connectors from sysfs (fallback when libdrm not available)
// Connectors are identified by GPU's PCI bus ID + connector name.
// ============================================================================
static std::vector<ConnectorObservation> query_connectors_from_sysfs(const std::string& pci_bus_id, const std::filesystem::path& card_path) {
    std::vector<ConnectorObservation> connectors;
    
    if (!std::filesystem::exists(card_path)) {
        return connectors;
    }
    
    for (const auto& entry : std::filesystem::directory_iterator(card_path)) {
        const auto& path = entry.path();
        std::string name = path.filename().string();
        
        // Skip non-connector directories
        if (name.find("crtc-") == 0) continue;
        if (name.find("card") != 0) continue;
        
        ConnectorObservation conn;
        conn.identity.gpu_pci_bus_id = pci_bus_id;  // Use stable PCI bus ID
        conn.identity.connector_name = name;        // Connector name from sysfs
        conn.observed_at = std::chrono::system_clock::now();
        conn.source = "sysfs";
        
        // Get type from directory name
        std::string type_name = get_connector_type_from_sysfs(path);
        if (type_name.empty()) {
            type_name = connector_type_to_string(0);  // Default to VGA if unknown
        }
        conn.type_name = type_name;
        conn.type = parse_connector_type(type_name);
        
        // Get connection status
        conn.connection = get_connection_status_from_sysfs(path.string());
        
        // Read EDID if available
        std::vector<uint8_t> edid_data = read_edid_from_sysfs(path);
        if (!edid_data.empty()) {
            conn.props = parse_edid(edid_data);
        }
        
        connectors.push_back(std::move(conn));
    }
    
    return connectors;
}

// ============================================================================
// DRMTopologyAdapter Implementation (using sysfs discovery with PCI bus IDs)
// ============================================================================

class DRMTopologyAdapter : public DisplayTopologyAdapter {
public:
    DRMTopologyAdapter() = default;
    ~DRMTopologyAdapter() override = default;
    
    DisplayTopologyResult observe_topology() override {
        DisplayTopologyResult result;
        result.observed_at = std::chrono::system_clock::now();
        
        auto start_time = std::chrono::steady_clock::now();
        
        // Find available DRM cards from sysfs
        std::filesystem::path drm_base = "/sys/class/drm";
        
        if (!std::filesystem::exists(drm_base)) {
            result.status = core::SemanticStatus::kUnknown;
            result.description = "No DRM/KMS devices found (sysfs /sys/class/drm not available)";
            return result;
        }
        
        // Collect all card paths with their PCI bus IDs
        std::vector<std::pair<std::filesystem::path, std::string>> cards;
        
        for (const auto& entry : std::filesystem::directory_iterator(drm_base)) {
            const auto& path = entry.path();
            std::string name = path.filename().string();
            
            if (name.find("card") == 0) {
                // Get PCI bus ID from the card's device/uevent file
                auto pci_id = read_pci_bus_id_from_card(path);
                if (pci_id.has_value()) {
                    cards.emplace_back(path, *pci_id);
                }
            }
        }
        
        if (cards.empty()) {
            result.status = core::SemanticStatus::kUnknown;
            result.description = "No DRM card directories found in sysfs";
            return result;
        }
        
        // Observe each adapter using PCI bus ID as stable identity
        for (const auto& [card_path, pci_bus_id] : cards) {
            GpuAdapterObservation adapter;
            adapter.pci_bus_id = pci_bus_id;  // Use stable PCI bus ID as identifier
            adapter.sysfs_path = card_path.string();
            adapter.observed_at = std::chrono::system_clock::now();
            adapter.source = "sysfs";
            
            auto crtcs = query_crtcs_from_sysfs(pci_bus_id, card_path);
            for (const auto& crtc : crtcs) {
                if (crtc.is_active) {
                    adapter.active_crtcs++;
                }
            }
            adapter.crtcs = std::move(crtcs);
            
            auto connectors = query_connectors_from_sysfs(pci_bus_id, card_path);
            for (const auto& conn : connectors) {
                if (conn.connection == ConnectionStatus::kConnected) {
                    adapter.connected_displays++;
                }
            }
            adapter.connectors = std::move(connectors);
            
            result.adapters.push_back(std::move(adapter));
        }
        
        auto end_time = std::chrono::steady_clock::now();
        result.elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(
            end_time - start_time);
        
        // Build final topology using PCI bus ID as key
        DisplayTopology topology;
        topology.captured_at = result.observed_at;
        
        for (const auto& adapter : result.adapters) {
            topology.total_adapters++;
            topology.total_connectors += adapter.connectors.size();
            topology.connected_displays += adapter.connected_displays;
            topology.active_crtcs += adapter.active_crtcs;
            
            // Move adapter to topology using PCI bus ID as key
            topology.adapters[adapter.pci_bus_id] = std::move(adapter);
        }
        
        // Build connector map with stable identifiers (PCI bus ID + connector name)
        for (const auto& adapter : result.adapters) {
            for (const auto& conn : adapter.connectors) {
                topology.connector_map[conn.identity] = conn;
            }
        }
        
        topology.capture_duration_ms = result.elapsed_ms;
        result.topology = topology;
        
        // Use the values already computed in topology
        result.total_adapters = topology.total_adapters;
        result.total_connectors = topology.total_connectors;
        result.connected_displays = topology.connected_displays;
        
        result.provider_source = "sysfs";
        result.status = core::SemanticStatus::kSuccess;
        result.description = "Successfully observed display topology via sysfs";
        
        return result;
    }
    
    DisplayTopology get_topology() override {
        auto result = observe_topology();
        if (result.topology) {
            return *std::move(result.topology);
        }
        return DisplayTopology{};
    }
    
    std::optional<GpuAdapterObservation> resolve_adapter(const std::string& pci_bus_id) override {
        auto topology = get_topology();
        auto it = topology.adapters.find(pci_bus_id);
        if (it != topology.adapters.end()) {
            return it->second;
        }
        return std::nullopt;
    }
    
    std::optional<ConnectorObservation> resolve_connector(const ConnectorIdentity& id) override {
        auto topology = get_topology();
        auto it = topology.connector_map.find(id);
        if (it != topology.connector_map.end()) {
            return it->second;
        }
        return std::nullopt;
    }
};

// ============================================================================
// Factory function
// ============================================================================

std::unique_ptr<DisplayTopologyAdapter> make_drm_topology_adapter() {
    return std::make_unique<DRMTopologyAdapter>();
}

}  // namespace rebuntu::adapters::drm