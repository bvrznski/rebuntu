# Rebuntu Runtime Module

## Overview

This module contains core runtime abstractions for Rebuntu's deterministic execution engine.

## Components

### Contracts (`contracts.hpp`)
Phase 0.2 semantic primitives:
- `SemanticStatus`: Success, Failure, Completed, Unknown, Cancelled
- `Error`: Error with code and message
- `Outcome`: Result with status and value
- `Evidence`: Provenance-bearing observation

### Executor (`executor.hpp`)
Phase 0.13 execution mechanisms:
- `Executor`: Base class for execution mechanisms
- `InlineExecutor`: In-process function call executor

### Runner (`runner.hpp`)
Execution state machine tracking progress through states.

### Dispatcher (`dispatcher.hpp`)
Work routing and selection of execution modes.

### Configuration & Specification Grammar (`config.hpp`, Phase 0.18)
Canonical grammar for configuration:
- `SchemaDefinition`: Typed schema for a configuration value
- `ConfigValue`: A configuration value with provenance
- `Configuration`: Complete configuration from multiple sources

### Settings (`settings.hpp`, Phase 1.5)
Settings model for relatively stable explicit behavioral selections:
- `SettingDefinition`: Typed setting specification with kind, scope, defaults
- `SettingValue`: Concrete setting value with provenance and precedence source
- `SettingChange`: Mutation request for a setting
- `SettingsSchema`: Collection of setting definitions forming a contract
- `SettingsRegistry`: Registry for managing settings schemas and values
- `SettingsManager`: High-level interface for managing settings mutations

## Source Kinds (Configuration)
Where a configuration value originates:
- `kDefault`: Built-in default (deterministic and documented)
- `kSystemConfig`: System-wide configuration
- `kHostProfile`: Host-specific profile
- `kUserConfig`: User-level configuration
- `kUserPreference`: User preferences (soft, may be unsatisfied)
- `kEnvironment`: Environment variables
- `kInvocation`: Invocation-time override
- `kPolicyEnforced`: Policy-enforced value (non-overridable)

## Setting Kinds
Types of settings:
- `kToggle`: Boolean-like (enabled/disabled, on/off)
- `kSelection`: One from mutually exclusive set of values
- `kChoice`: Multiple from a set

## Scopes
Where settings apply:
- `kSystem`: System-wide setting (requires privilege to modify)
- `kUser`: Per-user setting
- `kSession`: Per-session setting (transient)

## Usage Example

```cpp
#include <system/runtime/settings.hpp>

// Create schema with settings
rebuntu::runtime::settings::SettingsSchema schema;
rebuntu::runtime::settings::SettingDefinition def;
def.id = "network.enable_ipv6";
def.kind = rebuntu::runtime::settings::SettingKind::kToggle;
def.scope = rebuntu::runtime::settings::Scope::kUser;
def.default_value = "false";
schema.add_setting(def);

// Register schema and values
rebuntu::runtime::settings::SettingsRegistry registry;
registry.add_schema("default", std::move(schema));

// Get effective value
auto manager = rebuntu::runtime::settings::SettingsManager(registry);
auto value = manager.get_value("network.enable_ipv6");

// Apply change
rebuntu::runtime::settings::SettingChange change;
change.id = "network.enable_ipv6";
change.new_value = "true";
auto result = manager.apply_change(change);
```
