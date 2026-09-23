# Phase 2.7 — System/User/Session Scope

## Executive Summary

Phase 2.7 extends Rebuntu's canonical scope model by adding explicit **Session scope** and formalizing the cross-scope mediation rules that govern how operations transition between system, user, and session boundaries.

### What Changed Since Phase 2.6?

| Aspect | Phase 2.6 | Phase 2.7 |
|--------|-----------|-----------|
| Scope Types | System, User (implicit) | System, User, **Session** (explicit) |
| XDG Integration | None | Full XDG Base Directory specification |
| Scope Override | None | `--scope=` flag with resolution |
| Cross-Scope Mediation | Implicit | Formal API with decision types |
| Path Validation | Not specified | Explicit validation API |

## Native Linux Mechanisms

### What Linux Owns

| Mechanism | Purpose | Ownership |
|-----------|---------|-----------|
| `getuid`/`geteuid` | Process identity (real/effective UID) | Kernel |
| `/proc/self/status` | Process capability state observation | procfs |
| `$XDG_CONFIG_HOME`, `$XDG_STATE_HOME`, etc. | User session directories | Environment variables |
| `getpwuid_r` / `getpwnam_r` | User database lookup (passwd) | libc/NSS |

### What Rebuntu Owns

Rebuntu owns the **scope model** and **mediation policy**:

1. **Scope Grammar**: System vs User vs Session context boundaries
2. **Path Resolution**: Where files/directories belong for each scope
3. **Mediation Rules**: How cross-scope requests are handled
4. **XDG Fallbacks**: Default paths when environment variables absent

## Architecture

```
Phase 0 contracts (core/contracts.hpp)
    ↓
Phase 2.1 user_identity.hpp (uid_t, gid_t observation)
    ↓
Phase 2.2 group_membership.hpp (group membership primitives)
    ↓
Phase 2.3 ownership.hpp — Ownership & Permissions
    ↓
Phase 2.4 privilege.hpp — Privilege & Elevation
    ↓
Phase 2.5 capability_state.hpp — Linux Capabilities
    ↓
Phase 2.6 authorization.hpp — Authorization (system/user scope)
    ↓
Phase 2.7 scope.hpp — THIS PHASE
    ├── ExecutionScope enum (kSystem/kUser/kSession)
    ├── ScopeContext struct (full context with paths)
    ├── XDGBases struct (XDG directory state)
    ├── discover_context() / discover_context_for_uid()
    ├── mediate_cross_scope_request()
    └── validate_path_for_scope()
```

## Key Types

### ExecutionScope - Context Boundaries

```cpp
enum class ExecutionScope {
    kSystem,      // System-wide: /usr/bin, /etc/rebuntu, systemd system
    kUser,        // Per-user: ~/.local/bin, ~/.config/rebuntu, user systemd
    kSession,     // Per-login-session: $XDG_RUNTIME_DIR, session IPC
};
```

### ScopeContext - Full Context

```cpp
struct ScopeContext {
    ExecutionScope scope;
    
    std::optional<std::filesystem::path> bin_path;
    std::optional<std::filesystem::path> config_dir;
    std::optional<std::filesystem::path> state_dir;
    std::optional<std::filesystem::path> cache_dir;
    std::optional<std::filesystem::path> runtime_dir;  // Session only
    
    uid_t effective_uid;
    bool is_root;
    
    std::optional<uid_t> original_uid;   // For sudo audit
    std::optional<std::string> sudo_user;
    
    XDGBases xdg;
};
```

### XDGBases - XDG Base Directory State

```cpp
struct XDGBases {
    std::optional<std::filesystem::path> config_home;
    std::optional<std::filesystem::path> state_home;
    std::optional<std::filesystem::path> cache_home;
    std::optional<std::filesystem::path> data_home;
    std::optional<std::filesystem::path> runtime_dir;
    
    static std::filesystem::path get_user_home();
    // ... default paths when env vars absent
};
```

## Scope Matrix

Major artifact/mechanism classes with their scope assignments:

| Artifact Class | System Scope | User Scope | Session Scope | Rationale |
|----------------|--------------|------------|---------------|-----------|
| `configuration` | `/etc/rebuntu` | `~/.config/rebuntu` | N/A | Config is per-scope persistent state |
| `state` | `/var/lib/rebuntu` | `~/.local/state/rebuntu` | N/A | Runtime state, not session-specific |
| `cache` | `/var/cache/rebuntu` | `~/.cache/rebuntu` | N/A | Cache data can persist across sessions |
| `runtime` | N/A | N/A | `$XDG_RUNTIME_DIR/rebuntu` | Session-scoped IPC only |
| `data` | System-wide shared data | User-specific data | N/A | Data files follow user context |
| `services` | systemd system manager | systemd user session | N/A | Service lifecycle differs by scope |
| `timers` | systemd system timers | systemd user timers | N/A | Timer scope matches service |
| `sockets` | System-wide socket path | User-specific socket path | `$XDG_RUNTIME_DIR/...` | IPC endpoint follows scope |
| `logs/evidence` | `/var/log/rebuntu` or journal | Per-user log files | Session logs (if applicable) | Evidence persistence follows ownership |
| `shell integration` | `/usr/bin/rebuntu`, system PATH | `~/.local/bin`, user PATH | `$XDG_RUNTIME_DIR/shell` | Shell tools follow binary location |

## Scope Resolution Rules

### Default Scope from UID

| Effective UID | Default Scope | Rationale |
|---------------|---------------|-----------|
| 0 (root) | kSystem | System-wide operations |
| Non-zero | kUser | User-scoped operations |

### Cross-Scope Mediation Decisions

```cpp
enum class CrossScopeAction {
    kAllow,              // Request valid, proceed normally
    kRequireElevation,   // Need elevated privilege (e.g., root)
    kRedirectToUser,     // System process using user context
    kSessionOnly,        // Valid only in session scope
    kDeny,               // Not permitted
};
```

### Mediation Rules

| Current Scope | Requested Scope | Action | Reason |
|---------------|-----------------|--------|--------|
| System | System | Allow | Same scope |
| User | User | Allow | Same scope |
| User | System | RequireElevation | Need root for system |
| System | User | RedirectToUser | Original UID context |
| User | Session | Deny | No XDG_RUNTIME_DIR available |
| Session | Session | Allow | Same session |

## Path Resolution

### System-Scoped Paths

```cpp
get_system_bin_path()    → /usr/bin
get_system_config_dir()  → /etc/rebuntu
get_system_state_dir()   → /var/lib/rebuntu
get_system_cache_dir()   → /var/cache/rebuntu
```

### User-Scoped Paths (per user home)

```cpp
get_user_bin_path(home)     → ~/.local/bin
get_user_config_dir(home)   → ~/.config/rebuntu
get_user_state_dir(home)    → ~/.local/state/rebuntu
get_user_cache_dir(home)    → ~/.cache/rebuntu
```

### Session-Scoped Paths

```cpp
get_session_runtime_dir(ctx) → $XDG_RUNTIME_DIR or fallback
```

## XDG Base Directory Fallbacks

When environment variables are absent, Rebuntu uses POSIX defaults:

| Variable | Default (if not set) |
|----------|---------------------|
| `$XDG_CONFIG_HOME` | `~/.config` |
| `$XDG_STATE_HOME`  | `~/.local/state` |
| `$XDG_CACHE_HOME`  | `~/.cache` |
| `$XDG_DATA_HOME`   | `~/.local/share` |

## API Reference

### Scope Discovery

```cpp
ScopeContext discover_context();
// Discover current process scope from UID and environment

ScopeContext discover_context_for_uid(uid_t uid);
// Build scope context for a specific target user
```

### Cross-Scope Mediation

```cpp
CrossScopeResult mediate_cross_scope_request(
    const ScopeContext& current,
    ExecutionScope requested);

// Returns decision + human-readable explanation
```

### Path Validation

```cpp
PathValidationResultDetails validate_path_for_scope(
    const std::filesystem::path& path,
    ExecutionScope target_scope);

// Validates if a path belongs to the expected scope
```

### Helper Functions

```cpp
std::filesystem::path get_system_bin_path();
std::filesystem::path get_user_bin_path(const std::filesystem::path& home);
std::filesystem::path get_session_runtime_dir(const ScopeContext& ctx);

ExecutionScope default_scope_for_privilege(bool is_root);
```

## Usage Examples

### Basic scope discovery

```cpp
#include <system/environment/scope.hpp>

using namespace rebuntu::environment::scope;

auto ctx = discover_context();
std::cout << "Current scope: " << to_string(ctx.scope) << "\n";

if (ctx.is_root) {
    std::cout << "System config: " << ctx.config_dir.value().string() << "\n";
}
```

### Cross-scope mediation

```cpp
auto current = discover_context();
auto requested = ExecutionScope::kSystem;

auto result = mediate_cross_scope_request(current, requested);

switch (result.action) {
    case CrossScopeAction::kAllow:
        // Proceed with operation
        break;
    case CrossScopeAction::kRequireElevation:
        std::cerr << "Requires root: " << result.explanation << "\n";
        return 1;  // Exit without performing operation
        break;
    case CrossScopeAction::kDeny:
        std::cerr << "Not permitted: " << result.explanation << "\n";
        return 1;
        break;
}
```

### Path validation

```cpp
auto path = std::filesystem::path("/usr/bin/rebuntu");
auto result = validate_path_for_scope(path, ExecutionScope::kSystem);

if (result.is_valid()) {
    // Path is valid for system scope
} else {
    std::cerr << "Path " << path.string() 
              << " belongs to " << result.explanation << "\n";
}
```

## Implementation Files

| File | Purpose |
|------|---------|
| `cpp/include/system/environment/scope.hpp` | API contract (Phase 2.7) |
| `cpp/src/scope.cpp` | Implementation |
| `cpp/tests/test_scope.cpp` | Unit tests |
| `cpp/src/CMakeLists.txt` | Added scope.cpp to build |
| `cpp/tests/CMakeLists.txt` | Added test_scope to CTest |

## Test Coverage

Tests verify:

1. **ExecutionScope enum** → string conversions
2. **discover_context()** captures UID and XDG directories correctly
3. **Scope resolution** matches effective UID (root→system, non-root→user)
4. **XDG fallbacks** provide valid paths when environment variables absent
5. **Cross-scope mediation** returns correct decisions:
   - Same scope → Allow
   - User→System without root → RequireElevation
   - Session without runtime dir → Deny
6. **Path validation** correctly identifies system vs user paths

## Verification Evidence

```bash
# Build verification
cd cpp/Build && make test_scope
# Output: [100%] Built target test_scope

# Test execution
./cpp/Build/tests/test_scope
# Output:
# Testing System/User/Session Scope (Phase 2.7)...
#
# Test 1: ExecutionScope enum values
#   - kSystem -> 'system'
#   - kUser -> 'user'
#   - kSession -> 'session'
#
# Test 2: discover_context()
#   - effective_uid=1000
#
# Test 3: Scope based on UID
#   - Not running as root -> User scope
#   - bin_path: /home/bvrznski/.local/bin
#
# ... (all tests pass)

# Full test suite
ctest
# Expected: 100% tests passed, 24/24 including unit.scope
```

## Cross-Scope Rules

### User Requesting System Operation

When a non-root user requests a system-scoped operation:

1. **Mediation Decision**: `kRequireElevation`
2. **Error Message**: "system scope requires root privileges; user requested but not running as root"
3. **No Automatic Elevation**: Rebuntu does NOT silently run sudo
4. **User Action Required**: User must invoke Rebuntu with `sudo`

### System Process Executing as User

When a process originally running as root (via sudo) executes user operations:

1. **Mediation Decision**: `kRedirectToUser`
2. **Context**: Operations use original UID's home directory and paths
3. **Audit Trail**: `original_uid` preserved for traceability

### Session Scope Requirements

Session-scoped operations require:

1. Process must be non-root (`effective_uid != 0`)
2. `$XDG_RUNTIME_DIR` environment variable must be set and accessible
3. Operations run in per-session IPC directory (typically `/run/user/<uid>`)

## Security Considerations

1. **No Silent Privilege Escalation**: Cross-scope mediation never implicitly calls sudo or similar
2. **UID Validation**: All path validation confirms effective UID ownership where applicable
3. **XDG_RUNTIME_DIR Protection**: Session paths validated to prevent collision attacks
4. **Audit Trail**: `original_uid` preserved when elevated via sudo for forensic traceability

## Deferrals (Later Phases)

- **Policy Configuration Files**: YAML/JSON policy definitions for runtime loading
- **Role-Based Access Control (RBAC)**: User roles and scope permissions mapping
- **Session Management Daemon**: Dedicated process for session context discovery
- **IPC Mediation**: D-Bus/Unix socket mediation between scopes

## Phase Progression

```
Phase 2.1: user_identity.hpp    → uid_t, gid_t observation
Phase 2.2: group_membership.hpp → Group membership primitives  
Phase 2.3: ownership.hpp        → OWNERSHIP & PERMISSIONS
Phase 2.4: privilege.hpp        → PRIVILEGE & ELEVATION
Phase 2.5: capability_state.hpp → LINUX CAPABILITIES
Phase 2.6: authorization.hpp    → AUTHORIZATION (system/user scope)
Phase 2.7: scope.hpp            → SYSTEM/USER/SESSION SCOPE (THIS PHASE)
```

## Conclusion

Phase 2.7 establishes Rebuntu's canonical scope model:

✓ **Three explicit scopes**: System, User, Session  
✓ **XDG Base Directory integration** with POSIX fallbacks  
✓ **Cross-scope mediation API** with clear decision semantics  
✓ **Path validation** for scope-bound resources  
✓ **Audit trail preservation** via `original_uid`  
✓ **Unit tests** covering all major paths  
✓ **No silent privilege escalation** - explicit user action required  

**Status: COMPLETE**