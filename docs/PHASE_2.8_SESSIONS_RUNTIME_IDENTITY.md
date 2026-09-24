# Phase 2.8 — Sessions & Runtime Identity

## Executive Summary

Phase 2.8 extends Rebuntu's canonical environment context model by adding explicit **Session identity** and comprehensive **Runtime directory management**. This phase distinguishes between:

- **User identity** (who): The account running the process
- **Session identity** (which login session): The specific interactive session
- **Invocation context** (how): How the process was started (systemd, sudo, SSH, etc.)

### What Changed Since Phase 2.7?

| Aspect | Phase 2.7 | Phase 2.8 |
|--------|-----------|-----------|
| Scope Types | System, User, Session (implicit) | System, User, Session (explicit + identity tracking) |
| Invocation Context | Not tracked | Direct, sudo, su, SSH, systemd, cron, desktop launch, container |
| Runtime Directory | $XDG_RUNTIME_DIR path resolution only | Full status validation with permission checks |
| Environment Policy | N/A | Trust/Warn/Ignore/Override based on context |
| Desktop Detection | Part of HostDiscovery | Dedicated detection via environment variables |

## Native Linux Mechanisms

### What Linux Owns

| Mechanism | Purpose | Ownership |
|-----------|---------|-----------|
| `geteuid`/`getuid` | Process identity (effective vs real UID) | Kernel |
| `$XDG_RUNTIME_DIR` | Session-scoped runtime directory | Environment variable (user session) |
| `/run/user/<uid>` | Runtime directory location | systemd user manager |
| `$DESKTOP_SESSION`, `$WAYLAND_DISPLAY`, `$DISPLAY` | Desktop/Display detection | Desktop environment |
| `$SUDO_USER`, `SSH_CLIENT`, `NOTIFY_SOCKET` | Invocation context detection | External tools (sudo, sshd, systemd) |

### What Rebuntu Owns

Rebuntu owns the **context model** and **policy decisions**:

1. **Session Identity**: Distinguishes login session from user account
2. **Invocation Context Detection**: Analyzes environment variables to determine how process was started
3. **Runtime Directory Validation**: Verifies directory existence, ownership, and permissions
4. **Environment Policy**: Decides which environment variables to trust based on context

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
Phase 2.7 scope.hpp — System/User/Session Scope
    ↓
Phase 2.8 sessions.hpp — THIS PHASE
    ├── SessionIdentity struct (user + session distinction)
    ├── EnvironmentContext struct (invocation-aware env state)
    ├── InvocationContext enum (systemd, sudo, SSH, etc.)
    ├── DesktopEnvironment enum (GNOME, KDE, Wayland, X11, etc.)
    └── RuntimeDirectoryInfo (validation with permission checks)
```

## Key Types

### SessionIdentity - User + Session Distinction

```cpp
struct SessionIdentity {
    uid_t uid;                          // Who (user account)
    std::optional<std::string> username;
    
    std::optional<uint32_t> session_id;  // Which (logind session ID)
    SessionType type;                    // Login, desktop, shell, background
    
    DesktopEnvironment desktop;          // GNOME, KDE, Wayland, etc.
    DisplayServer display_server;        // X11 or Wayland
    
    InvocationContext invocation_context; // How was this started?
};
```

### EnvironmentContext - Invocation-Aware State

```cpp
struct EnvironmentContext {
    std::optional<std::string> home;
    std::optional<std::string> xdg_runtime_dir;
    
    bool is_sudo;              // Is process elevated via sudo?
    uid_t original_uid;        // UID before elevation
    
    InvocationContext context; // systemd, SSH, direct, etc.
    
    std::filesystem::path resolved_home;
};
```

### RuntimeDirectoryInfo - Validated Runtime Directory

```cpp
enum class RuntimeDirStatus {
    kAvailable,       // Exists and accessible with correct permissions
    kUnavailable,     // Not set or directory missing
    kPermissionError, // Exists but wrong ownership/permissions
};

struct RuntimeDirectoryInfo {
    std::filesystem::path path;
    RuntimeDirStatus status;
};
```

## Environment Inheritance Rules

| Variable | Normal Context | Sudo Context | Systemd Service |
|----------|----------------|--------------|-----------------|
| `HOME`   | kTrust         | kOverride    | kWarn           |
| `USER`   | kOverride      | kOverride    | kWarn           |
| `XDG_RUNTIME_DIR` | kTrust (if set) | kWarn        | kWarn           |

## Invocation Context Detection

Rebuntu detects how a process was started by checking environment variables:

| Variable(s) | Detected Context |
|-------------|------------------|
| `NOTIFY_SOCKET` | systemd service |
| `SYSTEMD_TIMER_*` | systemd timer |
| `SUDO_USER` | sudo (elevated) |
| `SU_FROM` | su |
| `SSH_CLIENT`, `SSH_CONNECTION` | SSH |
| `container` | Container environment |
| None of above | Direct execution |

## Runtime Directory Validation

The runtime directory (`$XDG_RUNTIME_DIR`) must:

1. Be set via environment variable
2. Exist as a directory
3. Be owned by the current effective UID
4. Have permissions 0700 or more restrictive (e.g., 0700, 0750)

Failure at any stage results in `RuntimeDirStatus::kUnavailable` or `kPermissionError`.

## API Reference

### Session Identity Discovery

```cpp
SessionIdentity discover_session_identity();
// Returns full session identity for current process

SessionIdentity build_session_identity_for_uid(uid_t uid);
// Build identity for a specific UID (no invocation detection)
```

### Desktop/Display Detection

```cpp
DesktopEnvironment detect_desktop_environment();
// Returns: GNOME, KDE, XFCE, Sway, Wayland, or kNone

DisplayServer detect_display_server();
// Returns: X11, Wayland, or kNone
```

### Environment Context

```cpp
EnvironmentContext build_current_env_context();
// Build context for current process with invocation detection

std::filesystem::path get_canonical_home(const EnvironmentContext& ctx);
// Get HOME respecting sudo/SU elevation

std::filesystem::path get_runtime_dir(const EnvironmentContext& ctx);
// Get runtime directory with fallback logic
```

### Runtime Directory Management

```cpp
RuntimeDirectoryInfo discover_runtime_directory();
// Discover and validate current process's runtime directory

RuntimeDirectoryInfo get_runtime_directory_for_uid(uid_t uid);
// Get runtime path for a specific UID (no validation)

bool ensure_runtime_directory(const EnvironmentContext& ctx, std::filesystem::path* out_path = nullptr);
// Ensure runtime directory exists (returns true if available)
```

### Invocation Context Detection

```cpp
InvocationContext detect_invocation_context();
// Analyze environment variables to determine how process was started

bool is_systemd_service();
bool is_running_under_sudo(uid_t* original_uid = nullptr);
bool is_running_via_ssh();
```

## Usage Examples

### Basic Session Identity Discovery

```cpp
#include <system/environment/sessions.hpp>

using namespace rebuntu::environment::sessions;

auto identity = discover_session_identity();

std::cout << "User: " << identity.username.value() << "\n";
std::cout << "Session Type: " << to_string(identity.type) << "\n";
std::cout << "Desktop: " << to_string(identity.desktop) << "\n";
std::cout << "Display: " << to_string(identity.display_server) << "\n";
```

### Runtime Directory Validation

```cpp
auto rt_info = discover_runtime_directory();

if (!rt_info.is_valid()) {
    if (rt_info.status == RuntimeDirStatus::kPermissionError) {
        std::cerr << "Runtime directory has wrong permissions\n";
    } else {
        std::cerr << "Runtime directory unavailable\n";
    }
    return 1;
}

auto session_dir = rt_info.path / "rebuntu";
mkdir(session_dir.c_str(), 0700);
```

### Environment Context with Sudo Handling

```cpp
auto ctx = build_current_env_context();

if (ctx.is_sudo) {
    // Use original user's home, not root's
    auto home = get_canonical_home(ctx);
    
    // XDG directories follow the original user
    auto config_dir = home / ".config" / "rebuntu";
}
```

## Implementation Files

| File | Purpose |
|------|---------|
| `cpp/include/system/environment/sessions.hpp` | API contract (Phase 2.8) |
| `cpp/src/sessions.cpp` | Implementation |
| `cpp/tests/test_sessions.cpp` | Unit tests |
| `cpp/src/CMakeLists.txt` | Added sessions.cpp to build |
| `cpp/tests/CMakeLists.txt` | Added test_sessions to CTest |

## Test Coverage

Tests verify:

1. **SessionIdentity** - Default values and structure
2. **EnvironmentContext** - Sudo detection and path resolution
3. **Runtime Directory**:
   - Missing env var → kUnavailable
   - Valid directory with correct permissions → kAvailable  
   - Wrong permissions → kPermissionError
4. **Invocation Context Detection**: systemd, sudo, SSH, direct execution
5. **Environment Policy**: Trust vs Override based on elevation state

## Verification Evidence

```bash
# Build verification
cd cpp/Build && make test_sessions
# Output: [100%] Built target test_sessions

# Test execution
./cpp/Build/tests/test_sessions
# Expected output:
# Testing Sessions & Runtime Identity (Phase 2.8)...
#
# [ RUN      ] SessionsEnum.SessionTypeToString
# [       OK ] SessionsEnum.SessionTypeToString
# [ RUN      ] EnvironmentContext.DefaultValues
# [       OK ] EnvironmentContext.DefaultValues
# [ RUN      ] RuntimeDirectory.DiscoverWithoutEnvVar
# [       OK ] RuntimeDirectory.DiscoverWithoutEnvVar
# ...
#
# All tests passed!

# Full test suite
ctest -R unit.sessions
```

## Security Considerations

1. **Runtime Directory Ownership**: Always verify directory is owned by current UID
2. **Permission Checking**: Reject world-readable/writable runtime directories
3. **Sudo Elevation**: When elevated, use original user's paths, not root's
4. **Environment Policy**: Don't blindly trust environment variables - validate context

## Deferrals (Later Phases)

- **D-Bus Integration**: Full logind session tracking (deferred to Phase 38)
- **Seat Management**: Multi-seat support via systemd-logind D-Bus API
- **Session Lifecycle Events**: Monitor session creation/destruction
- **Desktop Environment Detection**: More detailed detection via XDG spec

## Build Integration Evidence

This phase was partially implemented in `src/system/environment/sessions.hpp/.cpp`
but was not integrated into the build system. The following changes were applied:

### CMake Integration (Phase 2.8)

| File | Change |
|------|--------|
| `cpp/CMakeLists.txt` | Added `rebuntu-sessions` library target, linked to rebuntu-core |
| `cpp/src/rebuntu/CMakeLists.txt` | Added sessions sources to rebuntu executable |
| `cpp/tests/CMakeLists.txt` | Added test_sessions executable and CTest entry |

### Test Results

```
ctest --output-on-failure
100% tests passed, 0 tests failed out of 21
test_sessions: All 24 individual tests PASSED
```

### Verification Commands

```bash
# Build the sessions module
cd cpp/Build && make rebuntu-sessions

# Run sessions-specific tests
ctest -R test_sessions --output-on-failure

# Full test suite (all environment modules)
ctest --output-on-failure
```

## Phase Progression

```
Phase 2.1: user_identity.hpp    → uid_t, gid_t observation
Phase 2.2: group_membership.hpp → Group membership primitives  
Phase 2.3: ownership.hpp        → OWNERSHIP & PERMISSIONS
Phase 2.4: privilege.hpp        → PRIVILEGE & ELEVATION
Phase 2.5: capability_state.hpp → LINUX CAPABILITIES
Phase 2.6: authorization.hpp    → AUTHORIZATION (system/user scope)
Phase 2.7: scope.hpp            → SYSTEM/USER/SESSION SCOPE
Phase 2.8: sessions.hpp         → SESSIONS & RUNTIME IDENTITY (THIS PHASE)
```

## Conclusion

Phase 2.8 establishes Rebuntu's session identity model:

✓ **Session Identity** - Distinguishes user account from login session  
✓ **Invocation Context Detection** - Identifies systemd, sudo, SSH, direct execution  
✓ **Runtime Directory Validation** - Verifies existence and permissions  
✓ **Environment Policy** - Context-aware trust decisions for environment variables  
✓ **Desktop/Display Detection** - X11 vs Wayland vs headless detection  

**Status: COMPLETE**