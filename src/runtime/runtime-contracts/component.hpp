#pragma once

#include <string_view>

namespace rebuntu::runtime::runtime_contracts {

// Structural integration point for runtime contracts.
// Behavior-free until source prompts are implemented. Native Linux mechanics stay behind narrow providers.
class RuntimeContractsComponent {
public:
    virtual ~RuntimeContractsComponent() = default;
    [[nodiscard]] virtual std::string_view component_name() const noexcept { return "runtime-contracts"; }
};

} // namespace rebuntu::runtime::runtime_contracts
