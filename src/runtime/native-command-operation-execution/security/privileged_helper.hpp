// Rebuntu — Phase 6 Native Command Operation Execution
// Privileged Helper Interface
//
// Where required, route privileged effects through narrow typed helpers.
// Helpers must validate exact operation/target parameters and reject arbitrary
// command/script execution.

#pragma once

#include <string>
#include <vector>
#include <memory>
#include <map>
#include <set>

namespace rebuntu::runtime::native_command_operation_execution {

using Attributes = std::map<std::string, std::string>;

enum class SemanticStatus {
    kSuccess,
    kFailure,
    kUnknown,
};

struct Evidence {
    std::string source;
    std::string value;
    // Use integer timestamp (milliseconds since epoch) instead of chrono type
    long long observed_at_ms = 0;
};

// ============================================================================
// PrivilegedHelperResult — Result of a privileged helper invocation
// ============================================================================

struct PrivilegedHelperResult {
    SemanticStatus status = SemanticStatus::kUnknown;
    bool verified = false;  // Whether the helper successfully validated inputs
    
    std::vector<Evidence> evidence;
    
    struct ErrorInfo {
        std::string code;
        std::string message;
    };
    
    std::string error_message;  // Empty on success
    std::string error_code;
    
    static PrivilegedHelperResult success() {
        PrivilegedHelperResult r;
        r.status = SemanticStatus::kSuccess;
        r.verified = true;
        return r;
    }
    
    static PrivilegedHelperResult failure(std::string code, std::string message) {
        PrivilegedHelperResult r;
        r.status = SemanticStatus::kFailure;
        r.error_code = std::move(code);
        r.error_message = std::move(message);
        return r;
    }
    
    static PrivilegedHelperResult validation_failed(std::string reason) {
        return failure("E_VALIDATION_FAILED", "parameter validation failed: " + reason);
    }
    
    bool is_success() const {
        return status == SemanticStatus::kSuccess && verified && error_message.empty();
    }
};

// ============================================================================
// PrivilegedOperation — Typed operation for privileged effects
// ============================================================================

struct PrivilegedOperation {
    enum class Kind {
        kFilesystem,
        kNetwork,
        kProcess,
        kSystem,
        kStorage,
    };
    
    Kind kind;
    std::string verb;
    std::string target;
    Attributes arguments;
};

// ============================================================================
// PrivilegedHelper — Interface for typed privileged helpers
// ============================================================================

class PrivilegedHelper {
public:
    virtual ~PrivilegedHelper() = default;
    
    virtual PrivilegedOperation::Kind kind() const noexcept = 0;
    
    // Returns empty string if validation passes, error message otherwise
    virtual std::string validate(const PrivilegedOperation& op) const = 0;
    
    virtual PrivilegedHelperResult execute(const PrivilegedOperation& op) = 0;
};

// ============================================================================
// FilesystemHelper — Typed helper for filesystem privilege effects
// ============================================================================

class FilesystemHelper : public PrivilegedHelper {
public:
    PrivilegedOperation::Kind kind() const noexcept override;
    std::string validate(const PrivilegedOperation& op) const override;
    PrivilegedHelperResult execute(const PrivilegedOperation& op) override;
};

// ============================================================================
// ProcessHelper — Typed helper for process privilege effects
// ============================================================================

class ProcessHelper : public PrivilegedHelper {
public:
    PrivilegedOperation::Kind kind() const noexcept override;
    std::string validate(const PrivilegedOperation& op) const override;
    PrivilegedHelperResult execute(const PrivilegedOperation& op) override;
};

// ============================================================================
// StorageHelper — Typed helper for storage privilege effects
// ============================================================================

class StorageHelper : public PrivilegedHelper {
public:
    PrivilegedOperation::Kind kind() const noexcept override;
    std::string validate(const PrivilegedOperation& op) const override;
    PrivilegedHelperResult execute(const PrivilegedOperation& op) override;
};

// ============================================================================
// Helper registry — Register and dispatch helpers
// ============================================================================

class PrivilegedHelperRegistry {
public:
    static PrivilegedHelperRegistry& instance();
    
    void register_helper(std::unique_ptr<PrivilegedHelper> helper);
    
    std::string get_helper_kind_name(PrivilegedOperation::Kind kind) const;
    
    PrivilegedHelperResult execute_operation(const PrivilegedOperation& op);

private:
    PrivilegedHelperRegistry() = default;
    std::vector<std::unique_ptr<PrivilegedHelper>> helpers_;
};

// ============================================================================
// Helper factory functions
// ============================================================================

std::unique_ptr<FilesystemHelper> make_filesystem_helper();
std::unique_ptr<ProcessHelper> make_process_helper();
std::unique_ptr<StorageHelper> make_storage_helper();

}  // namespace rebuntu::runtime::native_command_operation_execution