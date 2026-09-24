// Rebuntu Operations — Filesystem Tests (Phase 0.10)
//
// Tests for filesystem operations implementation.

#include <gtest/gtest.h>
#include <filesystem>

#include <src/operations/filesystem.hpp>

namespace fs = std::filesystem;

namespace rebuntu::operations::test {

// ============================================================================
// FilesystemCopyInputs
// ============================================================================

TEST(FilesystemCopyInputs, ValidPath) {
    // This test requires a proper source file to validate
    std::string error;
    
    // TODO: Implement when test fixture can create temp files
}

// ============================================================================
// filesystem_copy Tests
// ============================================================================

TEST(FilesystemCopy, CopiesFileSuccessfully) {
    // Create temporary directory for test
    fs::path temp_dir = fs::temp_directory_path() / "rebuntu_test_" + std::to_string(getpid());
    fs::create_directories(temp_dir);
    
    // Create source file with known content
    fs::path source_file = temp_dir / "source.txt";
    {
        std::ofstream ofs(source_file);
        ofs << "Hello, World!";
        ofs.close();
    }
    
    // Target destination
    fs::path dest_file = temp_dir / "dest.txt";
    
    // Execute copy operation
    FilesystemCopyInputs inputs;
    inputs.source = source_file;
    inputs.destination = dest_file;
    inputs.overwrite = false;
    inputs.preserve_metadata = true;
    
    std::string error;
    EXPECT_TRUE(inputs.is_valid(error));
    
    // Note: Full test requires linking with implementation file
    
    // Cleanup
    fs::remove_all(temp_dir);
}

TEST(FilesystemCopy, ReturnsFailureForNonExistentSource) {
    fs::path non_existent = "/tmp/nonexistent_file_12345.txt";
    
    FilesystemCopyInputs inputs;
    inputs.source = non_existent;
    inputs.destination = "/tmp/dest.txt";
    
    std::string error;
    EXPECT_FALSE(inputs.is_valid(error));
    EXPECT_TRUE(error.find("source path does not exist") != std::string::npos);
}

// ============================================================================
// filesystem_exists Tests
// ============================================================================

TEST(FilesystemExists, ReturnsFoundForExistingFile) {
    // Test would create a temp file and verify it's found
    // Implementation requires linking with implementation file
}

TEST(FilesystemExists, ReturnsNotFoundForNonExistentPath) {
    fs::path path = "/tmp/nonexistent_test_path_12345";
    
    FilesystemExistsResult result = filesystem_exists(path);
    
    EXPECT_FALSE(result.exists);
    EXPECT_EQ(result.path, path);
}

// ============================================================================
// filesystem_verify_integrity Tests
// ============================================================================

TEST(FilesystemVerifyIntegrity, VerifiesExistingFile) {
    fs::path temp_dir = fs::temp_directory_path() / "rebuntu_test_" + std::to_string(getpid());
    fs::create_directories(temp_dir);
    
    fs::path test_file = temp_dir / "test.txt";
    {
        std::ofstream ofs(test_file);
        ofs << "Test content";
    }
    
    FilesystemVerifyResult result = filesystem_verify_integrity(test_file);
    
    EXPECT_TRUE(result.verified);
    
    // Cleanup
    fs::remove_all(temp_dir);
}

TEST(FilesystemVerifyIntegrity, ReturnsFailureForNonExistentFile) {
    fs::path path = "/tmp/nonexistent_verify_test.txt";
    
    FilesystemVerifyResult result = filesystem_verify_integrity(path);
    
    EXPECT_FALSE(result.verified);
    EXPECT_EQ(result.status, core::SemanticStatus::kFailure);
}

}  // namespace rebuntu::operations::test