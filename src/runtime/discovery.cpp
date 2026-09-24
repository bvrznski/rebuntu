// rebuntu::runtime::discovery — Naming, Namespaces, Registries & Discovery (Phase 0.19)
//
// Implementation of discovery mechanisms: shell verb detection, alias resolution,
// filesystem scanning, and provider selection.

#include "discovery.hpp"

namespace rebuntu::runtime::discovery {

// ============================================================================
// ShellVerbDetector implementation
// ============================================================================

bool ShellVerbDetector::is_verb_free(const std::string& verb) const {
    auto it = collisions_.find(std::string(verb));
    if (it != collisions_.end()) {
        return it->second.status == ShellVerbStatus::FREE;
    }
    
    // Check if in reserved verbs
    if (reserved_verbs_.contains(std::string(verb))) {
        return false;
    }
    
    return true;
}

ShellVerbCollisionInfo ShellVerbDetector::detect(const std::string& verb) const {
    ShellVerbCollisionInfo info;
    info.verb = std::string(verb);
    
    // Check if reserved
    if (reserved_verbs_.contains(std::string(verb))) {
        info.status = ShellVerbStatus::REBUNTU;
        return info;
    }
    
    auto it = collisions_.find(std::string(verb));
    if (it != collisions_.end()) {
        return it->second;
    }
    
    // Not found means free
    info.status = ShellVerbStatus::FREE;
    return info;
}

void ShellVerbDetector::add_reserved_verb(std::string verb) {
    reserved_verbs_.insert(verb);
    
    // Update collision map if needed
    auto it = collisions_.find(verb);
    if (it != collisions_.end()) {
        it->second.status = ShellVerbStatus::REBUNTU;
    } else {
        ShellVerbCollisionInfo info;
        info.verb = verb;
        info.status = ShellVerbStatus::REBUNTU;
        collisions_[verb] = info;
    }
}

// ============================================================================
// AliasResolver implementation
// ============================================================================

void AliasResolver::add_alias(Alias alias) {
    aliases_[alias.alias_id] = std::move(alias);
}

bool AliasResolver::contains(const std::string& alias_id) const {
    return aliases_.contains(std::string(alias_id));
}

std::optional<std::string> AliasResolver::resolve(const std::string& alias_id) const {
    auto it = aliases_.find(std::string(alias_id));
    if (it != aliases_.end()) {
        return it->second.canonical_id;
    }
    return std::nullopt;
}

// ============================================================================
// FilesystemScanner implementation
// ============================================================================

FilesystemScanner::FilesystemScanner(std::vector<DiscoveryPath> paths)
    : paths_(std::move(paths)) {}

std::vector<std::string> FilesystemScanner::scan_all() const {
    std::set<std::string> results;
    
    for (const auto& path_config : paths_) {
        if (!std::filesystem::exists(path_config.path)) {
            continue;
        }
        
        std::error_code ec;
        auto iter = std::filesystem::directory_iterator(path_config.path, ec);
        if (ec) {
            continue;
        }
        
        for (const auto& entry : iter) {
            if (entry.is_regular_file(ec)) {
                std::string filename = entry.path().filename().string();
                
                // Check allowed extensions
                bool valid_extension = path_config.allowed_extensions.empty();
                if (!path_config.allowed_extensions.empty()) {
                    std::string ext = entry.path().extension().string();
                    valid_extension = path_config.allowed_extensions.contains(ext);
                }
                
                if (valid_extension) {
                    results.insert(filename);
                }
            }
            
            if (path_config.recursive && entry.is_directory(ec)) {
                // Recursive scanning not fully implemented yet
            }
        }
    }
    
    return std::vector<std::string>(results.begin(), results.end());
}

std::vector<std::filesystem::path> FilesystemScanner::find_by_pattern(
    const std::filesystem::path& pth,
    const std::string& pattern) const {
    std::vector<std::filesystem::path> results;
    
    if (!std::filesystem::exists(pth)) {
        return results;
    }
    
    std::error_code ec;
    auto iter = std::filesystem::directory_iterator(pth, ec);
    if (ec) {
        return results;
    }
    
    for (const auto& entry : iter) {
        if (entry.is_regular_file(ec)) {
            std::string filename = entry.path().filename().string();
            // Simple substring matching for pattern
            if (filename.find(pattern.data()) != std::string::npos) {
                results.push_back(entry.path());
            }
        }
    }
    
    return results;
}

// ============================================================================
// ProviderSelector implementation
// ============================================================================

ProviderSelector::ProviderSelector(std::vector<core::OperationDefinition> ops) {
    for (const auto& op : ops) {
        operations_[op.id] = op;
    }
}

core::Result<std::vector<SelectedProvider>> ProviderSelector::select(
    const ProviderSelectionCriteria& criteria) const {
    
    core::Result<std::vector<SelectedProvider>> result;
    std::vector<SelectedProvider> selected;
    
    // Find operations matching the capability
    for (const auto& [id, op] : operations_) {
        if (id == criteria.capability_id || op.subject_type == criteria.capability_id) {
            // Add providers from this operation
            for (const auto& provider_id : op.provider_ids) {
                SelectedProvider sp;
                sp.provider_id = provider_id;
                sp.native_mechanism = op.subject_type;  // Simplified: use subject type as mechanism
                
                // Check if preferred
                sp.is_preferred = std::find(
                    criteria.preferred_providers.begin(),
                    criteria.preferred_providers.end(),
                    provider_id
                ) != criteria.preferred_providers.end();
                
                selected.push_back(sp);
            }
        }
    }
    
    // Apply selection mode - all modes return the full list for now
    result.value = selected;
    result.status = core::SemanticStatus::kSuccess;
    return result;
}

}  // namespace rebuntu::runtime::discovery