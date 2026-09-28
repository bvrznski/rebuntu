#include <runtime/discovery.hpp>
#include <array>
#include <cstdio>
#include <memory>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

namespace rebuntu::runtime::discovery {

// ============================================================================
// Helper: Execute subprocess via fork/execve with bounded output
// Uses native Linux primitives - no shell command interpretation
// ============================================================================

static std::string execute_subprocess(const char* executable, const std::vector<std::string>& argv) {
    int stdout_pipe[2];
    if (pipe(stdout_pipe) != 0) {
        return "";
    }
    
    pid_t pid = fork();
    if (pid == -1) {
        close(stdout_pipe[0]);
        close(stdout_pipe[1]);
        return "";
    }
    
    if (pid == 0) {
        // Child process
        close(stdout_pipe[0]);
        dup2(stdout_pipe[1], STDOUT_FILENO);
        close(stdout_pipe[1]);
        
        std::vector<char*> c_argv;
        c_argv.push_back(const_cast<char*>(executable));
        for (const auto& arg : argv) {
            c_argv.push_back(const_cast<char*>(arg.c_str()));
        }
        c_argv.push_back(nullptr);
        
        execvp(executable, c_argv.data());
        _exit(127);
    }
    
    // Parent process
    close(stdout_pipe[1]);
    
    std::array<char, 4096> buffer;
    std::string result;
    ssize_t bytes_read;
    
    while ((bytes_read = read(stdout_pipe[0], buffer.data(), buffer.size())) > 0) {
        result.append(buffer.data(), static_cast<size_t>(bytes_read));
        if (result.length() >= 4096) break;  // Bounded output
    }
    
    close(stdout_pipe[0]);
    
    int status = 0;
    waitpid(pid, &status, 0);
    return result;
}

// ============================================================================
// Native PATH traversal helper - check if verb exists without shell execution
// ============================================================================

static bool command_exists_native(const std::string& cmd) {
    const char* path_env = std::getenv("PATH");
    if (!path_env) return false;
    
    std::string path_str(path_env);
    size_t start = 0;
    
    while (start < path_str.length()) {
        size_t end = path_str.find(':', start);
        if (end == std::string::npos) end = path_str.length();
        
        std::string dir = path_str.substr(start, end - start);
        if (!dir.empty() && dir.back() != '/') dir += '/';
        dir += cmd;
        
        // Use access() to check if executable exists and is runnable
        if (access(dir.c_str(), X_OK) == 0) return true;
        
        start = end + 1;
    }
    
    return false;
}

// ShellVerbDetector implementation
bool ShellVerbDetector::is_verb_free(const std::string& verb) const {
    auto it = collisions_.find(verb);
    if (it != collisions_.end()) {
        return it->second.status == ShellVerbStatus::FREE;
    }
    
    if (reserved_verbs_.count(verb)) {
        return false;
    }
    
    // Native PATH traversal without shell execution
    return !command_exists_native(verb);
}

ShellVerbCollisionInfo ShellVerbDetector::detect(const std::string& verb) const {
    ShellVerbCollisionInfo info;
    info.verb = verb;
    
    if (reserved_verbs_.count(verb)) {
        info.status = ShellVerbStatus::REBUNTU;
        return info;
    }
    
    // Native PATH traversal without shell execution
    std::string cmd_path = command_exists_native(verb) ? "FOUND" : "";
    
    if (cmd_path.empty()) {
        info.status = ShellVerbStatus::FREE;
        return info;
    }
    
    info.locations.push_back(cmd_path);
    
    // Determine type via native means (check if shell builtin exists)
    // For now, use simple heuristic: if found in PATH, it's a system command
    // Shell builtins would be detected via separate builtin registry lookup
    info.status = ShellVerbStatus::SYSTEM_COMMAND;
    
    return info;
}

void ShellVerbDetector::add_reserved_verb(std::string verb) {
    reserved_verbs_.insert(std::move(verb));
}

// AliasResolver implementation
void AliasResolver::add_alias(Alias alias) {
    aliases_[std::move(alias.alias_id)] = std::move(alias);
}

bool AliasResolver::contains(const std::string& alias_id) const {
    return aliases_.count(alias_id) > 0;
}

std::optional<std::string> AliasResolver::resolve(const std::string& alias_id) const {
    auto it = aliases_.find(alias_id);
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
    const std::string& pattern) const {
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