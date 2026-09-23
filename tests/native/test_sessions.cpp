// Rebuntu — Sessions & Runtime Identity Tests (Phase 2.8)
//
// Test the session identity and runtime directory management:
//   - SessionIdentity struct
//   - InvocationContext detection
//   - Runtime directory discovery and validation

#include <observation/environment/sessions.hpp>

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

namespace {
int g_failures = 0;
#define CHECK(cond) do { if (!(cond)) { std::cerr << "CHECK failed: " << #cond << " (line " << __LINE__ << ")\\n"; ++g_failures; } } while(0)
}  // namespace

void test_session_type_to_string() {
    using rebuntu::environment::sessions::to_string;
    using rebuntu::environment::sessions::SessionType;
    
    CHECK(to_string(SessionType::kLogin) == "login");
    CHECK(to_string(SessionType::kDesktop) == "desktop");
    CHECK(to_string(SessionType::kShell) == "shell");
    CHECK(to_string(SessionType::kSystemdUser) == "systemd-user");
    CHECK(to_string(SessionType::kBackground) == "background");
}

void test_invocation_context_to_string() {
    using rebuntu::environment::sessions::to_string;
    using rebuntu::environment::sessions::InvocationContext;
    
    CHECK(to_string(InvocationContext::kDirect) == "direct");
    CHECK(to_string(InvocationContext::kSudo) == "sudo");
    CHECK(to_string(InvocationContext::kSU) == "su");
    CHECK(to_string(InvocationContext::kSSH) == "ssh");
    CHECK(to_string(InvocationContext::kSystemdService) == "systemd-service");
    CHECK(to_string(InvocationContext::kDesktopLaunch) == "desktop-launch");
}

void test_session_identity_defaults() {
    using rebuntu::environment::sessions::SessionIdentity;
    
    SessionIdentity identity;
    CHECK(identity.uid == 0u);
    CHECK(!identity.username.has_value());
    CHECK(!identity.session_id.has_value());
    CHECK(identity.type == rebuntu::environment::sessions::SessionType::kBackground);
}

void test_environment_context_defaults() {
    using rebuntu::environment::sessions::EnvironmentContext;
    
    EnvironmentContext ctx;
    CHECK(!ctx.is_sudo);
    // original_uid is uid_t (not optional) - should be initialized to 0
    CHECK(ctx.original_uid == 0u);
}

void test_runtime_directory_discover_missing() {
    using rebuntu::environment::sessions::discover_runtime_directory;
    using rebuntu::environment::sessions::RuntimeDirStatus;
    
    // Unset XDG_RUNTIME_DIR
    unsetenv("XDG_RUNTIME_DIR");
    
    auto info = discover_runtime_directory();
    CHECK(info.status == RuntimeDirStatus::kUnavailable);
}

void test_runtime_directory_discover_valid() {
    using rebuntu::environment::sessions::discover_runtime_directory;
    using rebuntu::environment::sessions::RuntimeDirStatus;
    
    // Create a test directory with proper permissions
    std::string test_dir = "/tmp/test-runtime-" + std::to_string(getuid());
    setenv("XDG_RUNTIME_DIR", test_dir.c_str(), 1);
    
    mkdir(test_dir.c_str(), 0700);
    
    auto info = discover_runtime_directory();
    CHECK(info.status == RuntimeDirStatus::kAvailable);
    
    // Verify it's valid
    CHECK(info.is_valid());
    
    // Cleanup
    rmdir(test_dir.c_str());
    unsetenv("XDG_RUNTIME_DIR");
}

void test_invocation_context_detection() {
    using rebuntu::environment::sessions::detect_invocation_context;
    using rebuntu::environment::sessions::InvocationContext;
    
    // Clear all special environment variables
    unsetenv("SUDO_USER");
    unsetenv("SSH_CLIENT");
    unsetenv("NOTIFY_SOCKET");
    
    auto ctx = detect_invocation_context();
    CHECK(ctx == InvocationContext::kDirect);
}

void test_sudo_detection() {
    using rebuntu::environment::sessions::is_running_under_sudo;
    using rebuntu::environment::sessions::InvocationContext;
    using rebuntu::environment::sessions::build_current_env_context;
    
    // Build current context - should correctly detect state
    auto ctx = build_current_env_context();
    
    // At minimum, we should get a valid home directory (non-empty)
    CHECK(!ctx.resolved_home.empty());
}

void test_desktop_detection() {
    using rebuntu::environment::sessions::detect_desktop_environment;
    using rebuntu::environment::sessions::DesktopEnvironment;
    
    auto de = detect_desktop_environment();
    // Should return a valid enum value (may be kNone if headless)
    CHECK(de == DesktopEnvironment::kNone || 
          de == DesktopEnvironment::kGNOME ||
          de == DesktopEnvironment::kKDE ||
          de == DesktopEnvironment::kWayland);
}

int main() {
    std::cout << "Testing Sessions & Runtime Identity (Phase 2.8)...\\n";
    
    test_session_type_to_string();
    test_invocation_context_to_string();
    test_session_identity_defaults();
    test_environment_context_defaults();
    test_runtime_directory_discover_missing();
    test_runtime_directory_discover_valid();
    test_invocation_context_detection();
    test_sudo_detection();
    test_desktop_detection();
    
    std::cout << "\\n";
    if (g_failures == 0) {
        std::cout << "All tests passed!\\n";
        return 0;
    } else {
        std::cerr << g_failures << " test(s) failed.\\n";
        return 1;
    }
}