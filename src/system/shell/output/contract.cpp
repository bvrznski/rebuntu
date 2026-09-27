// rebuntu::shell::output — Structured Output Contract Implementation (Phase 6.11)

#include "contract.hpp"
#include <sstream>
#include <iomanip>

namespace rebuntu::shell {

// ============================================================================
// OutputContext implementation
// ============================================================================

OutputContext OutputContext::from_env() {
    OutputContext ctx;
    // TODO: Read environment variables for mode override
    return ctx;
}

// ============================================================================
// JSON escape helper (for use in to_json methods)
// ============================================================================

static std::string escape_string(const std::string& s) {
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
                if (c >= 0 && c < 32) {
                    oss << "\\u" << std::hex << std::setw(4) << std::setfill('0') << static_cast<int>(c);
                } else {
                    oss << c;
                }
        }
    }
    return oss.str();
}

// ============================================================================
// StructuredResult to_json implementation
// ============================================================================

std::string StructuredResult::to_json() const {
    std::ostringstream oss;
    oss << "{\n";
    
    // Status
    oss << "  \"status\": \"" << to_string(status) << "\",\n";
    
    // is_true (optional)
    if (is_true.has_value()) {
        oss << "  \"is_true\": " << (is_true.value() ? "true" : "false") << ",\n";
    } else {
        oss << "  \"is_true\": null,\n";
    }
    
    // Command metadata
    oss << "  \"command_id\": \"" << escape_string(command_id) << "\",\n";
    oss << "  \"verb\": \"" << escape_string(verb) << "\"\n";
    
    if (subject_type.has_value()) {
        oss << ",\n  \"subject_type\": \"" << escape_string(subject_type.value()) << "\"";
    }
    if (target.has_value()) {
        oss << ",\n  \"target\": \"" << escape_string(target.value()) << "\"";
    }
    
    // Execution data
    oss << ",\n  \"changed\": " << (changed ? "true" : "false");
    oss << ",\n  \"verified\": " << (verified ? "true" : "false");
    oss << ",\n  \"elapsed_ms\": " << elapsed_ms;
    
    // Evidence
    if (!evidence.empty()) {
        oss << ",\n  \"evidence\": [";
        for (size_t i = 0; i < evidence.size(); ++i) {
            if (i > 0) oss << ", ";
            oss << "{\"source\": \"" << escape_string(evidence[i].source)
                << "\", \"value\": \"" << escape_string(evidence[i].value)
                << "\", \"captured_at\": \"" << escape_string(evidence[i].captured_at) << "\"}";
        }
        oss << "]";
    }
    
    // Error (optional)
    if (error.has_value()) {
        oss << ",\n  \"error\": {\"code\": \"" << escape_string(error.value().code)
            << "\", \"message\": \"" << escape_string(error.value().message) << "\"}";
    }
    
    // Warnings
    if (!warnings.empty()) {
        oss << ",\n  \"warnings\": [";
        for (size_t i = 0; i < warnings.size(); ++i) {
            if (i > 0) oss << ", ";
            oss << "\"" << escape_string(warnings[i]) << "\"";
        }
        oss << "]";
    }
    
    // Output value (optional)
    if (output_value.has_value()) {
        oss << ",\n  \"output_value\": \"" << escape_string(output_value.value()) << "\"";
    }
    
    // Exit code (optional)
    if (exit_code.has_value()) {
        oss << ",\n  \"exit_code\": " << exit_code.value();
    }
    
    oss << "\n}";
    return oss.str();
}

// ============================================================================
// HumanRenderer implementation
// ============================================================================

std::string HumanRenderer::format_status(SemanticStatus s) const {
    switch (s) {
        case SemanticStatus::kSuccess:   return "success";
        case SemanticStatus::kCompleted: return "completed";
        case SemanticStatus::kFailure:   return "failure";
        case SemanticStatus::kUnknown:   return "unknown";
        case SemanticStatus::kCancelled: return "cancelled";
    }
    return "unknown";
}

std::string HumanRenderer::format_duration(int64_t ms) const {
    std::ostringstream oss;
    if (ms < 1000) {
        oss << ms << "ms";
    } else if (ms < 60000) {
        oss << static_cast<double>(ms) / 1000.0 << "s";
    } else {
        oss << static_cast<double>(ms) / 60000.0 << "m";
    }
    return oss.str();
}

RenderedOutput HumanRenderer::render(const StructuredResult& result, const OutputContext& ctx) const {
    (void)ctx;  // Unused for now
    
    std::ostringstream oss;
    
    // Status line
    oss << format_status(result.status);
    
    // Command info
    if (!result.command_id.empty()) {
        oss << " [" << result.command_id.substr(0, 8) << "]";
    }
    
    // Result details based on status
    switch (result.status) {
        case SemanticStatus::kSuccess:
            oss << " ✓";
            break;
        case SemanticStatus::kFailure:
            if (result.error.has_value()) {
                oss << " ✗ (" << result.error.value().code << ": " << result.error.value().message << ")";
            } else {
                oss << " ✗";
            }
            break;
        case SemanticStatus::kUnknown:
            oss << " ? (status unknown)";
            break;
        case SemanticStatus::kCancelled:
            oss << " ⚠ cancelled";
            break;
        default:
            break;
    }
    
    // Output value for queries
    if (result.output_value.has_value()) {
        oss << "\n  Value: " << result.output_value.value();
    }
    
    return RenderedOutput::success(oss.str(), false);
}

// ============================================================================
// JSONRenderer implementation
// ============================================================================

RenderedOutput JSONRenderer::render(const StructuredResult& result, const OutputContext& ctx) const {
    (void)ctx;  // Unused for now
    
    std::string json = result.to_json();
    return RenderedOutput::success(json, true);
}

// ============================================================================
// JSONLRenderer implementation
// ============================================================================

RenderedOutput JSONLRenderer::render(const StructuredResult& result, const OutputContext& ctx) const {
    (void)ctx;  // Unused for now
    
    std::string json = result.to_json();
    return RenderedOutput::success(json + "\n", true);
}

// ============================================================================
// CollectionRenderer implementation
// ============================================================================

void CollectionRenderer::add_result(StructuredResult r) {
    results_.push_back(std::move(r));
}

RenderedOutput CollectionRenderer::render() const {
    if (results_.empty()) {
        return RenderedOutput::success("[]\n", true);
    }
    
    std::ostringstream oss;
    oss << "[\n";
    for (size_t i = 0; i < results_.size(); ++i) {
        if (i > 0) oss << ",\n";
        oss << "  " << results_[i].to_json();
    }
    oss << "\n]";
    
    return RenderedOutput::success(oss.str(), true);
}

}  // namespace rebuntu::shell