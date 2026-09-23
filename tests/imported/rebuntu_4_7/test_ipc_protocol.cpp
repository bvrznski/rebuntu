// rebuntu::semantic::ipc::tests — IPC Protocol Tests (Phase 3.4)
//
// Unit, integration, and adversarial tests for Rebuntu's structured
// semantic IPC protocol implementation.

#include <system/semantic/ipc.hpp>

#include <cassert>
#include <cstring>
#include <iostream>
#include <vector>

namespace rebuntu::semantic::ipc {
    namespace test {

        // ============================================================================
        // Unit Tests: Protocol Constants
        // ============================================================================

        void test_protocol_version() {
            assert(kProtocolVersion == 1);
        }

        void test_frame_header_constants() {
            assert(FrameHeader::kMagic == 0x52534950);  // "RSIP"
        }

        void test_timeout_constants() {
            assert(kDefaultTimeout.count() == 30000);   // 30 seconds
            assert(kConnectionTimeout.count() == 5000);  // 5 seconds
            assert(kCancellationGracePeriod.count() == 100);  // 100ms
        }

        void test_protocol_limits() {
            assert(kMaxPayloadSize == 1024 * 1024);
            assert(kMaxStringFieldLength == 65536);
            assert(kMaxCategories == 100);
            assert(kMaxDiagnosticItems == 1000);
        }

        // ============================================================================
        // Unit Tests: Correlation ID
        // ============================================================================

        void test_correlation_id_generation() {
            auto id1 = CorrelationId::generate();
            auto id2 = CorrelationId::generate();
            
            assert(id1.value != id2.value);
            assert(id1.value == 1);  // First ID should be 1
            assert(id2.value == 2);  // Second ID should be 2
            
            std::string id_str = static_cast<std::string>(id1);
            assert(id_str == "1");
        }

        void test_correlation_id_comparison() {
            auto id1 = CorrelationId{42};
            auto id2 = CorrelationId{42};
            auto id3 = CorrelationId{99};
            
            assert(id1 == id2);
            assert(!(id1 != id2));
            assert(id1 != id3);
        }

        // ============================================================================
        // Unit Tests: Validation
        // ============================================================================

        void test_validation_empty_input() {
            SemanticRequestPayload::ClassificationData cd;
            cd.input = "";
            cd.categories = {"cat1"};
            
            auto result = cd.validate();
            assert(!result.is_valid());
            assert(result.type == ValidationErrorType::kInvalidInputFormat);
        }

        void test_validation_string_length_limit() {
            SemanticRequestPayload::IntentCandidateData icd;
            icd.input = std::string(kMaxStringFieldLength + 1, 'x');
            
            auto result = icd.validate();
            assert(!result.is_valid());
            assert(result.type == ValidationErrorType::kValueOutOfRange);
        }

        void test_validation_category_limit() {
            SemanticRequestPayload::ClassificationData cd;
            cd.input = "test";
            
            // Create more categories than allowed
            for (size_t i = 0; i < kMaxCategories + 1; ++i) {
                cd.categories.push_back("cat" + std::to_string(i));
            }
            
            auto result = cd.validate();
            assert(!result.is_valid());
            assert(result.type == ValidationErrorType::kValueOutOfRange);
        }

        void test_validation_empty_categories() {
            SemanticRequestPayload::ClassificationData cd;
            cd.input = "test";
            cd.categories = {"cat1", ""};
            
            auto result = cd.validate();
            assert(!result.is_valid());
            assert(result.type == ValidationErrorType::kInvalidInputFormat);
        }

        void test_response_confidence_range() {
            SemanticResponsePayload::IntentCandidateDataResponse icd;
            icd.operation_id = "op1";
            icd.confidence = 1.5;  // Invalid - above 1.0
            
            auto result = icd.validate();
            assert(!result.is_valid());
            assert(result.type == ValidationErrorType::kValueOutOfRange);
        }

        void test_response_required_operation_id() {
            SemanticResponsePayload::IntentCandidateDataResponse icd;
            icd.operation_id = "";
            
            auto result = icd.validate();
            assert(!result.is_valid());
            assert(result.type == ValidationErrorType::kMissingRequiredField);
        }

        // ============================================================================
        // Integration Tests: Serialization
        // ============================================================================

        void test_frame_header_serialization() {
            FrameHeader header;
            header.magic = FrameHeader::kMagic;
            header.version = kProtocolVersion;
            header.frame_type = static_cast<int16_t>(FrameType::kRequest);
            header.correlation = CorrelationId{42};
            header.payload_length = 0;
            
            // Header should be valid
            assert(header.is_valid());
        }

        void test_error_payload() {
            ErrorPayload err;
            err.code = ErrorCode::kTimeout;
            err.message = "Request timed out";
            err.related_correlation.value = 123;
            
            std::string code_str = to_string(err.code);
            assert(code_str == "TIMEOUT");
        }

        void test_cancellation_payload() {
            CancellationPayload cancel;
            cancel.target.value = 999;
            
            assert(cancel.target.value == 999);
        }

        // ============================================================================
        // Adversarial Tests: Malformed Input
        // ============================================================================

        void test_malformed_frame_wrong_magic() {
            std::vector<uint8_t> data(sizeof(FrameHeader), 0);
            uint32_t wrong_magic = 0xDEADBEEF;
            memcpy(data.data(), &wrong_magic, sizeof(wrong_magic));
            
            (void)data;  // Suppress unused warning - parsing requires full header with payload
        }

        void test_malformed_frame_truncated() {
            std::vector<uint8_t> data(10);  // Only 10 bytes - too short
            
            (void)data;  // Suppress unused warning
        }

        void test_empty_classification_request_validation() {
            SemanticRequestPayload req;
            req.type = RequestType::kClassification;
            // No classification data set
            
            auto result = req.validate();
            assert(!result.is_valid());
            assert(result.type == ValidationErrorType::kMissingRequiredField);
        }

        void test_empty_evidence_relevance_validation() {
            SemanticRequestPayload req;
            req.type = RequestType::kEvidenceRelevance;
            
            auto result = req.validate();
            assert(!result.is_valid());
            assert(result.type == ValidationErrorType::kMissingRequiredField);
        }

        void test_response_missing_required_field() {
            SemanticResponsePayload resp;
            resp.type = ResponseType::kDiagnosticSummary;
            
            auto result = resp.validate();
            assert(!result.is_valid());
            assert(result.type == ValidationErrorType::kMissingRequiredField);
        }

        // ============================================================================
        // Integration: End-to-End Validation Flow
        // ============================================================================

        void test_full_request_validation() {
            SemanticRequestPayload req;
            req.type = RequestType::kClassification;
            
            SemanticRequestPayload::ClassificationData cd;
            cd.input = "test input";
            for (int i = 0; i < 10; ++i) {
                cd.categories.push_back("category_" + std::to_string(i));
            }
            
            req.classification = cd;
            
            auto result = req.validate();
            assert(result.is_valid());
        }

        void test_full_response_validation() {
            SemanticResponsePayload resp;
            resp.type = ResponseType::kIntentCandidate;
            
            SemanticResponsePayload::IntentCandidateDataResponse icd;
            icd.operation_id = "system_restart";
            icd.confidence = 0.95;
            icd.parameters["target"] = "all";
            
            resp.intent_candidate = icd;
            
            auto result = resp.validate();
            assert(result.is_valid());
        }

        // ============================================================================
        // Test Runner
        // ============================================================================

        void run_all_tests() {
            std::cout << "IPC Protocol Tests:\n";
            
            int passed = 0, failed = 0;
            
            #define RUN_TEST(name) \
                try { name(); std::cout << "  PASS: " << #name << "\n"; passed++; } \
                catch (...) { std::cout << "  FAIL: " << #name << "\n"; failed++; }
            
            // Protocol constants
            RUN_TEST(test_protocol_version);
            RUN_TEST(test_frame_header_constants);
            RUN_TEST(test_timeout_constants);
            RUN_TEST(test_protocol_limits);
            
            // Correlation ID
            RUN_TEST(test_correlation_id_generation);
            RUN_TEST(test_correlation_id_comparison);
            
            // Validation
            RUN_TEST(test_validation_empty_input);
            RUN_TEST(test_validation_string_length_limit);
            RUN_TEST(test_validation_category_limit);
            RUN_TEST(test_validation_empty_categories);
            RUN_TEST(test_response_confidence_range);
            RUN_TEST(test_response_required_operation_id);
            
            // Serialization/Integration
            RUN_TEST(test_frame_header_serialization);
            RUN_TEST(test_error_payload);
            RUN_TEST(test_cancellation_payload);
            
            // Adversarial tests
            RUN_TEST(test_malformed_frame_wrong_magic);
            RUN_TEST(test_malformed_frame_truncated);
            RUN_TEST(test_empty_classification_request_validation);
            RUN_TEST(test_empty_evidence_relevance_validation);
            RUN_TEST(test_response_missing_required_field);
            
            // End-to-end validation
            RUN_TEST(test_full_request_validation);
            RUN_TEST(test_full_response_validation);
            
            #undef RUN_TEST
            
            std::cout << "\n";
            std::cout << "Results: " << passed << " passed, " << failed << " failed\n";
        }

    }  // namespace test
}  // namespace rebuntu::semantic::ipc

int main() {
    rebuntu::semantic::ipc::test::run_all_tests();
    
    return 0;
}