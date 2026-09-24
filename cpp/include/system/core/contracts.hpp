// Rebuntu Core Contracts (Phase 0.0)
// ====================================

#pragma once

#include <string>
#include <string_view>
#include <chrono>
#include <memory>
#include <map>
#include <set>
#include <vector>
#include <optional>

namespace rebuntu::core {

// -----------------------------------------------------------------------------
// ComponentKind (Phase 0.7)
// -----------------------------------------------------------------------------
// The kind of structural component in the Rebuntu registry.
//
// Phase 0.7 establishes Units as first-class structural types alongside
// Systems and Modules for executable operational definitions.
// -----------------------------------------------------------------------------

enum class ComponentKind {
    kSystem,       // a major coherent part of Rebuntu with broad responsibility
    kModule,       // a substantial reusable functional component
    kUnit,         // a bounded independently identifiable unit of executable work

    // Side effect classification for Operations and Workflows
    kReadOnly,     // no state changes
    kMutating,     // may change state
    kPrivileged,   // requires elevated privilege
    kDestructive,  // destructive or irreversible operations
};

inline std::string to_string(ComponentKind k) {
    switch (k) {
        case ComponentKind::kSystem: return "system";
        case ComponentKind::kModule: return "module";
        case ComponentKind::kUnit:   return "unit";
    }
    return "unknown";
}

// -----------------------------------------------------------------------------
// Outcome
// -----------------------------------------------------------------------------
// The semantic result of an execution attempt.
// Distinct from success/failure status (exit code), outcome is about
// whether the desired state was achieved.
// -----------------------------------------------------------------------------

enum class Outcome {
    kSuccess,          // Desired state achieved
    kFailure,          // Execution failed or desired state not achieved
    kCancelled,        // Execution was cancelled
    kTimedOut,         // Execution exceeded timeout
};

inline std::string to_string(Outcome o) {
    switch (o) {
        case Outcome::kSuccess:   return "success";
        case Outcome::kFailure:   return "failure";
        case Outcome::kCancelled: return "cancelled";
        case Outcome::kTimedOut:  return "timed_out";
    }
    return "unknown";
}

// -----------------------------------------------------------------------------
// VerificationStatus
// -----------------------------------------------------------------------------
// Whether post-execution verification was performed and passed.
// -----------------------------------------------------------------------------

enum class VerificationStatus {
    kUnknown,     // Verification not yet attempted
    kNotRequired, // This operation does not require verification
    kVerifying,   // Verification is in progress
    kVerified,    // Verification completed successfully
    kUnverified,  // Verification failed or could not be performed
};

inline std::string to_string(VerificationStatus v) {
    switch (v) {
        case VerificationStatus::kUnknown:     return "unknown";
        case VerificationStatus::kNotRequired: return "not_required";
        case VerificationStatus::kVerifying:   return "verifying";
        case VerificationStatus::kVerified:    return "verified";
        case VerificationStatus::kUnverified:  return "unverified";
    }
    return "unknown";
}

// -----------------------------------------------------------------------------
// Evidence
// -----------------------------------------------------------------------------
// A provenance-bearing observation supporting an assertion.
// Evidence includes:
// - What was observed
// - Where it came from (source)
// - When it was observed
// - Who/what asserted its truth (authority)
// -----------------------------------------------------------------------------

struct Evidence {
    std::string subject;       // What the evidence is about (e.g., "service.active")
    std::string source;        // Where it came from (e.g., "systemd", "/proc/meminfo")
    std::optional<std::string> authority;  // Assertion of truth (optional)
    std::string value;         // The observed value
    std::chrono::system_clock::time_point observed_at;
};

// -----------------------------------------------------------------------------
// Result
// -----------------------------------------------------------------------------
// The complete result of an execution including semantic outcome and verification.
// -----------------------------------------------------------------------------

struct Result {
    Outcome outcome;
    VerificationStatus verification_status = VerificationStatus::kUnknown;
    std::vector<Evidence> evidence;
    
    // Timing information
    std::chrono::system_clock::time_point completed_at;
    
    bool is_success() const { return outcome == Outcome::kSuccess; }
    bool is_verified() const { return verification_status == VerificationStatus::kVerified; }
};

} // namespace rebuntu::core

namespace rebuntu::work {

struct ExecutionId {
    std::string value;
    ExecutionId() = default;
    explicit ExecutionId(std::string v) : value(std::move(v)) {}
};

enum class WorkPriority : uint8_t {
    kBackground = 0,
    kNormal = 1,
    kHigh = 2,
    kCritical = 3
};

} // namespace rebuntu::work

namespace rebuntu::core {

struct TimeoutPolicy {
    std::chrono::milliseconds default_timeout = std::chrono::minutes(5);
    std::chrono::milliseconds verification_timeout = std::chrono::seconds(30);
    bool cancel_on_timeout = true;
};

struct RetryPolicy {
    uint32_t max_attempts = 1;
    std::chrono::milliseconds initial_backoff = std::chrono::milliseconds(100);
    std::chrono::milliseconds max_backoff = std::chrono::seconds(5);
    bool use_exponential_backoff = true;
};

} // namespace rebuntu::core

namespace rebuntu::runtime {

class EvidenceRegistry;

struct CancellationToken {
    bool is_cancelled() const { return cancelled; }
    void request_cancel(std::string = "") { cancelled = true; }
private:
    bool cancelled = false;
};

struct RuntimeContext {
    work::ExecutionId execution_id;
    std::string caller_id;
    std::chrono::system_clock::time_point created_at;
    core::TimeoutPolicy timeout_policy;
    core::RetryPolicy retry_policy;
    std::shared_ptr<CancellationToken> cancellation_token;
    std::optional<std::string> working_directory;
    std::map<std::string, std::string> environment;
    std::shared_ptr<EvidenceRegistry> evidence_registry;
    work::WorkPriority priority = work::WorkPriority::kNormal;
    bool allow_concurrent_execution = true;
};

} // namespace rebuntu::runtime

namespace rebuntu::services {

// -----------------------------------------------------------------------------
// ServiceState (Phase 0.6)
// -----------------------------------------------------------------------------
// The availability and lifecycle state of a Service.
// -----------------------------------------------------------------------------

enum class ServiceState {
    kUnavailable,   // not available
    kActivating,    // in the process of becoming available
    kAvailable,     // available for use
    kDegraded,      // available but with reduced capability/quality
    kDeactivating,  // in the process of becoming unavailable
    kFailed         // activation failed or service became unavailable due to error
};

inline std::string to_string(ServiceState s) {
    switch (s) {
        case ServiceState::kUnavailable:   return "unavailable";
        case ServiceState::kActivating:    return "activating";
        case ServiceState::kAvailable:     return "available";
        case ServiceState::kDegraded:      return "degraded";
        case ServiceState::kDeactivating:  return "deactivating";
        case ServiceState::kFailed:        return "failed";
    }
    return "unknown";
}

inline bool is_available(ServiceState s) {
    return s == ServiceState::kAvailable || s == ServiceState::kDegraded;
}

inline bool is_unavailable(ServiceState s) {
    return s == ServiceState::kUnavailable || s == ServiceState::kFailed;
}

// -----------------------------------------------------------------------------
// ServiceActivation (Phase 0.6)
// -----------------------------------------------------------------------------
// How a Service is activated.
// -----------------------------------------------------------------------------

enum class ServiceActivation {
    kNone,           // no activation mechanism
    kPersistent,     // persistent process (systemd service with Type=simple)
    kManual,         // manual activation only
    kBoot,           // activated at boot time
    kOnDemand,       // on-demand activation when first needed
    kSocket,         // socket-activated by systemd
    kDBus,           // D-Bus-activated
    kPath,           // path-activated (file system event)
    kDevice,         // device-activated (udev event)
    kTimer,          // timer-triggered (systemd timer)
    kEvent           // event-triggered (kernel/eventfd)
};

inline std::string to_string(ServiceActivation a) {
    switch (a) {
        case ServiceActivation::kNone:       return "none";
        case ServiceActivation::kPersistent: return "persistent";
        case ServiceActivation::kManual:     return "manual";
        case ServiceActivation::kBoot:       return "boot";
        case ServiceActivation::kOnDemand:   return "on-demand";
        case ServiceActivation::kSocket:     return "socket-activated";
        case ServiceActivation::kDBus:       return "dbus-activated";
        case ServiceActivation::kPath:       return "path-activated";
        case ServiceActivation::kDevice:     return "device-activated";
        case ServiceActivation::kTimer:      return "timer-triggered";
        case ServiceActivation::kEvent:      return "event-triggered";
    }
    return "unknown";
}

// -----------------------------------------------------------------------------
// DependencyKind (Phase 0.6)
// -----------------------------------------------------------------------------
// A dependency of one Service on another.
// -----------------------------------------------------------------------------

enum class DependencyKind {
    kRequired,   // service cannot function without dependency
    kOptional,   // service functions but with reduced capability without dependency
    kOrdering,   // service should start after dependency (not required for functionality)
    kSoft        // best-effort relationship, failure doesn't cause failure
};

inline std::string to_string(DependencyKind k) {
    switch (k) {
        case DependencyKind::kRequired:  return "required";
        case DependencyKind::kOptional:  return "optional";
        case DependencyKind::kOrdering:  return "ordering";
        case DependencyKind::kSoft:      return "soft";
    }
    return "unknown";
}

// -----------------------------------------------------------------------------
// ServiceDependency (Phase 0.6)
// -----------------------------------------------------------------------------

struct ServiceDependency {
    std::string service_id;
    DependencyKind kind = DependencyKind::kRequired;
};

// -----------------------------------------------------------------------------
// ServiceInfo (Phase 0.6)
// -----------------------------------------------------------------------------
// A machine-readable description of a Service.
// -----------------------------------------------------------------------------

struct ServiceInfo {
    std::string id;
    std::string title;                    // human-readable name
    std::string description;              // human-readable description
    std::set<std::string> categories;     // category tags for grouping/discovery
    ServiceActivation activation;         // how this service is activated
    bool enabled = true;                  // desired state: should be available?
    std::optional<std::string> default_interface;  // default IPC/interface endpoint
    std::vector<ServiceDependency> dependencies;
    bool requires_root = false;           // whether root privilege is required
};

// -----------------------------------------------------------------------------
// ServiceRegistry (Phase 0.6)
// -----------------------------------------------------------------------------
// A data structure for managing known Services.
//
// This is a DATA structure and a structural-integrity checker — NOT a runtime
// bus, event system, or service locator.
// -----------------------------------------------------------------------------

class ServiceRegistry {
public:
    void register_service(ServiceInfo info) { services_[info.id] = std::move(info); }

    bool contains(std::string_view id) const {
        return services_.find(std::string{id}) != services_.end();
    }

    std::optional<ServiceInfo> find(std::string_view id) const {
        auto it = services_.find(std::string{id});
        if (it == services_.end()) return std::nullopt;
        return it->second;
    }

    std::size_t size() const { return services_.size(); }
    bool empty() const { return services_.empty(); }

    std::vector<ServiceInfo> all() const {
        std::vector<ServiceInfo> result;
        result.reserve(services_.size());
        for (const auto& [id, info] : services_) {
            result.push_back(info);
        }
        std::sort(result.begin(), result.end(),
                  [](const ServiceInfo& a, const ServiceInfo& b) { return a.id < b.id; });
        return result;
    }

    std::vector<ServiceInfo> enabled() const {
        std::vector<ServiceInfo> result;
        for (const auto& [id, info] : services_) {
            if (info.enabled) {
                result.push_back(info);
            }
        }
        std::sort(result.begin(), result.end(),
                  [](const ServiceInfo& a, const ServiceInfo& b) { return a.id < b.id; });
        return result;
    }

    std::vector<ServiceInfo> by_category(std::string_view category) const {
        std::vector<ServiceInfo> result;
        for (const auto& [id, info] : services_) {
            if (info.categories.contains(std::string{category})) {
                result.push_back(info);
            }
        }
        std::sort(result.begin(), result.end(),
                  [](const ServiceInfo& a, const ServiceInfo& b) { return a.id < b.id; });
        return result;
    }

    // Validate structural integrity
    std::pair<bool, std::vector<std::string>> validate() const {
        std::vector<std::string> issues;
        std::set<std::string> seen;

        for (const auto& [id, info] : services_) {
            if (!seen.insert(id).second) {
                issues.push_back("duplicate service id: " + id);
                continue;
            }
            for (const auto& dep : info.dependencies) {
                if (!contains(dep.service_id)) {
                    issues.push_back("service " + id + " depends on unknown service: " + dep.service_id);
                }
            }
        }

        return {issues.empty(), issues};
    }

private:
    std::map<std::string, ServiceInfo> services_;
};

} // namespace rebuntu::services