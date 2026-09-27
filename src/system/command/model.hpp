// rebuntu::command — Typed Command Model (Phase 6.1)
//
// This module defines the canonical typed Command representation for Rebuntu's
// execution system:
//
//   * Command: Semantic operation with typed arguments and targets
//   * CommandIR: Typed intermediate representation (parser output)
//   * CommandResolution: Mapping from IR to canonical capability
//   * ExecutionPlan: Concrete execution strategy derived from command
//
// Design Philosophy:
//   * Command != shell command (string with syntax)
//   * Command != intent (request before parsing)
//   * Command != operation (abstract capability)
//   * Command = typed request for concrete system action
//
// Key Principles:
//   * Commands are deterministic: same input, same output
//   * Commands have explicit targets and arguments (not stringly-typed)
//   * Commands preserve semantic intent through parsing/resolution
//   * Commands enable verification via typed structure

#pragma once

#include <system/core/contracts.hpp>
#include <string>
#include <vector>
#include <map>
#include <optional>
#include <chrono>

namespace rebuntu::command {

enum class SemanticKind {
    QUERY,
    OBSERVE,
    CONFIGURE,
    MANAGE,
    CREATE,
    UPDATE,
    REMOVE,
    EXECUTE,
    TRANSFORM,
};

inline std::string to_string(SemanticKind k) {
    switch (k) {
        case SemanticKind::QUERY:     return "query";
        case SemanticKind::OBSERVE:   return "observe";
        case SemanticKind::CONFIGURE: return "configure";
        case SemanticKind::MANAGE:    return "manage";
        case SemanticKind::CREATE:    return "create";
        case SemanticKind::UPDATE:    return "update";
        case SemanticKind::REMOVE:    return "remove";
        case SemanticKind::EXECUTE:   return "execute";
        case SemanticKind::TRANSFORM: return "transform";
    }
    return "unknown";
}

enum class ScopeContext {
    USER,
    SYSTEM,
    SESSION,
    WORKSPACE,
};

inline std::string to_string(ScopeContext s) {
    switch (s) {
        case ScopeContext::USER:     return "user";
        case ScopeContext::SYSTEM:   return "system";
        case ScopeContext::SESSION:  return "session";
        case ScopeContext::WORKSPACE:return "workspace";
    }
    return "unknown";
}

enum class SideEffectClass {
    NONE,
    OBSERVATION,
    MUTATING,
    PRIVILEGED,
    DESTRUCTIVE,
};

inline std::string to_string(SideEffectClass c) {
    switch (c) {
        case SideEffectClass::NONE:       return "none";
        case SideEffectClass::OBSERVATION:return "observation";
        case SideEffectClass::MUTATING:   return "mutating";
        case SideEffectClass::PRIVILEGED: return "privileged";
        case SideEffectClass::DESTRUCTIVE:return "destructive";
    }
    return "unknown";
}

struct TargetReference {
    std::string kind;
    std::optional<std::string> id;
    std::optional<std::string> name;
    std::optional<std::string> path;
};

struct Argument {
    std::string name;
    std::string value;
    bool required{false};
    std::optional<std::string> expected_type;
    std::optional<std::string> validation_pattern;
    
    static Argument required_arg(std::string n, std::string v) {
        Argument arg;
        arg.name = std::move(n);
        arg.value = std::move(v);
        arg.required = true;
        return arg;
    }
    
    static Argument optional_arg(std::string n, std::string v) {
        Argument arg;
        arg.name = std::move(n);
        arg.value = std::move(v);
        arg.required = false;
        return arg;
    }
};

struct Qualifier {
    std::string name;
    std::optional<std::string> value;
    
    static Qualifier flag(std::string n) {
        Qualifier q;
        q.name = std::move(n);
        return q;
    }
    
    static Qualifier with_value(std::string n, std::string v) {
        Qualifier q;
        q.name = std::move(n);
        q.value = std::move(v);
        return q;
    }
};

struct ExecutionPolicy {
    bool dry_run{false};
    bool verify{true};
    int max_attempts{1};
    std::chrono::milliseconds timeout{30000};
    
    static ExecutionPolicy default_policy() {
        return ExecutionPolicy{};
    }
    
    static ExecutionPolicy dry_run_only() {
        ExecutionPolicy p;
        p.dry_run = true;
        p.verify = false;
        return p;
    }
};

struct CommandIntent {
    std::string id;
    SemanticKind semantic_kind{SemanticKind::QUERY};
    std::string verb;
    TargetReference subject;
    std::vector<TargetReference> targets;
    std::vector<Argument> arguments;
    std::vector<Qualifier> qualifiers;
    ScopeContext scope{ScopeContext::USER};
    std::optional<std::string> caller_id;
    std::optional<std::string> source_context;
    std::optional<int> source_line;
    ExecutionPolicy execution_policy{};
};

enum class ResolutionStatus {
    kSuccess,
    kAmbiguous,
    kUnknownVerb,
    kUnknownTarget,
    kInvalidScope,
    kMissingRequired,
    kCollision,
};

inline std::string to_string(ResolutionStatus s) {
    switch (s) {
        case ResolutionStatus::kSuccess:     return "success";
        case ResolutionStatus::kAmbiguous:   return "ambiguous";
        case ResolutionStatus::kUnknownVerb: return "unknown_verb";
        case ResolutionStatus::kUnknownTarget:return "unknown_target";
        case ResolutionStatus::kInvalidScope:return "invalid_scope";
        case ResolutionStatus::kMissingRequired:return "missing_required";
        case ResolutionStatus::kCollision:   return "collision";
    }
    return "unknown";
}

struct CapabilityReference {
    std::string domain;
    std::string operation;
    
    static CapabilityReference make(std::string d, std::string o) {
        CapabilityReference cr;
        cr.domain = std::move(d);
        cr.operation = std::move(o);
        return cr;
    }
};

struct CommandResolution {
    ResolutionStatus status{ResolutionStatus::kSuccess};
    std::optional<CapabilityReference> capability;
    std::vector<std::string> candidates;
    std::string diagnostic;
    ScopeContext resolved_scope{ScopeContext::USER};
    
    static CommandResolution success(CapabilityReference cap) {
        CommandResolution r;
        r.status = ResolutionStatus::kSuccess;
        r.capability = std::move(cap);
        return r;
    }
    
    static CommandResolution ambiguous(std::vector<std::string> cands, std::string diag) {
        CommandResolution r;
        r.status = ResolutionStatus::kAmbiguous;
        r.candidates = std::move(cands);
        r.diagnostic = std::move(diag);
        return r;
    }
    
    static CommandResolution unknown_verb(std::string verb) {
        CommandResolution r;
        r.status = ResolutionStatus::kUnknownVerb;
        r.diagnostic = "unknown command: " + verb;
        return r;
    }
    
    static CommandResolution unknown_target(std::string target) {
        CommandResolution r;
        r.status = ResolutionStatus::kUnknownTarget;
        r.diagnostic = "target not found: " + target;
        return r;
    }
};

struct ExecutionPlanStep {
    std::string id;
    SemanticKind kind{SemanticKind::QUERY};
    CapabilityReference capability;
    std::optional<TargetReference> target;
    std::vector<Argument> arguments;
    std::vector<Qualifier> qualifiers;
    std::optional<std::string> expected_effect;
    bool requires_verification{false};
};

struct ExecutionPlan {
    std::string id;
    CommandIntent original_intent;
    CapabilityReference capability;
    ScopeContext scope{ScopeContext::USER};
    std::vector<ExecutionPlanStep> steps;
    bool supports_rollback{false};
    std::optional<std::string> rollback_description;
    std::vector<std::string> verification_steps;
    
    static ExecutionPlan make(const CommandIntent& intent, CapabilityReference cap) {
        ExecutionPlan plan;
        plan.id = intent.id;
        plan.original_intent = intent;
        plan.capability = std::move(cap);
        plan.scope = intent.scope;
        return plan;
    }
};

struct CommandResult {
    core::SemanticStatus status{core::SemanticStatus::kUnknown};
    bool changed{false};
    bool verified{false};
    std::vector<core::Evidence> evidence;
    std::optional<std::string> output_value;
    std::chrono::milliseconds elapsed_ms{0};
    std::optional<core::Error> error;
    
    static CommandResult success(bool ch = true, bool ver = true) {
        CommandResult r;
        r.status = core::SemanticStatus::kSuccess;
        r.changed = ch;
        r.verified = ver;
        return r;
    }
    
    static CommandResult no_change() {
        CommandResult r;
        r.status = core::SemanticStatus::kSuccess;
        r.changed = false;
        r.verified = true;
        return r;
    }
    
    static CommandResult failure(std::string code, std::string message) {
        CommandResult r;
        r.status = core::SemanticStatus::kFailure;
        r.error = core::Error{std::move(code), std::move(message)};
        return r;
    }
    
    static CommandResult unknown(std::string message) {
        CommandResult r;
        r.status = core::SemanticStatus::kUnknown;
        r.error = core::Error{"E_UNKNOWN", std::move(message)};
        return r;
    }
    
    bool is_success() const { return status == core::SemanticStatus::kSuccess && verified; }
};

namespace error {
    constexpr const char* kUnknownVerb = "E_UNKNOWN_VERB";
    constexpr const char* kUnknownTarget = "E_UNKNOWN_TARGET";
    constexpr const char* kAmbiguous = "E_AMBIGUOUS_RESOLUTION";
    constexpr const char* kInvalidScope = "E_INVALID_SCOPE";
    constexpr const char* kMissingRequired = "E_MISSING_REQUIRED_ARGUMENT";
    constexpr const char* kExecutionFailed = "E_EXECUTION_FAILED";
    constexpr const char* kVerificationFailed = "E_VERIFICATION_FAILED";
}

struct CommandMetadata {
    std::string name;
    std::vector<std::string> aliases;
    SemanticKind kind{SemanticKind::QUERY};
    SideEffectClass side_effect{SideEffectClass::NONE};
    std::optional<std::string> subject_type;
    bool requires_target{false};
    size_t min_targets{1};
    size_t max_targets{1};
    
    struct ArgumentSpec {
        std::string name;
        bool required{false};
        std::optional<std::string> type_hint;
    };
    std::vector<ArgumentSpec> arguments;
    std::vector<std::string> qualifiers;
    std::optional<CapabilityReference> mapped_capability;
    std::string summary;
    std::string long_description;
    std::vector<std::string> examples;
};

class CommandRegistry {
public:
    void register_command(CommandMetadata meta) {
        commands_[meta.name] = std::move(meta);
    }
    
    std::optional<CommandMetadata> find(std::string_view name) const {
        auto it = commands_.find(std::string{name});
        if (it == commands_.end()) return std::nullopt;
        return it->second;
    }
    
    std::vector<CommandMetadata> all() const {
        std::vector<CommandMetadata> result;
        for (const auto& [name, cmd] : commands_) {
            result.push_back(cmd);
        }
        std::sort(result.begin(), result.end(),
                  [](const CommandMetadata& a, const CommandMetadata& b) { return a.name < b.name; });
        return result;
    }

private:
    std::map<std::string, CommandMetadata> commands_;
};

class CommandBuilder {
public:
    CommandBuilder() : intent_(make_default_intent()) {}
    
    CommandBuilder& with_kind(SemanticKind kind) {
        intent_.semantic_kind = kind;
        return *this;
    }
    
    CommandBuilder& with_verb(std::string verb) {
        intent_.verb = std::move(verb);
        return *this;
    }
    
    CommandBuilder& with_subject(std::string k, std::optional<std::string> id,
                                  std::optional<std::string> n, std::optional<std::string> p) {
        intent_.subject.kind = std::move(k);
        intent_.subject.id = std::move(id);
        intent_.subject.name = std::move(n);
        intent_.subject.path = std::move(p);
        return *this;
    }
    
    CommandBuilder& with_target(std::string k, std::optional<std::string> id,
                                 std::optional<std::string> n, std::optional<std::string> p) {
        TargetReference t;
        t.kind = std::move(k);
        t.id = std::move(id);
        t.name = std::move(n);
        t.path = std::move(p);
        intent_.targets.push_back(t);
        return *this;
    }
    
    CommandBuilder& with_argument(std::string name, std::string value) {
        intent_.arguments.emplace_back(Argument::required_arg(std::move(name), std::move(value)));
        return *this;
    }
    
    CommandBuilder& with_qualifier(std::string n, std::optional<std::string> v = {}) {
        if (v.has_value()) {
            intent_.qualifiers.emplace_back(Qualifier::with_value(std::move(n), std::move(*v)));
        } else {
            intent_.qualifiers.emplace_back(Qualifier::flag(std::move(n)));
        }
        return *this;
    }
    
    CommandBuilder& with_scope(ScopeContext scope) {
        intent_.scope = scope;
        return *this;
    }
    
    CommandIntent build() {
        CommandIntent result = std::move(intent_);
        intent_ = make_default_intent();
        return result;
    }

private:
    static CommandIntent make_default_intent() {
        CommandIntent intent;
        intent.id = "cmd-" + std::to_string(std::chrono::system_clock::now().time_since_epoch().count());
        intent.semantic_kind = SemanticKind::QUERY;
        intent.scope = ScopeContext::USER;
        return intent;
    }
    
    CommandIntent intent_;
};

}  // namespace rebuntu::command