// rebuntu::environment::redact — Secret Redaction Framework (Phase 5.53)
//
// This module provides centralized secret redaction functionality for
// evidence collection, logging, and reporting.
//
// Key Principles:
//   - Redact at acquisition boundaries (before storage/logging)
//   - Never store raw secrets in logs, snapshots, or model context
//   - Use reference-based identification (SecretRef) not content matching
//   - Preserve provenance while hiding sensitive values

#pragma once

#include <string>
#include <vector>
#include <map>
#include <optional>
#include <sstream>
#include <algorithm>
#include <cctype>

namespace rebuntu::environment::redact {

// ============================================================================
// SecretPattern — Pattern for identifying secrets in text
// ============================================================================

struct SecretPattern {
    std::string name;               // Human-readable name (for logging)
    std::string key_prefix;         // Key prefix to match (e.g., "password", "token")
    bool case_sensitive = false;    // Case-sensitive matching
    
    static SecretPattern password() { return {"password", "password"}; }
    static SecretPattern token() { return {"token", "token"}; }
    static SecretPattern secret() { return {"secret", "secret"}; }
    static SecretPattern authorization() { return {"authorization", "authorization"}; }
    static SecretPattern api_key() { return {"api-key", "api_key"}; }
    static SecretPattern private_key() { return {"private-key", "private_key"}; }
};

// ============================================================================
// RedactionContext — Context for redaction operations
// ============================================================================

struct RedactionContext {
    std::vector<SecretPattern> patterns;
    
    // Default sensitive patterns to redact
    static RedactionContext default_context() {
        RedactionContext ctx;
        ctx.patterns = {
            SecretPattern::password(),
            SecretPattern::token(),
            SecretPattern::secret(),
            SecretPattern::authorization(),
            SecretPattern::api_key(),
            SecretPattern::private_key()
        };
        return ctx;
    }
};

// ============================================================================
// Core Redaction Functions
// ============================================================================

// Redact secrets from a string value (e.g., journal MESSAGE field)
// Returns a copy with sensitive values replaced by "<redacted>"
std::string redact_value(
    const std::string& value,
    const std::vector<SecretPattern>& patterns = {});

// Redact secrets from key=value pairs
// Only redacts the value portion, keeping keys visible for diagnostics
std::map<std::string, std::string> redact_key_values(
    const std::map<std::string, std::string>& values,
    const std::vector<SecretPattern>& patterns = {});

// Format a config map for display with secrets redacted
std::string format_config_with_redaction(
    const std::map<std::string, std::string>& values,
    const std::vector<SecretPattern>& patterns = {});

// ============================================================================
// Implementation Details
// ============================================================================

inline std::string redact_value(
    const std::string& value,
    const std::vector<SecretPattern>& patterns) {
    
    if (value.empty()) return value;
    
    std::string result = value;
    std::string lower_result = value;
    
    // Convert to lowercase for case-insensitive search
    std::transform(lower_result.begin(), lower_result.end(), lower_result.begin(),
                   [](unsigned char c){ return static_cast<char>(std::tolower(c)); });
    
    for (const auto& pattern : patterns) {
        std::string search_key = pattern.key_prefix;
        if (!pattern.case_sensitive) {
            // Already working with lowercase
        } else {
            std::transform(search_key.begin(), search_key.end(), search_key.begin(),
                          [](unsigned char c){ return static_cast<char>(std::tolower(c)); });
        }
        
        size_t pos = 0;
        while ((pos = lower_result.find(search_key, pos)) != std::string::npos) {
            // Found a potential match - now find the value
            // Look for patterns like: key=value or "key": "value"
            
            size_t value_start = std::string::npos;
            char quote_char = 0;
            
            // Check if this looks like key=value pattern (after the matched text)
            // Pattern: =<value> or ="<value>" or ='<value>'
            
            if (pos + search_key.size() < result.size()) {
                size_t after_key = pos + search_key.size();
                
                // Skip any characters between key and =
                while (after_key < result.size() && 
                       !std::isspace(result[after_key]) && 
                       result[after_key] != '=') {
                    after_key++;
                }
                
                if (after_key < result.size() && result[after_key] == '=') {
                    // Found =, now find the value
                    size_t after_eq = after_key + 1;
                    
                    // Skip whitespace
                    while (after_eq < result.size() && std::isspace(result[after_eq])) {
                        after_eq++;
                    }
                    
                    if (after_eq < result.size()) {
                        quote_char = 0;
                        
                        // Check for quoted value
                        if (result[after_eq] == '"' || result[after_eq] == '\'') {
                            quote_char = result[after_eq];
                            value_start = after_eq + 1;
                            
                            // Find closing quote
                            size_t end_pos = value_start;
                            while (end_pos < result.size() && result[end_pos] != quote_char) {
                                if (result[end_pos] == '\\' && end_pos + 1 < result.size()) {
                                    end_pos += 2; // Skip escaped character
                                } else {
                                    end_pos++;
                                }
                            }
                            
                            if (end_pos < result.size()) {
                                // Replace the value portion
                                std::string replacement = "<redacted>";
                                result.replace(value_start, end_pos - value_start + 1, replacement);
                                
                                // Update lowercase version for next search
                                lower_result = result;
                                std::transform(lower_result.begin(), lower_result.end(), 
                                              lower_result.begin(),
                                              [](unsigned char c){ return static_cast<char>(std::tolower(c)); });
                            }
                        } else {
                            // Unquoted value - find end (space, comma, semicolon, or end of string)
                            size_t end_pos = after_eq;
                            while (end_pos < result.size() && 
                                   !std::isspace(result[end_pos]) &&
                                   result[end_pos] != ',' && 
                                   result[end_pos] != ';' &&
                                   result[end_pos] != '&') {
                                end_pos++;
                            }
                            
                            if (end_pos > after_eq) {
                                // Replace with redacted
                                std::string replacement = "<redacted>";
                                result.replace(after_eq, end_pos - after_eq, replacement);
                                
                                lower_result = result;
                                std::transform(lower_result.begin(), lower_result.end(), 
                                              lower_result.begin(),
                                              [](unsigned char c){ return static_cast<char>(std::tolower(c)); });
                            }
                        }
                    }
                }
            }
            
            // Move past this match to continue searching
            pos++;
        }
    }
    
    return result;
}

inline std::map<std::string, std::string> redact_key_values(
    const std::map<std::string, std::string>& values,
    const std::vector<SecretPattern>& patterns) {
    
    std::map<std::string, std::string> result;
    
    for (const auto& [key, value] : values) {
        // Redact the value
        std::string redacted_value = redact_value(value, patterns);
        result[key] = redacted_value;
    }
    
    return result;
}

inline std::string format_config_with_redaction(
    const std::map<std::string, std::string>& values,
    const std::vector<SecretPattern>& patterns) {
    
    std::ostringstream ss;
    
    for (const auto& [key, value] : values) {
        // Redact the value
        std::string redacted_value = redact_value(value, patterns);
        
        ss << key << " = ";
        
        // Check if this looks like it should be quoted (contains spaces or special chars)
        bool needs_quotes = !redacted_value.empty() && 
                           (redacted_value.find(' ') != std::string::npos ||
                            redacted_value.find('=') != std::string::npos ||
                            redacted_value.find('#') != std::string::npos);
        
        if (needs_quotes) {
            // Escape internal quotes
            std::string safe = redacted_value;
            size_t pos = 0;
            while ((pos = safe.find('"', pos)) != std::string::npos) {
                safe.insert(pos, "\\");
                pos += 2;
            }
            ss << '"' << safe << '"';
        } else {
            ss << redacted_value;
        }
        
        ss << "\n";
    }
    
    return ss.str();
}

}  // namespace rebuntu::environment::redact