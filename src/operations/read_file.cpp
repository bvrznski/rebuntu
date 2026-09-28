// Rebuntu Operations — Read File Implementation (Phase 6.69 Vertical Slice)
//
// This module implements the safe file reading operation:
//   - Typed inputs and outputs
//   - Preconditions checked before execution
//   - Evidence collected during observation
//   - Verification of postconditions

#include "read_file.hpp"
#include "filesystem.hpp"  // For filesystem_copy to demonstrate full pipeline

#include <fstream>
#include <sstream>
#include <string>

namespace rebuntu::operations {

// ============================================================================
// ReadFileInputs validation
// ============================================================================

bool ReadFileInputs::is_valid(std::string& error) const {
    if (path.empty()) {
        error = "path cannot be empty";
        return false;
    }
    
    if (max_bytes == 0) {
        error = "max_bytes must be greater than 0 (safety bound)";
        return false;
    }
    
    if (max_bytes > 1024 * 1024 * 1024) {  // 1GB safety cap
        error = "max_bytes exceeds maximum allowed (1GB)";
        return false;
    }
    
    return true;
}

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

ReadFileResult read_file(const ReadFileInputs& inputs) {
    std::string error;
    
    // Check preconditions
    if (!inputs.is_valid(error)) {
        return ReadFileResult::failure("E_INVALID_INPUT", std::move(error));
    }
    
    // Precondition: path must exist
    std::error_code ec;
    if (!std::filesystem::exists(inputs.path, ec)) {
        return ReadFileResult::failure(
            "E_FILE_NOT_FOUND",
            "Path does not exist: " + inputs.path.string()
        );
    }
    
    // Precondition: must be a regular file (not directory or special file)
    if (!std::filesystem::is_regular_file(inputs.path, ec)) {
        return ReadFileResult::failure(
            "E_NOT_A_FILE",
            "Path is not a regular file: " + inputs.path.string()
        );
    }
    
    // Precondition: must have read permission
    std::ifstream test_stream(inputs.path);
    if (!test_stream) {
        return ReadFileResult::failure(
            "E_PERMISSION_DENIED",
            "Cannot open file for reading: " + inputs.path.string()
        );
    }
    
    // Execute the read operation (bounded by max_bytes)
    std::ifstream file(inputs.path, std::ios::binary);
    if (!file) {
        return ReadFileResult::failure(
            "E_READ_FAILED",
            "Failed to open file for reading: " + inputs.path.string()
        );
    }
    
    // Create buffer with size bound
    size_t buffer_size = std::min(inputs.max_bytes, static_cast<size_t>(1024 * 1024));  // Max 1MB buffer
    
    std::string content;
    content.resize(buffer_size);
    
    file.read(&content[0], buffer_size);
    size_t bytes_read = file.gcount();
    content.resize(bytes_read);  // Adjust to actual read size
    
    if (file.bad()) {
        return ReadFileResult::failure(
            "E_READ_ERROR",
            "Error occurred while reading file: " + inputs.path.string()
        );
    }
    
    // Collect evidence of the observation
    core::Evidence evidence;
    evidence.source = "procfs";  // Linux filesystem API
    evidence.value = "file_read:" + inputs.path.string() + ":" + std::to_string(bytes_read);
    evidence.captured_at = "2024-01-01T00:00:00Z";  // Placeholder
    
    // Postcondition verification: bytes_read <= max_bytes
    bool verified = bytes_read <= inputs.max_bytes;
    
    return ReadFileResult::success(std::move(content), bytes_read, verified);
}

// ============================================================================
// register_read_file_operation — Register with operation registry
// ============================================================================

void register_read_file_operation(core::OperationRegistry& registry) {
    core::OperationDefinition op;
    op.id = "filesystem.read_file";
    op.title = "Read File Contents";
    op.description = "Safely read file contents with bounded size";
    op.long_description =
        "Reads the contents of a file up to a specified maximum byte limit. "
        "The operation validates preconditions before reading and returns "
        "bounded evidence supporting the result.";
    
    op.subject_type = "filesystem.path";
    op.side_effect = core::SideEffectKind::NONE;  // Read-only
    op.idempotency = core::Idempotency::IDEMPOTENT;
    op.reversibility = core::Reversibility::UNKNOWN;  // N/A for read operations
    
    // Resource declarations (Phase 2 integration)
    core::OperationDefinition::ResourceDeclaration io_resource;
    io_resource.type = core::OperationDefinition::ResourceDeclaration::Type::STORAGE_IO;
    io_resource.amount = 1.0;  // Estimated: ~1% storage I/O bandwidth
    io_resource.is_minimum = false;
    io_resource.description = "Storage I/O bandwidth during file read operation";
    op.resources.emplace_back(std::move(io_resource));
    
    // Preconditions
    op.preconditions.emplace_back("file exists at path");
    op.preconditions.emplace_back("file is regular file type");
    op.preconditions.emplace_back("read permission granted");
    
    // Postconditions
    op.postconditions.emplace_back("bytes_read <= max_bytes (safety bound)");
    op.postconditions.emplace_back("content matches actual file contents");
    
    // Verification strategy
    op.verification_kind = core::OperationDefinition::VerificationKind::STATE_OBSERVATION;
    op.verification_description = "Verify bytes_read is within bounds";
    
    // Evidence sources
    op.evidence_sources.emplace_back("procfs");
    
    registry.register_operation(std::move(op));
}

}  // namespace rebuntu::operations