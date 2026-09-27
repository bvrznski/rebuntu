// rebuntu::shell — Predicate Dictionary (Phase 6.2)
//
// This module defines the complete predicate dictionary for Rebuntu:
//   - installed: Is a package installed?
//   - declared: Is a named entity defined?
//   - running: Is a process/service currently executing?
//   - enabled: Is a service/unit enabled for automatic activation?
//   - disabled: Is a service/unit disabled from automatic activation?
//   - active: Is a service currently active (running/online)?
//   - inactive: Is a service currently inactive?
//   - healthy: Does a service meet its health contract?
//   - ready: Can a service accept work now?
//   - reachable: Can network endpoint be contacted?
//   - writable: Can a path accept writes?
//   - readable: Can a path be read?
//   - executable: Is an entity executable?
//   - mounted: Is a filesystem mount point active?
//
// Design Philosophy:
//   * Predicates are READ-ONLY observations (no side effects)
//   * Three-valued logic: TRUE / FALSE / UNKNOWN
//   * Evidence is attached to every result for auditability
//   * Predicates never execute system mutations

#pragma once

#include "types.hpp"
#include <string>
#include <vector>
#include <map>

namespace rebuntu::shell {

// ============================================================================
// PredicateKind — Categories of predicates
// ============================================================================

enum class PredicateKind {
    kPackage,     // Package state (installed, declared)
    kService,     // Service lifecycle state
    kProcess,     // Process execution state
    kFilesystem,  // File/directory properties
    kNetwork,     // Network connectivity
};

inline std::string to_string(PredicateKind k) {
    switch (k) {
        case PredicateKind::kPackage:    return "package";
        case PredicateKind::kService:    return "service";
        case PredicateKind::kProcess:    return "process";
        case PredicateKind::kFilesystem: return "filesystem";
        case PredicateKind::kNetwork:    return "network";
    }
    return "unknown";
}

// ============================================================================
// PredicateMetadata — Machine-readable predicate documentation
// ============================================================================

struct PredicateMetadata {
    std::string name;                    // Canonical predicate name (e.g., "installed")
    std::vector<std::string> aliases;    // Alternative names (e.g., ["exists", "present"])
    PredicateKind kind{PredicateKind::kPackage};
    
    // Subject types this predicate works with
    std::vector<std::string> subject_types;
    
    // What the predicate checks
    std::string description;
    
    // Expected TRUE/FALSE conditions
    std::string true_condition;
    std::string false_condition;
    
    // When result is UNKNOWN
    std::string unknown_condition;
    
    // Side effects class (predicates should be NONE/OBSERVATION)
    SideEffectClass side_effect{SideEffectClass::OBSERVATION};
    
    // Mapped observation/query capability
    std::optional<std::string> mapped_capability;
};

// ============================================================================
// PredicateRegistry — Registry of available predicates
// ============================================================================

class PredicateRegistry {
public:
    void register_predicate(PredicateMetadata meta) {
        predicates_[meta.name] = std::move(meta);
    }
    
    // Find by canonical name or alias
    std::optional<PredicateMetadata> find(std::string_view name) const;
    
    // Get all predicates sorted by name
    std::vector<PredicateMetadata> all() const;
    
    size_t count() const { return predicates_.size(); }

private:
    std::map<std::string, PredicateMetadata> predicates_;
};

// ============================================================================
// installed_predicate — Check if a package is installed
//
// TRUE: Package exists in package database
// FALSE: Package does not exist in package database  
// UNKNOWN: Cannot determine package state (dpkg unavailable, error)
// ============================================================================

PredicateResult installed_predicate(const std::string& package_name);

// ============================================================================
// declared_predicate — Check if a named entity is declared/defined
//
// TRUE: Entity exists in configuration/system registry
// FALSE: Entity not found in registry
// UNKNOWN: Cannot access registry or ambiguous state
// ============================================================================

PredicateResult declared_predicate(
    const std::string& subject_type,  // e.g., "service", "user", "group"
    const std::string& entity_name
);

// ============================================================================
// running_predicate — Check if a process/service is currently running
//
// TRUE: Process/service is actively executing/operating
// FALSE: Process/service is stopped/inactive
// UNKNOWN: State cannot be determined (systemd unavailable, etc.)
// ============================================================================

PredicateResult running_predicate(
    const std::string& subject_type,  // e.g., "process", "service"
    const std::string& entity_id      // PID or service name
);

// ============================================================================
// enabled_predicate — Check if a service/unit is enabled for auto-activation
//
// TRUE: Service will start automatically (systemd enablement)
// FALSE: Service is disabled from automatic activation
// UNKNOWN: Enablement state unknown
// ============================================================================

PredicateResult enabled_predicate(const std::string& service_name);

// ============================================================================
// disabled_predicate — Check if a service/unit is disabled
//
// TRUE: Service is explicitly disabled
// FALSE: Service is not disabled (may be enabled or static)
// UNKNOWN: Cannot determine enablement state
// ============================================================================

PredicateResult disabled_predicate(const std::string& service_name);

// ============================================================================
// active_predicate — Check if a service is currently active
//
// TRUE: Service is in active/running state
// FALSE: Service is inactive/dead/failing
// UNKNOWN: Cannot determine service state
// ============================================================================

PredicateResult active_predicate(const std::string& service_name);

// ============================================================================
// inactive_predicate — Check if a service is currently inactive
//
// TRUE: Service is not running (stopped, dead, etc.)
// FALSE: Service is currently active
// UNKNOWN: Cannot determine service state
// ============================================================================

PredicateResult inactive_predicate(const std::string& service_name);

// ============================================================================
// healthy_predicate — Check if a service meets its health contract
//
// TRUE: Service passes all health checks
// FALSE: Service fails one or more health checks
// UNKNOWN: Health cannot be determined (no health check configured, error)
// ============================================================================

PredicateResult healthy_predicate(const std::string& service_name);

// ============================================================================
// ready_predicate — Check if a service is ready to accept work
//
// TRUE: Service is both ready AND healthy
// FALSE: Service is not ready (still initializing, degraded, etc.)
// UNKNOWN: Cannot determine readiness state
// ============================================================================

PredicateResult ready_predicate(const std::string& service_name);

// ============================================================================
// reachable_predicate — Check if a network endpoint is reachable
//
// TRUE: Target responds within timeout
// FALSE: Target unreachable or timed out
// UNKNOWN: Network stack unavailable, invalid target, etc.
// ============================================================================

PredicateResult reachable_predicate(
    const std::string& host,     // hostname or IP
    int port = -1                // port (if applicable, -1 for no port check)
);

// ============================================================================
// writable_predicate — Check if a path can accept writes
//
// TRUE: Path exists and is writable by current user
// FALSE: Path not writable (missing, read-only, permissions, etc.)
// UNKNOWN: Cannot determine write capability (stat failed, etc.)
// ============================================================================

PredicateResult writable_predicate(const std::string& path);

// ============================================================================
// readable_predicate — Check if a path can be read
//
// TRUE: Path exists and is readable by current user
// FALSE: Path not readable (missing, permissions, etc.)
// UNKNOWN: Cannot determine readability
// ============================================================================

PredicateResult readable_predicate(const std::string& path);

// ============================================================================
// executable_predicate — Check if an entity is executable
//
// For files: Has execute permission
// For processes: Can be started
//
// TRUE: Entity can be executed
// FALSE: Entity cannot be executed
// UNKNOWN: Cannot determine executability
// ============================================================================

PredicateResult executable_predicate(const std::string& path);

// ============================================================================
// mounted_predicate — Check if a filesystem mount point is active
//
// TRUE: Mount point has an active filesystem mounted
// FALSE: No filesystem mounted at this path
// UNKNOWN: Cannot determine mount status (procfs unreadable, etc.)
// ============================================================================

PredicateResult mounted_predicate(const std::string& mount_point);

// ============================================================================
// Utility functions for predicate evaluation
// ============================================================================

// Create a TRUE result with optional evidence
inline PredicateResult make_true(std::vector<core::Evidence> evidence = {}) {
    PredicateResult r;
    r.status = core::SemanticStatus::kSuccess;
    r.is_true = true;
    r.evidence = std::move(evidence);
    return r;
}

// Create a FALSE result with optional evidence  
inline PredicateResult make_false(std::vector<core::Evidence> evidence = {}) {
    PredicateResult r;
    r.status = core::SemanticStatus::kFailure;
    r.is_true = false;
    r.evidence = std::move(evidence);
    return r;
}

// Create an UNKNOWN result
inline PredicateResult make_unknown(std::string message) {
    PredicateResult r;
    r.status = core::SemanticStatus::kUnknown;
    r.is_true = std::nullopt;
    r.error = core::Error{"E_UNKNOWN", std::move(message)};
    return r;
}

// Convert shell exit code to predicate result status
inline core::SemanticStatus exit_code_to_status(int exit_code, bool is_predicate = true) {
    if (exit_code == 0) {
        return core::SemanticStatus::kSuccess;   // TRUE for predicates
    }
    if (exit_code == 1 && is_predicate) {
        return core::SemanticStatus::kFailure;   // FALSE for predicates
    }
    return core::SemanticStatus::kUnknown;       // UNKNOWN / error
}

}  // namespace rebuntu::shell