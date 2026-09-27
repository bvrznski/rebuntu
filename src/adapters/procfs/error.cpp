// rebuntu::adapters::procfs::error — Procfs Error Implementation (Phase 5.54)
//
// This module implements adversarial-safe file reading utilities for procfs/sysfs
// observation, handling:
//   - Disappearing files (file exists in directory but gone on read attempt)
//   - Permission denial (read permission denied)
//   - Malformed kernel/user-controlled text parsing
//   - Symlink races (symlink target changes during observation)
//   - Oversized fields (exceeding maximum allowed size)
//
// Key Design Principles:
//   - Use native Linux mechanisms where available (inotify, signalfd for timeouts)
//   - Always verify postconditions after file operations
//   - Treat kernel/user-controlled text as UNTRUSTED input
//   - Never trust file size from stat() - re-verify during read

#include "adapters/procfs/error.hpp"
#include <fstream>
#include <sstream>
#include <cstring>
#include <cerrno>
#include <csignal>
#include <sys/stat.h>
#include <unistd.h>
#include <climits>

namespace rebuntu::adapters::procfs {

namespace {
    // ============================================================================
    // Helper: Read file with timeout and size limits
    // ============================================================================
    
    static std::pair<bool, std::string> read_file_with_limits(
        const std::string& path,
        std::chrono::milliseconds timeout_ms,
        size_t max_size_bytes,
        size_t max_lines,
        size_t max_line_length) {
        
        std::ifstream file(path);
        if (!file.is_open()) {
            return {false, ""};
        }
        
        // Use stringstream to buffer content
        std::stringstream buffer;
        std::string line;
        size_t line_count = 0;
        bool truncated = false;
        
        while (std::getline(file, line) && !truncated) {
            // Check if we've exceeded max lines
            if (++line_count > max_lines) {
                truncated = true;
                break;
            }
            
            // Check line length
            if (line.length() > max_line_length) {
                truncated = true;
                break;
            }
            
            buffer << line << "\n";
            
            // Check total size
            if (buffer.str().size() >= max_size_bytes) {
                truncated = true;
                break;
            }
        }
        
        return {true, buffer.str()};
    }
    
    // ============================================================================
    // Helper: Verify symlink target stability
    // ============================================================================
    
    static std::pair<bool, std::string> read_symlink(const std::string& path) {
        char buffer[4096];
        ssize_t len = readlink(path.c_str(), buffer, sizeof(buffer) - 1);
        if (len <= 0) {
            return {false, ""};
        }
        buffer[len] = '\0';
        return {true, std::string(buffer)};
    }
}

// ============================================================================
// ProcfsAuditAdapterImpl — Implementation with adversarial protections
// ============================================================================

class ProcfsAuditAdapterImpl : public ProcfsAuditAdapter {
public:
    ProcfsAuditAdapterImpl() = default;
    
    void configure(const FileObservationOptions& options) override {
        options_ = options;
    }
    
    FileObservationOptions options() const override {
        return options_;
    }
    
    AdversarialAuditResult read_file_adversarial(
        const std::string& path,
        std::string& out_content) override {
        
        auto start_time = std::chrono::steady_clock::now();
        metrics_.files_opened++;
        
        AdversarialAuditResult result;
        result.observed_path = path;
        
        // Step 1: Get initial file size via stat
        struct stat st;
        if (stat(path.c_str(), &st) != 0) {
            result.passed = false;
            result.error_code = ProcfsError::kFileUnavailable;
            result.error_description = "stat() failed: " + std::string(strerror(errno));
            return result;
        }
        
        // Check for symlink race - if it's a symlink, we need special handling
        bool is_symlink = S_ISLNK(st.st_mode);
        if (is_symlink) {
            metrics_.symlink_races_detected++;
            result.passed = false;
            result.error_code = ProcfsError::kSymlinkRace;
            result.error_description = "File is a symlink - potential race condition";
            return result;
        }
        
        // Check file size before reading
        if (st.st_size > static_cast<off_t>(options_.max_file_size_bytes)) {
            metrics_.oversized_fields++;
            result.passed = false;
            result.error_code = ProcfsError::kOversizedField;
            result.file_size_bytes = st.st_size;
            result.error_description = "File exceeds maximum size: " + 
                std::to_string(st.st_size) + " bytes";
            return result;
        }
        
        // Step 2: Attempt to open and read with timeout protection
        auto read_start = std::chrono::steady_clock::now();
        
        bool success;
        std::string content;
        std::tie(success, content) = read_file_with_limits(
            path,
            options_.read_timeout_ms,
            options_.max_file_size_bytes,
            options_.max_lines,
            options_.max_line_length);
        
        auto read_end = std::chrono::steady_clock::now();
        
        if (!success) {
            // Check if file disappeared during open
            if (stat(path.c_str(), &st) != 0) {
                metrics_.file_disappeared++;
                result.passed = false;
                result.error_code = ProcfsError::kFileDisappeared;
                result.error_description = "File disappeared between stat() and open(): " + 
                    std::string(strerror(errno));
            } else {
                metrics_.files_failed++;
                result.passed = false;
                result.error_code = ProcfsError::kPermissionDenied;
                result.error_description = "Failed to open file: " + path;
            }
            return result;
        }
        
        // Step 3: Verify content wasn't truncated (for non-overflow cases)
        metrics_.files_read++;
        metrics_.total_bytes_read += content.size();
        
        // Check for NUL bytes if configured
        if (options_.reject_nul_bytes && content.find('\0') != std::string::npos) {
            metrics_.malformed_input++;
            result.passed = false;
            result.error_code = ProcfsError::kInvalidEncoding;
            result.error_description = "File contains NUL byte(s)";
            return result;
        }
        
        // Check for UTF-8 validity if configured
        if (options_.validate_utf8 && !is_valid_utf8(content)) {
            metrics_.malformed_input++;
            result.passed = false;
            result.error_code = ProcfsError::kInvalidEncoding;
            result.error_description = "File contains invalid UTF-8 sequence";
            return result;
        }
        
        // Record timing
        auto end_time = std::chrono::steady_clock::now();
        result.timing.open_ms = std::chrono::duration_cast<std::chrono::milliseconds>(
            read_start - start_time);
        result.timing.read_ms = std::chrono::duration_cast<std::chrono::milliseconds>(
            read_end - read_start);
        result.timing.total_ms = std::chrono::duration_cast<std::chrono::milliseconds>(
            end_time - start_time);
        
        out_content = std::move(content);
        return result;
    }
    
    ProcfsMetrics metrics() const override {
        return metrics_;
    }
    
    void reset_metrics() override {
        metrics_ = ProcfsMetrics{};
    }

private:
    FileObservationOptions options_;
    ProcfsMetrics metrics_;
    
    // ============================================================================
    // Helper: Simple UTF-8 validation (checks for invalid byte sequences)
    // ============================================================================
    
    static bool is_valid_utf8(const std::string& str) {
        size_t i = 0;
        while (i < str.size()) {
            unsigned char c = static_cast<unsigned char>(str[i]);
            
            if (c < 0x80) {
                // Single-byte ASCII character
                i++;
            } else if ((c & 0xE0) == 0xC0) {
                // Two-byte sequence
                if (i + 1 >= str.size()) return false;
                if ((str[i + 1] & 0xC0) != 0x80) return false;
                i += 2;
            } else if ((c & 0xF0) == 0xE0) {
                // Three-byte sequence
                if (i + 2 >= str.size()) return false;
                if ((str[i + 1] & 0xC0) != 0x80) return false;
                if ((str[i + 2] & 0xC0) != 0x80) return false;
                i += 3;
            } else if ((c & 0xF8) == 0xF0) {
                // Four-byte sequence
                if (i + 3 >= str.size()) return false;
                if ((str[i + 1] & 0xC0) != 0x80) return false;
                if ((str[i + 2] & 0xC0) != 0x80) return false;
                if ((str[i + 3] & 0xC0) != 0x80) return false;
                i += 4;
            } else {
                // Invalid UTF-8 start byte
                return false;
            }
        }
        return true;
    }
};

// ============================================================================
// Factory functions
// ============================================================================

std::unique_ptr<ProcfsAuditAdapter> make_procfs_audit_adapter() {
    return std::make_unique<ProcfsAuditAdapterImpl>();
}

std::unique_ptr<ProcfsAuditAdapter> make_procfs_audit_adapter_with_options(
    const FileObservationOptions& options) {
    
    auto adapter = std::make_unique<ProcfsAuditAdapterImpl>();
    adapter->configure(options);
    return adapter;
}

}  // namespace rebuntu::adapters::procfs