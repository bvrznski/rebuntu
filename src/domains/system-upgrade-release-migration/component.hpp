#pragma once

#include <string_view>

namespace rebuntu::domains::system_upgrade_release_migration {

// Structural integration point for system upgrade release migration.
// Behavior-free until source prompts are implemented. Native Linux mechanics stay behind narrow providers.
class SystemUpgradeReleaseMigrationComponent {
public:
    virtual ~SystemUpgradeReleaseMigrationComponent() = default;
    [[nodiscard]] virtual std::string_view component_name() const noexcept { return "system-upgrade-release-migration"; }
};

} // namespace rebuntu::domains::system_upgrade_release_migration
