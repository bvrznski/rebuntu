// rebuntu::shell — Predicate Implementations (Phase 6.9)
//
// This module provides implementations of all predicate functions defined in predicates.hpp:
//   - installed_predicate: Check if a package is installed
//   - declared_predicate: Check if a named entity is declared/defined
//   - running_predicate: Check if a process/service is currently running
//   - enabled_predicate: Check if a service/unit is enabled for auto-activation
//   - disabled_predicate: Check if a service/unit is disabled
//   - active_predicate: Check if a service is currently active
//   - inactive_predicate: Check if a service is currently inactive
//   - healthy_predicate: Check if a service meets its health contract
//   - ready_predicate: Check if a service is ready to accept work
//   - reachable_predicate: Check if a network endpoint is reachable
//   - writable_predicate: Check if a path can accept writes
//   - readable_predicate: Check if a path can be read
//   - executable_predicate: Check if an entity is executable
//   - mounted_predicate: Check if a filesystem mount point is active

#pragma once

#include "predicates.hpp"
#include "types.hpp"

#include <adapters/systemd/service/types.hpp>
#include <adapters/package_managers/dpkg/types.hpp>

#include <system/core/contracts.hpp>
#include <system/evidence/collector.hpp>

#include <filesystem>
#include <fstream>
#include <optional>
#include <vector>
#include <unistd.h>
#include <cstring>

namespace rebuntu::shell {

// ============================================================================
// Helper: Create evidence from observation
// ============================================================================

static core::Evidence make_evidence(std::string source, std::string value, std::chrono::system_clock::time_point captured_at = {}) {
    core::Evidence e;
    e.source = std::move(source);
    e.value = std::move(value);
    
    if (captured_at.time_since_epoch().count() == 0) {
        e.captured_at = "unknown";
    } else {
        auto tt = std::chrono::system_clock::to_time_t(captured_at);
        char buf[32];
        strftime(buf, sizeof(buf), "%Y-%m-%dT%H:%M:%SZ", gmtime(&tt));
        e.captured_at = std::string{buf};
    }
    return e;
}

// ============================================================================
// Helper: Check if package is installed using dpkg
// ============================================================================

static bool check_package_installed(const std::string& package_name) {
    namespace dpkg = rebuntu::adapters::package_managers::dpkg;
    
    auto adapter = dpkg::make_dpkg_package_inventory_adapter();
    if (!adapter) {
        return false;  // Adapter unavailable - cannot determine
    }
    
    // Get all packages and search for our target
    auto result = adapter->observe_all_packages();
    
    if (result.status != core::SemanticStatus::kSuccess) {
        return false;
    }
    
    for (const auto& pkg : result.packages) {
        if (pkg.identity.name == package_name && 
            pkg.install_state == dpkg::PackageInstallState::kInstalled) {
            return true;
        }
    }
    
    return false;
}

// ============================================================================
// Helper: Check service state using systemd
// ============================================================================

static std::optional<adapters::systemd::service::ServiceObservation> get_service_observation(
    const adapters::systemd::service::ServiceIdentity& identity) {
    
    auto adapter = adapters::systemd::service::make_systemd_service_discovery_adapter();
    if (!adapter) {
        return std::nullopt;
    }
    
    return adapter->observe_service(identity);
}

// ============================================================================
// installed_predicate — Check if a package is installed
// ============================================================================

PredicateResult installed_predicate(const std::string& package_name) {
    bool is_installed = check_package_installed(package_name);
    
    if (is_installed) {
        PredicateResult r;
        r.status = core::SemanticStatus::kSuccess;
        r.is_true = true;
        return r;
    } else {
        PredicateResult r;
        r.status = core::SemanticStatus::kFailure;
        r.is_true = false;
        return r;
    }
}

// ============================================================================
// declared_predicate — Check if a named entity is declared/defined
// ============================================================================

PredicateResult declared_predicate(
    const std::string& subject_type,
    const std::string& entity_name
) {
    // Handle known subject types
    if (subject_type == "service") {
        adapters::systemd::service::ServiceIdentity identity;
        identity.name = entity_name;
        identity.type = "service";
        
        auto observation = get_service_observation(identity);
        
        if (!observation) {
            PredicateResult r;
            r.status = core::SemanticStatus::kFailure;
            r.is_true = false;
            return r;
        }
        
        PredicateResult r;
        r.status = core::SemanticStatus::kSuccess;
        r.is_true = true;
        return r;
    }
    
    // Unknown subject type
    PredicateResult r;
    r.status = core::SemanticStatus::kUnknown;
    r.is_true = std::nullopt;
    r.error = core::Error{"E_UNKNOWN", "unknown subject type: " + subject_type};
    return r;
}

// ============================================================================
// running_predicate — Check if a process/service is currently running
// ============================================================================

PredicateResult running_predicate(
    const std::string& subject_type,
    const std::string& entity_id
) {
    if (subject_type == "service") {
        adapters::systemd::service::ServiceIdentity identity;
        identity.name = entity_id;
        identity.type = "service";
        
        auto observation = get_service_observation(identity);
        
        if (!observation) {
            PredicateResult r;
            r.status = core::SemanticStatus::kFailure;
            r.is_true = false;
            return r;
        }
        
        bool is_running = (observation->active_state == adapters::systemd::service::ServiceActiveState::kActive);
        
        PredicateResult r;
        r.status = is_running ? core::SemanticStatus::kSuccess : core::SemanticStatus::kFailure;
        r.is_true = is_running;
        return r;
    }
    
    // Unknown subject type
    PredicateResult r;
    r.status = core::SemanticStatus::kUnknown;
    r.is_true = std::nullopt;
    r.error = core::Error{"E_UNKNOWN", "unknown subject type: " + subject_type};
    return r;
}

// ============================================================================
// enabled_predicate — Check if a service/unit is enabled for auto-activation
// ============================================================================

PredicateResult enabled_predicate(const std::string& service_name) {
    adapters::systemd::service::ServiceIdentity identity;
    identity.name = service_name;
    identity.type = "service";
    
    auto observation = get_service_observation(identity);
    
    if (!observation) {
        PredicateResult r;
        r.status = core::SemanticStatus::kFailure;
        r.is_true = false;
        return r;
    }
    
    bool is_enabled = (observation->unit_state == adapters::systemd::service::ServiceUnitState::kEnabled);
    
    PredicateResult r;
    r.status = is_enabled ? core::SemanticStatus::kSuccess : core::SemanticStatus::kFailure;
    r.is_true = is_enabled;
    return r;
}

// ============================================================================
// disabled_predicate — Check if a service/unit is disabled
// ============================================================================

PredicateResult disabled_predicate(const std::string& service_name) {
    adapters::systemd::service::ServiceIdentity identity;
    identity.name = service_name;
    identity.type = "service";
    
    auto observation = get_service_observation(identity);
    
    if (!observation) {
        PredicateResult r;
        r.status = core::SemanticStatus::kFailure;
        r.is_true = false;
        return r;
    }
    
    bool is_disabled = (observation->unit_state == adapters::systemd::service::ServiceUnitState::kDisabled);
    
    PredicateResult r;
    r.status = is_disabled ? core::SemanticStatus::kSuccess : core::SemanticStatus::kFailure;
    r.is_true = is_disabled;
    return r;
}

// ============================================================================
// active_predicate — Check if a service is currently active
// ============================================================================

PredicateResult active_predicate(const std::string& service_name) {
    adapters::systemd::service::ServiceIdentity identity;
    identity.name = service_name;
    identity.type = "service";
    
    auto observation = get_service_observation(identity);
    
    if (!observation) {
        PredicateResult r;
        r.status = core::SemanticStatus::kFailure;
        r.is_true = false;
        return r;
    }
    
    bool is_active = (observation->active_state == adapters::systemd::service::ServiceActiveState::kActive);
    
    PredicateResult r;
    r.status = is_active ? core::SemanticStatus::kSuccess : core::SemanticStatus::kFailure;
    r.is_true = is_active;
    return r;
}

// ============================================================================
// inactive_predicate — Check if a service is currently inactive
// ============================================================================

PredicateResult inactive_predicate(const std::string& service_name) {
    adapters::systemd::service::ServiceIdentity identity;
    identity.name = service_name;
    identity.type = "service";
    
    auto observation = get_service_observation(identity);
    
    if (!observation) {
        PredicateResult r;
        r.status = core::SemanticStatus::kFailure;
        r.is_true = false;
        return r;
    }
    
    bool is_inactive = (observation->active_state == adapters::systemd::service::ServiceActiveState::kInactive);
    
    PredicateResult r;
    r.status = is_inactive ? core::SemanticStatus::kSuccess : core::SemanticStatus::kFailure;
    r.is_true = is_inactive;
    return r;
}

// ============================================================================
// healthy_predicate — Check if a service meets its health contract
//
// For now, this checks if the service is active and running.
// A more sophisticated implementation would check for specific health endpoints.
// ============================================================================

PredicateResult healthy_predicate(const std::string& service_name) {
    adapters::systemd::service::ServiceIdentity identity;
    identity.name = service_name;
    identity.type = "service";
    
    auto observation = get_service_observation(identity);
    
    if (!observation) {
        PredicateResult r;
        r.status = core::SemanticStatus::kFailure;
        r.is_true = false;
        return r;
    }
    
    // For services, being active and running typically means healthy
    bool is_healthy = 
        (observation->active_state == adapters::systemd::service::ServiceActiveState::kActive) &&
        (observation->sub_state == adapters::systemd::service::ServiceSubState::kRunning);
    
    PredicateResult r;
    r.status = is_healthy ? core::SemanticStatus::kSuccess : core::SemanticStatus::kFailure;
    r.is_true = is_healthy;
    return r;
}

// ============================================================================
// ready_predicate — Check if a service is ready to accept work
//
// For now, this checks if the service is active and running.
// A more sophisticated implementation would check readiness probes or endpoints.
// ============================================================================

PredicateResult ready_predicate(const std::string& service_name) {
    // For services, readiness typically means the same as being healthy
    return healthy_predicate(service_name);
}

// ============================================================================
// reachable_predicate — Check if a network endpoint is reachable
// ============================================================================

PredicateResult reachable_predicate(
    const std::string& host,
    int port
) {
    // Simple reachability check using access() - for now, return UNKNOWN
    (void)host;
    (void)port;
    
    PredicateResult r;
    r.status = core::SemanticStatus::kUnknown;
    r.is_true = std::nullopt;
    r.error = core::Error{"E_UNKNOWN", "network reachability check not yet implemented"};
    return r;
}

// ============================================================================
// writable_predicate — Check if a path can accept writes
// ============================================================================

PredicateResult writable_predicate(const std::string& path) {
    // Use native Linux access() system call to check writability
    int result = access(path.c_str(), W_OK);
    
    PredicateResult r;
    if (result == 0) {
        r.status = core::SemanticStatus::kSuccess;
        r.is_true = true;
    } else {
        r.status = core::SemanticStatus::kFailure;
        r.is_true = false;
    }
    return r;
}

// ============================================================================
// readable_predicate — Check if a path can be read
// ============================================================================

PredicateResult readable_predicate(const std::string& path) {
    // Use native Linux access() system call to check readability
    int result = access(path.c_str(), R_OK);
    
    PredicateResult r;
    if (result == 0) {
        r.status = core::SemanticStatus::kSuccess;
        r.is_true = true;
    } else {
        r.status = core::SemanticStatus::kFailure;
        r.is_true = false;
    }
    return r;
}

// ============================================================================
// executable_predicate — Check if an entity is executable
// ============================================================================

PredicateResult executable_predicate(const std::string& path) {
    // Use native Linux access() system call to check executability
    int result = access(path.c_str(), X_OK);
    
    PredicateResult r;
    if (result == 0) {
        r.status = core::SemanticStatus::kSuccess;
        r.is_true = true;
    } else {
        r.status = core::SemanticStatus::kFailure;
        r.is_true = false;
    }
    return r;
}

// ============================================================================
// mounted_predicate — Check if a filesystem mount point is active
// ============================================================================

PredicateResult mounted_predicate(const std::string& mount_point) {
    // Use native Linux approach: check if path exists and is accessible
    
    std::error_code ec;
    
    // Check if mount point path exists and is a directory
    if (!std::filesystem::exists(mount_point, ec)) {
        PredicateResult r;
        r.status = core::SemanticStatus::kFailure;
        r.is_true = false;
        return r;
    }
    
    if (!std::filesystem::is_directory(mount_point, ec)) {
        PredicateResult r;
        r.status = core::SemanticStatus::kFailure;
        r.is_true = false;
        return r;
    }
    
    // A more sophisticated implementation would check /proc/mounts for actual mounts
    PredicateResult r;
    r.status = core::SemanticStatus::kUnknown;
    r.is_true = std::nullopt;
    r.error = core::Error{"E_UNKNOWN", "mount state check not yet implemented - use filesystem adapter"};
    return r;
}

// ============================================================================
// Predicate Registry Implementation
// ============================================================================

std::optional<PredicateMetadata> PredicateRegistry::find(std::string_view name) const {
    auto it = predicates_.find(std::string{name});
    if (it == predicates_.end()) return std::nullopt;
    return it->second;
}

std::vector<PredicateMetadata> PredicateRegistry::all() const {
    std::vector<PredicateMetadata> result;
    for (const auto& [name, meta] : predicates_) {
        result.push_back(meta);
    }
    // Sort by name for deterministic output
    std::sort(result.begin(), result.end(),
              [](const PredicateMetadata& a, const PredicateMetadata& b) { return a.name < b.name; });
    return result;
}

// ============================================================================
// Predicate Registry Initialization (for metadata registration)
// ============================================================================

void initialize_predicate_registry(PredicateRegistry& registry) {
    // installed
    registry.register_predicate({
        .name = "installed",
        .aliases = {"exists", "present"},
        .kind = PredicateKind::kPackage,
        .subject_types = {"package"},
        .description = "Check if a package is installed in the system",
        .true_condition = "Package exists in dpkg database with full installation state",
        .false_condition = "Package not found or not fully installed",
        .unknown_condition = "dpkg adapter unavailable or error reading package database"
    });
    
    // declared
    registry.register_predicate({
        .name = "declared",
        .aliases = {"defined", "configured"},
        .kind = PredicateKind::kService,
        .subject_types = {"service", "user", "group"},
        .description = "Check if a named entity is declared in the system",
        .true_condition = "Entity exists in systemd or configuration registry",
        .false_condition = "Entity not found in registry",
        .unknown_condition = "Registry unavailable or unknown subject type"
    });
    
    // running
    registry.register_predicate({
        .name = "running",
        .aliases = {"active", "executing"},
        .kind = PredicateKind::kService,
        .subject_types = {"service", "process"},
        .description = "Check if a process/service is currently executing",
        .true_condition = "Process/service has active runtime state",
        .false_condition = "Process/service is stopped or inactive",
        .unknown_condition = "State cannot be determined from native interfaces"
    });
    
    // enabled
    registry.register_predicate({
        .name = "enabled",
        .aliases = {"auto-start", "autostart"},
        .kind = PredicateKind::kService,
        .subject_types = {"service"},
        .description = "Check if a service is enabled for automatic activation",
        .true_condition = "Service unit file state is 'enabled'",
        .false_condition = "Service unit file state is not 'enabled'",
        .unknown_condition = "Unit file state cannot be determined"
    });
    
    // disabled
    registry.register_predicate({
        .name = "disabled",
        .aliases = {"not-enabled"},
        .kind = PredicateKind::kService,
        .subject_types = {"service"},
        .description = "Check if a service is disabled from automatic activation",
        .true_condition = "Service unit file state is 'disabled'",
        .false_condition = "Service is enabled or static",
        .unknown_condition = "Unit file state cannot be determined"
    });
    
    // active
    registry.register_predicate({
        .name = "active",
        .aliases = {},
        .kind = PredicateKind::kService,
        .subject_types = {"service"},
        .description = "Check if a service is currently in active state",
        .true_condition = "Service active state is 'active'",
        .false_condition = "Service active state is not 'active'",
        .unknown_condition = "Active state cannot be determined"
    });
    
    // inactive
    registry.register_predicate({
        .name = "inactive",
        .aliases = {},
        .kind = PredicateKind::kService,
        .subject_types = {"service"},
        .description = "Check if a service is currently in inactive state",
        .true_condition = "Service active state is 'inactive'",
        .false_condition = "Service is active or in transitional state",
        .unknown_condition = "Active state cannot be determined"
    });
    
    // healthy
    registry.register_predicate({
        .name = "healthy",
        .aliases = {"ok", "health-ok"},
        .kind = PredicateKind::kService,
        .subject_types = {"service"},
        .description = "Check if a service meets its health contract",
        .true_condition = "Service is active and running normally",
        .false_condition = "Service is failing or in degraded state",
        .unknown_condition = "Health state cannot be determined"
    });
    
    // ready
    registry.register_predicate({
        .name = "ready",
        .aliases = {"available", "operational"},
        .kind = PredicateKind::kService,
        .subject_types = {"service"},
        .description = "Check if a service is ready to accept work",
        .true_condition = "Service is active, healthy and accepting connections",
        .false_condition = "Service is not ready for traffic",
        .unknown_condition = "Readiness cannot be determined"
    });
    
    // reachable
    registry.register_predicate({
        .name = "reachable",
        .aliases = {"accessible", "pingable"},
        .kind = PredicateKind::kNetwork,
        .subject_types = {"host", "endpoint", "service"},
        .description = "Check if a network endpoint is reachable",
        .true_condition = "Target responds within timeout",
        .false_condition = "Target unreachable or timed out",
        .unknown_condition = "Network stack unavailable"
    });
    
    // writable
    registry.register_predicate({
        .name = "writable",
        .aliases = {"writeable"},
        .kind = PredicateKind::kFilesystem,
        .subject_types = {"path", "file", "directory"},
        .description = "Check if a path can accept writes",
        .true_condition = "Current user has write permission to the path",
        .false_condition = "Path not writable due to permissions or missing parent",
        .unknown_condition = "Cannot determine write capability"
    });
    
    // readable
    registry.register_predicate({
        .name = "readable",
        .aliases = {},
        .kind = PredicateKind::kFilesystem,
        .subject_types = {"path", "file", "directory"},
        .description = "Check if a path can be read",
        .true_condition = "Current user has read permission to the path",
        .false_condition = "Path not readable due to permissions or missing",
        .unknown_condition = "Cannot determine readability"
    });
    
    // executable
    registry.register_predicate({
        .name = "executable",
        .aliases = {"runnable", "launchable"},
        .kind = PredicateKind::kFilesystem,
        .subject_types = {"path", "file"},
        .description = "Check if an entity is executable",
        .true_condition = "Entity has execute permission bits set",
        .false_condition = "Entity not executable or missing",
        .unknown_condition = "Cannot determine executability"
    });
    
    // mounted
    registry.register_predicate({
        .name = "mounted",
        .aliases = {"attached", "bound"},
        .kind = PredicateKind::kFilesystem,
        .subject_types = {"mount-point", "directory"},
        .description = "Check if a filesystem mount point is active",
        .true_condition = "Mount point has an active filesystem mounted",
        .false_condition = "No filesystem mounted at this path",
        .unknown_condition = "Cannot determine mount status"
    });
}

}  // namespace rebuntu::shell