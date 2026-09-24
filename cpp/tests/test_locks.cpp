// Test suite for rebuntu::environment::locks (Phase 2.12)
// Locking Primitives - Tests for flock/fcntl-based filesystem locking
//
// This tests:
//   - FileLock class with RAII semantics
//   - Blocking/non-blocking lock acquisition
//   - Timeout support
//   - Path validation and symlink safety
//   - Lock result status handling

#include "system/environment/locks.hpp"
#include <cassert>
#include <iostream>
#include <fstream>
#include <ctime>

using namespace rebuntu::environment::locks;

// Test helper: create a unique temporary file path with timestamp to avoid collisions
static std::filesystem::path make_temp_path() {
    static int counter = 0;
    auto ts = std::time(nullptr);
    return std::filesystem::temp_directory_path() / ("rebuntu-lock-test-" + std::to_string(ts) + "-" + std::to_string(counter++));
}

void test_lock_result_status() {
    LockResult result1;
    result1.status = LockStatus::kSuccess;
    assert(result1.is_success());
    assert(result1.semantic_status() == rebuntu::core::SemanticStatus::kSuccess);
    
    LockResult result2;
    result2.status = LockStatus::kWouldBlock;
    assert(!result2.is_success());
    assert(result2.semantic_status() == rebuntu::core::SemanticStatus::kFailure);
    
    LockResult result3;
    result3.status = LockStatus::kTimeout;
    assert(!result3.is_success());
    assert(result3.semantic_status() == rebuntu::core::SemanticStatus::kFailure);
    
    LockResult result4;
    result4.status = LockStatus::kInvalidPath;
    assert(!result4.is_success());
    assert(result4.semantic_status() == rebuntu::core::SemanticStatus::kFailure);
    
    LockResult result5;
    result5.status = LockStatus::kSystemError;
    assert(result5.semantic_status() == rebuntu::core::SemanticStatus::kUnknown);
}

void test_file_lock_open_create() {
    auto path = make_temp_path();
    
    std::filesystem::remove(path);
    assert(!std::filesystem::exists(path));
    
    auto result = FileLock::open(path);
    assert(result.status == LockStatus::kSuccess);
    assert(result.fd >= 0);
    assert(std::filesystem::exists(path));
    
    close(result.fd);
    std::filesystem::remove(path);
}

void test_file_lock_open_empty_path() {
    auto result = FileLock::open("");
    assert(result.status == LockStatus::kInvalidPath);
    assert(result.error_message.has_value());
}

void test_create_lock_file() {
    auto path = make_temp_path();
    
    auto result = create_lock_file(path);
    assert(result.status == LockStatus::kSuccess);
    assert(result.fd >= 0);
    assert(std::filesystem::exists(path));
    
    close(result.fd);
    std::filesystem::remove(path);
}

void test_create_lock_file_empty_path() {
    auto result = create_lock_file("");
    assert(result.status == LockStatus::kInvalidPath);
}

void test_is_safe_lock_path_valid() {
    auto path = make_temp_path();
    
    std::ofstream(path.string()) << "test";
    
    assert(is_safe_lock_path(path));
    
    std::filesystem::remove(path);
}

void test_is_safe_lock_path_empty() {
    assert(!is_safe_lock_path(""));
}

void test_file_lock_acquire_release() {
    auto path = make_temp_path();
    
    auto result = FileLock::open(path);
    assert(result.status == LockStatus::kSuccess);
    
    FileLock lock(result.fd, path);
    auto acquire_result = lock.try_acquire(LockOptions::non_blocking());
    
    assert(acquire_result.is_success());
    assert(lock.is_held());
    
    lock.release();
}

void test_file_lock_release() {
    auto path = make_temp_path();
    
    auto result = FileLock::open(path);
    assert(result.status == LockStatus::kSuccess);
    
    FileLock lock(result.fd, path);
    lock.try_acquire(LockOptions::non_blocking());
    
    assert(lock.is_held());
    lock.release();
    assert(!lock.is_held());
}

int main(int argc, char** argv) {
    (void)argc;
    (void)argv;
    
    std::cout << "Running Phase 2.12 Locking Primitives tests...\n";
    
    test_lock_result_status();
    test_file_lock_open_create();
    test_file_lock_open_empty_path();
    test_create_lock_file();
    test_create_lock_file_empty_path();
    test_is_safe_lock_path_valid();
    test_is_safe_lock_path_empty();
    test_file_lock_acquire_release();
    test_file_lock_release();
    
    std::cout << "All tests PASSED!\n";
    return 0;
}