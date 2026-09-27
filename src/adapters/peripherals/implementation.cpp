// rebuntu::adapters::peripherals — Udev/Sysfs Peripheral Discovery Implementation (Phase 5.36)
//
// This module implements the bounded udev/sysfs peripheral discovery adapter:
//   - Input devices via /sys/class/input/
//   - Audio devices via ALSA/HDA via sysfs/procfs
//   - USB devices via udev enumeration
//   - GPU adapters via DRM/KMS or PCI sysfs

#include "adapters/peripherals/types.hpp"

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <optional>

namespace rebuntu::adapters::peripherals {

// ============================================================================
// Helper: Read a file line by line
// ============================================================================
static std::vector<std::string> read_file_lines(std::filesystem::path path) {
    std::vector<std::string> lines;
    std::ifstream file(path);
    
    if (!file.is_open()) {
        return {};
    }
    
    std::string line;
    while (std::getline(file, line)) {
        if (!line.empty()) {
            lines.push_back(line);
        }
    }
    
    return lines;
}

// ============================================================================
// Helper: Read a single file value
// ============================================================================
static std::optional<std::string> read_file_value(std::filesystem::path path) {
    std::ifstream file(path);
    
    if (!file.is_open()) {
        return std::nullopt;
    }
    
    std::string content((std::istreambuf_iterator<char>(file)),
                        std::istreambuf_iterator<char>());
    
    // Trim whitespace
    size_t start = content.find_first_not_of(" \t\n\r");
    if (start == std::string::npos) return std::nullopt;
    
    size_t end = content.find_last_not_of(" \t\n\r");
    return content.substr(start, end - start + 1);
}

// ============================================================================
// Helper: Parse vendor/product IDs from hex strings
// ============================================================================
static uint16_t parse_hex_id(std::string_view hex_str) {
    try {
        return static_cast<uint16_t>(std::stoul(std::string(hex_str), nullptr, 16));
    } catch (...) {
        return 0;
    }
}

// ============================================================================
// Helper: Get USB bus and address from sysfs path
// ============================================================================
static std::optional<std::pair<uint8_t, uint8_t>> parse_usb_bus_address(
    const std::filesystem::path& sysfs_path) {
    // Example: /sys/bus/usb/devices/1-2.3 -> bus=1, address=2.3
    auto path_str = sysfs_path.string();
    
    // Look for pattern like "devices/N-N.N" or "devices/N-N"
    size_t pos = path_str.find("/devices/");
    if (pos == std::string::npos) {
        return std::nullopt;
    }
    
    std::string device_id = path_str.substr(pos + 9);  // After "/devices/"
    
    // Find the first dash
    size_t dash_pos = device_id.find('-');
    if (dash_pos == std::string::npos) {
        return std::nullopt;
    }
    
    uint8_t bus = static_cast<uint8_t>(std::stoul(device_id.substr(0, dash_pos)));
    
    // Parse address (may have dots for ports)
    std::string addr_str = device_id.substr(dash_pos + 1);
    size_t dot_pos = addr_str.find('.');
    if (dot_pos != std::string::npos) {
        addr_str = addr_str.substr(0, dot_pos);  // Use only the main address
    }
    
    uint8_t address = static_cast<uint8_t>(std::stoul(addr_str));
    
    return {{bus, address}};
}

// ============================================================================
// Discover Input Devices via /sys/class/input/
// ============================================================================
static std::vector<InputDeviceObservation> discover_input_devices() {
    std::vector<InputDeviceObservation> devices;
    
    auto input_class_path = std::filesystem::path("/sys/class/input");
    if (!std::filesystem::exists(input_class_path)) {
        return devices;
    }
    
    try {
        for (const auto& entry : std::filesystem::directory_iterator(input_class_path)) {
            if (!entry.is_directory()) continue;
            
            auto name = entry.path().filename().string();
            if (name.empty()) continue;
            if (name.substr(0, 5) != "event") continue;  // Focus on event devices
            
            InputDeviceObservation obs{};
            obs.identity.sysfs_path = entry.path().string();
            obs.observed_at = std::chrono::system_clock::now();
            obs.source = "sysfs";
            
            // Read device info from uevent or device files
            auto uevent_path = entry.path() / "uevent";
            if (std::filesystem::exists(uevent_path)) {
                auto lines = read_file_lines(uevent_path);
                for (const auto& line : lines) {
                    if (line.starts_with("DEVNAME=")) {
                        obs.identity.evdev_path = "/dev" + line.substr(8);
                    } else if (line.starts_with("MAJOR=")) {
                        try {
                            obs.devnode_major = std::stoi(line.substr(6));
                        } catch (...) {}
                    } else if (line.starts_with("MINOR=")) {
                        try {
                            obs.devnode_minor = std::stoi(line.substr(6));
                        } catch (...) {}
                    }
                }
            }
            
            // Try to determine device type from capabilities
            auto devnode_path = entry.path() / "device" / "id";
            if (std::filesystem::exists(devnode_path)) {
                auto vendor_opt = read_file_value(devnode_path / "vendor");
                auto product_opt = read_file_value(devnode_path / "product");
                
                if (vendor_opt && product_opt) {
                    obs.identity.vendor_id = parse_hex_id(*vendor_opt);
                    obs.identity.product_id = parse_hex_id(*product_opt);
                }
            }
            
            // Try to identify device kind from name or capabilities
            auto evdev_node = entry.path().parent_path() / "device" / "name";
            if (std::filesystem::exists(evdev_node)) {
                auto name_val = read_file_value(evdev_node);
                if (name_val) {
                    obs.identity.name = *name_val;
                    
                    // Try to infer device kind from name
                    std::string name_lower = *name_val;
                    std::transform(name_lower.begin(), name_lower.end(), 
                                   name_lower.begin(), ::tolower);
                    
                    if (name_lower.find("keyboard") != std::string::npos) {
                        obs.kind = InputDeviceKind::kKeyboard;
                    } else if (name_lower.find("mouse") != std::string::npos ||
                               name_lower.find("trackpad") != std::string::npos ||
                               name_lower.find("touchpad") != std::string::npos) {
                        obs.kind = InputDeviceKind::kMouse;
                    } else if (name_lower.find("touchscreen") != std::string::npos) {
                        obs.kind = InputDeviceKind::kTouchscreen;
                    } else if (name_lower.find("gamepad") != std::string::npos ||
                               name_lower.find("joystick") != std::string::npos) {
                        obs.kind = InputDeviceKind::kGamepad;
                    } else if (name_lower.find("tablet") != std::string::npos ||
                               name_lower.find("pen") != std::string::npos) {
                        obs.kind = InputDeviceKind::kTablet;
                    } else {
                        obs.kind = InputDeviceKind::kOther;
                    }
                }
            }
            
            // Get capabilities (EV_KEY, EV_ABS, etc.)
            auto devnode_opt = read_file_value(entry.path() / "device" / "id" / "bustype");
            if (devnode_opt) {
                obs.capabilities.push_back("input:" + *devnode_opt);
            }
            
            // Add to devices list
            devices.push_back(obs);
        }
    } catch (...) {
        // Ignore errors during enumeration
    }
    
    return devices;
}

// ============================================================================
// Discover Audio Devices via ALSA card info
// ============================================================================
static std::vector<AudioDeviceObservation> discover_audio_devices() {
    std::vector<AudioDeviceObservation> devices;
    
    auto alsa_cards_path = std::filesystem::path("/proc/asound/cards");
    if (!std::filesystem::exists(alsa_cards_path)) {
        return devices;
    }
    
    try {
        auto lines = read_file_lines(alsa_cards_path);
        for (const auto& line : lines) {
            // Format: " 0 [PCH            ]: HDA-Intel - HDA Intel PCH"
            if (line.empty() || line[0] != ' ') continue;
            
            size_t colon_pos = line.find(':');
            if (colon_pos == std::string::npos) continue;
            
            // Parse card index
            int32_t card_index = 0;
            try {
                card_index = std::stoi(line.substr(1, 2));
            } catch (...) {
                continue;
            }
            
            AudioDeviceObservation obs{};
            obs.identity.card_index = card_index;
            obs.observed_at = std::chrono::system_clock::now();
            obs.source = "alsa";
            
            // Parse card name
            size_t bracket_start = line.find('[');
            size_t bracket_end = line.find(']');
            if (bracket_start != std::string::npos && bracket_end != std::string::npos) {
                obs.identity.card_name = line.substr(bracket_start + 1, 
                                                     bracket_end - bracket_start - 1);
            }
            
            // Parse driver from description
            size_t driver_pos = colon_pos + 2;
            if (driver_pos < line.length()) {
                std::string desc = line.substr(driver_pos);
                // Extract driver name (first word before space)
                size_t space_pos = desc.find(' ');
                if (space_pos != std::string::npos) {
                    obs.driver = desc.substr(0, space_pos);
                }
            }
            
            devices.push_back(obs);
        }
    } catch (...) {
        // Ignore errors during enumeration
    }
    
    return devices;
}

// ============================================================================
// Discover USB Devices via sysfs /sys/bus/usb/devices/
// ============================================================================
static std::vector<USBDeviceObservation> discover_usb_devices() {
    std::vector<USBDeviceObservation> devices;
    
    auto usb_devices_path = std::filesystem::path("/sys/bus/usb/devices");
    if (!std::filesystem::exists(usb_devices_path)) {
        return devices;
    }
    
    try {
        for (const auto& entry : std::filesystem::directory_iterator(usb_devices_path)) {
            if (!entry.is_directory()) continue;
            
            auto name = entry.path().filename().string();
            if (name.empty() || name[0] == ':') continue;  // Skip non-device directories
            
            USBDeviceObservation obs{};
            obs.identity.bus_number = 0;
            obs.identity.device_address = 0;
            obs.observed_at = std::chrono::system_clock::now();
            obs.source = "sysfs";
            
            // Parse bus and address from path
            auto bus_addr = parse_usb_bus_address(entry.path());
            if (bus_addr) {
                obs.identity.bus_number = bus_addr->first;
                obs.identity.device_address = bus_addr->second;
            }
            
            // Read device descriptors
            auto dev_desc_path = entry.path() / "descriptors";
            if (std::filesystem::exists(dev_desc_path)) {
                std::ifstream desc_file(dev_desc_path, std::ios::binary);
                if (desc_file.is_open()) {
                    // First 18 bytes are device descriptor
                    char buf[18];
                    if (desc_file.read(buf, 18)) {
                        obs.identity.vendor_id = static_cast<uint16_t>(
                            (static_cast<uint8_t>(buf[8]) << 8) | 
                            static_cast<uint8_t>(buf[7]));
                        obs.identity.product_id = static_cast<uint16_t>(
                            (static_cast<uint8_t>(buf[10]) << 8) | 
                            static_cast<uint8_t>(buf[9]));
                        
                        // USB version (BCD format)
                        obs.usb_version = (static_cast<uint8_t>(buf[3]) << 4) |
                                         (static_cast<uint8_t>(buf[2]) & 0x0F);
                    }
                }
            }
            
            // Read vendor/product names from strings
            auto vendor_path = entry.path() / "manufacturer";
            if (std::filesystem::exists(vendor_path)) {
                obs.identity.manufacturer = read_file_value(vendor_path);
            }
            
            auto product_path = entry.path() / "product";
            if (std::filesystem::exists(product_path)) {
                obs.identity.product_name = read_file_value(product_path);
            }
            
            // Read device class info
            auto dev_class_opt = read_file_value(entry.path() / "bDeviceClass");
            if (dev_class_opt) {
                try {
                    uint8_t dev_class = static_cast<uint8_t>(std::stoul(*dev_class_opt, nullptr, 16));
                    obs.device_class.klass = dev_class;
                } catch (...) {}
            }
            
            // Read power properties
            auto max_power_opt = read_file_value(entry.path() / "bMaxPower");
            if (max_power_opt) {
                try {
                    obs.max_power_mA = static_cast<uint16_t>(std::stoul(*max_power_opt));
                } catch (...) {}
            }
            
            devices.push_back(obs);
        }
    } catch (...) {
        // Ignore errors during enumeration
    }
    
    return devices;
}

// ============================================================================
// Discover GPU Adapters via DRM/KMS
// ============================================================================
static std::vector<GPUAdapterObservation> discover_gpu_adapters() {
    std::vector<GPUAdapterObservation> devices;
    
    auto dri_path = std::filesystem::path("/dev/dri");
    if (!std::filesystem::exists(dri_path)) {
        return devices;
    }
    
    try {
        for (const auto& entry : std::filesystem::directory_iterator(dri_path)) {
            if (!entry.is_regular_file()) continue;
            
            auto name = entry.path().filename().string();
            if (name.empty() || name.substr(0, 4) != "card") continue;
            
            GPUAdapterObservation obs{};
            obs.identity.card_index = std::stoi(name.substr(4));
            obs.identity.card_path = entry.path().string();
            obs.observed_at = std::chrono::system_clock::now();
            obs.source = "drm";
            
            // Get sysfs path for this card
            auto sysfs_card_path = std::filesystem::path("/sys/class/drm") / name;
            if (std::filesystem::exists(sysfs_card_path)) {
                auto pci_dev_path = sysfs_card_path / ".." / "device";
                if (std::filesystem::exists(pci_dev_path)) {
                    // Try to read PCI address
                    auto bdf_opt = read_file_value(pci_dev_path / "modalias");
                    if (bdf_opt) {
                        // modalias contains pci:v...d... (vendor:device)
                        size_t v_pos = bdf_opt->find("pci:v");
                        if (v_pos != std::string::npos) {
                            // Parse vendor and device IDs
                            obs.identity.vendor_id = parse_hex_id(bdf_opt->substr(v_pos + 5));
                        }
                    }
                }
                
                // Try to get driver name
                auto driver_link = sysfs_card_path / "device" / "driver";
                if (std::filesystem::exists(driver_link)) {
                    try {
                        auto target = std::filesystem::read_symlink(driver_link);
                        obs.driver_name = target.filename().string();
                    } catch (...) {}
                }
                
                // Count connectors
                size_t connector_count = 0;
                for (const auto& conn_entry : std::filesystem::directory_iterator(sysfs_card_path)) {
                    if (conn_entry.is_directory()) {
                        auto conn_name = conn_entry.path().filename().string();
                        if (conn_name.find("card") != std::string::npos &&
                            (conn_name.find("HDMI") != std::string::npos ||
                             conn_name.find("DP") != std::string::npos ||
                             conn_name.find("eDP") != std::string::npos ||
                             conn_name.find("VGA") != std::string::npos)) {
                            connector_count++;
                        }
                    }
                }
                obs.num_connectors = connector_count;
            }
            
            devices.push_back(obs);
        }
    } catch (...) {
        // Ignore errors during enumeration
    }
    
    return devices;
}

// ============================================================================
// Implementation class
// ============================================================================
class UdevSysfsPeripheralDiscoveryAdapter final : public PeripheralDiscoveryAdapter {
public:
    ~UdevSysfsPeripheralDiscoveryAdapter() override = default;
    
    UdevSysfsPeripheralDiscoveryAdapter() {
        options_ = make_default_options();
    }
    
    // Configure adapter
    void configure(const PeripheralDiscoveryOptions& opts) {
        options_ = opts;
    }
    
    // Observe all peripherals
    PeripheralDiscoveryResult observe_all_peripherals() override {
        PeripheralDiscoveryResult result{};
        result.status = core::SemanticStatus::kCompleted;
        result.observed_at = std::chrono::system_clock::now();
        
        auto start_time = std::chrono::steady_clock::now();
        
        // Discover each category
        result.input_devices = discover_input_devices();
        result.audio_devices = discover_audio_devices();
        result.usb_devices = discover_usb_devices();
        result.gpu_adapters = discover_gpu_adapters();
        
        auto end_time = std::chrono::steady_clock::now();
        result.elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(
            end_time - start_time);
        
        // Build topology
        PeripheralTopology topology{};
        for (const auto& dev : result.input_devices) {
            if (dev.identity.sysfs_path.has_value()) {
                topology.input_devices[dev.identity.sysfs_path.value()] = dev;
            }
        }
        for (const auto& dev : result.audio_devices) {
            topology.audio_devices[dev.identity.card_index] = dev;
        }
        for (const auto& dev : result.usb_devices) {
            uint64_t key = (static_cast<uint64_t>(dev.identity.bus_number) << 8) |
                          static_cast<uint64_t>(dev.identity.device_address);
            topology.usb_devices[key] = dev;
        }
        for (const auto& dev : result.gpu_adapters) {
            topology.gpu_adapters[dev.identity.card_index] = dev;
        }
        
        topology.total_input_devices = result.input_devices.size();
        topology.total_audio_devices = result.audio_devices.size();
        topology.total_usb_devices = result.usb_devices.size();
        topology.total_gpu_adapters = result.gpu_adapters.size();
        topology.captured_at = result.observed_at;
        topology.capture_duration_ms = result.elapsed_ms;
        
        result.topology = topology;
        
        result.total_input_devices = result.input_devices.size();
        result.total_audio_devices = result.audio_devices.size();
        result.total_usb_devices = result.usb_devices.size();
        result.total_gpu_adapters = result.gpu_adapters.size();
        
        return result;
    }
    
    // Get full topology
    PeripheralTopology get_topology() override {
        auto result = observe_all_peripherals();
        if (result.topology.has_value()) {
            return *result.topology;
        }
        return {};
    }
    
    // Discover individual categories
    std::vector<InputDeviceObservation> discover_input_devices() override {
        return ::rebuntu::adapters::peripherals::discover_input_devices();
    }
    
    std::vector<AudioDeviceObservation> discover_audio_devices() override {
        return ::rebuntu::adapters::peripherals::discover_audio_devices();
    }
    
    std::vector<USBDeviceObservation> discover_usb_devices() override {
        return ::rebuntu::adapters::peripherals::discover_usb_devices();
    }
    
    std::vector<GPUAdapterObservation> discover_gpu_adapters() override {
        return ::rebuntu::adapters::peripherals::discover_gpu_adapters();
    }
    
    // Resolve by identity (not implemented for Phase 5.36 - returns nullopt)
    std::optional<InputDeviceObservation> resolve_input_device(
        const InputDeviceIdentity& /*id*/) override {
        return std::nullopt;
    }
    
    std::optional<AudioDeviceObservation> resolve_audio_device(
        const AudioDeviceIdentity& /*id*/) override {
        return std::nullopt;
    }
    
    std::optional<USBDeviceObservation> resolve_usb_device(
        const USBDeviceIdentity& /*id*/) override {
        return std::nullopt;
    }
    
    std::optional<GPUAdapterObservation> resolve_gpu_adapter(
        const GPUAdapterIdentity& /*id*/) override {
        return std::nullopt;
    }
    
private:
    static PeripheralDiscoveryOptions make_default_options() {
        PeripheralDiscoveryOptions opts{};
        opts.kinds.discover_input = true;
        opts.kinds.discover_audio = true;
        opts.kinds.discover_usb = true;
        opts.kinds.discover_gpu = true;
        opts.timeout_ms = std::chrono::milliseconds(30000);
        opts.max_total_devices = 5000;
        opts.include_properties = true;
        opts.include_topology = true;
        return opts;
    }
    
    PeripheralDiscoveryOptions options_;
};

// ============================================================================
// Factory function
// ============================================================================
std::unique_ptr<PeripheralDiscoveryAdapter> make_udev_sysfs_peripheral_discovery_adapter() {
    return std::make_unique<UdevSysfsPeripheralDiscoveryAdapter>();
}

}  // namespace rebuntu::adapters::peripherals