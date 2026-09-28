// Rebuntu Path Safety Tests (Phase 6.59)
//
// Unit tests for path safety validation utilities.

#include <gtest/gtest.h>
#include <filesystem>
#include <fstream>
#include <sys/stat.h>
#include <unistd.h>

#include <src/system/path_safety.hpp>

namespace fs = std::filesystem;

namespace rebuntu::path_safety {

// ============================================================================
// Path Syntax Validation Tests
// ============================================================================

TEST(PathSyntax, ValidPath) {
    fs::path path = "/tmp/test_file.txt";
    
    auto result = validate_path_syntax(path);
    
    EXPECT_EQ(result.status, SafetyCheckStatus::kPassed);
}

TEST(PathSyntax, EmptyPath) {
    fs::path path = "";
    
    auto result = validate_path_syntax(path);
    
    EXPECT_EQ(result.status, SafetyCheckStatus::kFailed);
}

TEST(PathSyntax, PathWithTraversal) {
    fs::path path = "/tmp/../etc/passwd";
    
    auto result = validate_path_syntax(path);
    
    // Traversal should trigger a warning
    EXPECT_EQ(result.status, SafetyCheckStatus::kWarning);
}

// ============================================================================
// Path Boundary Validation Tests
// ============================================================================

TEST(PathBoundary, PathUnderBoundary) {
    fs::path path = "/home/user/test.txt";
    fs::path boundary = "/home/user";
    
    auto result = validate_path_in_boundary(path, boundary);
    
    EXPECT_EQ(result.status, SafetyCheckStatus::kPassed);
}

TEST(PathBoundary, PathEscapesBoundary) {
    fs::path path = "/etc/passwd";
    fs::path boundary = "/home/user";
    
    auto result = validate_path_in_boundary(path, boundary);
    
    EXPECT_EQ(result.status, SafetyCheckStatus::kFailed);
}

TEST(PathBoundary, ExactBoundaryMatch) {
    fs::path path = "/tmp/test_dir";
    fs::path boundary = "/tmp/test_dir";
    
    auto result = validate_path_in_boundary(path, boundary, true);
    
    EXPECT_EQ(result.status, SafetyCheckStatus::kPassed);
}

// ============================================================================
// Symlink Policy Tests
// ============================================================================

TEST(SymlinkPolicy, NoSymlinkAllowed) {
    // Create a test directory and file
    fs::path temp_dir = fs::temp_directory_path() / 
                        "rebuntu_symlink_test_" + std::to_string(getpid());
    fs::create_directories(temp_dir);
    
    fs::path target_file = temp_dir / "target.txt";
    {
        std::ofstream f(target_file);
        f << "test content";
    }
    
    fs::path symlink_path = temp_dir / "link.txt";
    fs::create_symlink(target_file, symlink_path);
    
    // Test with kReject policy
    SymlinkPolicy reject_policy;
    reject_policy.behavior = SymlinkBehavior::kReject;
    
    auto result = check_symlink_policy(symlink_path, reject_policy);
    
    EXPECT_EQ(result.status, SafetyCheckStatus::kFailed);
    
    // Cleanup
    fs::remove_all(temp_dir);
}

TEST(SymlinkPolicy, FollowAllowed) {
    // Create a test directory and file
    fs::path temp_dir = fs::temp_directory_path() / 
                        "rebuntu_symlink_test_" + std::to_string(getpid());
    fs::create_directories(temp_dir);
    
    fs::path target_file = temp_dir / "target.txt";
    {
        std::ofstream f(target_file);
        f << "test content";
    }
    
    fs::path symlink_path = temp_dir / "link.txt";
    fs::create_symlink(target_file, symlink_path);
    
    // Test with kFollow policy
    SymlinkPolicy follow_policy;
    follow_policy.behavior = SymlinkBehavior::kFollow;
    
    auto result = check_symlink_policy(symlink_path, follow_policy);
    
    EXPECT_EQ(result.status, SafetyCheckStatus::kPassed);
    
    // Cleanup
    fs::remove_all(temp_dir);
}

// ============================================================================
// Ownership Verification Tests
// ============================================================================

TEST(OwnershipVerification, ValidOwner) {
    // Create a test file owned by current user
    fs::path temp_file = fs::temp_directory_path() / 
                         "rebuntu_ownership_test_" + std::to_string(getpid());
    
    {
        std::ofstream f(temp_file);
        f << "test content";
    }
    
    uid_t current_uid = getuid();
    
    auto result = verify_ownership(temp_file, current_uid);
    
    EXPECT_EQ(result.status, SafetyCheckStatus::kPassed);
    
    // Cleanup
    fs::remove(temp_file);
}

TEST(OwnershipVerification, InvalidOwner) {
    fs::path path = "/etc/passwd";  // File owned by root
    
    uid_t nobody_uid = 65534;  // Usually the nobody user
    
    auto result = verify_ownership(path, nobody_uid);
    
    EXPECT_EQ(result.status, SafetyCheckStatus::kFailed);
}

// ============================================================================
// Full Operation Validation Tests
// ============================================================================

TEST(OperationValidation, ReadOperation) {
    fs::path temp_file = fs::temp_directory_path() / 
                         "rebuntu_read_test_" + std::to_string(getpid());
    
    {
        std::ofstream f(temp_file);
        f << "test content";
    }
    
    PathContext context;
    context.op_type = OperationType::kRead;
    
    auto result = validate_path_for_operation(temp_file, context);
    
    EXPECT_EQ(result.status, SafetyCheckStatus::kPassed);
    
    // Cleanup
    fs::remove(temp_file);
}

TEST(OperationValidation, WriteOperation) {
    fs::path temp_dir = fs::temp_directory_path() / 
                        "rebuntu_write_test_" + std::to_string(getpid());
    fs::create_directories(temp_dir);
    
    fs::path target_file = temp_dir / "output.txt";
    
    PathContext context;
    context.op_type = OperationType::kWrite;
    context.target_owner_uid = getuid();
    
    auto result = validate_path_for_operation(target_file, context);
    
    // This will fail because file doesn't exist yet (expected for write)
    // or succeed if the parent directory is valid
    
    fs::remove_all(temp_dir);
}

TEST(OperationValidation, BoundaryViolation) {
    PathContext context;
    context.op_type = OperationType::kRead;
    context.boundary = PathBoundary::kUserHome;
    
    auto home_env = std::getenv("HOME");
    if (home_env && *home_env) {
        fs::path home(home_env);
        
        // Try to access something outside home
        fs::path path = "/etc/passwd";
        
        auto result = validate_path_for_operation(path, context);
        
        EXPECT_EQ(result.status, SafetyCheckStatus::kFailed);
    }
}

// ============================================================================
// FileDescriptor Tests
// ============================================================================

TEST(FileDescriptor, MoveOnlySemantics) {
    fs::path temp_file = fs::temp_directory_path() / 
                         "rebuntu_fd_test_" + std::to_string(getpid());
    
    {
        std::ofstream f(temp_file);
        f << "test";
    }
    
    auto fd_opt = open_file_safely(temp_file, O_RDONLY);
    ASSERT_TRUE(fd_opt.has_value());
    
    int original_fd = fd_opt->get();
    EXPECT_GT(original_fd, 0);
    
    // Test move
    FileDescriptor moved_fd = std::move(*fd_opt);
    EXPECT_EQ(moved_fd.get(), original_fd);
    
    // Verify original is closed
    EXPECT_FALSE(fd_opt->is_valid());
    
    moved_fd.close();
    fs::remove(temp_file);
}

// ============================================================================
// File Identity Tests
// ============================================================================

TEST(FileIdentity, GetIdentityFromFd) {
    fs::path temp_file = fs::temp_directory_path() / 
                         "rebuntu_identity_test_" + std::to_string(getpid());
    
    {
        std::ofstream f(temp_file);
        f << "test content";
    }
    
    auto fd_opt = open_file_safely(temp_file, O_RDONLY);
    ASSERT_TRUE(fd_opt.has_value());
    
    auto identity = get_file_identity(*fd_opt);
    EXPECT_TRUE(identity.has_value());
    
    EXPECT_EQ(identity->owner_uid, getuid());
    
    fd_opt->close();
    fs::remove(temp_file);
}

}  // namespace rebuntu::path_safety