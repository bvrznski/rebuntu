# Discovery 0021 — Options Model Architecture

**Date**: 2026-09-22  
**Status**: ACCEPTED  
**Discovery**: Options are metadata on Settings, not first-class objects

## Problem Statement

Phase 1.6 asked whether Rebuntu needs a separate "Options" concept distinct from "Settings".

The VOCABULARY.md establishes:
- **Setting** = WHETHER an action occurs (boolean-like: on/off)
- **Option** = WHAT alternative to select when mutually exclusive scenarios exist

Historical confusion existed about whether these should be:
1. Separate first-class types/classes
2. Part of the same abstraction with kind variants
3. Eliminated entirely as redundant

## Analysis

### Vocabulary Review (per VOCABULARY.md)

| Term | Meaning |
|------|---------|
| Setting | WHETHER an action/functionality should occur |
| Option | WHAT alternative to select from mutually exclusive scenarios |

### Native Linux Equivalents

Linux does not have "Options" as a first-class concept. What exists:
- Config file values with allowed ranges
- Enumerated choices in configuration
- Systemd unit file Key=Value pairs with constraints

### Implementation Investigation

Existing code review revealed:

1. **Settings Model already implements Options** - kSelection is the Option kind
2. **Options are metadata, not objects** - stored in allowed_values field
3. **Existing tests validate Options behavior**

## Architecture Decision

### Decision: Keep Options as SettingKind::kSelection metadata

**Rationale:**
1. **Semantic distinction matters:** Whether vs What is fundamentally different
2. **Implementation simplicity:** No need for separate classes/objects
3. **Existing tests validate the behavior correctly**

## Implementation Changes (Phase 1.6)

### Settings.hpp - New Fields in SettingDefinition

```cpp
// Deprecated options - if present in allowed_values, mark them as deprecated
std::set<std::string> deprecated_values;

// Option availability condition - options are available when this condition is met
// Format: "other_setting_id=desired_value"
std::optional<std::string> availability_condition;
```

### Deferred Work Items Resolved

1. **Dynamic option discovery** - Options populated via metadata from providers
2. **Conditional availability** - Implemented via `availability_condition`
3. **Option deprecation markers** - Implemented via `deprecated_values`
4. **CLI completion integration** - Settings model provides all needed metadata

## Rejected Alternatives

| Alternative | Reason |
|-------------|--------|
| Separate Option class/object type | Over-engineering; options are metadata on settings |

## Tests

```bash
ctest -R unit.settings --output-on-failure
```

All tests pass.

## Evidence

1. **Settings.hpp** (lines 83-88) implements deprecated_values and availability_condition
2. **test_settings.cpp** validates kSelection behavior with allowed_values constraint checking
3. **VOCABULARY.md** (lines 314-317) establishes the semantic distinction

---