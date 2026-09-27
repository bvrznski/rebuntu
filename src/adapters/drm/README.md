# rebuntu::adapters::drm — DRM/KMS Display Topology Observation Adapter (Phase 5.35)

This module implements Rebuntu's display topology observation adapter:

- **Observes**: GPU adapters, CRTCs, connectors, modes
- **Identifies** stable native attributes via sysfs  
- **Tracks provenance and freshness** of observations

## Native Interfaces Used

- `/sys/class/drm/` — Linux kernel DRM subsystem sysfs interface
- Reads from card directories for connector status, type, and EDID data

## Key Distinctions

| Concept | Description |
|---------|-------------|
| GPU adapter | DRM card device (card0, card1, etc.) |
| CRTC | Cathode Ray Tube Controller (display pipe/scanout) |
| Connector | Physical display output (HDMI, DP, LVDS, etc.) |
| Mode | Display resolution and timing configuration |
| Topology | Relationships between GPU → CRTC → Connector → Monitor |

## Architecture

```
DisplayTopologyResult
    └─ GpuAdapterObservation[]
         ├─ card_index (0, 1, ...)
         ├─ card_path ("/dev/dri/card0")
         ├─ crtcs[] (CrtcObservation)
         └─ connectors[] (ConnectorObservation)
              ├─ type (HDMI, DP, LVDS, etc.)
              ├─ connection (connected/disconnected/unknown)
              ├─ supported_modes[] (DisplayMode)
              └─ props (manufacturer, model, EDID info)
```

## Identity Model

- **GPU Adapter**: `card_index` = 0, 1, ... for `/dev/dri/card0`, `/dev/dri/card1`, etc.
- **Connector**: `(card_index, connector_id)` where `connector_id` is DRM's internal ID
- **CRTC**: `(card_index, crtc_id)` where `crtc_id` is DRM's internal ID

## Usage Example

```cpp
#include "adapters/drm/types.hpp"

using namespace rebuntu::adapters::drm;

auto adapter = make_drm_topology_adapter();
auto result = adapter->observe_topology();

if (result.status == core::SemanticStatus::kSuccess) {
    for (const auto& adapter : result.adapters) {
        std::cout << "GPU: " << adapter.card_path << "\n";
        for (const auto& conn : adapter.connectors) {
            if (conn.connection == ConnectionStatus::kConnected) {
                std::cout << "  Connector: " << to_string(conn.type)
                          << " (" << conn.props.model << ")\n";
            }
        }
    }
}
```

## References

- [DRM KMS Documentation](https://dri.freedesktop.org/docs/drm/guide/)
- `man 7 drm-kms` - Kernel Mode Setting
- `man 2 ioctl` - DRM ioctls