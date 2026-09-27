// rebuntu::system::diagnostics::snapshot — Snapshot Service Implementation (Phase 5.13)
//
// This module implements Rebuntu's diagnostic snapshot service that creates
// coherent point-in-time/incident diagnostic snapshots from evidence collectors.

#include "types.hpp"
#include "error.hpp"
#include "evidence.hpp"
#include <system/evidence/collector.hpp>
#include <uuid/uuid.h>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <ctime>
#include <cstring>

namespace rebuntu::system::diagnostics::snapshot {

// ============================================================================
// SnapshotServiceImpl — Concrete implementation of SnapshotService
// ============================================================================

class SnapshotServiceImpl : public SnapshotService {
public:
    explicit SnapshotServiceImpl(std::string base_path)
        : base_path_(std::move(base_path)) {}
    
    core::Outcome configure(const SnapshotServiceOptions& options) override {
        options_ = options;
        return core::Outcome::success();
    }
    
    core::Outcome start() override {
        if (!is_started_) {
            is_started_ = true;
            started_at_ = std::chrono::system_clock::now();
            metrics_.started_at = started_at_;
        }
        return core::Outcome::success();
    }
    
    core::Outcome stop() override {
        is_started_ = false;
        return core::Outcome::success();
    }
    
    bool is_running() const override {
        return is_started_;
    }
    
    SnapshotResult create_snapshot(const SnapshotRequest& request) override {
        metrics_.requests_received++;
        
        SnapshotResult result;
        auto now = std::chrono::system_clock::now();
        
        // Generate unique snapshot ID
        uuid_t uid;
        uuid_generate(uid);
        char uid_str[37];
        uuid_unparse_lower(uid, uid_str);
        
        result.metadata.identity.id = std::string(uid_str);
        result.metadata.identity.created_at = now;
        
        // Get current boot ID
        auto boot_id = get_current_boot_id();
        if (boot_id) {
            result.metadata.identity.boot_id = *boot_id;
        }
        
        // Determine temporal window
        if (request.since.has_value()) {
            result.metadata.since = request.since.value();
        } else {
            result.metadata.since = now - options_.default_window_ms;
        }
        result.metadata.until = now;
        
        // Set subjects from request or use empty string for all
        if (!request.subjects.empty()) {
            result.metadata.subject = combine_subjects(request.subjects);
        } else {
            result.metadata.subject = "*";  // All subjects
        }
        
        // Collect evidence using EvidenceCollector
        auto collector_result = collect_evidence_with_limit(request, now);
        result.metadata.collector_results = std::move(collector_result.collectors);
        
        // Update metrics
        size_t total_records = 0;
        for (const auto& [kind, cr] : result.metadata.collector_results) {
            total_records += cr.records_collected;
        }
        result.metadata.was_truncated = collector_result.truncated;
        if (collector_result.dropped > 0) {
            result.metadata.records_dropped_backpressure = collector_result.dropped;
        }
        
        metrics_.evidence_records_collected += total_records;
        metrics_.bytes_stored += collector_result.total_bytes;
        
        // Build content
        result.content.evidence = std::move(collector_result.evidence);
        for (const auto& ref : collector_result.references) {
            result.content.evidence_references.push_back(ref);
        }
        
        if (collector_result.truncated || !result.metadata.collector_results.empty()) {
            // Build summary note about what was collected
            std::string summary = "Snapshot created at ";
            summary += format_time(now);
            summary += ". Collected evidence from ";
            
            size_t kinds_collected = 0;
            for (const auto& [kind, cr] : result.metadata.collector_results) {
                if (cr.status == core::SemanticStatus::kSuccess && cr.records_collected > 0) {
                    kinds_collected++;
                }
            }
            
            summary += std::to_string(kinds_collected);
            summary += " evidence kind(s), ";
            summary += std::to_string(total_records);
            summary += " record(s).";
            
            if (collector_result.truncated) {
                summary += " Note: Evidence was truncated due to limits.";
            }
            
            result.content.summary = std::move(summary);
        }
        
        // Determine final status
        bool success = true;
        for (const auto& [kind, cr] : result.metadata.collector_results) {
            if (cr.status == core::SemanticStatus::kFailure ||
                cr.status == core::SemanticStatus::kUnknown) {
                success = false;
                break;
            }
        }
        
        // Use kCompleted when some collectors failed but not all
        if (!success && total_records > 0) {
            result.status = core::SemanticStatus::kCompleted;  // Partial success
            metrics_.snapshots_partial++;
        } else if (collector_result.truncated || !success) {
            result.status = core::SemanticStatus::kFailure;
        } else {
            result.status = core::SemanticStatus::kSuccess;
        }
        
        if (result.status == core::SemanticStatus::kSuccess && total_records > 0) {
            metrics_.snapshots_created++;
        }
        return result;
    }
    
    std::optional<SnapshotResult> get_snapshot(std::string_view id) override {
        auto file_path = base_path_ + "/" + std::string(id) + ".json";
        
        if (!std::filesystem::exists(file_path)) {
            return std::nullopt;
        }
        
        // TODO: Implement JSON parsing for stored snapshots
        return std::nullopt;
    }
    
    std::vector<std::string> list_snapshots(
        std::chrono::system_clock::time_point since,
        std::chrono::system_clock::time_point until) override {
        
        (void)since;  // Unused - TODO: implement time filtering
        (void)until;  // Unused - TODO: implement time filtering
        
        std::vector<std::string> result;
        
        if (!std::filesystem::exists(base_path_)) {
            return result;
        }
        
        for (const auto& entry : std::filesystem::directory_iterator(base_path_)) {
            if (entry.is_regular_file()) {
                auto filename = entry.path().filename().string();
                if (filename.ends_with(".json")) {
                    result.push_back(filename.substr(0, filename.size() - 5));
                }
            }
        }
        
        return result;
    }
    
    SnapshotServiceMetrics metrics() const override {
        return metrics_;
    }

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
        std::chrono::system_clock::time_point now) {
        
        EvidenceCollectionResult result;
        
        rebuntu::evidence::EvidenceRequest ec_request;
        ec_request.id = request.id.value_or("snapshot-" + std::to_string(now.time_since_epoch().count()));
        ec_request.created_at = now;
        
        if (request.since.has_value()) {
            ec_request.since = request.since.value();
        } else {
            ec_request.since = now - options_.default_window_ms;
        }
        ec_request.until = request.until ? *request.until : now;
        
        for (auto kind : request.evidence_kinds) {
            auto ek = convert_to_evidence_kind(kind);
            if (ek.has_value()) {
                ec_request.evidence_kinds.push_back(*ek);
            }
        }
        
        ec_request.max_records = request.max_records;
        ec_request.timeout_ms = request.timeout_ms;
        
        auto collector = rebuntu::evidence::make_evidence_collector();
        
        if (!collector) {
            for (auto kind : request.evidence_kinds) {
                SnapshotMetadata::CollectorResult cr;
                cr.kind = kind;
                cr.status = core::SemanticStatus::kFailure;
                cr.description = "Failed to create evidence collector";
                result.collectors[kind] = std::move(cr);
            }
            return result;
        }
        
        auto collection_result = collector->collect_evidence(ec_request);
        
        for (const auto& [ek, cr] : collection_result.collector_results) {
            SnapshotMetadata::CollectorResult my_cr;
            my_cr.kind = convert_from_evidence_kind(ek);
            my_cr.status = cr.status;
            my_cr.description = cr.description;
            my_cr.records_collected = cr.records_collected;
            
            if (cr.error.has_value()) {
                my_cr.error = cr.error.value();
            }
            
            result.collectors[my_cr.kind] = std::move(my_cr);
            
            for (const auto& e : cr.evidence) {
                result.evidence.push_back(e);
                result.total_bytes += e.source.size() + e.value.size();
                
                EvidenceReference ref;
                ref.source = e.source;
                ref.timestamp = now;
                if (!e.captured_at.empty()) {
                    ref.raw_reference = std::string("evidence_id:") + e.captured_at;
                }
                result.references.push_back(std::move(ref));
            }
        }
        
        if (collection_result.records_dropped_backpressure > 0) {
            result.truncated = true;
            result.dropped = collection_result.records_dropped_backpressure;
        }
        
        return result;
    }
    
    // NOTE: boot_id is read fresh each time to ensure we detect reboots.
    // A static cache would incorrectly return the same ID across reboots.
    std::optional<std::string> get_current_boot_id() const {
        auto boot_id_file = "/proc/sys/kernel/random/boot_id";
        std::ifstream ifs(boot_id_file);
        
        if (!ifs.is_open()) {
            return std::nullopt;
        }
        
        std::string boot_id;
        std::getline(ifs, boot_id);
        if (boot_id.empty()) {
            return std::nullopt;
        }
        
        // Remove trailing newline if present
        if (boot_id.back() == '\n') {
            boot_id.pop_back();
        }
        
        if (boot_id.empty()) {
            return std::nullopt;
        }
        
        return boot_id;
    }
    
    std::string combine_subjects(const std::vector<std::string>& subjects) const {
        if (subjects.empty()) return "";
        if (subjects.size() == 1) return subjects[0];
        
        std::string result = subjects[0];
        for (size_t i = 1; i < subjects.size(); ++i) {
            result += ", " + subjects[i];
        }
        return result;
    }
    
    std::string format_time(std::chrono::system_clock::time_point tp) const {
        auto tt = std::chrono::system_clock::to_time_t(tp);
        std::tm tm;
        gmtime_r(&tt, &tm);
        
        char buf[64];
        strftime(buf, sizeof(buf), "%Y-%m-%dT%H:%M:%SZ", &tm);
        return std::string(buf);
    }
    
    std::optional<rebuntu::evidence::EvidenceKind> convert_to_evidence_kind(
        EvidenceKind kind) const {
        
        switch (kind) {
            case EvidenceKind::kJournalSlice:      return rebuntu::evidence::EvidenceKind::kJournalSlice;
            case EvidenceKind::kSystemdState:      return rebuntu::evidence::EvidenceKind::kSystemdState;
            case EvidenceKind::kProcessMetadata:   return rebuntu::evidence::EvidenceKind::kProcessMetadata;
            case EvidenceKind::kKernelEvidence:    return rebuntu::evidence::EvidenceKind::kKernelEvidence;
            case EvidenceKind::kStorageState:      return rebuntu::evidence::EvidenceKind::kStorageState;
            case EvidenceKind::kResourceSnapshot:  return rebuntu::evidence::EvidenceKind::kResourceSnapshot;
            case EvidenceKind::kGpuProviderState:  return rebuntu::evidence::EvidenceKind::kGpuProviderState;
            case EvidenceKind::kRuntimeState:      return rebuntu::evidence::EvidenceKind::kRuntimeState;
        }
        return std::nullopt;
    }
    
    EvidenceKind convert_from_evidence_kind(rebuntu::evidence::EvidenceKind kind) const {
        switch (kind) {
            case rebuntu::evidence::EvidenceKind::kJournalSlice:      return EvidenceKind::kJournalSlice;
            case rebuntu::evidence::EvidenceKind::kSystemdState:      return EvidenceKind::kSystemdState;
            case rebuntu::evidence::EvidenceKind::kProcessMetadata:   return EvidenceKind::kProcessMetadata;
            case rebuntu::evidence::EvidenceKind::kKernelEvidence:    return EvidenceKind::kKernelEvidence;
            case rebuntu::evidence::EvidenceKind::kStorageState:      return EvidenceKind::kStorageState;
            case rebuntu::evidence::EvidenceKind::kResourceSnapshot:  return EvidenceKind::kResourceSnapshot;
            case rebuntu::evidence::EvidenceKind::kGpuProviderState:  return EvidenceKind::kGpuProviderState;
            case rebuntu::evidence::EvidenceKind::kRuntimeState:      return EvidenceKind::kRuntimeState;
        }
        return EvidenceKind::kJournalSlice;
    }

private:
    std::string base_path_;
    SnapshotServiceOptions options_;
    bool is_started_ = false;
    std::chrono::system_clock::time_point started_at_;
    SnapshotServiceMetrics metrics_;
};

// ============================================================================
// Factory functions
// ============================================================================

std::unique_ptr<SnapshotStorage> make_file_storage(std::string_view base_path) {
    // TODO: Implement FileStorage class
    (void)base_path;
    return nullptr;
}

std::unique_ptr<SnapshotService> make_snapshot_service() {
    const char* storage_path = std::getenv("REBUNTU_SNAPSHOT_PATH");
    if (!storage_path || strlen(storage_path) == 0) {
        storage_path = "/tmp/rebuntu/snapshots";
    }
    
    return std::make_unique<SnapshotServiceImpl>(std::string(storage_path));
}

}  // namespace rebuntu::system::diagnostics::snapshot