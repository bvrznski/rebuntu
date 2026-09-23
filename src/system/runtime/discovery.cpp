#include <system/runtime/discovery.hpp>
#include <array>
#include <cstdio>
#include <memory>

namespace rebuntu::runtime::discovery {

// Helper: Execute a shell command and capture output
static std::string exec_command(const std::string& cmd) {
    std::array<char, 1024> buffer;
    std::string result;
    
    auto pipe = std::unique_ptr<FILE, decltype(&pclose)>(popen(cmd.c_str(), "r"), pclose);
    if (!pipe) {
        return "";
    }
    
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    
    while (!result.empty() && (result.back() == '\n' || result.back() == ' ')) {
        result.pop_back();
    }
    
    return result;
}

// ShellVerbDetector implementation
bool ShellVerbDetector::is_verb_free(std::string_view verb) const {
    auto it = collisions_.find(std::string{verb});
    if (it != collisions_.end()) {
        return it->second.status == ShellVerbStatus::FREE;
    }
    
    if (reserved_verbs_.count(std::string{verb})) {
        return false;
    }
    
    auto cmd = "command -v " + std::string{verb} + " >/dev/null 2>&1 && echo FOUND || echo MISSING";
    auto output = exec_command(cmd);
    
    if (output == "FOUND") {
        return false;
    }
    
    return true;
}

ShellVerbCollisionInfo ShellVerbDetector::detect(std::string_view verb) const {
    ShellVerbCollisionInfo info;
    info.verb = std::string{verb};
    
    if (reserved_verbs_.count(std::string{verb})) {
        info.status = ShellVerbStatus::REBUNTU;
        return info;
    }
    
    auto cmd = "command -v " + std::string{verb} + " 2>&1";
    auto output = exec_command(cmd);
    
    if (output.empty()) {
        info.status = ShellVerbStatus::FREE;
        return info;
    }
    
    info.locations.push_back(output);
    
    auto type_cmd = "type -t " + std::string{verb} + " 2>&1";
    auto type_output = exec_command(type_cmd);
    
    if (type_output == "builtin") {
        info.status = ShellVerbStatus::SHELL_BUILTIN;
    } else if (!output.empty()) {
        info.status = ShellVerbStatus::SYSTEM_COMMAND;
    } else {
        info.status = ShellVerbStatus::FREE;
    }
    
    return info;
}

void ShellVerbDetector::add_reserved_verb(std::string verb) {
    reserved_verbs_.insert(std::move(verb));
}

// AliasResolver implementation
void AliasResolver::add_alias(Alias alias) {
    aliases_[std::move(alias.alias_id)] = std::move(alias);
}

bool AliasResolver::contains(std::string_view alias_id) const {
    return aliases_.count(std::string{alias_id}) > 0;
}

std::optional<std::string> AliasResolver::resolve(std::string_view alias_id) const {
    auto it = aliases_.find(std::string{alias_id});
    if (it == aliases_.end()) return std::nullopt;
    return it->second.canonical_id;
}

// FilesystemScanner implementation
FilesystemScanner::FilesystemScanner(std::vector<DiscoveryPath> paths)
    : paths_(std::move(paths)) {}

std::vector<std::string> FilesystemScanner::scan_all() const {
    std::set<std::string> result;
    
    for (const auto& path : paths_) {
        if (!std::filesystem::exists(path.path)) continue;
        
        // Non-recursive scan of directory
        for (const auto& entry : std::filesystem::directory_iterator(path.path)) {
            if (entry.is_regular_file()) {
                auto ext = entry.path().extension().string();
                
                if (!path.allowed_extensions.empty() && 
                    path.allowed_extensions.count(ext) == 0) {
                    continue;
                }
                
                auto name = entry.path().filename().stem().string();
                if (!name.empty() && name[0] != '_') {
                    result.insert(name);
                }
            }
        }
    }
    
    return std::vector<std::string>(result.begin(), result.end());
}

std::vector<std::filesystem::path> FilesystemScanner::find_by_pattern(
    const std::filesystem::path& pth,
    std::string_view pattern) const {
    std::vector<std::filesystem::path> results;
    
    if (!std::filesystem::exists(pth)) return results;
    
    for (const auto& entry : std::filesystem::directory_iterator(pth)) {
        if (entry.is_regular_file()) {
            auto ext = entry.path().extension().string();
            if (ext == ".cpp" || ext == ".hpp") {
                results.push_back(entry.path());
            }
        }
    }
    
    return results;
}

// ProviderSelector implementation
ProviderSelector::ProviderSelector(std::vector<core::OperationDefinition> ops) {
    for (auto& op : ops) {
        operations_[op.id] = std::move(op);
    }
}

core::Result<std::vector<SelectedProvider>> ProviderSelector::select(
    const ProviderSelectionCriteria& criteria) const {
    
    core::Result<std::vector<SelectedProvider>> result;
    result.status = core::SemanticStatus::kSuccess;
    
    auto it = operations_.find(criteria.capability_id);
    if (it == operations_.end()) {
        result.status = core::SemanticStatus::kFailure;
        result.error = core::Error{"E_CAPABILITY_NOT_FOUND",
            "Capability not found: " + criteria.capability_id};
        return result;
    }
    
    std::vector<SelectedProvider> providers;
    const auto& op = it->second;
    
    for (const auto& provider_id : op.provider_ids) {
        SelectedProvider sp;
        sp.provider_id = provider_id;
        sp.native_mechanism = "generic";
        sp.is_preferred = false;
        
        for (const auto& pref : criteria.preferred_providers) {
            if (pref == provider_id) {
                sp.is_preferred = true;
                break;
            }
        }
        providers.push_back(sp);
    }
    
    result.value = std::move(providers);
    return result;
}

}  // namespace rebuntu::runtime::discovery
