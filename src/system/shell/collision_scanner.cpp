// rebuntu::shell::collision — Command Collision Detection Scanner Implementation (Phase 6.14)
//
// This module implements systematic collision detection against:
//   - Shell builtins
//   - System commands (PATH executables)
//   - User-defined aliases and functions

#include "collision_scanner.hpp"
#include <array>
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <cstdlib>
#include <sys/stat.h>

namespace rebuntu::shell::collision {

// ============================================================================
// ShellBuiltinRegistry
// ============================================================================

const std::vector<std::string> ShellBuiltinRegistry::kBuiltins = {
    // POSIX/Bash builtins
    ":",          // no-op
    ".",          // source (POSIX)
    "alias",
    "bg",
    "bind",
    "break",
    "case",
    "command",
    "compgen",
    "complete",
    "continue",
    "declare",
    "dirs",
    "echo",
    "enable",
    "eval",
    "exec",
    "exit",
    "export",
    "fc",
    "fg",
    "getopts",
    "hash",
    "help",
    "history",
    "if",
    "jobs",
    "kill",
    "let",
    "local",
    "logout",
    "popd",
    "printf",
    "pushd",
    "pwd",
    "readonly",
    "return",
    "set",
    "shift",
    "shopt",
    "source",
    "suspend",
    "test",
    "times",
    "trap",
    "type",
    "typeset",
    "ulimit",
    "umask",
    "unalias",
    "unset",
    "until",
    "wait",
    "while",
    
    // Bash-specific
    "apply",
    "assoc",
    "cd",
    "coproc",
    " declare",
    "dir",
    "enable",
    "false",
    "help",
    "history",
    "login",
    "mapfile",
    "noglob",
    "popd",
    "printf",
    "pushd",
    "readarray",
    "select",
    "set",
    "shopt",
    "source",
    "true",
    "type",
};

std::vector<std::string> ShellBuiltinRegistry::get_builtins() {
    return kBuiltins;
}

bool ShellBuiltinRegistry::is_builtin(std::string_view word) {
    for (const auto& b : kBuiltins) {
        if (b == word) return true;
    }
    return false;
}

// ============================================================================
// SystemCommandScanner
// ============================================================================

SystemCommandScanner::SystemCommandScanner(const ScannerConfig& config)
    : config_(config) {
    // Get PATH environment variable
    const char* path_env = std::getenv("PATH");
    if (path_env == nullptr) {
        return;
    }
    
    std::string path_str(path_env);
    size_t pos = 0;
    size_t colon_pos;
    
    while ((colon_pos = path_str.find(':', pos)) != std::string::npos && 
           path_directories_.size() < config_.max_path_searches) {
        if (colon_pos > pos) {
            path_directories_.emplace_back(path_str.substr(pos, colon_pos - pos));
        }
        pos = colon_pos + 1;
    }
    
    // Add last directory if any
    if (pos < path_str.size() && path_directories_.size() < config_.max_path_searches) {
        path_directories_.emplace_back(path_str.substr(pos));
    }
}

bool is_executable(const std::string& path) {
    struct stat st;
    if (stat(path.c_str(), &st) != 0) {
        return false;
    }
    return (st.st_mode & S_IXUSR) != 0;
}

std::optional<std::string> SystemCommandScanner::find_command(std::string_view name) const {
    for (const auto& dir : path_directories_) {
        // Check if executable exists in this directory
        std::string exe_path = (dir / std::string{name}).string();
        
        if (std::filesystem::exists(dir / std::string{name})) {
            // Check if it's executable using stat()
            if (is_executable(exe_path)) {
                return exe_path;
            }
        }
        
        // Some systems have .exe extensions or other variants
        std::string alt_path = (dir / (std::string{name} + ".exe")).string();
        if (std::filesystem::exists(dir / (std::string{name} + ".exe")) &&
            is_executable(alt_path)) {
            return alt_path;
        }
    }
    
    return std::nullopt;
}

bool SystemCommandScanner::has_system_command(std::string_view name) const {
    return find_command(name).has_value();
}

std::vector<std::string> SystemCommandScanner::list_path_commands() const {
    std::set<std::string> commands;  // Use set for deduplication
    
    for (const auto& dir : path_directories_) {
        std::error_code ec;
        
        if (!std::filesystem::exists(dir, ec)) continue;
        if (!std::filesystem::is_directory(dir, ec)) continue;
        
        std::filesystem::directory_iterator it(dir, ec);
        if (ec) continue;
        
        for (const auto& entry : it) {
            if (entry.is_regular_file(ec) || entry.is_symlink(ec)) {
                auto filename = entry.path().filename().string();
                
                // Skip files with extensions that typically aren't executables
                // But keep .exe as Windows compatibility
                size_t dot_pos = filename.rfind('.');
                if (dot_pos != std::string::npos) {
                    auto ext = filename.substr(dot_pos);
                    if (ext == ".gz" || ext == ".bz2" || ext == ".xz" ||
                        ext == ".txt" || ext == ".md" || ext == ".html") {
                        continue;
                    }
                }
                
                // Add basename without path
                commands.insert(filename);
            }
            
            // Limit results for bounded discovery
            if (commands.size() >= config_.max_path_searches) {
                break;
            }
        }
        
        if (commands.size() >= config_.max_path_searches) {
            break;
        }
    }
    
    return std::vector<std::string>(commands.begin(), commands.end());
}

// ============================================================================
// UserDefinitionScanner
// ============================================================================

UserDefinitionScanner::UserDefinitionScanner(const ScannerConfig& config)
    : config_(config) {
}

std::vector<std::string> UserDefinitionScanner::get_user_aliases() const {
    // Use 'alias' command to list aliases - this is bounded by the shell itself
    std::vector<std::string> result;
    
    FILE* pipe = popen("alias 2>/dev/null", "r");
    if (!pipe) return result;
    
    char line[1024];
    size_t count = 0;
    
    while (fgets(line, sizeof(line), pipe) != nullptr && count < config_.max_aliases_to_check) {
        // Parse: alias name='value'
        std::string line_str(line);
        
        // Find 'alias ' and extract the name
        size_t pos = line_str.find("alias ");
        if (pos == std::string::npos) continue;
        
        pos += 6;  // Skip "alias "
        
        // Find '=' which marks end of alias name
        size_t eq_pos = line_str.find('=', pos);
        if (eq_pos == std::string::npos) continue;
        
        // Extract name (may contain alphanumeric and underscore)
        std::string name;
        for (size_t i = pos; i < eq_pos; ++i) {
            char c = line_str[i];
            if (std::isalnum(static_cast<unsigned char>(c)) || c == '_') {
                name += c;
            } else {
                break;
            }
        }
        
        if (!name.empty()) {
            result.push_back(name);
            count++;
        }
    }
    
    pclose(pipe);
    return result;
}

std::vector<std::string> UserDefinitionScanner::get_shell_functions() const {
    // Use 'compgen -f' to list shell functions
    std::vector<std::string> result;
    
    FILE* pipe = popen("compgen -f 2>/dev/null", "r");
    if (!pipe) return result;
    
    char line[1024];
    size_t count = 0;
    
    while (fgets(line, sizeof(line), pipe) != nullptr && count < config_.max_functions_to_check) {
        std::string func_name(line);
        
        // Remove trailing newline/whitespace
        while (!func_name.empty() && 
               (func_name.back() == '\n' || func_name.back() == '\r')) {
            func_name.pop_back();
        }
        
        if (!func_name.empty()) {
            result.push_back(func_name);
            count++;
        }
    }
    
    pclose(pipe);
    return result;
}

bool UserDefinitionScanner::is_alias(std::string_view word) const {
    auto aliases = get_user_aliases();
    return std::find(aliases.begin(), aliases.end(), word) != aliases.end();
}

bool UserDefinitionScanner::is_function(std::string_view word) const {
    auto functions = get_shell_functions();
    return std::find(functions.begin(), functions.end(), word) != functions.end();
}

// ============================================================================
// RebuntuReservedRegistry
// ============================================================================

const std::vector<std::string> RebuntuReservedRegistry::kReservedVerbs = {
    // Core shell verbs (Phase 6)
    "add",
    "alias",
    "apply",
    "archive",
    "attach",
    "authorize",
    "backup",
    "build",
    "cache",
    "call",
    "cancel",
    "catdir",
    "check",
    "clean",
    "clone",
    "close",
    "collect",
    "configure",
    "connect",
    "construct",
    "copy",
    "create",
    "decode",
    "decrypt",
    "declare",
    "delete",
    "deploy",
    "detach",
    "detect",
    "disable",
    "disconnect",
    "discover",
    "download",
    "draw",
    "dump",
    "edit",
    "enable",
    "encode",
    "encrypt",
    "ensure",
    "exec",
    "execute",
    "exit",
    "extract",
    "fetch",
    "find",
    "fix",
    "format",
    "generate",
    "get",
    "grep",
    "guard",
    "help",
    "identify",
    "import",
    "indent",
    "init",
    "install",
    "inspect",
    "join",
    "kill",
    "list",
    "load",
    "lock",
    "log",
    "maintain",
    "manage",
    "map",
    "merge",
    "migrate",
    "modify",
    "monitor",
    "move",
    "normalize",
    "observe",
    "open",
    "optimize",
    "organize",
    "pack",
    "package",
    "parse",
    "patch",
    "plan",
    "post",
    "print",
    "process",
    "publish",
    "pull",
    "push",
    "query",
    "quit",
    "rebuild",
    "receive",
    "record",
    "refresh",
    "register",
    "reload",
    "remove",
    "repair",
    "replay",
    "request",
    "reset",
    "resolve",
    "restart",
    "restore",
    "run",
    "save",
    "scan",
    "schedule",
    "search",
    "send",
    "set",
    "setup",
    "sign",
    "start",
    "status",
    "stop",
    "subscribe",
    "sync",
    "tail",
    "tag",
    "tee",
    "test",
    "trace",
    "trigger",
    "unarchive",
    "unlock",
    "unpack",
    "unregister",
    "unset",
    "update",
    "upgrade",
    "upload",
    "use",
    "validate",
    "verify",
    "watch",
    "write",
};

std::vector<std::string> RebuntuReservedRegistry::get_reserved_verbs() {
    return kReservedVerbs;
}

bool RebuntuReservedRegistry::is_reserved(std::string_view word) {
    for (const auto& r : kReservedVerbs) {
        if (r == word) return true;
    }
    return false;
}

// ============================================================================
// CollisionScanner
// ============================================================================

CollisionScanner::CollisionScanner(const ScannerConfig& config)
    : config_(config),
      builtin_registry_(),
      system_scanner_(config),
      user_scanner_(config) {
}

CollisionResult CollisionScanner::scan_verb(std::string_view verb) const {
    CollisionResult result;
    result.verb = std::string{verb};
    
    auto start_time = std::chrono::steady_clock::now();
    
    // Check for shell builtin collision
    if (config_.include_shell_builtins && 
        ShellBuiltinRegistry::is_builtin(verb)) {
        result.class_ = CollisionClass::kShellBuiltin;
        
        CollisionInfo info;
        info.verb = std::string{verb};
        info.class_ = CollisionClass::kShellBuiltin;
        info.is_rebuntu_internal = false;  // Builtins are system-defined
        
        result.info = info;
        return result;
    }
    
    // Check for Rebuntu reserved collision
    if (config_.include_rebuntu_reserved && 
        RebuntuReservedRegistry::is_reserved(verb)) {
        result.class_ = CollisionClass::kReservedRebuntu;
        
        CollisionInfo info;
        info.verb = std::string{verb};
        info.class_ = CollisionClass::kReservedRebuntu;
        info.is_rebuntu_internal = true;
        
        result.info = info;
        return result;
    }
    
    // Check for system command collision
    if (config_.include_system_commands) {
        auto sys_path = system_scanner_.find_command(verb);
        if (sys_path.has_value()) {
            result.class_ = CollisionClass::kSystemCommand;
            
            CollisionInfo info;
            info.verb = std::string{verb};
            info.class_ = CollisionClass::kSystemCommand;
            info.source_path = sys_path;
            info.is_rebuntu_internal = false;
            
            result.info = info;
            return result;
        }
    }
    
    // Check for user-defined alias/function collision
    if (config_.include_user_definitions) {
        if (user_scanner_.is_alias(verb)) {
            result.class_ = CollisionClass::kUserAlias;
            
            CollisionInfo info;
            info.verb = std::string{verb};
            info.class_ = CollisionClass::kUserAlias;
            info.is_rebuntu_internal = false;
            
            // TODO: Get alias definition for more details
            result.info = info;
            return result;
        }
        
        if (user_scanner_.is_function(verb)) {
            result.class_ = CollisionClass::kUserAlias;  // Functions treated same as aliases
            
            CollisionInfo info;
            info.verb = std::string{verb};
            info.class_ = CollisionClass::kUserAlias;
            info.is_rebuntu_internal = false;
            
            // TODO: Get function source for more details
            result.info = info;
            return result;
        }
    }
    
    // No collision found
    result.class_ = CollisionClass::kNone;
    
    auto end_time = std::chrono::steady_clock::now();
    result.scan_duration_ms = 
        std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
    
    return result;
}

std::vector<CollisionResult> CollisionScanner::scan_verbs(
    const std::vector<std::string>& verbs) const {
    std::vector<CollisionResult> results;
    
    for (const auto& verb : verbs) {
        results.push_back(scan_verb(verb));
    }
    
    return results;
}

CollisionScanner::Report CollisionScanner::generate_report(
    const std::vector<std::string>& verbs) const {
    Report report;
    
    for (const auto& verb : verbs) {
        auto result = scan_verb(verb);
        report.results.push_back(result);
        
        switch (result.class_) {
            case CollisionClass::kShellBuiltin:
                report.shell_builtins++;
                report.total_collisions++;
                break;
            case CollisionClass::kSystemCommand:
                report.system_commands++;
                report.total_collisions++;
                break;
            case CollisionClass::kUserAlias:
                report.user_definitions++;
                report.total_collisions++;
                break;
            case CollisionClass::kReservedRebuntu:
                // Reserved verbs don't count as collisions
                break;
            default:
                break;
        }
    }
    
    return report;
}

// ============================================================================
// Utility functions
// ============================================================================

CollisionClass get_collision_status(std::string_view verb) {
    ScannerConfig config = default_config();
    CollisionScanner scanner(config);
    
    auto result = scanner.scan_verb(verb);
    return result.class_;
}

std::string format_collision_info(const CollisionInfo& info) {
    std::ostringstream oss;
    
    oss << "Collision: " << to_string(info.class_) << "\n";
    oss << "  Verb:      " << info.verb << "\n";
    
    if (info.source_path.has_value()) {
        oss << "  Path:      " << info.source_path.value() << "\n";
    }
    
    if (info.alias_definition.has_value()) {
        oss << "  Alias:     " << info.alias_definition.value() << "\n";
    }
    
    if (info.function_source.has_value()) {
        oss << "  Function:  " << info.function_source.value() << "\n";
    }
    
    return oss.str();
}

}  // namespace rebuntu::shell::collision