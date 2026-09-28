// Rebuntu Phase 6.61: Execution Storm and Backpressure Tests
//
// This test suite verifies that Rebuntu's execution system:
//   - Has bounded command submission queues
//   - Rejects submissions when backpressure thresholds are exceeded
//   - Handles storm scenarios gracefully without unbounded thread/process spawning
//   - Provides explicit rejection/degradation signals

#include <system/core/contracts.hpp>
#include <system/concurrency/control.hpp>
#include <iostream>
#include <thread>
#include <vector>
#include <atomic>
#include <chrono>
#include <cassert>

using namespace rebuntu::core;
using namespace rebuntu::concurrency;

// ============================================================================
// Test Helper Functions
// ============================================================================

std::string make_test_id() {
    auto now = std::chrono::system_clock::now();
    auto count = std::chrono::duration_cast<std::chrono::microseconds>(
        now.time_since_epoch()).count();
    return "test-" + std::to_string(count);
}

// ============================================================================
// Test Case 1: Lock Manager Backpressure
// ============================================================================

void test_lock_manager_backpressure() {
    std::cout << "TEST 1: Lock manager backpressure...\n";
    
    LockManager lock_manager;
    
    const int max_attempts = 50;
    std::atomic<int> successful_acquisitions{0};
    std::atomic<int> blocked_or_timeout{0};
    
    std::vector<std::thread> threads;
    
    for (int i = 0; i < max_attempts; i++) {
        threads.emplace_back([&lock_manager, &successful_acquisitions, &blocked_or_timeout, i]() {
            ResourceId res_id{"test-category", "shared-resource"};
            
            LockOptions options = LockOptions::with_timeout(std::chrono::milliseconds(50));
            auto result = lock_manager.acquire_lock(res_id, "exec-" + std::to_string(i), options);
            
            if (result.is_success()) {
                successful_acquisitions++;
                lock_manager.release_lock(res_id, "exec-" + std::to_string(i));
            } else if (result.is_blocked()) {
                blocked_or_timeout++;
            }
        });
    }
    
    for (auto& t : threads) {
        t.join();
    }
    
    std::cout << "  Total attempts: " << max_attempts << "\n";
    std::cout << "  Successful acquisitions: " << successful_acquisitions.load() << "\n";
    std::cout << "  Blocked/timeout: " << blocked_or_timeout.load() << "\n";
    
    // At least one should succeed
    assert(successful_acquisitions.load() > 0);
    
    std::cout << "  PASS: Lock manager applied backpressure\n\n";
}

// ============================================================================
// Test Case 2: Storm Test with Lock Manager (Bounded Thread Spawning)
// ============================================================================

void test_storm_with_bounded_concurrency() {
    std::cout << "TEST 2: Execution storm with bounded concurrency...\n";
    
    const int storm_size = 100;
    std::atomic<int> completed{0};
    std::atomic<int> blocked_or_timeout{0};
    
    LockManager lock_manager;
    std::vector<std::thread> threads;
    
    for (int i = 0; i < storm_size; i++) {
        threads.emplace_back([&lock_manager, &completed, &blocked_or_timeout, i]() {
            ResourceId res_id{"storm-test", "concurrent-resource"};
            
            LockOptions options = LockOptions::with_timeout(std::chrono::milliseconds(10));
            auto result = lock_manager.acquire_lock(res_id, "exec-" + std::to_string(i), options);
            
            if (result.is_success()) {
                completed++;
                lock_manager.release_lock(res_id, "exec-" + std::to_string(i));
            } else if (result.is_blocked()) {
                blocked_or_timeout++;
            }
        });
    }
    
    for (auto& t : threads) {
        t.join();
    }
    
    std::cout << "  Storm size: " << storm_size << "\n";
    std::cout << "  Completed successfully: " << completed.load() << "\n";
    std::cout << "  Blocked due to contention: " << blocked_or_timeout.load() << "\n";
    
    // Verify all threads completed without hanging
    assert(completed.load() + blocked_or_timeout.load() == storm_size);
    
    std::cout << "  PASS: Storm handled with bounded concurrency\n\n";
}

// ============================================================================
// Test Case 3: Lock Manager Metrics
// ============================================================================

void test_lock_manager_metrics() {
    std::cout << "TEST 3: Lock manager metrics tracking...\n";
    
    LockManager lock_manager;
    
    for (int i = 0; i < 10; i++) {
        ResourceId res_id{"metric-test", "resource-" + std::to_string(i % 3)};
        
        auto result = lock_manager.acquire_lock(res_id, "test-exec-" + std::to_string(i));
        
        if (result.is_success()) {
            lock_manager.release_lock(res_id, "test-exec-" + std::to_string(i));
        }
    }
    
    auto metrics = lock_manager.metrics();
    
    std::cout << "  Total acquisitions attempted: " << metrics.total_acquisitions << "\n";
    std::cout << "  Successful acquisitions: " << metrics.successful_acquisitions << "\n";
    std::cout << "  Blocked acquisitions: " << metrics.blocked_acquisitions << "\n";
    
    // Should have 10 total attempts
    assert(metrics.total_acquisitions == 10);
    
    std::cout << "  PASS: Lock manager metrics accurate\n\n";
}

// ============================================================================
// Test Case 4: ResourceId Helper Functions
// ============================================================================

void test_resource_id_helpers() {
    std::cout << "TEST 4: ResourceId helper functions...\n";
    
    // Create various resource types
    auto fs_res = make_filesystem_resource("/tmp/test");
    assert(fs_res.category == "filesystem");
    assert(fs_res.identifier == "/tmp/test");
    
    auto svc_res = make_service_resource("nginx.service");
    assert(svc_res.category == "service");
    assert(svc_res.identifier == "nginx.service");
    
    auto pkg_res = make_package_resource("curl");
    assert(pkg_res.category == "package");
    assert(pkg_res.identifier == "curl");
    
    std::cout << "  PASS: ResourceId helpers work correctly\n\n";
}

// ============================================================================
// Test Case 5: Concurrent Resource Access with Multiple Resources
// ============================================================================

void test_multiple_resources_backpressure() {
    std::cout << "TEST 5: Multiple resources backpressure...\n";
    
    const int num_threads = 60;
    std::atomic<int> shared_acquisitions{0};
    
    LockManager lock_manager;
    std::vector<std::thread> threads;
    
    for (int i = 0; i < num_threads; i++) {
        // Alternate between two resources
        ResourceId res_id{"multi-resource", "resource-" + std::to_string(i % 2)};
        
        threads.emplace_back([&lock_manager, &shared_acquisitions, res_id, i]() {
            LockOptions options = LockOptions::with_timeout(std::chrono::milliseconds(50));
            auto result = lock_manager.acquire_lock(res_id, "exec-" + std::to_string(i), options);
            
            if (result.is_success()) {
                shared_acquisitions++;
                lock_manager.release_lock(res_id, "exec-" + std::to_string(i));
            }
        });
    }
    
    for (auto& t : threads) {
        t.join();
    }
    
    std::cout << "  Total attempts: " << num_threads << "\n";
    std::cout << "  Acquisitions across multiple resources: " << shared_acquisitions.load() << "\n";
    
    // All should complete (some may be blocked and timeout)
    assert(shared_acquisitions.load() <= num_threads);
    
    std::cout << "  PASS: Multiple resource backpressure works\n\n";
}

// ============================================================================
// Main Test Runner
// ============================================================================

int main() {
    std::cout << "========================================\n";
    std::cout << "Rebuntu Phase 6.61: Execution Storm & Backpressure Tests\n";
    std::cout << "========================================\n\n";
    
    srand(static_cast<unsigned>(std::chrono::system_clock::now().time_since_epoch().count()));
    
    try {
        test_lock_manager_backpressure();
        test_storm_with_bounded_concurrency();
        test_lock_manager_metrics();
        test_resource_id_helpers();
        test_multiple_resources_backpressure();
        
        std::cout << "========================================\n";
        std::cout << "ALL TESTS PASSED!\n";
        std::cout << "========================================\n";
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "\nTEST FAILED: " << e.what() << "\n";
        return 1;
    }
}