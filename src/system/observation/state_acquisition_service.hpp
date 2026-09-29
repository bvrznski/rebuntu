// rebuntu::system::observation::state_acquisition — State Acquisition Service (Phase 7.2)
//
// This module provides a unified interface for acquiring system state from multiple
// domain adapters:
//   - procfs: process, memory, CPU information
//   - systemd: service/unit state
//   - sysfs: device and hardware information
//   - netlink: network topology
//
// Design principles:
//   - Observation is read-only (no hidden mutation)
//   - Bounded acquisition with timeout/cancellation support
//   - Per-domain freshness tracking
//   - Evidence/provenance preserved for all observations

#pragma once

#include "types.hpp"
#include "bounds.hpp"
#include "snapshot_builder.hpp"

#include <chrono>
#include <memory>
#include <optional>
#include <set>
#include <string>
#include <vector>

namespace rebuntu::system::observation {

// ============================================================================
// StateAcquisitionConfig — Configuration for state acquisition
// ============================================================================

struct StateAcquisitionConfig {
    // Global timeout for complete acquisition operation
    std::chrono::milliseconds global_timeout_ms{std::chrono::seconds(30)};
    
    // Per-domain timeout (applied if domain has many items)
    std::optional<std::chrono::milliseconds> per_domain_timeout_ms;
    
    // Default freshness TTL for domains without specific override
    std::chrono::milliseconds default_freshness_ttl_ms{std::chrono::seconds(30)};
    
    // Per-domain freshness TTL overrides (e.g., process state needs frequent updates)
    std::map<ObservationDomain, std::chrono::milliseconds> domain_freshness_ttls;
    
    // Which domains to include in acquisition
    std::set<ObservationDomain> enabled_domains{
        ObservationDomain::kProcess,
        ObservationDomain::kService
    };
    
    // Maximum records per domain (for bounded observation)
    size_t max_records_per_domain{1000};
};

// ============================================================================
// StateAcquisitionResult — Result of a state acquisition operation
// ============================================================================

struct StateAcquisitionResult {
    core::SemanticStatus status{core::SemanticStatus::kUnknown};
    
    std::optional<std::string> error_code{};
    std::optional<std::string> error_message{};
    
    // Acquired snapshots per domain
    std::map<ObservationDomain, Snapshot> domain_snapshots{};
    
    // Facts derived from observations
    std::vector<Fact> facts{};
    
    // Timing information
    std::chrono::system_clock::time_point acquired_at{};
    std::chrono::milliseconds elapsed_ms{0};
    
    // Domain statistics
    struct DomainStats {
        size_t observation_count{0};
        size_t fact_count{0};
        bool succeeded{false};
        std::optional<std::string> error_description;
    };
    std::map<ObservationDomain, DomainStats> domain_stats{};
    
    // Overall quality assessment
    ObservationQuality overall_quality{ObservationQuality::kUnknown};
};

// ============================================================================
// StateAcquisitionService — Interface for state acquisition from multiple domains
// ============================================================================

class StateAcquisitionService {
public:
    virtual ~StateAcquisitionService() = default;
    
    // Get a snapshot of current system state for specified domains
    // This is the primary interface for Phase 7.2 consumers (shell, query, events)
    virtual core::Outcome get_current_state(
        const std::set<ObservationDomain>& domains,
        StateAcquisitionResult& out_result) = 0;
    
    // Get a snapshot with configuration
    virtual core::Outcome get_current_state_with_config(
        const StateAcquisitionConfig& config,
        StateAcquisitionResult& out_result) = 0;
    
    // Force refresh: discard cached state and re-acquire from all sources
    virtual core::Outcome force_refresh() = 0;
    
    // Get the time of the last successful acquisition
    virtual std::optional<std::chrono::system_clock::time_point> 
    last_acquisition_time() const = 0;
    
    // Get current configuration
    virtual StateAcquisitionConfig get_config() const = 0;
};

// ============================================================================
// Factory function for creating a state acquisition service
// ============================================================================

std::unique_ptr<StateAcquisitionService> make_state_acquisition_service(
    const StateAcquisitionConfig& config = {});

}  // namespace rebuntu::system::observation