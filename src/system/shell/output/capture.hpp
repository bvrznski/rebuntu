// rebuntu::shell::output::capture — Bounded stdout/stderr Capture Semantics (Phase 6.19)
//
// This module defines bounded output capture semantics:
//
//   * CapturedOutput: Typed result with stdout, stderr, truncation metadata
//   * OutputBounds: Configuration for maximum buffer sizes and record counts
//   * UTF-8 safe decoding without interpreting arbitrary text as structured state
//   * Truncation tracking when bounds are exceeded
//
// Key Principles:
//   * OUTPUT != CONTROL — captured text is never authoritative state
//   * BOUNDED — capture has configurable size limits to prevent memory exhaustion
//   * EVIDENCE — captured output becomes evidence, not authority
//   * UTF-8 SAFE — decoding preserves byte sequences without interpretation

#pragma once

#include <string>
#include <vector>
#include <chrono>

#include <system/core/contracts.hpp>

namespace rebuntu::shell {

namespace output {

enum class TruncationReason {
    NONE,
    STDOUT_LIMIT,
    STDERR_LIMIT,
    TOTAL_LIMIT,
    LINE_COUNT_LIMIT
};

inline std::string to_string(TruncationReason r) {
    switch (r) {
        case TruncationReason::NONE:           return "none";
        case TruncationReason::STDOUT_LIMIT:   return "stdout_limit";
        case TruncationReason::STDERR_LIMIT:   return "stderr_limit";
        case TruncationReason::TOTAL_LIMIT:    return "total_limit";
        case TruncationReason::LINE_COUNT_LIMIT:return "line_count_limit";
    }
    return "unknown";
}

struct OutputBounds {
    size_t max_stdout_bytes = 16 * 1024;
    size_t max_stderr_bytes = 8 * 1024;
    size_t max_total_bytes = 32 * 1024;
    size_t max_lines = 1000;
    
    static OutputBounds make_default() {
        return {};
    }
};

struct CaptureResult {
    std::string stdout_data;
    std::string stderr_data;
    int exit_status = 0;
    std::chrono::milliseconds elapsed_ms{0};
    bool was_truncated = false;
    TruncationReason truncation_reason{TruncationReason::NONE};
    size_t bytes_dropped = 0;
    size_t stdout_lines_captured = 0;
    size_t stderr_lines_captured = 0;
    bool is_stdout_valid_utf8 = true;
    bool is_stderr_valid_utf8 = true;
    std::string utf8_error;
    
    static CaptureResult success() {
        CaptureResult r;
        r.exit_status = 0;
        return r;
    }
    
    static CaptureResult with_exit_code(int code) {
        CaptureResult r;
        r.exit_status = code;
        return r;
    }
};

class Utf8Decoder {
public:
    Utf8Decoder() = default;
    
    // Returns decoded string, validity flag, and error message (empty if valid)
    std::string decode(const std::string& bytes, bool* is_valid, std::string* error);
    
    // Same as above but with output bounds - returns the reason for truncation
    std::string decode_bounded(const std::string& bytes, size_t max_bytes,
                               bool* is_valid, std::string* error, TruncationReason* trunc_reason);
    
private:
    bool is_continuation_byte(uint8_t b) const;
    int expected_sequence_length(uint8_t first_byte) const;
};

class OutputCapture {
public:
    explicit OutputCapture(OutputBounds bounds = OutputBounds::make_default());
    
    void capture_stdout(const std::string& data);
    void capture_stderr(const std::string& data);
    
    CaptureResult finalize(int exit_status, 
                          std::chrono::milliseconds elapsed = std::chrono::milliseconds{0});
    
    void reset();
    
    const OutputBounds& bounds() const { return bounds_; }
    void set_bounds(OutputBounds bounds) { bounds_ = std::move(bounds); }
    
private:
    OutputBounds bounds_;
    std::string stdout_buffer_;
    std::string stderr_buffer_;
    size_t stdout_lines_{0};
    size_t stderr_lines_{0};
    TruncationReason truncation_reason_{TruncationReason::NONE};
    bool was_truncated_{false};
    size_t bytes_dropped_{0};
};

bool is_valid_utf8(const std::string& s);
size_t count_lines(const std::string& s);

}  // namespace output

// ============================================================================
// Evidence integration — CaptureResult to Evidence conversion
// ============================================================================

std::vector<rebuntu::core::Evidence> capture_to_evidence(
    const output::CaptureResult& result);

}  // namespace rebuntu::shell