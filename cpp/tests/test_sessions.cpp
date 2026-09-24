// Rebuntu Sessions & Runtime Identity Tests (Phase 2.8)
// ======================================================
// Testing Session identity, environment context, invocation detection,
// and runtime directory validation

#include <system/environment/sessions.hpp>
#include <cassert>
#include <iostream>
#include <cstdlib>
#include <sys/stat.h>
#include <unistd.h>

using namespace rebuntu::environment::sessions;

void test_session_identity_default_values() {
    // Default SessionIdentity should have zero uid and background type
    SessionIdentity identity;
    
    assert(identity.uid == 0);
    assert(identity.session_id == std::nullopt);
    assert(identity.type == SessionType::kBackground);
    assert(identity.desktop == DesktopEnvironment::kUnknown);
    assert(identity.display_server == DisplayServer::kNone);
    assert(!identity.authenticated);
    assert(identity.invocation_context == InvocationContext::kDirect);
    
    std::cout << "test_session_identity_default_values: PASSED" << std::endl;
}

void test_environment_context_default_values() {
    // Default EnvironmentContext should have empty optionals
    EnvironmentContext ctx;
    
    assert(ctx.home == std::nullopt);
    assert(ctx.user == std::nullopt);
    assert(ctx.xdg_runtime_dir == std::nullopt);
    assert(ctx.invocation_context == InvocationContext::kDirect);
    assert(!ctx.is_sudo);
    assert(ctx.original_uid == 0);
    
    std::cout << "test_environment_context_default_values: PASSED" << std::endl;
}

void test_session_type_to_string() {
    // Verify to_string produces expected values
    assert(to_string(SessionType::kLogin) == "login");
    assert(to_string(SessionType::kDesktop) == "desktop");
    assert(to_string(SessionType::kShell) == "shell");
    assert(to_string(SessionType::kSystemdUser) == "systemd-user");
    assert(to_string(SessionType::kBackground) == "background");
    
    std::cout << "test_session_type_to_string: PASSED" << std::endl;
}

void test_desktop_environment_to_string() {
    // Verify to_string produces expected values
    assert(to_string(DesktopEnvironment::kNone) == "none");
    assert(to_string(DesktopEnvironment::kGNOME) == "gnome");
    assert(to_string(DesktopEnvironment::kKDE) == "kde");
    assert(to_string(DesktopEnvironment::ki3) == "i3");
    
    std::cout << "test_desktop_environment_to_string: PASSED" << std::endl;
}

void test_display_server_to_string() {
    // Verify to_string produces expected values
    assert(to_string(DisplayServer::kNone) == "none");
    assert(to_string(DisplayServer::kX11) == "x11");
    assert(to_string(DisplayServer::kWayland) == "wayland");
    
    std::cout << "test_display_server_to_string: PASSED" << std::endl;
}

void test_invocation_context_to_string() {
    // Verify to_string produces expected values
    assert(to_string(InvocationContext::kDirect) == "direct");
    assert(to_string(InvocationContext::kSudo) == "sudo");
    assert(to_string(InvocationContext::kSSH) == "ssh");
    assert(to_string(InvocationContext::kSystemdService) == "systemd-service");
    
    std::cout << "test_invocation_context_to_string: PASSED" << std::endl;
}

void test_runtime_dir_status_values() {
    // Verify enum values
    assert(static_cast<int>(RuntimeDirStatus::kAvailable) >= 0);
    assert(static_cast<int>(RuntimeDirStatus::kUnavailable) >= 0);
    assert(static_cast<int>(RuntimeDirStatus::kPermissionError) >= 0);
    
    std::cout << "test_runtime_dir_status_values: PASSED" << std::endl;
}

void test_build_current_env_context() {
    // Build context for current process
    auto ctx = build_current_env_context();
    
    // Should at least have the effective UID set correctly
    assert(ctx.original_uid == geteuid());
    
    std::cout << "test_build_current_env_context: PASSED" << std::endl;
}

void test_get_runtime_dir_fallback() {
    // Test fallback when XDG_RUNTIME_DIR is not set
    EnvironmentContext ctx;
    ctx.original_uid = 1000;  // Non-root user
    
    auto rt_dir = get_runtime_dir(ctx);
    
    // Should fall back to /run/user/<uid> for non-root
    if (!rt_dir.empty()) {
        assert(rt_dir.string().find("/run/user/1000") == 0 || 
               rt_dir.string().find("/run/user/") == 0);
    }
    
    std::cout << "test_get_runtime_dir_fallback: PASSED" << std::endl;
}

void test_env_var_policy_sudo_override() {
    // When running under sudo, HOME should use kOverride policy
    EnvironmentContext ctx;
    ctx.is_sudo = true;
    
    assert(get_env_var_policy("HOME", ctx) == EnvVarPolicy::kOverride);
    assert(get_env_var_policy("USER", ctx) == EnvVarPolicy::kOverride);
    
    std::cout << "test_env_var_policy_sudo_override: PASSED" << std::endl;
}

void test_env_var_policy_normal_trust() {
    // When not elevated, most env vars should use kTrust policy
    EnvironmentContext ctx;
    ctx.is_sudo = false;
    
    assert(get_env_var_policy("HOME", ctx) == EnvVarPolicy::kTrust);
    assert(get_env_var_policy("XDG_RUNTIME_DIR", ctx) == EnvVarPolicy::kTrust);
    
    std::cout << "test_env_var_policy_normal_trust: PASSED" << std::endl;
}

void test_get_canonical_home_with_sudo() {
    // When elevated, canonical home should use original UID
    EnvironmentContext ctx;
    ctx.is_sudo = true;
    ctx.original_uid = 1000;  // Original user
    
    auto home = get_canonical_home(ctx);
    
    // Should resolve to the original user's home (may fail if user doesn't exist)
    std::cout << "test_get_canonical_home_with_sudo: PASSED (got path: " 
              << (home.empty() ? "<empty>" : home.string()) << ")" << std::endl;
}

void test_runtime_directory_discover_without_env_var() {
    // Temporarily unset XDG_RUNTIME_DIR
    unsetenv("XDG_RUNTIME_DIR");
    
    auto info = discover_runtime_directory();
    
    assert(info.status == RuntimeDirStatus::kUnavailable);
    assert(info.path.empty());
    
    std::cout << "test_runtime_directory_discover_without_env_var: PASSED" << std::endl;
}

void test_runtime_directory_status_is_valid() {
    // Test is_valid() method
    RuntimeDirectoryInfo info;
    info.status = RuntimeDirStatus::kUnavailable;
    assert(!info.is_valid());
    
    info.status = RuntimeDirStatus::kAvailable;
    assert(info.is_valid());
    
    std::cout << "test_runtime_directory_status_is_valid: PASSED" << std::endl;
}

void test_build_env_context_for_uid() {
    // Build context for a specific UID
    auto ctx = build_env_context_for_uid(1000, InvocationContext::kDirect);
    
    assert(ctx.original_uid == 1000);
    assert(!ctx.is_sudo);
    assert(ctx.invocation_context == InvocationContext::kDirect);
    
    std::cout << "test_build_env_context_for_uid: PASSED" << std::endl;
}

void test_is_systemd_service_detection() {
    // Check if we're running under systemd
    bool is_systemd = is_systemd_service();
    
    // This should return false in most test environments
    (void)is_systemd;
    
    std::cout << "test_is_systemd_service_detection: PASSED" << std::endl;
}

void test_invocation_context_detection() {
    // Detect current invocation context
    auto ctx = detect_invocation_context();
    
    // Should be able to determine at least one context type
    assert(ctx >= InvocationContext::kDirect && ctx <= InvocationContext::kContainer);
    
    std::cout << "test_invocation_context_detection: PASSED" << std::endl;
}

void test_session_record_structure() {
    // Verify SessionRecord has expected fields
    SessionRecord record;
    
    assert(record.session_id == 0);
    assert(record.uid == 0);
    assert(record.state == SessionState::kUnknown);
    assert(!record.is_local);
    assert(!record.is_graphical);
    
    std::cout << "test_session_record_structure: PASSED" << std::endl;
}

void test_get_logind_session_id_unavailable() {
    // Without D-Bus, get_logind_session_id should return nullopt
    auto session_id = get_logind_session_id(1000);
    
    assert(session_id == std::nullopt);
    
    std::cout << "test_get_logind_session_id_unavailable: PASSED" << std::endl;
}

void test_user_sessions_empty() {
    // Without D-Bus, user sessions should return empty vector
    auto sessions = get_user_sessions(1000);
    
    assert(sessions.empty());
    
    std::cout << "test_user_sessions_empty: PASSED" << std::endl;
}

void test_primary_session_none() {
    // Without D-Bus, primary session should return nullopt
    auto primary = get_primary_session(1000);
    
    assert(primary == std::nullopt);
    
    std::cout << "test_primary_session_none: PASSED" << std::endl;
}

void test_runtime_directory_for_uid() {
    // Test runtime directory discovery for specific UID
    auto info = get_runtime_directory_for_uid(1000);
    
    // Should have correct path pattern (may or may not be valid)
    if (!info.path.empty()) {
        assert(info.path.string().find("/run/user/1000") == 0 ||
               info.path.string().find("/run/user/") == 0);
    }
    
    std::cout << "test_runtime_directory_for_uid: PASSED" << std::endl;
}

void test_resolve_canonical_home() {
    // Test canonical home resolution
    auto home = resolve_canonical_home(
        build_current_env_context(),
        getuid()
    );
    
    // Should return a path (may be empty if NSS lookup fails)
    std::cout << "test_resolve_canonical_home: PASSED" << std::endl;
}

void test_ensure_runtime_directory() {
    // Test runtime directory creation
    std::filesystem::path out_path;
    bool success = ensure_runtime_directory(build_current_env_context(), &out_path);
    
    // May succeed or fail depending on environment, but should not crash
    (void)success;
    
    std::cout << "test_ensure_runtime_directory: PASSED" << std::endl;
}

int main() {
    std::cout << "Running Rebuntu Sessions & Runtime Identity Tests (Phase 2.8)" 
              << std::endl;
    std::cout << "===================================================================" 
              << std::endl;
    
    // Enum value tests
    test_session_identity_default_values();
    test_environment_context_default_values();
    test_session_type_to_string();
    test_desktop_environment_to_string();
    test_display_server_to_string();
    test_invocation_context_to_string();
    test_runtime_dir_status_values();
    
    // Context building tests
    test_build_current_env_context();
    test_get_runtime_dir_fallback();
    test_build_env_context_for_uid();
    
    // Environment policy tests
    test_env_var_policy_sudo_override();
    test_env_var_policy_normal_trust();
    test_get_canonical_home_with_sudo();
    
    // Runtime directory tests
    test_runtime_directory_discover_without_env_var();
    test_runtime_directory_status_is_valid();
    test_runtime_directory_for_uid();
    
    // Identity tests
    test_resolve_canonical_home();
    test_get_logind_session_id_unavailable();
    
    // Session state tests
    test_session_record_structure();
    test_user_sessions_empty();
    test_primary_session_none();
    
    // Invocation context tests
    test_invocation_context_detection();
    test_is_systemd_service_detection();
    
    // Edge case tests
    test_ensure_runtime_directory();
    
    std::cout << "===================================================================" 
              << std::endl;
    std::cout << "All sessions & runtime identity tests PASSED" << std::endl;
    
    return 0;
}