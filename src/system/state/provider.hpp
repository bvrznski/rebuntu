// rebuntu::state::provider — Native state mapping providers
//
// This header establishes Rebuntu's interface for mapping native Linux state
// sources (systemd, procfs, sysfs) to Rebuntu's orthogonal state vocabulary:
//
//   LifecycleState: created, initializing, ready, active, stopping, stopped, failed
//   WorkState: idle, processing, waiting, paused
//   HealthState: unknown, healthy, degraded, unhealthy
//   RecoveryState: none, retrying, rolling_back, restoring, repairing, failing_over
//
// These providers translate platform-specific state representations into the
// canonical Rebuntu model. They do NOT own state; they observe and report.
//
// State provenance is preserved via ProviderId so consumers know:
//   - where state was observed (systemd, procfs, sysfs)
//   - when it was observed (timestamp)
//   - confidence in the observation (freshness)

#pragma once

#include <runtime/contracts.hpp>
#include <memory>
#include <string>
#include <string_view>
#include <optional>
#include <chrono>

namespace rebuntu::state {

// ---------------------------------------------------------------------------
// ProviderId
// A typed identifier for a state provider source.
// Distinct from runtime::ExecutionId which tracks execution instances.
// ---------------------------------------------------------------------------

struct ProviderId {
    ProviderId() = default;
    std::string value;  // e.g., "systemd", "procfs", "sysfs"
    
    explicit ProviderId(std::string v) : value(std::move(v)) {}
    explicit operator std::string() const { return value; }
};

inline bool operator==(const ProviderId& a, const ProviderId& b) {
    return a.value == b.value;
}
inline bool operator!=(const ProviderId& a, const ProviderId& b) {
    return !(a == b);
}

// ---------------------------------------------------------------------------
// StateObservation
// A single observation of an entity's state at a point in time.
//
// Combines all orthogonal dimensions: lifecycle + work + health + recovery.
// ---------------------------------------------------------------------------

struct StateObservation {
    StateObservation() = default;
    
    std::string entity_id;       // e.g., "org.freedesktop.systemd1", "/proc/1234"
    
    ProviderId provider;         // source of this observation
    
    std::chrono::system_clock::time_point observed_at;
    
    rebuntu::runtime::LifecycleState lifecycle;
    rebuntu::runtime::WorkState work;
    rebuntu::runtime::HealthState health;
    rebuntu::runtime::RecoveryState recovery;
    
    // Optional metadata
    std::optional<std::string> native_state_name;   // original state name from provider
    std::optional<int64_t> pid;                      // process id where applicable
    std::optional<std::string> description;          // human-readable context
};

// ---------------------------------------------------------------------------
// ProviderResult
// Result of a state observation operation.
// ---------------------------------------------------------------------------

struct ProviderResult {
    bool success = false;
    
    std::vector<StateObservation> observations;
    
    // Error information (if not successful)
    std::optional<std::string> error_code;
    std::optional<std::string> error_message;
};

// ---------------------------------------------------------------------------
// EntityStateObserver
// Interface for observing state of a specific entity from a provider.
//
// Implementations:
//   - SystemdProvider: observes systemd unit states via D-Bus
//   - ProcfsProvider: observes process states from /proc
//   - SysfsProvider: observes device/hardware states from sysfs
// ---------------------------------------------------------------------------

class EntityStateObserver {
public:
    virtual ~EntityStateObserver() = default;
    
    // Observe the current state of a single entity
    virtual StateObservation observe(const std::string& entity_id) = 0;
    
    // Get the canonical provider identifier
    virtual ProviderId provider_id() const = 0;
};

// ---------------------------------------------------------------------------
// SystemdStateProvider — systemd unit state mapping
//
// Maps systemd ActiveState/SubState/UnitFileState to Rebuntu state:
//   ActiveState: active, inactive, activating, deactivating, failed, not-found
//   SubState: various (e.g., running, dead, mounted)
// ---------------------------------------------------------------------------

class SystemdStateProvider : public EntityStateObserver {
public:
    // Construct with optional D-Bus connection string (empty = system bus)
    explicit SystemdStateProvider(std::optional<std::string> dbus_address = std::nullopt);
    
    ~SystemdStateProvider() override;
    
    StateObservation observe(const std::string& entity_id) override;
    ProviderId provider_id() const override { return ProviderId{"systemd"}; }
    
private:
    struct Impl;
    std::unique_ptr<Impl> impl_;
    
    rebuntu::runtime::LifecycleState map_active_state(std::string_view active, std::string_view sub);
    rebuntu::runtime::HealthState determine_health_from_systemd(std::string_view unit_file_state);
};

// ---------------------------------------------------------------------------
// ProcfsStateProvider — Linux process state mapping from /proc
//
// Maps /proc/[pid]/stat states:
//   R = running
//   S = sleeping (waiting for event)
//   D = disk sleep (uninterruptible)
//   T = stopped
//   Z = zombie
//   X = dead
//   t = tracing stop
//   W = paging
// ---------------------------------------------------------------------------

class ProcfsStateProvider : public EntityStateObserver {
public:
    ProcfsStateProvider() = default;
    ~ProcfsStateProvider() override = default;
    
    StateObservation observe(const std::string& entity_id) override;
    ProviderId provider_id() const override { return ProviderId{"procfs"}; }
    
private:
    rebuntu::runtime::LifecycleState map_proc_state(char state_char);
    rebuntu::runtime::WorkState determine_work_from_proc(char state_char, int64_t pid);
};

// ---------------------------------------------------------------------------
// SysfsStateProvider — sysfs device state mapping
//
// Maps sysfs states for devices:
//   power/state: on, suspend
//   uevent: ADD, REMOVE, CHANGE, MOVE
// ---------------------------------------------------------------------------

class SysfsStateProvider : public EntityStateObserver {
public:
    explicit SysfsStateProvider(std::optional<std::string> sysfs_path = std::nullopt);
    
    ~SysfsStateProvider() override;
    
    StateObservation observe(const std::string& entity_id) override;
    ProviderId provider_id() const override { return ProviderId{"sysfs"}; }
    
private:
    struct Impl;
    std::unique_ptr<Impl> impl_;
};

// ---------------------------------------------------------------------------
// CompositeObserver — combines multiple providers for a complete state view
//
// Uses weighted voting or priority-based resolution where providers disagree.
// ---------------------------------------------------------------------------

class CompositeObserver {
public:
    void add_provider(std::unique_ptr<EntityStateObserver> provider);
    
    // Get combined observation from all providers
    StateObservation observe(const std::string& entity_id);
    
    ProviderId provider_id() const { return ProviderId{"composite"}; }
    
private:
    std::vector<std::unique_ptr<EntityStateObserver>> providers_;
};

// ---------------------------------------------------------------------------
// State freshness tracking
// ---------------------------------------------------------------------------

inline bool is_fresh(std::chrono::system_clock::time_point observed_at,
                     std::chrono::milliseconds max_age) {
    auto now = std::chrono::system_clock::now();
    return (now - observed_at) <= max_age;
}

// ---------------------------------------------------------------------------
// Conversion utilities
// ---------------------------------------------------------------------------

std::string to_string(const StateObservation& obs);
std::string to_string(const ProviderResult& result);

}  // namespace rebuntu::state

namespace std {
template <> struct hash<rebuntu::state::ProviderId> {
    size_t operator()(const rebuntu::state::ProviderId& id) const noexcept {
        return std::hash<std::string>{}(id.value);
    }
};
}