// rebuntu::infrastructure::docker_cli — Unit Tests (Phase 3.5)
//
// Test the Docker provider contracts and implementation.

#include <system/core/contracts.hpp>
#include <system/infrastructure/docker.hpp>

#include <cstddef>
#include <iostream>
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

void test_docker_container_state_to_string() {
    using namespace rebuntu::infrastructure;

    CHECK(to_string(DockerContainerState::kCreated) == "created");
    CHECK(to_string(DockerContainerState::kRunning) == "running");
    CHECK(to_string(DockerContainerState::kPaused) == "paused");
    CHECK(to_string(DockerContainerState::kRestarting) == "restarting");
    CHECK(to_string(DockerContainerState::kExited) == "exited");
    CHECK(to_string(DockerContainerState::kDead) == "dead");
    CHECK(to_string(DockerContainerState::kUnknown) == "unknown");
}

void test_docker_result_success() {
    auto result = DockerResult::success();
    CHECK(result.status == SemanticStatus::kSuccess);
    CHECK(!result.error.has_value());
}

void test_docker_result_success_with_containers() {
    std::vector<DockerContainerInfo> containers;
    auto info = DockerContainerInfo{};
    info.id = "abc123";
    info.name = "test-container";
    containers.push_back(info);

    auto result = DockerResult::success_with_containers(containers);
    CHECK(result.status == SemanticStatus::kSuccess);
    CHECK(!result.error.has_value());
    CHECK(result.containers.size() == 1u);
    CHECK(result.containers[0].id == "abc123");
}

void test_docker_result_success_with_images() {
    std::vector<DockerImageInfo> images;
    auto info = DockerImageInfo{};
    info.id = "sha256:abc";
    info.repository = "nginx";
    info.tag = "latest";
    images.push_back(info);

    auto result = DockerResult::success_with_images(images);
    CHECK(result.status == SemanticStatus::kSuccess);
    CHECK(!result.error.has_value());
    CHECK(result.images.size() == 1u);
    CHECK(result.images[0].repository == "nginx");
}

void test_docker_result_failure() {
    auto result = DockerResult::failure("E_TEST", "test error message");
    CHECK(result.status == SemanticStatus::kFailure);
    CHECK(result.error.has_value());
    CHECK(result.error->code == "E_TEST");
    CHECK(result.error->message == "test error message");
}

void test_docker_result_unavailable() {
    auto result = DockerResult::unavailable("Docker not available");
    CHECK(result.status == SemanticStatus::kUnknown);
    CHECK(result.error.has_value());
    CHECK(result.error->code == "E_DOCKER_UNAVAILABLE");
    CHECK(result.error->message == "Docker not available");
}

void test_provider_id_conversion() {
    DockerProviderId id{"docker-cli"};
    std::string s = static_cast<std::string>(id);
    CHECK(s == "docker-cli");
}

}  // namespace

int main(int argc, char** argv) {
    (void)argc;
    (void)argv;

    test_docker_container_state_to_string();
    test_docker_result_success();
    test_docker_result_success_with_containers();
    test_docker_result_success_with_images();
    test_docker_result_failure();
    test_docker_result_unavailable();
    test_provider_id_conversion();

    std::cout << "docker provider tests: ";
    if (g_failures == 0) {
        std::cout << "PASS\n";
        return 0;
    } else {
        std::cout << "FAIL (" << g_failures << " failures)\n";
        return 1;
    }
}