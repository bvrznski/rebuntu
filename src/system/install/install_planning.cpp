// rebuntu::install::planning — Installation planning & environment preparation (Phase 1.2)
#include <system/install/planning.hpp>

#include <array>
#include <cstdio>
#include <filesystem>
#include <fstream>
#include <regex>
#include <sstream>

namespace fs = std::filesystem;

namespace rebuntu::install::planning {

// ============================================================================
// PreflightEvaluator implementation
// ============================================================================

PreflightEvaluator::PreflightEvaluator(const environment::discovery::HostDiscoveryResult& facts)
    : facts_(facts) {}

PreInstallationCheckResult PreflightEvaluator::check_distribution() const {
    PreInstallationCheckResult result;
    result.name = "supported-distribution";
    
    if (!facts_.distribution.id.has_value()) {
        result.passed = false;
        result.level = PreInstallationCheckResult::Level::kWarning;
        result.message = "Could not detect distribution";
        return result;
    }
    
    const std::string& id = facts_.distribution.id.value();
    bool supported = (id.find("ubuntu") != std::string::npos ||
                      id.find("debian") != std::string::npos ||
                      id.find("fedora") != std::string::npos);
    
    if (supported) {
        result.passed = true;
        result.level = PreInstallationCheckResult::Level::kInfo;
        result.message = "Distribution '" + id + "' is supported";
    } else {
        result.passed = false;
        result.level = PreInstallationCheckResult::Level::kWarning;
        result.message = "Distribution '" + id + "' not explicitly tested";
    }
    
    return result;
}

PreInstallationCheckResult PreflightEvaluator::check_root_privileges() const {
    PreInstallationCheckResult result;
    result.name = "root-privileges";
    
    if (facts_.privilege.is_root) {
        result.passed = true;
        result.level = PreInstallationCheckResult::Level::kInfo;
        result.message = "Running with root privileges (system-wide installation)";
    } else {
        result.passed = false;
        result.level = PreInstallationCheckResult::Level::kBlocker;
        result.message = "Root privileges required for system-wide installation";
        result.remediation = "Run with sudo or use --scope=user flag for user-scoped install";
    }
    
    return result;
}

PreInstallationCheckResult PreflightEvaluator::check_bin_directory_writable() const {
    PreInstallationCheckResult result;
    result.name = "bin-directory-writable";
    
    if (facts_.privilege.is_root) {
        // For root, we assume /usr/bin is writable
        std::error_code ec;
        auto info = fs::status("/usr/bin", ec);
        
        if (!ec && fs::exists("/usr/bin", ec) && fs::is_directory("/usr/bin", ec)) {
            result.passed = true;
            result.level = PreInstallationCheckResult::Level::kInfo;
            result.message = "/usr/bin is accessible";
        } else {
            result.passed = false;
            result.level = PreInstallationCheckResult::Level::kBlocker;
            result.message = "/usr/bin is not accessible";
            result.remediation = "Ensure /usr/bin exists and is writable";
        }
    } else {
        // User-scoped: check ~/.local/bin
        if (facts_.filesystem.home_dir.has_value()) {
            std::string user_bin_path = facts_.filesystem.home_dir.value() + "/.local/bin";
            std::error_code ec;
            
            if (!fs::exists(user_bin_path, ec)) {
                // Directory doesn't exist yet - will be created during install
                result.passed = true;
                result.level = PreInstallationCheckResult::Level::kInfo;
                result.message = user_bin_path + " will be created";
            } else if (fs::is_directory(user_bin_path, ec)) {
                result.passed = true;
                result.level = PreInstallationCheckResult::Level::kInfo;
                result.message = user_bin_path + " is accessible";
            } else {
                result.passed = false;
                result.level = PreInstallationCheckResult::Level::kBlocker;
                result.message = user_bin_path + " exists but is not a directory";
            }
        } else {
            result.passed = false;
            result.level = PreInstallationCheckResult::Level::kBlocker;
            result.message = "HOME environment variable not set";
            result.remediation = "Set HOME and ensure ~/.local/bin is accessible";
        }
    }
    
    return result;
}

PreInstallationCheckResult PreflightEvaluator::check_state_directory_writable() const {
    PreInstallationCheckResult result;
    result.name = "state-directory-writable";
    
    if (facts_.privilege.is_root) {
        std::error_code ec;
        auto info = fs::status("/var/lib", ec);
        
        if (!ec && fs::exists("/usr/bin", ec) && fs::is_directory("/usr/bin", ec)) {
            result.passed = true;
            result.level = PreInstallationCheckResult::Level::kInfo;
            result.message = "/var/lib is accessible";
        } else {
            result.passed = false;
            result.level = PreInstallationCheckResult::Level::kBlocker;
            result.message = "/var/lib is not accessible";
        }
    } else {
        // User-scoped: check ~/.local/state
        if (facts_.filesystem.home_dir.has_value()) {
            std::string user_state_path = facts_.filesystem.home_dir.value() + "/.local/state";
            std::error_code ec;
            
            if (!fs::exists(user_state_path, ec)) {
                result.passed = true;
                result.level = PreInstallationCheckResult::Level::kInfo;
                result.message = user_state_path + " will be created";
            } else if (fs::is_directory(user_state_path, ec)) {
                result.passed = true;
                result.level = PreInstallationCheckResult::Level::kInfo;
                result.message = user_state_path + " is accessible";
            } else {
                result.passed = false;
                result.level = PreInstallationCheckResult::Level::kBlocker;
                result.message = user_state_path + " exists but is not a directory";
            }
        } else {
            result.passed = false;
            result.level = PreInstallationCheckResult::Level::kBlocker;
            result.message = "HOME environment variable not set";
        }
    }
    
    return result;
}

PreInstallationCheckResult PreflightEvaluator::check_package_manager_available() const {
    PreInstallationCheckResult result;
    result.name = "package-manager";
    
    if (facts_.package_manager.available.empty()) {
        // We may still proceed with manual installation, just warn
        result.passed = false;
        result.level = PreInstallationCheckResult::Level::kWarning;
        result.message = "No package manager detected";
        result.remediation = "Manual dependency management required";
    } else {
        result.passed = true;
        result.level = PreInstallationCheckResult::Level::kInfo;
        
        std::ostringstream oss;
        oss << "Package managers available: ";
        for (size_t i = 0; i < facts_.package_manager.available.size(); ++i) {
            if (i > 0) oss << ", ";
            switch (facts_.package_manager.available[i]) {
                case environment::discovery::PackageManager::kApt:
                    oss << "apt"; break;
                case environment::discovery::PackageManager::kDpkg:
                    oss << "dpkg"; break;
                case environment::discovery::PackageManager::kSnap:
                    oss << "snap"; break;
                case environment::discovery::PackageManager::kPip:
                    oss << "pip"; break;
                default:
                    oss << "unknown";
            }
        }
        result.message = oss.str();
    }
    
    return result;
}

std::vector<PreInstallationCheckResult> PreflightEvaluator::evaluate() const {
    std::vector<PreInstallationCheckResult> results;
    
    results.push_back(check_distribution());
    results.push_back(check_root_privileges());
    results.push_back(check_bin_directory_writable());
    results.push_back(check_state_directory_writable());
    results.push_back(check_package_manager_available());
    
    return results;
}

// ============================================================================
// Planner implementation
// ============================================================================

Planner::Planner(const environment::discovery::HostDiscoveryResult& facts)
    : facts_(facts) {}

bool Planner::has_blockers(const std::vector<PreInstallationCheckResult>& checks) const {
    for (const auto& check : checks) {
        if (check.level == PreInstallationCheckResult::Level::kBlocker && !check.passed) {
            return true;
        }
    }
    return false;
}

std::vector<PreInstallationCheckResult> Planner::evaluate_preflight_checks(
    const InstallationIntent& intent) const {
    
    PreflightEvaluator evaluator(facts_);
    auto results = evaluator.evaluate();
    
    // Add intent-specific checks
    PreInstallationCheckResult scope_check;
    scope_check.name = "scope-consistency";
    scope_check.level = PreInstallationCheckResult::Level::kInfo;
    
    if (intent.scope == InstallationScope::kSystem && !facts_.privilege.is_root) {
        scope_check.passed = false;
        scope_check.level = PreInstallationCheckResult::Level::kBlocker;
        scope_check.message = "System installation requires root privileges";
        scope_check.remediation = "Run with sudo or use user scope";
    } else {
        scope_check.passed = true;
        scope_check.message = "Scope configuration is consistent";
    }
    
    results.push_back(scope_check);
    
    return results;
}

std::vector<DependencyInfo> Planner::resolve_dependencies(
    const InstallationIntent& intent) const {
    
    (void)&intent;  // Suppress unused parameter warning
    
    std::vector<DependencyInfo> deps;
    
    // Base system dependencies
    {
        DependencyInfo dep;
        dep.name = "C++ runtime";
        dep.id = "libstdc++6";
        
        if (facts_.package_manager.available.empty()) {
            dep.status = DependencyInfo::Status::kUnknown;
        } else {
            dep.status = DependencyInfo::Status::kAvailable;
        }
        deps.push_back(dep);
    }
    
    // Add any optional feature dependencies
    for (const auto& feature : intent.optional_features) {
        if (feature == "semantic" || feature == "ml") {
            DependencyInfo dep;
            dep.name = "Python 3 runtime";
            dep.id = "python3";
            
            if (facts_.runtime.python_status == environment::discovery::RuntimeAvailability::kAvailable) {
                dep.status = DependencyInfo::Status::kAvailable;
                if (facts_.runtime.python_major.has_value() && facts_.runtime.python_minor.has_value()) {
                    std::ostringstream oss;
                    oss << facts_.runtime.python_major.value() << "." 
                        << facts_.runtime.python_minor.value();
                    dep.installed_version = oss.str();
                }
            } else if (facts_.runtime.python_status == environment::discovery::RuntimeAvailability::kVersionTooOld) {
                dep.status = DependencyInfo::Status::kVersionTooOld;
                dep.required_version = "3.8";
            } else {
                dep.status = DependencyInfo::Status::kNotInstalled;
            }
            
            deps.push_back(dep);
        }
    }
    
    return deps;
}

std::vector<InstallationStep> Planner::build_installation_steps(
    const InstallationIntent& intent,
    const std::vector<PreInstallationCheckResult>& preflight,
    const std::vector<DependencyInfo>& /*deps*/) const {
    
    (void)&preflight;  // Suppress unused parameter warning
    
    std::vector<InstallationStep> steps;
    
    // Step 1: Validate preconditions
    {
        InstallationStep step;
        step.type = InstallationStep::Type::kValidate;
        step.description = "Validate installation prerequisites";
        
        if (has_blockers(preflight)) {
            step.argv.push_back("--dry-run");
            step.argv.push_back("--strict");
        }
        
        steps.push_back(step);
    }
    
    // Step 2: Create directory structure
    std::string bin_path, state_path, config_path;
    
    if (intent.scope == InstallationScope::kSystem) {
        bin_path = "/usr/bin";
        state_path = "/var/lib/rebuntu";
        config_path = "/etc/rebuntu";
    } else {
        if (facts_.filesystem.home_dir.has_value()) {
            bin_path = facts_.filesystem.home_dir.value() + "/.local/bin";
            state_path = facts_.filesystem.home_dir.value() + "/.local/state/rebuntu";
            config_path = facts_.filesystem.home_dir.value() + "/.config/rebuntu";
        }
    }
    
    if (!bin_path.empty()) {
        InstallationStep step;
        step.type = InstallationStep::Type::kCreateDirectory;
        step.description = "Create bin directory: " + bin_path;
        
        if (intent.scope == InstallationScope::kSystem) {
            step.argv.push_back("mkdir");
            step.argv.push_back("-p");
            step.argv.push_back(bin_path);
            step.requires_privilege = true;
            step.expected_owner = "root";
        } else {
            step.argv.push_back("mkdir");
            step.argv.push_back("-p");
            step.argv.push_back(bin_path);
        }
        
        step.verification_steps.push_back("test -d " + bin_path);
        steps.push_back(step);
    }
    
    if (!state_path.empty()) {
        InstallationStep step;
        step.type = InstallationStep::Type::kCreateDirectory;
        step.description = "Create state directory: " + state_path;
        
        if (intent.scope == InstallationScope::kSystem) {
            step.argv.push_back("mkdir");
            step.argv.push_back("-p");
            step.argv.push_back(state_path);
            step.requires_privilege = true;
            step.expected_owner = "root";
        } else {
            step.argv.push_back("mkdir");
            step.argv.push_back("-p");
            step.argv.push_back(state_path);
        }
        
        step.verification_steps.push_back("test -d " + state_path);
        steps.push_back(step);
    }
    
    if (!config_path.empty()) {
        InstallationStep step;
        step.type = InstallationStep::Type::kCreateDirectory;
        step.description = "Create config directory: " + config_path;
        
        if (intent.scope == InstallationScope::kSystem) {
            step.argv.push_back("mkdir");
            step.argv.push_back("-p");
            step.argv.push_back(config_path);
            step.requires_privilege = true;
            step.expected_owner = "root";
        } else {
            step.argv.push_back("mkdir");
            step.argv.push_back("-p");
            step.argv.push_back(config_path);
        }
        
        step.verification_steps.push_back("test -d " + config_path);
        steps.push_back(step);
    }
    
    // Step 3: Copy binary
    {
        InstallationStep step;
        step.type = InstallationStep::Type::kCopyFile;
        step.description = "Install rebuntu binary to " + bin_path;
        
        std::string source = "build/src/rebuntu";
        std::string target = bin_path + "/rebuntu";
        
        if (intent.scope == InstallationScope::kSystem) {
            step.argv.push_back("cp");
            step.argv.push_back(source);
            step.argv.push_back(target);
            step.requires_privilege = true;
            step.expected_mode = 0755u;
            step.expected_owner = "root";
        } else {
            step.argv.push_back("cp");
            step.argv.push_back(source);
            step.argv.push_back(target);
        }
        
        step.verification_steps.push_back("test -x " + target);
        steps.push_back(step);
    }
    
    // Step 4: Set permissions (for system installs)
    if (intent.scope == InstallationScope::kSystem) {
        InstallationStep step;
        step.type = InstallationStep::Type::kSetPermissions;
        step.description = "Verify binary permissions";
        step.target_path = bin_path + "/rebuntu";
        step.expected_mode = 0755u;
        step.verification_steps.push_back("test -x " + bin_path + "/rebuntu");
        steps.push_back(step);
    }
    
    // Step 5: Verify installation
    {
        InstallationStep step;
        step.type = InstallationStep::Type::kVerify;
        step.description = "Verify binary is executable";
        
        if (intent.scope == InstallationScope::kSystem) {
            step.argv.push_back("test");
            step.argv.push_back("-x");
            step.argv.push_back("/usr/bin/rebuntu");
        } else {
            if (facts_.filesystem.home_dir.has_value()) {
                std::string test_path = facts_.filesystem.home_dir.value() + "/.local/bin/rebuntu";
                step.argv.push_back("test");
                step.argv.push_back("-x");
                step.argv.push_back(test_path);
            }
        }
        
        steps.push_back(step);
    }
    
    // Step 6: Add to PATH (user scope only)
    if (intent.scope == InstallationScope::kUser && facts_.filesystem.home_dir.has_value()) {
        InstallationStep step;
        step.type = InstallationStep::Type::kVerify;
        step.description = "Confirm user bin in PATH";
        step.is_optional = true;
        
        std::string home = facts_.filesystem.home_dir.value();
        step.verification_steps.push_back("echo $PATH | grep -q '" + home + "/.local/bin'");
        
        steps.push_back(step);
    }
    
    // Add verification summary step
    {
        InstallationStep step;
        step.type = InstallationStep::Type::kVerify;
        step.description = "Final verification: check binary version";
        
        if (intent.scope == InstallationScope::kSystem) {
            step.argv.push_back("/usr/bin/rebuntu");
            step.argv.push_back("--version");
        } else {
            if (facts_.filesystem.home_dir.has_value()) {
                std::string test_path = facts_.filesystem.home_dir.value() + "/.local/bin/rebuntu";
                step.argv.push_back(test_path);
                step.argv.push_back("--version");
            }
        }
        
        steps.push_back(step);
    }
    
    return steps;
}

InstallationPlan Planner::produce_plan(const InstallationIntent& intent) const {
    InstallationPlan plan;
    
    // Populate plan metadata
    plan.version = intent.version;
    plan.scope = intent.scope;
    plan.is_dry_run = true;  // Planning phase - no actual mutation
    
    // Copy host facts for transparency
    plan.host_facts = facts_;
    
    // Evaluate preflight checks
    auto preflight = evaluate_preflight_checks(intent);
    plan.preflight_checks.insert(plan.preflight_checks.end(),
                                  preflight.begin(), preflight.end());
    
    // Determine overall status
    if (has_blockers(preflight)) {
        plan.status = InstallationPlan::Status::kBlocked;
    } else {
        plan.status = InstallationPlan::Status::kWarningOnly;
    }
    
    // Resolve dependencies
    auto deps = resolve_dependencies(intent);
    plan.dependencies.insert(plan.dependencies.end(),
                             deps.begin(), deps.end());
    
    // Build installation steps
    plan.steps = build_installation_steps(intent, preflight, deps);
    
    // Add rollback description (for system-wide installs)
    if (intent.scope == InstallationScope::kSystem) {
        std::ostringstream rollback;
        rollback << "To rollback: rm -rf /usr/bin/rebuntu "
                 << "/var/lib/rebuntu /etc/rebuntu 2>/dev/null || true";
        plan.rollback_description = rollback.str();
    } else if (facts_.filesystem.home_dir.has_value()) {
        std::ostringstream rollback;
        std::string home = facts_.filesystem.home_dir.value();
        rollback << "To rollback: rm -rf " << home << "/.local/bin/rebuntu "
                 << home << "/.local/state/rebuntu "
                 << home << "/.config/rebuntu 2>/dev/null || true";
        plan.rollback_description = rollback.str();
    }
    
    // Expected postconditions
    {
        std::string target_path;
        if (intent.scope == InstallationScope::kSystem) {
            target_path = "/usr/bin/rebuntu";
        } else if (facts_.filesystem.home_dir.has_value()) {
            target_path = facts_.filesystem.home_dir.value() + "/.local/bin/rebuntu";
        }
        
        if (!target_path.empty()) {
            plan.expected_postconditions.push_back("Binary exists at " + target_path);
            plan.expected_postconditions.push_back("Binary has executable permissions");
            plan.expected_postconditions.push_back("Binary can be executed without errors");
            plan.expected_postconditions.push_back("State directory is accessible");
        }
    }
    
    return plan;
}

}  // namespace rebuntu::install::planning
