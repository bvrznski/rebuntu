// rebuntu::semantic::ipc - Frame serialization/deserialization (Phase 3.4)
//
// This implements:
//   - Binary frame framing: Magic + Version + Type + CorrelationID + PayloadLen + Payload
//   - Little-endian encoding for wire format consistency
//   - Bounded payload sizes to prevent DoS attacks
//   - Protocol version validation

#include <system/semantic/ipc.hpp>
#include <cstring>

namespace rebuntu::semantic {

namespace {

// Helper: read a little-endian uint16_t from bytes
uint16_t read_uint16_le(const uint8_t* data) {
    return static_cast<uint16_t>(data[0]) |
           (static_cast<uint16_t>(data[1]) << 8);
}

// Helper: write a little-endian uint16_t to bytes
void write_uint16_le(uint8_t* data, uint16_t value) {
    data[0] = static_cast<uint8_t>(value & 0xFF);
    data[1] = static_cast<uint8_t>((value >> 8) & 0xFF);
}

// Helper: read a little-endian uint32_t from bytes
uint32_t read_uint32_le(const uint8_t* data) {
    return static_cast<uint32_t>(data[0]) |
           (static_cast<uint32_t>(data[1]) << 8) |
           (static_cast<uint32_t>(data[2]) << 16) |
           (static_cast<uint32_t>(data[3]) << 24);
}

// Helper: write a little-endian uint32_t to bytes
void write_uint32_le(uint8_t* data, uint32_t value) {
    data[0] = static_cast<uint8_t>(value & 0xFF);
    data[1] = static_cast<uint8_t>((value >> 8) & 0xFF);
    data[2] = static_cast<uint8_t>((value >> 16) & 0xFF);
    data[3] = static_cast<uint8_t>((value >> 24) & 0xFF);
}

// Helper: read a little-endian uint64_t from bytes
uint64_t read_uint64_le(const uint8_t* data) {
    return static_cast<uint64_t>(data[0]) |
           (static_cast<uint64_t>(data[1]) << 8) |
           (static_cast<uint64_t>(data[2]) << 16) |
           (static_cast<uint64_t>(data[3]) << 24) |
           (static_cast<uint64_t>(data[4]) << 32) |
           (static_cast<uint64_t>(data[5]) << 40) |
           (static_cast<uint64_t>(data[6]) << 48) |
           (static_cast<uint64_t>(data[7]) << 56);
}

// Helper: write a little-endian uint64_t to bytes
void write_uint64_le(uint8_t* data, uint64_t value) {
    data[0] = static_cast<uint8_t>(value & 0xFF);
    data[1] = static_cast<uint8_t>((value >> 8) & 0xFF);
    data[2] = static_cast<uint8_t>((value >> 16) & 0xFF);
    data[3] = static_cast<uint8_t>((value >> 24) & 0xFF);
    data[4] = static_cast<uint8_t>((value >> 32) & 0xFF);
    data[5] = static_cast<uint8_t>((value >> 40) & 0xFF);
    data[6] = static_cast<uint8_t>((value >> 48) & 0xFF);
    data[7] = static_cast<uint8_t>((value >> 56) & 0xFF);
}

}  // anonymous namespace

// ============================================================================
// Frame Header Parsing
// ============================================================================

std::optional<FrameHeader> parse_header(const uint8_t* data, size_t len) {
    if (len < FrameHeader::kSize) {
        return std::nullopt;
    }

    FrameHeader header;
    header.magic = read_uint32_le(data + 0);
    header.version = read_uint16_le(data + 4);
    header.frame_type = read_uint16_le(data + 6);
    header.correlation_id = read_uint64_le(data + 8);
    header.payload_len = read_uint32_le(data + 16);

    // Validate magic
    if (header.magic != kProtocolMagic) {
        return std::nullopt;
    }

    // Validate version
    if (header.version != kProtocolVersion) {
        return std::nullopt;
    }

    // Validate frame type
    FrameType ft = static_cast<FrameType>(header.frame_type);
    switch (ft) {
        case FrameType::kRequest:
        case FrameType::kResponse:
        case FrameType::kError:
        case FrameType::kCancellation:
            break;  // valid
        default:
            return std::nullopt;
    }

    return header;
}

const uint8_t* get_payload_ptr(const uint8_t* data, size_t len) {
    if (len < FrameHeader::kSize) {
        return nullptr;
    }
    return data + FrameHeader::kSize;
}

// ============================================================================
// Request Serialization
// ============================================================================

std::vector<uint8_t> serialize_request(const SemanticRequest& req) {
    std::vector<uint8_t> payload;

    // Reserve space for header components
    payload.reserve(4096);

    // RequestType (2B)
    uint16_t rt = static_cast<uint16_t>(req.type);
    write_uint16_le(&payload[payload.size()], rt);
    payload.resize(payload.size() + 2);

    // TimeoutFlag (1B) + optional TimeoutMs
    bool has_timeout = req.timeout.count() != kDefaultRequestTimeoutMs;
    payload.push_back(has_timeout ? 1 : 0);
    if (has_timeout) {
        uint64_t timeout_ms = static_cast<uint64_t>(req.timeout.count());
        write_uint64_le(&payload[payload.size()], timeout_ms);
        payload.resize(payload.size() + 8);
    }

    // InputTextLen (4B) + InputText
    uint32_t input_len = static_cast<uint32_t>(req.input_text.length());
    write_uint32_le(&payload[payload.size()], input_len);
    payload.resize(payload.size() + 4);
    payload.insert(payload.end(), req.input_text.begin(), req.input_text.end());

    // QueryContext (for assess_evidence_relevance)
    if (!req.query_context.has_value()) {
        uint32_t empty_len = 0;
        write_uint32_le(&payload[payload.size()], empty_len);
        payload.resize(payload.size() + 4);
    } else {
        uint32_t ctx_len = static_cast<uint32_t>(req.query_context->length());
        write_uint32_le(&payload[payload.size()], ctx_len);
        payload.resize(payload.size() + 4);
        payload.insert(payload.end(), req.query_context->begin(), req.query_context->end());
    }

    // EvidenceLinesCount (4B) + lines
    uint32_t evidence_count = static_cast<uint32_t>(req.evidence_lines.size());
    write_uint32_le(&payload[payload.size()], evidence_count);
    payload.resize(payload.size() + 4);
    for (const auto& line : req.evidence_lines) {
        uint32_t line_len = static_cast<uint32_t>(line.length());
        write_uint32_le(&payload[payload.size()], line_len);
        payload.resize(payload.size() + 4);
        payload.insert(payload.end(), line.begin(), line.end());
    }

    return payload;
}

// ============================================================================
// Response Serialization
// ============================================================================

std::vector<uint8_t> serialize_response(const SemanticResponse& resp) {
    std::vector<uint8_t> payload;

    // SuccessFlag (1B)
    payload.push_back(resp.succeeded ? 1 : 0);

    if (resp.succeeded && resp.output.has_value()) {
        // OutputLen (4B) + Output
        uint32_t output_len = static_cast<uint32_t>(resp.output->length());
        write_uint32_le(&payload[payload.size()], output_len);
        payload.resize(payload.size() + 4);
        payload.insert(payload.end(), resp.output->begin(), resp.output->end());

        // ErrorMsgLen (4B, zero for success)
        uint32_t empty_len = 0;
        write_uint32_le(&payload[payload.size()], empty_len);
        payload.resize(payload.size() + 4);
    } else {
        // OutputLen (4B, zero for failure)
        uint32_t empty_len = 0;
        write_uint32_le(&payload[payload.size()], empty_len);
        payload.resize(payload.size() + 4);

        // ErrorMsgLen (4B) + ErrorMsg
        std::string err_msg = resp.error_message.value_or("");
        uint32_t err_len = static_cast<uint32_t>(err_msg.length());
        write_uint32_le(&payload[payload.size()], err_len);
        payload.resize(payload.size() + 4);
        payload.insert(payload.end(), err_msg.begin(), err_msg.end());
    }

    return payload;
}

// ============================================================================
// Error Serialization
// ============================================================================

std::vector<uint8_t> serialize_error(const SemanticError& error) {
    std::vector<uint8_t> payload;

    // ErrorCode (2B)
    uint16_t ec = static_cast<uint16_t>(error.code);
    write_uint16_le(&payload[payload.size()], ec);
    payload.resize(payload.size() + 2);

    // MessageLen (4B) + Message
    uint32_t msg_len = static_cast<uint32_t>(error.message.length());
    write_uint32_le(&payload[payload.size()], msg_len);
    payload.resize(payload.size() + 4);
    payload.insert(payload.end(), error.message.begin(), error.message.end());

    return payload;
}

// ============================================================================
// Frame Serialization
// ============================================================================

std::vector<uint8_t> serialize_frame(const SemanticFrame& frame) {
    // Calculate total size: header (20) + payload
    size_t total_size = FrameHeader::kSize + frame.payload.size();
    std::vector<uint8_t> result;
    result.resize(total_size);

    uint8_t* data = result.data();

    // Write header
    write_uint32_le(data + 0, frame.header.magic);
    write_uint16_le(data + 4, frame.header.version);
    write_uint16_le(data + 6, frame.header.frame_type);
    write_uint64_le(data + 8, frame.header.correlation_id);
    write_uint32_le(data + 16, frame.header.payload_len);

    // Write payload
    if (!frame.payload.empty()) {
        std::memcpy(data + FrameHeader::kSize, frame.payload.data(), frame.payload.size());
    }

    return result;
}

// ============================================================================
// Frame Deserialization
// ============================================================================

std::optional<SemanticFrame> deserialize_frame(const uint8_t* data, size_t len) {
    if (len < FrameHeader::kSize) {
        return std::nullopt;
    }

    auto header_opt = parse_header(data, len);
    if (!header_opt.has_value()) {
        return std::nullopt;
    }

    SemanticFrame frame;
    frame.header = header_opt.value();
    frame.header.payload_len = read_uint32_le(data + 16);

    // Validate payload length
    if (frame.header.payload_len > kMaxPayloadSize) {
        return std::nullopt;
    }

    // Check we have enough data for the payload
    size_t expected_total = FrameHeader::kSize + frame.header.payload_len;
    if (len < expected_total) {
        return std::nullopt;
    }

    // Copy payload
    frame.payload.resize(frame.header.payload_len);
    std::memcpy(frame.payload.data(), data + FrameHeader::kSize, frame.header.payload_len);

    return frame;
}

// ============================================================================
// Utility Functions
// ============================================================================

namespace {

// Helper to extract string from payload at current position
std::optional<std::string> extract_string_from_payload(
    const uint8_t* data, size_t len, size_t& pos) {
    if (pos + 4 > len) return std::nullopt;
    uint32_t str_len = read_uint32_le(data + pos);
    pos += 4;

    if (str_len == 0) {
        return "";
    }

    if (pos + str_len > len) return std::nullopt;
    if (str_len > kMaxStringFieldLen) return std::nullopt;

    std::string result(reinterpret_cast<const char*>(data + pos), str_len);
    pos += str_len;
    return result;
}

}  // anonymous namespace

// ============================================================================
// Request Deserialization
// ============================================================================

std::optional<SemanticRequest> deserialize_request(const uint8_t* payload, size_t len) {
    SemanticRequest req;

    if (len < 1) return std::nullopt;
    size_t pos = 0;

    // RequestType (2B)
    if (pos + 2 > len) return std::nullopt;
    uint16_t rt = read_uint16_le(payload + pos);
    pos += 2;
    req.type = static_cast<RequestType>(rt);

    // TimeoutFlag (1B) + optional TimeoutMs
    if (pos + 1 > len) return std::nullopt;
    bool has_timeout = payload[pos++] != 0;

    if (has_timeout) {
        if (pos + 8 > len) return std::nullopt;
        uint64_t timeout_ms = read_uint64_le(payload + pos);
        pos += 8;
        req.timeout = std::chrono::milliseconds(timeout_ms);
    }

    // InputText
    auto input_opt = extract_string_from_payload(payload, len, pos);
    if (!input_opt.has_value()) return std::nullopt;
    req.input_text = std::move(input_opt.value());

    // QueryContext (for assess_evidence_relevance)
    auto ctx_opt = extract_string_from_payload(payload, len, pos);
    if (!ctx_opt.has_value()) return std::nullopt;
    if (!ctx_opt->empty()) {
        req.query_context = std::move(ctx_opt.value());
    }

    // EvidenceLinesCount (4B)
    if (pos + 4 > len) return std::nullopt;
    uint32_t evidence_count = read_uint32_le(payload + pos);
    pos += 4;

    for (uint32_t i = 0; i < evidence_count; ++i) {
        auto line_opt = extract_string_from_payload(payload, len, pos);
        if (!line_opt.has_value()) return std::nullopt;
        req.evidence_lines.push_back(std::move(line_opt.value()));
    }

    // Correlation IDs - currently not serialized in request payload
    // They're part of the frame header's correlation_id field

    return req;
}

// ============================================================================
// Response Deserialization
// ============================================================================

std::optional<SemanticResponse> deserialize_response(const uint8_t* payload, size_t len) {
    SemanticResponse resp;

    if (len < 1) return std::nullopt;
    size_t pos = 0;

    // SuccessFlag (1B)
    bool success = payload[pos++] != 0;
    resp.succeeded = success;

    if (success) {
        // Output
        auto output_opt = extract_string_from_payload(payload, len, pos);
        if (!output_opt.has_value()) return std::nullopt;
        resp.output = std::move(output_opt.value());

        // Skip ErrorMsgLen (we don't use it for success)
    } else {
        // Skip OutputLen
        if (pos + 4 > len) return std::nullopt;
        pos += 4;

        // ErrorMsg
        auto error_opt = extract_string_from_payload(payload, len, pos);
        if (!error_opt.has_value()) return std::nullopt;
        resp.error_message = std::move(error_opt.value());
    }

    return resp;
}

// ============================================================================
// Error Deserialization
// ============================================================================

std::optional<SemanticError> deserialize_error(const uint8_t* payload, size_t len) {
    SemanticError err;

    if (len < 2) return std::nullopt;
    size_t pos = 0;

    // ErrorCode (2B)
    uint16_t ec = read_uint16_le(payload + pos);
    pos += 2;
    err.code = static_cast<ErrorCode>(ec);

    // Message
    auto msg_opt = extract_string_from_payload(payload, len, pos);
    if (!msg_opt.has_value()) return std::nullopt;
    err.message = std::move(msg_opt.value());

    return err;
}

}  // namespace rebuntu::semantic