#pragma once

#include <string_view>

namespace rebuntu::runtime::configuration_and_profiles {

// Structural integration point for configuration and profiles.
// Behavior-free until source prompts are implemented. Native Linux mechanics stay behind narrow providers.
class ConfigurationAndProfilesComponent {
public:
    virtual ~ConfigurationAndProfilesComponent() = default;
    [[nodiscard]] virtual std::string_view component_name() const noexcept { return "configuration-and-profiles"; }
};

} // namespace rebuntu::runtime::configuration_and_profiles
