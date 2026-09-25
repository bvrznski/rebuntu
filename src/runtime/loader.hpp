// rebuntu::runtime::loader — Safe Runtime Definition Loader (Phase 4.9)
//
// The Loader is responsible for:
//   - Discovering and materializing runtime definitions
//   - Validating schema and metadata before execution
//   - Separating trusted installed Rebuntu from user configuration
//   - Detecting duplicates, malformed specs, and load cycles
//   - Avoiding import-time side effects (definitions are NOT executed)
//
// Safety principles:
//   - Trusted path: /etc/rebuntu/, /usr/share/rebuntu/
//   - Untrusted paths: ~/rebuntu/, /tmp/rebuntu/ (read-only validation only)
//   - No arbitrary code execution from untrusted sources
//   - Definitions are materialized but NOT executed

#pragma once

#include <filesystem>
#include <map>
#include <memory>
#include <optional>
#include <set>
#include <string>
#include <vector>

namespace rebuntu::runtime::loader {

// ============================================================================
// LoadKind — What kind of definition is being loaded
// ============================================================================

enum class LoadKind {
    kUnit,
    kOperation,
    kWorkflow,
    kTask,
};

inline std::string to_string(LoadKind k) {
    switch (k) {
        case LoadKind::kUnit: return "unit";
        case LoadKind::kOperation: return "operation";
        case LoadKind::kWorkflow: return "workflow";
        case LoadKind::kTask: return "task";
    }
    return "unknown";
}

// ============================================================================
// DefinitionId — Unique identifier for a loaded definition
// ============================================================================

struct DefinitionId {
    std::string value;
    
    explicit DefinitionId(std::string v) : value(std::move(v)) {}
    
    bool operator==(const DefinitionId& other) const { return value == other.value; }
    bool operator!=(const DefinitionId& other) const { return !(*this == other); }
    bool operator<(const DefinitionId& other) const { return value < other.value; }
};

// ============================================================================
// DefinitionMetadata — Static information about a definition
// ============================================================================

struct DefinitionMetadata {
    std::string id;
    LoadKind kind = LoadKind::kUnit;
    std::optional<std::string> title;
    std::optional<std::string> description;
    int schema_version = 1;
    std::optional<std::string> created_at;
    std::optional<std::string> updated_at;
    std::filesystem::path source_path;
    bool is_trusted = false;
    std::vector<DefinitionId> dependencies;
    bool schema_valid = false;
    bool metadata_complete = false;
};

// ============================================================================
// LoadErrorCode — Error categories for loader failures
// ============================================================================

enum class LoadErrorCode {
    kFileNotFound,
    kPermissionDenied,
    kMalformedSchema,
    kInvalidId,
    kDuplicateId,
    kCycleDetected,
    kMissingRequiredField,
    kTypeMismatch,
    kUntrustedSource,
};

// ============================================================================
// LoadError — Detailed error information for failed loads
// ============================================================================

struct LoadError {
    LoadErrorCode code;
    std::string message;
    std::filesystem::path file_path;
    int line_number = 0;
    
    static LoadError not_found(const std::filesystem::path& pth) {
        LoadError e;
        e.code = LoadErrorCode::kFileNotFound;
        e.message = "Definition file not found";
        e.file_path = pth;
        return e;
    }
    
    static LoadError duplicate(const DefinitionId& id, const std::filesystem::path& existing) {
        LoadError e;
        e.code = LoadErrorCode::kDuplicateId;
        e.message = "Duplicate definition ID: " + id.value;
        e.file_path = existing;
        return e;
    }
    
    static LoadError malformed(const std::string& msg, int line = 0) {
        LoadError e;
        e.code = LoadErrorCode::kMalformedSchema;
        e.message = "Malformed definition: " + msg;
        e.line_number = line;
        return e;
    }
};

// ============================================================================
// LoadResultStatus — Result status for loader operations
// ============================================================================

enum class LoadResultStatus {
    kSuccess,
    kFailure,
    kSkipped,
};

// ============================================================================
// LoadResult — Result of a single definition load operation
// ============================================================================

struct LoadResult {
    LoadResultStatus status;
    std::optional<DefinitionMetadata> metadata;
    std::vector<std::string> evidence;
    std::optional<LoadError> error;
    
    static LoadResult success(const DefinitionMetadata& meta) {
        LoadResult r;
        r.status = LoadResultStatus::kSuccess;
        r.metadata = meta;
        return r;
    }
    
    static LoadResult failure(LoadError err, const std::string& ev = "") {
        LoadResult r;
        r.status = LoadResultStatus::kFailure;
        r.error = std::move(err);
        if (!ev.empty()) r.evidence.push_back(ev);
        return r;
    }
    
    static LoadResult skipped(const DefinitionId& id, const std::string& reason) {
        LoadResult r;
        r.status = LoadResultStatus::kSkipped;
        r.error = LoadError{LoadErrorCode::kUntrustedSource, reason, std::filesystem::path{}, 0};
        return r;
    }
    
    bool succeeded() const { return status == LoadResultStatus::kSuccess; }
};

// ============================================================================
// TrustedPaths — Configuration for trusted filesystem paths
// ============================================================================

struct TrustedPaths {
    std::vector<std::filesystem::path> config_dir;
    std::vector<std::filesystem::path> share_dir;
    std::vector<std::filesystem::path> local_dir;
};

// ============================================================================
// LoaderConfig — Configuration for the Loader
// ============================================================================

struct LoaderConfig {
    TrustedPaths trusted_paths;
    bool allow_untrusted = false;
    std::vector<std::string> definition_extensions = {".yaml", ".json", ".conf"};
    size_t max_file_size_bytes = 1024 * 1024;
    bool strict_validation_only = true;
};

// ============================================================================
// Loader — Runtime definition loader
// ============================================================================

class Loader {
public:
    explicit Loader();
    explicit Loader(LoaderConfig config);
    
    virtual ~Loader() = default;
    
    LoadResult load_from_path(const std::filesystem::path& pth, LoadKind kind);
    std::vector<LoadResult> load_trusted(LoadKind kind);
    std::vector<LoadResult> load_all(LoadKind kind);
    std::vector<LoadResult> load_untrusted(const std::filesystem::path& pth, LoadKind kind);
    
    std::optional<DefinitionMetadata> get(const DefinitionId& id) const;
    bool contains(const DefinitionId& id) const;
    std::vector<DefinitionId> list_all() const;
    std::vector<DefinitionMetadata> list_by_kind(LoadKind kind) const;
    
    void clear();
    std::vector<LoadResult> reload_trusted(LoadKind kind);
    bool can_accept(const std::filesystem::path& pth, LoadKind kind) const;

private:
    LoaderConfig config_;
    std::map<DefinitionId, DefinitionMetadata> registry_;
    mutable std::set<std::string> load_errors_;
    
    bool is_trusted_path(const std::filesystem::path& pth) const;
    LoadResult validate_and_load(const std::filesystem::path& pth, LoadKind kind);
    LoadResult parse_metadata(const std::filesystem::path& pth, LoadKind kind);
    bool detect_cycle(const DefinitionId& id, std::set<DefinitionId>& visiting) const;
};

// ============================================================================
// LoaderBuilder — Fluent configuration for Loader
// ============================================================================

class LoaderBuilder {
public:
    LoaderBuilder();
    
    LoaderBuilder& set_trusted_paths(TrustedPaths paths);
    LoaderBuilder& add_trusted_config_dir(std::filesystem::path pth);
    LoaderBuilder& add_trusted_share_dir(std::filesystem::path pth);
    
    LoaderBuilder& allow_untrusted(bool allow);
    LoaderBuilder& set_max_file_size(size_t bytes);
    LoaderBuilder& set_strict_validation(bool strict);
    
    std::unique_ptr<Loader> build();

private:
    LoaderConfig config_;
};

// ============================================================================
// Factory functions
// ============================================================================

inline std::unique_ptr<Loader> make_loader() {
    return std::make_unique<Loader>();
}

inline std::unique_ptr<Loader> make_loader_with_config(LoaderConfig cfg) {
    return std::make_unique<Loader>(std::move(cfg));
}

}  // namespace rebuntu::runtime::loader