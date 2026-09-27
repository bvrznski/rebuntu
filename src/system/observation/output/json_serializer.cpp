// rebuntu::system::observation::output — JSON Output Serializer (Phase 5.61)
//
// This module implements JSON serialization for observation outputs:
//   - Schema versioning in output header
//   - Structured record serialization with provenance tracking
//   - Bounded output to prevent resource exhaustion

#include "types.hpp"
#include <sstream>
#include <iomanip>
#include <chrono>

namespace rebuntu::system::observation::output {

namespace {

// ============================================================================
// JSON escape helper (basic, for values)
// ============================================================================

std::string json_escape_string(const std::string& s) {
    std::ostringstream oss;
    for (char c : s) {
        switch (c) {
            case '"':  oss << "\\\""; break;
            case '\\': oss << "\\\\"; break;
            case '\b': oss << "\\b";  break;
            case '\f': oss << "\\f";  break;
            case '\n': oss << "\\n";  break;
            case '\r': oss << "\\r";  break;
            case '\t': oss << "\\t";  break;
            default:
                if (static_cast<unsigned char>(c) < 0x20) {
                    oss << "\\u" << std::hex << std::setfill('0') << std::setw(4)
                        << static_cast<int>(static_cast<unsigned char>(c));
                } else {
                    oss << c;
                }
        }
    }
    return oss.str();
}

// ============================================================================
// Format ISO-8601 timestamp
// ============================================================================

std::string format_iso8601(std::chrono::system_clock::time_point tp) {
    auto tt = std::chrono::system_clock::to_time_t(tp);
    std::tm tm;
    gmtime_r(&tt, &tm);
    
    char buf[64];
    strftime(buf, sizeof(buf), "%Y-%m-%dT%H:%M:%SZ", &tm);
    return std::string(buf);
}

// ============================================================================
// State to string conversion
// ============================================================================

std::string state_to_string(ObservationRecord::State state) {
    switch (state) {
        case ObservationRecord::State::kActive:    return "active";
        case ObservationRecord::State::kInactive:  return "inactive";
        case ObservationRecord::State::kPending:   return "pending";
        case ObservationRecord::State::kFailed:    return "failed";
        case ObservationRecord::State::kDegraded:  return "degraded";
        default:                                   return "unknown";
    }
}

// ============================================================================
// Schema to string (for JSON output)
// ============================================================================

std::string schema_to_json_string(const OutputSchema& schema) {
    std::ostringstream oss;
    oss << "{\n";
    oss << "    \"name\": \"" << json_escape_string(schema.name) << "\",\n";
    oss << "    \"version\": \"" << json_escape_string(schema.version) << "\"";
    if (schema.schema_uri.has_value()) {
        oss << ",\n    \"schema_uri\": \"" << json_escape_string(schema.schema_uri.value()) << "\"";
    }
    oss << "\n  }";
    return oss.str();
}

}  // namespace

// ============================================================================
// OutputGeneratorImpl — Concrete JSON output generator
// ============================================================================

class OutputGeneratorImpl : public OutputGenerator {
public:
    ~OutputGeneratorImpl() override = default;
    
    explicit OutputGeneratorImpl() = default;
    
    core::Outcome configure(const OutputOptions& options) override {
        options_ = options;
        start_time_ = std::chrono::system_clock::now();
        records_.clear();
        stats_ = OutputRecord::Statistics{};
        return core::Outcome::success();
    }
    
    core::Outcome add_record(ObservationRecord record) override {
        if (records_.size() >= options_.max_records) {
            stats_.invalid_values++;
            if (!options_.truncate_on_overflow) {
                return core::Outcome::failure(
                    "E_OVERFLOW",
                    "maximum records exceeded");
            }
            // Truncate: don't add this record
            return core::Outcome::completed();
        }
        
        records_.push_back(std::move(record));
        stats_.total_records++;
        return core::Outcome::success();
    }
    
    std::string generate() override {
        std::ostringstream oss;
        
        auto now = std::chrono::system_clock::now();
        
        // Calculate statistics
        stats_ = OutputRecord::Statistics{};
        stats_.total_records = records_.size();
        
        for (const auto& rec : records_) {
            stats_.valid_values += count_valid_values(rec);
        }
        
        if (options_.include_statistics) {
            stats_.elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(
                now - start_time_);
        }
        
        // Build metadata
        OutputMetadata meta;
        meta.schema = options_.schema;
        meta.generated_at = now;
        meta.source = "observation";
        meta.applied_bounds.max_records = options_.max_records;
        meta.applied_bounds.records_dropped = records_.size() > options_.max_records ? 
            records_.size() - options_.max_records : 0;
        
        // Generate JSON output
        oss << "{\n";
        oss << "  \"$schema\": \"https://rebuntu.system/schema/observation/v1.json\",\n";
        oss << "  \"version\": \"" << meta.schema.version << "\",\n";
        oss << "  \"generated_at\": \"" << format_iso8601(now) << "\",\n";
        oss << "  \"source\": \"" << json_escape_string(meta.source) << "\",\n";
        
        // Temporal window
        if (meta.since.has_value()) {
            oss << "  \"since\": \"" << format_iso8601(meta.since.value()) << "\",\n";
        }
        if (meta.until.has_value()) {
            oss << "  \"until\": \"" << format_iso8601(meta.until.value()) << "\",\n";
        }
        
        // Records array
        oss << "  \"records\": [\n";
        for (size_t i = 0; i < records_.size(); ++i) {
            const auto& rec = records_[i];
            oss << "    {\n";
            oss << "      \"id\": \"" << json_escape_string(rec.id) << "\",\n";
            
            if (rec.name.has_value()) {
                oss << "      \"name\": \"" << json_escape_string(rec.name.value()) << "\",\n";
            }
            
            if (rec.category.has_value()) {
                oss << "      \"category\": \"" << json_escape_string(rec.category.value()) << "\",\n";
            }
            
            oss << "      \"state\": \"" << state_to_string(rec.state) << "\",\n";
            
            // Attributes
            oss << "      \"attributes\": {\n";
            size_t attr_count = 0;
            for (const auto& [k, v] : rec.attributes) {
                oss << "        \"" << json_escape_string(k) << "\": "
                    << "\"" << json_escape_string(v) << "\"";
                if (++attr_count < rec.attributes.size()) oss << ",";
                oss << "\n";
            }
            oss << "      },\n";
            
            // Observed at
            oss << "      \"observed_at\": \"" << format_iso8601(rec.observed_at) << "\",\n";
            
            // Observations array
            oss << "      \"observations\": [\n";
            for (size_t j = 0; j < rec.observations.size(); ++j) {
                const auto& obs = rec.observations[j];
                oss << "        {\n";
                oss << "          \"source\": \"" << json_escape_string(obs.source) << "\",\n";
                
                if (obs.path.has_value()) {
                    oss << "          \"path\": \"" << json_escape_string(obs.path.value()) << "\",\n";
                }
                
                oss << "          \"value\": \"" << json_escape_string(obs.value) << "\",\n";
                oss << "          \"valid\": " << (obs.validation_status == ObservationValue::ValidationStatus::kValid ? "true" : "false") << "\n";
                oss << "        }";
                if (j < rec.observations.size() - 1) oss << ",";
                oss << "\n";
            }
            oss << "      ]\n";
            
            oss << "    }";
            if (i < records_.size() - 1) oss << ",";
            oss << "\n";
        }
        oss << "  ]\n";
        
        // Statistics
        if (options_.include_statistics) {
            oss << ",\n  \"statistics\": {\n";
            oss << "    \"total_records\": " << stats_.total_records << ",\n";
            oss << "    \"valid_values\": " << stats_.valid_values << ",\n";
            oss << "    \"invalid_values\": " << stats_.invalid_values << ",\n";
            oss << "    \"elapsed_ms\": " << stats_.elapsed_ms.count() << "\n";
            oss << "  }\n";
        }
        
        oss << "}\n";
        
        return oss.str();
    }
    
    OutputMetadata metadata() const override {
        OutputMetadata meta;
        meta.schema = options_.schema;
        meta.generated_at = start_time_;
        meta.source = "observation";
        meta.applied_bounds.max_records = options_.max_records;
        meta.applied_bounds.records_dropped = 0;
        return meta;
    }
    
    OutputRecord::Statistics statistics() const override {
        return stats_;
    }

private:
    struct OutputOptions options_;
    std::vector<ObservationRecord> records_;
    std::chrono::system_clock::time_point start_time_{std::chrono::system_clock::now()};
    OutputRecord::Statistics stats_;
    
    size_t count_valid_values(const ObservationRecord& rec) const {
        size_t count = 0;
        for (const auto& obs : rec.observations) {
            if (obs.validation_status == ObservationValue::ValidationStatus::kValid) {
                count++;
            }
        }
        return count;
    }
};

// ============================================================================
// Factory function
// ============================================================================

std::unique_ptr<OutputGenerator> make_output_generator() {
    return std::make_unique<OutputGeneratorImpl>();
}

}  // namespace rebuntu::system::observation::output