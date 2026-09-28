// rebuntu::shell::output::capture unit tests (Phase 6.19)
//
// Tests for bounded stdout/stderr capture semantics:
//   * OutputBounds configuration
//   * Truncation metadata preservation
//   * UTF-8 safe decoding

#include <system/shell/output/capture.hpp>
#include <cassert>
#include <iostream>

namespace rebuntu::shell {

void test_default_bounds() {
    output::OutputBounds bounds = output::OutputBounds::make_default();
    
    assert(bounds.max_stdout_bytes == 16 * 1024);
    assert(bounds.max_stderr_bytes == 8 * 1024);
    assert(bounds.max_total_bytes == 32 * 1024);
    assert(bounds.max_lines == 1000);
}

void test_custom_bounds() {
    output::OutputBounds bounds;
    bounds.max_stdout_bytes = 8 * 1024;
    bounds.max_stderr_bytes = 4 * 1024;
    bounds.max_total_bytes = 16 * 1024;
    bounds.max_lines = 500;
    
    assert(bounds.max_stdout_bytes == 8 * 1024);
    assert(bounds.max_stderr_bytes == 4 * 1024);
    assert(bounds.max_total_bytes == 16 * 1024);
    assert(bounds.max_lines == 500);
}

void test_truncation_reason_string() {
    using namespace output;
    
    assert(to_string(TruncationReason::NONE) == "none");
    assert(to_string(TruncationReason::STDOUT_LIMIT) == "stdout_limit");
    assert(to_string(TruncationReason::STDERR_LIMIT) == "stderr_limit");
    assert(to_string(TruncationReason::TOTAL_LIMIT) == "total_limit");
    assert(to_string(TruncationReason::LINE_COUNT_LIMIT) == "line_count_limit");
}

void test_capture_result_success() {
    output::CaptureResult result = output::CaptureResult::success();
    
    assert(result.exit_status == 0);
    assert(!result.was_truncated);
    assert(result.truncation_reason == TruncationReason::NONE);
}

void test_capture_result_with_exit_code() {
    output::CaptureResult result = output::CaptureResult::with_exit_code(127);
    
    assert(result.exit_status == 127);
}

void test_utf8_decoder_ascii() {
    bool is_valid;
    std::string error;
    
    // Simple ASCII text
    std::string decoded = output::Utf8Decoder{}.decode("hello world", &is_valid, &error);
    
    assert(is_valid);
    assert(error.empty());
    assert(decoded == "hello world");
}

void test_utf8_decoder_valid_utf8() {
    bool is_valid;
    std::string error;
    
    // Valid UTF-8: 3-byte sequence for Chinese character
    std::string decoded = output::Utf8Decoder{}.decode("\xE4\xB8\xAD", &is_valid, &error);
    
    assert(is_valid);
    assert(error.empty());
}

void test_utf8_decoder_invalid_leading_byte() {
    bool is_valid;
    std::string error;
    
    // Invalid: byte 0xFF is not a valid UTF-8 leading byte
    std::string decoded = output::Utf8Decoder{}.decode("\xFF", &is_valid, &error);
    
    assert(!is_valid);
    assert(!error.empty());
}

void test_utf8_decoder_incomplete_sequence() {
    bool is_valid;
    std::string error;
    
    // Incomplete: 0xC2 followed by only one byte (needs continuation)
    std::string decoded = output::Utf8Decoder{}.decode("\xC2\x41", &is_valid, &error);
    
    assert(!is_valid);
    assert(!error.empty());
}

void test_output_capture_stdout() {
    output::OutputCapture capture;
    
    // Capture stdout
    capture.capture_stdout("hello\n");
    capture.capture_stdout("world\n");
    
    auto result = capture.finalize(0);
    
    assert(result.stdout_data == "hello\nworld\n");
    assert(!result.was_truncated);
}

void test_output_capture_stderr() {
    output::OutputCapture capture;
    
    // Capture stderr
    capture.capture_stderr("error message\n");
    
    auto result = capture.finalize(1);
    
    assert(result.stderr_data == "error message\n");
    assert(result.exit_status == 1);
}

void test_output_capture_truncation() {
    output::OutputBounds bounds;
    bounds.max_total_bytes = 20;  // Very small limit
    
    output::OutputCapture capture(bounds);
    
    // Try to exceed the limit
    capture.capture_stdout("this is a long line ");
    capture.capture_stdout("that should be truncated");
    
    auto result = capture.finalize(0);
    
    assert(result.was_truncated);
    assert(result.bytes_dropped > 0);
}

void test_output_capture_utf8_validation() {
    output::OutputCapture capture;
    
    // Valid UTF-8
    capture.capture_stdout("\xE4\xB8\xAD\xE6\x96\x87");  // 中文
    
    auto result = capture.finalize(0);
    
    assert(result.is_stdout_valid_utf8);
}

void test_output_capture_reset() {
    output::OutputCapture capture;
    
    capture.capture_stdout("hello");
    capture.reset();
    
    auto result = capture.finalize(0);
    
    assert(result.stdout_data.empty());
    assert(!result.was_truncated);
}

}  // namespace rebuntu::shell

int main() {
    using namespace rebuntu::shell;
    
    std::cout << "Testing shell output capture module (Phase 6.19)\n";
    
    test_default_bounds();
    std::cout << "  default_bounds: PASS\n";
    
    test_custom_bounds();
    std::cout << "  custom_bounds: PASS\n";
    
    test_truncation_reason_string();
    std::cout << "  truncation_reason_string: PASS\n";
    
    test_capture_result_success();
    std::cout << "  capture_result_success: PASS\n";
    
    test_capture_result_with_exit_code();
    std::cout << "  capture_result_with_exit_code: PASS\n";
    
    test_utf8_decoder_ascii();
    std::cout << "  utf8_decoder_ascii: PASS\n";
    
    test_utf8_decoder_valid_utf8();
    std::cout << "  utf8_decoder_valid_utf8: PASS\n";
    
    test_utf8_decoder_invalid_leading_byte();
    std::cout << "  utf8_decoder_invalid_leading_byte: PASS\n";
    
    test_utf8_decoder_incomplete_sequence();
    std::cout << "  utf8_decoder_incomplete_sequence: PASS\n";
    
    test_output_capture_stdout();
    std::cout << "  output_capture_stdout: PASS\n";
    
    test_output_capture_stderr();
    std::cout << "  output_capture_stderr: PASS\n";
    
    test_output_capture_truncation();
    std::cout << "  output_capture_truncation: PASS\n";
    
    test_output_capture_utf8_validation();
    std::cout << "  output_capture_utf8_validation: PASS\n";
    
    test_output_capture_reset();
    std::cout << "  output_capture_reset: PASS\n";
    
    std::cout << "\nAll tests passed!\n";
    return 0;
}