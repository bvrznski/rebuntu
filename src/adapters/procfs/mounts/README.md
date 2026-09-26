# rebuntu::adapters::procfs::mounts — Procfs Mounts Observation Adapter

## Overview

This module implements Rebuntu's procfs-based filesystem observation adapter with mount topology support (Phase 5.17 + 5.18).

### Features

#### Phase 5.17: Basic Mount Observation
- Reads mount information from `/proc/self/mountinfo`
- Observes: source identity, target (mountpoint), filesystem type, options
- Supports capacity observation via `statvfs(2)` for mounted filesystems

#### Phase 5.18: Mount Topology Extension
Represents layered mount relationships and bind/overlay/network mounts without flattening them into a misleading disk list.

### Mount Topology Types

| Type | Description |
|------|-------------|
| `kPrimary` | Native mount from block device or remote source |
| `kBind` | Bind mount (mirror of another directory within same filesystem) |
| `kOverlay` | Overlay/union mount (layers multiple directories) |
| `kBindOverlay` | Bind mount of an overlay filesystem |
| `kNetwork` | Network-mounted filesystem (NFS, CIFS, etc.) |
| `kSpecial` | Special in-memory filesystem (tmpfs, proc, sys, devpts, etc.) |

### Data Structures

#### MountIdentity
Stable identity for a mounted filesystem using major:minor device numbers + source path.

#### MountTopologyType
Enum representing how a mount is related to its base filesystem.

#### MountRelationship
Describes the relationship between mounts:
- `parent_mount_id`: Parent in the mount hierarchy
- `base_source`: Actual source filesystem path
- `relationship_type`: Type of relationship (bind, overlay, etc.)
- `overlay_layers`: Layer directories for overlay mounts

#### MountTopology
Complete mount topology graph with:
- All mounts indexed by ID
- Root mount IDs
- Parent-child relationships map
- Statistics by topology type

### Native Interfaces Used

- `/proc/self/mountinfo` — detailed mount table with mount IDs, parent ID, flags
- `statvfs(2)` — filesystem capacity and usage information

### Integration Points

The adapter integrates with:
- Evidence collection system (`rebuntu-evidence-collector`)
- Snapshot service for diagnostic snapshots
- Observer pattern for monitoring mount changes

### Usage Example

```cpp
#include <adapters/procfs/mounts/types.hpp>

using namespace rebuntu::adapters::procfs::mounts;

auto adapter = make_procfs_mounts_adapter();

// Get all mounts with topology
auto result = adapter->observe_mounts();
if (result.status == core::SemanticStatus::kSuccess) {
    // Access raw observations
    for (const auto& mount : result.mounts) {
        std::cout << mount.identity.mountpoint 
                  << " (" << to_string(mount.relationship.relationship_type) << ")\n";
    }
    
    // Get the full topology graph
    if (result.topology) {
        const auto& topo = *result.topology;
        for (const auto& [id, mount] : topo.mounts_by_id) {
            std::cout << "Mount " << id << ": " 
                      << mount.identity.mountpoint << "\n";
        }
    }
}
```

### Provenance Tracking

All observations include:
- `observed_at`: Timestamp of observation
- `source`: Source adapter name ("procfs")
- `provider_source`: Provider identity ("procfs")

### Performance Considerations

- Observation is bounded and cancellable
- Capacity calculation is optional (may fail for some mounts)
- Topology graph construction is O(n) where n = number of mounts