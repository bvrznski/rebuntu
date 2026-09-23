#pragma once

#include <string_view>

namespace rebuntu::distributed::distributed_failure_partition_management {

// Structural integration point for distributed failure partition management.
// Behavior-free until source prompts are implemented. Native Linux mechanics stay behind narrow providers.
class DistributedFailurePartitionManagementComponent {
public:
    virtual ~DistributedFailurePartitionManagementComponent() = default;
    [[nodiscard]] virtual std::string_view component_name() const noexcept { return "distributed-failure-partition-management"; }
};

} // namespace rebuntu::distributed::distributed_failure_partition_management
