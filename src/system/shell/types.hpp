// rebuntu::shell — Shell Language Foundation Types (Phase 6.0)
//
// This module defines the typed intermediate representation and vocabulary
// for Rebuntu's shell language:
//
//   - CommandIntent: Typed command request from shell
//   - Verb/Predicate classification
//   - Subject/target resolution
//   - Scope and privilege context
//
// Design Philosophy:
//   * Shell is a PRESENTATION SURFACE, not an independent runtime
//   * Typed IR ensures deterministic parsing before execution
//   * Resolution happens BEFORE execution (no implicit provider logic)
//   * Evidence and verification are first-class result elements

#pragma once

#include "../core/contracts.hpp"
#include <string>
#include <string_view>
#include <vector>
#include <map>
#include <optional>
#include <chrono>
#include <filesystem>

namespace rebuntu::shell {

// ============================================================================
// IntentKind — Category of command intent
// ============================================================================

enum class IntentKind {
    kUnknown,        // Not yet determined or invalid
    kVerb,           // Action verb (install, remove, restart)
    kPredicate,      // Query predicate (installed?, running?)
    kQuery,          // Informational query (list, status)
    kWorkflow,       // Multi-step workflow (upgrade, migrate)
};

inline std::string to_string(IntentKind k) {
    switch (k) {
        case IntentKind::kUnknown:   return "unknown";
        case IntentKind::kVerb:      return "verb";
        case IntentKind::kPredicate: return "predicate";
        case IntentKind::kQuery:     return "query";
        case IntentKind::kWorkflow:  return "workflow";
    }
    return "unknown";
}

// ============================================================================
// SideEffectClass — Categorization of side effects for safety
// ============================================================================

enum class SideEffectClass {
    NONE,       // No observable effect (pure read/query)
    OBSERVATION,// Reads state but doesn't change it
    MUTATING,   // Changes system state (idempotent or not)
    PRIVILEGED, // Requires elevated privilege
    DESTRUCTIVE,// Irreversible or hard-to-reverse
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

// ============================================================================
// ScopeContext — Semantic scope of a command
//
// Distinct from effective UID; determines what targets are accessible.
// ============================================================================

enum class ScopeContext {
    USER,      // User-level scope (home directory, user services)
    SYSTEM,    // System-level scope (global state, system services)
    SESSION,   // Session-scoped (current login session)
    RUNTIME,   // Runtime-scoped (process-local)
};

inline std::string to_string(ScopeContext s) {
    switch (s) {
        case ScopeContext::USER:    return "user";
        case ScopeContext::SYSTEM:  return "system";
        case ScopeContext::SESSION: return "session";
        case ScopeContext::RUNTIME: return "runtime";
    }
    return "unknown";
}

// ============================================================================
// ExecutionPolicy — User-controllable execution hints
// ============================================================================

struct ExecutionPolicy {
    bool dry_run = false;          // Don't actually execute, just plan
    bool verify = true;           // Verify postconditions (where applicable)
    int max_attempts = 1;         // Maximum retry attempts
    std::chrono::milliseconds timeout{30000};  // Operation timeout
    
    static ExecutionPolicy default_policy() {
        return ExecutionPolicy{};
    }
    
    static ExecutionPolicy dry_run_only() {
        ExecutionPolicy p;
        p.dry_run = true;
        p.verify = false;  // No verification in dry-run
        return p;
    }
};

// ============================================================================
// CommandIntent — Typed command intent from shell
//
// This is the canonical IR that all shell commands must produce after parsing.
// ============================================================================

struct CommandIntent {
    std::string id;                          // Unique intent ID (UUID-like)
    
    IntentKind kind{IntentKind::kUnknown};  // Category of this intent
    
    // Action description
    std::string verb;                        // e.g., "install", "remove"
    std::optional<std::string> predicate;    // for predicates, e.g., "installed?", "running?"
    
    // Target identification
    std::optional<std::string> subject;      // Subject type: package, service, file, etc.
    std::optional<std::string> target;       // Concrete target identity
    
    // Parameters (positional arguments)
    std::vector<std::pair<std::string, std::string>> arguments;
    
    // Qualifiers/modifiers
    std::map<std::string, std::string> qualifiers;
    
    // Context
    ScopeContext scope{ScopeContext::USER};
    std::optional<std::string> caller_id;     // For authorization audit
    
    // Execution hints
    ExecutionPolicy execution_policy{};
    
    // Source information (for debugging/explain)
    std::optional<std::string> source_context;
    std::optional<int> source_line;
};

// ============================================================================
// ResolutionStatus — Status of command resolution
// ============================================================================

enum class ResolutionStatus {
    kSuccess,       // Intent fully resolved to a capability
    kAmbiguous,     // Multiple valid resolutions exist
    kUnknownVerb,   // Verb not recognized
    kUnknownSubject,// Subject type not recognized
    kUnknownTarget, // Target identity cannot be resolved
    kCollision,     // Collision with native shell command
    kInvalid,       // Intent has semantic errors (missing target, invalid scope)
};

inline std::string to_string(ResolutionStatus s) {
    switch (s) {
        case ResolutionStatus::kSuccess:    return "success";
        case ResolutionStatus::kAmbiguous:  return "ambiguous";
        case ResolutionStatus::kUnknownVerb:return "unknown_verb";
        case ResolutionStatus::kUnknownSubject:return "unknown_subject";
        case ResolutionStatus::kUnknownTarget:return "unknown_target";
        case ResolutionStatus::kCollision:  return "collision";
        case ResolutionStatus::kInvalid:    return "invalid";
    }
    return "unknown";
}

struct CommandResolution {
    ResolutionStatus status{ResolutionStatus::kSuccess};
    
    // If successful, the resolved operation
    std::optional<std::string> operation_id;   // e.g., "package.install"
    
    // Resolution details for debugging/explain
    std::vector<std::string> candidates;       // Multiple possible resolutions (for ambiguity)
    std::string diagnostic;                    // Human-readable explanation
    
    // Contextual information
    ScopeContext resolved_scope{ScopeContext::USER};
};

// ============================================================================
// PredicateResult — Result of predicate evaluation
//
// Predicates must distinguish TRUE, FALSE, and UNKNOWN clearly.
// ============================================================================

struct PredicateResult {
    core::SemanticStatus status{core::SemanticStatus::kUnknown};
    
    // For predicates: the evaluated truth value
    std::optional<bool> is_true;      // true = condition holds
                                      // false = condition does not hold
                                      // nullopt = unknown/cannot determine
    
    // Evidence supporting the result
    std::vector<core::Evidence> evidence;
    
    // Error information if acquisition failed
    std::optional<core::Error> error;
    
    static PredicateResult true_result() {
        PredicateResult r;
        r.status = core::SemanticStatus::kSuccess;
        r.is_true = true;
        return r;
    }
    
    static PredicateResult false_result() {
        PredicateResult r;
        r.status = core::SemanticStatus::kFailure;  // Condition not met
        r.is_true = false;
        return r;
    }
    
    static PredicateResult unknown(std::string message) {
        PredicateResult r;
        r.status = core::SemanticStatus::kUnknown;
        r.is_true = std::nullopt;
        r.error = core::Error{"E_UNKNOWN", std::move(message)};
        return r;
    }
};

// ============================================================================
// CommandMetadata — Machine-readable command documentation
//
// Used by help, completion, and schema introspection.
// ============================================================================

struct CommandMetadata {
    std::string canonical_name;              // Primary name: "install"
    std::vector<std::string> aliases;        // Alternative names: ["add", "ensure"]
    
    IntentKind kind{IntentKind::kUnknown};
    
    std::optional<std::string> subject_type; // What this acts upon: "package", "service"
    bool target_required{false};             // Must a target be specified?
    size_t min_targets{1};                   // Minimum number of targets
    size_t max_targets{1};                   // Maximum number of targets
    
    // Options (named flags)
    std::vector<std::pair<std::string, std::string>> options;  // name, description
    
    // Qualifiers (positional modifiers)
    std::vector<std::string> qualifiers;
    
    SideEffectClass side_effect{SideEffectClass::NONE};
    
    // Scope support
    bool supports_user_scope{false};
    bool supports_system_scope{true};  // Most operations need system scope
    
    // Safety metadata
    bool requires_authorization{false};
    bool is_destructive{false};
    
    // Mapped capability (if applicable)
    std::optional<std::string> mapped_operation;
    
    std::string summary;                     // One-line description
    std::string long_description;            // Detailed help text
    
    // Examples for help
    std::vector<std::string> examples;
};

// ============================================================================
// CommandRegistry — Registry of available shell commands
//
// This is a DATA structure: no runtime behavior, just metadata lookup.
// ============================================================================

class CommandRegistry {
public:
    void register_command(CommandMetadata meta) {
        commands_[meta.canonical_name] = std::move(meta);
    }
    
    // Find by canonical name or alias
    std::optional<CommandMetadata> find(std::string_view name) const {
        auto it = commands_.find(std::string{name});
        if (it == commands_.end()) return std::nullopt;
        return it->second;
    }
    
    // Find all matching a prefix (for abbreviation resolution)
    std::vector<std::pair<std::string, CommandMetadata>> find_by_prefix(std::string_view prefix) const {
        std::vector<std::pair<std::string, CommandMetadata>> result;
        for (const auto& [name, cmd] : commands_) {
            if (name.substr(0, prefix.size()) == prefix) {
                result.emplace_back(name, cmd);
            }
        }
        std::sort(result.begin(), result.end(),
                  [](const auto& a, const auto& b) { return a.first < b.first; });
        return result;
    }
    
    // Get all commands sorted by name
    std::vector<CommandMetadata> all() const {
        std::vector<CommandMetadata> result;
        for (const auto& [name, cmd] : commands_) {
            result.push_back(cmd);
        }
        std::sort(result.begin(), result.end(),
                  [](const CommandMetadata& a, const CommandMetadata& b) { return a.canonical_name < b.canonical_name; });
        return result;
    }

private:
    std::map<std::string, CommandMetadata> commands_;
};

// ============================================================================
// OutputMode — Result rendering mode
// ============================================================================

enum class OutputMode {
    AUTO,        // Auto-detect based on TTY
    HUMAN,       // Human-readable prose
    STRUCTURED,  // Machine-readable JSON/JSONL
    SILENT,      // No output (for scripting)
};

inline std::string to_string(OutputMode m) {
    switch (m) {
        case OutputMode::AUTO:     return "auto";
        case OutputMode::HUMAN:    return "human";
        case OutputMode::STRUCTURED:return "structured";
        case OutputMode::SILENT:   return "silent";
    }
    return "unknown";
}

// ============================================================================
// CommandResult — Result of command execution
//
// This is the canonical structured result that all commands produce.
// ============================================================================

struct CommandResult {
    core::SemanticStatus status{core::SemanticStatus::kUnknown};
    
    // For non-predicate commands, the operation result
    std::optional<core::Outcome> outcome;
    
    // Evidence supporting the result
    std::vector<core::Evidence> evidence;
    
    // Timing information
    std::chrono::milliseconds elapsed_ms{0};
    
    static CommandResult success() {
        CommandResult r;
        r.status = core::SemanticStatus::kSuccess;
        return r;
    }
    
    static CommandResult failure(std::string code, std::string message) {
        CommandResult r;
        r.status = core::SemanticStatus::kFailure;
        r.outcome = core::Outcome::failure(std::move(code), std::move(message));
        return r;
    }
    
    static CommandResult unknown(std::string message) {
        CommandResult r;
        r.status = core::SemanticStatus::kUnknown;
        r.outcome = core::Outcome::unknown(std::move(message));
        return r;
    }
};

// ============================================================================
// ShellContext — Session-wide context for shell commands
//
// This is the execution environment that all commands inherit.
// ============================================================================

struct ShellContext {
    std::string session_id;                  // Unique session identifier
    ScopeContext default_scope{ScopeContext::USER};
    OutputMode output_mode{OutputMode::AUTO};
    
    // Current working directory (for relative paths)
    std::optional<std::filesystem::path> cwd;
    
    // User context
    std::optional<int> effective_uid;
    std::optional<int> real_uid;
    
    // Execution constraints
    bool strict_mode{false};  // Fail on ambiguity instead of prompting
    
    static ShellContext make_current();
};

// ============================================================================
// Error codes for shell language
// ============================================================================

namespace error {
    constexpr const char* kUnknownVerb = "E_UNKNOWN_VERB";
    constexpr const char* kUnknownSubject = "E_UNKNOWN_SUBJECT";
    constexpr const char* kAmbiguousTarget = "E_AMBIGUOUS_TARGET";
    constexpr const char* kCollision = "E_COMMAND_COLLISION";
    constexpr const char* kInvalidScope = "E_INVALID_SCOPE";
    constexpr const char* kUnauthorized = "E_UNAUTHORIZED";
    constexpr const char* kExecutionFailed = "E_EXECUTION_FAILED";
    constexpr const char* kVerificationFailed = "E_VERIFICATION_FAILED";
}

}  // namespace rebuntu::shell

namespace std {

template <> struct hash<rebuntu::shell::CommandIntent> {
    size_t operator()(const rebuntu::shell::CommandIntent& intent) const noexcept {
        size_t h = std::hash<std::string>{}(intent.id);
        h ^= std::hash<int>{}(static_cast<int>(intent.kind));
        return h;
    }
};

}  // namespace std