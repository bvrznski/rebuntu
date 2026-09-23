// rebuntu::infrastructure::ProviderSelection — Unified Provider Selection Model (Phase 3.13)
//
// This establishes Rebuntu's unified provider selection model without creating a
// monolithic ProviderManager:
//
//   * Capability-driven selection: Start from requested capability
//   * Policy-based filtering: NATIVE_FIRST, ALLOW_EXTERNAL policies enforced
//   * Explainable results: Candidates considered and rejected reasons documented
//   * Evidence collection: Human-readable explanation property for traceability
//
// Key principles:
//   * PROVIDER != CAPABILITY != OPERATION != SERVICE
//   * Selection is read-only metadata analysis (no execution)
//   * Native providers preferred when they directly solve the task
//   * No privilege escalation - selection happens before execution

#pragma once

#include <system/core/contracts.hpp>
#include <system/infrastructure/contracts.hpp>
#include <chrono>
#include <optional>
#include <string>
#include <string_view>
#include <vector>

namespace rebuntu::infrastructure {

// ============================================================================
// NativeProviderType (Phase 3.13)
// Native Linux provider types - extends infrastructure contracts ProviderType
// ============================================================================

enum class NativeProviderType {
    kNative,          // Native Linux provider (systemd, etc.)
    kBitNetCpu,       // BitNet semantic provider (CPU-only)
    kDocker,          // Docker container runtime
    kAnsible,         // Ansible configuration management
};

inline std::string_view to_string(NativeProviderType t) {
    switch (t) {
        case NativeProviderType::kNative:     return "native";
        case NativeProviderType::kBitNetCpu:  return "bitnet-cpu";
        case NativeProviderType::kDocker:     return "docker";
        case NativeProviderType::kAnsible:    return "ansible";
    }
    return "unknown";
}

// ============================================================================
// ProviderStatus
// The availability and readiness state of a provider
// ============================================================================

enum class ProviderStatus {
    kAvailable,       // Available and usable
    kUnavailable,     // Not available on system
    kDegraded,        // Partially available with reduced capability
};

inline std::string_view to_string(ProviderStatus s) {
    switch (s) {
        case ProviderStatus::kAvailable:  return "available";
        case ProviderStatus::kUnavailable:return "unavailable";
        case ProviderStatus::kDegraded:   return "degraded";
    }
    return "unknown";
}

// ============================================================================
// SelectionPolicy
// The policy governing provider selection behavior
// ============================================================================

enum class SelectionPolicy {
    kNativeFirst,     // If any native providers available, only consider those
    kAllowExternal,   // All available providers considered
    kExternalOnly,    // Only non-native (fallback case)
};

inline std::string_view to_string(SelectionPolicy p) {
    switch (p) {
        case SelectionPolicy::kNativeFirst:  return "native-first";
        case SelectionPolicy::kAllowExternal:return "allow-external";
        case SelectionPolicy::kExternalOnly: return "external-only";
    }
    return "unknown";
}

// ============================================================================
// Scope
// The execution scope for provider operations
// ============================================================================

enum class Scope {
    kSystem,          // System-wide (requires root)
    kUser,            // User-level
    kSession,         // Session-scoped
};

inline std::string_view to_string(Scope s) {
    switch (s) {
        case Scope::kSystem: return "system";
        case Scope::kUser:   return "user";
        case Scope::kSession:return "session";
    }
    return "unknown";
}

// ============================================================================
// ProviderInfo
// Metadata about a provider including availability and selection criteria
// ============================================================================

struct ProviderInfo {
    std::string id;                   // Unique provider identifier (e.g., "native:systemd", "docker:cli")
    NativeProviderType type;         // What kind of provider this is
    std::string name;                // Human-readable display name
    ProviderStatus status;           // Current availability state
    
    // Priority in selection (lower = higher priority)
    // Native providers get 1-99, external providers default to 100+
    int priority = 100;
    
    // Capabilities this provider supports (e.g., "service.control", "container.run")
    std::vector<std::string> capabilities;
    
    // Configuration metadata
    bool native = false;             // Is this a native Linux provider?
    std::optional<std::string> version;     // Detected version
    std::optional<std::string> executable;  // Path to executable if applicable
    
    // Timestamp of last status check (for cache invalidation)
    std::chrono::system_clock::time_point checked_at;
    
    // Human-readable notes about this provider
    std::optional<std::string> description;
};


// ============================================================================
// ProviderSelectionContext
// Immutable context for a provider selection request
//
// frozen=true ensures consistent input during selection
// ============================================================================

struct ProviderSelectionContext {
    // The capability being requested (e.g., "service.control", "container.run")
    std::string capability;
    
    // Policy governing which providers to consider
    SelectionPolicy policy = SelectionPolicy::kNativeFirst;
    
    // Execution scope
    Scope scope = Scope::kUser;
    
    // Optional preference for a specific provider type
    std::optional<NativeProviderType> preferred_type;
    
    // Timeout for provider discovery operations
    std::chrono::milliseconds timeout = std::chrono::seconds{30};
};

// ============================================================================
// ProviderSelectionResult
// The result of a provider selection operation with full explanation
// ============================================================================

struct ProviderSelectionResult {
    core::SemanticStatus status;     // Overall outcome
    
    // Selected provider (where applicable)
    std::optional<ProviderInfo> selected;
    
    // All candidates considered during discovery
    std::vector<ProviderInfo> candidates;
    
    // Providers that were rejected with reasons
    struct RejectedReason {
        ProviderInfo provider;
        std::string reason;  // Human-readable explanation
    };
    std::vector<RejectedReason> rejected;
    
    // Evidence collected during selection (for traceability)
    std::vector<core::Evidence> evidence;
    
    // Error information (if not success)
    std::optional<core::Error> error;
    
    // Is this a successful selection?
    bool is_success() const {
        return status == core::SemanticStatus::kSuccess && selected.has_value();
    }
    
    // Human-readable explanation of the selection decision
    std::string explanation() const;
};

// ============================================================================
// ProviderSelector
// The unified provider selection engine without monolithic architecture
//
// Key design decisions:
//   * Separate discovery and selection phases
//   * Caching with TTL for performance (60s default)
//   * Policy enforcement before selection
//   * Explainable results with full rejection documentation
// ============================================================================

class ProviderSelector {
public:
    // Default cache TTL of 60 seconds balances freshness with performance
    explicit ProviderSelector(std::chrono::seconds cache_ttl = std::chrono::seconds{60});
    
    ~ProviderSelector() = default;
    
    // Disable copy/move for resource management
    ProviderSelector(const ProviderSelector&) = delete;
    ProviderSelector& operator=(const ProviderSelector&) = delete;
    
    // Discover all available providers (populates cache)
    std::vector<ProviderInfo> discover_providers();
    
    // Select a provider based on context (uses cached data if fresh)
    ProviderSelectionResult select_provider(const ProviderSelectionContext& context);
    
    // Get the current cache state
    bool is_cache_fresh() const;
    
    // Force cache refresh
    void invalidate_cache();

private:
    // Discovery implementation (called when cache is stale or empty)
    std::vector<ProviderInfo> do_discover_providers();
    
    // Apply policy-based filtering to candidate list
    std::vector<ProviderInfo> apply_policy_filtering(
        const std::vector<ProviderInfo>& candidates,
        SelectionPolicy policy,
        Scope scope
    );
    
    // Select best provider from filtered candidates
    std::optional<ProviderInfo> select_from_candidates(
        const std::vector<ProviderInfo>& candidates,
        std::optional<NativeProviderType> preferred_type
    );
    
    // Check if a capability is supported by a provider
    bool capability_supported(const ProviderInfo& provider, const std::string& capability) const;
    
    // Build evidence from selection process
    core::Evidence make_evidence(std::string source, std::string value);
    
    // Discovery helper methods
    std::optional<ProviderInfo> discover_systemd_provider();
    std::optional<ProviderInfo> discover_docker_provider();
    std::optional<ProviderInfo> discover_ansible_provider();
    
    // Cache storage
    std::vector<ProviderInfo> cached_providers_;
    std::chrono::system_clock::time_point cache_timestamp_;
    std::chrono::seconds cache_ttl_;
};

// ============================================================================
// ProviderAdapter (wrapper pattern for execution after selection)
//
// This adapter wraps a selected provider to separate selection concerns
// from execution concerns.
// ============================================================================

class ProviderAdapter {
public:
    explicit ProviderAdapter(ProviderInfo provider);
    
    ~ProviderAdapter() = default;
    
    // Get the wrapped provider info
    const ProviderInfo& provider_info() const { return provider_; }
    
    // Check if the adapter's provider is available
    bool is_available() const;
    
    // Execute a request through the provider (interface method)
    // Implementation would be provided by concrete adapter subclasses
    virtual core::Outcome execute(const std::string& operation,
                                  const std::vector<std::string>& args) = 0;

protected:
    ProviderInfo provider_;
};

// ============================================================================
// Inline implementations for ProviderSelector methods that must be defined
// before being called (caching methods, explanation method)
// ============================================================================

inline bool ProviderSelector::is_cache_fresh() const {
    auto now = std::chrono::system_clock::now();
    return (now - cache_timestamp_) < cache_ttl_;
}

inline void ProviderSelector::invalidate_cache() {
    cached_providers_.clear();
    cache_timestamp_ = std::chrono::system_clock::now();
}

inline std::string ProviderSelectionResult::explanation() const {
    if (status == core::SemanticStatus::kSuccess && selected.has_value()) {
        return "Selected provider '" + selected->name +
               "' (type=" + std::string(to_string(selected->type)) + ", priority=" +
               std::to_string(selected->priority) + ")";
    }
    
    if (candidates.empty()) {
        return "No providers available for selection";
    }
    
    if (!selected.has_value() && !rejected.empty()) {
        std::string msg = "Provider selection failed: ";
        bool first = true;
        for (const auto& r : rejected) {
            if (!first) msg += "; ";
            msg += "'" + r.provider.name + "' rejected: " + r.reason;
            first = false;
        }
        return msg;
    }
    
    return "Selection completed with status: " + std::string(core::to_string(status));
}

}  // namespace rebuntu::infrastructure
