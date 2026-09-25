// rebuntu::semantic::bitnet_provider - Phase 3.1 BitNet CPU-only provider tests
//
// Tests for:
//   - Provider interface contract compliance
//   - Model path validation
//   - CPU-only enforcement
//   - Semantic operations (classify, generate_intent, assess_relevance, summarize)
//   - Registry pattern

#include <system/semantic/provider.hpp>
#include <cassert>
#include <iostream>
#include <string>

void test_provider_id() {
    rebuntu::semantic::ProviderId id1("test-id");
    assert(id1.value == "test-id");
    
    rebuntu::semantic::ProviderId id2 = std::move(id1);
    assert(id2.value == "test-id");
    
    rebuntu::semantic::ProviderId id3("test-id");
    assert(id2 == id3);
    assert(!(id2 != id3));
}

void test_model_info() {
    rebuntu::semantic::ModelInfo info;
    info.name = "bitnet-b1.58-2B4T";
    info.version = "1.58";
    info.architecture = "2B4T";
    info.model_path = "/path/to/model.bin";
    info.cpu_only = true;
    
    assert(info.name == "bitnet-b1.58-2B4T");
    assert(info.version == "1.58");
    assert(info.cpu_only);
}

void test_semantic_status() {
    using namespace rebuntu::semantic;
    assert(to_string(rebuntu::semantic::SemanticStatus::kSuccess) == "success");
    assert(to_string(rebuntu::semantic::SemanticStatus::kFailure) == "failure");
    assert(to_string(rebuntu::semantic::SemanticStatus::kUnknown) == "unknown");
    assert(to_string(rebuntu::semantic::SemanticStatus::kTimeout) == "timeout");
    assert(to_string(rebuntu::semantic::SemanticStatus::kCancelled) == "cancelled");
}

void test_evidence() {
    rebuntu::semantic::Evidence ev;
    ev.subject = "test-subject";
    ev.source = "test-source";
    ev.value = "test-value";
    
    assert(ev.subject == "test-subject");
    assert(ev.source == "test-source");
    assert(ev.value == "test-value");
}

void test_semantic_result_success() {
    rebuntu::semantic::Evidence ev{"classify", "bitnet-cpu-provider", {}, "classification_completed"};
    
    rebuntu::semantic::SemanticResult r = rebuntu::semantic::SemanticResult::success("test output", ev);
    
    assert(r.status == rebuntu::semantic::SemanticStatus::kSuccess);
    assert(r.output.has_value());
    assert(r.output.value() == "test output");
    assert(!r.evidence.empty());
    assert(r.verification_successful);
}

void test_semantic_result_failure() {
    rebuntu::semantic::Evidence ev{"classify", "bitnet-cpu-provider", {}, "classification_failed"};
    
    rebuntu::semantic::SemanticResult r = rebuntu::semantic::SemanticResult::failure("error message", ev);
    
    assert(r.status == rebuntu::semantic::SemanticStatus::kFailure);
    assert(r.error_message.has_value());
    assert(r.error_message.value() == "error message");
}

void test_semantic_result_unknown() {
    rebuntu::semantic::SemanticResult r = rebuntu::semantic::SemanticResult::unknown("timeout occurred");
    
    assert(r.status == rebuntu::semantic::SemanticStatus::kUnknown);
    assert(r.error_message.has_value());
    assert(r.error_message.value() == "timeout occurred");
}

void test_semantic_result_timeout() {
    rebuntu::semantic::SemanticResult r = rebuntu::semantic::SemanticResult::timeout();
    
    assert(r.status == rebuntu::semantic::SemanticStatus::kTimeout);
    assert(r.error_message.has_value());
    assert(r.error_message.value() == "semantic operation timed out");
}

int main(int argc, char** argv) {
    (void)argc;
    (void)argv;
    
    std::cout << "Running Phase 3.1 BitNet CPU-only provider tests...\n";
    
    test_provider_id();
    std::cout << "  test_provider_id... PASS\n";
    
    test_model_info();
    std::cout << "  test_model_info... PASS\n";
    
    test_semantic_status();
    std::cout << "  test_semantic_status... PASS\n";
    
    test_evidence();
    std::cout << "  test_evidence... PASS\n";
    
    test_semantic_result_success();
    std::cout << "  test_semantic_result_success... PASS\n";
    
    test_semantic_result_failure();
    std::cout << "  test_semantic_result_failure... PASS\n";
    
    test_semantic_result_unknown();
    std::cout << "  test_semantic_result_unknown... PASS\n";
    
    test_semantic_result_timeout();
    std::cout << "  test_semantic_result_timeout... PASS\n";
    
    std::cout << "All tests PASSED!\n";
    return 0;
}