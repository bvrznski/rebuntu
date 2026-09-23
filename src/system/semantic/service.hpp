// rebuntu::semantic::service — Native Semantic Service contracts (Phase 3.3)
//
// This header establishes Rebuntu's native local semantic service:
//
//   * Lifecycle: systemd-supervised persistent process
//   * IPC: Unix domain socket for bounded requests
//   * Readiness: separate from running state
//   * Resources: CPU-only, bounded memory, timeouts enforced
//
// Architecture:
//   Service contracts -> this header (cpp/include/system/semantic/service.hpp)
//   Service runtime   -> cpp/src/semantic/service.cpp
//   IPC transport     -> cpp/include/system/environment/ipc.hpp
//   Model provider    -> cpp/include/system/semantic/provider.hpp

#pragma once

#include <system/core/contracts.hpp>
#include <system/runtime/contracts.hpp>
#include <system/semantic/provider.hpp>
#include <string>
#include <memory>
#include <optional>
#include <chrono>
#include <vector>
#include <mutex>

namespace rebuntu::semantic {

namespace service {

// ============================================================================
// Service Identity
// ============================================================================

inline constexpr char const* kServiceId = "rebuntu-semantic";
inline constexpr char const* kServiceTitle = "Rebuntu Native Semantic Service";

// ============================================================================
// Service Activation (for systemd integration)
// ============================================================================

enum class ServiceActivation {
    kPersistent,     // always running (systemd Type=simple)
    kOnDemand,       // started when first accessed
};

inline std::string to_string(ServiceActivation a) {
    switch (a) {
        case ServiceActivation::kPersistent: return "persistent";
        case ServiceActivation::kOnDemand:   return "on-demand";
    }
    return "unknown";
}

// ============================================================================
// Service State
// ============================================================================

enum class ServiceState {
    kUnavailable,   // not available
    kActivating,    // in the process of becoming available (model loading)
    kReady,         // service running AND model loaded and ready
    kActive,        // accepting requests but model may be reloading
    kDegraded,      // partially available with reduced capability
    kDeactivating,  // in the process of stopping
    kFailed,        // activation failed or service became unavailable due to error
};

inline std::string to_string(ServiceState s) {
    switch (s) {
        case ServiceState::kUnavailable:  return "unavailable";
        case ServiceState::kActivating:   return "activating";
        case ServiceState::kReady:        return "ready";
        case ServiceState::kActive:       return "active";
        case ServiceState::kDegraded:     return "degraded";
        case ServiceState::kDeactivating: return "deactivating";
        case ServiceState::kFailed:       return "failed";
    }
    return "unknown";
}

// ============================================================================
// Readiness State
// Can the service correctly process requests now?
// ============================================================================

enum class ReadinessState {
    kNotReady,      // not yet ready (model loading, initial startup)
    kReady,         // model loaded and ready for requests
    kDraining,      // shutting down, not accepting new work
};

inline std::string to_string(ReadinessState s) {
    switch (s) {
        case ReadinessState::kNotReady: return "not_ready";
        case ReadinessState::kReady:    return "ready";
        case ReadinessState::kDraining: return "draining";
    }
    return "unknown";
}

// ============================================================================
// Service Configuration
// ============================================================================

struct Config {
    // Path to the bitnet.cpp executable (discovered at runtime)
    std::optional<std::string> bitnet_executable;
    
    // Path to model artifacts directory
    std::optional<std::string> model_path;
    
    // CPU-only execution (required per policy)
    bool cpu_only = true;
    
    // Memory limit in bytes (0 = unlimited, but provider may still enforce limits)
    std::optional<int64_t> memory_limit_bytes;
    
    // Default timeout for inference requests
    std::chrono::milliseconds default_timeout{30000};  // 30 seconds
    
    // IPC socket path
    std::string ipc_socket_path;
};

// ============================================================================
// Service Info (Phase 0.6 ServiceInfo extension)
// ============================================================================

struct ServiceInfo {
    std::string id;
    std::string title;
    std::string description;
    
    // Activation method (systemd-managed service = persistent)
    ServiceActivation activation;
    
    // Resource constraints
    bool cpu_only = true;
    std::optional<int64_t> memory_limit_bytes;
    
    // Readiness check configuration
    bool has_readiness_check = true;
    
    // Health check endpoint (for external monitoring)
    bool has_health_check_endpoint = false;
    
    // IPC interface
    std::vector<std::string> interfaces;  // e.g., "unix-socket"
};

// ============================================================================
// Service Control Operations
// ============================================================================

enum class ServiceControl {
    kStart,         // Start the service (if not running)
    kStop,          // Stop the service gracefully
    kRestart,       // Restart the service
    kReload,        // Reload configuration without full restart
};

inline std::string to_string(ServiceControl c) {
    switch (c) {
        case ServiceControl::kStart:   return "start";
        case ServiceControl::kStop:    return "stop";
        case ServiceControl::kRestart: return "restart";
        case ServiceControl::kReload:  return "reload";
    }
    return "unknown";
}

// ============================================================================
// IPC Request Types
// ============================================================================

enum class SemanticRequestType : int {
    kClassification,
    kIntentCandidate,
    kEvidenceRelevance,
    kDiagnosticSummary,
};

struct SemanticRequest {
    SemanticRequestType type;
    std::chrono::system_clock::time_point timestamp;
    
    // Typed request data (one of these will be populated)
    struct ClassificationData {
        std::string input;
        std::vector<std::string> categories;
    } classification;
    
    struct IntentCandidateData {
        std::string input;
        std::vector<std::string> allowed_operations;
    } intent_candidate;
    
    struct EvidenceRelevanceData {
        std::string evidence;
        std::string context;
    } evidence_relevance;
    
    struct DiagnosticSummaryData {
        std::vector<std::string> diagnostic_items;
    } diagnostic_summary;
    
    // Request metadata
    std::optional<std::chrono::milliseconds> timeout_ms;
};

struct SemanticResponseData {
    std::optional<semantic::ClassificationResult> classification;
    std::optional<semantic::IntentCandidate> intent_candidate;
    std::optional<semantic::EvidenceRelevance> relevance;
    std::optional<semantic::DiagnosticSummary> summary;
};

// ============================================================================
// IPC Response Types
// ============================================================================

struct SemanticServiceResponse {
    std::chrono::system_clock::time_point responded_at;
    
    // Timing information
    std::optional<std::chrono::milliseconds> inference_time_ms;
    
    // Response data (where applicable)
    SemanticResponseData data;
    
    // Provider metadata
    std::string provider_id;
};

struct ServiceResult {
    core::SemanticStatus status = core::SemanticStatus::kUnknown;
    
    // Response data (where applicable)
    std::optional<SemanticServiceResponse> response;
    
    // Error information (if not success)
    std::optional<core::Error> error;
    
    // Evidence for verification
    std::vector<core::Evidence> evidence;
    
    static ServiceResult success(SemanticServiceResponse resp) {
        ServiceResult r;
        r.status = core::SemanticStatus::kSuccess;
        r.response = std::move(resp);
        return r;
    }
    
    static ServiceResult failure(std::string code, std::string message) {
        ServiceResult r;
        r.status = core::SemanticStatus::kFailure;
        r.error = core::Error{std::move(code), std::move(message)};
        return r;
    }
    
    static ServiceResult unavailable(std::string message) {
        ServiceResult r;
        r.status = core::SemanticStatus::kUnknown;
        r.error = core::Error{"E_SEMANTIC_UNAVAILABLE", std::move(message)};
        return r;
    }
};

// ============================================================================
// Service Control Interface
// ============================================================================

class SemanticServiceController {
public:
    virtual ~SemanticServiceController() = default;
    
    // Get current service state
    virtual ServiceState get_state() const = 0;
    
    // Check if service is ready to accept requests (model loaded)
    virtual ReadinessState get_readiness() const = 0;
    
    // Control operations
    virtual bool start() = 0;        // Start service
    virtual bool stop() = 0;         // Stop service gracefully
    virtual bool restart() = 0;      // Restart service
    
    // Send a semantic request (blocking, with timeout)
    virtual ServiceResult send_request(const SemanticRequest& request) = 0;
    
    // Health check (can we connect?)
    virtual bool is_healthy() const = 0;
};

// ============================================================================
// Native systemd-based service controller
// ============================================================================

class SystemdServiceController : public SemanticServiceController {
public:
    explicit SystemdServiceController(Config config);
    ~SystemdServiceController() override;
    
    // Disable copy/move
    SystemdServiceController(const SystemdServiceController&) = delete;
    SystemdServiceController& operator=(const SystemdServiceController&) = delete;
    
    ServiceState get_state() const override;
    ReadinessState get_readiness() const override;
    bool start() override;
    bool stop() override;
    bool restart() override;
    
    ServiceResult send_request(const SemanticRequest& request) override;
    bool is_healthy() const override;

private:
    class Impl;
    std::unique_ptr<Impl> pimpl_;
};

// ============================================================================
// In-memory service state (for testing without systemd)
// ============================================================================

class MockServiceController : public SemanticServiceController {
public:
    explicit MockServiceController(Config config);
    
    ServiceState get_state() const override;
    ReadinessState get_readiness() const override;
    bool start() override;
    bool stop() override;
    bool restart() override;
    
    ServiceResult send_request(const SemanticRequest& request) override;
    bool is_healthy() const override;
    
    // Mock control methods
    void set_state(ServiceState state);
    void set_readiness(ReadinessState readiness);

private:
    Config config_;
    mutable std::mutex mutex_;
    ServiceState state_ = ServiceState::kUnavailable;
    ReadinessState readiness_ = ReadinessState::kNotReady;
};

}  // namespace service

// ============================================================================
// Semantic Service Registry (combines provider + service)
// ============================================================================

class SemanticServiceRegistry {
public:
    void add_provider(std::unique_ptr<semantic::SemanticProvider> provider);
    std::vector<std::unique_ptr<semantic::SemanticProvider>> all_providers() const;
    std::optional<semantic::SemanticProvider*> find_provider(const semantic::ProviderId& id) const;
    
    bool is_semantic_available() const;

private:
    std::vector<semantic::SemanticProvider*> providers_;
};

}  // namespace rebuntu::semantic