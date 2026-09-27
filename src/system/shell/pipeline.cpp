// rebuntu::shell::pipeline — Pipeline Semantics Implementation (Phase 6.10)
//
// This module provides implementation for pipeline semantics:
//   - stdin/stdout stream handling with TTY detection
//   - JSON/JSONL structured output formatting
//   - Backpressure and broken-pipe handling
//   - Stream processing with bounded resources

#include "pipeline.hpp"
#include <unistd.h>
#include <climits>
#include <csignal>
#include <sys/select.h>

namespace rebuntu::shell::pipeline {

namespace {
    // Check if file descriptor is a TTY
    bool is_tty(int fd) {
        return isatty(fd) == 1;
    }

    // SIGPIPE handler state - we need to track if SIGPIPE occurred
    volatile sig_atomic_t sigpipe_received = 0;

    // SIGPIPE signal handler
    void sigpipe_handler(int) {
        sigpipe_received = 1;
    }
}  // namespace

// ============================================================================
// StdinStreamReader — Full stdin reader with TTY detection and timeout
// ============================================================================

class StdinStreamReader : public StreamReader {
public:
    explicit StdinStreamReader(const InputMode& mode)
        : mode_(mode), bytes_read_(0) {
        struct sigaction sa;
        sa.sa_handler = sigpipe_handler;
        sigemptyset(&sa.sa_mask);
        sa.sa_flags = SA_RESTART;
        sigaction(SIGPIPE, &sa, nullptr);
    }

    std::optional<std::string> read_line() override {
        if (sigpipe_received) {
            return std::nullopt;
        }

        fd_set read_fds;
        FD_ZERO(&read_fds);
        FD_SET(STDIN_FILENO, &read_fds);

        struct timeval tv;
        tv.tv_sec = mode_.read_timeout_ms.count() / 1000;
        tv.tv_usec = (mode_.read_timeout_ms.count() % 1000) * 1000;

        int ret = select(STDIN_FILENO + 1, &read_fds, nullptr, nullptr, &tv);

        if (ret < 0) {
            return std::nullopt;
        }

        if (ret == 0) {
            return std::nullopt;
        }

        std::string line;
        char buf[4096];

        ssize_t nread = read(STDIN_FILENO, buf, sizeof(buf) - 1);

        if (nread <= 0) {
            return std::nullopt;
        }

        bytes_read_ += nread;

        if (bytes_read_ > mode_.max_records * 1024) {
            return std::nullopt;
        }

        for (ssize_t i = 0; i < nread; ++i) {
            char c = buf[i];
            if (c == '\n') {
                break;
            }
            if (c != '\r') {
                line += c;
            }
        }

        return line;
    }

    bool is_eof() const override {
        return sigpipe_received || bytes_read_ > mode_.max_records * 1024;
    }

    size_t bytes_read() const override {
        return bytes_read_;
    }

private:
    InputMode mode_;
    size_t bytes_read_;
};

std::unique_ptr<StreamReader> make_stdin_reader(const InputMode& mode) {
    return std::make_unique<StdinStreamReader>(mode);
}

// ============================================================================
// String reader for testing
// ============================================================================

class StringStreamReader : public StreamReader {
public:
    explicit StringStreamReader(const std::string& input)
        : input_(input), pos_(0) {}

    std::optional<std::string> read_line() override {
        if (pos_ >= input_.size()) {
            return std::nullopt;
        }

        size_t end = input_.find('\n', pos_);
        std::string line;

        if (end == std::string::npos) {
            line = input_.substr(pos_);
            pos_ = input_.size();
        } else {
            line = input_.substr(pos_, end - pos_);
            pos_ = end + 1;
        }

        if (!line.empty() && line.back() == '\r') {
            line.pop_back();
        }

        return line;
    }

    bool is_eof() const override {
        return pos_ >= input_.size();
    }

    size_t bytes_read() const override {
        return pos_;
    }

private:
    std::string input_;
    size_t pos_;
};

std::unique_ptr<StreamReader> make_string_reader(
    const std::string& input,
    StreamKind kind) {
    (void)kind;
    return std::make_unique<StringStreamReader>(input);
}

// ============================================================================
// StdoutStreamWriter — stdout writer with TTY detection and bounds checking
// ============================================================================

class StdoutStreamWriter : public StreamWriter {
public:
    explicit StdoutStreamWriter(const OutputMode& mode)
        : mode_(mode), bytes_written_(0), is_tty_(is_tty(STDOUT_FILENO)) {}

    PipelineResult write_record(const std::string& record) override {
        if (sigpipe_received) {
            return PipelineResult::failure(error::kBrokenPipe, "broken pipe");
        }

        size_t record_size = record.size() + 1;
        if (mode_.max_output_size_bytes > 0 &&
            bytes_written_ + record_size > mode_.max_output_size_bytes) {
            return PipelineResult::failure(
                error::kExceededBounds,
                "output size exceeded limit"
            );
        }

        std::cout << record;
        if (mode_.trailing_newline) {
            std::cout << "\n";
        }
        std::cout.flush();

        bytes_written_ += record_size;

        if (bytes_written_ >= mode_.max_output_size_bytes && 
            mode_.max_output_size_bytes > 0) {
            return PipelineResult::failure(
                error::kOutputTruncated,
                "output size exceeded limit"
            );
        }

        return PipelineResult::success();
    }

    PipelineResult flush() override {
        std::cout.flush();

        if (sigpipe_received) {
            return PipelineResult::failure(error::kBrokenPipe, "broken pipe");
        }

        return PipelineResult::success();
    }

    size_t bytes_written() const override {
        return bytes_written_;
    }

private:
    OutputMode mode_;
    size_t bytes_written_;
    bool is_tty_;
};

std::unique_ptr<StreamWriter> make_stdout_writer(const OutputMode& mode) {
    return std::make_unique<StdoutStreamWriter>(mode);
}

// ============================================================================
// StringWriter for testing
// ============================================================================

class StringWriter : public StreamWriter {
public:
    explicit StringWriter() : output_("") {}

    PipelineResult write_record(const std::string& record) override {
        if (!output_.empty()) {
            output_ += "\n";
        }
        output_ += record;
        return PipelineResult::success();
    }

    PipelineResult flush() override {
        return PipelineResult::success();
    }

    size_t bytes_written() const override {
        return output_.size();
    }

    std::string get_output() const { return output_; }

private:
    std::string output_;
};

std::unique_ptr<StreamWriter> make_string_writer() {
    return std::make_unique<StringWriter>();
}

// ============================================================================
// PipelineBuilder implementation
// ============================================================================

PipelineBuilder::PipelineBuilder()
    : input_mode_(InputMode::default_text()),
      output_mode_(OutputMode::human()),
      process_fn_(nullptr) {}

PipelineBuilder& PipelineBuilder::with_input_mode(InputMode mode) {
    input_mode_ = mode;
    return *this;
}

PipelineBuilder& PipelineBuilder::from_stdin() {
    input_path_.reset();
    return *this;
}

PipelineBuilder& PipelineBuilder::from_file(const std::string& path) {
    input_path_ = path;
    return *this;
}

PipelineBuilder& PipelineBuilder::with_output_mode(OutputMode mode) {
    output_mode_ = mode;
    return *this;
}

PipelineBuilder& PipelineBuilder::to_stdout() {
    output_path_.reset();
    return *this;
}

PipelineBuilder& PipelineBuilder::to_file(const std::string& path) {
    output_path_ = path;
    return *this;
}

PipelineBuilder& PipelineBuilder::process(
    std::function<PipelineResult(const std::string&)> fn) {
    process_fn_ = std::move(fn);
    return *this;
}

PipelineResult PipelineBuilder::execute() {
    if (!process_fn_) {
        return PipelineResult::failure(
            error::kInvalidInput,
            "no process function provided"
        );
    }

    auto start_time = std::chrono::steady_clock::now();

    std::unique_ptr<StreamReader> reader;
    if (input_path_.has_value()) {
        return PipelineResult::failure(
            error::kInvalidInput,
            "file input not yet implemented"
        );
    } else {
        reader = make_stdin_reader(input_mode_);
    }

    std::unique_ptr<StreamWriter> writer;
    if (output_path_.has_value()) {
        return PipelineResult::failure(
            error::kInvalidInput,
            "file output not yet implemented"
        );
    } else {
        writer = make_stdout_writer(output_mode_);
    }

    PipelineResult result;
    size_t record_count = 0;

    while (!reader->is_eof()) {
        auto line_opt = reader->read_line();

        if (line_opt && !line_opt->empty()) {
            const std::string& line = *line_opt;

            PipelineResult rec_result = process_fn_(line);

            if (rec_result.status != core::SemanticStatus::kSuccess) {
                result = rec_result;
                return result;
            }

            for (const auto& ev : rec_result.evidence) {
                PipelineResult write_result = writer->write_record(ev.value);
                if (write_result.status != core::SemanticStatus::kSuccess) {
                    result.was_truncated = true;
                    break;
                }
                record_count++;
            }

            if (record_count >= input_mode_.max_records && 
                input_mode_.max_records > 0) {
                result.was_truncated = true;
                break;
            }
        } else {
            break;
        }
    }

    PipelineResult flush_result = writer->flush();
    if (flush_result.status != core::SemanticStatus::kSuccess) {
        result.status = flush_result.status;
    }

    auto end_time = std::chrono::steady_clock::now();
    result.elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(
        end_time - start_time
    );

    if (result.status == core::SemanticStatus::kUnknown) {
        result.status = core::SemanticStatus::kSuccess;
    }

    return result;
}

// ============================================================================
// Pipeline diagnostics implementation
// ============================================================================

PipelineDiagnostics get_pipeline_diagnostics() {
    return PipelineDiagnostics{};
}

}  // namespace rebuntu::shell::pipeline