# Parallel Discovery Infrastructure (Phase 5.51)

## Overview

This module provides bounded parallel discovery utilities for aggregating observations from multiple sources where beneficial.

## Design Principles

- **Parallelize only where independent work benefits from concurrency** - Avoid unbounded thread-per-device patterns
- **Deterministic shutdown with proper cancellation propagation** - Clean resource cleanup on cancel/timeout
- **Bounded concurrency using thread pools** - Fixed worker count prevents resource exhaustion
- **Race-safe aggregation via thread-local results and final merge** - No data races during parallel operations

## Typed Identities for Discovered Entities

Each adapter defines its own observation types with embedded identity information:

```cpp
struct NetworkInterfaceIdentity {
    std::string name;        // Interface name (eth0, wlan0)
    int ifindex;            // Kernel interface index (durable identity)
    std::string mac_address;
};

struct NetworkInterfaceObservation {
    NetworkInterfaceIdentity identity;
    bool is_up;
    std::optional<std::string> ipv4_address;
    std::vector<std::string> ipv6_addresses;
};
```

The parallel engine's template parameter `T` is the observation type, which includes:
- **Typed identity**: A unique durable identifier (ifindex, not interface name)
- **Observation data**: All measured state at discovery time
- **Provenance context**: Timestamp, adapter source

## Key Components

### WorkerPool

A bounded thread pool for parallel task execution with:
- Configurable number of workers (capped at 32)
- Graceful shutdown with proper thread joining
- Task submission via `std::future` for result retrieval

### ParallelAggregator<T>

Thread-safe aggregation container for parallel results:
- Bounded by max_items to prevent unbounded memory growth
- Thread-safe add operations
- Error tracking with index -> error mapping

### ParallelDiscoveryEngine<T>

Main engine for bounded parallel discovery with:
- `execute_parallel()`: Execute discovery on multiple items in parallel chunks
- `execute_sequential()`: Fallback when parallel is not beneficial
- Cancellation support via cooperative flag checking
- Timeout tracking per operation

## Usage Example

```cpp
// Create options
ParallelDiscoveryOptions opts;
opts.max_concurrent = 4;      // Use 4 workers
opts.batch_size = 100;        // Process 100 items per worker
opts.timeout_per_item = std::chrono::milliseconds(500);

// Create engine
auto engine = ParallelDiscoveryEngineFactory::create_default<Item>();

// Execute in parallel
std::vector<Item> items = get_items_to_discover();
auto result = engine->execute_parallel(items, [](const Item& item) {
    return observe_item(item);  // Returns T or DiscoveryResult<T>
});

// Use results
for (const auto& observation : result.observations) {
    process(observation);
}
```

## Cancellation

Cancellation is cooperative:
- Call `request_stop()` to signal cancellation
- Check `is_cancelled()` periodically in long-running operations
- Workers will complete current work before stopping

## Timeout Handling

Timeouts are tracked per operation:
- `overall_timeout` sets maximum duration for the entire discovery
- If exceeded, result status is set to kCancelled or kFailure