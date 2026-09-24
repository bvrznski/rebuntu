#pragma once

#include <runtime/contracts.hpp>
#include <chrono>
#include <optional>
#include <string>
#include <vector>

namespace rebuntu::runtime::work {

enum class ExecutionMode {
    kInline, kThread, kSubprocess, kSystemdUnit, kDBus, kUnixSocket
};

inline std::string to_string(ExecutionMode m) {
    switch (m) {
        case ExecutionMode::kInline: return "inline";
        case ExecutionMode::kThread: return "thread";
        case ExecutionMode::kSubprocess: return "subprocess";
        case ExecutionMode::kSystemdUnit: return "systemd-unit";
        case ExecutionMode::kDBus: return "dbus";
        case ExecutionMode::kUnixSocket: return "unix-socket";
    }
    return "unknown";
}

struct TaskId { std::string value; explicit operator std::string() const { return value; } };
inline bool operator==(const TaskId& a, const TaskId& b) { return a.value == b.value; }
inline bool operator!=(const TaskId& a, const TaskId& b) { return !(a == b); }

struct JobId { std::string value; explicit operator std::string() const { return value; } };
inline bool operator==(const JobId& a, const JobId& b) { return a.value == b.value; }
inline bool operator!=(const JobId& a, const JobId& b) { return !(a == b); }

struct ExecutionId { std::string value; explicit operator std::string() const { return value; } };
inline bool operator==(const ExecutionId& a, const ExecutionId& b) { return a.value == b.value; }
inline bool operator!=(const ExecutionId& a, const ExecutionId& b) { return !(a == b); }

struct AttemptNumber { int value; explicit operator int() const { return value; } };
inline bool operator==(const AttemptNumber& a, const AttemptNumber& b) { return a.value == b.value; }
inline bool operator!=(const AttemptNumber& a, const AttemptNumber& b) { return !(a == b); }

enum class TaskState { kCreated, kReady, kCancelled, kDeprecated };
inline std::string to_string(TaskState s) {
    switch (s) {
        case TaskState::kCreated: return "created";
        case TaskState::kReady: return "ready";
        case TaskState::kCancelled: return "cancelled";
        case TaskState::kDeprecated: return "deprecated";
    }
    return "unknown";
}

enum class JobState { kCreated, kQueued, kReady, kRunning, kCompleted, kFailed, kCancelled };
inline std::string to_string(JobState s) {
    switch (s) {
        case JobState::kCreated: return "created";
        case JobState::kQueued: return "queued";
        case JobState::kReady: return "ready";
        case JobState::kRunning: return "running";
        case JobState::kCompleted: return "completed";
        case JobState::kFailed: return "failed";
        case JobState::kCancelled: return "cancelled";
    }
    return "unknown";
}

enum class AttemptState { kCreated, kStarting, kRunning, kFinishing, kFinished };
inline std::string to_string(AttemptState s) {
    switch (s) {
        case AttemptState::kCreated: return "created";
        case AttemptState::kStarting: return "starting";
        case AttemptState::kRunning: return "running";
        case AttemptState::kFinishing: return "finishing";
        case AttemptState::kFinished: return "finished";
    }
    return "unknown";
}

enum class CancellationReason { kExplicit, kTimeout, kDependencyFailed, kResourceExhausted };
inline std::string to_string(CancellationReason r) {
    switch (r) {
        case CancellationReason::kExplicit: return "explicit";
        case CancellationReason::kTimeout: return "timeout";
        case CancellationReason::kDependencyFailed: return "dependency_failed";
        case CancellationReason::kResourceExhausted: return "resource_exhausted";
    }
    return "unknown";
}

struct Task {
    TaskId id;
    std::string title;
    std::string description;
    std::string unit_id;
    ExecutionMode mode = ExecutionMode::kInline;
    std::vector<std::string> required_parameters;
    std::optional<std::string> output_schema;
    std::chrono::system_clock::time_point created_at;
    TaskState state = TaskState::kCreated;
};

struct Job {
    JobId id;
    std::string task_id;
    std::chrono::system_clock::time_point created_at;
    std::vector<std::pair<std::string, std::string>> parameters;
    JobState state = JobState::kCreated;
    std::optional<AttemptNumber> max_attempts{1};
    runtime::RetryPolicy retry_policy;
    runtime::TimeoutPolicy timeout_policy;
    runtime::WorkPriority priority = runtime::WorkPriority::kNormal;
    std::optional<CancellationReason> cancellation_reason;
    std::vector<ExecutionId> attempt_ids;
};

struct Attempt {
    ExecutionId id;
    JobId job_id;
    AttemptNumber number;
    std::chrono::system_clock::time_point started_at;
    std::optional<std::chrono::system_clock::time_point> finished_at;
    AttemptState state = AttemptState::kCreated;
    ExecutionMode mode = ExecutionMode::kInline;
    std::optional<int32_t> pid;
    std::optional<rebuntu::core::Outcome> outcome;
};

struct TaskInstance {
    TaskId task_id;
    std::vector<std::pair<std::string, std::string>> parameters;
    JobId job_id;
    ExecutionId execution_id;
};

struct ExecutionRecord {
    ExecutionId id;
    TaskId task_id;
    JobId job_id;
    AttemptNumber attempt_number;
    std::chrono::system_clock::time_point started_at;
    std::optional<std::chrono::system_clock::time_point> completed_at;
    ExecutionMode mode = ExecutionMode::kInline;
    std::optional<int32_t> pid;
    std::string executor_id;
    rebuntu::core::Outcome outcome;
};

struct AttemptResult {
    ExecutionId execution_id;
    AttemptNumber number;
    bool is_last_attempt;
    rebuntu::core::Outcome outcome;
    std::optional<std::chrono::milliseconds> preparation_duration;
    std::optional<std::chrono::milliseconds> execution_duration;
    std::optional<std::chrono::milliseconds> verification_duration;
};

struct JobSummary {
    JobId id;
    std::string task_id;
    rebuntu::runtime::WorkState work_state = rebuntu::runtime::WorkState::kIdle;
    rebuntu::runtime::HealthState health_state = rebuntu::runtime::HealthState::kUnknown;
    JobState state = JobState::kCreated;
    int attempts_total = 0;
    int attempts_completed = 0;
    int attempts_pending = 0;
    std::chrono::system_clock::time_point created_at;
    std::optional<std::chrono::system_clock::time_point> started_at;
    std::optional<std::chrono::system_clock::time_point> completed_at;
    std::optional<rebuntu::core::Outcome> final_outcome;
};

}

namespace std {
template <> struct hash<rebuntu::runtime::work::TaskId> { size_t operator()(const rebuntu::runtime::work::TaskId& id) const noexcept { return std::hash<std::string>{}(id.value); } };
template <> struct hash<rebuntu::runtime::work::JobId> { size_t operator()(const rebuntu::runtime::work::JobId& id) const noexcept { return std::hash<std::string>{}(id.value); } };
template <> struct hash<rebuntu::runtime::work::ExecutionId> { size_t operator()(const rebuntu::runtime::work::ExecutionId& id) const noexcept { return std::hash<std::string>{}(id.value); } };
}