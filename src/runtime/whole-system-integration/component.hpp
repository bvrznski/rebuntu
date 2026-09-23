#pragma once

#include <string_view>

namespace rebuntu::runtime::whole_system_integration {

// Structural integration point for whole system integration.
// Behavior-free until source prompts are implemented. Native Linux mechanics stay behind narrow providers.
class WholeSystemIntegrationComponent {
public:
    virtual ~WholeSystemIntegrationComponent() = default;
    [[nodiscard]] virtual std::string_view component_name() const noexcept { return "whole-system-integration"; }
};

} // namespace rebuntu::runtime::whole_system_integration
