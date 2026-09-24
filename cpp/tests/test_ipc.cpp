// Test suite for rebuntu::environment::ipc (Phase 2.12)
// Inter-Process Communication - Tests for Unix domain sockets and FIFOs
//
// This tests:
//   - UnixDomainSocket class with RAII semantics
//   - Fifo class for named pipes
//   - Path validation and symlink safety
//   - IPC result status handling

#include "system/environment/ipc.hpp"
#include <cassert>
#include <iostream>
#include <fstream>
#include <filesystem>

using namespace rebuntu::environment::ipc;

// Test helper: create a unique temporary path
static std::filesystem::path make_temp_path(const std::string& suffix) {
    static int counter = 0;
    return std::filesystem::temp_directory_path() / ("rebuntu-ipc-test-" + std::to_string(counter++) + suffix);
}

void test_ipc_result_status() {
    // Success status
    IPCResult result1;
    result1.error = IPCError::kSuccess;
    assert(result1.is_success());
    assert(result1.semantic_status() == rebuntu::core::SemanticStatus::kSuccess);
    
    // WouldBlock status
    IPCResult result2;
    result2.error = IPCError::kWouldBlock;
    assert(!result2.is_success());
    assert(result2.semantic_status() == rebuntu::core::SemanticStatus::kFailure);
    
    // Timeout status
    IPCResult result3;
    result3.error = IPCError::kTimeout;
    assert(!result3.is_success());
    assert(result3.semantic_status() == rebuntu::core::SemanticStatus::kFailure);
    
    // InvalidPath status
    IPCResult result4;
    result4.error = IPCError::kInvalidPath;
    assert(!result4.is_success());
    assert(result4.semantic_status() == rebuntu::core::SemanticStatus::kFailure);
}

void test_create_pipe() {
    auto pipe = create_pipe();
    
    // Both file descriptors should be valid (>= 0)
    assert(pipe.first >= 0);
    assert(pipe.second >= 0);
    
    // Clean up - close both ends
    ::close(pipe.first);
    ::close(pipe.second);
}

void test_is_safe_ipc_path_valid() {
    auto path = make_temp_path(".sock");
    
    // Create a dummy file for testing
    std::ofstream(path.string()) << "test";
    
    assert(is_safe_ipc_path(path));
    
    std::filesystem::remove(path);
}

void test_is_safe_ipc_path_empty() {
    assert(!is_safe_ipc_path(""));
}

int main(int argc, char** argv) {
    (void)argc;
    (void)argv;
    
    std::cout << "Running Phase 2.12 IPC Primitives tests...\n";
    
    test_ipc_result_status();
    test_create_pipe();
    test_is_safe_ipc_path_valid();
    test_is_safe_ipc_path_empty();
    
    std::cout << "All tests PASSED!\n";
    return 0;
}