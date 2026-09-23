// rebuntu::infrastructure — Engineering Infrastructure Contracts (Phase 3.0)
//
// This establishes Rebuntu's engineering infrastructure foundation:
//   * Production runtime dependencies
//   * Optional providers (Docker, Ansible, BitNet, etc.)
//   * Development/test infrastructure
//   * CI infrastructure
//   * Model/runtime artifacts
//
// Key principles:
//   * PROVIDER != CAPABILITY != OPERATION != SERVICE
//   * Infrastructure readiness is capability-specific, not a single boolean
//   * Optional infrastructure remains optional unless explicitly required
//   * Missing infrastructure reports precise unavailable capabilities

#pragma once

#include <system/core/contracts.hpp>
#include <algorithm>
#include <cstring>
#include <map>
#include <unistd.h>
#include <sys/stat.h>
#include <optional>
#include <set>
#include <string>
#include <string_view>
#include <vector>

namespace rebuntu::infrastructure {

// ============================================================================
// Infrastructure Category
// Defines how infrastructure is categorized in the system
// ============================================================================

enum class InfrastructureCategory {
    kProduction,     // Required for core Rebuntu functionality
    kOptional,       // May enhance functionality but not required
    kDevelopment,    // Used only during development/testing
    kCi,             // CI/CD infrastructure (not a production dependency)
    kModelArtifact,  // Model/runtime artifacts (BitNet models, etc.)
};

inline std::string_view to_string(InfrastructureCategory c) {
    switch (c) {
        case InfrastructureCategory::kProduction: return "production";
        case InfrastructureCategory::kOptional:   return "optional";
        case InfrastructureCategory::kDevelopment:return "development";
        case InfrastructureCategory::kCi:         return "ci";
        case InfrastructureCategory::kModelArtifact:return "model-artifact";
    }
    return "unknown";
}

// ============================================================================
// DependencyStatus
// The availability and readiness state of a dependency
// ============================================================================

enum class DependencyStatus {
    kUnknown,           // Status not yet assessed
    kAvailable,         // Available and usable
    kUnavailable,       // Not available on system
    kUnusable,          // Available but unusable (wrong version, broken)
    kUnauthorized,      // Available but unauthorized for use
    kNotChecked,        // Has not been checked yet
};

inline std::string_view to_string(DependencyStatus s) {
    switch (s) {
        case DependencyStatus::kUnknown:       return "unknown";
        case DependencyStatus::kAvailable:     return "available";
        case DependencyStatus::kUnavailable:   return "unavailable";
        case DependencyStatus::kUnusable:      return "unusable";
        case DependencyStatus::kUnauthorized:  return "unauthorized";
        case DependencyStatus::kNotChecked:    return "not_checked";
    }
    return "unknown";
}

// ============================================================================
// ProviderType
// The type of external infrastructure provider
// ============================================================================

enum class ProviderType {
    kRuntime,          // Runtime execution (Docker, containerd)
    kToolchain,        // Build/compilation tools (CMake, make)
    kAutomation,       // Automation/orchestration (Ansible)
    kSemantic,         // Semantic/model providers (BitNet)
    kTesting,          // Testing infrastructure
    kMonitoring,       // Monitoring/logging infrastructure
};

inline std::string_view to_string(ProviderType t) {
    switch (t) {
        case ProviderType::kRuntime:     return "runtime";
        case ProviderType::kToolchain:   return "toolchain";
        case ProviderType::kAutomation:  return "automation";
        case ProviderType::kSemantic:    return "semantic";
        case ProviderType::kTesting:     return "testing";
        case ProviderType::kMonitoring:  return "monitoring";
    }
    return "unknown";
}

// ============================================================================
// ToolInfo
// Information about an external tool/provider
// ============================================================================

struct ToolInfo {
    std::string name;              // Tool identifier (e.g., "docker", "ansible")
    std::string display_name;      // Human-readable name
    ProviderType type;             // What kind of provider this is
    std::optional<std::string> executable;  // Path to executable if available
    std::optional<std::string> version;     // Detected version
    bool is_optional = false;      // Is this optional?
    
    // Configuration
    std::optional<std::string> config_path;    // Where configuration is stored
    std::optional<int64_t> memory_limit_bytes; // Memory limit if applicable
    
    // Capabilities this tool provides
    std::vector<std::string> capabilities;
    
    // Provider selection criteria
    bool cpu_only = false;         // CPU-only execution required?
};

// ============================================================================
// InfrastructureState
// The current state of infrastructure readiness assessment
// ============================================================================

struct InfrastructureState {
    // Tool availability status
    std::map<std::string, DependencyStatus> tool_status;
    
    // Capabilities and their provider assignments
    std::map<std::string, std::vector<std::string>> capability_providers;
    
    // Version requirements (tool -> minimum version)
    std::map<std::string, std::string> minimum_versions;
    
    // Configuration issues
    std::vector<std::string> configuration_issues;
};

// ============================================================================
// InfrastructureContract
// A contract defining what infrastructure is needed for a capability
// ============================================================================

struct InfrastructureContract {
    std::string capability_id;              // What this contract enables
    
    std::vector<ToolInfo> required_tools;   // Tools that MUST be available
    std::vector<ToolInfo> optional_tools;   // Tools that MAY enhance functionality
    
    // Execution constraints
    bool requires_root = false;
    std::optional<int64_t> memory_limit_bytes;
    bool cpu_only = true;  // Default: CPU-only unless specified otherwise
    
    // Provider selection policy
    enum class SelectionPolicy {
        kAny,          // Any provider is acceptable
        kSpecific,     // Specific provider required
        kPriorityList, // Try providers in order
    } selection_policy = SelectionPolicy::kAny;
    
    std::vector<std::string> preferred_providers;  // For kPriorityList policy
    
    // Error codes for failure cases
    inline static const std::string kErrorToolMissing = "E_INFRA_TOOL_MISSING";
    inline static const std::string kErrorVersionTooOld = "E_INFRA_VERSION_TOO_OLD";
    inline static const std::string kErrorUnavailable = "E_INFRA_UNAVAILABLE";
};

// ============================================================================
// InfrastructureAssessment
// Assessment of infrastructure readiness for a capability
// ============================================================================

struct ToolAssessment {
    std::string tool_name;
    DependencyStatus status;
    std::optional<std::string> version;
    
    // For unavailable/unusable tools
    std::optional<std::string> reason;           // Why it's not available/usable
    std::optional<std::string> install_hint;     // How to install/fix it
    
    bool is_usable() const {
        return status == DependencyStatus::kAvailable;
    }
};

struct CapabilityAssessment {
    std::string capability_id;
    
    std::vector<ToolAssessment> tool_assessments;
    
    bool all_tools_available() const {
        // A capability with no tools is vacuously available
        if (tool_assessments.empty()) return true;
        
        for (const auto& t : tool_assessments) {
            if (!t.is_usable()) return false;
        }
        return true;
    }
};

// ============================================================================
// InfrastructureRegistry
// Registry of known infrastructure components and their status
// ============================================================================

class InfrastructureRegistry {
public:
    // Register a tool/provider
    void register_tool(ToolInfo info) {
        tools_[info.name] = std::move(info);
    }
    
    // Register an infrastructure contract
    void register_contract(InfrastructureContract contract) {
        contracts_[contract.capability_id] = std::move(contract);
    }
    
    // Get tool status by name
    std::optional<ToolInfo> find_tool(std::string_view name) const {
        auto it = tools_.find(std::string{name});
        if (it == tools_.end()) return std::nullopt;
        return it->second;
    }
    
    // Get contract for a capability
    std::optional<InfrastructureContract> find_contract(std::string_view capability_id) const {
        auto it = contracts_.find(std::string{capability_id});
        if (it == contracts_.end()) return std::nullopt;
        return it->second;
    }
    
    // Get all tools
    std::vector<ToolInfo> all_tools() const {
        std::vector<ToolInfo> result;
        for (const auto& [name, tool] : tools_) {
            result.push_back(tool);
        }
        std::sort(result.begin(), result.end(),
                  [](const ToolInfo& a, const ToolInfo& b) { return a.name < b.name; });
        return result;
    }
    
    // Get all contracts
    std::vector<InfrastructureContract> all_contracts() const {
        std::vector<InfrastructureContract> result;
        for (const auto& [id, contract] : contracts_) {
            result.push_back(contract);
        }
        std::sort(result.begin(), result.end(),
                  [](const InfrastructureContract& a, const InfrastructureContract& b) { 
                      return a.capability_id < b.capability_id; 
                  });
        return result;
    }
    
    // Get tool status with actual PATH search and executable check
    ToolAssessment assess_tool(std::string_view name) const {
        ToolAssessment assessment;
        assessment.tool_name = std::string{name};
        
        auto it = tools_.find(std::string{name});
        if (it == tools_.end()) {
            assessment.status = DependencyStatus::kUnknown;
            return assessment;
        }
        
        // Native PATH search using access() - follows environment_discovery pattern
        const char* path_env = std::getenv("PATH");
        if (!path_env) {
            assessment.status = DependencyStatus::kUnusable;
            assessment.reason = "PATH not set";
            return assessment;
        }
        
        bool found = false;
        std::string executable_path;
        
        // Parse PATH directories (colon-separated on Unix)
        size_t start = 0;
        while (start < std::strlen(path_env)) {
            size_t end = std::strchr(path_env + start, ':') 
                ? std::strchr(path_env + start, ':') - path_env
                : std::strlen(path_env);
            
            if (end > start) {
                std::string dir(path_env + start, end - start);
                if (!dir.empty()) {
                    std::string candidate = dir + "/" + std::string{name};
                    if (access(candidate.c_str(), X_OK) == 0) {
                        found = true;
                        executable_path = candidate;
                        break;
                    }
                }
            }
            
            if (end >= std::strlen(path_env)) break;
            start = end + 1;
        }
        
        if (!found) {
            assessment.status = DependencyStatus::kUnavailable;
            assessment.reason = "executable not found in PATH";
            return assessment;
        }
        
        // Executable is accessible - check it's a regular file
        struct stat st;
        if (stat(executable_path.c_str(), &st) == 0 && S_ISREG(st.st_mode)) {
            assessment.status = DependencyStatus::kAvailable;
            assessment.version = it->second.executable.has_value() 
                ? it->second.executable : executable_path;
        } else {
            assessment.status = DependencyStatus::kUnusable;
            assessment.reason = "not a regular file";
        }
        
        return assessment;
    }
    
    // Assess capability readiness
    CapabilityAssessment assess_capability(std::string_view capability_id) const {
        CapabilityAssessment assessment;
        assessment.capability_id = std::string{capability_id};
        
        auto contract_opt = find_contract(capability_id);
        if (!contract_opt.has_value()) {
            return assessment;  // Empty assessment for unknown capability
        }
        
        const auto& contract = *contract_opt;
        
        // Assess required tools
        for (const auto& tool : contract.required_tools) {
            assessment.tool_assessments.push_back(assess_tool(tool.name));
        }
        
        // Also assess optional tools
        for (const auto& tool : contract.optional_tools) {
            assessment.tool_assessments.push_back(assess_tool(tool.name));
        }
        
        return assessment;
    }
    
private:
    std::map<std::string, ToolInfo> tools_;
    std::map<std::string, InfrastructureContract> contracts_;
};

// ============================================================================
// InfrastructureResult
// Result of an infrastructure operation (e.g., capability readiness check)
// ============================================================================

struct InfrastructureResult {
    core::SemanticStatus status;
    
    // Capability that was checked
    std::optional<std::string> capability_id;
    
    // Tool assessments for this result
    std::vector<ToolAssessment> tool_assessments;
    
    // Error information (if not success)
    std::optional<core::Error> error;
    
    // Verification evidence
    std::vector<core::Evidence> evidence;
    
    static InfrastructureResult available() {
        InfrastructureResult r;
        r.status = core::SemanticStatus::kSuccess;
        return r;
    }
    
    static InfrastructureResult unavailable(std::string tool_name, std::string reason) {
        InfrastructureResult r;
        r.status = core::SemanticStatus::kUnknown;
        r.error = core::Error{
            "E_INFRA_UNAVAILABLE",
            tool_name + ": " + reason
        };
        return r;
    }
    
    static InfrastructureResult partial(std::vector<ToolAssessment> tools) {
        InfrastructureResult r;
        r.status = core::SemanticStatus::kUnknown;
        r.tool_assessments = std::move(tools);
        return r;
    }
};

// ============================================================================
// Infrastructure readiness constants
// ============================================================================

inline constexpr std::string_view kProviderTypeRuntime = "runtime";
inline constexpr std::string_view kProviderTypeToolchain = "toolchain";
inline constexpr std::string_view kProviderTypeAutomation = "automation";
inline constexpr std::string_view kProviderTypeSemantic = "semantic";

}  // namespace rebuntu::infrastructure