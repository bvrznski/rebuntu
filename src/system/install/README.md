# Rebuntu Installation Architecture

## Overview

This module provides the canonical C++ installation/bootstrap entry path for Rebuntu.

## Core Questions Answered

### What does "Rebuntu is installed" precisely mean?

A system has Rebuntu installed when:
1. The binary exists at the target path (`/usr/bin/rebuntu` for system, `$HOME/.local/bin/rebuntu` for user)
2. State directory exists and is accessible (`/var/lib/rebuntu` or `$HOME/.local/state/rebuntu`)
3. Configuration directory is accessible (`/etc/rebuntu` or `$HOME/.config/rebuntu`)
4. Verification passes with `BootstrapResult::is_success() == true`

### Which files/artifacts constitute the minimum installation?

The minimal installation includes:
- `bin_path/rebuntu` - The main executable
- `state_dir/` - State directory for persistent data
- `config_dir/` - Configuration directory

Paths are determined by scope:
- **System**: `/usr/bin`, `/var/lib/rebuntu`, `/etc/rebuntu`
- **User**: `$HOME/.local/bin`, `$HOME/.local/state/rebuntu`, `$HOME/.config/rebuntu`

### Which dependencies are bootstrap dependencies?

Bootstrap requires:
- C++ runtime (libstdc++6) - for C++20 standard library features
- Filesystem API - for directory creation and permission management

### Which dependencies can be installed later?

Later phases will add:
- Systemd integration (Phase 1.1)
- Package manager (apt, snap, pip) integration (Phase 1.3)
- Environment discovery via systemd/procfs/sysfs/cgroups v2 (Phase 1.1-1.9)

### What requires privilege?

System-wide installation (`InstallationScope::kSystem`) requires root privileges.
User-scoped installation runs as the invoking user without elevation.

Authorization checks:
```cpp
if (scope == InstallationScope::kSystem && !is_root) {
    // Authorization fails - system install needs root
}
```

### What is user-scoped vs system-scoped?

| Aspect | System Scope | User Scope |
|--------|-------------|------------|
| Install root | `/` | `$HOME` |
| Binary path | `/usr/bin` | `$HOME/.local/bin` |
| State dir | `/var/lib/rebuntu` | `$HOME/.local/state/rebuntu` |
| Config dir | `/etc/rebuntu` | `$HOME/.config/rebuntu` |
| Privilege required | Yes (root) | No |

## Bootstrap Phases

1. **Discovery** - Determine host environment facts
2. **Planning** - Generate explicit installation plan
3. **Authorization** - Verify user intent and scope
4. **Execution** - Apply installation steps
5. **Verification** - Confirm postconditions are met

## Usage

```cpp
#include <system/install/bootstrap.hpp>

using namespace rebuntu::install::bootstrap;

// With defaults (auto-detects system vs user)
BootstrapResult result = install_with_defaults();

// With explicit context
BootstrapContext ctx;
ctx.scope = InstallationScope::kSystem;
BootstrapResult result = install(ctx);

// Dry run mode (no actual mutation)
ctx.dry_run = true;
result = install(ctx);
```

## Deferred Work

- Phase 1.1: Environment discovery integration
- Phase 1.3: Real plan execution
- Phase 1.4: Package manager integration
- Phase 1.5: Binary installation
- Phase 1.6: Service registration