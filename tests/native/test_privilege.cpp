// Rebuntu — Privilege & Elevation Tests (Phase 2.4)
//
// Test the privilege and elevation model:
//   - UID/GID discovery
//   - Elevation capability detection
//   - Scope resolution (system vs user)

#include <observation/environment/privilege.hpp>

#include <iostream>
#include <cstdlib>
#include <unistd.h>

namespace {
int g_failures = 0;
#define CHECK(cond) do { if (!(cond)) { std::cerr << "CHECK failed: " << #cond << " (line " << __LINE__ << ")\\n"; ++g_failures; } } while(0)
}  // namespace

int main() {
    using rebuntu::environment::privilege::discover_privilege;
    using rebuntu::environment::privilege::discover_scope;
    using rebuntu::environment::privilege::build_current_process_identity;
    using rebuntu::environment::privilege::get_real_uid_when_elevated;
    using rebuntu::environment::privilege::is_running_under_sudo;
    using rebuntu::environment::privilege::get_sudo_user_from_env;
    
    std::cout << "Testing privilege and elevation discovery...\\n";
    
    // Test 1: Discover privilege state
    auto info = discover_privilege();
    CHECK(info.status == 1);  // DiscoveryStatus::kKnown (represented as int)
    CHECK(info.effective_uid == geteuid());
    
    std::cout << "  - Privilege discovery: effective_uid=" << info.effective_uid << ", is_root=" << info.is_root << "\\n";
    
    // Test 2: Detect root state
    if (info.is_root) {
        CHECK(info.elevation == rebuntu::environment::privilege::ElevationCapability::kAlreadyElevated);
        std::cout << "  - Running as root, elevation=" << static_cast<int>(info.elevation) << "\\n";
    } else {
        std::cout << "  - Not running as root, elevation=" << static_cast<int>(info.elevation) << "\\n";
    }
    
    // Test 3: Discover scope
    auto scope = discover_scope(info);
    if (info.is_root) {
        CHECK(scope.scope == rebuntu::environment::privilege::InstallationScope::kSystem);
        std::cout << "  - Scope for root: system\\n";
    } else {
        CHECK(scope.scope == rebuntu::environment::privilege::InstallationScope::kUser);
        std::cout << "  - Scope for non-root: user\\n";
    }
    
    // Test 4: Build process identity
    auto ident = build_current_process_identity();
    CHECK(ident.real_uid == getuid());
    CHECK(ident.effective_uid == geteuid());
    std::cout << "  - Process identity built successfully\\n";
    
    // Test 5: get_real_uid_when_elevated()
    uid_t ruid = getuid();
    uid_t euid = geteuid();
    uid_t result = get_real_uid_when_elevated();
    
    if (euid == 0 && ruid != 0) {
        CHECK(result == ruid);
        std::cout << "  - Elevated: real_uid=" << result << "\\n";
    } else {
        CHECK(result == euid);
        std::cout << "  - Not elevated: uid=" << result << "\\n";
    }
    
    // Test 6: is_running_under_sudo()
    bool sudo_result = is_running_under_sudo();
    const char* sudo_user = std::getenv("SUDO_USER");
    if (sudo_user != nullptr && euid == 0 && ruid != 0) {
        CHECK(sudo_result == true);
        std::cout << "  - Running under sudo\\n";
    } else {
        std::cout << "  - SUDO_USER=" << (sudo_user ? sudo_user : "nullptr") << ", result=" << sudo_result << "\\n";
    }
    
    // Test 7: get_sudo_user_from_env()
    auto sudo_user_result = get_sudo_user_from_env();
    if (sudo_user != nullptr) {
        CHECK(sudo_user_result.has_value());
        CHECK(sudo_user_result.value() == std::string(sudo_user));
        std::cout << "  - SUDO_USER in env: " << sudo_user_result.value() << "\\n";
    } else {
        std::cout << "  - No SUDO_USER in environment\\n";
    }
    
    // Test 8: Scope context verification
    auto scope2 = discover_scope(info);
    if (info.is_root) {
        CHECK(scope2.is_root == true);
        if (info.real_uid.has_value()) {
            std::cout << "  - Original UID for sudo context: " << info.real_uid.value() << "\\n";
        }
    } else {
        CHECK(scope2.is_root == false);
        const char* home = std::getenv("HOME");
        if (home) {
            CHECK(scope2.home_dir.has_value());
            CHECK(scope2.home_dir.value() == std::string(home));
            std::cout << "  - Home directory: " << scope2.home_dir.value() << "\\n";
        }
    }
    
    // Summary
    std::cout << "\\nPrivilege & Elevation Tests Complete\\n";
    if (g_failures > 0) {
        std::cerr << g_failures << " test(s) failed.\\n";
        return 1;
    }
    std::cout << "All tests passed.\\n";
    return 0;
}