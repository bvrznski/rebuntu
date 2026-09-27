# Observation Query Foundation (Phase 5.44)

This directory contains narrow typed queries over live/snapshot observations in Rebuntu's C++-native system.

## Overview

The Observation Query Foundation provides:

1. **Typed Queries** - Type-safe query structures for filtering and aggregating observations
2. **Narrow Interface** - Focused on patterns needed by current components, not a universal SQL-like language
3. **Evidence Preservation** - All queries return provenance-bearing results

## Key Principles

- **QUERY != CONTROL**: Queries observe, they don't mutate
- **DATA != AUTHORITY**: Query results are evidence, not policy decisions
- **UNKNOWN != PASS**: Missing data is not a successful observation
- **BOUNDED**: All queries have time/resource limits to prevent storms

## Architecture

```
ObservationQueryEngine (interface)
    ├── execute_filter()     // Filter observations by criteria
    ├── execute_aggregate()  // Compute aggregates over observations
    └── list_sources()       // List available observation sources

ObservationFilterQuery
    ├── root_expressions: vector<QueryExpression>
    ├── limit: optional<size_t>
    └── sort_by: optional<SortBy>

ObservationAggregateQuery  
    ├── filters: vector<QueryExpression>
    ├── field: ObservationField
    └── function: AggregateFunction
```

## Query Types

### Filter Queries
Filter observations by field-value comparisons:
- Equal, NotEqual
- LessThan, GreaterThan, etc.
- Contains (string matching)
- In/NotIn (set membership)

### Aggregate Queries  
Compute aggregate functions over filtered observation sets:
- Count: Number of matching observations
- Sum/Average/Min/Max: Numeric aggregations

## Fields Available for Querying

- **Timestamp** - Observation timestamp
- **Source** - Source identifier (procfs, systemd, etc.)
- **Identity** - Entity identity string
- **State** - Current state value
- **Status** - Semantic status
- **ResourceUsage** - Resource usage value
- **MemoryKb** - Memory in KB
- **CpuUsageNs** - CPU usage in nanoseconds
- **Subject** - Subject being observed
- **BootId** - Boot context identifier

## Usage Example

```cpp
#include <system/diagnostics/observation/query_types.hpp>

using namespace rebuntu::diagnostics::observation;

// Create a filter query for processes using more than 1GB memory
auto query = ObservationQueryBuilder::make_filter()
    .where_greater_than(ObservationField::kMemoryKb, 1048576)
    .where_equal(ObservationField::kSource, "procfs")
    .limit(100)
    .order_by(ObservationField::kMemoryKb, false) // descending
    .build();

QueryExecutionOptions options;
options.timeout_ms = std::chrono::milliseconds(30000);
options.max_results = 10000;

auto engine = make_observation_query_engine();
auto result = engine->execute_filter(query, options);

if (result.status == core::SemanticStatus::kSuccess) {
    for (const auto& id : result.matching_ids) {
        // Process matching observation IDs
    }
}
```

## Native Linux Integration

Query results ultimately come from native Linux interfaces:
- /procfs for process state
- systemd D-Bus/servicectl for service state  
- journald for log evidence
- sysfs for hardware state

## Related Modules

- `src/system/evidence/collector.hpp` - Evidence collection infrastructure
- `src/system/diagnostics/snapshot/types.hpp` - Snapshot types and storage
- `src/adapters/procfs/process/types.hpp` - Process observation types
- `src/adapters/systemd/service/types.hpp` - Service observation types