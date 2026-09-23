// Rebuntu — Testing Infrastructure Tests (Phase 3.12)
//
// Test the testing infrastructure foundation:
//   * TestEnvironmentConfig - Configuration from environment variables
//   * TestCategory and TestClassification - Test metadata
//   * ProviderExecutorResult - Execution result types

#include <support/testing/contracts.hpp>

#include <iostream>
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

void test_test_category_to_string() {
    using rebuntu::testing::TestCategory;
    using rebuntu::testing::to_string;
    
    CHECK(std::strcmp(to_string(TestCategory::kUnit), "unit") == 0);
    CHECK(std::strcmp(to_string(TestCategory::kIntegration), "integration") == 0);
    CHECK(std::strcmp(to_string(TestCategory::kAdversarial), "adversarial") == 0);
    CHECK(std::strcmp(to_string(TestCategory::kPerformance), "performance") == 0);
    CHECK(std::strcmp(to_string(TestCategory::kSmoke), "smoke") == 0);
}

void test_classification_is_integration() {
    using rebuntu::testing::TestClassification;
    
    TestClassification c1;
    c1.categories = {rebuntu::testing::TestCategory::kUnit};
    CHECK(!c1.is_integration());
    
    TestClassification c2;
    c2.categories = {rebuntu::testing::TestCategory::kIntegration};
    CHECK(c2.is_integration());
    
    TestClassification c3;
    c3.categories = {
        rebuntu::testing::TestCategory::kUnit,
        rebuntu::testing::TestCategory::kIntegration
    };
    CHECK(c3.is_integration());
}

void test_classification_is_adversarial() {
    using rebuntu::testing::TestClassification;
    
    TestClassification c1;
    c1.categories = {rebuntu::testing::TestCategory::kUnit};
    CHECK(!c1.is_adversarial());
    
    TestClassification c2;
    c2.categories = {rebuntu::testing::TestCategory::kAdversarial};
    CHECK(c2.is_adversarial());
}

void test_environment_config_defaults() {
    using rebuntu::testing::TestEnvironmentConfig;
    
    TestEnvironmentConfig cfg;
    CHECK(cfg.temp_root.has_parent_path());
    CHECK(cfg.default_timeout_ms == std::chrono::seconds(30));
    CHECK(cfg.fast_simulation_mode == true);
    CHECK(cfg.host_mutation_allowed == false);
}

void test_environment_config_from_env() {
    using rebuntu::testing::TestEnvironmentConfig;
    
    // Save original env
    const char* orig_root = std::getenv(TestEnvironmentConfig::kEnvTempRoot);
    const char* orig_host = std::getenv(TestEnvironmentConfig::kEnvHostMutation);
    
    // Set temp root
    std::string temp_path = "/tmp/rebuntu-test-env";
    setenv(TestEnvironmentConfig::kEnvTempRoot, temp_path.c_str(), 1);
    setenv(TestEnvironmentConfig::kEnvHostMutation, "1", 1);
    setenv(TestEnvironmentConfig::kEnvFastSimulation, "0", 1);
    
    TestEnvironmentConfig cfg;
    cfg.load_from_environment();
    
    CHECK(cfg.temp_root.string().find("rebuntu-test-env") != std::string::npos);
    CHECK(cfg.host_mutation_allowed == true);
    CHECK(cfg.fast_simulation_mode == false);
    
    // Restore original env
    if (orig_root) {
        setenv(TestEnvironmentConfig::kEnvTempRoot, orig_root, 1);
    } else {
        unsetenv(TestEnvironmentConfig::kEnvTempRoot);
    }
    if (orig_host) {
        setenv(TestEnvironmentConfig::kEnvHostMutation, orig_host, 1);
    } else {
        unsetenv(TestEnvironmentConfig::kEnvHostMutation);
    }
}

void test_provider_execution_outcome_to_string() {
    using rebuntu::testing::ProviderExecutionOutcome;
    using rebuntu::testing::to_string;
    
    CHECK(std::strcmp(to_string(ProviderExecutionOutcome::kSuccess), "success") == 0);
    CHECK(std::strcmp(to_string(ProviderExecutionOutcome::kTimeout), "timeout") == 0);
    CHECK(std::strcmp(to_string(ProviderExecutionOutcome::kOutputLimit), "output_limit") == 0);
    CHECK(std::strcmp(to_string(ProviderExecutionOutcome::kExecutionFailed), "execution_failed") == 0);
    CHECK(std::strcmp(to_string(ProviderExecutionOutcome::kCancelled), "cancelled") == 0);
}

void test_provider_executor_result_success() {
    using rebuntu::testing::ProviderExecutorResult;
    
    ProviderExecutorResult result;
    CHECK(result.status == rebuntu::core::SemanticStatus::kUnknown);
    CHECK(!result.is_success());
}

void test_provider_executor_result_with_evidence() {
    using rebuntu::testing::ProviderExecutorResult;
    using rebuntu::core::Evidence;
    
    ProviderExecutorResult result;
    Evidence ev;
    ev.source = "provider";
    ev.value = "test";
    ev.captured_at = "2024-01-01T00:00:00Z";
    result.evidence.push_back(ev);
    
    CHECK(result.evidence.size() == 1);
    CHECK(result.evidence[0].source == "provider");
}

void test_temp_directory_creation() {
    using rebuntu::testing::TestContext;
    using rebuntu::testing::TestEnvironmentConfig;
    using rebuntu::environment::temp_files::TempFileStatus;
    
    TestEnvironmentConfig cfg;
    cfg.temp_root = "/tmp/rebuntu-test-ctx";
    
    // Clean up first
    std::filesystem::remove_all(cfg.temp_root);
    
    {
        TestContext ctx(cfg);
        
        // Create temp dir directly using temp_dir_ path (simpler approach)
        auto test_path = ctx.temp_root() / "test-subdir";
        std::error_code ec;
        std::filesystem::create_directory(test_path, ec);
        CHECK(!ec);
        CHECK(std::filesystem::exists(test_path));
    }
}

void test_fake_provider_exit() {
    using rebuntu::testing::FakeProvider;
    
    std::filesystem::path tmp_dir = "/tmp/rebuntu-fake-test";
    std::filesystem::create_directories(tmp_dir);
    
    auto provider_path = FakeProvider::create_exit_provider(tmp_dir, 42, "fake-exit-01");
    CHECK(!provider_path.empty());
    CHECK(std::filesystem::exists(provider_path));
    
    // Clean up
    std::filesystem::remove(provider_path);
    std::filesystem::remove(provider_path.parent_path() / (provider_path.stem().string() + ".cpp"));
}

void test_fake_provider_output() {
    using rebuntu::testing::FakeProvider;
    
    std::filesystem::path tmp_dir = "/tmp/rebuntu-fake-test";
    std::filesystem::create_directories(tmp_dir);
    
    auto provider_path = FakeProvider::create_output_provider(tmp_dir, "Hello World", 0, "fake-output-01");
    CHECK(!provider_path.empty());
    CHECK(std::filesystem::exists(provider_path));
    
    // Clean up
    std::filesystem::remove(provider_path);
    std::filesystem::remove(provider_path.parent_path() / (provider_path.stem().string() + ".cpp"));
}

void test_context_move_semantics() {
    using rebuntu::testing::TestContext;
    using rebuntu::testing::TestEnvironmentConfig;
    
    TestEnvironmentConfig cfg;
    cfg.temp_root = "/tmp/rebuntu-test-move";
    
    std::filesystem::remove_all(cfg.temp_root);
    
    TestContext ctx1(cfg);
    auto temp_path = ctx1.temp_root();
    
    // Move construct
    TestContext ctx2(std::move(ctx1));
    CHECK(ctx2.temp_root() == temp_path);
}

int main() {
    std::cout << "Testing Testing Infrastructure (Phase 3.12)...\n";
    
    test_test_category_to_string();
    test_classification_is_integration();
    test_classification_is_adversarial();
    test_environment_config_defaults();
    test_environment_config_from_env();
    test_provider_execution_outcome_to_string();
    test_provider_executor_result_success();
    test_provider_executor_result_with_evidence();
    test_temp_directory_creation();
    test_fake_provider_exit();
    test_fake_provider_output();
    test_context_move_semantics();
    
    std::cout << "\nTesting Infrastructure Tests Complete\n";
    if (g_failures > 0) {
        std::cerr << g_failures << " test(s) failed.\n";
        return 1;
    }
    std::cout << "All tests passed.\n";
    return 0;
}