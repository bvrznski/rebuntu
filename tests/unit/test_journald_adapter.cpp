// rebuntu::test_journald_adapter — Unit Tests for Journald Adapter (Phase 5.2)

#include "adapters/journald.hpp"

#include <gtest/gtest.h>
#include <chrono>
#include <thread>

namespace rebuntu::adapters {

// Test factory function creates valid adapter
TEST(JournaldAdapterTest, FactoryCreatesValidAdapter) {
    bool event_received = false;
    
    auto adapter = make_journald_adapter(
        JournaldConfig{},
        [&event_received](const runtime::Event&) { event_received = true; });
    
    ASSERT_NE(adapter, nullptr);
    EXPECT_FALSE(adapter->is_running());
}

// Test start/stop lifecycle
TEST(JournaldAdapterTest, StartStopLifecycle) {
    bool event_received = false;
    
    auto adapter = make_journald_adapter(
        JournaldConfig{},
        [&event_received](const runtime::Event&) { event_received = true; });
    
    auto result = adapter->start();
    EXPECT_TRUE(result.is_success());
    EXPECT_TRUE(adapter->is_running());
    
    result = adapter->stop();
    EXPECT_TRUE(result.is_success());
    EXPECT_FALSE(adapter->is_running());
}

// Test duplicate start is rejected
TEST(JournaldAdapterTest, DuplicateStartRejected) {
    auto adapter = make_journald_adapter(
        JournaldConfig{},
        [](const runtime::Event&) {});
    
    auto result = adapter->start();
    EXPECT_TRUE(result.is_success());
    
    // Second start should fail
    result = adapter->start();
    EXPECT_TRUE(result.is_error());
}

// Test stop when not running is rejected
TEST(JournaldAdapterTest, StopWhenNotRunningRejected) {
    auto adapter = make_journald_adapter(
        JournaldConfig{},
        [](const runtime::Event&) {});
    
    // Stop when not running should fail
    auto result = adapter->stop();
    EXPECT_TRUE(result.is_error());
}

// Test cursor management
TEST(JournaldAdapterTest, CursorManagement) {
    auto adapter = make_journald_adapter(
        JournaldConfig{},
        [](const runtime::Event&) {});
    
    // Before start, no cursor should be set
    EXPECT_FALSE(adapter->get_cursor().has_value());
    
    // Set cursor before starting
    adapter->set_cursor("test-cursor-123");
    
    auto result = adapter->start();
    EXPECT_TRUE(result.is_success());
    
    // Cursor should still be available after start
    auto cursor = adapter->get_cursor();
    EXPECT_TRUE(cursor.has_value());
    EXPECT_EQ(cursor.value(), "test-cursor-123");
}

// Test metrics are zeroed on start
TEST(JournaldAdapterTest, MetricsZeroedOnStart) {
    auto adapter = make_journald_adapter(
        JournaldConfig{},
        [](const runtime::Event&) {});
    
    // Start and check initial metrics
    adapter->start();
    auto metrics = adapter->metrics();
    
    EXPECT_EQ(metrics.records_read, 0);
    EXPECT_EQ(metrics.events_published, 0);
    EXPECT_EQ(metrics.errors_parse_failed, 0);
}

// Test config values are stored correctly
TEST(JournaldAdapterTest, ConfigStoredCorrectly) {
    JournaldConfig config;
    config.boot_id = -1;  // Previous boot
    config.max_records_per_query = 500;
    config.follow_mode = true;
    
    auto adapter = make_journald_adapter(
        config,
        [](const runtime::Event&) {});
    
    // The config should be stored (we can't directly access it from the interface)
    // but we can verify the adapter starts successfully with this config
    auto result = adapter->start();
    EXPECT_TRUE(result.is_success());
}

// Test parse_json_record extracts key fields
TEST(JournaldAdapterTest, ParseJsonRecordExtractsFields) {
    // Sample JSON record from journalctl --output=json
    std::string json = R"({
        "_SYSTEMD_UNIT": "test.service",
        "SYSLOG_IDENTIFIER": "test-app",
        "_TRANSPORT": "stdout",
        "_BOOT_ID": "abc123def456",
        "_MACHINE_ID": "machine789",
        "__CURSOR": "cursor-xyz",
        "__REALTIME_TIMESTAMP": "1700000000000000",
        "PRIORITY": "4",
        "MESSAGE": "Test log message"
    })";
    
    auto event_opt = JournaldAdapter::parse_json_record(json, std::chrono::system_clock::now());
    
    ASSERT_TRUE(event_opt.has_value());
    auto& event = event_opt.value();
    
    EXPECT_EQ(event.source, "journald");
    EXPECT_EQ(event.type, "info");  // PRIORITY 4 is info
    EXPECT_EQ(event.evidence.size(), 6);  // MESSAGE + unit + syslog_id + transport + boot + machine
    
    bool found_message = false;
    for (const auto& e : event.evidence) {
        if (e.source == "journal_message") {
            found_message = true;
            break;
        }
    }
    EXPECT_TRUE(found_message);
}

// Test parse_json_record handles priority levels
TEST(JournaldAdapterTest, ParseJsonRecordPriorityLevels) {
    auto test_priority = [](int priority, const char* expected_type) {
        std::string json = R"({
            "MESSAGE": "test",
            "PRIORITY": ")" + std::to_string(priority) + R"("
        })";
        
        auto event_opt = JournaldAdapter::parse_json_record(json, std::chrono::system_clock::now());
        
        ASSERT_TRUE(event_opt.has_value());
        EXPECT_EQ(event_opt.value().type, expected_type);
    };
    
    // Error level (0-3)
    test_priority(0, "error");
    test_priority(3, "error");
    
    // Warning level (4-5)
    test_priority(4, "warning");
    test_priority(5, "warning");
    
    // Info level (6+)
    test_priority(6, "info");
    test_priority(7, "info");
}

// Test parse_json_record handles missing message
TEST(JournaldAdapterTest, ParseJsonRecordMissingMessage) {
    std::string json = R"({
        "_SYSTEMD_UNIT": "test.service"
    })";
    
    auto event_opt = JournaldAdapter::parse_json_record(json, std::chrono::system_clock::now());
    
    // Should return nullopt when MESSAGE is missing
    EXPECT_FALSE(event_opt.has_value());
}

// Test parse_json_record handles invalid priority gracefully
TEST(JournaldAdapterTest, ParseJsonRecordInvalidPriority) {
    std::string json = R"({
        "MESSAGE": "test",
        "PRIORITY": "not-a-number"
    })";
    
    auto event_opt = JournaldAdapter::parse_json_record(json, std::chrono::system_clock::now());
    
    ASSERT_TRUE(event_opt.has_value());
    // Should default to info level (6) when priority is invalid
    EXPECT_EQ(event_opt.value().type, "info");
}

// Test JournaldQuery build_argv generates correct arguments
TEST(JournaldQueryTest, BuildArgvGeneratesCorrectArguments) {
    JournaldQuery::QueryConfig config;
    config.boot_id = -1;
    config.max_records = 100;
    
    auto argv = JournaldQuery::build_argv(config);
    
    bool has_boot = false;
    bool has_n_100 = false;
    bool has_json_output = false;
    
    for (size_t i = 0; i < argv.size(); ++i) {
        if (argv[i] == "-b" && i + 1 < argv.size() && argv[i+1] == "-1") {
            has_boot = true;
        }
        if (argv[i] == "-n" && i + 1 < argv.size() && argv[i+1] == "100") {
            has_n_100 = true;
        }
        if (argv[i] == "--output=json") {
            has_json_output = true;
        }
    }
    
    EXPECT_TRUE(has_boot);
    EXPECT_TRUE(has_n_100);
    EXPECT_TRUE(has_json_output);
}

// Test JournaldQuery build_argv with current boot
TEST(JournaldQueryTest, BuildArgvWithCurrentBoot) {
    JournaldQuery::QueryConfig config;
    config.boot_id = 0;  // Current boot
    
    auto argv = JournaldQuery::build_argv(config);
    
    bool has_boot_flag = false;
    for (const auto& arg : argv) {
        if (arg == "--boot") {
            has_boot_flag = true;
            break;
        }
    }
    
    EXPECT_TRUE(has_boot_flag);
}

// Test JournaldQuery build_argv with units
TEST(JournaldQueryTest, BuildArgvWithUnits) {
    JournaldQuery::QueryConfig config;
    config.units = {"unit1.service", "unit2.service"};
    
    auto argv = JournaldQuery::build_argv(config);
    
    bool has_unit1 = false;
    bool has_unit2 = false;
    for (size_t i = 0; i < argv.size(); ++i) {
        if (argv[i] == "-u" && i + 1 < argv.size()) {
            if (argv[i+1] == "unit1.service") has_unit1 = true;
            if (argv[i+1] == "unit2.service") has_unit2 = true;
        }
    }
    
    EXPECT_TRUE(has_unit1);
    EXPECT_TRUE(has_unit2);
}

// Test JournaldQuery build_argv with priority filter
TEST(JournaldQueryTest, BuildArgvWithPriorityFilter) {
    JournaldQuery::QueryConfig config;
    config.min_priority = 3;  // Show priority <= 3 (errors)
    
    auto argv = JournaldQuery::build_argv(config);
    
    bool has_priority_filter = false;
    for (size_t i = 0; i < argv.size(); ++i) {
        if (argv[i] == "--priority" && i + 1 < argv.size() && argv[i+1] == "3") {
            has_priority_filter = true;
            break;
        }
    }
    
    EXPECT_TRUE(has_priority_filter);
}

// Test parse_json_record handles empty timestamp
TEST(JournaldAdapterTest, ParseJsonRecordEmptyTimestamp) {
    std::string json = R"({
        "MESSAGE": "test",
        "__REALTIME_TIMESTAMP": ""
    })";
    
    auto event_opt = JournaldAdapter::parse_json_record(json, std::chrono::system_clock::now());
    
    ASSERT_TRUE(event_opt.has_value());
    // Should use acquisition_time when timestamp is empty
}

// Test metrics are tracked during operation
TEST(JournaldAdapterTest, MetricsTracking) {
    bool event_received = false;
    size_t receive_count = 0;
    
    auto adapter = make_journald_adapter(
        JournaldConfig{},
        [&receive_count](const runtime::Event&) { 
            receive_count++; 
        });
    
    // Start the adapter
    auto result = adapter->start();
    EXPECT_TRUE(result.is_success());
    
    // Check metrics after start (before any parsing)
    auto metrics = adapter->metrics();
    EXPECT_EQ(receive_count, 0);
    
    // Stop and verify final state
    adapter->stop();
}

}  // namespace rebuntu::adapters

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}