#pragma once

#include <string_view>

namespace rebuntu::providers::kernel_driver_hardware_evolution {

// Structural integration point for kernel driver hardware evolution.
// Behavior-free until source prompts are implemented. Native Linux mechanics stay behind narrow providers.
class KernelDriverHardwareEvolutionComponent {
public:
    virtual ~KernelDriverHardwareEvolutionComponent() = default;
    [[nodiscard]] virtual std::string_view component_name() const noexcept { return "kernel-driver-hardware-evolution"; }
};

} // namespace rebuntu::providers::kernel_driver_hardware_evolution
