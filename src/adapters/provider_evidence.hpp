// rebuntu::adapters::provider_evidence — Provider Result Distrust (Task 6.52)
//
// This module establishes the architectural contract that provider responses
// are mechanism evidence, NOT policy decisions.
//
// Key Principles:
//   - PROVIDER OBSERVATION != AUTHORITY DECISION
//   - Providers return observed facts with provenance, not policy approval
//   - Authorization is a separate decision made by canonical policy engine
//   - Evidence supports authorization but never constitutes it
//
// Design Pattern:
//
//   BEFORE (INCORRECT):
//     ProviderResult result = provider->check_access();
//     if (result.authorized) {  // WRONG: Provider granting authority!
//         execute_operation();
//     }
//
//   AFTER (CORRECT):
//     Evidence evidence = provider->observe_state();
//     AuthorizationRequest req{.subject=..., .action=..., .evidence=evidence};
//     PolicyDecision decision = policy_engine.evaluate(req);
//     if (decision.allowed) {  // RIGHT: Canonical authority making decision
//         execute_operation();
//     }

#pragma once

#include <system/core/contracts.hpp>
#include <adapters/isolated_provider.hpp>
#include <string>
#include <chrono>
#include <vector>
#include <optional>

namespace rebuntu::adapters {

// ============================================================================
// ProviderEvidence — Provenance-bearing observation from a provider
//
// This is the canonical result type for all providers. It represents an
// observed fact with source information, NOT an authorization decision.
//
// Key Invariants:
//   - Evidence is DATA, not CONTROL
//   - Evidence never confers authority
//   - Evidence has provenance (source, timestamp, observation details)
// ============================================================================
struct ProviderEvidence {
    // The subject of the observation
    std::string subject;      // e.g., "service:apache2", "file:/etc/passwd"
    
    // What was observed
    std::string observation;  // e.g., "running", "exists", "permission denied"
    
    // Where this evidence came from (provider identification)
    std::string source;
    
    // When the observation was made
    std::chrono::system_clock::time_point observed_at{};
    
    // Evidence category for classification
    enum class Category {
        kState,          // System state observation (running/stopped/unknown)
        kProperty,       // Attribute observation (version, path, type)
        kPermission,     // Permission/accessibility observation
        kPresence,       // Entity presence/absence observation
        kConfiguration,  // Configuration value observation
        kError,          // Error condition observed
        kUnknown,
    } category{Category::kUnknown};
    
    std::string category_string() const {
        switch (category) {
            case Category::kState:         return "state";
            case Category::kProperty:      return "property";
            case Category::kPermission:    return "permission";
            case Category::kPresence:      return "presence";
            case Category::kConfiguration: return "configuration";
            case Category::kError:         return "error";
            default:                       return "unknown";
        }
    }
    
    // Factory methods
    
    static ProviderEvidence state(
        std::string subject,
        std::string observation_value,
        std::string source,
        std::chrono::system_clock::time_point time = {}
    ) {
        ProviderEvidence e;
        e.subject = std::move(subject);
        e.observation = std::move(observation_value);
        e.source = std::move(source);
        e.category = Category::kState;
        if (time == std::chrono::system_clock::time_point{}) {
            e.observed_at = std::chrono::system_clock::now();
        } else {
            e.observed_at = time;
        }
        return e;
    }
    
    static ProviderEvidence property(
        std::string subject,
        std::string observation_value,
        std::string source,
        std::chrono::system_clock::time_point time = {}
    ) {
        ProviderEvidence e;
        e.subject = std::move(subject);
        e.observation = std::move(observation_value);
        e.source = std::move(source);
        e.category = Category::kProperty;
        if (time == std::chrono::system_clock::time_point{}) {
            e.observed_at = std::chrono::system_clock::now();
        } else {
            e.observed_at = time;
        }
        return e;
    }
    
    static ProviderEvidence permission(
        std::string subject,
        bool has_access,
        std::string source,
        std::chrono::system_clock::time_point time = {}
    ) {
        ProviderEvidence e;
        e.subject = std::move(subject);
        e.observation = has_access ? "access_granted" : "access_denied";
        e.source = std::move(source);
        e.category = Category::kPermission;
        if (time == std::chrono::system_clock::time_point{}) {
            e.observed_at = std::chrono::system_clock::now();
        } else {
            e.observed_at = time;
        }
        return e;
    }
    
    static ProviderEvidence presence(
        std::string subject,
        bool exists,
        std::string source,
        std::chrono::system_clock::time_point time = {}
    ) {
        ProviderEvidence e;
        e.subject = std::move(subject);
        e.observation = exists ? "exists" : "not_found";
        e.source = std::move(source);
        e.category = Category::kPresence;
        if (time == std::chrono::system_clock::time_point{}) {
            e.observed_at = std::chrono::system_clock::now();
        } else {
            e.observed_at = time;
        }
        return e;
    }
};

inline std::string to_string(const ProviderEvidence& e) {
    return "ProviderEvidence{" +
           std::string("subject=") + e.subject + ", " +
           std::string("observation=") + e.observation + ", " +
           std::string("source=") + e.source + ", " +
           std::string("category=") + e.category_string() + ", " +
           std::string("observed_at=") + std::to_string(
               std::chrono::duration_cast<std::chrono::seconds>(
                   e.observed_at.time_since_epoch()).count()) +
           "}";
}

// ============================================================================
// ProviderResult<T> — Typed result from a provider
//
// This is the return type for all provider operations. It contains:
//   - Status: The semantic outcome (SUCCESS/FAILURE/UNKNOWN/CANCELLED)
//   - Evidence: The observations made during the operation
//   - Value: The actual result data (if any)
//   - Errors: Any errors encountered (non-fatal, may be partial)
//
// Key Invariants:
//   - This is NOT an authorization result
//   - A provider cannot "authorize" anything
//   - Evidence supports but never replaces authorization decisions
// ============================================================================
template<typename T>
struct ProviderResult {
    // Semantic status of the operation
    core::SemanticStatus status{core::SemanticStatus::kUnknown};
    
    // The actual result value (if successful)
    std::optional<T> value;
    
    // Evidence collected during the observation
    std::vector<ProviderEvidence> evidence;
    
    // Errors encountered (may be non-fatal, partial operation)
    std::vector<std::pair<std::string, core::Error>> errors;  // error_code -> details
    
    // Timing information
    std::chrono::milliseconds elapsed_ms{0};
    
    // Factory methods for common outcomes
    
    static ProviderResult success(T v, std::vector<ProviderEvidence> ev = {}, 
                                   std::chrono::milliseconds elapsed = {}) {
        ProviderResult r;
        r.status = core::SemanticStatus::kSuccess;
        r.value = std::move(v);
        r.evidence = std::move(ev);
        r.elapsed_ms = elapsed;
        return r;
    }
    
    static ProviderResult completed(T v, std::vector<ProviderEvidence> ev = {},
                                     std::chrono::milliseconds elapsed = {}) {
        ProviderResult r;
        r.status = core::SemanticStatus::kCompleted;  // Work done but verification skipped
        r.value = std::move(v);
        r.evidence = std::move(ev);
        r.elapsed_ms = elapsed;
        return r;
    }
    
    static ProviderResult failure(std::string error_code, std::string message,
                                   std::vector<ProviderEvidence> ev = {},
                                   std::chrono::milliseconds elapsed = {}) {
        ProviderResult r;
        r.status = core::SemanticStatus::kFailure;
        r.errors.emplace_back(std::move(error_code), 
                              core::Error{error_code, std::move(message)});
        r.evidence = std::move(ev);
        r.elapsed_ms = elapsed;
        return r;
    }
    
    static ProviderResult unknown(std::string message,
                                   std::vector<ProviderEvidence> ev = {},
                                   std::chrono::milliseconds elapsed = {}) {
        ProviderResult r;
        r.status = core::SemanticStatus::kUnknown;  // Outcome could not be determined
        r.errors.emplace_back("E_UNKNOWN", 
                              core::Error{"E_UNKNOWN", std::move(message)});
        r.evidence = std::move(ev);
        r.elapsed_ms = elapsed;
        return r;
    }
    
    static ProviderResult cancelled(std::string message,
                                     std::chrono::milliseconds elapsed = {}) {
        ProviderResult r;
        r.status = core::SemanticStatus::kCancelled;
        r.errors.emplace_back("E_CANCELLED",
                              core::Error{"E_CANCELLED", std::move(message)});
        r.elapsed_ms = elapsed;
        return r;
    }
    
    // Add evidence after construction
    void add_evidence(ProviderEvidence e) {
        evidence.push_back(std::move(e));
    }
    
    bool has_value() const { return value.has_value(); }
};

// ============================================================================
// ProviderResult<void> specialization — Void result handling
// ============================================================================
template<>
struct ProviderResult<void> {
    core::SemanticStatus status{core::SemanticStatus::kUnknown};
    std::vector<ProviderEvidence> evidence;
    std::vector<std::pair<std::string, core::Error>> errors;
    std::chrono::milliseconds elapsed_ms{0};
    
    static ProviderResult success(std::vector<ProviderEvidence> ev = {},
                                   std::chrono::milliseconds elapsed = {}) {
        ProviderResult r;
        r.status = core::SemanticStatus::kSuccess;
        r.evidence = std::move(ev);
        r.elapsed_ms = elapsed;
        return r;
    }
    
    static ProviderResult completed(std::vector<ProviderEvidence> ev = {},
                                     std::chrono::milliseconds elapsed = {}) {
        ProviderResult r;
        r.status = core::SemanticStatus::kCompleted;
        r.evidence = std::move(ev);
        r.elapsed_ms = elapsed;
        return r;
    }
    
    static ProviderResult failure(std::string error_code, std::string message,
                                   std::vector<ProviderEvidence> ev = {},
                                   std::chrono::milliseconds elapsed = {}) {
        ProviderResult r;
        r.status = core::SemanticStatus::kFailure;
        r.errors.emplace_back(error_code, core::Error{error_code, std::move(message)});
        r.evidence = std::move(ev);
        r.elapsed_ms = elapsed;
        return r;
    }
    
    static ProviderResult unknown(std::string message,
                                   std::vector<ProviderEvidence> ev = {},
                                   std::chrono::milliseconds elapsed = {}) {
        ProviderResult r;
        r.status = core::SemanticStatus::kUnknown;
        r.errors.emplace_back("E_UNKNOWN", core::Error{"E_UNKNOWN", std::move(message)});
        r.evidence = std::move(ev);
        r.elapsed_ms = elapsed;
        return r;
    }
    
    static ProviderResult cancelled(std::string message,
                                     std::chrono::milliseconds elapsed = {}) {
        ProviderResult r;
        r.status = core::SemanticStatus::kCancelled;
        r.errors.emplace_back("E_CANCELLED", core::Error{"E_CANCELLED", std::move(message)});
        r.elapsed_ms = elapsed;
        return r;
    }
    
    void add_evidence(ProviderEvidence e) {
        evidence.push_back(std::move(e));
    }
    
    bool has_value() const { return false; }
};

// ============================================================================
// ProviderResult<T> helpers
// ============================================================================
template<typename T>
std::string to_string(const ProviderResult<T>& r) {
    std::string result = "ProviderResult{" + std::string(core::to_string(r.status));
    if (r.value.has_value()) {
        result += ", value=<value present>";
    }
    result += ", evidence_size=" + std::to_string(r.evidence.size());
    result += "}";
    return result;
}

}  // namespace rebuntu::adapters

// ============================================================================
// Usage Example
// ============================================================================
//
// // WRONG: Provider returning authority decision
// struct BadProvider {
//     struct Result { bool success; bool authorized; };
//     Result observe() { return {true, true}; }  // WRONG: provider granting auth!
// };
//
// // CORRECT: Provider returning evidence only
// struct GoodProvider {
//     using Result = rebuntu::adapters::ProviderResult<ObservedState>;
//     
//     Result observe() {
//         ObservedState state{...};
//         std::vector<ProviderEvidence> ev;
//         ev.push_back(ProviderEvidence::state("service:apache2", "running", "systemd"));
//         ev.push_back(ProviderEvidence::property("service:apache2", "enabled", "systemd"));
//         return Result::success(state, ev);
//     }
// };
//
// // Authorization is a SEPARATE decision
// void process() {
//     auto provider = make_good_provider();
//     auto result = provider->observe();
//     
//     if (result.status == core::SemanticStatus::kSuccess) {
//         // Use evidence to inform authorization decision
//         PolicyRequest req{
//             .subject = "apache2",
//             .action = "stop",
//             .evidence = result.evidence  // Evidence, NOT authority!
//         };
//         
//         PolicyDecision decision = policy_engine.evaluate(req);
//         
//         if (decision.allowed) {  // Canonical authority decision
//             execute_stop();
//         } else {
//             // Authorization denied by canonical policy engine
//         }
//     }
// }
//
// ============================================================================