#pragma once

#include <string_view>

namespace rebuntu::distributed::distributed_rebuntu_system {

// Structural integration point for distributed rebuntu system.
// Behavior-free until source prompts are implemented. Native Linux mechanics stay behind narrow providers.
class DistributedRebuntuSystemComponent {
public:
    virtual ~DistributedRebuntuSystemComponent() = default;
    [[nodiscard]] virtual std::string_view component_name() const noexcept { return "distributed-rebuntu-system"; }
};

} // namespace rebuntu::distributed::distributed_rebuntu_system
