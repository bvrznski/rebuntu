// Unit tests for rebuntu::runtime contracts (Phase 0.2).
// Minimal, dependency-free assertion harness.
#include <runtime/contracts.hpp>

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
    using rebuntu::runtime::LifecycleState;
    using rebuntu::runtime::WorkState;
    using rebuntu::runtime::ControlState;
    using rebuntu::runtime::ReadinessState;
    using rebuntu::runtime::HealthState;
    using rebuntu::runtime::RecoveryState;
    using rebuntu::runtime::to_string;
    
    // Lifecycle state string conversions
    CHECK(to_string(LifecycleState::kCreated) == "created");
    CHECK(to_string(LifecycleState::kInitializing) == "initializing");
    CHECK(to_string(LifecycleState::kReady) == "ready");
    CHECK(to_string(LifecycleState::kActive) == "active");
    CHECK(to_string(LifecycleState::kStopping) == "stopping");
    CHECK(to_string(LifecycleState::kStopped) == "stopped");
    CHECK(to_string(LifecycleState::kFailed) == "failed");
    
    // Work state string conversions (Phase 0.14: added kJammed)
    CHECK(to_string(WorkState::kIdle) == "idle");
    CHECK(to_string(WorkState::kJammed) == "jammed");  // jammed detection
    CHECK(to_string(WorkState::kProcessing) == "processing");
    CHECK(to_string(WorkState::kWaiting) == "waiting");
    CHECK(to_string(WorkState::kPaused) == "paused");

    // Control state string conversions (Phase 0.14)
    CHECK(to_string(ControlState::kEnabled) == "enabled");
    CHECK(to_string(ControlState::kDisabled) == "disabled");
    CHECK(to_string(ControlState::kPaused) == "paused_admin");
    CHECK(to_string(ControlState::kFrozen) == "frozen");
    CHECK(to_string(ControlState::kLocked) == "locked");

    // Readiness state string conversions (Phase 0.14)
    CHECK(to_string(ReadinessState::kReady) == "ready");
    CHECK(to_string(ReadinessState::kNotReady) == "not_ready");

    // Health state string conversions
    CHECK(to_string(HealthState::kUnknown) == "unknown");
    CHECK(to_string(HealthState::kHealthy) == "healthy");
    CHECK(to_string(HealthState::kDegraded) == "degraded");
    CHECK(to_string(HealthState::kUnhealthy) == "unhealthy");
    
    // Recovery state string conversions
    CHECK(to_string(RecoveryState::kNone) == "none");
    CHECK(to_string(RecoveryState::kRetrying) == "retrying");
    CHECK(to_string(RecoveryState::kRollingBack) == "rolling_back");
    CHECK(to_string(RecoveryState::kRestoring) == "restoring");
    CHECK(to_string(RecoveryState::kReparing) == "repairing");
    CHECK(to_string(RecoveryState::kFailingOver) == "failing_over");
    
    // Request construction
    rebuntu::runtime::Request req;
    req.id = "test-001";
    req.operation = "filesystem.copy";
    req.parameters.emplace_back("source", "/tmp/a.txt");
    req.parameters.emplace_back("destination", "/tmp/b.txt");
    req.timeout = std::chrono::milliseconds(5000);
    req.priority = 5;
    CHECK(req.id == "test-001");
    CHECK(req.operation == "filesystem.copy");
    
    // Event construction
    rebuntu::runtime::Event evt;
    evt.id = "evt-001";
    evt.source = "systemd";
    evt.type = "service.state_changed";
    auto now = std::chrono::system_clock::now();
    evt.occurred_at = now;
    evt.is_observable = true;
    CHECK(evt.id == "evt-001");
    CHECK(evt.source == "systemd");
    
    // Signal construction
    rebuntu::runtime::Signal sig;
    sig.type = rebuntu::runtime::SignalType::kCancel;
    sig.target = "job-123";
    CHECK(sig.type == rebuntu::runtime::SignalType::kCancel);
    CHECK(sig.target.has_value());
    CHECK(*sig.target == "job-123");
    
    // Trigger construction
    rebuntu::runtime::Trigger trig;
    trig.id = "trig-001";
    trig.source_event_id = "evt-001";
    trig.activation_kind = "task";
    trig.activation_target = "backup-task";
    CHECK(trig.id == "trig-001");
    CHECK(trig.activation_kind == "task");
    
    // Condition construction
    using rebuntu::runtime::Condition;
    using rebuntu::runtime::ConditionOperator;
    using rebuntu::runtime::ConditionOperand;
    
    Condition cond;
    cond.lhs.path = "service.active";
    cond.op = ConditionOperator::kEquals;
    ConditionOperand rhs;
    rhs.path = "true";
    cond.rhs_value = rhs;
    CHECK(cond.lhs.path == "service.active");
    CHECK(cond.op == ConditionOperator::kEquals);
    
    // EntityState construction (Phase 0.14: all 6 dimensions)
    rebuntu::runtime::EntityState state;
    state.lifecycle = LifecycleState::kReady;
    state.work = WorkState::kJammed;  // jammed process
    state.control = ControlState::kEnabled;
    state.readiness = ReadinessState::kNotReady;  // not ready yet
    state.health = HealthState::kHealthy;
    state.recovery = RecoveryState::kRetrying;
    
    CHECK(state.ready() == false);  // not_ready fails readiness predicate
    
    // Test degraded health affects readiness
    state.readiness = ReadinessState::kReady;
    state.health = HealthState::kDegraded;
    CHECK(state.ready() == false);  // degraded health fails readiness

    // Test jammed work state is set correctly
    state.work = WorkState::kJammed;
    
    // ExecutionIds construction
    auto ids1 = rebuntu::runtime::ExecutionIds::make_root("req-001");
    CHECK(ids1.request_id == "req-001");
    CHECK(ids1.execution_id == "req-001");
    
    auto ids2 = rebuntu::runtime::ExecutionIds::make_child(ids1, "exec-002");
    CHECK(ids2.request_id == "req-001");  // inherited
    CHECK(ids2.parent_execution_id.has_value());
    CHECK(*ids2.parent_execution_id == "req-001");
    
    // Retry policy tests
    using rebuntu::runtime::RetryPolicy;
    using rebuntu::core::Error;
    
    RetryPolicy retry_policy;
    retry_policy.max_attempts = 3;
    retry_policy.initial_delay = std::chrono::milliseconds(100);
    retry_policy.exponential_backoff = true;
    retry_policy.backoff_multiplier = 2.0;
    
    // Should retry on first and second attempt
    CHECK(retry_policy.should_retry(1, nullptr) == true);
    CHECK(retry_policy.should_retry(2, nullptr) == true);
    CHECK(retry_policy.should_retry(3, nullptr) == false);  // max reached
    
    // Compute delays
    auto d1 = retry_policy.compute_delay(1);
    auto d2 = retry_policy.compute_delay(2);  // should be 200ms (100 * 2)
    CHECK(d1.count() == 100);
    CHECK(d2.count() == 200);
    
    // Schedule construction
    using rebuntu::runtime::Schedule;
    using rebuntu::runtime::ScheduleKind;
    
    Schedule sched;
    sched.id = "sched-001";
    sched.kind = ScheduleKind::kInterval;
    sched.interval = std::chrono::minutes(5);
    sched.target_kind = "task";
    sched.target_id = "health-check";
    CHECK(sched.id == "sched-001");
    CHECK(sched.kind == ScheduleKind::kInterval);
    
    // Timeout policy tests
    using rebuntu::runtime::TimeoutPolicy;
    
    TimeoutPolicy tp;
    tp.default_timeout = std::chrono::seconds(30);
    tp.operation_timeout = std::chrono::seconds(15);
    tp.verification_timeout = std::chrono::seconds(10);
    CHECK(tp.has_operation_timeout() == true);
    CHECK(tp.has_verification_timeout() == true);
    
    // WorkPriority string conversions
    using rebuntu::runtime::WorkPriority;
    using rebuntu::runtime::to_string;
    CHECK(to_string(WorkPriority::kCritical) == "critical");
    CHECK(to_string(WorkPriority::kHigh) == "high");
    CHECK(to_string(WorkPriority::kNormal) == "normal");
    CHECK(to_string(WorkPriority::kLow) == "low");
    CHECK(to_string(WorkPriority::kBackground) == "background");
    
    // RequestStatus string conversions
    using rebuntu::runtime::RequestStatus;
    CHECK(to_string(RequestStatus::kReceived) == "received");
    CHECK(to_string(RequestStatus::kValidating) == "validating");
    CHECK(to_string(RequestStatus::kAuthorized) == "authorized");
    CHECK(to_string(RequestStatus::kDispatched) == "dispatched");
    CHECK(to_string(RequestStatus::kExecuting) == "executing");
    CHECK(to_string(RequestStatus::kVerifying) == "verifying");
    CHECK(to_string(RequestStatus::kCompleted) == "completed");
    CHECK(to_string(RequestStatus::kVerified) == "verified");
    CHECK(to_string(RequestStatus::kCancelled) == "cancelled");
    CHECK(to_string(RequestStatus::kTimedOut) == "timed_out");
    CHECK(to_string(RequestStatus::kFailed) == "failed");
    
    if (g_failures != 0) {
        std::cerr << g_failures << " check(s) FAILED\n";
        return 1;
    }
    std::cout << "test_runtime_contracts: OK\n";
    return 0;
}