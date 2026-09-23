# Discovery 0022 — Preferences Model Architecture

**Date**: 2026-09-23  
**Status**: ACCEPTED  
**Discovery**: Preferences are soft choices that may be unsatisfied due to environment/policy/capability constraints

## Problem Statement

Phase 1.7 asked for a canonical grammar for user preferences: soft choices that guide Rebuntu behavior without pretending they are guaranteed system state.

The key distinction is:
- **Preference** = soft choice that may be unsatisfied
- **Policy** = rules describing what MAY/MUST/SHOULD/MUST NOT happen (enforced)
- **State** = authoritative runtime-owned data

## Architecture Decision

### Decision: New Preferences Model as Extension of Settings

**Rationale:**
1. **Semantic distinction matters**: Preferences are softer than settings
2. **Existing infrastructure**: Can reuse settings model structure  
3. **Satisfaction tracking**: Unique to preferences (settings are hard requirements)
4. **Fallback support**: Explicit fallback mechanism for preferences

### Implementation Components

```
cpp/include/system/runtime/preferences.hpp

PreferenceSatisfaction:
  - SATISFIED: preference is satisfied
  - UNSATISFIED: preference cannot be satisfied  
  - NOT_APPLICABLE: preference does not apply in context
  - UNKNOWN: satisfaction status could not be determined

Key Classes:
  - PreferenceDefinition: Typed preference specification
  - PreferenceValue: Concrete value with provenance and satisfaction status
  - PreferencesSchema: Collection of definitions forming a contract
  - PreferencesRegistry: Registry for managing schemas and values
  - PreferencesManager: High-level interface for managing preferences
  - PreferenceEvaluator: Utility for evaluating preference satisfaction
```

## Implementation Changes

### New Files Created

1. `cpp/include/system/runtime/preferences.hpp` — Full implementation (Phase 1.7)
2. `cpp/tests/test_preferences.cpp` — Comprehensive test suite
3. Updated `cpp/tests/CMakeLists.txt` — Added test_preferences executable

## Tests

```bash
cd cpp/Build && ctest -R unit.preferences --output-on-failure
```

Test categories: basic, schema, registry, evaluator, change, integration.

---

## Phase 1.7 Acceptance Criteria

| Criterion | Status |
|-----------|--------|
| Preferences defined as soft choices | ✅ |
| May be unsatisfied due to environment/policy/capability | ✅ |
| Fallback must be explicit and explainable | ✅ |
| Persistence in user-owned configuration | ✅ (Source::kUserConfig) |
| Satisfaction tracking (SATISFIED/UNSATISFIED/NOT_APPLICABLE/UNKNOWN) | ✅ |
| Tests proving meaningful behavior | ✅ |
| Failure-path tests | ✅ |

## Deferred Work

- Native Linux integration (systemd user session, environment.d, XDG config)
- Configuration file parsing/writing for preferences
- Preference precedence resolution across multiple sources
- Audit trail/evidence recording for preference changes
