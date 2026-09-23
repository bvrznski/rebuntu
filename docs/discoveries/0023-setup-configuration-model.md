# Discovery #23: Setup & Configuration Model (Phase 1.8)

**Status:** ACCEPTED  
**Date:** 2026-09-23  
**Author:** Rebuntu Agent

## Summary

This document describes the Phase 1.8 implementation of Rebuntu's setup and configuration
machinery - establishing the canonical grammar for environment initialization and parameter
specification.

## Core Distinction

```
Installation = place/establish Rebuntu artifacts and prerequisites
Setup        = establish an initial usable Rebuntu environment for a user/host
Configuration = durable parameters governing behavior
```

**Key Insight:** Setup is not necessarily a persistent object - it's the state achieved
after initialization. Configuration is what's applied during that process.

## Architecture

### Components

| Component | Responsibility |
|-----------|----------------|
| `rebuntu::setup` namespace | Canonical setup API |
| `SetupPhase` enum | Lifecycle phases (not_started, in_progress, complete, failed, degraded) |
| `ConfigurationSource` enum | Where configuration originates (default, system, user, environment, override) |
| `ConfigurationMode` enum | How configuration is applied (standard, strict, permissive) |
| `SetupContext` struct | Environment context (scope, paths, dry_run mode) |
| `SetupIntent` struct | User's desired setup state |
| `SetupArtifact` struct | Managed artifacts with verification state |
| `ConfigurationValue` struct | Key-value entry with provenance |
| `SetupResult` struct | Result of setup operation |
| `ConfigurationResult` struct | Result of configuration loading/applying |

### API Functions

```cpp
// Build a default setup context based on current host state
SetupContext build_default_context();

// Apply configuration from multiple sources with precedence
ConfigurationResult apply_configuration(
    const std::map<std::string, std::string>& user_config,
    ConfigurationMode mode = ConfigurationMode::kStandard);

// Perform initial environment setup (create directories, write config)
SetupResult setup_initial_environment(const SetupIntent& intent, const SetupContext& ctx_override);

// Reconfigure existing environment with new settings
SetupResult setup_reconfigure(const SetupContext& context, const std::map<std::string, std::string>& config);

// Load configuration from a directory
ConfigurationResult load_configuration(const std::string& config_dir);
```

## Scope

### System-wide vs Per-user

```cpp
enum class SetupContext::Scope {
    kSystem,   // /etc/rebuntu, /var/lib/rebuntu (root)
    kUser,     // ~/.config/rebuntu, ~/.local/state/rebuntu (user)
    kSession,  // /tmp/rebuntu_session_<pid> (temporary)
}
```

### Configuration Precedence

1. **Default** - Built-in deterministic values
2. **Environment** - System-wide config (`/etc/rebuntu`)
3. **User Config** - User-level config (`~/.config/rebuntu`)
4. **Override** - Invocation-time override (highest precedence)

## Implementation Details

### File Locations

| Path | Purpose |
|------|---------|
| `cpp/include/system/setup/contracts.hpp` | Header-only type definitions |
| `cpp/src/setup.cpp` | Implementation of API functions |
| `cpp/tests/test_setup.cpp` | Comprehensive test suite |

### Configuration Storage

```
System: /etc/rebuntu/config
User:   ~/.config/rebuntu/config
Session: /tmp/rebuntu_session_<pid>/config
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

All tests pass (17/17):

```bash
cd cpp/Build && ctest --output-on-failure
```

Test coverage:
- Phase string conversions
- Configuration source precedence
- Context creation with scope overrides
- Result structure integrity
- Dry-run mode simulation

## Acceptance Criteria

| Criterion | Status |
|-----------|--------|
| Canonical grammar established | ✅ |
| All types are header-only where possible | ✅ |
| API is callable without host mutation | ✅ |
| Tests prove meaningful behavior | ✅ |
| Error codes defined | ✅ |

## Rejected Alternatives

### Alternative 1: Nested ConfigurationMode
**Rejected:** Making `ConfigurationMode` nested inside `SetupContext`
- Increases complexity unnecessarily
- Less discoverable via code completion
- No semantic benefit from nesting

### Alternative 2: String-based configuration paths
**Rejected:** Using arbitrary path parameters instead of enum-based scope
- Prone to typos and invalid paths
- Makes verification harder
- Loses type safety benefits

## Deferred Work

| Task | Phase |
|------|-------|
| Systemd unit file installation | 1.9 (Native Integration) |
| D-Bus configuration interface | 1.10 (IPC) |
| Configuration validation schemas | 2.0 (Validation) |

## Related Discoveries

- [DISC#0021](./0021-installation-architecture.md): Installation Architecture
- [DISC#0022](./0022-preferences-model.md): Preferences Model (Phase 1.7)
- Phase 0.18: Configuration Specification Grammar

## Files Modified/Created

| File | Action |
|------|--------|
| `cpp/include/system/setup/contracts.hpp` | Created - Header-only types |
| `cpp/src/setup.cpp` | Created - Implementation |
| `cpp/tests/test_setup.cpp` | Created - Test suite |
| `cpp/tests/CMakeLists.txt` | Modified - Added test target |

## Conclusion

Phase 1.8 establishes the foundation for Rebuntu's setup and configuration machinery.
The implementation follows Phase 0 contracts, uses C++20 idiomatically, and provides
a clean API that can be used by CLI, GUI, and other interfaces without duplicating
logic.