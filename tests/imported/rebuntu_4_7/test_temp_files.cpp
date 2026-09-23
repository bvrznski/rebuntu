// Rebuntu — Secure Temporary Files Tests (Phase 2.12)
//
// Test the secure temporary file handling:
//   - TempFileResult status handling
//   - Unique name generation

#include <system/environment/temp_files.hpp>

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <filesystem>

namespace {
int g_failures = 0;
#define CHECK(cond) do { if (!(cond)) { std::cerr << "CHECK failed: " << #cond << " (line " << __LINE__ << ")\n"; ++g_failures; } } while(0)
}  // namespace

void test_tempfile_result_status() {
    using rebuntu::environment::temp_files::TempFileStatus;
    using rebuntu::environment::temp_files::TempFileResult;
    
    TempFileResult result;
    result.status = TempFileStatus::kSuccess;
    CHECK(result.is_success());
    CHECK(result.semantic_status() == rebuntu::core::SemanticStatus::kSuccess);
    
    result.status = TempFileStatus::kPermissionDenied;
    CHECK(!result.is_success());
    CHECK(result.semantic_status() == rebuntu::core::SemanticStatus::kFailure);
}

void test_tempfile_result_unknown_status() {
    using rebuntu::environment::temp_files::TempFileStatus;
    using rebuntu::environment::temp_files::TempFileResult;
    
    TempFileResult result;
    result.status = TempFileStatus::kUnknown;
    CHECK(!result.is_success());
    CHECK(result.semantic_status() == rebuntu::core::SemanticStatus::kUnknown);
}

void test_unique_name_generation() {
    using rebuntu::environment::temp_files::generate_unique_name;
    
    std::string name1 = generate_unique_name("test-");
    std::string name2 = generate_unique_name("test-");
    
    // Names should be different (with very high probability)
    CHECK(name1 != name2);
    
    // Names should start with prefix
    CHECK(name1.substr(0, 5) == "test-");
}

void test_is_safe_temp_directory() {
    using rebuntu::environment::temp_files::is_safe_temp_directory;
    
    std::error_code ec;
    auto temp_dir = std::filesystem::temp_directory_path();
    
    // Should return true for a valid temp directory
    CHECK(is_safe_temp_directory(temp_dir));
    
    // Should return false for an empty path
    CHECK(!is_safe_temp_directory(std::filesystem::path()));
}

void test_secure_temp_file_create() {
    using rebuntu::environment::temp_files::SecureTempFile;
    
    std::error_code ec;
    auto temp_dir = std::filesystem::temp_directory_path() / "rebuntu-test-tmpfile";
    
    // Clean up if exists
    std::filesystem::remove_all(temp_dir, ec);
    std::filesystem::create_directories(temp_dir, ec);
    
    auto result = SecureTempFile::create_in_directory(temp_dir, "test-", 0600);
    CHECK(result.is_success());
    CHECK(result.fd >= 0);
    CHECK(!result.path.empty());
    
    // File should exist
    CHECK(std::filesystem::exists(result.path));
}

void test_secure_temp_file_ownership() {
    using rebuntu::environment::temp_files::SecureTempFile;
    
    std::error_code ec;
    auto temp_dir = std::filesystem::temp_directory_path() / "rebuntu-test-ownership";
    
    // Clean up if exists
    std::filesystem::remove_all(temp_dir, ec);
    std::filesystem::create_directories(temp_dir, ec);
    
    {
        auto result = SecureTempFile::create_in_directory(temp_dir, "test-", 0600);
        CHECK(result.is_success());
        
        int fd = result.fd;
        std::filesystem::path path = result.path;
        
        // Test move semantics
        SecureTempFile moved(std::move(fd), std::move(path));
        CHECK(moved.is_valid());
        CHECK(moved.fd() == fd);
    }
    
    // After scope exit, file should be removed by destructor
}

void test_secure_temp_dir_create() {
    using rebuntu::environment::temp_files::SecureTempDir;
    
    std::error_code ec;
    auto parent_dir = std::filesystem::temp_directory_path() / "rebuntu-test-tmpdir";
    
    // Clean up if exists
    std::filesystem::remove_all(parent_dir, ec);
    std::filesystem::create_directories(parent_dir, ec);
    
    {
        // First create the directory manually since SecureTempDir doesn't auto-create
        auto dir_path = parent_dir / "test-dir";
        std::filesystem::create_directory(dir_path, ec);
        
        SecureTempDir dir(dir_path, 0700);
        CHECK(dir.is_valid());
        
        // Directory should exist (but will be removed by destructor when scope ends)
        CHECK(std::filesystem::exists(dir_path));
    }
}

void test_secure_temp_dir_ownership() {
    using rebuntu::environment::temp_files::SecureTempDir;
    
    std::error_code ec;
    auto parent_dir = std::filesystem::temp_directory_path() / "rebuntu-test-tmpdir-ownership";
    
    // Clean up if exists
    std::filesystem::remove_all(parent_dir, ec);
    std::filesystem::create_directories(parent_dir, ec);
    
    {
        SecureTempDir dir1(parent_dir / "test-dir1", 0700);
        
        // Test move semantics
        SecureTempDir dir2(std::move(dir1));
        CHECK(dir2.is_valid());
    }
}

void test_runtime_tmp_dir() {
    using rebuntu::environment::temp_files::get_runtime_tmp_dir;
    using rebuntu::environment::sessions::RuntimeDirectoryInfo;
    
    // With unavailable runtime directory, should return empty path
    RuntimeDirectoryInfo rt_info;
    rt_info.status = rebuntu::environment::sessions::RuntimeDirStatus::kUnavailable;
    CHECK(get_runtime_tmp_dir(rt_info).empty());
}

int main() {
    std::cout << "Testing Secure Temporary Files (Phase 2.12)...\n";
    
    test_tempfile_result_status();
    test_tempfile_result_unknown_status();
    test_unique_name_generation();
    test_is_safe_temp_directory();
    test_secure_temp_file_create();
    test_secure_temp_file_ownership();
    test_secure_temp_dir_create();
    test_secure_temp_dir_ownership();
    test_runtime_tmp_dir();
    
    std::cout << "\nTemp File Tests Complete\n";
    if (g_failures > 0) {
        std::cerr << g_failures << " test(s) failed.\n";
        return 1;
    }
    std::cout << "All tests passed.\n";
    return 0;
}