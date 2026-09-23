// rebuntu::environment::config_storage — Configuration File Storage Implementation (Phase 2.11)
#include <system/environment/config_storage.hpp>

#include <cstdlib>
#include <cstring>
#include <fstream>
#include <sstream>
#include <sys/stat.h>
#include <unistd.h>
#include <pwd.h>
#include <cerrno>
#include <filesystem>
#include <iostream>

using rebuntu::environment::scope::ScopeContext;

namespace rebuntu::environment::config_storage {

// ============================================================================
// Core Path Resolution
// ============================================================================

std::filesystem::path get_config_dir(const ScopeContext& ctx) {
    if (ctx.is_root) {
        // System scope: /etc/rebuntu
        return "/etc/rebuntu";
    } else {
        // User scope: $XDG_CONFIG_HOME/rebuntu or ~/.config/rebuntu
        if (ctx.config_dir.has_value()) {
            return *ctx.config_dir;
        }
        
        auto home = std::filesystem::path();
        const char* home_env = std::getenv("HOME");
        if (home_env) {
            home = std::filesystem::path(home_env);
        } else {
            // Fallback to passwd database
            struct passwd pw;
            struct passwd* result = nullptr;
            char buf[4096];
            
            uid_t uid = getuid();
            if (getpwuid_r(uid, &pw, buf, sizeof(buf), &result) == 0 && result) {
                home = std::filesystem::path(result->pw_dir);
            }
        }
        
        if (!home.empty()) {
            return home / ".config" / "rebuntu";
        }
        
        return std::filesystem::path();
    }
}

std::filesystem::path get_config_file_path(
    const ScopeContext& ctx,
    std::string_view filename,
    ConfigFileFormat format) {
    
    auto dir = get_config_dir(ctx);
    if (dir.empty()) {
        return std::filesystem::path();
    }
    
    // Add filename with appropriate extension
    std::string ext;
    switch (format) {
        case ConfigFileFormat::kEnv:   ext = ".env"; break;
        case ConfigFileFormat::kToml:  ext = ".toml"; break;
        case ConfigFileFormat::kJson:  ext = ".json"; break;
        case ConfigFileFormat::kIni:   ext = ".ini"; break;
    }
    
    return dir / (std::string{filename} + ext);
}

ConfigFileLocation discover_config_file(const std::filesystem::path& path) {
    ConfigFileLocation loc;
    loc.path = path;
    
    if (path.empty()) {
        loc.is_valid = false;
        loc.validation_error = "empty path";
        return loc;
    }
    
    std::error_code ec;
    
    if (!std::filesystem::exists(path, ec)) {
        loc.exists = false;
        return loc;
    }
    
    if (!std::filesystem::is_regular_file(path, ec)) {
        loc.is_valid = false;
        loc.validation_error = "path is not a regular file";
        return loc;
    }
    
    loc.exists = true;
    
    // Get file attributes
    struct stat st;
    if (stat(path.string().c_str(), &st) == 0) {
        loc.current_uid = st.st_uid;
        loc.current_gid = st.st_gid;
        loc.current_mode = st.st_mode & 0777;
        
        // Check for world-writable
        if ((loc.current_mode & 0002)) {
            loc.is_valid = false;
            loc.validation_error = "file is world-writable";
        }
    } else {
        loc.validation_error = "failed to stat file";
        loc.is_valid = false;
    }
    
    return loc;
}

// ============================================================================
// Environment File Parsing (KEY=value)
// ============================================================================

ConfigLoadResult load_env_file(const std::filesystem::path& path) {
    ConfigLoadResult result;
    
    if (path.empty()) {
        result.status = core::SemanticStatus::kUnknown;
        result.error_message = "empty path";
        return result;
    }
    
    std::error_code ec;
    if (!std::filesystem::exists(path, ec)) {
        result.status = core::SemanticStatus::kFailure;
        result.error_message = "file does not exist: " + path.string();
        return result;
    }
    
    if (!std::filesystem::is_regular_file(path, ec)) {
        result.status = core::SemanticStatus::kFailure;
        result.error_message = "path is not a regular file";
        return result;
    }
    
    std::ifstream file(path);
    if (!file.is_open()) {
        result.status = core::SemanticStatus::kUnknown;
        result.error_message = "failed to open file: " + path.string();
        return result;
    }
    
    std::string line;
    int line_number = 0;
    
    while (std::getline(file, line)) {
        line_number++;
        
        // Skip empty lines and comments
        if (line.empty() || line[0] == '#') {
            continue;
        }
        
        // Trim whitespace
        size_t start = line.find_first_not_of(" \t\r\n");
        if (start == std::string::npos) continue;
        size_t end = line.find_last_not_of(" \t\r\n");
        line = line.substr(start, end - start + 1);
        
        // Skip comments (after trimming)
        if (line.empty() || line[0] == '#') {
            continue;
        }
        
        // Parse KEY=value
        size_t eq_pos = line.find('=');
        if (eq_pos == std::string::npos) {
            result.status = core::SemanticStatus::kFailure;
            result.error_message = "invalid syntax at line " + std::to_string(line_number);
            return result;
        }
        
        std::string key = line.substr(0, eq_pos);
        std::string value = line.substr(eq_pos + 1);
        
        // Trim whitespace from key and value
        start = key.find_first_not_of(" \t");
        if (start != std::string::npos) {
            end = key.find_last_not_of(" \t");
            key = key.substr(start, end - start + 1);
        }
        
        if (key.empty()) {
            result.status = core::SemanticStatus::kFailure;
            result.error_message = "empty key at line " + std::to_string(line_number);
            return result;
        }
        
        // Handle quoted values
        if (!value.empty() && value[0] == '"') {
            end = value.find_last_of('"');
            if (end != std::string::npos && end > 0) {
                value = value.substr(1, end - 1);
            }
        }
        
        result.values[key] = value;
    }
    
    result.status = core::SemanticStatus::kSuccess;
    return result;
}

ConfigWriteResult save_env_file(
    const std::filesystem::path& path,
    const std::map<std::string, std::string>& values,
    const ConfigStorageOptions& options) {
    
    ConfigWriteResult result;
    result.written_path = path;
    
    if (path.empty()) {
        result.error_message = "empty path";
        return result;
    }
    
    // Build content
    std::ostringstream ss;
    for (const auto& [key, value] : values) {
        // Escape special characters in value if needed
        std::string safe_value = value;
        
        // Check if value contains spaces or special chars that need quoting
        bool needs_quotes = !safe_value.empty() && 
                           (safe_value.find(' ') != std::string::npos ||
                            safe_value.find('=') != std::string::npos ||
                            safe_value.find('#') != std::string::npos);
        
        if (needs_quotes) {
            // Escape internal quotes
            size_t pos = 0;
            while ((pos = safe_value.find('"', pos)) != std::string::npos) {
                safe_value.insert(pos, "\\");
                pos += 2;
            }
            ss << key << "=\"" << safe_value << "\"\n";
        } else {
            ss << key << "=" << safe_value << "\n";
        }
    }
    
    std::string content = ss.str();
    
    if (options.atomic_write) {
        // Use atomic write pattern
        auto write_result = atomic_write_file(path, content, 
                                              options.owner_uid, 
                                              options.owner_gid,
                                              options.file_mode);
        
        result.success = write_result.success;
        result.written_path = write_result.final_path;
        result.error_message = std::move(write_result.error_message);
    } else {
        // Direct write without atomic pattern
        std::error_code ec;
        
        // Create parent directories if needed
        auto parent = path.parent_path();
        if (options.create_parent_dirs && !parent.empty() && 
            !std::filesystem::exists(parent, ec)) {
            
            std::filesystem::create_directories(parent, ec);
            if (ec) {
                result.error_message = "failed to create parent directory: " + ec.message();
                return result;
            }
        }
        
        // Write the file
        std::ofstream file(path);
        if (!file.is_open()) {
            result.error_message = "failed to open file for writing";
            return result;
        }
        
        file << content;
        file.close();
        
        if (file.fail()) {
            result.error_message = "failed to write file content";
            return result;
        }
        
        // Set ownership and permissions
        if (options.owner_uid == 0 || geteuid() == 0) {
            if (chown(path.string().c_str(), options.owner_uid, options.owner_gid) != 0) {
                std::cerr << "warning: failed to chown " << path << ": " 
                          << strerror(errno) << "\n";
            }
            
            if (chmod(path.string().c_str(), options.file_mode) != 0) {
                std::cerr << "warning: failed to chmod " << path << ": " 
                          << strerror(errno) << "\n";
            }
        }
        
        result.success = true;
    }
    
    return result;
}

// ============================================================================
// TOML File Parsing (Simple implementation)
// ============================================================================

ConfigLoadResult load_toml_file(const std::filesystem::path& path) {
    ConfigLoadResult result;
    
    if (path.empty()) {
        result.status = core::SemanticStatus::kUnknown;
        result.error_message = "empty path";
        return result;
    }
    
    std::error_code ec;
    if (!std::filesystem::exists(path, ec)) {
        result.status = core::SemanticStatus::kFailure;
        result.error_message = "file does not exist: " + path.string();
        return result;
    }
    
    if (!std::filesystem::is_regular_file(path, ec)) {
        result.status = core::SemanticStatus::kFailure;
        result.error_message = "path is not a regular file";
        return result;
    }
    
    std::ifstream file(path);
    if (!file.is_open()) {
        result.status = core::SemanticStatus::kUnknown;
        result.error_message = "failed to open file: " + path.string();
        return result;
    }
    
    std::string line;
    int line_number = 0;
    
    // Simple TOML parser for key=value pairs (section headers ignored)
    while (std::getline(file, line)) {
        line_number++;
        
        // Skip empty lines and comments
        if (line.empty() || line[0] == '#') {
            continue;
        }
        
        // Trim whitespace
        size_t start = line.find_first_not_of(" \t\r\n");
        if (start == std::string::npos) continue;
        
        // Skip section headers [section]
        if (line[start] == '[') {
            continue;
        }
        
        size_t end = line.find_last_not_of(" \t\r\n");
        line = line.substr(start, end - start + 1);
        
        // Parse key = value
        size_t eq_pos = line.find('=');
        if (eq_pos == std::string::npos) {
            continue;  // Skip lines without =
        }
        
        std::string key = line.substr(0, eq_pos);
        std::string value = line.substr(eq_pos + 1);
        
        // Trim whitespace
        start = key.find_first_not_of(" \t");
        if (start != std::string::npos) {
            end = key.find_last_not_of(" \t\r\n");
            key = key.substr(start, end - start + 1);
        }
        
        start = value.find_first_not_of(" \t");
        if (start != std::string::npos) {
            end = value.find_last_not_of(" \t\r\n");
            value = value.substr(start, end - start + 1);
        }
        
        // Remove surrounding quotes from value
        if (!value.empty() && value[0] == '"' && value.back() == '"') {
            value = value.substr(1, value.size() - 2);
        }
        
        if (key.empty()) continue;
        
        result.values[key] = value;
    }
    
    result.status = core::SemanticStatus::kSuccess;
    return result;
}

ConfigWriteResult save_toml_file(
    const std::filesystem::path& path,
    const std::map<std::string, std::string>& values,
    const ConfigStorageOptions& options) {
    
    ConfigWriteResult result;
    result.written_path = path;
    
    if (values.empty()) {
        result.error_message = "no values to write";
        return result;
    }
    
    // Build TOML content
    std::ostringstream ss;
    
    for (const auto& [key, value] : values) {
        bool needs_quotes = !value.empty() && 
                           (value.find(' ') != std::string::npos ||
                            value.find('#') != std::string::npos);
        
        if (needs_quotes) {
            // Escape quotes in value
            std::string safe_value = value;
            size_t pos = 0;
            while ((pos = safe_value.find('"', pos)) != std::string::npos) {
                safe_value.insert(pos, "\\");
                pos += 2;
            }
            ss << key << " = \"" << safe_value << "\"\n";
        } else {
            ss << key << " = " << value << "\n";
        }
    }
    
    if (options.atomic_write) {
        auto write_result = atomic_write_file(path, ss.str(),
                                              options.owner_uid,
                                              options.owner_gid,
                                              options.file_mode);
        
        result.success = write_result.success;
        result.written_path = write_result.final_path;
        result.error_message = std::move(write_result.error_message);
    } else {
        // Direct write (same as save_env_file fallback)
        std::error_code ec;
        auto parent = path.parent_path();
        
        if (options.create_parent_dirs && !parent.empty() &&
            !std::filesystem::exists(parent, ec)) {
            std::filesystem::create_directories(parent, ec);
            if (ec) {
                result.error_message = "failed to create parent directory: " + ec.message();
                return result;
            }
        }
        
        std::ofstream file(path);
        if (!file.is_open()) {
            result.error_message = "failed to open file for writing";
            return result;
        }
        
        file << ss.str();
        file.close();
        
        if (file.fail()) {
            result.error_message = "failed to write file content";
            return result;
        }
        
        // Set ownership and permissions
        if (options.owner_uid == 0 || geteuid() == 0) {
            if (chown(path.string().c_str(), options.owner_uid, options.owner_gid) != 0) {
                std::cerr << "warning: failed to chown " << path << ": "
                          << strerror(errno) << "\n";
            }
            
            if (chmod(path.string().c_str(), options.file_mode) != 0) {
                std::cerr << "warning: failed to chmod " << path << ": "
                          << strerror(errno) << "\n";
            }
        }
        
        result.success = true;
    }
    
    return result;
}

// ============================================================================
// Secret Redaction API
// ============================================================================

std::map<std::string, std::string> get_redacted_values(
    const std::map<std::string, std::string>& values,
    const std::vector<std::string>& secret_keys) {
    
    std::map<std::string, std::string> result;
    
    for (const auto& [key, value] : values) {
        bool is_secret = false;
        
        // Check if this key matches any secret key pattern
        for (const auto& secret_key : secret_keys) {
            // Simple substring match - could be improved with regex or exact match
            if (key.find(secret_key) != std::string::npos) {
                is_secret = true;
                break;
            }
            
            // Also check if the key equals the secret key exactly
            if (key == secret_key) {
                is_secret = true;
                break;
            }
        }
        
        result[key] = is_secret ? "[REDACTED]" : value;
    }
    
    return result;
}

std::string format_config_for_display(
    const std::map<std::string, std::string>& values,
    const std::vector<std::string>& secret_keys) {
    
    std::ostringstream ss;
    
    for (const auto& [key, value] : values) {
        bool is_secret = false;
        
        for (const auto& secret_key : secret_keys) {
            if (key == secret_key || key.find(secret_key) != std::string::npos) {
                is_secret = true;
                break;
            }
        }
        
        ss << key << " = ";
        if (is_secret) {
            ss << "[REDACTED]";
        } else {
            ss << value;
        }
        ss << "\n";
    }
    
    return ss.str();
}

// ============================================================================
// Atomic File Writer
// ============================================================================

AtomicWriteResult atomic_write_file(
    const std::filesystem::path& path,
    std::string_view content,
    uid_t owner_uid,
    gid_t owner_gid,
    mode_t permissions) {
    
    AtomicWriteResult result;
    result.final_path = path;
    
    if (path.empty()) {
        result.error_message = "empty path";
        return result;
    }
    
    // Create temp file in same directory
    auto parent = path.parent_path();
    std::error_code ec;
    
    if (!std::filesystem::exists(parent, ec)) {
        result.error_message = "parent directory does not exist";
        return result;
    }
    
    // Generate unique temp filename
    static int counter = 0;
    auto temp_path = parent / (".tmp-" + std::to_string(getpid()) + 
                               "-" + std::to_string(counter++));
    
    // Write to temp file
    {
        std::ofstream file(temp_path);
        if (!file.is_open()) {
            result.error_message = "failed to open temp file: " + temp_path.string();
            return result;
        }
        
        file << content;
        file.close();
        
        if (file.fail()) {
            result.error_message = "failed to write temp file";
            std::filesystem::remove(temp_path, ec);  // Clean up
            return result;
        }
    }
    
    // fsync the temp file
    int fd = open(temp_path.string().c_str(), O_WRONLY);
    if (fd < 0) {
        result.error_message = "failed to open temp file for fsync";
        std::filesystem::remove(temp_path, ec);  // Clean up
        return result;
    }
    
    if (fsync(fd) != 0) {
        result.error_message = "fsync failed: " + std::string(strerror(errno));
        close(fd);
        std::filesystem::remove(temp_path, ec);  // Clean up
        return result;
    }
    
    close(fd);
    
    // Rename temp file to final path (atomic on POSIX)
    if (rename(temp_path.string().c_str(), path.string().c_str()) != 0) {
        result.error_message = "rename failed: " + std::string(strerror(errno));
        std::filesystem::remove(temp_path, ec);  // Clean up
        return result;
    }
    
    // fsync parent directory
    int parent_fd = open(parent.string().c_str(), O_RDONLY | O_DIRECTORY);
    if (parent_fd >= 0) {
        if (fsync(parent_fd) != 0) {
            std::cerr << "warning: parent dir fsync failed\n";
        }
        close(parent_fd);
    }
    
    // Set ownership and permissions
    if (owner_uid == 0 || geteuid() == 0) {
        if (chown(path.string().c_str(), owner_uid, owner_gid) != 0) {
            std::cerr << "warning: failed to chown " << path << ": "
                      << strerror(errno) << "\n";
        }
        
        if (chmod(path.string().c_str(), permissions) != 0) {
            std::cerr << "warning: failed to chmod " << path << ": "
                      << strerror(errno) << "\n";
        }
    }
    
    result.success = true;
    return result;
}

}  // namespace rebuntu::environment::config_storage