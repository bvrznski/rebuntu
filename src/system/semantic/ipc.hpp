// rebuntu::semantic::ipc — Structured IPC Protocol Contracts (Phase 3.4)
//
// This establishes Rebuntu's canonical semantic service IPC protocol:
//
//   PROTOCOL CHARACTERISTICS
//     - Local only (Unix domain sockets, no TCP for security)
//     - Versioned (protocol versioning for compatibility)
//     - Typed requests/responses with structured schemas
//     - Correlation IDs for request tracking and cancellation
//     - Bounded payloads with size/time limits
//     - Error categories with semantic meaning
//
//   CRITICAL INVARIENTS
//     - MODEL OUTPUT != AUTHORITY (validation required)
//     - All requests attributable and cancellable
//     - Evidence trail for verification
//     - No secrets in protocol frames

#pragma once

#include <system/core/contracts.hpp>
#include <system/runtime/contracts.hpp>
#include <system/semantic/service.hpp>

#include <atomic>
#include <chrono>
#include <cstdint>
#include <map>
#include <optional>
#include <string>
#include <vector>

namespace rebuntu::semantic::ipc {

// ============================================================================
// Protocol Versioning
// ============================================================================

inline constexpr int kProtocolVersion = 1;

// ============================================================================
// Timeout Constants (for transport-level handling)
// ============================================================================

inline constexpr std::chrono::milliseconds kDefaultTimeout = std::chrono::seconds(30);
inline constexpr std::chrono::milliseconds kConnectionTimeout = std::chrono::seconds(5);
inline constexpr std::chrono::milliseconds kCancellationGracePeriod = std::chrono::milliseconds(100);

// ============================================================================
// Protocol Limits (for bounded execution and DoS prevention)
// ============================================================================

inline constexpr size_t kMaxPayloadSize = 1024 * 1024;       // 1 MB max payload
inline constexpr size_t kMaxStringFieldLength = 65536;       // Max string length
inline constexpr size_t kMaxCategories = 100;                // Max classification categories
inline constexpr size_t kMaxDiagnosticItems = 1000;          // Max diagnostic items

// ============================================================================
// Correlation ID — For request tracking and cancellation
// ============================================================================

struct CorrelationId {
    std::uint64_t value;
    
    static CorrelationId generate() {
        // Simple monotonically increasing counter for local IPC
        static std::atomic<std::uint64_t> next_id{1};
        return CorrelationId{next_id++};
    }
    
    explicit operator std::string() const { return std::to_string(value); }
};

inline bool operator==(CorrelationId a, CorrelationId b) {
    return a.value == b.value;
}

inline bool operator!=(CorrelationId a, CorrelationId b) {
    return !(a == b);
}

// ============================================================================
// IPC Error Categories
// ============================================================================

enum class IpcError : int16_t {
    kNone = 0,
    
    // Protocol errors
    kInvalidProtocolVersion,
    kMalformedFrame,
    kMissingField,
    kTypeMismatch,
    
    // Transport errors
    kConnectionRefused,
    kConnectionLost,
    kTimeout,
    kWouldBlock,
    
    // Server errors
    kServerUnavailable,
    kServerBusy,
    kServerInternalError,
    
    // Semantic errors (forwarded from provider)
    kSemanticTimeout,
    kSemanticProviderUnavailable,
    kSemanticValidationError,
};

inline std::string to_string(IpcError e) {
    switch (e) {
        case IpcError::kNone: return "IPC_NONE";
        case IpcError::kInvalidProtocolVersion: return "IPC_INVALID_VERSION";
        case IpcError::kMalformedFrame: return "IPC_MALFORMED_FRAME";
        case IpcError::kMissingField: return "IPC_MISSING_FIELD";
        case IpcError::kTypeMismatch: return "IPC_TYPE_MISMATCH";
        case IpcError::kConnectionRefused: return "IPC_CONNECTION_REFUSED";
        case IpcError::kConnectionLost: return "IPC_CONNECTION_LOST";
        case IpcError::kTimeout: return "IPC_TIMEOUT";
        case IpcError::kWouldBlock: return "IPC_WOULD_BLOCK";
        case IpcError::kServerUnavailable: return "IPC_SERVER_UNAVAILABLE";
        case IpcError::kServerBusy: return "IPC_SERVER_BUSY";
        case IpcError::kServerInternalError: return "IPC_SERVER_INTERNAL_ERROR";
        case IpcError::kSemanticTimeout: return "IPC_SEMANTIC_TIMEOUT";
        case IpcError::kSemanticProviderUnavailable: return "IPC_SEMANTIC_UNAVAILABLE";
        case IpcError::kSemanticValidationError: return "IPC_SEMANTIC_VALIDATION_ERROR";
    }
    return "IPC_UNKNOWN";
}

// ============================================================================
// IPC Result Type
// ============================================================================

struct IpcResult {
    IpcError error = IpcError::kNone;
    std::optional<std::string> error_message;
    
    core::SemanticStatus semantic_status() const {
        switch (error) {
            case IpcError::kNone:
                return core::SemanticStatus::kSuccess;
            case IpcError::kInvalidProtocolVersion:
            case IpcError::kMalformedFrame:
            case IpcError::kMissingField:
            case IpcError::kTypeMismatch:
            case IpcError::kConnectionRefused:
            case IpcError::kConnectionLost:
            case IpcError::kTimeout:
            case IpcError::kWouldBlock:
                return core::SemanticStatus::kFailure;
            default:
                return core::SemanticStatus::kUnknown;
        }
    }
    
    bool is_success() const { return semantic_status() == core::SemanticStatus::kSuccess; }
};

// ============================================================================
// Schema Validation Result
// ============================================================================

enum class ValidationErrorType : int16_t {
    kNone = 0,
    kInvalidInputFormat,
    kMissingRequiredField,
    kValueOutOfRange,
    kUnknownCategory,
    kMalformedResponse,
};

struct ValidationError {
    ValidationErrorType type;
    std::string field_name;
    std::string description;
    
    bool is_valid() const { return type == ValidationErrorType::kNone; }
};

// ============================================================================
// Frame Header — For framing and length-prefixed messages
// ============================================================================

struct FrameHeader {
    // Protocol magic to identify Rebuntu semantic frames
    static constexpr uint32_t kMagic = 0x52534950;  // "RSIP" (Rebuntu Semantic IPC)
    
    uint32_t magic;              // Must be kMagic
    int16_t version;             // Protocol version (kProtocolVersion)
    int16_t frame_type;          // FrameType enum value
    CorrelationId correlation;   // Request/response correlation
    uint32_t payload_length;     // Length of payload in bytes
    
    bool is_valid() const {
        return magic == kMagic && version <= kProtocolVersion;
    }
};

// ============================================================================
// Frame Types
// ============================================================================

enum class FrameType : int16_t {
    kRequest = 1,           // Client to server request
    kResponse = 2,          // Server to client response
    kError = 3,             // Error frame (server error or protocol error)
    kCancellation = 4,      // Cancel pending request
};

inline std::string to_string(FrameType ft) {
    switch (ft) {
        case FrameType::kRequest: return "request";
        case FrameType::kResponse: return "response";
        case FrameType::kError: return "error";
        case FrameType::kCancellation: return "cancellation";
    }
    return "unknown";
}

// ============================================================================
// Request Payload Types
// ============================================================================

enum class RequestType : int16_t {
    kClassification = 1,
    kIntentCandidate = 2,
    kEvidenceRelevance = 3,
    kDiagnosticSummary = 4,
};

inline std::string to_string(RequestType rt) {
    switch (rt) {
        case RequestType::kClassification: return "classification";
        case RequestType::kIntentCandidate: return "intent-candidate";
        case RequestType::kEvidenceRelevance: return "evidence-relevance";
        case RequestType::kDiagnosticSummary: return "diagnostic-summary";
    }
    return "unknown";
}

struct SemanticRequestPayload {
    RequestType type;
    
    // Common request fields
    std::chrono::system_clock::time_point timestamp;
    std::optional<std::chrono::milliseconds> timeout_ms;
    
    // Typed request data
    struct ClassificationData {
        std::string input;
        std::vector<std::string> categories;
        
        ValidationError validate() const {
            if (input.empty()) {
                return {ValidationErrorType::kInvalidInputFormat, "input", "Classification input must not be empty"};
            }
            if (input.length() > kMaxStringFieldLength) {
                return {ValidationErrorType::kValueOutOfRange, "input", 
                        "Input exceeds maximum length of " + std::to_string(kMaxStringFieldLength)};
            }
            if (categories.size() > kMaxCategories) {
                return {ValidationErrorType::kValueOutOfRange, "categories",
                        "Too many categories: max is " + std::to_string(kMaxCategories)};
            }
            for (const auto& cat : categories) {
                if (cat.empty()) {
                    return {ValidationErrorType::kInvalidInputFormat, "category", "Category must not be empty"};
                }
            }
            return {ValidationErrorType::kNone, "", ""};
        }
    };
    
    struct IntentCandidateData {
        std::string input;
        std::vector<std::string> allowed_operations;
        
        ValidationError validate() const {
            if (input.empty()) {
                return {ValidationErrorType::kInvalidInputFormat, "input", "Intent candidate input must not be empty"};
            }
            if (input.length() > kMaxStringFieldLength) {
                return {ValidationErrorType::kValueOutOfRange, "input",
                        "Input exceeds maximum length of " + std::to_string(kMaxStringFieldLength)};
            }
            if (allowed_operations.size() > kMaxCategories) {
                return {ValidationErrorType::kValueOutOfRange, "operations",
                        "Too many operations: max is " + std::to_string(kMaxCategories)};
            }
            for (const auto& op : allowed_operations) {
                if (op.empty()) {
                    return {ValidationErrorType::kInvalidInputFormat, "operation", "Operation must not be empty"};
                }
            }
            return {ValidationErrorType::kNone, "", ""};
        }
    };
    
    struct EvidenceRelevanceData {
        std::string evidence;
        std::string context;
        
        ValidationError validate() const {
            if (evidence.empty()) {
                return {ValidationErrorType::kMissingRequiredField, "evidence", "Evidence is required"};
            }
            if (evidence.length() > kMaxStringFieldLength) {
                return {ValidationErrorType::kValueOutOfRange, "evidence",
                        "Evidence exceeds maximum length of " + std::to_string(kMaxStringFieldLength)};
            }
            return {ValidationErrorType::kNone, "", ""};
        }
    };
    
    struct DiagnosticSummaryData {
        std::vector<std::string> diagnostic_items;
        
        ValidationError validate() const {
            if (diagnostic_items.empty()) {
                return {ValidationErrorType::kMissingRequiredField, "diagnostic_items",
                        "At least one diagnostic item is required"};
            }
            if (diagnostic_items.size() > kMaxDiagnosticItems) {
                return {ValidationErrorType::kValueOutOfRange, "diagnostic_items",
                        "Too many items: max is " + std::to_string(kMaxDiagnosticItems)};
            }
            for (const auto& item : diagnostic_items) {
                if (item.empty()) {
                    return {ValidationErrorType::kInvalidInputFormat, "item", "Item must not be empty"};
                }
            }
            return {ValidationErrorType::kNone, "", ""};
        }
    };
    
    // One of these will be populated based on type
    std::optional<ClassificationData> classification;
    std::optional<IntentCandidateData> intent_candidate;
    std::optional<EvidenceRelevanceData> evidence_relevance;
    std::optional<DiagnosticSummaryData> diagnostic_summary;
    
    ValidationError validate() const {
        switch (type) {
            case RequestType::kClassification:
                return classification.has_value() ? classification->validate() 
                    : ValidationError{ValidationErrorType::kMissingRequiredField, "classification", "Classification data required"};
            case RequestType::kIntentCandidate:
                return intent_candidate.has_value() ? intent_candidate->validate()
                    : ValidationError{ValidationErrorType::kMissingRequiredField, "intent_candidate", "Intent candidate data required"};
            case RequestType::kEvidenceRelevance:
                return evidence_relevance.has_value() ? evidence_relevance->validate()
                    : ValidationError{ValidationErrorType::kMissingRequiredField, "evidence_relevance", "Evidence relevance data required"};
            case RequestType::kDiagnosticSummary:
                return diagnostic_summary.has_value() ? diagnostic_summary->validate()
                    : ValidationError{ValidationErrorType::kMissingRequiredField, "diagnostic_summary", "Diagnostic summary data required"};
        }
        return {ValidationErrorType::kInvalidInputFormat, "type", "Unknown request type"};
    }
};

// ============================================================================
// Response Payload Types
// ============================================================================

enum class ResponseType : int16_t {
    kClassification = 1,
    kIntentCandidate = 2,
    kEvidenceRelevance = 3,
    kDiagnosticSummary = 4,
    kUnknownError = 5,  // Generic server error
};

inline std::string to_string(ResponseType rt) {
    switch (rt) {
        case ResponseType::kClassification: return "classification";
        case ResponseType::kIntentCandidate: return "intent-candidate";
        case ResponseType::kEvidenceRelevance: return "evidence-relevance";
        case ResponseType::kDiagnosticSummary: return "diagnostic-summary";
        case ResponseType::kUnknownError: return "unknown-error";
    }
    return "unknown";
}

struct SemanticResponsePayload {
    ResponseType type;
    
    // Timing information
    std::chrono::system_clock::time_point responded_at;
    std::optional<std::chrono::milliseconds> inference_time_ms;
    
    // Provider metadata (for traceability)
    std::string provider_id;
    
    // Typed response data
    struct ClassificationResultData {
        std::vector<std::pair<std::string, double>> categories;
        
        ValidationError validate() const {
            if (categories.empty()) {
                return {ValidationErrorType::kMissingRequiredField, "categories", 
                        "At least one category result is required"};
            }
            for (const auto& cat : categories) {
                if (cat.first.empty()) {
                    return {ValidationErrorType::kInvalidInputFormat, "category_name",
                            "Category name must not be empty"};
                }
                if (cat.second < 0.0 || cat.second > 1.0) {
                    return {ValidationErrorType::kValueOutOfRange, "confidence",
                            "Confidence must be between 0.0 and 1.0"};
                }
            }
            return {ValidationErrorType::kNone, "", ""};
        }
    };
    
    struct IntentCandidateDataResponse {
        std::string operation_id;
        std::optional<std::string> subject;
        std::map<std::string, std::string> parameters;
        double confidence;
        
        ValidationError validate() const {
            if (operation_id.empty()) {
                return {ValidationErrorType::kMissingRequiredField, "operation_id", 
                        "Operation ID is required"};
            }
            if (confidence < 0.0 || confidence > 1.0) {
                return {ValidationErrorType::kValueOutOfRange, "confidence",
                        "Confidence must be between 0.0 and 1.0"};
            }
            return {ValidationErrorType::kNone, "", ""};
        }
    };
    
    struct EvidenceRelevanceDataResponse {
        bool is_relevant;
        std::optional<double> relevance_score;
        std::optional<std::string> explanation;
        
        ValidationError validate() const {
            if (is_relevant && !explanation.has_value()) {
                return {ValidationErrorType::kMissingRequiredField, "explanation",
                        "Explanation required for relevant evidence"};
            }
            return {ValidationErrorType::kNone, "", ""};
        }
    };
    
    struct DiagnosticSummaryDataResponse {
        std::string summary;
        std::vector<std::string> key_findings;
        std::optional<std::string> suggested_action;
        
        ValidationError validate() const {
            if (summary.empty()) {
                return {ValidationErrorType::kMissingRequiredField, "summary", 
                        "Summary is required"};
            }
            return {ValidationErrorType::kNone, "", ""};
        }
    };
    
    std::optional<ClassificationResultData> classification;
    std::optional<IntentCandidateDataResponse> intent_candidate;
    std::optional<EvidenceRelevanceDataResponse> relevance;
    std::optional<DiagnosticSummaryDataResponse> summary;
    
    ValidationError validate() const {
        switch (type) {
            case ResponseType::kClassification:
                return classification.has_value() ? classification->validate()
                    : ValidationError{ValidationErrorType::kMissingRequiredField, "classification", "Classification data required"};
            case ResponseType::kIntentCandidate:
                return intent_candidate.has_value() ? intent_candidate->validate()
                    : ValidationError{ValidationErrorType::kMissingRequiredField, "intent_candidate", "Intent candidate data required"};
            case ResponseType::kEvidenceRelevance:
                return relevance.has_value() ? relevance->validate()
                    : ValidationError{ValidationErrorType::kMissingRequiredField, "relevance", "Relevance data required"};
            case ResponseType::kDiagnosticSummary:
                return summary.has_value() ? summary->validate()
                    : ValidationError{ValidationErrorType::kMissingRequiredField, "summary", "Summary data required"};
            default:
                return {ValidationErrorType::kNone, "", ""};  // kUnknownError doesn't need further validation
        }
    }
};

// ============================================================================
// Error Payload Type
// ============================================================================

enum class ErrorCode : int16_t {
    kNone = 0,
    kInvalidRequest = 1,      // Request format is invalid
    kUnknownRequestType = 2,  // Request type not recognized
    kTimeout = 3,             // Request timed out
    kServerBusy = 4,          // Server is busy processing other requests
    kProviderUnavailable = 5, // Semantic provider unavailable
    kValidationError = 6,     // Response validation failed
    kInternalError = 7,       // Internal server error
};

inline std::string to_string(ErrorCode ec) {
    switch (ec) {
        case ErrorCode::kNone: return "NONE";
        case ErrorCode::kInvalidRequest: return "INVALID_REQUEST";
        case ErrorCode::kUnknownRequestType: return "UNKNOWN_REQUEST_TYPE";
        case ErrorCode::kTimeout: return "TIMEOUT";
        case ErrorCode::kServerBusy: return "SERVER_BUSY";
        case ErrorCode::kProviderUnavailable: return "PROVIDER_UNAVAILABLE";
        case ErrorCode::kValidationError: return "VALIDATION_ERROR";
        case ErrorCode::kInternalError: return "INTERNAL_ERROR";
    }
    return "UNKNOWN";
}

struct ErrorPayload {
    ErrorCode code;
    std::string message;
    
    // Optional correlation to the original request
    CorrelationId related_correlation;
};

// ============================================================================
// Cancellation Payload Type
// ============================================================================

struct CancellationPayload {
    CorrelationId target;  // The request to cancel
};

// ============================================================================
// Frame Container — Complete wire format frame (using separate members)
// ============================================================================

struct Frame {
    FrameHeader header;
    
    // Separate payload members (union is problematic with non-trivial types)
    std::optional<SemanticRequestPayload> request;
    std::optional<SemanticResponsePayload> response;
    std::optional<ErrorPayload> error;
    std::optional<CancellationPayload> cancellation;
    
    FrameType frame_type() const { return static_cast<FrameType>(header.frame_type); }
};

// ============================================================================
// Frame Serialization (wire format)
// ============================================================================

// Serialize a frame to bytes (returns empty vector on failure)
std::vector<uint8_t> serialize_frame(const Frame& frame);

// Parse bytes into a frame (returns nullopt on failure)
std::optional<Frame> parse_frame(const std::vector<uint8_t>& data);

// Get the expected frame size from header (for streaming parsing)
std::optional<size_t> get_expected_frame_size(const uint8_t* data, size_t len);

}  // namespace rebuntu::semantic::ipc

namespace std {
    template <> struct hash<rebuntu::semantic::ipc::CorrelationId> {
        size_t operator()(const rebuntu::semantic::ipc::CorrelationId& id) const noexcept {
            return std::hash<std::uint64_t>{}(id.value);
        }
    };
}  // namespace std