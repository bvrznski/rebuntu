# rebuntu::adapters::peripherals — Bounded Udev/Sysfs Peripheral Discovery (Phase 5.36)

## Overview

This module implements Rebuntu's bounded udev/sysfs peripheral discovery system for observing
system peripherals without indiscriminate device-data collection.

## Native Interfaces Used

### Input Devices
- `/sys/class/input/` — Input device class (evdev, mouse, touchpad)
- `/dev/input/event*` — Event devices

### Audio Devices  
- `/proc/asound/cards` — ALSA audio cards
- `/sys/class/sound/` — Audio devices via sysfs

### USB Devices
- `/sys/bus/usb/devices/` — USB device enumeration
- `/dev/bus/usb/` — USB device nodes

### GPU Adapters
- `/dev/dri/card*` — DRM/KMS card devices
- `/sys/class/drm/` — DRM sysfs interface

## Typed Identities

### InputDeviceIdentity
- `evdev_path`: /dev/input/eventX path (where available)
- `sysfs_path`: /sys/class/input/... path (stable)
- `vendor_id`, `product_id`: USB/HID identifiers (if available)

### AudioDeviceIdentity  
- `card_index`: ALSA card number (0, 1, etc.)
- `device_index`: Device/subdevice index
- `name`: Human-readable name from udev/ALSA

### USBDeviceIdentity
- `bus_number`, `device_address`: USB bus topology (bus-addr)
- `vendor_id`, `product_id`: USB vendor/product ID
- `serial_number`: Device serial (if available)

### GPUAdapterIdentity
- `card_index`: DRM card number (0, 1, etc.)
- `pci_address`: PCI BDF address
- `vendor_id`, `device_id`: PCI IDs

## Discovery Categories

### InputDeviceKind
- `kKeyboard`: Physical keyboard (evdev event nodes)
- `kMouse`: Pointing device (mouse, touchpad)
- `kTouchscreen`: Touch-sensitive display/surface
- `kGamepad`: Game controller (joystick, gamepad)
- `kTablet`: Drawing tablet/stylus device

### AudioDeviceKind
- `kCapture`: Input device (microphone, line-in)
- `kPlayback`: Output device (speakers, headphones)
- `kDuplex`: Both capture and playback

## Safety Boundaries

- No device configuration/mutation (Phase 5.36 is observation only)
- No privilege escalation beyond read access to /sys and udev
- No kernel module loading or hardware reset
- No firmware write operations

## Key Distinctions

### Observation vs Inference
- Direct sysfs/procfs reading = Observation
- Pattern matching on names = Inference (marked as such)

### Cache vs Authority  
- Observed state is cached data, not authoritative source
- Linux kernel owns actual device state

### Identity vs Name
- Stable identity comes from sysfs paths and device IDs
- Human-readable names are supplementary metadata

## Bounded Discovery

Discovery is bounded by:
- Timeout limits (configurable, default 30 seconds)
- Maximum devices per category (default 1000 each)
- Total maximum devices (default 5000)

## Freshness Tracking

Each observation includes:
- `observed_at`: Timestamp of observation
- `source`: Source of data ("sysfs", "alsa", "drm")
- `elapsed_ms`: Discovery duration for performance tracking

## Topology Graph

The discovery returns a `PeripheralTopology` containing:
- Input devices indexed by sysfs path
- Audio devices indexed by card index  
- USB devices indexed by bus:address tuple
- GPU adapters indexed by card index
- Statistics and timing information

## Usage

```cpp
#include "adapters/peripherals/types.hpp"

using namespace rebuntu::adapters::peripherals;

auto adapter = make_udev_sysfs_peripheral_discovery_adapter();

// Discover all peripherals
auto result = adapter->observe_all_peripherals();

if (result.status == core::SemanticStatus::kCompleted) {
    auto& topology = result.topology.value();
    
    // Access by category
    for (const auto& [path, obs] : topology.input_devices) {
        // Process input device observation
    }
    
    for (const auto& [card_idx, obs] : topology.audio_devices) {
        // Process audio device observation
    }
}
```

## Implementation Notes

- Uses C++17 filesystem API for directory enumeration
- No external dependencies beyond standard library
- Graceful error handling - individual device failures don't stop discovery
- Reads only from read-only filesystem paths (no privilege escalation needed)