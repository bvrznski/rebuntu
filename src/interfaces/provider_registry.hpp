// rebuntu::interfaces::provider_registry — Provider selection interface
// Phase 0.16: Interfaces, Adapters, Providers & System Boundaries
//
// This header establishes Rebuntu's provider registry pattern:
// how external tools/providers can be discovered, registered, selected,
// and invoked for infrastructure capabilities.
//

#pragma once

#include <string>
#include <vector>
#include <map>
#include <chrono>
#include <optional>
#include <memory>

namespace rebuntu::interfaces {

// ProviderId - Unique identifier for a provider
struct ProviderId {
    std::string value;
    
    // Default constructor
    ProviderId() = default;
    // Constructor from string (takes ownership)
    explicit ProviderId(std::string v) : value(std::move(v)) {}
    explicit operator std::string() const { return value; }
};

inline bool operator==(const ProviderId& a, const ProviderId& b) {
    return a.value == b.value;
}

inline bool operator!=(const ProviderId& a, const ProviderId& b) {
    return !(a == b);
}

// CapabilityAvailabilityState - Phase-1 capability availability states
//
// This enum defines the available states for capabilities and providers:
//   AVAILABLE      - Fully operational, ready to use
//   DEGRADED       - Operational but with reduced capability or performance
//   UNAVAILABLE    - Present but not currently available (e.g., in use by another process)
//   UNSUPPORTED    - Not supported by the current system/configuration
//   NOT_APPLICABLE - Not applicable in the current context
//   UNKNOWN        - Availability has not been determined
//
enum class CapabilityAvailabilityState {
    kUnknown,
    kAvailable,
    kDegraded,
    kUnavailable,
    kUnsupported,
    kNotApplicable,
};

inline std::string to_string(CapabilityAvailabilityState a) {
    switch (a) {
        case CapabilityAvailabilityState::kUnknown:       return "unknown";
        case CapabilityAvailabilityState::kAvailable:     return "available";
        case CapabilityAvailabilityState::kDegraded:      return "degraded";
        case CapabilityAvailabilityState::kUnavailable:   return "unavailable";
        case CapabilityAvailabilityState::kUnsupported:   return "unsupported";
        case CapabilityAvailabilityState::kNotApplicable: return "not_applicable";
    }
    return "unknown";
}

// Alias for backward compatibility
using ProviderAvailability = CapabilityAvailabilityState;

// CapabilityAvailability - Detailed availability state with metadata
struct CapabilityAvailability {
    CapabilityAvailabilityState state = CapabilityAvailabilityState::kUnknown;
    
    // Optional metadata explaining why the capability is in this state
    std::optional<std::string> reason;
    std::optional<std::chrono::system_clock::time_point> last_assessed_at;
    std::optional<uint64_t> observed_evidence_count;  // Evidence items that informed this assessment
};

// ProviderInfo - Static information about a provider
struct ProviderInfo {
    ProviderId id;
    std::string name;
    std::string description;
    std::string version;
    std::string executable_path;
    
    CapabilityAvailabilityState availability = CapabilityAvailabilityState::kUnknown;
    
    // Capability-specific availability states for fine-grained discovery
    std::map<std::string, CapabilityAvailability> capability_availability;
    
    std::vector<std::string> supported_capabilities;
};

// ProviderSelectionPolicy - How to select among multiple providers
enum class ProviderSelectionPolicy {
    kAny,
    kFirst,
    kPreferred,
    kExplicit,
};

inline std::string to_string(ProviderSelectionPolicy p) {
    switch (p) {
        case ProviderSelectionPolicy::kAny:       return "any";
        case ProviderSelectionPolicy::kFirst:     return "first";
        case ProviderSelectionPolicy::kPreferred: return "preferred";
        case ProviderSelectionPolicy::kExplicit:  return "explicit";
    }
    return "unknown";
}

// ProviderSelector - Interface for selecting a provider
class ProviderSelector {
public:
    virtual ~ProviderSelector() = default;
    
    virtual std::string select_provider(
        const std::string& capability,
        ProviderSelectionPolicy policy = ProviderSelectionPolicy::kFirst
    ) const = 0;
    
    virtual bool can_provide(
        const std::string& capability,
        const std::string& provider_id
    ) const = 0;
};

// ProviderRegistry - Interface for managing providers
class ProviderRegistry {
public:
    virtual ~ProviderRegistry() = default;
    
    virtual void register_provider(
        std::string provider_id,
        std::string name,
        std::string description,
        std::vector<std::string> capabilities
    ) = 0;
    
    virtual void unregister_provider(const std::string& provider_id) = 0;
    
    virtual bool has_provider(const std::string& provider_id) const = 0;
    
    virtual ProviderInfo get_provider_info(const std::string& provider_id) const = 0;
    
    virtual std::vector<ProviderInfo> list_providers() const = 0;
    
    // Assess availability for a specific provider
    virtual void assess_provider_availability(const std::string& provider_id) = 0;
    
    // Assess availability for a specific capability on a provider
    virtual void assess_capability_availability(
        const std::string& provider_id,
        const std::string& capability
    ) = 0;
    
    // Get availability state for a specific capability on a provider
    virtual CapabilityAvailability get_capability_availability(
        const std::string& provider_id,
        const std::string& capability
    ) const = 0;
    
    virtual ProviderSelector* get_selector() = 0;
};

// Factory function to create a new registry
std::unique_ptr<ProviderRegistry> create_provider_registry();

}  // namespace rebuntu::interfaces

namespace std {

template <> struct hash<rebuntu::interfaces::ProviderId> {
    size_t operator()(const rebuntu::interfaces::ProviderId& id) const noexcept {
        return std::hash<std::string>{}(id.value);
    }
};

// Hash for CapabilityAvailabilityState
template <> struct hash<rebuntu::interfaces::CapabilityAvailabilityState> {
    size_t operator()(rebuntu::interfaces::CapabilityAvailabilityState state) const noexcept {
        return std::hash<int>{}(static_cast<int>(state));
    }
};

}  // namespace std