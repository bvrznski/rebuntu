#pragma once

#include <string_view>

namespace rebuntu::domains::storage_management {

// Structural integration point for storage management.
// Behavior-free until source prompts are implemented. Native Linux mechanics stay behind narrow providers.
class StorageManagementComponent {
public:
    virtual ~StorageManagementComponent() = default;
    [[nodiscard]] virtual std::string_view component_name() const noexcept { return "storage-management"; }
};

} // namespace rebuntu::domains::storage_management
