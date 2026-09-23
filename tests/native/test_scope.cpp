// Rebuntu — System/User/Session Scope Tests (Phase 2.7)
//
// Test the scope model:
//   - ExecutionScope enum and conversions
//   - XDG Base Directory resolution
//   - ScopeContext discovery
//   - Cross-scope mediation

#include <observation/environment/scope.hpp>

#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <sys/types.h>

namespace {
int g_failures = 0;
#define CHECK(cond) do { if (!(cond)) { std::cerr << "CHECK failed: " << #cond << " (line " << __LINE__ << ")\\n"; ++g_failures; } } while(0)
}  // namespace

int main() {
    using rebuntu::environment::scope::ExecutionScope;
    using rebuntu::environment::scope::to_string;
    using rebuntu::environment::scope::discover_context;
    using rebuntu::environment::scope::mediate_cross_scope_request;
    using rebuntu::environment::scope::validate_path_for_scope;
    
    std::cout << "Testing System/User/Session Scope (Phase 2.7)...\\n";
    
    // Test 1: ExecutionScope enum to string conversion
    std::cout << "\\nTest 1: ExecutionScope enum values\\n";
    CHECK(to_string(ExecutionScope::kSystem) == "system");
    CHECK(to_string(ExecutionScope::kUser) == "user");
    CHECK(to_string(ExecutionScope::kSession) == "session");
    std::cout << "  - kSystem -> 'system'\\n";
    std::cout << "  - kUser -> 'user'\\n";
    std::cout << "  - kSession -> 'session'\\n";
    
    // Test 2: Discover current context
    std::cout << "\\nTest 2: discover_context()\\n";
    auto ctx = discover_context();
    CHECK(ctx.effective_uid == geteuid());
    std::cout << "  - effective_uid=" << ctx.effective_uid << "\\n";
    
    // Test 3: Scope resolution from privilege
    std::cout << "\\nTest 3: Scope based on UID\\n";
    if (ctx.is_root) {
        CHECK(ctx.scope == ExecutionScope::kSystem);
        std::cout << "  - Running as root -> System scope\\n";
    } else {
        CHECK(ctx.scope == ExecutionScope::kUser);
        std::cout << "  - Not running as root -> User scope\\n";
        
        // Check user-specific paths
        if (ctx.bin_path.has_value()) {
            std::cout << "  - bin_path: " << ctx.bin_path.value().string() << "\\n";
        }
    }
    
    // Test 4: XDG Base Directory resolution
    std::cout << "\\nTest 4: XDG base directories\\n";
    const char* xdg_config = std::getenv("XDG_CONFIG_HOME");
    if (xdg_config) {
        CHECK(ctx.xdg.config_home.has_value());
        std::cout << "  - XDG_CONFIG_HOME set: " << ctx.xdg.config_home.value().string() << "\\n";
    } else {
        // Without env var, should have fallback
        if (ctx.xdg.config_home.has_value()) {
            auto path = ctx.xdg.config_home.value().string();
            CHECK(path.find(".config") != std::string::npos);
            std::cout << "  - XDG_CONFIG_HOME fallback: " << path << "\\n";
        }
    }
    
    // Test 5: Cross-scope mediation
    std::cout << "\\nTest 5: mediate_cross_scope_request()\\n";
    
    // Same scope should be allowed
    auto result_same = mediate_cross_scope_request(ctx, ctx.scope);
    CHECK(result_same.action == rebuntu::environment::scope::CrossScopeAction::kAllow);
    std::cout << "  - Same scope request: ALLOW\\n";
    
    // User requesting system scope when not root should require elevation
    if (!ctx.is_root) {
        auto result_elevate = mediate_cross_scope_request(ctx, ExecutionScope::kSystem);
        CHECK(result_elevate.action == rebuntu::environment::scope::CrossScopeAction::kRequireElevation);
        std::cout << "  - User requesting system scope: REQUIRES_ELEVATION\\n";
    }
    
    // Session scope without XDG_RUNTIME_DIR should be denied
    if (!ctx.xdg.runtime_dir.has_value()) {
        auto result_session = mediate_cross_scope_request(ctx, ExecutionScope::kSession);
        CHECK(result_session.action == rebuntu::environment::scope::CrossScopeAction::kDeny);
        std::cout << "  - User requesting session scope (no XDG_RUNTIME_DIR): DENIED\\n";
    }
    
    // Test 6: Path validation
    std::cout << "\\nTest 6: validate_path_for_scope()\\n";
    
    auto system_result = validate_path_for_scope("/usr/bin/test", ExecutionScope::kSystem);
    CHECK(system_result.is_valid());
    std::cout << "  - /usr/bin/test for System scope: VALID\\n";
    
    // Test 7: System path helpers
    std::cout << "\\nTest 7: System path helpers\\n";
    auto sys_bin = rebuntu::environment::scope::get_system_bin_path();
    CHECK(sys_bin.string().find("/usr/bin") != std::string::npos);
    std::cout << "  - get_system_bin_path() -> " << sys_bin.string() << "\\n";
    
    auto sys_config = rebuntu::environment::scope::get_system_config_dir();
    CHECK(sys_config.string().find("/etc/rebuntu") != std::string::npos);
    std::cout << "  - get_system_config_dir() -> " << sys_config.string() << "\\n";
    
    // Test 8: User path helpers
    std::cout << "\\nTest 8: User path helpers\\n";
    auto home = rebuntu::environment::scope::XDGBases::get_user_home();
    if (!home.empty()) {
        auto user_bin = rebuntu::environment::scope::get_user_bin_path(home);
        CHECK(user_bin.string().find("/.local/bin") != std::string::npos);
        std::cout << "  - get_user_bin_path() -> " << user_bin.string() << "\\n";
        
        auto user_config = rebuntu::environment::scope::get_user_config_dir(home);
        CHECK(user_config.string().find("/.config/rebuntu") != std::string::npos);
        std::cout << "  - get_user_config_dir() -> " << user_config.string() << "\\n";
    }
    
    // Summary
    std::cout << "\\nScope Tests Complete\\n";
    if (g_failures > 0) {
        std::cerr << g_failures << " test(s) failed.\\n";
        return 1;
    }
    std::cout << "All tests passed.\\n";
    return 0;
}