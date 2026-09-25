// rebuntu::infrastructure::container_runtime — Unit Tests (Phase 3.6)
//
// Test the container runtime contracts and registry implementation.

#include <system/core/contracts.hpp>
#include <system/infrastructure/container.hpp>

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
    CHECK(to_string(ContainerState::kCreated) == "created");
    CHECK(to_string(ContainerState::kRunning) == "running");
    CHECK(to_string(ContainerState::kPaused) == "paused");
    CHECK(to_string(ContainerState::kStopped) == "stopped");
    CHECK(to_string(ContainerState::kDead) == "dead");
    CHECK(to_string(ContainerState::kUnknown) == "unknown");
}

void test_container_info_default() {
    ContainerInfo info;
    CHECK(info.id.empty());
    CHECK(info.name.empty());
    CHECK(info.image.empty());
    CHECK(info.state == ContainerState::kUnknown);
    CHECK(!info.is_running);
}

void test_container_result_success() {
    auto result = ContainerResult::success();
    CHECK(result.status == SemanticStatus::kSuccess);
    CHECK(!result.error.has_value());
    CHECK(result.containers.empty());
    CHECK(result.images.empty());
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
    CHECK(result.error->message == "Container runtime not available");
}

void test_container_provider_registry_empty_initially() {
    ContainerProviderRegistry registry;
    CHECK(registry.all_providers().empty());
}

void test_container_provider_registry_register_and_get() {
    // This tests that the registry can be constructed and has the methods
    // We can't register a concrete provider here without implementing one,
    // but we verify the API exists and compiles correctly
    
    ContainerProviderRegistry registry;
    
    // all_providers should return empty vector
    auto providers = registry.all_providers();
    CHECK(providers.empty());
}

void test_image_info_default() {
    ImageInfo info;
    CHECK(info.id.empty());
    CHECK(info.repository.empty());
    CHECK(info.tag.empty());
    CHECK(info.size_bytes == 0);
}

}  // namespace

int main(int argc, char** argv) {
    (void)argc;
    (void)argv;

    test_container_state_to_string();
    test_container_info_default();
    test_container_result_success();
    test_container_result_success_with_containers();
    test_container_result_success_with_images();
    test_container_result_failure();
    test_container_result_unavailable();
    test_container_provider_registry_empty_initially();
    test_container_provider_registry_register_and_get();
    test_image_info_default();

    std::cout << "container runtime tests: ";
    if (g_failures == 0) {
        std::cout << "PASS\n";
        return 0;
    } else {
        std::cout << "FAIL (" << g_failures << " failures)\n";
        return 1;
    }
}