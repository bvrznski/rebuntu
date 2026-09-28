// Rebuntu — Phase 6 Native Command Operation Execution
// Privileged Helper Unit Tests

#include "privileged_helper.hpp"
#include <cassert>
#include <iostream>

using namespace rebuntu::runtime::native_command_operation_execution;

void test_filesystem_helper_valid_operations() {
    // Test chmod with valid mode
    {
        FilesystemHelper h;
        PrivilegedOperation op{
            .kind = PrivilegedOperation::Kind::kFilesystem,
            .verb = "chmod",
            .target = "/tmp/test",
            .arguments = {{"mode", "0644"}}
        };
        
        std::string error = h.validate(op);
        assert(error.empty() && "chmod with valid mode should pass validation");
    }
    
    // Test truncate
    {
        FilesystemHelper h;
        PrivilegedOperation op{
            .kind = PrivilegedOperation::Kind::kFilesystem,
            .verb = "truncate",
            .target = "/tmp/testfile",
            .arguments = {}
        };
        
        std::string error = h.validate(op);
        assert(error.empty() && "truncate should pass validation");
    }
}

void test_filesystem_helper_invalid_operations() {
    // Test unknown verb
    {
        FilesystemHelper h;
        PrivilegedOperation op{
            .kind = PrivilegedOperation::Kind::kFilesystem,
            .verb = "rm",
            .target = "/tmp/test",
            .arguments = {}
        };
        
        std::string error = h.validate(op);
        assert(!error.empty() && "unknown verb should fail validation");
    }
    
    // Test invalid mode (contains non-octal characters)
    {
        FilesystemHelper h;
        PrivilegedOperation op{
            .kind = PrivilegedOperation::Kind::kFilesystem,
            .verb = "chmod",
            .target = "/tmp/test",
            .arguments = {{"mode", "0999"}}
        };
        
        std::string error = h.validate(op);
        assert(!error.empty() && "invalid octal mode should fail");
    }
}

void test_process_helper_valid_operations() {
    // Test kill with valid PID and signal
    {
        ProcessHelper h;
        PrivilegedOperation op{
            .kind = PrivilegedOperation::Kind::kProcess,
            .verb = "kill",
            .target = "12345",
            .arguments = {{"signal", "15"}}
        };
        
        std::string error = h.validate(op);
        assert(error.empty() && "valid kill should pass validation");
    }
    
    // Test kill with self target
    {
        ProcessHelper h;
        PrivilegedOperation op{
            .kind = PrivilegedOperation::Kind::kProcess,
            .verb = "kill",
            .target = "self",
            .arguments = {{"signal", "0"}}
        };
        
        std::string error = h.validate(op);
        assert(error.empty() && "kill self should pass validation");
    }
}

void test_process_helper_invalid_operations() {
    // Test invalid signal number
    {
        ProcessHelper h;
        PrivilegedOperation op{
            .kind = PrivilegedOperation::Kind::kProcess,
            .verb = "kill",
            .target = "12345",
            .arguments = {{"signal", "99"}}
        };
        
        std::string error = h.validate(op);
        assert(!error.empty() && "invalid signal should fail validation");
    }
    
    // Test invalid PID (contains non-digits)
    {
        ProcessHelper h;
        PrivilegedOperation op{
            .kind = PrivilegedOperation::Kind::kProcess,
            .verb = "kill",
            .target = "abc123",
            .arguments = {{"signal", "15"}}
        };
        
        std::string error = h.validate(op);
        assert(!error.empty() && "invalid PID should fail validation");
    }
}

void test_storage_helper_valid_operations() {
    // Test mount with valid source and options
    {
        StorageHelper h;
        PrivilegedOperation op{
            .kind = PrivilegedOperation::Kind::kStorage,
            .verb = "mount",
            .target = "/mnt/test",
            .arguments = {
                {"source", "/dev/sda1"},
                {"fstype", "ext4"}
            }
        };
        
        std::string error = h.validate(op);
        assert(error.empty() && "valid mount should pass validation");
    }
}

void test_storage_helper_invalid_operations() {
    // Test umount (allowed)
    {
        StorageHelper h;
        PrivilegedOperation op{
            .kind = PrivilegedOperation::Kind::kStorage,
            .verb = "umount",
            .target = "/mnt/test",
            .arguments = {}
        };
        
        std::string error = h.validate(op);
        assert(error.empty() && "umount should pass validation");
    }
    
    // Test invalid mount with shell metacharacters
    {
        StorageHelper h;
        PrivilegedOperation op{
            .kind = PrivilegedOperation::Kind::kStorage,
            .verb = "mount",
            .target = "/mnt/test",
            .arguments = {{"options", "ro;rm -rf /"}}
        };
        
        std::string error = h.validate(op);
        assert(!error.empty() && "shell metacharacters should fail validation");
    }
}

void test_registry() {
    PrivilegedHelperRegistry& registry = PrivilegedHelperRegistry::instance();
    
    // Register a helper
    registry.register_helper(make_filesystem_helper());
    
    // The registry will find helpers by kind internally
    std::cout << "  Registry registration successful\n";
}

void test_result_types() {
    // Test success
    auto result = PrivilegedHelperResult::success();
    assert(result.status == SemanticStatus::kSuccess);
    assert(result.is_success());
    
    // Test failure
    auto fail_result = PrivilegedHelperResult::failure("E_TEST", "test error");
    assert(fail_result.status == SemanticStatus::kFailure);
    assert(!fail_result.is_success());
}

int main() {
    std::cout << "[TEST] Privileged helper validation and execution...\n";
    
    test_filesystem_helper_valid_operations();
    std::cout << "  [PASS] Filesystem helper valid operations\n";
    
    test_filesystem_helper_invalid_operations();
    std::cout << "  [PASS] Filesystem helper invalid operations rejected\n";
    
    test_process_helper_valid_operations();
    std::cout << "  [PASS] Process helper valid operations\n";
    
    test_process_helper_invalid_operations();
    std::cout << "  [PASS] Process helper invalid operations rejected\n";
    
    test_storage_helper_valid_operations();
    std::cout << "  [PASS] Storage helper valid operations\n";
    
    test_storage_helper_invalid_operations();
    std::cout << "  [PASS] Storage helper invalid operations rejected\n";
    
    test_registry();
    std::cout << "  [PASS] Registry registration works\n";
    
    test_result_types();
    std::cout << "  [PASS] Result types correct\n";
    
    std::cout << "\n[SUCCESS] All privileged helper tests passed\n";
    return 0;
}