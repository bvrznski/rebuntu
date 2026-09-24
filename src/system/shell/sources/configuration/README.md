# configuration/ — Configuration Access Utilities

## Purpose

Shell-native utilities for accessing configuration values, primarily through
environment variables with shell-convenient wrappers.

## What Belongs Here

| Category | Description |
|----------|-------------|
| Environment access | Getting environment variable values with defaults |
| Key existence checks | Verifying config keys are set |
| Shell-facing config reading | Wrapper functions for shell convenience |

## What Does NOT Belong Here

| Category | Where to Go |
|----------|-------------|
| Canonical configuration management | Rebuntu configuration subsystem |
| File-based configuration parsing | Parsing category or Python module |
| Complex configuration validation | C++ runtime with typed schemas |

## Examples

* `rebuntu_config_get()` — get config value with default
* `rebuntu_config_exists()` — check if config key is set
* `rebuntu_env_get()` — explicit environment variable getter

## Dependencies

Uses native Linux utilities:
* Bash parameter expansion for variable access
* Shell conditional operators

## Safety Classification

| Class | Description |
|-------|-------------|
| READ_ONLY | Configuration reading only |

## Pipeline Semantics

* stdout: Config values (for get operations)
* stderr: Error messages on failure
* Exit status: 0 for success, non-zero for not found/empty

## Notes

This category provides shell-convenient access to configuration. The canonical
configuration system is managed by the Rebuntu configuration subsystem with
typed schemas and proper validation.