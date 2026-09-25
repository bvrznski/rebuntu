// Rebuntu - Phase 4.19 Shutdown & Cancellation Tests
//
// Unit tests for shutdown coordinator, cancellation propagation,
// and bounded drain behavior.

#include <runtime/shutdown/coordinator.hpp>
#include <runtime/cancellation/token.hpp>
#include <system/core/results.hpp>
#include <cassert>
#include <iostream>
#include <thread>
#include <chrono>

using namespace rebuntu;
using namespace rebuntu::runtime;

void test_coordinator_creation() {
    ShutdownCoordinator coordinator;
    assert(coordinator.component_count() == 0);
    std::cout << "[PASS] Coordinator creation\n";
}

void test_component_registration() {
    ShutdownCoordinator coordinator;
    
    bool shutdown_called = false;
    bool force_shutdown_called = false;
    
    coordinator.register_component(
        "test_component",
        [&]() { shutdown_called = true; },
        [&]() { force_shutdown_called = true; }
    );
    
    assert(coordinator.component_count() == 1);
    assert(!shutdown_called);
    std::cout << "[PASS] Component registration\n";
}

void test_shutdown_all_with_default_policy() {
    ShutdownCoordinator coordinator;
    
    bool component_shut_down = false;
    coordinator.register_component(
        "test",
        [&]() { 
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            component_shut_down = true; 
        }
    );
    
    auto result = coordinator.shutdown_all();
    
    assert(result.status == core::SemanticStatus::kSuccess);
    assert(component_shut_down || result.force_terminated > 0 || result.graceful_completions > 0);
    std::cout << "[PASS] Shutdown all with default policy\n";
}

void test_cancellation_token_propagation() {
    CancellationToken token;
    
    bool callback_called = false;
    [[maybe_unused]] int callback_id = token.register_callback([&]() { callback_called = true; });
    
    assert(!token.is_cancelled());
    assert(!callback_called);
    
    token.request_cancel("test reason");
    
    assert(token.is_cancelled());
    assert(callback_called);
    std::cout << "[PASS] Cancellation token propagation\n";
}

void test_cancellation_reason() {
    CancellationToken token;
    token.request_cancel("shutdown initiated");
    
    auto reason = token.cancellation_reason();
    assert(reason.has_value());
    assert(*reason == "shutdown initiated");
    std::cout << "[PASS] Cancellation reason\n";
}

void test_shutdown_context_initialization() {
    shutdown::ShutdownContext ctx;
    assert(ctx.phase == shutdown::ShutdownPhase::kIdle);
    assert(ctx.policy.total_timeout.count() > 0);
    assert(ctx.cancellation_token != nullptr);
    std::cout << "[PASS] Shutdown context initialization\n";
}

int main() {
    std::cout << "Phase 4.19 Shutdown & Cancellation Tests\n";
    std::cout << "==========================================\n\n";
    
    test_coordinator_creation();
    test_component_registration();
    test_shutdown_all_with_default_policy();
    test_cancellation_token_propagation();
    test_cancellation_reason();
    test_shutdown_context_initialization();
    
    std::cout << "\nAll Phase 4.19 tests passed!\n";
    return 0;
}