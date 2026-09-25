// rebuntu::infrastructure::jenkins — Jenkins Provider Contracts (Phase 3.9)
//
// This header establishes Rebuntu's typed interface for Jenkins CI/build/test
// integration. It defines what a Jenkins provider MUST implement without dictating HOW.
//
// Architecture:
//   Interfaces (what)        -> src/interfaces/
//   Adapters/Providers (how) -> cpp/src/adapters/jenkins/
//
// Key principles:
//   * PROVIDER != CAPABILITY != OPERATION != SERVICE
//   * Jenkins is OPTIONAL engineering infrastructure (not a production dependency)
//   * No arbitrary shell strings - use structured argv for jenkins CLI
//   * Credentials managed by Jenkins, not Rebuntu
//   * Build artifacts are evidence, not control

#pragma once

#include <system/core/contracts.hpp>
#include <system/infrastructure/contracts.hpp>
#include <chrono>
#include <memory>
#include <optional>
#include <string>
#include <vector>

namespace rebuntu::infrastructure {

// ============================================================================
// Jenkins Provider Identity
// ============================================================================

struct JenkinsProviderId {
    std::string value;
    
    explicit JenkinsProviderId(std::string v) : value(std::move(v)) {}
    explicit operator std::string() const { return value; }
};

inline bool operator==(const JenkinsProviderId& a, const JenkinsProviderId& b) {
    return a.value == b.value;
}

inline bool operator!=(const JenkinsProviderId& a, const JenkinsProviderId& b) {
    return !(a == b);
}

// ============================================================================
// Jenkins Build Result Status
// ============================================================================

enum class JenkinsBuildStatus {
    kQueued,          // Build is in the queue
    kStarted,         // Build has started running
    kRunning,         // Build is actively executing
    kAborted,         // Build was manually aborted
    kSuccess,         // Build completed successfully
    kFailed,          // Build failed (non-zero exit)
    kNotBuilt,        // Build was not executed (e.g., dependency failure)
    kUnknown,         // Status unknown
};

inline std::string_view to_string(JenkinsBuildStatus s) {
    switch (s) {
        case JenkinsBuildStatus::kQueued:    return "queued";
        case JenkinsBuildStatus::kStarted:   return "started";
        case JenkinsBuildStatus::kRunning:   return "running";
        case JenkinsBuildStatus::kAborted:   return "aborted";
        case JenkinsBuildStatus::kSuccess:   return "success";
        case JenkinsBuildStatus::kFailed:    return "failed";
        case JenkinsBuildStatus::kNotBuilt:  return "not_built";
        case JenkinsBuildStatus::kUnknown:   return "unknown";
    }
    return "unknown";
}

// ============================================================================
// Jenkins Build Information
// ============================================================================

struct JenkinsBuildInfo {
    std::string job_name;           // Name of the Jenkins job
    int build_number = 0;           // Build number within the job
    JenkinsBuildStatus status;      // Current build status
    
    // Timing information
    std::optional<std::chrono::system_clock::time_point> queue_time;
    std::optional<std::chrono::system_clock::time_point> start_time;
    std::optional<std::chrono::system_clock::time_point> finish_time;
    
    // Duration in milliseconds (if available)
    std::optional<int64_t> duration_ms;
    
    // Build parameters
    std::map<std::string, std::string> parameters;
    
    // Whether the build is executable (not a dry run)
    bool is_executable = true;
};

// ============================================================================
// Jenkins Artifact Information
// ============================================================================

struct JenkinsArtifactInfo {
    std::string filename;           // Name of the artifact file
    std::optional<std::chrono::system_clock::time_point> timestamp;
    std::optional<int64_t> size_bytes;
};

// ============================================================================
// Jenkins Provider Result Types
// ============================================================================

struct JenkinsResult {
    core::SemanticStatus status;
    
    // Operation that was performed (for verification)
    std::optional<std::string> operation_id;
    
    // Build information (where applicable)
    std::optional<JenkinsBuildInfo> build_info;
    
    // Artifact information
    std::vector<JenkinsArtifactInfo> artifacts;
    
    // Error information (if not success)
    std::optional<infrastructure::Error> error;
    
    // Evidence for verification
    std::vector<core::Evidence> evidence;
    
    static JenkinsResult success() {
        JenkinsResult r;
        r.status = core::SemanticStatus::kSuccess;
        return r;
    }
    
    static JenkinsResult success_with_build(JenkinsBuildInfo build_info) {
        JenkinsResult r;
        r.status = core::SemanticStatus::kSuccess;
        r.build_info = std::move(build_info);
        return r;
    }
    
    static JenkinsResult success_with_artifacts(std::vector<JenkinsArtifactInfo> artifacts) {
        JenkinsResult r;
        r.status = core::SemanticStatus::kSuccess;
        r.artifacts = std::move(artifacts);
        return r;
    }
    
    static JenkinsResult failure(std::string code, std::string message) {
        JenkinsResult r;
        r.status = core::SemanticStatus::kFailure;
        r.error = infrastructure::Error{std::move(code), std::move(message)};
        return r;
    }
    
    static JenkinsResult unavailable(std::string message) {
        JenkinsResult r;
        r.status = core::SemanticStatus::kUnknown;
        r.error = infrastructure::Error{"E_JENKINS_UNAVAILABLE", std::move(message)};
        return r;
    }
};

// ============================================================================
// Jenkins Provider Interface
// ============================================================================

class JenkinsProvider {
public:
    virtual ~JenkinsProvider() = default;
    
    // Get provider identity
    virtual JenkinsProviderId provider_id() const = 0;
    
    // Check if Jenkins is available and accessible
    virtual bool is_available() const = 0;
    
    // Trigger a build for the specified job with optional parameters
    virtual JenkinsResult trigger_build(
        const std::string& job_name,
        const std::map<std::string, std::string>& parameters,
        std::optional<std::chrono::milliseconds> timeout = std::nullopt
    ) = 0;
    
    // Check the status of a specific build
    virtual JenkinsResult get_build_status(
        const std::string& job_name,
        int build_number,
        std::optional<std::chrono::milliseconds> timeout = std::nullopt
    ) = 0;
    
    // List recent builds for a job
    virtual JenkinsResult list_builds(
        const std::string& job_name,
        std::optional<int> limit = std::nullopt,
        std::optional<std::chrono::milliseconds> timeout = std::nullopt
    ) = 0;
    
    // Retrieve artifacts from a completed build
    virtual JenkinsResult get_artifacts(
        const std::string& job_name,
        int build_number,
        std::optional<std::chrono::milliseconds> timeout = std::nullopt
    ) = 0;
    
    // Get information about the Jenkins server (version, etc.)
    virtual std::optional<std::string> get_server_info(
        std::optional<std::chrono::milliseconds> timeout = std::nullopt
    ) const = 0;
};

// ============================================================================
// Native CLI Provider (Jenkins CLI wrapper using native subprocess)
// ============================================================================

namespace jenkins_cli {

// Configuration for the Jenkins provider
struct Config {
    std::optional<std::string> cli_path;      // Path to jenkins CLI executable
    std::optional<std::string> server_url;     // Jenkins server URL
    bool cpu_only = true;                      // CPU-only execution (policy)
};

// The Jenkins CLI provider wraps the jenkins command-line interface
class Provider : public JenkinsProvider {
public:
    explicit Provider(Config config);
    ~Provider() override;
    
    // Disable copy/move for resource management
    Provider(const Provider&) = delete;
    Provider& operator=(const Provider&) = delete;
    
    // JenkinsProvider interface
    JenkinsProviderId provider_id() const override;
    bool is_available() const override;
    std::optional<std::string> get_server_info(
        std::optional<std::chrono::milliseconds> timeout = std::nullopt
    ) const override;
    
    JenkinsResult trigger_build(
        const std::string& job_name,
        const std::map<std::string, std::string>& parameters,
        std::optional<std::chrono::milliseconds> timeout = std::nullopt
    ) override;
    
    JenkinsResult get_build_status(
        const std::string& job_name,
        int build_number,
        std::optional<std::chrono::milliseconds> timeout = std::nullopt
    ) override;
    
    JenkinsResult list_builds(
        const std::string& job_name,
        std::optional<int> limit = std::nullopt,
        std::optional<std::chrono::milliseconds> timeout = std::nullopt
    ) override;
    
    JenkinsResult get_artifacts(
        const std::string& job_name,
        int build_number,
        std::optional<std::chrono::milliseconds> timeout = std::nullopt
    ) override;

private:
    class Impl;
    std::unique_ptr<Impl> pimpl_;
};

}  // namespace jenkins_cli

}  // namespace rebuntu::infrastructure

// ============================================================================
// Hash support for JenkinsProviderId
// ============================================================================

namespace std {
template <> struct hash<rebuntu::infrastructure::JenkinsProviderId> {
    size_t operator()(const rebuntu::infrastructure::JenkinsProviderId& id) const noexcept {
        return std::hash<std::string>{}(id.value);
    }
};
}  // namespace std