// rebuntu::adapters::procfs — Procfs error types (Phase 5.54)
//
// Adversarial audit error definitions for procfs/sysfs observation:
//   - Disappearing files
//   - Permission denial
//   - Malformed input handling
//   - Symlink races
//   - Oversized fields

#pragma once

#include <string>
#include <cstdint>
#include <chrono>
#include <memory>
#include <optional>

namespace rebuntu::adapters::procfs {

// ============================================================================
// ProcfsError — Errors specific to procfs/sysfs observation
//
// Each error code has a stable identifier that can be used for:
//   - Machine-readable error handling
//   - Logging and diagnostics
//   - Monitoring and alerting
//
// Error codes follow the pattern: E_PROCFSSYSFS_<CATEGORY>_<CAUSE>
// ============================================================================

enum class ProcfsError {
    // File access errors
    kFileUnavailable,       // File exists in directory listing but cannot be opened
    kPermissionDenied,      // Open succeeds but read fails due to permissions
    kPathNotFound,          // Path component does not exist
    
    // Race condition errors
    kSymlinkRace,           // Symlink target changed during observation
    kFileDisappeared,       // File was deleted between check and open
    kDirectoryChanged,      // Directory structure changed during enumeration
    
    // Parsing/Validation errors
    kMalformedInput,        // Input format is invalid or malformed
    kOversizedField,        // Field exceeds maximum allowed size
    kParseOverflow,         // Numeric value overflowed expected range
    kInvalidEncoding,       // Text encoding is invalid or contains NUL bytes
    
    // Resource errors
    kTimeout,               // Read operation exceeded timeout
    kResourceLimitExceeded, // Exceeded memory/size budget for read
};

inline std::string to_string(ProcfsError error) {
    switch (error) {
        case ProcfsError::kFileUnavailable:      return "E_PROCFSSYSFS_FILE_UNAVAILABLE";
        case ProcfsError::kPermissionDenied:     return "E_PROCFSSYSFS_PERMISSION_DENIED";
        case ProcfsError::kPathNotFound:         return "E_PROCFSSYSFS_PATH_NOT_FOUND";
        case ProcfsError::kSymlinkRace:          return "E_PROCFSSYSFS_SYMLINK_RACE";
        case ProcfsError::kFileDisappeared:      return "E_PROCFSSYSFS_FILE_DISAPPEARED";
        case ProcfsError::kDirectoryChanged:     return "E_PROCFSSYSFS_DIRECTORY_CHANGED";
        case ProcfsError::kMalformedInput:       return "E_PROCFSSYSFS_MALFORMED_INPUT";
        case ProcfsError::kOversizedField:       return "E_PROCFSSYSFS_OVERSIZED_FIELD";
        case ProcfsError::kParseOverflow:        return "E_PROCFSSYSFS_PARSE_OVERFLOW";
        case ProcfsError::kInvalidEncoding:      return "E_PROCFSSYSFS_INVALID_ENCODING";
        case ProcfsError::kTimeout:              return "E_PROCFSSYSFS_TIMEOUT";
        case ProcfsError::kResourceLimitExceeded:return "E_PROCFSSYSFS_RESOURCE_LIMIT_EXCEEDED";
    }
    return "E_UNKNOWN_PROCFS_ERROR";
}

// ============================================================================
// AuditTiming — Timing information for adversarial audit
// ============================================================================

struct AuditTiming {
    std::chrono::milliseconds open_ms{0};
    std::chrono::milliseconds read_ms{0};
    std::chrono::milliseconds total_ms{0};
};

// ============================================================================
// AdversarialAuditResult — Result of an adversarial audit check
//
// Used to track whether observation succeeded, and if not, what type
// of adversarial condition was encountered.
// ============================================================================

struct AdversarialAuditResult {
    bool passed{true};                // true if audit check passed (no adversarial conditions)
    
    // Error details (if passed == false)
    ProcfsError error_code{ProcfsError::kFileUnavailable};
    std::string error_description;
    
    // Timing information for debugging
    AuditTiming timing;
    
    // Observed state at time of failure (for debugging)
    std::optional<std::string> observed_path;      // What path was being accessed
    std::optional<int64_t> file_size_bytes;        // What size was observed
    
    static AdversarialAuditResult success() {
        AdversarialAuditResult r;
        r.passed = true;
        return r;
    }
    
    static AdversarialAuditResult failure(ProcfsError code, std::string description) {
        AdversarialAuditResult r;
        r.passed = false;
        r.error_code = code;
        r.error_description = std::move(description);
        return r;
    }
};

// ============================================================================
// FileObservationOptions — Configuration for adversarial-safe file reading
//
// These options control how strictly the adapter validates file contents
// and what protections are applied against adversarial conditions.
// ============================================================================

struct FileObservationOptions {
    // Timeouts (in milliseconds)
    std::chrono::milliseconds open_timeout_ms{100};   // Max time to open a file
    std::chrono::milliseconds read_timeout_ms{500};   // Max time for a single read operation
    
    // Size limits
    size_t max_file_size_bytes{128 * 1024};           // 128KB default - most proc files are small
    size_t max_line_length{4096};                     // Maximum length of a single line
    size_t max_lines{1000};                           // Maximum number of lines to read
    
    // Validation options
    bool validate_utf8{true};                         // Validate UTF-8 encoding
    bool reject_nul_bytes{true};                      // Reject files containing NUL bytes
    bool verify_symlink_target{false};                // Verify symlink target (expensive)
    
    // Behavior on error
    enum class OnError {
        kFail,            // Return error immediately
        kSkip,            // Skip this file and continue with others
        kPartial,         // Return partial results with error flag set
    } on_error{OnError::kSkip};
};

// ============================================================================
// ProcfsMetrics — Runtime metrics for procfs observation
//
// Tracks both successful observations and adversarial events.
// ============================================================================

struct ProcfsMetrics {
    std::chrono::system_clock::time_point started_at{};
    
    // File operation statistics
    size_t files_opened{0};
    size_t files_read{0};
    size_t files_failed{0};
    size_t files_skipped{0};
    
    // Adversarial event counts
    size_t symlink_races_detected{0};
    size_t permission_denied{0};
    size_t file_disappeared{0};
    size_t malformed_input{0};
    size_t oversized_fields{0};
    size_t parse_overflows{0};
    size_t timeouts{0};
    
    // Resource usage
    size_t total_bytes_read{0};
    std::chrono::milliseconds total_time_ms{0};
};

// ============================================================================
// ProcfsAuditAdapter — Interface for adversarial audit operations
//
// Provides utilities to safely read from procfs/sysfs while detecting
// and handling adversarial conditions.
// ============================================================================

class ProcfsAuditAdapter {
public:
    virtual ~ProcfsAuditAdapter() = default;
    
    // Configure adversarial protection settings
    virtual void configure(const FileObservationOptions& options) = 0;
    
    // Get current configuration
    virtual FileObservationOptions options() const = 0;
    
    // Read file with adversarial protections
    // Returns audit result indicating whether the read was safe or if
    // an adversarial condition was detected
    virtual AdversarialAuditResult read_file_adversarial(
        const std::string& path,
        std::string& out_content) = 0;
    
    // Read file with adversarial protections, returning parsed content
    template<typename T>
    AdversarialAuditResult read_and_parse_file(
        const std::string& path,
        T& out_value) {
        std::string content;
        auto result = read_file_adversarial(path, content);
        if (!result.passed) {
            return result;
        }
        
        // Parse the content
        return parse_content(content, out_value);
    }
    
    // Get runtime metrics
    virtual ProcfsMetrics metrics() const = 0;
    
    // Reset metrics (e.g., at start of a new observation cycle)
    virtual void reset_metrics() = 0;

private:
    template<typename T>
    AdversarialAuditResult parse_content(const std::string& content, T& out_value) {
        // Default implementation - may be specialized
        return AdversarialAuditResult::failure(
            ProcfsError::kMalformedInput,
            "No parser implemented for type");
    }
};

// ============================================================================
// Factory functions
// ============================================================================

std::unique_ptr<ProcfsAuditAdapter> make_procfs_audit_adapter();
std::unique_ptr<ProcfsAuditAdapter> make_procfs_audit_adapter_with_options(
    const FileObservationOptions& options);

}  // namespace rebuntu::adapters::procfs