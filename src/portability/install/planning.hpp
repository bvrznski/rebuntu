#include <cstdint>
// rebuntu::install::planning — Installation planning & environment preparation (Phase 1.2)
//
// This module takes validated installation intent + discovered host facts
// and produces an explicit, reviewable installation plan.
#pragma once

#include <system/core/contracts.hpp>
#include <portability/install/contracts.hpp>
#include <observation/environment/discovery.hpp>

#include <string>
#include <vector>
#include <optional>

namespace rebuntu::install::planning {

// ---------------------------------------------------------------------------
// InstallationIntent
// The user's declared intent for what should be installed.
// ---------------------------------------------------------------------------
struct InstallationIntent {
    std::string version;                    // Target version to install
    InstallationScope scope;               // System-wide or per-user
    bool skip_verification = false;        // Skip verification during planning
    
    // Optional features/components to include
    std::vector<std::string> optional_features;
    
    // Explicit targets (overrides default paths)
    std::optional<std::string> explicit_bin_path;
    std::optional<std::string> explicit_state_dir;
    std::optional<std::string> explicit_config_dir;
};

// ---------------------------------------------------------------------------
// DependencyInfo
// Information about a dependency and its status.
// ---------------------------------------------------------------------------
struct DependencyInfo {
    std::string name;                      // Human-readable name
    std::string id;                        // Machine identifier (e.g., package name)
    
    enum class Status {
        kAvailable,
        kNotInstalled,
        kVersionTooOld,
        kUnknown
    } status = Status::kUnknown;
    
    std::optional<std::string> installed_version;
    std::optional<std::string> required_version;
};

// ---------------------------------------------------------------------------
// PreInstallationCheckResult
// Result of pre-installation checks.
// ---------------------------------------------------------------------------
struct PreInstallationCheckResult {
    enum class Level {
        kInfo,
        kWarning,
        kBlocker
    };
    
    std::string name;                      // Check identifier
    bool passed = false;
    Level level = Level::kInfo;
    std::optional<std::string> message;
    std::optional<std::string> remediation;
};

// ---------------------------------------------------------------------------
// InstallationStep
// A single step in the installation plan.
// ---------------------------------------------------------------------------
struct InstallationStep {
    enum class Type {
        kValidate,
        kAcquire,
        kCreateDirectory,
        kCopyFile,
        kSetPermissions,
        kEnableService,
        kVerify
    } type = Type::kValidate;
    
    std::string description;               // Human-readable step description
    std::vector<std::string> argv;         // Command arguments for executable types
    
    std::optional<std::string> target_path;
    std::optional<uint32_t> expected_mode;
    std::optional<std::string> expected_owner;
    
    bool requires_privilege = false;
    bool is_optional = false;
    
    // Verification after this step
    std::vector<std::string> verification_steps;
};

// ---------------------------------------------------------------------------
// InstallationPlan
// A complete, reviewable installation plan.
// ---------------------------------------------------------------------------
struct InstallationPlan {
    enum class Status {
        kReady,           // Plan is ready to execute
        kBlocked,         // Has blockers that must be resolved
        kWarningOnly      // Has warnings but can proceed
    } status = Status::kReady;
    
    std::string version;                   // Target version being installed
    
    InstallationScope scope;              // System vs user installation
    bool is_dry_run = false;               // True if this is just a plan (no actual mutation)
    
    // Host facts that informed the plan
    environment::discovery::HostDiscoveryResult host_facts;
    
    // Dependencies with their status
    std::vector<DependencyInfo> dependencies;
    
    // Pre-installation checks
    std::vector<PreInstallationCheckResult> preflight_checks;
    
    // Installation steps (ordered)
    std::vector<InstallationStep> steps;
    
    // Rollback strategy
    std::optional<std::string> rollback_description;
    
    // Expected outcomes after completion
    std::vector<std::string> expected_postconditions;
};

// ---------------------------------------------------------------------------
// Planner
// Produces installation plans from intent and discovered host facts.
// ---------------------------------------------------------------------------
class Planner {
public:
    explicit Planner(const environment::discovery::HostDiscoveryResult& facts);
    
    // Produce an installation plan for the given intent.
    InstallationPlan produce_plan(const InstallationIntent& intent) const;
    
private:
    const environment::discovery::HostDiscoveryResult& facts_;
    
    std::vector<PreInstallationCheckResult> evaluate_preflight_checks(
        const InstallationIntent& intent) const;
    
    std::vector<DependencyInfo> resolve_dependencies(
        const InstallationIntent& intent) const;
    
    std::vector<InstallationStep> build_installation_steps(
        const InstallationIntent& intent,
        const std::vector<PreInstallationCheckResult>& preflight,
        const std::vector<DependencyInfo>& deps) const;
    
    bool has_blockers(const std::vector<PreInstallationCheckResult>& checks) const;
};

// ---------------------------------------------------------------------------
// PreflightEvaluator
// Evaluates whether the host environment is ready for installation.
// ---------------------------------------------------------------------------
class PreflightEvaluator {
public:
    explicit PreflightEvaluator(const environment::discovery::HostDiscoveryResult& facts);
    
    // Run all preflight evaluations and return results.
    std::vector<PreInstallationCheckResult> evaluate() const;

private:
    const environment::discovery::HostDiscoveryResult& facts_;
    
    PreInstallationCheckResult check_distribution() const;
    PreInstallationCheckResult check_root_privileges() const;
    PreInstallationCheckResult check_bin_directory_writable() const;
    PreInstallationCheckResult check_state_directory_writable() const;
    PreInstallationCheckResult check_package_manager_available() const;
};

}  // namespace rebuntu::install::planning
