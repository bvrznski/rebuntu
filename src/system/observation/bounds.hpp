// rebuntu::observation::bounds — Observation Memory Bounds System (Phase 5.52)
//
// This module defines the memory bounds for observation systems:
//   - Payload size limits (evidence, snapshots, native output)
//   - Retention policies (snapshot count, total bytes, age)
//   - High-cardinality collection limits (processes, services, events)
//   - Backpressure and throttling mechanisms

#pragma once

#include <chrono>
#include <cstddef>
#include <optional>
#include <vector>
#include <string>

namespace rebuntu::observation {

// ============================================================================
// PayloadSizeLimit — Maximum size of payload data
// ============================================================================
//
// Defines limits on:
//   - Raw native output (e.g., journalctl output, systemctl output)
//   - Evidence record values
//   - Snapshot content
//

struct PayloadSizeLimit {
    // Maximum bytes for raw native command output
    // e.g., limit of `journalctl --no-pager -n 1000` output
    size_t max_native_output_bytes = 64 * 1024;  // 64KB default
    
    // Maximum bytes per evidence record value
    size_t max_evidence_value_bytes = 4 * 1024;  // 4KB default
    
    // Maximum total bytes in a snapshot
    size_t max_snapshot_bytes = 512 * 1024;      // 512KB default
    
    // Maximum bytes for cmdline arguments (per process)
    size_t max_cmdline_bytes = 8 * 1024;         // 8KB default
    
    // Maximum bytes for description fields
    size_t max_description_bytes = 256;          // 256B default
};

// ============================================================================
// CollectionLimit — Limits on collection cardinality
// ============================================================================
//
// Defines maximum numbers of items in high-cardinality collections:
//   - Process observations
//   - Service observations  
//   - Event records
//   - Evidence records per request
//

struct CollectionLimit {
    // Maximum number of processes to observe
    size_t max_processes = 1000;
    
    // Maximum number of systemd units/services to observe
    size_t max_services = 500;
    
    // Maximum evidence records per collection request
    size_t max_evidence_records = 1000;
    
    // Maximum events to retain in memory buffer
    size_t max_event_buffer = 10000;
};

// ============================================================================
// RetentionPolicy — Snapshot and observation retention configuration
// ============================================================================
//
// Defines how long and how many snapshots/observations to keep:
//   - Time-based retention (delete after X days)
//   - Count-based retention (keep at most N snapshots)
//   - Size-based retention (keep until total bytes < X)
//

struct RetentionPolicy {
    // Maximum age of a snapshot before deletion
    std::chrono::milliseconds max_age_ms{std::chrono::hours(24 * 7)};  // 7 days
    
    // Maximum number of snapshots to retain
    size_t max_snapshot_count = 100;
    
    // Maximum total storage bytes for snapshots
    size_t max_total_bytes = 100 * 1024 * 1024;  // 100MB default
    
    // Minimum age before cleanup runs (throttle cleanup frequency)
    std::chrono::milliseconds min_cleanup_interval_ms{std::chrono::hours(1)};
};

// ============================================================================
// BackpressureConfig — Backpressure and throttling configuration
// ============================================================================
//
// Prevents observation storms by:
//   - Limiting request rate
//   - Bounding queue depths
//   - Dropping oldest when full
//

struct BackpressureConfig {
    // Maximum pending requests in queue
    size_t max_pending_requests = 10;
    
    // Maximum observations per second (throttle)
    size_t max_observations_per_second = 100;
    
    // When true, drop oldest pending request instead of rejecting new ones
    bool drop_oldest_on_backpressure = false;
    
    // Timeout for requests in the queue
    std::chrono::milliseconds queue_timeout_ms{std::chrono::seconds(30)};
};

// ============================================================================
// ObservationBounds — Complete bounds configuration
// ============================================================================
//
// Aggregates all bound types into a single configuration object.
//

struct ObservationBounds {
    PayloadSizeLimit payload;
    CollectionLimit collection;
    RetentionPolicy retention;
    BackpressureConfig backpressure;
    
    // Global flag to enable/disable bounds enforcement
    bool enabled = true;
};

// ============================================================================
// BoundsEnforcement — Runtime bounds enforcement metrics
// ============================================================================
//
// Tracks how many items were dropped, truncated, or limited due to bounds.
//

struct BoundsEnforcementMetrics {
    std::chrono::system_clock::time_point started_at{};
    
    // Collection limits hit
    size_t collections_dropped_process_limit = 0;
    size_t collections_dropped_service_limit = 0;
    size_t evidence_records_truncated = 0;
    
    // Payload limits hit
    size_t native_output_truncated = 0;
    size_t evidence_value_truncated = 0;
    size_t snapshot_bytes_exceeded = 0;
    
    // Retention enforcement
    size_t snapshots_deleted_age = 0;
    size_t snapshots_deleted_count = 0;
    size_t bytes_freed_by_cleanup = 0;
    
    // Backpressure events
    size_t requests_dropped_backpressure = 0;
    size_t requests_timed_out_queue = 0;
};

// ============================================================================
// BoundsConfiguration — Configuration builder
// ============================================================================

class BoundsConfiguration {
public:
    static ObservationBounds make_default();
    
    // Modify individual limit types
    BoundsConfiguration& with_payload_limits(PayloadSizeLimit limits);
    BoundsConfiguration& with_collection_limits(CollectionLimit limits);
    BoundsConfiguration& with_retention_policy(RetentionPolicy policy);
    BoundsConfiguration& with_backpressure_config(BackpressureConfig config);
    BoundsConfiguration& with_enabled(bool enabled);
    
private:
    ObservationBounds bounds_;
};

// ============================================================================
// Truncation — Result of bounded collection
// ============================================================================
//
// Indicates whether a collection was truncated due to bounds.
//

struct Truncation {
    bool was_truncated = false;
    std::optional<size_t> records_dropped;  // How many items were dropped
    std::optional<std::string> reason;      // Why truncation occurred
    
    static Truncation no_truncation() {
        return {};
    }
    
    static Truncation with_reason(const std::string& reason) {
        Truncation t;
        t.was_truncated = true;
        t.reason = reason;
        return t;
    }
    
    static Truncation with_dropped(size_t count, const std::string& reason) {
        Truncation t;
        t.was_truncated = true;
        t.records_dropped = count;
        t.reason = reason;
        return t;
    }
};

}  // namespace rebuntu::observation