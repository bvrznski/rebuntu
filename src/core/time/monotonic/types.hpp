// rebuntu::core::time::monotonic — Monotonic Time Primitives (Phase 6.30)
//
// Canonical monotonic time vocabulary and contracts for Rebuntu.
// Monotonic time is essential for deadlines because it's unaffected by
// system clock adjustments (NTP, manual changes).
//
// Key principles:
//   - CLOCK_MONOTONIC: Elapsed time since boot, never goes backward
//   - Deadlines MUST use monotonic for bounded execution guarantees

#pragma once

#include <chrono>
#include <cstdint>
#include <optional>
#include <string>

namespace rebuntu::core::time {

// -----------------------------------------------------------------------------
// MonotonicTimePoint
// -----------------------------------------------------------------------------
using MonotonicTimePoint = std::chrono::steady_clock::time_point;

inline MonotonicTimePoint now() {
    return std::chrono::steady_clock::now();
}

// -----------------------------------------------------------------------------
// MonotonicTimestamp
// -----------------------------------------------------------------------------
// A timestamp using monotonic time (CLOCK_MONOTONIC).

struct MonotonicTimestamp {
    std::optional<std::chrono::steady_clock::time_point> monotonic_time;
    
    static MonotonicTimestamp now() {
        return MonotonicTimestamp{std::chrono::steady_clock::now()};
    }
    
    static MonotonicTimestamp from_duration(std::chrono::steady_clock::duration offset) {
        return MonotonicTimestamp{std::chrono::steady_clock::time_point{} + offset};
    }
    
    bool has_value() const { return monotonic_time.has_value(); }
};

// -----------------------------------------------------------------------------
// MonotonicDuration
// -----------------------------------------------------------------------------

using MonotonicDuration = std::chrono::steady_clock::duration;

inline constexpr MonotonicDuration zero_monotonic_duration() {
    return MonotonicDuration{0};
}

// -----------------------------------------------------------------------------
// MonotonicDeadline
// -----------------------------------------------------------------------------

struct MonotonicDeadline {
    std::chrono::steady_clock::time_point timestamp;
    
    static MonotonicDeadline from_duration(std::chrono::steady_clock::duration d) {
        return MonotonicDeadline{std::chrono::steady_clock::now() + d};
    }
    
    bool is_expired() const {
        return std::chrono::steady_clock::now() >= timestamp;
    }
    
    std::optional<std::chrono::steady_clock::duration> remaining() const {
        auto now = std::chrono::steady_clock::now();
        auto diff = timestamp - now;
        if (diff <= std::chrono::steady_clock::duration{0}) {
            return std::nullopt;
        }
        return diff;
    }
    
    bool is_before(const MonotonicDeadline& other) const {
        return timestamp < other.timestamp;
    }
    
    bool operator<(const MonotonicDeadline& other) const { return timestamp < other.timestamp; }
    bool operator<=(const MonotonicDeadline& other) const { return timestamp <= other.timestamp; }
    bool operator>(const MonotonicDeadline& other) const { return timestamp > other.timestamp; }
    bool operator>=(const MonotonicDeadline& other) const { return timestamp >= other.timestamp; }
    bool operator==(const MonotonicDeadline& other) const { return timestamp == other.timestamp; }
};

// -----------------------------------------------------------------------------
// MonotonicTimeout
// -----------------------------------------------------------------------------

struct MonotonicTimeout {
    std::chrono::steady_clock::duration max_duration;
    
    static constexpr MonotonicTimeout from_seconds(int64_t s) { 
        return MonotonicTimeout{std::chrono::seconds(s)}; 
    }
    
    static constexpr MonotonicTimeout from_minutes(int64_t m) { 
        return MonotonicTimeout{std::chrono::minutes(m)}; 
    }
    
    bool would_exceed(std::chrono::steady_clock::duration d) const {
        return d > max_duration;
    }
};

// -----------------------------------------------------------------------------
// MonotonicContext
// -----------------------------------------------------------------------------

struct MonotonicContext {
    std::optional<MonotonicDeadline> deadline;
    std::optional<MonotonicTimeout> default_timeout;
    
    bool has_deadline() const { 
        return static_cast<bool>(deadline); 
    }
    
    MonotonicTimeout get_effective_timeout(MonotonicTimeout fallback = MonotonicTimeout{std::chrono::minutes(5)}) const {
        if (default_timeout) {
            return *default_timeout;
        }
        auto rem = remaining();
        if (rem.has_value()) {
            return MonotonicTimeout{*rem};
        }
        return fallback;
    }
    
    bool is_expired() const {
        return deadline && deadline->is_expired();
    }
    
    std::optional<std::chrono::steady_clock::duration> remaining() const {
        return deadline ? deadline->remaining() : std::nullopt;
    }
    
    MonotonicContext with_deadline(MonotonicDeadline d) const {
        MonotonicContext child = *this;
        if (!child.deadline || d.is_before(*child.deadline)) {
            child.deadline = d;
        }
        return child;
    }
    
    MonotonicContext with_timeout(MonotonicTimeout t) const {
        MonotonicContext child = *this;
        if (!child.default_timeout || 
            t.max_duration < child.default_timeout->max_duration) {
            child.default_timeout = t;
        }
        return child;
    }
};

inline constexpr MonotonicContext default_monotonic_context{std::nullopt, std::nullopt};

// -----------------------------------------------------------------------------
// DeadlineStatus
// -----------------------------------------------------------------------------

enum class DeadlineStatus {
    kNotSet,
    kActive,
    kExpired,
    kExhausted,
};

inline std::string to_string(DeadlineStatus s) {
    switch (s) {
        case DeadlineStatus::kNotSet:   return "not_set";
        case DeadlineStatus::kActive:   return "active";
        case DeadlineStatus::kExpired:  return "expired";
        case DeadlineStatus::kExhausted:return "exhausted";
    }
    return "unknown";
}

// -----------------------------------------------------------------------------
// MonotonicResult
// -----------------------------------------------------------------------------

template<typename T>
struct MonotonicResult {
    core::SemanticStatus status;
    
    std::optional<T> value;
    
    std::chrono::steady_clock::time_point start_time{std::chrono::steady_clock::time_point{}};
    std::optional<MonotonicDeadline> deadline;
    std::optional<MonotonicTimeout> timeout_used;
    
    std::chrono::milliseconds elapsed_ms{0};
    
    DeadlineStatus deadline_status = DeadlineStatus::kNotSet;
    std::string post_deadline_assessment;
    
    bool is_success() const { return status == core::SemanticStatus::kSuccess; }
    bool is_timeout() const { 
        return deadline_status == DeadlineStatus::kExpired || 
               deadline_status == DeadlineStatus::kExhausted; 
    }
};

// -----------------------------------------------------------------------------
// TimeBudget
// -----------------------------------------------------------------------------

struct TimeBudget {
    std::chrono::steady_clock::duration total_budget;
    
    std::optional<std::chrono::steady_clock::duration> remaining() const {
        if (total_budget <= zero_monotonic_duration()) return std::nullopt;
        return total_budget;
    }
    
    bool try_consume(std::chrono::steady_clock::duration duration) {
        if (duration > total_budget) {
            return false;
        }
        total_budget -= duration;
        return true;
    }
};

// -----------------------------------------------------------------------------
// DeadlinePropagation
// -----------------------------------------------------------------------------

enum class DeadlinePropagation {
    kInherit,
    kOverride,
    kShortenOnly,
};

inline std::string to_string(DeadlinePropagation p) {
    switch (p) {
        case DeadlinePropagation::kInherit:     return "inherit";
        case DeadlinePropagation::kOverride:    return "override";
        case DeadlinePropagation::kShortenOnly: return "shorten_only";
    }
    return "unknown";
}

}  // namespace rebuntu::core::time