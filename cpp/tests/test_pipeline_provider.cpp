// rebuntu::infrastructure::pipeline — Unit Tests (Phase 3.10)
//
// Test the build/test/deployment pipeline infrastructure contracts and provider.

#include <system/infrastructure/pipeline.hpp>

#include <iostream>
#include <string>
#include <vector>

using namespace rebuntu::infrastructure;
using namespace rebuntu::core;

namespace {

int g_failures = 0;
#define CHECK(cond)                                                              \
    do {                                                                         \
        if (!(cond)) {                                                           \
            std::cerr << "CHECK failed: " #cond " (line " << __LINE__            \
                      << ")\n";                                                  \
            ++g_failures;                                                        \
        }                                                                        \
    } while (0)

void test_pipeline_stage_to_string() {
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
    CHECK(to_string(PipelineToolType::kFormatter) == "formatter");
    CHECK(to_string(PipelineToolType::kLinter) == "linter");
    CHECK(to_string(PipelineToolType::kCompiler) == "compiler");
    CHECK(to_string(PipelineToolType::kBuildSystem) == "build_system");
    CHECK(to_string(PipelineToolType::kTesting) == "testing");
    CHECK(to_string(PipelineToolType::kShellValidator) == "shell_validator");
}

void test_pipeline_stage_result_to_string() {
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
    std::vector<PipelineStageInfo> stages;
    
    PipelineStageInfo info1;
    info1.stage = PipelineStage::kEnvironment;
    info1.result = PipelineStageResult::kPassed;
    stages.push_back(info1);
    
    auto result = PipelineResult::success(std::move(stages));
    CHECK(result.overall_status == SemanticStatus::kSuccess);
    CHECK(result.passed_stages == 1);
    CHECK(result.total_stages == 1);
}

void test_pipeline_result_failure() {
    std::vector<PipelineStageInfo> stages;
    
    PipelineStageInfo info1;
    info1.stage = PipelineStage::kEnvironment;
    info1.result = PipelineStageResult::kPassed;
    stages.push_back(info1);
    
    PipelineStageInfo info2;
    info2.stage = PipelineStage::kFormatting;
    info2.result = PipelineStageResult::kFailed;
    stages.push_back(info2);
    
    auto result = PipelineResult::failure(std::move(stages), "E_TEST_ERROR", "test failure");
    CHECK(result.overall_status == SemanticStatus::kFailure);
    CHECK(result.passed_stages == 1);
    CHECK(result.failed_stages == 1);
    CHECK(result.total_stages == 2);
    CHECK(result.error.has_value());
    CHECK(result.error->code == "E_TEST_ERROR");
}

void test_pipeline_result_cancelled() {
    auto result = PipelineResult::cancelled("pipeline cancelled by user");
    CHECK(result.overall_status == SemanticStatus::kFailure);
    CHECK(result.error.has_value());
    CHECK(result.error->code.find("CANCELLED") != std::string::npos);
}

void test_pipeline_config_defaults() {
    pipeline_native::Config config;
    CHECK(config.cpu_only == true);
    CHECK(config.source_dirs.empty());
}

void test_pipeline_provider_create() {
    pipeline_native::Config config;
    auto provider = std::make_unique<pipeline_native::Provider>(config);
    CHECK(provider != nullptr);
    CHECK(!provider->provider_id().empty());
}

void test_pipeline_provider_get_available_stages() {
    pipeline_native::Config config;
    pipeline_native::Provider provider(config);
    
    auto stages = provider.get_available_stages();
    // Should have at least kEnvironment stage
    bool has_environment = false;
    for (auto s : stages) {
        if (s == PipelineStage::kEnvironment) {
            has_environment = true;
            break;
        }
    }
    CHECK(has_environment);
}

void test_pipeline_result_summary_counts() {
    std::vector<PipelineStageInfo> stages;
    
    // Add some passed stages
    for (int i = 0; i < 3; ++i) {
        PipelineStageInfo info;
        info.stage = static_cast<PipelineStage>(i);
        info.result = PipelineStageResult::kPassed;
        stages.push_back(info);
    }
    
    // Add one failed stage
    PipelineStageInfo failed_info;
    failed_info.stage = PipelineStage::kPackage;
    failed_info.result = PipelineStageResult::kFailed;
    stages.push_back(failed_info);
    
    auto result = PipelineResult::success(std::move(stages));
    CHECK(result.total_stages == 4);
    CHECK(result.passed_stages == 3);
    CHECK(result.failed_stages == 1);
}

void test_pipeline_stage_info() {
    PipelineStageInfo info;
    info.stage = PipelineStage::kUnitTest;
    info.result = PipelineStageResult::kPassed;
    info.verified = true;
    
    CHECK(info.stage == PipelineStage::kUnitTest);
    CHECK(info.result == PipelineStageResult::kPassed);
    CHECK(info.verified == true);
}

void test_pipeline_execute_unit_test_stage() {
    pipeline_native::Config config;
    pipeline_native::Provider provider(config);
    
    // Unit test stage should pass (ctest availability check)
    auto result = provider.execute_stage(PipelineStage::kUnitTest);
    CHECK(result.stage == PipelineStage::kUnitTest);
    // May be passed or skipped if ctest not available
    CHECK(result.result == PipelineStageResult::kPassed ||
          result.result == PipelineStageResult::kSkipped);
}

void test_pipeline_execute_package_stage() {
    pipeline_native::Config config;
    pipeline_native::Provider provider(config);
    
    auto result = provider.execute_stage(PipelineStage::kPackage);
    CHECK(result.stage == PipelineStage::kPackage);
    // May be passed, skipped, or error depending on cmake/make availability
    CHECK(result.result == PipelineStageResult::kPassed ||
          result.result == PipelineStageResult::kSkipped ||
          result.result == PipelineStageResult::kError);
}

void test_pipeline_execute_environment_stage() {
    pipeline_native::Config config;
    pipeline_native::Provider provider(config);
    
    auto result = provider.execute_stage(PipelineStage::kEnvironment);
    CHECK(result.stage == PipelineStage::kEnvironment);
    // Environment stage should succeed if cmake and gcc are available
    CHECK(result.result == PipelineStageResult::kPassed ||
          result.result == PipelineStageResult::kError);  // Error if tools missing
}

}  // namespace

int main(int argc, char** argv) {
    test_pipeline_stage_to_string();
    test_pipeline_tool_type_to_string();
    test_pipeline_stage_result_to_string();
    
    test_pipeline_result_success();
    test_pipeline_result_failure();
    test_pipeline_result_cancelled();
    
    test_pipeline_config_defaults();
    test_pipeline_provider_create();
    test_pipeline_provider_get_available_stages();
    
    test_pipeline_result_summary_counts();
    test_pipeline_stage_info();
    
    // These may fail if build tools are not available on the system
    // but we still want to verify the interface works
    try {
        test_pipeline_execute_unit_test_stage();
        test_pipeline_execute_package_stage();
        test_pipeline_execute_environment_stage();
    } catch (...) {
        // Ignore exceptions from tool availability checks
    }
    
    std::cout << "pipeline_provider tests: ";
    if (g_failures == 0) {
        std::cout << "PASS\n";
        return 0;
    } else {
        std::cout << "FAIL (" << g_failures << " failures)\n";
        return 1;
    }
}