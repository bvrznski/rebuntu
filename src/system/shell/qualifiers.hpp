// rebuntu::shell::qualifiers — Qualifiers & Modifiers Taxonomy (Phase 6.4)
//
// This module defines the canonical grammar for command qualifiers and modifiers
// in Rebuntu's shell language:
//
//   Execution qualifiers:     force, dry-run, verify, timeout, max-attempts
//   Selection qualifiers:     all, current, recursive
//   Output qualifiers:        quiet, verbose, output-mode, format
//   Domain-specific modifiers: scope, context, policy-hint
//
// Design Principles:
//   * Qualifiers refine operations without creating combinatorial flag jungle
//   * Modifiers are distinct from options, targets, scope, policy selection
//   * Type-safe qualifier parsing and validation
//   * No qualifier bypasses Operation schemas or authorization

#pragma once

#include "types.hpp"
#include <string>
#include <vector>
#include <map>
#include <set>
#include <optional>
#include <chrono>

namespace rebuntu::shell {

// ============================================================================
// Forward declarations
// ============================================================================

struct ParseError;

// ============================================================================
// QualifierKind — Category of qualifier/modifier
// ============================================================================

enum class QualifierKind {
    kUnknown,           // Not a recognized qualifier
    kExecution,         // Execution behavior control
    kSelection,         // Target selection refinement
    kOutput,            // Result rendering control
    kDomainSpecific,    // Domain-specific modifier
};

inline std::string to_string(QualifierKind k) {
    switch (k) {
        case QualifierKind::kUnknown:       return "unknown";
        case QualifierKind::kExecution:     return "execution";
        case QualifierKind::kSelection:     return "selection";
        case QualifierKind::kOutput:        return "output";
        case QualifierKind::kDomainSpecific:return "domain-specific";
    }
    return "unknown";
}

// ============================================================================
// ExecutionQualifier — Control execution behavior
// ============================================================================

struct ExecutionQualifier {
    // Dry-run mode: plan but don't execute
    bool dry_run = false;
    
    // Verify postconditions after execution
    bool verify = true;
    
    // Maximum retry attempts for idempotent operations
    int max_attempts = 1;
    
    // Operation timeout in milliseconds
    std::chrono::milliseconds timeout{30000};
    
    // Force mode: bypass safety checks (dangerous)
    bool force = false;
    
    static ExecutionQualifier default_() {
        return ExecutionQualifier{};
    }
    
    static ExecutionQualifier dry_run_only() {
        ExecutionQualifier q;
        q.dry_run = true;
        q.verify = false;  // No verification in dry-run
        return q;
    }
};

// ============================================================================
// SelectionQualifier — Refine target selection
// ============================================================================

struct SelectionQualifier {
    // Select all matching targets (instead of first)
    bool all = false;
    
    // Use current context when no explicit target given
    bool current = false;
    
    // Apply recursively to sub-entities
    bool recursive = false;
    
    static SelectionQualifier default_() {
        return SelectionQualifier{};
    }
};

// ============================================================================
// OutputQualifier — Control result rendering
// ============================================================================

struct OutputQualifier {
    // Silent mode: no output (for scripting)
    bool quiet = false;
    
    // Verbose mode: detailed diagnostics
    bool verbose = false;
    
    static OutputQualifier default_() {
        return OutputQualifier{};
    }
};

// ============================================================================
// ScopeQualifier — Explicit scope selection (user/system/session/runtime)
//
// These qualifiers allow users to explicitly select which scope a command
// operates in, overriding contextual defaults.
// ============================================================================

struct ScopeQualifier {
    // Explicit scope selection
    std::optional<ScopeContext> explicit_scope;
    
    // When ambiguous targets exist, require disambiguation
    bool require_explicit_scope = false;
    
    static ScopeQualifier default_() {
        return ScopeQualifier{};
    }
};

// ============================================================================
// DomainSpecificModifier — Domain-specific refinement
// ============================================================================

struct DomainSpecificModifier {
    // Policy hint to influence resolution strategy
    std::optional<std::string> policy_hint;
    
    // Context path for relative operations
    std::optional<std::string> context_path;
    
    static DomainSpecificModifier default_() {
        return DomainSpecificModifier{};
    }
};

// ============================================================================
// QualifierBundle — All qualifiers combined
// ============================================================================

struct QualifierBundle {
    ExecutionQualifier execution;
    SelectionQualifier selection;
    OutputQualifier output;
    ScopeQualifier scope;           // Explicit scope selection
    DomainSpecificModifier domain_specific;
    
    static QualifierBundle default_() {
        return QualifierBundle{};
    }
};

// ============================================================================
// QualifierDefinition — Metadata about a recognized qualifier
// ============================================================================

struct QualifierDefinition {
    std::string name;              // Canonical name: "dry-run"
    std::vector<std::string> aliases;  // Alternative names: ["--plan"]
    
    QualifierKind kind;
    
    // Value requirements
    bool accepts_value = false;    // Does --opt=value or --opt value?
    std::optional<std::string> expected_format;  // e.g., "duration", "path"
    
    // Side effects classification
    SideEffectClass side_effect{SideEffectClass::NONE};
    
    // Whether this qualifier requires elevated privilege
    bool requires_authorization = false;
    
    // Description for help text
    std::string summary;
    std::string long_description;
};

// ============================================================================
// ScopeQualifierRegistry — Registry of scope-related qualifier definitions
// ============================================================================

class ScopeQualifierRegistry {
public:
    // Get all scope-related qualifier definitions
    static std::vector<QualifierDefinition> get_scope_qualifiers() {
        return {
            {
                .name = "scope",
                .aliases = {},
                .kind = QualifierKind::kDomainSpecific,
                .accepts_value = true,
                .expected_format = "user|system|session|runtime",
                .summary = "Explicitly select scope: user, system, session, or runtime"
            },
        };
    }
    
    // Find scope-related qualifier by name
    static std::optional<QualifierDefinition> find_scope_qualifier(std::string_view name) {
        for (const auto& def : get_scope_qualifiers()) {
            if (def.name == name || 
                std::find(def.aliases.begin(), def.aliases.end(), name) != def.aliases.end()) {
                return def;
            }
        }
        return std::nullopt;
    }
    
    // Validate scope value
    static bool is_valid_scope_value(std::string_view value) {
        return value == "user" || value == "system" || 
               value == "session" || value == "runtime";
    }
    
    // Parse scope string to ScopeContext enum
    static std::optional<ScopeContext> parse_scope(std::string_view value) {
        if (value == "user") return ScopeContext::USER;
        if (value == "system") return ScopeContext::SYSTEM;
        if (value == "session") return ScopeContext::SESSION;
        if (value == "runtime") return ScopeContext::RUNTIME;
        return std::nullopt;
    }
    
    // Format scope context as string
    static std::string to_scope_string(ScopeContext ctx) {
        switch (ctx) {
            case ScopeContext::USER: return "user";
            case ScopeContext::SYSTEM: return "system";
            case ScopeContext::SESSION: return "session";
            case ScopeContext::RUNTIME: return "runtime";
        }
        return "unknown";
    }
};

// ============================================================================
// QualifierRegistry — Registry of recognized qualifiers
// ============================================================================

class QualifierRegistry {
public:
    void register_qualifier(QualifierDefinition def) {
        qualifiers_[def.name] = std::move(def);
    }
    
    // Find by canonical name or alias
    std::optional<QualifierDefinition> find(std::string_view name) const {
        auto it = qualifiers_.find(std::string{name});
        if (it == qualifiers_.end()) return std::nullopt;
        return it->second;
    }
    
    // Get all qualifiers sorted by kind and name
    std::vector<QualifierDefinition> all() const {
        std::vector<QualifierDefinition> result;
        for (const auto& [name, def] : qualifiers_) {
            result.push_back(def);
        }
        // Sort by kind then name
        std::sort(result.begin(), result.end(),
                  [](const QualifierDefinition& a, const QualifierDefinition& b) {
                      if (a.kind != b.kind) return a.kind < b.kind;
                      return a.name < b.name;
                  });
        return result;
    }
    
    // Get qualifiers of a specific kind
    std::vector<QualifierDefinition> by_kind(QualifierKind kind) const {
        auto all_defs = all();
        std::vector<QualifierDefinition> result;
        for (const auto& def : all_defs) {
            if (def.kind == kind) {
                result.push_back(def);
            }
        }
        return result;
    }

private:
    std::map<std::string, QualifierDefinition> qualifiers_;
};

// ============================================================================
// QualifierParser — Parse qualifier tokens from command line
// ============================================================================

class QualifierParser {
public:
    explicit QualifierParser(const QualifierRegistry* registry);
    
    // Parse qualifiers from argv, starting at start_idx
    // Returns the index after the last parsed qualifier
    size_t parse(
        const std::vector<std::string>& argv,
        size_t start_idx,
        QualifierBundle& out_bundle,
        ParseError& out_error
    );
    
    // Parse a single token as a qualifier
    bool parse_token(
        const std::string& token,
        const std::optional<std::string>& value,
        QualifierBundle& bundle,
        ParseError& error
    );

private:
    const QualifierRegistry* registry_;
    
    // Helper to extract value from --name=value format
    std::optional<std::pair<std::string, std::string>> split_name_value(
        std::string_view token
    ) const;
    
    // Helper for duration parsing (e.g., "30s", "5m")
    std::chrono::milliseconds parse_duration(std::string_view value) const;
};

// ============================================================================
// QualifierValidator — Validate qualifier combinations
// ============================================================================

class QualifierValidator {
public:
    // Check if a qualifier bundle is internally consistent
    bool validate(
        const QualifierBundle& bundle,
        ParseError& out_error
    ) const;
    
    // Check if qualifiers are compatible with the command's side effect class
    bool is_compatible(
        const QualifierBundle& bundle,
        SideEffectClass command_side_effect,
        ParseError& out_error
    ) const;

private:
    std::set<std::string> incompatible_pairs_{
        "dry-run+force",      // dry-run should not bypass safety
        "quiet+verbose"       // mutually exclusive output modes
    };
};

// ============================================================================
// Error codes for qualifier parsing
// ============================================================================

namespace error {
    constexpr const char* kUnknownQualifier = "E_UNKNOWN_QUALIFIER";
    constexpr const char* kInvalidQualifierValue = "E_INVALID_QUALIFIER_VALUE";
    constexpr const char* kConflictingQualifiers = "E_CONFLICTING_QUALIFIERS";
    constexpr const char* kMissingQualifierValue = "E_MISSING_QUALIFIER_VALUE";
}

}  // namespace rebuntu::shell