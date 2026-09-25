// rebuntu::adapters::journald — Native Journald Acquisition Adapter (Phase 5.2)
//
// This module provides an adapter that acquires events from systemd journal
// using journalctl with structured JSON output.
//
// Journald Features:
//   - Cursor-based reading for continuity across restarts
//   - Boot filtering (current/previous boot)
//   - Unit/service filtering
//   - Bounded queries with limit support
//   - Realtime and monotonic timestamps
//   - Follow mode for continuous monitoring

#pragma once

#include <runtime/contracts.hpp>
#include <system/core/contracts.hpp>

#include <memory>
#include <string>
#include <functional>
#include <chrono>
#include <unordered_map>
#include <vector>
#include <optional>
#include <mutex>

namespace rebuntu::adapters {

// ============================================================================
// JournaldConfig — Configuration for journald acquisition
// ============================================================================

struct JournaldConfig {
    // Boot filtering
    std::optional<int> boot_id;  // -1 for previous boot, 0 for current (default)
    
    // Filter by unit/service
    std::vector<std::string> units;
    std::vector<std::string> exclude_units;
    
    // Filter by priority level (0-7, lower = more severe)
    std::optional<int> min_priority;
    
    // Query limits
    size_t max_records_per_query = 1000;
    std::chrono::milliseconds query_timeout_ms{10000};
    
    // Follow mode settings
    bool follow_mode = false;
    std::chrono::milliseconds follow_poll_interval_ms{100};
    
    // Evidence retention
    bool preserve_raw_evidence = true;
    size_t max_evidence_per_record = 32;
};

// ============================================================================
// JournaldAdapter — Native journald event adapter
// ============================================================================

class JournaldAdapter {
public:
    using OnEventCallback = std::function<void(const runtime::Event&)>;
    
    explicit JournaldAdapter(
        const JournaldConfig& config,
        OnEventCallback callback);
    
    ~JournaldAdapter();
    
    // Start/stop the adapter (connect to journal)
    core::Outcome start();
    core::Outcome stop();
    
    // Check if adapter is running
    bool is_running() const;
    
    // Get current adapter metrics
    struct AdapterMetrics {
        size_t records_read = 0;
        size_t events_published = 0;
        size_t errors_parse_failed = 0;
        size_t errors_source_unavailable = 0;
        size_t records_dropped_backpressure = 0;
    };
    AdapterMetrics metrics() const;
    
    // Get the current cursor (for checkpointing)
    std::optional<std::string> get_cursor() const;
    
    // Set a cursor to resume from (must be called before start())
    void set_cursor(const std::string& cursor);

private:
    JournaldConfig config_;
    OnEventCallback callback_;
    bool running_ = false;
    AdapterMetrics metrics_;
    mutable std::mutex metrics_mutex_;
    
    // Cursor state
    std::optional<std::string> current_cursor_;
    std::optional<std::string> last_seen_cursor_;
    
    // Command execution helpers
    core::Outcome execute_journalctl(
        const std::vector<std::string>& argv,
        std::string& output,
        std::chrono::milliseconds timeout);
    
    // Parse JSON record from journalctl output
    std::optional<runtime::Event> parse_json_record(
        const std::string& json_line,
        std::chrono::system_clock::time_point acquisition_time);
    
    // Extract timestamp from journald fields (both realtime and monotonic)
    static std::optional<std::chrono::system_clock::time_point>
    extract_realtime_timestamp(const std::unordered_map<std::string, std::string>& fields);
    
    static std::optional<std::chrono::steady_clock::time_point>
    extract_monotonic_timestamp(const std::unordered_map<std::string, std::string>& fields);
};

// ============================================================================
// JournaldQuery — Query builder for bounded journal queries
// ============================================================================

class JournaldQuery {
public:
    // Create a query configuration
    struct QueryConfig {
        // Time window
        std::optional<std::chrono::system_clock::time_point> since;
        std::optional<std::chrono::system_clock::time_point> until;
        
        // Boot filtering
        std::optional<int> boot_id;
        
        // Record limits
        size_t max_records = 1000;
        
        // Filter by unit
        std::vector<std::string> units;
        
        // Priority filter (0-7)
        std::optional<int> min_priority;
    };
    
    static std::vector<std::string> build_argv(const QueryConfig& config);
};

// ============================================================================
// Factory Functions
// ============================================================================

inline std::unique_ptr<JournaldAdapter> make_journald_adapter(
    const JournaldConfig& config,
    JournaldAdapter::OnEventCallback callback) {
    return std::make_unique<JournaldAdapter>(config, std::move(callback));
}

}  // namespace rebuntu::adapters