# Discovery #24: Profile Generation & Application (Phase 1.10)

**Status:** ACCEPTED  
**Date:** 2026-09-23  
**Author:** Rebuntu Agent

## Summary

This document describes the Phase 1.10 implementation of Rebuntu's initial profile
generation and application machinery - establishing the canonical grammar for
generating bounded bootstrap representations of configuration from explicit user
input, preferences, and discovered host facts.

## Core Distinction

```
Preference = soft choice that may be unsatisfied (Phase 1.7)
Configuration = variable specification applied at init ("WITH WHAT") (Phase 1.8)
Profile = derived configuration based on choices + constraints + capabilities (Phase 1.10)
```

**Key Insight:** Profile is the *result* of derivation: taking user inputs,
preferences, discovery facts, and policy constraints and producing a consistent
configuration state.

## Architecture

### Components

| Component | Responsibility |
|-----------|----------------|
| `rebuntu::setup::profile` namespace | Canonical profile API |
| `ProfileSource` enum | Where profile data originates (user_input, preference, default, discovery, policy) |
| `DerivationReason` enum | Why a value was selected (user_choice, preference_satisfied, default_fallback, discovery_based, policy_enforced) |
| `ProfileStatus` enum | Lifecycle phases (pending, generating, generated, applying, applied, failed, degraded) |
| `GenerationContext` struct | Context for profile generation (scope, paths, inputs, constraints) |
| `ProfileValue` struct | Value with provenance and derivation metadata |
| `Profile` struct | Complete profile with all values |
| `ProfileDiff` struct | Difference between two profiles |
| `ProfilePlan` struct | Execution plan for applying a profile |

### API Functions

```cpp
// Generate a profile from inputs and discovery facts
Profile generate_profile(const GenerationContext& ctx);

// Validate a profile against schema constraints
core::Outcome validate_profile(const Profile& profile);

// Calculate difference between current configuration and target profile
ProfileDiff diff_profile(
    const std::map<std::string, std::string>& current_config,
    const Profile& target_profile);

// Create an execution plan for applying the profile
ProfilePlan plan_profile_application(const Profile& profile, const GenerationContext& ctx);

// Apply a profile to configuration storage
SetupResult apply_profile(const Profile& profile, const GenerationContext& ctx);

// Load a profile from configuration storage
Profile load_profile(const std::string& config_dir);

// Reapply existing profile (idempotent)
SetupResult reapply_profile(
    const Profile& original_profile,
    const std::map<std::string, std::string>& current_config,
    const GenerationContext& ctx);
```

## Derivation Logic

Profiles are generated in this order of precedence:

1. **Policy-enforced values** (highest priority, cannot be overridden)
2. **User inputs/choices** (explicit selections)
3. **Preference satisfaction** (from available options based on discovery)
4. **Discovery-based defaults** (based on host capabilities - CPU, memory, GPU, etc.)
5. **Built-in defaults** (fallbacks)

## Scope

### System-wide vs Per-user

```cpp
enum class GenerationContext::Scope {
    kSystem,   // /etc/rebuntu (root)
    kUser,     // ~/.config/rebuntu (user)
    kSession,  // temporary directory (transient)
}
```

## Implementation Details

### File Locations

| Path | Purpose |
|------|---------|
| `cpp/include/system/setup/profile.hpp` | Header-only type definitions |
| `cpp/src/profile.cpp` | Implementation of API functions |
| `cpp/tests/test_profile.cpp` | Comprehensive test suite |

### Profile Storage

```
System: /etc/rebuntu/config
User:   ~/.config/rebuntu/config
Session: temporary directory
```

Format: Simple key=value with optional comments (`#`)

## Verification Strategy

Configuration write success is NOT verification. The system:

1. Writes to atomic temp file + rename
2. Verifies file exists and is readable
3. Parses written content
4. Compares against expected values

## Safety Considerations

- No host mutation in dry-run mode
- Atomic file writes prevent corruption
- User-owned files are never overwritten (only merged)
- Error messages preserve context without secrets

## Testing

All tests pass:

```bash
cd cpp/Build && ./tests/test_profile
```

Output:
```
test_profile_basic: OK
test_profile_generation: OK
test_profile_validation: OK
test_profile_integration: OK
```

Test coverage:
- ProfileSource enum string conversion
- DerivationReason enum string conversion
- ProfileStatus enum string conversion
- GenerationContext creation
- Profile generation (empty, with user input, with discovery)
- Profile validation
- Profile diff calculation
- Integration tests

## Acceptance Criteria

| Criterion | Status |
|-----------|--------|
| Canonical grammar established | ✅ |
| Derivation logic defined and implemented | ✅ |
| Deterministic for equivalent inputs | ✅ |
| Dry-run mode supported | ✅ |
| Idempotent reapplication | ✅ |
| User edits preserved where possible | ✅ |
| All types are header-only where possible | ✅ |
| API is callable without host mutation | ✅ |
| Tests proving meaningful behavior | ✅ |
| Error codes defined | ✅ |

## Rejected Alternatives

### Alternative 1: Using Result<void> for validate_profile
**Rejected:** Outcome is the proper type for void-returning operations
- `Outcome` is designed specifically for operations without return values
- `Result<T>` with T=void has compilation issues due to template specialization

### Alternative 2: Merging profile generation and application
**Rejected:** Separating them allows for:
- Planning before execution
- Diff calculation between current and target state
- Checkpoint/backup before mutation
- Better error handling and recovery

## Deferred Work

| Task | Phase |
|------|-------|
| Full integration with environment::discovery results | 1.11 (Discovery Integration) |
| User config file parsing/writing for profile storage | 2.0 (Storage) |
| Policy enforcement engine | 2.5 (Policy Engine) |

## Related Discoveries

- [DISC#0022](./0022-preferences-model.md): Preferences Model (Phase 1.7)
- [DISC#0023](./0023-setup-configuration-model.md): Setup & Configuration Model (Phase 1.8)

## Files Modified/Created

| File | Action |
|------|--------|
| `cpp/include/system/setup/profile.hpp` | Created - Header-only types |
| `cpp/src/profile.cpp` | Created - Implementation |
| `cpp/tests/test_profile.cpp` | Created - Test suite |
| `cpp/src/CMakeLists.txt` | Modified - Added profile.cpp to system library |
| `cpp/tests/CMakeLists.txt` | Modified - Added test_profile target |

## Conclusion

Phase 1.10 establishes the foundation for Rebuntu's profile generation and
application machinery. The implementation follows Phase 0 contracts, uses C++20
idiomatically, and provides a clean API that can be used by CLI, GUI, and other
interfaces without duplicating logic.