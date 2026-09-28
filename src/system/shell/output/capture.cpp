// rebuntu::shell::output::capture — Bounded stdout/stderr Capture Semantics Implementation (Phase 6.19)

#include <system/core/contracts.hpp>
#include <system/shell/output/capture.hpp>

namespace rebuntu {

using Evidence = core::Evidence;

std::vector<Evidence> capture_to_evidence(const shell::output::CaptureResult& result) {
    std::vector<Evidence> evidence;
    
    // Capture stdout if present
    if (!result.stdout_data.empty()) {
        Evidence ev;
        ev.source = "stdout";
        ev.value = result.stdout_data.substr(0, 1024);  // Bounded to 1KB
        // captured_at set by caller
        evidence.push_back(ev);
    }
    
    // Capture stderr if present
    if (!result.stderr_data.empty()) {
        Evidence ev;
        ev.source = "stderr";
        ev.value = result.stderr_data.substr(0, 512);  // Bounded to 512B
        // captured_at set by caller
        evidence.push_back(ev);
    }
    
    return evidence;
}

}  // namespace rebuntu

namespace rebuntu::shell {

namespace output {

bool Utf8Decoder::is_continuation_byte(uint8_t b) const {
    return (b & 0xC0) == 0x80;
}

int Utf8Decoder::expected_sequence_length(uint8_t first_byte) const {
    if ((first_byte & 0x80) == 0x00) return 1;   // ASCII
    if ((first_byte & 0xE0) == 0xC0) return 2;   // 2-byte sequence
    if ((first_byte & 0xF0) == 0xE0) return 3;   // 3-byte sequence
    if ((first_byte & 0xF8) == 0xF0) return 4;   // 4-byte sequence
    return -1;  // Invalid leading byte
}

std::string Utf8Decoder::decode(const std::string& bytes, bool* is_valid, std::string* error) {
    std::string result;
    *is_valid = true;
    error->clear();
    
    size_t i = 0;
    
    while (i < bytes.size()) {
        uint8_t first_byte = static_cast<uint8_t>(bytes[i]);
        
        // Check for ASCII
        if ((first_byte & 0x80) == 0x00) {
            result += static_cast<char>(first_byte);
            i++;
            continue;
        }
        
        int expected_len = expected_sequence_length(first_byte);
        if (expected_len < 1 || expected_len > 4) {
            *is_valid = false;
            *error = "Invalid UTF-8 starting byte at position " + std::to_string(i);
            return result;
        }
        
        // Check we have enough bytes
        if (i + expected_len > bytes.size()) {
            *is_valid = false;
            *error = "Incomplete UTF-8 sequence at end of input";
            return result;
        }
        
        // Verify continuation bytes
        bool valid = true;
        for (int j = 1; j < expected_len; j++) {
            if (!is_continuation_byte(static_cast<uint8_t>(bytes[i + j]))) {
                valid = false;
                break;
            }
        }
        
        if (!valid) {
            *is_valid = false;
            *error = "Invalid UTF-8 continuation at position " + std::to_string(i);
            return result;
        }
        
        // Copy the valid sequence
        result.append(bytes.data() + i, expected_len);
        i += expected_len;
    }
    
    return result;
}

std::string Utf8Decoder::decode_bounded(const std::string& bytes, size_t max_bytes,
                                        bool* is_valid, std::string* error,
                                        TruncationReason* trunc_reason) {
    *trunc_reason = TruncationReason::NONE;
    
    if (bytes.size() <= max_bytes) {
        return decode(bytes, is_valid, error);
    }
    
    // Need to truncate - find a safe boundary
    std::string truncated(bytes.data(), max_bytes);
    std::string result = decode(truncated, is_valid, error);
    
    if (!*is_valid && error->empty()) {
        // Decoding failed on truncated data, need to trim further
        while (truncated.size() > 0) {
            size_t new_size = truncated.size() - 1;
            truncated.resize(new_size);
            result = decode(truncated, is_valid, error);
            if (*is_valid || new_size == 0) break;
        }
    }
    
    *trunc_reason = (bytes.size() > max_bytes) ? TruncationReason::STDOUT_LIMIT : TruncationReason::NONE;
    return result;
}

OutputCapture::OutputCapture(OutputBounds bounds)
    : bounds_(bounds),
      truncation_reason_{TruncationReason::NONE},
      was_truncated_{false},
      bytes_dropped_{0} {
}

void OutputCapture::capture_stdout(const std::string& data) {
    // Check if adding this would exceed total limit
    size_t new_total = stdout_buffer_.size() + stderr_buffer_.size() + data.size();
    
    if (new_total > bounds_.max_total_bytes) {
        size_t available = bounds_.max_total_bytes - stdout_buffer_.size() - stderr_buffer_.size();
        if (available <= 0) {
            truncation_reason_ = TruncationReason::TOTAL_LIMIT;
            return;  // No more space
        }
        
        std::string truncated(data.data(), available);
        stdout_buffer_ += truncated;
        bytes_dropped_ += data.size() - available;
        was_truncated_ = true;
    } else {
        stdout_buffer_ += data;
    }
    
    // Count lines for line-based bounds
    size_t new_lines = count_lines(stdout_buffer_) - stdout_lines_;
    if (new_lines > 0) {
        stdout_lines_ += new_lines;
        if (stdout_lines_ >= bounds_.max_lines && bytes_dropped_ == 0) {
            truncation_reason_ = TruncationReason::LINE_COUNT_LIMIT;
            was_truncated_ = true;
        }
    }
}

void OutputCapture::capture_stderr(const std::string& data) {
    // Check if adding this would exceed total limit
    size_t new_total = stdout_buffer_.size() + stderr_buffer_.size() + data.size();
    
    if (new_total > bounds_.max_total_bytes) {
        size_t available = bounds_.max_total_bytes - stdout_buffer_.size() - stderr_buffer_.size();
        if (available <= 0) {
            truncation_reason_ = TruncationReason::TOTAL_LIMIT;
            return;  // No more space
        }
        
        std::string truncated(data.data(), available);
        stderr_buffer_ += truncated;
        bytes_dropped_ += data.size() - available;
        was_truncated_ = true;
    } else {
        stderr_buffer_ += data;
    }
    
    // Count lines for line-based bounds
    size_t new_lines = count_lines(stderr_buffer_) - stderr_lines_;
    if (new_lines > 0) {
        stderr_lines_ += new_lines;
        if (stderr_lines_ >= bounds_.max_lines && bytes_dropped_ == 0) {
            truncation_reason_ = TruncationReason::LINE_COUNT_LIMIT;
            was_truncated_ = true;
        }
    }
}

CaptureResult OutputCapture::finalize(int exit_status, std::chrono::milliseconds elapsed) {
    CaptureResult result;
    
    // Validate UTF-8 and capture validation status
    bool stdout_valid;
    std::string stdout_error;
    std::string stdout_decoded = Utf8Decoder{}.decode(stdout_buffer_, &stdout_valid, &stdout_error);
    
    bool stderr_valid;
    std::string stderr_error;
    std::string stderr_decoded = Utf8Decoder{}.decode(stderr_buffer_, &stderr_valid, &stderr_error);
    
    result.stdout_data = std::move(stdout_decoded);
    result.stderr_data = std::move(stderr_decoded);
    result.exit_status = exit_status;
    result.elapsed_ms = elapsed;
    result.was_truncated = was_truncated_;
    result.truncation_reason = truncation_reason_;
    result.bytes_dropped = bytes_dropped_;
    result.stdout_lines_captured = stdout_lines_;
    result.stderr_lines_captured = stderr_lines_;
    result.is_stdout_valid_utf8 = stdout_valid;
    result.is_stderr_valid_utf8 = stderr_valid;
    
    if (!stdout_error.empty()) {
        result.utf8_error = stdout_error;
    } else if (!stderr_error.empty()) {
        result.utf8_error = stderr_error;
    }
    
    return result;
}

void OutputCapture::reset() {
    stdout_buffer_.clear();
    stderr_buffer_.clear();
    stdout_lines_ = 0;
    stderr_lines_ = 0;
    truncation_reason_ = TruncationReason::NONE;
    was_truncated_ = false;
    bytes_dropped_ = 0;
}

bool is_valid_utf8(const std::string& s) {
    size_t i = 0;
    
    while (i < s.size()) {
        uint8_t first_byte = static_cast<uint8_t>(s[i]);
        
        // ASCII
        if ((first_byte & 0x80) == 0x00) {
            i++;
            continue;
        }
        
        int expected_len = -1;
        if ((first_byte & 0xE0) == 0xC0) expected_len = 2;
        else if ((first_byte & 0xF0) == 0xE0) expected_len = 3;
        else if ((first_byte & 0xF8) == 0xF0) expected_len = 4;
        
        if (expected_len < 1 || i + expected_len > s.size()) {
            return false;
        }
        
        for (int j = 1; j < expected_len; j++) {
            uint8_t byte = static_cast<uint8_t>(s[i + j]);
            if ((byte & 0xC0) != 0x80) {
                return false;
            }
        }
        
        i += expected_len;
    }
    
    return true;
}

size_t count_lines(const std::string& s) {
    size_t count = 0;
    for (char c : s) {
        if (c == '\n') count++;
    }
    // Count last line if it doesn't end with newline but has content
    if (!s.empty() && s.back() != '\n') {
        count++;
    }
    return count;
}

}  // namespace output

}  // namespace rebuntu::shell