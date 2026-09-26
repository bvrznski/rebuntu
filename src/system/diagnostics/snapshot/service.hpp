// rebuntu::system::diagnostics::snapshot — Snapshot Service Interface (Phase 5.13)

#pragma once

#include "types.hpp"

namespace rebuntu::system::diagnostics::snapshot {

// ============================================================================
// SnapshotServiceImpl — Concrete implementation of SnapshotService
// ============================================================================

class SnapshotServiceImpl : public SnapshotService {
public:
    explicit SnapshotServiceImpl(std::string base_path);
    
    core::Outcome configure(const SnapshotServiceOptions& options) override;
    core::Outcome start() override;
    core::Outcome stop() override;
    bool is_running() const override;
    
    SnapshotResult create_snapshot(const SnapshotRequest& request) override;
    std::optional<SnapshotResult> get_snapshot(std::string_view id) override;
    std::vector<std::string> list_snapshots(
        std::chrono::system_clock::time_point since,
        std::chrono::system_clock::time_point until) override;
    SnapshotServiceMetrics metrics() const override;

private:
    struct EvidenceCollectionResult {
        std::unordered_map<EvidenceKind, SnapshotMetadata::CollectorResult> collectors;
        std::vector<core::Evidence> evidence;
        std::vector<EvidenceReference> references;
        size_t total_bytes = 0;
        bool truncated = false;
        size_t dropped = 0;
    };
    
    EvidenceCollectionResult collect_evidence_with_limit(
        const SnapshotRequest& request,
        std::chrono::system_clock::time_point now);
    
    std::optional<std::string> get_current_boot_id() const;
    std::string combine_subjects(const std::vector<std::string>& subjects) const;
    std::string format_time(std::chrono::system_clock::time_point tp) const;
    rebuntu::evidence::EvidenceKind convert_to_evidence_kind(EvidenceKind kind) const;
    EvidenceKind convert_from_evidence_kind(rebuntu::evidence::EvidenceKind kind) const;

private:
    std::string base_path_;
    SnapshotServiceOptions options_;
    bool is_started_ = false;
    std::chrono::system_clock::time_point started_at_;
    SnapshotServiceMetrics metrics_;
};

}  // namespace rebuntu::system::diagnostics::snapshot