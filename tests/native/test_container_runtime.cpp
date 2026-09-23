// rebuntu::infrastructure::container_runtime — Unit Tests (Phase 3.6)
//
// Test the generalized container runtime contracts and provider registry.

#include <runtime/core/contracts.hpp>
#include <domains/development/infrastructure/container.hpp>

#include <cstddef>
#include <iostream>
#include <memory>
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

void test_container_state_to_string() {
    using namespace rebuntu::infrastructure;

    CHECK(to_string(ContainerState::kCreated) == "created");
    CHECK(to_string(ContainerState::kRunning) == "running");
    CHECK(to_string(ContainerState::kPaused) == "paused");
    CHECK(to_string(ContainerState::kStopped) == "stopped");
    CHECK(to_string(ContainerState::kDead) == "dead");
    CHECK(to_string(ContainerState::kUnknown) == "unknown");
}

void test_container_result_success() {
    auto result = ContainerResult::success();
    CHECK(result.status == SemanticStatus::kSuccess);
    CHECK(!result.error.has_value());
}

void test_container_result_success_with_containers() {
    std::vector<ContainerInfo> containers;
    auto info = ContainerInfo{};
    info.id = "abc123";
    info.name = "test-container";
    containers.push_back(info);

    auto result = ContainerResult::success_with_containers(containers);
    CHECK(result.status == SemanticStatus::kSuccess);
    CHECK(!result.error.has_value());
    CHECK(result.containers.size() == 1u);
    CHECK(result.containers[0].id == "abc123");
}

void test_container_result_success_with_images() {
    std::vector<ImageInfo> images;
    auto info = ImageInfo{};
    info.id = "sha256:abc";
    info.repository = "nginx";
    info.tag = "latest";
    images.push_back(info);

    auto result = ContainerResult::success_with_images(images);
    CHECK(result.status == SemanticStatus::kSuccess);
    CHECK(!result.error.has_value());
    CHECK(result.images.size() == 1u);
    CHECK(result.images[0].repository == "nginx");
}

void test_container_result_failure() {
    auto result = ContainerResult::failure("E_TEST", "test error message");
    CHECK(result.status == SemanticStatus::kFailure);
    CHECK(result.error.has_value());
    CHECK(result.error->code == "E_TEST");
    CHECK(result.error->message == "test error message");
}

void test_container_result_unavailable() {
    auto result = ContainerResult::unavailable("Container runtime not available");
    CHECK(result.status == SemanticStatus::kUnknown);
    CHECK(result.error.has_value());
    CHECK(result.error->code == "E_CONTAINER_UNAVAILABLE");
}

void test_container_provider_id_conversion() {
    ContainerProviderId id{"container-runtime"};
    std::string s = static_cast<std::string>(id);
    CHECK(s == "container-runtime");
}

void test_image_info_struct() {
    ImageInfo info;
    info.id = "sha256:12345";
    info.repository = "alpine";
    info.tag = "latest";
    info.size_bytes = 1024 * 1024;

    CHECK(info.id == "sha256:12345");
    CHECK(info.repository == "alpine");
    CHECK(info.tag == "latest");
    CHECK(info.size_bytes == 1024 * 1024);
}

void test_container_info_struct() {
    ContainerInfo info;
    info.id = "def678";
    info.name = "my-app";
    info.image = "nginx:latest";
    info.state = ContainerState::kRunning;
    info.is_running = true;

    CHECK(info.id == "def678");
    CHECK(info.name == "my-app");
    CHECK(info.image == "nginx:latest");
    CHECK(info.state == ContainerState::kRunning);
    CHECK(info.is_running == true);
}

}  // namespace

int main(int argc, char** argv) {
    test_container_state_to_string();
    test_container_result_success();
    test_container_result_success_with_containers();
    test_container_result_success_with_images();
    test_container_result_failure();
    test_container_result_unavailable();
    test_container_provider_id_conversion();
    test_image_info_struct();
    test_container_info_struct();

    std::cout << "container runtime tests: ";
    if (g_failures == 0) {
        std::cout << "PASS\n";
        return 0;
    } else {
        std::cout << "FAIL (" << g_failures << " failures)\n";
        return 1;
    }
}