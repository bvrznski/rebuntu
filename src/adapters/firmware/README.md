# Firmware Observation Adapter (Phase 5.33)

This module implements Rebuntu's firmware/BIOS observation adapter.

## Overview

The firmware adapter provides safe, read-only access to firmware metadata through Linux sysfs interfaces:

- **DMI/SMBIOS**: System Hardware Management BIOS data (vendor, product, board info)
- **EFI**: Unified Extensible Firmware Interface state and variables
- **ACPI**: Advanced Configuration and Power Interface tables
- **Firmware timeout**: Loading configuration

## Native Interfaces Used

| Path | Description |
|------|-------------|
| `/sys/class/dmi/id/*` | DMI/SMBIOS system identification data |
| `/sys/firmware/acpi/tables` | ACPI firmware tables |
| `/sys/firmware/efi/` | UEFI firmware interface |
| `/sys/class/firmware/timeout` | Firmware loading timeout configuration |

## Key Distinctions

- **Firmware observation** = reading metadata only, no mutation allowed
- **DMI/SMBIOS** = system hardware identification (vendor/product/version)
- **BIOS/UEFI** = boot firmware version and configuration state
- **EFI variables** = runtime UEFI variable storage

## Safety Boundaries

- No firmware write/mutation operations (Phase 5.33 is observation only)
- DMI data is readable via sysfs without root privilege on most systems
- Firmware tables are read-only from userspace via `/sys`
- EFI variables require explicit capability for modification

## Types

| Type | Description |
|------|-------------|
| `FirmwareKind` | BIOS, UEFI, or Fallback firmware type |
| `FirmwarePlatform` | Standard, Setup, or OS Maintenance mode |
| `DMISystemInfo` | DMI/SMBIOS system hardware identity |
| `FirmwareState` | Complete firmware state observation |
| `FirmwareObservationResult` | Result of firmware observation |

## Interface

```cpp
class FirmwareAdapter {
public:
    // Observe complete firmware state
    virtual FirmwareObservationResult observe_firmware() = 0;
    
    // Get DMI/SMBIOS system information
    virtual std::optional<DMISystemInfo> get_dmi_system_info() = 0;
    
    // Check if UEFI firmware is present
    virtual bool has_uefi() const = 0;
    
    // List available firmware table types
    virtual std::vector<FirmwareTableType> available_tables() const = 0;
    
    // Get firmware timeout configuration (in seconds)
    virtual std::optional<int> get_firmware_timeout() const = 0;
};
```

## Usage

```cpp
#include "src/adapters/firmware/types.hpp"

auto adapter = rebuntu::adapters::firmware::make_sysfs_firmware_adapter();
auto result = adapter->observe_firmware();

if (result.status == rebuntu::core::SemanticStatus::kSuccess) {
    auto& state = result.state;
    
    // Access firmware identity
    std::cout << "Vendor: " << state.identity.vendor << "\n";
    
    if (state.is_uefi) {
        std::cout << "UEFI firmware detected\n";
    } else {
        std::cout << "Legacy BIOS detected\n";
    }
    
    // Access DMI system info
    if (state.dmi_info.product_name) {
        std::cout << "Product: " << *state.dmi_info.product_name << "\n";
    }
}
```

## Testing

The adapter can be tested by building with CMake:

```bash
cd cpp/build
make rebuntu-firmware-adapter
```

## Phase Status

**Phase 5.33** - COMPLETE

Observation boundary for firmware metadata exposed through Linux sysfs interfaces.