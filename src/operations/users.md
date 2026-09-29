# User Management Operations (Phase 6.77)

## Overview

This directory contains Rebuntu's canonical User Management Operation implementations.

## Operations

### user.create
Create a new system user account with typed inputs and full contract semantics.

**Inputs:**
- `username` (required): The login name for the new user
- `uid` (optional): Specific UID to assign
- `home_dir` (optional): Path to home directory
- `shell` (optional): Login shell path
- `skip_if_exists` (default: false): Don't error if user already exists

**Side Effects:** MUTATING | PRIVILEGED
**Idempotency:** CONDITIONALLY_IDEMPOTENT
**Reversibility:** REVERSIBLE

### user.delete
Delete a system user account.

**Inputs:**
- `username` (required): The username to delete
- `remove_home` (default: false): Also remove home directory?

**Side Effects:** MUTATING | PRIVILEGED | DESTRUCTIVE
**Idempotency:** IDEMPOTENT
**Reversibility:** IRREVERSIBLE

### user.query
Query information about a system user (read-only).

**Inputs:**
- `username` (required): The username to query

**Side Effects:** NONE
**Idempotency:** IDEMPOTENT

## Implementation Notes

1. **Native Mechanism**: Uses `useradd`/`userdel` via bounded subprocess with argv-style invocation
2. **Privilege**: Operations require elevated privilege (effective UID 0)
3. **Verification**: Postconditions verified by observing `/etc/passwd`
4. **Evidence**: Process exit result and state observations captured for audit trail

## Architecture Flow

```
CommandIntent (typed)
    ↓
user_create() / user_delete() / user_query()
    ↓
Precondition checks (privilege, input validation)
    ↓
Native subprocess invocation (bounded argv-style)
    ↓
Postcondition verification (/etc/passwd observation)
    ↓
OperationResult with evidence chain