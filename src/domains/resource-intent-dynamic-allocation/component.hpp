#pragma once

#include <string_view>

namespace rebuntu::domains::resource_intent_dynamic_allocation {

// Structural integration point for resource intent dynamic allocation.
// Behavior-free until source prompts are implemented. Native Linux mechanics stay behind narrow providers.
class ResourceIntentDynamicAllocationComponent {
public:
    virtual ~ResourceIntentDynamicAllocationComponent() = default;
    [[nodiscard]] virtual std::string_view component_name() const noexcept { return "resource-intent-dynamic-allocation"; }
};

} // namespace rebuntu::domains::resource_intent_dynamic_allocation
