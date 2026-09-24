# time/ — Time and Duration Helpers

## Purpose

Shell-native time utilities for timestamps, duration calculation, formatting,
and deadline management.

## What Belongs Here

| Category | Description |
|----------|-------------|
| Timestamps | Current time in various formats (wall clock) |
| Duration calculation | Elapsed time between two points |
| Time formatting | Human-readable duration display |
| Deadline checks | Checking if a deadline has passed |

## What Does NOT Belong Here

| Category | Where to Go |
|----------|-------------|
| Scheduling | systemd timers or Rebuntu schedules |
| Wall clock reading | Use `date` directly for simple cases |
| Monotonic timing | Consider using `/proc/uptime` or clock_gettime() |

## Examples

* `rebuntu_time_now()` — get current time in nanoseconds
* `rebuntu_time_elapsed()` — calculate elapsed milliseconds
* `rebuntu_time_format()` — format duration as string (e.g., "2m30s")
* `rebuntu_time_deadline_passed()` — check if deadline exceeded

## Dependencies

Uses native Linux utilities:
* `/proc/uptime` for high-resolution monotonic time
* `date +%s%N` or `date +%s000` for wall clock fallback

## Safety Classification

| Class | Description |
|-------|-------------|
| PURE | Time reading and calculations without mutation |

## Pipeline Semantics

* stdout: Timestamp, duration, or formatted time string
* stderr: Error messages on failure (rare)
* Exit status: 0 for success

## Notes

Time utilities use nanosecond precision internally. When comparing times,
ensure consistent units (nanoseconds vs milliseconds) are used throughout.