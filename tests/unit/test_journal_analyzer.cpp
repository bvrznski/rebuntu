// rebuntu::test_journal_analyzer — Unit Tests for Journal Analyzer (Phase 5.4)
//
// Tests deterministic journal analysis, failure classification,
// correlation and causal hypothesis generation.

#include "adapters/journal_analyzer.hpp"
#include "adapters/journal_normalizer.hpp"

#include <gtest/gtest.h>
#include <chrono>

namespace rebuntu::adapters {

// ============================================================================
// Helper functions
// ============================================================================

static NormalizedEvent make_normalized_event(
    const std::string& message,
    int priority = 6) {
    NormalizedEvent result;
    
    // Create a basic runtime event with evidence
    result.event.source = "journald";
    result.event.type = (priority <= 2) ? "error" : "info";
    
    core::Evidence e1;
    e1.source = "journal_message";
    e1.value = message;
    result.original_evidence.push_back(e1);
    
    core::Evidence e2;
    e2.source = "journal_priority";
    e2.value = std::to_string(priority);
    result.original_evidence.push_back(e2);
    
    return result;
}

// ============================================================================
// FailureClass to_string tests
// ============================================================================

TEST(JournalAnalyzerTest, FailureClassToString) {
    EXPECT_EQ(to_string(FailureClass::kNone), "none");
    EXPECT_EQ(to_string(FailureClass::kOOM), "oom");
    EXPECT_EQ(to_string(FailureClass::kServiceFailure), "service_failure");
    EXPECT_EQ(to_string(FailureClass::kKernelCrash), "kernel_crash");
    EXPECT_EQ(to_string(FailureClass::kGPUFault), "gpu_fault");
}

// ============================================================================
// Severity to_string tests
// ============================================================================

TEST(JournalAnalyzerTest, SeverityToString) {
    EXPECT_EQ(to_string(Severity::kUnknown), "unknown");
    EXPECT_EQ(to_string(Severity::kInfo), "info");
    EXPECT_EQ(to_string(Severity::kLow), "low");
    EXPECT_EQ(to_string(Severity::kMedium), "medium");
    EXPECT_EQ(to_string(Severity::kHigh), "high");
    EXPECT_EQ(to_string(Severity::kCritical), "critical");
}

// ============================================================================
// EvidenceConfidence to_string tests
// ============================================================================

TEST(JournalAnalyzerTest, EvidenceConfidenceToString) {
    EXPECT_EQ(to_string(EvidenceConfidence::kDirect), "direct");
    EXPECT_EQ(to_string(EvidenceConfidence::kDeduced), "deduced");
    EXPECT_EQ(to_string(EvidenceConfidence::kCorrelated), "correlated");
    EXPECT_EQ(to_string(EvidenceConfidence::kHypothesized), "hypothesized");
}

// ============================================================================
// AnalysisResult default initialization tests
// ============================================================================

TEST(JournalAnalyzerTest, AnalysisResultDefaults) {
    AnalysisResult r;
    
    EXPECT_EQ(r.failure_class, FailureClass::kNone);
    EXPECT_EQ(r.severity, Severity::kUnknown);
    EXPECT_EQ(r.confidence, EvidenceConfidence::kDirect);
    EXPECT_FALSE(r.verified);
}

// ============================================================================
// JournalAnalyzer creation tests
// ============================================================================

TEST(JournalAnalyzerTest, FactoryCreatesValidAnalyzer) {
    auto analyzer = make_journal_analyzer();
    
    ASSERT_NE(analyzer, nullptr);
}

// ============================================================================
// Failure signature detection tests
// ============================================================================

TEST(JournalAnalyzerTest, DetectsOOMFromMessage) {
    JournalAnalyzerConfig config;
    auto analyzer = make_journal_analyzer(config);
    
    auto event = make_normalized_event("Out of memory: Kill process 1234");
    std::vector<NormalizedEvent> events{event};
    
    auto results = analyzer->analyze_events(events, std::chrono::system_clock::now());
    
    EXPECT_EQ(results.size(), 1u);
    EXPECT_EQ(results[0].failure_class, FailureClass::kOOM);
}

TEST(JournalAnalyzerTest, DetectsServiceFailure) {
    JournalAnalyzerConfig config;
    auto analyzer = make_journal_analyzer(config);
    
    auto event = make_normalized_event("Failed to start ssh.service");
    std::vector<NormalizedEvent> events{event};
    
    auto results = analyzer->analyze_events(events, std::chrono::system_clock::now());
    
    EXPECT_EQ(results.size(), 1u);
    EXPECT_EQ(results[0].failure_class, FailureClass::kServiceFailure);
}

TEST(JournalAnalyzerTest, DetectsKernelPanic) {
    JournalAnalyzerConfig config;
    auto analyzer = make_journal_analyzer(config);
    
    auto event = make_normalized_event("Kernel panic - not syncing");
    std::vector<NormalizedEvent> events{event};
    
    auto results = analyzer->analyze_events(events, std::chrono::system_clock::now());
    
    EXPECT_EQ(results.size(), 1u);
    EXPECT_EQ(results[0].failure_class, FailureClass::kKernelCrash);
}

// ============================================================================
// Non-failure message tests
// ============================================================================

TEST(JournalAnalyzerTest, NonFailureMessageClassification) {
    JournalAnalyzerConfig config;
    auto analyzer = make_journal_analyzer(config);
    
    auto event = make_normalized_event("Systemd service started successfully");
    std::vector<NormalizedEvent> events{event};
    
    auto results = analyzer->analyze_events(events, std::chrono::system_clock::now());
    
    EXPECT_EQ(results.size(), 1u);
    EXPECT_EQ(results[0].failure_class, FailureClass::kNone);
    EXPECT_EQ(results[0].severity, Severity::kInfo);
}

// ============================================================================
// Evidence preservation tests
// ============================================================================

TEST(JournalAnalyzerTest, EvidenceReferencesPreserved) {
    JournalAnalyzerConfig config;
    auto analyzer = make_journal_analyzer(config);
    
    auto event = make_normalized_event("Out of memory error");
    std::vector<NormalizedEvent> events{event};
    
    auto results = analyzer->analyze_events(events, std::chrono::system_clock::now());
    
    EXPECT_FALSE(results[0].raw_evidence_pointers.empty());
    EXPECT_GT(results[0].raw_evidence_pointers.size(), 0u);
}

// ============================================================================
// Confidence assessment tests
// ============================================================================

TEST(JournalAnalyzerTest, DirectEvidenceConfidence) {
    JournalAnalyzerConfig config;
    auto analyzer = make_journal_analyzer(config);
    
    auto event = make_normalized_event("OOM detected");
    std::vector<NormalizedEvent> events{event};
    
    auto results = analyzer->analyze_events(events, std::chrono::system_clock::now());
    
    EXPECT_EQ(results[0].confidence, EvidenceConfidence::kDirect);
}

// ============================================================================
// Possible causes and alternatives tests
// ============================================================================

TEST(JournalAnalyzerTest, PossibleCausesPopulated) {
    JournalAnalyzerConfig config;
    auto analyzer = make_journal_analyzer(config);
    
    auto event = make_normalized_event("Out of memory: Kill process 1234");
    std::vector<NormalizedEvent> events{event};
    
    auto results = analyzer->analyze_events(events, std::chrono::system_clock::now());
    
    EXPECT_FALSE(results[0].possible_causes.empty());
}

TEST(JournalAnalyzerTest, AlternativeHypothesesGenerated) {
    JournalAnalyzerConfig config;
    auto analyzer = make_journal_analyzer(config);
    
    // Create an event that matches multiple signatures
    auto event = make_normalized_event("Out of memory error");
    std::vector<NormalizedEvent> events{event};
    
    auto results = analyzer->analyze_events(events, std::chrono::system_clock::now());
    
    EXPECT_GT(results[0].possible_causes.size(), 1u);
}

// ============================================================================
// Metrics tracking tests
// ============================================================================

TEST(JournalAnalyzerTest, MetricsTracking) {
    JournalAnalyzerConfig config;
    auto analyzer = make_journal_analyzer(config);
    
    // Analyze some events
    for (int i = 0; i < 5; ++i) {
        auto event = make_normalized_event("test message " + std::to_string(i));
        std::vector<NormalizedEvent> events{event};
        analyzer->analyze_events(events, std::chrono::system_clock::now());
    }
    
    auto metrics = analyzer->metrics();
    
    EXPECT_EQ(metrics.events_analyzed, 5u);
}

// ============================================================================
// CorrelationEngine tests
// ============================================================================

TEST(JournalAnalyzerTest, CorrelationEngineAddEvent) {
    CorrelationEngine engine(std::chrono::seconds(60));
    
    AnalysisResult result;
    result.failure_class = FailureClass::kOOM;
    
    engine.add_event(result);
    
    auto correlated = engine.get_correlated_events();
    EXPECT_EQ(correlated.size(), 1u);
}

TEST(JournalAnalyzerTest, CorrelationEngineSummary) {
    CorrelationEngine engine(std::chrono::seconds(60));
    
    AnalysisResult r1;
    r1.failure_class = FailureClass::kOOM;
    r1.severity = Severity::kCritical;
    r1.subject = "systemd";
    
    engine.add_event(r1);
    
    auto summary = engine.summary();
    
    EXPECT_EQ(summary.event_count, 1u);
}

// ============================================================================
// Service state tracking tests
// ============================================================================

TEST(JournalAnalyzerTest, ServiceStateTracking) {
    JournalAnalyzerConfig config;
    auto analyzer = make_journal_analyzer(config);
    
    // Update service state multiple times to simulate restarts
    for (int i = 0; i < 5; ++i) {
        AnalysisResult result;
        result.subject = "test.service";
        result.failure_class = FailureClass::kServiceFailure;
        analyzer->update_service_state(result);
    }
    
    auto metrics = analyzer->metrics();
}

}  // namespace rebuntu::adapters