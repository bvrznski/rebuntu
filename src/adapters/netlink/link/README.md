# rebuntu::adapters::netlink::link — Network Interface Discovery Adapter (Phase 5.21)

## Overview

This module implements Rebuntu's network interface discovery adapter using Linux native mechanisms.

### Native Interfaces Used
- **rtnetlink** (`/proc/net/rtnetlink`) - Linux kernel network interface management protocol
- **sysfs** (`/sys/class/net/`) - Network device attributes and properties
- **iproute2** (via subprocess) - IPv4/IPv6 address discovery

### What It Observes
- Interface name (e.g., "eth0", "wlan0") - NOT durable identity
- Interface index (ifindex) - Kernel's runtime stable identifier
- MAC address - Hardware-based identifier (persistent across reboots)
- Link state (up/down/dormant/unknown)
- IPv4 and IPv6 addresses with CIDR prefixes
- MTU, driver name, interface flags

### Key Distinctions
- **Interface index** = kernel's runtime stable identifier (ifindex) - unique during runtime but changes on reboot
- **MAC address** = hardware-based identifier (persistent across reboots if not changed)
- **Interface name** = "eth0", "wlan0", etc. - NOT durable across reboots or interface renames

## Architecture

```
NetlinkLinkAdapter (implementation)
    ├── observe_interfaces()     // Discover all network interfaces
    ├── get_topology()           // Build relationship topology
    ├── resolve_by_index()       // Lookup by ifindex
    └── resolve_by_name()        // Lookup by name (less reliable)
```

## Usage

```cpp
#include <adapters/netlink/link/types.hpp>
#include <adapters/netlink/link/implementation.hpp>

using namespace rebuntu::adapters::netlink::link;

auto adapter = make_netlink_link_adapter();
auto result = adapter->observe_interfaces();

if (result.status == core::SemanticStatus::kSuccess) {
    for (const auto& iface : result.interfaces) {
        std::cout << "Interface: " << iface.name << "\n";
        std::cout << "  State: " << to_string(iface.state) << "\n";
        std::cout << "  MAC: " << iface.identity.mac_address << "\n";
    }
}
```

## Provenance Tracking

Each observation includes:
- `observed_at` - Timestamp of when the observation was made
- `source` - Source of data ("netlink" for rtnetlink queries)
- `provider_source` - Provider identifier in result

## Topology Support

The adapter builds a topology graph tracking:
- All interfaces indexed by ifindex
- Interface name → ifindex mapping
- Statistics (total, up, down, loopback counts)

## Error Handling

Results include:
- `status` - Semantic outcome (success/failure/unknown)
- `description` - Human-readable explanation
- `error` - Optional detailed error information