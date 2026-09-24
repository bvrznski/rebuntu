# state/ — Shell State Management

## Purpose

Shell-native utilities for managing temporary shell-level state using environment variables.

## What Belongs Here

| Category | Description |
|----------|-------------|
| State storage | Setting key-value pairs in shell environment |
| State retrieval | Reading state values with default fallbacks |
| State cleanup | Clearing all Rebuntu-managed state |

## What Does NOT Belong Here

| Category | Where to Go |
|----------|-------------|
| Persistent state | Filesystem or database |
| System-wide state | systemd, D-Bus, or Rebuntu runtime |
| Complex data structures | Structures category for arrays/maps |

## Examples

* `rebuntu_state_set()` — store value in REBUNTU_STATE_ variable
* `rebuntu_state_get()` — retrieve stored value
* `rebuntu_state_clear()` — clear all state variables

## Dependencies

Uses native Linux utilities:
* Bash environment variables for storage
* Parameter expansion for access and defaults

## Safety Classification

| Class | Description |
|-------|-------------|
| MUTATING | Environment variable modification |

## Pipeline Semantics

* stdout: Retrieved values (for `rebuntu_state_get`)
* stderr: Error messages on failure
* Exit status: 0 for success, non-zero for errors

## Notes

State is stored in environment variables with the prefix `REBUNTU_STATE_`.
This state is process-scoped and lost when the shell exits.