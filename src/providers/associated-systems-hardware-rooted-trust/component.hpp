#pragma once

#include <string_view>

namespace rebuntu::providers::associated_systems_hardware_rooted_trust {

// Structural integration point for associated systems hardware rooted trust.
// Behavior-free until source prompts are implemented. Native Linux mechanics stay behind narrow providers.
class AssociatedSystemsHardwareRootedTrustComponent {
public:
    virtual ~AssociatedSystemsHardwareRootedTrustComponent() = default;
    [[nodiscard]] virtual std::string_view component_name() const noexcept { return "associated-systems-hardware-rooted-trust"; }
};

} // namespace rebuntu::providers::associated_systems_hardware_rooted_trust
