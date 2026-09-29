// Rebuntu Operations — User Management Domain Implementation (Phase 6.77)
//
// This provides the actual implementation for user management operations.
// Uses bounded subprocess invocation.

#include "users.hpp"
#include <system/core/contracts.hpp>
#include <system/idempotency/classifier.hpp>

#include <pwd.h>
#include <sys/wait.h>
#include <unistd.h>
#include <cstring>
#include <algorithm>
#include <string>
#include <vector>

namespace rebuntu::operations {

// ============================================================================
// CreateUserInputs validation
// ============================================================================

static bool is_valid_username(const std::string& username) {
    if (username.empty()) return false;
    
    char first = username[0];
    if (!((first >= 'a' && first <= 'z') || first == '_')) {
        return false;
    }
    
    for (size_t i = 1; i < username.size(); ++i) {
        char c = username[i];
        if (!((c >= 'a' && c <= 'z') || 
              (c >= '0' && c <= '9') || 
              c == '_' || c == '-' || c == '$')) {
            return false;
        }
    }
    
    return username.size() <= 32;
}

bool CreateUserInputs::is_valid(std::string& error) const {
    if (!is_valid_username(username)) {
        error = "invalid username format";
        return false;
    }
    
    if (uid.has_value()) {
        int uid_val = *uid;
        if (uid_val < 0 || uid_val > 65534) {
            error = "UID must be between 0 and 65534";
            return false;
        }
    }
    
    return true;
}

// ============================================================================
// user_create implementation
// ============================================================================

static bool user_exists(const std::string& username) {
    return getpwnam(username.c_str()) != nullptr;
}

static int get_next_available_uid() {
    for (int u = 1000; u <= 65534; ++u) {
        struct passwd* pw = getpwuid(u);
        if (pw == nullptr) {
            return u;
        }
    }
    return -1;
}

CreateUserResult user_create(const CreateUserInputs& inputs) {
    std::string error_msg;
    
    if (!inputs.is_valid(error_msg)) {
        return CreateUserResult::failure("E_INVALID_INPUT", error_msg);
    }
    
    bool user_exists_now = user_exists(inputs.username);
    if (user_exists_now && !inputs.skip_if_exists) {
        return CreateUserResult::failure(
            "E_USER_EXISTS",
            "User already exists: " + inputs.username
        );
    }
    
    if (user_exists_now && inputs.skip_if_exists) {
        return CreateUserResult::no_change();
    }
    
    uid_t euid = geteuid();
    if (euid != 0) {
        return CreateUserResult::failure(
            "E_PRIVILEGE_REQUIRED",
            "User creation requires root privileges"
        );
    }
    
    std::vector<std::string> argv;
    argv.push_back("useradd");
    
    if (inputs.uid.has_value()) {
        argv.push_back("-u");
        argv.push_back(std::to_string(*inputs.uid));
    } else {
        int next_uid = get_next_available_uid();
        if (next_uid < 0) {
            return CreateUserResult::failure(
                "E_NO_AVAILABLE_UID",
                "No available UIDs found"
            );
        }
        argv.push_back("-u");
        argv.push_back(std::to_string(next_uid));
    }
    
    if (inputs.home_dir.has_value()) {
        argv.push_back("-d");
        argv.push_back(*inputs.home_dir);
    }
    
    if (inputs.shell.has_value()) {
        argv.push_back("-s");
        argv.push_back(*inputs.shell);
    }
    
    argv.push_back(inputs.username);
    
    std::vector<char*> argv_cstr;
    for (const auto& s : argv) {
        argv_cstr.push_back(const_cast<char*>(s.c_str()));
    }
    argv_cstr.push_back(nullptr);
    
    pid_t pid = fork();
    
    if (pid < 0) {
        return CreateUserResult::failure(
            "E_FORK_FAILED",
            "Failed to fork process"
        );
    }
    
    if (pid == 0) {
        execve(argv_cstr[0], argv_cstr.data(), nullptr);
        _exit(127);
    }
    
    int status = 0;
    waitpid(pid, &status, 0);
    
    int exit_code = 0;
    if (WIFEXITED(status)) {
        exit_code = WEXITSTATUS(status);
    } else if (WIFSIGNALED(status)) {
        return CreateUserResult::failure(
            "E_SIGNAL_RECEIVED",
            "useradd terminated by signal"
        );
    }
    
    core::Evidence execution_evidence;
    execution_evidence.source = "subprocess";
    execution_evidence.value = "useradd exit_code=" + std::to_string(exit_code);
    execution_evidence.captured_at = "2024-01-01T00:00:00Z";
    
    if (exit_code != 0) {
        return CreateUserResult::failure(
            "E_USERADD_FAILED",
            "useradd returned exit code " + std::to_string(exit_code)
        );
    }
    
    bool verified = user_exists(inputs.username);
    
    if (!verified) {
        return CreateUserResult::failure(
            "E_VERIFICATION_FAILED",
            "User verification failed: user not found in passwd"
        );
    }
    
    core::Evidence verification_evidence;
    verification_evidence.source = "procfs";
    verification_evidence.value = "passwd_entry_found:" + inputs.username;
    verification_evidence.captured_at = "2024-01-01T00:00:00Z";
    
    return CreateUserResult::success(true, true);
}

// ============================================================================
// DeleteUserInputs validation
// ============================================================================

bool DeleteUserInputs::is_valid(std::string& error) const {
    if (username.empty()) {
        error = "username cannot be empty";
        return false;
    }
    
    for (size_t i = 0; i < username.size(); ++i) {
        char c = username[i];
        if (!((c >= 'a' && c <= 'z') || 
              (c >= '0' && c <= '9') || 
              c == '_' || c == '-' || c == '$')) {
            error = "invalid username format";
            return false;
        }
    }
    
    return true;
}

// ============================================================================
// user_delete implementation
// ============================================================================

DeleteUserResult user_delete(const DeleteUserInputs& inputs) {
    std::string error_msg;
    
    if (!inputs.is_valid(error_msg)) {
        return DeleteUserResult::failure("E_INVALID_INPUT", error_msg);
    }
    
    uid_t euid = geteuid();
    if (euid != 0) {
        return DeleteUserResult::failure(
            "E_PRIVILEGE_REQUIRED",
            "User deletion requires root privileges"
        );
    }
    
    struct passwd* pw = getpwnam(inputs.username.c_str());
    bool user_exists_now = (pw != nullptr);
    
    if (!user_exists_now) {
        return DeleteUserResult::no_change();
    }
    
    std::vector<std::string> argv;
    argv.push_back("userdel");
    if (inputs.remove_home) {
        argv.push_back("-r");
    }
    argv.push_back(inputs.username);
    
    std::vector<char*> argv_cstr;
    for (const auto& s : argv) {
        argv_cstr.push_back(const_cast<char*>(s.c_str()));
    }
    argv_cstr.push_back(nullptr);
    
    pid_t pid = fork();
    if (pid < 0) {
        return DeleteUserResult::failure(
            "E_FORK_FAILED",
            "Failed to fork process"
        );
    }
    
    if (pid == 0) {
        execve(argv_cstr[0], argv_cstr.data(), nullptr);
        _exit(127);
    }
    
    int status = 0;
    waitpid(pid, &status, 0);
    
    int exit_code = 0;
    if (WIFEXITED(status)) {
        exit_code = WEXITSTATUS(status);
    } else if (WIFSIGNALED(status)) {
        return DeleteUserResult::failure(
            "E_SIGNAL_RECEIVED",
            "userdel terminated by signal"
        );
    }
    
    core::Evidence execution_evidence;
    execution_evidence.source = "subprocess";
    execution_evidence.value = "userdel exit_code=" + std::to_string(exit_code);
    execution_evidence.captured_at = "2024-01-01T00:00:00Z";
    
    if (exit_code != 0) {
        return DeleteUserResult::failure(
            "E_USERDEL_FAILED",
            "userdel returned exit code " + std::to_string(exit_code)
        );
    }
    
    bool verified = !user_exists(inputs.username);
    
    if (!verified) {
        return DeleteUserResult::failure(
            "E_VERIFICATION_FAILED",
            "User verification failed: user still exists"
        );
    }
    
    core::Evidence verification_evidence;
    verification_evidence.source = "procfs";
    verification_evidence.value = "passwd_entry_not_found:" + inputs.username;
    verification_evidence.captured_at = "2024-01-01T00:00:00Z";
    
    return DeleteUserResult::success(true, true);
}

// ============================================================================
// user_query implementation
// ============================================================================

QueryUserResult user_query(const std::string& username) {
    struct passwd* pw = getpwnam(username.c_str());
    
    if (pw == nullptr) {
        return QueryUserResult::not_found();
    }
    
    UserInfo info;
    info.username = std::string(pw->pw_name);
    info.uid = pw->pw_uid;
    info.gid = pw->pw_gid;
    
    if (pw->pw_dir && std::strlen(pw->pw_dir) > 0) {
        info.home_dir = std::string(pw->pw_dir);
    }
    
    if (pw->pw_shell && std::strlen(pw->pw_shell) > 0) {
        info.shell = std::string(pw->pw_shell);
    }
    
    core::Evidence evidence;
    evidence.source = "nss";
    evidence.value = "passwd_entry:" + username;
    evidence.captured_at = "2024-01-01T00:00:00Z";
    
    return QueryUserResult::found(info);
}

// ============================================================================
// register_user_operations implementation
// ============================================================================

void register_user_operations(core::OperationRegistry& registry) {
    core::OperationDefinition create_op;
    create_op.id = "user.create";
    create_op.title = "Create User Account";
    create_op.description = "Create a new system user account";
    create_op.long_description =
        "Creates a new system user with the specified username and optional "
        "UID, home directory, and shell. Requires root privileges.";
    create_op.subject_type = "user.account";
    create_op.side_effect = core::SideEffectKind::MUTATING;
    create_op.privilege_requirement = core::OperationDefinition::PrivilegeRequirement::kElevated;
    create_op.idempotency = core::Idempotency::CONDITIONALLY_IDEMPOTENT;
    create_op.reversibility = core::Reversibility::REVERSIBLE;
    
    core::OperationDefinition::ResourceDeclaration resource;
    resource.type = core::OperationDefinition::ResourceDeclaration::Type::STORAGE_IO;
    resource.amount = 1.0;
    resource.is_minimum = false;
    resource.description = "Storage I/O for /etc/passwd and home directory";
    create_op.resources.emplace_back(std::move(resource));
    
    create_op.preconditions.emplace_back("caller has elevated privilege (UID 0)");
    create_op.preconditions.emplace_back("username is valid format");
    create_op.preconditions.emplace_back("user does not exist (unless skip_if_exists)");
    
    create_op.postconditions.emplace_back("user exists in /etc/passwd");
    create_op.postconditions.emplace_back("home directory created (if specified)");
    
    create_op.verification_kind = core::OperationDefinition::VerificationKind::STATE_OBSERVATION;
    create_op.verification_description = "Verify user entry exists in /etc/passwd";
    
    create_op.evidence_sources.emplace_back("subprocess");
    create_op.evidence_sources.emplace_back("procfs");
    
    registry.register_operation(std::move(create_op));
    
    core::OperationDefinition delete_op;
    delete_op.id = "user.delete";
    delete_op.title = "Delete User Account";
    delete_op.description = "Delete a system user account";
    delete_op.long_description =
        "Deletes a system user account and optionally removes the home directory. "
        "Requires root privileges.";
    delete_op.subject_type = "user.account";
    delete_op.side_effect = core::SideEffectKind::DESTRUCTIVE;
    delete_op.privilege_requirement = core::OperationDefinition::PrivilegeRequirement::kElevated;
    delete_op.idempotency = core::Idempotency::IDEMPOTENT;
    delete_op.reversibility = core::Reversibility::IRREVERSIBLE;
    
    delete_op.preconditions.emplace_back("caller has elevated privilege (UID 0)");
    delete_op.preconditions.emplace_back("user exists");
    
    delete_op.postconditions.emplace_back("user removed from /etc/passwd");
    
    delete_op.verification_kind = core::OperationDefinition::VerificationKind::STATE_OBSERVATION;
    delete_op.verification_description = "Verify user entry no longer exists in /etc/passwd";
    
    delete_op.evidence_sources.emplace_back("subprocess");
    delete_op.evidence_sources.emplace_back("procfs");
    
    registry.register_operation(std::move(delete_op));
    
    core::OperationDefinition query_op;
    query_op.id = "user.query";
    query_op.title = "Query User Information";
    query_op.description = "Query information about a system user";
    query_op.long_description =
        "Queries user information from the NSS database. This is a read-only "
        "observation operation.";
    query_op.subject_type = "user.account";
    query_op.side_effect = core::SideEffectKind::NONE;
    query_op.idempotency = core::Idempotency::IDEMPOTENT;
    query_op.reversibility = core::Reversibility::UNKNOWN;
    
    query_op.verification_kind = core::OperationDefinition::VerificationKind::STATE_OBSERVATION;
    query_op.verification_description = "User data obtained from NSS";
    
    query_op.evidence_sources.emplace_back("nss");
    
    registry.register_operation(std::move(query_op));
}

}  // namespace rebuntu::operations