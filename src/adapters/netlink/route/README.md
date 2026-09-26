# rebuntu::adapters::netlink::route — Route Observation Adapter (Phase 5.22)

## Overview

This module implements Rebuntu's route observation adapter using Linux procfs interfaces.

### Native Interfaces Used
- **procfs** (`/proc/net/route`, `/proc/net/ipv6_route`) - Kernel routing table data
- **sysfs** (`/sys/class/net/`) - Interface information for output_ifindex resolution

### What It Observes
- IPv4 and IPv6 route entries in kernel routing tables
- Destination networks with CIDR prefix lengths
- Gateway addresses (next hop)
- Output interface index and name
- Route type (unicast, local, blackhole, etc.)
- Route scope and priority
- Statistics (bytes, packets, calls, errors)

### Key Distinctions
- **Route** = kernel routing table entry for packet forwarding
- **Destination + Prefix** = unique identifier for a route
- **Gateway** = next hop IP address (if applicable)
- **Output Interface** = network interface used to reach destination

## Architecture

```
RouteAdapter (implementation)
    ├── observe_routes()       // Discover all routing table entries
    ├── get_routing_table()    // Get complete routing table
    ├── find_routes_to()       // Find routes to a specific destination
    ├── get_default_routes()   // Get default routes (0.0.0.0/0, ::/0)
    └── resolve_route()        // Lookup by route identity
```

## Usage

```cpp
#include <adapters/netlink/route/types.hpp>
#include <adapters/netlink/route/implementation.hpp>

using namespace rebuntu::adapters::netlink::route;

auto adapter = make_netlink_route_adapter();
auto result = adapter->observe_routes();

if (result.status == core::SemanticStatus::kSuccess) {
    auto table = result.table.value();
    
    std::cout << "IPv4 routes: " << table.ipv4_route_count << "\n";
    std::cout << "IPv6 routes: " << table.ipv6_route_count << "\n";
    
    for (const auto& route : table.ipv4_routes) {
        std::cout << route.destination << "/" << route.destination_prefix_length
                  << " via " << route.gateway.value_or("direct") << "\n";
    }
}
```

## Provenance Tracking

Each observation includes:
- `observed_at` - Timestamp of when the observation was made
- `source` - Source of data ("netlink" for procfs queries)
- `provider_source` - Provider identifier in result

## Error Handling

Results include:
- `status` - Semantic outcome (success/failure/unknown)
- `description` - Human-readable explanation
- `error` - Optional detailed error information

## Performance Notes

- Reading `/proc/net/route` is fast (no kernel calls needed)
- IPv6 route parsing may be slower on systems with many routes
- Route discovery is bounded by procfs read time (<10ms typically)