// Rebuntu Scope Tests (Phase 2.7)
// ===================================
// Testing System/User/Session Scope resolution and cross-scope mediation

#include <system/environment/scope.hpp>
#include <cassert>
#include <iostream>
#include <cstdlib>

using namespace rebuntu::environment::scope;

void test_execution_scope_enum_values() {
    // Verify enum values are as expected
    assert(to_string(ExecutionScope::kSystem) == "system");
    assert(to_string(ExecutionScope::kUser) == "user");
    assert(to_string(ExecutionScope::kSession) == "session");
    
    std::cout << "test_execution_scope_enum_values: PASSED" << std::endl;
}

void test_xdg_bases_get_user_home_with_env() {
    // Set HOME environment variable
    setenv("HOME", "/home/testuser", 1);
    
    auto home = XDGBases::get_user_home();
    assert(home.string().find("/home/testuser") == 0);
    
    // Cleanup
    unsetenv("HOME");
    
    std::cout << "test_xdg_bases_get_user_home_with_env: PASSED" << std::endl;
}

void test_default_config_path() {
    setenv("HOME", "/home/testuser", 1);
    
    auto config = default_config_home();
    assert(config.string().find("/home/testuser/.config") == 0);
    
    unsetenv("HOME");
    
    std::cout << "test_default_config_path: PASSED" << std::endl;
}

void test_system_paths() {
    // System paths should be absolute and under /usr, /etc, or /var/lib
    auto bin = get_system_bin_path();
    assert(bin.string().find("/usr/bin") == 0);
    
    auto config = get_system_config_dir();
    assert(config.string().find("/etc/rebuntu") == 0);
    
    auto state = get_system_state_dir();
    assert(state.string().find("/var/lib/rebuntu") == 0);
    
    auto cache = get_system_cache_dir();
    assert(cache.string().find("/var/cache/rebuntu") == 0);
    
    std::cout << "test_system_paths: PASSED" << std::endl;
}

void test_user_paths() {
    // User paths should be under home directory
    setenv("HOME", "/home/testuser", 1);
    
    auto bin = get_user_bin_path("/home/testuser");
    assert(bin.string().find("/home/testuser/.local/bin") == 0);
    
    auto config = get_user_config_dir("/home/testuser");
    assert(config.string().find("/home/testuser/.config/rebuntu") == 0);
    
    auto state = get_user_state_dir("/home/testuser");
    assert(state.string().find("/home/testuser/.local/state/rebuntu") == 0);
    
    auto cache = get_user_cache_dir("/home/testuser");
    assert(cache.string().find("/home/testuser/.cache/rebuntu") == 0);
    
    unsetenv("HOME");
    
    std::cout << "test_user_paths: PASSED" << std::endl;
}

void test_default_scope_for_privilege() {
    // Root should get system scope
    assert(default_scope_for_privilege(true) == ExecutionScope::kSystem);
    
    // Non-root should get user scope
    assert(default_scope_for_privilege(false) == ExecutionScope::kUser);
    
    std::cout << "test_default_scope_for_privilege: PASSED" << std::endl;
}

void test_mediate_cross_scope_same_scope() {
    ScopeContext current;
    current.scope = ExecutionScope::kSystem;
    current.effective_uid = 0;
    current.is_root = true;
    
    auto result = mediate_cross_scope_request(current, ExecutionScope::kSystem);
    assert(result.action == CrossScopeAction::kAllow);
    assert(result.explanation.find("matches") != std::string::npos);
    
    std::cout << "test_mediate_cross_scope_same_scope: PASSED" << std::endl;
}

void test_mediate_cross_scope_user_requests_system() {
    ScopeContext current;
    current.scope = ExecutionScope::kUser;
    current.effective_uid = 1000;
    current.is_root = false;
    
    auto result = mediate_cross_scope_request(current, ExecutionScope::kSystem);
    assert(result.action == CrossScopeAction::kRequireElevation);
    assert(result.explanation.find("root") != std::string::npos);
    
    std::cout << "test_mediate_cross_scope_user_requests_system: PASSED" << std::endl;
}

void test_mediate_cross_scope_system_to_user() {
    ScopeContext current;
    current.scope = ExecutionScope::kSystem;
    current.effective_uid = 0;
    current.is_root = true;
    current.original_uid = 1000;  // Was elevated from regular user
    
    auto result = mediate_cross_scope_request(current, ExecutionScope::kUser);
    assert(result.action == CrossScopeAction::kRedirectToUser);
    
    std::cout << "test_mediate_cross_scope_system_to_user: PASSED" << std::endl;
}

void test_mediate_cross_scope_session_without_runtime_dir() {
    ScopeContext current;
    current.scope = ExecutionScope::kUser;
    current.effective_uid = 1000;
    current.is_root = false;
    
    // No runtime directory set
    auto result = mediate_cross_scope_request(current, ExecutionScope::kSession);
    assert(result.action == CrossScopeAction::kDeny);
    assert(result.explanation.find("XDG_RUNTIME_DIR") != std::string::npos);
    
    std::cout << "test_mediate_cross_scope_session_without_runtime_dir: PASSED" << std::endl;
}

void test_validate_path_system() {
    // System path should be valid for kSystem scope
    auto result = validate_path_for_scope("/usr/bin/rebuntu", ExecutionScope::kSystem);
    assert(result.is_valid());
    
    std::cout << "test_validate_path_system: PASSED" << std::endl;
}

void test_validate_path_wrong_scope() {
    // User path should be wrong for kSystem scope
    auto result = validate_path_for_scope("/home/user/.local/bin/rebuntu", ExecutionScope::kSystem);
    assert(result.result == PathValidationResult::kWrongScope);
    
    std::cout << "test_validate_path_wrong_scope: PASSED" << std::endl;
}

void test_resolve_explicit_scope_system() {
    ScopeContext current;
    current.effective_uid = 0;
    current.is_root = true;
    
    auto result = resolve_explicit_scope("system", current);
    assert(result.has_value());
    assert(*result == ExecutionScope::kSystem);
    
    std::cout << "test_resolve_explicit_scope_system: PASSED" << std::endl;
}

void test_resolve_explicit_scope_user() {
    ScopeContext current;
    current.effective_uid = 1000;
    current.is_root = false;
    
    auto result = resolve_explicit_scope("user", current);
    assert(result.has_value());
    assert(*result == ExecutionScope::kUser);
    
    std::cout << "test_resolve_explicit_scope_user: PASSED" << std::endl;
}

void test_resolve_explicit_scope_session() {
    ScopeContext current;
    current.effective_uid = 1000;
    current.is_root = false;
    current.xdg.runtime_dir = "/run/user/1000";
    
    auto result = resolve_explicit_scope("session", current);
    assert(result.has_value());
    assert(*result == ExecutionScope::kSession);
    
    std::cout << "test_resolve_explicit_scope_session: PASSED" << std::endl;
}

void test_cross_scope_mediations() {
    // Test various cross-scope mediation scenarios
    
    ScopeContext rootCtx;
    rootCtx.scope = ExecutionScope::kSystem;
    rootCtx.effective_uid = 0;
    rootCtx.is_root = true;
    
    ScopeContext userCtx;
    userCtx.scope = ExecutionScope::kUser;
    userCtx.effective_uid = 1000;
    userCtx.is_root = false;
    
    // System to system - allow
    auto r1 = mediate_cross_scope_request(rootCtx, ExecutionScope::kSystem);
    assert(r1.action == CrossScopeAction::kAllow);
    
    // User to user - allow
    auto r2 = mediate_cross_scope_request(userCtx, ExecutionScope::kUser);
    assert(r2.action == CrossScopeAction::kAllow);
    
    // User to system - require elevation
    auto r3 = mediate_cross_scope_request(userCtx, ExecutionScope::kSystem);
    assert(r3.action == CrossScopeAction::kRequireElevation);
    
    std::cout << "test_cross_scope_mediations: PASSED" << std::endl;
}

int main() {
    std::cout << "Running Rebuntu Scope Tests (Phase 2.7)" << std::endl;
    std::cout << "==========================================" << std::endl;
    
    test_execution_scope_enum_values();
    test_xdg_bases_get_user_home_with_env();
    test_default_config_path();
    test_system_paths();
    test_user_paths();
    test_default_scope_for_privilege();
    test_mediate_cross_scope_same_scope();
    test_mediate_cross_scope_user_requests_system();
    test_mediate_cross_scope_system_to_user();
    test_mediate_cross_scope_session_without_runtime_dir();
    test_validate_path_system();
    test_validate_path_wrong_scope();
    test_resolve_explicit_scope_system();
    test_resolve_explicit_scope_user();
    test_resolve_explicit_scope_session();
    test_cross_scope_mediations();
    
    std::cout << "==========================================" << std::endl;
    std::cout << "All scope tests PASSED" << std::endl;
    
    return 0;
}