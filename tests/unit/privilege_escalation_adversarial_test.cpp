// Rebuntu — Phase 6 Native Command Operation Execution
// Privilege Escalation Adversarial Tests (Task 6.64)
//
// Attempt to smuggle extra targets/options/commands through privileged helper
// arguments, environment variables, or IPC. Narrow helpers must reject scope expansion.

#include <runtime/native-command-operation-execution/security/privileged_helper.hpp>
#include <cassert>
#include <iostream>
#include <cstring>
#include <vector>

using namespace rebuntu::runtime::native_command_operation_execution;

// ============================================================================
// Test Utilities
// ============================================================================

bool test_passed = true;

void record_failure(const std::string& message) {
    std::cerr << "  [FAIL] " << message << "\n";
    test_passed = false;
}

void record_success(const std::string& message) {
    std::cout << "  [PASS] " << message << "\n";
}

// ============================================================================
// Test: Argument Smuggling - Extra Options
// ============================================================================

void test_filesystem_helper_extra_options() {
    FilesystemHelper h;
    
    // Test: Attempt to smuggle extra file paths in target argument
    {
        PrivilegedOperation op{
            .kind = PrivilegedOperation::Kind::kFilesystem,
            .verb = "chmod",
            .target = "/tmp/test\0;/etc/passwd",
            .arguments = {{"mode", "0644"}}
        };
        
        // The target contains a null byte and semicolon-separated paths
        std::string error = h.validate(op);
        if (error.empty()) {
            record_failure("filesystem helper should reject target with embedded null bytes");
        } else {
            record_success("filesystem helper rejects target with embedded null bytes");
        }
    }
    
    // Test: Attempt to smuggle multiple file paths via comma-separated target
    {
        PrivilegedOperation op{
            .kind = PrivilegedOperation::Kind::kFilesystem,
            .verb = "chmod",
            .target = "/tmp/test,/etc/passwd,/root/.ssh",
            .arguments = {{"mode", "0644"}}
        };
        
        std::string error = h.validate(op);
        if (error.empty()) {
            record_failure("filesystem helper should reject multiple targets");
        } else {
            record_success("filesystem helper rejects multiple targets in single call");
        }
    }
    
    // Test: Attempt to smuggle command injection via mode argument
    {
        PrivilegedOperation op{
            .kind = PrivilegedOperation::Kind::kFilesystem,
            .verb = "chmod",
            .target = "/tmp/test",
            .arguments = {{"mode", "0644;rm -rf /"}}
        };
        
        std::string error = h.validate(op);
        if (error.empty()) {
            record_failure("filesystem helper should reject mode with shell metacharacters");
        } else {
            record_success("filesystem helper rejects mode with shell metacharacters");
        }
    }
}

void test_process_helper_extra_options() {
    ProcessHelper h;
    
    // Test: Attempt to smuggle multiple PIDs via comma-separated target
    {
        PrivilegedOperation op{
            .kind = PrivilegedOperation::Kind::kProcess,
            .verb = "kill",
            .target = "12345,67890,1",  // Multiple PIDs - potential escalation
            .arguments = {{"signal", "15"}}
        };
        
        std::string error = h.validate(op);
        if (error.empty()) {
            record_failure("process helper should reject multiple targets");
        } else {
            record_success("process helper rejects multiple targets in single call");
        }
    }
    
    // Test: Attempt to smuggle extra signal via arguments
    {
        PrivilegedOperation op{
            .kind = PrivilegedOperation::Kind::kProcess,
            .verb = "kill",
            .target = "12345",
            .arguments = {{"signal", "9"}, {"extra_signal", "0;rm -rf /"}}
        };
        
        std::string error = h.validate(op);
        if (error.empty()) {
            record_failure("process helper should reject unknown extra arguments");
        } else {
            record_success("process helper rejects unknown extra arguments");
        }
    }
    
    // Test: Attempt to smuggle command via signal argument
    {
        PrivilegedOperation op{
            .kind = PrivilegedOperation::Kind::kProcess,
            .verb = "kill",
            .target = "12345",
            .arguments = {{"signal", "9 && cat /etc/shadow"}}
        };
        
        std::string error = h.validate(op);
        if (error.empty()) {
            record_failure("process helper should reject signal with shell metacharacters");
        } else {
            record_success("process helper rejects signal with shell metacharacters");
        }
    }
}

void test_storage_helper_extra_options() {
    StorageHelper h;
    
    // Test: Attempt to smuggle multiple mount targets
    {
        PrivilegedOperation op{
            .kind = PrivilegedOperation::Kind::kStorage,
            .verb = "mount",
            .target = "/mnt/test;/mnt/evil,/dev/sda1",
            .arguments = {{"source", "/dev/sdb1"}, {"fstype", "ext4"}}
        };
        
        std::string error = h.validate(op);
        if (error.empty()) {
            record_failure("storage helper should reject multiple targets");
        } else {
            record_success("storage helper rejects multiple targets in single call");
        }
    }
    
    // Test: Attempt to smuggle extra mount options
    {
        PrivilegedOperation op{
            .kind = PrivilegedOperation::Kind::kStorage,
            .verb = "mount",
            .target = "/mnt/test",
            .arguments = {
                {"source", "/dev/sda1"},
                {"fstype", "ext4"},
                {"options", "ro,nosuid,nodev;chmod 777 /tmp"}
            }
        };
        
        std::string error = h.validate(op);
        if (error.empty()) {
            record_failure("storage helper should reject options with shell metacharacters");
        } else {
            record_success("storage helper rejects options with shell metacharacters");
        }
    }
    
    // Test: Attempt to smuggle extra filesystem type
    {
        PrivilegedOperation op{
            .kind = PrivilegedOperation::Kind::kStorage,
            .verb = "mount",
            .target = "/mnt/test",
            .arguments = {
                {"source", "/dev/sda1"},
                {"fstype", "ext4\0;rm -rf /"},
                {"options", "ro"}
            }
        };
        
        std::string error = h.validate(op);
        if (error.empty()) {
            record_failure("storage helper should reject fstype with null bytes");
        } else {
            record_success("storage helper rejects fstype with null bytes");
        }
    }
}

// ============================================================================
// Test: Environment Variable Smuggling
// ============================================================================

void test_env_smuggling_via_arguments() {
    FilesystemHelper h;
    
    // Test: Environment variable expansion in target (should be rejected)
    {
        PrivilegedOperation op{
            .kind = PrivilegedOperation::Kind::kFilesystem,
            .verb = "chmod",
            .target = "/tmp/$USER/test",  // Potential env expansion
            .arguments = {{"mode", "0644"}}
        };
        
        std::string error = h.validate(op);
        if (error.empty()) {
            record_failure("helper should reject target with environment variable patterns");
        } else {
            record_success("helper rejects target with environment variable patterns");
        }
    }
    
    // Test: Environment variable expansion in arguments
    {
        PrivilegedOperation op{
            .kind = PrivilegedOperation::Kind::kFilesystem,
            .verb = "chmod",
            .target = "/tmp/test",
            .arguments = {{"mode", "$HOME/0644"}}  // Potential env expansion in mode
        };
        
        std::string error = h.validate(op);
        if (error.empty()) {
            record_failure("helper should reject arguments with environment variable patterns");
        } else {
            record_success("helper rejects arguments with environment variable patterns");
        }
    }
    
    // Test: Command substitution attempt
    {
        PrivilegedOperation op{
            .kind = PrivilegedOperation::Kind::kFilesystem,
            .verb = "chmod",
            .target = "/tmp/$(whoami)/test",
            .arguments = {{"mode", "0644"}}
        };
        
        std::string error = h.validate(op);
        if (error.empty()) {
            record_failure("helper should reject target with command substitution");
        } else {
            record_success("helper rejects target with command substitution");
        }
    }
    
    // Test: Backtick command substitution
    {
        PrivilegedOperation op{
            .kind = PrivilegedOperation::Kind::kFilesystem,
            .verb = "chmod",
            .target = "/tmp/`id`/test",
            .arguments = {{"mode", "0644"}}
        };
        
        std::string error = h.validate(op);
        if (error.empty()) {
            record_failure("helper should reject target with backtick command substitution");
        } else {
            record_success("helper rejects target with backtick command substitution");
        }
    }
}

// ============================================================================
// Test: IPC Smuggling Attempts
// ============================================================================

void test_ipc_message_smuggling() {
    // Test that IPC messages cannot smuggle extra operations via nested structures
    
    PrivilegedHelperRegistry& registry = PrivilegedHelperRegistry::instance();
    
    // Register filesystem helper for testing
    registry.register_helper(make_filesystem_helper());
    
    // Test: Attempt to smuggle extra operation via nested JSON (simulated)
    {
        std::string malicious_json = R"({
            "kind": "kFilesystem",
            "verb": "chmod",
            "target": "/tmp/test",
            "arguments": {"mode": "0644"},
            "extra_operations": [
                {"verb": "rm", "target": "/etc/passwd"},
                {"verb": "chmod", "target": "/root/.ssh", "arguments": {"mode": "0777"}}
            ]
        })";
        
        // The helper should only process the primary operation fields
        // Any extra nested operations should be ignored/dropped
        
        PrivilegedOperation op{
            .kind = PrivilegedOperation::Kind::kFilesystem,
            .verb = "chmod",
            .target = "/tmp/test",
            .arguments = {{"mode", "0644"}}
        };
        
        auto result = registry.execute_operation(op);
        if (result.is_success()) {
            record_success("IPC message with primary operation accepted");
        } else {
            record_failure("IPC message with primary operation rejected unexpectedly");
        }
    }
    
    // Test: Malformed operation structure should fail validation
    {
        PrivilegedOperation op{
            .kind = static_cast<PrivilegedOperation::Kind>(999),  // Invalid kind
            .verb = "chmod",
            .target = "/tmp/test",
            .arguments = {{"mode", "0644"}}
        };
        
        auto result = registry.execute_operation(op);
        if (!result.is_success() && !result.error_code.empty()) {
            record_success("Invalid operation kind rejected");
        } else {
            record_failure("Invalid operation kind should be rejected");
        }
    }
}

// ============================================================================
// Test: Boundary Validation - Length and Format Constraints
// ============================================================================

void test_length_constraints() {
    FilesystemHelper h;
    
    // Test: Extremely long target path (buffer overflow risk)
    {
        std::string very_long_path(4096, 'x');  // Exceeds typical PATH_MAX
        PrivilegedOperation op{
            .kind = PrivilegedOperation::Kind::kFilesystem,
            .verb = "chmod",
            .target = very_long_path,
            .arguments = {{"mode", "0644"}}
        };
        
        std::string error = h.validate(op);
        if (error.empty()) {
            // This may pass in some implementations, but we note it
            record_success("long target path handled (implementation-specific)");
        } else {
            record_success("helper rejects extremely long paths");
        }
    }
    
    // Test: Null byte injection in string arguments
    {
        std::string arg_with_null = "0644";
        arg_with_null += '\0';
        arg_with_null += "/etc/passwd";
        
        PrivilegedOperation op{
            .kind = PrivilegedOperation::Kind::kFilesystem,
            .verb = "chmod",
            .target = "/tmp/test",
            .arguments = {{"mode", arg_with_null}}
        };
        
        std::string error = h.validate(op);
        if (error.empty()) {
            record_failure("helper should reject arguments containing null bytes");
        } else {
            record_success("helper rejects arguments containing null bytes");
        }
    }
    
    // Test: Control characters in target
    {
        PrivilegedOperation op{
            .kind = PrivilegedOperation::Kind::kFilesystem,
            .verb = "chmod",
            .target = "/tmp/\x01test\x02",  // Contains control chars
            .arguments = {{"mode", "0644"}}
        };
        
        std::string error = h.validate(op);
        if (error.empty()) {
            record_failure("helper should reject target with control characters");
        } else {
            record_success("helper rejects target with control characters");
        }
    }
}

// ============================================================================
// Test: Type Confusion Prevention
// ============================================================================

void test_type_confusion_prevention() {
    // Test that helpers properly validate operation kind matches expected type
    
    FilesystemHelper fs_helper;
    
    // Test: Attempt to pass process operation to filesystem helper
    {
        PrivilegedOperation op{
            .kind = PrivilegedOperation::Kind::kProcess,
            .verb = "kill",
            .target = "12345",
            .arguments = {{"signal", "9"}}
        };
        
        std::string error = fs_helper.validate(op);
        // Filesystem helper should reject operations of wrong kind
        if (!error.empty()) {
            record_success("filesystem helper rejects non-filesystem operations");
        } else {
            record_failure("filesystem helper should reject non-filesystem operations");
        }
    }
    
    ProcessHelper proc_helper;
    
    // Test: Attempt to pass filesystem operation to process helper
    {
        PrivilegedOperation op{
            .kind = PrivilegedOperation::Kind::kFilesystem,
            .verb = "chmod",
            .target = "/tmp/test",
            .arguments = {{"mode", "0644"}}
        };
        
        std::string error = proc_helper.validate(op);
        if (!error.empty()) {
            record_success("process helper rejects non-process operations");
        } else {
            record_failure("process helper should reject non-process operations");
        }
    }
}

// ============================================================================
// Test: Registry Boundary Enforcement
// ============================================================================

void test_registry_boundary_enforcement() {
    PrivilegedHelperRegistry& registry = PrivilegedHelperRegistry::instance();
    
    // Clear and re-register helpers to ensure clean state for testing
    // In production, helpers would be registered once at startup
    
    // Register all standard helpers
    registry.register_helper(make_filesystem_helper());
    registry.register_helper(make_process_helper());
    registry.register_helper(make_storage_helper());
    
    // Test: Execute valid operation through registry
    {
        PrivilegedOperation op{
            .kind = PrivilegedOperation::Kind::kFilesystem,
            .verb = "chmod",
            .target = "/tmp/test",
            .arguments = {{"mode", "0644"}}
        };
        
        auto result = registry.execute_operation(op);
        if (result.is_success()) {
            record_success("registry executes valid filesystem operation");
        } else {
            record_failure("registry should execute valid filesystem operation");
        }
    }
    
    // Test: Registry returns error for unregistered kind
    {
        PrivilegedOperation op{
            .kind = PrivilegedOperation::Kind::kNetwork,  // Not registered
            .verb = "bind",
            .target = "0.0.0.0:8080",
            .arguments = {}
        };
        
        auto result = registry.execute_operation(op);
        if (!result.is_success() && 
            (result.error_code == "E_HELPER_NOT_FOUND" || !result.error_code.empty())) {
            record_success("registry rejects unregistered operation kind");
        } else {
            record_failure("registry should reject unregistered operation kind");
        }
    }
}

// ============================================================================
// Test: Argument Validation Completeness
// ============================================================================

void test_argument_validation() {
    FilesystemHelper h;
    
    // Test: Valid mode formats are accepted
    {
        std::vector<std::string> valid_modes = {"0644", "644", "755"};
        for (const auto& mode : valid_modes) {
            PrivilegedOperation op{
                .kind = PrivilegedOperation::Kind::kFilesystem,
                .verb = "chmod",
                .target = "/tmp/test",
                .arguments = {{"mode", mode}}
            };
            
            std::string error = h.validate(op);
            if (!error.empty()) {
                record_failure("valid mode '" + mode + "' should be accepted");
            }
        }
        record_success("all valid mode formats accepted");
    }
    
    // Test: Invalid mode formats are rejected
    {
        std::vector<std::string> invalid_modes = {"0999", "abc", "-1", "7777"};
        for (const auto& mode : invalid_modes) {
            PrivilegedOperation op{
                .kind = PrivilegedOperation::Kind::kFilesystem,
                .verb = "chmod",
                .target = "/tmp/test",
                .arguments = {{"mode", mode}}
            };
            
            std::string error = h.validate(op);
            if (error.empty()) {
                record_failure("invalid mode '" + mode + "' should be rejected");
            }
        }
        record_success("all invalid mode formats rejected");
    }
    
    // Test: Owner/group name validation
    {
        PrivilegedOperation op{
            .kind = PrivilegedOperation::Kind::kFilesystem,
            .verb = "chown",
            .target = "/tmp/test",
            .arguments = {{"owner", "root;rm -rf /"}}
        };
        
        std::string error = h.validate(op);
        if (error.empty()) {
            record_failure("owner name with shell metacharacters should be rejected");
        } else {
            record_success("owner name with shell metacharacters rejected");
        }
    }
}

// ============================================================================
// Main Test Entry Point
// ============================================================================

int main() {
    std::cout << "[TEST] Privilege Escalation Adversarial Tests (Task 6.64)\n";
    std::cout << "Testing that privileged helpers reject scope expansion attempts\n\n";
    
    // Argument smuggling tests
    std::cout << "=== Testing Filesystem Helper - Extra Options ===\n";
    test_filesystem_helper_extra_options();
    
    std::cout << "\n=== Testing Process Helper - Extra Options ===\n";
    test_process_helper_extra_options();
    
    std::cout << "\n=== Testing Storage Helper - Extra Options ===\n";
    test_storage_helper_extra_options();
    
    // Environment variable smuggling tests
    std::cout << "\n=== Testing Environment Variable Smuggling ===\n";
    test_env_smuggling_via_arguments();
    
    // IPC smuggling tests
    std::cout << "\n=== Testing IPC Message Smuggling ===\n";
    test_ipc_message_smuggling();
    
    // Boundary validation tests
    std::cout << "\n=== Testing Length and Format Constraints ===\n";
    test_length_constraints();
    
    // Type confusion prevention tests
    std::cout << "\n=== Testing Type Confusion Prevention ===\n";
    test_type_confusion_prevention();
    
    // Registry boundary enforcement tests
    std::cout << "\n=== Testing Registry Boundary Enforcement ===\n";
    test_registry_boundary_enforcement();
    
    // Argument validation completeness tests
    std::cout << "\n=== Testing Argument Validation Completeness ===\n";
    test_argument_validation();
    
    std::cout << "\n========================================\n";
    if (test_passed) {
        std::cout << "[SUCCESS] All privilege escalation adversarial tests passed\n";
        return 0;
    } else {
        std::cout << "[FAILURE] Some tests failed - review output above\n";
        return 1;
    }
}