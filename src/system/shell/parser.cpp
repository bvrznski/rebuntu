// rebuntu::shell::parser — Shell Command Parser Implementation (Phase 6.4)
// 
// Qualifiers & Modifiers support added in Phase 6.4

#include "parser.hpp"
#include <algorithm>
#include <cctype>

namespace rebuntu::shell::parser {

// ============================================================================
// tokenize — Split input string into tokens respecting quotes
// ============================================================================

std::vector<std::string> tokenize(std::string_view input) {
    std::vector<std::string> tokens;
    std::string current_token;
    bool in_single_quote = false;
    bool in_double_quote = false;
    
    for (size_t i = 0; i < input.size(); ++i) {
        char c = input[i];
        
        if (!in_single_quote && !in_double_quote) {
            // Whitespace separates tokens
            if (std::isspace(static_cast<unsigned char>(c))) {
                if (!current_token.empty()) {
                    tokens.push_back(current_token);
                    current_token.clear();
                }
            } else if (c == '\'') {
                in_single_quote = true;
            } else if (c == '"') {
                in_double_quote = true;
            } else {
                current_token += c;
            }
        } else if (in_single_quote) {
            if (c == '\'') {
                in_single_quote = false;
            } else {
                current_token += c;
            }
        } else if (in_double_quote) {
            if (c == '"') {
                in_double_quote = false;
            } else {
                current_token += c;
            }
        }
    }
    
    // Add final token
    if (!current_token.empty()) {
        tokens.push_back(current_token);
    }
    
    return tokens;
}

// ============================================================================
// parse_duration — Parse duration string (e.g., "30s", "5m")
// ============================================================================

std::chrono::milliseconds parse_duration(std::string_view value) {
    using namespace std::chrono_literals;
    
    if (value.empty()) {
        return 30000ms;  // Default 30 seconds
    }
    
    size_t len = value.length();
    if (len == 0) {
        return 30000ms;
    }
    
    // Parse numeric part
    std::string num_str;
    size_t i = 0;
    while (i < len && (std::isdigit(value[i]) || value[i] == '.')) {
        num_str += value[i];
        i++;
    }
    
    if (num_str.empty()) {
        return 30000ms;  // Default on parse failure
    }
    
    double numeric_value = std::stod(num_str);
    
    // Parse unit part
    std::string unit;
    if (i < len) {
        unit = std::string(value.substr(i));
    } else {
        unit = "s";
    }
    
    if (unit == "s" || unit == "sec" || unit == "seconds") {
        return static_cast<std::chrono::milliseconds>(
            static_cast<int64_t>(numeric_value * 1000)
        );
    } else if (unit == "m" || unit == "min" || unit == "minutes") {
        return static_cast<std::chrono::milliseconds>(
            static_cast<int64_t>(numeric_value * 60000)
        );
    } else if (unit == "h" || unit == "hour" || unit == "hours") {
        return static_cast<std::chrono::milliseconds>(
            static_cast<int64_t>(numeric_value * 3600000)
        );
    } else if (unit == "ms" || unit == "msec" || unit == "milliseconds") {
        return static_cast<std::chrono::milliseconds>(
            static_cast<int64_t>(numeric_value)
        );
    }
    
    // Default to seconds
    return static_cast<std::chrono::milliseconds>(
        static_cast<int64_t>(numeric_value * 1000)
    );
}

// ============================================================================
// parse_qualifiers — Extract qualifier options from argv
// ============================================================================

size_t parse_qualifiers(
    const std::vector<std::string>& argv,
    size_t start_idx,
    QualifierRegistry& registry,
    QualifierBundle& out_bundle,
    ParseError& out_error
) {
    size_t idx = start_idx;
    
    while (idx < argv.size()) {
        const std::string& token = argv[idx];
        
        // Check if this is an option (starts with -- or -)
        if (token.size() > 1 && token[0] == '-') {
            // Extract qualifier name from --name=value, --name value, or --name
            std::string qualifier_name;
            std::optional<std::string> value;
            
            size_t eq_pos = token.find('=');
            if (eq_pos != std::string::npos) {
                qualifier_name = token.substr(2, eq_pos - 2);  // Skip --
                value = token.substr(eq_pos + 1);
            } else {
                qualifier_name = token.substr(2);  // Skip --
                
                // Check if next token is a value
                if (idx + 1 < argv.size() && !argv[idx + 1].empty() && argv[idx + 1][0] != '-') {
                    idx++;
                    value = argv[idx];
                }
            }
            
            // Look up qualifier definition
            auto def_opt = registry.find(qualifier_name);
            if (!def_opt.has_value()) {
                out_error.message = "unknown qualifier: " + qualifier_name;
                out_error.token_index = static_cast<int>(idx);
                return idx;  // Stop parsing, return error
            }
            
            // Apply qualifier based on type
            if (qualifier_name == "dry-run" || qualifier_name == "--plan") {
                out_bundle.execution.dry_run = true;
                out_bundle.execution.verify = false;  // No verification in dry-run
            } else if (qualifier_name == "force") {
                out_bundle.execution.force = true;
            } else if (qualifier_name == "verify") {
                out_bundle.execution.verify = value.has_value() 
                    ? (value.value() != "false" && value.value() != "0")
                    : true;
            } else if (qualifier_name == "timeout") {
                if (!value.has_value()) {
                    out_error.message = "timeout requires a duration value";
                    return idx;
                }
                out_bundle.execution.timeout = parse_duration(value.value());
            } else if (qualifier_name == "all") {
                out_bundle.selection.all = true;
            } else if (qualifier_name == "current") {
                out_bundle.selection.current = true;
            } else if (qualifier_name == "recursive" || qualifier_name == "recurse") {
                out_bundle.selection.recursive = true;
            } else if (qualifier_name == "quiet") {
                out_bundle.output.quiet = true;
            } else if (qualifier_name == "verbose") {
                out_bundle.output.verbose = true;
            }
            
            idx++;
        } else {
            // Not an option, stop parsing qualifiers
            break;
        }
    }
    
    return idx;
}

// ============================================================================
// apply_qualifiers_to_intent — Apply parsed qualifiers to CommandIntent
// ============================================================================

void apply_qualifiers_to_intent(
    const QualifierBundle& bundle,
    CommandIntent& intent
) {
    // Map execution qualifier to ExecutionPolicy
    intent.execution_policy.dry_run = bundle.execution.dry_run;
    intent.execution_policy.verify = bundle.execution.verify;
    intent.execution_policy.max_attempts = bundle.execution.max_attempts;
    intent.execution_policy.timeout = bundle.execution.timeout;
    
    // Add selection qualifiers to intent's qualifier map
    if (bundle.selection.all) {
        intent.qualifiers["all"] = "true";
    }
    if (bundle.selection.current) {
        intent.qualifiers["current"] = "true";
    }
    if (bundle.selection.recursive) {
        intent.qualifiers["recursive"] = "true";
    }
    
    // Add output qualifiers
    if (bundle.output.quiet) {
        intent.qualifiers["quiet"] = "true";
    }
    if (bundle.output.verbose) {
        intent.qualifiers["verbose"] = "true";
    }
}

// ============================================================================
// parse_argv — Parse command line arguments into CommandIntent
// ============================================================================

CommandResult parse_argv(
    const std::vector<std::string>& argv,
    const CommandRegistry& registry,
    CommandIntent& out_intent,
    ParseError& out_error
) {
    // Clear output
    out_intent = CommandIntent{};
    
    if (argv.empty()) {
        out_error.message = "no command provided";
        return CommandResult::failure(error::kUnknownVerb, "no command provided");
    }
    
    // argv[0] is program name, commands start at argv[1]
    std::vector<std::string> args;
    for (size_t i = 1; i < argv.size(); ++i) {
        args.push_back(argv[i]);
    }
    
    if (args.empty()) {
        out_error.message = "no command provided";
        return CommandResult::failure(error::kUnknownVerb, "no command provided");
    }
    
    // Build default qualifier bundle and registry
    QualifierRegistry qual_registry;
    qual_registry.register_qualifier({
        .name = "dry-run",
        .aliases = {"--plan", "--check"},
        .kind = QualifierKind::kExecution,
        .summary = "Preview changes without applying them"
    });
    
    qual_registry.register_qualifier({
        .name = "force",
        .aliases = {},
        .kind = QualifierKind::kExecution,
        .summary = "Bypass safety checks (use with caution)"
    });
    
    qual_registry.register_qualifier({
        .name = "verify",
        .aliases = {},
        .kind = QualifierKind::kExecution,
        .accepts_value = true,
        .summary = "Enable/disable postcondition verification"
    });
    
    qual_registry.register_qualifier({
        .name = "timeout",
        .aliases = {},
        .kind = QualifierKind::kExecution,
        .accepts_value = true,
        .summary = "Set operation timeout"
    });
    
    qual_registry.register_qualifier({
        .name = "all",
        .aliases = {},
        .kind = QualifierKind::kSelection,
        .summary = "Apply to all matching targets"
    });
    
    qual_registry.register_qualifier({
        .name = "current",
        .aliases = {},
        .kind = QualifierKind::kSelection,
        .summary = "Use current context when no target specified"
    });
    
    qual_registry.register_qualifier({
        .name = "recursive",
        .aliases = {"recurse"},
        .kind = QualifierKind::kSelection,
        .summary = "Apply recursively to sub-entities"
    });
    
    qual_registry.register_qualifier({
        .name = "quiet",
        .aliases = {},
        .kind = QualifierKind::kOutput,
        .summary = "Suppress output (for scripting)"
    });
    
    qual_registry.register_qualifier({
        .name = "verbose",
        .aliases = {"-v"},
        .kind = QualifierKind::kOutput,
        .summary = "Enable detailed diagnostics"
    });
    
    // First, parse qualifiers to extract them from the argument list
    QualifierBundle qualifier_bundle;
    size_t qual_end_idx = 0;
    ParseError qual_error{};
    bool has_qualifiers = false;
    
    for (size_t i = 0; i < args.size(); ++i) {
        if (!args[i].empty() && args[i][0] == '-' && args[i].size() > 1) {
            qual_end_idx = parse_qualifiers(args, i, qual_registry, qualifier_bundle, qual_error);
            has_qualifiers = true;
            break;  // Qualifiers typically appear before verb/target
        }
    }
    
    // First non-option token is the verb/predicate
    size_t arg_idx = has_qualifiers ? qual_end_idx : 0;
    std::string first_token;
    
    while (arg_idx < args.size()) {
        if (args[arg_idx] == "--help" || args[arg_idx] == "-h") {
            out_error.message = "help flag found during parsing";
            return CommandResult::success();  // Help is a valid request
        } else if (args[arg_idx].empty() || args[arg_idx][0] != '-') {
            first_token = args[arg_idx];
            break;
        }
        arg_idx++;
    }
    
    if (first_token.empty()) {
        out_error.message = "no command provided";
        return CommandResult::failure(error::kUnknownVerb, "no command provided");
    }
    
    // Look up in registry
    auto cmd_meta_opt = registry.find(first_token);
    if (!cmd_meta_opt.has_value()) {
        out_error.message = "unknown command: " + first_token;
        return CommandResult::failure(error::kUnknownVerb, "unknown command: " + first_token);
    }
    
    // Build intent from parsed arguments
    out_intent.id = std::to_string(std::chrono::system_clock::now().time_since_epoch().count());
    out_intent.verb = first_token;
    
    if (cmd_meta_opt->kind == IntentKind::kPredicate) {
        out_intent.kind = IntentKind::kPredicate;
        // Predicate form: "installed foo" -> verb="installed", predicate="installed?"
    } else {
        out_intent.kind = IntentKind::kVerb;
    }
    
    out_intent.subject = cmd_meta_opt->subject_type;
    
    // Apply qualifiers to intent
    apply_qualifiers_to_intent(qualifier_bundle, out_intent);
    
    return CommandResult::success();
}

// ============================================================================
// resolve — Resolve a parsed intent to canonical capabilities
// ============================================================================

CommandResolution resolve(
    const CommandIntent& intent,
    const CommandRegistry& registry
) {
    CommandResolution resolution;
    
    // Validate kind
    if (intent.kind == IntentKind::kUnknown) {
        resolution.status = ResolutionStatus::kInvalid;
        resolution.diagnostic = "command intent has unknown type";
        return resolution;
    }
    
    // For verbs, look up the mapped operation
    auto cmd_meta_opt = registry.find(intent.verb);
    if (!cmd_meta_opt.has_value()) {
        resolution.status = ResolutionStatus::kUnknownVerb;
        resolution.diagnostic = "unknown verb: " + intent.verb;
        return resolution;
    }
    
    const auto& meta = *cmd_meta_opt;
    
    // Check subject
    if (meta.subject_type.has_value() && !intent.subject.has_value()) {
        // Try to infer from command metadata
        resolution.resolved_scope = ScopeContext::SYSTEM;  // Default for most commands
        return resolution;
    }
    
    // Map to canonical operation
    if (meta.mapped_operation.has_value()) {
        resolution.operation_id = meta.mapped_operation.value();
    } else {
        // No direct mapping - this is a query or simple command
        resolution.status = ResolutionStatus::kSuccess;
        resolution.diagnostic = "command does not map to canonical operation";
        return resolution;
    }
    
    resolution.status = ResolutionStatus::kSuccess;
    return resolution;
}

}  // namespace rebuntu::shell::parser