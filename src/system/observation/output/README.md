# src/system/observation/output — Machine-Readable Observation Output (Phase 5.61)

## Overview

This module provides machine-readable observation output for inspection commands with explicit schema/versioning where external compatibility matters.

## Key Features

- **Bounded structured output**: Prevents resource exhaustion through record limits and value size bounds
- **Explicit schema/versioning**: Each output includes schema name and version for compatibility
- **Provenance tracking**: Every observation carries source information and timing data
- **Typed identities**: Stable identifiers (not transient properties like PIDs)
- **State dimensions**: Lifecycle, activity, control, readiness, health states properly tracked

## Schema Structure

```json
{
  "$schema": "https://rebuntu.system/schema/observation/v1.json",
  "version": "1.0.0",
  "generated_at": "2026-09-27T...",
  "source": "observation",
  "records": [...]
}
```

## Components

### OutputSchema
Identifies the schema with name, version, and optional JSON Schema URI for validation.

### OutputMetadata
Provides context: when generated, what was covered, source information, bounds applied.

### ObservationValue
Single observation with provenance (source, path, value, timestamp, validation status).

### ObservationRecord
Complete record for one entity: identity, state, attributes, timing, observations.

### OutputGenerator
Interface for generating machine-readable output from observation records.

## Key Distinctions

- **Observation != Inference**: Only native Linux data, no speculation
- **Observation != Recommendation**: Observations are facts, not advice
- **Cache != Authority**: Cached observations include freshness tracking
- **Name != Identity**: Stable identifiers used throughout
- **Path != Identity**: File paths may change; use stable IDs

## Usage

```cpp
#include <system/observation/output/types.hpp>

auto generator = rebuntu::system::observation::output::make_output_generator();

rebuntu::system::observation::output::OutputOptions options;
options.max_records = 1000;

generator->configure(options);

// Add records...
generator->add_record(record);

// Generate JSON output
std::string json = generator->generate();
```

## Design Principles

1. **DATA != CONTROL**: Output never confers authority
2. **No inference or speculation**: Only raw observations from native sources
3. **Bounded size limits**: Prevent resource exhaustion
4. **Versioning ensures compatibility**: Schema version in output header
5. **Provenance tracking**: Every observation carries source and timing