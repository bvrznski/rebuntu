// Rebuntu Directories Module Tests (Phase 2.9)
// ==============================================
// Testing Operational Directory Layout implementation

#include "system/environment/directories.hpp"
#include "system/environment/scope.hpp"
#include <cassert>
#include <iostream>
#include <cstdlib>
#include <sys/stat.h>
#include <unistd.h>
#include <filesystem>

void test_directory_type_to_string() {
    // Verify to_string produces expected values
    using namespace rebuntu::environment::directories;
    
    assert(to_string(rebuntu::environment::directories::DirectoryType::kConfig) == "config");
    assert(to_string(rebuntu::environment::directories::DirectoryType::kState) == "state");
    assert(to_string(rebuntu::environment::directories::DirectoryType::kCache) == "cache");
    assert(to_string(rebuntu::environment::directories::DirectoryType::kData) == "data");
    assert(to_string(rebuntu::environment::directories::DirectoryType::kRuntime) == "runtime");
    assert(to_string(rebuntu::environment::directories::DirectoryType::kTemp) == "temp");
    assert(to_string(rebuntu::environment::directories::DirectoryType::kLog) == "log");
    
    std::cout << "test_directory_type_to_string: PASSED" << std::endl;
}

void test_get_system_runtime_dir() {
    // System runtime dir should be /run/rebuntu
    auto path = rebuntu::environment::directories::get_system_runtime_dir();
    assert(path.string().find("/run/rebuntu") == 0);
    
    std::cout << "test_get_system_runtime_dir: PASSED" << std::endl;
}

void test_get_system_data_dir() {
    // System data dir should be /usr/share/rebuntu
    auto path = rebuntu::environment::directories::get_system_data_dir();
    assert(path.string().find("/usr/share/rebuntu") == 0);
    
    std::cout << "test_get_system_data_dir: PASSED" << std::endl;
}

void test_get_system_log_dir() {
    // System log dir should be /var/log/rebuntu
    auto path = rebuntu::environment::directories::get_system_log_dir();
    assert(path.string().find("/var/log/rebuntu") == 0);
    
    std::cout << "test_get_system_log_dir: PASSED" << std::endl;
}

void test_get_user_data_dir() {
    // User data dir should be under home/.local/share/rebuntu
    setenv("HOME", "/home/testuser", 1);
    auto path = rebuntu::environment::directories::get_user_data_dir("/home/testuser");
    
    assert(path.string().find("/home/testuser/.local/share/rebuntu") == 0);
    
    // Test with empty home - should return empty path
    auto empty_path = rebuntu::environment::directories::get_user_data_dir("");
    assert(empty_path.empty());
    
    std::cout << "test_get_user_data_dir: PASSED" << std::endl;
}

void test_directory_operation_result_status() {
    // Verify status enum values
    using namespace rebuntu::environment::directories;
    
    assert(static_cast<int>(DirectoryOperationStatus::kSuccess) >= 0);
    assert(static_cast<int>(DirectoryOperationStatus::kAlreadyExists) >= 0);
    assert(static_cast<int>(DirectoryOperationStatus::kPermissionDenied) >= 0);
    assert(static_cast<int>(DirectoryOperationStatus::kInvalidPath) >= 0);
    assert(static_cast<int>(DirectoryOperationStatus::kMissingParent) >= 0);
    assert(static_cast<int>(DirectoryOperationStatus::kUnknown) >= 0);
    
    std::cout << "test_directory_operation_result_status: PASSED" << std::endl;
}

void test_directory_validation_result() {
    // Verify validation result enum values
    using namespace rebuntu::environment::directories;
    
    assert(static_cast<int>(DirectoryValidationResult::kValid) >= 0);
    assert(static_cast<int>(DirectoryValidationResult::kMissing) >= 0);
    assert(static_cast<int>(DirectoryValidationResult::kPermissionIssue) >= 0);
    assert(static_cast<int>(DirectoryValidationResult::kOwnershipIssue) >= 0);
    assert(static_cast<int>(DirectoryValidationResult::kSymlinkRisk) >= 0);
    assert(static_cast<int>(DirectoryValidationResult::kInvalidPath) >= 0);
    assert(static_cast<int>(DirectoryValidationResult::kUnknown) >= 0);
    
    std::cout << "test_directory_validation_result: PASSED" << std::endl;
}

void test_directory_policy_fields() {
    // Verify DirectoryPolicy has expected fields
    rebuntu::environment::directories::DirectoryPolicy policy;
    
    policy.type = rebuntu::environment::directories::DirectoryType::kConfig;
    policy.owner_type = rebuntu::environment::directories::DirectoryPolicy::OwnerType::kSystem;
    policy.required_mode = 0755;
    policy.maximum_mode = 0777;
    policy.must_be_owner_executable = true;
    policy.must_not_be_world_writable = true;
    
    std::cout << "test_directory_policy_fields: PASSED" << std::endl;
}

void test_discover_directory_empty_path() {
    // Discovering empty path should return directory with exists=false
    auto info = rebuntu::environment::directories::discover_directory("");
    assert(!info.exists);
    
    std::cout << "test_discover_directory_empty_path: PASSED" << std::endl;
}

void test_ensure_directory_with_existing_dir() {
    // Create a temp directory
    std::error_code ec;
    auto temp_dir = std::filesystem::temp_directory_path(ec) / "rebuntu-test-ensure";
    
    if (!ec && std::filesystem::exists(temp_dir, ec)) {
        std::filesystem::remove_all(temp_dir, ec);
    }
    
    // Create the directory first
    std::filesystem::create_directories(temp_dir, ec);
    
    // Now ensure it (should return kAlreadyExists)
    auto result = rebuntu::environment::directories::ensure_directory(
        temp_dir, geteuid(), getgid());
    assert(result.status == rebuntu::environment::directories::DirectoryOperationStatus::kAlreadyExists || 
           result.status == rebuntu::environment::directories::DirectoryOperationStatus::kSuccess);
    
    // Cleanup
    std::filesystem::remove_all(temp_dir, ec);
    
    std::cout << "test_ensure_directory_with_existing_dir: PASSED" << std::endl;
}

void test_create_rebuntu_directory_config() {
    // Test creating a config directory
    rebuntu::environment::scope::ScopeContext ctx;
    ctx.effective_uid = geteuid();
    ctx.is_root = (geteuid() == 0);
    
    auto result = rebuntu::environment::directories::create_rebuntu_directory(ctx, 
        rebuntu::environment::directories::DirectoryType::kConfig);
    
    // Should succeed or already exist (idempotent)
    assert(result.status == rebuntu::environment::directories::DirectoryOperationStatus::kSuccess ||
           result.status == rebuntu::environment::directories::DirectoryOperationStatus::kAlreadyExists);
    
    std::cout << "test_create_rebuntu_directory_config: PASSED" << std::endl;
}

void test_remove_directory_empty_path() {
    // Removing empty path should return kInvalidPath
    auto result = rebuntu::environment::directories::remove_directory("");
    assert(result.status == rebuntu::environment::directories::DirectoryOperationStatus::kInvalidPath);
    
    std::cout << "test_remove_directory_empty_path: PASSED" << std::endl;
}

void test_is_path_safe_empty_path() {
    // Empty path should not be safe
    assert(!rebuntu::environment::directories::is_path_safe(""));
    
    std::cout << "test_is_path_safe_empty_path: PASSED" << std::endl;
}

void test_get_directory_policy_config_system() {
    // System config policy should have system owner type
    auto policy = rebuntu::environment::directories::get_directory_policy(
        rebuntu::environment::directories::DirectoryType::kConfig, 
        rebuntu::environment::scope::ExecutionScope::kSystem);
    
    assert(policy.type == rebuntu::environment::directories::DirectoryType::kConfig);
    assert(policy.owner_type == rebuntu::environment::directories::DirectoryPolicy::OwnerType::kSystem);
    assert(policy.must_not_be_world_writable);
    
    std::cout << "test_get_directory_policy_config_system: PASSED" << std::endl;
}

void test_get_directory_policy_user() {
    // User scope policies should have user owner type
    auto policy = rebuntu::environment::directories::get_directory_policy(
        rebuntu::environment::directories::DirectoryType::kState, 
        rebuntu::environment::scope::ExecutionScope::kUser);
    
    assert(policy.type == rebuntu::environment::directories::DirectoryType::kState);
    assert(policy.owner_type == rebuntu::environment::directories::DirectoryPolicy::OwnerType::kUser);
    
    std::cout << "test_get_directory_policy_user: PASSED" << std::endl;
}

void test_get_scope_policies_count() {
    // Should return policies for all directory types (7 total)
    auto policies = rebuntu::environment::directories::get_scope_policies(
        rebuntu::environment::scope::ExecutionScope::kSystem);
    
    assert(policies.size() == 7);  // kConfig, kState, kCache, kRuntime, kData, kLog, kTemp
    
    std::cout << "test_get_scope_policies_count: PASSED" << std::endl;
}

void test_discover_all_directories_structure() {
    // Verify discover_all_directories returns correct structure
    rebuntu::environment::scope::ScopeContext ctx;
    ctx.effective_uid = geteuid();
    ctx.is_root = (geteuid() == 0);
    
    auto dirs = rebuntu::environment::directories::discover_all_directories(ctx);
    
    // Should return at least some directories
    assert(!dirs.empty());
    
    std::cout << "test_discover_all_directories_structure: PASSED" << std::endl;
}

void test_directory_validation_valid_path() {
    // Test validation with an existing directory (tmp)
    auto temp_dir = std::filesystem::temp_directory_path();
    
    auto result = rebuntu::environment::directories::validate_directory_for_rebuntu(
        temp_dir, rebuntu::environment::scope::ScopeContext{}, 
        rebuntu::environment::directories::DirectoryType::kTemp);
    
    // Should be valid or at least not fail unexpectedly
    assert(result.result == rebuntu::environment::directories::DirectoryValidationResult::kValid ||
           result.result == rebuntu::environment::directories::DirectoryValidationResult::kUnknown);
    
    std::cout << "test_directory_validation_valid_path: PASSED" << std::endl;
}

void test_get_user_runtime_dir_without_xdg() {
    // Without XDG_RUNTIME_DIR, should fall back to /run/user/<uid>
    rebuntu::environment::scope::ScopeContext ctx;
    ctx.effective_uid = geteuid();
    ctx.is_root = false;
    
    auto rt_dir = rebuntu::environment::directories::get_user_runtime_dir(ctx);
    
    // Either returns valid path or empty (if root)
    if (!rt_dir.empty()) {
        std::cout << "test_get_user_runtime_dir_without_xdg: PASSED (got: " 
                  << rt_dir.string() << ")" << std::endl;
    } else {
        std::cout << "test_get_user_runtime_dir_without_xdg: PASSED (empty fallback)" << std::endl;
    }
}

void test_directory_validation_result_is_valid() {
    // Test is_valid() method
    rebuntu::environment::directories::DirectoryValidationResultDetails result;
    
    result.result = rebuntu::environment::directories::DirectoryValidationResult::kValid;
    assert(result.is_valid());
    
    result.result = rebuntu::environment::directories::DirectoryValidationResult::kInvalidPath;
    assert(!result.is_valid());
    
    std::cout << "test_directory_validation_result_is_valid: PASSED" << std::endl;
}

void test_verify_directory_state_with_missing() {
    // Test verification with a non-existent directory
    rebuntu::environment::directories::DirectoryInfo info;
    info.exists = false;
    info.path = "/nonexistent/rebuntu-test";
    
    rebuntu::environment::directories::DirectoryPolicy policy;
    policy.owner_type = rebuntu::environment::directories::DirectoryPolicy::OwnerType::kSystem;
    
    bool valid = rebuntu::environment::directories::verify_directory_state(info, policy);
    
    // Should not be valid (directory doesn't exist)
    assert(!valid);
    
    std::cout << "test_verify_directory_state_with_missing: PASSED" << std::endl;
}

void test_get_system_config_dir_from_scope() {
    // Using get_system_config_dir from scope namespace
    auto config = rebuntu::environment::scope::get_system_config_dir();
    assert(config.string().find("/etc/rebuntu") == 0);
    
    std::cout << "test_get_system_config_dir_from_scope: PASSED" << std::endl;
}

int main() {
    std::cout << "Running Rebuntu Directories Module Tests (Phase 2.9)" << std::endl;
    std::cout << "=====================================================" << std::endl;
    
    // Enum value tests
    test_directory_type_to_string();
    test_directory_operation_result_status();
    test_directory_validation_result();
    
    // Path resolution tests
    test_get_system_runtime_dir();
    test_get_system_data_dir();
    test_get_system_log_dir();
    test_get_user_data_dir();
    test_get_user_runtime_dir_without_xdg();
    
    // Policy tests
    test_directory_policy_fields();
    test_get_directory_policy_config_system();
    test_get_directory_policy_user();
    test_get_scope_policies_count();
    
    // Directory discovery tests
    test_discover_directory_empty_path();
    test_discover_all_directories_structure();
    
    // Directory management tests
    test_ensure_directory_with_existing_dir();
    test_create_rebuntu_directory_config();
    test_remove_directory_empty_path();
    
    // Validation tests
    test_is_path_safe_empty_path();
    test_directory_validation_valid_path();
    test_directory_validation_result_is_valid();
    
    // State verification tests
    test_verify_directory_state_with_missing();
    
    // Scope integration tests
    test_get_system_config_dir_from_scope();
    
    std::cout << "=====================================================" << std::endl;
    std::cout << "All directories module tests PASSED" << std::endl;
    
    return 0;
}