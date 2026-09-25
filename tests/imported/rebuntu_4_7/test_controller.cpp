// Unit tests for rebuntu::runtime::controller (Phase 4.6)
// Minimal, dependency-free assertion harness.

#include <runtime/controller.hpp>

#include <iostream>
#include <memory>

namespace {
int g_failures = 0;
#define CHECK(cond)                                                              \
    do {                                                                         \
        if (!(cond)) {                                                           \
            std::cerr << "CHECK failed: " << #cond << " (line " << __LINE__      \
                      << ")\n";                                                  \
            ++g_failures;                                                        \
        }                                                                        \
    } while (0)
}  // namespace

int main() {
    using rebuntu::runtime::controller::ControlOperation;
    using rebuntu::runtime::controller::TargetType;
    using rebuntu::runtime::controller::ControlRequest;
    using rebuntu::runtime::controller::ControlResult;
    using rebuntu::runtime::controller::Controller;
    using rebuntu::runtime::controller::ExecutionController;
    using rebuntu::runtime::controller::EngineController;
    using rebuntu::runtime::controller::make_default_controller;
    
    // Test ControlOperation to_string
    {
        CHECK(rebuntu::runtime::controller::to_string(ControlOperation::kCancel) == "cancel");
        CHECK(rebuntu::runtime::controller::to_string(ControlOperation::kPause) == "pause");
        CHECK(rebuntu::runtime::controller::to_string(ControlOperation::kResume) == "resume");
        CHECK(rebuntu::runtime::controller::to_string(ControlOperation::kFreeze) == "freeze");
        CHECK(rebuntu::runtime::controller::to_string(ControlOperation::kUnfreeze) == "unfreeze");
        CHECK(rebuntu::runtime::controller::to_string(ControlOperation::kStop) == "stop");
        CHECK(rebuntu::runtime::controller::to_string(ControlOperation::kTerminate) == "terminate");
    }
    
    // Test TargetType to_string
    {
        CHECK(rebuntu::runtime::controller::to_string(TargetType::kExecution) == "execution");
        CHECK(rebuntu::runtime::controller::to_string(TargetType::kRunner) == "runner");
        CHECK(rebuntu::runtime::controller::to_string(TargetType::kWorkflow) == "workflow");
        CHECK(rebuntu::runtime::controller::to_string(TargetType::kEngine) == "engine");
    }
    
    // Test ControlRequest static factories
    {
        auto req1 = ControlRequest::cancel_execution("exec-123", "test reason");
        CHECK(req1.operation == ControlOperation::kCancel);
        CHECK(req1.target_type == TargetType::kExecution);
        CHECK(req1.target_id == "exec-123");
        CHECK(req1.reason.has_value());
        CHECK(*req1.reason == "test reason");
        
        auto req2 = ControlRequest::pause_runner("runner-456", "paused for maintenance");
        CHECK(req2.operation == ControlOperation::kPause);
        CHECK(req2.target_type == TargetType::kRunner);
        CHECK(req2.target_id == "runner-456");
        
        auto req3 = ControlRequest::resume_runner("runner-789");
        CHECK(req3.operation == ControlOperation::kResume);
    }
    
    // Test Controller base class
    {
        Controller ctrl;
        auto req = ControlRequest::cancel_execution("exec-123", "test");
        auto result = ctrl.submit_control(req);
        
        CHECK(result.status == rebuntu::runtime::controller::ControlStatus::kAccepted);
        
        auto caps = ctrl.get_capabilities(TargetType::kExecution);
        bool has_cancel = false;
        for (const auto& op : caps) {
            if (op == ControlOperation::kCancel) {
                has_cancel = true;
                break;
            }
        }
        CHECK(has_cancel);
    }
    
    // Test ExecutionController
    {
        ExecutionController ctrl;
        auto result = ctrl.cancel_execution("exec-123", "test cancellation");
        
        CHECK(result.status == rebuntu::runtime::controller::ControlStatus::kCompleted);
        CHECK(result.verified == true);
        
        auto state = ctrl.query_state("exec-456", TargetType::kExecution);
        CHECK(state.lifecycle == rebuntu::runtime::LifecycleState::kActive);
    }
    
    // Test EngineController
    {
        EngineController ctrl;
        
        // Check initial state (not frozen)
        auto initial_state = ctrl.query_state("", TargetType::kEngine);
        CHECK(initial_state.control == rebuntu::runtime::ControlState::kEnabled);
        
        // Freeze
        auto freeze_result = ctrl.freeze_engine("maintenance");
        CHECK(freeze_result.status == rebuntu::runtime::controller::ControlStatus::kCompleted);
        CHECK(freeze_result.verified == true);
        
        // Check frozen state
        auto frozen_state = ctrl.query_state("", TargetType::kEngine);
        CHECK(frozen_state.control == rebuntu::runtime::ControlState::kFrozen);
        
        // Unfreeze
        auto unfreeze_result = ctrl.unfreeze_engine();
        CHECK(unfreeze_result.status == rebuntu::runtime::controller::ControlStatus::kCompleted);
        CHECK(unfreeze_result.verified == true);
        
        // Check unfrozen state
        auto unfrozen_state = ctrl.query_state("", TargetType::kEngine);
        CHECK(unfrozen_state.control == rebuntu::runtime::ControlState::kEnabled);
    }
    
    // Test make_default_controller factory
    {
        auto ctrl = make_default_controller();
        CHECK(ctrl != nullptr);
        
        // Verify it's an ExecutionController
        ExecutionController* ec = dynamic_cast<ExecutionController*>(ctrl.get());
        CHECK(ec != nullptr);
    }
    
    if (g_failures != 0) {
        std::cerr << g_failures << " check(s) FAILED\n";
        return 1;
    }
    std::cout << "test_controller: OK\n";
    return 0;
}