// rebuntu::interfaces::ProviderRegistryImpl — Concrete provider registry implementation
// Phase 0.16: Interfaces, Adapters, Providers & System Boundaries

#include "provider_registry.hpp"
#include <algorithm>
#include <filesystem>
#include <map>

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
        // Find all providers that support this capability
        std::vector<std::string> available_providers;
        
        for (const auto& info : providers_) {
            bool supports_capability = std::find(
                info.supported_capabilities.begin(),
                info.supported_capabilities.end(),
                capability
            ) != info.supported_capabilities.end();
            
            if (supports_capability && is_available(info.availability)) {
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
                
                return supports_capability && is_available(info.availability);
            }
        }
        
        return false;
    }

private:
    static bool is_available(ProviderAvailability availability) {
        return availability == ProviderAvailability::kAvailable ||
               availability == ProviderAvailability::kUnknown;
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
        info.availability = ProviderAvailability::kUnknown;
        
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
    
    void assess_availability(const std::string& provider_id) override {
        auto it = providers_.find(provider_id);
        if (it == providers_.end()) {
            return;
        }
        
        if (!it->second.executable_path.empty()) {
            std::error_code ec;
            if (std::filesystem::exists(it->second.executable_path, ec)) {
                it->second.availability = ProviderAvailability::kAvailable;
            } else {
                it->second.availability = ProviderAvailability::kNotInstalled;
            }
        } else {
            if (it->second.availability == ProviderAvailability::kUnknown) {
                it->second.availability = ProviderAvailability::kAvailable;
            }
        }
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