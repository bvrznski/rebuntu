// rebuntu::core::time — Temporal Primitives (Phase 0.9)
//
// Canonical temporal vocabulary and contracts for Rebuntu.
// Time is a dimension, not a subsystem.
//
// Key distinctions:
//   - Timestamp: Point in time (absolute or relative)
//   - Duration: Amount of elapsed time
//   - Delay: Postponement instruction
//   - Schedule: Specification for WHEN activation should occur
//   - Deadline: Temporal boundary for objective completion
//   - Timeout: Maximum duration for an operation

#pragma once

#include <chrono>
#include <cstdint>
#include <optional>
#include <string>
#include <string_view>
#include <vector>

using namespace std::literals::chrono_literals;

namespace rebuntu::core::time {

// -----------------------------------------------------------------------------
// ClockDomain
// -----------------------------------------------------------------------------
// The clock source used for temporal measurements.
//
// CLOCK_REALTIME: Wall-clock time (affected by NTP/manual adjustments)
// CLOCK_MONOTONIC: Monotonic time (unaffected by clock changes, best for durations)
// CLOCK_BOOTTIME: Boot time including suspend (useful for boot-relative schedules)

enum class ClockDomain {
    kWallClock,      // CLOCK_REALTIME - calendar time
    kMonotonic,      // CLOCK_MONOTONIC - elapsed time
    kBootTime,       // CLOCK_BOOTTIME - uptime including suspend
};

inline std::string_view to_string(ClockDomain d) {
    switch (d) {
        case ClockDomain::kWallClock:   return "wall_clock";
        case ClockDomain::kMonotonic:   return "monotonic";
        case ClockDomain::kBootTime:    return "boot_time";
    }
    return "unknown";
}

// -----------------------------------------------------------------------------
// Timestamp
// -----------------------------------------------------------------------------
// A point in time, representing an instant.
//
// Can be represented as:
//   - Absolute (wall clock): 2026-09-23T03:00:00Z
//   - Relative to epoch: 1727058000 seconds since Unix epoch
//   - Relative to another event: "5 seconds after previous completion"

struct Timestamp {
    std::optional<std::chrono::system_clock::time_point> wall_time;      // CLOCK_REALTIME
    std::optional<std::chrono::steady_clock::time_point> monotonic_time; // CLOCK_MONOTONIC
    
    bool is_absolute() const { return wall_time.has_value(); }
    bool is_relative() const { return monotonic_time.has_value(); }
    bool is_monotonic() const { return monotonic_time.has_value(); }
};

// -----------------------------------------------------------------------------
// Duration
// -----------------------------------------------------------------------------
// An amount of elapsed time.
//
// Used for:
//   - Timeout calculations (operation may take at most 30 seconds)
//   - Retry delays (retry after 5 seconds)
//   - Execution measurements (took 4.2 seconds)

struct Duration {
    std::chrono::milliseconds value;
    
    constexpr Duration() : value(0) {}
    explicit constexpr Duration(std::chrono::milliseconds v) : value(v) {}
    
    template <typename Rep, typename Period>
    explicit Duration(const std::chrono::duration<Rep, Period>& d)
        : value(std::chrono::duration_cast<std::chrono::milliseconds>(d)) {}
    
    static constexpr Duration zero() { return Duration{0ms}; }
    static constexpr Duration from_seconds(int64_t s) { return Duration{s * 1s}; }
    static constexpr Duration from_minutes(int64_t m) { return Duration{m * 60s}; }
    static constexpr Duration from_hours(int64_t h) { return Duration{h * 3600s}; }
    
    int64_t count() const { return value.count(); }
    int64_t seconds() const { return value.count() / 1000; }
    int64_t minutes() const { return seconds() / 60; }
    int64_t hours() const { return minutes() / 60; }
    
    Duration& operator+=(Duration other) {
        value += other.value;
        return *this;
    }
    
    Duration& operator-=(Duration other) {
        value -= other.value;
        return *this;
    }
};

inline constexpr Duration operator""_ms(unsigned long long ms) { 
    return Duration{std::chrono::milliseconds(ms)}; 
}
inline constexpr Duration operator""_s(unsigned long long s) { 
    return Duration{std::chrono::seconds(s)}; 
}
inline constexpr Duration operator""_m(unsigned long long m) { 
    return Duration{std::chrono::minutes(m)}; 
}
inline constexpr Duration operator""_h(unsigned long long h) { 
    return Duration{std::chrono::hours(h)}; 
}

// -----------------------------------------------------------------------------
// Delay
// -----------------------------------------------------------------------------
// A postponement instruction - "wait before doing something".
//
// Distinct from Duration:
//   - Duration: measurement (how long did it take?)
//   - Delay: instruction (how long should we wait?)

struct Delay {
    Duration duration;
    ClockDomain clock = ClockDomain::kMonotonic;  // delays use monotonic to avoid wall-clock changes
    
    static constexpr Delay from_duration(Duration d) { return Delay{d, ClockDomain::kMonotonic}; }
    static constexpr Delay from_seconds(int64_t s) { 
        return Delay{Duration::from_seconds(s), ClockDomain::kMonotonic}; 
    }
};

// -----------------------------------------------------------------------------
// ScheduleKind
// -----------------------------------------------------------------------------
// The type of schedule specification.

enum class ScheduleKind {
    kOnce,          // Single execution at a specific absolute time
    kInterval,      // Recurring at fixed intervals (relative to previous completion or activation)
    kCron,          // Calendar-based schedule (cron-like syntax)
};

inline std::string_view to_string(ScheduleKind k) {
    switch (k) {
        case ScheduleKind::kOnce: return "once";
        case ScheduleKind::kInterval: return "interval";
        case ScheduleKind::kCron: return "cron";
    }
    return "unknown";
}

// -----------------------------------------------------------------------------
// Schedule
// -----------------------------------------------------------------------------
// A specification for when activation should occur.
//
// Distinct from Scheduler (the mechanism that realizes schedules).
// A Schedule is data, not a running process.
//
// Example:
//   Schedule {
//     kind: kOnce,
//     absolute_time: 2026-09-23T03:00:00Z
//     target_kind: "task",
//     target_id: "backup.verify"
//   }

struct Schedule {
    std::string id;                           // Unique identifier for this schedule
    
    ScheduleKind kind;
    
    // Timing specification
    std::optional<Timestamp> absolute_time;   // For kOnce - when to run once
    std::optional<Duration> interval;         // For kInterval - how often
    std::optional<std::string> cron_expr;     // For kCron - cron-like expression
    
    // Recurrence control
    std::optional<int32_t> max_executions;    // -1 = unlimited, 0 = none, >0 = count
    
    // Activation target (what to run)
    std::string target_kind;                  // "task", "workflow", etc.
    std::string target_id;                    // Identifier of what to activate
    
    bool enabled = true;                      // Is this schedule active?
    
    // Clock domain for interpretation
    ClockDomain clock_domain = ClockDomain::kWallClock;
};

// -----------------------------------------------------------------------------
// Deadline
// -----------------------------------------------------------------------------
// A temporal boundary - "must be completed by X time".
//
// Distinct from Timeout:
//   - Deadline: absolute point in time ("complete before 18:00")
//   - Timeout: relative duration ("operation may take at most 30 seconds")

struct Deadline {
    Timestamp timestamp;                      // The absolute deadline
    
    bool is_expired(Timestamp now) const {
        if (!now.is_absolute() || !timestamp.is_absolute()) return false;
        
        auto now_time = now.wall_time.value();
        auto deadline_time = timestamp.wall_time.value();
        
        return now_time > deadline_time;
    }
};

// -----------------------------------------------------------------------------
// Timeout
// -----------------------------------------------------------------------------
// Maximum duration allowed for an operation.
//
// Distinct from Deadline:
//   - Timeout: relative ("max 30 seconds")
//   - Deadline: absolute ("by 18:00")

struct Timeout {
    Duration max_duration;
    ClockDomain clock = ClockDomain::kMonotonic;  // Use monotonic to avoid wall-clock changes
    
    static constexpr Timeout from_duration(Duration d) { 
        return Timeout{d, ClockDomain::kMonotonic}; 
    }
    
    bool is_expired(Timestamp start_time, Timestamp now) const {
        if (!start_time.is_monotonic() || !now.is_monotonic()) return false;
        
        auto elapsed = now.monotonic_time.value() - start_time.monotonic_time.value();
        return Duration{elapsed} > max_duration;
    }
};

// -----------------------------------------------------------------------------
// Window
// -----------------------------------------------------------------------------
// A bounded temporal region for correlation/observation.
//
// Example:
//   "service failed 3 times within 5 minutes"
//   The "5 minutes" here is a window, not a Schedule.

struct Window {
    Duration duration;
    
    // For counting events within this window
    bool contains(Timestamp event_time, Timestamp reference_time) const {
        if (!event_time.is_monotonic() || !reference_time.is_monotonic()) return false;
        
        auto diff = reference_time.monotonic_time.value() - event_time.monotonic_time.value();
        return Duration{diff} <= duration && diff >= 0ms;
    }
};

// -----------------------------------------------------------------------------
// Recurrence
// -----------------------------------------------------------------------------
// Pattern of repeated activation.
//
// Can be:
//   - Fixed interval (every N units)
//   - Cron expression (specific times/days)
//   - Business rules (weekday mornings, excluding holidays)

struct Recurrence {
    std::vector<Duration> intervals;          // The recurrence interval(s)
    std::optional<Window> observation_window; // For rate limiting within windows
    
    bool is_eligible_at(Timestamp now, Timestamp last_activation) const {
        if (intervals.empty()) return false;
        
        auto diff = Duration{now.monotonic_time.value() - last_activation.monotonic_time.value()};
        return diff >= intervals[0];
    }
};

// -----------------------------------------------------------------------------
// TemporalMetadata
// -----------------------------------------------------------------------------
// Additional temporal information associated with entities.
//
// Not all entities need all of these; use what's semantically relevant.

struct TemporalMetadata {
    // Lifecycle timestamps (wall clock, for human reference)
    std::optional<Timestamp> created_at;
    std::optional<Timestamp> requested_at;
    std::optional<Timestamp> scheduled_for;
    
    // Activation timestamps
    std::optional<Timestamp> activated_at;     // When activation decision was made
    
    // Execution timestamps (can be wall or monotonic depending on need)
    std::optional<Timestamp> started_at;
    std::optional<Timestamp> last_progress_at; // For jam detection
    
    // Completion timestamps
    std::optional<Timestamp> completed_at;
    std::optional<Timestamp> verified_at;
    
    // Failure timestamps
    std::optional<Timestamp> failed_at;
    std::optional<Timestamp> cancelled_at;
    
    // Timings (durations - use monotonic)
    std::optional<Duration> execution_duration;
    std::optional<Duration> verification_duration;
    
    // Boundaries
    std::optional<Deadline> deadline;
    std::optional<Timeout> timeout;
};

// -----------------------------------------------------------------------------
// MissedActivationPolicy
// -----------------------------------------------------------------------------
// What to do when an activation was missed (e.g., machine was off).

enum class MissedActivationPolicy {
    kSkip,              // Skip the missed activation
    kRunOnceOnStart,    // Run once when system comes back up
    kReconcile,         // Try to reconcile desired state
    kExpire,            // Mark as expired/invalid
};

inline std::string_view to_string(MissedActivationPolicy p) {
    switch (p) {
        case MissedActivationPolicy::kSkip: return "skip";
        case MissedActivationPolicy::kRunOnceOnStart: return "run_once_on_start";
        case MissedActivationPolicy::kReconcile: return "reconcile";
        case MissedActivationPolicy::kExpire: return "expire";
    }
    return "unknown";
}

// -----------------------------------------------------------------------------
// OverlapPolicy
// -----------------------------------------------------------------------------
// What to do when the next activation occurs while previous work is still running.

enum class OverlapPolicy {
    kAllow,             // Allow overlapping executions
    kSkip,              // Skip this activation
    kQueue,             // Add to queue for later execution
    kCoalesce,          // Merge with pending (if applicable)
    kReplace,           // Replace current execution with new one
    kCancelPrevious,    // Cancel previous and start new
};

inline std::string_view to_string(OverlapPolicy p) {
    switch (p) {
        case OverlapPolicy::kAllow: return "allow";
        case OverlapPolicy::kSkip: return "skip";
        case OverlapPolicy::kQueue: return "queue";
        case OverlapPolicy::kCoalesce: return "coalesce";
        case OverlapPolicy::kReplace: return "replace";
        case OverlapPolicy::kCancelPrevious: return "cancel_previous";
    }
    return "unknown";
}

} // namespace rebuntu::core::time

// -----------------------------------------------------------------------------
// Standard hash specializations
// -----------------------------------------------------------------------------

namespace std {

template <>
struct hash<rebuntu::core::time::Duration> {
    size_t operator()(const rebuntu::core::time::Duration& d) const noexcept {
        return std::hash<int64_t>{}(d.value.count());
    }
};

} // namespace std