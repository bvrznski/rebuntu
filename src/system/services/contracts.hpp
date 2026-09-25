// rebuntu::system::services — Foundational Services Framework Contracts (Phase 5.0)
//
// This header establishes the foundational contracts for Rebuntu's service framework.
// It provides common abstractions that all Phase 5+ services can use without
// creating a parallel runtime or microservice platform.

#pragma once

namespace rebuntu { namespace system { namespace services {

enum class ServiceState {
    kCreated,
    kInitializing,
    kReady,
    kActive,
    kStopping,
    kStopped,
    kFailed,
};

struct ServiceStatus {
    ServiceState lifecycle;
    int work_state;
    int control_state;
    bool ready_to_accept_work;
    int health_state;
    int recovery_state;
};

struct Observation {
    const char* id;
    void* observed_at;
    const char* domain;
    const char* key;
    const char* value;
    const char* source;
    void* subject;
    bool is_authoritative;
    bool is_complete;
    long acquisition_duration_ms;
};

class EvidencePublisher {
public:
    virtual ~EvidencePublisher() = default;
    virtual void publish(const Observation& obs) = 0;
    virtual int subscribe(void* callback) = 0;
    virtual void unsubscribe(int id) = 0;
};

struct ServiceMetrics {
    unsigned long tasks_submitted;
    unsigned long tasks_completed;
    unsigned long tasks_failed;
    unsigned long queue_depth_current;
    unsigned long queue_depth_max_seen;
    unsigned long messages_dropped_newest;
    unsigned long messages_dropped_oldest;
    unsigned long send_blocked_count;
    unsigned long tasks_cancelled;
    long total_execution_time_ms;
    long avg_task_duration_ms;
    void* started_at;
    void* stopped_at;
};

enum class BackpressurePolicy {
    kBlock,
    kDropNewest,
    kDropOldest,
};

struct ServiceConfig {
    const char* service_id;
    unsigned int max_queue_size;
    BackpressurePolicy backpressure_policy;
    unsigned int max_concurrent_tasks;
    long default_task_timeout_ms;
    long health_check_interval_ms;
    bool cancel_pending_on_stop;
    const char* native_mechanism;
};

struct ServiceStartResult {
    enum class Status { kSuccess, kFailure, kUnknown, kCancelled } status;
    const char* error_message;
    long startup_time_ms;
};

struct ServiceStopResult {
    enum class Status { kSuccess, kFailure, kTimeout, kUnknown } status;
    bool graceful_completed;
    bool force_terminated;
    long shutdown_time_ms;
    long timeout_remaining_ms;
    unsigned int pending_tasks_at_stop;
};

class ServiceBase {
public:
    explicit ServiceBase(ServiceConfig config);
    virtual ~ServiceBase() = default;
    virtual ServiceStartResult start();
    virtual ServiceStopResult stop(long timeout_ms);
    ServiceState state() const { return state_; }
    ServiceStatus status() const;
    ServiceMetrics metrics() const;
    const ServiceConfig& config() const { return config_; }
    virtual EvidencePublisher* evidence_publisher();
protected:
    void set_state(ServiceState s) { state_ = s; }
    void mark_ready() {}
    void mark_failed(const char*) {}
    virtual void publish_observation(const Observation&) {}
private:
    ServiceConfig config_;
    ServiceState state_{ServiceState::kCreated};
};

class ServiceBuilder {
public:
    ServiceBuilder();
    ServiceBuilder& set_service_id(const char* id);
    ServiceBuilder& set_max_queue_size(unsigned int size);
    ServiceBuilder& set_backpressure_policy(BackpressurePolicy p);
    ServiceBuilder& set_max_concurrent_tasks(unsigned int n);
    ServiceBuilder& set_default_task_timeout(long ms);
    ServiceBuilder& set_health_check_interval(long ms);
    ServiceBuilder& set_cancel_pending_on_stop(bool b);
    ServiceBuilder& set_native_mechanism(const char* m);
    void* build();
private:
    ServiceConfig config_;
};

void* make_service(const char* id);

}}}  // namespace rebuntu::system::services