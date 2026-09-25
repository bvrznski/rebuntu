// rebuntu::events::collector — System Event Collector (Phase 5.1)
//
// This module establishes the contracts and interfaces for Rebuntu's system
// event collector that acquires events from native Linux sources.
//
// Event Collection Pipeline:
//   Native Linux Events
//      ↓
//   [source: systemd D-Bus, udev netlink, inotify/fanotify, procfs]
//      ↓
//   Adapter → raw observation → normalized Event/Fact → channel/publish
//      ↓
//   Evidence store with provenance + timestamp preservation

#pragma once

#include <runtime/contracts.hpp>
#include <system/core/contracts.hpp>

#include <memory>
#include <string>
#include <string_view>
#include <vector>
#include <chrono>
#include <unordered_map>
#include <optional>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <atomic>

namespace rebuntu::events {

// ============================================================================
// EventSource — Identifier for native Linux event sources
// ============================================================================

enum class EventSource {
    kSystemd,          // systemd D-Bus signals (service state changes)
    kUdev,             // udev/netlink device events
    kInotify,          // filesystem change notifications
    kFanotify,         // filesystem event monitoring
    kProcfs,           // process lifecycle from procfs
    kCgroup,           // cgroups v2 resource events
    kNetlink,          // generic netlink messages
    kKernel,           // kernel tracepoints
};

inline std::string_view to_string(EventSource s) {
    switch (s) {
        case EventSource::kSystemd:  return "systemd";
        case EventSource::kUdev:     return "udev";
        case EventSource::kInotify:  return "inotify";
        case EventSource::kFanotify: return "fanotify";
        case EventSource::kProcfs:   return "procfs";
        case EventSource::kCgroup:   return "cgroup";
        case EventSource::kNetlink:  return "netlink";
        case EventSource::kKernel:   return "kernel";
    }
    return "unknown";
}

// ============================================================================
// SourceConfig — Per-source configuration for the collector
// ============================================================================

struct SourceConfig {
    EventSource source;
    bool enabled = true;
    
    // Rate limiting (events per second)
    std::optional<double> max_events_per_second;
    
    // Burst handling
    size_t max_burst_size = 100;
    std::chrono::milliseconds burst_window_ms{1000};
    
    // Evidence retention policy
    bool preserve_raw_evidence = true;
    size_t max_evidence_per_event = 16;
};

// ============================================================================
// EventCollectorState — Collector operational state
// ============================================================================

enum class EventCollectorState {
    kInitializing,   // configuration in progress
    kReady,          // ready to start collecting
    kRunning,        // actively collecting events
    kPaused,         // temporarily paused (e.g., backpressure)
    kStopping,       // shutdown initiated
    kStopped,        // fully stopped
    kFailed,         // terminated due to error
};

inline std::string_view to_string(EventCollectorState s) {
    switch (s) {
        case EventCollectorState::kInitializing: return "initializing";
        case EventCollectorState::kReady:       return "ready";
        case EventCollectorState::kRunning:     return "running";
        case EventCollectorState::kPaused:      return "paused";
        case EventCollectorState::kStopping:    return "stopping";
        case EventCollectorState::kStopped:     return "stopped";
        case EventCollectorState::kFailed:      return "failed";
    }
    return "unknown";
}

// ============================================================================
// EventCollectorMetrics — Runtime metrics for the collector
// ============================================================================

struct EventCollectorMetrics {
    std::chrono::system_clock::time_point started_at;
    std::chrono::system_clock::time_point last_event_time;
    
    // Event counts
    size_t events_collected = 0;
    size_t events_normalized = 0;
    size_t events_published = 0;
    
    // Backpressure-related counts
    size_t events_dropped = 0;
    size_t events_coalesced = 0;
    size_t events_throttled = 0;
    
    // Source-specific counts (source → count)
    std::unordered_map<std::string, size_t> source_counts;
    
    // Error counts by error type
    size_t errors_source_unavailable = 0;
    size_t errors_acquisition_failed = 0;
    size_t errors_parse_failed = 0;
};

// ============================================================================
// EventCollectorOptions — Runtime configuration for the collector
// ============================================================================

struct EventCollectorOptions {
    // Global settings
    std::chrono::milliseconds default_timeout_ms{5000};
    std::chrono::milliseconds shutdown_timeout_ms{30000};
    
    // Queue sizes (per-source)
    size_t max_queue_size = 1024;
    
    // Backpressure policy
    enum class BackpressurePolicy {
        kDropNewest,     // drop newest events when queue full
        kDropOldest,     // drop oldest events when queue full
        kBlock,          // block producer until space available
    };
    
    BackpressurePolicy backpressure = BackpressurePolicy::kDropNewest;
    
    // Evidence retention
    bool preserve_raw_evidence = true;
    size_t max_evidence_per_event = 16;
    
    // Source configuration (by source type)
    std::vector<SourceConfig> sources;
    
    // Callback for event processing failures
    std::function<void(const runtime::Event&, const core::Error&)> on_failure;
};

// ============================================================================
// EventCollector — System event collector interface
// ============================================================================

class EventCollector {
public:
    virtual ~EventCollector() = default;
    
    // Lifecycle management
    virtual core::Outcome configure(const EventCollectorOptions& options) = 0;
    virtual core::Outcome start() = 0;
    virtual core::Outcome stop() = 0;
    
    // Runtime state
    virtual EventCollectorState state() const = 0;
    virtual bool is_running() const = 0;
    
    // Metrics (read-only snapshot)
    virtual EventCollectorMetrics metrics() const = 0;
    
    // Configuration query
    virtual EventCollectorOptions options() const = 0;
};

// ============================================================================
// NativeSourceAdapter — Interface for native Linux event adapters
// ============================================================================

class NativeSourceAdapter {
public:
    virtual ~NativeSourceAdapter() = default;
    
    // Start/stop the adapter (connect to native source)
    virtual core::Outcome start() = 0;
    virtual core::Outcome stop() = 0;
    
    // Check if adapter is running
    virtual bool is_running() const = 0;
    
    // Get source type this adapter handles
    virtual EventSource source_type() const = 0;
    
    // Get current adapter metrics
    struct AdapterMetrics {
        size_t events_read = 0;
        size_t events_parsed = 0;
        size_t errors_parse_failed = 0;
        size_t errors_source_unavailable = 0;
    };
    virtual AdapterMetrics metrics() const = 0;
};

// ============================================================================
// EventPublisher — Interface for publishing normalized events
// ============================================================================

class EventPublisher {
public:
    virtual ~EventPublisher() = default;
    
    // Publish an event (returns false if publisher is full/closed)
    virtual bool publish(const runtime::Event& event) = 0;
    
    // Get queue depth
    virtual size_t queue_depth() const = 0;
};

// ============================================================================
// InMemoryEventChannel — In-memory bounded channel for events
// ============================================================================

class InMemoryEventChannel : public EventPublisher {
public:
    explicit InMemoryEventChannel(size_t max_size = 1024);
    
    bool publish(const runtime::Event& event) override;
    size_t queue_depth() const override;
    
    // Blocking receive with timeout (returns nullopt on timeout)
    std::optional<runtime::Event> receive(std::chrono::milliseconds timeout);
    
    void close();
    bool has_ready() const;
    
private:
    mutable std::mutex mutex_;
    std::queue<runtime::Event> queue_;
    size_t max_size_;
    std::condition_variable cv_;
    std::atomic<bool> closed_{false};
};

// ============================================================================
// EventNormalization — Normalization utilities for raw observations
// ============================================================================

struct NormalizedEvent {
    runtime::Event event;
    std::vector<core::Evidence> extra_evidence;  // additional normalized data
};

class EventNormalizer {
public:
    // Normalize a raw observation from a native source into an Event/Fact
    static core::Result<NormalizedEvent> normalize_event(
        EventSource source,
        const std::string& raw_data,
        std::chrono::system_clock::time_point acquisition_time);
    
    // Parse systemd unit state changes
    static std::optional<runtime::Event> parse_systemd_state_change(
        const std::string& unit_name,
        const std::string& new_state,
        std::chrono::system_clock::time_point timestamp);
    
    // Parse udev events
    static std::optional<runtime::Event> parse_udev_event(
        const std::string& action,
        const std::unordered_map<std::string, std::string>& env,
        std::chrono::system_clock::time_point timestamp);
    
    // Parse inotify/fanotify events
    static std::optional<runtime::Event> parse_filesystem_event(
        int watch_descriptor,
        uint32_t mask,
        const std::string& filename,
        std::chrono::system_clock::time_point timestamp);
};

// ============================================================================
// Factory functions for creating collector components
// ============================================================================

inline std::unique_ptr<EventCollector> make_event_collector();
inline std::unique_ptr<InMemoryEventChannel> make_event_channel(size_t max_size = 1024);

}  // namespace rebuntu::events

namespace std {
template <> struct hash<rebuntu::events::EventSource> {
    size_t operator()(const rebuntu::events::EventSource& s) const noexcept {
        return static_cast<size_t>(s);
    }
};
}