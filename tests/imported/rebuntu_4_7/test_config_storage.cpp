// Rebuntu — Configuration & Secrets Locations Tests (Phase 2.11)
//
// Test the configuration file storage:
//   - Path resolution per scope (system/user)
//   - Environment-style file parsing (KEY=value)
//   - Atomic write with fsync/rename
//   - Secret redaction

#include <system/environment/config_storage.hpp>

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <filesystem>

namespace {
int g_failures = 0;
#define CHECK(cond) do { if (!(cond)) { std::cerr << "CHECK failed: " << #cond << " (line " << __LINE__ << ")\n"; ++g_failures; } } while(0)
}  // namespace

void test_path_resolution_system_scope() {
    using rebuntu::environment::config_storage::get_config_dir;
    using rebuntu::environment::scope::ScopeContext;
    
    // System scope for root
    ScopeContext ctx;
    ctx.is_root = true;
    ctx.effective_uid = 0;
    
    auto config_dir = get_config_dir(ctx);
    CHECK(config_dir.string().find("/etc/rebuntu") != std::string::npos);
}

void test_path_resolution_user_scope() {
    using rebuntu::environment::config_storage::get_config_dir;
    using rebuntu::environment::scope::ScopeContext;
    
    // User scope for non-root
    ScopeContext ctx;
    ctx.is_root = false;
    ctx.effective_uid = 1000;
    const char* home_env = std::getenv("HOME");
    if (home_env) {
        auto home_path = std::filesystem::path(home_env);
        // For user scope, use XDG config path resolution from existing code
    // The config_dir is optional in ScopeContext - we'll test via scope module functions instead
    }
    
    auto config_dir = get_config_dir(ctx);
    CHECK(!config_dir.empty());
}

void test_file_path_generation() {
    using rebuntu::environment::config_storage::get_config_file_path;
    using rebuntu::environment::config_storage::ConfigFileFormat;
    using rebuntu::environment::scope::ScopeContext;
    
    ScopeContext ctx;
    ctx.is_root = false;
    // config_dir is optional - we'll use get_user_config_dir directly
    auto path = get_config_file_path(ctx, "test", ConfigFileFormat::kEnv);
    CHECK(!path.empty());
    CHECK(path.extension().string() == ".env");
}

void test_env_file_parsing() {
    using rebuntu::environment::config_storage::load_env_file;
    
    // Create a temporary file with env-style content
    std::error_code ec;
    auto temp_dir = std::filesystem::temp_directory_path();
    auto temp_file = temp_dir / "rebuntu-test-env.conf";
    
    // Clean up if exists from previous runs
    std::filesystem::remove(temp_file, ec);
    
    // Write test content
    {
        std::ofstream file(temp_file);
        file << "# Comment line\n";
        file << "KEY1=value1\n";
        file << "KEY2=\"quoted value\"\n";
        file << "KEY3=value with spaces\n";
    }
    
    auto result = load_env_file(temp_file);
    CHECK(result.is_success());
    CHECK(result.values.size() == 3);
    CHECK(result.values["KEY1"] == "value1");
    CHECK(result.values["KEY2"] == "quoted value");
    
    // Cleanup
    std::filesystem::remove(temp_file, ec);
}

void test_env_file_writing() {
    using rebuntu::environment::config_storage::save_env_file;
    using rebuntu::environment::config_storage::ConfigStorageOptions;
    
    std::error_code ec;
    auto temp_dir = std::filesystem::temp_directory_path();
    auto temp_file = temp_dir / "rebuntu-test-write.conf";
    
    // Clean up if exists
    std::filesystem::remove(temp_file, ec);
    
    std::map<std::string, std::string> values = {
        {"KEY1", "value1"},
        {"KEY2", "value with spaces"}
    };
    
    ConfigStorageOptions options;
    options.atomic_write = true;  // Test atomic write
    
    auto result = save_env_file(temp_file, values, options);
    CHECK(result.success);
    
    // Verify file was created
    CHECK(std::filesystem::exists(temp_file, ec));
    
    // Cleanup
    std::filesystem::remove(temp_file, ec);
}

void test_secret_redaction() {
    using rebuntu::environment::config_storage::get_redacted_values;
    
    std::map<std::string, std::string> values = {
        {"username", "alice"},
        {"password", "secret123"},
        {"api_key", "my-api-key"},
        {"normal_value", "hello"}
    };
    
    std::vector<std::string> secret_keys = {"password", "api_key"};
    
    auto redacted = get_redacted_values(values, secret_keys);
    
    CHECK(redacted["username"] == "alice");
    CHECK(redacted["password"] == "[REDACTED]");
    CHECK(redacted["api_key"] == "[REDACTED]");
    CHECK(redacted["normal_value"] == "hello");
}

void test_atomic_write() {
    using rebuntu::environment::config_storage::atomic_write_file;
    
    std::error_code ec;
    auto temp_dir = std::filesystem::temp_directory_path();
    auto target_file = temp_dir / "rebuntu-test-atomic.conf";
    
    // Clean up if exists
    std::filesystem::remove(target_file, ec);
    
    std::string content = "test content for atomic write\n";
    
    auto result = atomic_write_file(target_file, content, geteuid(), getgid(), 0644);
    CHECK(result.success);
    
    // Verify file was created with correct content
    CHECK(std::filesystem::exists(target_file, ec));
    
    std::ifstream file(target_file);
    std::string loaded_content((std::istreambuf_iterator<char>(file)),
                               std::istreambuf_iterator<char>());
    CHECK(loaded_content == content);
    
    // Cleanup
    std::filesystem::remove(target_file, ec);
}

void test_config_file_discovery() {
    using rebuntu::environment::config_storage::discover_config_file;
    
    std::error_code ec;
    auto temp_dir = std::filesystem::temp_directory_path();
    auto temp_file = temp_dir / "rebuntu-test-discover.conf";
    
    // Test with non-existent file
    auto result1 = discover_config_file(temp_file);
    CHECK(!result1.exists);
    
    // Create the file
    {
        std::ofstream file(temp_file);
        file << "test=value\n";
    }
    
    auto result2 = discover_config_file(temp_file);
    CHECK(result2.exists);
    CHECK(result2.is_valid);
    
    // Cleanup
    std::filesystem::remove(temp_file, ec);
}

int main() {
    using rebuntu::environment::scope::ExecutionScope;
    
    std::cout << "Testing Configuration & Secrets Locations (Phase 2.11)...\n";
    
    test_path_resolution_system_scope();
    test_path_resolution_user_scope();
    test_file_path_generation();
    test_env_file_parsing();
    test_env_file_writing();
    test_secret_redaction();
    test_atomic_write();
    test_config_file_discovery();
    
    // Summary
    std::cout << "\nPhase 2.11 Tests Complete\n";
    if (g_failures > 0) {
        std::cerr << g_failures << " test(s) failed.\n";
        return 1;
    }
    std::cout << "All tests passed.\n";
    return 0;
}