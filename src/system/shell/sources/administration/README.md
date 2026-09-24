# administration/ — System Administration Helpers

## Purpose

Shell-native utilities for common system administration tasks, particularly
integration with systemd and user management.

## What Belongs Here

| Category | Description |
|----------|-------------|
| Service status queries | Checking service state via systemd or process |
| User existence checks | Verifying user accounts exist |
| Group membership | Listing group members |

## What Does NOT Belong Here

| Category | Where to Go |
|----------|-------------|
| System configuration | Configuration category for shell-facing access |
| User/group creation/modification | Privileged operations (use Rebuntu runtime) |
| Service lifecycle management | systemd directly or Rebuntu service management |

## Examples

* `rebuntu_admin_service_status()` — get service status from systemd
* `rebuntu_admin_user_exists()` — check if user account exists
* `rebuntu_admin_group_members()` — list members of a group

## Dependencies

Uses native Linux utilities:
* `systemctl` for systemd service queries
* `id` command for user verification
* `getent` or `/etc/group` parsing for groups
* `pgrep` as fallback for process-based checks

## Safety Classification

| Class | Description |
|-------|-------------|
| READ_ONLY | Observation and querying only |

## Pipeline Semantics

* stdout: Status information, group member lists
* stderr: Error messages on failure or unavailable tools
* Exit status: 0 for success, non-zero for errors

## Notes

These helpers query existing state without modification. For administrative
actions that mutate system state (create users, start services), use the
Rebuntu runtime with typed operations and proper authorization.