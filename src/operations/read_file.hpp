// Rebuntu Operations — Read File Operation (Phase 6.69 Vertical Slice)
//
// This module implements a safe read file operation following the canonical
// Operation contract semantics:
//   - Typed inputs and outputs
//   - Preconditions (must hold before execution)
//   - Postconditions (must hold for success verification)
//   - Verification strategy
//   - Evidence supporting results

#pragma once

#include <system/core/contracts.hpp>
#include <filesystem>
#include <optional>
#include <string>
#include <vector>

namespace rebuntu::operations {

// ============================================================================
// ReadFileInputs — Typed inputs for read_file operation
// ============================================================================

struct ReadFileInputs {
    std::filesystem::path path;           // Path to read
    size_t max_bytes{65536};              // Maximum bytes to read (safety bound)
    
    // Validate inputs before execution
    bool is_valid(std::string& error) const;
};

// ============================================================================
// ReadFileResult — Typed output for read_file operation
// ============================================================================

struct ReadFileResult {
    core::SemanticStatus status = core::SemanticStatus::kUnknown;
    
    // Success data
    std::optional<std::string> content;   // File contents (if successful)
    size_t bytes_read{0};                 // Actual bytes read
    
    // Verification status
    bool verified = false;
    std::string verification_details;
    
    // Evidence sources
    std::vector<core::Evidence> evidence;
    
    // Error information (if not success)
    std::optional<core::Error> error;
    
    static ReadFileResult success(
        std::string content,
        size_t bytes_read = 0,
        bool verified = true
    ) {
        ReadFileResult r;
        r.status = core::SemanticStatus::kSuccess;
        r.content = std::move(content);
        r.bytes_read = bytes_read;
        r.verified = verified;
        return r;
    }
    
    static ReadFileResult failure(std::string code, std::string message) {
        ReadFileResult r;
        r.status = core::SemanticStatus::kFailure;
        r.error = core::Error{std::move(code), std::move(message)};
        return r;
    }
};

// ============================================================================
// read_file — Read file contents with full contract semantics
//
// Preconditions:
//   - Path must exist and be accessible
//   - Must have read permission on the file
//   - max_bytes must be > 0 (safety bound)
//
// Postconditions:
//   - If successful: file exists at path, content matches actual file contents
//   - bytes_read <= max_bytes (bound respected)
//
// Side Effects: NONE (read-only observation)
// Idempotency: IDEMPOTENT
// Reversibility: N/A (not mutating)
// ============================================================================

ReadFileResult read_file(const ReadFileInputs& inputs);

// ============================================================================
// register_read_file_operation — Register with operation registry
// ============================================================================

void register_read_file_operation(core::OperationRegistry& registry);

}  // namespace rebuntu::operations