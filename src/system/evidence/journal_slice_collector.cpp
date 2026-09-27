// rebuntu::evidence::journal_slice — Journal Slice Collector Implementation (Phase 5.59)
//
// This module implements the journal slice collector that acquires bounded
// diagnostic evidence from journald for provider failures and important resync events.

#include "system/evidence/journal_slice_collector.hpp"

#include <optional>
#include <cstdlib>
#include <cstring>
#include <cstddef>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <cerrno>
#include <memory>
#include <string_view>
#include <array>
#include <sstream>

#include "adapters/journald.hpp"

namespace rebuntu::evidence {

// ============================================================================
// Helper Functions for Command Execution
// ============================================================================

namespace {
    
core::Outcome execute_command(
    const std::vector<std::string>& argv,
    std::string& stdout_output,
    std::chrono::milliseconds timeout) {
    
    std::vector<char*> args;
    for (const auto& arg : argv) {
        args.push_back(const_cast<char*>(arg.c_str()));
    }
    args.push_back(nullptr);
    
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
        close(pipefd[0]);
        dup2(pipefd[1], STDOUT_FILENO);
        execv(args[0], args.data());
        _exit(127);
    }
    
    close(pipefd[1]);
    
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
            
            tv.tv_sec = timeout.count() / 1000;
            tv.tv_usec = (timeout.count() % 1000) * 1000;
            FD_ZERO(&read_fds);
            FD_SET(pipefd[0], &read_fds);
        }
    }
    
    close(pipefd[0]);
    
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

std::optional<std::string> extract_json_string(const std::string& json, const std::string& key) {
    std::string search_key = "\"" + key + "\"";
    auto it = json.find(search_key);
    if (it == std::string::npos) return std::nullopt;
    
    size_t colon_pos = json.find(':', it + search_key.length());
    if (colon_pos == std::string::npos) return std::nullopt;
    
    size_t value_start = json.find('"', colon_pos);
    if (value_start == std::string::npos) return std::nullopt;
    
    size_t value_end = json.find('"', value_start + 1);
    if (value_end == std::string::npos) return std::nullopt;
    
    return json.substr(value_start + 1, value_end - value_start - 1);
}

std::string redact_secrets_from_message(const std::string& message) {
    std::string result = message;
    std::string lower_result = message;
    
    std::transform(lower_result.begin(), lower_result.end(), lower_result.begin(),
                   [](unsigned char c){ return static_cast<char>(std::tolower(c)); });
    
    const std::vector<std::string> patterns = {"password", "token", "secret", "authorization"};
    
    for (const auto& pattern : patterns) {
        size_t pos = 0;
        while ((pos = lower_result.find(pattern, pos)) != std::string::npos) {
            size_t after_key = pos + pattern.size();
            
            while (after_key < result.size() && 
                   std::isspace(result[after_key]) && 
                   result[after_key] != '=') {
                after_key++;
            }
            
            if (after_key < result.size() && result[after_key] == '=') {
                size_t after_eq = after_key + 1;
                
                while (after_eq < result.size() && std::isspace(result[after_eq])) {
                    after_eq++;
                }
                
                if (after_eq < result.size()) {
                    char quote_char = 0;
                    
                    if (result[after_eq] == '"' || result[after_eq] == '\'') {
                        quote_char = result[after_eq];
                        size_t end_pos = after_eq + 1;
                        
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
                            
                            lower_result = result;
                            std::transform(lower_result.begin(), lower_result.end(), 
                                          lower_result.begin(),
                                          [](unsigned char c){ return static_cast<char>(std::tolower(c)); });
                        }
                    } else {
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
// JournalSliceCollector Implementation
// ============================================================================

JournalSliceCollector::JournalSliceCollector(
    const adapters::JournaldConfig& adapter_config,
    OnRecordCallback callback)
    : adapter_config_(adapter_config), 
      callback_(std::move(callback)) {}

JournalSliceCollector::~JournalSliceCollector() {
    stop();
}

core::Outcome JournalSliceCollector::start() {
    if (running_) {
        return core::Outcome::failure("E_ALREADY_STARTED", "Collector already running");
    }
    
    adapter_ = adapters::make_journald_adapter(adapter_config_, 
        [this](const runtime::Event& event) {
            // This callback is for follow mode; we handle batch collection differently
        });
    
    if (!adapter_) {
        return core::Outcome::failure("E_ADAPTER_FAILED", "Failed to create journald adapter");
    }
    
    auto outcome = adapter_->start();
    if (outcome.status != core::SemanticStatus::kSuccess) {
        adapter_.reset();
        return outcome;
    }
    
    running_ = true;
    
    return core::Outcome::success();
}

core::Outcome JournalSliceCollector::stop() {
    if (!running_) {
        return core::Outcome::failure("E_NOT_RUNNING", "Collector not running");
    }
    
    auto outcome = adapter_->stop();
    
    adapter_.reset();
    running_ = false;
    
    return outcome;
}

bool JournalSliceCollector::is_running() const {
    return running_;
}

std::string JournalSliceCollector::redact_secrets(const std::string& message) {
    return redact_secrets_from_message(message);
}

JournalSliceResult JournalSliceCollector::collect_slice(
    const std::chrono::system_clock::time_point& since,
    const std::chrono::system_clock::time_point& until,
    size_t max_records) {
    
    auto start_time = std::chrono::steady_clock::now();
    
    JournalSliceResult result;
    result.status = core::SemanticStatus::kUnknown;
    
    if (!running_) {
        auto outcome = start();
        if (outcome.status != core::SemanticStatus::kSuccess) {
            result.description = "Failed to start collector: " + outcome.error.value_or(core::Error{}).message;
            std::lock_guard<std::mutex> lock(stats_mutex_);
            collector_stats_.collections_failed++;
            return result;
        }
    }
    
    // Build journctl arguments for the time window
    std::vector<std::string> argv;
    
    // Add boot filter if configured
    if (adapter_config_.boot_id.has_value()) {
        argv.push_back("-b");
        argv.push_back(std::to_string(adapter_config_.boot_id.value()));
    }
    
    // Since timestamp
    auto since_epoch = std::chrono::duration_cast<std::chrono::seconds>(
        since.time_since_epoch()).count();
    argv.push_back("--since");
    argv.push_back("@" + std::to_string(since_epoch));
    
    // Until timestamp  
    auto until_epoch = std::chrono::duration_cast<std::chrono::seconds>(
        until.time_since_epoch()).count();
    argv.push_back("--until");
    argv.push_back("@" + std::to_string(until_epoch));
    
    // Record limit
    argv.push_back("-n");
    argv.push_back(std::to_string(max_records));
    
    // Add unit filters if configured
    for (const auto& unit : adapter_config_.units) {
        argv.push_back("-u");
        argv.push_back(unit);
    }
    
    // Output format for structured parsing
    argv.push_back("--output=json");
    
    std::string output;
    auto outcome = execute_command({"/usr/bin/journalctl"}, output, 
                                   adapter_config_.query_timeout_ms);
    
    if (outcome.status != core::SemanticStatus::kSuccess) {
        result.description = "journalctl execution failed: " + 
            outcome.error.value_or(core::Error{}).message;
        
        std::lock_guard<std::mutex> lock(stats_mutex_);
        collector_stats_.collections_failed++;
        return result;
    }
    
    // Parse JSON output line by line
    std::istringstream stream(output);
    std::string line;
    size_t record_count = 0;
    size_t secrets_redacted = 0;
    
    // Variables to track first-record metadata for result (outside loop scope)
    std::optional<std::string> boot_id_opt;
    std::optional<std::string> machine_id_opt;
    
    while (std::getline(stream, line) && record_count < max_records) {
        if (line.empty()) continue;
        
        // Extract fields
        auto message_opt = extract_json_string(line, "MESSAGE");
        if (!message_opt.has_value()) continue;
        
        auto priority_str = extract_json_string(line, "PRIORITY");
        int priority = 6;  // Default info level
        if (priority_str.has_value()) {
            try {
                priority = std::stoi(priority_str.value());
            } catch (...) {
                priority = 6;
            }
        }
        
        auto unit_opt = extract_json_string(line, "_SYSTEMD_UNIT");
        auto syslog_id_opt = extract_json_string(line, "SYSLOG_IDENTIFIER");
        auto cursor_opt = extract_json_string(line, "__CURSOR");
        auto first_boot_id_opt = extract_json_string(line, "_BOOT_ID");
        auto first_machine_id_opt = extract_json_string(line, "_MACHINE_ID");
        
        // Capture boot_id and machine_id from first record for result metadata
        if (!boot_id_opt.has_value() && first_boot_id_opt.has_value()) {
            boot_id_opt = first_boot_id_opt;
        }
        if (!machine_id_opt.has_value() && first_machine_id_opt.has_value()) {
            machine_id_opt = first_machine_id_opt;
        }
        
        // Build event
        runtime::Event event;
        event.id = cursor_opt.value_or("journal-" + std::to_string(
            since.time_since_epoch().count()));
        event.occurred_at = since;
        event.source = "journald";
        event.type = priority <= 3 ? "error" : (priority <= 5 ? "warning" : "info");
        
        // Add evidence with redaction
        core::Evidence msg_evidence;
        msg_evidence.source = "journal_message";
        std::string redacted_message = redact_secrets(message_opt.value());
        if (redacted_message != message_opt.value()) {
            secrets_redacted++;
        }
        msg_evidence.value = redacted_message;
        
        char buffer[64];
        auto now = std::chrono::system_clock::now();
        auto time_t_now = std::chrono::system_clock::to_time_t(now);
        struct tm tm_buf;
        gmtime_r(&time_t_now, &tm_buf);
        strftime(buffer, sizeof(buffer), "%Y-%m-%dT%H:%M:%SZ", &tm_buf);
        msg_evidence.captured_at = buffer;
        event.evidence.push_back(msg_evidence);
        
        if (unit_opt.has_value()) {
            core::Evidence unit_evidence;
            unit_evidence.source = "journal_unit";
            unit_evidence.value = "_SYSTEMD_UNIT=" + unit_opt.value();
            event.evidence.push_back(unit_evidence);
        }
        
        // Create record
        JournalSliceResult::Record record;
        record.event = std::move(event);
        record.cursor = cursor_opt.value_or("");
        record.acquisition_time = std::chrono::system_clock::now();
        
        result.records.push_back(record);
        record_count++;
        
        // Call callback if provided
        if (callback_) {
            callback_(record);
        }
    }
    
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::steady_clock::now() - start_time);
    
    result.status = core::SemanticStatus::kSuccess;
    result.description = "Collected " + std::to_string(record_count) + " journal records";
    result.total_records_available = record_count;  // In this bounded query, we get all available
        // Set result metadata from first-record values
        if (boot_id_opt.has_value()) {
            result.boot_id = boot_id_opt;
        }
        if (machine_id_opt.has_value()) {
            result.machine_id = machine_id_opt;
        }
    
    result.stats.records_collected = record_count;
    result.stats.secrets_redacted = secrets_redacted;
    result.stats.elapsed_ms = elapsed;
    
    std::lock_guard<std::mutex> lock(stats_mutex_);
    collector_stats_.collections_completed++;
    collector_stats_.total_records_collected += record_count;
    collector_stats_.total_secrets_redacted += secrets_redacted;
    collector_stats_.total_elapsed_ms += elapsed;
    
    return result;
}

JournalSliceCollector::CollectorStats JournalSliceCollector::stats() const {
    std::lock_guard<std::mutex> lock(stats_mutex_);
    return collector_stats_;
}

// ============================================================================
// Factory Functions
// ============================================================================

std::unique_ptr<JournalSliceCollector> make_journal_slice_collector(
    const adapters::JournaldConfig& config,
    JournalSliceCollector::OnRecordCallback callback) {
    return std::make_unique<JournalSliceCollector>(config, std::move(callback));
}

}  // namespace rebuntu::evidence