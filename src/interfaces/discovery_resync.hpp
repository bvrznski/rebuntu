// rebuntu::interfaces::discovery_resync — Discovery Resynchronization Contracts (Phase 5.40)
//
// This module establishes Rebuntu's interface for bounded authoritative
// discovery resynchronization after missed events, overflow, or provider restart.
//
// Event Loss Scenarios:
//   - Queue overflow: Events arrive faster than they can be processed
//   - Provider restart: Adapter/provider restarts and loses state
//   - Missed udev/systemd events: Native event sources drop messages
//
// Resynchronization Goals:
//   - Detect when inventory may be stale (missed events)
//   - Perform bounded authoritative refresh of discovery state
//   - Ensure no silent stale inventory remains
//
// Key Distinctions:
//   - Observation vs Inference: Only native Linux data, no speculation
//   - Freshness-aware: Track observation timestamps
//   - Bounded: Time-limited, record-limited operations
//   - Cancellable: Resync can be interrupted if needed

#pragma once

#include <runtime/contracts.hpp>
#include <system/core/contracts.hpp>
#include <string>
#include <string_view>
#include <chrono>
#include <vector>
#include <memory>
#include <optional>
#include <atomic>
#include <unordered_map>

namespace rebuntu::interfaces {

// ============================================================================
// DiscoveryProviderId — Typed identifier for a discovery provider
// ============================================================================
struct DiscoveryProviderId {
    std::string value;

    // Default constructor (empty ID)
    DiscoveryProviderId() = default;
    
    // Explicit constructor from string
    explicit DiscoveryProviderId(std::string v) : value(std::move(v)) {}
    
    // Implicit conversion to std::string_view for convenience
    explicit operator std::string_view() const { return value; }
};

inline bool operator==(const DiscoveryProviderId& a, const DiscoveryProviderId& b) {
    return a.value == b.value;
}

inline bool operator!=(const DiscoveryProviderId& a, const DiscoveryProviderId& b) {
    return !(a == b);
}

// ============================================================================
// ResyncTriggerReason — Why resynchronization was triggered
// ============================================================================
enum class ResyncTriggerReason {
    kOverflow,              // Event queue overflow detected
    kProviderRestart,       // Provider restart detected (e.g., PID changed)
    kStaleInventory,        // Inventory freshness exceeded threshold
    kMissedEvents,          // Potential event loss indicated
    kManualRequest,         // Explicit user/admin request
};

inline std::string_view to_string(ResyncTriggerReason r) {
    switch (r) {
        case ResyncTriggerReason::kOverflow:       return "overflow";
        case ResyncTriggerReason::kProviderRestart:return "provider-restart";
        case ResyncTriggerReason::kStaleInventory: return "stale-inventory";
        case ResyncTriggerReason::kMissedEvents:   return "missed-events";
        case ResyncTriggerReason::kManualRequest:  return "manual-request";
    }
    return "unknown";
}

// ============================================================================
// DiscoveryProviderMetrics — Runtime metrics for a discovery provider
// ============================================================================
struct DiscoveryProviderMetrics {
    std::chrono::system_clock::time_point last_observation_time{};
    
    // Event-related metrics
    size_t events_processed = 0;
    size_t events_dropped_overflow = 0;     // Events dropped due to queue overflow
    size_t events_dropped_backpressure = 0; // Events dropped due to backpressure
    
    // Observation metrics
    size_t observations_performed = 0;
    size_t observations_failed = 0;
    
    // Resync-related metrics
    size_t resync_requests = 0;
    size_t resync_completions = 0;
    size_t resync_failures = 0;
};

// ============================================================================
// DiscoveryProviderState — Current state of a discovery provider
// ============================================================================
enum class DiscoveryProviderState {
    kInitializing,          // Provider is initializing
    kRunning,               // Provider is running normally
    kPaused,                // Provider is temporarily paused
    kResyncing,             // Provider is performing resynchronization
    kFailed,                // Provider has failed
};

inline std::string_view to_string(DiscoveryProviderState s) {
    switch (s) {
        case DiscoveryProviderState::kInitializing: return "initializing";
        case DiscoveryProviderState::kRunning:      return "running";
        case DiscoveryProviderState::kPaused:       return "paused";
        case DiscoveryProviderState::kResyncing:    return "resyncing";
        case DiscoveryProviderState::kFailed:       return "failed";
    }
    return "unknown";
}

// ============================================================================
// ResyncResult — Result of a resynchronization operation
// ============================================================================
struct ResyncResult {
    core::SemanticStatus status{core::SemanticStatus::kUnknown};
    std::string description;
    
    DiscoveryProviderId provider_id;
    ResyncTriggerReason trigger_reason{ResyncTriggerReason::kManualRequest};
    
    std::chrono::system_clock::time_point started_at{};
    std::chrono::system_clock::time_point completed_at{};
    
    std::chrono::milliseconds elapsed_ms{0};
    
    // What was refreshed
    size_t observations_refreshed = 0;
    size_t new_observations = 0;
    size_t updated_observations = 0;
    
    // Errors encountered (non-fatal)
    std::vector<std::pair<std::string, core::Error>> errors;  // entity_id -> error
    
    std::optional<core::Error> fatal_error;
};

// ============================================================================
// ResyncBudget — Resource budget for a resynchronization operation
// ============================================================================
struct ResyncBudget {
    size_t max_observations = 10000;        // Max observations to refresh
    std::chrono::milliseconds timeout_ms{60000};  // Operation timeout
    
    struct ProviderBudget {
        DiscoveryProviderId provider_id;
        size_t max_observations;
        std::chrono::milliseconds timeout_ms;
    };
    
    std::vector<ProviderBudget> provider_budgets;
};

// ============================================================================
// ResyncRequest — Request for discovery resynchronization
// ============================================================================
struct ResyncRequest {
    std::string id;                         // Unique request ID
    
    std::chrono::system_clock::time_point created_at;
    
    std::optional<std::vector<DiscoveryProviderId>> providers;  // Specific providers, or all
    
    ResyncTriggerReason trigger_reason{ResyncTriggerReason::kManualRequest};
    
    std::chrono::system_clock::time_point deadline;           // When resync must complete
    ResyncBudget budget;                                      // Resource constraints
    
    static ResyncRequest make(std::string id) {
        ResyncRequest r;
        r.id = std::move(id);
        r.created_at = std::chrono::system_clock::now();
        return r;
    }
};

// ============================================================================
// DiscoveryResyncController — Controller for discovery resynchronization
//
// Provides methods to:
//   - Trigger resynchronization for providers
//   - Query provider states and metrics
//   - Check inventory freshness
// ============================================================================
class DiscoveryResyncController {
public:
    virtual ~DiscoveryResyncController() = default;
    
    // Lifecycle management
    virtual core::Outcome configure(const ResyncBudget& budget) = 0;
    virtual core::Outcome start() = 0;
    virtual core::Outcome stop() = 0;
    
    // Runtime state
    virtual DiscoveryProviderState provider_state(const DiscoveryProviderId& id) const = 0;
    
    // Metrics query
    virtual DiscoveryProviderMetrics provider_metrics(const DiscoveryProviderId& id) const = 0;
    
    // Trigger resynchronization for specific providers or all
    virtual ResyncResult resync(const ResyncRequest& request) = 0;
    
    // Check if an inventory is stale (beyond freshness threshold)
    virtual bool is_inventory_stale(const DiscoveryProviderId& id,
                                     std::chrono::milliseconds staleness_threshold) const = 0;
};

// ============================================================================
// Factory function
// ============================================================================
std::unique_ptr<DiscoveryResyncController> make_discovery_resync_controller();

}  // namespace rebuntu::interfaces

namespace std {
template <> struct hash<rebuntu::interfaces::DiscoveryProviderId> {
    size_t operator()(const rebuntu::interfaces::DiscoveryProviderId& id) const noexcept {
        return std::hash<std::string>{}(id.value);
    }
};
}  // namespace std
