// rebuntu::semantic::ipc — Structured IPC Protocol for Semantic Service (Phase 3.4)
//
// This header establishes Rebuntu's canonical structured local IPC protocol
// between deterministic components and the semantic service.
//
// CRITICAL INVARIENTS:
//   - MODEL OUTPUT != AUTHORITY (output is UNTRUSTED until validated)
//   - EXECUTION_SUCCESS != VERIFIED_SUCCESS (postcondition verification required)
//   - DATA != CONTROL (request data does not confer authority)
//   - PROTOCOL_FRAMING: Versioned binary frames prevent protocol confusion
//
// ARCHITECTURE:
//   - Frame format: Magic + Version + Type + CorrelationID + PayloadLen + Payload
//   - Transport: Unix domain socket (Phase 2.12 IPC module)
//   - Bounded payloads: Prevent DoS attacks from oversized requests

#pragma once

#include <cstdint>
#include <cstring>
#include <optional>
#include <string>
#include <string_view>
#include <chrono>
#include <memory>
#include <vector>

namespace rebuntu::semantic {

// ============================================================================
// Protocol Constants
// ============================================================================

inline constexpr uint32_t kProtocolMagic = 0x52534950;  // "RSIP" - Rebuntu Semantic IPC
inline constexpr uint16_t kProtocolVersion = 1;

inline constexpr size_t kMaxPayloadSize = 1024 * 1024;     // 1 MB max payload
inline constexpr size_t kMaxStringFieldLen = 64 * 1024;    // 64 KB per string field

inline constexpr int64_t kDefaultRequestTimeoutMs = 30000;   // 30s
inline constexpr int64_t kConnectionTimeoutMs = 5000;        // 5s
inline constexpr int64_t kCancellationGracePeriodMs = 100;

// ============================================================================
// Frame Types
// ============================================================================

enum class FrameType : uint16_t {
    kRequest = 1,      // Client to server semantic requests
    kResponse = 2,     // Server response with results
    kError = 3,        // Protocol or server errors
    kCancellation = 4, // Cancel pending request
};

inline std::string_view to_string(FrameType t) {
    switch (t) {
        case FrameType::kRequest:      return "request";
        case FrameType::kResponse:     return "response";
        case FrameType::kError:        return "error";
        case FrameType::kCancellation: return "cancellation";
    }
    return "unknown";
}

// ============================================================================
// Request Types (for kRequest frames)
// ============================================================================

enum class RequestType : uint16_t {
    kClassify = 1,
    kGenerateIntentCandidate = 2,
    kAssessEvidenceRelevance = 3,
    kSummarizeDiagnostics = 4,
};

inline std::string_view to_string(RequestType t) {
    switch (t) {
        case RequestType::kClassify:               return "classify";
        case RequestType::kGenerateIntentCandidate: return "generate_intent_candidate";
        case RequestType::kAssessEvidenceRelevance: return "assess_evidence_relevance";
        case RequestType::kSummarizeDiagnostics:   return "summarize_diagnostics";
    }
    return "unknown";
}

// ============================================================================
// Error Codes (for kError frames)
// ============================================================================

enum class ErrorCode : uint16_t {
    // Protocol errors
    kInvalidMagic = 1,
    kInvalidVersion = 2,
    kInvalidFrameType = 3,
    kMalformedPayload = 4,
    kPayloadTooLarge = 5,

    // Request validation errors
    kEmptyInput = 6,
    kInputTooLong = 7,
    kInvalidCategoryCount = 8,

    // Server errors
    kServerUnavailable = 9,
    kTimeout = 10,
    kInternalError = 11,
};

inline std::string_view to_string(ErrorCode c) {
    switch (c) {
        case ErrorCode::kInvalidMagic:       return "invalid_magic";
        case ErrorCode::kInvalidVersion:     return "invalid_version";
        case ErrorCode::kInvalidFrameType:   return "invalid_frame_type";
        case ErrorCode::kMalformedPayload:   return "malformed_payload";
        case ErrorCode::kPayloadTooLarge:    return "payload_too_large";
        case ErrorCode::kEmptyInput:         return "empty_input";
        case ErrorCode::kInputTooLong:       return "input_too_long";
        case ErrorCode::kInvalidCategoryCount:return "invalid_category_count";
        case ErrorCode::kServerUnavailable:  return "server_unavailable";
        case ErrorCode::kTimeout:            return "timeout";
        case ErrorCode::kInternalError:      return "internal_error";
    }
    return "unknown";
}

// ============================================================================
// CorrelationIds
// ============================================================================

struct CorrelationIds {
    std::string request_id;         // Unique per-request ID (UUID-like)
    std::optional<std::string> correlation_id;
    std::optional<std::string> causation_id;

    static CorrelationIds make_default() {
        CorrelationIds ids;
        // Generate a simple monotonic counter-based request ID
        static uint64_t counter = 0;
        ids.request_id = "req-" + std::to_string(++counter);
        return ids;
    }
};

// ============================================================================
// Request Payload (for kRequest frames)
//
// Frame layout for kRequest:
//   [Header: 20 bytes]
//   [Payload]:
//     - RequestType (2B)
//     - TimeoutFlag (1B) - is timeout set?
//     - TimeoutMs (8B, if timeout flag set)
//     - InputTextLen (4B)
//     - InputText (variable)
// ============================================================================

struct SemanticRequest {
    RequestType type;
    std::string input_text;                    // For classify, generate_intent
    std::vector<std::string> evidence_lines;   // For summarize
    std::optional<std::string> query_context;  // For assess_relevance
    std::chrono::milliseconds timeout{kDefaultRequestTimeoutMs};

    // Request metadata for tracing
    CorrelationIds correlations;
};

// ============================================================================
// Response Payload (for kResponse frames)
//
// Frame layout for kResponse:
//   [Header: 20 bytes]
//   [Payload]:
//     - SuccessFlag (1B) - true if operation succeeded
//     - OutputLen (4B, if success flag set)
//     - Output (variable, if success flag set)
//     - ErrorMsgLen (4B, if not success flag set)
//     - ErrorMsg (variable, if not success flag set)
// ============================================================================

struct SemanticResponse {
    bool succeeded = false;
    std::optional<std::string> output;        // Model response if successful
    std::optional<std::string> error_message;

    // Timing
    std::chrono::milliseconds request_duration_ms{0};

    static SemanticResponse make_success(std::string out) {
        SemanticResponse r;
        r.succeeded = true;
        r.output = std::move(out);
        return r;
    }

    static SemanticResponse make_failure(std::string err) {
        SemanticResponse r;
        r.error_message = std::move(err);
        return r;
    }
};

// ============================================================================
// Error Payload (for kError frames)
//
// Frame layout for kError:
//   [Header: 20 bytes]
//   [Payload]:
//     - ErrorCode (2B)
//     - MessageLen (4B)
//     - Message (variable)
// ============================================================================

struct SemanticError {
    ErrorCode code;
    std::string message;

    static SemanticError make(ErrorCode c, std::string msg) {
        SemanticError e;
        e.code = c;
        e.message = std::move(msg);
        return e;
    }
};

// ============================================================================
// Frame Header (20 bytes fixed)
//
//   0                   1                   2                   3
//   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
//  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//  |                     Magic (4B) - 0x52534950                   |
//  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//  |    Version(2B)|     FrameType(2B)|         CorrelationID(8B)  |
//  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//  |                        PayloadLen (4B)                        |
//  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//
// Total: 20 bytes header
// ============================================================================

struct FrameHeader {
    uint32_t magic;           // Must be kProtocolMagic
    uint16_t version;         // Protocol version
    uint16_t frame_type;      // FrameType enum value
    uint64_t correlation_id;  // Correlation ID (counter-based)
    uint32_t payload_len;     // Length of payload in bytes

    static constexpr size_t kSize = 20;
};

// ============================================================================
// SemanticFrame - Complete framed message
// ============================================================================

struct SemanticFrame {
    FrameHeader header;
    std::vector<uint8_t> payload;

    bool is_valid() const {
        return header.magic == kProtocolMagic &&
               header.version == kProtocolVersion;
    }
};

// ============================================================================
// Validation helpers
// ============================================================================

namespace validation {

inline bool validate_input_text(const std::string& text) {
    if (text.empty()) return false;
    if (text.length() > kMaxStringFieldLen) return false;
    return true;
}

inline bool validate_evidence_lines(const std::vector<std::string>& lines, size_t max_count = 100) {
    if (lines.size() > max_count) return false;
    for (const auto& line : lines) {
        if (line.length() > kMaxStringFieldLen) return false;
    }
    return true;
}

inline bool validate_request(const SemanticRequest& req) {
    if (!validate_input_text(req.input_text)) return false;

    switch (req.type) {
        case RequestType::kClassify:
            // classify only needs input_text
            return true;
        case RequestType::kGenerateIntentCandidate:
            // generate_intent_candidate only needs input_text
            return true;
        case RequestType::kAssessEvidenceRelevance:
            // assess_evidence_relevance needs query_context
            if (!req.query_context.has_value() || req.query_context->empty()) {
                return false;
            }
            if (req.query_context->length() > kMaxStringFieldLen) {
                return false;
            }
            return true;
        case RequestType::kSummarizeDiagnostics:
            // summarize_diagnostics needs evidence_lines
            if (!validate_evidence_lines(req.evidence_lines)) {
                return false;
            }
            return true;
    }
    return false;
}

}  // namespace validation

// ============================================================================
// Frame Serialization/Deserialization (all in rebuntu::semantic namespace)
// ============================================================================

// Frame header parsing
std::optional<FrameHeader> parse_header(const uint8_t* data, size_t len);
const uint8_t* get_payload_ptr(const uint8_t* data, size_t len);

// Frame serialization/deserialization
std::vector<uint8_t> serialize_frame(const SemanticFrame& frame);
std::optional<SemanticFrame> deserialize_frame(const uint8_t* data, size_t len);

// Request serialization/deserialization (for client-side requests)
std::vector<uint8_t> serialize_request(const SemanticRequest& req);
std::optional<SemanticRequest> deserialize_request(const uint8_t* payload, size_t len);

// Response serialization/deserialization (for server responses)
std::vector<uint8_t> serialize_response(const SemanticResponse& resp);
std::optional<SemanticResponse> deserialize_response(const uint8_t* payload, size_t len);

// Error serialization/deserialization
std::vector<uint8_t> serialize_error(const SemanticError& error);
std::optional<SemanticError> deserialize_error(const uint8_t* payload, size_t len);

// ============================================================================
// Client-side IPC bindings (high-level API)
// ============================================================================

class SemanticIPCClient {
public:
    virtual ~SemanticIPCClient() = default;

    // Connect to the semantic service
    virtual bool connect(std::chrono::milliseconds timeout = std::chrono::milliseconds{kConnectionTimeoutMs}) = 0;

    // Disconnect from the service
    virtual void disconnect() = 0;

    // Check if connected
    virtual bool is_connected() const = 0;

    // Send a request and wait for response (with timeout)
    virtual std::optional<SemanticResponse> send_request(
        const SemanticRequest& request,
        std::chrono::milliseconds timeout = std::chrono::milliseconds{kDefaultRequestTimeoutMs}
    ) = 0;

    // Cancel a pending request
    virtual bool cancel_request(uint64_t correlation_id) = 0;
};

// Factory function to create an IPC client
std::unique_ptr<SemanticIPCClient> make_semantic_ipc_client(
    const std::string& socket_path);

}  // namespace rebuntu::semantic