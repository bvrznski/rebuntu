#pragma once

#include <string_view>

namespace rebuntu::domains::process_workload_management {

// Structural integration point for process workload management.
// Behavior-free until source prompts are implemented. Native Linux mechanics stay behind narrow providers.
class ProcessWorkloadManagementComponent {
public:
    virtual ~ProcessWorkloadManagementComponent() = default;
    [[nodiscard]] virtual std::string_view component_name() const noexcept { return "process-workload-management"; }
};

} // namespace rebuntu::domains::process_workload_management
