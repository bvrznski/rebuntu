// rebuntu::infrastructure::ansible — Ansible Provider Contracts (Phase 3.7)
//
// This header establishes Rebuntu's typed interface for Ansible configuration management
// and execution integration. It defines what an Ansible provider MUST implement without
// dictating HOW.
//
// Architecture:
//   Interfaces (what)        -> src/interfaces/
//   Adapters/Providers (how) -> cpp/src/adapters/ansible/
//
// Key principles:
//   * PROVIDER != CAPABILITY != OPERATION != SERVICE
//   * Ansible is OPTIONAL infrastructure (not a production dependency)
//   * No arbitrary shell strings - use structured argv for ansible CLI
//   * CPU-only execution by default (GPU use requires explicit enablement)
//   * Playbook ownership must be explicit - no arbitrary YAML execution

#pragma once

#include <system/core/contracts.hpp>
#include <system/infrastructure/contracts.hpp>
#include <chrono>
#include <memory>
#include <optional>
#include <string>
#include <string_view>
#include <map>
#include <vector>

namespace rebuntu::infrastructure {

// ============================================================================
// Ansible Provider Identity
// ============================================================================

struct AnsibleProviderId {
    std::string value;
    
    explicit AnsibleProviderId(std::string v) : value(std::move(v)) {}
    explicit operator std::string() const { return value; }
};

inline bool operator==(const AnsibleProviderId& a, const AnsibleProviderId& b) {
    return a.value == b.value;
}

inline bool operator!=(const AnsibleProviderId& a, const AnsibleProviderId& b) {
    return !(a == b);
}

// ============================================================================
// Ansible Execution Mode
// ============================================================================

enum class AnsibleMode {
    kNormal,     // Normal execution (may change system state)
    kCheck,      // Check mode - simulate without making changes
    kDryRun,     // Dry run with verbose output
};

inline std::string_view to_string(AnsibleMode m) {
    switch (m) {
        case AnsibleMode::kNormal:  return "normal";
        case AnsibleMode::kCheck:   return "check";
        case AnsibleMode::kDryRun:  return "dry-run";
    }
    return "unknown";
}

// ============================================================================
// Ansible Execution Type
// ============================================================================

enum class AnsibleExecutionType {
    kPlaybook,     // Execute a playbook file
    kModule,       // Execute a single module ad-hoc
    kInventory,    // Query inventory only
};

inline std::string_view to_string(AnsibleExecutionType t) {
    switch (t) {
        case AnsibleExecutionType::kPlaybook: return "playbook";
        case AnsibleExecutionType::kModule:   return "module";
        case AnsibleExecutionType::kInventory:return "inventory";
    }
    return "unknown";
}

// ============================================================================
// Task Result - Represents a single task execution result
// ============================================================================

struct AnsibleTaskResult {
    std::string task_name;         // Name of the task from playbook
    std::string host_name;         // Host where task executed
    bool changed = false;          // Did this task change state?
    bool skipped = false;          // Was this task skipped?
    bool failed = false;           // Did this task fail?
    
    // Return values (if any)
    std::map<std::string, std::string> return_values;
    
    // Error information (if failed)
    std::optional<std::string> error_message;
};

// ============================================================================
// Playbook Result
// ============================================================================

struct AnsiblePlaybookResult {
    std::string playbook_path;     // Path to the executed playbook
    std::string execution_id;      // Unique ID for this execution
    
    bool changed = false;          // Did any task change state?
    bool failed = false;           // Did any task fail?
    
    std::vector<AnsibleTaskResult> tasks;
};

// ============================================================================
// Module Result (ad-hoc command)
// ============================================================================

struct AnsibleModuleResult {
    std::string module_name;       // Name of the executed module
    std::string host_name;         // Target host
    
    bool changed = false;          // Did this change state?
    bool failed = false;           // Did this fail?
    
    // Module return values
    std::map<std::string, std::string> return_values;
};

// ============================================================================
// AnsibleProvider Verification Result (defined before AnsibleResult for inline methods)
// ============================================================================

struct AnsibleVerificationResult {
    core::SemanticStatus status = core::SemanticStatus::kUnknown;
    bool verified_flag = false;  // Postconditions were independently verified
    
    static AnsibleVerificationResult make_verified() {
        AnsibleVerificationResult r;
        r.status = core::SemanticStatus::kSuccess;
        r.verified_flag = true;
        return r;
    }
    
    static AnsibleVerificationResult not_verified(std::string description) {
        AnsibleVerificationResult r;
        r.status = core::SemanticStatus::kCompleted;
        r.verified_flag = false;
        return r;
    }
    
    static AnsibleVerificationResult verification_failed(std::string description) {
        AnsibleVerificationResult r;
        r.status = core::SemanticStatus::kFailure;
        r.verified_flag = false;
        return r;
    }
};

// ============================================================================
// Ansible Provider Result Types
// ============================================================================

struct AnsibleResult {
    core::SemanticStatus status;
    
    // Operation that was performed (for verification)
    std::optional<std::string> operation_id;
    
    // Execution results (where applicable)
    std::optional<AnsiblePlaybookResult> playbook_result;
    std::optional<AnsibleModuleResult> module_result;
    
    // Error information (if not success)
    std::optional<core::Error> error;
    
    // Evidence for verification
    std::vector<core::Evidence> evidence;
    
    // Postcondition verification result
    AnsibleVerificationResult verification_status;
    
    static AnsibleResult success() {
        AnsibleResult r;
        r.status = core::SemanticStatus::kSuccess;
        return r;
    }
    
    static AnsibleResult success_with_playbook(AnsiblePlaybookResult result) {
        AnsibleResult r;
        r.status = core::SemanticStatus::kSuccess;
        r.playbook_result = std::move(result);
        return r;
    }
    
    static AnsibleResult success_with_module(AnsibleModuleResult result) {
        AnsibleResult r;
        r.status = core::SemanticStatus::kSuccess;
        r.module_result = std::move(result);
        return r;
    }
    
    static AnsibleResult failure(std::string code, std::string message) {
        AnsibleResult r;
        r.status = core::SemanticStatus::kFailure;
        r.error = core::Error{std::move(code), std::move(message)};
        return r;
    }
    
    static AnsibleResult unavailable(std::string message) {
        AnsibleResult r;
        r.status = core::SemanticStatus::kUnknown;
        r.error = core::Error{"E_ANSIBLE_UNAVAILABLE", std::move(message)};
        return r;
    }
    
    static AnsibleResult success_with_verification(AnsiblePlaybookResult result, bool verified = false) {
        AnsibleResult r;
        r.status = core::SemanticStatus::kSuccess;
        r.playbook_result = std::move(result);
        r.verification_status = verified ? AnsibleVerificationResult::make_verified() : 
                                          AnsibleVerificationResult::not_verified("postcondition verification not performed");
        return r;
    }
};

// ============================================================================
// Ansible Provider Interface
// ============================================================================

class AnsibleProvider {
public:
    virtual ~AnsibleProvider() = default;
    
    // Get provider identity
    virtual AnsibleProviderId provider_id() const = 0;
    
    // Check if Ansible is available and accessible
    virtual bool is_available() const = 0;
    
    // Get Ansible version information
    virtual std::optional<std::string> get_version() const = 0;
    
    // Execute a playbook file with options
    virtual AnsibleResult execute_playbook(
        const std::string& playbook_path,
        const std::vector<std::string>& hosts,         // Target hosts
        const std::map<std::string, std::string>& vars,// Extra variables
        AnsibleMode mode,                               // Execution mode (check/dry-run/normal)
        std::optional<std::chrono::milliseconds> timeout = std::nullopt
    ) = 0;
    
    // Execute a single module ad-hoc on targets
    virtual AnsibleResult execute_module(
        const std::string& module_name,                // Module to execute
        const std::vector<std::string>& hosts,         // Target hosts
        const std::vector<std::string>& arguments,     // Module arguments
        const std::map<std::string, std::string>& vars,
        AnsibleMode mode,
        std::optional<std::chrono::milliseconds> timeout = std::nullopt
    ) = 0;
    
    // Query inventory information
    virtual AnsibleResult query_inventory(
        const std::vector<std::string>& patterns,      // Host patterns to match
        std::optional<std::chrono::milliseconds> timeout = std::nullopt
    ) = 0;
};

// ============================================================================
// Native CLI Provider (Ansible CLI wrapper using native subprocess)
// ============================================================================

namespace ansible_cli {

// Configuration for the Ansible provider
struct Config {
    std::optional<std::string> cli_path;      // Path to ansible executable
    std::optional<std::string> inventory_path;// Default inventory file/path
    bool cpu_only = true;                      // CPU-only execution (policy)
};

// The Ansible CLI provider wraps the ansible/ansible-playbook command-line interface
class Provider : public AnsibleProvider {
public:
    explicit Provider(Config config);
    ~Provider() override;
    
    // Disable copy/move for resource management
    Provider(const Provider&) = delete;
    Provider& operator=(const Provider&) = delete;
    
    // AnsibleProvider interface
    AnsibleProviderId provider_id() const override;
    bool is_available() const override;
    std::optional<std::string> get_version() const override;
    
    AnsibleResult execute_playbook(
        const std::string& playbook_path,
        const std::vector<std::string>& hosts,
        const std::map<std::string, std::string>& vars,
        AnsibleMode mode,
        std::optional<std::chrono::milliseconds> timeout = std::nullopt
    ) override;
    
    AnsibleResult execute_module(
        const std::string& module_name,
        const std::vector<std::string>& hosts,
        const std::vector<std::string>& arguments,
        const std::map<std::string, std::string>& vars,
        AnsibleMode mode,
        std::optional<std::chrono::milliseconds> timeout = std::nullopt
    ) override;
    
    AnsibleResult query_inventory(
        const std::vector<std::string>& patterns,
        std::optional<std::chrono::milliseconds> timeout = std::nullopt
    ) override;

private:
    class Impl;
    std::unique_ptr<Impl> pimpl_;
};

}  // namespace ansible_cli

}  // namespace rebuntu::infrastructure

// ============================================================================
// Hash support for AnsibleProviderId
// ============================================================================

namespace std {
template <> struct hash<rebuntu::infrastructure::AnsibleProviderId> {
    size_t operator()(const rebuntu::infrastructure::AnsibleProviderId& id) const noexcept {
        return std::hash<std::string>{}(id.value);
    }
};
}  // namespace std