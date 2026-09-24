// Rebuntu Operations — Filesystem Domain (Phase 0.10)
//
// This module implements filesystem operations as canonical Rebuntu Operations.
// Each Operation is a reusable, explicitly contracted capability with:
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

namespace rebuntu::operations {

// ============================================================================
// FilesystemCopyInputs — Typed inputs for filesystem.copy operation
// ============================================================================

struct FilesystemCopyInputs {
    std::filesystem::path source;
    std::filesystem::path destination;
    bool overwrite = false;           // Overwrite if destination exists?
    bool preserve_metadata = true;    // Preserve timestamps, permissions?
    
    // Validate inputs before execution
    bool is_valid(std::string& error) const;
};

// ============================================================================
// FilesystemCopyResult — Typed output for filesystem.copy operation
// ============================================================================

struct FilesystemCopyResult {
    core::SemanticStatus status = core::SemanticStatus::kUnknown;
    bool changed = false;            // Did state actually change?
    
    // Verification status
    bool verified = false;
    std::string verification_details;
    
    // Evidence sources
    std::vector<core::Evidence> evidence;
    
    // Error information (if not success)
    std::optional<core::Error> error;
    
    static FilesystemCopyResult success(
        bool was_changed = true,
        bool was_verified = true
    ) {
        FilesystemCopyResult r;
        r.status = core::SemanticStatus::kSuccess;
        r.changed = was_changed;
        r.verified = was_verified;
        return r;
    }
    
    static FilesystemCopyResult no_change() {
        // No-op: destination already exists with expected content
        FilesystemCopyResult r;
        r.status = core::SemanticStatus::kSuccess;
        r.changed = false;
        r.verified = true;
        return r;
    }
    
    static FilesystemCopyResult failure(std::string code, std::string message) {
        FilesystemCopyResult r;
        r.status = core::SemanticStatus::kFailure;
        r.error = core::Error{std::move(code), std::move(message)};
        return r;
    }
};

// ============================================================================
// filesystem_copy — Copy file with full contract semantics
//
// Precondition:
//   - Source path must exist and be readable
//   - Destination parent directory must exist (unless overwrite creates it)
//
// Postcondition:
//   - Destination exists at target location
//   - Destination content matches source
//   - Metadata preserved if requested
//
// Side Effects: MUTATING
// Idempotency: IDEMPOTENT (if overwrite=false, same result on repeated calls)
// Reversibility: CONDITIONALLY_REVERSIBLE (can delete destination)
// ============================================================================

FilesystemCopyResult filesystem_copy(const FilesystemCopyInputs& inputs);

// ============================================================================
// filesystem_exists — Query whether a path exists (observation operation)
//
// This is an observational query, not a mutation.
//
// Side Effects: NONE
// Idempotency: IDEMPOTENT
// Reversibility: N/A (not mutating)
// ============================================================================

struct FilesystemExistsResult {
    bool exists = false;
    std::filesystem::path path;
    
    // Evidence of observation
    core::Evidence source_evidence;
    
    static FilesystemExistsResult found(const std::filesystem::path& p) {
        FilesystemExistsResult r;
        r.exists = true;
        r.path = p;
        return r;
    }
    
    static FilesystemExistsResult not_found(const std::filesystem::path& p) {
        FilesystemExistsResult r;
        r.exists = false;
        r.path = p;
        return r;
    }
};

FilesystemExistsResult filesystem_exists(const std::filesystem::path& path);

// ============================================================================
// filesystem_verify_integrity — Verify file integrity against expected hash
//
// Postcondition:
//   - File exists at specified path
//   - File content hash matches expected_hash (if provided)
//
// Side Effects: NONE (read-only verification)
// Idempotency: IDEMPOTENT
// Reversibility: N/A
// ============================================================================

struct FilesystemVerifyResult {
    core::SemanticStatus status = core::SemanticStatus::kUnknown;
    bool verified = false;
    std::string verification_method;
    
    core::Evidence evidence;
    
    static FilesystemVerifyResult success(const std::string& method) {
        FilesystemVerifyResult r;
        r.status = core::SemanticStatus::kSuccess;
        r.verified = true;
        r.verification_method = method;
        return r;
    }
    
    static FilesystemVerifyResult failed(
        const std::string& method,
        std::string actual_value
    ) {
        FilesystemVerifyResult r;
        r.status = core::SemanticStatus::kFailure;
        r.verified = false;
        r.verification_method = method;
        return r;
    }
};

FilesystemVerifyResult filesystem_verify_integrity(
    const std::filesystem::path& path,
    std::optional<std::string> expected_hash = std::nullopt
);

// ============================================================================
// Operation Registry Registration Helpers
// ============================================================================

void register_filesystem_operations(core::OperationRegistry& registry);

}  // namespace rebuntu::operations