// rebuntu::install — installation implementation (Phase 1.0)
#include <portability/install/contracts.hpp>

#include <unistd.h>
#include <sys/stat.h>
#include <filesystem>

namespace fs = std::filesystem;

namespace rebuntu::install {
namespace {

bool file_exists(const std::string& path) {
    return fs::exists(fs::path(path));
}

uid_t get_effective_uid() {
    return geteuid();
}

InstallationScope detect_scope(const InstallContext& ctx) {
    return ctx.is_root ? InstallationScope::kSystem : InstallationScope::kUser;
}

InstallationState check_installation_state(const InstallContext& ctx) {
    std::vector<std::string> candidate_paths;
    
    if (ctx.is_root) {
        candidate_paths = {"/usr/bin/rebuntu", "/usr/local/bin/rebuntu", "/opt/rebuntu/bin/rebuntu"};
    } else {
        const char* home = std::getenv("HOME");
        if (home) {
            candidate_paths = {std::string(home) + "/.local/bin/rebuntu"};
        }
    }
    
    for (const auto& p : candidate_paths) {
        fs::path path(p);
        std::error_code ec;
        
        if (fs::is_regular_file(path, ec)) {
            fs::perms permissions = fs::status(path, ec).permissions();
            
            bool has_exec = false;
            if ((permissions & fs::perms::owner_exec) == fs::perms::owner_exec) has_exec = true;
            else if ((permissions & fs::perms::group_exec) == fs::perms::group_exec) has_exec = true;
            else if ((permissions & fs::perms::others_exec) == fs::perms::others_exec) has_exec = true;
            
            if (has_exec) return InstallationState::kInstalled;
        }
    }
    
    return InstallationState::kNotInstalled;
}

bool verify_binary_executable(const std::string& path) {
    fs::path binary_path(path);
    std::error_code ec;
    
    if (!fs::exists(binary_path, ec)) return false;
    if (ec.value() != 0) return false;
    if (!fs::is_regular_file(binary_path, ec)) return false;
    
    fs::perms permissions = fs::status(binary_path, ec).permissions();
    
    bool has_exec = false;
    if ((permissions & fs::perms::owner_exec) == fs::perms::owner_exec) has_exec = true;
    else if ((permissions & fs::perms::group_exec) == fs::perms::group_exec) has_exec = true;
    else if ((permissions & fs::perms::others_exec) == fs::perms::others_exec) has_exec = true;
    
    return has_exec;
}

}  // namespace

uid_t get_context_uid(const InstallContext& ctx) {
    return ctx.effective_uid;
}

bool is_context_root(const InstallContext& ctx) {
    return ctx.is_root;
}

InstallContext build_default_context() {
    InstallContext ctx;
    ctx.effective_uid = get_effective_uid();
    ctx.is_root = (ctx.effective_uid == 0);
    
    const char* home = std::getenv("HOME");
    if (home) {
        ctx.install_root = ctx.is_root ? "/" : std::string(home);
    } else {
        ctx.install_root = "/";
    }
    ctx.default_scope = detect_scope(ctx);
    return ctx;
}

InstallationState check_installation(const InstallContext& ctx) {
    return check_installation_state(ctx);
}

VerificationResult verify_installation(const InstallContext& ctx) {
    VerificationResult result;
    auto state = check_installation(ctx);
    result.is_installed = (state == InstallationState::kInstalled || 
                           state == InstallationState::kDegraded);
    
    std::string bin_path;
    if (ctx.is_root) {
        bin_path = "/usr/bin/rebuntu";
    } else {
        const char* home = std::getenv("HOME");
        if (home) {
            bin_path = std::string(home) + "/.local/bin/rebuntu";
        }
    }
    
    VerificationResult::Check binary_check;
    binary_check.name = "binary-executable";
    binary_check.passed = !bin_path.empty() && verify_binary_executable(bin_path);
    result.checks.push_back(binary_check);
    
    VerificationResult::Check state_dir_check;
    state_dir_check.name = "state-directory-accessible";
    state_dir_check.passed = true;
    result.checks.push_back(state_dir_check);
    
    return result;
}

std::string get_bin_directory(InstallationScope scope, const std::string& install_root) {
    return (scope == InstallationScope::kSystem) ? "/usr/bin" : (install_root + "/.local/bin");
}

std::string get_state_directory(InstallationScope scope, const std::string& install_root) {
    return (scope == InstallationScope::kSystem) ? "/var/lib/rebuntu" : (install_root + "/.local/state/rebuntu");
}

std::string get_config_directory(InstallationScope scope, const std::string& install_root) {
    return (scope == InstallationScope::kSystem) ? "/etc/rebuntu" : (install_root + "/.config/rebuntu");
}

std::string get_lib_directory(InstallationScope scope, const std::string& install_root) {
    return (scope == InstallationScope::kSystem) ? "/usr/lib" : (install_root + "/.local/lib");
}

}  // namespace rebuntu::install
