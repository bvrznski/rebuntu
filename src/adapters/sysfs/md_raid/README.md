# adapters / sysfs / md_raid

Software RAID (md) Observation Adapter - Phase 5.20.

## Responsibility

Provides observation of Linux Software RAID (mdadm) arrays using native sysfs interfaces.

## Native Interfaces Used

- `/sys/block/md-X/` - MD device attributes (level, state, disk counts)
- `/proc/mdstat` - Array status information (referenced in code comments)

## Observation Capabilities

### RAID Arrays
- **Array Identity**: Name (md0, md127, etc.), UUID, major:minor numbers
- **RAID Level**: linear, raid0, raid1, raid4, raid5, raid6, raid10
- **Disk Configuration**: Total, active, working, failed, spare disk counts
- **Array State**: inactive, active, degraded, syncing, recovering
- **Member Disks**: Device paths, positions, and health status

### Topology
- Maps device-to-array relationships
- Tracks array statistics (active, degraded, syncing counts)

## Key Distinctions

| Concept | Implementation |
|---------|---------------|
| **RAID Level** | Configuration type from sysfs (not inference) |
| **Array State** | Current operational state (observed directly) |
| **Member Disk** | Individual device participation with health flags |
| **Sync Progress** | Percentage and time remaining (when applicable) |

## Provenance

All observations include:
- Source: `sysfs`
- Timestamp: When observation was captured
- Freshness-aware results (re-reads from sysfs on each call)

## Architecture

```
SysfsMdRaidAdapter (implementation)
    └── MdRaidAdapter (interface)
            ├── observe_arrays() → MdObservationResult
            ├── get_topology() → MdTopology  
            └── resolve_array(name) → optional<MdArrayObservation>
```

## Implementation Notes

- Uses only native Linux interfaces (sysfs, procfs)
- No external dependencies or shell commands
- Deterministic: same input → same output
- Bounded discovery: only reads existing arrays, no configuration changes