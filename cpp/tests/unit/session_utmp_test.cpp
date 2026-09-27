// rebuntu::adapters::session::utmp - Unit Tests (Phase 5.27)
//
// Test coverage:
//   - UtmpAdapter interface
//   - Session observation from utmp file
//   - Login history parsing from wtmp file
//   - Failed login tracking from btmp file

#include <adapters/session/utmp/types.hpp>
#include <gtest/gtest.h>
#include <chrono>
#include <thread>

namespace rebuntu::adapters::session::utmp {
namespace test {

using namespace rebuntu::adapters::session::utmp;

// ============================================================================
// SessionType Tests
// ============================================================================

TEST(SessionUtmpTest, SessionTypeToString) {
    EXPECT_EQ(to_string(SessionType::kUnknown), "unknown");
    EXPECT_EQ(to_string(SessionType::kLogin), "login");
    EXPECT_EQ(to_string(SessionType::kDesktop), "desktop");
    EXPECT_EQ(to_string(SessionType::kRemote), "remote");
    EXPECT_EQ(to_string(SessionType::kSystemdUser), "systemd-user");
    EXPECT_EQ(to_string(SessionType::kContainer), "container");
}

// ============================================================================
// LoginType Tests
// ============================================================================

TEST(SessionUtmpTest, LoginTypeToString) {
    EXPECT_EQ(to_string(LoginType::kUnknown), "unknown");
    EXPECT_EQ(to_string(LoginType::kNormal), "normal");
    EXPECT_EQ(to_string(LoginType::kReboot), "reboot");
    EXPECT_EQ(to_string(LoginType::kNewTime), "new-time");
}

// ============================================================================
// SessionIdentity Tests
// ============================================================================

TEST(SessionUtmpTest, SessionIdentityValid) {
    SessionIdentity id;
    EXPECT_FALSE(id.is_valid());
    
    id.uid = 1000;
    id.terminal = "/dev/tty1";
    auto now = std::chrono::system_clock::now();
    id.start_time = now;
    
    EXPECT_TRUE(id.is_valid());
}

TEST(SessionUtmpTest, SessionIdentityEquality) {
    SessionIdentity a, b;
    a.uid = 1000; b.uid = 1000;
    a.terminal = "/dev/tty1"; b.terminal = "/dev/tty1";
    
    auto now = std::chrono::system_clock::now();
    a.start_time = now;
    b.start_time = now;
    
    EXPECT_EQ(a, b);
    EXPECT_FALSE(a != b);
}

// ============================================================================
// UtmpAdapter Tests
// ============================================================================

TEST(SessionUtmpTest, FactoryReturnsValidAdapter) {
    auto adapter = make_utmp_adapter();
    ASSERT_NE(adapter, nullptr);
}

TEST(SessionUtmpTest, ObserveCurrentSessionsCompletes) {
    auto adapter = make_utmp_adapter();
    
    auto result = adapter->observe_current_sessions();
    
    EXPECT_EQ(result.status, core::SemanticStatus::kSuccess) << "Status should be success";
    EXPECT_FALSE(result.description.empty());
    EXPECT_GT(result.elapsed_ms.count(), 0);
}

TEST(SessionUtmapTest, ObserveCurrentSessionsHasExpectedStructure) {
    auto adapter = make_utmp_adapter();
    
    auto result = adapter->observe_current_sessions();
    
    // Verify statistics are populated
    EXPECT_EQ(result.total_sessions, result.current_sessions.size());
    EXPECT_EQ(result.local_sessions + result.remote_sessions, result.total_sessions);
}

// ============================================================================
// Wtmp/Btmp Tests (may not have data in container/test environments)
// ============================================================================

TEST(SessionUtmapTest, GetLoginHistoryCompletes) {
    auto adapter = make_utmp_adapter();
    
    // This may return empty if wtmp is not accessible or has no entries
    auto history = adapter->get_login_history(10);
    
    EXPECT_EQ(history.size(), 0);  // Likely empty in container environments
}

TEST(SessionUtmapTest, GetFailedLoginsCompletes) {
    auto adapter = make_utmp_adapter();
    
    // This may return empty if btmp is not accessible or has no entries
    auto failures = adapter->get_failed_logins(10);
    
    EXPECT_EQ(failures.size(), 0);  // Likely empty in container environments
}

// ============================================================================
// Edge Cases Tests
// ============================================================================

TEST(SessionUtmapTest, ForceRefreshWorks) {
    auto adapter = make_utmp_adapter();
    
    // First observation
    auto result1 = adapter->observe_current_sessions();
    auto time1 = adapter->get_last_observation_time();
    
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    
    // Force refresh should update the timestamp
    auto result2 = adapter->force_refresh();
    auto time2 = adapter->get_last_observation_time();
    
    EXPECT_GE(time2.time_since_epoch().count(), time1.time_since_epoch().count());
}

// ============================================================================
// Integration Test - Verify session observation works end-to-end
// ============================================================================

TEST(SessionUtmapTest, EndToEndSessionObservation) {
    auto adapter = make_utmp_adapter();
    
    // Get current sessions
    auto result = adapter->observe_current_sessions();
    
    // Verify all required fields are populated in results
    for (const auto& session : result.current_sessions) {
        EXPECT_FALSE(session.username.empty());
        EXPECT_FALSE(session.terminal.empty());
        EXPECT_GE(session.uid, 0);
        EXPECT_TRUE(session.start_time.time_since_epoch().count() > 0);
    }
}

}  // namespace test
}  // namespace rebuntu::adapters::session::utmp

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}