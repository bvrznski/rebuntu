// rebuntu::runtime::resolver — Runtime Resolution (Phase 4.8)
//
// The Resolver is responsible for mapping stable semantic identifiers/specifications
// to concrete executable capabilities/providers/targets WITHOUT executing them.
//
// Key principles:
//   * Deterministic: same input always produces same output
//   * Explainable: can document WHY a candidate was selected/rejected
//   * Scope-aware: respects scope boundaries and policies
//   * Policy-compatible: adheres to authorization and policy constraints
//   * Non-mutating: resolution does not change state or execute work
//
// Resolution outcomes:
//   RESOLVED / NOT_FOUND / AMBIGUOUS / UNAVAILABLE / FORBIDDEN / UNKNOWN

#pragma once

#include <runtime/work.hpp>
#include <runtime/contracts.hpp>
#include <optional>
#include <string>
#include <vector>
#include <map>
#include <memory>

namespace rebuntu::runtime::resolver {

// ============================================================================
// Resolution Status
// ============================================================================

enum class ResolutionStatus {
    kResolved,        // Successfully resolved to a concrete target
    kNotFound,        // No matching definition/capability found
    kAmbiguous,       // Multiple candidates with equal claim
    kUnavailable,     // Definition exists but provider is unavailable
    kForbidden,       // Policy/authorization prevents resolution
    kUnknown,         // Could not determine status (not a negative observation)
};

inline std::string to_string(ResolutionStatus s) {
    switch (s) {
        case ResolutionStatus::kResolved: return "resolved";
        case ResolutionStatus::kNotFound: return "not_found";
        case ResolutionStatus::kAmbiguous: return "ambiguous";
        case ResolutionStatus::kUnavailable: return "unavailable";
        case ResolutionStatus::kForbidden: return "forbidden";
        case ResolutionStatus::kUnknown: return "unknown";
    }
    return "unknown";
}

// ============================================================================
// Resolution Candidate
// ============================================================================

struct ResolutionCandidate {
    std::string id;                    // Stable semantic identifier
    std::string title;                 // Human-readable name
    std::string description;           // One-line purpose statement
    
    enum class Kind {
        kTask,              // A parameterized Task definition
        kWorkflow,          // A Workflow specification
        kOperation,         // An Operation definition
        kProvider,          // A provider implementation
        kTarget,            // A concrete target (path, unit, etc.)
    } kind = Kind::kTask;
    
    std::optional<std::string> provider_id;
    std::optional<std::string> native_mechanism;
    
    std::vector<std::string> allowed_scopes;  // Empty = all scopes
    
    bool requires_verification = false;
};

// ============================================================================
// Rejection Reason
// ============================================================================

struct RejectionReason {
    enum class Category {
        kNotFound,
        kAmbiguous,
        kUnavailable,
        kForbidden,
        kScopeMismatch,
        kCapabilityMissing,
        kInvalidDefinition,
    } category;
    
    std::string code;
    std::string message;
    
    std::optional<std::string> candidate_id;
};

inline std::string to_string(RejectionReason::Category c) {
    switch (c) {
        case RejectionReason::Category::kNotFound: return "not_found";
        case RejectionReason::Category::kAmbiguous: return "ambiguous";
        case RejectionReason::Category::kUnavailable: return "unavailable";
        case RejectionReason::Category::kForbidden: return "forbidden";
        case RejectionReason::Category::kScopeMismatch: return "scope_mismatch";
        case RejectionReason::Category::kCapabilityMissing: return "capability_missing";
        case RejectionReason::Category::kInvalidDefinition: return "invalid_definition";
    }
    return "unknown";
}

// ============================================================================
// Resolution Result
// ============================================================================

struct ResolutionResult {
    rebuntu::core::SemanticStatus status = rebuntu::core::SemanticStatus::kUnknown;
    
    ResolutionCandidate candidate;  // Always present when resolved
    
    std::vector<rebuntu::core::Evidence> evidence;
    
    std::vector<RejectionReason> rejections;
    
    std::string resolved_scope;
    
    bool succeeded() const {
        return status == rebuntu::core::SemanticStatus::kSuccess && !candidate.id.empty();
    }
};

// ============================================================================
// Resolution Context
// ============================================================================

struct ResolutionContext {
    std::optional<std::string> scope;
    std::chrono::system_clock::time_point at_time = std::chrono::system_clock::now();
    
    bool allow_unverified = false;
    bool require_provider = true;
    
    std::optional<std::string> required_capability;
    
    static ResolutionContext default_context() {
        return ResolutionContext{};
    }
};

// ============================================================================
// Resolver Interface
// ============================================================================

class Resolver {
public:
    virtual ~Resolver() = default;
    
    virtual ResolutionResult resolve(const std::string& id, const ResolutionContext& ctx) = 0;
    
    virtual std::vector<ResolutionCandidate> list_candidates(
        std::optional<ResolutionCandidate::Kind> kind_filter = std::nullopt,
        std::optional<std::string> scope_filter = std::nullopt) const = 0;
    
    virtual std::vector<ResolutionResult> get_resolution_history() const = 0;
};

// ============================================================================
// InMemoryResolver
// ============================================================================

class InMemoryResolver : public Resolver {
public:
    InMemoryResolver();
    ~InMemoryResolver() override;
    
    void add_task(const work::Task& task);
    void add_operation(const rebuntu::core::OperationDefinition& op_def);
    
    ResolutionResult resolve(const std::string& id, const ResolutionContext& ctx) override;
    
    std::vector<ResolutionCandidate> list_candidates(
        std::optional<ResolutionCandidate::Kind> kind_filter = std::nullopt,
        std::optional<std::string> scope_filter = std::nullopt) const override;
    
    std::vector<ResolutionResult> get_resolution_history() const override;

private:
    std::map<std::string, work::Task> tasks_;
    std::map<std::string, rebuntu::core::OperationDefinition> operations_;
    
    mutable std::vector<ResolutionResult> resolution_history_;
    
    ResolutionResult resolve_task(const std::string& id, const ResolutionContext& ctx) const;
    ResolutionResult resolve_operation(const std::string& id, const ResolutionContext& ctx) const;
};

// ============================================================================
// Factory functions
// ============================================================================

std::unique_ptr<Resolver> make_resolver();

}  // namespace rebuntu::runtime::resolver