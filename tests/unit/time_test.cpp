// rebuntu::core::time - Unit Tests (Phase 0.9)
//
// Tests for the temporal primitives defined in src/core/time/types.hpp

#include <gtest/gtest.h>
#include <core/time/types.hpp>

using namespace rebuntu::core::time;

// Duration tests
TEST(Duration, Construction) {
    auto d1 = Duration{5s};
    EXPECT_EQ(d1.seconds(), 5);
    
    auto d2 = Duration::from_minutes(2);
    EXPECT_EQ(d2.minutes(), 2);
    
    auto d3 = Duration::zero();
    EXPECT_EQ(d3.count(), 0);
}

TEST(Duration, Operators) {
    auto d1 = 5s;
    auto d2 = 3s;
    
    auto sum = d1 + d2;
    EXPECT_EQ(sum.seconds(), 8);
    
    auto diff = d1 - d2;
    EXPECT_EQ(diff.seconds(), 2);
}

TEST(Duration, LiteralOperators) {
    using namespace std::literals;
    
    auto d1 = 5ms;
    EXPECT_EQ(d1.count(), 5);
    
    auto d2 = 3s;
    EXPECT_EQ(d2.count(), 3000);
}

// Timestamp tests
TEST(Timestamp, AbsoluteAndRelative) {
    Timestamp abs_ts{.wall_time = std::chrono::system_clock::now()};
    EXPECT_TRUE(abs_ts.is_absolute());
    EXPECT_FALSE(abs_ts.is_relative());
    
    Timestamp rel_ts{.monotonic_time = std::chrono::steady_clock::now()};
    EXPECT_TRUE(rel_ts.is_monotonic());
    EXPECT_TRUE(rel_ts.is_relative());
}

// Schedule tests
TEST(Schedule, Construction) {
    Schedule schedule{
        .id = "daily-backup",
        .kind = ScheduleKind::kCron,
        .cron_expr = "0 3 * * *",
        .target_kind = "task",
        .target_id = "backup.verify",
        .enabled = true
    };
    
    EXPECT_EQ(schedule.id, "daily-backup");
    EXPECT_EQ(to_string(schedule.kind), "cron");
    EXPECT_TRUE(schedule.enabled);
}

TEST(Schedule, IntervalSchedule) {
    Schedule schedule{
        .id = "every-5-minutes",
        .kind = ScheduleKind::kInterval,
        .interval = 5min
    };
    
    EXPECT_EQ(to_string(schedule.kind), "interval");
    ASSERT_TRUE(schedule.interval.has_value());
    EXPECT_EQ(schedule.interval->minutes(), 5);
}

// Deadline tests
TEST(Deadline, Expiration) {
    auto now = Timestamp{.wall_time = std::chrono::system_clock::now()};
    auto future = Timestamp{
        .wall_time = std::chrono::system_clock::now() + 1h
    };
    
    Deadline deadline{.timestamp = future};
    
    EXPECT_FALSE(deadline.is_expired(now));
}

// Timeout tests
TEST(Timeout, Construction) {
    Timeout t1 = Timeout::from_duration(30s);
    EXPECT_EQ(t1.max_duration.seconds(), 30);
}

// Window tests
TEST(Window, Contains) {
    auto ref_time = Timestamp{.monotonic_time = std::chrono::steady_clock::now()};
    auto event_time = Timestamp{
        .monotonic_time = std::chrono::steady_clock::now() - 2s
    };
    
    Window w{5s};
    EXPECT_TRUE(w.contains(event_time, ref_time));
}

// MissedActivationPolicy tests
TEST(MissedActivationPolicy, ToString) {
    EXPECT_EQ(to_string(MissedActivationPolicy::kSkip), "skip");
    EXPECT_EQ(to_string(MissedActivationPolicy::kRunOnceOnStart), "run_once_on_start");
    EXPECT_EQ(to_string(MissedActivationPolicy::kReconcile), "reconcile");
    EXPECT_EQ(to_string(MissedActivationPolicy::kExpire), "expire");
}

// OverlapPolicy tests
TEST(OverlapPolicy, ToString) {
    EXPECT_EQ(to_string(OverlapPolicy::kAllow), "allow");
    EXPECT_EQ(to_string(OverlapPolicy::kSkip), "skip");
    EXPECT_EQ(to_string(OverlapPolicy::kQueue), "queue");
    EXPECT_EQ(to_string(OverlapPolicy::kCancelPrevious), "cancel_previous");
}

// ClockDomain tests
TEST(ClockDomain, ToString) {
    EXPECT_EQ(to_string(ClockDomain::kWallClock), "wall_clock");
    EXPECT_EQ(to_string(ClockDomain::kMonotonic), "monotonic");
    EXPECT_EQ(to_string(ClockDomain::kBootTime), "boot_time");
}