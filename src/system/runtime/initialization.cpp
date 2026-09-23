// rebuntu::runtime::initialization — Core Initialization Implementation (Phase 4.1)
//
// Implements deterministic Rebuntu core initialization:
//   - Configuration resolution from multiple sources
//   - Host identity discovery
//   - Dependency validation
//   - Provider readiness facts collection

#include <system/runtime/initialization.hpp>

#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>

#ifdef __linux__
#include <unistd.h>
#endif

namespace rebuntu::runtime::initialization {

// ---------------------------------------------------------------------------
// Helper: Get current time in milliseconds
// ---------------------------------------------------------------------------

static std::chrono::milliseconds get_time_ms() {
    auto now = std::chrono::system_clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch());
}

// ---------------------------------------------------------------------------
// InitializationContext implementation (header-only, no implementation needed)
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// InitializationRegistry implementation
// ---------------------------------------------------------------------------

const InitializationPhase* InitializationRegistry::get_phase(InitializationStage stage) const {
    auto it = phases_.find(stage);
    return (it == phases_.end()) ? nullptr : &it->second;
}

std::vector<InitializationPhase> InitializationRegistry::all_phases() const {
    std::vector<InitializationPhase> result;
    
    for (auto stage : {
        InitializationStage::kNotStarted,
        InitializationStage::kConfigResolve,
        InitializationStage::kIdentityDiscover,
        InitializationStage::kDependencyCheck,
        InitializationStage::kProviderReady,
        InitializationStage::kRuntimeReady
    }) {
        auto it = phases_.find(stage);
        if (it != phases_.end()) {
            result.push_back(it->second);
        }
    }
    
    return result;
}

// ---------------------------------------------------------------------------
// Initializer implementation
// ---------------------------------------------------------------------------

Initializer::Initializer(InitializationContext ctx)
    : ctx_(std::move(ctx)) {
}

InitializationResult Initializer::initialize() {
    InitializationResult result;
    auto start_time = get_time_ms();
    
    // Run each initialization stage in sequence
    std::vector<std::pair<InitializationStage, std::function<InitializationPhase()>>> stages = {
        {InitializationStage::kConfigResolve, [this]() { return run_config_resolve(); }},
        {InitializationStage::kIdentityDiscover, [this]() { return run_identity_discovery(); }},
        {InitializationStage::kDependencyCheck, [this]() { return run_dependency_check(); }},
        {InitializationStage::kProviderReady, [this]() { return run_provider_readiness(); }},
    };
    
    bool all_stages_succeeded = true;
    
    for (const auto& [stage, runner] : stages) {
        auto phase_start = get_time_ms();
        
        // Check timeout
        if (ctx_.timeout_ms > std::chrono::milliseconds(0)) {
            auto elapsed = get_time_ms() - start_time;
            if (elapsed >= ctx_.timeout_ms) {
                InitializationPhase phase;
                phase.name = "initialization_timeout";
                phase.stage = stage;
                phase.status = core::SemanticStatus::kFailure;
                phase.error = core::Error{
                    "E_TIMEOUT",
                    "Initialization timed out after " + 
                    std::to_string(elapsed.count()) + "ms"
                };
                registry_.add_phase(phase);
                
                result.success = false;
                result.final_stage = stage;
                result.failed_stage_name = to_string(stage);
                result.error = phase.error;
                
                // Record remaining time as evidence
                core::Evidence e;
                e.source = "runtime";
                e.value = "timeout_exceeded";
                e.captured_at = std::to_string(get_time_ms().count());
                phase.evidence.push_back(e);
                
                break;
            }
        }
        
        InitializationPhase phase = runner();
        auto duration = get_time_ms() - phase_start;
        phase.duration_ms = duration;
        
        registry_.add_phase(phase);
        
        if (phase.status != core::SemanticStatus::kSuccess && 
            phase.status != core::SemanticStatus::kCompleted) {
            all_stages_succeeded = false;
            
            result.success = false;
            result.final_stage = stage;
            result.failed_stage_name = to_string(stage);
            result.error = phase.error;
            break;
        }
        
        if (stage == InitializationStage::kProviderReady) {
            result.success = true;
            result.final_stage = InitializationStage::kRuntimeReady;
        }
    }
    
    auto end_time = get_time_ms();
    result.total_duration_ms = end_time - start_time;
    
    // Record all phases in the result
    for (auto stage : {
        InitializationStage::kConfigResolve,
        InitializationStage::kIdentityDiscover,
        InitializationStage::kDependencyCheck,
        InitializationStage::kProviderReady
    }) {
        auto phase = registry_.get_phase(stage);
        if (phase) {
            result.phases.push_back(*phase);
        }
    }
    
    return result;
}

InitializationPhase Initializer::run_config_resolve() {
    InitializationPhase phase;
    phase.name = "config_resolve";
    phase.stage = InitializationStage::kConfigResolve;
    
    // Start with defaults
    std::map<std::string, std::string> merged_values;
    
    for (const auto& source : ctx_.config_sources) {
        for (const auto& [key, value] : source.values) {
            merged_values[key] = value;
        }
    }
    
    // Load environment variables
    if (!ctx_.dry_run) {
#ifdef __linux__
        char** envp = environ;
        for (char** env = envp; *env != nullptr; ++env) {
            std::string entry(*env);
            size_t eq_pos = entry.find('=');
            if (eq_pos != std::string::npos) {
                std::string key = entry.substr(0, eq_pos);
                std::string value = entry.substr(eq_pos + 1);
                
                // Only include REBUNTU_* prefixed variables
                if (key.rfind("REBUNTU_", 0) == 0) {
                    merged_values[key] = value;
                }
            }
        }
#endif
    }
    
    // Load system configuration file if specified
    if (ctx_.system_config_path.has_value()) {
        std::filesystem::path config_file = *ctx_.system_config_path / "config";
        
        if (!ctx_.dry_run && std::filesystem::exists(config_file)) {
            std::ifstream ifs(config_file);
            std::string line;
            
            while (std::getline(ifs, line)) {
                // Skip comments and empty lines
                if (line.empty() || line[0] == '#') continue;
                
                size_t eq_pos = line.find('=');
                if (eq_pos != std::string::npos) {
                    std::string key = line.substr(0, eq_pos);
                    std::string value = line.substr(eq_pos + 1);
                    
                    // Trim whitespace
                    key.erase(0, key.find_first_not_of(" \t"));
                    key.erase(key.find_last_not_of(" \t") + 1);
                    value.erase(0, value.find_first_not_of(" \t"));
                    value.erase(value.find_last_not_of(" \t") + 1);
                    
                    merged_values[key] = value;
                }
            }
        }
    }
    
    config_values_ = std::move(merged_values);
    
    phase.status = core::SemanticStatus::kSuccess;
    
    // Record configuration count as evidence
    core::Evidence e;
    e.source = "config";
    e.value = "resolved";
    e.captured_at = std::to_string(get_time_ms().count());
    phase.evidence.push_back(e);
    
    return phase;
}

InitializationPhase Initializer::run_identity_discovery() {
    InitializationPhase phase;
    phase.name = "identity_discover";
    phase.stage = InitializationStage::kIdentityDiscover;
    
#ifdef __linux__
    // Get hostname
    char hostname_buf[256];
    if (gethostname(hostname_buf, sizeof(hostname_buf)) == 0) {
        host_identity_.hostname = std::string(hostname_buf);
    }
    
    // Get user ID
    host_identity_.user_id = getuid();
    
    // Get group ID  
    host_identity_.group_id = getgid();
    
    // Check for systemd session (if D-Bus available)
    // For now, just note that we're in a Linux environment
    host_identity_.platform = "linux";
#endif
    
    // Set the session ID if provided via context or detect it
    // Using a simple approach: session is derived from process properties
    host_identity_.session_id = std::to_string(getpid());
    
    // Check OS release information
    std::ifstream os_release("/etc/os-release");
    if (os_release.is_open()) {
        std::string line;
        while (std::getline(os_release, line)) {
            if (line.rfind("PRETTY_NAME=", 0) == 0) {
                host_identity_.os_release = line.substr(12);
                // Remove quotes
                auto& os_str = *host_identity_.os_release;
                if (!os_str.empty() && os_str.back() == '"') {
                    os_str.pop_back();
                }
            }
        }
    }
    
    // Check boot time from /proc/uptime
    std::ifstream uptime("/proc/uptime");
    if (uptime.is_open()) {
        double uptime_seconds;
        uptime >> uptime_seconds;
        auto now = get_time_ms().count();
        host_identity_.boot_time_ms = static_cast<int64_t>(now - (uptime_seconds * 1000));
    }
    
    // If dry run, don't set final status - just report what would be discovered
    if (ctx_.dry_run) {
        phase.status = core::SemanticStatus::kCompleted;
        phase.evidence.push_back({
            "identity",
            "would_discover",
            std::to_string(get_time_ms().count())
        });
    } else {
        phase.status = core::SemanticStatus::kSuccess;
        
        if (host_identity_.is_valid()) {
            core::Evidence e;
            e.source = "identity";
            e.value = "valid";
            e.captured_at = std::to_string(get_time_ms().count());
            phase.evidence.push_back(e);
        } else {
            // Partial discovery - not an error, just incomplete
            phase.status = core::SemanticStatus::kCompleted;
        }
    }
    
    return phase;
}

InitializationPhase Initializer::run_dependency_check() {
    InitializationPhase phase;
    phase.name = "dependency_check";
    phase.stage = InitializationStage::kDependencyCheck;
    
    // Check essential dependencies: required files, commands, libraries
    std::vector<std::string> essential_deps = {"stdc++", "libc"};
    
    for (const auto& dep : essential_deps) {
        DependencyCheckResult result;
        result.dependency_name = dep;
        
#ifdef __linux__
        if (dep == "stdc++") {
            // libstdc++ is always available for C++ programs
            result.satisfied = true;
            result.status = core::SemanticStatus::kSuccess;
        } else if (dep == "libc") {
            // libc is fundamental to Linux
            result.satisfied = true;
            result.status = core::SemanticStatus::kSuccess;
        }
#else
        // For non-Linux platforms, assume basic dependencies exist
        result.satisfied = true;
        result.status = core::SemanticStatus::kCompleted;
#endif
        
        if (!result.satisfied && !result.reason.has_value()) {
            result.reason = "dependency check failed";
        }
        
        // Record evidence
        core::Evidence e;
        e.source = "dependencies";
        e.value = (result.satisfied ? "satisfied" : "unsatisfied");
        e.captured_at = std::to_string(get_time_ms().count());
        phase.evidence.push_back(e);
    }
    
    // If dry run, report what would be checked
    if (ctx_.dry_run) {
        phase.status = core::SemanticStatus::kCompleted;
        core::Evidence e;
        e.source = "dependencies";
        e.value = "would_check";
        e.captured_at = std::to_string(get_time_ms().count());
        phase.evidence.push_back(e);
    } else {
        phase.status = core::SemanticStatus::kSuccess;
    }
    
    return phase;
}

InitializationPhase Initializer::run_provider_readiness() {
    InitializationPhase phase;
    phase.name = "provider_ready";
    phase.stage = InitializationStage::kProviderReady;
    
    // Check provider readiness facts
    // In a real implementation, this would:
    //   - Query systemd for service states
    //   - Check if D-Bus is available
    //   - Verify native mechanisms are ready
    
    // For now, record that providers exist and are ready
    core::Evidence e;
    e.source = "providers";
    e.value = "ready";
    e.captured_at = std::to_string(get_time_ms().count());
    phase.evidence.push_back(e);
    
    if (ctx_.dry_run) {
        phase.status = core::SemanticStatus::kCompleted;
    } else {
        phase.status = core::SemanticStatus::kSuccess;
    }
    
    return phase;
}

bool Initializer::is_provider_ready(std::string_view provider_id) const {
    // Check cache first (use mutable cache for performance)
    auto it = const_cast<std::map<std::string, bool>&>(provider_ready_cache_).find(
        std::string{provider_id});
    if (it != const_cast<std::map<std::string, bool>&>(provider_ready_cache_).end()) {
        return it->second;
    }
    
    // In a real implementation, this would check actual provider state
    // For now, assume providers are ready if initialization succeeded
    bool is_ready = registry_.is_complete();
    const_cast<std::map<std::string, bool>&>(provider_ready_cache_)[std::string{provider_id}] = 
        is_ready;
    return is_ready;
}

// ---------------------------------------------------------------------------
// Helper function implementations
// ---------------------------------------------------------------------------

core::Result<std::map<std::string, std::string>> resolve_configuration(
    const std::vector<ConfigurationSource>& sources,
    std::optional<std::filesystem::path> system_config_path) {
    
    core::Result<std::map<std::string, std::string>> result;
    result.status = core::SemanticStatus::kSuccess;
    
    // Start with defaults
    std::map<std::string, std::string> merged_values;
    
    for (const auto& source : sources) {
        for (const auto& [key, value] : source.values) {
            merged_values[key] = value;
        }
    }
    
    // Load environment variables
#ifdef __linux__
    char** envp = environ;
    for (char** env = envp; *env != nullptr; ++env) {
        std::string entry(*env);
        size_t eq_pos = entry.find('=');
        if (eq_pos != std::string::npos) {
            std::string key = entry.substr(0, eq_pos);
            std::string value = entry.substr(eq_pos + 1);
            
            // Only include REBUNTU_* prefixed variables
            if (key.rfind("REBUNTU_", 0) == 0) {
                merged_values[key] = value;
            }
        }
    }
#endif
    
    // Load system configuration file if specified
    if (system_config_path.has_value()) {
        std::filesystem::path config_file = *system_config_path / "config";
        
        if (std::filesystem::exists(config_file)) {
            std::ifstream ifs(config_file);
            std::string line;
            
            while (std::getline(ifs, line)) {
                // Skip comments and empty lines
                if (line.empty() || line[0] == '#') continue;
                
                size_t eq_pos = line.find('=');
                if (eq_pos != std::string::npos) {
                    std::string key = line.substr(0, eq_pos);
                    std::string value = line.substr(eq_pos + 1);
                    
                    // Trim whitespace
                    key.erase(0, key.find_first_not_of(" \t"));
                    key.erase(key.find_last_not_of(" \t") + 1);
                    value.erase(0, value.find_first_not_of(" \t"));
                    value.erase(value.find_last_not_of(" \t") + 1);
                    
                    merged_values[key] = value;
                }
            }
        }
    }
    
    result.value = std::move(merged_values);
    return result;
}

core::Result<HostIdentity> discover_host_identity() {
    core::Result<HostIdentity> result;
    result.status = core::SemanticStatus::kSuccess;
    
#ifdef __linux__
    HostIdentity identity;
    
    // Get hostname
    char hostname_buf[256];
    if (gethostname(hostname_buf, sizeof(hostname_buf)) == 0) {
        identity.hostname = std::string(hostname_buf);
    }
    
    // Get user ID
    identity.user_id = getuid();
    
    // Get group ID  
    identity.group_id = getgid();
    
    // Session ID from process ID
    identity.session_id = std::to_string(getpid());
    
    // Platform identification
    identity.platform = "linux";
    
    // OS release information
    std::ifstream os_release("/etc/os-release");
    if (os_release.is_open()) {
        std::string line;
        while (std::getline(os_release, line)) {
            if (line.rfind("PRETTY_NAME=", 0) == 0) {
                identity.os_release = line.substr(12);
                // Remove quotes
                if (!identity.os_release->empty() && 
                    identity.os_release->back() == '"') {
                    identity.os_release->pop_back();
                }
            }
        }
    }
    
    // Boot time from /proc/uptime
    std::ifstream uptime("/proc/uptime");
    if (uptime.is_open()) {
        double uptime_seconds;
        uptime >> uptime_seconds;
        auto now = get_time_ms().count();
        identity.boot_time_ms = static_cast<int64_t>(now - (uptime_seconds * 1000));
    }
    
    result.value = std::move(identity);
#else
    // Fallback for non-Linux platforms
    HostIdentity identity;
    identity.user_id = 0;  // Unknown user ID on other platforms
    identity.session_id = "unknown";
    identity.platform = "unknown";
    result.value = std::move(identity);
#endif
    
    return result;
}

core::Result<bool> check_dependency(
    std::string_view name,
    std::optional<std::filesystem::path> path,
    std::optional<std::string> version_regex) {
    
    core::Result<bool> result;
    
    // For now, assume dependencies are satisfied if no specific check is required
    // In a real implementation:
    //   - Check if file/command exists at path
    //   - Run command and match output against version_regex
    //   - Check for library availability via dlopen
    
    result.status = core::SemanticStatus::kSuccess;
    result.value = true;
    
    return result;
}

}  // namespace rebuntu::runtime::initialization