// rebuntu::adapters::journal_normalizer — Journal Filtering & Normalization Implementation (Phase 5.3)
//
// This module implements journal filtering, normalization, deduplication,
// and noise suppression for Rebuntu's journal acquisition system.

#include "adapters/journal_normalizer.hpp"

#include <algorithm>
#include <cctype>
#include <sstream>

namespace rebuntu::adapters {

// ============================================================================
// NoisePattern Implementation
// ============================================================================

bool NoisePattern::matches(const std::string& message) const {
    if (pattern_type == "exact_match") {
        return message == pattern;
    }
    else if (pattern_type == "prefix") {
        return message.size() >= pattern.size() &&
               message.compare(0, pattern.size(), pattern) == 0;
    }
    else if (pattern_type == "contains") {
        return message.find(pattern) != std::string::npos;
    }
    else if (pattern_type == "regex" || pattern_type.empty()) {
        // Fallback: simple contains match
        return message.find(pattern) != std::string::npos;
    }
    return false;
}

// ============================================================================
// JournalDeduplicationCache Implementation
// ============================================================================

JournalDeduplicationCache::JournalDeduplicationCache(
    std::chrono::milliseconds window,
    size_t max_entries)
    : window_(window), max_entries_(max_entries) {}

bool JournalDeduplicationCache::is_duplicate(const std::string& fingerprint) const {
    std::lock_guard<std::mutex> lock(mutex_);
    
    auto it = events_.find(fingerprint);
    if (it == events_.end()) {
        return false;
    }
    
    // Check if entry is still within window
    auto now = std::chrono::system_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(
        now - it->second).count();
    
    return elapsed <= static_cast<int64_t>(window_.count());
}

void JournalDeduplicationCache::record_event(const std::string& fingerprint) {
    std::lock_guard<std::mutex> lock(mutex_);
    
    auto now = std::chrono::system_clock::now();
    
    // Evict old entries if we're at capacity
    if (events_.size() >= max_entries_) {
        cleanup(now);
    }
    
    events_[fingerprint] = now;
    stats_.total_events++;
}

size_t JournalDeduplicationCache::cleanup(std::chrono::system_clock::time_point now) {
    std::lock_guard<std::mutex> lock(mutex_);
    
    size_t removed = 0;
    auto it = events_.begin();
    
    while (it != events_.end()) {
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(
            now - it->second).count();
        
        if (elapsed > static_cast<int64_t>(window_.count())) {
            it = events_.erase(it);
            removed++;
        }
        else {
            ++it;
        }
    }
    
    return removed;
}

JournalDeduplicationCache::Statistics JournalDeduplicationCache::statistics() const {
    std::lock_guard<std::mutex> lock(mutex_);
    Statistics result = stats_;
    // Calculate unique events from total minus duplicates
    result.unique_events = events_.size();
    return result;
}

// ============================================================================
// Helper function to extract message from event evidence
// ============================================================================

static std::string get_message_from_event(const runtime::Event& event) {
    for (const auto& e : event.evidence) {
        if (e.source == "journal_message") {
            return e.value;
        }
    }
    return "";
}

// ============================================================================
// JournalEventFilter Implementation
// ============================================================================

JournalEventFilter::JournalEventFilter(
    const JournalFilterConfig& config,
    OnNormalizedCallback callback)
    : config_(config), 
      callback_(std::move(callback)),
      dedup_cache_(std::make_unique<JournalDeduplicationCache>()),
      running_(false) {
    
    // Initialize default noise patterns
    for (const auto& msg : JournalNoiseFilter::kSystemdNoiseMessages) {
        noise_patterns_.push_back({
            "systemd_noise",
            "contains",
            msg
        });
    }
    for (const auto& msg : JournalNoiseFilter::kKernelNoiseMessages) {
        noise_patterns_.push_back({
            "kernel_noise",
            "contains",
            msg
        });
    }
}

JournalEventFilter::~JournalEventFilter() = default;

FilterDecision JournalEventFilter::process_record(
    const runtime::Event& raw_event,
    std::chrono::system_clock::time_point acquisition_time) {
    
    {
        std::lock_guard<std::mutex> lock(mutex_);
        metrics_.records_received++;
    }
    
    // Apply priority filter
    FilterDecision decision = apply_priority_filter(raw_event);
    if (decision != FilterDecision::kAllow) {
        {
            std::lock_guard<std::mutex> lock(mutex_);
            metrics_.records_filtered++;
        }
        return decision;
    }
    
    // Apply unit filter
    decision = apply_unit_filter(raw_event);
    if (decision != FilterDecision::kAllow) {
        {
            std::lock_guard<std::mutex> lock(mutex_);
            metrics_.records_filtered++;
        }
        return decision;
    }
    
    // Check noise patterns
    bool is_noise = JournalNoiseFilter::is_noise(get_message_from_event(raw_event));
    if (is_noise) {
        {
            std::lock_guard<std::mutex> lock(mutex_);
            metrics_.records_suppressed_noise++;
        }
        return FilterDecision::kSuppressNoise;
    }
    
    // Generate fingerprint for deduplication
    std::string fingerprint = generate_fingerprint(raw_event);
    
    if (dedup_cache_->is_duplicate(fingerprint)) {
        {
            std::lock_guard<std::mutex> lock(mutex_);
            metrics_.records_dropped_duplicate++;
        }
        return FilterDecision::kSuppressDuplicate;
    }
    
    // Normalize the event
    NormalizedEvent normalized = normalize_event(raw_event, acquisition_time);
    
    // Record in deduplication cache
    dedup_cache_->record_event(fingerprint);
    
    {
        std::lock_guard<std::mutex> lock(mutex_);
        metrics_.records_normalized++;
    }
    
    // Callback with normalized event
    callback_(normalized);
    
    return FilterDecision::kAllow;
}

size_t JournalEventFilter::process_batch(
    const std::vector<runtime::Event>& events,
    std::chrono::system_clock::time_point acquisition_time) {
    
    size_t processed = 0;
    
    for (const auto& event : events) {
        FilterDecision decision = process_record(event, acquisition_time);
        
        // Count non-backpressure decisions as processed
        if (decision != FilterDecision::kBackpressure) {
            processed++;
        }
    }
    
    return processed;
}

JournalFilterMetrics JournalEventFilter::metrics() const {
    std::lock_guard<std::mutex> lock(mutex_);
    return metrics_;
}

JournalDeduplicationCache::Statistics JournalEventFilter::dedup_statistics() const {
    if (dedup_cache_) {
        return dedup_cache_->statistics();
    }
    return {};
}

bool JournalEventFilter::is_running() const {
    std::lock_guard<std::mutex> lock(mutex_);
    return running_;
}

// ============================================================================
// Filter Helper Methods
// ============================================================================

FilterDecision JournalEventFilter::apply_priority_filter(
    const runtime::Event& event) const {
    
    if (!config_.min_priority.has_value()) {
        return FilterDecision::kAllow;
    }
    
    // Extract priority from evidence (PRIORITY field)
    int priority = 6;  // Default info level
    
    for (const auto& e : event.evidence) {
        // PRIORITY is a simple numeric value
        if (e.source == "journal_message") {
            try {
                priority = std::stoi(e.value);
            } catch (...) {
                // Keep default
            }
        }
    }
    
    if (priority < config_.min_priority.value()) {
        return FilterDecision::kSuppressFilter;
    }
    
    return FilterDecision::kAllow;
}

FilterDecision JournalEventFilter::apply_unit_filter(
    const runtime::Event& event) const {
    
    // If include_units is empty, all units are allowed
    if (config_.include_units.empty()) {
        // But check exclude_units first
        for (const auto& excluded : config_.exclude_units) {
            for (const auto& e : event.evidence) {
                if (e.source == "journal_unit" && 
                    e.value.find(excluded) != std::string::npos) {
                    return FilterDecision::kSuppressFilter;
                }
            }
        }
        return FilterDecision::kAllow;
    }
    
    // Include list is not empty - must match one
    bool matched = false;
    for (const auto& included : config_.include_units) {
        for (const auto& e : event.evidence) {
            if (e.source == "journal_unit" && 
                e.value.find(included) != std::string::npos) {
                matched = true;
                break;
            }
        }
        if (matched) break;
    }
    
    return matched ? FilterDecision::kAllow : FilterDecision::kSuppressFilter;
}

FilterDecision JournalEventFilter::apply_boot_filter(
    const runtime::Event& event) const {
    
    // Boot filtering is typically done at the source (journalctl query)
    // For normalization, we just pass through - boot ID is preserved in evidence
    return FilterDecision::kAllow;
}

// ============================================================================
// Normalization
// ============================================================================

NormalizedEvent JournalEventFilter::normalize_event(
    const runtime::Event& raw_event,
    std::chrono::system_clock::time_point acquisition_time) {
    
    NormalizedEvent normalized;
    
    // Copy event data (with some normalization)
    normalized.event = raw_event;
    
    // Preserve original evidence
    normalized.original_evidence = raw_event.evidence;
    
    // Record normalization time
    normalized.normalized_at = acquisition_time;
    
    // Extract source identifiers from evidence
    for (const auto& e : raw_event.evidence) {
        if (e.source == "journal_cursor") {
            normalized.journal_cursor = e.value;
        }
        else if (e.source == "journal_boot_id") {
            size_t eq_pos = e.value.find('=');
            if (eq_pos != std::string::npos && eq_pos + 1 < e.value.size()) {
                normalized.boot_id = e.value.substr(eq_pos + 1);
            }
        }
        else if (e.source == "journal_machine_id") {
            size_t eq_pos = e.value.find('=');
            if (eq_pos != std::string::npos && eq_pos + 1 < e.value.size()) {
                normalized.machine_id = e.value.substr(eq_pos + 1);
            }
        }
    }
    
    // Determine priority class from event type
    normalized.priority_class = 6;  // Default info level
    
    if (raw_event.type == "error") {
        normalized.priority_class = 0;  // Emergency/Critical
    }
    else if (raw_event.type == "warning") {
        normalized.priority_class = 4;  // Warning/Notice
    }
    
    // Determine normalization quality
    if (!normalized.journal_cursor.empty() && !raw_event.evidence.empty()) {
        normalized.quality = NormalizedEvent::NormalizationQuality::kComplete;
    }
    else if (!raw_event.evidence.empty()) {
        normalized.quality = NormalizedEvent::NormalizationQuality::kPartial;
    }
    else {
        normalized.quality = NormalizedEvent::NormalizationQuality::kDegraded;
    }
    
    return normalized;
}

std::string JournalEventFilter::generate_fingerprint(const runtime::Event& event) {
    std::ostringstream oss;
    
    // Fingerprint components:
    // - Source (to avoid cross-source collisions)
    // - Message content hash
    // - Timestamp rounded to minute
    
    oss << event.source << "|";
    
    // Use acquisition time rounded to minute
    auto tp = std::chrono::time_point_cast<std::chrono::minutes>(
        std::chrono::system_clock::now());
    oss << tp.time_since_epoch().count() << "|";
    
    // Hash of message content (simplified - just first N chars for fingerprinting)
    std::string msg = get_message_from_event(event);
    if (!msg.empty()) {
        size_t hash = 0;
        for (size_t i = 0; i < msg.size() && i < 64; ++i) {
            hash = hash * 31 + static_cast<size_t>(msg[i]);
        }
        oss << std::hex << hash;
    }
    
    return oss.str();
}

// ============================================================================
// JournalNoiseFilter Implementation
// ============================================================================

const std::vector<std::string> JournalNoiseFilter::kSystemdNoiseMessages = {
    "Received SIGCHLD",
    "Child",
    "State changed",
    "Reloading",
    "Got message",
};

const std::vector<std::string> JournalNoiseFilter::kKernelNoiseMessages = {
    "[    0.000000]",
    "DMI:",
    "ACPI:",
    "pci ",
    "Memory: ",
};

std::vector<NoisePattern> JournalNoiseFilter::default_noise_patterns() {
    std::vector<NoisePattern> patterns;
    
    for (const auto& msg : kSystemdNoiseMessages) {
        patterns.push_back({
            "systemd noise: " + msg,
            "contains",
            msg
        });
    }
    
    for (const auto& msg : kKernelNoiseMessages) {
        patterns.push_back({
            "kernel noise: " + msg,
            "contains",
            msg
        });
    }
    
    return patterns;
}

bool JournalNoiseFilter::is_noise(const std::string& message) {
    // Check against known systemd noise patterns
    for (const auto& pattern : kSystemdNoiseMessages) {
        if (message.find(pattern) != std::string::npos) {
            return true;
        }
    }
    
    // Check against kernel noise patterns
    for (const auto& pattern : kKernelNoiseMessages) {
        if (message.find(pattern) != std::string::npos) {
            return true;
        }
    }
    
    return false;
}

// ============================================================================
// Factory Functions
// ============================================================================

std::unique_ptr<JournalEventFilter> make_journal_filter(
    const JournalFilterConfig& config,
    JournalEventFilter::OnNormalizedCallback callback) {
    
    auto filter = std::make_unique<JournalEventFilter>(config, std::move(callback));
    
    return filter;
}

}  // namespace rebuntu::adapters