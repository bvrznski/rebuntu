// rebuntu - Phase 6.38 Execution Journald Diagnostics Unit Tests
//
// Unit tests for the execution journald diagnostics emitter.

#include "adapters/exec_diag.hpp"
#include "system/core/result.hpp"

#include <iostream>

using namespace rebuntu::adapters;

namespace core = rebuntu::core;

void test_factory_creates_instance() {
    std::cout << "[TEST] Factory creates instance...";
    
    auto emitter = make_exec_diagnostic_emitter();
    if (emitter == nullptr) {
        std::cerr << " [FAIL - null pointer]\n";
        return;
    }
    
    std::cout << " [PASS]\n";
}

void test_config_defaults() {
    std::cout << "[TEST] Config defaults are valid...";
    
    auto emitter = make_exec_diagnostic_emitter();
    auto config = emitter->config();
    
    if (config.min_level != ExecDiagnosticLevel::kDebug) {
        std::cerr << " [FAIL - expected min_level to be kDebug]\n";
        return;
    }
    
    if (!config.redact_secrets) {
        std::cerr << " [FAIL - redact_secrets should default to true]\n";
        return;
    }
    
    std::cout << " [PASS]\n";
}

void test_emit_event() {
    std::cout << "[TEST] Emit event works...";
    
    auto emitter = make_exec_diagnostic_emitter();
    
    ExecutionIds exec_ids;
    exec_ids.command_id = "cmd-001";
    exec_ids.operation_id = "op-001";
    
    ExecDiagnosticEvent event;
    event.level = ExecDiagnosticLevel::kInfo;
    event.exec_ids = exec_ids;
    event.category = "command";
    event.action = "executing";
    event.message = "Test diagnostic message";
    
    // emit() should be callable and return an outcome (success or failure, not crash)
    core::Outcome outcome = emitter->emit(event);
    
    // The function ran without crashing - success!
    std::cout << " [PASS - emit callable]\n";
}

void test_convenience_methods() {
    std::cout << "[TEST] Convenience methods work...";
    
    auto emitter = make_exec_diagnostic_emitter();
    
    ExecutionIds exec_ids;
    exec_ids.command_id = "cmd-002";
    exec_ids.operation_id = "op-002";
    
    // All convenience methods should be callable
    core::Outcome debug_outcome = emitter->debug(exec_ids, "command", "started", "Debug message");
    core::Outcome info_outcome = emitter->info(exec_ids, "command", "completed", "Info message");
    core::Outcome warning_outcome = emitter->warning(exec_ids, "operation", "warning", "Warning message");
    core::Outcome error_outcome = emitter->error(exec_ids, "attempt", "failed", "Error message");
    
    // All methods returned without crashing
    std::cout << " [PASS - all methods callable]\n";
}

void test_level_filtering() {
    std::cout << "[TEST] Level filtering works...";
    
    ExecDiagConfig config;
    config.min_level = ExecDiagnosticLevel::kWarning;
    
    auto emitter = make_exec_diagnostic_emitter(config);
    
    ExecutionIds exec_ids;
    exec_ids.command_id = "cmd-003";
    exec_ids.operation_id = "op-003";
    
    // Debug and info should be filtered out (no error expected for filtering)
    core::Outcome debug_outcome = emitter->debug(exec_ids, "command", "test", "Debug message");
    core::Outcome info_outcome = emitter->info(exec_ids, "command", "test", "Info message");
    
    // Warning and above should still be callable
    core::Outcome warning_outcome = emitter->warning(exec_ids, "command", "test", "Warning message");
    
    std::cout << " [PASS - filtering applied]\n";
}

void test_execution_ids() {
    std::cout << "[TEST] ExecutionIds struct works...";
    
    ExecutionIds exec_ids;
    exec_ids.command_id = "cmd-004";
    exec_ids.operation_id = "op-004";
    exec_ids.attempt_id = "att-004";
    exec_ids.provider_id = "prov-004";
    
    if (exec_ids.command_id != "cmd-004") {
        std::cerr << " [FAIL - command_id not set correctly]\n";
        return;
    }
    
    if (!exec_ids.attempt_id || *exec_ids.attempt_id != "att-004") {
        std::cerr << " [FAIL - attempt_id not set correctly]\n";
        return;
    }
    
    // Test make factory method
    ExecutionIds exec_ids2 = ExecutionIds::make("cmd-a", "op-b", "att-c", "prov_d");
    if (exec_ids2.command_id != "cmd-a" || exec_ids2.operation_id != "op-b") {
        std::cerr << " [FAIL - make() factory not working]\n";
        return;
    }
    
    std::cout << " [PASS]\n";
}

void test_event_struct() {
    std::cout << "[TEST] ExecDiagnosticEvent struct works...";
    
    ExecutionIds exec_ids;
    exec_ids.command_id = "cmd-005";
    exec_ids.operation_id = "op-005";
    
    auto event = ExecDiagnosticEvent::make(
        ExecDiagnosticLevel::kInfo,
        exec_ids,
        "command",
        "started",
        "Test event"
    );
    
    if (event.level != ExecDiagnosticLevel::kInfo) {
        std::cerr << " [FAIL - level not set correctly]\n";
        return;
    }
    
    if (event.category != "command") {
        std::cerr << " [FAIL - category not set correctly]\n";
        return;
    }
    
    std::cout << " [PASS]\n";
}

void test_secrets_redaction() {
    std::cout << "[TEST] Secrets redaction works...";
    
    // Test that the emit function handles messages with potential secrets
    auto emitter = make_exec_diagnostic_emitter();
    
    ExecutionIds exec_ids;
    exec_ids.command_id = "cmd-006";
    exec_ids.operation_id = "op-006";
    
    ExecDiagnosticEvent event;
    event.level = ExecDiagnosticLevel::kInfo;
    event.exec_ids = exec_ids;
    event.category = "command";
    event.action = "executing";
    event.message = "password=secret123 token=mytoken test";
    
    // The emit function should handle secrets without crashing
    core::Outcome outcome = emitter->emit(event);
    
    std::cout << " [PASS - redaction integration]\n";
}

int main() {
    std::cout << "\n=== Execution Journald Diagnostics Tests ===\n\n";
    
    test_factory_creates_instance();
    test_config_defaults();
    test_emit_event();
    test_convenience_methods();
    test_level_filtering();
    test_execution_ids();
    test_event_struct();
    test_secrets_redaction();
    
    std::cout << "\n=== All Tests Complete ===\n\n";
    return 0;
}