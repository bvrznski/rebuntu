// rebuntu::system::diagnostics::snapshot — Diagnostic Snapshot Service (Phase 5.13)
//
// This module implements Rebuntu's diagnostic snapshot service that captures
// point-in-time/incident diagnostic evidence from collectors without dumping
// the entire machine.
//
// Snapshot Features:
//   - Typed SnapshotRequest with incident correlation, temporal window, limits
//   - Boot identity tracking (current/previous boot distinction)
//   - Evidence collector integration for bounded acquisition
//   - Storage under Phase 2 data contracts
//   - Retention management

#pragma once

#include <runtime/contracts.hpp>
#include <system/core/contracts.hpp>

#include <memory>
#include <string>
#include <vector>
#include <chrono>
#include <unordered_map>
#include <optional>

namespace rebuntu::system::diagnostics::snapshot {

// ============================================================================
// SnapshotKind — Types of snapshots that can be created
// ============================================================================

enum class SnapshotKind {
    kIncident,     // Snapshot triggered by an incident/alert
    kDiagnostic,   // Diagnostic snapshot on demand
    kPreReboot,    // Snapshot before reboot
    kPeriodic,     // Periodic scheduled snapshot
};

inline std::string to_string(SnapshotKind kind) {
    switch (kind) {
        case SnapshotKind::kIncident:      return "incident";
        case SnapshotKind::kDiagnostic:    return "diagnostic";
        case SnapshotKind::kPreReboot:     return "pre-reboot";
        case SnapshotKind::kPeriodic:      return "periodic";
    }
    return "unknown";
}

// ============================================================================
// EvidenceKind — Types of evidence that can be included in a snapshot
// (Mirrors rebuntu::evidence::EvidenceKind for snapshot-specific use)
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
// SnapshotIdentity — Unique identifier for a snapshot
// ============================================================================

struct SnapshotIdentity {
    std::string id;                          // Unique snapshot ID (UUID)
    std::chrono::system_clock::time_point created_at;
    
    std::optional<std::string> boot_id;      // Boot context for correlation
    std::optional<std::string> previous_boot_id;  // Previous boot if cross-boot
    
    // Trigger information
    std::optional<std::string> trigger_event_id;   // Event that triggered this snapshot
    std::optional<std::string> trigger_reason;     // Human-readable reason
};

// ============================================================================
// SnapshotStatus — Status of a snapshot's lifecycle
// ============================================================================

enum class SnapshotStatus {
    kPending,      // Requested but not yet created
    kCreating,     // In the process of creating
    kReady,        // Created and available
    kPartial,      // Created with some evidence missing
    kFailed,       // Creation failed
};

inline std::string to_string(SnapshotStatus status) {
    switch (status) {
        case SnapshotStatus::kPending:   return "pending";
        case SnapshotStatus::kCreating:  return "creating";
        case SnapshotStatus::kReady:     return "ready";
        case SnapshotStatus::kPartial:   return "partial";
        case SnapshotStatus::kFailed:    return "failed";
    }
    return "unknown";
}

// ============================================================================
// EvidenceReference — Reference to evidence within a snapshot
// ============================================================================

struct EvidenceReference {
    std::string source;           // Source of the evidence (e.g., "journald")
    std::chrono::system_clock::time_point timestamp;
    std::optional<std::string> record_id;  // Record ID if applicable
    
    // Fallback to raw reference for forensic recovery
    std::optional<std::string> raw_reference;
};

// ============================================================================
// SnapshotMetadata — Metadata about a snapshot
// ============================================================================

struct SnapshotMetadata {
    SnapshotIdentity identity;
    
    // Temporal window covered
    std::chrono::system_clock::time_point since;
    std::chrono::system_clock::time_point until;
    
    std::string subject;          // What the snapshot is about (service, host, etc.)
    
    // Collector results summary
    struct CollectorResult {
        EvidenceKind kind;
        core::SemanticStatus status;
        std::string description;  // Human-readable description of result
        size_t records_collected = 0;
        std::optional<core::Error> error;
    };
    
    std::unordered_map<EvidenceKind, CollectorResult> collector_results;
    
    // Limits applied
    size_t max_records_total = 10000;
    std::chrono::milliseconds max_duration_ms{60000};
    
    // Truncation info
    bool was_truncated = false;
    std::optional<size_t> records_dropped_backpressure;
};

// ============================================================================
// SnapshotContent — The actual snapshot content
// ============================================================================

struct SnapshotContent {
    // Evidence collected (bounded, with provenance preserved)
    std::vector<core::Evidence> evidence;
    
    // References to raw sources for forensic recovery
    std::vector<EvidenceReference> evidence_references;
    
    // Summary/diagnostic notes
    std::optional<std::string> summary;
};

// ============================================================================
// SnapshotResult — Result of snapshot creation
// ============================================================================

struct SnapshotResult {
    core::SemanticStatus status;
    std::string description;
    
    SnapshotMetadata metadata;
    SnapshotContent content;
    
    bool verified = false;  // Postconditions were verified
};

// ============================================================================
// SnapshotRequest — Request for a diagnostic snapshot
// ============================================================================

struct SnapshotRequest {
    std::optional<std::string> id;  // Optional client-provided ID
    
    std::chrono::system_clock::time_point created_at;
    
    // Temporal window
    std::optional<std::chrono::system_clock::time_point> since;
    std::optional<std::chrono::system_clock::time_point> until;
    
    // Subjects to include
    std::vector<std::string> subjects;
    
    // Evidence kinds to collect
    std::vector<EvidenceKind> evidence_kinds;
    
    // Limits
    size_t max_records = 100;
    std::chrono::milliseconds timeout_ms{30000};
    
    // Trigger information
    SnapshotKind kind = SnapshotKind::kDiagnostic;
    std::optional<std::string> trigger_event_id;
    std::optional<std::string> reason;
    
    // Storage options
    bool preserve_raw_evidence = true;
};

// ============================================================================
// SnapshotStorage — Interface for snapshot persistence
// ============================================================================

class SnapshotStorage {
public:
    virtual ~SnapshotStorage() = default;
    
    // Store a snapshot (atomic write if supported)
    virtual core::Outcome store(const SnapshotResult& result) = 0;
    
    // Retrieve a snapshot by ID
    virtual std::optional<SnapshotResult> retrieve(std::string_view id) = 0;
    
    // List snapshots matching criteria
    virtual std::vector<std::string> list(
        std::chrono::system_clock::time_point since,
        std::chrono::system_clock::time_point until,
        std::optional<SnapshotKind> kind_filter = std::nullopt) = 0;
    
    // Delete old snapshots beyond retention
    virtual core::Outcome cleanup(std::chrono::system_clock::time_point cutoff) = 0;
};

// ============================================================================
// SnapshotServiceOptions — Configuration for the snapshot service
// ============================================================================

struct SnapshotServiceOptions {
    // Retention period (snapshots older than this are deleted)
    std::chrono::milliseconds retention_ms{std::chrono::hours(24 * 7)};  // 7 days
    
    // Maximum number of snapshots to retain
    size_t max_snapshots_retained = 100;
    
    // Default temporal window for snapshots
    std::chrono::milliseconds default_window_ms{std::chrono::minutes(30)};
    
    // Storage backend
    std::string storage_path;  // Path for snapshot storage
    
    bool async_storage = true;  // Store asynchronously if possible
};

// ============================================================================
// SnapshotServiceMetrics — Runtime metrics
// ============================================================================

struct SnapshotServiceMetrics {
    std::chrono::system_clock::time_point started_at;
    
    size_t requests_received = 0;
    size_t snapshots_created = 0;
    size_t snapshots_failed = 0;
    size_t snapshots_partial = 0;
    
    size_t evidence_records_collected = 0;
    size_t bytes_stored = 0;
};

// ============================================================================
// SnapshotService — Main snapshot service interface
// ============================================================================

class SnapshotService {
public:
    virtual ~SnapshotService() = default;
    
    // Configure the service
    virtual core::Outcome configure(const SnapshotServiceOptions& options) = 0;
    
    // Start/stop lifecycle
    virtual core::Outcome start() = 0;
    virtual core::Outcome stop() = 0;
    virtual bool is_running() const = 0;
    
    // Create a snapshot from a request
    virtual SnapshotResult create_snapshot(const SnapshotRequest& request) = 0;
    
    // Retrieve a stored snapshot
    virtual std::optional<SnapshotResult> get_snapshot(std::string_view id) = 0;
    
    // List snapshots in a time window
    virtual std::vector<std::string> list_snapshots(
        std::chrono::system_clock::time_point since,
        std::chrono::system_clock::time_point until) = 0;
    
    // Metrics
    virtual SnapshotServiceMetrics metrics() const = 0;
};

// ============================================================================
// Factory functions
// ============================================================================

std::unique_ptr<SnapshotStorage> make_file_storage(std::string_view base_path);
std::unique_ptr<SnapshotService> make_snapshot_service();

}  // namespace rebuntu::system::diagnostics::snapshot