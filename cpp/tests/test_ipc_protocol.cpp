// rebuntu::semantic::ipc - Protocol tests (Phase 3.4)
//
// Tests for:
//   - Protocol constants and magic number validation
//   - Frame header parsing/serialization
//   - Request/response/error serialization/deserialization
//   - Validation helpers
//   - Adversarial cases

#include <system/semantic/ipc.hpp>
#include <cassert>
#include <iostream>
#include <cstring>

using namespace rebuntu::semantic;

void test_protocol_constants() {
    assert(kProtocolMagic == 0x52534950);
    assert(kProtocolVersion == 1);
    assert(kMaxPayloadSize == 1024 * 1024);
    assert(kMaxStringFieldLen == 64 * 1024);
    std::cout << "  test_protocol_constants... PASS\n";
}

void test_frame_types_to_string() {
    using namespace rebuntu::semantic;
    
    assert(to_string(FrameType::kRequest) == "request");
    assert(to_string(FrameType::kResponse) == "response");
    assert(to_string(FrameType::kError) == "error");
    assert(to_string(FrameType::kCancellation) == "cancellation");
    std::cout << "  test_frame_types_to_string... PASS\n";
}

void test_request_types_to_string() {
    using namespace rebuntu::semantic;
    
    assert(to_string(RequestType::kClassify) == "classify");
    assert(to_string(RequestType::kGenerateIntentCandidate) == "generate_intent_candidate");
    assert(to_string(RequestType::kAssessEvidenceRelevance) == "assess_evidence_relevance");
    assert(to_string(RequestType::kSummarizeDiagnostics) == "summarize_diagnostics");
    std::cout << "  test_request_types_to_string... PASS\n";
}

void test_error_codes_to_string() {
    using namespace rebuntu::semantic;
    
    assert(to_string(ErrorCode::kInvalidMagic) == "invalid_magic");
    assert(to_string(ErrorCode::kInvalidVersion) == "invalid_version");
    assert(to_string(ErrorCode::kInvalidFrameType) == "invalid_frame_type");
    assert(to_string(ErrorCode::kMalformedPayload) == "malformed_payload");
    assert(to_string(ErrorCode::kPayloadTooLarge) == "payload_too_large");
    std::cout << "  test_error_codes_to_string... PASS\n";
}

void test_correlation_ids() {
    auto ids1 = CorrelationIds::make_default();
    auto ids2 = CorrelationIds::make_default();
    
    assert(ids1.request_id.substr(0, 4) == "req-");
    assert(ids2.request_id.substr(0, 4) == "req-");
    assert(ids1.request_id != ids2.request_id);  // Should be unique
    std::cout << "  test_correlation_ids... PASS\n";
}

void test_frame_header_size() {
    assert(FrameHeader::kSize == 20);
    std::cout << "  test_frame_header_size... PASS\n";
}

void test_semantic_request_defaults() {
    SemanticRequest req;
    
    assert(req.type == RequestType::kClassify);  // Default
    assert(req.input_text.empty());
    assert(!req.query_context.has_value());
    assert(req.timeout.count() == kDefaultRequestTimeoutMs);
    std::cout << "  test_semantic_request_defaults... PASS\n";
}

void test_semantic_response_constructors() {
    SemanticResponse r1 = SemanticResponse::make_success("test output");
    assert(r1.succeeded == true);
    assert(r1.output.has_value());
    assert(r1.output.value() == "test output");
    
    SemanticResponse r2 = SemanticResponse::make_failure("error message");
    assert(r2.succeeded == false);
    assert(r2.error_message.has_value());
    assert(r2.error_message.value() == "error message");
    std::cout << "  test_semantic_response_constructors... PASS\n";
}

void test_semantic_error_constructor() {
    SemanticError e = SemanticError::make(ErrorCode::kInvalidMagic, "test error");
    assert(e.code == ErrorCode::kInvalidMagic);
    assert(e.message == "test error");
    std::cout << "  test_semantic_error_constructor... PASS\n";
}

void test_validation_empty_input() {
    SemanticRequest req;
    req.type = RequestType::kClassify;
    
    assert(!validation::validate_request(req));
    std::cout << "  test_validation_empty_input... PASS\n";
}

void test_validation_input_too_long() {
    SemanticRequest req;
    req.type = RequestType::kClassify;
    req.input_text.resize(kMaxStringFieldLen + 1, 'x');
    
    assert(!validation::validate_request(req));
    std::cout << "  test_validation_input_too_long... PASS\n";
}

void test_validation_valid_classify() {
    SemanticRequest req;
    req.type = RequestType::kClassify;
    req.input_text = "test input text";
    
    assert(validation::validate_request(req));
    std::cout << "  test_validation_valid_classify... PASS\n";
}

void test_validation_assess_evidence_relevance_no_context() {
    SemanticRequest req;
    req.type = RequestType::kAssessEvidenceRelevance;
    
    // assess_evidence_relevance requires query_context
    assert(!validation::validate_request(req));
    std::cout << "  test_validation_assess_evidence_relevance_no_context... PASS\n";
}

void test_validation_valid_assess_evidence() {
    SemanticRequest req;
    req.type = RequestType::kAssessEvidenceRelevance;
    req.input_text = "test input";
    req.query_context = "test context";
    
    assert(validation::validate_request(req));
    std::cout << "  test_validation_valid_assess_evidence... PASS\n";
}

void test_validation_summarize_no_evidence() {
    SemanticRequest req;
    req.type = RequestType::kSummarizeDiagnostics;
    req.input_text = "test input";
    
    // summarize_diagnostics requires evidence_lines
    assert(!validation::validate_request(req));
    std::cout << "  test_validation_summarize_no_evidence... PASS\n";
}

void test_validation_valid_summarize() {
    SemanticRequest req;
    req.type = RequestType::kSummarizeDiagnostics;
    req.input_text = "test input";
    req.evidence_lines = {"line1", "line2"};
    
    assert(validation::validate_request(req));
    std::cout << "  test_validation_valid_summarize... PASS\n";
}

void test_validation_evidence_too_many() {
    SemanticRequest req;
    req.type = RequestType::kSummarizeDiagnostics;
    req.input_text = "test input";
    
    // Create more than max_count (100) evidence lines
    for (size_t i = 0; i < 101; ++i) {
        req.evidence_lines.push_back("line");
    }
    
    assert(!validation::validate_request(req));
    std::cout << "  test_validation_evidence_too_many... PASS\n";
}

void test_header_parse_valid() {
    uint8_t header[FrameHeader::kSize];
    uint32_t magic = kProtocolMagic;
    uint16_t version = kProtocolVersion;
    uint16_t frame_type = static_cast<uint16_t>(FrameType::kRequest);
    uint64_t corr_id = 12345;
    uint32_t payload_len = 0;
    
    // Write header in little-endian
    std::memcpy(header + 0, &magic, 4);
    std::memcpy(header + 4, &version, 2);
    std::memcpy(header + 6, &frame_type, 2);
    std::memcpy(header + 8, &corr_id, 8);
    std::memcpy(header + 16, &payload_len, 4);
    
    auto header_opt = parse_header(header, FrameHeader::kSize);
    assert(header_opt.has_value());
    assert(header_opt->magic == kProtocolMagic);
    assert(header_opt->version == kProtocolVersion);
    assert(header_opt->frame_type == frame_type);
    assert(header_opt->correlation_id == corr_id);
    std::cout << "  test_header_parse_valid... PASS\n";
}

void test_header_parse_invalid_magic() {
    uint8_t header[FrameHeader::kSize];
    uint32_t invalid_magic = 0xFFFFFFFF;
    
    std::memcpy(header + 0, &invalid_magic, 4);
    std::memset(header + 4, 0, FrameHeader::kSize - 4);
    
    auto header_opt = parse_header(header, FrameHeader::kSize);
    assert(!header_opt.has_value());
    std::cout << "  test_header_parse_invalid_magic... PASS\n";
}

void test_header_parse_invalid_version() {
    uint8_t header[FrameHeader::kSize];
    uint32_t magic = kProtocolMagic;
    uint16_t invalid_version = 999;
    
    std::memcpy(header + 0, &magic, 4);
    std::memcpy(header + 4, &invalid_version, 2);
    std::memset(header + 6, 0, FrameHeader::kSize - 6);
    
    auto header_opt = parse_header(header, FrameHeader::kSize);
    assert(!header_opt.has_value());
    std::cout << "  test_header_parse_invalid_version... PASS\n";
}

void test_frame_payload_too_large() {
    uint8_t header[FrameHeader::kSize];
    uint32_t magic = kProtocolMagic;
    uint16_t version = kProtocolVersion;
    uint16_t frame_type = static_cast<uint16_t>(FrameType::kRequest);
    uint64_t corr_id = 1;
    
    std::memcpy(header + 0, &magic, 4);
    std::memcpy(header + 4, &version, 2);
    std::memcpy(header + 6, &frame_type, 2);
    std::memcpy(header + 8, &corr_id, 8);
    
    // Set payload length to more than max
    uint32_t too_large_len = kMaxPayloadSize + 1;
    std::memcpy(header + 16, &too_large_len, 4);
    
    auto frame_opt = deserialize_frame(header, FrameHeader::kSize);
    assert(!frame_opt.has_value());
    std::cout << "  test_frame_payload_too_large... PASS\n";
}

void test_request_serialization() {
    SemanticRequest req;
    req.type = RequestType::kClassify;
    req.input_text = "test input for serialization";
    
    auto payload = serialize_request(req);
    assert(!payload.empty());
    
    // Deserialize and verify
    auto parsed_opt = deserialize_request(payload.data(), payload.size());
    assert(parsed_opt.has_value());
    assert(parsed_opt->type == RequestType::kClassify);
    assert(parsed_opt->input_text == req.input_text);
    std::cout << "  test_request_serialization... PASS\n";
}

void test_response_serialization_success() {
    SemanticResponse resp = SemanticResponse::make_success("test response");
    
    auto payload = serialize_response(resp);
    assert(!payload.empty());
    
    auto parsed_opt = deserialize_response(payload.data(), payload.size());
    assert(parsed_opt.has_value());
    assert(parsed_opt->succeeded == true);
    assert(parsed_opt->output.has_value());
    std::cout << "  test_response_serialization_success... PASS\n";
}

void test_response_serialization_failure() {
    SemanticResponse resp = SemanticResponse::make_failure("test error");
    
    auto payload = serialize_response(resp);
    assert(!payload.empty());
    
    auto parsed_opt = deserialize_response(payload.data(), payload.size());
    assert(parsed_opt.has_value());
    assert(parsed_opt->succeeded == false);
    assert(parsed_opt->error_message.has_value());
    std::cout << "  test_response_serialization_failure... PASS\n";
}

void test_error_serialization() {
    SemanticError err = SemanticError::make(ErrorCode::kInvalidMagic, "test error message");
    
    auto payload = serialize_error(err);
    assert(!payload.empty());
    
    auto parsed_opt = deserialize_error(payload.data(), payload.size());
    assert(parsed_opt.has_value());
    assert(parsed_opt->code == ErrorCode::kInvalidMagic);
    assert(parsed_opt->message == "test error message");
    std::cout << "  test_error_serialization... PASS\n";
}

int main(int argc, char** argv) {
    (void)argc;
    (void)argv;
    
    std::cout << "Running Phase 3.4 IPC Protocol tests...\n";
    
    test_protocol_constants();
    test_frame_types_to_string();
    test_request_types_to_string();
    test_error_codes_to_string();
    test_correlation_ids();
    test_frame_header_size();
    test_semantic_request_defaults();
    test_semantic_response_constructors();
    test_semantic_error_constructor();
    test_validation_empty_input();
    test_validation_input_too_long();
    test_validation_valid_classify();
    test_validation_assess_evidence_relevance_no_context();
    test_validation_valid_assess_evidence();
    test_validation_summarize_no_evidence();
    test_validation_valid_summarize();
    test_validation_evidence_too_many();
    test_header_parse_valid();
    test_header_parse_invalid_magic();
    test_header_parse_invalid_version();
    test_frame_payload_too_large();
    test_request_serialization();
    test_response_serialization_success();
    test_response_serialization_failure();
    
    std::cout << "All Phase 3.4 IPC protocol tests PASSED!\n";
    return 0;
}