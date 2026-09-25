// rebuntu::test — Storage Health Monitor Unit Tests (Phase 5.8)
//
// Test suite for the Storage Health Monitor module.
// Verifies:
//   - Block device health assessment
//   - Filesystem health tracking
//   - Mount state transitions
//   - Event generation and deduplication

#include "src/modules/storage_health_monitor/types.hpp"
#include "src/modules/storage_health_monitor/storage_health_monitor.hpp"

#include <gtest/gtest.h>
#include <chrono>

namespace rebuntu::modules::storage_health_monitor {

// ============================================================================
// Test fixture for storage health monitor tests
// ============================================================================

class StorageHealthMonitorTest : public ::testing::Test {
protected:
    void SetUp() override {
        config_.io_error_threshold = 5;
        config_.capacity_warning_percent = 90.0;
        config_.capacity_critical_percent = 95.0;
        config_.temperature_warning_celsius = 70;
        config_.temperature_critical_celsius = 85;
    }
    
    StorageHealthMonitorConfig config_;
};

// ============================================================================
// Test: Initial state is unknown
// ============================================================================

TEST_F(StorageHealthMonitorTest, InitialStateIsUnknown) {
    auto monitor = make_storage_health_monitor(config_);
    
    // Assess without any observations
    auto assessment = monitor->assess_storage_health();
    
    // Should be UNKNOWN for both block and filesystem health
    EXPECT_EQ(assessment.aggregate_block_health, BlockDeviceHealthState::kUnknown);
    EXPECT_EQ(assessment.aggregate_fs_health, FilesystemHealthState::kUnknown);
}

// ============================================================================
// Test: Empty observation produces empty assessment
// ============================================================================

TEST_F(StorageHealthMonitorTest, NoObservationsResultsInEmptyAssessment) {
    auto monitor = make_storage_health_monitor(config_);
    
    auto assessment = monitor->assess_storage_health();
    
    EXPECT_EQ(assessment.block_devices.size(), 0);
    EXPECT_EQ(assessment.filesystems.size(), 0);
}

// ============================================================================
// Test: Block device health state transitions
// ============================================================================

TEST_F(StorageHealthMonitorTest, BlockDeviceHealthyState) {
    auto monitor = make_storage_health_monitor(config_);
    
    // Create a healthy device observation
    BlockDeviceHealth device;
    device.device_id = "dev-001";
    device.health_state = BlockDeviceHealthState::kHealthy;
    device.observed_at = std::chrono::system_clock::now();
    
    monitor->observe_block_device(device, std::chrono::system_clock::now());
    
    auto health = monitor->get_block_device_health("dev-001");
    EXPECT_TRUE(health.has_value());
    EXPECT_EQ(health->health_state, BlockDeviceHealthState::kHealthy);
}

TEST_F(StorageHealthMonitorTest, BlockDeviceFailingStateWithErrors) {
    auto monitor = make_storage_health_monitor(config_);
    
    // Create a device with errors
    BlockDeviceHealth device;
    device.device_id = "dev-002";
    device.health_state = BlockDeviceHealthState::kUnknown;  // Will be assessed
    device.io_error_count = config_.io_error_threshold;      // At threshold
    device.observed_at = std::chrono::system_clock::now();
    
    monitor->observe_block_device(device, std::chrono::system_clock::now());
    
    auto health = monitor->get_block_device_health("dev-002");
    EXPECT_TRUE(health.has_value());
    
    // At threshold should be at least failing
    EXPECT_GE(health->health_state, BlockDeviceHealthState::kFailing);
}

// ============================================================================
// Test: Filesystem health state transitions
// ============================================================================

TEST_F(StorageHealthMonitorTest, FilesystemHealthyState) {
    auto monitor = make_storage_health_monitor(config_);
    
    FilesystemHealth fs;
    fs.mount_point = "/home";
    fs.health_state = FilesystemHealthState::kHealthy;
    fs.mount_state = MountState::kMounted;
    fs.observed_at = std::chrono::system_clock::now();
    
    monitor->observe_filesystem(fs, std::chrono::system_clock::now());
    
    auto fs_health = monitor->get_filesystem_health("/home");
    EXPECT_TRUE(fs_health.has_value());
    EXPECT_EQ(fs_health->health_state, FilesystemHealthState::kHealthy);
}

TEST_F(StorageHealthMonitorTest, FilesystemReadOnlyRemount) {
    auto monitor = make_storage_health_monitor(config_);
    
    FilesystemHealth fs;
    fs.mount_point = "/data";
    fs.health_state = FilesystemHealthState::kReadOnly;
    fs.mount_state = MountState::kMounted;
    fs.observed_at = std::chrono::system_clock::now();
    
    monitor->observe_filesystem(fs, std::chrono::system_clock::now());
    
    auto fs_health = monitor->get_filesystem_health("/data");
    EXPECT_TRUE(fs_health.has_value());
    EXPECT_EQ(fs_health->health_state, FilesystemHealthState::kReadOnly);
}

// ============================================================================
// Test: Mount transition detection
// ============================================================================

TEST_F(StorageHealthMonitorTest, MountAddedTransition) {
    auto monitor = make_storage_health_monitor(config_);
    
    std::vector<MountInfo> mounts;
    mounts.push_back(MountInfo{
        .source = "/dev/sda1",
        .mount_point = "/home",
        .filesystem_type = "ext4"
    });
    
    monitor->process_mount_entries(mounts, std::chrono::system_clock::now());
    
    // Check that filesystem was recorded
    auto fs_health = monitor->get_filesystem_health("/home");
    EXPECT_TRUE(fs_health.has_value());
}

TEST_F(StorageHealthMonitorTest, MountRemovedTransition) {
    auto monitor = make_storage_health_monitor(config_);
    
    // First add a mount
    std::vector<MountInfo> mounts1;
    mounts1.push_back(MountInfo{
        .source = "/dev/sdb1",
        .mount_point = "/mnt/usb",
        .filesystem_type = "vfat"
    });
    monitor->process_mount_entries(mounts1, std::chrono::system_clock::now());
    
    // Now remove it (empty list means all previous mounts were removed)
    std::vector<MountInfo> mounts2;
    monitor->process_mount_entries(mounts2, std::chrono::system_clock::now());
}

// ============================================================================
// Test: Capacity threshold events
// ============================================================================

TEST_F(StorageHealthMonitorTest, CapacityWarningEvent) {
    auto monitor = make_storage_health_monitor(config_);
    
    FilesystemHealth fs;
    fs.mount_point = "/data";
    fs.usage_percent = 92.0;  // Above warning (90%), below critical (95%)
    fs.health_state = FilesystemHealthState::kHealthy;
    fs.mount_state = MountState::kMounted;
    fs.observed_at = std::chrono::system_clock::now();
    
    monitor->observe_filesystem(fs, std::chrono::system_clock::now());
    
    auto events = monitor->get_pending_events();
    
    // Should have at least one capacity warning event
    bool found_warning = false;
    for (const auto& e : events) {
        if (e.event_type == StorageHealthEventType::kCapacityWarning) {
            found_warning = true;
            break;
        }
    }
    EXPECT_TRUE(found_warning);
}

TEST_F(StorageHealthMonitorTest, CapacityCriticalEvent) {
    auto monitor = make_storage_health_monitor(config_);
    
    FilesystemHealth fs;
    fs.mount_point = "/data";
    fs.usage_percent = 97.0;  // Above critical (95%)
    fs.health_state = FilesystemHealthState::kHealthy;
    fs.mount_state = MountState::kMounted;
    fs.observed_at = std::chrono::system_clock::now();
    
    monitor->observe_filesystem(fs, std::chrono::system_clock::now());
    
    auto events = monitor->get_pending_events();
    
    // Should have at least one capacity critical event
    bool found_critical = false;
    for (const auto& e : events) {
        if (e.event_type == StorageHealthEventType::kCapacityCritical) {
            found_critical = true;
            break;
        }
    }
    EXPECT_TRUE(found_critical);
}

// ============================================================================
// Test: Metrics tracking
// ============================================================================

TEST_F(StorageHealthMonitorTest, TracksObservationMetrics) {
    auto monitor = make_storage_health_monitor(config_);
    
    auto initial_metrics = monitor->metrics();
    EXPECT_EQ(initial_metrics.block_device_observations, 0);
    EXPECT_EQ(initial_metrics.filesystem_observations, 0);
    EXPECT_EQ(initial_metrics.mount_observations, 0);
    
    // Add some observations
    BlockDeviceHealth device;
    device.device_id = "dev-test";
    device.health_state = BlockDeviceHealthState::kHealthy;
    device.observed_at = std::chrono::system_clock::now();
    monitor->observe_block_device(device, std::chrono::system_clock::now());
    
    FilesystemHealth fs;
    fs.mount_point = "/test";
    fs.health_state = FilesystemHealthState::kHealthy;
    fs.mount_state = MountState::kMounted;
    fs.observed_at = std::chrono::system_clock::now();
    monitor->observe_filesystem(fs, std::chrono::system_clock::now());
    
    auto final_metrics = monitor->metrics();
    
    EXPECT_EQ(final_metrics.block_device_observations, 1);
    EXPECT_EQ(final_metrics.filesystem_observations, 1);
}

// ============================================================================
// Test: StorageHealthAssessment structure
// ============================================================================

TEST_F(StorageHealthMonitorTest, AssessmentStructure) {
    auto monitor = make_storage_health_monitor(config_);
    
    // Add one device and one filesystem
    BlockDeviceHealth device;
    device.device_id = "dev-001";
    device.health_state = BlockDeviceHealthState::kHealthy;
    device.observed_at = std::chrono::system_clock::now();
    monitor->observe_block_device(device, std::chrono::system_clock::now());
    
    FilesystemHealth fs;
    fs.mount_point = "/home";
    fs.health_state = FilesystemHealthState::kHealthy;
    fs.mount_state = MountState::kMounted;
    fs.observed_at = std::chrono::system_clock::now();
    monitor->observe_filesystem(fs, std::chrono::system_clock::now());
    
    auto assessment = monitor->assess_storage_health();
    
    EXPECT_EQ(assessment.block_devices.size(), 1);
    EXPECT_EQ(assessment.filesystems.size(), 1);
    EXPECT_NE(assessment.assessed_at.time_since_epoch().count(), 0);
}

// ============================================================================
// Test: Event deduplication
// ============================================================================

TEST_F(StorageHealthMonitorTest, EventsAreDeduplicatedWithinWindow) {
    auto monitor = make_storage_health_monitor(config_);
    
    FilesystemHealth fs;
    fs.mount_point = "/data";
    fs.usage_percent = 92.0;  // Above warning threshold
    fs.health_state = FilesystemHealthState::kHealthy;
    fs.mount_state = MountState::kMounted;
    fs.observed_at = std::chrono::system_clock::now();
    
    // First observation should generate event
    monitor->observe_filesystem(fs, std::chrono::system_clock::now());
    auto events1 = monitor->get_pending_events();
    EXPECT_GT(events1.size(), 0);
    
    // Clear the events (simulating they were processed)
    monitor->get_pending_events();
    
    // Second observation with same mount_point should not generate new event
    // (within deduplication window)
    fs.usage_percent = 92.5;  // Slightly higher but same event type
    monitor->observe_filesystem(fs, std::chrono::system_clock::now());
    auto events2 = monitor->get_pending_events();
    
    // Events should be empty or minimal since we deduplicate within window
    EXPECT_EQ(events2.size(), 0);
}

// ============================================================================
// Test: Monitor lifecycle (start/stop)
// ============================================================================

TEST_F(StorageHealthMonitorTest, StartStopLifecycle) {
    auto monitor = make_storage_health_monitor(config_);
    
    EXPECT_FALSE(monitor->is_running());
    
    auto start_result = monitor->start();
    EXPECT_TRUE(start_result.status == core::SemanticStatus::kSuccess);
    EXPECT_TRUE(monitor->is_running());
    
    auto stop_result = monitor->stop();
    EXPECT_TRUE(stop_result.status == core::SemanticStatus::kSuccess);
    EXPECT_FALSE(monitor->is_running());
}

}  // namespace rebuntu::modules::storage_health_monitor

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}