// Rebuntu Operations — User Management Domain (Phase 6.77)
//
// This module implements user management operations as canonical Rebuntu Operations.
// Each Operation is a reusable, explicitly contracted capability with:
//   - Typed inputs and outputs
//   - Preconditions (must hold before execution)
//   - Postconditions (must hold for success verification)
//   - Verification strategy
//   - Evidence supporting results

#pragma once

#include <system/core/contracts.hpp>
#include <optional>
#include <string>

namespace rebuntu::operations {

struct CreateUserInputs {
    std::string username;
    std::optional<int> uid;
    std::optional<std::string> home_dir;
    std::optional<std::string> shell;
    bool skip_if_exists = false;
    
    bool is_valid(std::string& error) const;
};

struct CreateUserResult {
    core::SemanticStatus status = core::SemanticStatus::kUnknown;
    bool created = false;
    bool verified = false;
    
    std::vector<core::Evidence> evidence;
    std::optional<core::Error> error;
    
    static CreateUserResult success(bool was_created, bool was_verified = true) {
        CreateUserResult r;
        r.status = core::SemanticStatus::kSuccess;
        r.created = was_created;
        r.verified = was_verified;
        return r;
    }
    
    static CreateUserResult no_change() {
        CreateUserResult r;
        r.status = core::SemanticStatus::kSuccess;
        r.created = false;
        r.verified = true;
        return r;
    }
    
    static CreateUserResult failure(std::string code, std::string message) {
        CreateUserResult r;
        r.status = core::SemanticStatus::kFailure;
        r.error = core::Error{std::move(code), std::move(message)};
        return r;
    }
};

CreateUserResult user_create(const CreateUserInputs& inputs);

struct DeleteUserInputs {
    std::string username;
    bool remove_home = false;
    
    bool is_valid(std::string& error) const;
};

struct DeleteUserResult {
    core::SemanticStatus status = core::SemanticStatus::kUnknown;
    bool deleted = false;
    bool verified = false;
    
    std::vector<core::Evidence> evidence;
    std::optional<core::Error> error;
    
    static DeleteUserResult success(bool was_deleted, bool was_verified = true) {
        DeleteUserResult r;
        r.status = core::SemanticStatus::kSuccess;
        r.deleted = was_deleted;
        r.verified = was_verified;
        return r;
    }
    
    static DeleteUserResult no_change() {
        DeleteUserResult r;
        r.status = core::SemanticStatus::kSuccess;
        r.deleted = false;
        r.verified = true;
        return r;
    }
    
    static DeleteUserResult failure(std::string code, std::string message) {
        DeleteUserResult r;
        r.status = core::SemanticStatus::kFailure;
        r.error = core::Error{std::move(code), std::move(message)};
        return r;
    }
};

DeleteUserResult user_delete(const DeleteUserInputs& inputs);

struct UserInfo {
    std::string username;
    int uid;
    int gid;
    std::optional<std::string> home_dir;
    std::optional<std::string> shell;
};

struct QueryUserResult {
    core::SemanticStatus status = core::SemanticStatus::kUnknown;
    
    std::optional<UserInfo> user_info;
    bool verified = false;
    
    std::vector<core::Evidence> evidence;
    std::optional<core::Error> error;
    
    static QueryUserResult found(const UserInfo& info) {
        QueryUserResult r;
        r.status = core::SemanticStatus::kSuccess;
        r.user_info = info;
        r.verified = true;
        return r;
    }
    
    static QueryUserResult not_found() {
        QueryUserResult r;
        r.status = core::SemanticStatus::kSuccess;
        r.verified = true;
        return r;
    }
    
    static QueryUserResult failure(std::string code, std::string message) {
        QueryUserResult r;
        r.status = core::SemanticStatus::kFailure;
        r.error = core::Error{std::move(code), std::move(message)};
        return r;
    }
};

QueryUserResult user_query(const std::string& username);

void register_user_operations(core::OperationRegistry& registry);

}  // namespace rebuntu::operations