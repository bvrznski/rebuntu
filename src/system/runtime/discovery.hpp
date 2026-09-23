// rebuntu::runtime::discovery — Naming, Namespaces, Registries & Discovery (Phase 0.19)
//
// Establishes how Rebuntu names, identifies, locates and discovers capabilities
// without building registry bureaucracy or magical plugin loading.

#pragma once

#include <system/core/contracts.hpp>
#include <algorithm>
#include <filesystem>
#include <map>
#include <set>
#include <string>
#include <string_view>
#include <vector>

namespace rebuntu::runtime::discovery {

// ShellVerbCollisionInfo
enum class ShellVerbStatus {
    FREE,
    REBUNTU,
    SHELL_BUILTIN,
    SYSTEM_COMMAND,
    AMBIGUOUS,
};

inline std::string_view to_string(ShellVerbStatus s) {
    switch (s) {
        case ShellVerbStatus::FREE: return "free";
        case ShellVerbStatus::REBUNTU: return "rebuntu";
        case ShellVerbStatus::SHELL_BUILTIN: return "shell_builtin";
        case ShellVerbStatus::SYSTEM_COMMAND: return "system_command";
        case ShellVerbStatus::AMBIGUOUS: return "ambiguous";
    }
    return "unknown";
}

struct ShellVerbCollisionInfo {
    std::string verb;
    ShellVerbStatus status = ShellVerbStatus::FREE;
    std::vector<std::string> locations;
};

class ShellVerbDetector {
public:
    bool is_verb_free(std::string_view verb) const;
    ShellVerbCollisionInfo detect(std::string_view verb) const;
    void add_reserved_verb(std::string verb);

private:
    mutable std::map<std::string, ShellVerbCollisionInfo> collisions_;
    std::set<std::string> reserved_verbs_;
};

struct Alias {
    std::string alias_id;
    std::string canonical_id;
    std::optional<std::string> description;
};

class AliasResolver {
public:
    void add_alias(Alias alias);
    bool contains(std::string_view alias_id) const;
    std::optional<std::string> resolve(std::string_view alias_id) const;

private:
    std::map<std::string, Alias> aliases_;
};

struct DiscoveryPath {
    std::filesystem::path path;
    bool recursive = false;
    std::set<std::string> allowed_extensions;
};

class FilesystemScanner {
public:
    explicit FilesystemScanner(std::vector<DiscoveryPath> paths = {});
    std::vector<std::string> scan_all() const;
    std::vector<std::filesystem::path> find_by_pattern(
        const std::filesystem::path& pth,
        std::string_view pattern) const;

private:
    std::vector<DiscoveryPath> paths_;
};

enum class ProviderSelectionMode {
    FIRST,
    PREFERRED_FIRST,
    BY_NATIVE_MECHANISM,
    ALL_AVAILABLE,
};

struct ProviderSelectionCriteria {
    std::string capability_id;
    ProviderSelectionMode mode = ProviderSelectionMode::FIRST;
    std::vector<std::string> preferred_providers;
    std::optional<std::string> required_native_mechanism;
};

struct SelectedProvider {
    std::string provider_id;
    std::string native_mechanism;
    bool is_preferred = false;
};

class ProviderSelector {
public:
    explicit ProviderSelector(std::vector<core::OperationDefinition> ops);
    core::Result<std::vector<SelectedProvider>> select(
        const ProviderSelectionCriteria& criteria) const;

private:
    std::map<std::string, core::OperationDefinition> operations_;
};

}  // namespace rebuntu::runtime::discovery
