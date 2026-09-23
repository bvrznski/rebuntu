# Discovery 0018 — Configuration & Specification Grammar

**Date**: 2026-09-22  
**Status**: ACCEPTED  
**Discovery**: Canonical grammar for configuration and specification in Rebuntu  

## Problem Statement

Historical Rebuntu used multiple overlapping terms without clear semantic boundaries.

## Vocabulary Review (per VOCABULARY.md)

### Control/Specification Distinctions
| Term | Meaning |
|------|---------|
| Configuration | Variable spec applied at init ("WITH WHAT") |
| Setup | Installation/environment ("WHERE") |
| Setting | WHETHER an action occurs |
| Option | WHAT alternative to select |
| Preference | HOW work is performed (soft choice) |
| Property | Characteristic OF A DEFINITION |
| Attribute | Characteristic OF AN INSTANCE |
| Policy | Rules describing what MAY/MUST/SHOULD |

## New Architecture Components

### SourceKind: Where configuration comes from
```
kPolicyEnforced > kInvocation > kEnvironment > kUserPreference >
kUserConfig > kHostProfile > kSystemConfig > kDefault
```

### Schema & Configuration: Typed contracts with provenance

```cpp
Schema config_schema;
config_schema.add_field({
    .name = "gpu.primary",
    .type = ValueType::kString,
    .constraint = ConstraintKind::kOptional,
    .default_value = "auto"
});
```

## Implementation Files

| File | Purpose |
|------|---------|
| `cpp/include/system/runtime/config.hpp` | Phase 0.18 configuration grammar |

## Tests
```bash
cmake -B build && cmake --build build
ctest --test-dir build
```
