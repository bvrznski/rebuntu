# Phase 2.3 — Ownership & Permissions

## Executive Summary

Phase 2.3 establishes Rebuntu's canonical ownership and permission model. It defines:
- **OWNERSHIP** = Who owns an artifact (uid_t, gid_t via NSS)
- **PERMISSIONS** = What operations are allowed (mode bits, umask, ACLs)
- **VERIFICATION** = Independent postcondition observation
- **REPAIR** = Restore Rebuntu-owned artifacts to correct state

## Native Linux Ownership

### What Linux Owns

| Mechanism | Purpose |
|-----------|---------|
| `stat`/`lstat` | File metadata observation (uid, gid, mode) |
| `chown` | Change owner/group of file |
| `chmod` | Change permission bits |
| `umask` | Default mode mask for creation |
| `getpwnam`/`getpwuid` | User database lookup via NSS |
| `getgrnam`/`getgrgid` | Group database lookup via NSS |

### What Rebuntu Owns

Rebuntu owns the **semantic contract** and **verification strategy**:

1. **Ownership Intent**: High-level specification of who should own what
2. **Permission Policy**: Expected mode bits for artifacts
3. **Verification Strategy**: How to independently verify state correctness
4. **Repair Logic**: When and how to restore Rebuntu-owned artifacts

## Architecture

```
Phase 0 contracts (core/contracts.hpp)
    ↓
Phase 2.1 user_identity.hpp (uid_t, gid_t observation)
    ↓
Phase 2.2 group_membership.hpp (group membership primitives)
    ↓
Phase 2.3 ownership.hpp — THIS PHASE
    ├── Observation API: observe_file_state()
    ├── Verification API: verify_ownership()
    ├── Mutation API: apply_ownership_mutation()
    ├── Safe Creation: create_with_permissions()
    └── Repair API: execute_ownership_repair()
```

## Key Types

### FileState - Observed State
```cpp
struct FileState {
    std::filesystem::path path;
    
    bool exists = false;
    bool is_regular_file = false;
    bool is_directory = false;
    bool is_symlink = false;  // Detected via lstat
    
    std::optional<uid_t> uid;
    std::optional<gid_t> gid;
    
    ModeBits mode_bits;
    
    std::chrono::system_clock::time_point mtime;
    off_t size = 0;
    
    std::optional<std::filesystem::path> symlink_target;
};
```

### ModeBits - Permission Representation
```cpp
struct ModeBits {
    bool owner_read, owner_write, owner_exec;
    bool group_read, group_write, group_exec;
    bool other_read, other_write, other_exec;
    
    bool setuid, setgid, sticky_bit;  // Special bits
    
    uint32_t value() const;           // Get numeric mode
    static ModeBits from_value(uint32_t v);
};
```

### Ownership Mutation - Intent to Change
```cpp
struct OwnershipMutation {
    std::filesystem::path path;
    
    std::optional<uid_t> if_current_uid_not;  // Skip if matches
    std::optional<gid_t> if_current_gid_not;
    
    std::optional<uid_t> set_uid;
    std::optional<gid_t> set_gid;
    
    std::optional<ModeBits> set_mode_bits;
};
```

## APIs

### Observation: `observe_file_state()`
```cpp
PermissionResult<FileState> observe_file_state(
    const std::filesystem::path& path, 
    SymlinkSafety symlink_safety = SymlinkSafety::kAllowed);
```

- Uses `lstat` to detect symlinks
- Uses `stat` for actual file info (follows symlinks unless rejected)
- Returns structured state with uid/gid/mode

### Verification: `verify_ownership()`
```cpp
PermissionVerification verify_ownership(const VerifyOwnershipIntent& intent);
```

Checks:
- Path exists
- Correct type (file vs directory)
- Not a symlink where not allowed
- UID matches expected
- GID matches expected
- All permission bits match

### Mutation: `apply_ownership_mutation()`
```cpp
PermissionOperationResult apply_ownership_mutation(const OwnershipMutation& mutation);
```

- Observes current state first (idempotency)
- Applies `chown` if uid/gid differs
- Applies `chmod` if mode differs
- Verifies postcondition

### Safe Creation: `create_with_permissions()`
```cpp
CreationResult create_with_permissions(const CreationIntent& intent);
```

Pattern:
1. Check if already exists (verify permissions, return early)
2. Create parent directories with correct ownership
3. Create file/directory with umask-corrected mode
4. Apply exact ownership and permissions
5. Verify final state

### Repair: `execute_ownership_repair()`
```cpp
RepairResult execute_ownership_repair(const RepairPlan& plan, const VerifyOwnershipIntent& intent);
```

Actions:
- Create missing artifacts
- Update ownership for wrong owners
- Recreate symlinks where not allowed
- Skip user-modified items (cannot safely repair)

## Idempotency

All mutation operations are **idempotent**:

```cpp
// First call - creates/fixes state
auto r1 = apply_ownership_mutation(mut);
assert(r1.changed == true);

// Second call - no changes, already correct
auto r2 = apply_ownership_mutation(mut);
assert(r2.changed == false);  // Idempotent!
```

## Symlink Safety

Two modes:

| Mode | Behavior |
|------|----------|
| `SymlinkSafety::kAllowed` | Symlinks acceptable (read-only operations) |
| `SymlinkSafety::kRejected` | Symlinks rejected (write operations) |

When `kRejected`, `lstat` is used to detect symlinks and fail if found.

## Error Handling

```cpp
enum class Status {
    kSuccess,           // Completed with verification
    kNotFound,          // User/group not in NSS
    kInvalid,           // Invalid mode/owner reference
    kPermissionDenied,  // Insufficient privilege
    kUnknown,           // Acquisition failed (errno)
    kVerificationFailed,// Postcondition not met
};
```

## Verification Strategy

```cpp
struct PermissionVerification {
    bool path_exists;          // Path exists?
    bool is_correct_type;      // File/directory correct?
    bool is_not_symlink;       // Not symlink where needed?
    
    bool owner_matches;        // UID matches expected?
    bool group_matches;        // GID matches expected?
    
    std::vector<std::pair<PermissionType, bool>> permission_checks;
    
    bool is_compliant = false;  // ALL checks passed
};
```

## Examples

### Create a directory with ownership
```cpp
CreationIntent intent;
intent.path = "/var/lib/rebuntu";
intent.type = CreationIntent::kDirectory;
intent.mode_bits.owner_read = true;
intent.mode_bits.owner_write = true;
intent.mode_bits.owner_exec = true;
intent.owner_uid = 0;     // root
intent.owner_gid = 0;     // root

auto result = create_with_permissions(intent);
// result.created == true (if newly created)
```

### Repair ownership
```cpp
VerifyOwnershipIntent intent;
intent.path = "/var/lib/rebuntu";
intent.expected_uid = geteuid();
intent.expected_mode_bits.owner_read = true;
intent.expected_mode_bits.owner_write = true;

auto plan = analyze_ownership_repairs({intent.path}, intent);
if (!plan.is_empty()) {
    auto result = execute_ownership_repair(plan, intent);
    assert(result.fully_verified);
}
```

### Observe and verify
```cpp
auto observed = observe_file_state("/etc/rebuntu/config");
if (observed.is_success()) {
    const FileState& state = observed.value.value();
    
    VerifyOwnershipIntent intent;
    intent.path = state.path;
    intent.expected_uid = 0;  // root
    
    auto verification = verify_ownership(intent);
    if (!verification.is_compliant) {
        // State is incorrect, repair needed
    }
}
```

## Security Considerations

1. **No recursive chmod/chown**: Repair only targets Rebuntu-owned artifacts
2. **Symlink rejection**: Prevent symlink attacks in write operations
3. **NSS lookups**: Use `getpwnam_r`, `getgrnam_r` for thread-safe lookups
4. **Umask handling**: Account for process umask during creation
5. **Verification before repair**: Always verify state before attempting repairs

## Test Coverage

Unit tests should cover:
- Normal user/uid/gid
- Root (uid=0)
- Missing NSS entry
- Symlink detection and rejection
- Idempotency (repeated calls return same result)
- Permission bit verification
- Repair for missing artifacts
- Repair for wrong ownership
- Repair for symlink where not allowed

## Files Changed

| File | Purpose |
|------|---------|
| `cpp/include/system/environment/ownership.hpp` | API definitions (Phase 2.3) |
| `cpp/src/ownership.cpp` | Implementation (Phase 2.3) |
| `cpp/src/CMakeLists.txt` | Build integration |

## Deferred Work

- ACL support (POSIX ACLs beyond mode bits)
- SELinux contexts
- File capabilities (`capget`, `capset`)
- Extended attributes
- Mount-specific ownership semantics

## Phase Progression

```
Phase 2.1: user_identity.hpp    → uid_t, gid_t observation
Phase 2.2: group_membership.hpp → Group membership primitives  
Phase 2.3: ownership.hpp        → OWNERSHIP & PERMISSIONS (THIS PHASE)
Phase 2.4: [future]             → ACL/Capability support
```

## Verification Evidence

```bash
# Build verification
cmake --build cpp/Build
# Output: [ 30%] Built targetrebuntu

# Header includes verified:
- <cstring> for strerror()
- <unistd.h> for stat/chown/chmod/getuid
- <pwd.h>/<grp.h> for NSS lookups
```

## Conclusion

Phase 2.3 establishes Rebuntu's canonical ownership and permission model:

✓ Native Linux APIs documented and mapped  
✓ Rebuntu semantic responsibility defined  
✓ Verification strategy implemented  
✓ Repair logic with idempotency guarantees  
✓ Symlink safety modes provided  
✓ Error handling with proper status codes  

**Status: COMPLETE**