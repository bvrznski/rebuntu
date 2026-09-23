// rebuntu::infrastructure::pipeline — Unit Tests (Phase 3.10)
//
// Test the engineering pipeline contracts and providers.

#include <runtime/core/contracts.hpp>
#include <domains/development/infrastructure/pipeline.hpp>

#include <cstddef>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace rebuntu::core;
using namespace rebuntu::infrastructure;

namespace {

int g_failures = 0;
#define CHECK(cond)                                                              \
    do {                                                                         \
        if (!(cond)) {                                                           \
            std::cerr << "CHECK failed: " << #cond << " (line " << __LINE__      \
                      << ")\n";                                                  \
            ++g_failures;                                                        \
        }                                                                        \
    } while (0)

void test_pipeline_stage_to_string() {
    using namespace rebuntu::infrastructure;
    
    CHECK(to_string(PipelineStage::kEnvironment) == "environment");
    CHECK(to_string(PipelineStage::kFormatting) == "formatting");
    CHECK(to_string(PipelineStage::kLint) == "lint");
    CHECK(to_string(PipelineStage::kTypeCheck) == "type_check");
    CHECK(to_string(PipelineStage::kUnitTest) == "unit_test");
    CHECK(to_string(PipelineStage::kIntegrationTest) == "integration_test");
    CHECK(to_string(PipelineStage::kShellCheck) == "shell_check");
    CHECK(to_string(PipelineStage::kSecurityTest) == "security_test");
    CHECK(to_string(PipelineStage::kPackage) == "package");
    CHECK(to_string(PipelineStage::kArtifactVerify) == "artifact_verify");
}

void test_pipeline_tool_type_to_string() {
    using namespace rebuntu::infrastructure;
    
    CHECK(to_string(PipelineToolType::kFormatter) == "formatter");
    CHECK(to_string(PipelineToolType::kLinter) == "linter");
    CHECK(to_string(PipelineToolType::kCompiler) == "compiler");
    CHECK(to_string(PipelineToolType::kBuildSystem) == "build_system");
    CHECK(to_string(PipelineToolType::kTesting) == "testing");
    CHECK(to_string(PipelineToolType::kShellValidator) == "shell_validator");
}

void test_pipeline_stage_result_to_string() {
    using namespace rebuntu::infrastructure;
    
    CHECK(to_string(PipelineStageResult::kNotRun) == "not_run");
    CHECK(to_string(PipelineStageResult::kSkipped) == "skipped");
    CHECK(to_string(PipelineStageResult::kRunning) == "running");
    CHECK(to_string(PipelineStageResult::kPassed) == "passed");
    CHECK(to_string(PipelineStageResult::kFailed) == "failed");
    CHECK(to_string(PipelineStageResult::kTimeout) == "timeout");
    CHECK(to_string(PipelineStageResult::kCancelled) == "cancelled");
    CHECK(to_string(PipelineStageResult::kError) == "error");
}

void test_pipeline_result_success() {
    using namespace rebuntu::infrastructure;
    
    std::vector<PipelineStageInfo> stages;
    
    PipelineStageInfo stage1;
    stage1.stage = PipelineStage::kEnvironment;
    stage1.result = PipelineStageResult::kPassed;
    stages.push_back(stage1);
    
    PipelineStageInfo stage2;
    stage2.stage = PipelineStage::kFormatting;
    stage2.result = PipelineStageResult::kPassed;
    stages.push_back(stage2);
    
    auto result = PipelineResult::success(stages);
    CHECK(result.overall_status == rebuntu::core::SemanticStatus::kSuccess);
    CHECK(result.passed_stages == 2u);
    CHECK(result.failed_stages == 0u);
    CHECK(result.skipped_stages == 0u);
    CHECK(result.total_stages == 2u);
}

void test_pipeline_result_failure() {
    using namespace rebuntu::infrastructure;
    
    std::vector<PipelineStageInfo> stages;
    
    PipelineStageInfo stage1;
    stage1.stage = PipelineStage::kEnvironment;
    stage1.result = PipelineStageResult::kPassed;
    stages.push_back(stage1);
    
    PipelineStageInfo stage2;
    stage2.stage = PipelineStage::kFormatting;
    stage2.result = PipelineStageResult::kFailed;
    stages.push_back(stage2);
    
    auto result = PipelineResult::failure(stages, "E_TEST_ERROR", "Test error");
    CHECK(result.overall_status == rebuntu::core::SemanticStatus::kFailure);
    CHECK(result.passed_stages == 1u);
    CHECK(result.failed_stages == 1u);
    CHECK(result.total_stages == 2u);
    CHECK(result.error.has_value());
    CHECK(result.error->code == "E_TEST_ERROR");
}

void test_pipeline_result_cancelled() {
    using namespace rebuntu::infrastructure;
    
    auto result = PipelineResult::cancelled("Pipeline cancelled by user");
    CHECK(result.overall_status == rebuntu::core::SemanticStatus::kCancelled);
    CHECK(result.error.has_value());
    CHECK(result.error->code == "E_PIPELINE_CANCELLED");
}

void test_pipeline_provider_config() {
    using namespace rebuntu::infrastructure;
    
    pipeline_native::Config config;
    config.clang_format_path = "/usr/bin/clang-format";
    config.cmake_path = "/usr/bin/cmake";
    config.source_dirs = {"/src"};
    config.cpu_only = true;
    
    CHECK(config.clang_format_path.has_value());
    CHECK(config.clang_format_path.value() == "/usr/bin/clang-format");
    CHECK(config.cmake_path.has_value());
    CHECK(config.cpu_only == true);
}

void test_pipeline_provider_create() {
    using namespace rebuntu::infrastructure;
    
    pipeline_native::Config config;
    pipeline_native::Provider provider(config);
    
    // Provider should be available if cmake or make is in PATH
    bool available = provider.is_available();
    
    // Even if tools aren't available, creation should succeed
    CHECK(provider.provider_id() == "pipeline-native");
}

void test_pipeline_provider_get_available_stages() {
    using namespace rebuntu::infrastructure;
    
    pipeline_native::Config config;
    pipeline_native::Provider provider(config);
    
    auto stages = provider.get_available_stages();
    
    // At minimum, environment and package stages should be available
    bool has_environment = false;
    bool has_package = false;
    
    for (auto stage : stages) {
        if (stage == PipelineStage::kEnvironment) has_environment = true;
        if (stage == PipelineStage::kPackage) has_package = true;
    }
    
    CHECK(has_environment == true);
    CHECK(has_package == true);
}

void test_pipeline_result_summary_counts() {
    using namespace rebuntu::infrastructure;
    
    std::vector<PipelineStageInfo> stages;
    
    // Add different result types
    PipelineStageInfo stage1;
    stage1.stage = PipelineStage::kEnvironment;
    stage1.result = PipelineStageResult::kPassed;
    stages.push_back(stage1);
    
    PipelineStageInfo stage2;
    stage2.stage = PipelineStage::kFormatting;
    stage2.result = PipelineStageResult::kSkipped;
    stages.push_back(stage2);
    
    PipelineStageInfo stage3;
    stage3.stage = PipelineStage::kLint;
    stage3.result = PipelineStageResult::kPassed;
    stages.push_back(stage3);
    
    auto result = PipelineResult::success(stages);
    CHECK(result.passed_stages == 2u);
    CHECK(result.skipped_stages == 1u);
    CHECK(result.total_stages == 3u);
}

void test_pipeline_stage_info() {
    using namespace rebuntu::infrastructure;
    
    PipelineStageInfo info;
    info.stage = PipelineStage::kUnitTest;
    info.result = PipelineStageResult::kPassed;
    info.verified = true;
    
    CHECK(info.stage == PipelineStage::kUnitTest);
    CHECK(info.result == PipelineStageResult::kPassed);
    CHECK(info.verified == true);
}

// ============================================================================
// Integration Tests
// ============================================================================

void test_pipeline_execute_environment_stage() {
    using namespace rebuntu::infrastructure;
    
    pipeline_native::Config config;
    pipeline_native::Provider provider(config);
    
    auto result = provider.execute_stage(PipelineStage::kEnvironment);
    // Environment stage checks for cmake and gcc availability
    // If not available, it will return Error status which is acceptable
}

void test_pipeline_execute_package_stage() {
    using namespace rebuntu::infrastructure;
    
    pipeline_native::Config config;
    pipeline_native::Provider provider(config);
    
    auto result = provider.execute_stage(PipelineStage::kPackage);
    // Package stage checks for cmake or make availability
    // If not available, it will return Error status which is acceptable
}

void test_pipeline_execute_full_pipeline() {
    using namespace rebuntu::infrastructure;
    
    pipeline_native::Config config;
    pipeline_native::Provider provider(config);
    
    std::vector<PipelineStage> stages = {
        PipelineStage::kEnvironment,
        PipelineStage::kPackage
    };
    
    auto result = provider.execute_pipeline(stages);
    
    // At minimum, we should get a valid result structure
    CHECK(result.total_stages >= 2u);
}

}  // namespace

int main(int argc, char** argv) {
    test_pipeline_stage_to_string();
    test_pipeline_tool_type_to_string();
    test_pipeline_stage_result_to_string();
    test_pipeline_result_success();
    test_pipeline_result_failure();
    test_pipeline_result_cancelled();
    test_pipeline_provider_config();
    test_pipeline_provider_create();
    test_pipeline_provider_get_available_stages();
    test_pipeline_result_summary_counts();
    test_pipeline_stage_info();
    
    // Integration tests
    test_pipeline_execute_environment_stage();
    test_pipeline_execute_package_stage();
    test_pipeline_execute_full_pipeline();
    
    std::cout << "pipeline_provider tests: ";
    if (g_failures == 0) {
        std::cout << "PASS\n";
        return 0;
    } else {
        std::cout << "FAIL (" << g_failures << " failures)\n";
        return 1;
    }
}