#pragma once

#include <string_view>

namespace rebuntu::domains::gpu_accelerator_management {

// Structural integration point for gpu accelerator management.
// Behavior-free until source prompts are implemented. Native Linux mechanics stay behind narrow providers.
class GpuAcceleratorManagementComponent {
public:
    virtual ~GpuAcceleratorManagementComponent() = default;
    [[nodiscard]] virtual std::string_view component_name() const noexcept { return "gpu-accelerator-management"; }
};

} // namespace rebuntu::domains::gpu_accelerator_management
