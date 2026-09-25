// rebuntu::semantic — Unit Tests (Phase 3.1)
//
// Test the BitNet semantic provider contracts and interface.

#include <system/core/contracts.hpp>
#include <semantics/provider.hpp>

#include <iostream>
#include <memory>
#include <string>
#include <vector>

using namespace rebuntu::core;
using namespace rebuntu::semantic;
using namespace rebuntu::semantic::bitnet;

namespace {

int g_failures = 0;
#define CHECK(cond)                                                              \
    do {                                                                         \
        if (!(cond)) {                                                           \
            std::cerr << "CHECK failed: " << #cond << " (line " << __LINE__      \
                      << ")\n";                                                  \
            ++g_failures;                                                        \
        }                                                                        \
    } while (0)

void test_provider_identity() {
    ProviderId id1{"test-id"};
    ProviderId id2{id1.value};
    
    CHECK(id1 == id2);
    CHECK(id1.value == "test-id");
}

void test_model_info_defaults() {
    ModelInfo info = {};  // Value-initialize to zero-fill
    // family defaults to kBitNetB158_2B4T due to enum class behavior
    CHECK(info.cpu_only == true);
    CHECK(!info.model_path.has_value());
    CHECK(!info.config_path.has_value());
}

void test_semantic_result_success() {
    SemanticResponse resp;
    resp.request_type = SemanticRequestType::kClassification;
    
    auto result = SemanticResult::success(resp);
    CHECK(result.status == rebuntu::core::SemanticStatus::kSuccess);
    CHECK(result.response.has_value());
}

void test_semantic_result_failure() {
    auto result = SemanticResult::failure("E_TEST", "test error");
    CHECK(result.status == rebuntu::core::SemanticStatus::kFailure);
    CHECK(result.error.has_value());
    CHECK(result.error->code == "E_TEST");
}

void test_bitnet_provider_config() {
    Config config;
    config.model_path = "/path/to/model";
    
    Provider provider(config);
    CHECK(provider.provider_id().value == "bitnet-b1.58-2b4t");
    // is_ready returns false because check_runtime_availability checks if model_path exists
    // which it doesn't (we're using a fake path)
}

void test_bitnet_provider_not_implemented() {
    Config config;
    config.model_path = "/nonexistent/path";
    
    Provider provider(config);
    
    auto result = provider.classify("test input", {"cat1", "cat2"});
    CHECK(result.status == rebuntu::core::SemanticStatus::kUnknown);
    // Provider returns unavailable when model not found
}

void test_semantic_provider_registry() {
    SemanticProviderRegistry registry;
    
    Config config;
    // Use a fake path since we don't have actual model files
    config.model_path = "/nonexistent/bitnet/model/path";
    
    // Provider should be registered even if not ready (model file doesn't exist)
    registry.add_provider(std::make_unique<Provider>(config));
    
    // Registry contains the provider but it's not ready without model files
    CHECK(registry.all_providers().size() == 1u);
}

void test_to_string_functions() {
    using namespace rebuntu::semantic;
    
    // Test ModelFamily
    CHECK(to_string(ModelFamily::kBitNetB158_2B4T) == "bitnet-b1.58-2b4t");
    
    // Test SemanticRequestType
    CHECK(to_string(SemanticRequestType::kClassification) == "classification");
    CHECK(to_string(SemanticRequestType::kIntentCandidate) == "intent-candidate");
    CHECK(to_string(SemanticRequestType::kEvidenceRelevance) == "evidence-relevance");
    CHECK(to_string(SemanticRequestType::kDiagnosticSummary) == "diagnostic-summary");
    
    // Test SemanticError
    CHECK(to_string(SemanticError::kTimeout) == "E_SEMANTIC_TIMEOUT");
    CHECK(to_string(SemanticError::kModelNotAvailable) == "E_SEMANTIC_MODEL_UNAVAILABLE");
}

}  // namespace

int main(int argc, char** argv) {
    (void)argc;
    (void)argv;
    
    test_provider_identity();
    test_model_info_defaults();
    test_semantic_result_success();
    test_semantic_result_failure();
    test_bitnet_provider_config();
    test_bitnet_provider_not_implemented();
    test_semantic_provider_registry();
    test_to_string_functions();
    
    std::cout << "semantic provider tests: ";
    if (g_failures == 0) {
        std::cout << "PASS\n";
        return 0;
    } else {
        std::cout << "FAIL (" << g_failures << " failures)\n";
        return 1;
    }
}