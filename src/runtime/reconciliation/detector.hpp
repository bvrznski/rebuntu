// rebuntu::runtime::reconciliation::detector — Crash/Restart Detection (Phase 6.40)
//
// This module provides crash and restart detection for the reconciliation system.
// After a system restart, pending operations can be discovered from durable records
// and reconciled using fresh Phase-5 observations.
//
// Detection mechanisms:
//   * Process state file timestamp comparison
//   * System uptime change analysis
//   * Operation record modification timestamps vs boot time

#pragma once

#include <chrono>
#include <fstream>
#include <filesystem>
#include <optional>
#include <string>

namespace rebuntu::runtime::reconciliation {

// ============================================================================
// RestartEvidence — Evidence that a restart occurred since last shutdown
//
// This class collects and analyzes various signals to determine if the system
// restarted between two observation points.
// ============================================================================
class RestartEvidence {
public:
    // Boot time (when kernel started)
    std::chrono::system_clock::time_point boot_time;
    
    // Previous shutdown/crash marker timestamp (from disk)
    std::optional<std::chrono::system_clock::time_point> last_shutdown_marker;
    
    // Current system uptime in seconds
    std::chrono::seconds current_uptime_seconds{0};
    
    // Whether a restart is detected
    bool restart_detected = false;
    
    // Human-readable explanation for the detection result
    std::string explanation;
    
    static RestartEvidence detect_from_procfs() {
        RestartEvidence e;
        
        // Read uptime from /proc/uptime (seconds since boot)
        if (auto uptime_str = read_file_string("/proc/uptime")) {
            if (!uptime_str->empty()) {
                double uptime_seconds = std::stod(*uptime_str);
                e.current_uptime_seconds = std::chrono::duration_cast<std::chrono::seconds>(
                    std::chrono::milliseconds(static_cast<int64_t>(uptime_seconds * 1000)));
                
                // Get current time
                auto now = std::chrono::system_clock::now();
                
                // Calculate boot time (now - uptime)
                e.boot_time = now - e.current_uptime_seconds;
                
                return e;
            }
        }
        
        // Fallback: assume we're running since some reasonable time
        e.current_uptime_seconds = std::chrono::seconds(300);  // 5 minutes
        e.boot_time = std::chrono::system_clock::now() - e.current_uptime_seconds;
        return e;
    }
    
    static std::optional<std::string> read_file_string(const std::filesystem::path& path) {
        std::error_code ec;
        if (!std::filesystem::exists(path, ec)) {
            return std::nullopt;
        }
        
        std::ifstream file(path);
        if (!file.is_open()) {
            return std::nullopt;
        }
        
        std::string content((std::istreambuf_iterator<char>(file)),
                           std::istreambuf_iterator<char>());
        return content;
    }
};

// ============================================================================
// CrashIndicator — File system marker for crash detection
//
// A simple file-based mechanism to track if the process shut down cleanly.
// When rebuntu starts, it looks for a "dirty" indicator:
//   * If shutdown_marker exists and is recent → clean shutdown likely
//   * If shutdown_marker doesn't exist or is old + operations pending → restart/crash detected
// ============================================================================
class CrashIndicator {
public:
    explicit CrashIndicator(const std::filesystem::path& state_dir)
        : state_directory_(state_dir) {}
    
    // Path where we store the crash indicator files
    std::filesystem::path state_directory_;
    
    // The marker file path for tracking shutdown state
    std::filesystem::path marker_path() const {
        return state_directory_ / "rebuntu_shutdown_marker";
    }
    
    // Create a clean shutdown marker (called during graceful shutdown)
    bool mark_clean_shutdown() const {
        std::error_code ec;
        
        // Write current timestamp to marker file
        auto now = std::chrono::system_clock::now();
        auto epoch_ms = std::chrono::duration_cast<std::chrono::milliseconds>(
            now.time_since_epoch()).count();
        
        std::ofstream file(marker_path());
        if (!file.is_open()) {
            return false;
        }
        
        file << epoch_ms;
        return true;
    }
    
    // Check if a clean shutdown was recorded
    // Returns: timestamp of last clean shutdown (if exists), nullopt otherwise
    std::optional<std::chrono::system_clock::time_point> get_last_clean_shutdown() const {
        std::error_code ec;
        
        if (!std::filesystem::exists(marker_path(), ec)) {
            return std::nullopt;  // No marker file - unclean shutdown or first run
        }
        
        auto content = RestartEvidence::read_file_string(marker_path());
        if (!content) {
            return std::nullopt;
        }
        
        try {
            int64_t epoch_ms = std::stoll(*content);
            return std::chrono::system_clock::time_point{
                std::chrono::milliseconds(epoch_ms)};
        } catch (...) {
            return std::nullopt;  // Invalid content
        }
    }
    
    // Check if a restart likely occurred since the last recorded shutdown
    bool detect_restart() const {
        auto last_shutdown = get_last_clean_shutdown();
        
        if (!last_shutdown.has_value()) {
            // No previous clean shutdown recorded - this could be first run
            return false;  // Don't treat first run as a "restart"
        }
        
        // Compare with current uptime to see if boot time is after shutdown
        auto evidence = RestartEvidence::detect_from_procfs();
        return evidence.boot_time > last_shutdown.value();
    }
    
    // Remove the crash marker (called after reconciliation completes)
    bool clear_marker() const {
        std::error_code ec;
        return std::filesystem::remove(marker_path(), ec);
    }
};

// ============================================================================
// PendingOperationDetector — Detects pending operations from durable records
//
// Scans operation record storage and identifies operations that were in progress
// at the time of crash/interruption.
// ============================================================================
class PendingOperationDetector {
public:
    explicit PendingOperationDetector(const std::filesystem::path& record_dir)
        : record_directory_(record_dir) {}
    
    std::filesystem::path record_directory_;
    
    // Maximum number of pending operations to process in one reconciliation pass
    size_t max_pending_operations = 100;
    
    // Structure describing a detected pending operation
    struct PendingOperationInfo {
        std::string record_id;
        std::chrono::system_clock::time_point created_at;
        std::optional<std::chrono::system_clock::time_point> interrupted_at;
        std::filesystem::path record_path;  // Path to the record file
    };
    
    // Scan for pending operations
    std::vector<PendingOperationInfo> scan_pending() const {
        std::vector<PendingOperationInfo> results;
        std::error_code ec;
        
        if (!std::filesystem::exists(record_directory_, ec)) {
            return results;  // No records directory - nothing to find
        }
        
        // Scan the record directory for operation files
        for (auto& entry : std::filesystem::directory_iterator(record_directory_, ec)) {
            if (ec) break;
            
            // Only process regular files with .json or .rec extension
            auto ext = entry.path().extension();
            if (ext != ".json" && ext != ".rec") {
                continue;
            }
            
            PendingOperationInfo info;
            info.record_id = entry.path().filename().string();
            info.record_path = entry.path();
            
            // Try to parse the file for timestamps
            parse_record_timestamps(entry.path(), &info);
            
            results.push_back(info);
            
            if (results.size() >= max_pending_operations) {
                break;
            }
        }
        
        return results;
    }
    
private:
    // Parse timestamp information from a record file
    void parse_record_timestamps(const std::filesystem::path& path,
                                 PendingOperationInfo* info) const {
        // In a full implementation, this would:
        // 1. Open and parse the JSON record file
        // 2. Extract created_at and interrupted_at timestamps
        //
        // For now, we use current time as a placeholder
        
        std::error_code ec;
        auto status = std::filesystem::status(path, ec);
        if (!ec && status.type() == std::filesystem::file_type::regular) {
            info->created_at = status.creation_time();
        } else {
            info->created_at = std::chrono::system_clock::now();
        }
    }
};

}  // namespace rebuntu::runtime::reconciliation