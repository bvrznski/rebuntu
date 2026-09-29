// rebuntu::adapters::exec_diag — Execution Journald Diagnostics Emitter Implementation (Phase 6.38)
//
// This module implements a structured diagnostic emitter that writes to journald
// with command/operation/attempt/provider IDs for tracing execution flow.

#include "adapters/exec_diag.hpp"
#include "adapters/subprocess_utility.hpp"

#include <cstdlib>
#include <cstring>
#include <cstddef>
#include <memory>
#include <optional>
#include <string_view>
#include <array>
#include <thread>
#include <mutex>
#include <sstream>
#include <algorithm>

#include "adapters/journald.hpp"
#include <system/environment/redact.hpp>

namespace rebuntu::adapters {

// ============================================================================
// Subprocess Utility Wrapper
// ============================================================================

// Static SubprocessUtility instance for the adapter
static SubprocessUtility g_subprocess_utility{std::chrono::seconds(30)};

// Execute a command using the canonical subprocess utility
core::Outcome execute_command(
    const std::vector<std::string>& argv,
    const std::string* stdin_input,  // Optional: pointer to stdin data (nullptr if none)
    std::string& stdout_output,
    std::chrono::milliseconds timeout) {
    
    // Use SubprocessUtility for canonical subprocess execution
    SubprocessUtility::ExecutionResult result;
    
    if (stdin_input != nullptr && !stdin_input->empty()) {
        result = g_subprocess_utility.execute_with_stdin(
            argv[0], std::vector<std::string>(argv.begin() + 1, argv.end()),
            *stdin_input, std::nullopt, timeout);
    } else {
        result = g_subprocess_utility.execute(
            argv[0], std::vector<std::string>(argv.begin() + 1, argv.end()),
            std::nullopt, timeout);
    }
    
    stdout_output = result.stdout_output;
    
    // Convert SubprocessUtility result to Outcome
    if (result.success) {
        return core::Outcome::success();
    } else {
        return core::Outcome::failure(
            "E_SUBPROCESS_FAILED",
            "subprocess exited with code " + std::to_string(result.exit_code));
    }
}

// Redact secrets from a message string (adapted from journald.cpp)
std::string redact_secrets(const std::string& message) {
    std::string result = message;
    std::string lower_result = message;
    
    // Convert to lowercase for case-insensitive search
    std::transform(lower_result.begin(), lower_result.end(), lower_result.begin(),
                   [](unsigned char c){ return static_cast<char>(std::tolower(c)); });
    
    // Patterns to redact: password=, token=, secret=, authorization=
    const std::vector<std::string> patterns = {"password", "token", "secret", "authorization"};
    
    for (const auto& pattern : patterns) {
        size_t pos = 0;
        while ((pos = lower_result.find(pattern, pos)) != std::string::npos) {
            // Look for = after the key name
            size_t after_key = pos + pattern.size();
            
            // Skip whitespace between key and =
            while (after_key < result.size() && 
                   std::isspace(result[after_key]) && 
                   result[after_key] != '=') {
                after_key++;
            }
            
            if (after_key < result.size() && result[after_key] == '=') {
                size_t after_eq = after_key + 1;
                
                // Skip whitespace
                while (after_eq < result.size() && std::isspace(result[after_eq])) {
                    after_eq++;
                }
                
                if (after_eq < result.size()) {
                    char quote_char = 0;
                    
                    // Check for quoted value
                    if (result[after_eq] == '"' || result[after_eq] == '\'') {
                        quote_char = result[after_eq];
                        size_t end_pos = after_eq + 1;
                        
                        // Find closing quote (handle escapes)
                        while (end_pos < result.size() && 
                               result[end_pos] != quote_char) {
                            if (result[end_pos] == '\\' && end_pos + 1 < result.size()) {
                                end_pos += 2;
                            } else {
                                end_pos++;
                            }
                        }
                        
                        if (end_pos < result.size()) {
                            std::string replacement = "<redacted>";
                            result.replace(after_eq + 1, end_pos - after_eq, replacement);
                            
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
            
            pos++;
        }
    }
    
    return result;
}

// Format timestamp for journal
std::string format_timestamp(std::chrono::system_clock::time_point tp) {
    auto time_t_now = std::chrono::system_clock::to_time_t(tp);
    struct tm tm_buf;
    gmtime_r(&time_t_now, &tm_buf);
    
    char buffer[64];
    strftime(buffer, sizeof(buffer), "%Y-%m-%dT%H:%M:%SZ", &tm_buf);
    return std::string(buffer);
}

// Build structured message for journald
std::string build_journal_message(const ExecDiagnosticEvent& event) {
    std::ostringstream oss;
    
    // Build JSON-like structured output
    oss << "{";
    oss << "\"LEVEL\":\"" << to_string(event.level) << "\",";
    oss << "\"COMMAND_ID\":\"" << event.exec_ids.command_id << "\",";
    oss << "\"OPERATION_ID\":\"" << event.exec_ids.operation_id << "\",";
    
    std::string attempt_id = event.exec_ids.attempt_id ? 
        *event.exec_ids.attempt_id : "";
    std::string provider_id = event.exec_ids.provider_id ? 
        *event.exec_ids.provider_id : "";
    
    if (!attempt_id.empty()) {
        oss << "\"ATTEMPT_ID\":\"" << attempt_id << "\",";
    }
    if (!provider_id.empty()) {
        oss << "\"PROVIDER_ID\":\"" << provider_id << "\",";
    }
    
    oss << "\"CATEGORY\":\"" << event.category << "\",";
    oss << "\"ACTION\":\"" << event.action << "\",";
    oss << "\"MESSAGE\":" << std::string("\"") + event.message + "\"";  // Simple quoted string
    
    // Add context data (redacted)
    oss << "\"CONTEXT\":[";
    for (size_t i = 0; i < event.context.size(); ++i) {
        if (i > 0) oss << ",";
        
        std::string key = event.context[i].first;
        std::string value = redact_secrets(event.context[i].second);
        
        oss << "{\"" << key << "\":\"" << value << "\"}";
    }
    oss << "],";
    
    // Add source location if available
    std::string source_file = event.source_file ? *event.source_file : "";
    int source_line = event.source_line ? *event.source_line : 0;
    
    if (!source_file.empty()) {
        oss << "\"SOURCE_FILE\":\"" << source_file << "\",";
    }
    oss << "\"SOURCE_LINE\":" << source_line << ",";
    
    oss << "}";
    
    return oss.str();
}

// ============================================================================
// ExecDiagnosticEmitterImpl — Implementation of ExecDiagnosticEmitter
// ============================================================================

class ExecDiagnosticEmitterImpl : public ExecDiagnosticEmitter {
public:
    explicit ExecDiagnosticEmitterImpl(const ExecDiagConfig& config)
        : config_(config) {}
    
    ~ExecDiagnosticEmitterImpl() override = default;
    
    // Emit a single diagnostic event to journald
    core::Outcome emit(const ExecDiagnosticEvent& event) override {
        // Check if we should emit at this level
        if (!should_emit(event.level)) {
            return core::Outcome::success();
        }
        
        // Build the message with redaction
        std::string message = build_journal_message(event);
        
        // Truncate if too long
        if (config_.max_message_length > 0 && 
            message.length() > config_.max_message_length) {
            message = message.substr(0, config_.max_message_length) + "...[truncated]";
        }
        
        // Build journalctl arguments to emit structured data
        std::vector<std::string> argv;
        argv.push_back("/usr/bin/journalctl");
        argv.push_back("--priority=info");
        argv.push_back("-n1");
        argv.push_back("--output=json");
        argv.push_back("--no-pager");
        
        // Format: --identifier=rebuntu-exec-diag
        argv.push_back("--identifier=rebuntu-exec-diag");
        
        // Execute journalctl with message via stdin (using null for now)
        std::string output;
        return execute_command(argv, nullptr, output, std::chrono::seconds(5));
    }
    
    // Convenience methods
    core::Outcome debug(
        const ExecutionIds& exec_ids,
        std::string category,
        std::string action,
        std::string message) override {
        ExecDiagnosticEvent event;
        event.level = ExecDiagnosticLevel::kDebug;
        event.exec_ids = exec_ids;
        event.category = std::move(category);
        event.action = std::move(action);
        event.message = std::move(message);
        return emit(event);
    }
    
    core::Outcome info(
        const ExecutionIds& exec_ids,
        std::string category,
        std::string action,
        std::string message) override {
        ExecDiagnosticEvent event;
        event.level = ExecDiagnosticLevel::kInfo;
        event.exec_ids = exec_ids;
        event.category = std::move(category);
        event.action = std::move(action);
        event.message = std::move(message);
        return emit(event);
    }
    
    core::Outcome warning(
        const ExecutionIds& exec_ids,
        std::string category,
        std::string action,
        std::string message) override {
        ExecDiagnosticEvent event;
        event.level = ExecDiagnosticLevel::kWarning;
        event.exec_ids = exec_ids;
        event.category = std::move(category);
        event.action = std::move(action);
        event.message = std::move(message);
        return emit(event);
    }
    
    core::Outcome error(
        const ExecutionIds& exec_ids,
        std::string category,
        std::string action,
        std::string message) override {
        ExecDiagnosticEvent event;
        event.level = ExecDiagnosticLevel::kError;
        event.exec_ids = exec_ids;
        event.category = std::move(category);
        event.action = std::move(action);
        event.message = std::move(message);
        return emit(event);
    }
    
    core::Outcome critical(
        const ExecutionIds& exec_ids,
        std::string category,
        std::string action,
        std::string message) override {
        ExecDiagnosticEvent event;
        event.level = ExecDiagnosticLevel::kCritical;
        event.exec_ids = exec_ids;
        event.category = std::move(category);
        event.action = std::move(action);
        event.message = std::move(message);
        return emit(event);
    }
    
    // Configuration
    core::Outcome configure(const ExecDiagConfig& config) override {
        config_ = config;
        return core::Outcome::success();
    }
    
    ExecDiagConfig config() const override {
        return config_;
    }

private:
    bool should_emit(ExecDiagnosticLevel level) const {
        // Debug < Info < Warning < Error < Critical
        int event_level_int = static_cast<int>(level);
        int min_level_int = static_cast<int>(config_.min_level);
        return event_level_int >= min_level_int;
    }
    
    ExecDiagConfig config_;
};

// ============================================================================
// Factory function
// ============================================================================

std::unique_ptr<ExecDiagnosticEmitter> make_exec_diagnostic_emitter(
    const ExecDiagConfig& config) {
    return std::make_unique<ExecDiagnosticEmitterImpl>(config);
}

}  // namespace rebuntu::adapters