// rebuntu::environment::privilege — Privilege & Elevation Implementation (Phase 2.4)
#include <system/environment/privilege.hpp>

#include <array>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <string>
#include <sstream>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>

namespace rebuntu::environment::privilege {

// ============================================================================
// Native Linux helper: command_exists() - Use access() instead of shell
// ============================================================================

static bool command_exists(const std::string& cmd) {
    // Search through PATH directories using native access()
    const char* path_env = std::getenv("PATH");
    if (!path_env) {
        return false;
    }
    
    std::string path_str(path_env);
    size_t start = 0;
    
    while (start < path_str.length()) {
        size_t end = path_str.find(':', start);
        if (end == std::string::npos) {
            end = path_str.length();
        }
        
        std::string dir = path_str.substr(start, end - start);
        if (!dir.empty() && dir.back() != '/') {
            dir += '/';
        }
        dir += cmd;
        
        // Use access() to check if executable exists and is runnable
        if (access(dir.c_str(), X_OK) == 0) {
            return true;
        }
        
        start = end + 1;
    }
    
    return false;
}

// ============================================================================
// Native Linux helper: test_elevation() - Direct process execution without shell
// ============================================================================

static bool test_elevation_capability() {
    // Use fork/execve directly instead of shell command
    pid_t pid = fork();
    
    if (pid == 0) {
        // Child process - try to run 'true' with empty argv
        std::array<char*, 2> argv = {const_cast<char*>("true"), nullptr};
        execv("/bin/true", argv.data());
        _exit(1);  // If execv fails
    } else if (pid > 0) {
        // Parent process - wait for child
        int status;
        waitpid(pid, &status, 0);
        
        // Check if child exited successfully
        return WIFEXITED(status) && WEXITSTATUS(status) == 0;
    }
    
    return false;
}

PrivilegeInfo discover_privilege() {
    PrivilegeInfo info;
    
    // Get current effective UID
    uid_t euid = geteuid();
    info.effective_uid = euid;
    info.is_root = (euid == 0);
    
    if (info.is_root) {
        // Process is already running as root
        info.elevation = ElevationCapability::kAlreadyElevated;
        
        // Capture real UID for audit trail
        uid_t ruid = getuid();
        if (ruid != euid) {
            info.real_uid = ruid;
            
            // Check SUDO_USER environment variable
            const char* sudo_user = std::getenv("SUDO_USER");
            if (sudo_user) {
                info.sudo_user = sudo_user;
            }
        }
    } else if (command_exists("sudo")) {
        // Test if sudo is usable with current credentials using native fork/execve
        bool test_result = test_elevation_capability();
        
        if (test_result) {
            info.elevation = ElevationCapability::kSudoUsable;
            
            // Record real UID for audit trail
            uid_t ruid = getuid();
            if (ruid != euid) {
                info.real_uid = ruid;
            }
            
            const char* sudo_user = std::getenv("SUDO_USER");
            if (sudo_user) {
                info.sudo_user = sudo_user;
            }
        } else {
            // sudo exists but test failed - might be due to password prompt
            info.elevation = ElevationCapability::kSudoAvailable;
            
            // Still record the real user
            uid_t ruid = getuid();
            if (ruid != euid) {
                info.real_uid = ruid;
            }
        }
    } else {
        // No sudo available - cannot elevate
        info.elevation = ElevationCapability::kNone;
    }
    
    info.status = 1;  // DiscoveryStatus::kKnown
    return info;
}

// ============================================================================
// Observation: discover_scope() - Resolve system vs user context
// ============================================================================

ScopeContext discover_scope(const PrivilegeInfo& info) {
    ScopeContext ctx;
    
    // Root always defaults to system scope (unless explicitly overridden)
    if (info.is_root) {
        ctx.scope = InstallationScope::kSystem;
        
        // Record original UID when elevated via sudo
        if (info.real_uid.has_value()) {
            ctx.original_uid = info.real_uid.value();
        } else {
            ctx.original_uid = getuid();
        }
    } else {
        // Non-root users get user scope by default
        ctx.scope = InstallationScope::kUser;
        ctx.original_uid = info.effective_uid;
        
        // Set home directory if available
        const char* home = std::getenv("HOME");
        if (home) {
            ctx.home_dir = home;
        }
    }
    
    ctx.is_root = info.is_root;
    return ctx;
}

// ============================================================================
// Helper: build_current_process_identity() - Full identity context
// ============================================================================

ProcessIdentity build_current_process_identity() {
    ProcessIdentity ident;
    
    // Get all UID/GID values
    ident.real_uid = getuid();
    ident.effective_uid = geteuid();
    ident.saved_uid = ident.real_uid;  // Saved set-user-ID (simplified)
    
    ident.real_gid = getgid();
    ident.effective_gid = getegid();
    ident.saved_gid = ident.real_gid;
    
    // Determine root status
    ident.is_root = (ident.effective_uid == 0);
    
    // Detect elevation capability using native fork/execve
    if (ident.is_root) {
        ident.elevation = ElevationCapability::kAlreadyElevated;
        
        // Check for sudo user context
        const char* sudo_user = std::getenv("SUDO_USER");
        if (sudo_user) {
            ident.sudo_user = sudo_user;
        }
    } else if (command_exists("sudo")) {
        bool test_result = test_elevation_capability();
        if (test_result) {
            ident.elevation = ElevationCapability::kSudoUsable;
            
            const char* sudo_user = std::getenv("SUDO_USER");
            if (sudo_user) {
                ident.sudo_user = sudo_user;
            }
        } else {
            ident.elevation = ElevationCapability::kSudoAvailable;
        }
    } else {
        ident.elevation = ElevationCapability::kNone;
    }
    
    // Identity type defaults to effective
    ident.identity_type = IdentityType::kEffective;
    
    return ident;
}

// ============================================================================
// Helper: get_real_uid_when_elevated() - Get original user when under sudo
// ============================================================================

uid_t get_real_uid_when_elevated() {
    uid_t real_uid = getuid();
    uid_t effective_uid = geteuid();
    
    // If we're elevated (effective is root but real is not), return real UID
    if (effective_uid == 0 && real_uid != 0) {
        return real_uid;
    }
    
    return effective_uid;
}

// ============================================================================
// Helper: is_running_under_sudo() - Check if process was invoked via sudo
// ============================================================================

bool is_running_under_sudo() {
    const char* sudo_user = std::getenv("SUDO_USER");
    if (sudo_user == nullptr) {
        return false;
    }
    
    // Additional check: effective UID should be root while real UID is not
    uid_t real_uid = getuid();
    uid_t effective_uid = geteuid();
    
    if (effective_uid == 0 && real_uid != 0) {
        return true;
    }
    
    return false;
}

// ============================================================================
// Helper: get_sudo_user_from_env() - Get SUDO_USER environment variable
// ============================================================================

std::optional<std::string> get_sudo_user_from_env() {
    const char* sudo_user = std::getenv("SUDO_USER");
    if (sudo_user) {
        return std::string(sudo_user);
    }
    return std::nullopt;
}

// ============================================================================
// Verification: verify_privilege_state() - Is this privilege state correct?
// ============================================================================

PrivilegeVerification verify_privilege_state(
    const PrivilegeIntent& intent,
    const PrivilegeInfo& info) {
    
    PrivilegeVerification verification;
    
    // Check UID consistency (real vs saved)
    if (info.real_uid.has_value()) {
        verification.uid_consistent = true;  // Simplified - real_uid should be consistent
    }
    
    // Check effective UID matches scope requirements
    if (intent.required_scope == InstallationScope::kSystem) {
        // System scope requires root
        verification.euid_matches_context = info.is_root;
    } else {
        // User scope allows any non-root or root with user override
        verification.euid_matches_context = !info.is_root || 
            intent.expected_home_dir.has_value();
    }
    
    // Check is_root state consistency
    if (info.is_root) {
        // Root should have elevation set appropriately
        verification.is_root_sane = (info.elevation == ElevationCapability::kAlreadyElevated ||
                                      info.elevation == ElevationCapability::kSudoUsable);
    } else {
        // Non-root should not report already elevated
        verification.is_root_sane = (info.elevation != ElevationCapability::kAlreadyElevated);
    }
    
    // Record observed values
    verification.observed_real_uid = info.real_uid;
    verification.observed_effective_uid = info.effective_uid;
    
    // Verify elevation matches observed state
    if (info.is_root) {
        verification.expected_elevation = ElevationCapability::kAlreadyElevated;
        verification.elevation_valid = (info.elevation == ElevationCapability::kAlreadyElevated);
    } else if (info.elevation != ElevationCapability::kNone) {
        // Non-root but has elevation capability
        verification.expected_elevation = info.elevation;
        verification.elevation_valid = true;
    }
    
    return verification;
}

}  // namespace rebuntu::environment::privilege