# rebuntu::runtime::discovery — Naming, Namespaces, Registries & Discovery (Phase 0.19)

## Overview

This module establishes how Rebuntu names, identifies, locates and discovers capabilities
without building registry bureaucracy or magical plugin loading.

## Design Principles

### Name vs ID vs Path

| Concept | Description |
|---------|-------------|
| **Human name** | Presentation label (e.g., "Filesystem Copy") |
| **Semantic ID** | Stable identifier (e.g., "filesystem.copy") |
| **Filesystem path** | Physical location (e.g., "src/system/core/") |
| **C++ namespace** | Code organization (e.g., "rebuntu::core") |

These must not be assumed identical - the system maintains explicit mapping.

### Registry vs Catalog

| Aspect | Registry | Catalog |
|--------|----------|---------|
| Purpose | Authoritative resolution | Discoverable inventory |
| Usage | Runtime resolution | Documentation/search |
| Validation | Required (duplicate detection) | Optional |

### Discovery vs Registration

**Discovery mechanisms:**
1. Source code inspection
2. Filesystem scan of `src/system/`
3. Registry lookup (C++ API)
4. Shell command help

**Registration requirements:**
- All structural components registered in `ComponentRegistry`
- Operations registered in `OperationRegistry`

## Components

### ShellVerbDetector
Detects shell verb collisions and manages reserved verbs.

```cpp
ShellVerbDetector detector;
detector.add_reserved_verb("rebuntu_reserved");
auto info = detector.detect("help");  // FREE
```

### AliasResolver
Resolves aliases to canonical IDs.

```cpp
AliasResolver resolver;
resolver.add_alias({"filesystem.cp", "filesystem.copy", ""});
auto resolved = resolver.resolve("filesystem.cp");  // Returns "filesystem.copy"
```

### FilesystemScanner
Scans directories for files matching patterns.

```cpp
FilesystemScanner scanner({{"/path/to/scan", true, {"txt"}}});
auto files = scanner.scan_all();
```

### ProviderSelector
Selects providers based on capability criteria.

```cpp
ProviderSelector selector(operations);
auto result = selector.select({
    "filesystem.copy",
    ProviderSelectionMode::FIRST,
    {},
    std::nullopt
});
```

## Files

| File | Purpose |
|------|---------|
| `discovery.hpp` | Header with all public types and interfaces |
| `discovery.cpp` | Implementation of discovery mechanisms |
| `README.md` | This documentation |

## Integration Points

- **Runtime**: Used by runtime for capability resolution
- **CLI**: Shell verb collision detection for command parsing
- **Provider system**: Provider selection based on capabilities

## Testing

Run tests with:
```bash
ctest -R test_discovery
```

## Status

**CURRENT** — Phase 0.19 implementation complete.

---

*Phase 0.19: Naming, Namespaces, Registries & Discovery*