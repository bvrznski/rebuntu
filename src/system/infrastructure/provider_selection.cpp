// rebuntu::infrastructure::ProviderSelection — Implementation (Phase 3.13)
//
// This provides the runtime implementation for provider selection.

#include <system/infrastructure/provider_selection.hpp>

#include <algorithm>
#include <filesystem>
#include <optional>
#include <string>
#include <vector>

namespace rebuntu::infrastructure {

// ============================================================================
// ProviderSelector constructor implementation
// ============================================================================

ProviderSelector::ProviderSelector(std::chrono::seconds cache_ttl)
    : cache_timestamp_(std::chrono::system_clock::now()),
      cache_ttl_(cache_ttl) {}

// ============================================================================
// ProviderSelector implementation
// ============================================================================

std::vector<ProviderInfo> ProviderSelector::discover_providers() {
    // If cache is fresh, return cached providers
    if (is_cache_fresh() && !cached_providers_.empty()) {
        return cached_providers_;
    }
    
    // Perform discovery
    cached_providers_ = do_discover_providers();
    cache_timestamp_ = std::chrono::system_clock::now();
    
    return cached_providers_;
}

ProviderSelectionResult ProviderSelector::select_provider(
    const ProviderSelectionContext& context) {
    ProviderSelectionResult result;
    result.status = core::SemanticStatus::kUnknown;
    
    // Discover providers (uses cache if fresh)
    auto candidates = discover_providers();
    result.candidates = candidates;
    
    // Filter by capability first
    std::vector<ProviderInfo> capability_filtered;
    for (const auto& provider : candidates) {
        if (capability_supported(provider, context.capability)) {
            capability_filtered.push_back(provider);
        }
    }
    
    // Apply policy-based filtering
    auto policy_filtered = apply_policy_filtering(
        capability_filtered, context.policy, context.scope);
    
    // Select best provider from filtered candidates
    result.selected = select_from_candidates(policy_filtered, context.preferred_type);
    
    if (result.selected.has_value()) {
        result.status = core::SemanticStatus::kSuccess;
        
        // Build evidence
        result.evidence.push_back(make_evidence(
            "provider_selection",
            "selection completed successfully"));
        
        return result;
    }
    
    // No provider found - document rejected providers
    for (const auto& candidate : candidates) {
        if (!capability_supported(candidate, context.capability)) {
            result.rejected.push_back({candidate, "capability not supported"});
        } else if (policy_filtered.empty()) {
            result.rejected.push_back({candidate, "excluded by policy"});
        }
    }
    
    return result;
}

std::vector<ProviderInfo> ProviderSelector::do_discover_providers() {
    std::vector<ProviderInfo> providers;
    
    // Discover native Linux providers (systemd)
    auto systemd_info = discover_systemd_provider();
    if (systemd_info.has_value()) {
        providers.push_back(*systemd_info);
    }
    
    // Discover Docker provider
    auto docker_info = discover_docker_provider();
    if (docker_info.has_value()) {
        providers.push_back(*docker_info);
    }
    
    // Discover Ansible provider
    auto ansible_info = discover_ansible_provider();
    if (ansible_info.has_value()) {
        providers.push_back(*ansible_info);
    }
    
    return providers;
}

std::optional<ProviderInfo> ProviderSelector::discover_systemd_provider() {
    std::filesystem::path systemd_path = "/bin/systemctl";
    
    if (!std::filesystem::exists(systemd_path)) {
        return std::nullopt;
    }
    
    auto now = std::chrono::system_clock::now();
    
    // Initialize in field order: id, type, name, status, priority, capabilities,
    // native, version, executable, checked_at, description
    ProviderInfo info{};
    info.id = "native:systemd";
    info.type = NativeProviderType::kNative;
    info.name = "Systemd Service Manager";
    info.status = ProviderStatus::kAvailable;
    info.priority = 10;  // High priority for native providers
    info.capabilities = {"service.control", "service.status"};
    info.native = true;
    info.checked_at = now;
    info.executable = "/bin/systemctl";
    
    return info;
}

std::optional<ProviderInfo> ProviderSelector::discover_docker_provider() {
    std::filesystem::path docker_path = "/usr/bin/docker";
    
    if (!std::filesystem::exists(docker_path)) {
        return std::nullopt;
    }
    
    auto now = std::chrono::system_clock::now();
    
    // Initialize in field order
    ProviderInfo info{};
    info.id = "docker:cli";
    info.type = NativeProviderType::kDocker;
    info.name = "Docker CLI";
    info.status = ProviderStatus::kAvailable;
    info.priority = 100;  // Lower priority than native
    info.capabilities = {"container.run", "container.list"};
    info.native = false;
    info.checked_at = now;
    info.executable = "/usr/bin/docker";
    
    return info;
}

std::optional<ProviderInfo> ProviderSelector::discover_ansible_provider() {
    std::filesystem::path ansible_path = "/usr/bin/ansible-playbook";
    
    if (!std::filesystem::exists(ansible_path)) {
        return std::nullopt;
    }
    
    auto now = std::chrono::system_clock::now();
    
    // Initialize in field order
    ProviderInfo info{};
    info.id = "ansible:cli";
    info.type = NativeProviderType::kAnsible;
    info.name = "Ansible CLI";
    info.status = ProviderStatus::kAvailable;
    info.priority = 100;  // Lower priority than native
    info.capabilities = {"configuration.manage"};
    info.native = false;
    info.checked_at = now;
    info.executable = "/usr/bin/ansible-playbook";
    
    return info;
}

std::vector<ProviderInfo> ProviderSelector::apply_policy_filtering(
    const std::vector<ProviderInfo>& candidates,
    SelectionPolicy policy,
    Scope /* scope */) {
    switch (policy) {
        case SelectionPolicy::kNativeFirst: {
            // Only return native providers
            std::vector<ProviderInfo> result;
            for (const auto& p : candidates) {
                if (p.native) {
                    result.push_back(p);
                }
            }
            return result;
        }
        case SelectionPolicy::kAllowExternal:
            // Return all candidates
            return candidates;
        case SelectionPolicy::kExternalOnly: {
            // Only non-native providers
            std::vector<ProviderInfo> result;
            for (const auto& p : candidates) {
                if (!p.native) {
                    result.push_back(p);
                }
            }
            return result;
        }
    }
    
    // Default to allowing all
    return candidates;
}

std::optional<ProviderInfo> ProviderSelector::select_from_candidates(
    const std::vector<ProviderInfo>& candidates,
    std::optional<NativeProviderType> preferred_type) {
    if (candidates.empty()) {
        return std::nullopt;
    }
    
    // If a preference is specified, try to find it first
    if (preferred_type.has_value()) {
        for (const auto& p : candidates) {
            if (p.type == *preferred_type) {
                return p;
            }
        }
    }
    
    // Otherwise, select by priority (lowest = highest priority)
    const ProviderInfo* best = nullptr;
    for (const auto& p : candidates) {
        if (!best || p.priority < best->priority) {
            best = &p;
        }
    }
    
    return *best;
}

bool ProviderSelector::capability_supported(
    const ProviderInfo& provider, const std::string& capability) const {
    // Check if capability matches any of the provider's capabilities
    for (const auto& cap : provider.capabilities) {
        if (cap == capability) {
            return true;
        }
    }
    
    return false;
}

core::Evidence ProviderSelector::make_evidence(
    std::string source, std::string value) {
    auto now = std::chrono::system_clock::now();
    auto time_str = std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(
        now.time_since_epoch()).count());
    
    // Build evidence with captured_at as a timestamp string
    return core::Evidence{
        .source = source,
        .value = value,
        .captured_at = time_str + "Z"
    };
}

// ============================================================================
// ProviderAdapter implementation
// ============================================================================

ProviderAdapter::ProviderAdapter(ProviderInfo provider)
    : provider_(std::move(provider)) {}

bool ProviderAdapter::is_available() const {
    return provider_.status == ProviderStatus::kAvailable;
}

}  // namespace rebuntu::infrastructure