// rebuntu::system::diagnostics::snapshot — Error types for snapshot service (Phase 5.13)

#pragma once

#include <string>

namespace rebuntu::system::diagnostics::snapshot {

// Snapshot error codes
enum class ErrorCode {
    kUnknown,
    kStorageUnavailable,
    kInvalidRequest,
    kTimeout,
    kPartialEvidence,
    kBootIdMismatch,
};

inline std::string to_string(ErrorCode code) {
    switch (code) {
        case ErrorCode::kUnknown:           return "unknown";
        case ErrorCode::kStorageUnavailable:return "storage_unavailable";
        case ErrorCode::kInvalidRequest:    return "invalid_request";
        case ErrorCode::kTimeout:           return "timeout";
        case ErrorCode::kPartialEvidence:   return "partial_evidence";
        case ErrorCode::kBootIdMismatch:    return "boot_id_mismatch";
    }
    return "unknown";
}

}  // namespace rebuntu::system::diagnostics::snapshot