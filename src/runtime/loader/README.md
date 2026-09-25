# Rebuntu Runtime Loader (Phase 4.9 + 4.15)

## Overview

The `rebuntu::runtime::loader` namespace provides safe runtime definition loading for Rebuntu.

**Mission**: Load definitions without executing them.
Loading is discovery/materialization, not execution.

### Phase 4.15 Updates

- Shell Source definitions (`.sh`, `.bash`) via `LoadKind::kShellSource`
- Safe source-time validation without side effects
- Integration with subprocess execution through runtime contracts

## Safety Principles

1. **Trusted vs Untrusted Paths**: Definitions from `/etc/rebuntu/`, `/usr/share/rebuntu/` are trusted. Untrusted paths (e.g., `~/rebuntu/`, `/tmp/rebuntu/`) require explicit opt-in and strict validation only.

2. **No Import-Time Side Effects**: Definition metadata is loaded but NOT executed or evaluated.
   - Shell sources are scanned for execution patterns (`main "$@"`, `exit $?`, top-level exec)
   - Unsafe shell sources are rejected from trusted paths

3. **Duplicate Detection**: Loading the same definition ID twice is rejected with an error.

4. **File Validation**: Path existence, size limits, and extension filtering are enforced.

5. **Shell Source Safety** (Phase 4.15):
   - Shell sources must not execute at top level
   - No arbitrary code execution from untrusted sources
   - Shebang detection for interpreter verification

## API

### Core Types

| Type | Description |
|------|-------------|
| `LoadKind` | Definition type: Unit, Operation, Workflow, Task, **ShellSource** (4.15) |
| `DefinitionId` | Unique identifier for loaded definitions |
| `DefinitionMetadata` | Static information about a definition |
| `LoadResult` | Result of load operation (success/failure/skipped) |

### Loader Class

```cpp
class Loader {
public:
    // Create loader with default config
    static std::unique_ptr<Loader> make_loader();
    
    // Create loader with custom config
    static std::unique_ptr<Loader> make_loader_with_config(LoaderConfig cfg);
    
    // Load from specific path
    LoadResult load_from_path(const std::filesystem::path& pth, LoadKind kind);
    
    // Load all trusted definitions of a kind
    std::vector<LoadResult> load_trusted(LoadKind kind);
    
    // Load from both trusted and optionally untrusted paths
    std::vector<LoadResult> load_all(LoadKind kind);
    
    // Get loaded definition by ID
    std::optional<DefinitionMetadata> get(const DefinitionId& id) const;
    
    // Check if definition is loaded
    bool contains(const DefinitionId& id) const;
    
    // List all loaded definitions
    std::vector<DefinitionId> list_all() const;
    
    // Clear the registry
    void clear();
};
```

### LoaderBuilder

```cpp
class LoaderBuilder {
public:
    LoaderBuilder& add_trusted_config_dir(std::filesystem::path pth);
    LoaderBuilder& add_trusted_share_dir(std::filesystem::path pth);
    LoaderBuilder& allow_untrusted(bool allow);
    LoaderBuilder& set_max_file_size(size_t bytes);
    LoaderBuilder& set_strict_validation(bool strict);
    
    std::unique_ptr<Loader> build();
};
```

## Usage Example

```cpp
#include "runtime/loader.hpp"

// Create loader with trusted paths
auto loader = rebuntu::runtime::loader::make_loader();

// Load a specific definition file (Phase 4.15)
auto result = loader->load_from_path("/etc/rebuntu/units/my-unit.yaml", 
                                      rebuntu::runtime::loader::LoadKind::kUnit);

if (result.succeeded()) {
    auto meta = result.metadata.value();
    std::cout << "Loaded: " << meta.id << "\n";
}

// Load shell source (Phase 4.15)
auto shell_result = loader->load_from_path("/usr/share/rebuntu/sources/utils.sh",
                                           rebuntu::runtime::loader::LoadKind::kShellSource);

if (shell_result.succeeded()) {
    // Shell source loaded - metadata available but NOT executed
}
```

## Error Handling

| Error Code | Description |
|------------|-------------|
| `kFileNotFound` | Path doesn't exist or isn't accessible |
| `kPermissionDenied` | File access denied or size limit exceeded |
| `kMalformedSchema` | Definition file has invalid structure |
| `kDuplicateId` | Same ID already loaded |
| `kUntrustedSource` | Loading from untrusted path without permission |

## Shell Source Integration (Phase 4.15)

Shell sources are loaded via the loader for metadata discovery but NOT executed.
Execution happens through runtime contracts:

```cpp
// Phase 4.15: Runtime execution flow
Request -> Validation -> Target/Resolver -> Authorization ->
  Dispatch -> ShellSourceDefinition -> SubprocessExecutor -> Outcome

Shell source loading:
  - /etc/rebuntu/sources/      (trusted)
  - /usr/share/rebuntu/sources/ (trusted)
  
Execution via subprocess:
  - Shell interpreter detected from shebang
  - argv array passed to subprocess_executor_
  - Result collected with verification
```

## Testing

Tests are in `cpp/tests/loader_test.cpp`. Run with:
```bash
ctest -R loader_test
```

## Integration Points

- Phase 4.10: Runtime execution uses Loader to materialize definitions before execution
- Phase 4.11: Workflow engine uses Loader for step definition resolution
- **Phase 4.15**: Shell source loading and subprocess integration
