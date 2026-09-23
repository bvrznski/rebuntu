#pragma once

#include <string_view>

namespace rebuntu::runtime::core_runtime {

// Structural integration point for core runtime.
// Behavior-free until source prompts are implemented. Native Linux mechanics stay behind narrow providers.
class CoreRuntimeComponent {
public:
    virtual ~CoreRuntimeComponent() = default;
    [[nodiscard]] virtual std::string_view component_name() const noexcept { return "core-runtime"; }
};

} // namespace rebuntu::runtime::core_runtime
