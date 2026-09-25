// rebuntu::semantic::service — Native Semantic Service Architecture (Phase 3.3)
//
// This establishes the canonical architecture for Rebuntu's native semantic
// service that hosts the BitNet b1.58 2B4T model as a persistent, systemd-supervised
// process.
//
// ARCHITECTURE
//   - Service: Persistent daemon with lifecycle management (systemd supervised)
//   - Provider: CPU-only inference engine (Phase 3.1-3.2)
//   - IPC: Unix domain socket for bounded requests (Phase 3.4+)
//
// CRITICAL INVARIENTS
//   - SERVICE != DAEMON (service is systemd unit, daemon is process implementation)
//   - READINESS != RUNNING (ready means ready to accept work)
//   - EXECUTION_SUCCESS != VERIFIED_SUCCESS (postcondition verification required)
//   - DATA != CONTROL (model output is UNTRUSTED until validated)

#pragma once

#include <system/semantic/provider.hpp>
#include <system/core/contracts.hpp>
#include <filesystem>
#include <chrono>
#include <optional>
#include <string>
#include <vector>
#include <memory>

namespace rebuntu::semantic {

// Forward declaration
class SemanticServiceController;

// ============================================================================
// LifecycleState — Service lifecycle stage
// ============================================================================

enum class LifecycleState {
    kUnavailable,     // Not running at all
    kActivating,      // Starting up (loading model)
    kReady,           // Running and accepting requests
    kDraining,        // Stopping, finishing in-flight requests
    kTerminating,     // Force stopping
};

inline std::string to_string(LifecycleState s) {
    switch (s) {
        case LifecycleState::kUnavailable: return "unavailable";
        case LifecycleState::kActivating:  return "activating";
        case LifecycleState::kReady:       return "ready";
        case LifecycleState::kDraining:    return "draining";
        case LifecycleState::kTerminating: return "terminating";
    }
    return "unknown";
}

// ============================================================================
// ReadinessState — Can accept new work right now?
// ============================================================================

enum class ReadinessState {
    kNotReady,        // Cannot accept requests (loading, degraded)
    kReady,           // Can accept and process requests
    kDraining,        // Accepting only for graceful shutdown
};

inline std::string to_string(ReadinessState r) {
    switch (r) {
        case ReadinessState::kNotReady: return "not_ready";
        case ReadinessState::kReady:    return "ready";
        case ReadinessState::kDraining: return "draining";
    }
    return "unknown";
}

// ============================================================================
// HealthState — Is the service healthy?
// ============================================================================

enum class HealthState {
    kUnknown,         // No health data yet
    kHealthy,         // Operating normally
    kDegraded,        // Functioning but with reduced capacity
    kUnhealthy,       // Not functioning correctly
};

inline std::string to_string(HealthState h) {
    switch (h) {
        case HealthState::kUnknown:   return "unknown";
        case HealthState::kHealthy:   return "healthy";
        case HealthState::kDegraded:  return "degraded";
        case HealthState::kUnhealthy: return "unhealthy";
    }
    return "unknown";
}

// ============================================================================
// ServiceMetrics — Runtime metrics for monitoring
// ============================================================================

struct ServiceMetrics {
    std::chrono::system_clock::time_point started_at;
    std::optional<std::chrono::system_clock::time_point> ready_at;
    
    size_t total_requests = 0;
    size_t successful_requests = 0;
    size_t failed_requests = 0;
    size_t timed_out_requests = 0;
    
    std::chrono::milliseconds average_response_time_ms{0};
    std::optional<std::chrono::milliseconds> last_response_time_ms;
};

// ============================================================================
// ServiceState — Complete service status summary
// ============================================================================

struct ServiceState {
    LifecycleState lifecycle = LifecycleState::kUnavailable;
    ReadinessState readiness = ReadinessState::kNotReady;
    HealthState health = HealthState::kUnknown;
    
    std::optional<std::string> state_detail;  // Human-readable detail
    
    ServiceMetrics metrics;
};

// ============================================================================
// SemanticRequest — Canonical request type for semantic service
// ============================================================================

enum class SemanticRequestType {
    kClassify,
    kGenerateIntentCandidate,
    kAssessEvidenceRelevance,
    kSummarizeDiagnostics,
};

struct SemanticRequest {
    SemanticRequestType type;
    
    // Request-specific data
    std::string input_text;                    // For classify, generate_intent
    std::vector<std::string> evidence_lines;   // For summarize
    std::optional<std::string> query_context;  // For assess_relevance
    
    std::chrono::milliseconds timeout = std::chrono::seconds(30);
    
    // Request metadata for tracing
    std::optional<std::string> request_id;
    std::optional<std::string> client_info;
};

// ============================================================================
// ServiceResult — Result of a service operation
// ============================================================================

struct ServiceResult {
    bool succeeded = false;
    std::optional<std::string> output;        // Model response if successful
    std::optional<std::string> error_message;
    
    // Timing
    std::chrono::milliseconds request_duration_ms{0};
    
    // Evidence for verification
    std::vector<Evidence> evidence;
    
    static ServiceResult success(std::string output, const Evidence& ev = {}) {
        ServiceResult r;
        r.succeeded = true;
        r.output = std::move(output);
        if (!ev.source.empty()) r.evidence.push_back(ev);
        return r;
    }
    
    static ServiceResult failure(std::string error, const Evidence& ev = {}) {
        ServiceResult r;
        r.error_message = std::move(error);
        if (!ev.source.empty()) r.evidence.push_back(ev);
        return r;
    }
    
    static ServiceResult timeout() {
        ServiceResult r;
        r.error_message = "semantic request timed out";
        return r;
    }
};

// ============================================================================
// SemanticServiceController — Interface for service lifecycle management
// ============================================================================

class SemanticServiceController {
public:
    virtual ~SemanticServiceController() = default;
    
    // Lifecycle control (may require privilege elevation)
    virtual bool start() = 0;           // Start the service (if not running)
    virtual bool stop() = 0;            // Stop the service gracefully
    virtual bool restart() = 0;         // Restart the service
    
    // State queries (always available)
    virtual LifecycleState lifecycle_state() const = 0;
    virtual ReadinessState readiness_state() const = 0;
    virtual HealthState health_state() const = 0;
    
    virtual ServiceState get_state() const = 0;  // Complete status
    virtual std::optional<std::string> state_detail() const = 0;
    
    // Service metrics
    virtual ServiceMetrics metrics() const = 0;
    
    // Cancel all pending operations (graceful shutdown)
    virtual void cancel_all_operations() = 0;
    
    // Semantic operations (delegate to provider)
    virtual ServiceResult classify(
        const std::string& text,
        std::chrono::milliseconds timeout = std::chrono::seconds(30),
        rebuntu::runtime::CancellationToken* cancellation_token = nullptr
    ) = 0;
    
    virtual ServiceResult generate_intent_candidate(
        const std::string& text,
        std::chrono::milliseconds timeout = std::chrono::seconds(30),
        rebuntu::runtime::CancellationToken* cancellation_token = nullptr
    ) = 0;
    
    virtual ServiceResult assess_evidence_relevance(
        const std::string& query,
        const std::string& evidence_text,
        std::chrono::milliseconds timeout = std::chrono::seconds(30),
        rebuntu::runtime::CancellationToken* cancellation_token = nullptr
    ) = 0;
    
    virtual ServiceResult summarize_diagnostics(
        const std::vector<std::string>& input_lines,
        size_t max_output_tokens = 512,
        std::chrono::milliseconds timeout = std::chrono::seconds(30),
        rebuntu::runtime::CancellationToken* cancellation_token = nullptr
    ) = 0;
};

// ============================================================================
// IPC endpoint configuration
// ============================================================================

struct ServiceIPCConfig {
    std::filesystem::path socket_path;     // Unix domain socket path
    mode_t permissions = 0660;             // Socket file permissions
    int max_connections = 10;              // Max pending connections
};

// ============================================================================
// Factory functions for service creation
// ============================================================================

// Create a controller that uses the system's native systemd supervisor
std::unique_ptr<SemanticServiceController> make_systemd_controller();

// Create a mock controller for testing (no systemd required)
std::unique_ptr<SemanticServiceController> make_mock_controller(
    std::unique_ptr<SemanticProvider> provider = nullptr);

}  // namespace rebuntu::semantic

namespace std {

// Hash support for enum class in unordered_map
template <>
struct hash<rebuntu::semantic::LifecycleState> {
    size_t operator()(rebuntu::semantic::LifecycleState s) const noexcept {
        return static_cast<size_t>(s);
    }
};

template <>
struct hash<rebuntu::semantic::ReadinessState> {
    size_t operator()(rebuntu::semantic::ReadinessState r) const noexcept {
        return static_cast<size_t>(r);
    }
};

}  // namespace std