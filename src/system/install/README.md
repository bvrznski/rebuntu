# Rebuntu Installation Forms & Structured Setup Input (Phase 1.3)

## Overview

This module provides installation forms and structured setup input functionality for Rebuntu.

## Form Concept

A `Form` is a schema-backed collection of user-supplied values with presentation metadata and validation.

### Key Components

- **FieldType**: Defines supported field types (string, integer, boolean, enum, path, choice, multiselect)
- **ValidationLevel**: Defines validation severity (info, warning, error)
- **FieldConstraint**: Validates field values against constraints
- **InputChannel**: Abstract interface for input sources
- **FormParser**: Parses and validates form data from an InputChannel
- **FormBuilder**: Fluent API for constructing FormDefinition objects

### Field Types

| Type | Description |
|------|-------------|
| kString | Free-form text string |
| kInteger | Signed integer value |
| kBoolean | Boolean (true/false/yes/no/1/0) |
| kEnum | One of a set of allowed values |
| kPath | Filesystem path with validation options |

### Validation Constraints

- `kRequired` - Field must be present
- `kMinLength` / `kMaxLength` - String length constraints
- `kMinValue` / `kMaxValue` - Numeric value constraints
- `kAllowedValues` - Only these values are acceptable
- `kPathExists` - Filesystem path must exist
- `kPathIsDirectory` - Path must be a directory
- `kPathIsFile` - Path must be a regular file

### Input Channels

| Channel | Description |
|---------|-------------|
| InteractiveInputChannel | For interactive CLI input (in-memory) |
| ConfigFileChannel | For config/spec file input |

## Usage Examples

### Creating a Form

```cpp
#include <system/install/forms.hpp>

using namespace rebuntu::install::forms;

// Build a form definition
auto form = FormBuilder::create("installation", "Installation Settings")
    .add_string_field("version", "Version", "Target version to install")
    .add_enum_field("scope", "Scope", "Install scope", {"system", "user"})
    .add_boolean_field("verify", "Verify", "Enable verification")
    .build();

// Create input channel with values
ConfigFileChannel channel({{"version", "1.0.0"}, {"scope", "user"}});

// Parse and validate
FormParser parser(form);
FormResult result = parser.parse(channel);

if (result.is_valid()) {
    // Process validated form data
}
```

### Unknown Field Detection

The FormParser automatically detects unknown fields and marks them as errors:

```cpp
ConfigFileChannel channel({{"version", "1.0.0"}, {"unknown_field", "value"}});
FormResult result = parser.parse(channel);
// result.is_valid() will be false due to unknown field
```

## InstallationFormFactory

Predefined forms for common installation scenarios:

- `create_installation_intent_form()` - Version, scope, verification settings
- `create_scope_selection_form()` - System vs user scope selection
- `create_feature_selection_form()` - Optional features selection

## Pressure Tests Covered

1. **Fully interactive** - InteractiveInputChannel with set_value()
2. **Fully non-interactive** - ConfigFileChannel with complete spec
3. **Partial form** - Missing optional fields use defaults
4. **Invalid enum** - Out-of-range enum values detected as errors
5. **Invalid path** - Path validation constraints enforced
6. **Secret input** - Sensitive field handling (value_source metadata)
7. **Conflicting choices** - Multiple constraint validations
8. **Host-derived suggestion** - ValueSource::kDetectedHost metadata
9. **Policy-forbidden value** - AllowedValues constraint enforced
10. **Unknown field** - Extra fields in input channel detected

## Architecture

```
User Input
    ↓
InputChannel (InteractiveInputChannel / ConfigFileChannel)
    ↓
FormParser.parse()
    ↓
FormResult with:
  - Field values
  - Validation status per field
  - Error/warning messages
    ↓
InstallationIntent / Configuration
```

## Phase History

- **Phase 1.0**: Initial installation module foundation
- **Phase 1.2**: Installation planning and host discovery
- **Phase 1.3**: Forms & structured setup input (this phase)

## See Also

- `src/system/install/planning.hpp` - Installation planning
- `src/system/install/discovery.hpp` - Host discovery