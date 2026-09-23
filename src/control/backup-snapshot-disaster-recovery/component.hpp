#pragma once

#include <string_view>

namespace rebuntu::control::backup_snapshot_disaster_recovery {

// Structural integration point for backup snapshot disaster recovery.
// Behavior-free until source prompts are implemented. Native Linux mechanics stay behind narrow providers.
class BackupSnapshotDisasterRecoveryComponent {
public:
    virtual ~BackupSnapshotDisasterRecoveryComponent() = default;
    [[nodiscard]] virtual std::string_view component_name() const noexcept { return "backup-snapshot-disaster-recovery"; }
};

} // namespace rebuntu::control::backup_snapshot_disaster_recovery
