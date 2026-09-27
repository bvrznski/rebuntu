# Phase 6.2 — Predicate Dictionary Collision Analysis

## Date: 2026-09-27

## Historical Shell Function Collisions

### `installed`
**Status**: USER_FUNCTION (historical Rebuntu)
**Location**: Sourced shell environment
**Type**: Package existence checker with multiple package manager backends (dpkg, pacman, rpm, snap, flatpak)

```bash
installed ()
{
    local app="$1";
    if command -v "$app" > /dev/null 2>&1; then
        echo "yes:path:$(command -v "$app")";
        return 0;
    fi;
    # ... dpkg, pacman, rpm, snap, flatpak checks ...
}
```

**Collision Analysis**: 
- This function already exists in the Rebuntu shell environment
- The Phase 6.2 predicate `installed_predicate` provides the same semantic functionality but with:
  - Typed result structure (PredicateResult)
  - Three-valued logic (TRUE/FALSE/UNKNOWN) with explicit semantics
  - Evidence tracking for auditability
- Recommendation: Use namespaced CLI form (`rebuntu installed`)

### `declared`
**Status**: USER_FUNCTION (historical Rebuntu)
**Location**: Sourced shell environment  
**Type**: Alias existence checker

```bash
declared ()
{
    local name="$1";
    if alias "$name" &> /dev/null; then
        echo "yes:alias";
        return 0;
    fi;
    # ... other checks ...
}
```

**Collision Analysis**:
- This function already exists in the Rebuntu shell environment  
- The Phase 6.2 predicate `declared_predicate` provides expanded functionality:
  - Check systemd units, users, groups in addition to aliases
  - Typed result with evidence tracking
- Recommendation: Use namespaced CLI form (`rebuntu declared`)

### Shell Builtins
The following shell builtins were checked as potential collision candidates:

| Builtin | Status | Collision Risk |
|---------|--------|----------------|
| test | SHELL_BUILTIN | LOW (test is a general utility) |
| declare | SHELL_BUILTIN | MEDIUM (Bash declare vs predicate intent differ) |

## Native System Command Collisions

| Command | Status | Collision Risk |
|---------|--------|----------------|
| find | SYSTEM_COMMAND | LOW (path-based search vs state queries) |
| mount | SYSTEM_COMMAND | LOW (mount action vs mounted predicate check) |
| open | SYSTEM_COMMAND | LOW |
| patch | SYSTEM_COMMAND | LOW |
| sync | SYSTEM_COMMAND | LOW |

## Collision Resolution Strategy

**Rule**: When a predicate conflicts with an existing shell function/builtin:

1. **Preserve the native shell function** - Do not override or shadow
2. **Use namespaced CLI form** - `rebuntu installed foo` instead of `installed foo`
3. **Documentation** - Clearly indicate collision status in command metadata
4. **Completion system** - Recommend full command name where collisions exist

## Implementation Notes

The Phase 6.2 predicate dictionary is implemented as C++ header-only interface:
- Location: `src/system/shell/predicates.hpp`
- Namespace: `rebuntu::shell`
- All predicates return `PredicateResult` with three-valued logic
- Evidence tracking via `core::Evidence`