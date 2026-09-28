// rebuntu - Phase 6.14 Collision Scanner Unit Tests
//
// Unit tests for the command collision detection system.

#include <system/shell/collision_scanner.hpp>
#include <iostream>
#include <cassert>

using namespace rebuntu::shell::collision;

void test_shell_builtin_detection() {
    std::cout << "[TEST] Shell builtin detection...\n";
    
    ScannerConfig config = default_config();
    config.include_system_commands = false;
    config.include_user_definitions = false;
    
    CollisionScanner scanner(config);
    
    // Test that shell builtins are detected
    auto result = scanner.scan_verb("export");
    assert(result.class_ == CollisionClass::kShellBuiltin);
    std::cout << "  export -> " << to_string(result.class_) << " [PASS]\n";
    
    result = scanner.scan_verb("cd");
    assert(result.class_ == CollisionClass::kShellBuiltin);
    std::cout << "  cd -> " << to_string(result.class_) << " [PASS]\n";
    
    // Test that non-builtin is not flagged
    result = scanner.scan_verb("rebuntu_command");
    assert(result.class_ == CollisionClass::kNone);
    std::cout << "  rebuntu_command -> " << to_string(result.class_) << " [PASS]\n";
}

void test_system_command_detection() {
    std::cout << "[TEST] System command detection...\n";
    
    ScannerConfig config = default_config();
    config.include_shell_builtins = false;
    config.include_user_definitions = false;
    
    CollisionScanner scanner(config);
    
    // Test that common system commands are detected
    auto result = scanner.scan_verb("ls");
    if (result.class_ == CollisionClass::kSystemCommand) {
        std::cout << "  ls -> " << to_string(result.class_) << " [PASS]\n";
    } else {
        std::cout << "  ls -> " << to_string(result.class_) 
                  << " (skipped, command may not exist in test env)\n";
    }
    
    result = scanner.scan_verb("find");
    if (result.class_ == CollisionClass::kSystemCommand) {
        std::cout << "  find -> " << to_string(result.class_) << " [PASS]\n";
    } else {
        std::cout << "  find -> " << to_string(result.class_) 
                  << " (skipped, command may not exist in test env)\n";
    }
    
    // Test that non-existent command is not flagged
    result = scanner.scan_verb("nonexistent_command_xyz");
    assert(result.class_ == CollisionClass::kNone);
    std::cout << "  nonexistent_command_xyz -> " << to_string(result.class_) << " [PASS]\n";
}

void test_reserved_verb_detection() {
    std::cout << "[TEST] Reserved Rebuntu verb detection...\n";
    
    ScannerConfig config = default_config();
    config.include_shell_builtins = false;
    config.include_system_commands = false;
    config.include_user_definitions = false;
    
    CollisionScanner scanner(config);
    
    // Test that reserved verbs are detected
    auto result = scanner.scan_verb("install");
    assert(result.class_ == CollisionClass::kReservedRebuntu);
    std::cout << "  install -> " << to_string(result.class_) << " [PASS]\n";
    
    result = scanner.scan_verb("remove");
    assert(result.class_ == CollisionClass::kReservedRebuntu);
    std::cout << "  remove -> " << to_string(result.class_) << " [PASS]\n";
    
    // Test that non-reserved verb is not flagged
    result = scanner.scan_verb("custom_command");
    assert(result.class_ == CollisionClass::kNone);
    std::cout << "  custom_command -> " << to_string(result.class_) << " [PASS]\n";
}

void test_collision_scanner_report() {
    std::cout << "[TEST] Collision report generation...\n";
    
    ScannerConfig config = default_config();
    CollisionScanner scanner(config);
    
    // Scan multiple verbs
    std::vector<std::string> verbs = {"export", "ls", "install", "echo"};
    auto report = scanner.generate_report(verbs);
    
    std::cout << "  Total collisions: " << report.total_collisions << "\n";
    std::cout << "  Shell builtins: " << report.shell_builtins << "\n";
    std::cout << "  System commands: " << report.system_commands << "\n";
    std::cout << "  User definitions: " << report.user_definitions << "\n";
    
    // We expect some collisions
    assert(report.total_collisions > 0);
    std::cout << "  Collisions detected [PASS]\n";
}

void test_get_collision_status() {
    std::cout << "[TEST] get_collision_status utility function...\n";
    
    auto status = get_collision_status("export");
    assert(status == CollisionClass::kShellBuiltin);
    std::cout << "  export -> " << to_string(status) << " [PASS]\n";
}

int main() {
    std::cout << "Phase 6.14 Collision Scanner Unit Tests\n";
    std::cout << "========================================\n\n";
    
    test_shell_builtin_detection();
    std::cout << "\n";
    
    test_system_command_detection();
    std::cout << "\n";
    
    test_reserved_verb_detection();
    std::cout << "\n";
    
    test_collision_scanner_report();
    std::cout << "\n";
    
    test_get_collision_status();
    std::cout << "\n";
    
    std::cout << "All collision scanner tests completed!\n";
    return 0;
}