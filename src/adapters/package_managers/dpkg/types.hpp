// rebuntu::adapters::package_managers::dpkg — DPKG Package Inventory Adapter (Phase 5.31)
//
// This module implements Rebuntu's dpkg-based read-only package inventory provider:
//   - Observes installed packages from dpkg database (/var/lib/dpkg/*)
//   - Provides typed, bounded observation of package state without inference
//   - Distinguishes PackageIdentity (stable identifier) from PackageObservation
//
// Native Interfaces Used:
//   - /var/lib/dpkg/status — installed packages status file
//   - dpkg -l [pattern] — list installed packages
//   - dpkg-query -W --showformat='...' — query package metadata
//
// Key Distinctions:
//   - PackageIdentity = name + architecture (stable identifier)
//   - PackageState = installation state (installed, half-installed, etc.)
//   - Version format: epoch:version-release (e.g., "1:2.4.14-1ubuntu1.6")
//
// Observation Invariants:
//   - No inference: only observed values from dpkg
//   - Bounded acquisition: timeouts, limits on output size
//   - Freshness-aware: tracks when observation was performed
//   - Provenance-preserving: source identification for every observation

#pragma once

#include <system/core/contracts.hpp>
#include <cstdint>
#include <memory>
#include <optional>
#include <string>
#include <chrono>
#include <vector>

namespace rebuntu::adapters::package_managers::dpkg {

// ============================================================================
// PackageIdentity — Stable identity for a dpkg package
//
// A package is uniquely identified by:
//   - name: The package name (e.g., "apt", "gcc")
//   - architecture: The target architecture (e.g., "amd64", "all")
//
// Note: PackageIdentity != PID. PIDs are transient; package names are durable identifiers.
// ============================================================================
struct PackageIdentity {
    std::string name;              // e.g., "apt"
    std::string architecture;      // e.g., "amd64" or "all"
    
    bool is_valid() const {
        return !name.empty();
    }
};

inline bool operator==(const PackageIdentity& a, const PackageIdentity& b) {
    return a.name == b.name && a.architecture == b.architecture;
}

// ============================================================================
// PackageInstallState — Installation state from dpkg
//
// From dpkg: Status field (first character = desired state, second = actual state)
//   i = install, r = remove/purge, h = hold, w = wait, c = config-files
//   
// Combined states:
//   ii = installed
//   ri = awaiting removal, then install
//   hi = awaiting hold, then install
//   ci = awaiting configuration
//   pi = awaiting purge, then install
// ============================================================================
enum class PackageInstallState {
    kUnknown,         // State unknown (acquisition failed)
    kInstalled,       // Package is fully installed
    kHalfInstalled,   // Package installation started but not completed
    kUnpacked,        // Package unpacked but not configured
    kFilesOnly,       // Package files only (no config)
    kConfigFiles,     // Config files present but package removed
    kNotInstalled,    // Package never installed or purged
};

inline std::string to_string(PackageInstallState s) {
    switch (s) {
        case PackageInstallState::kUnknown:      return "unknown";
        case PackageInstallState::kInstalled:    return "installed";
        case PackageInstallState::kHalfInstalled:return "half-installed";
        case PackageInstallState::kUnpacked:     return "unpacked";
        case PackageInstallState::kFilesOnly:    return "files-only";
        case PackageInstallState::kConfigFiles:  return "config-files";
        case PackageInstallState::kNotInstalled: return "not-installed";
    }
    return "unknown";
}

// ============================================================================
// PackageStatus — Full dpkg status (desired + actual state)
//
// dpkg uses two characters:
//   First char = desired state (i=install, r=remove, h=hold, p=purge, u=unpack)
//   Second char = actual state (i=inst-obs, h=half-inst, u=unpacked, f=config-files, w=awaiting-def-pkg)
// ============================================================================
struct PackageStatus {
    char desired_state{'?'};         // i, r, h, p, u
    char actual_state{'?'};          // i, h, u, f, w
    
    bool is_installed() const {
        return desired_state == 'i' && actual_state == 'i';
    }
    
    bool is_remove_awaiting() const {
        return desired_state == 'r' && actual_state == 'i';
    }
    
    bool is_config_pending() const {
        return desired_state == 'i' && actual_state == 'f';
    }
};

// ============================================================================
// PackageObservation — Complete observation for a single dpkg package
//
// Combines all available information from dpkg status database with provenance.
// This is the primary output of the inventory provider.
// ============================================================================
struct PackageObservation {
    PackageIdentity identity;        // name + architecture
    
    // Version info
    std::string version;             // Full version string (e.g., "2.4.14-1ubuntu1.6")
    std::optional<std::string> epoch;
    std::optional<std::string> version_num;
    std::optional<std::string> revision;
    
    // Package metadata
    std::string description;         // Short description
    std::string long_description;    // Full description (may be empty)
    std::vector<std::string> section;// Section(s) this package belongs to
    
    // Installation state
    PackageStatus status;            // Full dpkg status
    PackageInstallState install_state{PackageInstallState::kUnknown};
    
    // Dependencies
    std::vector<std::string> depends;          // Direct dependencies
    std::vector<std::string> recommends;       // Recommended packages
    std::vector<std::string> suggests;         // Suggested packages
    std::vector<std::string> conflicts;        // Conflicting packages
    std::vector<std::string> breaks;           // Packages this breaks
    std::vector<std::string> replaces;         // Packages this replaces
    
    // Package files info (bounded - may be unavailable)
    std::optional<uint64_t> installed_size_kb;   // Installed size in KB
    
    // Provenance tracking
    std::chrono::system_clock::time_point observed_at{};
    std::string source{"dpkg"};        // "dpkg" for native observation
};

// ============================================================================
// PackageInventoryResult — Result of package inventory operation
//
// Contains all observations, statistics, and timing information.
// ============================================================================
struct PackageInventoryResult {
    core::SemanticStatus status{core::SemanticStatus::kUnknown};
    std::string description{};
    
    // All observed packages
    std::vector<PackageObservation> packages;
    
    // Statistics by section
    size_t total_packages{0};
    size_t installed_packages{0};
    
    // Timing
    std::chrono::system_clock::time_point observed_at{};
    std::chrono::milliseconds elapsed_ms{0};
    
    // Provider provenance
    std::string provider_source{"dpkg"};
    
    // Errors encountered during discovery (non-fatal)
    std::vector<std::pair<std::string, core::Error>> errors;  // package_name -> error mapping
    
    std::optional<core::Error> fatal_error;
};

// ============================================================================
// PackageInventoryAdapter — Interface for dpkg package inventory
//
// Provides bounded, cancellable, freshness-aware package observation:
//   - observe_all_packages: Discover all installed packages from dpkg
//   - observe_package: Observe a specific package by identity
//   - get_freshness: Check when last observation was performed
// ============================================================================
class PackageInventoryAdapter {
public:
    virtual ~PackageInventoryAdapter() = default;
    
    // Observe all installed packages currently visible from dpkg
    // Returns observations sorted by package name for deterministic iteration
    virtual PackageInventoryResult observe_all_packages() = 0;
    
    // Observe a specific package by its identity (name + architecture)
    // Returns std::nullopt if the package is not found or inaccessible
    virtual std::optional<PackageObservation> observe_package(
        const PackageIdentity& identity) = 0;
    
    // Get freshness information about the last observation
    // Returns the timestamp of the last complete observation, if any
    virtual std::chrono::system_clock::time_point get_last_observation_time() const = 0;
    
    // Force refresh: discard cached state and re-observe from dpkg
    // This is idempotent and safe to call multiple times
    virtual PackageInventoryResult force_refresh() = 0;
};

// ============================================================================
// Factory function
// ============================================================================
std::unique_ptr<PackageInventoryAdapter> make_dpkg_package_inventory_adapter();

}  // namespace rebuntu::adapters::package_managers::dpkg