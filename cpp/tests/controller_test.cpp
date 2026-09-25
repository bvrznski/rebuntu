// rebuntu::runtime::controller tests (Phase 4.6)
//
// Tests for the runtime control operations interface.

#include <runtime/controller.hpp>
#include <cassert>
#include <iostream>
#include <thread>
#include <chrono>

using namespace rebuntu::runtime::controller;

void test_control_request_factory_functions() {
    std::cout << "Testing ControlRequest factory functions...\n";
    
    // Test make_cancel_request
    auto cancel_req = make_cancel_request("test-exec-1", "user requested");
    assert(cancel_req.id.find("ctrl_test-exec-1_") == 0);
    assert(cancel_req.target_type == ControlTarget::kExecution);
    assert(cancel_req.target_id == "test-exec-1");
    assert(cancel_req.operation == ControlRequest::Operation::kCancel);
    assert(cancel_req.reason.has_value());
    assert(*cancel_req.reason == "user requested");
    
    // Test make_pause_request
    auto pause_req = make_pause_request("test-exec-2", std::chrono::milliseconds(5000));
    assert(pause_req.id.find("ctrl_test-exec-2_") == 0);
    assert(pause_req.target_type == ControlTarget::kExecution);
    assert(pause_req.target_id == "test-exec-2");
    assert(pause_req.operation == ControlRequest::Operation::kPause);
    assert(pause_req.timeout.has_value());
    assert(*pause_req.timeout == std::chrono::milliseconds(5000));
    
    // Test make_resume_request
    auto resume_req = make_resume_request("test-exec-3");
    assert(resume_req.id.find("ctrl_test-exec-3_") == 0);
    assert(resume_req.target_type == ControlTarget::kExecution);
    assert(resume_req.target_id == "test-exec-3");
    assert(resume_req.operation == ControlRequest::Operation::kResume);
    
    std::cout << "  control_request_factories... PASS\n";
}

void test_control_result() {
    std::cout << "Testing ControlResult...\n";
    
    // Test success case
    auto success_result = ControlResult{
        .request_id = "req-1",
        .created_at = std::chrono::system_clock::now(),
        .status = ControlResultStatus::kSuccess,
        .completed_at = std::chrono::system_clock::now()
    };
    assert(success_result.succeeded() == true);
    
    // Test failure case
    auto failed_result = ControlResult{
        .request_id = "req-2",
        .created_at = std::chrono::system_clock::now(),
        .status = ControlResultStatus::kFailed,
        .error_code = "E_TIMEOUT",
        .error_message = "Operation timed out"
    };
    assert(failed_result.succeeded() == false);
    
    // Test not_found case
    auto not_found_result = ControlResult{
        .request_id = "req-3",
        .created_at = std::chrono::system_clock::now(),
        .status = ControlResultStatus::kNotFound
    };
    assert(not_found_result.succeeded() == false);
    
    std::cout << "  control_result... PASS\n";
}

void test_control_state_to_string() {
    std::cout << "Testing to_string functions...\n";
    
    // Test ControlTarget
    assert(to_string(ControlTarget::kExecution) == "execution");
    assert(to_string(ControlTarget::kWorkflow) == "workflow");
    assert(to_string(ControlTarget::kService) == "service");
    assert(to_string(ControlTarget::kProcess) == "process");
    assert(to_string(ControlTarget::kCustom) == "custom");
    
    // Test ControlResultStatus
    assert(to_string(ControlResultStatus::kAccepted) == "accepted");
    assert(to_string(ControlResultStatus::kPending) == "pending");
    assert(to_string(ControlResultStatus::kSuccess) == "success");
    assert(to_string(ControlResultStatus::kFailed) == "failed");
    assert(to_string(ControlResultStatus::kTimedOut) == "timed_out");
    assert(to_string(ControlResultStatus::kNotFound) == "not_found");
    assert(to_string(ControlResultStatus::kUnsupported) == "unsupported");
    assert(to_string(ControlResultStatus::kUnauthorized) == "unauthorized");
    
    std::cout << "  to_string_functions... PASS\n";
}

void test_control_operation_enum() {
    std::cout << "Testing ControlRequest::Operation enum...\n";
    
    // Test all operations
    assert(ControlRequest::Operation::kCancel != ControlRequest::Operation::kPause);
    assert(ControlRequest::Operation::kResume != ControlRequest::Operation::kFreeze);
    assert(ControlRequest::Operation::kTerminate != ControlRequest::Operation::kKill);
    assert(ControlRequest::Operation::kRestart != ControlRequest::Operation::kUnfreeze);
    
    std::cout << "  control_operation_enum... PASS\n";
}

void test_control_observer() {
    std::cout << "Testing ControlObserver...\n";
    
    // Test that we can create a simple observer
    class SimpleObserver : public ControlObserver {
    public:
        int on_started_calls = 0;
        int on_result_updated_calls = 0;
        int on_completed_calls = 0;
        
        void on_control_started(const ControlRequest&) override {
            on_started_calls++;
        }
        
        void on_result_updated(const ControlResult&) override {
            on_result_updated_calls++;
        }
        
        void on_control_completed(const std::string&, const ControlResult&) override {
            on_completed_calls++;
        }
    };
    
    auto observer = std::make_shared<SimpleObserver>();
    assert(observer->on_started_calls == 0);
    assert(observer->on_result_updated_calls == 0);
    assert(observer->on_completed_calls == 0);
    
    std::cout << "  control_observer... PASS\n";
}

void test_controller_builder() {
    std::cout << "Testing ControllerBuilder...\n";
    
    // Test default builder
    auto builder = ControllerBuilder{};
    (void)builder;  // Suppress unused warning
    
    // Test with timeout
    auto builder_with_timeout = ControllerBuilder{}
        .set_default_timeout(std::chrono::milliseconds(10000));
    (void)builder_with_timeout;
    
    std::cout << "  controller_builder... PASS\n";
}

int main() {
    std::cout << "\n=== Phase 4.6: Controller Tests ===\n\n";
    
    test_control_request_factory_functions();
    test_control_result();
    test_control_state_to_string();
    test_control_operation_enum();
    test_control_observer();
    test_controller_builder();
    
    std::cout << "\nAll controller tests passed!\n\n";
    
    return 0;
}