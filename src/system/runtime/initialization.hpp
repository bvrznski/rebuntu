// rebuntu::runtime::initialization — Core Initialization (Phase 4.1)
//
// Establishes Rebuntu's deterministic core initialization flow:
//   configuration resolution → host identity discovery → dependency check
//   → provider readiness validation → runtime ready state
//
// Key principles:
//   * INITIALIZATION != BOOT (boot is kernel/systemd responsibility)
//   * INITIALIZATION ≠ RUNTIME STARTUP (startup is activation of services)
//   * INITIALIZE = DETERMINISTIC SETUP OF CORE STRUCTURE
//   * RE-ENTRANT IDEMPOTENCE where practical (no destructive operations)
//
// Initialization stages:
//   STAGE_CONFIG_RESOLVE    → Load and merge configuration from all sources
//   STAGE_IDENTITY_DISCOVER → Discover host identity, user, session context
//   STAGE_DEPENDENCY_CHECK  → Validate required dependencies are present
//   STAGE_PROVIDER_READY    → Verify provider readiness facts
//   STAGE_RUNTIME_READY     → Runtime is fully initialized and ready

#pragma once

#include <system/core/contracts.hpp>
#include <system/runtime/contracts.hpp>
#include <system/environment/discovery.hpp>

#include <chrono>
#include <filesystem>
#include <map>
#include <optional>
#include <string>
#include <vector>

namespace rebuntu::runtime::initialization {

// ---------------------------------------------------------------------------
// InitializationStage
// The discrete phases of initialization.
// ---------------------------------------------------------------------------

enum class InitializationStage {
    kNotStarted,           // initialization not yet initiated
    kConfigResolve,        // resolving configuration from sources
    kIdentityDiscover,     // discovering host/runtime identity
    kDependencyCheck,      // validating dependencies
    kProviderReady,        // verifying provider readiness facts
    kRuntimeReady,         // runtime fully initialized and ready
};

inline std::string_view to_string(InitializationStage s) {
    switch (s) {
        case InitializationStage::kNotStarted:   return "not_started";
        case InitializationStage::kConfigResolve: return "config_resolve";
        case InitializationStage::kIdentityDiscover: return "identity_discover";
        case InitializationStage::kDependencyCheck: return "dependency_check";
        case InitializationStage::kProviderReady: return "provider_ready";
        case InitializationStage::kRuntimeReady: return "runtime_ready";
    }
    return "unknown";
}

// ---------------------------------------------------------------------------
// InitializationPhase
// A single phase of initialization with its own validation.
// ---------------------------------------------------------------------------

struct InitializationPhase {
    std::string name;                    // Phase name (e.g., "config", "identity")
    InitializationStage stage;          // Which stage this represents
    core::SemanticStatus status;        // kSuccess, kFailure, kUnknown, etc.
    std::optional<std::chrono::milliseconds> duration_ms;
    std::vector<core::Evidence> evidence;
    std::optional<core::Error> error;
};

// ---------------------------------------------------------------------------
// InitializationResult
// The outcome of an initialization attempt.
// ---------------------------------------------------------------------------

struct InitializationResult {
    bool success = false;                // Overall initialization succeeded
    std::chrono::milliseconds total_duration_ms{0};
    
    InitializationStage final_stage = InitializationStage::kNotStarted;
    std::optional<std::string> failed_stage_name;
    
    std::vector<InitializationPhase> phases;      // All completed phases
    std::optional<core::Error> error;             // First error encountered
    
    bool is_complete() const { return final_stage == InitializationStage::kRuntimeReady; }
    bool is_failed() const { return !success && error.has_value(); }
};

// ---------------------------------------------------------------------------
// ConfigurationSource
// A named source of configuration values.
// ---------------------------------------------------------------------------

struct ConfigurationSource {
    std::string name;                    // "defaults", "env", "system", etc.
    std::map<std::string, std::string> values;
    bool optional = false;               // Missing required config in this source is OK
};

// ---------------------------------------------------------------------------
// HostIdentity
// Discovered host and runtime identity information.
// ---------------------------------------------------------------------------

struct HostIdentity {
    std::optional<std::string> hostname;           // System hostname
    std::optional<int> user_id;                    // Effective UID
    std::optional<int> group_id;                   // Primary GID
    std::optional<std::string> session_id;         // Session/terminal identifier
    std::optional<std::string> platform;           // "linux", "windows", etc.
    std::optional<std::string> os_release;         // "ubuntu-24.04", etc.
    std::optional<int64_t> boot_time_ms;          // System boot timestamp
    
    bool is_valid() const {
        return hostname.has_value() && user_id.has_value();
    }
};

// ---------------------------------------------------------------------------
// DependencyCheckResult
// Result of validating a dependency requirement.
// ---------------------------------------------------------------------------

struct DependencyCheckResult {
    std::string dependency_name;
    bool satisfied = false;
    core::SemanticStatus status;       // kSuccess, kFailure, kUnknown
    std::optional<std::string> reason;  // Why it failed (if not satisfied)
};

// ---------------------------------------------------------------------------
// ProviderReadinessFact
// Evidence that a provider is ready to accept work.
// ---------------------------------------------------------------------------

struct ProviderReadinessFact {
    std::string provider_id;
    bool ready = false;
    core::SemanticStatus status;
    std::vector<core::Evidence> evidence;
};

// ---------------------------------------------------------------------------
// InitializationContext
// Context provided when starting initialization.
// ---------------------------------------------------------------------------

struct InitializationContext {
    // Configuration sources to merge (order matters: last wins)
    std::vector<ConfigurationSource> config_sources;
    
    // Where to look for configuration files
    std::optional<std::filesystem::path> system_config_path;  // e.g., /etc/rebuntu/
    std::optional<std::filesystem::path> user_config_path;    // e.g., ~/.config/rebuntu/
    std::optional<std::filesystem::path> data_dir;            // Runtime state directory
    
    // Host identity overrides (for testing)
    std::optional<std::string> override_hostname;
    
    // Timeout for initialization
    std::chrono::milliseconds timeout_ms{30000};  // Default: 30 seconds
    
    bool dry_run = false;  // Don't actually write anything, just validate
};

// ---------------------------------------------------------------------------
// InitializationRegistry
// Registry of initialized components with their status.
// ---------------------------------------------------------------------------

class InitializationRegistry {
public:
    // Add a phase result to the registry
    void add_phase(InitializationPhase phase) {
        phases_[phase.stage] = std::move(phase);
    }
    
    // Get a specific phase's result
    const InitializationPhase* get_phase(InitializationStage stage) const;
    
    // Get all phases in order
    std::vector<InitializationPhase> all_phases() const;
    
    // Has all stages completed successfully?
    bool is_complete() const {
        for (auto stage : {
            InitializationStage::kConfigResolve,
            InitializationStage::kIdentityDiscover,
            InitializationStage::kDependencyCheck,
            InitializationStage::kProviderReady
        }) {
            auto phase = get_phase(stage);
            if (!phase || !is_success(phase->status)) {
                return false;
            }
        }
        return true;
    }
    
private:
    static bool is_success(core::SemanticStatus s) {
        return s == core::SemanticStatus::kSuccess || 
               s == core::SemanticStatus::kCompleted;
    }
    
    std::map<InitializationStage, InitializationPhase> phases_;
};

// ---------------------------------------------------------------------------
// Initializer — Core initialization engine
//
// Performs deterministic initialization of Rebuntu's runtime foundation:
//   - Configuration resolution from multiple sources
//   - Host identity discovery
//   - Dependency validation
//   - Provider readiness facts collection
// ---------------------------------------------------------------------------

class Initializer {
public:
    explicit Initializer(InitializationContext ctx);
    
    // Run full initialization. Returns result with all phases documented.
    InitializationResult initialize();
    
    // Get the current runtime state after initialization
    const InitializationRegistry& registry() const { return registry_; }
    
    // Get discovered host identity
    const HostIdentity& host_identity() const { return host_identity_; }
    
    // Check if a specific provider is ready
    bool is_provider_ready(std::string_view provider_id) const;

private:
    InitializationContext ctx_;
    InitializationRegistry registry_;
    HostIdentity host_identity_;
    
    // Configuration values merged from all sources
    std::map<std::string, std::string> config_values_;
    
    // Provider readiness cache
    std::map<std::string, bool> provider_ready_cache_;
    
    // Run each initialization stage
    InitializationPhase run_config_resolve();
    InitializationPhase run_identity_discovery();
    InitializationPhase run_dependency_check();
    InitializationPhase run_provider_readiness();
};

// ---------------------------------------------------------------------------
// Helper functions for common initialization tasks
// ---------------------------------------------------------------------------

// Resolve configuration from multiple sources (env, config files, defaults)
core::Result<std::map<std::string, std::string>> resolve_configuration(
    const std::vector<ConfigurationSource>& sources,
    std::optional<std::filesystem::path> system_config_path = std::nullopt);

// Discover host identity information
core::Result<HostIdentity> discover_host_identity();

// Check if a dependency is satisfied (file, command, library)
core::Result<bool> check_dependency(
    std::string_view name,
    std::optional<std::filesystem::path> path = std::nullopt,
    std::optional<std::string> version_regex = std::nullopt);

}  // namespace rebuntu::runtime::initialization