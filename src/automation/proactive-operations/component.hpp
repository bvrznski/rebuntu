#pragma once

#include <string_view>

namespace rebuntu::automation::proactive_operations {

// Structural integration point for proactive operations.
// Behavior-free until source prompts are implemented. Native Linux mechanics stay behind narrow providers.
class ProactiveOperationsComponent {
public:
    virtual ~ProactiveOperationsComponent() = default;
    [[nodiscard]] virtual std::string_view component_name() const noexcept { return "proactive-operations"; }
};

} // namespace rebuntu::automation::proactive_operations
