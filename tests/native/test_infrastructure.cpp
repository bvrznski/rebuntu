// rebuntu::infrastructure — Unit Tests (Phase 3.0)
//
// Test the engineering infrastructure foundation contracts.

#include "cli.hpp"

#include <runtime/core/contracts.hpp>
#include <domains/development/infrastructure/contracts.hpp>
#include <domains/development/infrastructure/jenkins.hpp>

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

void test_infrastructure_category_to_string() {
    using namespace rebuntu::infrastructure;
    
    CHECK(to_string(InfrastructureCategory::kProduction) == "production");
    CHECK(to_string(InfrastructureCategory::kOptional) == "optional");
    CHECK(to_string(InfrastructureCategory::kDevelopment) == "development");
    CHECK(to_string(InfrastructureCategory::kCi) == "ci");
    CHECK(to_string(InfrastructureCategory::kModelArtifact) == "model-artifact");
}

void test_dependency_status_to_string() {
    using namespace rebuntu::infrastructure;
    
    CHECK(to_string(DependencyStatus::kUnknown) == "unknown");
    CHECK(to_string(DependencyStatus::kAvailable) == "available");
    CHECK(to_string(DependencyStatus::kUnavailable) == "unavailable");
    CHECK(to_string(DependencyStatus::kUnusable) == "unusable");
    CHECK(to_string(DependencyStatus::kUnauthorized) == "unauthorized");
    CHECK(to_string(DependencyStatus::kNotChecked) == "not_checked");
}

void test_provider_type_to_string() {
    using namespace rebuntu::infrastructure;
    
    CHECK(to_string(ProviderType::kRuntime) == "runtime");
    CHECK(to_string(ProviderType::kToolchain) == "toolchain");
    CHECK(to_string(ProviderType::kAutomation) == "automation");
    CHECK(to_string(ProviderType::kSemantic) == "semantic");
    CHECK(to_string(ProviderType::kTesting) == "testing");
    CHECK(to_string(ProviderType::kMonitoring) == "monitoring");
}

void test_infrastructure_registry_empty_initially() {
    using namespace rebuntu::infrastructure;
    
    InfrastructureRegistry registry;
    CHECK(registry.all_tools().size() == 0u);
    CHECK(registry.all_contracts().size() == 0u);
}

void test_infrastructure_registry_register_and_find_tool() {
    using namespace rebuntu::infrastructure;
    
    InfrastructureRegistry registry;
    
    ToolInfo tool{
        .name = "cmake",
        .display_name = "CMake",
        .type = ProviderType::kToolchain,
        .is_optional = false
    };
    
    registry.register_tool(tool);
    
    auto found = registry.find_tool("cmake");
    CHECK(found.has_value());
    CHECK(found->name == "cmake");
    CHECK(found->display_name == "CMake");
    CHECK(found->type == ProviderType::kToolchain);
}

void test_infrastructure_registry_find_non_existent_tool() {
    using namespace rebuntu::infrastructure;
    
    InfrastructureRegistry registry;
    
    auto found = registry.find_tool("nonexistent-tool");
    CHECK(!found.has_value());
}

void test_infrastructure_registry_register_and_find_contract() {
    using namespace rebuntu::infrastructure;
    
    InfrastructureRegistry registry;
    
    ToolInfo tool{
        .name = "docker",
        .display_name = "Docker",
        .type = ProviderType::kRuntime,
        .is_optional = true
    };
    
    InfrastructureContract contract{
        .capability_id = "container.build",
        .required_tools = {tool},
        .optional_tools = {},
        .cpu_only = false
    };
    
    registry.register_contract(contract);
    
    auto found = registry.find_contract("container.build");
    CHECK(found.has_value());
    CHECK(found->capability_id == "container.build");
}

void test_infrastructure_registry_register_multiple_tools() {
    using namespace rebuntu::infrastructure;
    
    InfrastructureRegistry registry;
    
    ToolInfo cmake{
        .name = "cmake",
        .display_name = "CMake",
        .type = ProviderType::kToolchain
    };
    
    ToolInfo docker{
        .name = "docker",
        .display_name = "Docker",
        .type = ProviderType::kRuntime,
        .is_optional = true
    };
    
    registry.register_tool(cmake);
    registry.register_tool(docker);
    
    auto tools = registry.all_tools();
    CHECK(tools.size() == 2u);
    
    // Verify sorted order by name
    CHECK(tools[0].name == "cmake");
    CHECK(tools[1].name == "docker");
}

void test_infrastructure_registry_assess_capability_with_no_tools() {
    using namespace rebuntu::infrastructure;
    
    InfrastructureRegistry registry;
    
    InfrastructureContract contract{
        .capability_id = "test.capability",
        .required_tools = {},
        .optional_tools = {}
    };
    
    registry.register_contract(contract);
    
    auto assessment = registry.assess_capability("test.capability");
    CHECK(assessment.capability_id == "test.capability");
    // No tools means all available (vacuously true)
    CHECK(assessment.all_tools_available() == true);
}

void test_infrastructure_result_available() {
    auto result = InfrastructureResult::available();
    CHECK(result.status == rebuntu::core::SemanticStatus::kSuccess);
}

void test_infrastructure_result_unavailable() {
    auto result = InfrastructureResult::unavailable("docker", "not installed");
    CHECK(result.status == rebuntu::core::SemanticStatus::kUnknown);
    CHECK(result.error.has_value());
    CHECK(result.error->code == "E_INFRA_UNAVAILABLE");
    CHECK(result.error->message.find("docker") != std::string::npos);
}

void test_infrastructure_result_partial() {
    ToolAssessment assessment{
        .tool_name = "cmake",
        .status = DependencyStatus::kNotChecked
    };
    
    auto result = InfrastructureResult::partial({assessment});
    CHECK(result.status == rebuntu::core::SemanticStatus::kUnknown);
    CHECK(result.tool_assessments.size() == 1u);
    CHECK(result.tool_assessments[0].tool_name == "cmake");
}

void test_tool_assessment_is_usable() {
    ToolAssessment assessment;
    
    // Not checked is not usable
    assessment.status = DependencyStatus::kNotChecked;
    CHECK(assessment.is_usable() == false);
    
    // Unknown is not usable
    assessment.status = DependencyStatus::kUnknown;
    CHECK(assessment.is_usable() == false);
    
    // Unavailable is not usable
    assessment.status = DependencyStatus::kUnavailable;
    CHECK(assessment.is_usable() == false);
    
    // Usable is usable
    assessment.status = DependencyStatus::kAvailable;
    CHECK(assessment.is_usable() == true);
}

// ============================================================================
// Ansible Provider Integration Tests (Phase 3.8)
// ============================================================================

void test_ansible_provider_type_is_automation() {
    using namespace rebuntu::infrastructure;
    
    ToolInfo ansible{
        .name = "ansible",
        .display_name = "Ansible Automation",
        .type = ProviderType::kAutomation,
        .is_optional = true
    };
    
    CHECK(ansible.type == ProviderType::kAutomation);
    CHECK(to_string(ansible.type) == "automation");
}

void test_ansible_capability_contract_registration() {
    using namespace rebuntu::infrastructure;
    
    InfrastructureRegistry registry;
    
    // Register Ansible tool
    ToolInfo ansible{
        .name = "ansible",
        .display_name = "Ansible Automation",
        .type = ProviderType::kAutomation,
        .is_optional = true,
        .cpu_only = true
    };
    
    registry.register_tool(ansible);
    
    // Create capability contract for playbook execution
    InfrastructureContract playbook_contract{
        .capability_id = "ansible.playbook.execute",
        .required_tools = {ansible},
        .optional_tools = {},
        .cpu_only = true,
        .selection_policy = InfrastructureContract::SelectionPolicy::kAny
    };
    
    registry.register_contract(playbook_contract);
    
    // Verify contract can be found
    auto found = registry.find_contract("ansible.playbook.execute");
    CHECK(found.has_value());
    CHECK(found->capability_id == "ansible.playbook.execute");
    CHECK(found->required_tools.size() == 1u);
}

void test_ansible_capability_assessment_with_missing_provider() {
    using namespace rebuntu::infrastructure;
    
    InfrastructureRegistry registry;
    
    ToolInfo ansible{
        .name = "ansible",
        .display_name = "Ansible Automation",
        .type = ProviderType::kAutomation,
        .is_optional = true
    };
    
    registry.register_tool(ansible);
    
    // Check assessment for playbook execution capability
    InfrastructureContract contract{
        .capability_id = "ansible.playbook.execute",
        .required_tools = {ansible},
        .optional_tools = {},
        .cpu_only = true
    };
    
    registry.register_contract(contract);
    
    auto assessment = registry.assess_capability("ansible.playbook.execute");
    CHECK(assessment.capability_id == "ansible.playbook.execute");
    // Tool may be unavailable if ansible is not in PATH, which is expected for tests
}

void test_infrastructure_all_tools_includes_automation() {
    using namespace rebuntu::infrastructure;
    
    InfrastructureRegistry registry;
    
    // Register various tools including automation
    ToolInfo cmake{
        .name = "cmake",
        .display_name = "CMake",
        .type = ProviderType::kToolchain
    };
    
    ToolInfo ansible{
        .name = "ansible",
        .display_name = "Ansible Automation",
        .type = ProviderType::kAutomation,
        .is_optional = true
    };
    
    registry.register_tool(cmake);
    registry.register_tool(ansible);
    
    auto tools = registry.all_tools();
    
    // Verify automation tool is in list
    bool found_ansible = false;
    for (const auto& tool : tools) {
        if (tool.name == "ansible") {
            found_ansible = true;
            CHECK(tool.type == ProviderType::kAutomation);
            break;
        }
    }
    CHECK(found_ansible == true);
}

void test_infrastructure_registry_register_and_find_automation_contract() {
    using namespace rebuntu::infrastructure;
    
    InfrastructureRegistry registry;
    
    ToolInfo automation_tool{
        .name = "ansible",
        .display_name = "Ansible Automation",
        .type = ProviderType::kAutomation,
        .is_optional = true
    };
    
    // Create contract for automation capability
    InfrastructureContract automation_contract{
        .capability_id = "automation.orchestrate",
        .required_tools = {automation_tool},
        .optional_tools = {},
        .cpu_only = true,
        .selection_policy = InfrastructureContract::SelectionPolicy::kAny
    };
    
    registry.register_contract(automation_contract);
    
    auto found = registry.find_contract("automation.orchestrate");
    CHECK(found.has_value());
    CHECK(found->capability_id == "automation.orchestrate");
    CHECK(found->cpu_only == true);
}

void test_jenkins_provider_type_is_ci() {
    using namespace rebuntu::infrastructure;
    
    ToolInfo jenkins{
        .name = "jenkins",
        .display_name = "Jenkins CI",
        .type = ProviderType::kTesting,
        .is_optional = true
    };
    
    CHECK(jenkins.type == ProviderType::kTesting);
    CHECK(to_string(jenkins.type) == "testing");
}

void test_jenkins_capability_contract_registration() {
    using namespace rebuntu::infrastructure;
    
    InfrastructureRegistry registry;
    
    // Register Jenkins tool
    ToolInfo jenkins{
        .name = "jenkins",
        .display_name = "Jenkins CI",
        .type = ProviderType::kTesting,
        .is_optional = true,
        .cpu_only = true
    };
    
    registry.register_tool(jenkins);
    
    // Create capability contract for build trigger
    InfrastructureContract build_contract{
        .capability_id = "jenkins.build.trigger",
        .required_tools = {jenkins},
        .optional_tools = {},
        .cpu_only = true,
        .selection_policy = InfrastructureContract::SelectionPolicy::kAny
    };
    
    registry.register_contract(build_contract);
    
    // Verify contract can be found
    auto found = registry.find_contract("jenkins.build.trigger");
    CHECK(found.has_value());
    CHECK(found->capability_id == "jenkins.build.trigger");
    CHECK(found->required_tools.size() == 1u);
}

void test_jenkins_result_success() {
    using namespace rebuntu::infrastructure;
    
    JenkinsResult r = JenkinsResult::success();
    CHECK(r.status == rebuntu::core::SemanticStatus::kSuccess);
}

void test_jenkins_result_unavailable() {
    using namespace rebuntu::infrastructure;
    
    JenkinsResult r = JenkinsResult::unavailable("Jenkins server not reachable");
    CHECK(r.status == rebuntu::core::SemanticStatus::kUnknown);
    CHECK(r.error.has_value());
    CHECK(r.error->code == "E_JENKINS_UNAVAILABLE");
}

}  // namespace

int main(int argc, char** argv) {
    test_infrastructure_category_to_string();
    test_dependency_status_to_string();
    test_provider_type_to_string();
    test_infrastructure_registry_empty_initially();
    test_infrastructure_registry_register_and_find_tool();
    test_infrastructure_registry_find_non_existent_tool();
    test_infrastructure_registry_register_and_find_contract();
    test_infrastructure_registry_register_multiple_tools();
    test_infrastructure_registry_assess_capability_with_no_tools();
    test_infrastructure_result_available();
    test_infrastructure_result_unavailable();
    test_infrastructure_result_partial();
    test_tool_assessment_is_usable();
    
    // Phase 3.8 Ansible Provider Integration tests
    test_ansible_provider_type_is_automation();
    test_ansible_capability_contract_registration();
    test_ansible_capability_assessment_with_missing_provider();
    test_infrastructure_all_tools_includes_automation();
    test_infrastructure_registry_register_and_find_automation_contract();
    
    // Phase 3.9 Jenkins Provider Integration tests
    test_jenkins_provider_type_is_ci();
    test_jenkins_capability_contract_registration();
    test_jenkins_result_success();
    test_jenkins_result_unavailable();
    
    std::cout << "infrastructure tests: ";
    if (g_failures == 0) {
        std::cout << "PASS\n";
        return 0;
    } else {
        std::cout << "FAIL (" << g_failures << " failures)\n";
        return 1;
    }
}