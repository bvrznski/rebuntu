// rebuntu::evidence::collector — Bounded Provenance-Rich Diagnostic Evidence Collector (Phase 5.12)
//
// This module implements Rebuntu's evidence collector that assembles bounded,
// provenance-rich diagnostic evidence in response to events/alerts/diagnostic requests.
//
// Evidence Collection Features:
//   - Typed EvidenceRequest with incident correlation, temporal window, limits
//   - Multiple collectors: journal slice, systemd state, process metadata, kernel evidence
//   - Resource budget and backpressure to prevent event storms
//   - Privacy-aware collection (no secrets collected by default)
//   - Source, boot/time, command/query provenance preserved

#pragma once

#include <runtime/contracts.hpp>
#include <system/core/contracts.hpp>

#include <memory>
#include <string>
#include <vector>
#include <chrono>
#include <unordered_map>
#include <optional>

namespace rebuntu::evidence {

// ============================================================================
// EvidenceKind — Types of evidence that can be collected
// ============================================================================

enum class EvidenceKind {
    kJournalSlice,         // Journal records from a time window
    kSystemdState,         // systemd unit/service state snapshot
    kProcessMetadata,      // Process metadata (PID info, cgroups, etc.)
    kKernelEvidence,       // Kernel logs/dmesg/bpf events
    kStorageState,         // Storage/filesystem/mount state
    kResourceSnapshot,     // CPU/memory/disk I/O/PSI snapshot
    kGpuProviderState,     // GPU provider state (NVIDIA, etc.)
    kRuntimeState,         // Rebuntu runtime state
};

inline std::string to_string(EvidenceKind kind) {
    switch (kind) {
        case EvidenceKind::kJournalSlice:      return "journal-slice";
        case EvidenceKind::kSystemdState:      return "systemd-state";
        case EvidenceKind::kProcessMetadata:   return "process-metadata";
        case EvidenceKind::kKernelEvidence:    return "kernel-evidence";
        case EvidenceKind::kStorageState:      return "storage-state";
        case EvidenceKind::kResourceSnapshot:  return "resource-snapshot";
        case EvidenceKind::kGpuProviderState:  return "gpu-provider-state";
        case EvidenceKind::kRuntimeState:      return "runtime-state";
    }
    return "unknown";
}

// ============================================================================
// EvidenceRequest — Request for diagnostic evidence
// ============================================================================

struct EvidenceRequest {
    std::string id;
    std::chrono::system_clock::time_point created_at;
    
    std::vector<std::string> subjects;
    
    std::optional<std::chrono::system_clock::time_point> since;
    std::optional<std::chrono::system_clock::time_point> until;
    
    std::vector<EvidenceKind> evidence_kinds;
    
    size_t max_records = 100;
    std::chrono::milliseconds timeout_ms{30000};
    
    enum class Urgency {
        kBackground,
        kNormal,
        kHigh,
        kCritical,
    } urgency = Urgency::kNormal;
    
    bool exclude_secrets = true;
    bool redact_paths = false;
    
    std::optional<std::chrono::system_clock::time_point> deadline;
    
    std::optional<std::string> correlation_event_id;
    std::optional<std::string> correlation_alert_type;
    
    static EvidenceRequest make(std::string id) {
        EvidenceRequest r;
        r.id = std::move(id);
        r.created_at = std::chrono::system_clock::now();
        return r;
    }
};

// ============================================================================
// EvidenceCollectionResult — Result of evidence collection
// ============================================================================

struct EvidenceCollectionResult {
    core::SemanticStatus status;
    std::string description;
    
    std::vector<core::Evidence> evidence;
    
    struct CollectorResult {
        EvidenceKind kind;
        core::SemanticStatus status;
        std::string description;
        std::vector<core::Evidence> evidence;
        std::optional<core::Error> error;
        size_t records_collected = 0;
        std::chrono::milliseconds elapsed_ms{0};
    };
    
    std::unordered_map<EvidenceKind, CollectorResult> collector_results;
    
    std::optional<std::string> boot_id;
    std::chrono::system_clock::time_point collected_at;
    std::chrono::milliseconds total_duration_ms{0};
    
    size_t records_dropped_backpressure = 0;
    size_t collectors_skipped_budget = 0;
};

// ============================================================================
// EvidenceBudget — Resource budget for evidence collection
// ============================================================================

struct EvidenceBudget {
    size_t max_total_records = 10000;
    std::chrono::milliseconds max_duration_ms{60000};
    
    struct CollectorBudget {
        EvidenceKind kind;
        size_t max_records;
        std::chrono::milliseconds timeout_ms;
    };
    
    std::vector<CollectorBudget> collector_budgets;
};

// ============================================================================
// EvidenceCollectorMetrics — Runtime metrics
// ============================================================================

struct EvidenceCollectorMetrics {
    std::chrono::system_clock::time_point started_at;
    size_t requests_received = 0;
    size_t requests_completed = 0;
    size_t requests_failed = 0;
    size_t requests_timed_out = 0;
    size_t evidence_records_collected = 0;
    size_t evidence_bytes_collected = 0;
    size_t requests_dropped_budget = 0;
    size_t records_dropped_backpressure = 0;
    size_t collectors_skipped = 0;
    size_t errors_source_unavailable = 0;
    size_t errors_permission_denied = 0;
    size_t errors_acquisition_failed = 0;
    size_t errors_parse_failed = 0;
};

// ============================================================================
// EvidenceCollectorOptions — Runtime configuration
// ============================================================================

struct EvidenceCollectorOptions {
    EvidenceBudget budget;
    
    struct KindConfig {
        EvidenceKind kind;
        bool enabled = true;
        std::optional<size_t> max_records;
        std::chrono::milliseconds timeout_ms{10000};
        bool preserve_raw_evidence = true;
    };
    
    std::vector<KindConfig> kind_configs;
};

// ============================================================================
// EvidenceCollector — Interface
// ============================================================================

class EvidenceCollector {
public:
    virtual ~EvidenceCollector() = default;
    
    virtual core::Outcome configure(const EvidenceCollectorOptions& options) = 0;
    virtual core::Outcome start() = 0;
    virtual core::Outcome stop() = 0;
    
    virtual bool is_running() const = 0;
    
    virtual EvidenceCollectionResult collect_evidence(const EvidenceRequest& request) = 0;
    
    virtual EvidenceCollectorMetrics metrics() const = 0;
    virtual EvidenceCollectorOptions options() const = 0;
};

// ============================================================================
// CollectorRegistry — Registry
// ============================================================================

struct CollectorInfo {
    EvidenceKind kind;
    std::string name;
    std::string description;
    bool enabled_by_default = true;
};

class CollectorRegistry {
public:
    void register_collector(CollectorInfo info);
    bool contains(EvidenceKind kind) const;
    std::optional<CollectorInfo> find(EvidenceKind kind) const;
    std::vector<CollectorInfo> all() const;
    std::vector<CollectorInfo> enabled() const;

private:
    std::unordered_map<EvidenceKind, CollectorInfo> collectors_;
};

// ============================================================================
// Factory functions
// ============================================================================

std::unique_ptr<EvidenceCollector> make_evidence_collector();

}  // namespace rebuntu::evidence