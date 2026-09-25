// rebuntu::runtime::loader — Safe Runtime Definition Loader Implementation (Phase 4.9)
//
// Implementation of safe runtime definition loading for Rebuntu.
// See loader.hpp for documentation on the Loader API and responsibilities.

#include "runtime/loader.hpp"

#include <filesystem>
#include <fstream>
#include <optional>
#include <set>

namespace rebuntu::runtime::loader {

// ============================================================================
// Helper functions (forward declarations needed before class methods)
// ============================================================================

static bool is_subpath(const std::filesystem::path& base, const std::filesystem::path& candidate) {
    auto canonical_base = std::filesystem::canonical(base);
    auto canonical_candidate = std::filesystem::canonical(candidate);
    
    auto it1 = canonical_base.begin();
    auto it2 = canonical_candidate.begin();
    
    while (it1 != canonical_base.end() && it2 != canonical_candidate.end()) {
        if (*it1 != *it2) return false;
        ++it1;
        ++it2;
    }
    
    return it1 == canonical_base.end();  // Base must be fully consumed
}

static std::vector<LoadResult> load_directory(const std::filesystem::path& pth, LoadKind kind, const LoaderConfig& config) {
    std::vector<LoadResult> results;
    std::error_code ec;
    
    for (auto iter = std::filesystem::directory_iterator(pth, ec); 
         iter != std::filesystem::directory_iterator(); 
         ++iter) {
        if (ec) break;
        
        const auto& entry = *iter;
        if (!entry.is_regular_file(ec)) continue;
        
        auto ext = entry.path().extension().string();
        bool found_ext = false;
        
        for (const auto& cfg_ext : config.definition_extensions) {
            if (ext == cfg_ext) {
                found_ext = true;
                break;
            }
        }
        
        if (!found_ext && !config.definition_extensions.empty()) continue;
        
        // For now, just record the file was found - actual loading would be done here
        // This is a stub implementation to demonstrate the structure
        
        results.push_back(LoadResult{
            LoadResultStatus::kSkipped,
            std::nullopt,
            {entry.path().string() + " - directory scan"},
            LoadError{LoadErrorCode::kUntrustedSource, "skipped in stub", entry.path(), 0}
        });
    }
    
    return results;
}

// ============================================================================
// Loader implementation
// ============================================================================

Loader::Loader() : config_{} {
    // Default configuration - no trusted paths set
}

Loader::Loader(LoaderConfig config) : config_(std::move(config)) {
    // Configuration provided by caller
}

LoadResult Loader::load_from_path(const std::filesystem::path& pth, LoadKind kind) {
    std::error_code ec;
    
    if (!std::filesystem::exists(pth, ec)) {
        return LoadResult::failure(LoadError::not_found(pth));
    }
    
    if (ec) {
        auto err = LoadError{LoadErrorCode::kPermissionDenied,
                             "Cannot access file", pth, 0};
        return LoadResult::failure(err);
    }
    
    // Check file size limit
    auto file_size = std::filesystem::file_size(pth, ec);
    if (ec || file_size > config_.max_file_size_bytes) {
        auto err = LoadError{LoadErrorCode::kPermissionDenied,
                             "File too large or access error", pth, 0};
        return LoadResult::failure(err);
    }
    
    // Basic validation
    bool is_trusted = is_trusted_path(pth);
    
    LoadResult result;
    
    std::ifstream file(pth);
    if (!file) {
        result.status = LoadResultStatus::kFailure;
        result.error = LoadError{LoadErrorCode::kPermissionDenied,
                                 "Cannot open file for reading", pth, 0};
        return result;
    }
    
    // Read content to verify it's readable
    std::string line;
    if (std::getline(file, line)) {
        // Basic structure check - could be expanded for schema validation
    }
    
    DefinitionMetadata meta;
    meta.kind = kind;
    meta.source_path = pth;
    meta.schema_valid = true;
    result.metadata = meta;
    result.status = LoadResultStatus::kSuccess;
    
    return result;
}

std::vector<LoadResult> Loader::load_trusted(LoadKind kind) {
    std::vector<LoadResult> results;
    
    for (const auto& config_dir : config_.trusted_paths.config_dir) {
        if (std::filesystem::exists(config_dir)) {
            auto dir_results = load_directory(config_dir, kind, config_);
            results.insert(results.end(), dir_results.begin(), dir_results.end());
        }
    }
    
    for (const auto& share_dir : config_.trusted_paths.share_dir) {
        if (std::filesystem::exists(share_dir)) {
            auto dir_results = load_directory(share_dir, kind, config_);
            results.insert(results.end(), dir_results.begin(), dir_results.end());
        }
    }
    
    return results;
}

std::vector<LoadResult> Loader::load_all(LoadKind kind) {
    std::vector<LoadResult> results;
    
    auto trusted = load_trusted(kind);
    results.insert(results.end(), trusted.begin(), trusted.end());
    
    if (config_.allow_untrusted) {
        for (const auto& local_dir : config_.trusted_paths.local_dir) {
            if (std::filesystem::exists(local_dir)) {
                auto dir_results = load_directory(local_dir, kind, config_);
                results.insert(results.end(), dir_results.begin(), dir_results.end());
            }
        }
    }
    
    return results;
}

std::vector<LoadResult> Loader::load_untrusted(const std::filesystem::path& pth, LoadKind kind) {
    if (!config_.allow_untrusted && config_.strict_validation_only) {
        return {};  // Return empty - not an error, just skipped
    }
    
    if (!std::filesystem::exists(pth)) {
        auto err = LoadError{LoadErrorCode::kFileNotFound,
                             "Directory not found", pth, 0};
        return {LoadResult::failure(err)};
    }
    
    return load_directory(pth, kind, config_);
}

auto Loader::get(const DefinitionId& id) const -> std::optional<DefinitionMetadata> {
    auto it = registry_.find(id);
    if (it != registry_.end()) {
        return it->second;
    }
    return std::nullopt;
}

bool Loader::contains(const DefinitionId& id) const {
    return registry_.find(id) != registry_.end();
}

std::vector<DefinitionId> Loader::list_all() const {
    std::vector<DefinitionId> ids;
    ids.reserve(registry_.size());
    
    for (const auto& [id, meta] : registry_) {
        ids.push_back(id);
    }
    
    return ids;
}

std::vector<DefinitionMetadata> Loader::list_by_kind(LoadKind kind) const {
    std::vector<DefinitionMetadata> results;
    
    for (const auto& [id, meta] : registry_) {
        if (meta.kind == kind) {
            results.push_back(meta);
        }
    }
    
    return results;
}

void Loader::clear() {
    registry_.clear();
    load_errors_.clear();
}

std::vector<LoadResult> Loader::reload_trusted(LoadKind kind) {
    clear();
    return load_trusted(kind);
}

bool Loader::can_accept(const std::filesystem::path& pth, LoadKind kind) const {
    (void)kind;  // suppress unused warning - can_accept doesn't need kind for now
    
    if (!std::filesystem::exists(pth)) {
        return false;
    }
    
    auto ext = pth.extension().string();
    bool has_valid_ext = false;
    for (const auto& valid_ext : config_.definition_extensions) {
        if (ext == valid_ext) {
            has_valid_ext = true;
            break;
        }
    }
    
    if (!has_valid_ext && !config_.definition_extensions.empty()) {
        return false;
    }
    
    std::error_code ec;
    auto size = std::filesystem::file_size(pth, ec);
    if (ec || size > config_.max_file_size_bytes) {
        return false;
    }
    
    return true;
}

bool Loader::is_trusted_path(const std::filesystem::path& pth) const {
    for (const auto& path : config_.trusted_paths.config_dir) {
        if (is_subpath(path, pth)) return true;
    }
    
    for (const auto& path : config_.trusted_paths.share_dir) {
        if (is_subpath(path, pth)) return true;
    }
    
    for (const auto& path : config_.trusted_paths.local_dir) {
        if (is_subpath(path, pth)) return true;
    }
    
    return false;
}

LoadResult Loader::validate_and_load(const std::filesystem::path& pth, LoadKind kind) {
    return load_from_path(pth, kind);
}

LoadResult Loader::parse_metadata(const std::filesystem::path& pth, LoadKind kind) {
    (void)pth;  // suppress unused warning
    
    DefinitionMetadata meta;
    meta.kind = kind;
    
    return LoadResult::success(meta);
}

bool Loader::detect_cycle(const DefinitionId& id, std::set<DefinitionId>& visiting) const {
    if (visiting.contains(id)) {
        return true;
    }
    
    auto it = registry_.find(id);
    if (it == registry_.end()) {
        return false;
    }
    
    visiting.insert(id);
    
    for (const auto& dep : it->second.dependencies) {
        if (detect_cycle(dep, visiting)) {
            return true;
        }
    }
    
    visiting.erase(id);
    return false;
}

// ============================================================================
// LoaderBuilder implementation
// ============================================================================

LoaderBuilder::LoaderBuilder() : config_{} {
    // Initialize with reasonable defaults
}

LoaderBuilder& LoaderBuilder::set_trusted_paths(TrustedPaths paths) {
    config_.trusted_paths = std::move(paths);
    return *this;
}

LoaderBuilder& LoaderBuilder::add_trusted_config_dir(std::filesystem::path pth) {
    config_.trusted_paths.config_dir.push_back(std::move(pth));
    return *this;
}

LoaderBuilder& LoaderBuilder::add_trusted_share_dir(std::filesystem::path pth) {
    config_.trusted_paths.share_dir.push_back(std::move(pth));
    return *this;
}

LoaderBuilder& LoaderBuilder::allow_untrusted(bool allow) {
    config_.allow_untrusted = allow;
    return *this;
}

LoaderBuilder& LoaderBuilder::set_max_file_size(size_t bytes) {
    config_.max_file_size_bytes = bytes;
    return *this;
}

LoaderBuilder& LoaderBuilder::set_strict_validation(bool strict) {
    config_.strict_validation_only = strict;
    return *this;
}

std::unique_ptr<Loader> LoaderBuilder::build() {
    return std::make_unique<Loader>(config_);
}

}  // namespace rebuntu::runtime::loader