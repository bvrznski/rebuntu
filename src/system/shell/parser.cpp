// rebuntu::shell::parser — Shell Command Parser Implementation (Phase 6.0)

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
    
    // First non-option token is the verb/predicate
    size_t arg_idx = 0;
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
    out_intent.execution_policy = ExecutionPolicy::default_policy();
    
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