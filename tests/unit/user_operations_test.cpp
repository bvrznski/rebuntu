// User Operations Unit Tests (Phase 6.77)
//
// Tests for user management operations with proper contract semantics.
#include <gtest/gtest.h>

#include <system/core/contracts.hpp>
#include <operations/users.hpp>

namespace {

using namespace rebuntu::operations;

TEST(UserOperationsTest, CreateUserInputsValidation) {
    std::string error;
    
    // Valid username
    CreateUserInputs valid_inputs;
    valid_inputs.username = "testuser";
    EXPECT_TRUE(valid_inputs.is_valid(error));
    
    // Empty username should fail
    CreateUserInputs empty_username;
    empty_username.username = "";
    EXPECT_FALSE(empty_username.is_valid(error));
    
    // Invalid format with numbers at start should fail
    CreateUserInputs invalid_format;
    invalid_format.username = "123test";
    EXPECT_FALSE(invalid_format.is_valid(error));
    
    // UID validation
    CreateUserInputs valid_uid;
    valid_uid.username = "testuser";
    valid_uid.uid = 1001;
    EXPECT_TRUE(valid_uid.is_valid(error));
    
    CreateUserInputs invalid_uid;
    invalid_uid.username = "testuser";
    invalid_uid.uid = -1;
    EXPECT_FALSE(invalid_uid.is_valid(error));
}

TEST(UserOperationsTest, UserQueryResultSuccess) {
    UserInfo info;
    info.username = "testuser";
    info.uid = 1001;
    info.gid = 1001;
    
    QueryUserResult result = QueryUserResult::found(info);
    EXPECT_EQ(result.status, core::SemanticStatus::kSuccess);
    EXPECT_TRUE(result.verified);
    EXPECT_TRUE(result.user_info.has_value());
}

TEST(UserOperationsTest, CreateUserResultNoChange) {
    CreateUserResult result = CreateUserResult::no_change();
    EXPECT_EQ(result.status, core::SemanticStatus::kSuccess);
    EXPECT_FALSE(result.created);
    EXPECT_TRUE(result.verified);
}

TEST(UserOperationsTest, DeleteUserResultSuccess) {
    DeleteUserResult result = DeleteUserResult::success(true);
    EXPECT_EQ(result.status, core::SemanticStatus::kSuccess);
    EXPECT_TRUE(result.deleted);
    EXPECT_TRUE(result.verified);
}

}  // namespace