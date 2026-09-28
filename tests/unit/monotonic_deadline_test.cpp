// Rebuntu Phase 6.30 — Monotonic Deadline Unit Tests
//
// Tests monotonic deadline types and propagation

#include <cassert>
#include <chrono>
#include <iostream>
#include <thread>

#include <system/core/contracts.hpp>
#include <core/time/monotonic/types.hpp>

void test_monotonic_deadline_creation() {
    auto deadline = rebuntu::core::time::MonotonicDeadline::from_duration(std::chrono::milliseconds(100));
    
    assert(!deadline.is_expired());
}

void test_monotonic_deadline_remaining() {
    auto deadline = rebuntu::core::time::MonotonicDeadline::from_duration(std::chrono::milliseconds(200));
    
    auto remaining = deadline.remaining();
    assert(remaining.has_value());
    
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(
        *remaining).count();
    assert(elapsed_ms >= 100);
}

void test_monotonic_deadline_expiration() {
    auto deadline = rebuntu::core::time::MonotonicDeadline::from_duration(std::chrono::milliseconds(50));
    
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    
    assert(deadline.is_expired());
}

void test_monotonic_context_no_deadline() {
    auto ctx = rebuntu::core::time::default_monotonic_context;
    
    assert(!ctx.has_deadline());
    assert(!ctx.is_expired());
}

void test_monotonic_context_with_deadline() {
    auto ctx = rebuntu::core::time::default_monotonic_context.with_deadline(
        rebuntu::core::time::MonotonicDeadline::from_duration(std::chrono::seconds(10)));
    
    assert(ctx.has_deadline());
    assert(!ctx.is_expired());
}

void test_monotonic_context_child_shortens() {
    auto parent = rebuntu::core::time::default_monotonic_context.with_deadline(
        rebuntu::core::time::MonotonicDeadline::from_duration(std::chrono::minutes(5)));
    
    auto child = parent.with_deadline(
        rebuntu::core::time::MonotonicDeadline::from_duration(std::chrono::seconds(30)));
    
    assert(child.has_deadline());
}

void test_monotonic_context_get_effective_timeout() {
    auto ctx = rebuntu::core::time::default_monotonic_context;
    
    auto timeout = ctx.get_effective_timeout(rebuntu::core::time::MonotonicTimeout{std::chrono::seconds(30)});
    assert(timeout.max_duration == std::chrono::seconds(30));
}

void test_deadline_status_strings() {
    using namespace rebuntu::core::time;
    
    assert(to_string(DeadlineStatus::kNotSet) == "not_set");
    assert(to_string(DeadlineStatus::kActive) == "active");
    assert(to_string(DeadlineStatus::kExpired) == "expired");
    assert(to_string(DeadlineStatus::kExhausted) == "exhausted");
}

void test_monotonic_result_success() {
    using namespace rebuntu::core;
    
    rebuntu::core::time::MonotonicResult<int> result;
    result.status = SemanticStatus::kSuccess;
    
    assert(result.is_success());
    assert(!result.is_timeout());
}

void test_monotonic_result_timeout() {
    using namespace rebuntu::core;
    
    rebuntu::core::time::MonotonicResult<int> result;
    result.status = SemanticStatus::kFailure;
    result.deadline_status = rebuntu::core::time::DeadlineStatus::kExpired;
    
    assert(!result.is_success());
    assert(result.is_timeout());
}

int main() {
    std::cout << "Running monotonic deadline unit tests...\n";
    
    test_monotonic_deadline_creation();
    std::cout << "  [PASS] MonotonicDeadline creation\n";
    
    test_monotonic_deadline_remaining();
    std::cout << "  [PASS] MonotonicDeadline remaining time\n";
    
    test_monotonic_deadline_expiration();
    std::cout << "  [PASS] MonotonicDeadline expiration\n";
    
    test_monotonic_context_no_deadline();
    std::cout << "  [PASS] MonotonicContext no deadline\n";
    
    test_monotonic_context_with_deadline();
    std::cout << "  [PASS] MonotonicContext with deadline\n";
    
    test_monotonic_context_child_shortens();
    std::cout << "  [PASS] MonotonicContext child shortens deadline\n";
    
    test_monotonic_context_get_effective_timeout();
    std::cout << "  [PASS] MonotonicContext effective timeout\n";
    
    test_deadline_status_strings();
    std::cout << "  [PASS] DeadlineStatus string conversion\n";
    
    test_monotonic_result_success();
    std::cout << "  [PASS] MonotonicResult success\n";
    
    test_monotonic_result_timeout();
    std::cout << "  [PASS] MonotonicResult timeout\n";
    
    std::cout << "\nAll monotonic deadline tests passed!\n";
    return 0;
}