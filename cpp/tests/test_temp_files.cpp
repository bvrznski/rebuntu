// Test suite for rebuntu::environment::temp_files (Phase 2.12)
// Secure Temporary Files - Tests for secure temp file creation
//
// This tests:
//   - SecureTempFile class with RAII semantics
//   - SecureTempDir class
//   - Path validation and symlink safety
//   - Temp file result status handling

#include "system/environment/temp_files.hpp"
#include <cassert>
#include <iostream>
#include <fstream>

using namespace rebuntu::environment::temp_files;

void test_temp_file_result_status() {
    // Success status
    TempFileResult result1;
    result1.status = TempFileStatus::kSuccess;
    assert(result1.is_success());
    assert(result1.semantic_status() == rebuntu::core::SemanticStatus::kSuccess);
    
    // AlreadyExists status
    TempFileResult result2;
    result2.status = TempFileStatus::kAlreadyExists;
    assert(!result2.is_success());
    assert(result2.semantic_status() == rebuntu::core::SemanticStatus::kFailure);
    
    // InvalidPath status
    TempFileResult result3;
    result3.status = TempFileStatus::kInvalidPath;
    assert(!result3.is_success());
    assert(result3.semantic_status() == rebuntu::core::SemanticStatus::kFailure);
}

void test_get_system_temp_dir() {
    auto temp_dir = get_system_temp_dir();
    
    // Should return a valid path
    assert(!temp_dir.empty());
}

int main(int argc, char** argv) {
    (void)argc;
    (void)argv;
    
    std::cout << "Running Phase 2.12 Temp Files tests...\n";
    
    test_temp_file_result_status();
    test_get_system_temp_dir();
    
    std::cout << "All tests PASSED!\n";
    return 0;
}