// rebuntu::infrastructure::container_runtime — Container Provider Registry Implementation (Phase 3.6)
//
// This implements the ContainerProviderRegistry for multi-runtime container support
// including Docker, Podman, and runc.

#include <system/infrastructure/container.hpp>

#include <algorithm>
#include <chrono>
#include <memory>
#include <optional>
#include <stdexcept>
#include <string>
#include <vector>

namespace rebuntu::infrastructure {

void ContainerProviderRegistry::register_provider(std::unique_ptr<ContainerProvider> provider) {
    if (!provider) {
        throw std::invalid_argument("ContainerProviderRegistry: cannot register null provider");
    }
    
    auto type = provider->provider_type();
    providers_[type] = std::move(provider);
}

std::optional<ContainerProvider*> ContainerProviderRegistry::get_provider(ProviderType type) const {
    auto it = providers_.find(type);
    if (it != providers_.end()) {
        return it->second.get();
    }
    return std::nullopt;
}

std::vector<ContainerProvider*> ContainerProviderRegistry::all_providers() const {
    std::vector<ContainerProvider*> result;
    for (const auto& [type, provider] : providers_) {
        result.push_back(provider.get());
    }
    return result;
}

ContainerResult ContainerProviderRegistry::list_containers(
    const std::vector<ContainerState>& states,
    std::optional<std::chrono::milliseconds> timeout
) const {
    // Try to find an available provider
    for (const auto& [type, provider] : providers_) {
        if (provider->is_available()) {
            return provider->list_containers(states, timeout);
        }
    }
    
    return ContainerResult::unavailable("No container runtime provider is available");
}

ContainerResult ContainerProviderRegistry::inspect_container(
    const std::string& container_id_or_name,
    std::optional<std::chrono::milliseconds> timeout
) const {
    for (const auto& [type, provider] : providers_) {
        if (provider->is_available()) {
            return provider->inspect_container(container_id_or_name, timeout);
        }
    }
    
    return ContainerResult::unavailable("No container runtime provider is available");
}

ContainerResult ContainerProviderRegistry::list_images(
    std::optional<std::chrono::milliseconds> timeout
) const {
    for (const auto& [type, provider] : providers_) {
        if (provider->is_available()) {
            return provider->list_images(timeout);
        }
    }
    
    return ContainerResult::unavailable("No container runtime provider is available");
}

ContainerResult ContainerProviderRegistry::pull_image(
    const std::string& image_ref,
    std::optional<std::chrono::milliseconds> timeout
) const {
    for (const auto& [type, provider] : providers_) {
        if (provider->is_available()) {
            return provider->pull_image(image_ref, timeout);
        }
    }
    
    return ContainerResult::unavailable("No container runtime provider is available");
}

ContainerResult ContainerProviderRegistry::inspect_image(
    const std::string& image_id_or_name,
    std::optional<std::chrono::milliseconds> timeout
) const {
    for (const auto& [type, provider] : providers_) {
        if (provider->is_available()) {
            return provider->inspect_image(image_id_or_name, timeout);
        }
    }
    
    return ContainerResult::unavailable("No container runtime provider is available");
}

ContainerResult ContainerProviderRegistry::start_container(
    const std::string& container_id_or_name,
    std::optional<std::chrono::milliseconds> timeout
) const {
    for (const auto& [type, provider] : providers_) {
        if (provider->is_available()) {
            return provider->start_container(container_id_or_name, timeout);
        }
    }
    
    return ContainerResult::unavailable("No container runtime provider is available");
}

ContainerResult ContainerProviderRegistry::stop_container(
    const std::string& container_id_or_name,
    std::optional<std::chrono::milliseconds> timeout
) const {
    for (const auto& [type, provider] : providers_) {
        if (provider->is_available()) {
            return provider->stop_container(container_id_or_name, timeout);
        }
    }
    
    return ContainerResult::unavailable("No container runtime provider is available");
}

ContainerResult ContainerProviderRegistry::remove_container(
    const std::string& container_id_or_name,
    bool force,
    std::optional<std::chrono::milliseconds> timeout
) const {
    for (const auto& [type, provider] : providers_) {
        if (provider->is_available()) {
            return provider->remove_container(container_id_or_name, force, timeout);
        }
    }
    
    return ContainerResult::unavailable("No container runtime provider is available");
}

}  // namespace rebuntu::infrastructure