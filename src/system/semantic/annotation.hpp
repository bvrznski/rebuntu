// rebuntu::semantic::annotation — Semantic Annotation Boundary (Phase 5.43)
//
// This module establishes Rebuntu's typed semantic annotation boundary for
// observations that may later be packaged for semantic analysis.
//
// Architecture:
//   Annotations -> src/system/semantic/annotation.hpp
//   Provider    -> src/system/semantic/annotation_provider.cpp
//
// Key principles:
//   * MODEL OUTPUT != AUTHORITY
//   * Semantic output remains SEMANTIC_ANNOTATION/HYPOTHESIS (not fact)
//   * Observations are evidence; annotations are interpretations
//   * Boundary provides future-safe packaging for semantic analysis

#pragma once

#include <chrono>
#include <memory>
#include <optional>
#include <string>
#include <vector>

#include <system/core/contracts.hpp>
#include <runtime/contracts.hpp>

namespace rebuntu::semantic {

// ============================================================================
// AnnotationKind — Types of semantic annotations
// ============================================================================

enum class AnnotationKind {
    kHypothesis,
    kClassification,
    kCorrelation,
    kInference,
    kContextual,
};

inline std::string to_string(AnnotationKind kind) {
    switch (kind) {
        case AnnotationKind::kHypothesis:   return "hypothesis";
        case AnnotationKind::kClassification: return "classification";
        case AnnotationKind::kCorrelation:  return "correlation";
        case AnnotationKind::kInference:    return "inference";
        case AnnotationKind::kContextual:   return "contextual";
    }
    return "unknown";
}

// ============================================================================
// AnnotationConfidence — Confidence level in an annotation
// ============================================================================

enum class AnnotationConfidence {
    kHigh,
    kMedium,
    kLow,
    kUnknown,
};

inline std::string to_string(AnnotationConfidence confidence) {
    switch (confidence) {
        case AnnotationConfidence::kHigh:   return "high";
        case AnnotationConfidence::kMedium: return "medium";
        case AnnotationConfidence::kLow:    return "low";
        case AnnotationConfidence::kUnknown:return "unknown";
    }
    return "unknown";
}

// ============================================================================
// AnnotationSource — Where the annotation came from
// ============================================================================

enum class AnnotationSource {
    kDirectObservation,
    kDeduced,
    kCorrelated,
    kModelHypothesis,
    kHeuristic,
};

inline std::string to_string(AnnotationSource source) {
    switch (source) {
        case AnnotationSource::kDirectObservation: return "direct-observation";
        case AnnotationSource::kDeduced:           return "deduced";
        case AnnotationSource::kCorrelated:        return "correlated";
        case AnnotationSource::kModelHypothesis:   return "model-hypothesis";
        case AnnotationSource::kHeuristic:         return "heuristic";
    }
    return "unknown";
}

// ============================================================================
// AnnotationEvidence — Evidence supporting an annotation
// ============================================================================

struct AnnotationEvidence {
    std::string source;
    std::chrono::system_clock::time_point timestamp;
    std::optional<std::string> record_id;
    std::optional<std::string> value;
};

// ============================================================================
// Annotation — A semantic annotation of an observation
// ============================================================================

struct Annotation {
    std::string id;
    std::chrono::system_clock::time_point created_at;
    
    AnnotationKind kind;
    std::string label;
    std::string description;
    
    AnnotationConfidence confidence;
    double confidence_score;
    
    AnnotationSource source;
    std::optional<std::string> source_id;
    
    std::vector<AnnotationEvidence> supporting_evidence;
    
    std::optional<std::string> missing_evidence;
    std::optional<std::string> alternative_explanations;
    
    std::vector<std::string> related_observation_ids;
};

// ============================================================================
// AnnotationPackaging — Container for packaging annotations with observations
// ============================================================================

struct AnnotationPackaging {
    std::vector<core::Evidence> observations;
    std::vector<Annotation> annotations;
    
    std::chrono::system_clock::time_point packaged_at;
    std::optional<std::string> context;
    
    std::optional<std::string> annotator_id;
    AnnotationSource annotator_source;
    
    bool verified = false;
};

// ============================================================================
// AnnotationRequest — Request to create annotations from observations
// ============================================================================

struct AnnotationRequest {
    std::string id;
    
    std::vector<core::Evidence> observations;
    
    std::optional<std::chrono::milliseconds> timeout_ms;
    size_t max_annotations = 100;
    bool include_evidence_details = true;
    
    std::chrono::system_clock::time_point created_at;
    std::optional<std::string> context;
};

// ============================================================================
// AnnotationResult — Result of annotation generation
// ============================================================================

struct AnnotationResult {
    core::SemanticStatus status;
    std::string description;
    
    std::vector<Annotation> annotations;
    std::vector<core::Evidence> annotated_observations;
    
    std::chrono::system_clock::time_point completed_at;
    std::optional<std::chrono::milliseconds> elapsed_ms;
    
    std::optional<core::Error> error;
    
    static AnnotationResult success(std::vector<Annotation> anns, std::vector<core::Evidence> obs) {
        AnnotationResult r;
        r.status = core::SemanticStatus::kSuccess;
        r.annotations = std::move(anns);
        r.annotated_observations = std::move(obs);
        return r;
    }
    
    static AnnotationResult completed() {
        AnnotationResult r;
        r.status = core::SemanticStatus::kCompleted;
        return r;
    }
    
    static AnnotationResult failure(std::string code, std::string message) {
        AnnotationResult r;
        r.status = core::SemanticStatus::kFailure;
        r.error = core::Error{std::move(code), std::move(message)};
        return r;
    }
    
    static AnnotationResult unknown(std::string message) {
        AnnotationResult r;
        r.status = core::SemanticStatus::kUnknown;
        r.error = core::Error{"E_ANNOTATION_UNKNOWN", std::move(message)};
        return r;
    }
};

// ============================================================================
// AnnotationProviderOptions — Configuration for annotation provider
// ============================================================================

struct AnnotationProviderOptions {
    std::chrono::milliseconds default_timeout_ms{30000};
    
    size_t max_annotations_per_request = 100;
    
    double min_confidence_score = 0.5;
    
    std::vector<AnnotationSource> enabled_sources{
        AnnotationSource::kDeduced,
        AnnotationSource::kHeuristic,
        AnnotationSource::kCorrelated,
    };
    
    bool preserve_evidence_details = true;
};

// ============================================================================
// AnnotationProviderMetrics — Runtime metrics for annotation provider
// ============================================================================

struct AnnotationProviderMetrics {
    std::chrono::system_clock::time_point started_at;
    size_t requests_received = 0;
    size_t annotations_generated = 0;
    size_t failures = 0;
    size_t timeouts = 0;
};

// ============================================================================
// AnnotationProvider — Interface for semantic annotation generation
// ============================================================================

class AnnotationProvider {
public:
    virtual ~AnnotationProvider() = default;
    
    virtual std::string provider_id() const = 0;
    
    virtual core::Outcome configure(const AnnotationProviderOptions& options) = 0;
    
    virtual core::Outcome start() = 0;
    virtual core::Outcome stop() = 0;
    virtual bool is_running() const = 0;
    
    virtual AnnotationResult annotate_observations(const AnnotationRequest& request) = 0;
    
    virtual AnnotationPackaging package_annotations(
        const std::vector<core::Evidence>& observations,
        const std::vector<Annotation>& annotations,
        std::optional<std::string> context = std::nullopt
    ) = 0;
    
    virtual AnnotationProviderMetrics metrics() const = 0;
};

// ============================================================================
// DeterministicAnnotationProvider — Default deterministic provider
// ============================================================================

class DeterministicAnnotationProvider : public AnnotationProvider {
public:
    explicit DeterministicAnnotationProvider();
    ~DeterministicAnnotationProvider() override;
    
    DeterministicAnnotationProvider(const DeterministicAnnotationProvider&) = delete;
    DeterministicAnnotationProvider& operator=(const DeterministicAnnotationProvider&) = delete;
    
    std::string provider_id() const override;
    
    core::Outcome configure(const AnnotationProviderOptions& options) override;
    
    core::Outcome start() override;
    core::Outcome stop() override;
    bool is_running() const override;
    
    AnnotationResult annotate_observations(const AnnotationRequest& request) override;
    
    AnnotationPackaging package_annotations(
        const std::vector<core::Evidence>& observations,
        const std::vector<Annotation>& annotations,
        std::optional<std::string> context = std::nullopt
    ) override;
    
    AnnotationProviderMetrics metrics() const override;

private:
    class Impl;
    std::unique_ptr<Impl> pimpl_;
};

// ============================================================================
// AnnotationProviderRegistry — Registry of known annotation providers
// ============================================================================

class AnnotationProviderRegistry {
public:
    void add_provider(std::unique_ptr<AnnotationProvider> provider);
    
    std::vector<std::unique_ptr<AnnotationProvider>> all_providers() const;
    
    std::optional<AnnotationProvider*> find_provider(const std::string& id) const;
    
    bool is_annotation_available() const;

private:
    std::vector<AnnotationProvider*> providers_;
};

// ============================================================================
// Factory function — Create default annotation provider
// ============================================================================

std::unique_ptr<AnnotationProvider> make_annotation_provider();

}  // namespace rebuntu::semantic