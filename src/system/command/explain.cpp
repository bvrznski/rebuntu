// rebuntu::command::explain — Implementation (Phase 6.28)
//
// This module provides structured operator-readable plan explanation showing:
//
//   * Exact target, operation
//   * Evidence sources and uncertainty
//   * Preconditions and expected effects
//   * Verification strategy
//   * Known irreversible/unknown aspects

#include "system/command/explain.hpp"

#include <sstream>
#include <iomanip>
#include <ctime>

namespace rebuntu::command::explain {

// Helper function to escape JSON strings
static std::string json_escape(const std::string& s) {
    std::ostringstream oss;
    for (char c : s) {
        switch (c) {
            case '"':  oss << "\\\""; break;
            case '\\': oss << "\\\\"; break;
            case '\b': oss << "\\b"; break;
            case '\f': oss << "\\f"; break;
            case '\n': oss << "\\n"; break;
            case '\r': oss << "\\r"; break;
            case '\t': oss << "\\t"; break;
            default:
                if (static_cast<unsigned char>(c) < 0x20) {
                    oss << "\\u" << std::hex << std::setw(4) << std::setfill('0') 
                        << static_cast<int>(c);
                } else {
                    oss << c;
                }
        }
    }
    return oss.str();
}

// Helper to format timestamp
static std::string format_timestamp(std::chrono::system_clock::time_point tp) {
    auto time_t_val = std::chrono::system_clock::to_time_t(tp);
    std::tm tm_val;
    gmtime_r(&time_t_val, &tm_val);
    
    std::ostringstream oss;
    oss << std::put_time(&tm_val, "%Y-%m-%dT%H:%M:%SZ");
    return oss.str();
}

// ============================================================================
// PlanExplanation methods
// ============================================================================

std::string PlanExplanation::to_text() const {
    std::ostringstream oss;
    
    oss << "=== Execution Plan Explanation ===\n\n";
    
    // Basic info
    oss << "Plan ID:     " << plan_id << "\n";
    oss << "Operation:   " << operation_name << "\n";
    if (subject_type.has_value()) {
        oss << "Subject Type: " << subject_type.value() << "\n";
    }
    if (target_id.has_value()) {
        oss << "Target ID:    " << target_id.value() << "\n";
    }
    
    // Input parameters
    if (!input_parameters.empty()) {
        oss << "\n--- Input Parameters ---\n";
        for (const auto& [name, value] : input_parameters) {
            oss << "  " << name << " = " << value << "\n";
        }
    }
    
    // Preconditions
    if (!preconditions.empty()) {
        oss << "\n--- Preconditions ---\n";
        for (size_t i = 0; i < preconditions.size(); ++i) {
            oss << "[" << to_string(preconditions_met[i]) << "] ";
            oss << preconditions[i] << "\n";
        }
    }
    
    // Expected effects
    if (!expected_effects.empty()) {
        oss << "\n--- Expected Effects ---\n";
        for (const auto& effect : expected_effects) {
            oss << "  * " << effect << "\n";
        }
    }
    
    // Steps
    if (!steps.empty()) {
        oss << "\n--- Execution Steps (" << steps.size() << ") ---\n";
        for (const auto& step : steps) {
            oss << "\nStep " << step.index + 1 << ": [" << to_string(step.status) << "] " 
                << step.description << "\n";
            oss << "  Capability: " << step.capability.domain << "." << step.capability.operation << "\n";
            
            if (!step.arguments.empty()) {
                oss << "  Arguments:\n";
                for (const auto& arg : step.arguments) {
                    oss << "    " << arg.name << " = " << arg.value;
                    if (arg.required) oss << " [required]";
                    oss << "\n";
                }
            }
            
            if (!step.qualifiers.empty()) {
                oss << "  Qualifiers:\n";
                for (const auto& qual : step.qualifiers) {
                    if (qual.value.has_value()) {
                        oss << "    " << qual.name << "=" << qual.value.value() << "\n";
                    } else {
                        oss << "    --" << qual.name << "\n";
                    }
                }
            }
            
            if (!step.depends_on.empty()) {
                oss << "  Depends on: ";
                for (size_t i = 0; i < step.depends_on.size(); ++i) {
                    if (i > 0) oss << ", ";
                    oss << step.depends_on[i];
                }
                oss << "\n";
            }
        }
    }
    
    // Verification
    if (!verification_steps.empty()) {
        oss << "\n--- Verification Steps (" << verification_steps.size() << ") ---\n";
        for (const auto& vstep : verification_steps) {
            oss << "[" << to_string(vstep.status) << "] " << vstep.description << "\n";
            if (!vstep.verification_type.empty()) {
                oss << "  Type: " << vstep.verification_type << "\n";
            }
        }
    }
    
    // Uncertainties
    if (!uncertainties.empty()) {
        oss << "\n--- Uncertainties (" << uncertainties.size() << ") ---\n";
        for (const auto& u : uncertainties) {
            oss << "[" << u.severity << "] " << u.description << "\n";
            if (!u.impact.empty()) {
                oss << "  Impact: " << u.impact[0];
                for (size_t i = 1; i < u.impact.size(); ++i) {
                    oss << ", " << u.impact[i];
                }
                oss << "\n";
            }
        }
    }
    
    // Irreversible aspects
    if (!irreversible_aspects.empty()) {
        oss << "\n--- Irreversible Aspects (" << irreversible_aspects.size() << ") ---\n";
        for (const auto& irr : irreversible_aspects) {
            oss << "* " << irr.description << "\n";
            if (irr.can_be_restored && irr.recovery_method.has_value()) {
                oss << "  Recovery: " << irr.recovery_method.value() << "\n";
            }
        }
    }
    
    // Evidence sources
    if (!evidence_sources.empty()) {
        oss << "\n--- Evidence Sources ---\n";
        for (const auto& src : evidence_sources) {
            oss << "  * " << src << "\n";
        }
    }
    
    // Summary
    oss << "\n=== Summary ===\n";
    oss << "Requires Privilege: " << (requires_privilege ? "yes" : "no") << "\n";
    oss << "Idempotent:         " << (is_idempotent ? "yes" : "no") << "\n";
    if (estimated_duration_ms > 0) {
        oss << "Estimated Duration: " << estimated_duration_ms << " ms\n";
    }
    
    return oss.str();
}

std::string PlanExplanation::to_json() const {
    std::ostringstream oss;
    
    oss << "{\n";
    
    // Basic info
    oss << "  \"plan_id\": \"" << json_escape(plan_id) << "\",\n";
    oss << "  \"created_at\": \"" << format_timestamp(created_at) << "\",\n";
    oss << "  \"operation_name\": \"" << json_escape(operation_name) << "\",\n";
    
    if (subject_type.has_value()) {
        oss << "  \"subject_type\": \"" << json_escape(subject_type.value()) << "\",\n";
    }
    if (target_id.has_value()) {
        oss << "  \"target_id\": \"" << json_escape(target_id.value()) << "\",\n";
    }
    
    // Input parameters
    oss << "  \"input_parameters\": {";
    bool first = true;
    for (const auto& [name, value] : input_parameters) {
        if (!first) oss << ", ";
        oss << "\"" << json_escape(name) << "\": \"" << json_escape(value) << "\"";
        first = false;
    }
    oss << "},\n";
    
    // Preconditions
    oss << "  \"preconditions\": [";
    for (size_t i = 0; i < preconditions.size(); ++i) {
        if (i > 0) oss << ", ";
        oss << "{\"condition\": \"" << json_escape(preconditions[i]) << "\", "
            << "\"status\": \"" << to_string(preconditions_met[i]) << "\"}";
    }
    oss << "],\n";
    
    // Expected effects
    oss << "  \"expected_effects\": [";
    for (size_t i = 0; i < expected_effects.size(); ++i) {
        if (i > 0) oss << ", ";
        oss << "\"" << json_escape(expected_effects[i]) << "\"";
    }
    oss << "],\n";
    
    // Steps
    oss << "  \"steps\": [\n";
    for (size_t i = 0; i < steps.size(); ++i) {
        const auto& step = steps[i];
        if (i > 0) oss << ",\n";
        oss << "    {\n";
        oss << "      \"index\": " << step.index << ",\n";
        oss << "      \"id\": \"" << json_escape(step.id) << "\",\n";
        oss << "      \"kind\": \"" << to_string(step.kind) << "\",\n";
        oss << "      \"description\": \"" << json_escape(step.description) << "\",\n";
        oss << "      \"capability\": {\n";
        oss << "        \"domain\": \"" << json_escape(step.capability.domain) << "\",\n";
        oss << "        \"operation\": \"" << json_escape(step.capability.operation) << "\"\n";
        oss << "      },\n";
        
        // Arguments
        oss << "      \"arguments\": [";
        for (size_t j = 0; j < step.arguments.size(); ++j) {
            const auto& arg = step.arguments[j];
            if (j > 0) oss << ", ";
            oss << "{\"name\": \"" << json_escape(arg.name) << "\", "
                << "\"value\": \"" << json_escape(arg.value) << "\", "
                << "\"required\": " << (arg.required ? "true" : "false") << "}";
        }
        oss << "],\n";
        
        // Qualifiers
        oss << "      \"qualifiers\": [";
        for (size_t j = 0; j < step.qualifiers.size(); ++j) {
            const auto& qual = step.qualifiers[j];
            if (j > 0) oss << ", ";
            oss << "{\"name\": \"" << json_escape(qual.name) << "\"";
            if (qual.value.has_value()) {
                oss << ", \"value\": \"" << json_escape(qual.value.value()) << "\"";
            }
            oss << "}";
        }
        oss << "],\n";
        
        // Status
        oss << "      \"status\": \"" << to_string(step.status) << "\"\n";
        oss << "    }";
    }
    oss << "\n  ],\n";
    
    // Verification steps
    oss << "  \"verification_steps\": [";
    for (size_t i = 0; i < verification_steps.size(); ++i) {
        const auto& vstep = verification_steps[i];
        if (i > 0) oss << ", ";
        oss << "{\"id\": \"" << json_escape(vstep.id) << "\", "
            << "\"description\": \"" << json_escape(vstep.description) << "\", "
            << "\"type\": \"" << json_escape(vstep.verification_type) << "\", "
            << "\"status\": \"" << to_string(vstep.status) << "\"}";
    }
    oss << "],\n";
    
    // Uncertainties
    oss << "  \"uncertainties\": [";
    for (size_t i = 0; i < uncertainties.size(); ++i) {
        const auto& u = uncertainties[i];
        if (i > 0) oss << ", ";
        oss << "{\"description\": \"" << json_escape(u.description) << "\", "
            << "\"severity\": \"" << json_escape(u.severity) << "\"}";
    }
    oss << "],\n";
    
    // Irreversible aspects
    oss << "  \"irreversible_aspects\": [";
    for (size_t i = 0; i < irreversible_aspects.size(); ++i) {
        const auto& irr = irreversible_aspects[i];
        if (i > 0) oss << ", ";
        oss << "{\"description\": \"" << json_escape(irr.description) << "\", "
            << "\"can_be_restored\": " << (irr.can_be_restored ? "true" : "false") << "}";
        if (irr.recovery_method.has_value()) {
            oss << ", \"recovery_method\": \"" << json_escape(irr.recovery_method.value()) << "\"";
        }
        oss << "}";
    }
    oss << "],\n";
    
    // Evidence sources
    oss << "  \"evidence_sources\": [";
    for (size_t i = 0; i < evidence_sources.size(); ++i) {
        if (i > 0) oss << ", ";
        oss << "\"" << json_escape(evidence_sources[i]) << "\"";
    }
    oss << "],\n";
    
    // Summary
    oss << "  \"requires_privilege\": " << (requires_privilege ? "true" : "false") << ",\n";
    oss << "  \"is_idempotent\": " << (is_idempotent ? "true" : "false") << "\n";
    
    oss << "}";
    
    return oss.str();
}

std::string PlanExplanation::to_table() const {
    std::ostringstream oss;
    
    // Header
    oss << "+-----------------------------------------------+\n";
    oss << "|           EXECUTION PLAN EXPLANATION          |\n";
    oss << "+-----------------------------------------------+\n\n";
    
    // Summary table
    oss << "Plan ID:     " << plan_id << "\n";
    oss << "Operation:   " << operation_name << "\n";
    if (subject_type.has_value()) {
        oss << "Subject Type: " << subject_type.value() << "\n";
    }
    if (target_id.has_value()) {
        oss << "Target ID:    " << target_id.value() << "\n";
    }
    oss << "\n";
    
    // Step table
    oss << "+-----+------------------+------------------------------------------+\n";
    oss << "| #   | Status           | Description                              |\n";
    oss << "+-----+------------------+------------------------------------------+\n";
    
    for (size_t i = 0; i < steps.size(); ++i) {
        const auto& step = steps[i];
        std::string status_str = to_string(step.status);
        // Truncate description if too long
        std::string desc = step.description;
        if (desc.length() > 40) {
            desc = desc.substr(0, 37) + "...";
        }
        
        oss << "| " << std::setw(2) << (i + 1) 
            << " | " << std::setw(16) << status_str
            << " | " << std::setw(40) << desc
            << " |\n";
    }
    
    oss << "+-----+------------------+------------------------------------------+\n\n";
    
    // Verification steps
    if (!verification_steps.empty()) {
        oss << "Verification Steps:\n";
        for (const auto& vstep : verification_steps) {
            std::string status_str = to_string(vstep.status);
            std::string desc = vstep.description;
            if (desc.length() > 50) {
                desc = desc.substr(0, 47) + "...";
            }
            oss << "  [" << status_str << "] " << desc << "\n";
        }
    }
    
    // Summary info
    oss << "\n+-----------------------------------------------+\n";
    oss << "| SUMMARY                                       |\n";
    oss << "+-----------------------------------------------+\n";
    oss << "| Requires Privilege: " << std::left << std::setw(15) 
        << (requires_privilege ? "yes" : "no") << "|\n";
    oss << "| Idempotent:         " << std::left << std::setw(15)
        << (is_idempotent ? "yes" : "no") << "|\n";
    if (estimated_duration_ms > 0) {
        oss << "| Estimated Duration: " << estimated_duration_ms << " ms   |\n";
    }
    oss << "+-----------------------------------------------+\n";
    
    return oss.str();
}

}  // namespace rebuntu::command::explain