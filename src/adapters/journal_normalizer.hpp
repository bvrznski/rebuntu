// rebuntu::adapters::journal_normalizer — Journal Filtering & Normalization (Phase 5.3)
//
// This module provides journal filtering and normalization capabilities:
//   - Source-side filtering (by priority, unit, boot ID)
//   - Noise suppression (known-noise record filtering)
//   - Deduplication with coalescing
//   - Evidence preservation during normalization
//   - Backpressure handling with loss accounting

#pragma once

#include "adapters/journald.hpp"
#include <runtime/contracts.hpp>
#include <system/core/contracts.hpp>

#include <memory>
#include <string>
#include <vector>
#include <chrono>
#include <unordered_map>
#include <optional>
#include <mutex>
#include <atomic>

namespace rebuntu::adapters {

// ============================================================================
// JournalFilterConfig — Configuration for journal filtering
// ============================================================================

struct JournalFilterConfig {
    std::optional<int> min_priority;
    std::vector<std::string> include_units;
    std::vector<std::string> exclude_units;
    std::optional<int> boot_id;
    std::optional<std::chrono::system_clock::time_point> since;
    std::optional<std::chrono::system_clock::time_point> until;
    size_t max_evidence_per_record = 16;
};

// ============================================================================
// NoisePattern — Known noise patterns to suppress
// ============================================================================

struct NoisePattern {
    std::string description;
    std::string pattern_type;
    std::string pattern;

    bool matches(const std::string& message) const;
};

// ============================================================================
// JournalDeduplicationCache — Deduplication state management
// ============================================================================

class JournalDeduplicationCache {
public:
    explicit JournalDeduplicationCache(
        std::chrono::milliseconds window = std::chrono::seconds(60),
        size_t max_entries = 10000);

    bool is_duplicate(const std::string& fingerprint) const;
    void record_event(const std::string& fingerprint);
    size_t cleanup(std::chrono::system_clock::time_point now);

    struct Statistics {
        size_t total_events = 0;
        size_t duplicates_detected = 0;
        size_t unique_events = 0;
    };
    Statistics statistics() const;

private:
    std::chrono::milliseconds window_;
    size_t max_entries_;

    mutable std::mutex mutex_;
    std::unordered_map<std::string, std::chrono::system_clock::time_point> events_;
    Statistics stats_;
};

// ============================================================================
// JournalFilterMetrics — Runtime metrics for filtering
// ============================================================================

struct JournalFilterMetrics {
    size_t records_received = 0;
    size_t records_filtered = 0;

    size_t records_suppressed_noise = 0;
    size_t records_dropped_duplicate = 0;
    size_t records_coalesced = 0;

    size_t records_dropped_backpressure = 0;
    size_t records_normalized = 0;
};

// ============================================================================
// FilterDecision — Result of applying filters to an event
// ============================================================================

enum class FilterDecision {
    kAllow,
    kSuppressNoise,
    kSuppressFilter,
    kSuppressDuplicate,
    kBackpressure,
};

inline std::string to_string(FilterDecision d) {
    switch (d) {
        case FilterDecision::kAllow:          return "allow";
        case FilterDecision::kSuppressNoise:  return "suppress_noise";
        case FilterDecision::kSuppressFilter: return "suppress_filter";
        case FilterDecision::kSuppressDuplicate: return "suppress_duplicate";
        case FilterDecision::kBackpressure:   return "backpressure";
    }
    return "unknown";
}

// ============================================================================
// NormalizedEvent — Journal record normalized for Rebuntu
// ============================================================================

struct NormalizedEvent {
    runtime::Event event;
    std::optional<std::string> suppression_reason;

    std::vector<core::Evidence> original_evidence;
    std::chrono::system_clock::time_point normalized_at;

    std::optional<std::chrono::system_clock::time_point> source_realtime;
    std::optional<std::chrono::steady_clock::time_point> source_monotonic;

    std::string journal_cursor;
    std::string boot_id;
    std::string machine_id;

    int priority_class = 6;

    enum class NormalizationQuality {
        kComplete,
        kPartial,
        kDegraded,
    } quality = NormalizationQuality::kComplete;
};

// ============================================================================
// JournalEventFilter — Main filtering and normalization interface
// ============================================================================

class JournalEventFilter {
public:
    using OnNormalizedCallback = std::function<void(const NormalizedEvent&)>;

    explicit JournalEventFilter(
        const JournalFilterConfig& config,
        OnNormalizedCallback callback);

    ~JournalEventFilter();

    FilterDecision process_record(
        const runtime::Event& raw_event,
        std::chrono::system_clock::time_point acquisition_time);

    size_t process_batch(
        const std::vector<runtime::Event>& events,
        std::chrono::system_clock::time_point acquisition_time);

    JournalFilterMetrics metrics() const;
    JournalDeduplicationCache::Statistics dedup_statistics() const;
    bool is_running() const;

private:
    JournalFilterConfig config_;
    OnNormalizedCallback callback_;

    std::unique_ptr<JournalDeduplicationCache> dedup_cache_;

    mutable std::mutex mutex_;
    JournalFilterMetrics metrics_;
    bool running_ = false;

    std::vector<NoisePattern> noise_patterns_;

    FilterDecision apply_priority_filter(const runtime::Event& event) const;
    FilterDecision apply_unit_filter(const runtime::Event& event) const;
    FilterDecision apply_boot_filter(const runtime::Event& event) const;

    NormalizedEvent normalize_event(
        const runtime::Event& raw_event,
        std::chrono::system_clock::time_point acquisition_time);

    static std::string generate_fingerprint(const runtime::Event& event);
};

// ============================================================================
// JournalNoiseFilter — Static utility for noise pattern matching
// ============================================================================

class JournalNoiseFilter {
public:
    static std::vector<NoisePattern> default_noise_patterns();
    static bool is_noise(const std::string& message);

    static const std::vector<std::string> kSystemdNoiseMessages;
    static const std::vector<std::string> kKernelNoiseMessages;
};

// ============================================================================
// Factory functions
// ============================================================================

std::unique_ptr<JournalEventFilter> make_journal_filter(
    const JournalFilterConfig& config,
    JournalEventFilter::OnNormalizedCallback callback);

}  // namespace rebuntu::adapters