// rebuntu::adapters::peripherals — Bounded Udev/Sysfs Peripheral Discovery (Phase 5.36)
//
// This module implements Rebuntu's bounded udev/sysfs peripheral discovery system:
//   - Observes input devices (keyboards, mice, touchpads) via /sys/class/input/
//   - Observes USB devices via udev properties and sysfs
//   - Observes audio devices via ALSA/HDA via sysfs/procfs
//   - Observes GPU adapters via DRM/KMS (separate adapter) or sysfs PCI
//   - Observes storage controllers via sysfs PCI
//
// Native Interfaces Used:
//   - /sys/class/input/ — Input device class (evdev, mouse, touchpad)
//   - udev enumeration — Device properties and relationships
//   - /sys/class/sound/ — Audio devices (HDA codecs, card0-*)
//   - /sys/bus/pci/devices/ — PCI devices (GPU, storage controllers)
//   - /proc/asound/cards — ALSA audio cards (fallback)
//
// Key Distinctions:
//   - Input device = Human input (keyboard, mouse, touchpad, gamepad)
//   - Audio device = Sound output/input (speakers, microphones, headphones)
//   - USB device = Plug-and-play peripheral via USB bus
//   - GPU adapter = Graphics processing unit (DRM card devices)
//   - Storage controller = Host Bus Adapter (SATA/USB/NVMe controllers)
//
// Safety Boundaries:
//   - No device configuration/mutation (Phase 5.36 is observation only)
//   - No privilege escalation beyond read access to /sys and udev
//   - No kernel module loading or hardware reset

#pragma once

#include <system/core/contracts.hpp>
#include <cstdint>
#include <optional>
#include <string>
#include <chrono>
#include <vector>
#include <memory>
#include <unordered_map>

namespace rebuntu::adapters::peripherals {

// ============================================================================
// InputDeviceKind — Type of input device
//
// Represents different categories of human input devices:
//   - kKeyboard: Physical keyboard (evdev event nodes)
//   -kMouse: Pointing device (mouse, touchpad)
//   - kTouchscreen: Touch-sensitive display/surface
//   - kGamepad: Game controller (joystick, gamepad)
//   - kTablet: Drawing tablet/stylus device
//   - kOther: Other input device type
// ============================================================================
enum class InputDeviceKind {
    kKeyboard,
    kMouse,
    kTouchscreen,
    kGamepad,
    kTablet,
    kOther,
};

inline std::string to_string(InputDeviceKind kind) {
    switch (kind) {
        case InputDeviceKind::kKeyboard:  return "keyboard";
        case InputDeviceKind::kMouse:     return "mouse";
        case InputDeviceKind::kTouchscreen: return "touchscreen";
        case InputDeviceKind::kGamepad:   return "gamepad";
        case InputDeviceKind::kTablet:    return "tablet";
        case InputDeviceKind::kOther:     return "other";
    }
    return "unknown";
}

// ============================================================================
// AudioDeviceKind — Type of audio device
//
// Represents different categories of audio devices:
//   - kCapture: Input device (microphone, line-in)
//   - kPlayback: Output device (speakers, headphones)
//   - kDuplex: Both capture and playback
// ============================================================================
enum class AudioDeviceKind {
    kCapture,
    kPlayback,
    kDuplex,
};

inline std::string to_string(AudioDeviceKind kind) {
    switch (kind) {
        case AudioDeviceKind::kCapture: return "capture";
        case AudioDeviceKind::kPlayback: return "playback";
        case AudioDeviceKind::kDuplex: return "duplex";
    }
    return "unknown";
}

struct USBDeviceClass {
    uint8_t klass{0};
    uint8_t subclass{0};
    uint8_t protocol{0};
    
    std::string description() const {
        switch (klass) {
            case 0x00: return "Interface Specific";
            case 0x03: return "HID (Human Interface Device)";
            case 0x08: return "Mass Storage";
            case 0x09: return "USB Hub";
            case 0x0B: return "Smart Card";
            case 0xDC: return "Diagnostic Device";
            case 0xE0: return "Wireless Controller";
            case 0xFE: return "Application Specific";
            case 0xFF: return "Vendor Specific";
            default:     return "Unknown";
        }
    }
};

inline bool operator==(const USBDeviceClass& a, const USBDeviceClass& b) {
    return a.klass == b.klass && a.subclass == b.subclass && a.protocol == b.protocol;
}

// ============================================================================
// InputDeviceIdentity — Stable identity for an input device
//
// An input device is uniquely identified by:
//   - evdev_path: The /dev/input/eventX path (where available)
//   - sysfs_path: The /sys/class/input/... path (stable)
//   - vendor_id + product_id: USB/HID identifiers (if available)
// ============================================================================
struct InputDeviceIdentity {
    std::optional<std::string> evdev_path;
    std::optional<std::string> sysfs_path;
    std::optional<uint16_t> vendor_id;
    std::optional<uint16_t> product_id;
    std::optional<std::string> name;
    int32_t card_index{-1};
};

inline bool operator==(const InputDeviceIdentity& a, const InputDeviceIdentity& b) {
    return a.evdev_path == b.evdev_path &&
           a.sysfs_path == b.sysfs_path &&
           a.vendor_id == b.vendor_id &&
           a.product_id == b.product_id &&
           a.name == b.name;
}

// ============================================================================
// AudioDeviceIdentity — Stable identity for an audio device
//
// An audio device is uniquely identified by:
//   - card_index: ALSA card number (0, 1, etc.)
//   - device_index: Device number within the card
//   - name: Human-readable name from udev/ALSA
// ============================================================================
struct AudioDeviceIdentity {
    int32_t card_index{-1};
    int32_t device_index{0};
    std::optional<std::string> name;
    std::optional<std::string> card_name;
    
    bool is_capture() const { return kind == AudioDeviceKind::kCapture || 
                                  kind == AudioDeviceKind::kDuplex; }
    bool is_playback() const { return kind == AudioDeviceKind::kPlayback || 
                                   kind == AudioDeviceKind::kDuplex; }
    
    std::string full_id() const {
        if (card_index >= 0) {
            std::string id = "hw:" + std::to_string(card_index);
            if (device_index > 0) {
                id += "," + std::to_string(device_index);
            }
            return id;
        }
        return "unknown";
    }
    
    AudioDeviceKind kind{AudioDeviceKind::kDuplex};
};

inline bool operator==(const AudioDeviceIdentity& a, const AudioDeviceIdentity& b) {
    return a.card_index == b.card_index && 
           a.device_index == b.device_index &&
           a.name == b.name &&
           a.card_name == b.card_name;
}

// ============================================================================
// USBDeviceIdentity — Stable identity for a USB device
//
// A USB device is uniquely identified by:
//   - bus_number + device_address: USB bus topology (bus-addr)
//   - vendor_id + product_id: USB vendor/product ID
//   - serial_number: Device serial (if available)
// ============================================================================
struct USBDeviceIdentity {
    uint8_t bus_number{0};
    uint8_t device_address{0};
    uint16_t vendor_id{0};
    uint16_t product_id{0};
    std::optional<std::string> serial_number;
    std::optional<std::string> manufacturer;
    std::optional<std::string> product_name;
    
    std::string path() const {
        return "/dev/bus/usb/" + std::to_string(bus_number) + "/" + 
               std::to_string(device_address);
    }
};

inline bool operator==(const USBDeviceIdentity& a, const USBDeviceIdentity& b) {
    return a.bus_number == b.bus_number &&
           a.device_address == b.device_address &&
           a.vendor_id == b.vendor_id &&
           a.product_id == b.product_id;
}

// ============================================================================
// GPUAdapterIdentity — Stable identity for a GPU adapter
//
// A GPU is uniquely identified by:
//   - card_index: DRM card number (0, 1, etc.)
//   - pci_address: PCI BDF address (bus:device.function)
//   - vendor + device_id: PCI IDs
// ============================================================================
struct GPUAdapterIdentity {
    int32_t card_index{-1};
    std::optional<std::string> pci_address;
    uint16_t vendor_id{0};
    uint16_t device_id{0};
    std::optional<std::string> card_path;
    
    bool is_integrated() const { return false; }
};

inline bool operator==(const GPUAdapterIdentity& a, const GPUAdapterIdentity& b) {
    return a.card_index == b.card_index &&
           a.pci_address == b.pci_address &&
           a.vendor_id == b.vendor_id &&
           a.device_id == b.device_id;
}

// ============================================================================
// InputDeviceObservation — Complete observation of an input device
//
// Combines evdev, udev, and sysfs information about an input device.
// ============================================================================
struct InputDeviceObservation {
    InputDeviceIdentity identity;
    InputDeviceKind kind{InputDeviceKind::kOther};
    
    // Device properties from udev/sysfs
    std::optional<std::string> sysfs_path;        // /sys/class/input/... path
    std::optional<int32_t> devnode_major;         // Major device number
    std::optional<int32_t> devnode_minor;         // Minor device number
    
    // Input capabilities (from evdev)
    std::vector<std::string> capabilities;        // e.g., "EV_KEY", "EV_ABS"
    
    // Provenance tracking
    std::chrono::system_clock::time_point observed_at{};
    std::string source{"udev"};  // "udev", "sysfs", "evdev"
};

// ============================================================================
// AudioDeviceObservation — Complete observation of an audio device
//
// Combines ALSA, udev, and sysfs information about an audio device.
// ============================================================================
struct AudioDeviceObservation {
    AudioDeviceIdentity identity;
    AudioDeviceKind kind{AudioDeviceKind::kDuplex};
    
    // Card properties from /proc/asound/cards or udev
    std::optional<std::string> card_name;         // Human-readable card name
    std::optional<int32_t> vendor_id;             // Sound card vendor ID
    std::optional<std::string> driver;            // ALSA driver (hda-intel, etc.)
    
    // Device properties from udev
    std::optional<std::string> sysfs_path;
    
    // Stream capabilities
    size_t max_playback_streams{0};
    size_t max_capture_streams{0};
    
    // Provenance tracking
    std::chrono::system_clock::time_point observed_at{};
    std::string source{"alsa"};  // "alsa", "udev"
};

// ============================================================================
// USBDeviceObservation — Complete observation of a USB device
//
// Combines udev and sysfs information about a USB device.
// ============================================================================
struct USBDeviceObservation {
    USBDeviceIdentity identity;
    
    // Device descriptor info
    uint8_t usb_version{0};       // USB version (e.g., 0x0200 for USB 2.0)
    USBDeviceClass device_class;
    
    // Configuration
    uint8_t num_configurations{1};
    std::optional<std::string> speed;  // "480M" (USB 2.0), "5G" (USB 3.0), etc.
    
    // Power properties
    uint16_t max_power_mA{0};      // Maximum power consumption
    
    // Ports and topology
    std::optional<uint8_t> parent_port_number;  // Port on parent hub
    std::optional<std::string> parent_path;
    
    // Provenance tracking
    std::chrono::system_clock::time_point observed_at{};
    std::string source{"udev"};  // "udev", "sysfs"
};

// ============================================================================
// GPUAdapterObservation — Complete observation of a GPU adapter
//
// Combines DRM/KMS and PCI sysfs information about a GPU.
// ============================================================================
struct GPUAdapterObservation {
    GPUAdapterIdentity identity;
    
    // DRM capabilities
    std::optional<std::string> driver_name;       // e.g., "i915", "nvidia", "amdgpu"
    bool has_render_node{false};                  // /dev/dri/renderD*
    bool has_control_node{false};                 // /dev/dri/controlD*
    
    // PCI properties from sysfs
    std::optional<uint32_t> subsystem_vendor_id;
    std::optional<uint32_t> subsystem_device_id;
    
    // Display capabilities (from DRM)
    size_t num_crtcs{0};
    size_t num_connectors{0};
    
    // Memory
    std::optional<size_t> vram_size_bytes;        // VRAM in bytes
    
    // Provenance tracking
    std::chrono::system_clock::time_point observed_at{};
    std::string source{"drm"};  // "drm", "pci-sysfs"
};

// ============================================================================
// PeripheralTopology — Complete peripheral topology graph
//
// Represents all discovered peripherals as a hierarchical graph:
//   - USB buses -> devices -> interfaces
//   - Input devices (evdev, mouse, touchscreen)
//   - Audio cards -> devices
//   - GPU adapters
// ============================================================================
struct PeripheralTopology {
    // All observed input devices indexed by evdev path or sysfs path
    std::unordered_map<std::string, InputDeviceObservation> input_devices;
    
    // All observed audio devices indexed by card index
    std::unordered_map<int32_t, AudioDeviceObservation> audio_devices;
    
    // All observed USB devices indexed by bus:address
    std::unordered_map<uint64_t, USBDeviceObservation> usb_devices;  // key = (bus<<8)|addr
    
    // All observed GPU adapters indexed by card index
    std::unordered_map<int32_t, GPUAdapterObservation> gpu_adapters;
    
    // Statistics
    size_t total_input_devices{0};
    size_t total_audio_devices{0};
    size_t total_usb_devices{0};
    size_t total_gpu_adapters{0};
    
    std::chrono::system_clock::time_point captured_at{};
    std::chrono::milliseconds capture_duration_ms{0};
};

// ============================================================================
// PeripheralDiscoveryResult — Result of peripheral discovery
//
// Contains all discovered peripherals with topology and statistics.
// ============================================================================
struct PeripheralDiscoveryResult {
    core::SemanticStatus status;
    std::string description;
    
    // Raw observations (individual devices)
    std::vector<InputDeviceObservation> input_devices;
    std::vector<AudioDeviceObservation> audio_devices;
    std::vector<USBDeviceObservation> usb_devices;
    std::vector<GPUAdapterObservation> gpu_adapters;
    
    // Full topology graph
    std::optional<PeripheralTopology> topology;
    
    // Provenance tracking
    std::chrono::system_clock::time_point observed_at{};
    std::chrono::milliseconds elapsed_ms{0};
    
    size_t total_input_devices{0};
    size_t total_audio_devices{0};
    size_t total_usb_devices{0};
    size_t total_gpu_adapters{0};
    size_t observation_failures{0};  // Number of devices where observation failed
    
    // Provider provenance
    std::string provider_source{"udev-sysfs"};  // "udev", "sysfs", "drm", etc.
    
    std::optional<rebuntu::core::Error> error;
};

// ============================================================================
// PeripheralDiscoveryOptions — Discovery configuration
//
// Configures what types of peripherals to discover and discovery limits.
// ============================================================================
struct PeripheralDiscoveryOptions {
    struct DiscoveryKindConfig {
        bool discover_input{true};      // Discover input devices
        bool discover_audio{true};      // Discover audio devices
        bool discover_usb{true};        // Discover USB devices
        bool discover_gpu{true};        // Discover GPU adapters
        
        size_t max_devices_per_kind{1000};  // Max devices per category
    } kinds;
    
    std::chrono::milliseconds timeout_ms{30000};  // Total discovery timeout
    size_t max_total_devices{5000};                // Hard limit on total devices
    
    bool include_properties{true};  // Include detailed device properties (udev)
    bool include_topology{true};    // Build full topology graph
};

// ============================================================================
// PeripheralDiscoveryAdapter — Interface for udev/sysfs peripheral discovery
//
// Provides bounded, cancellable discovery of system peripherals:
//   - Input devices via /sys/class/input/ and evdev
//   - Audio devices via ALSA/HDA via sysfs/procfs
//   - USB devices via udev enumeration
//   - GPU adapters via DRM/KMS or PCI sysfs
//
// Key properties:
//   - Bounded: Respects timeout, max_devices limits
//   - Cancellable: Can be interrupted during long discovery
//   - Freshness-aware: Tracks observation timestamps
//   - Provenance-rich: Records source of each observation
// ============================================================================
class PeripheralDiscoveryAdapter {
public:
    virtual ~PeripheralDiscoveryAdapter() = default;
    
    // Observe all peripherals (returns raw observations)
    virtual PeripheralDiscoveryResult observe_all_peripherals() = 0;
    
    // Get the full topology graph
    virtual PeripheralTopology get_topology() = 0;
    
    // Discover input devices only
    virtual std::vector<InputDeviceObservation> discover_input_devices() = 0;
    
    // Discover audio devices only
    virtual std::vector<AudioDeviceObservation> discover_audio_devices() = 0;
    
    // Discover USB devices only
    virtual std::vector<USBDeviceObservation> discover_usb_devices() = 0;
    
    // Discover GPU adapters only
    virtual std::vector<GPUAdapterObservation> discover_gpu_adapters() = 0;
    
    // Resolve a specific device by identity (if available in cache/topology)
    virtual std::optional<InputDeviceObservation> resolve_input_device(
        const InputDeviceIdentity& id) = 0;
    
    virtual std::optional<AudioDeviceObservation> resolve_audio_device(
        const AudioDeviceIdentity& id) = 0;
    
    virtual std::optional<USBDeviceObservation> resolve_usb_device(
        const USBDeviceIdentity& id) = 0;
    
    virtual std::optional<GPUAdapterObservation> resolve_gpu_adapter(
        const GPUAdapterIdentity& id) = 0;
};

// ============================================================================
// Factory function
// ============================================================================
std::unique_ptr<PeripheralDiscoveryAdapter> make_udev_sysfs_peripheral_discovery_adapter();

}  // namespace rebuntu::adapters::peripherals