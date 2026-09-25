// rebuntu::semantic::provider — BitNet CPU-only semantic provider interface (Phase 3.1)
//
// This header establishes the semantic provider contract for Rebuntu's native
// BitNet b1.58 2B4T model integration.
//
// Key invariants:
//   - CPU-only execution by default (GPU disabled)
//   - Model path must be validated before use
//   - All operations have bounded timeout support
//   - Results include evidence for verification

#pragma once

#include <string>
#include <vector>
#include <chrono>
#include <optional>
#include <memory>
#include <cstdint>

namespace rebuntu::semantic {

// ============================================================================
// ProviderId — Unique identifier for a semantic provider
// ============================================================================

struct ProviderId {
    std::string value;
    
    ProviderId() = default;
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
// ModelInfo — Static information about a semantic model
// ============================================================================

struct ModelInfo {
    std::string name;           // e.g., "bitnet-b1.58-2B4T"
    std::string version;        // e.g., "1.58"
    std::string architecture;   // e.g., "2B4T" (2 Billion parameters, 4-bit quantization)
    std::string model_path;     // path to the model file
    std::optional<std::string> config_path;  // optional path to model config
    bool cpu_only = true;       // CPU-only enforcement (default: true)
};

// ============================================================================
// SemanticStatus — Outcome of semantic operations
// ============================================================================

enum class SemanticStatus {
    kSuccess,         // Operation completed successfully with valid output
    kFailure,         // Operation failed or produced invalid output
    kUnknown,         // Could not determine status (timeout, no response, etc.)
    kTimeout,         // Operation exceeded timeout threshold
    kCancelled,       // Operation was cancelled
};

inline std::string to_string(SemanticStatus s) {
    switch (s) {
        case SemanticStatus::kSuccess:   return "success";
        case SemanticStatus::kFailure:   return "failure";
        case SemanticStatus::kUnknown:   return "unknown";
        case SemanticStatus::kTimeout:   return "timeout";
        case SemanticStatus::kCancelled: return "cancelled";
    }
    return "unknown";
}

// ============================================================================
// Evidence — Provenance-bearing observation
// ============================================================================

struct Evidence {
    std::string subject;                     // What the evidence is about
    std::string source;                      // Where it came from
    std::chrono::system_clock::time_point observed_at;
    std::string value;                       // The observed value
};

// ============================================================================
// SemanticResult — Result of a semantic operation with verification tracking
// ============================================================================

struct SemanticResult {
    SemanticStatus status = SemanticStatus::kUnknown;
    std::optional<std::string> output;       // Model-generated output (if any)
    std::vector<Evidence> evidence;          // Evidence supporting the result
    std::chrono::milliseconds response_time_ms{0};
    std::optional<std::string> error_message;// Error details if failed
    bool verification_successful = false;    // Was postcondition verified?
    
    // Static constructors
    static SemanticResult success(std::string output, const Evidence& ev = {}) {
        SemanticResult r;
        r.status = SemanticStatus::kSuccess;
        r.output = std::move(output);
        if (!ev.source.empty()) r.evidence.push_back(ev);
        r.verification_successful = true;
        return r;
    }
    
    static SemanticResult failure(std::string error, const Evidence& ev = {}) {
        SemanticResult r;
        r.status = SemanticStatus::kFailure;
        r.error_message = std::move(error);
        if (!ev.source.empty()) r.evidence.push_back(ev);
        return r;
    }
    
    static SemanticResult unknown(std::string message) {
        SemanticResult r;
        r.status = SemanticStatus::kUnknown;
        r.error_message = std::move(message);
        return r;
    }
    
    static SemanticResult timeout() {
        SemanticResult r;
        r.status = SemanticStatus::kTimeout;
        r.error_message = "semantic operation timed out";
        return r;
    }
    
    static SemanticResult cancelled(std::string reason) {
        SemanticResult r;
        r.status = SemanticStatus::kCancelled;
        r.error_message = std::move(reason);
        return r;
    }
    
    bool succeeded() const {
        return status == SemanticStatus::kSuccess && verification_successful;
    }
};

// ============================================================================
// BitNetConfig — Configuration for BitNet provider
// ============================================================================

struct BitNetConfig {
    std::string model_path;           // Path to the .bin or .ggml model file
    std::optional<std::string> config_path;  // Optional path to model config
    bool cpu_only = true;             // CPU-only enforcement (default: true)
    size_t context_size = 2048;       // Maximum context length in tokens
    size_t batch_size = 512;          // Batch size for inference
    std::chrono::milliseconds default_timeout = std::chrono::seconds(30);
    std::chrono::milliseconds verification_timeout = std::chrono::seconds(10);
};

// ============================================================================
// GPUPolicy — Explicit control over GPU usage in semantic providers
// ============================================================================

enum class GPUPolicy {
    kCPUOnly,        // Force CPU-only execution (default for security)
    kAllowGPU,       // Allow GPU usage if available  
    kRequireGPU,     // Fail if GPU is not available
};

inline std::string to_string(GPUPolicy p) {
    switch (p) {
        case GPUPolicy::kCPUOnly: return "cpu_only";
        case GPUPolicy::kAllowGPU: return "allow_gpu";
        case GPUPolicy::kRequireGPU: return "require_gpu";
    }
    return "unknown";
}

// ============================================================================
// ModelArtifact — Information about a downloaded model artifact
// ============================================================================

struct ModelArtifact {
    std::string path;
    std::optional<std::string> expected_sha256;  // If present, will be verified
    bool verified = false;
    size_t size_bytes = 0;
};

// ============================================================================
// ArtifactResult — Result of a model artifact operation  
// ============================================================================

struct ArtifactResult {
    bool succeeded = false;
    ModelArtifact artifact;
    std::optional<std::string> error_message;
    
    static ArtifactResult make_success(const ModelArtifact& m) {
        ArtifactResult r;
        r.succeeded = true;
        r.artifact = m;
        return r;
    }
    
    static ArtifactResult make_failure(std::string message) {
        ArtifactResult r;
        r.error_message = std::move(message);
        return r;
    }
};

// ============================================================================
// AvailableArtifact — Information about available model artifacts
// ============================================================================

struct AvailableArtifact {
    std::string name;
    std::string url;           // Where to download from
    size_t size_bytes = 0;
    std::optional<std::string> sha256;  // Expected checksum for verification
    
    bool requires_verification() const { return sha256.has_value(); }
};

// ============================================================================
// ModelArtifactManager — Interface for model artifact operations
// ============================================================================

class ModelArtifactManager {
public:
    virtual ~ModelArtifactManager() = default;
    
    // Discover available artifacts from configuration or registry
    virtual std::vector<AvailableArtifact> discover_available_artifacts() const = 0;
    
    // Download an artifact to a target path
    // Returns success with downloaded path, or failure with error message
    virtual ArtifactResult download_artifact(const AvailableArtifact& artifact,
                                              const std::string& target_path) = 0;
    
    // Verify checksum of a downloaded file
    virtual bool verify_checksum(const std::string& path, const std::string& expected_sha256) = 0;
    
    // Get cached artifacts (already downloaded but not necessarily verified)
    virtual std::vector<ModelArtifact> get_cached_artifacts() const = 0;
    
    // Clear cache (delete downloaded files)
    virtual void clear_cache() = 0;
};

// Factory for artifact manager
std::unique_ptr<ModelArtifactManager> make_artifact_manager();

// ============================================================================
// Validation helpers (defined in implementation file)
// ============================================================================

namespace validation {

bool model_path_exists(const std::string& path);
bool appears_to_be_bitnet_model(const std::string& path);
bool validate_config(const BitNetConfig& config, std::vector<std::string>* errors = nullptr);

}  // namespace validation

// ============================================================================
// SemanticProvider — Interface for semantic/model inference providers
// ============================================================================

class SemanticProvider {
public:
    virtual ~SemanticProvider() = default;
    
    // Provider identification
    virtual ProviderId provider_id() const = 0;
    virtual ModelInfo model_info() const = 0;
    
    // Readiness checks
    virtual bool is_ready() const = 0;                     // Can accept requests now?
    virtual std::optional<std::string> readiness_issue() const = 0;  // Why not ready?
    
    // Semantic operations with optional timeout support
    
    // Classify input text into predefined categories
    virtual SemanticResult classify(
        const std::string& text,
        std::chrono::milliseconds timeout = std::chrono::seconds(30)
    ) = 0;
    
    // Generate an intent candidate from natural language input
    virtual SemanticResult generate_intent_candidate(
        const std::string& text,
        std::chrono::milliseconds timeout = std::chrono::seconds(30)
    ) = 0;
    
    // Assess relevance of evidence for a given query/context
    virtual SemanticResult assess_evidence_relevance(
        const std::string& query,
        const std::string& evidence_text,
        std::chrono::milliseconds timeout = std::chrono::seconds(30)
    ) = 0;
    
    // Summarize diagnostic or log information
    virtual SemanticResult summarize_diagnostics(
        const std::vector<std::string>& input_lines,
        size_t max_output_tokens = 512,
        std::chrono::milliseconds timeout = std::chrono::seconds(30)
    ) = 0;
    
    // Get the last response time for metrics
    virtual std::optional<std::chrono::milliseconds> last_response_time() const = 0;
};

// ============================================================================
// SemanticProviderFactory — Factory for creating semantic providers
// ============================================================================

class SemanticProviderFactory {
public:
    virtual ~SemanticProviderFactory() = default;
    
    // Create a BitNet provider with the specified model path
    // Returns nullptr if the model cannot be loaded
    virtual std::unique_ptr<SemanticProvider> create_bitnet_provider(
        const std::string& model_path,
        bool cpu_only = true,
        std::chrono::milliseconds timeout = std::chrono::seconds(30)
    ) = 0;
    
    // Check if a provider can be created for the given path
    virtual bool can_create_provider(const std::string& model_path) const = 0;
};

// ============================================================================
// ProviderRegistry — Central registry for semantic providers
// ============================================================================

class ProviderRegistry {
public:
    virtual ~ProviderRegistry() = default;
    
    // Register a provider (takes ownership)
    virtual void register_provider(std::unique_ptr<SemanticProvider> provider) = 0;
    
    // Unregister a provider by ID
    virtual void unregister_provider(const ProviderId& id) = 0;
    
    // Check if a provider is registered
    virtual bool has_provider(const ProviderId& id) const = 0;
    
    // Get a provider by ID (returns nullptr if not found)
    virtual SemanticProvider* get_provider(const ProviderId& id) = 0;
    
    // Get all registered providers
    virtual std::vector<SemanticProvider*> all_providers() const = 0;
    
    // Check if any semantic provider is available
    virtual bool is_semantic_available() const = 0;
};

// ============================================================================
// Factory functions (defined in implementation file)
// ============================================================================

std::unique_ptr<SemanticProviderFactory> make_bitnet_factory();
std::unique_ptr<ProviderRegistry> make_provider_registry();

}  // namespace rebuntu::semantic