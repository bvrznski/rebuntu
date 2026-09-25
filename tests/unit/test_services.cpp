// rebuntu::system::services - Unit Tests (Phase 5.0)
//
// Tests for the Foundational Services Framework contracts.

#include <gtest/gtest.h>
#include <system/services/contracts.hpp>

using namespace rebuntu::system::services;

// ServiceState enum conversion tests
TEST(ServiceState, ToString) {
    EXPECT_EQ(service_state_to_string(ServiceState::kCreated), "created");
    EXPECT_EQ(service_state_to_string(ServiceState::kInitializing), "initializing");
    EXPECT_EQ(service_state_to_string(ServiceState::kReady), "ready");
    EXPECT_EQ(service_state_to_string(ServiceState::kActive), "active");
    EXPECT_EQ(service_state_to_string(ServiceState::kStopping), "stopping");
    EXPECT_EQ(service_state_to_string(ServiceState::kStopped), "stopped");
    EXPECT_EQ(service_state_to_string(ServiceState::kFailed), "failed");
}

// BackpressurePolicy enum conversion tests
TEST(BackpressurePolicy, ToString) {
    EXPECT_EQ(backpressure_policy_to_string(BackpressurePolicy::kBlock), "block");
    EXPECT_EQ(backpressure_policy_to_string(BackpressurePolicy::kDropNewest), "drop_newest");
    EXPECT_EQ(backpressure_policy_to_string(BackpressurePolicy::kDropOldest), "drop_oldest");
}

// ServiceBase default state tests
TEST(ServiceBase, DefaultState) {
    ServiceConfig config{};
    config.service_id = "test.service";
    
    ServiceBase base(config);
    EXPECT_EQ(base.state(), ServiceState::kCreated);
    EXPECT_EQ(std::string(base.config().service_id), "test.service");
}

// ServiceBase start/stop tests
TEST(ServiceBase, StartStop) {
    ServiceConfig config{};
    config.service_id = "test.service";
    
    ServiceBase base(config);
    
    auto result = base.start();
    EXPECT_EQ(result.status, ServiceStartResult::Status::kSuccess);
    
    auto stop_result = base.stop(1000);
    EXPECT_EQ(stop_result.status, ServiceStopResult::Status::kSuccess);
}

// ServiceBuilder fluent interface tests
TEST(ServiceBuilder, FluentInterface) {
    auto base = ServiceBuilder{}
        .set_service_id("test.builder")
        .set_max_queue_size(2048)
        .set_backpressure_policy(BackpressurePolicy::kDropOldest)
        .set_max_concurrent_tasks(64)
        .build();
    
    ASSERT_NE(base, nullptr);
    delete static_cast<ServiceBase*>(base);
}

// make_service factory tests
TEST(ServiceFactory, MakeService) {
    auto base = make_service("test.factory");
    ASSERT_NE(base, nullptr);
    delete static_cast<ServiceBase*>(base);
}

// ServiceStatus derived predicates tests
TEST(ServiceStatus, DerivedPredicates) {
    ServiceStatus status{};
    status.lifecycle = ServiceState::kActive;
    status.ready_to_accept_work = true;
    
    EXPECT_EQ(status.active(), true);
    EXPECT_EQ(status.ready(), true);
    EXPECT_EQ(status.unavailable(), false);
}

// ServiceStatus inactive when not ready
TEST(ServiceStatus, NotReady) {
    ServiceStatus status{};
    status.lifecycle = ServiceState::kActive;
    status.ready_to_accept_work = false;
    
    EXPECT_EQ(status.ready(), false);
}