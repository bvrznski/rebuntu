// rebuntu::evidence::journal_slice — Journal Slice Collector (Phase 5.59)
//
// This module provides a journal-based evidence collector that acquires bounded
// diagnostic evidence from journald for provider failures and important resync events.
//
// Evidence Characteristics:
//   - Bounded by time window and record count
//   - Preserves provenance with timestamps and cursor references
//   - Redacts sensitive data from messages
//   - Provides structured metadata (boot_id, machine_id, priority)

#pragma once

#include <runtime/contracts.hpp>
#include <system/core/contracts.hpp>
#include <adapters/journald.hpp>

#include <memory>
#include <string>
#include <vector>
#include <chrono>
#include <optional>
#include <mutex>
#include <functional>

namespace rebuntu::evidence {

// ============================================================================
// JournalSliceResult — Result of journal slice collection
// ============================================================================

struct JournalSliceResult {
    core::SemanticStatus status = core::SemanticStatus::kUnknown;
    std::string description;
    
    struct Record {
        runtime::Event event;
        std::string cursor;
        std::chrono::system_clock::time_point acquisition_time;
    };
    
    std::vector<Record> records;
    size_t total_records_available = 0;
    
    std::optional<std::string> boot_id;
    std::optional<std::string> machine_id;
    
    struct Stats {
        size_t records_collected = 0;
        size_t records_filtered = 0;
        size_t secrets_redacted = 0;
        std::chrono::milliseconds elapsed_ms{0};
    } stats;
};

// ============================================================================
// JournalSliceCollector — Evidence collector for journal data
// ============================================================================

class JournalSliceCollector {
public:
    using OnRecordCallback = std::function<void(const JournalSliceResult::Record&)>;
    
    explicit JournalSliceCollector(
        const adapters::JournaldConfig& adapter_config,
        OnRecordCallback callback);
    
    ~JournalSliceCollector();
    
    core::Outcome start();
    core::Outcome stop();
    
    bool is_running() const;
    
    JournalSliceResult collect_slice(
        const std::chrono::system_clock::time_point& since,
        const std::chrono::system_clock::time_point& until,
        size_t max_records = 100);
    
    struct CollectorStats {
        size_t collections_started = 0;
        size_t collections_completed = 0;
        size_t collections_failed = 0;
        size_t total_records_collected = 0;
        size_t total_secrets_redacted = 0;
        std::chrono::milliseconds total_elapsed_ms{0};
    };
    
    CollectorStats stats() const;

private:
    adapters::JournaldConfig adapter_config_;
    OnRecordCallback callback_;
    
    std::unique_ptr<adapters::JournaldAdapter> adapter_;
    
    mutable std::mutex stats_mutex_;
    CollectorStats collector_stats_;
    
    bool running_ = false;
    
    static std::string redact_secrets(const std::string& message);
};

std::unique_ptr<JournalSliceCollector> make_journal_slice_collector(
    const adapters::JournaldConfig& config = adapters::JournaldConfig{},
    JournalSliceCollector::OnRecordCallback callback = nullptr);

}  // namespace rebuntu::evidence