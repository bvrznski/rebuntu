// rebuntu::core — foundational contracts (Phase 0.0-0.9)
//
// These are Rebuntu's deterministic semantic primitives. They encode the
// project's core invariants as types rather than conventions:
//
//   * EXECUTION SUCCESS != VERIFIED SEMANTIC SUCCESS
//       An exit status of zero proves only what the exit status proves. A
//       Result distinguishes "completed" from "completed AND verified".
//
//   * UNKNOWN != FALSE / != FAILED / != PASS
//       Acquisition failure is not a negative observation.
//
//   * DATA != CONTROL
//       Evidence is provenance-bearing data. It never confers authority.
//
//   * SECRET MATERIAL NEVER APPEARS IN EVIDENCE / ERRORS / RESULT
//       See docs/SAFETY.md.
//
// Phase 0.6 adds Service model definitions for managed functionality:
//   * SERVICE = MANAGED FUNCTIONALITY WITH AVAILABILITY, LIFECYCLE, INTERFACE
//   * Service != Daemon (process/runtime characteristic)
//   * Service != systemd .service unit (deployment mechanism)
//
// Phase 0.7 establishes Units as structural execution definitions.
//
// Phase 0.8 defines Work ontology: Task (specification), Job (execution),
// Attempt (try), Result (outcome with verification status).
//
// Phase 0.9 introduces temporal grammar: Schedule, TimeoutPolicy, RetryPolicy.
//
// Phase 0.10 introduces Operation — the canonical abstraction for system
// capabilities. An Operation is a reusable, explicitly contracted capability
// that can observe, query, change, construct, remove, transform, or control
// system state or resources with full contract semantics (preconditions,
// postconditions, effects, verification strategy, evidence).
//
// These are contracts, not a runtime. There is no I/O, no threads, no
// global state. They are the shared vocabulary that operations, workflows,
// verification and the semantic boundary will speak in later phases.

#pragma once

#include <algorithm>
#include <chrono>
#include <cstddef>
#include <map>
#include <optional>
#include <set>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

namespace rebuntu::core {

// ---------------------------------------------------------------------------
// ExitReason — How a process/execution terminated (Phase 6.20)
//
// Distinct from SemanticStatus which represents the semantic outcome.
// ExitReason captures the actual mechanism of termination:
//
//   - NormalExit: Process completed with explicit exit() or return from main()
//   - NonzeroExit: Process exited with nonzero status (typically error)
//   - SignalTermination: Process killed by a POSIX signal
//   - Timeout: Execution exceeded its configured timeout
//   - Cancellation: Explicit cancellation request was processed
//   - SpawnFailure: Failed to spawn/start the process
//   - ProtocolFailure: Execution failed due to protocol errors (IPC, serialization)
//
// This is foundational data for execution verification and recovery.
// ---------------------------------------------------------------------------
enum class ExitReason {
    kNormalExit,           // Process exited normally with explicit exit code
    kNonzeroExit,          // Process exited with nonzero status code
    kSignalTermination,    // Terminated by POSIX signal (SIGKILL, SIGTERM, etc.)
    kTimeout,              // Execution exceeded its timeout limit
    kCancellation,         // Explicitly cancelled before completion
    kSpawnFailure,         // Failed to spawn/start the process
    kProtocolFailure,      // Protocol/IPC failure during execution
    kUnknown,              // Termination reason unknown
};

inline std::string_view to_string(ExitReason r) {
    switch (r) {
        case ExitReason::kNormalExit:       return "normal_exit";
        case ExitReason::kNonzeroExit:      return "nonzero_exit";
        case ExitReason::kSignalTermination:return "signal_termination";
        case ExitReason::kTimeout:          return "timeout";
        case ExitReason::kCancellation:     return "cancellation";
        case ExitReason::kSpawnFailure:     return "spawn_failure";
        case ExitReason::kProtocolFailure:  return "protocol_failure";
        case ExitReason::kUnknown:          return "unknown_exit";
    }
    return "unknown";
}

// ---------------------------------------------------------------------------
// ProcessExitCode — Raw process exit code (0-255, platform-specific encoding)
//
// On POSIX systems:
//   - Low 8 bits: exit status (if WIFEXITED)
//   - High bit: signal number if killed by signal (if WIFSIGNALED)
//
// On Windows:
//   - Standardized exit codes (0 = success, nonzero = failure)
// ---------------------------------------------------------------------------
using ProcessExitCode = int;

// ============================================================================
// ExitResult — Structured result of a process/execution termination
//
// Combines exit mechanism, exit code, and signal information into a single
// typed result. This is the authoritative source for execution outcome.
// ============================================================================
struct ExitResult {
    // How the process terminated (primary classification)
    ExitReason reason{ExitReason::kUnknown};
    
    // Raw exit code (0-255 on POSIX, platform-defined on Windows)
    ProcessExitCode exit_code{-1};
    
    // If terminated by signal: which signal
    std::optional<int> signal_number;
    
    // Human-readable description of the termination
    std::string description;
    
    // Timing information
    std::chrono::milliseconds execution_duration_ms{0};
    
    // Output capture (bounded, may be partial)
    std::string stdout_data;
    std::string stderr_data;
    
    // Helper predicates
    
    bool is_success() const {
        return reason == ExitReason::kNormalExit && exit_code == 0;
    }
    
    bool is_failure() const {
        return reason != ExitReason::kNormalExit || exit_code != 0;
    }
    
    bool was_signaled() const {
        return reason == ExitReason::kSignalTermination;
    }
    
    bool timed_out() const {
        return reason == ExitReason::kTimeout;
    }
    
    bool cancelled() const {
        return reason == ExitReason::kCancellation;
    }
    
    bool spawn_failed() const {
        return reason == ExitReason::kSpawnFailure;
    }
    
    static ExitResult success(ProcessExitCode code = 0, std::chrono::milliseconds duration = {}) {
        ExitResult r;
        r.reason = ExitReason::kNormalExit;
        r.exit_code = code;
        r.description = "process completed successfully";
        r.execution_duration_ms = duration;
        return r;
    }
    
    static ExitResult nonzero_exit(ProcessExitCode code, std::chrono::milliseconds duration = {}) {
        ExitResult r;
        r.reason = ExitReason::kNonzeroExit;
        r.exit_code = code;
        r.description = "process exited with nonzero status";
        r.execution_duration_ms = duration;
        return r;
    }
    
    static ExitResult signal_termination(int sig, std::chrono::milliseconds duration = {}) {
        ExitResult r;
        r.reason = ExitReason::kSignalTermination;
        r.exit_code = -1;  // No exit code when killed by signal
        r.signal_number = sig;
        r.description = "process terminated by signal " + std::to_string(sig);
        r.execution_duration_ms = duration;
        return r;
    }
    
    static ExitResult timeout(std::chrono::milliseconds elapsed, const std::string& msg = {}) {
        ExitResult r;
        r.reason = ExitReason::kTimeout;
        r.exit_code = -1;
        r.description = msg.empty() ? "execution timed out" : msg;
        r.execution_duration_ms = elapsed;
        return r;
    }
    
    static ExitResult cancellation(const std::string& reason = {}) {
        ExitResult r;
        r.reason = ExitReason::kCancellation;
        r.exit_code = -1;
        r.description = reason.empty() ? "execution was cancelled" : reason;
        return r;
    }
    
    static ExitResult spawn_failure(const std::string& error_msg) {
        ExitResult r;
        r.reason = ExitReason::kSpawnFailure;
        r.exit_code = -1;
        r.description = "failed to spawn process: " + error_msg;
        return r;
    }
    
    static ExitResult protocol_failure(const std::string& msg) {
        ExitResult r;
        r.reason = ExitReason::kProtocolFailure;
        r.exit_code = -1;
        r.description = "protocol failure: " + msg;
        return r;
    }
    
    static ExitResult unknown(const std::string& msg = {}) {
        ExitResult r;
        r.reason = ExitReason::kUnknown;
        r.exit_code = -1;
        r.description = msg.empty() ? "termination outcome unknown" : msg;
        return r;
    }
};

// ---------------------------------------------------------------------------
// SemanticStatus
// The outcome of an attempt, distinct from any process exit code.
// ---------------------------------------------------------------------------
enum class SemanticStatus {
    kSuccess,    // completed AND independently verified against its postconditions
    kCompleted,  // completed the work, but verification was not performed / not applicable
    kFailure,    // the attempt ran but the objective was not met
    kUnknown,    // the outcome could not be determined (not a negative observation)
    kCancelled,  // explicitly cancelled before completion
};

inline std::string_view to_string(SemanticStatus s) {
    switch (s) {
        case SemanticStatus::kSuccess:   return "success";
        case SemanticStatus::kCompleted: return "completed";
        case SemanticStatus::kFailure:   return "failure";
        case SemanticStatus::kUnknown:   return "unknown";
        case SemanticStatus::kCancelled: return "cancelled";
    }
    return "unknown";
}

// ---------------------------------------------------------------------------
// OperationStatus
// The lifecycle stages of a consequential operation:
//   discover -> precheck -> plan -> execute -> verify -> report
// with checkpoint/rollback/recovery available where appropriate.
// ---------------------------------------------------------------------------
enum class OperationStatus {
    kDiscovered,
    kPrechecked,
    kPlanned,
    kExecuted,
    kVerified,
    kReported,
};

inline std::string_view to_string(OperationStatus s) {
    switch (s) {
        case OperationStatus::kDiscovered: return "discovered";
        case OperationStatus::kPrechecked: return "prechecked";
        case OperationStatus::kPlanned:    return "planned";
        case OperationStatus::kExecuted:   return "executed";
        case OperationStatus::kVerified:   return "verified";
        case OperationStatus::kReported:   return "reported";
    }
    return "discovered";
}

// ---------------------------------------------------------------------------
// Error
// A typed, machine-readable error. Not a boolean, not a raw exit code, and
// never a carrier of secret material.
// ---------------------------------------------------------------------------
struct Error {
    std::string code;     // stable machine-readable code, e.g. "E_UNSUPPORTED"
    std::string message;  // human-readable; must not contain secrets
};

// ---------------------------------------------------------------------------
// Evidence
// A provenance-bearing observation. DATA, not CONTROL.
// Bounded; must not contain secret material.
// ---------------------------------------------------------------------------
struct Evidence {
    std::string source;      // where this evidence came from (e.g. "procfs", "systemd")
    std::string value;       // the observed value / excerpt (bounded)
    std::string captured_at; // ISO-8601, UTC
};

// ---------------------------------------------------------------------------
// Outcome
// The result of an operation that does not return a value.
// Always carries a SemanticStatus and (optionally) evidence and an error.
// ---------------------------------------------------------------------------
struct Outcome {
    SemanticStatus status = SemanticStatus::kUnknown;
    std::vector<Evidence> evidence;
    std::optional<Error> error;
    bool verified = false;  // true ONLY when a postcondition was independently verified

    static Outcome success(bool verified = true) {
        Outcome o;
        o.status = SemanticStatus::kSuccess;
        o.verified = verified;
        return o;
    }
    static Outcome completed() {
        Outcome o;
        o.status = SemanticStatus::kCompleted;
        o.verified = false;
        return o;
    }
    static Outcome failure(std::string code, std::string message) {
        Outcome o;
        o.status = SemanticStatus::kFailure;
        o.error = Error{std::move(code), std::move(message)};
        return o;
    }
    static Outcome unknown(std::string message) {
        Outcome o;
        o.status = SemanticStatus::kUnknown;
        o.error = Error{"E_UNKNOWN", std::move(message)};
        return o;
    }
    static Outcome cancelled(std::string message) {
        Outcome o;
        o.status = SemanticStatus::kCancelled;
        o.error = Error{"E_CANCELLED", std::move(message)};
        return o;
    }

    bool is_success() const { return status == SemanticStatus::kSuccess && verified; }
    bool is_completed() const { return status == SemanticStatus::kCompleted || status == SemanticStatus::kSuccess; }
    bool is_error() const { return error.has_value(); }
};

// ---------------------------------------------------------------------------
// Result<T>
// An Outcome that additionally returns a value.
// ---------------------------------------------------------------------------
template <typename T>
struct Result : Outcome {
    std::optional<T> value;

    static Result<T> success(T v, bool verified = true) {
        Result<T> r;
        r.status = SemanticStatus::kSuccess;
        r.verified = verified;
        r.value = std::move(v);
        return r;
    }
    static Result<T> ok(T v) {
        Result<T> r;
        r.status = SemanticStatus::kCompleted;
        r.verified = false;
        r.value = std::move(v);
        return r;
    }

    bool has_value() const { return value.has_value(); }
};

// ---------------------------------------------------------------------------
// Component
// The unit of structural registration.
// ---------------------------------------------------------------------------
enum class ComponentKind {
    kSystem,  // a major coherent part of Rebuntu with broad responsibility
    kModule,  // a substantial reusable functional component
    kUnit,    // a smaller independently identifiable unit of work/behavior/specification
};

inline std::string_view to_string(ComponentKind k) {
    switch (k) {
        case ComponentKind::kSystem: return "system";
        case ComponentKind::kModule: return "module";
        case ComponentKind::kUnit:   return "unit";
    }
    return "unknown";
}

struct Component {
    std::string id;                  // stable identifier, e.g. "system.core"
    ComponentKind kind = ComponentKind::kModule;
    std::string title;               // human-readable name
    std::string purpose;             // one-line responsibility
    std::string native_mechanism;    // the Linux mechanism beneath, if any (may be empty)
    std::vector<std::string> depends_on;  // stable ids of components this depends on
};

// ---------------------------------------------------------------------------
// ComponentRegistry
// The initial structural/semantic registry. It is a DATA structure and a
// structural-integrity checker — NOT a runtime bus, event system, or service
// locator.
// ---------------------------------------------------------------------------
class ComponentRegistry {
public:
    void register_component(Component c) { components_.push_back(std::move(c)); }

    bool contains(std::string_view id) const {
        for (const auto& c : components_) {
            if (c.id == id) return true;
        }
        return false;
    }

    std::optional<Component> find(std::string_view id) const {
        for (const auto& c : components_) {
            if (c.id == id) return c;
        }
        return std::nullopt;
    }

    std::size_t size() const { return components_.size(); }
    bool empty() const { return components_.empty(); }

    // Deterministic: sorted by id.
    std::vector<Component> all() const {
        std::vector<Component> out = components_;
        std::sort(out.begin(), out.end(),
                  [](const Component& a, const Component& b) { return a.id < b.id; });
        return out;
    }

    std::vector<std::string> ids() const {
        std::vector<std::string> out;
        out.reserve(components_.size());
        for (const auto& c : all()) out.push_back(c.id);
        return out;
    }

    // Structural integrity. Returns a list of human-readable problems.
    std::vector<std::string> validate() const {
        std::vector<std::string> issues;
        std::vector<std::string> seen;
        for (const auto& c : components_) {
            bool dup = false;
            for (const auto& s : seen) {
                if (s == c.id) { dup = true; break; }
            }
            if (dup) {
                issues.push_back("duplicate component id: " + c.id);
            } else {
                seen.push_back(c.id);
            }
            for (const auto& dep : c.depends_on) {
                bool found = false;
                for (const auto& s : seen) {
                    if (s == dep) { found = true; break; }
                }
                // allow dependencies on ids registered later
                bool later = false;
                for (const auto& o : components_) {
                    if (o.id == dep) { later = true; break; }
                }
                if (!found && !later) {
                    issues.push_back("unknown dependency: " + c.id + " -> " + dep);
                }
            }
        }
        return issues;
    }

private:
    std::vector<Component> components_;
};

// ---------------------------------------------------------------------------
// ServiceState (Phase 0.6)
// The availability and lifecycle state of a Service.
// ---------------------------------------------------------------------------
enum class ServiceState {
    kUnavailable,  // not available
    kActivating,   // in the process of becoming available
    kAvailable,    // ready to accept requests
    kDegraded,     // partially available with reduced capability
    kDeactivating, // in the process of becoming unavailable
    kFailed,       // activation failed or service became unavailable due to error
};

inline std::string_view to_string(ServiceState s) {
    switch (s) {
        case ServiceState::kUnavailable:  return "unavailable";
        case ServiceState::kActivating:   return "activating";
        case ServiceState::kAvailable:    return "available";
        case ServiceState::kDegraded:     return "degraded";
        case ServiceState::kDeactivating: return "deactivating";
        case ServiceState::kFailed:       return "failed";
    }
    return "unknown";
}

// ---------------------------------------------------------------------------
// ServiceActivation (Phase 0.6)
// How a Service is activated.
// ---------------------------------------------------------------------------
enum class ServiceActivation {
    kNone,           // no activation
    kPersistent,     // always running
    kManual,         // activated on explicit request
    kBoot,           // started at boot time
    kOnDemand,       // started when first accessed
    kSocket,         // socket-activated by systemd
    kDBus,           // D-Bus activated
    kPath,           // path-activated (filesystem event)
    kDevice,         // device-activated (udev)
    kTimer,          // timer-triggered (systemd .timer)
    kEvent,          // event-triggered (inotify/fanotify/subscriptions)
};

inline std::string_view to_string(ServiceActivation a) {
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

// ---------------------------------------------------------------------------
// DependencyKind (Phase 0.6)
// A dependency of one Service on another.
// ---------------------------------------------------------------------------
enum class DependencyKind {
    kRequired,       // hard dependency
    kOptional,       // optional dependency
    kOrdering,       // ordering only
    kSoft,           // soft dependency
};

inline std::string_view to_string(DependencyKind k) {
    switch (k) {
        case DependencyKind::kRequired: return "required";
        case DependencyKind::kOptional: return "optional";
        case DependencyKind::kOrdering: return "ordering";
        case DependencyKind::kSoft:     return "soft";
    }
    return "unknown";
}

struct ServiceDependency {
    std::string service_id;
    DependencyKind kind;
    bool is_satisfied = false;
};

// ---------------------------------------------------------------------------
// ServiceInfo (Phase 0.6)
// A machine-readable description of a Service.
// ---------------------------------------------------------------------------
struct ServiceInfo {
    std::string id;
    std::string title;
    std::string description;
    std::string owner_system;
    std::set<std::string> categories;
    ServiceActivation activation;
    bool enabled = true;
    std::vector<std::string> interfaces;
    std::optional<std::string> default_interface;
    std::vector<ServiceDependency> dependencies;
    bool requires_root = false;
    bool cpu_only = false;
    std::optional<int64_t> memory_limit_bytes;
    bool has_readiness_check = false;
    bool has_health_check = false;
};

// ---------------------------------------------------------------------------
// ServiceRegistry (Phase 0.6)
// A data structure for managing known Services.
// ---------------------------------------------------------------------------
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
    
    std::vector<std::string> validate() const {
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
        
        return issues;
    }

private:
    std::map<std::string, ServiceInfo> services_;
};

inline bool is_available(ServiceState s) {
    return s == ServiceState::kAvailable || s == ServiceState::kDegraded;
}

inline bool is_unavailable(ServiceState s) {
    return s == ServiceState::kUnavailable || s == ServiceState::kFailed;
}

// ---------------------------------------------------------------------------
// OperationMetadata (Phase 0.10)
// Metadata describing an Operation's characteristics.
//
// An Operation is a reusable, explicitly contracted system capability that:
//   - Observes, queries, changes, constructs, removes, transforms, or controls
//     system state or resources
//   - Has typed inputs and outputs
//   - Documents preconditions (must hold before execution)
//   - Documents expected effects (what should change after execution)
//   - Documents postconditions (must hold for success to be verified)
//   - Provides verification strategy (how success is independently confirmed)
//   - Carries Evidence supporting the result
//
// An Operation is NOT:
//   - A shell command or script
//   - A Unit (Units are structural execution definitions)
//   - A Task (Tasks parameterize Operations for concrete work)
//   - A Provider (Providers supply implementations)
// ---------------------------------------------------------------------------
enum class SideEffectKind {
    NONE,        // read-only operation, no mutation
    OBSERVATION, // reads state but doesn't change it
    MUTATING,    // changes system state
    PRIVILEGED,  // requires elevated privilege
    DESTRUCTIVE, // irreversible or hard-to-reverse change
};

inline std::string_view to_string(SideEffectKind k) {
    switch (k) {
        case SideEffectKind::NONE:       return "none";
        case SideEffectKind::OBSERVATION:return "observation";
        case SideEffectKind::MUTATING:   return "mutating";
        case SideEffectKind::PRIVILEGED: return "privileged";
        case SideEffectKind::DESTRUCTIVE:return "destructive";
    }
    return "unknown";
}

enum class Idempotency {
    IDEMPOTENT,        
    CONDITIONALLY_IDEMPOTENT,
    NON_IDEMPOTENT,
    UNKNOWN,
};

inline std::string_view to_string(Idempotency k) {
    switch (k) {
        case Idempotency::IDEMPOTENT:         return "idempotent";
        case Idempotency::CONDITIONALLY_IDEMPOTENT: return "conditionally_idempotent";
        case Idempotency::NON_IDEMPOTENT:     return "non_idempotent";
        case Idempotency::UNKNOWN:            return "unknown";
    }
    return "unknown";
}

enum class Reversibility {
    REVERSIBLE,         
    CONDITIONALLY_REVERSIBLE,
    IRREVERSIBLE,
    UNKNOWN,
};

inline std::string_view to_string(Reversibility k) {
    switch (k) {
        case Reversibility::REVERSIBLE:         return "reversible";
        case Reversibility::CONDITIONALLY_REVERSIBLE: return "conditionally_reversible";
        case Reversibility::IRREVERSIBLE:       return "irreversible";
        case Reversibility::UNKNOWN:            return "unknown";
    }
    return "unknown";
}

// ---------------------------------------------------------------------------
// OperationDefinition
// The canonical contract for an Operation.
// ---------------------------------------------------------------------------
struct OperationDefinition {
    std::string id;                     // stable semantic identifier, e.g., "filesystem.copy"
    
    // Semantic information
    std::string title;                  // human-readable name
    std::string description;            // one-line purpose statement
    std::string long_description;       // detailed description of behavior
    
    // Subject/target type (what the operation acts upon)
    std::string subject_type;           // e.g., "filesystem.path", "service", "package"
    
    // Input schema reference
    std::string input_schema_ref;
    
    // Output schema reference
    std::string output_schema_ref;
    
    // Preconditions: what must be true before execution
    std::vector<std::string> preconditions;
    
    // Expected effects
    std::vector<std::string> expected_effects;
    
    // Postconditions: what MUST be true for success to be verified
    std::vector<std::string> postconditions;
    
    // Verification strategy
    enum class VerificationKind {
        NONE,
        COMMAND_RESULT,
        STATE_OBSERVATION,
        FUNCTIONAL,
        END_TO_END,
    } verification_kind = VerificationKind::NONE;
    
    std::string verification_description;
    
    // Evidence sources
    std::vector<std::string> evidence_sources;
    
    // Provider information
    std::vector<std::string> provider_ids;
    
    // Safety characteristics
    SideEffectKind side_effect = SideEffectKind::NONE;
    Idempotency idempotency = Idempotency::UNKNOWN;
    Reversibility reversibility = Reversibility::UNKNOWN;
    
    // Scope and privilege requirements
    std::optional<std::string> required_privilege;
    bool requires_lock = false;
    
    // Execution constraints
    std::optional<int64_t> max_execution_time_ms;
    bool allows_concurrent_execution = true;
    
    // Registry metadata
    ComponentKind kind = ComponentKind::kUnit;
};

// ---------------------------------------------------------------------------
// OperationRequest
// A request to execute an Operation with concrete parameters.
// ---------------------------------------------------------------------------
struct OperationRequest {
    std::string operation_id;
    
    // Subject: what the operation acts upon
    std::optional<std::string> subject;
    
    // Parameters: concrete input values
    std::map<std::string, std::string> parameters;
    
    // Execution control
    bool dry_run = false;
    bool allow_partial = false;
    
    // Context
    std::optional<std::string> caller_id;
    std::optional<int> priority;
};

// ---------------------------------------------------------------------------
// SecretRef
// An opaque reference to a secret stored in native credential storage.
//
// Key principles:
//   * NEVER contains actual secret material (password, token, key bytes)
//   * Provider + scope + key identify the secret location
//   * Resolution is done via native provider API (systemd_credentials_get,
//     Secret Service D-Bus, etc.)
//   * Redaction occurs at serialization boundaries - never log or persist values
//
// This is Phase 37's domain for credential storage integration. Here we define
// the generic reference type for use across Rebuntu.
// ---------------------------------------------------------------------------
struct SecretRef {
    std::string provider;        // "systemd", "keyring", "env"
    std::string scope;           // "system", "user", "session"  
    std::string key;             // Reference key within provider
    std::optional<std::string> description;
    
    bool is_valid() const {
        return !provider.empty() && !scope.empty() && !key.empty();
    }
};

inline std::string to_string(const SecretRef& ref) {
    return "SecretRef{" + ref.provider + "/" + ref.scope + ":" + ref.key + "}";
}

// ---------------------------------------------------------------------------
// OperationResult
// The result of executing an Operation.
//
// This carries both the outcome and evidence supporting it. It is the
// canonical return type for all Operations.
// ---------------------------------------------------------------------------
struct OperationResult {
    SemanticStatus status = SemanticStatus::kUnknown;
    
    // Success indicators
    bool changed = false;             // true if state was actually modified
    
    // Verification status
    bool verified = false;            // postconditions were independently verified
    
    // Evidence: observations supporting the result
    std::vector<Evidence> evidence;
    
    // Error information (if not success)
    std::optional<Error> error;
    
    // Output value (where applicable)
    std::optional<std::string> output_value;
    
    // Execution metadata
    std::optional<int64_t> execution_time_ms;
    
    static OperationResult success(bool changed = true, bool verified = true) {
        OperationResult r;
        r.status = SemanticStatus::kSuccess;
        r.changed = changed;
        r.verified = verified;
        return r;
    }
    
    static OperationResult no_change() {
        // No-op: desired state already existed
        OperationResult r;
        r.status = SemanticStatus::kSuccess;
        r.changed = false;
        r.verified = true;
        return r;
    }
    
    static OperationResult failure(std::string code, std::string message) {
        OperationResult r;
        r.status = SemanticStatus::kFailure;
        r.error = Error{std::move(code), std::move(message)};
        return r;
    }
    
    static OperationResult unknown(std::string message) {
        OperationResult r;
        r.status = SemanticStatus::kUnknown;
        r.error = Error{"E_UNKNOWN", std::move(message)};
        return r;
    }
    
    bool is_success() const { return status == SemanticStatus::kSuccess && verified; }
};

// ---------------------------------------------------------------------------
// PreconditionCheckResult
// Result of evaluating preconditions before execution.
// ---------------------------------------------------------------------------
enum class PreconditionResult {
    SATISFIED,      // all preconditions satisfied
    FAILED,         // required preconditions not met
    WARNING,        // optional preconditions not met
};

inline std::string_view to_string(PreconditionResult r) {
    switch (r) {
        case PreconditionResult::SATISFIED: return "satisfied";
        case PreconditionResult::FAILED:    return "failed";
        case PreconditionResult::WARNING:   return "warning";
    }
    return "unknown";
}

// ---------------------------------------------------------------------------
// PlanStep
// A step in an execution plan, produced during the PLANNING phase.
// ---------------------------------------------------------------------------
struct PlanStep {
    std::string description;       // human-readable step description
    std::string native_action;     // native mechanism to invoke (e.g., "apt install", "cp")
    std::vector<std::string> argv; // argument vector for the action
    
    // State before and after this step
    std::optional<std::string> expected_before_state;
    std::optional<std::string> expected_after_state;
    
    // Verification for this step
    bool requires_verification = false;
};

// ---------------------------------------------------------------------------
// ExecutionPlan
// A complete execution plan for an Operation.
// ---------------------------------------------------------------------------
struct ExecutionPlan {
    std::string operation_id;          // which operation this plans
    
    // Overall strategy
    bool is_no_op = false;             // no action needed (preconditions already met)
    bool requires_checkpoint = false;  // should capture state before mutation
    
    // Steps to execute
    std::vector<PlanStep> steps;
    
    // Rollback plan (if operation is reversible)
    std::optional<std::string> rollback_plan_description;
    
    // Verification strategy for post-execution
    std::vector<std::string> verification_steps;
};

// ---------------------------------------------------------------------------
// OperationRegistry
// A registry of known Operations.
//
// This enables:
//   - Discovery: what operations are available?
//   - Resolution: which provider implements this operation?
//   - Validation: is this operation definition valid?
//   - Documentation generation
// ---------------------------------------------------------------------------
class OperationRegistry {
public:
    void register_operation(OperationDefinition def) {
        operations_[def.id] = std::move(def);
    }
    
    bool contains(std::string_view id) const {
        return operations_.find(std::string{id}) != operations_.end();
    }
    
    std::optional<OperationDefinition> find(std::string_view id) const {
        auto it = operations_.find(std::string{id});
        if (it == operations_.end()) return std::nullopt;
        return it->second;
    }
    
    // Find operations by subject type
    std::vector<OperationDefinition> by_subject(std::string_view subject_type) const {
        std::vector<OperationDefinition> result;
        for (const auto& [id, op] : operations_) {
            if (op.subject_type == subject_type) {
                result.push_back(op);
            }
        }
        std::sort(result.begin(), result.end(),
                  [](const OperationDefinition& a, const OperationDefinition& b) { return a.id < b.id; });
        return result;
    }
    
    // Find operations by side effect kind
    std::vector<OperationDefinition> by_side_effect(SideEffectKind kind) const {
        std::vector<OperationDefinition> result;
        for (const auto& [id, op] : operations_) {
            if (op.side_effect == kind || kind == SideEffectKind::NONE) {
                if (op.side_effect == kind) {
                    result.push_back(op);
                }
            }
        }
        std::sort(result.begin(), result.end(),
                  [](const OperationDefinition& a, const OperationDefinition& b) { return a.id < b.id; });
        return result;
    }
    
    // Get all registered operations
    std::vector<OperationDefinition> all() const {
        std::vector<OperationDefinition> result;
        result.reserve(operations_.size());
        for (const auto& [id, op] : operations_) {
            result.push_back(op);
        }
        std::sort(result.begin(), result.end(),
                  [](const OperationDefinition& a, const OperationDefinition& b) { return a.id < b.id; });
        return result;
    }
    
    // Validate registry structure
    std::vector<std::string> validate() const {
        std::vector<std::string> issues;
        std::set<std::string> seen;
        
        for (const auto& [id, op] : operations_) {
            if (!seen.insert(id).second) {
                issues.push_back("duplicate operation id: " + id);
                continue;
            }
            
            // Check required fields
            if (op.title.empty()) {
                issues.push_back("operation " + id + " missing title");
            }
            if (op.description.empty()) {
                issues.push_back("operation " + id + " missing description");
            }
            if (op.subject_type.empty()) {
                issues.push_back("operation " + id + " missing subject type");
            }
        }
        
        return issues;
    }
    
private:
    std::map<std::string, OperationDefinition> operations_;
};

// ---------------------------------------------------------------------------
// OperationStatus helpers
// ---------------------------------------------------------------------------

inline bool is_executed(OperationStatus s) {
    return s >= OperationStatus::kExecuted;
}

inline bool is_verified(OperationStatus s) {
    return s == OperationStatus::kVerified;
}

}  // namespace rebuntu::core