// rebuntu::interfaces::provider_registry — Provider selection interface
// Phase 0.16: Interfaces, Adapters, Providers & System Boundaries
//
// This header establishes Rebuntu's provider registry pattern:
// how external tools/providers can be discovered, registered, selected,
// and invoked for infrastructure capabilities.

#pragma once

#include <string>
#include <vector>

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

// ProviderAvailability - Provider availability state
enum class ProviderAvailability {
    kUnknown,
    kAvailable,
    kUnavailable,
    kNotInstalled,
};

inline std::string to_string(ProviderAvailability a) {
    switch (a) {
        case ProviderAvailability::kUnknown:      return "unknown";
        case ProviderAvailability::kAvailable:    return "available";
        case ProviderAvailability::kUnavailable:  return "unavailable";
        case ProviderAvailability::kNotInstalled: return "not_installed";
    }
    return "unknown";
}

// ProviderInfo - Static information about a provider
struct ProviderInfo {
    ProviderId id;
    std::string name;
    std::string description;
    std::string version;
    std::string executable_path;
    
    ProviderAvailability availability = ProviderAvailability::kUnknown;
    
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
    
    virtual void assess_availability(const std::string& provider_id) = 0;
    
    virtual ProviderSelector* get_selector() = 0;
};

}  // namespace rebuntu::interfaces