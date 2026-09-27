# Rebuntu Utmp/Wtmp/Btmp Session Observation Adapter (Phase 5.27)

This module implements native Linux session observation through the standard utmp/wtmp/btmp files.

## Overview

The adapter observes current sessions and login history using:

- **utmp** (`/var/run/utmp`): Current user sessions
- **wtmp** (`/var/log/wtmp`): Login/logout history  
- **btmp** (`/var/log/btmp`): Failed login attempts

## Native Linux Interfaces Used

The implementation uses standard C library functions to read the binary utmp file format:

- `fopen()` / `fread()` - Read binary utmp entries
- `struct utmp` - Standard utmp structure with fields:
  - `ut_type`: Entry type (USER_PROCESS, LOGIN_PROCESS, etc.)
  - `ut_pid`: Process ID
  - `ut_line`: Terminal device name (e.g., "tty1", "pts/0")
  - `ut_id`: Inittab ID
  - `ut_user`: Username
  - `ut_host`: Remote hostname (for SSH connections)
  - `ut_time`: Login timestamp

## Session Types

- **kLogin**: Traditional login via getty/login on TTY devices
- **kDesktop**: Desktop environment sessions (X11/Wayland)
- **kRemote**: Remote connections (SSH, telnet) detected by hostname
- **kSystemdUser**: systemd --user manager session
- **kContainer**: Container-based sessions

## Key Distinctions

1. **Session ≠ User Identity**
   - A single user can have multiple sessions
   - Each session is identified by UID + terminal + start time

2. **No Authentication Inference**
   - Session presence does NOT imply authorized access
   - Login history (wtmp) includes both successful and failed attempts
   - Failed logins are tracked separately in btmp

3. **Provenance Tracking**
   - Each observation includes source ("utmp", "wtmp")
   - Timestamps are preserved for temporal ordering

4. **Bounded Observation**
   - Limits on entries read (default 100 sessions, 50 failed logins)
   - Graceful handling when files don't exist

## Architecture

```
src/adapters/session/utmp/
├── types.hpp         # Typed interfaces and data structures
├── implementation.cpp # Native utmp/wtmp/btmp observation
└── README.md         # This file
```

## Usage Example

```cpp
#include <adapters/session/utmp/types.hpp>

auto adapter = rebuntu::adapters::session::utmp::make_utmp_adapter();

// Get current sessions
auto result = adapter->observe_current_sessions();
for (const auto& session : result.current_sessions) {
    std::cout << "User: " << session.username 
              << " Terminal: " << session.terminal
              << " Duration: " << session.session_duration.count() << "s\n";
}

// Get login history
auto history = adapter->get_login_history(50);

// Get failed logins  
auto failures = adapter->get_failed_logins(20);
```

## File Locations

- `/var/run/utmp` - Current sessions (requires read access)
- `/var/log/wtmp` - Login history (usually world-readable)
- `/var/log/btmp` - Failed logins (typically root-only)

## Limitations

1. No D-Bus integration (deferred to Phase 38 for logind support)
2. Binary format parsing depends on glibc utmp structure
3. Timestamp resolution is limited to seconds
4. No support for modern login records with extended attributes

## Future Enhancements

- Integration with systemd-logind D-Bus interface
- Support for login records with IPv6 addresses
- Extended attributes from recent utmp versions