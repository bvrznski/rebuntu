// rebuntu::adapters::exec_diag — Execution Journald Diagnostics Emitter (Phase 6.38)
//
// This module provides a structured diagnostic emitter that writes to journald
// with command/operation/attempt/provider IDs for tracing execution flow.
//
// Diagnostic Features:
//   - Structured event emission to systemd journal
//   - Execution correlation via command/operation/attempt/provider IDs
//   - Secret-safe redaction of sensitive data
//   - Context-rich diagnostic messages

#pragma once

#include <string>
#include <vector>
#include <chrono>
#include <optional>
#include <memory>

#include <runtime/contracts.hpp>
#include <system/core/contracts.hpp>

namespace rebuntu::adapters {

// ============================================================================
// ExecDiagnosticLevel — Severity levels for diagnostics
// ============================================================================

enum class ExecDiagnosticLevel {
    kDebug,     // Detailed debug information (verbose)
    kInfo,      // General informational messages
    kWarning,   // Non-critical issues that may need attention
    kError,     // Error conditions
    kCritical,  // Critical errors requiring immediate attention
};

inline std::string to_string(ExecDiagnosticLevel level) {
    switch (level) {
        case ExecDiagnosticLevel::kDebug:    return "debug";
        case ExecDiagnosticLevel::kInfo:     return "info";
        case ExecDiagnosticLevel::kWarning:  return "warning";
        case ExecDiagnosticLevel::kError:    return "error";
        case ExecDiagnosticLevel::kCritical: return "critical";
    }
    return "unknown";
}

// ============================================================================
// ExecutionIds — Correlation IDs for execution tracing
//
// These IDs enable tracing execution across components and attempts.
// ============================================================================

struct ExecutionIds {
    std::string command_id;       // Original command request ID
    std::string operation_id;     // Operation being executed
    std::optional<std::string> attempt_id;  // Specific attempt in retry chain
    std::optional<std::string> provider_id; // Provider that executed this attempt
    
    static ExecutionIds make(
        std::string cmd_id,
        std::string op_id,
        std::optional<std::string> att_id = std::nullopt,
        std::optional<std::string> prov_id = std::nullopt) {
        return ExecutionIds{
            std::move(cmd_id),
            std::move(op_id),
            std::move(att_id),
            std::move(prov_id)
        };
    }
};

// ============================================================================
// ExecDiagnosticEvent — A single diagnostic event
// ============================================================================

struct ExecDiagnosticEvent {
    std::chrono::system_clock::time_point timestamp;
    
    ExecDiagnosticLevel level;
    
    // Correlation IDs
    ExecutionIds exec_ids;
    
    // Event details
    std::string category;         // e.g., "command", "operation", "attempt"
    std::string action;           // What happened (e.g., "started", "completed")
    std::string message;          // Human-readable description
    
    // Context data (will be redacted for secrets)
    std::vector<std::pair<std::string, std::string>> context;
    
    // Metadata
    std::optional<std::string> source_file;
    std::optional<int> source_line;
    
    static ExecDiagnosticEvent make(
        ExecDiagnosticLevel level,
        const ExecutionIds& exec_ids,
        std::string cat,
        std::string act,
        std::string msg) {
        return ExecDiagnosticEvent{
            std::chrono::system_clock::now(),
            level,
            exec_ids,
            std::move(cat),
            std::move(act),
            std::move(msg),
            {},
            std::nullopt,
            std::nullopt
        };
    }
};

// ============================================================================
// ExecDiagConfig — Configuration for the diagnostic emitter
// ============================================================================

struct ExecDiagConfig {
    // Minimum level to emit (lower levels will be filtered)
    ExecDiagnosticLevel min_level = ExecDiagnosticLevel::kDebug;
    
    // Whether to redact secrets from context data
    bool redact_secrets = true;
    
    // Maximum length of message values
    size_t max_message_length = 4096;
    
    // Additional static context to include in all events
    std::vector<std::pair<std::string, std::string>> global_context;
};

// ============================================================================
// ExecDiagnosticEmitter — Journald diagnostic emitter interface
// ============================================================================

class ExecDiagnosticEmitter {
public:
    virtual ~ExecDiagnosticEmitter() = default;
    
    // Emit a single diagnostic event
    virtual core::Outcome emit(const ExecDiagnosticEvent& event) = 0;
    
    // Convenience methods for common operations
    virtual core::Outcome debug(
        const ExecutionIds& exec_ids,
        std::string category,
        std::string action,
        std::string message) = 0;
    
    virtual core::Outcome info(
        const ExecutionIds& exec_ids,
        std::string category,
        std::string action,
        std::string message) = 0;
    
    virtual core::Outcome warning(
        const ExecutionIds& exec_ids,
        std::string category,
        std::string action,
        std::string message) = 0;
    
    virtual core::Outcome error(
        const ExecutionIds& exec_ids,
        std::string category,
        std::string action,
        std::string message) = 0;
    
    virtual core::Outcome critical(
        const ExecutionIds& exec_ids,
        std::string category,
        std::string action,
        std::string message) = 0;
    
    // Update configuration (can be called at any time)
    virtual core::Outcome configure(const ExecDiagConfig& config) = 0;
    
    // Get current configuration
    virtual ExecDiagConfig config() const = 0;
};

// ============================================================================
// Factory function
// ============================================================================

std::unique_ptr<ExecDiagnosticEmitter> make_exec_diagnostic_emitter(
    const ExecDiagConfig& config = ExecDiagConfig{});

}  // namespace rebuntu::adapters