# rebuntu::adapters::sysfs::encrypted_storage — Encrypted Storage Observation Adapter

## Overview

This module implements Rebuntu's sysfs-based encrypted storage observation adapter (Phase 5.19).

### Features

- Observes LUKS device-mapper relationships without exposing key material
- Identifies encrypted volumes via UUID prefixes in `/sys/block/dm-X/dm/`
- Maps dm devices to their underlying sources where possible
- Tracks LUKS vs LVM relationships safely

### Native Interfaces Used

- `/sys/block/dm-X/dm/name` — device-mapper device names
- `/sys/block/dm-X/dm/uuid` — device-mapper UUIDs (contains LUKS/LVM info)
- `/dev/mapper` — mapper symlinks (read-only, for name resolution)

### Key Distinctions

| Type | UUID Prefix | Description |
|------|-------------|-------------|
| kLUKS | `CRYPT-LUKS` | LUKS-encrypted volume (cryptsetup) |
| kLVM | `LVM-` | LVM logical volume |

**Important:** UUIDs do NOT contain key material. The `SecretRef != SecretMaterial` principle applies - we observe encrypted device state, not secrets.

## Data Structures

### EncryptedStorageKind
Enum representing the type of encrypted storage entity:
- `kLUKS`: LUKS-encrypted volumes (CRYPT-LUKS* UUID prefix)
- `kLVM`: LVM logical volumes (LVM-* UUID prefix)
- `kOther`: Other device-mapper entities without encryption

### EncryptedStorageObservation
Complete observation of an encrypted storage device combining:
- Device identity (name, uuid, major:minor numbers)
- Encryption type
- LUKS-specific fields (luks_uuid, state)
- LVM-specific fields (vg_name, lv_name)
- Provenance tracking (timestamp, source)

### EncryptedStorageTopology
Relationship topology of encrypted storage:
- All devices indexed by name
- Root encrypted devices (LUKS without LVM on top)
- LVM volume groups with their member LVs
- Statistics (total, luks, lvm, other counts)

## Usage Example

```cpp
#include <adapters/sysfs/encrypted_storage/types.hpp>

using namespace rebuntu::adapters::sysfs::encrypted_storage;

auto adapter = make_sysfs_encrypted_storage_adapter();

// Get all encrypted storage devices
auto result = adapter->observe_devices();
if (result.status == core::SemanticStatus::kSuccess) {
    for (const auto& device : result.devices) {
        std::cout << "Device: " << device.identity.name << "\n";
        std::cout << "  Type: " << to_string(device.kind) << "\n";
        
        if (device.kind == EncryptedStorageKind::kLUKS && device.luks_uuid) {
            std::cout << "  LUKS UUID: " << *device.luks_uuid << "\n";
            if (device.state) {
                std::cout << "  State: " << to_string(*device.state) << "\n";
            }
        }
        
        if (device.kind == EncryptedStorageKind::kLVM) {
            if (device.lvm_vg_name) {
                std::cout << "  VG Name: " << *device.lvm_vg_name << "\n";
            }
            if (device.lvm_lv_name) {
                std::cout << "  LV Name: " << *device.lvm_lv_name << "\n";
            }
        }
    }
}

// Get the full topology
auto topology = adapter->get_topology();
std::cout << "Total devices: " << topology.total_devices << "\n";
std::cout << "LUKS devices: " << topology.luks_devices << "\n";
std::cout << "LVM devices: " << topology.lvm_devices << "\n";
```

## Provenance Tracking

All observations include:
- `observed_at`: Timestamp of observation
- `source`: Source adapter name ("sysfs")
- `provider_source`: Provider identity ("sysfs")

## Security Considerations

- **NO KEY MATERIAL**: UUIDs and device names do not contain encryption keys
- **READ-ONLY**: Only observes existing state, never modifies configuration
- **SecretRef != SecretMaterial**: References to encrypted devices are safe; actual secrets remain protected in kernel/keyring

## Performance Considerations

- Observation is bounded and cancellable
- sysfs reads are lightweight (no disk I/O required)
- Topology graph construction is O(n) where n = number of dm devices