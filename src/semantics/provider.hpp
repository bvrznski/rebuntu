// rebuntu::semantic::Provider — BitNet Semantic Provider Contracts (Phase 3.1)
//
// This header establishes Rebuntu's typed interface for semantic/model providers.
// It defines what a semantic provider MUST implement, without dictating HOW it
// provides semantic services.
//
// Architecture:
//   Interfaces (what)        -> src/interfaces/
//   Adapters/Providers (how) -> cpp/src/semantic/provider_*.cpp
//
// Key principles:
//   * MODEL OUTPUT != AUTHORITY
//   * Semantic output must pass through validation before becoming policy
//   * CPU-only execution by default (GPU use requires explicit enablement)

#pragma once

#include <runtime/core/contracts.hpp>
#include <runtime/contracts.hpp>
#include <map>
#include <memory>
#include <optional>
#include <string>
#include <string_view>
#include <vector>
#include <chrono>

namespace rebuntu::semantic {

// ============================================================================
// Provider Identity
// ============================================================================

struct ProviderId {
    std::string value;
    
    explicit ProviderId(std::string v) : value(std::move(v)) {}
    explicit operator std::string() const { return value; }
};

inline bool operator==(const ProviderId& a, const ProviderId& b) {
    return a.value == b.value;
}

inline bool operator!=(const ProviderId& a, const ProviderId& b) {
    return !(a == b);
}

// ============================================================================
// Model Information
// ============================================================================

enum class ModelFamily {
    kBitNetB158_2B4T,  // Microsoft BitNet b1.58 2B4T (initial target)
};

inline std::string_view to_string(ModelFamily f) {
    switch (f) {
        case ModelFamily::kBitNetB158_2B4T: return "bitnet-b1.58-2b4t";
    }
    return "unknown";
}

struct ModelInfo {
    ModelFamily family;
    std::optional<std::string> model_path;      // Path to model artifacts
    std::optional<std::string> config_path;     // Path to configuration
    bool cpu_only = true;                        // CPU-only execution (default)
};

// ============================================================================
// Semantic Request Types
// ============================================================================

enum class SemanticRequestType {
    kClassification,   // Classify input into predefined categories
    kIntentCandidate,  // Generate candidate intent with structured output
    kEvidenceRelevance,// Assess relevance of evidence to context
    kDiagnosticSummary,// Summarize diagnostics for human consumption
};

inline std::string_view to_string(SemanticRequestType t) {
    switch (t) {
        case SemanticRequestType::kClassification:   return "classification";
        case SemanticRequestType::kIntentCandidate:  return "intent-candidate";
        case SemanticRequestType::kEvidenceRelevance:return "evidence-relevance";
        case SemanticRequestType::kDiagnosticSummary:return "diagnostic-summary";
    }
    return "unknown";
}

// ============================================================================
// Structured Output Types
// ============================================================================

struct ClassificationResult {
    std::vector<std::pair<std::string, double>> categories;  // (label, confidence)
};

struct IntentCandidate {
    std::string operation_id;      // The operation this intent suggests
    std::optional<std::string> subject;   // Target of the operation
    std::map<std::string, std::string> parameters;  // Operation parameters
    double confidence;             // Confidence in this candidate (0.0 - 1.0)
};

struct EvidenceRelevance {
    bool is_relevant;              // Is this evidence relevant?
    std::optional<double> relevance_score;  // Numeric score if available
    std::optional<std::string> explanation; // Why relevant/irrelevant
};

struct DiagnosticSummary {
    std::string summary;           // Human-readable summary
    std::vector<std::string> key_findings;
    std::optional<std::string> suggested_action;
};

// ============================================================================
// Semantic Response Types
// ============================================================================

struct SemanticResponse {
    SemanticRequestType request_type;
    
    std::chrono::system_clock::time_point requested_at;
    std::chrono::system_clock::time_point responded_at;
    
    // Timing information
    std::optional<std::chrono::milliseconds> inference_time_ms;
    
    // Response data (one of these will be set based on request type)
    std::optional<ClassificationResult> classification;
    std::optional<IntentCandidate> intent_candidate;
    std::optional<EvidenceRelevance> relevance;
    std::optional<DiagnosticSummary> summary;
    
    // Provider metadata
    std::string provider_id;
};

// ============================================================================
// Error Types
// ============================================================================

enum class SemanticError {
    kTimeout,              // Request timed out before response
    kModelNotAvailable,    // Model not loaded or unavailable
    kInvalidInput,         // Input failed validation
    kUnsupportedType,      // Request type not supported by this provider
    kProviderUnavailable,  // Provider process/daemon is not running
};

inline std::string_view to_string(SemanticError e) {
    switch (e) {
        case SemanticError::kTimeout:             return "E_SEMANTIC_TIMEOUT";
        case SemanticError::kModelNotAvailable:   return "E_SEMANTIC_MODEL_UNAVAILABLE";
        case SemanticError::kInvalidInput:        return "E_SEMANTIC_INVALID_INPUT";
        case SemanticError::kUnsupportedType:     return "E_SEMANTIC_UNSUPPORTED_TYPE";
        case SemanticError::kProviderUnavailable: return "E_SEMANTIC_PROVIDER_UNAVAILABLE";
    }
    return "E_SEMANTIC_UNKNOWN";
}

struct SemanticResult {
    core::SemanticStatus status;
    
    // Response data (where applicable)
    std::optional<SemanticResponse> response;
    
    // Error information (if not success)
    std::optional<core::Error> error;
    
    // Evidence for verification
    std::vector<core::Evidence> evidence;
    
    static SemanticResult success(SemanticResponse resp) {
        SemanticResult r;
        r.status = core::SemanticStatus::kSuccess;
        r.response = std::move(resp);
        return r;
    }
    
    static SemanticResult failure(std::string code, std::string message) {
        SemanticResult r;
        r.status = core::SemanticStatus::kFailure;
        r.error = core::Error{std::move(code), std::move(message)};
        return r;
    }
    
    static SemanticResult unavailable(std::string message) {
        SemanticResult r;
        r.status = core::SemanticStatus::kUnknown;
        r.error = core::Error{"E_SEMANTIC_UNAVAILABLE", std::move(message)};
        return r;
    }
};

// ============================================================================
// Provider Interface
// ============================================================================

class SemanticProvider {
public:
    virtual ~SemanticProvider() = default;
    
    // Get provider identity
    virtual ProviderId provider_id() const = 0;
    
    // Get model information
    virtual ModelInfo model_info() const = 0;
    
    // Check if provider is ready to accept requests
    virtual bool is_ready() const = 0;
    
    // Send a classification request
    virtual SemanticResult classify(
        const std::string& input,
        const std::vector<std::string>& categories,
        std::optional<std::chrono::milliseconds> timeout = std::nullopt
    ) = 0;
    
    // Generate an intent candidate from text
    virtual SemanticResult generate_intent_candidate(
        const std::string& input,
        const std::vector<std::string>& allowed_operations,
        std::optional<std::chrono::milliseconds> timeout = std::nullopt
    ) = 0;
    
    // Assess evidence relevance
    virtual SemanticResult assess_evidence_relevance(
        const std::string& evidence,
        const std::string& context,
        std::optional<std::chrono::milliseconds> timeout = std::nullopt
    ) = 0;
    
    // Summarize diagnostics
    virtual SemanticResult summarize_diagnostics(
        const std::vector<std::string>& diagnostic_items,
        std::optional<std::chrono::milliseconds> timeout = std::nullopt
    ) = 0;
};

// ============================================================================
// BitNet Provider (Microsoft bitnet.cpp integration)
// ============================================================================

namespace bitnet {

// Configuration for the BitNet runtime
struct Config {
    std::string model_path;           // Path to BitNet model directory
    bool cpu_only = true;              // CPU-only execution (required)
    std::optional<int64_t> memory_limit_bytes;
};

// The BitNet provider wraps the bitnet.cpp runtime
class Provider : public SemanticProvider {
public:
    explicit Provider(Config config);
    ~Provider() override;
    
    // Disable copy/move for resource management
    Provider(const Provider&) = delete;
    Provider& operator=(const Provider&) = delete;
    
    // SemanticProvider interface
    ProviderId provider_id() const override;
    semantic::ModelInfo model_info() const override;  // Use base ModelInfo
    bool is_ready() const override;
    
    SemanticResult classify(
        const std::string& input,
        const std::vector<std::string>& categories,
        std::optional<std::chrono::milliseconds> timeout = std::nullopt
    ) override;
    
    SemanticResult generate_intent_candidate(
        const std::string& input,
        const std::vector<std::string>& allowed_operations,
        std::optional<std::chrono::milliseconds> timeout = std::nullopt
    ) override;
    
    SemanticResult assess_evidence_relevance(
        const std::string& evidence,
        const std::string& context,
        std::optional<std::chrono::milliseconds> timeout = std::nullopt
    ) override;
    
    SemanticResult summarize_diagnostics(
        const std::vector<std::string>& diagnostic_items,
        std::optional<std::chrono::milliseconds> timeout = std::nullopt
    ) override;

private:
    class Impl;
    std::unique_ptr<Impl> pimpl_;
};

}  // namespace bitnet

// ============================================================================
// Provider Registry (defined after SemanticProvider to access its types)
// ============================================================================

class SemanticProviderRegistry {
public:
    // Register a provider (takes ownership by moving into internal storage)
    void add_provider(std::unique_ptr<SemanticProvider> provider);
    
    // Get all registered providers (returns copies of unique_ptrs)
    std::vector<std::unique_ptr<SemanticProvider>> all_providers() const;
    
    // Find a provider by ID
    std::optional<SemanticProvider*> find_provider(const ProviderId& id) const;
    
    // Assess if semantic capability is available
    bool is_semantic_available() const;

private:
    // Use raw pointer storage to avoid vector unique_ptr issues with C++11/14
    // The registry takes ownership via move semantics when adding
    std::vector<SemanticProvider*> providers_;
};

}  // namespace rebuntu::semantic

// ============================================================================
// Hash support for ProviderId
// ============================================================================

namespace std {
template <> struct hash<rebuntu::semantic::ProviderId> {
    size_t operator()(const rebuntu::semantic::ProviderId& id) const noexcept {
        return std::hash<std::string>{}(id.value);
    }
};
}  // namespace std