// rebuntu::operations::read_file unit tests (Phase 6.69 Vertical Slice)
//
// Tests for the safe read file operation:
//   - Typed inputs and outputs
//   - Precondition validation
//   - Bounded read operations
//   - Evidence collection

#include <cassert>
#include <chrono>
#include <iostream>
#include <fstream>
#include <string>

#include <system/core/contracts.hpp>
#include "operations/read_file.hpp"

using namespace rebuntu::operations;

void test_register_operation() {
    rebuntu::core::OperationRegistry registry;
    register_read_file_operation(registry);
    
    auto op = registry.find("filesystem.read_file");
    assert(op.has_value());
    assert(op->id == "filesystem.read_file");
    assert(op->side_effect == SideEffectKind::NONE);
}

void test_read_nonexistent_file() {
    ReadFileInputs inputs;
    inputs.path = "/nonexistent/file/path.txt";
    inputs.max_bytes = 1024;
    
    auto result = read_file(inputs);
    
    assert(result.status == core::SemanticStatus::kFailure);
    assert(!result.content.has_value());
}

void test_read_valid_file() {
    // Create a temporary file for testing
    std::ofstream temp_file("/tmp/rebuntu_test_read.txt");
    temp_file << "Hello, Rebuntu!";
    temp_file.close();
    
    ReadFileInputs inputs;
    inputs.path = "/tmp/rebuntu_test_read.txt";
    inputs.max_bytes = 1024;
    
    auto result = read_file(inputs);
    
    assert(result.status == core::SemanticStatus::kSuccess);
    assert(result.content.has_value());
    assert(result.content.value() == "Hello, Rebuntu!");
    assert(result.bytes_read > 0);
    
    // Cleanup
    std::remove("/tmp/rebuntu_test_read.txt");
}

void test_read_with_max_bytes_bound() {
    // Create a file with known content
    std::ofstream temp_file("/tmp/rebuntu_test_large.txt");
    for (int i = 0; i < 100; ++i) {
        temp_file << "Line " << i << "\n";
    }
    temp_file.close();
    
    ReadFileInputs inputs;
    inputs.path = "/tmp/rebuntu_test_large.txt";
    inputs.max_bytes = 50;  // Limit to 50 bytes
    
    auto result = read_file(inputs);
    
    assert(result.status == core::SemanticStatus::kSuccess);
    assert(result.content.has_value());
    assert(result.bytes_read <= 50);  // Should respect the bound
    
    // Cleanup
    std::remove("/tmp/rebuntu_test_large.txt");
}

void test_invalid_inputs() {
    // Empty path should fail validation
    ReadFileInputs inputs1;
    inputs1.path = "";
    inputs1.max_bytes = 1024;
    
    std::string error;
    bool valid1 = inputs1.is_valid(error);
    assert(!valid1);
    assert(!error.empty());
    
    // Zero max_bytes should fail
    ReadFileInputs inputs2;
    inputs2.path = "/tmp";
    inputs2.max_bytes = 0;
    
    bool valid2 = inputs2.is_valid(error);
    assert(!valid2);
}

void test_evidence_collected() {
    std::ofstream temp_file("/tmp/rebuntu_test_evidence.txt");
    temp_file << "Test content";
    temp_file.close();
    
    ReadFileInputs inputs;
    inputs.path = "/tmp/rebuntu_test_evidence.txt";
    inputs.max_bytes = 1024;
    
    auto result = read_file(inputs);
    
    assert(result.status == core::SemanticStatus::kSuccess);
    // Evidence should be collected
    assert(!result.evidence.empty());
    
    // Cleanup
    std::remove("/tmp/rebuntu_test_evidence.txt");
}


int main() {
    std::cout << "=== Phase 6.69: Read File Operation Tests ===" << std::endl;
    
    test_read_nonexistent_file();
    std::cout << "[PASS] Nonexistent file returns failure" << std::endl;
    
    test_read_valid_file();
    std::cout << "[PASS] Valid file read returns success with content" << std::endl;
    
    test_read_with_max_bytes_bound();
    std::cout << "[PASS] Max bytes bound is respected" << std::endl;
    
    test_invalid_inputs();
    std::cout << "[PASS] Invalid inputs are rejected" << std::endl;
    
    test_evidence_collected();
    std::cout << "[PASS] Evidence is collected during observation" << std::endl;
    
    test_register_operation();
    std::cout << "[PASS] Operation registers correctly in registry" << std::endl;
    
    std::cout << "\n=== All Phase 6.69 tests passed ===" << std::endl;
    return 0;
}