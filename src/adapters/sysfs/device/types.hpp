// rebuntu::adapters::sysfs::device — Sysfs Device Observation Adapter (Phase 7.8)
//
// This module implements Rebuntu's bounded, freshness-aware device observation
// adapter using native Linux sysfs interfaces.
//
// Key Distinctions:
//   - Observation = raw evidence from /sys (source-bound, timestamped)
//   - Fact = derived claim (evaluated, typed, possibly verified)
//   - DeviceIdentity = stable identifier across hotplug cycles
//
// Native Interfaces Used:
//   - /sys/class/ — Linux device model (input, sound, display, block, etc.)
//   - /sys/block/ — Block devices (disk partitions, loop devices)
//   - /sys/bus/ — Bus-specific device information
//   - /sys/devices/ — Device hierarchy and parent-child relationships
//
// Stability Guarantees:
//   - PCI address, serial number, UUID are stable across reboots
//   - /sys paths may change but hardware identifiers remain constant

#pragma once

#include "system/core/contracts.hpp"

#include <chrono>
#include <cstdint>
#include <memory>
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

namespace rebuntu::adapters::sysfs::device {

// ============================================================================
// DeviceKind — Type of device
//
// Represents different categories of devices that can be observed:
//   - kInput: Human input devices (keyboards, mice, touchpads)
//   - kAudio: Audio devices (speakers, microphones, headphones)
//   - kDisplay: Display devices (monitors, projectors, GPUs)
//   - kStorage: Storage devices (disks, partitions, USB drives)
//   - kNetwork: Network interfaces
//   - kOther: Other device types
// ============================================================================
enum class DeviceKind {
    kInput,
    kAudio,
    kDisplay,
    kStorage,
    kNetwork,
    kOther,
};

inline std::string to_string(DeviceKind kind) {
    switch (kind) {
        case DeviceKind::kInput:   return "input";
        case DeviceKind::kAudio:   return "audio";
        case DeviceKind::kDisplay: return "display";
        case DeviceKind::kStorage: return "storage";
        case DeviceKind::kNetwork: return "network";
        case DeviceKind::kOther:   return "other";
    }
    return "unknown";
}

// ============================================================================
// HardwareIdentifier — Stable hardware identifier for a device
//
// A device's stable identity comes from hardware properties that persist
// across reboots, hotplug cycles, and path changes:
//   - pci_address: PCI bus address (e.g., 0000:01:00.0) - unique per slot
//   - serial_number: Device serial number (where available)
//   - uuid: UUID from filesystem or device metadata
//   - wwn: World Wide Name for storage devices
//
// Critical: Identity comparison uses these hardware identifiers, NOT /sys paths.
// ============================================================================
struct HardwareIdentifier {
    // PCI address in standard format (e.g., "0000:01:00.0")
    std::optional<std::string> pci_address;
    
    // Vendor and device IDs for PCIe/PCI devices
    std::optional<uint16_t> vendor_id;
    std::optional<uint16_t> device_id;
    std::optional<uint16_t> subsystem_vendor_id;
    std::optional<uint16_t> subsystem_device_id;
    
    // Hardware serial (where available)
    std::optional<std::string> serial_number;
    
    // UUID/GUID from device metadata
    std::optional<std::string> uuid;
    
    // WWN for storage devices
    std::optional<std::string> wwn;
    
    // Current sysfs path (may change on reconnection)
    std::optional<std::string> sysfs_path;
    
    // Helper: Check if identifier is valid (has at least one stable field)
    bool is_valid() const {
        return pci_address.has_value() ||
               serial_number.has_value() ||
               uuid.has_value() ||
               wwn.has_value();
    }
    
    // Helper: Get a unique key for this device based on available identifiers
    std::string key() const {
        std::string k;
        if (pci_address.has_value()) k += "pci:" + pci_address.value();
        if (serial_number.has_value()) {
            if (!k.empty()) k += ",";
            k += "serial:" + serial_number.value();
        }
        if (uuid.has_value()) {
            if (!k.empty()) k += ",";
            k += "uuid:" + uuid.value();
        }
        return k;
    }
};

// ============================================================================
// DeviceIdentity — Complete identity for a device
//
// Combines hardware identifiers with dynamic information:
//   - HardwareIdentifier: Stable properties from /sys (PCI, serial, UUID)
//   - sysfs_path: Current sysfs path (may change on reconnection)
//   - dev_node: Current device node (e.g., /dev/sda - may change)
//
// DeviceIdentity is used to track the same physical device across
// different observation points.
// ============================================================================
struct DeviceIdentity {
    HardwareIdentifier hw;
    
    // Current sysfs path (for observation only, not for identity comparison)
    std::optional<std::string> sysfs_path;
    
    // Current device node path (may change on reconnection)
    std::optional<std::string> dev_node;
    
    // Bus type (pci, usb, platform, etc.)
    std::optional<std::string> bus_type;
    
    // Helper: Check if identity is valid
    bool is_valid() const {
        return hw.is_valid();
    }
    
    // Helper: Get the stable key for this device
    std::string key() const {
        return hw.key();
    }
};

// ============================================================================
// DeviceState — Current state of a device
//
// Represents the lifecycle and availability state:
//   - kUnknown: State not determined (acquisition failed)
//   - kPresent: Device is present in the system
//   - kAbsent: Device was removed (history preserved for evidence)
//   - kStale: Evidence exists but freshness check failed
// ============================================================================
enum class DeviceState {
    kUnknown,
    kPresent,
    kAbsent,
    kStale,
};

inline std::string to_string(DeviceState state) {
    switch (state) {
        case DeviceState::kUnknown: return "unknown";
        case DeviceState::kPresent: return "present";
        case DeviceState::kAbsent:  return "absent";
        case DeviceState::kStale:   return "stale";
    }
    return "unknown";
}

// ============================================================================
// DeviceObservation — Complete observation of a device at a point in time
//
// Captures all available sysfs properties about a device. This represents
// a SNAPSHOT, not a continuous state.
// ============================================================================
struct DeviceObservation {
    // Stable identity
    DeviceIdentity identity;
    
    // Device kind/category
    DeviceKind kind{DeviceKind::kOther};
    
    // Hardware properties from sysfs
    std::optional<std::string> vendor_name;       // From vendor name files
    std::optional<std::string> product_name;      // From product name files
    std::optional<std::string> model_name;        // Model string
    
    // Driver information
    std::optional<std::string> driver;
    
    // Subsystem (from /sys/class/)
    std::optional<std::string> subsystem;
    
    // Device class/type info
    std::optional<uint32_t> vendor_id;
    std::optional<uint32_t> device_id;
    
    // Physical location
    std::optional<std::string> bus_info;          // Bus-specific address
    
    // Capabilities and features
    std::vector<std::string> capabilities;        // From sysfs attributes
    
    // Provenance tracking
    std::chrono::system_clock::time_point observed_at{};
    core::Evidence evidence;
};

// ============================================================================
// DeviceRecord — Persistent record of a device with history
//
// A DeviceRecord maintains the complete state history of a device:
//   - Current state (present/absent/stale)
//   - Last observation time
//   - First seen timestamp
//   - Observation count for statistics
// ============================================================================
struct DeviceRecord {
    DeviceIdentity identity;
    
    // Current state
    DeviceState state{DeviceState::kUnknown};
    
    // Timestamps
    std::chrono::system_clock::time_point first_seen{};
    std::chrono::system_clock::time_point last_observed{};
    std::optional<std::chrono::system_clock::time_point> removed_at;
    
    // Last observation (for historical reference)
    std::optional<DeviceObservation> last_observation;
    
    // Statistics
    size_t total_observations{0};
};

// ============================================================================
// DeviceDiscoveryResult — Result of device discovery operation
//
// Contains all observations with statistics and timing information.
// ============================================================================
struct DeviceDiscoveryResult {
    core::SemanticStatus status;
    std::string description;
    
    // All observed devices indexed by identity key
    std::unordered_map<std::string, DeviceRecord> device_records;
    
    // Raw observations for evidence collection
    std::vector<DeviceObservation> observations;
    
    // Statistics by kind
    size_t total_devices{0};
    size_t present_devices{0};
    size_t absent_devices{0};
    size_t unknown_state_devices{0};
    
    // Per-kind counts
    size_t input_devices{0};
    size_t audio_devices{0};
    size_t display_devices{0};
    size_t storage_devices{0};
    size_t network_devices{0};
    size_t other_devices{0};
    
    // Provenance tracking
    std::chrono::system_clock::time_point captured_at{};
    std::chrono::milliseconds capture_duration_ms{0};
    
    // Provider provenance
    std::string provider_source{"sysfs"};
    
    // Errors encountered (non-fatal, per-device)
    std::vector<std::pair<std::string, core::Error>> errors;
};

// ============================================================================
// SysfsDeviceOptions — Configuration for sysfs device discovery
//
// Configures discovery behavior and bounds.
// ============================================================================
struct SysfsDeviceOptions {
    // Discovery kinds to monitor
    struct DiscoverKindConfig {
        bool discover_input{true};
        bool discover_audio{true};
        bool discover_display{true};
        bool discover_storage{true};
        bool discover_network{false};  // Network interfaces often managed separately
        bool discover_other{true};
        
        size_t max_devices_per_kind{500};
    } kinds;
    
    // Discovery limits
    size_t max_total_devices{1000};
    std::chrono::milliseconds timeout_ms{std::chrono::seconds(30)};
    
    // Freshness threshold: how long until an observation becomes stale
    std::chrono::milliseconds freshness_threshold_ms{std::chrono::minutes(5)};
    
    static SysfsDeviceOptions make_default() {
        SysfsDeviceOptions opts{};
        opts.kinds.discover_input = true;
        opts.kinds.discover_audio = true;
        opts.kinds.discover_display = true;
        opts.kinds.discover_storage = true;
        opts.kinds.discover_network = false;
        opts.kinds.discover_other = true;
        opts.kinds.max_devices_per_kind = 500;
        opts.max_total_devices = 1000;
        opts.timeout_ms = std::chrono::seconds(30);
        opts.freshness_threshold_ms = std::chrono::minutes(5);
        return opts;
    }
};

// ============================================================================
// SysfsDeviceAdapter — Interface for sysfs device observation
//
// Provides bounded, cancellable device observation from /sys:
//   - discover_devices: One-time scan of current device state
//   - get_all_device_records: Get cached state (may be stale)
//   - resync: Force fresh scan from sysfs
//
// Key Properties:
//   - Bounded: Respects timeout, max_devices limits
//   - Cancellable: Can be interrupted during long operations
//   - Freshness-aware: Tracks observation timestamps and marks stale evidence
//   - Provenance-rich: Records source of each observation
//   - Identity-stable: Uses hardware identifiers for device tracking
// ============================================================================
class SysfsDeviceAdapter {
public:
    virtual ~SysfsDeviceAdapter() = default;
    
    // Perform a one-time scan of current device state
    // Returns all devices currently present in the system
    virtual DeviceDiscoveryResult discover_devices() = 0;
    
    // Get the current cached state of all devices
    // May return stale data - freshness check should be performed by caller
    virtual std::unordered_map<std::string, DeviceRecord> get_all_device_records() = 0;
    
    // Get a specific device record by identity
    virtual std::optional<DeviceRecord> get_device_record(const DeviceIdentity& id) = 0;
    
    // Force a resync of device state from sysfs (clears cache, fresh scan)
    virtual core::Outcome resync_devices() = 0;
    
    // Set discovery options
    virtual void set_options(const SysfsDeviceOptions& opts) = 0;
};

// ============================================================================
// Factory function
// ============================================================================
std::unique_ptr<SysfsDeviceAdapter> make_sysfs_device_adapter();

}  // namespace rebuntu::adapters::sysfs::device

// Hash specialization for DeviceIdentity
namespace std {
template<>
struct hash<rebuntu::adapters::sysfs::device::DeviceIdentity> {
    size_t operator()(const rebuntu::adapters::sysfs::device::DeviceIdentity& id) const noexcept {
        return std::hash<std::string>{}(id.key());
    }
};
}