// rebuntu::infrastructure::jenkins_cli — Unit Tests (Phase 3.9)
//
// Test the Jenkins CI provider contracts and implementation.

#include <system/infrastructure/jenkins.hpp>
#include <system/core/contracts.hpp>

#include <iostream>
#include <string>
#include <chrono>

using namespace rebuntu::infrastructure;
using namespace rebuntu::core;

namespace {

int g_failures = 0;
#define CHECK(cond)                                                              \
    do {                                                                         \
        if (!(cond)) {                                                           \
            std::cerr << "CHECK failed: " #cond " (line " << __LINE__           \
                      << ")\n";                                                  \
            ++g_failures;                                                        \
        }                                                                        \
    } while (0)

void test_jenkins_provider_id_creation() {
    JenkinsProviderId id{"jenkins-cli"};
    CHECK(id.value == "jenkins-cli");
    CHECK(std::string(id) == "jenkins-cli");
}

void test_jenkins_provider_id_equality() {
    JenkinsProviderId a{"jenkins-cli"};
    JenkinsProviderId b{"jenkins-cli"};
    JenkinsProviderId c{"other-provider"};
    
    CHECK(a == b);
    CHECK(!(a == c));
    CHECK(a != c);
}

void test_jenkins_build_status_to_string() {
    using namespace rebuntu::infrastructure;
    
    CHECK(to_string(JenkinsBuildStatus::kQueued) == "queued");
    CHECK(to_string(JenkinsBuildStatus::kStarted) == "started");
    CHECK(to_string(JenkinsBuildStatus::kRunning) == "running");
    CHECK(to_string(JenkinsBuildStatus::kAborted) == "aborted");
    CHECK(to_string(JenkinsBuildStatus::kSuccess) == "success");
    CHECK(to_string(JenkinsBuildStatus::kFailed) == "failed");
    CHECK(to_string(JenkinsBuildStatus::kNotBuilt) == "not_built");
    CHECK(to_string(JenkinsBuildStatus::kUnknown) == "unknown");
}

void test_jenkins_result_success() {
    auto result = JenkinsResult::success();
    CHECK(result.status == SemanticStatus::kSuccess);
    CHECK(!result.build_info.has_value());
    CHECK(result.artifacts.empty());
    CHECK(!result.error.has_value());
}

void test_jenkins_result_success_with_build() {
    JenkinsBuildInfo info;
    info.job_name = "test-job";
    info.build_number = 42;
    info.status = JenkinsBuildStatus::kSuccess;
    
    auto result = JenkinsResult::success_with_build(info);
    CHECK(result.status == SemanticStatus::kSuccess);
    CHECK(result.build_info.has_value());
    CHECK(result.build_info->job_name == "test-job");
    CHECK(result.build_info->build_number == 42);
}

void test_jenkins_result_success_with_artifacts() {
    std::vector<JenkinsArtifactInfo> artifacts = {
        {"artifact1.jar", std::nullopt, std::nullopt},
        {"artifact2.war", std::nullopt, std::nullopt}
    };
    
    auto result = JenkinsResult::success_with_artifacts(artifacts);
    CHECK(result.status == SemanticStatus::kSuccess);
    CHECK(result.artifacts.size() == 2u);
    CHECK(result.artifacts[0].filename == "artifact1.jar");
}

void test_jenkins_result_failure() {
    auto result = JenkinsResult::failure("E_TEST", "test error message");
    CHECK(result.status == SemanticStatus::kFailure);
    CHECK(result.error.has_value());
    CHECK(result.error->code == "E_TEST");
    CHECK(result.error->message.find("test error message") != std::string::npos);
}

void test_jenkins_result_unavailable() {
    auto result = JenkinsResult::unavailable("Jenkins not installed");
    CHECK(result.status == SemanticStatus::kUnknown);
    CHECK(result.error.has_value());
    CHECK(result.error->code == "E_JENKINS_UNAVAILABLE");
}

void test_jenkins_provider_config_default() {
    jenkins_cli::Config config;
    CHECK(config.cpu_only == true);  // CPU-only by default
    CHECK(!config.cli_path.has_value());
    CHECK(!config.server_url.has_value());
}

void test_jenkins_result_hash_works() {
    JenkinsProviderId id{"jenkins-cli"};
    std::hash<JenkinsProviderId> hasher;
    auto hash = hasher(id);
    CHECK(hash != 0);  // Just verify it produces a hash
}

}  // namespace

int main(int argc, char** argv) {
    test_jenkins_provider_id_creation();
    test_jenkins_provider_id_equality();
    test_jenkins_build_status_to_string();
    test_jenkins_result_success();
    test_jenkins_result_success_with_build();
    test_jenkins_result_success_with_artifacts();
    test_jenkins_result_failure();
    test_jenkins_result_unavailable();
    test_jenkins_provider_config_default();
    test_jenkins_result_hash_works();
    
    std::cout << "jenkins_provider tests: ";
    if (g_failures == 0) {
        std::cout << "PASS\n";
        return 0;
    } else {
        std::cout << "FAIL (" << g_failures << " failures)\n";
        return 1;
    }
}