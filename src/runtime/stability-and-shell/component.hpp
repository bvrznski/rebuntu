#pragma once

#include <string_view>

namespace rebuntu::runtime::stability_and_shell {

// Structural integration point for stability and shell.
// Behavior-free until source prompts are implemented. Native Linux mechanics stay behind narrow providers.
class StabilityAndShellComponent {
public:
    virtual ~StabilityAndShellComponent() = default;
    [[nodiscard]] virtual std::string_view component_name() const noexcept { return "stability-and-shell"; }
};

} // namespace rebuntu::runtime::stability_and_shell
