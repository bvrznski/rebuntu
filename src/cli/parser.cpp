// rebuntu::cli::parser — Command Parser Boundary Implementation (Task 6.46)
//
// This module implements the parser boundary where CLI input is converted
// to typed structures. After this point, domain code receives ONLY typed
// structures - no string re-parsing.

#include "parser.hpp"
#include <algorithm>
#include <cctype>
#include <chrono>

#include <system/shell/types.hpp>

namespace rebuntu::cli::parser {

// ============================================================================
// tokenize — Split command line input into tokens
//
// This is lexical tokenization only - no semantic parsing.
// Respects single and double quotes but doesn't interpret meaning.
// ============================================================================

std::vector<std::string> tokenize(std::string_view input) {
    std::vector<std::string> tokens;
    std::string current_token;
    bool in_single_quote = false;
    bool in_double_quote = false;
    
    for (size_t i = 0; i < input.size(); ++i) {
        char c = static_cast<char>(input[i]);
        
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
// parse_argv — Parse command line arguments into typed CommandIntent
//
// This is the parser boundary: argv → CommandIntent.
// 
// After this function, domain execution receives ONLY typed structures.
// No string re-parsing in downstream code.
// ============================================================================

rebuntu::shell::CommandIntent parse_argv(
    const std::vector<std::string>& argv,
    ParseError& out_error
) {
    // Clear output
    rebuntu::shell::CommandIntent result{};
    
    if (argv.empty()) {
        out_error.message = "no command provided";
        out_error.token_index = -1;
        return result;
    }
    
    // argv[0] is program name, commands start at index 1
    size_t arg_idx = 1;
    
    if (arg_idx >= argv.size()) {
        out_error.message = "no command provided";
        out_error.token_index = -1;
        return result;
    }
    
    // First non-flag token is the verb/command
    std::string first_verb;
    
    while (arg_idx < argv.size()) {
        const std::string& token = argv[arg_idx];
        
        // Stop at first non-option (doesn't start with -)
        if (!token.empty() && token[0] != '-') {
            first_verb = token;
            arg_idx++;
            break;
        }
        
        arg_idx++;
    }
    
    if (first_verb.empty()) {
        out_error.message = "no command provided";
        out_error.token_index = -1;
        return result;
    }
    
    // Build typed intent from parsed arguments
    result.id = "cli-" + std::to_string(std::chrono::system_clock::now().time_since_epoch().count());
    result.verb = first_verb;
    result.kind = rebuntu::shell::IntentKind::kVerb;
    result.scope = rebuntu::shell::ScopeContext::USER;
    
    // Capture any remaining tokens as arguments
    while (arg_idx < argv.size()) {
        const std::string& token = argv[arg_idx];
        
        // Check if this is an option (starts with -)
        if (!token.empty() && token[0] == '-') {
            // Parse --option=value or --option value format
            std::optional<std::string> opt_name;
            std::optional<std::string> opt_value;
            
            size_t eq_pos = token.find('=');
            if (eq_pos != std::string::npos) {
                opt_name = token.substr(2, eq_pos - 2);  // Skip --
                opt_value = token.substr(eq_pos + 1);
            } else {
                opt_name = token.substr(2);  // Skip --
                
                // Check if next token is a value (not another option)
                if (arg_idx + 1 < argv.size() && 
                    !argv[arg_idx + 1].empty() && 
                    argv[arg_idx + 1][0] != '-') {
                    arg_idx++;
                    opt_value = argv[arg_idx];
                }
            }
            
            // Store as qualifier
            if (opt_name.has_value()) {
                result.qualifiers[opt_name.value()] = opt_value.value_or("true");
            }
        } else {
            // Positional argument
            result.arguments.emplace_back(std::to_string(result.arguments.size()), token);
        }
        
        arg_idx++;
    }
    
    return result;
}

}  // namespace rebuntu::cli::parser