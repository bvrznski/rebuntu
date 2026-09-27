// rebuntu::adapters::hotplug — Hotplug Device State Management (Phase 5.48)
//
// This module implements Rebuntu's bounded, freshness-aware device state
// tracking system for handling hotplug events and removal races safely.
//
// Key Invariants:
//   - Observation != inference
//   - Cache != authority
//   - MISSING_EVIDENCE != ABSENCE
//   - UNKNOWN != PASS
//   - DATA != CONTROL
//   - MODEL_OUTPUT != FACT
//
// Hotplug Handling:
//   - Device additions: fresh observation from udev/sysfs
//   - Device removals: stale evidence marked as removed, history preserved
//   - Removal races: use freshness timestamps to detect out-of-date state
//
// Native Interfaces Used:
//   - /sys/class/ — Linux device model (input, sound, display, etc.)
//   - udev rules/events — Device lifecycle notifications
//   - procfs — Runtime device state (where available)
//
// Safety Boundaries:
//   - No device configuration/mutation (Phase 5.48 is observation only)
//   - No privilege escalation beyond read access to /sys and udev events
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

namespace rebuntu::adapters::hotplug {

// ============================================================================
// DeviceKind — Type of device
//
// Represents different categories of devices that can be hotplugged:
//   - kInput: Human input devices (keyboards, mice, touchpads)
//   - kAudio: Audio devices (speakers, microphones, headphones)
//   - kDisplay: Display devices (monitors, projectors)
//   - kStorage: Storage devices (USB drives, SD cards)
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
// HotplugEvent — Udev/sysfs hotplug event type
//
// Represents the type of hotplug event received from the kernel/udev:
//   - kAdded: New device appeared
//   - kRemoved: Device disappeared
//   - kChanged: Device properties changed (e.g., capacity, state)
// ============================================================================
enum class HotplugEvent {
    kAdded,
    kRemoved,
    kChanged,
};

inline std::string to_string(HotplugEvent event) {
    switch (event) {
        case HotplugEvent::kAdded:   return "added";
        case HotplugEvent::kRemoved: return "removed";
        case HotplugEvent::kChanged: return "changed";
    }
    return "unknown";
}

// ============================================================================
// DeviceState — Current state of a device
//
// Tracks the lifecycle and availability state of a device:
//   - kUnknown: State not yet determined (acquisition failure)
//   - kPresent: Device is currently present and operational
//   - kRemoved: Device has been removed
//   - kStale: Evidence exists but freshness check failed
// ============================================================================
enum class DeviceState {
    kUnknown,
    kPresent,
    kRemoved,
    kStale,
};

inline std::string to_string(DeviceState state) {
    switch (state) {
        case DeviceState::kUnknown: return "unknown";
        case DeviceState::kPresent: return "present";
        case DeviceState::kRemoved: return "removed";
        case DeviceState::kStale:   return "stale";
    }
    return "unknown";
}

// ============================================================================
// DeviceIdentity — Stable identity for a device
//
// A device is uniquely identified by:
//   - sysfs_path: The /sys/class/... path (stable across hotplug cycles)
//   - udev_path: The /dev/... node path (may change on reconnection)
//   - vendor_id + product_id: Vendor/product identifiers (where available)
//   - serial_number: Device serial (if available)
//
// Critical: Identity must be stable and unique. Path-based identity is
// preferred over name-based as it's more stable across reconnections.
// ============================================================================
struct DeviceIdentity {
    std::optional<std::string> sysfs_path;      // Stable sysfs path
    std::optional<std::string> udev_path;       // Current dev node (may change)
    
    // Hardware identifiers (where available)
    std::optional<uint16_t> vendor_id;
    std::optional<uint16_t> product_id;
    std::optional<uint32_t> serial_number;
    
    // Device kind
    DeviceKind kind{DeviceKind::kOther};
    
    // Helper: Check if identity is valid (has at least one stable identifier)
    bool is_valid() const {
        return sysfs_path.has_value() || udev_path.has_value();
    }
    
    // Helper: Get a unique key for this device
    std::string key() const {
        std::string k;
        if (sysfs_path.has_value()) k += "sys:" + sysfs_path.value();
        if (udev_path.has_value()) {
            if (!k.empty()) k += ",";
            k += "dev:" + udev_path.value();
        }
        return k;
    }
};

inline bool operator==(const DeviceIdentity& a, const DeviceIdentity& b) {
    // Primary comparison by sysfs path (most stable)
    if (a.sysfs_path.has_value() && b.sysfs_path.has_value()) {
        return a.sysfs_path.value() == b.sysfs_path.value();
    }
    
    // Fallback to udev path
    if (a.udev_path.has_value() && b.udev_path.has_value()) {
        return a.udev_path.value() == b.udev_path.value();
    }
    
    // Fall back to hardware identifiers
    return a.vendor_id == b.vendor_id &&
           a.product_id == b.product_id &&
           a.serial_number == b.serial_number;
}

// ============================================================================
// DeviceObservation — Complete observation of a device at a point in time
//
// Combines udev/sysfs information about a device at the moment of observation.
// This represents a SNAPSHOT, not a continuous state.
// ============================================================================
struct DeviceObservation {
    DeviceIdentity identity;
    
    // Hardware properties from sysfs/udev
    std::optional<std::string> manufacturer;       // From udev ID_MANUFACTURER
    std::optional<std::string> product_name;       // From udev ID_PRODUCT
    std::optional<std::string> model;              // Model string
    std::optional<std::string> firmware_version;   // Firmware revision
    
    // Device properties
    std::optional<uint32_t> vendor_id;
    std::optional<uint32_t> product_id;
    
    // Physical location
    std::optional<std::string> bus;                // e.g., "usb", "pci", "platform"
    std::optional<std::string> address;            // Bus-specific address
    
    // Device capabilities (from sysfs)
    std::vector<std::string> capabilities;         // e.g., "input", "storage"
    
    // Provenance tracking
    std::chrono::system_clock::time_point observed_at{};
    std::string source{"hotplug"};  // "hotplug", "sysfs", "udev"
};

// ============================================================================
// DeviceRecord — Persistent record of a device with history
//
// A DeviceRecord maintains the complete state history of a device:
//   - Current state (present/removed/stale)
//   - Last observation time
//   - Removal timestamp (if removed)
//   - Historical observations (bounded for memory efficiency)
//
// This is where we track historical evidence while ensuring stale data
// doesn't appear current. A removed device may remain in records but
// must be marked as kRemoved, not kPresent.
// ============================================================================
struct DeviceRecord {
    DeviceIdentity identity;
    
    // Current state of the device
    DeviceState state{DeviceState::kUnknown};
    
    // Timestamps (epoch microseconds)
    std::chrono::system_clock::time_point first_seen{};
    std::chrono::system_clock::time_point last_observed{};
    std::optional<std::chrono::system_clock::time_point> removed_at;
    
    // Last observation before removal (for historical reference)
    std::optional<DeviceObservation> last_observation;
    
    // Statistics
    size_t total_observations{0};
    size_t hotplug_events_received{0};
};

// ============================================================================
// HotplugResult — Result of a hotplug operation
//
// Contains observations with state, timing, and error information.
// ============================================================================
struct HotplugResult {
    core::SemanticStatus status;
    std::string description;
    
    // Device records indexed by identity key
    std::unordered_map<std::string, DeviceRecord> device_records;
    
    // Raw observations (for evidence collection)
    std::vector<DeviceObservation> observations;
    
    // Statistics
    size_t total_devices{0};
    size_t present_devices{0};
    size_t removed_devices{0};
    size_t stale_devices{0};
    
    // Provenance tracking
    std::chrono::system_clock::time_point captured_at{};
    std::chrono::milliseconds capture_duration_ms{0};
    
    // Provider provenance
    std::string provider_source{"hotplug"};  // "hotplug", "sysfs", "udev"
    
    std::optional<rebuntu::core::Error> error;
};

// ============================================================================
// HotplugOptions — Configuration for hotplug monitoring
//
// Configures discovery behavior and stale detection thresholds.
// ============================================================================
struct HotplugOptions {
    // Freshness threshold: how long until an observation becomes stale
    // If a device hasn't been observed within this window, it's marked kStale
    std::chrono::milliseconds freshness_threshold_ms{std::chrono::minutes(5)};
    
    // Maximum history to retain per device (for debugging/troubleshooting)
    size_t max_history_per_device{10};
    
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
    
    // Hotplug event handling
    bool enable_hotplug_events{true};      // Subscribe to udev hotplug events
    std::chrono::milliseconds event_timeout_ms{std::chrono::seconds(30)};
    
    // Freshness enforcement
    bool enforce_freshness{true};          // Mark stale devices as kStale
    bool preserve_removed_evidence{true};  // Keep removed devices in history
    
    static HotplugOptions make_default() {
        HotplugOptions opts{};
        opts.freshness_threshold_ms = std::chrono::minutes(5);
        opts.max_history_per_device = 10;
        opts.kinds.discover_input = true;
        opts.kinds.discover_audio = true;
        opts.kinds.discover_display = true;
        opts.kinds.discover_storage = true;
        opts.kinds.discover_network = false;
        opts.kinds.discover_other = true;
        opts.kinds.max_devices_per_kind = 500;
        opts.enable_hotplug_events = true;
        opts.event_timeout_ms = std::chrono::seconds(30);
        opts.enforce_freshness = true;
        opts.preserve_removed_evidence = true;
        return opts;
    }
};

// ============================================================================
// HotplugObserver — Interface for hotplug device monitoring
//
// Provides bounded, cancellable monitoring of device hotplug events:
//   - Device additions: fresh observation from udev/sysfs
//   - Device removals: stale evidence marked as removed, history preserved
//   - Removal races: freshness timestamps detect out-of-date state
//
// Key Properties:
//   - Bounded: Respects timeout, max_devices limits
//   - Cancellable: Can be interrupted during long operations
//   - Freshness-aware: Tracks observation timestamps and marks stale evidence
//   - Provenance-rich: Records source of each observation
//   - Removal-safe: Removed devices are marked as such, not silently dropped
//
// Thread Safety:
//   This interface is designed for single-threaded use. For multi-threaded
//   scenarios, the caller must provide external synchronization.
// ============================================================================
class HotplugObserver {
public:
    virtual ~HotplugObserver() = default;
    
    // Start monitoring hotplug events
    virtual core::Outcome start() = 0;
    
    // Stop monitoring and clean up
    virtual core::Outcome stop() = 0;
    
    // Check if monitoring is active
    virtual bool is_running() const = 0;
    
    // Perform a one-time scan of current device state (no hotplug events)
    virtual HotplugResult discover_devices() = 0;
    
    // Get the current state of all devices (cached, may be stale)
    virtual std::unordered_map<std::string, DeviceRecord> get_all_device_records() = 0;
    
    // Get a specific device record by identity
    virtual std::optional<DeviceRecord> get_device_record(const DeviceIdentity& id) = 0;
    
    // Force a resync of device state from udev/sysfs
    virtual core::Outcome resync_devices() = 0;
    
    // Get monitoring metrics
    struct Metrics {
        size_t devices_observed{0};
        size_t hotplug_events_received{0};
        size_t devices_added{0};
        size_t devices_removed{0};
        std::chrono::system_clock::time_point started_at{};
        std::optional<std::chrono::system_clock::time_point> last_resync;
    };
    
    virtual Metrics metrics() const = 0;
};

// ============================================================================
// Factory function
// ============================================================================
std::unique_ptr<HotplugObserver> make_hotplug_observer();

}  // namespace rebuntu::adapters::hotplug