// rebuntu::environment::authorization — Authorization & Scope Contract (Phase 2.6)
//
// This establishes Rebuntu's canonical authorization model:
//
//   AUTHORIZATION = Policy decision: "Is this action permitted?"
//   SCOPE         = System vs User context that constrains authorization
//   POLICY        = Rules governing what is allowed for whom, where, when
//   EVIDENCE      = Provenance-bearing observation supporting the decision
//
// Architecture:
//   Interfaces      -> src/interfaces/
//   Adapters/Providers -> src/adapters/*/
//   Semantics       -> src/system/environment/authorization.hpp
//
// Phase 2.6 adds authorization grammar and scope binding to Rebuntu.
//
// Authorization Grammar:
//   subject/caller + requested operation + target + scope + context + policy -> decision
//
// Decisions: ALLOW / DENY / REQUIRE_ELEVATION / REQUIRE_CONFIRMATION / UNKNOWN

#pragma once

#include <unistd.h>
#include <sys/types.h>

#include <runtime/core/contracts.hpp>
#include <string>
#include <vector>
#include <set>
#include <optional>
#include <chrono>
#include <map>

// Include privilege first since we reference it
#include <observation/environment/privilege.hpp>

// Authorization module types that extend privilege functionality
namespace rebuntu::environment::authorization {

// ============================================================================
// Authorization Decision
// ============================================================================

enum class AuthorizationDecision {
    kAllow,                    // Request is authorized
    kDeny,                     // Request is explicitly denied
    kRequireElevation,         // Requires elevated privilege (e.g., root)
    kRequireConfirmation,      // Requires explicit user confirmation
    kInsufficientInformation,  // Cannot determine authorization state
};

inline const char* to_string(AuthorizationDecision d) {
    switch (d) {
        case AuthorizationDecision::kAllow: return "allow";
        case AuthorizationDecision::kDeny: return "deny";
        case AuthorizationDecision::kRequireElevation: return "require-elevation";
        case AuthorizationDecision::kRequireConfirmation: return "require-confirmation";
        case AuthorizationDecision::kInsufficientInformation: return "insufficient-information";
    }
    return "unknown";
}

// ============================================================================
// Subject/Caller
// ============================================================================

struct Caller {
    uid_t uid = 0;                    // Real UID of caller
    uid_t euid = 0;                   // Effective UID of caller
    
    std::optional<std::string> username;     // Username from NSS if available
    std::optional<gid_t> gid;                // Primary GID
    std::set<gid_t> supplementary_groups;    // All groups caller belongs to
    
    bool is_root = false;
    
    // Audit trail
    std::optional<std::string> sudo_user;  // SUDO_USER env var if elevated
    
    static Caller current() {
        Caller c;
        c.uid = getuid();
        c.euid = geteuid();
        c.is_root = (c.euid == 0);
        
        const char* username_env = std::getenv("USER");
        if (username_env) c.username = username_env;
        
        // Get primary GID
        c.gid = getgid();
        
        // SUDO_USER check for audit trail
        const char* sudo_user_env = std::getenv("SUDO_USER");
        if (sudo_user_env && c.is_root && c.uid != 0) {
            c.sudo_user = sudo_user_env;
        }
        
        return c;
    }
};

// ============================================================================
// Requested Operation
// ============================================================================

enum class OperationClass {
    kRead,           // Read-only observation/query
    kWrite,          // State modification
    kManage,         // Configuration/administrative change
    kDestroy,        // Destructive operation (deletion/removal)
};

inline const char* to_string(OperationClass oc) {
    switch (oc) {
        case OperationClass::kRead: return "read";
        case OperationClass::kWrite: return "write";
        case OperationClass::kManage: return "manage";
        case OperationClass::kDestroy: return "destroy";
    }
    return "unknown";
}

struct RequestedOperation {
    std::string name;              // Human-readable operation name
    OperationClass op_class;       // Class of operation
    
    std::optional<std::string> subject_type;  // e.g., "filesystem.path", "service"
    std::optional<std::string> target_id;     // Specific target identifier
    
    bool is_read_only() const { return op_class == OperationClass::kRead; }
};

// ============================================================================
// Target
// ============================================================================

enum class TargetType {
    kSystem,       // System-wide resource (requires root)
    kUser,         // User-scoped resource (uid-specific)
    kFilesystem,   // Filesystem path
    kService,      // systemd service
    kProcess,      // Process ID
    kNetwork,      // Network configuration
};

inline const char* to_string(TargetType tt) {
    switch (tt) {
        case TargetType::kSystem: return "system";
        case TargetType::kUser: return "user";
        case TargetType::kFilesystem: return "filesystem";
        case TargetType::kService: return "service";
        case TargetType::kProcess: return "process";
        case TargetType::kNetwork: return "network";
    }
    return "unknown";
}

struct AuthorizationTarget {
    TargetType type;
    
    // Type-specific target data
    std::optional<std::string> path;           // For kFilesystem
    std::optional<std::string> service_name;   // For kService
    std::optional<pid_t> pid;                  // For kProcess
    
    // Expected ownership (for verification)
    std::optional<uid_t> expected_owner;
    std::optional<gid_t> expected_group;
    
    static AuthorizationTarget filesystem(std::string p) {
        AuthorizationTarget t;
        t.type = TargetType::kFilesystem;
        t.path = std::move(p);
        return t;
    }
    
    static AuthorizationTarget service(std::string s) {
        AuthorizationTarget t;
        t.type = TargetType::kService;
        t.service_name = std::move(s);
        return t;
    }
};

// ============================================================================
// Scope Context
// Note: This extends rebuntu::environment::privilege::ScopeContext with additional
// fields for authorization-specific needs.
// ============================================================================

// ScopeContext reuses privilege module's type for consistency
using ScopeContext = rebuntu::environment::privilege::ScopeContext;

// ============================================================================
// Policy Evaluation Context
// ============================================================================

struct PolicyContext {
    // When the request was made (for time-based policies)
    std::chrono::system_clock::time_point timestamp;
    
    // Source of the request (CLI, API, internal)
    std::optional<std::string> source_context;  // e.g., "cli", "api", "internal"
    
    // Additional metadata for policy evaluation
    std::map<std::string, std::string> metadata;
};

// ============================================================================
// Authorization Decision Result
// ============================================================================

struct AuthorizationDecisionResult {
    AuthorizationDecision decision = AuthorizationDecision::kInsufficientInformation;
    
    // Human-readable explanation (never contains secrets)
    std::string reason;
    
    // Required conditions for this decision to change
    struct RequiredChange {
        enum class Type {
            kElevation,       // Need elevated privilege (e.g., root)
            kConfirmation,    // Need explicit user confirmation
            kAdditionalInfo,  // Need more information
        } type;
        
        std::string description;  // What's needed to change the decision
    };
    
    std::vector<RequiredChange> required_changes;
    
    // Evidence supporting this decision
    struct DecisionEvidence {
        std::string source;           // e.g., "policy_engine", "capability_check"
        std::string observation;      // What was observed
        std::chrono::system_clock::time_point observed_at;
    };
    
    std::vector<DecisionEvidence> evidence;
    
    // Helper methods
    bool is_allowed() const { return decision == AuthorizationDecision::kAllow; }
    bool is_denied() const { return decision == AuthorizationDecision::kDeny; }
    
    static AuthorizationDecisionResult allow(std::string r) {
        AuthorizationDecisionResult result;
        result.decision = AuthorizationDecision::kAllow;
        result.reason = std::move(r);
        return result;
    }
    
    static AuthorizationDecisionResult deny(std::string r) {
        AuthorizationDecisionResult result;
        result.decision = AuthorizationDecision::kDeny;
        result.reason = std::move(r);
        return result;
    }
    
    static AuthorizationDecisionResult require_elevation(std::string desc, std::string r) {
        AuthorizationDecisionResult result;
        result.decision = AuthorizationDecision::kRequireElevation;
        result.reason = std::move(r);
        RequiredChange rc;
        rc.type = RequiredChange::Type::kElevation;
        rc.description = std::move(desc);
        result.required_changes.push_back(rc);
        return result;
    }
    
    static AuthorizationDecisionResult require_confirmation(std::string desc, std::string r) {
        AuthorizationDecisionResult result;
        result.decision = AuthorizationDecision::kRequireConfirmation;
        result.reason = std::move(r);
        RequiredChange rc;
        rc.type = RequiredChange::Type::kConfirmation;
        rc.description = std::move(desc);
        result.required_changes.push_back(rc);
        return result;
    }
    
    static AuthorizationDecisionResult insufficient(std::string r) {
        AuthorizationDecisionResult result;
        result.decision = AuthorizationDecision::kInsufficientInformation;
        result.reason = std::move(r);
        return result;
    }
};

// ============================================================================
// Policy Engine Interface
// ============================================================================

struct AuthorizationRequest {
    Caller caller;
    RequestedOperation operation;
    AuthorizationTarget target;
    ScopeContext scope;
    std::optional<PolicyContext> context;
};

class PolicyEngine {
public:
    virtual ~PolicyEngine() = default;
    
    // Evaluate an authorization request and return a decision
    virtual AuthorizationDecisionResult evaluate(const AuthorizationRequest& request) const = 0;
    
    // Check if policy can make a decision (returns true if sufficient information available)
    virtual bool can_evaluate(const AuthorizationRequest& request) const = 0;
    
    // Get the policy name/version for logging
    virtual const char* policy_name() const = 0;
};

// ============================================================================
// Built-in Policy Implementations
// ============================================================================

class BasicAuthorizationPolicy : public PolicyEngine {
public:
    AuthorizationDecisionResult evaluate(const AuthorizationRequest& request) const override;
    
    bool can_evaluate(const AuthorizationRequest& request) const override {
        (void)request;
        return true;  // Can always evaluate with available information
    }
    
    const char* policy_name() const override { return "basic"; }
};

// ============================================================================
// Authorization Context - Top-level entry point
// ============================================================================

class AuthorizationContext {
public:
    // Construct from caller context (uses current process identity)
    static AuthorizationContext current();
    
    // Evaluate an authorization request
    AuthorizationDecisionResult authorize(
        const RequestedOperation& operation,
        const AuthorizationTarget& target) const;
    
    // Check if caller is authorized for a read-only operation
    AuthorizationDecisionResult authorize_read(
        const std::string& operation_name,
        const AuthorizationTarget& target) const;
    
    // Check if caller is authorized for a write operation
    AuthorizationDecisionResult authorize_write(
        const std::string& operation_name,
        const AuthorizationTarget& target) const;
    
    // Get the current scope context
    const ScopeContext& get_scope() const { return scope_; }
    
    // Get the current caller identity
    const Caller& get_caller() const { return caller_; }

private:
    Caller caller_;
    ScopeContext scope_;
};

}  // namespace rebuntu::environment::authorization