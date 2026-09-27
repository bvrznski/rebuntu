// rebuntu::tests::isolated_provider — Tests for Provider Isolation and Degradation (Task 5.50)
//
// These tests verify that:
//   - Failed adapters produce DEGRADED/UNAVAILABLE observations
//   - Failures don't crash unrelated discovery
//   - Failure evidence is preserved

#include <adapters/isolated_provider.hpp>
#include <system/core/contracts.hpp>
#include <stdexcept>

#include <cassert>
#include <iostream>
#include <chrono>

using namespace rebuntu::adapters;
using namespace rebuntu::core;

// ============================================================================
// Test helper: Adapter that succeeds
// ============================================================================

struct SuccessfulAdapter {
    std::string provider_id() const { return "successful-adapter"; }
    
    struct Result {
        int value{42};
        bool success{true};
    };
    
    Result observe_all() const {
        return Result{};
    }
};

// ============================================================================
// Test helper: Adapter that throws
// ============================================================================

struct FailingAdapter {
    std::string provider_id() const { return "failing-adapter"; }
    
    struct Result {
        int value{-1};
        bool success{false};
    };
    
    Result observe_all() const {
        throw std::runtime_error("Simulated adapter failure");
    }
};

// ============================================================================
// Test helper: Adapter that throws system_error
// ============================================================================

struct SystemErrorAdapter {
    std::string provider_id() const { return "system-error-adapter"; }
    
    struct Result {
        int value{-1};
        bool success{false};
    };
    
    Result observe_all() const {
        throw std::system_error(std::make_error_code(std::errc::permission_denied), "Permission denied");
    }
};

// ============================================================================
// Test helper: Adapter with timeout behavior
// ============================================================================

struct TimeoutAdapter {
    std::string provider_id() const { return "timeout-adapter"; }
    
    struct Result {
        int value{-1};
        bool success{false};
    };
    
    Result observe_all() const {
        throw std::system_error(std::make_error_code(std::errc::timed_out), "Connection timeout");
    }
};

// ============================================================================
// Test helper: Flaky adapter that succeeds after first failure
// ============================================================================

struct FlakyAdapter {
    std::string provider_id() const { return "flaky-adapter"; }
    
    struct Result {
        int value{0};
    };
    
    Result observe_all() const {
        static int call_count = 0;
        ++call_count;
        if (call_count <= 1) {
            throw std::runtime_error("First attempt fails");
        }
        return Result{.value = 123};
    }
};

// ============================================================================
// Test helper: Adapter with void methods
// ============================================================================

struct VoidMethodAdapter {
    std::string provider_id() const { return "void-adapter"; }
    
    struct Result {};
    
    Result observe_all() const {
        return Result{};
    }
    
    bool is_ready() const { return true; }
    bool is_running() const { return false; }
    void cancel() {}
};

// ============================================================================
// Test helpers: Function to dereference unique_ptr
// ============================================================================

template<typename T>
auto& deref_unique(T& ptr) {
    return *ptr;
}

// ============================================================================
// Test: Successful adapter returns success status
// ============================================================================

void test_successful_adapter() {
    auto wrapped = std::make_unique<SuccessfulAdapter>();
    auto isolated = make_isolated_provider(std::move(wrapped));
    
    auto result = deref_unique(isolated).observe_all();
    
    assert(result.status == SemanticStatus::kSuccess);
    assert(result.value.has_value());
    assert(result.failures.empty());
    
    // Access value correctly (result.value is optional<T>)
    const auto& val = *result.value;
    assert(val.value == 42);
    
    std::cout << "[PASS] test_successful_adapter" << std::endl;
}

// ============================================================================
// Test: Failing adapter produces unavailable status
// ============================================================================

void test_failing_adapter() {
    auto wrapped = std::make_unique<FailingAdapter>();
    auto isolated = make_isolated_provider(std::move(wrapped));
    
    auto result = deref_unique(isolated).observe_all();
    
    assert(result.status == SemanticStatus::kUnknown);
    assert(!result.value.has_value());
    assert(!result.failures.empty());
    
    // Verify failure details
    const auto& failure = result.failures.front();
    // provider_id is prefixed with "isolated-" so it will be "isolated-failing-adapter"
    assert(failure.provider_id.find("failing-adapter") != std::string::npos);
    assert(failure.category == ProviderFailure::Category::kSystemError);
    assert(failure.description.find("Runtime error") != std::string::npos);
    
    std::cout << "[PASS] test_failing_adapter" << std::endl;
}

// ============================================================================
// Test: System error produces appropriate category
// ============================================================================

void test_system_error_category() {
    auto wrapped = std::make_unique<SystemErrorAdapter>();
    auto isolated = make_isolated_provider(std::move(wrapped));
    
    auto result = deref_unique(isolated).observe_all();
    
    assert(result.status == SemanticStatus::kUnknown);
    
    // Permission denied should be categorized as permission
    const auto& failure = result.failures.front();
    assert(failure.category == ProviderFailure::Category::kPermission);
    
    std::cout << "[PASS] test_system_error_category" << std::endl;
}

// ============================================================================
// Test: Timeout produces appropriate category
// ============================================================================

void test_timeout_category() {
    auto wrapped = std::make_unique<TimeoutAdapter>();
    auto isolated = make_isolated_provider(std::move(wrapped));
    
    auto result = deref_unique(isolated).observe_all();
    
    assert(result.status == SemanticStatus::kUnknown);
    
    // Timeout should be categorized as timeout
    const auto& failure = result.failures.front();
    assert(failure.category == ProviderFailure::Category::kTimeout);
    
    std::cout << "[PASS] test_timeout_category" << std::endl;
}

// ============================================================================
// Test: Provider ID is preserved correctly
// ============================================================================

void test_provider_id() {
    auto wrapped = std::make_unique<SuccessfulAdapter>();
    auto isolated = make_isolated_provider(std::move(wrapped), "custom-id");
    
    assert(deref_unique(isolated).provider_id() == "custom-id");
    
    std::cout << "[PASS] test_provider_id" << std::endl;
}

// ============================================================================
// Test: Multiple failures are captured
// ============================================================================

void test_multiple_failures() {
    // This tests that we can chain failures from multiple operations
    
    struct MultiFailingAdapter {
        std::string provider_id() const { return "multi-fail"; }
        
        struct Result {
            int value{-1};
        };
        
        Result observe_all() const {
            throw std::runtime_error("First error");
        }
    };
    
    auto wrapped = std::make_unique<MultiFailingAdapter>();
    auto isolated = make_isolated_provider(std::move(wrapped));
    
    // Call multiple times to verify each call is independent
    for (int i = 0; i < 3; ++i) {
        auto result = deref_unique(isolated).observe_all();
        assert(result.status == SemanticStatus::kUnknown);
        assert(!result.failures.empty());
    }
    
    std::cout << "[PASS] test_multiple_failures" << std::endl;
}

// ============================================================================
// Test: Exception safety - adapter still accessible after failure
// ============================================================================

void test_adapter_accessible_after_failure() {
    auto wrapped = std::make_unique<FlakyAdapter>();
    auto isolated = make_isolated_provider(std::move(wrapped));
    
    // First call should fail
    auto result1 = deref_unique(isolated).observe_all();
    assert(result1.status == SemanticStatus::kUnknown);
    
    // Second call should succeed (adapter is still usable)
    auto result2 = deref_unique(isolated).observe_all();
    assert(result2.status == SemanticStatus::kSuccess);
    assert(result2.value.has_value());
    assert((*result2.value).value == 123);
    
    std::cout << "[PASS] test_adapter_accessible_after_failure" << std::endl;
}

// ============================================================================
// Test: Null wrapped adapter handling
// ============================================================================

void test_null_wrapped_adapter() {
    auto isolated = make_isolated_provider<SuccessfulAdapter>(nullptr, "null-adapter");
    
    auto result = deref_unique(isolated).observe_all();
    
    assert(result.status == SemanticStatus::kUnknown);
    assert(!result.value.has_value());
    
    // Should have a connection failure
    const auto& failure = result.failures.front();
    assert(failure.category == ProviderFailure::Category::kConnection);
    
    std::cout << "[PASS] test_null_wrapped_adapter" << std::endl;
}

// ============================================================================
// Test: to_string for ProviderFailure
// ============================================================================

void test_provider_failure_to_string() {
    auto now = std::chrono::system_clock::now();
    ProviderFailure failure{
        .provider_id = "test-failure",
        .failure_time = now,
        .category = ProviderFailure::Category::kTimeout,
        .description = "Test timeout",
    };
    
    std::string s = to_string(failure);
    assert(s.find("test-failure") != std::string::npos);
    assert(s.find("timeout") != std::string::npos);
    
    std::cout << "[PASS] test_provider_failure_to_string: " << s << std::endl;
}

// ============================================================================
// Test: DegradedObservation factory methods
// ============================================================================

void test_degraded_observation_factories() {
    // Success
    auto success = DegradedObservation<int>::success(42);
    assert(success.status == SemanticStatus::kSuccess);
    assert(success.value.has_value());
    assert(*success.value == 42);
    
    // Degraded (work done but with issues)
    std::vector<ProviderFailure> failures;
    auto degraded = DegradedObservation<int>::degraded(
        10, 
        std::move(failures));
    assert(degraded.status == SemanticStatus::kCompleted);
    assert(degraded.value.has_value());
    
    // Unavailable
    auto unavailable = DegradedObservation<int>::unavailable({});
    assert(unavailable.status == SemanticStatus::kUnknown);
    assert(!unavailable.value.has_value());
    
    // Cancelled
    auto cancelled = DegradedObservation<int>::cancelled("Operation cancelled");
    assert(cancelled.status == SemanticStatus::kCancelled);
    
    std::cout << "[PASS] test_degraded_observation_factories" << std::endl;
}

// ============================================================================
// Test: Has value helper
// ============================================================================

void test_has_value() {
    auto success = DegradedObservation<int>::success(42);
    assert(success.has_value());
    
    auto unavailable = DegradedObservation<int>::unavailable({});
    assert(!unavailable.has_value());
    
    std::cout << "[PASS] test_has_value" << std::endl;
}

// ============================================================================
// Test: Void method handling
// ============================================================================

void test_void_method_handling() {
    // Void method handling is not implemented in this version
    // Only observe_all() with exception handling is provided
    // This test demonstrates that the basic functionality works
    
    auto wrapped = std::make_unique<VoidMethodAdapter>();
    auto isolated = make_isolated_provider(std::move(wrapped));
    
    // Test that we can access the original adapter
    assert(deref_unique(isolated).get_original() != nullptr);
    
    std::cout << "[PASS] test_void_method_handling" << std::endl;
}

// ============================================================================
// Test: get_original method
// ============================================================================

void test_get_original() {
    auto wrapped = std::make_unique<SuccessfulAdapter>();
    auto isolated = make_isolated_provider(std::move(wrapped));
    
    // Verify we can access the original adapter
    auto* original = deref_unique(isolated).get_original();
    assert(original != nullptr);
    assert(original->provider_id() == "successful-adapter");
    
    std::cout << "[PASS] test_get_original" << std::endl;
}

// ============================================================================
// Test: Multiple failures across different operations
// ============================================================================

void test_isolation_across_operations() {
    auto wrapped = std::make_unique<FailingAdapter>();
    auto isolated = make_isolated_provider(std::move(wrapped));
    
    // Call multiple times - each should fail independently
    for (int i = 0; i < 5; ++i) {
        auto result = deref_unique(isolated).observe_all();
        
        // Each call should produce failure, not crash
        assert(result.status == SemanticStatus::kUnknown);
        assert(!result.failures.empty());
    }
    
    std::cout << "[PASS] test_isolation_across_operations" << std::endl;
}

// ============================================================================
// Test: Failure evidence is preserved
// ============================================================================

void test_failure_evidence_preserved() {
    auto wrapped = std::make_unique<FailingAdapter>();
    auto isolated = make_isolated_provider(std::move(wrapped));
    
    auto result = deref_unique(isolated).observe_all();
    
    // Verify the failure contains useful information
    assert(!result.failures.empty());
    const auto& failure = result.failures.front();
    
    // Provider ID should be set
    assert(!failure.provider_id.empty());
    
    // Category should be known (system error in this case)
    assert(failure.category != ProviderFailure::Category::kUnknown);
    
    // Description should not be empty
    assert(!failure.description.empty());
    
    std::cout << "[PASS] test_failure_evidence_preserved" << std::endl;
}

// ============================================================================
// Main test runner
// ============================================================================

int main() {
    std::cout << "Testing IsolatedProvider (Task 5.50)" << std::endl;
    
    test_successful_adapter();
    test_failing_adapter();
    test_system_error_category();
    test_timeout_category();
    test_provider_id();
    test_multiple_failures();
    test_adapter_accessible_after_failure();
    test_null_wrapped_adapter();
    test_provider_failure_to_string();
    test_degraded_observation_factories();
    test_has_value();
    test_void_method_handling();
    test_get_original();
    test_isolation_across_operations();
    test_failure_evidence_preserved();
    
    std::cout << "\nAll tests passed!" << std::endl;
    return 0;
}
