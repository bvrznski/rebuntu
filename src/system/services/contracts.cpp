// rebuntu::system::services — Foundational Services Framework Implementation (Phase 5.0)
//
// This implements the contracts defined in contracts.hpp.

#include <system/services/contracts.hpp>

namespace rebuntu { namespace system { namespace services {

ServiceBase::ServiceBase(ServiceConfig config) : config_(config), state_{ServiceState::kCreated} {}

ServiceStartResult ServiceBase::start() {
    ServiceStartResult result;
    result.status = ServiceStartResult::Status::kSuccess;
    return result;
}

ServiceStopResult ServiceBase::stop(long timeout_ms) {
    (void)timeout_ms;
    ServiceStopResult result;
    result.status = ServiceStopResult::Status::kSuccess;
    return result;
}

ServiceStatus ServiceBase::status() const {
    ServiceStatus status;
    status.lifecycle = state_;
    status.work_state = 0;
    status.control_state = 0;
    status.ready_to_accept_work = true;
    status.health_state = 0;
    status.recovery_state = 0;
    return status;
}

ServiceMetrics ServiceBase::metrics() const {
    ServiceMetrics m{};
    return m;
}

EvidencePublisher* ServiceBase::evidence_publisher() {
    return nullptr;
}

ServiceBuilder::ServiceBuilder() {
    config_.service_id = "";
    config_.max_queue_size = 1024;
    config_.backpressure_policy = BackpressurePolicy::kDropNewest;
    config_.max_concurrent_tasks = 32;
    config_.default_task_timeout_ms = -1;
    config_.health_check_interval_ms = 1000;
    config_.cancel_pending_on_stop = true;
    config_.native_mechanism = nullptr;
}

ServiceBuilder& ServiceBuilder::set_service_id(const char* id) {
    config_.service_id = id;
    return *this;
}

ServiceBuilder& ServiceBuilder::set_max_queue_size(unsigned int size) {
    config_.max_queue_size = size;
    return *this;
}

ServiceBuilder& ServiceBuilder::set_backpressure_policy(BackpressurePolicy p) {
    config_.backpressure_policy = p;
    return *this;
}

ServiceBuilder& ServiceBuilder::set_max_concurrent_tasks(unsigned int n) {
    config_.max_concurrent_tasks = n;
    return *this;
}

ServiceBuilder& ServiceBuilder::set_default_task_timeout(long ms) {
    config_.default_task_timeout_ms = ms;
    return *this;
}

ServiceBuilder& ServiceBuilder::set_health_check_interval(long ms) {
    config_.health_check_interval_ms = ms;
    return *this;
}

ServiceBuilder& ServiceBuilder::set_cancel_pending_on_stop(bool b) {
    config_.cancel_pending_on_stop = b;
    return *this;
}

ServiceBuilder& ServiceBuilder::set_native_mechanism(const char* m) {
    config_.native_mechanism = m;
    return *this;
}

void* ServiceBuilder::build() {
    return new ServiceBase(config_);
}

void* make_service(const char* id) {
    ServiceBuilder builder;
    builder.set_service_id(id);
    return builder.build();
}

}}}  // namespace rebuntu::system::services