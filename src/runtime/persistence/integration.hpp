#pragma once

#include <memory>
#include <optional>
#include <string>
#include <vector>

namespace rebuntu::runtime::persistence {

// ============================================================================
// ExecutionRecord — Persisted execution facts for restart/reconciliation/audit
// ============================================================================

struct ExecutionRecord {
    /// Request-level identity
    std::string request_id;
    
    /// Execution-level identity
    std::string execution_id;
    std::string parent_execution_id;  // empty if no parent
    
    /// Timing information
    long started_at_ms;
    long finished_at_ms;
    
    /// Execution outcome (from core contracts)
    int outcome;  // SemanticStatus enum value
    
    bool verification_successful = false;
    
    /// Retry tracking
    int attempt_number = 1;
    
    /// Cancellation/timeout flags
    bool was_cancelled = false;
    bool timed_out = false;
    
    // Optional result data (bounded - not all executions persist full value)
    std::string result_summary;  // empty if no summary
    
    /// Evidence reference (pointer to evidence store, not embedded evidence)
    std::vector<std::string> evidence_refs;
};

// ============================================================================
// PersistenceStatus — Result type for persistence operations
// ============================================================================

enum class PersistenceStatus {
    kSuccess,
    kNotFound,
    kAlreadyExists,
    kIOError,
    kSerializationError,
    kPermissionError
};

// ============================================================================
// FilesystemPersistence — Simple file-based execution record persistence
// ============================================================================

/// Filesystem-based implementation of execution record persistence.
/// Stores records as JSON-like entries in a directory.
class FilesystemPersistence {
public:
    /// Create a filesystem persistence instance at the given path
    explicit FilesystemPersistence(const std::string& storage_path);
    
    ~FilesystemPersistence();
    
    // Disable copy, enable move
    FilesystemPersistence(const FilesystemPersistence&) = delete;
    FilesystemPersistence& operator=(const FilesystemPersistence&) = delete;
    FilesystemPersistence(FilesystemPersistence&&) noexcept;
    FilesystemPersistence& operator=(FilesystemPersistence&&) noexcept;
    
    /// Save an execution record to persistent storage
    bool save(const ExecutionRecord& record);
    
    /// Load a specific execution record by execution_id
    std::optional<ExecutionRecord> load(const std::string& exec_id);
    
    /// List all records matching a request_id (for restart recovery)
    std::vector<ExecutionRecord> list_by_request(const std::string& req_id);
    
    /// List recent records (for audit trail display)
    std::vector<ExecutionRecord> list_recent(int limit = 100);
    
    /// Delete a specific record
    bool remove(const std::string& exec_id);
    
    /// Clear all persisted records
    void clear();
    
private:
    std::string storage_path_;
};

}  // namespace rebuntu::runtime::persistence