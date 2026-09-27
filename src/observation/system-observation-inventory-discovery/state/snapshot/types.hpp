// rebuntu::observation::system_observation_inventory_discovery::state::snapshot
// Inventory Snapshot Semantics (Phase 5.38)
//
// This module defines inventory snapshot semantics as a time/freshness-bounded
// aggregate of observations, not eternal truth.
//
// Key Invariants:
//   - Snapshot = bounded aggregate at point in time (not eternal truth)
//   - Per-source timestamps preserved for freshness tracking
//   - Partiality supported: some sources may be unavailable
//   - Evidence preserved with provenance from each source
//   - Snapshot validity is time-bound; stale snapshots must be detected

#pragma once

#include <system/core/contracts.hpp>
#include <cstdint>
#include <memory>
#include <optional>
#include <string>
#include <chrono>
#include <vector>
#include <unordered_map>

namespace rebuntu::observation::system_observation_inventory_discovery::state::snapshot {

// SnapshotIdentity - Unique identifier for a snapshot
struct SnapshotIdentity {
    std::string id;
    std::chrono::system_clock::time_point created_at;
    std::optional<std::string> parent_id;

    bool is_valid() const { return !id.empty(); }
};

// SnapshotStatus - Lifecycle status of an inventory snapshot
enum class SnapshotStatus {
    kPending,
    kCollecting,
    kReady,
    kPartial,
    kStale,
    kFailed,
};

inline std::string to_string(SnapshotStatus s) {
    switch (s) {
        case SnapshotStatus::kPending:   return "pending";
        case SnapshotStatus::kCollecting:return "collecting";
        case SnapshotStatus::kReady:     return "ready";
        case SnapshotStatus::kPartial:   return "partial";
        case SnapshotStatus::kStale:     return "stale";
        case SnapshotStatus::kFailed:    return "failed";
    }
    return "unknown";
}

// SourceFreshness - Freshness tracking for a single observation source
struct SourceFreshness {
    std::string source;
    std::chrono::system_clock::time_point observed_at;
    std::optional<std::string> observation_id;
    std::optional<std::chrono::milliseconds> max_age_ms;

    bool is_fresh(std::chrono::system_clock::time_point now) const {
        if (!max_age_ms.has_value()) return true;
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(
            now - observed_at);
        return elapsed <= max_age_ms.value();
    }
};

// SnapshotObservation - A single observation within a snapshot
struct SnapshotObservation {
    std::string source;
    std::chrono::system_clock::time_point observed_at;
    core::Evidence evidence;
    std::optional<std::string> observation_id;
    bool was_truncated = false;
    size_t records_dropped = 0;
};

// SourceCollectionResult - Result of collecting from one inventory source
struct SourceCollectionResult {
    std::string source;
    core::SemanticStatus status{core::SemanticStatus::kUnknown};
    std::optional<core::Error> error;
    std::vector<SnapshotObservation> observations;
    size_t total_records_observed = 0;
    size_t records_collected = 0;
    size_t records_dropped_backpressure = 0;
    std::chrono::system_clock::time_point collection_started_at{};
    std::chrono::system_clock::time_point collection_completed_at{};
    std::chrono::milliseconds elapsed_ms{0};
};

// SnapshotMetadata - Metadata about an inventory snapshot
struct SnapshotMetadata {
    SnapshotIdentity identity;
    std::chrono::system_clock::time_point created_at{};
    std::optional<std::chrono::system_clock::time_point> valid_until;
    size_t max_records_per_source = 10000;
    std::unordered_map<std::string, SourceCollectionResult> source_results;
    SnapshotStatus status{SnapshotStatus::kPending};
    std::optional<SourceFreshness> freshness_info;
    bool has_partial_data = false;
    size_t sources_unavailable = 0;
    std::optional<std::string> parent_snapshot_id;
};

// InventorySnapshot - The complete inventory snapshot
struct InventorySnapshot {
    SnapshotMetadata metadata;
    std::vector<SnapshotObservation> observations;
    std::unordered_map<std::string, core::Evidence> source_provenance;
    std::chrono::milliseconds total_collection_time_ms{0};
    bool verified = false;
};

// SnapshotRequest - Request to create an inventory snapshot
struct SnapshotRequest {
    std::optional<std::string> id;
    std::chrono::system_clock::time_point created_at{};
    std::optional<std::chrono::system_clock::time_point> since;
    std::optional<std::chrono::system_clock::time_point> until;
    std::vector<std::string> sources;
    size_t max_records_per_source = 10000;
    std::chrono::milliseconds timeout_ms{30000};
    std::optional<std::chrono::milliseconds> max_age_ms;
    bool allow_partial = false;
};

// SnapshotValidity - Validity status of a snapshot
enum class SnapshotValidity {
    kFresh,
    kAcceptable,
    kStale,
    kInvalid,
};

inline std::string to_string(SnapshotValidity v) {
    switch (v) {
        case SnapshotValidity::kFresh:     return "fresh";
        case SnapshotValidity::kAcceptable:return "acceptable";
        case SnapshotValidity::kStale:     return "stale";
        case SnapshotValidity::kInvalid:   return "invalid";
    }
    return "unknown";
}

inline bool is_valid_for_use(SnapshotValidity v) {
    return v == SnapshotValidity::kFresh || v == SnapshotValidity::kAcceptable;
}

// SnapshotServiceOptions - Configuration for snapshot service
struct SnapshotServiceOptions {
    std::unordered_map<std::string, std::chrono::milliseconds> default_freshness_ms{
        {"dpkg", std::chrono::hours(24)},
        {"procfs", std::chrono::minutes(5)},
        {"sysfs", std::chrono::minutes(5)},
    };
    std::chrono::milliseconds max_retention_ms{std::chrono::minutes(10080)};
    size_t default_max_records_per_source = 10000;
    std::chrono::milliseconds default_timeout_ms{30000};
};

// SnapshotServiceMetrics - Runtime metrics
struct SnapshotServiceMetrics {
    std::chrono::system_clock::time_point started_at{};
    size_t snapshots_created = 0;
    size_t snapshots_partial = 0;
    size_t snapshots_stale = 0;
    size_t snapshots_failed = 0;
    size_t total_observations_collected = 0;
    size_t sources_observed = 0;
    std::chrono::milliseconds total_collection_time_ms{0};
};

// SnapshotService - Interface
class SnapshotService {
public:
    virtual ~SnapshotService() = default;

    virtual core::Outcome configure(const SnapshotServiceOptions& options) = 0;
    virtual core::Outcome start() = 0;
    virtual core::Outcome stop() = 0;
    virtual bool is_running() const = 0;

    virtual std::pair<InventorySnapshot, SnapshotValidity> create_snapshot(
        const SnapshotRequest& request) = 0;

    virtual std::optional<std::pair<InventorySnapshot, SnapshotValidity>> get_snapshot(
        std::string_view id) = 0;

    virtual SnapshotValidity check_validity(const SnapshotMetadata& metadata) const = 0;

    virtual std::vector<std::string> list_snapshots(
        std::chrono::system_clock::time_point since,
        std::chrono::system_clock::time_point until) = 0;

    virtual SnapshotServiceMetrics metrics() const = 0;
};

// Factory functions
std::unique_ptr<SnapshotService> make_inventory_snapshot_service();

}  // namespace rebuntu::observation::system_observation_inventory_discovery::state::snapshot