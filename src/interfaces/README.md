# src/interfaces/ — typed contracts and protocol interfaces

This directory contains Rebuntu's typed interface definitions: protocols,
contracts, IPC schemas, and message formats. Interfaces are *static*—they
declare contracts but contain no runtime implementation.

## Categories

| Subdirectory | Responsibility |
|---|---|
| `cli/` | Command-line interface contracts (commands, options, output formats) |
| `ipc/` | Inter-process communication protocols and message types |
| `api/` | HTTP/gRPC API definitions (requests/responses, errors, schemas) |
| `shell/` | Shell-facing command contracts (parsing, IR, intent) |

## CLI Interface Module

The `cli/` subdirectory contains the machine-readable command boundary module
(Task 6.47):

```
src/interfaces/cli/
├── input.hpp          # Versioned structured command input schema
└── input.cpp          # Implementation with validation and security filtering
```

### Features:

- **Versioned Schema**: Explicit `SchemaVersion` with major/minor/patch versioning
  for safe evolution and backward compatibility checking

- **Security Validation**: Rejects unknown security-sensitive field names and
  values containing forbidden patterns (shell injection vectors, path traversal,
  privilege escalation attempts)

- **Whitelist Validation**: Verbs and subject types must be in whitelist of
  safe operations

- **JSON Serialization**: `serialization::to_json_string()` and
  `serialization::from_json_string()` for IPC/structured output

- **Filtering**: `SecurityFilter` class can strip dangerous fields from inputs

### Example Usage:

```cpp
rebuntu::interfaces::cli::input::CommandInput input;
input.verb = "install";
input.subject_type = "package";
input.targets = {"curl"};
input.parameters["version"] = "latest";

rebuntu::interfaces::cli::input::InputValidator validator;
auto result = validator.validate(input);
if (result.valid) {
    // Input is valid - proceed with execution
}
```

## Principles

- **No implementation**: interfaces declare *what*, not *how*.
- **No dependencies on consumers**: an interface may be depended upon but must
  not depend on code that consumes it.
- **Stable identifiers**: interface versions and message types are versioned
  contracts, not arbitrary structures.

## Provider Registry Pattern (Phase 0.16)

The provider registry is implemented directly in the interfaces directory as a
concrete implementation of its own contract:

```
src/interfaces/provider_registry.hpp    → Interface definition
src/interfaces/provider_registry.cpp    → Concrete implementation
Native mechanism                        → Linux filesystem, process management
```

Key components:
- **ProviderId**: Unique identifier for each provider
- **ProviderAvailability**: State (unknown/available/unavailable/not_installed)
- **ProviderInfo**: Static information about a provider
- **ProviderSelector**: Strategy for selecting among available providers
- **ProviderRegistry**: Manager for registering and querying providers

Selection policies:
- `kAny`: Any available provider is acceptable
- `kFirst`: First registered provider that supports the capability
- `kPreferred`: Configurable preferred provider with fallback
- `kExplicit`: Caller must specify exact provider

## Status

COMPLETE (Phase 0.16). Interface and implementation established.

**Files created:**
- `src/interfaces/provider_registry.hpp` - Provider registry interface and implementation
- `src/interfaces/provider_registry.cpp` - Implementation file with PIMPL pattern