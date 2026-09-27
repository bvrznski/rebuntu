# Rebuntu Shell — Predicate Dictionary (Phase 6.2)

## Overview

The predicate dictionary defines read-only queries about system state, capability,
identity and conditions. Predicates return three-valued logic: TRUE / FALSE / UNKNOWN.

## Key Distinctions

| Concept | Meaning |
|---------|---------|
| `installed foo` | Package exists in package database (TRUE/FALSE/UNKNOWN) |
| `declared type name` | Entity exists in registry (TRUE/FALSE/UNKNOWN) |
| `running subject id` | Process/service actively executing (TRUE/FALSE/UNKNOWN) |
| `enabled service` | Service enabled for auto-activation (TRUE/FALSE/UNKNOWN) |
| `active service` | Service currently active/online (TRUE/FALSE/UNKNOWN) |

## Predicates

### Package State
- `installed_predicate(package_name)` — Is package installed?

### Entity Declaration  
- `declared_predicate(subject_type, entity_name)` — Is entity defined in registry?
  - subject_type: "service", "user", "group"

### Process/Service Lifecycle
- `running_predicate(subject_type, entity_id)` — Is process/service executing?
- `enabled_predicate(service_name)` — Service enabled for auto-start?
- `disabled_predicate(service_name)` — Service disabled?
- `active_predicate(service_name)` — Service currently active?
- `inactive_predicate(service_name)` — Service inactive?

### Health & Readiness
- `healthy_predicate(service_name)` — Service meets health contract?
- `ready_predicate(service_name)` — Service ready to accept work?

### Filesystem State
- `writable_predicate(path)` — Path accepts writes?
- `readable_predicate(path)` — Path readable?
- `executable_predicate(path)` — Entity executable?
- `mounted_predicate(mount_point)` — Mount point active?

## Usage Pattern

```cpp
#include "rebuntu/shell/predicates.hpp"

// Check if a package is installed
auto result = rebuntu::shell::installed_predicate("nginx");
if (result.is_true.value_or(false)) {
    // Package exists
} else if (result.is_true.has_value()) {
    // Package does not exist
} else {
    // State unknown - check error for details
}
```

## Architecture

```
Predicate Query
    ↓
Native Linux Source (procfs/sysfs/udev/dpkg)
    ↓
Evidence Collection
    ↓
PredicateResult(status=SUCCESS/FAILURE/UNKNOWN, is_true=bool?, evidence=...)
```

## Implementation

- Header: `src/system/shell/predicates.hpp`
- Namespace: `rebuntu::shell`
- Result type: `PredicateResult` with:
  - `status`: core::SemanticStatus (kSuccess/kFailure/kUnknown)
  - `is_true`: std::optional<bool> (true/false/nullopt for unknown)
  - `evidence`: vector of provenance-bearing observations
  - `error`: optional Error details if acquisition failed