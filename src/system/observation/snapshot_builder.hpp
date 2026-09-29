// rebuntu::system::observation::snapshot_builder — Snapshot Builder (Phase 7.2)
//
// This module implements a snapshot builder for constructing current-state
// observations from multiple domain adapters:
//   - Integrates procfs, systemd, sysfs adapters
//   - Bounded collection with timeout/cancellation support
//   - Tracks freshness and quality per observation
//   - Produces coherent snapshots for query/shell consumers

#pragma once

#include "types.hpp"
#include "bounds.hpp"

#include <chrono>
#include <mutex>
#include <memory>
#include <optional>
#include <set>
#include <string>
#include <vector>

namespace rebuntu::system::observation {

class SnapshotBuilderImpl : public SnapshotBuilder {
public:
    explicit SnapshotBuilderImpl(const rebuntu::observation::ObservationBounds& bounds = {});
    ~SnapshotBuilderImpl() override;
    
    core::Outcome start(const std::string& id = "");
    core::Outcome configure_bounds(const rebuntu::observation::ObservationBounds& bounds);
    core::Outcome add_observation(Observation o);
    core::Outcome add_fact(Fact f);
    core::Outcome mark_domain_complete(ObservationDomain d);
    core::Outcome mark_domain_failed(ObservationDomain d, core::Error e);
    core::Outcome set_snapshot_state(SnapshotState s);
    std::optional<Snapshot> build();
    
    struct Progress {
        size_t observations_added = 0;
        size_t facts_added = 0;
        std::set<ObservationDomain> domains_complete{};
        std::vector<std::string> domains_failed{};
    };
    Progress progress() const;

private:
    rebuntu::observation::ObservationBounds bounds_;
    bool started_ = false;
    Snapshot snapshot_;
    size_t total_observations_expected_{0};
    std::chrono::system_clock::time_point start_time_{};
};

class CurrentStateViewImpl : public CurrentStateView {
public:
    explicit CurrentStateViewImpl();
    ~CurrentStateViewImpl() override;
    
    std::optional<Snapshot> get_snapshot(
        const std::set<ObservationDomain>& domains,
        const rebuntu::observation::ObservationBounds& bounds);
    
    std::vector<Fact> get_facts(const ObservationIdentity& subject);
    bool is_fresh(
        const ObservationIdentity& subject,
        const FreshnessPolicy& policy);
    
    std::optional<std::chrono::system_clock::time_point> last_snapshot_time() const;
    void register_adapter(std::unique_ptr<ObservationAdapter> adapter);

private:
    mutable std::mutex mutex_;
    std::vector<std::unique_ptr<ObservationAdapter>> adapters_;
    std::chrono::system_clock::time_point last_snapshot_time_{};
    std::map<ObservationDomain, std::chrono::milliseconds> domain_ttls_;
};

std::unique_ptr<SnapshotBuilderImpl> make_snapshot_builder_impl(
    const rebuntu::observation::ObservationBounds& bounds = {});

std::unique_ptr<CurrentStateViewImpl> make_current_state_view_impl();

}  // namespace rebuntu::system::observation