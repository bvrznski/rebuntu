// rebuntu::environment::ownership — Ownership & Permissions Implementation (Phase 2.3)
//
// This implements Rebuntu's canonical ownership and permission model:
//
//   * OWNERSHIP = Who owns an artifact (uid_t, gid_t via NSS)
//   * PERMISSIONS = What operations are allowed (mode bits, umask, ACLs)
//   * VERIFICATION = Independent postcondition observation
//   * REPAIR = Restore Rebuntu-owned artifacts to correct state

#include <observation/environment/ownership.hpp>

#include <cstring>   // strerror
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pwd.h>
#include <grp.h>
#include <limits.h>  // PATH_MAX
#include <fstream>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <algorithm>

namespace rebuntu::environment::ownership {

// ============================================================================
// Utility: Error handling helpers
// ============================================================================

static std::string errno_string(int err) {
    char buffer[256];
    const char* msg = strerror(err);
    if (msg) {
        return std::string(msg);
    }
    return "Unknown error";
}

static PermissionResult<FileState> make_unknown_result(const std::filesystem::path& path, const std::string& msg) {
    PermissionResult<FileState> r;
    r.status = PermissionResult<FileState>::Status::kUnknown;
    r.error_code = kErrorAcquisitionFailed;
    r.error_message = msg;
    PermissionEvidence e;
    e.source = "errno";
    e.observed_at = std::chrono::system_clock::now();
    r.evidence.push_back(std::move(e));
    return r;
}

// ============================================================================
// Observation API - What is the current state?
// ============================================================================

PermissionResult<FileState> observe_file_state(const std::filesystem::path& path, 
                                                 SymlinkSafety symlink_safety) {
    PermissionResult<FileState> result;
    
    struct stat lstat_buf;
    if (lstat(path.c_str(), &lstat_buf) != 0) {
        // Path doesn't exist or lstat failed
        if (errno == ENOENT || errno == EACCES || errno == EPERM) {
            result.status = PermissionResult<FileState>::Status::kNotFound;
            result.error_code = kErrorNoSuchUser;
            result.error_message = "File not found: " + path.string();
        } else {
            result = make_unknown_result(path, errno_string(errno));
        }
        return result;
    }
    
    FileState state;
    state.path = path;
    
    // Check if it's a symlink first (using lstat which doesn't follow)
    state.is_symlink = S_ISLNK(lstat_buf.st_mode);
    
    // Use stat for actual file info (follows symlinks unless rejected)
    struct stat stat_buf;
    bool use_lstat = (symlink_safety == SymlinkSafety::kRejected && state.is_symlink);
    
    if (use_lstat) {
        stat_buf = lstat_buf;
    } else if (stat(path.c_str(), &stat_buf) != 0) {
        result = make_unknown_result(path, errno_string(errno));
        return result;
    }
    
    // Record file type
    state.is_regular_file = S_ISREG(stat_buf.st_mode);
    state.is_directory = S_ISDIR(stat_buf.st_mode);
    state.exists = true;
    
    // Ownership
    state.uid = stat_buf.st_uid;
    state.gid = stat_buf.st_gid;
    
    // Mode bits
    state.mode_bits = ModeBits::from_value(stat_buf.st_mode & 07777);
    
    // Timestamps and size
    state.mtime = std::chrono::system_clock::from_time_t(stat_buf.st_mtime);
    state.size = stat_buf.st_size;
    
    // Symlink target (only set if is_symlink)
    if (state.is_symlink) {
        char link_target[PATH_MAX];
        ssize_t len = readlink(path.c_str(), link_target, sizeof(link_target) - 1);
        if (len >= 0) {
            link_target[len] = '\0';
            state.symlink_target = std::filesystem::path(link_target);
        }
    }
    
    result.status = PermissionResult<FileState>::Status::kSuccess;
    result.value = std::move(state);
    return result;
}

PermissionResult<uid_t> resolve_owner_uid(const OwnerRef& owner_ref) {
    PermissionResult<uid_t> result;
    
    if (owner_ref.kind == OwnerRef::Kind::kByName) {
        if (!owner_ref.name.has_value()) {
            result.status = PermissionResult<uid_t>::Status::kInvalid;
            result.error_code = kErrorNoSuchUser;
            result.error_message = "OwnerRef by_name requires name";
            return result;
        }
        
        struct passwd pwd;
        struct passwd* result_pwd = nullptr;
        char buffer[4096];
        
        int err = getpwnam_r(owner_ref.name->c_str(), &pwd, buffer, sizeof(buffer), &result_pwd);
        
        if (err != 0 || result_pwd == nullptr) {
            result.status = PermissionResult<uid_t>::Status::kNotFound;
            result.error_code = kErrorNoSuchUser;
            result.error_message = "User not found: " + owner_ref.name.value();
            return result;
        }
        
        result.status = PermissionResult<uid_t>::Status::kSuccess;
        result.value = pwd.pw_uid;
    } else {
        // kById - just validate the uid
        if (!owner_ref.id.has_value()) {
            result.status = PermissionResult<uid_t>::Status::kInvalid;
            result.error_code = kErrorNoSuchUser;
            result.error_message = "OwnerRef by_id requires id";
            return result;
        }
        
        // Validate by attempting to look up the uid
        struct passwd pwd;
        struct passwd* result_pwd = nullptr;
        char buffer[4096];
        
        int err = getpwuid_r(owner_ref.id.value(), &pwd, buffer, sizeof(buffer), &result_pwd);
        
        if (err != 0 || result_pwd == nullptr) {
            // uid doesn't exist in NSS, but we'll return it anyway
            // This allows setting ownership for non-existent users (for idempotency)
            result.status = PermissionResult<uid_t>::Status::kNotFound;
            result.error_code = kErrorNoSuchUser;
            result.error_message = "User not found in NSS: " + std::to_string(owner_ref.id.value());
        } else {
            result.status = PermissionResult<uid_t>::Status::kSuccess;
            result.value = owner_ref.id.value();
        }
    }
    
    return result;
}

PermissionResult<gid_t> resolve_group_gid(const OwnerRef& group_ref) {
    PermissionResult<gid_t> result;
    
    if (group_ref.kind == OwnerRef::Kind::kByName) {
        if (!group_ref.name.has_value()) {
            result.status = PermissionResult<gid_t>::Status::kInvalid;
            result.error_code = kErrorNoSuchGroup;
            result.error_message = "OwnerRef by_name requires name";
            return result;
        }
        
        struct group grp;
        struct group* result_grp = nullptr;
        char buffer[4096];
        
        int err = getgrnam_r(group_ref.name->c_str(), &grp, buffer, sizeof(buffer), &result_grp);
        
        if (err != 0 || result_grp == nullptr) {
            result.status = PermissionResult<gid_t>::Status::kNotFound;
            result.error_code = kErrorNoSuchGroup;
            result.error_message = "Group not found: " + group_ref.name.value();
            return result;
        }
        
        result.status = PermissionResult<gid_t>::Status::kSuccess;
        result.value = grp.gr_gid;
    } else {
        // kById
        if (!group_ref.id.has_value()) {
            result.status = PermissionResult<gid_t>::Status::kInvalid;
            result.error_code = kErrorNoSuchGroup;
            result.error_message = "OwnerRef by_id requires id";
            return result;
        }
        
        // Validate by attempting to look up the gid
        struct group grp;
        struct group* result_grp = nullptr;
        char buffer[4096];
        
        int err = getgrgid_r(group_ref.id.value(), &grp, buffer, sizeof(buffer), &result_grp);
        
        if (err != 0 || result_grp == nullptr) {
            result.status = PermissionResult<gid_t>::Status::kNotFound;
            result.error_code = kErrorNoSuchGroup;
            result.error_message = "Group not found in NSS: " + std::to_string(group_ref.id.value());
        } else {
            result.status = PermissionResult<gid_t>::Status::kSuccess;
            result.value = group_ref.id.value();
        }
    }
    
    return result;
}

// ============================================================================
// Permission Verification - Is the current state correct?
// ============================================================================

PermissionVerification verify_ownership(const VerifyOwnershipIntent& intent) {
    PermissionVerification verification;
    verification.verification_source = "verify_ownership";
    
    // Observe current state
    auto observed = observe_file_state(intent.path, intent.symlink_safety);
    
    if (!observed.is_success() || !observed.value.has_value()) {
        verification.is_compliant = false;
        return verification;
    }
    
    const FileState& state = observed.value.value();
    
    // Check path exists
    verification.path_exists = state.exists;
    
    // Check type is correct (not symlink where not allowed)
    verification.is_not_symlink = !state.is_symlink || 
                                  (intent.symlink_safety == SymlinkSafety::kAllowed);
    
    if (intent.expected_uid.has_value()) {
        verification.owner_matches = state.uid.has_value() && (state.uid.value() == intent.expected_uid.value());
    } else {
        // No expectation - consider it a pass
        verification.owner_matches = true;
    }
    
    if (intent.expected_gid.has_value()) {
        verification.group_matches = state.gid.has_value() && (state.gid.value() == intent.expected_gid.value());
    } else {
        verification.group_matches = true;
    }
    
    // Check mode bits
    auto check_mode_bit = [](const ModeBits& obs, const ModeBits& exp, PermissionType pt) -> bool {
        switch (pt) {
            case PermissionType::kOwnerRead:   return obs.owner_read == exp.owner_read;
            case PermissionType::kOwnerWrite:  return obs.owner_write == exp.owner_write;
            case PermissionType::kOwnerExec:   return obs.owner_exec == exp.owner_exec;
            case PermissionType::kGroupRead:   return obs.group_read == exp.group_read;
            case PermissionType::kGroupWrite:  return obs.group_write == exp.group_write;
            case PermissionType::kGroupExec:   return obs.group_exec == exp.group_exec;
            case PermissionType::kOtherRead:   return obs.other_read == exp.other_read;
            case PermissionType::kOtherWrite:  return obs.other_write == exp.other_write;
            case PermissionType::kOtherExec:   return obs.other_exec == exp.other_exec;
            case PermissionType::kSetuid:      return obs.setuid == exp.setuid;
            case PermissionType::kSetgid:      return obs.setgid == exp.setgid;
            case PermissionType::kStickyBit:   return obs.sticky_bit == exp.sticky_bit;
        }
        return false;
    };
    
    // Build permission check results
    std::vector<PermissionType> all_types = {
        PermissionType::kOwnerRead, PermissionType::kOwnerWrite, PermissionType::kOwnerExec,
        PermissionType::kGroupRead, PermissionType::kGroupWrite, PermissionType::kGroupExec,
        PermissionType::kOtherRead, PermissionType::kOtherWrite, PermissionType::kOtherExec,
        PermissionType::kSetuid, PermissionType::kSetgid, PermissionType::kStickyBit
    };
    
    for (auto pt : all_types) {
        verification.permission_checks.emplace_back(pt, check_mode_bit(state.mode_bits, intent.expected_mode_bits, pt));
    }
    
    // Overall compliance: all checks must pass
    verification.is_compliant = 
        verification.path_exists &&
        verification.is_not_symlink &&
        verification.owner_matches &&
        verification.group_matches;
    
    for (const auto& [pt, passed] : verification.permission_checks) {
        if (!passed) {
            verification.is_compliant = false;
            break;
        }
    }
    
    return verification;
}

// ============================================================================
// Permission Operations - Mutate state
// ============================================================================

PermissionOperationResult apply_ownership_mutation(const OwnershipMutation& mutation) {
    PermissionOperationResult result;
    
    // First observe current state
    auto observed = observe_file_state(mutation.path, SymlinkSafety::kRejected);
    
    if (!observed.is_success() || !observed.value.has_value()) {
        result.verified = false;
        return result;
    }
    
    const FileState& state = observed.value.value();
    
    bool needs_change = false;
    uid_t new_uid = state.uid.value_or(0);
    gid_t new_gid = state.gid.value_or(0);
    
    // Check if we need to change UID
    if (mutation.set_uid.has_value()) {
        if (!mutation.if_current_uid_not.has_value() || 
            mutation.if_current_uid_not.value() != state.uid.value_or(0)) {
            needs_change = true;
            new_uid = mutation.set_uid.value();
        }
    } else if (mutation.if_current_uid_not.has_value() && 
               mutation.if_current_uid_not.value() == state.uid.value_or(0)) {
        // Skip because current matches exclusion
        return result;  // No-op
    }
    
    // Check if we need to change GID
    if (mutation.set_gid.has_value()) {
        if (!mutation.if_current_gid_not.has_value() || 
            mutation.if_current_gid_not.value() != state.gid.value_or(0)) {
            needs_change = true;
            new_gid = mutation.set_gid.value();
        }
    } else if (mutation.if_current_gid_not.has_value() && 
               mutation.if_current_gid_not.value() == state.gid.value_or(0)) {
        return result;  // No-op
    }
    
    // Apply ownership change if needed
    if (needs_change) {
        if (chown(mutation.path.c_str(), new_uid, new_gid) != 0) {
            result.verified = false;
            return result;
        }
        result.changed = true;
    }
    
    // Apply mode change if specified
    if (mutation.set_mode_bits.has_value()) {
        ModeBits desired = mutation.set_mode_bits.value();
        
        // Check current mode first (idempotency)
        if (state.mode_bits.value() != desired.value()) {
            if (chmod(mutation.path.c_str(), desired.value()) != 0) {
                result.verified = false;
                return result;
            }
            result.changed = true;
        }
    }
    
    // Verify postcondition
    auto verified = verify_ownership({
        .path = mutation.path,
        .expected_uid = mutation.set_uid,
        .expected_gid = mutation.set_gid,
        .expected_mode_bits = mutation.set_mode_bits.value_or(ModeBits{}),
        .symlink_safety = SymlinkSafety::kRejected
    });
    
    result.verified = verified.is_compliant;
    
    return result;
}

PermissionOperationResult apply_permission_change(const PermissionMutation& mutation) {
    PermissionOperationResult result;
    
    // Observe current state for idempotency check
    auto observed = observe_file_state(mutation.path, SymlinkSafety::kRejected);
    
    if (!observed.is_success() || !observed.value.has_value()) {
        result.verified = false;
        return result;
    }
    
    const FileState& state = observed.value.value();
    
    // Check if change is needed (idempotency)
    if (state.mode_bits.value() == mutation.mode_bits.value()) {
        // Already correct - verify it
        auto verified = verify_ownership({
            .path = mutation.path,
            .expected_uid = std::nullopt,
            .expected_gid = std::nullopt,
            .expected_mode_bits = mutation.mode_bits,
            .symlink_safety = SymlinkSafety::kRejected
        });
        
        result.verified = verified.is_compliant;
        return result;  // No-op but verified
    }
    
    // Apply mode change
    if (chmod(mutation.path.c_str(), mutation.mode_bits.value()) != 0) {
        result.verified = false;
        return result;
    }
    result.changed = true;
    
    // Verify postcondition
    auto verified = verify_ownership({
        .path = mutation.path,
        .expected_uid = std::nullopt,
        .expected_gid = std::nullopt,
        .expected_mode_bits = mutation.mode_bits,
        .symlink_safety = SymlinkSafety::kRejected
    });
    
    result.verified = verified.is_compliant;
    
    return result;
}

// ============================================================================
// Safe Creation - Create files/directories with correct permissions
// ============================================================================

CreationResult create_with_permissions(const CreationIntent& intent) {
    CreationResult result;
    result.postcondition_state.path = intent.path;
    
    // Check if path already exists
    std::error_code ec;
    bool exists = std::filesystem::exists(intent.path, ec);
    
    if (exists) {
        result.already_existed = true;
        
        // Verify permissions are correct
        auto observed = observe_file_state(intent.path, SymlinkSafety::kRejected);
        
        if (observed.is_success() && observed.value.has_value()) {
            const FileState& state = observed.value.value();
            
            bool needs_chown = false;
            bool needs_chmod = false;
            
            if (intent.owner_uid != state.uid.value_or(0)) {
                needs_chown = true;
            }
            if (intent.owner_gid != state.gid.value_or(0)) {
                needs_chown = true;
            }
            if (intent.mode_bits.value() != state.mode_bits.value()) {
                needs_chmod = true;
            }
            
            if (needs_chown) {
                if (chown(intent.path.c_str(), intent.owner_uid, intent.owner_gid) != 0) {
                    result.error_code = kErrorPermissionDenied;
                    result.error_message = "Failed to set ownership on existing path";
                    return result;
                }
            }
            
            if (needs_chmod) {
                if (chmod(intent.path.c_str(), intent.mode_bits.value()) != 0) {
                    result.error_code = kErrorPermissionDenied;
                    result.error_message = "Failed to set permissions on existing path";
                    return result;
                }
            }
        }
        
        // Verify final state
        auto verified = observe_file_state(intent.path, SymlinkSafety::kRejected);
        if (verified.is_success() && verified.value.has_value()) {
            result.postcondition_state = verified.value.value();
            result.postcondition_state.exists = true;
        }
        
        return result;
    }
    
    // Create the path with correct permissions from the start
    std::filesystem::path parent = intent.path.parent_path();
    
    if (!parent.empty() && !std::filesystem::exists(parent, ec)) {
        // Create parent directories
        std::error_code dir_ec;
        if (intent.type == CreationIntent::Type::kParentDirectories ||
            intent.type == CreationIntent::Type::kDirectory) {
            if (!std::filesystem::create_directories(parent, dir_ec)) {
                result.error_code = kErrorRepairFailed;
                result.error_message = "Failed to create parent directories: " + dir_ec.message();
                return result;
            }
        } else {
            // For files, we need to create the directory
            if (!std::filesystem::create_directories(parent, dir_ec)) {
                result.error_code = kErrorRepairFailed;
                result.error_message = "Failed to create parent directories: " + dir_ec.message();
                return result;
            }
        }
    }
    
    // Create with correct permissions from the start (umask will still apply)
    // We'll fix it after creation
    if (intent.type == CreationIntent::Type::kDirectory) {
        mode_t umask_val = umask(0);
        umask(umask_val);  // Restore
        
        mode_t desired_mode = intent.mode_bits.value();
        mode_t actual_mode = desired_mode & ~umask_val;
        
        if (mkdir(intent.path.c_str(), actual_mode) != 0) {
            result.error_code = kErrorRepairFailed;
            result.error_message = "Failed to create directory: " + errno_string(errno);
            return result;
        }
    } else {
        // Create file with owner-only permissions first, then fix
        mode_t umask_val = umask(0);
        umask(umask_val);  // Restore
        
        std::ofstream ofs(intent.path.c_str(), std::ios::out | std::ios::trunc);
        if (!ofs) {
            result.error_code = kErrorRepairFailed;
            result.error_message = "Failed to create file";
            return result;
        }
        ofs.close();
    }
    
    // Now set the exact ownership and permissions
    if (chown(intent.path.c_str(), intent.owner_uid, intent.owner_gid) != 0) {
        result.error_code = kErrorPermissionDenied;
        result.error_message = "Failed to set ownership: " + errno_string(errno);
        return result;
    }
    
    if (chmod(intent.path.c_str(), intent.mode_bits.value()) != 0) {
        result.error_code = kErrorPermissionDenied;
        result.error_message = "Failed to set permissions: " + errno_string(errno);
        return result;
    }
    
    result.created = true;
    result.already_existed = false;
    
    // Verify final state
    auto verified = observe_file_state(intent.path, SymlinkSafety::kRejected);
    if (verified.is_success() && verified.value.has_value()) {
        result.postcondition_state = verified.value.value();
        result.postcondition_state.exists = true;
    }
    
    return result;
}

// ============================================================================
// Repair - Restore Rebuntu-owned artifacts to correct state
// ============================================================================

RepairPlan analyze_ownership_repairs(const std::vector<std::filesystem::path>& paths,
                                      const VerifyOwnershipIntent& intent) {
    RepairPlan plan;
    
    for (const auto& path : paths) {
        // Check if path exists
        std::error_code ec;
        bool exists = std::filesystem::exists(path, ec);
        
        if (!exists) {
            RepairIssue issue;
            issue.path = path;
            issue.type = RepairIssue::Type::kMissingArtifact;
            issue.description = "Path does not exist: " + path.string();
            plan.issues.push_back(std::move(issue));
            continue;
        }
        
        // Check for symlinks where not allowed
        struct stat lstat_buf;
        if (lstat(path.c_str(), &lstat_buf) == 0) {
            if (S_ISLNK(lstat_buf.st_mode) && intent.symlink_safety == SymlinkSafety::kRejected) {
                RepairIssue issue;
                issue.path = path;
                issue.type = RepairIssue::Type::kSymlinkDetected;
                issue.description = "Symlink detected where regular file/directory expected: " + path.string();
                plan.issues.push_back(std::move(issue));
                continue;
            }
        }
        
        // Verify current state
        auto verification = verify_ownership({
            .path = path,
            .expected_uid = intent.expected_uid,
            .expected_gid = intent.expected_gid,
            .expected_mode_bits = intent.expected_mode_bits,
            .symlink_safety = intent.symlink_safety
        });
        
        if (!verification.is_compliant) {
            RepairIssue issue;
            issue.path = path;
            
            if (!verification.owner_matches) {
                issue.type = RepairIssue::Type::kWrongOwner;
                issue.description = "Ownership mismatch for: " + path.string();
            } else if (!verification.group_matches) {
                issue.type = RepairIssue::Type::kWrongOwner;
                issue.description = "Group ownership mismatch for: " + path.string();
            } else if (!verification.is_correct_type) {
                issue.type = RepairIssue::Type::kWrongType;
                issue.description = "Type mismatch for: " + path.string();
            } else if (verification.permission_checks.empty() || 
                       !verification.permission_checks.back().second) {
                issue.type = RepairIssue::Type::kWrongPermissions;
                issue.description = "Permission mismatch for: " + path.string();
            } else {
                issue.type = RepairIssue::Type::kUnknownOwnership;
                issue.description = "Unknown ownership issue for: " + path.string();
            }
            
            plan.issues.push_back(std::move(issue));
        }
    }
    
    return plan;
}

struct RepairWorkItem {
    std::filesystem::path path;
    uid_t expected_uid;
    gid_t expected_gid;
    ModeBits expected_mode_bits;
};

RepairResult execute_ownership_repair(const RepairPlan& plan, 
                                       const VerifyOwnershipIntent& intent) {
    RepairResult result;
    
    if (plan.is_empty()) {
        // Nothing to repair
        result.fully_verified = true;
        return result;
    }
    
    for (const auto& issue : plan.issues) {
        switch (issue.type) {
            case RepairIssue::Type::kMissingArtifact: {
                // Create the missing path
                if (intent.expected_mode_bits.owner_read && intent.expected_mode_bits.owner_write &&
                    intent.expected_mode_bits.owner_exec) {
                    // Directory with full permissions
                    std::filesystem::path parent = issue.path.parent_path();
                    if (!parent.empty() && !std::filesystem::exists(parent)) {
                        std::filesystem::create_directories(parent);
                    }
                    
                    mode_t desired_mode = intent.expected_mode_bits.value();
                    umask(0);  // Clear umask for creation
                    mkdir(issue.path.c_str(), desired_mode);
                    chmod(issue.path.c_str(), desired_mode);
                } else {
                    // File - create with correct permissions
                    std::ofstream ofs(issue.path.c_str());
                    ofs.close();
                    
                    chown(issue.path.c_str(), 
                          intent.expected_uid.value_or(getuid()),
                          intent.expected_gid.value_or(getgid()));
                    chmod(issue.path.c_str(), intent.expected_mode_bits.value());
                }
                
                result.actions_taken.push_back(RepairAction::kRecreate);
                break;
            }
                
            case RepairIssue::Type::kWrongOwner:
            case RepairIssue::Type::kWrongPermissions: {
                // Apply ownership mutation
                OwnershipMutation mut;
                mut.path = issue.path;
                mut.set_uid = intent.expected_uid;
                mut.set_gid = intent.expected_gid;
                mut.set_mode_bits = intent.expected_mode_bits;
                
                auto op_result = apply_ownership_mutation(mut);
                if (op_result.changed) {
                    result.actions_taken.push_back(
                        op_result.verified ? RepairAction::kUpdateOwner : RepairAction::kRecreate);
                    result.any_changed = true;
                }
                break;
            }
                
            case RepairIssue::Type::kSymlinkDetected: {
                // Remove symlink and recreate
                std::filesystem::remove(issue.path);
                std::filesystem::path parent = issue.path.parent_path();
                if (!parent.empty() && !std::filesystem::exists(parent)) {
                    std::filesystem::create_directories(parent);
                }
                
                if (intent.expected_mode_bits.owner_read && intent.expected_mode_bits.owner_write &&
                    intent.expected_mode_bits.owner_exec) {
                    mkdir(issue.path.c_str(), intent.expected_mode_bits.value());
                } else {
                    std::ofstream ofs(issue.path.c_str());
                    ofs.close();
                    chmod(issue.path.c_str(), intent.expected_mode_bits.value());
                }
                
                chown(issue.path.c_str(),
                      intent.expected_uid.value_or(getuid()),
                      intent.expected_gid.value_or(getgid()));
                
                result.actions_taken.push_back(RepairAction::kRecreate);
                break;
            }
                
            case RepairIssue::Type::kWrongType:
            case RepairIssue::Type::kUserModified:
            case RepairIssue::Type::kUnknownOwnership:
                // Skip - cannot safely repair without more information
                break;
        }
    }
    
    // Final verification
    if (!plan.issues.empty()) {
        auto final_verification = verify_ownership(intent);
        result.fully_verified = final_verification.is_compliant;
    }
    
    return result;
}

// ============================================================================
// Umask Support
// ============================================================================

PermissionResult<UmaskState> observe_umask() {
    PermissionResult<UmaskState> result;
    
    mode_t current = umask(0);
    umask(current);  // Restore
    
    UmaskState state;
    state.current_umask = static_cast<uint32_t>(current);
    
    result.status = PermissionResult<UmaskState>::Status::kSuccess;
    result.value = std::move(state);
    
    return result;
}

ModeBits mode_after_umask(ModeBits desired, uint32_t current_umask) {
    ModeBits result = desired;
    
    // Apply umask: bits are cleared where umask has 1s
    if (current_umask & 0400) result.owner_read = false;
    if (current_umask & 0200) result.owner_write = false;
    if (current_umask & 0100) result.owner_exec = false;
    if (current_umask & 0040) result.group_read = false;
    if (current_umask & 0020) result.group_write = false;
    if (current_umask & 0010) result.group_exec = false;
    if (current_umask & 0004) result.other_read = false;
    if (current_umask & 0002) result.other_write = false;
    if (current_umask & 0001) result.other_exec = false;
    
    return result;
}

// ============================================================================
// Utility Functions
// ============================================================================

std::string mode_to_string(uint32_t mode) {
    std::ostringstream oss;
    oss << std::oct << std::setfill('0') << std::setw(4) << (mode & 07777);
    return oss.str();
}

std::string mode_bits_to_string(const ModeBits& bits) {
    std::ostringstream oss;
    oss << std::oct << std::setfill('0') << std::setw(4) << bits.value();
    return oss.str();
}

PermissionResult<ModeBits> parse_mode_string(std::string_view s) {
    PermissionResult<ModeBits> result;
    
    // Try parsing as octal (e.g., "0755")
    if (!s.empty() && s[0] == '0') {
        try {
            unsigned long val = std::stoul(std::string(s), nullptr, 8);
            if (val <= 07777) {
                result.status = PermissionResult<ModeBits>::Status::kSuccess;
                result.value = ModeBits::from_value(static_cast<uint32_t>(val));
                return result;
            }
        } catch (...) {
            // Fall through to error
        }
    }
    
    // Try parsing as rwxrwxrwx format
    if (s.length() == 9 || s.length() == 10) {
        ModeBits bits;
        
        size_t idx = 0;
        if (s.length() == 10 && (s[0] == 'd' || s[0] == '-')) idx = 1;
        
        // Owner: rwx
        if (idx < s.length()) {
            if (s[idx] == 'r') bits.owner_read = true; else if (s[idx] != '-') result.status = PermissionResult<ModeBits>::Status::kInvalid;
            ++idx;
        }
        if (idx < s.length()) {
            if (s[idx] == 'w') bits.owner_write = true; else if (s[idx] != '-') result.status = PermissionResult<ModeBits>::Status::kInvalid;
            ++idx;
        }
        if (idx < s.length()) {
            if (s[idx] == 'x') bits.owner_exec = true; else if (s[idx] == 'S' || s[idx] == 's') { bits.owner_exec = true; bits.setuid = true; }
            else if (s[idx] == 'S' || s[idx] == '-') { /* S means no x, setuid */ }
            ++idx;
        }
        
        // Group: rwx
        if (idx < s.length()) {
            if (s[idx] == 'r') bits.group_read = true; else if (s[idx] != '-') result.status = PermissionResult<ModeBits>::Status::kInvalid;
            ++idx;
        }
        if (idx < s.length()) {
            if (s[idx] == 'w') bits.group_write = true; else if (s[idx] != '-') result.status = PermissionResult<ModeBits>::Status::kInvalid;
            ++idx;
        }
        if (idx < s.length()) {
            if (s[idx] == 'x') bits.group_exec = true; else if (s[idx] == 'S' || s[idx] == 's') { bits.group_exec = true; bits.setgid = true; }
            ++idx;
        }
        
        // Other: rwx
        if (idx < s.length()) {
            if (s[idx] == 'r') bits.other_read = true; else if (s[idx] != '-') result.status = PermissionResult<ModeBits>::Status::kInvalid;
            ++idx;
        }
        if (idx < s.length()) {
            if (s[idx] == 'w') bits.other_write = true; else if (s[idx] != '-') result.status = PermissionResult<ModeBits>::Status::kInvalid;
            ++idx;
        }
        if (idx < s.length()) {
            if (s[idx] == 'x') bits.other_exec = true; else if (s[idx] == 'T' || s[idx] == 't') { bits.other_exec = true; bits.sticky_bit = true; }
            ++idx;
        }
        
        result.status = PermissionResult<ModeBits>::Status::kSuccess;
        result.value = std::move(bits);
        return result;
    }
    
    result.status = PermissionResult<ModeBits>::Status::kInvalid;
    result.error_code = kErrorInvalidMode;
    result.error_message = "Cannot parse mode string: " + std::string(s);
    
    return result;
}

}  // namespace rebuntu::environment::ownership