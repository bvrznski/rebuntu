// rebuntu::infrastructure::packages — Package Metadata & Environment Reproducibility (Phase 3.11)
//
// This establishes Rebuntu's packaging infrastructure foundation:
//   * Typed dependency definitions with pip specifiers
//   * JSON-based lock file format for reproducible builds
//   * Runtime environment detection and verification
//   * Directory hashing for content-addressable reproducibility checking
//
// Key principles:
//   * FROZEN DATASTRUCTURES prevent runtime mutation
//   * HASH VERIFICATION is read-only (returns boolean)
//   * NO external tool invocation in core module
//   * CONTENT INTEGRITY via SHA256 hashing

#pragma once

#include <system/core/contracts.hpp>
#include <system/core/results.hpp>
#include <system/infrastructure/contracts.hpp>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <optional>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

namespace rebuntu::infrastructure::packages {

// ============================================================================
// Dependency — Typed dependency specifier
//
// Represents a single package dependency with version constraints,
// optional extras, and environment markers.
// ============================================================================

struct Dependency {
    std::string name;                    // Package name (e.g., "requests")
    std::string version;                 // Version constraint (e.g., ">=2.28.0,<3.0.0")
    std::vector<std::string> extras;     // Optional features (e.g., ["security", "socks"])
    std::optional<std::string> markers;  // Environment markers (e.g., "sys_platform == 'linux'")
    
    // Create a dependency from a pip-style specifier string
    static std::optional<Dependency> from_pip_specifier(std::string spec);
    
    // Serialize to pip specifier format
    std::string to_pip_specifier() const;
    
    // Equality comparison for testing
    bool operator==(const Dependency& other) const {
        return name == other.name &&
               version == other.version &&
               extras == other.extras &&
               markers == other.markers;
    }
};

// ============================================================================
// PackageMetadata — Static package specification
//
// Represents the complete metadata for a package as defined in configuration.
// ============================================================================

struct PackageMetadata {
    std::string name;                    // Package name
    std::string version;                 // Package version
    std::optional<std::string> description;
    std::vector<Dependency> dependencies;
    
    // Create placeholder metadata for testing
    static PackageMetadata placeholder();
};

// ============================================================================
// LockFile — Locked package state
//
// Represents a locked dependency graph with exact versions and hashes.
// Used for reproducible builds and environment verification.
// ============================================================================

struct LockFile {
    std::string version;                          // Lock file format version
    std::chrono::system_clock::time_point generated_at;
    std::vector<std::pair<Dependency, std::string>> packages;  // (dependency, sha256_hash)
    
    // Create a lock file from dependencies
    static LockFile from_dependencies(std::vector<std::pair<Dependency, std::string>> deps);
    
    // Serialize to JSON string
    std::string to_json() const;
    
    // Verify hash of a package content
    bool verify_hash(const std::string& package_name, const std::filesystem::path& file_path) const;
    
    // Load lock file from JSON file (returns nullopt if not found)
    static std::optional<LockFile> from_file(const std::filesystem::path& path);
    
    // Save to JSON file
    bool save_to_file(const std::filesystem::path& path) const;
};

// ============================================================================
// EnvironmentInfo — Runtime environment information
//
// Captures information about the current Python runtime environment.
// ============================================================================

struct EnvironmentInfo {
    std::string python_version;           // e.g., "3.11.5"
    std::filesystem::path executable;     // Path to python executable
    std::filesystem::path prefix;         // Installation prefix
    bool is_venv = false;                 // Whether running in a virtual environment
    
    // Get information from the current runtime environment
    static EnvironmentInfo from_current();
    
    // Check if this looks like a virtual environment (static helper)
    static bool check_is_venv(const std::filesystem::path& prefix);
};

// ============================================================================
// Directory hashing for reproducibility verification
//
// Computes content-addressable hashes of directory contents.
// ============================================================================

std::string compute_directory_hash(const std::filesystem::path& directory);

}  // namespace rebuntu::infrastructure::packages