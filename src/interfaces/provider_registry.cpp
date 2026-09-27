// rebuntu::interfaces::ProviderRegistryImpl — Concrete provider registry implementation
// Phase 0.16: Interfaces, Adapters, Providers & System Boundaries

#include "provider_registry.hpp"
#include <algorithm>
#include <filesystem>
#include <map>
#include <system_error>

namespace rebuntu::interfaces {

// ProviderSelectorImpl - Implementation of ProviderSelector interface
class ProviderSelectorImpl : public ProviderSelector {
public:
    explicit ProviderSelectorImpl(std::vector<ProviderInfo> providers)
        : providers_(std::move(providers)) {}
    
    ~ProviderSelectorImpl() override = default;
    
    std::string select_provider(
        const std::string& capability,
        ProviderSelectionPolicy policy
    ) const override {
        // Find all providers that support this capability and have available state
        std::vector<std::string> available_providers;
        
        for (const auto& info : providers_) {
            bool supports_capability = std::find(
                info.supported_capabilities.begin(),
                info.supported_capabilities.end(),
                capability
            ) != info.supported_capabilities.end();
            
            // Check provider's own availability and capability-specific availability
            if (!supports_capability) continue;
            
            bool is_available = is_provider_available(info.availability);
            
            // Also check capability-specific availability if available
            auto cap_it = info.capability_availability.find(capability);
            if (cap_it != info.capability_availability.end()) {
                is_available = is_provider_available(cap_it->second.state);
            }
            
            if (is_available) {
                available_providers.push_back(info.id.value);
            }
        }
        
        if (available_providers.empty()) {
            return "";
        }
        
        switch (policy) {
            case ProviderSelectionPolicy::kAny:
            case ProviderSelectionPolicy::kFirst:
                // Return first available
                return available_providers.front();
            
            case ProviderSelectionPolicy::kPreferred:
                if (!available_providers.empty()) {
                    return available_providers.front();
                }
                return "";
            
            case ProviderSelectionPolicy::kExplicit:
                return "";
        }
        
        return "";
    }
    
    bool can_provide(
        const std::string& capability,
        const std::string& provider_id
    ) const override {
        for (const auto& info : providers_) {
            if (info.id.value == provider_id) {
                bool supports_capability = std::find(
                    info.supported_capabilities.begin(),
                    info.supported_capabilities.end(),
                    capability
                ) != info.supported_capabilities.end();
                
                if (!supports_capability) return false;
                
                // Check provider's availability and capability-specific availability
                bool is_available = is_provider_available(info.availability);
                
                auto cap_it = info.capability_availability.find(capability);
                if (cap_it != info.capability_availability.end()) {
                    is_available = is_provider_available(cap_it->second.state);
                }
                
                return is_available;
            }
        }
        
        return false;
    }

private:
    static bool is_provider_available(CapabilityAvailabilityState availability) {
        // Available states that mean the provider/capability can be used
        return availability == CapabilityAvailabilityState::kAvailable ||
               availability == CapabilityAvailabilityState::kDegraded;
    }
    
    std::vector<ProviderInfo> providers_;
};

// ProviderRegistryImpl - Concrete implementation of ProviderRegistry
class ProviderRegistryImpl : public ProviderRegistry {
public:
    ProviderRegistryImpl() = default;
    ~ProviderRegistryImpl() override = default;
    
    void register_provider(
        std::string provider_id,
        std::string name,
        std::string description,
        std::vector<std::string> capabilities
    ) override {
        ProviderInfo info;
        info.id = ProviderId(std::move(provider_id));
        info.name = std::move(name);
        info.description = std::move(description);
        info.supported_capabilities = std::move(capabilities);
        info.availability = CapabilityAvailabilityState::kUnknown;
        
        // Initialize capability availability states to unknown
        for (const auto& cap : info.supported_capabilities) {
            info.capability_availability[cap] = {};
            info.capability_availability[cap].state = CapabilityAvailabilityState::kUnknown;
        }
        
        providers_[info.id.value] = std::move(info);
        
        rebuild_selector();
    }
    
    void unregister_provider(const std::string& provider_id) override {
        providers_.erase(provider_id);
        rebuild_selector();
    }
    
    bool has_provider(const std::string& provider_id) const override {
        return providers_.find(provider_id) != providers_.end();
    }
    
    ProviderInfo get_provider_info(const std::string& provider_id) const override {
        auto it = providers_.find(provider_id);
        if (it != providers_.end()) {
            return it->second;
        }
        return ProviderInfo{};
    }
    
    std::vector<ProviderInfo> list_providers() const override {
        std::vector<ProviderInfo> result;
        for (const auto& [id, info] : providers_) {
            result.push_back(info);
        }
        std::sort(result.begin(), result.end(),
            [](const auto& a, const auto& b) { return a.id.value < b.id.value; });
        return result;
    }
    
    void assess_provider_availability(const std::string& provider_id) override {
        auto it = providers_.find(provider_id);
        if (it == providers_.end()) {
            return;
        }
        
        // Check executable path if available
        if (!it->second.executable_path.empty()) {
            std::error_code ec;
            if (std::filesystem::exists(it->second.executable_path, ec)) {
                it->second.availability = CapabilityAvailabilityState::kAvailable;
            } else {
                it->second.availability = CapabilityAvailabilityState::kUnsupported;
            }
        } else {
            // If no executable path, mark as available if not explicitly unknown
            if (it->second.availability == CapabilityAvailabilityState::kUnknown) {
                it->second.availability = CapabilityAvailabilityState::kAvailable;
            }
        }
    }
    
    void assess_capability_availability(
        const std::string& provider_id,
        const std::string& capability
    ) override {
        auto it = providers_.find(provider_id);
        if (it == providers_.end()) {
            return;
        }
        
        // Check if this provider supports the capability
        bool supports_cap = std::find(
            it->second.supported_capabilities.begin(),
            it->second.supported_capabilities.end(),
            capability
        ) != it->second.supported_capabilities.end();
        
        if (!supports_cap) {
            it->second.capability_availability[capability].state =
                CapabilityAvailabilityState::kNotApplicable;
            return;
        }
        
        // Check executable path if available
        if (!it->second.executable_path.empty()) {
            std::error_code ec;
            if (std::filesystem::exists(it->second.executable_path, ec)) {
                it->second.capability_availability[capability].state =
                    CapabilityAvailabilityState::kAvailable;
            } else {
                it->second.capability_availability[capability].state =
                    CapabilityAvailabilityState::kUnsupported;
            }
        } else {
            if (it->second.capability_availability[capability].state ==
                CapabilityAvailabilityState::kUnknown) {
                it->second.capability_availability[capability].state =
                    CapabilityAvailabilityState::kAvailable;
            }
        }
    }
    
    CapabilityAvailability get_capability_availability(
        const std::string& provider_id,
        const std::string& capability
    ) const override {
        auto it = providers_.find(provider_id);
        if (it == providers_.end()) {
            return {};
        }
        
        // Check capability-specific availability first
        auto cap_it = it->second.capability_availability.find(capability);
        if (cap_it != it->second.capability_availability.end()) {
            return cap_it->second;
        }
        
        // Fall back to provider-level availability
        CapabilityAvailability result;
        result.state = it->second.availability;
        return result;
    }
    
    ProviderSelector* get_selector() override {
        rebuild_selector();
        return selector_.get();
    }

private:
    void rebuild_selector() {
        std::vector<ProviderInfo> provider_list;
        for (const auto& [id, info] : providers_) {
            provider_list.push_back(info);
        }
        selector_ = std::make_unique<ProviderSelectorImpl>(provider_list);
    }
    
    std::map<std::string, ProviderInfo> providers_;
    std::unique_ptr<ProviderSelector> selector_;
};

// Factory function to create a new registry
std::unique_ptr<ProviderRegistry> create_provider_registry() {
    return std::make_unique<ProviderRegistryImpl>();
}

}  // namespace rebuntu::interfaces