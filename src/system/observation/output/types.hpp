// rebuntu::system::observation::output — Machine-Readable Observation Output Schema (Phase 5.61)
//
// This module defines the machine-readable observation output schema:
//   - Versioned output format with explicit schema identifiers
//   - Bounded structured data for inspection commands
//   - Evidence preservation and provenance tracking
//   - Typed identity, state, timing dimensions
//
// Key Principles:
//   - Output is NEVER control authority (DATA != CONTROL)
//   - Observations are raw facts from native sources
//   - No inference or speculation in output
//   - Bounded size limits prevent resource exhaustion
//   - Versioning ensures external compatibility

#pragma once

#include <memory>
#include <system/core/contracts.hpp>
#include <string>
#include <vector>
#include <chrono>
#include <optional>
#include <map>

namespace rebuntu::system::observation::output {

// ============================================================================
// OutputSchema — Schema identifier for output format versioning
//
// This enables:
//   - Backward compatibility across output versions
//   - External tool compatibility (schema validation)
//   - Version negotiation between client and server
//
// ============================================================================

struct OutputSchema {
    std::string name;                    // e.g., "observation/v1"
    std::string version;                 // Semantic version, e.g., "1.0.0"
    std::optional<std::string> schema_uri;  // Optional JSON Schema URL
    
    static OutputSchema make_v1() {
        OutputSchema s;
        s.name = "observation";
        s.version = "1.0.0";
        s.schema_uri = "https://rebuntu.system/schema/observation/v1.json";
        return s;
    }
};

// ============================================================================
// OutputMetadata — Metadata about an observation output
//
// This provides context for interpreting the observation data:
//   - When it was generated (temporal reference)
//   - Where it came from (source)
//   - What it covers (subjects, temporal window)
//   - How to interpret it (schema, bounds applied)
//
// ============================================================================

struct OutputMetadata {
    // Output schema information
    OutputSchema schema;
    
    // Generation timing
    std::chrono::system_clock::time_point generated_at{};
    
    // Temporal coverage of observations
    std::optional<std::chrono::system_clock::time_point> since;
    std::optional<std::chrono::system_clock::time_point> until;
    
    // What was observed
    std::vector<std::string> subjects;  // e.g., "host", "service:nginx", "process:1234"
    
    // Source information
    std::string source{"observation"};   // e.g., "procfs", "sysfs", "journald"
    
    // Bounds applied to the output
    struct AppliedBounds {
        size_t max_records{0};
        size_t records_dropped{0};  // How many were dropped due to bounds
        std::optional<std::string> truncation_reason;
    } applied_bounds;
};

// ============================================================================
// ObservationValue — A single observation value with provenance
//
// This is the atomic unit of observation data:
//   - source: Where this value came from (file, API, etc.)
//   - path: Where in the source hierarchy (e.g., "/proc/1234/cmdline")
//   - value: The observed value (bounded)
//   - timestamp: When it was read
//
// ============================================================================

struct ObservationValue {
    // Provenance
    std::string source;
    std::optional<std::string> path;       // e.g., "/proc/1234/stat"
    
    // Timestamp when the observation was made
    std::chrono::system_clock::time_point observed_at{};
    
    // The observed value (bounded, must not exceed PayloadSizeLimit)
    std::string value;
    
    // Validation status
    enum class ValidationStatus {
        kValid,          // Value is valid and can be trusted
        kInvalid,        // Value was malformed or out of expected range
        kUnknown,        // Could not validate (acquisition failure)
    } validation_status{ValidationStatus::kValid};
    
    // Error information if not valid
    std::optional<core::Error> error;
    
    static ObservationValue make(
        std::string src,
        std::string p,
        std::chrono::system_clock::time_point when,
        std::string v) {
        ObservationValue o;
        o.source = std::move(src);
        o.path = std::move(p);
        o.observed_at = when;
        o.value = std::move(v);
        return o;
    }
};

// ============================================================================
// ObservationRecord — A complete observation record for a single entity
//
// This groups related observations about one entity:
//   - identity: Stable identifier (not transient properties)
//   - state: The entity's current state
//   - attributes: Key-value metadata
//   - timing: When this snapshot was taken
//   - sources: Where each piece came from
//
// ============================================================================

struct ObservationRecord {
    // Entity identity (stable across time, not transient properties)
    std::string id;                       // e.g., "service:nginx", "process:1234:boot:5678"
    
    // Human-readable name if available
    std::optional<std::string> name;
    
    // Category/type of this entity
    std::optional<std::string> category;
    
    // Entity state
    enum class State {
        kUnknown,
        kActive,      // Currently running/active
        kInactive,    // Not currently active
        kPending,     // Waiting to start/stop
        kFailed,      // Last attempt failed
        kDegraded,    // Active but with reduced capability
    } state{State::kUnknown};
    
    // Entity attributes as key-value pairs (bounded)
    std::map<std::string, std::string> attributes;
    
    // When this observation was made
    std::chrono::system_clock::time_point observed_at{};
    
    // All individual observations that make up this record
    std::vector<ObservationValue> observations;
};

// ============================================================================
// OutputRecord — A complete machine-readable output record
//
// This is the top-level container for all inspection command outputs:
//   - schema: Versioned schema identifier
//   - metadata: Context about the output generation
//   - records: The actual observation data
//
// ============================================================================

struct OutputRecord {
    // Schema versioning information
    OutputSchema schema;
    
    // Context and timing
    OutputMetadata metadata;
    
    // The actual observations
    std::vector<ObservationRecord> records;
    
    // Overall outcome
    core::SemanticStatus status{core::SemanticStatus::kUnknown};
    std::optional<std::string> description;
    
    // Statistics about this output
    struct Statistics {
        size_t total_records{0};
        size_t fresh_records{0};      // Within freshness threshold
        size_t stale_records{0};      // Beyond freshness threshold
        size_t valid_values{0};       // Successfully validated
        size_t invalid_values{0};     // Validation failures
        std::chrono::milliseconds elapsed_ms{0};
    } statistics;
    
    static OutputRecord make(const OutputSchema& s, const OutputMetadata& m) {
        OutputRecord r;
        r.schema = s;
        r.metadata = m;
        return r;
    }
};

// ============================================================================
// OutputFormat — Supported output serialization formats
//
// This allows the same data structure to be serialized in different ways:
//   - JSON: Machine-readable, structured (primary format)
//   - YAML: Human-friendly configuration/serialization
//   - Table: CLI display format
//
// ============================================================================

enum class OutputFormat {
    kJSON,      // Primary machine-readable format
    kYAML,      // Human-friendly alternative
    kTable,     // CLI display format (not structured output)
};

inline std::string to_string(OutputFormat f) {
    switch (f) {
        case OutputFormat::kJSON:  return "json";
        case OutputFormat::kYAML:  return "yaml";
        case OutputFormat::kTable: return "table";
    }
    return "unknown";
}

// ============================================================================
// OutputOptions — Configuration for output generation
//
// Controls how observations are serialized:
//   - Format choice (JSON vs YAML)
//   - Bounds enforcement (size limits, record counts)
//   - Fallback behavior when bounds are hit
//
// ============================================================================

struct OutputOptions {
    OutputFormat format{OutputFormat::kJSON};
    
    // Boundaries for the output
    size_t max_records{1000};           // Maximum observation records
    size_t max_value_bytes{4096};       // Max bytes per value (truncation)
    
    // When bounds are hit
    bool truncate_on_overflow{true};     // Truncate rather than fail
    bool include_statistics{true};       // Include statistics in output
    
    // Freshness tracking
    std::chrono::milliseconds freshness_threshold_ms{std::chrono::minutes(5)};
    
    // Schema to use in output (for versioning)
    OutputSchema schema{OutputSchema::make_v1()};
};

// ============================================================================
// OutputGenerator — Interface for generating observation outputs
//
// This interface abstracts the serialization process:
//   - Accept observation records
//   - Apply bounds (size, count)
//   - Serialize in requested format
//   - Return structured result with metadata
//
// ============================================================================

class OutputGenerator {
public:
    virtual ~OutputGenerator() = default;
    
    // Configure the generator
    virtual core::Outcome configure(const OutputOptions& options) = 0;
    
    // Add an observation record (may be truncated if bounds exceeded)
    virtual core::Outcome add_record(ObservationRecord record) = 0;
    
    // Generate output in configured format
    virtual std::string generate() = 0;
    
    // Get the final metadata about this generation
    virtual OutputMetadata metadata() const = 0;
    
    // Get statistics about what was generated
    virtual OutputRecord::Statistics statistics() const = 0;
};

// ============================================================================
// Factory functions
// ============================================================================

std::unique_ptr<OutputGenerator> make_output_generator();

}  // namespace rebuntu::system::observation::output