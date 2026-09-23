// Rebuntu — Operational Directory Layout Tests (Phase 2.9)
//
// Test the directory management:
//   - DirectoryType enum and conversions
//   - Canonical path resolution for system/user/session scopes
//   - Directory discovery and state verification

#include <system/environment/directories.hpp>

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <filesystem>

namespace {
int g_failures = 0;
#define CHECK(cond) do { if (!(cond)) { std::cerr << "CHECK failed: " << #cond << " (line " << __LINE__ << ")\\n"; ++g_failures; } } while(0)
}  // namespace

void test_directory_type_to_string() {
    using rebuntu::environment::directories::to_string;
    using rebuntu::environment::directories::DirectoryType;
    
    CHECK(to_string(DirectoryType::kConfig) == "config");
    CHECK(to_string(DirectoryType::kState) == "state");
    CHECK(to_string(DirectoryType::kCache) == "cache");
    CHECK(to_string(DirectoryType::kData) == "data");
    CHECK(to_string(DirectoryType::kRuntime) == "runtime");
    CHECK(to_string(DirectoryType::kTemp) == "temp");
    CHECK(to_string(DirectoryType::kLog) == "log");
}

void test_system_path_helpers() {
    using rebuntu::environment::directories::get_system_config_dir;
    using rebuntu::environment::directories::get_system_state_dir;
    using rebuntu::environment::directories::get_system_cache_dir;
    using rebuntu::environment::directories::get_system_runtime_dir;
    using rebuntu::environment::directories::get_system_data_dir;
    using rebuntu::environment::directories::get_system_log_dir;
    
    auto config = get_system_config_dir();
    CHECK(config.string().find("/etc/rebuntu") != std::string::npos);
    
    auto state = get_system_state_dir();
    CHECK(state.string().find("/var/lib/rebuntu") != std::string::npos);
    
    auto cache = get_system_cache_dir();
    CHECK(cache.string().find("/var/cache/rebuntu") != std::string::npos);
    
    auto runtime = get_system_runtime_dir();
    CHECK(runtime.string().find("/run/rebuntu") != std::string::npos);
    
    auto data = get_system_data_dir();
    CHECK(data.string().find("/usr/share/rebuntu") != std::string::npos);
    
    auto log = get_system_log_dir();
    CHECK(log.string().find("/var/log/rebuntu") != std::string::npos);
}

void test_user_path_helpers() {
    using rebuntu::environment::directories::get_user_config_dir;
    using rebuntu::environment::directories::get_user_state_dir;
    using rebuntu::environment::directories::get_user_cache_dir;
    using rebuntu::environment::directories::get_user_data_dir;
    
    auto home = std::filesystem::path("/home/testuser");
    
    auto config = get_user_config_dir(home);
    CHECK(config.string().find("/.config/rebuntu") != std::string::npos);
    
    auto state = get_user_state_dir(home);
    CHECK(state.string().find("/.local/state/rebuntu") != std::string::npos);
    
    auto cache = get_user_cache_dir(home);
    CHECK(cache.string().find("/.cache/rebuntu") != std::string::npos);
    
    auto data = get_user_data_dir(home);
    CHECK(data.string().find("/.local/share/rebuntu") != std::string::npos);
}

void test_directory_discovery() {
    using rebuntu::environment::directories::discover_directory;
    using rebuntu::environment::directories::DirectoryInfo;
    
    // Create a temporary directory
    std::error_code ec;
    auto temp_dir = std::filesystem::temp_directory_path() / "rebuntu-test-dir";
    std::filesystem::create_directories(temp_dir, ec);
    
    if (!ec) {
        auto info = discover_directory(temp_dir);
        CHECK(info.exists == true);
        CHECK(info.is_accessible == true);
        
        // Cleanup
        std::filesystem::remove_all(temp_dir, ec);
    }
}

void test_ensure_directory() {
    using rebuntu::environment::directories::ensure_directory;
    
    std::error_code ec;
    auto temp_dir = std::filesystem::temp_directory_path() / "rebuntu-test-ensure";
    
    // Clean up if exists from previous runs
    std::filesystem::remove_all(temp_dir, ec);
    
    auto result = ensure_directory(temp_dir, geteuid(), getgid(), 0755, true);
    CHECK(result.is_success());
    
    // Test idempotency - second call should succeed with kAlreadyExists
    auto result2 = ensure_directory(temp_dir, geteuid(), getgid(), 0755, true);
    CHECK(result2.status == rebuntu::environment::directories::DirectoryOperationStatus::kAlreadyExists);
    
    // Cleanup
    std::filesystem::remove_all(temp_dir, ec);
}

void test_scope_policies() {
    using rebuntu::environment::directories::get_directory_policy;
    using rebuntu::environment::directories::get_scope_policies;
    using rebuntu::environment::scope::ExecutionScope;
    
    auto system_policies = get_scope_policies(ExecutionScope::kSystem);
    CHECK(!system_policies.empty());
    
    // Check that config policy for system has correct FHS section
    auto config_policy = get_directory_policy(
        rebuntu::environment::directories::DirectoryType::kConfig,
        ExecutionScope::kSystem);
    CHECK(config_policy.fhs_section.find("/etc") != std::string_view::npos);
}

int main() {
    using rebuntu::environment::scope::ExecutionScope;
    
    std::cout << "Testing Operational Directory Layout (Phase 2.9)...\\n";
    
    test_directory_type_to_string();
    test_system_path_helpers();
    test_user_path_helpers();
    test_directory_discovery();
    test_ensure_directory();
    test_scope_policies();
    
    // Summary
    std::cout << "\\nDirectory Tests Complete\\n";
    if (g_failures > 0) {
        std::cerr << g_failures << " test(s) failed.\\n";
        return 1;
    }
    std::cout << "All tests passed.\\n";
    return 0;
}