// Unit tests for rebuntu::runtime::work (Phase 0.8).
#include <runtime/work.hpp>

#include <cstddef>
#include <iostream>
#include <string>
#include <chrono>

namespace {
int g_failures = 0;
#define CHECK(cond)                                                              \
    do {                                                                         \
        if (!(cond)) {                                                           \
            std::cerr << "CHECK failed: " << #cond << " (line " << __LINE__      \
                      << ")\n";                                                  \
            ++g_failures;                                                        \
        }                                                                        \
    } while (0)
}  // namespace

int main() {
    using rebuntu::runtime::work::TaskId;
    using rebuntu::runtime::work::JobId;
    using rebuntu::runtime::work::ExecutionId;
    using rebuntu::runtime::work::AttemptNumber;
    using rebuntu::runtime::work::TaskState;
    using rebuntu::runtime::work::JobState;
    using rebuntu::runtime::work::AttemptState;
    using rebuntu::runtime::work::CancellationReason;
    using rebuntu::runtime::work::to_string;

    // TaskId tests
    TaskId tid1{"task-001"};
    CHECK(tid1.value == "task-001");

    TaskId tid2{"task-001"};
    TaskId tid3{"task-002"};
    CHECK(tid1 == tid2);
    CHECK(!(tid1 == tid3));

    // JobId tests
    JobId jid1{"job-001"};
    CHECK(jid1.value == "job-001");

    // ExecutionId tests
    ExecutionId eid1{"exec-001"};
    CHECK(eid1.value == "exec-001");

    // AttemptNumber tests
    AttemptNumber an1{1};
    AttemptNumber an2{1};
    AttemptNumber an3{2};
    CHECK(an1 == an2);
    CHECK(an1 != an3);

    // TaskState string conversions
    CHECK(to_string(TaskState::kCreated) == "created");
    CHECK(to_string(TaskState::kReady) == "ready");
    CHECK(to_string(TaskState::kCancelled) == "cancelled");
    CHECK(to_string(TaskState::kDeprecated) == "deprecated");

    // JobState string conversions
    CHECK(to_string(JobState::kCreated) == "created");
    CHECK(to_string(JobState::kQueued) == "queued");
    CHECK(to_string(JobState::kReady) == "ready");
    CHECK(to_string(JobState::kRunning) == "running");
    CHECK(to_string(JobState::kCompleted) == "completed");
    CHECK(to_string(JobState::kFailed) == "failed");
    CHECK(to_string(JobState::kCancelled) == "cancelled");

    // AttemptState string conversions
    CHECK(to_string(AttemptState::kCreated) == "created");
    CHECK(to_string(AttemptState::kStarting) == "starting");
    CHECK(to_string(AttemptState::kRunning) == "running");
    CHECK(to_string(AttemptState::kFinishing) == "finishing");
    CHECK(to_string(AttemptState::kFinished) == "finished");

    // CancellationReason string conversions
    CHECK(to_string(CancellationReason::kExplicit) == "explicit");
    CHECK(to_string(CancellationReason::kTimeout) == "timeout");
    CHECK(to_string(CancellationReason::kDependencyFailed) == "dependency_failed");
    CHECK(to_string(CancellationReason::kResourceExhausted) == "resource_exhausted");

    // Task structure tests
    using rebuntu::runtime::work::Task;
    Task task;
    task.id.value = "task-001";
    task.title = "Test task";
    task.description = "A test task for verification";
    task.unit_id = "test.unit";
    CHECK(task.id.value == "task-001");
    CHECK(task.title == "Test task");

    // Job structure tests
    using rebuntu::runtime::work::Job;
    Job job;
    job.id.value = "job-001";
    job.task_id = "task-001";
    job.state = JobState::kCreated;
    job.max_attempts = AttemptNumber{3};
    CHECK(job.id.value == "job-001");
    CHECK(job.task_id == "task-001");
    CHECK(job.max_attempts.has_value());
    CHECK(job.max_attempts.value().value == 3);

    // Attempt structure tests
    using rebuntu::runtime::work::Attempt;
    Attempt attempt;
    attempt.id.value = "exec-001";
    attempt.job_id.value = "job-001";
    attempt.number.value = 1;
    attempt.state = AttemptState::kRunning;
    CHECK(attempt.id.value == "exec-001");
    CHECK(attempt.number.value == 1);

    // Hash tests
    using std::hash;
    hash<TaskId> task_hasher;
    hash<JobId> job_hasher;
    
    CHECK(task_hasher(tid1) == task_hasher(tid2));
    CHECK(job_hasher(jid1) > 0);

    if (g_failures != 0) {
        std::cerr << g_failures << " check(s) FAILED\n";
        return 1;
    }
    std::cout << "test_work: OK\n";
    return 0;
}
