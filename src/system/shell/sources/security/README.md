# security/ — Security-Aware Helpers

## Purpose

Shell-native utilities that help with security-related checks and privilege validation.

## What Belongs Here

| Category | Description |
|----------|-------------|
| Capability checking | Verifying effective user ID (root/non-root) |
| Permission verification | Checking read/write/execute permissions |
| Privilege escalation prevention | Rejecting operations when not privileged |

## What Does NOT Belong Here

| Category | Where to Go |
|----------|-------------|
| Authentication/authorization | Rebuntu security subsystem |
| Secret handling | Rebuntu secrets management |
| Cryptographic operations | Native Linux crypto APIs |

## Examples

* `rebuntu_security_has_capability()` — check if running as root (UID 0)
* `rebuntu_security_can_access()` — verify read/write/execute permission
* `rebuntu_security_require_root()` — fail with error if not privileged

## Dependencies

Uses native Linux utilities:
* Bash `$EUID` variable for effective user ID
* Test operators (`-r`, `-w`, `-x`) for permissions
* Shell arithmetic for comparisons

## Safety Classification

| Class | Description |
|-------|-------------|
| READ_ONLY | Security checks only, no mutation |

## Pipeline Semantics

* stdout: None (exit code indicates result)
* stderr: Error messages when security checks fail
* Exit status: 0 for success/passing check, non-zero for failure

## Notes

Security helpers provide lightweight checks at the shell boundary. For comprehensive
security policy enforcement, use the Rebuntu security subsystem with typed operations.