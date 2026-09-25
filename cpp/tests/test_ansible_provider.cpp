// rebuntu::infrastructure::ansible_cli — Unit Tests (Phase 3.7)
//
// Test the Ansible provider contracts and implementation.

#include <system/core/contracts.hpp>
#include <system/infrastructure/ansible.hpp>

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

void test_ansible_mode_to_string() {
    using namespace rebuntu::infrastructure;

    CHECK(to_string(AnsibleMode::kNormal) == "normal");
    CHECK(to_string(AnsibleMode::kCheck) == "check");
    CHECK(to_string(AnsibleMode::kDryRun) == "dry-run");
}

void test_ansible_execution_type_to_string() {
    using namespace rebuntu::infrastructure;

    CHECK(to_string(AnsibleExecutionType::kPlaybook) == "playbook");
    CHECK(to_string(AnsibleExecutionType::kModule) == "module");
    CHECK(to_string(AnsibleExecutionType::kInventory) == "inventory");
}

void test_ansible_result_success() {
    auto result = AnsibleResult::success();
    CHECK(result.status == SemanticStatus::kSuccess);
    CHECK(!result.error.has_value());
}

void test_ansible_result_success_with_playbook() {
    AnsiblePlaybookResult playbook_result;
    playbook_result.playbook_path = "/tmp/test.yml";
    
    auto result = AnsibleResult::success_with_playbook(playbook_result);
    CHECK(result.status == SemanticStatus::kSuccess);
    CHECK(!result.error.has_value());
    CHECK(result.playbook_result.has_value());
    CHECK(result.playbook_result->playbook_path == "/tmp/test.yml");
}

void test_ansible_result_success_with_module() {
    AnsibleModuleResult module_result;
    module_result.module_name = "ping";
    
    auto result = AnsibleResult::success_with_module(module_result);
    CHECK(result.status == SemanticStatus::kSuccess);
    CHECK(!result.error.has_value());
    CHECK(result.module_result.has_value());
    CHECK(result.module_result->module_name == "ping");
}

void test_ansible_result_failure() {
    auto result = AnsibleResult::failure("E_TEST", "test error message");
    CHECK(result.status == SemanticStatus::kFailure);
    CHECK(result.error.has_value());
    CHECK(result.error->code == "E_TEST");
    CHECK(result.error->message == "test error message");
}

void test_ansible_result_unavailable() {
    auto result = AnsibleResult::unavailable("Ansible not available");
    CHECK(result.status == SemanticStatus::kUnknown);
    CHECK(result.error.has_value());
    CHECK(result.error->code == "E_ANSIBLE_UNAVAILABLE");
    CHECK(result.error->message == "Ansible not available");
}

void test_provider_id_conversion() {
    AnsibleProviderId id{"ansible-cli"};
    std::string s = static_cast<std::string>(id);
    CHECK(s == "ansible-cli");
}

}  // namespace

int main(int argc, char** argv) {
    (void)argc;
    (void)argv;

    test_ansible_mode_to_string();
    test_ansible_execution_type_to_string();
    test_ansible_result_success();
    test_ansible_result_success_with_playbook();
    test_ansible_result_success_with_module();
    test_ansible_result_failure();
    test_ansible_result_unavailable();
    test_provider_id_conversion();

    std::cout << "ansible provider tests: ";
    if (g_failures == 0) {
        std::cout << "PASS\n";
        return 0;
    } else {
        std::cout << "FAIL (" << g_failures << " failures)\n";
        return 1;
    }
}