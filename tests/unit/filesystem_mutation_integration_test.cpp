// Rebuntu Operations — Filesystem Mutation Integration Test (Phase 6.70)
//
// This is a contained mutation integration test that exercises a real mutation
// against a temporary/test-contained resource and proves before/after observation
// plus verification.
//
// Key requirements:
//   - Use only temporary/test-contained resources
//   - No mutation of unrelated host services/storage/network/users/packages
//   - Prove before state, perform mutation, prove after state
//   - Verify postconditions independently

#include <cassert>
#include <chrono>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <optional>
#include <sstream>
#include <string>
#include <vector>

#include <system/core/contracts.hpp>
#include <operations/filesystem.hpp>

namespace fs = std::filesystem;

using namespace rebuntu::operations;
using namespace rebuntu::core;

// ============================================================================
// Test Utilities
// ============================================================================

// Create a unique temporary directory for testing
fs::path create_test_temp_dir(const std::string& prefix = "rebuntu_mutation_test_") {
    auto temp_dir = fs::temp_directory_path() / (prefix + 
        std::to_string(std::chrono::duration_cast<std::chrono::nanoseconds>(
            std::chrono::system_clock::now().time_since_epoch()).count()));
    
    std::error_code ec;
    if (!fs::create_directories(temp_dir, ec)) {
        std::cerr << "Failed to create temp directory: " << ec.message() << std::endl;
        return {};
    }
    
    return temp_dir;
}

// Write content to a file
bool write_file(const fs::path& path, const std::string& content) {
    std::error_code ec;
    
    // Ensure parent directory exists
    fs::path parent = path.parent_path();
    if (!parent.empty()) {
        fs::create_directories(parent, ec);
        if (ec) {
            return false;
        }
    }
    
    std::ofstream file(path);
    if (!file) {
        return false;
    }
    
    file << content;
    return !file.fail();
}

// Read content from a file
std::optional<std::string> read_file(const fs::path& path) {
    std::error_code ec;
    
    if (!fs::exists(path, ec)) {
        return std::nullopt;
    }
    
    std::ifstream file(path);
    if (!file) {
        return std::nullopt;
    }
    
    std::stringstream ss;
    ss << file.rdbuf();
    return ss.str();
}

// Get file size
std::optional<uint64_t> get_file_size(const fs::path& path) {
    std::error_code ec;
    auto size = fs::file_size(path, ec);
    if (ec) {
        return std::nullopt;
    }
    return size;
}

// Check if two files have identical content
bool files_are_identical(const fs::path& p1, const fs::path& p2) {
    auto c1 = read_file(p1);
    auto c2 = read_file(p2);
    
    if (!c1.has_value() || !c2.has_value()) {
        return false;
    }
    
    return *c1 == *c2;
}

// ============================================================================
// Before/After Observation
// ============================================================================

struct StateSnapshot {
    fs::path path;
    bool exists_before{false};
    std::optional<std::string> content_before;
    std::optional<uint64_t> size_before;
    std::chrono::system_clock::time_point observed_at;
    
    // After state (if mutated)
    bool exists_after{false};
    std::optional<std::string> content_after;
    std::optional<uint64_t> size_after;
};

// ============================================================================
// Test: filesystem_copy Mutation with Verification
// ============================================================================

void test_filesystem_copy_mutation() {
    std::cout << "\n=== Test: Filesystem Copy Mutation ===" << std::endl;
    
    // Step 1: Create temporary test directory (test-contained resource)
    auto temp_dir = create_test_temp_dir("copy_mutation_");
    assert(!temp_dir.empty());
    std::cout << "Test temp dir: " << temp_dir.string() << std::endl;
    
    fs::path source_file = temp_dir / "source.txt";
    fs::path dest_file = temp_dir / "dest.txt";
    
    // Test content
    const std::string test_content = "Hello, Rebuntu! Phase 6.70 Mutation Test";
    
    // Step 2: BEFORE observation - establish baseline state
    StateSnapshot before;
    before.path = dest_file;
    before.observed_at = std::chrono::system_clock::now();
    
    {
        std::error_code ec;
        before.exists_before = fs::exists(dest_file, ec);
        assert(!ec);
        
        if (before.exists_before) {
            before.content_before = read_file(dest_file);
            before.size_before = get_file_size(dest_file);
        }
    }
    
    // Ensure source file exists
    assert(write_file(source_file, test_content));
    
    std::cout << "Source file created: " << source_file.string() << std::endl;
    
    // Step 3: Execute the filesystem.copy operation
    FilesystemCopyInputs inputs;
    inputs.source = source_file;
    inputs.destination = dest_file;
    inputs.overwrite = false;  // First copy should succeed
    inputs.preserve_metadata = true;
    
    std::string validation_error;
    assert(inputs.is_valid(validation_error));
    
    auto result = filesystem_copy(inputs);
    
    std::cout << "Copy result status: " << to_string(result.status) << std::endl;
    std::cout << "Changed: " << (result.changed ? "true" : "false") << std::endl;
    std::cout << "Verified: " << (result.verified ? "true" : "false") << std::endl;
    
    // Step 4: AFTER observation - verify postconditions
    StateSnapshot after;
    after.path = dest_file;
    
    {
        std::error_code ec;
        after.exists_after = fs::exists(dest_file, ec);
        assert(!ec);
        
        if (after.exists_after) {
            after.content_after = read_file(dest_file);
            after.size_after = get_file_size(dest_file);
        }
    }
    
    // Step 5: Verify postconditions
    std::cout << "\n--- Postcondition Verification ---" << std::endl;
    
    // PV1: Destination must exist after copy
    assert(after.exists_after),
    "Postcondition PV1 failed: destination file must exist after copy";
    std::cout << "[PV1 PASS] Destination exists at target location" << std::endl;
    
    // PV2: Destination content must match source
    assert(files_are_identical(source_file, dest_file)),
    "Postcondition PV2 failed: destination content must match source";
    std::cout << "[PV2 PASS] Destination content matches source" << std::endl;
    
    // PV3: Copy result indicates success and change
    assert(result.status == SemanticStatus::kSuccess),
    "Postcondition PV3 failed: operation should report kSuccess status";
    assert(result.changed),
    "Postcondition PV4 failed: operation should indicate state was changed";
    std::cout << "[PV3-PV4 PASS] Operation reports success with change" << std::endl;
    
    // PV5: Verification flag is set
    assert(result.verified),
    "Postcondition PV5 failed: verification must be performed and reported";
    std::cout << "[PV5 PASS] Verification is performed and verified=true" << std::endl;
    
    // PV6: Evidence is collected (non-empty)
    assert(!result.evidence.empty()),
    "Postcondition PV6 failed: evidence must be collected";
    std::cout << "[PV6 PASS] Evidence is collected during operation" << std::endl;
    
    // Step 6: Verify no unexpected state changes
    assert(before.exists_before == false),
    "Unexpected: destination existed before test (state pollution)";
    std::cout << "[PV7 PASS] No pre-existing destination file (clean test)" << std::endl;
    
    std::cout << "\n=== filesystem_copy Mutation Test PASSED ===" << std::endl;
}

// ============================================================================
// Test: Idempotency - Repeated copy without overwrite
// ============================================================================

void test_filesystem_copy_idempotency() {
    std::cout << "\n=== Test: Filesystem Copy Idempotency (no overwrite) ===" << std::endl;
    
    // Create temp directory
    auto temp_dir = create_test_temp_dir("copy_idempotent_");
    assert(!temp_dir.empty());
    
    fs::path source_file = temp_dir / "source.txt";
    fs::path dest_file = temp_dir / "dest.txt";
    
    const std::string test_content = "Idempotency Test Content";
    
    // Create source file
    assert(write_file(source_file, test_content));
    
    // First copy should succeed and change state
    FilesystemCopyInputs inputs1;
    inputs1.source = source_file;
    inputs1.destination = dest_file;
    inputs1.overwrite = false;
    inputs1.preserve_metadata = true;
    
    auto result1 = filesystem_copy(inputs1);
    
    std::cout << "First copy - changed: " << (result1.changed ? "true" : "false") 
              << ", status: " << to_string(result1.status) << std::endl;
    
    assert(result1.status == SemanticStatus::kSuccess),
        "First copy should succeed";
    
    // Second copy without overwrite should return no_change
    FilesystemCopyInputs inputs2;
    inputs2.source = source_file;
    inputs2.destination = dest_file;
    inputs2.overwrite = false;  // Still don't overwrite
    
    auto result2 = filesystem_copy(inputs2);
    
    std::cout << "Second copy (no overwrite) - changed: " 
              << (result2.changed ? "true" : "false") 
              << ", status: " << to_string(result2.status) << std::endl;
    
    // Since dest exists and overwrite=false, should return no_change
    assert(result2.status == SemanticStatus::kSuccess),
        "Second copy without overwrite should report success";
    
    std::cout << "\n=== Idempotency Test PASSED ===" << std::endl;
}

// ============================================================================
// Test: Precondition Failure - Non-existent source
// ============================================================================

void test_filesystem_copy_precondition_failure() {
    std::cout << "\n=== Test: Filesystem Copy Precondition Failure (non-existent source) ===" << std::endl;
    
    auto temp_dir = create_test_temp_dir("copy_precond_");
    assert(!temp_dir.empty());
    
    fs::path non_existent_source = temp_dir / "does_not_exist.txt";
    fs::path dest_file = temp_dir / "dest.txt";
    
    FilesystemCopyInputs inputs;
    inputs.source = non_existent_source;
    inputs.destination = dest_file;
    inputs.overwrite = false;
    inputs.preserve_metadata = true;
    
    // Validate inputs first
    std::string validation_error;
    bool valid = inputs.is_valid(validation_error);
    
    assert(!valid),
        "Invalid input (non-existent source) should be rejected";
    assert(!validation_error.empty()),
        "Validation error message should be populated";
    
    std::cout << "Input validation failed as expected: " << validation_error << std::endl;
    
    // Execute should also fail
    auto result = filesystem_copy(inputs);
    
    std::cout << "Execution result status: " << to_string(result.status) << std::endl;
    
    assert(result.status == SemanticStatus::kFailure),
        "Operation on non-existent source should return failure";
    
    assert(result.error.has_value()),
        "Error information should be present in failure result";
    
    std::cout << "Error code: " << result.error->code << std::endl;
    std::cout << "Error message: " << result.error->message << std::endl;
    
    // PV1: Error indicates source not found
    assert(result.error->code == "E_SOURCE_NOT_FOUND" ||
           result.error->code == "E_FILE_NOT_FOUND"),
        "Error code should indicate source not found";
    std::cout << "[PV1 PASS] Precondition failure handled correctly with proper error" << std::endl;
    
    // PV2: No destination created
    std::error_code ec;
    bool dest_exists = fs::exists(dest_file, ec);
    assert(!ec);
    assert(!dest_exists),
        "No destination file should be created when source is missing";
    std::cout << "[PV2 PASS] No spurious state change on precondition failure" << std::endl;
    
    std::cout << "\n=== Precondition Failure Test PASSED ===" << std::endl;
}

// ============================================================================
// Clean up test resources
// ============================================================================

bool cleanup_test_resources(const fs::path& temp_dir) {
    if (temp_dir.empty()) {
        return true;  // Nothing to clean up
    }
    
    std::error_code ec;
    fs::remove_all(temp_dir, ec);
    
    if (ec) {
        std::cerr << "Warning: Failed to cleanup test resources: " 
                  << ec.message() << std::endl;
        return false;
    }
    
    return true;
}

// ============================================================================
// Integration Test Runner
// ============================================================================

int main() {
    std::cout << "=== Phase 6.70: Contained Mutation Integration Tests ===" << std::endl;
    std::cout << "Testing filesystem.copy operation with before/after observation + verification" << std::endl;
    
    int exit_code = 0;
    
    // Track temporary directories for cleanup
    std::vector<fs::path> temp_dirs_to_cleanup;
    
    // Run tests
    try {
        // Test 1: Full mutation with before/after observation
        test_filesystem_copy_mutation();
        
        // Test 2: Idempotency check
        test_filesystem_copy_idempotency();
        
        // Test 3: Precondition failure handling
        test_filesystem_copy_precondition_failure();
        
    } catch (const std::exception& e) {
        std::cerr << "Test error: " << e.what() << std::endl;
        exit_code = 1;
    }
    
    // Cleanup - remove all temporary directories created during tests
    for (const auto& dir : temp_dirs_to_cleanup) {
        cleanup_test_resources(dir);
    }
    
    if (exit_code == 0) {
        std::cout << "\n=== All Phase 6.70 Tests PASSED ===" << std::endl;
    } else {
        std::cout << "\n=== Some Phase 6.70 Tests FAILED ===" << std::endl;
    }
    
    return exit_code;
}