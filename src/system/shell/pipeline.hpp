// rebuntu::shell::pipeline — Pipeline Semantics (Phase 6.10)
//
// This module defines how Rebuntu commands participate in Unix pipelines
// while preserving typed semantics:
//
//   - Input stream kinds: plain text, JSON/JSONL, binary (where supported)
//   - stdin/stdout/stderr discipline for structured output
//   - Streaming vs materialized data handling
//   - Failure propagation and backpressure
//   - Conversion boundaries between formats
//   - UNIX pipeline compatibility guarantees
//
// Design Principles:
//   * Shell is a PRESENTATION SURFACE, not an independent runtime
//   * Pipeline operations must preserve typed semantics
//   * Stream processing must be bounded and cancellable
//   * Backpressure must be respected throughout the pipeline

#pragma once

#include "types.hpp"
#include "../core/contracts.hpp"
#include <string>
#include <vector>
#include <optional>
#include <functional>
#include <memory>
#include <iostream>
#include <sstream>

namespace rebuntu::shell::pipeline {

// ============================================================================
// StreamKind — Classification of input/output stream types
// ============================================================================

enum class StreamKind {
    kPlainText,   // Human-readable text (default for human mode)
    kJSON,        // JSON document (single object or array)
    kJSONL,       // JSON Lines (one JSON object per line)
    kBinary,      // Binary data (where explicitly supported)
};

inline std::string to_string(StreamKind k) {
    switch (k) {
        case StreamKind::kPlainText: return "plaintext";
        case StreamKind::kJSON:      return "json";
        case StreamKind::kJSONL:     return "jsonl";
        case StreamKind::kBinary:    return "binary";
    }
    return "unknown";
}

// ============================================================================
// InputMode — How input is received and processed
// ============================================================================

struct InputMode {
    StreamKind stream_kind{StreamKind::kPlainText};
    
    // Whether to accept piped input (stdin)
    bool allow_stdin{true};
    
    // For JSON/JSONL: max records to read (0 = unlimited, but bounded)
    size_t max_records{10000};  // Reasonable default
    
    // Timeout for reading input
    std::chrono::milliseconds read_timeout_ms{std::chrono::seconds(30)};
    
    static InputMode default_text() {
        return InputMode{};
    }
    
    static InputMode json_lines(size_t max = 10000) {
        InputMode m;
        m.stream_kind = StreamKind::kJSONL;
        m.max_records = max;
        return m;
    }
    
    static InputMode json_document() {
        InputMode m;
        m.stream_kind = StreamKind::kJSON;
        return m;
    }
};

// ============================================================================
// OutputMode — How output is formatted and written
// ============================================================================

struct OutputMode {
    StreamKind stream_kind{StreamKind::kPlainText};
    
    // For structured output: include metadata (timestamps, provenance)
    bool include_metadata{false};
    
    // Maximum output size before truncation (0 = no limit, but bounded internally)
    size_t max_output_size_bytes{1024 * 1024};  // 1MB default
    
    // Whether to add trailing newline
    bool trailing_newline{true};
    
    static OutputMode human() {
        return OutputMode{};
    }
    
    static OutputMode structured_jsonl(size_t max = 1024 * 1024) {
        OutputMode m;
        m.stream_kind = StreamKind::kJSONL;
        m.max_output_size_bytes = max;
        m.include_metadata = true;
        return m;
    }
    
    static OutputMode structured_json() {
        OutputMode m;
        m.stream_kind = StreamKind::kJSON;
        m.include_metadata = true;
        return m;
    }
};

// ============================================================================
// PipelineResult — Result of pipeline execution
// ============================================================================

struct PipelineResult {
    rebuntu::core::SemanticStatus status{rebuntu::core::SemanticStatus::kUnknown};
    
    // Execution outcome
    std::optional<rebuntu::core::Outcome> outcome;
    
    // Evidence gathered during pipeline execution
    std::vector<rebuntu::core::Evidence> evidence;
    
    // Timing information
    std::chrono::milliseconds elapsed_ms{0};
    
    // Pipeline-specific metadata
    size_t input_records_read{0};
    size_t output_records_written{0};
    bool was_truncated{false};  // true if output was truncated
    
    static PipelineResult success() {
        PipelineResult r;
        r.status = rebuntu::core::SemanticStatus::kSuccess;
        return r;
    }
    
    static PipelineResult failure(std::string code, std::string message) {
        PipelineResult r;
        r.status = rebuntu::core::SemanticStatus::kFailure;
        r.outcome = rebuntu::core::Outcome::failure(std::move(code), std::move(message));
        return r;
    }
    
    static PipelineResult unknown(std::string message) {
        PipelineResult r;
        r.status = rebuntu::core::SemanticStatus::kUnknown;
        r.outcome = rebuntu::core::Outcome::unknown(std::move(message));
        return r;
    }
};

// ============================================================================
// StreamReader — Interface for reading from various input sources
// ============================================================================

class StreamReader {
public:
    virtual ~StreamReader() = default;
    
    // Read next line/record (returns empty string on EOF)
    virtual std::optional<std::string> read_line() = 0;
    
    // Check if we've reached the end
    virtual bool is_eof() const = 0;
    
    // Get total bytes read (for bounds checking)
    virtual size_t bytes_read() const = 0;
};

// ============================================================================
// StreamWriter — Interface for writing to various output destinations
// ============================================================================

class StreamWriter {
public:
    virtual ~StreamWriter() = default;
    
    // Write a record (returns success/failure)
    virtual PipelineResult write_record(const std::string& record) = 0;
    
    // Flush any buffered output
    virtual PipelineResult flush() = 0;
    
    // Get total bytes written
    virtual size_t bytes_written() const = 0;
};

// ============================================================================
// StreamProcessor — Interface for streaming input/output processing
// ============================================================================

class StreamProcessor {
public:
    virtual ~StreamProcessor() = default;
    
    // Process a single input record and produce output
    virtual PipelineResult process_one(const std::string& input) = 0;
    
    // Flush any remaining buffered output
    virtual PipelineResult flush() = 0;
    
    // Get the current count of processed records
    virtual size_t records_processed() const = 0;
};

// ============================================================================
// InputAdapters — Factory functions for different input sources
// ============================================================================

// Read from stdin with stream processing support
std::unique_ptr<StreamReader> make_stdin_reader(const InputMode& mode);

// Read from a string (for testing)
std::unique_ptr<StreamReader> make_string_reader(
    const std::string& input,
    StreamKind kind = StreamKind::kPlainText);

// ============================================================================
// OutputAdapters — Factory functions for different output destinations
// ============================================================================

// Write to stdout with proper stream handling
std::unique_ptr<StreamWriter> make_stdout_writer(const OutputMode& mode);

// Write to a string buffer (for testing)
std::unique_ptr<StreamWriter> make_string_writer();

// ============================================================================
// PipelineBuilder — Fluent interface for building pipeline configurations
// ============================================================================

class PipelineBuilder {
public:
    PipelineBuilder();
    
    // Set input source
    PipelineBuilder& with_input_mode(InputMode mode);
    PipelineBuilder& from_stdin();
    PipelineBuilder& from_file(const std::string& path);
    
    // Set output destination
    PipelineBuilder& with_output_mode(OutputMode mode);
    PipelineBuilder& to_stdout();
    PipelineBuilder& to_file(const std::string& path);
    
    // Set processing function
    PipelineBuilder& process(std::function<PipelineResult(const std::string&)> fn);
    
    // Build and execute the pipeline
    PipelineResult execute();
    
private:
    InputMode input_mode_;
    OutputMode output_mode_;
    std::optional<std::string> input_path_;
    std::optional<std::string> output_path_;
    std::function<PipelineResult(const std::string&)> process_fn_;
};

// ============================================================================
// Error codes for pipeline operations
// ============================================================================

namespace error {
    constexpr const char* kStreamError = "E_STREAM_ERROR";
    constexpr const char* kBrokenPipe = "E_BROKEN_PIPE";
    constexpr const char* kTimeout = "E_TIMEOUT";
    constexpr const char* kExceededBounds = "E_EXCEEDED_BOUNDS";
    constexpr const char* kInvalidInput = "E_INVALID_INPUT";
    constexpr const char* kOutputTruncated = "E_OUTPUT_TRUNCATED";
}

// ============================================================================
// Pipeline diagnostics
// ============================================================================

struct PipelineDiagnostics {
    std::chrono::milliseconds total_time_ms{0};
    size_t records_processed{0};
    bool was_cancelled{false};
    std::optional<std::string> cancellation_reason;
};

PipelineDiagnostics get_pipeline_diagnostics();

}  // namespace rebuntu::shell::pipeline