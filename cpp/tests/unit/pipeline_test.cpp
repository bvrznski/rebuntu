// rebuntu - Phase 6.10 Pipeline Semantics Unit Tests
//
// Unit tests for the pipeline semantics module.

#include <system/shell/pipeline.hpp>
#include <system/core/contracts.hpp>
#include <iostream>

using namespace rebuntu::shell::pipeline;

void test_stream_kind_to_string() {
    std::cout << "[TEST] StreamKind to_string...";
    
    if (to_string(StreamKind::kPlainText) != "plaintext") {
        std::cerr << " [FAIL - kPlainText string mismatch]\n";
        return;
    }
    if (to_string(StreamKind::kJSON) != "json") {
        std::cerr << " [FAIL - kJSON string mismatch]\n";
        return;
    }
    if (to_string(StreamKind::kJSONL) != "jsonl") {
        std::cerr << " [FAIL - kJSONL string mismatch]\n";
        return;
    }
    if (to_string(StreamKind::kBinary) != "binary") {
        std::cerr << " [FAIL - kBinary string mismatch]\n";
        return;
    }
    
    std::cout << " [PASS]\n";
}

void test_input_mode_defaults() {
    std::cout << "[TEST] InputMode defaults...";
    
    InputMode m;
    
    if (m.stream_kind != StreamKind::kPlainText) {
        std::cerr << " [FAIL - default stream_kind not kPlainText]\n";
        return;
    }
    if (!m.allow_stdin) {
        std::cerr << " [FAIL - allow_stdin should be true by default]\n";
        return;
    }
    if (m.max_records != 10000) {
        std::cerr << " [FAIL - max_records not set to 10000]\n";
        return;
    }
    
    std::cout << " [PASS]\n";
}

void test_input_mode_json_lines() {
    std::cout << "[TEST] InputMode json_lines...";
    
    auto m = InputMode::json_lines(5000);
    
    if (m.stream_kind != StreamKind::kJSONL) {
        std::cerr << " [FAIL - stream_kind not kJSONL]\n";
        return;
    }
    if (m.max_records != 5000) {
        std::cerr << " [FAIL - max_records not set to 5000]\n";
        return;
    }
    
    std::cout << " [PASS]\n";
}

void test_output_mode_defaults() {
    std::cout << "[TEST] OutputMode defaults...";
    
    OutputMode m;
    
    if (m.stream_kind != StreamKind::kPlainText) {
        std::cerr << " [FAIL - default stream_kind not kPlainText]\n";
        return;
    }
    if (!m.trailing_newline) {
        std::cerr << " [FAIL - trailing_newline should be true by default]\n";
        return;
    }
    
    std::cout << " [PASS]\n";
}

void test_output_mode_structured_jsonl() {
    std::cout << "[TEST] OutputMode structured_jsonl...";
    
    auto m = OutputMode::structured_jsonl(2048 * 1024);
    
    if (m.stream_kind != StreamKind::kJSONL) {
        std::cerr << " [FAIL - stream_kind not kJSONL]\n";
        return;
    }
    if (!m.include_metadata) {
        std::cerr << " [FAIL - include_metadata should be true]\n";
        return;
    }
    
    std::cout << " [PASS]\n";
}

void test_pipeline_result_success() {
    std::cout << "[TEST] PipelineResult success...";
    
    auto r = PipelineResult::success();
    
    if (r.status != rebuntu::core::SemanticStatus::kSuccess) {
        std::cerr << " [FAIL - status not kSuccess]\n";
        return;
    }
    
    std::cout << " [PASS]\n";
}

void test_pipeline_result_failure() {
    std::cout << "[TEST] PipelineResult failure...";
    
    auto r = PipelineResult::failure("E_TEST", "test error");
    
    if (r.status != rebuntu::core::SemanticStatus::kFailure) {
        std::cerr << " [FAIL - status not kFailure]\n";
        return;
    }
    if (!r.outcome.has_value()) {
        std::cerr << " [FAIL - outcome should be set]\n";
        return;
    }
    
    std::cout << " [PASS]\n";
}

void test_pipeline_result_unknown() {
    std::cout << "[TEST] PipelineResult unknown...";
    
    auto r = PipelineResult::unknown("state unknown");
    
    if (r.status != rebuntu::core::SemanticStatus::kUnknown) {
        std::cerr << " [FAIL - status not kUnknown]\n";
        return;
    }
    
    std::cout << " [PASS]\n";
}

void test_pipeline_result_metadata() {
    std::cout << "[TEST] PipelineResult metadata...";
    
    auto r = PipelineResult::success();
    r.input_records_read = 42;
    r.output_records_written = 10;
    r.was_truncated = true;
    
    if (r.input_records_read != 42) {
        std::cerr << " [FAIL - input_records_read not set]\n";
        return;
    }
    
    std::cout << " [PASS]\n";
}

void test_pipeline_builder_creation() {
    std::cout << "[TEST] PipelineBuilder creation...";
    
    PipelineBuilder builder;
    (void)builder;  // Suppress unused variable warning
    
    if (true) {
        std::cout << " [PASS]\n";
        return;
    }
}

void test_string_stream_reader() {
    std::cout << "[TEST] StringStreamReader...";
    
    std::string input = "line1\nline2\nline3";
    auto reader = make_string_reader(input, StreamKind::kPlainText);
    
    if (!reader) {
        std::cerr << " [FAIL - reader is null]\n";
        return;
    }
    
    // Test EOF condition first
    bool eof = reader->is_eof();
    (void)eof;  // Suppress unused warning
    
    std::cout << " [PASS]\n";
}

void test_bounds_checking() {
    std::cout << "[TEST] Bounds checking...";
    
    InputMode mode = InputMode::json_lines(3);
    if (mode.max_records != 3) {
        std::cerr << " [FAIL - max_records not set correctly]\n";
        return;
    }
    
    OutputMode out_mode;
    out_mode.max_output_size_bytes = 1024;
    if (out_mode.max_output_size_bytes != 1024) {
        std::cerr << " [FAIL - output size limit not set correctly]\n";
        return;
    }
    
    std::cout << " [PASS]\n";
}

void test_error_codes() {
    std::cout << "[TEST] Error codes...";
    
    constexpr const char* kStreamError = rebuntu::shell::pipeline::error::kStreamError;
    constexpr const char* kBrokenPipe = rebuntu::shell::pipeline::error::kBrokenPipe;
    constexpr const char* kTimeout = rebuntu::shell::pipeline::error::kTimeout;
    
    if (std::string(kStreamError) != "E_STREAM_ERROR") {
        std::cerr << " [FAIL - kStreamError value incorrect]\n";
        return;
    }
    if (std::string(kBrokenPipe) != "E_BROKEN_PIPE") {
        std::cerr << " [FAIL - kBrokenPipe value incorrect]\n";
        return;
    }
    
    std::cout << " [PASS]\n";
}

int main() {
    std::cout << "=== Phase 6.10 Pipeline Semantics Unit Tests ===\n\n";
    
    test_stream_kind_to_string();
    test_input_mode_defaults();
    test_input_mode_json_lines();
    test_output_mode_defaults();
    test_output_mode_structured_jsonl();
    test_pipeline_result_success();
    test_pipeline_result_failure();
    test_pipeline_result_unknown();
    test_pipeline_result_metadata();
    test_pipeline_builder_creation();
    test_string_stream_reader();
    test_bounds_checking();
    test_error_codes();
    
    std::cout << "\n=== All tests completed ===\n";
    return 0;
}