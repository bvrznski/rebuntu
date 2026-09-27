// rebuntu::observation::system_observation_inventory_discovery::state::snapshot
// Inventory Snapshot Service (Phase 5.38)

#pragma once

#include "types.hpp"
#include <memory>

namespace rebuntu::observation::system_observation_inventory_discovery::state::snapshot {

class SnapshotServiceImpl : public SnapshotService {
public:
    core::Outcome configure(const SnapshotServiceOptions& options) override;
    core::Outcome start() override;
    core::Outcome stop() override;
    bool is_running() const override;

    std::pair<InventorySnapshot, SnapshotValidity> create_snapshot(
        const SnapshotRequest& request) override;

    std::optional<std::pair<InventorySnapshot, SnapshotValidity>> get_snapshot(
        std::string_view id) override;

    SnapshotValidity check_validity(const SnapshotMetadata& metadata) const override;

    std::vector<std::string> list_snapshots(
        std::chrono::system_clock::time_point since,
        std::chrono::system_clock::time_point until) override;

    SnapshotServiceMetrics metrics() const override;
};

std::unique_ptr<SnapshotService> make_inventory_snapshot_service();

}  // namespace rebuntu::observation::system_observation_inventory_discovery::state::snapshot