// rebuntu::adapters::journald — Native Journald Acquisition Adapter Implementation (Phase 5.2)
//
// This module implements an adapter that acquires events from systemd journal
// using journalctl with structured JSON output.

#include "adapters/journald.hpp"

#include <cstdlib>
#include <cstring>
#include <cstddef>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/select.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <cerrno>
#include <memory>
#include <string_view>
#include <array>
#include <thread>
#include <mutex>
#include <sstream>

#include <system/environment/redact.hpp>

namespace rebuntu::adapters {

// ============================================================================
// Helper Functions for JSON Parsing and Command Execution
// ============================================================================

namespace {
    
// Execute a command and capture its output
core::Outcome execute_command(
    const std::vector<std::string>& argv,
    std::string& stdout_output,
    std::chrono::milliseconds timeout) {
    
    // Convert vector of strings to null-terminated array for execve
    std::vector<char*> args;
    for (const auto& arg : argv) {
        args.push_back(const_cast<char*>(arg.c_str()));
    }
    args.push_back(nullptr);
    
    // Create pipe for stdout
    int pipefd[2];
    if (pipe(pipefd) != 0) {
        return core::Outcome::failure(
            "E_PIPE_FAILED",
            "Failed to create pipe: " + std::string(strerror(errno)));
    }
    
    pid_t pid = fork();
    if (pid < 0) {
        close(pipefd[0]);
        close(pipefd[1]);
        return core::Outcome::failure(
            "E_FORK_FAILED",
            "Failed to fork process: " + std::string(strerror(errno)));
    }
    
    if (pid == 0) {
        // Child process
        close(pipefd[0]);  // Close read end
        
        // Redirect stdout to pipe
        dup2(pipefd[1], STDOUT_FILENO);
        
        // Execute the command
        execv(args[0], args.data());
        
        // If we get here, exec failed
        _exit(127);
    }
    
    // Parent process
    close(pipefd[1]);  // Close write end
    
    // Read output with timeout
    char buffer[4096];
    stdout_output.clear();
    
    fd_set read_fds;
    FD_ZERO(&read_fds);
    FD_SET(pipefd[0], &read_fds);
    
    struct timeval tv;
    tv.tv_sec = timeout.count() / 1000;
    tv.tv_usec = (timeout.count() % 1000) * 1000;
    
    ssize_t bytes_read;
    while ((bytes_read = select(pipefd[0] + 1, &read_fds, nullptr, nullptr, &tv)) > 0) {
        if (FD_ISSET(pipefd[0], &read_fds)) {
            ssize_t n = read(pipefd[0], buffer, sizeof(buffer));
            if (n <= 0) break;
            stdout_output.append(buffer, n);
            
            // Reset timeout for next iteration
            tv.tv_sec = timeout.count() / 1000;
            tv.tv_usec = (timeout.count() % 1000) * 1000;
            FD_ZERO(&read_fds);
            FD_SET(pipefd[0], &read_fds);
        }
    }
    
    close(pipefd[0]);
    
    // Wait for process to complete
    int status;
    waitpid(pid, &status, 0);
    
    if (WIFEXITED(status)) {
        int exit_code = WEXITSTATUS(status);
        if (exit_code == 0) {
            return core::Outcome::success();
        } else {
            return core::Outcome::failure(
                "E_JOURNALCTL_FAILED",
                "journalctl exited with code " + std::to_string(exit_code));
        }
    } else if (WIFSIGNALED(status)) {
        int sig = WTERMSIG(status);
        return core::Outcome::failure(
            "E_JOURNALCTL_SIGNALED",
            "journalctl terminated by signal " + std::to_string(sig));
    }
    
    return core::Outcome::success();
}

// Extract a string value from JSON
std::optional<std::string> extract_json_string(const std::string& json, const std::string& key) {
    // Simple JSON parsing - find "key" : "value"
    std::string search_key = "\"" + key + "\"";
    auto it = json.find(search_key);
    if (it == std::string::npos) return std::nullopt;
    
    // Find the colon
    size_t colon_pos = json.find(':', it + search_key.length());
    if (colon_pos == std::string::npos) return std::nullopt;
    
    // Skip whitespace and find opening quote
    size_t value_start = json.find('"', colon_pos);
    if (value_start == std::string::npos) return std::nullopt;
    
    // Find closing quote (simple version - doesn't handle escaped quotes)
    size_t value_end = json.find('"', value_start + 1);
    if (value_end == std::string::npos) return std::nullopt;
    
    return json.substr(value_start + 1, value_end - value_start - 1);
}

// Extract a numeric value from JSON
std::optional<int64_t> extract_json_int(const std::string& json, const std::string& key) {
    std::string search_key = "\"" + key + "\"";
    auto it = json.find(search_key);
    if (it == std::string::npos) return std::nullopt;
    
    size_t colon_pos = json.find(':', it + search_key.length());
    if (colon_pos == std::string::npos) return std::nullopt;
    
    // Skip whitespace
    size_t value_start = colon_pos + 1;
    while (value_start < json.size() && isspace(json[value_start])) {
        ++value_start;
    }
    
    // Parse integer
    const char* start = json.c_str() + value_start;
    char* end;
    int64_t value = strtoll(start, &end, 10);
    
    if (end == start) return std::nullopt;
    
    return value;
}

// Redact secrets from a message string
std::string redact_message_secrets(const std::string& message) {
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

}  // namespace

// ============================================================================
// JournaldAdapter Implementation
// ============================================================================

JournaldAdapter::JournaldAdapter(
    const JournaldConfig& config,
    OnEventCallback callback)
    : config_(config), callback_(std::move(callback)) {}

JournaldAdapter::~JournaldAdapter() {
    stop();
}

core::Outcome JournaldAdapter::start() {
    if (running_) {
        return core::Outcome::failure("E_ALREADY_STARTED", "Adapter already running");
    }
    
    // If cursor is set, we'll resume from there
    // Otherwise start from tail (or beginning for previous boot)
    
    running_ = true;
    metrics_.records_read = 0;
    metrics_.events_published = 0;
    metrics_.errors_parse_failed = 0;
    metrics_.errors_source_unavailable = 0;
    metrics_.records_dropped_backpressure = 0;
    
    return core::Outcome::success();
}

core::Outcome JournaldAdapter::stop() {
    if (!running_) {
        return core::Outcome::failure("E_NOT_RUNNING", "Adapter not running");
    }
    
    running_ = false;
    current_cursor_.reset();
    last_seen_cursor_.reset();
    
    return core::Outcome::success();
}

bool JournaldAdapter::is_running() const {
    return running_;
}

JournaldAdapter::AdapterMetrics JournaldAdapter::metrics() const {
    std::lock_guard<std::mutex> lock(metrics_mutex_);
    return metrics_;
}

std::optional<std::string> JournaldAdapter::get_cursor() const {
    std::lock_guard<std::mutex> lock(metrics_mutex_);
    return current_cursor_;
}

void JournaldAdapter::set_cursor(const std::string& cursor) {
    current_cursor_ = cursor;
}

core::Outcome JournaldAdapter::execute_journalctl(
    const std::vector<std::string>& argv,
    std::string& output,
    std::chrono::milliseconds timeout) {
    
    // Build the command: journalctl [args...]
    std::vector<std::string> cmd = {"/usr/bin/journalctl"};
    cmd.insert(cmd.end(), argv.begin(), argv.end());
    
    return execute_command(cmd, output, timeout);
}

std::optional<runtime::Event> JournaldAdapter::parse_json_record(
    const std::string& json_line,
    std::chrono::system_clock::time_point acquisition_time) {
    
    // Extract key fields from JSON
    auto message = extract_json_string(json_line, "MESSAGE");
    if (!message.has_value()) return std::nullopt;
    
    auto priority_str = extract_json_string(json_line, "PRIORITY");
    int priority = 6;  // Default info level
    if (priority_str.has_value()) {
        try {
            priority = std::stoi(priority_str.value());
        } catch (...) {
            priority = 6;
        }
    }
    
    auto unit = extract_json_string(json_line, "_SYSTEMD_UNIT");
    auto syslog_id = extract_json_string(json_line, "SYSLOG_IDENTIFIER");
    auto transport = extract_json_string(json_line, "_TRANSPORT");
    auto boot_id = extract_json_string(json_line, "_BOOT_ID");
    auto machine_id = extract_json_string(json_line, "_MACHINE_ID");
    auto cursor = extract_json_string(json_line, "__CURSOR");
    
    // Extract timestamps
    std::unordered_map<std::string, std::string> timestamp_fields;
    if (auto ts_opt = extract_json_string(json_line, "__REALTIME_TIMESTAMP")) {
        timestamp_fields["__REALTIME_TIMESTAMP"] = *ts_opt;
    }
    
    auto realtime_ts = extract_realtime_timestamp(timestamp_fields);
    
    std::chrono::system_clock::time_point timestamp;
    if (realtime_ts.has_value()) {
        timestamp = realtime_ts.value();
    } else {
        timestamp = acquisition_time;
    }
    
    // Build the event
    runtime::Event event;
    event.id = cursor.value_or("journal-" + std::to_string(timestamp.time_since_epoch().count()));
    event.occurred_at = timestamp;
    event.source = "journald";
    event.type = priority <= 3 ? "error" : (priority <= 5 ? "warning" : "info");
    
    // Add evidence with redaction for sensitive data in MESSAGE field
    core::Evidence msg_evidence;
    msg_evidence.source = "journal_message";
    
    // Redact secrets from the message value before storing as evidence
    std::string redacted_message = redact_message_secrets(message.value());
    msg_evidence.value = redacted_message;
    
    char buffer[64];
    auto now = std::chrono::system_clock::now();
    auto time_t_now = std::chrono::system_clock::to_time_t(now);
    struct tm tm_buf;
    gmtime_r(&time_t_now, &tm_buf);
    strftime(buffer, sizeof(buffer), "%Y-%m-%dT%H:%M:%SZ", &tm_buf);
    msg_evidence.captured_at = buffer;
    event.evidence.push_back(msg_evidence);
    
    if (unit.has_value()) {
        core::Evidence unit_evidence;
        unit_evidence.source = "journal_unit";
        unit_evidence.value = "_SYSTEMD_UNIT=" + unit.value();
        event.evidence.push_back(unit_evidence);
    }
    
    if (syslog_id.has_value()) {
        core::Evidence id_evidence;
        id_evidence.source = "journal_syslog_identifier";
        id_evidence.value = "SYSLOG_IDENTIFIER=" + syslog_id.value();
        event.evidence.push_back(id_evidence);
    }
    
    if (transport.has_value()) {
        core::Evidence transport_evidence;
        transport_evidence.source = "journal_transport";
        transport_evidence.value = "_TRANSPORT=" + transport.value();
        event.evidence.push_back(transport_evidence);
    }
    
    if (boot_id.has_value()) {
        core::Evidence boot_evidence;
        boot_evidence.source = "journal_boot_id";
        boot_evidence.value = "_BOOT_ID=" + boot_id.value();
        event.evidence.push_back(boot_evidence);
    }
    
    if (machine_id.has_value()) {
        core::Evidence machine_evidence;
        machine_evidence.source = "journal_machine_id";
        machine_evidence.value = "_MACHINE_ID=" + machine_id.value();
        event.evidence.push_back(machine_evidence);
    }
    
    // Update metrics
    {
        std::lock_guard<std::mutex> lock(metrics_mutex_);
        metrics_.records_read++;
        if (cursor.has_value()) {
            current_cursor_ = cursor;
            last_seen_cursor_ = cursor;
        }
    }
    
    return event;
}

std::optional<std::chrono::system_clock::time_point>
JournaldAdapter::extract_realtime_timestamp(
    const std::unordered_map<std::string, std::string>& fields) {
    
    auto it = fields.find("__REALTIME_TIMESTAMP");
    if (it == fields.end() || it->second.empty()) return std::nullopt;
    
    try {
        // The timestamp is in microseconds since epoch
        auto us = std::stoll(it->second);
        return std::chrono::system_clock::time_point(
            std::chrono::microseconds(us));
    } catch (...) {
        return std::nullopt;
    }
}

std::optional<std::chrono::steady_clock::time_point>
JournaldAdapter::extract_monotonic_timestamp(
    const std::unordered_map<std::string, std::string>& fields) {
    
    auto it = fields.find("__MONOTONIC_TIMESTAMP");
    if (it == fields.end() || it->second.empty()) return std::nullopt;
    
    try {
        // The timestamp is in microseconds
        auto us = std::stoll(it->second);
        return std::chrono::steady_clock::time_point(
            std::chrono::microseconds(us));
    } catch (...) {
        return std::nullopt;
    }
}

// ============================================================================
// JournaldQuery Implementation
// ============================================================================

std::vector<std::string> JournaldQuery::build_argv(const QueryConfig& config) {
    std::vector<std::string> argv;
    
    // Boot filtering
    if (config.boot_id.has_value()) {
        if (config.boot_id.value() == 0) {
            argv.push_back("--boot");
        } else {
            argv.push_back("-b");
            argv.push_back(std::to_string(config.boot_id.value()));
        }
    }
    
    // Time window
    if (config.since.has_value()) {
        auto since_epoch = std::chrono::duration_cast<std::chrono::seconds>(
            config.since.value().time_since_epoch()).count();
        argv.push_back("--since");
        argv.push_back("@" + std::to_string(since_epoch));
    }
    
    if (config.until.has_value()) {
        auto until_epoch = std::chrono::duration_cast<std::chrono::seconds>(
            config.until.value().time_since_epoch()).count();
        argv.push_back("--until");
        argv.push_back("@" + std::to_string(until_epoch));
    }
    
    // Record limits
    if (config.max_records > 0) {
        argv.push_back("-n");
        argv.push_back(std::to_string(config.max_records));
    }
    
    // Unit filters
    for (const auto& unit : config.units) {
        argv.push_back("-u");
        argv.push_back(unit);
    }
    
    // Priority filter
    if (config.min_priority.has_value()) {
        argv.push_back("--priority");
        argv.push_back(std::to_string(config.min_priority.value()));
    }
    
    // Output format for structured parsing
    argv.push_back("--output=json");
    
    return argv;
}

}  // namespace rebuntu::adapters