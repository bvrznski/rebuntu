# coordination/ — Coordination Primitives

## Purpose

Shell-native utilities for coordinating shell operations, particularly around
locking and atomic groups.

## What Belongs Here

| Category | Description |
|----------|-------------|
| File locking | Acquiring exclusive locks using flock |
| Atomic groups | Executing multiple commands atomically |

## What Does NOT Belong Here

| Category | Where to Go |
|----------|-------------|
| Process synchronization | Rebuntu runtime coordination |
| Distributed locking | System-wide mechanisms (Redis, etc.) |
| Complex workflows | Workflow category |

## Examples

* `rebuntu_coord_with_lock()` — execute with file-based exclusive lock
* `rebuntu_coord_atomic_group()` — run multiple commands as atomic group

## Dependencies

Uses native Linux utilities:
* `flock` for file locking
* Bash compound commands (`{ }`) for grouping

## Safety Classification

| Class | Description |
|-------|-------------|
| MUTATING | Lock acquisition may affect concurrent operations |

## Pipeline Semantics

* stdout: Command output (if any)
* stderr: Error messages on lock failure or command errors
* Exit status: 0 for success, non-zero for errors or lock contention

## Notes

Locking is advisory and only effective when all participants use the same lock file.
For robust coordination in complex environments, consider Rebuntu's runtime
coordination facilities.