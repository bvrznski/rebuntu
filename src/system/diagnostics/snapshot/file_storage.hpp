// rebuntu::system::diagnostics::snapshot — File-based Snapshot Storage (Phase 5.13)
//
// FileStorage implements persistent snapshot storage using JSON files.
// Snapshots are stored under a configurable base path with atomic writes.

#pragma once

#include "types.hpp"

namespace rebuntu::system::diagnostics::snapshot {

// ============================================================================
// FileStorage — Persistent snapshot storage using file system
// ============================================================================

class FileStorage : public SnapshotStorage {
public:
    explicit FileStorage(std::string base_path);
    
    core::Outcome store(const SnapshotResult& result) override;
    std::optional<SnapshotResult> retrieve(std::string_view id) override;
    std::vector<std::string> list(
        std::chrono::system_clock::time_point since,
        std::chrono::system_clock::time_point until,
        std::optional<SnapshotKind> kind_filter = std::nullopt) override;
    
    core::Outcome cleanup(std::chrono::system_clock::time_point cutoff) override;
    
    // Get storage statistics
    struct StorageStats {
        size_t total_snapshots = 0;
        size_t total_bytes = 0;
        size_t oldest_snapshot_age_days = 0;
    };
    
    StorageStats stats() const;

private:
    std::string make_file_path(std::string_view id) const;
    core::Outcome write_json_file(std::string_view path, std::string_view content);
    std::optional<std::string> read_json_file(std::string_view path);
    SnapshotResult parse_snapshot(const std::string& json_content);

private:
    std::string base_path_;
};

}  // namespace rebuntu::system::diagnostics::snapshot