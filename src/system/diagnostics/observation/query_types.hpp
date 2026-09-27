// rebuntu::diagnostics::observation::query — Observation Query Foundation (Phase 5.44)
//
// This module provides narrow typed queries over live/snapshot observations.
// It does NOT implement a universal SQL-like query language, but rather
// focused query patterns needed by current components.
//
// Key Principles:
//   - QUERY != CONTROL: Queries observe, they don't mutate
//   - DATA != AUTHORITY: Query results are evidence, not policy
//   - UNKNOWN != PASS: Missing data is not a successful observation
//   - BOUNDED: All queries have time/resource limits to prevent storms

#pragma once

#include <memory>
#include <runtime/contracts.hpp>
#include <system/core/contracts.hpp>
#include <string>
#include <vector>
#include <chrono>
#include <optional>

namespace rebuntu::diagnostics::observation {

// ============================================================================
// ObservationQueryKind — Types of queries supported
// ============================================================================

enum class ObservationQueryKind {
    kFilter,         // Filter observations by criteria (like WHERE clause)
    kAggregate,      // Aggregate observations across sources
    kJoin,           // Join observations from different sources
    kWindowed,       // Window-based queries over time ranges
};

inline std::string to_string(ObservationQueryKind kind) {
    switch (kind) {
        case ObservationQueryKind::kFilter:     return "filter";
        case ObservationQueryKind::kAggregate:  return "aggregate";
        case ObservationQueryKind::kJoin:       return "join";
        case ObservationQueryKind::kWindowed:   return "windowed";
    }
    return "unknown";
}

// ============================================================================
// QueryOperator — Comparison operators for filter queries
// ============================================================================

enum class QueryOperator {
    kEqual,           // =
    kNotEqual,        // !=
    kLessThan,        // <
    kLessThanOrEqual, // <=
    kGreaterThan,     // >
    kGreaterThanOrEqual, // >=
    kContains,        // string contains substring
    kIn,              // value in set
    kNotIn,           // value not in set
};

inline std::string to_string(QueryOperator op) {
    switch (op) {
        case QueryOperator::kEqual:            return "=";
        case QueryOperator::kNotEqual:         return "!=";
        case QueryOperator::kLessThan:         return "<";
        case QueryOperator::kLessThanOrEqual:  return "<=";
        case QueryOperator::kGreaterThan:      return ">";
        case QueryOperator::kGreaterThanOrEqual: return ">=";
        case QueryOperator::kContains:         return "contains";
        case QueryOperator::kIn:               return "in";
        case QueryOperator::kNotIn:            return "not in";
    }
    return "unknown";
}

// ============================================================================
// ObservationField — Fields available for querying
// ============================================================================

enum class ObservationField {
    // Timestamp fields
    kTimestamp,           // Observation timestamp
    
    // Identity fields  
    kSource,              // Source identifier (e.g., "procfs", "systemd")
    kIdentity,            // Entity identity string
    
    // State fields
    kState,               // Current state value
    kStatus,              // Semantic status
    
    // Resource fields
    kResourceUsage,       // Resource usage value
    kMemoryKb,            // Memory in KB
    kCpuUsageNs,          // CPU usage in nanoseconds
    
    // Metadata fields
    kSubject,             // Subject being observed
    kBootId,              // Boot context identifier
};

inline std::string to_string(ObservationField field) {
    switch (field) {
        case ObservationField::kTimestamp:       return "timestamp";
        case ObservationField::kSource:          return "source";
        case ObservationField::kIdentity:        return "identity";
        case ObservationField::kState:           return "state";
        case ObservationField::kStatus:          return "status";
        case ObservationField::kResourceUsage:   return "resource_usage";
        case ObservationField::kMemoryKb:        return "memory_kb";
        case ObservationField::kCpuUsageNs:      return "cpu_usage_ns";
        case ObservationField::kSubject:         return "subject";
        case ObservationField::kBootId:          return "boot_id";
    }
    return "unknown";
}

// ============================================================================
// QueryExpression — A single query expression (e.g., "field = value")
// ============================================================================

struct QueryExpression {
    ObservationField field;
    QueryOperator op;
    
    // Value to compare against (typed variant)
    struct Value {
        std::optional<std::string> string_value;
        std::optional<int64_t> int_value;
        std::optional<uint64_t> uint_value;
        std::optional<bool> bool_value;
        std::optional<std::chrono::system_clock::time_point> time_value;
    };
    
    Value value;
    
    // For IN/NOT IN: set of values
    std::vector<std::string> string_set;
};

// ============================================================================
// ObservationFilterQuery — Filter query over observations
//
// Provides typed filtering based on field-value comparisons.
// ============================================================================

struct ObservationFilterQuery {
    // Root expressions (AND together)
    std::vector<QueryExpression> root_expressions;
    
    // Optional: limit number of results
    std::optional<size_t> limit;
    
    // Optional: sort by field (ascending or descending)
    struct SortBy {
        ObservationField field;
        bool ascending = true;
    };
    
    std::optional<SortBy> sort_by;
};

// ============================================================================
// AggregateFunction — Functions for aggregate queries
// ============================================================================

enum class AggregateFunction {
    kCount,      // Count of matching observations
    kSum,        // Sum of numeric field values
    kAverage,    // Average of numeric field values
    kMin,        // Minimum value
    kMax,        // Maximum value
};

inline std::string to_string(AggregateFunction fn) {
    switch (fn) {
        case AggregateFunction::kCount:   return "count";
        case AggregateFunction::kSum:     return "sum";
        case AggregateFunction::kAverage: return "average";
        case AggregateFunction::kMin:     return "min";
        case AggregateFunction::kMax:     return "max";
    }
    return "unknown";
}

// ============================================================================
// ObservationAggregateQuery — Aggregate query over observations
//
// Computes aggregate functions over filtered observation sets.
// ============================================================================

struct ObservationAggregateQuery {
    // Filter expressions to apply first
    std::vector<QueryExpression> filters;
    
    // Field to aggregate
    ObservationField field;
    AggregateFunction function;
};

// ============================================================================
// QueryResult — Result of executing a query
// ============================================================================

struct QueryResult {
    core::SemanticStatus status;
    std::string description;
    
    // Evidence supporting the result
    std::vector<core::Evidence> evidence;
    
    // For filter queries: matching observations
    std::vector<std::string> matching_ids;  // observation IDs
    
    // For aggregate queries: computed value
    struct AggregateValue {
        int64_t count{0};
        double sum{0.0};
        double average{0.0};
        int64_t min_value{0};
        int64_t max_value{0};
    };
    
    AggregateValue aggregate;
    
    bool verified = false;  // Postconditions verified
};

// ============================================================================
// QueryExecutionOptions — Options for query execution
// ============================================================================

struct QueryExecutionOptions {
    std::chrono::milliseconds timeout_ms{30000};      // Total query timeout
    size_t max_results = 10000;                        // Max results to return
    bool include_provenance = true;                    // Include evidence
    bool allow_partial = false;                         // Allow partial results
};

// ============================================================================
// ObservationQueryEngine — Interface for executing queries over observations
//
// This is a narrow interface focused on the query patterns needed by
// current Rebuntu components. It does NOT implement a full query language.
// ============================================================================

class ObservationQueryEngine {
public:
    virtual ~ObservationQueryEngine() = default;
    
    // Execute a filter query against available observations
    // Returns IDs of matching observations and evidence
    virtual QueryResult execute_filter(const ObservationFilterQuery& query,
                                       const QueryExecutionOptions& options) = 0;
    
    // Execute an aggregate query
    // Returns computed aggregate value with evidence
    virtual QueryResult execute_aggregate(const ObservationAggregateQuery& query,
                                          const QueryExecutionOptions& options) = 0;
    
    // List available observation sources
    virtual std::vector<std::string> list_sources() const = 0;
};

// ============================================================================
// QueryBuilder — Fluent builder for constructing queries
//
// Provides a type-safe way to build queries programmatically.
// ============================================================================

class ObservationQueryBuilder {
public:
    // Create a new filter query builder
    static ObservationQueryBuilder make_filter();
    
    // Filter operators
    ObservationQueryBuilder& where_equal(ObservationField field, std::string value);
    ObservationQueryBuilder& where_not_equal(ObservationField field, std::string value);
    ObservationQueryBuilder& where_less_than(ObservationField field, int64_t value);
    ObservationQueryBuilder& where_greater_than(ObservationField field, int64_t value);
    ObservationQueryBuilder& where_in(ObservationField field, const std::vector<std::string>& values);
    
    // Time range filters (common pattern)
    ObservationQueryBuilder& since(std::chrono::system_clock::time_point t);
    ObservationQueryBuilder& until(std::chrono::system_clock::time_point t);
    ObservationQueryBuilder& within(std::chrono::milliseconds window);
    
    // Limits
    ObservationQueryBuilder& limit(size_t n);
    
    // Sort
    ObservationQueryBuilder& order_by(ObservationField field, bool ascending = true);
    
    // Build the query
    ObservationFilterQuery build() &&;
    
private:
    ObservationFilterQuery query_;
};

// ============================================================================
// QueryResultBuilder — Builder for query results
// ============================================================================

class QueryResultBuilder {
public:
    static QueryResultBuilder success();
    static QueryResultBuilder failure(std::string code, std::string message);
    static QueryResultBuilder unknown(std::string message);
    
    QueryResultBuilder& add_evidence(core::Evidence e);
    QueryResultBuilder& set_description(std::string desc);
    
    // For filter results
    QueryResultBuilder& add_matching_id(std::string id);
    
    // For aggregate results
    QueryResultBuilder& set_count(int64_t count);
    QueryResultBuilder& set_sum(double sum);
    QueryResultBuilder& set_average(double avg);
    
    QueryResult build() &&;
    
private:
    QueryResult result_;
};

// ============================================================================
// Factory functions
// ============================================================================

std::unique_ptr<ObservationQueryEngine> make_observation_query_engine();

}  // namespace rebuntu::diagnostics::observation