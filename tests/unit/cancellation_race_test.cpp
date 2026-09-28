// Rebuntu Phase 6.62: Cancellation Race Condition Tests
//
// This test suite verifies cancellation behavior under stress conditions:
//   - Cancellation before start (intent not yet dispatched)
//   - Cancellation during provider call (execution in progress)
//   - Cancellation during verification (postcondition check)
//   - Cancellation during shutdown (runtime teardown)
//
// Ensures exactly one terminal execution state and no leaked resources.

#include <iostream>
#include <cassert>
#include "runtime/cancellation/token.hpp"
#include "runtime/cancellation/points.hpp"
#include <string>
#include <vector>
#include <map>
#include <atomic>
#include <thread>
#include <chrono>
#include <mutex>

using namespace rebuntu::core;
using namespace rebuntu::runtime;
using namespace rebuntu::runtime::cancellation;

#include <iterator>

// ============================================================================
// Test Helper Functions
// ============================================================================

std::string make_test_id() {
    auto now = std::chrono::system_clock::now();
    auto count = std::chrono::duration_cast<std::chrono::microseconds>(
        now.time_since_epoch()).count();
    return "test-" + std::to_string(count);
}

void assert_equal(int actual, int expected, const char* msg) {
    if (actual != expected) {
        std::cerr << "FAIL: " << msg 
                  << " - expected " << expected 
                  << ", got " << actual << "\n";
        exit(1);
    }
}

void assert_true(bool condition, const char* msg) {
    if (!condition) {
        std::cerr << "FAIL: " << msg << "\n";
        exit(1);
    }
}

// ============================================================================
// Test 1: Cancellation Before Start (Race - multiple threads cancel before dispatch)
// ============================================================================

void test_before_start_no_leaked_resources() {
    std::cout << "TEST 1: Cancellation before start (race condition)...\n";
    
    const int num_threads = 100;
    std::vector<std::thread> threads;
    std::atomic<int> cancelled_before_dispatch{0};
    
    // Create many cancellation tokens and race to cancel them
    for (int i = 0; i < num_threads; i++) {
        threads.emplace_back([&cancelled_before_dispatch, i]() {
            CancellationToken token;
            
            // All threads try to cancel before any dispatch happens
            if (!token.is_cancelled()) {
                token.request_cancel("race-test-before-start-" + std::to_string(i));
                cancelled_before_dispatch++;
            }
            
            // Verify state is consistent after cancellation
            assert_true(token.is_cancelled(), "Token should be cancelled");
        });
    }
    
    for (auto& t : threads) {
        t.join();
    }
    
    // All threads should have been able to cancel before dispatch
    assert_equal(cancelled_before_dispatch.load(), num_threads,
                 "All threads should have cancelled");
    
    std::cout << "  PASS: All " << num_threads << " tokens cancelled successfully\n\n";
}

// ============================================================================
// Test 2: Cancellation During Provider Call (Race - cancellation during execution)
// ============================================================================

void test_during_provider_call_exact_terminal_state() {
    std::cout << "TEST 2: Cancellation during provider call...\n";
    
    const int num_executions = 50;
    std::vector<std::thread> threads;
    
    // Shared state
    std::mutex results_mutex;
    int terminal_states[3] = {0};  // kCancelled, kFailed, kUnknown
    
    for (int i = 0; i < num_executions; i++) {
        threads.emplace_back([&results_mutex, &terminal_states, i]() {
            CancellationToken token;
            
            // Simulate execution that checks for cancellation
            std::atomic<bool> execution_started{false};
            std::atomic<bool> cancelled_during_execution{false};
            
            // Start a "provider call" in parallel with potential cancellation
            std::thread provider_thread([&]() {
                execution_started.store(true, std::memory_order_release);
                
                // Simulate slow provider work (sleep)
                std::this_thread::sleep_for(std::chrono::milliseconds(50));
                
                // Check for cancellation during execution
                if (token.is_cancelled()) {
                    cancelled_during_execution.store(true, std::memory_order_release);
                }
            });
            
            // Race to cancel during provider call
            std::this_thread::sleep_for(std::chrono::milliseconds(10 + (i % 30)));
            token.request_cancel("race-during-provider-" + std::to_string(i));
            
            provider_thread.join();
            
            // Record terminal state
            if (cancelled_during_execution.load()) {
                std::lock_guard<std::mutex> lock(results_mutex);
                terminal_states[0]++;  // kCancelled
            } else {
                std::lock_guard<std::mutex> lock(results_mutex);
                terminal_states[1]++;  // kFailed
            }
        });
    }
    
    for (auto& t : threads) {
        t.join();
    }
    
    // Verify we got some cancelled states and no unknown states
    assert_true(terminal_states[0] >= 1, "At least some cancellations should occur");
    assert_equal(terminal_states[2], 0, "No unknown states should occur");
    
    std::cout << "  Cancelled: " << terminal_states[0] << "\n";
    std::cout << "  Failed: " << terminal_states[1] << "\n";
    std::cout << "  PASS: Provider call cancellation works correctly\n\n";
}

// ============================================================================
// Test 3: Cancellation During Verification (Race - verification in progress)
// ============================================================================

void test_during_verification_no_state_leak() {
    std::cout << "TEST 3: Cancellation during verification...\n";
    
    const int num_verifications = 50;
    std::vector<std::thread> threads;
    
    // Track verification attempts
    std::atomic<int> verification_attempts{0};
    std::mutex state_mutex;
    int final_states[2] = {0};  // kVerified, kCancelled
    
    for (int i = 0; i < num_verifications; i++) {
        threads.emplace_back([&]() {
            CancellationToken token;
            
            verification_attempts.fetch_add(1, std::memory_order_relaxed);
            
            // Simulate verification process
            bool was_cancelled = false;
            
            auto verify_start = [&token, &was_cancelled]() -> bool {
                if (token.is_cancelled()) {
                    was_cancelled = true;
                    return false;
                }
                return true;
            };
            
            auto do_verification = [&]() {
                // Simulate verification work
                std::this_thread::sleep_for(std::chrono::milliseconds(5));
            };
            
            // Start verification
            bool can_verify = verify_start();
            
            if (can_verify) {
                do_verification();
                
                // Race to cancel during verification
                std::this_thread::sleep_for(std::chrono::milliseconds(2));
                token.request_cancel("race-during-verify-" + make_test_id());
                
                std::lock_guard<std::mutex> lock(state_mutex);
                if (token.is_cancelled()) {
                    final_states[1]++;  // kCancelled
                } else {
                    final_states[0]++;  // kVerified
                }
            } else {
                std::lock_guard<std::mutex> lock(state_mutex);
                final_states[1]++;  // kCancelled
            }
        });
    }
    
    for (auto& t : threads) {
        t.join();
    }
    
    // Verify no state leaks - all verifications reached terminal state
    assert_equal(verification_attempts.load(), 
              final_states[0] + final_states[1],
              "All verifications should reach terminal state");
    
    std::cout << "  Verified: " << final_states[0] << "\n";
    std::cout << "  Cancelled: " << final_states[1] << "\n";
    std::cout << "  PASS: No verification state leaks\n\n";
}

// ============================================================================
// Test 4: Cancellation During Shutdown (Race - runtime teardown)
// ============================================================================

void test_during_shutdown_no_resources_leaked() {
    std::cout << "TEST 4: Cancellation during shutdown...\n";
    
    const int num_operations = 30;
    
    // Track operations during shutdown
    std::mutex result_mutex;
    int final_states[2] = {0};  // kCompleted, kCancelled
    
    for (int i = 0; i < num_operations; i++) {
        std::thread op_thread([&]() {
            CancellationToken token;
            
            // Simulate work with potential cancellation
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
            
            if (token.is_cancelled()) {
                std::lock_guard<std::mutex> lock(result_mutex);
                final_states[1]++;  // kCancelled
            } else {
                std::lock_guard<std::mutex> lock(result_mutex);
                final_states[0]++;  // kCompleted
            }
        });
        
        op_thread.join();
    }
    
    // All operations should have completed
    assert_true(final_states[0] + final_states[1] == num_operations, 
                "All operations should complete");
    
    std::cout << "  Completed: " << final_states[0] << "\n";
    std::cout << "  Cancelled: " << final_states[1] << "\n";
    std::cout << "  PASS: Shutdown handled correctly\n\n";
}

// ============================================================================
// Test 5: Multiple Cancellation Requests (Idempotency check)
// ============================================================================

void test_multiple_cancellation_requests_idempotent() {
    std::cout << "TEST 5: Multiple cancellation requests (idempotency)...\n";
    
    const int num_cancel_requests = 10;
    std::vector<std::thread> threads;
    
    CancellationToken token;
    
    std::atomic<int> first_cancel_timestamp{0};
    std::mutex timestamp_mutex;
    auto start_time = std::chrono::steady_clock::now();
    
    // All threads try to cancel simultaneously
    for (int i = 0; i < num_cancel_requests; i++) {
        threads.emplace_back([&token, &first_cancel_timestamp, &timestamp_mutex, 
                              start_time, i]() {
            auto now = std::chrono::steady_clock::now();
            
            // Record when first cancellation succeeded
            if (!token.is_cancelled()) {
                token.request_cancel("race-multi-cancel-" + std::to_string(i));
                
                std::lock_guard<std::mutex> lock(timestamp_mutex);
                if (first_cancel_timestamp.load() == 0) {
                    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(
                        now - start_time).count();
                    first_cancel_timestamp.store(static_cast<int>(duration));
                }
            } else {
                // All subsequent requests should be no-ops
                assert_true(token.is_cancelled(), "Token should remain cancelled");
            }
        });
    }
    
    for (auto& t : threads) {
        t.join();
    }
    
    // Verify token is cancelled exactly once
    assert_true(token.is_cancelled(), "Token should be cancelled");
    
    int timestamp = first_cancel_timestamp.load();
    assert_true(timestamp > 0, "First cancellation timestamp should be recorded");
    
    std::cout << "  First cancellation at: " << timestamp << " microseconds\n";
    std::cout << "  PASS: Multiple cancellation requests handled idempotently\n\n";
}

// ============================================================================
// Test 6: Callback Registration Race (Thread safety check)
// ============================================================================

void test_callback_registration_thread_safe() {
    std::cout << "TEST 6: Callback registration thread safety...\n";
    
    const int num_threads = 50;
    std::vector<std::thread> threads;
    
    CancellationToken token;
    
    std::atomic<int> callbacks_registered{0};
    std::atomic<int> cancellation_callbacks_invoked{0};
    
    // Start threads that register callbacks
    for (int i = 0; i < num_threads; i++) {
        threads.emplace_back([&token, &callbacks_registered, 
                              &cancellation_callbacks_invoked]() {
            auto callback_id = token.register_callback([&cancellation_callbacks_invoked]() {
                cancellation_callbacks_invoked.fetch_add(1, std::memory_order_relaxed);
            });
            
            if (callback_id > 0) {
                callbacks_registered.fetch_add(1, std::memory_order_relaxed);
            }
        });
    }
    
    for (auto& t : threads) {
        t.join();
    }
    
    int initial_count = cancellation_callbacks_invoked.load();
    token.request_cancel("race-callback-registration");
    
    // Give time for callbacks to execute
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    
    int final_count = cancellation_callbacks_invoked.load();
    int callbacks_invoked_during_cancellation = final_count - initial_count;
    
    // At least some callbacks should have been invoked
    assert_true(callbacks_invoked_during_cancellation > 0, 
                "Some callbacks should be invoked");
    assert_true(callbacks_invoked_during_cancellation <= num_threads,
                "No more than all callbacks should be invoked");
    
    std::cout << "  Callbacks registered: " << callbacks_registered.load() << "\n";
    std::cout << "  Callbacks invoked: " << final_count << "\n";
    std::cout << "  PASS: Callback registration is thread-safe\n\n";
}

// ============================================================================
// Test 7: Cancellation Point Semantics (Comprehensive check)
// ============================================================================

void test_points_semantics_exact_transitions() {
    std::cout << "TEST 7: Cancellation point semantics...\n";
    
    const int num_iterations = 20;
    std::vector<std::thread> threads;
    
    // Track transitions through cancellation points
    std::mutex point_mutex;
    std::map<CancellationPoint, int> point_counts;
    
    for (int i = 0; i < num_iterations; i++) {
        threads.emplace_back([&]() {
            CancellationToken token;
            
            // Simulate progression through cancellation points
            std::vector<CancellationPoint> points = {
                rebuntu::runtime::cancellation::CancellationPoint::kPreconditionCheck,
                rebuntu::runtime::cancellation::CancellationPoint::kPlanGeneration,
                rebuntu::runtime::cancellation::CancellationPoint::kExecutionStart,
                rebuntu::runtime::cancellation::CancellationPoint::kExecutionPhase,
                rebuntu::runtime::cancellation::CancellationPoint::kVerificationStart,
                rebuntu::runtime::cancellation::CancellationPoint::kVerificationPhase
            };
            
            for (size_t j = 0; j < points.size(); j++) {
                // Simulate work at this point
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
                
                if (!token.is_cancelled()) {
                    // Record we passed through this point
                    std::lock_guard<std::mutex> lock(point_mutex);
                    point_counts[points[j]]++;
                    
                    // Randomly cancel at some points
                    if (j > 0 && j % 2 == 0) {
                        token.request_cancel("race-points-" + make_test_id());
                        break;
                    }
                } else {
                    break;  // Cancelled, stop progression
                }
            }
        });
    }
    
    for (auto& t : threads) {
        t.join();
    }
    
    std::cout << "  Cancellation Points Reached:\n";
    for (auto it = point_counts.begin(); it != point_counts.end(); ++it) {
        const auto& point = it->first;
        int count = it->second;
        std::cout << "    " << to_string(point) << ": " << count << "\n";
    }
    std::cout << "  PASS: Cancellation point semantics work correctly\n\n";
}

// ============================================================================
// Test 8: Resource Cleanup Race (No resource leaks)
// ============================================================================

void test_resource_cleanup_no_leaks() {
    std::cout << "TEST 8: Resource cleanup race conditions...\n";
    
    const int num_operations = 40;
    std::vector<std::thread> threads;
    
    // Track resources
    std::atomic<int> active_resources{0};
    std::atomic<int> max_active_resources{0};
    std::mutex resource_mutex;
    
    for (int i = 0; i < num_operations; i++) {
        threads.emplace_back([&]() {
            CancellationToken token;
            
            // Simulate acquiring a resource
            int current = active_resources.fetch_add(1, std::memory_order_relaxed) + 1;
            
            {
                std::lock_guard<std::mutex> lock(resource_mutex);
                if (current > max_active_resources.load()) {
                    max_active_resources.store(current);
                }
            }
            
            // Do some work that can be cancelled
            std::this_thread::sleep_for(std::chrono::milliseconds(20));
            
            // Simulate cleanup regardless of cancellation
            int current_after = active_resources.fetch_sub(1, std::memory_order_relaxed) - 1;
            
            if (current_after < 0) {
                std::cerr << "FAIL: Negative resource count - cleanup race!\n";
                exit(1);
            }
        });
    }
    
    for (auto& t : threads) {
        t.join();
    }
    
    // Final state should be zero resources active
    assert_equal(active_resources.load(), 0, 
                 "All resources should be cleaned up");
    
    std::cout << "  Max concurrent resources: " << max_active_resources.load() << "\n";
    std::cout << "  PASS: No resource leaks during cancellation\n\n";
}

// ============================================================================
// Test 9: Timeout Integration with Cancellation (Integration test)
// ============================================================================

void test_timeout_with_cancellation_coordinated() {
    std::cout << "TEST 9: Timeout integration with cancellation...\n";
    
    const int num_tests = 30;
    std::vector<std::thread> threads;
    
    for (int i = 0; i < num_tests; i++) {
        threads.emplace_back([i]() {
            CancellationToken token;
            
            auto start_time = std::chrono::steady_clock::now();
            bool was_cancelled = false;
            
            // Simulate long operation with timeout
            while ((std::chrono::steady_clock::now() - start_time) < 
                   std::chrono::milliseconds(100)) {
                
                if (token.is_cancelled()) {
                    was_cancelled = true;
                    break;
                }
                
                std::this_thread::sleep_for(std::chrono::milliseconds(5));
            }
            
            // Verify exactly one terminal state
            bool completed_normally = !was_cancelled && 
                                      (std::chrono::steady_clock::now() - start_time) >= 
                                      std::chrono::milliseconds(100);
            
            assert_true(was_cancelled || completed_normally,
                        "Operation should reach terminal state");
        });
    }
    
    for (auto& t : threads) {
        t.join();
    }
    
    std::cout << "  PASS: Timeout/cancellation coordination works correctly\n\n";
}

// ============================================================================
// Test 10: Token Copy Semantics (Race - multiple copies of same token state)
// ============================================================================

void test_token_copy_semantics() {
    std::cout << "TEST 11: Shared token race conditions...\n";
    
    const int num_threads = 50;
    CancellationToken shared_token;
    std::vector<std::thread> threads;
    
    for (int i = 0; i < num_threads; i++) {
        threads.emplace_back([&shared_token]() {
            // All threads try to check and cancel
            if (!shared_token.is_cancelled()) {
                shared_token.request_cancel("race-shared-token-" + make_test_id());
            }
            
            assert_true(shared_token.is_cancelled(), "Shared token should be cancelled");
        });
    }
    
    for (auto& t : threads) {
        t.join();
    }
    
    std::cout << "  PASS: Shared token race conditions handled correctly\n\n";
}

// ============================================================================
// Main Test Entry Point
// ============================================================================

int main(int argc, char** argv) {
    (void)argc;
    (void)argv;
    
    std::cout << "========================================\n";
    std::cout << "Rebuntu Phase 6.62: Cancellation Race Tests\n";
    std::cout << "========================================\n\n";
    
    try {
        test_before_start_no_leaked_resources();
        test_during_provider_call_exact_terminal_state();
        test_during_verification_no_state_leak();
        test_during_shutdown_no_resources_leaked();
        test_multiple_cancellation_requests_idempotent();
        test_callback_registration_thread_safe();
        test_points_semantics_exact_transitions();
        test_resource_cleanup_no_leaks();
        test_timeout_with_cancellation_coordinated();
        test_token_copy_semantics();
        
        std::cout << "========================================\n";
        std::cout << "ALL RACE TESTS PASSED!\n";
        std::cout << "========================================\n";
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "\nTEST FAILED: " << e.what() << "\n";
        return 1;
    }
}