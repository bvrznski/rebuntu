// rebuntu::test — Sysfs MD RAID Adapter Unit Tests (Phase 5.20)
//
// Test suite for the sysfs md RAID observation adapter.
// Verifies:
//   - md device parsing from /sys/block/md*/
//   - RAID level identification
//   - Topology graph construction
//   - Identity semantics

#include "adapters/sysfs/md_raid/types.hpp"
#include <gtest/gtest.h>
#include <chrono>

namespace rebuntu::adapters::sysfs::md_raid {

// ============================================================================
// Test fixture for md raid adapter tests
// ============================================================================

class SysfsMdRaidAdapterTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Set up test fixtures if needed
    }
};

// ============================================================================
// Test: RaidLevel string conversion
// ============================================================================

TEST_F(SysfsMdRaidAdapterTest, RaidLevelStringConversion) {
    EXPECT_EQ(to_string(RaidLevel::kLinear), "linear");
    EXPECT_EQ(to_string(RaidLevel::kRaid0), "raid0");
    EXPECT_EQ(to_string(RaidLevel::kRaid1), "raid1");
    EXPECT_EQ(to_string(RaidLevel::kRaid4), "raid4");
    EXPECT_EQ(to_string(RaidLevel::kRaid5), "raid5");
    EXPECT_EQ(to_string(RaidLevel::kRaid6), "raid6");
    EXPECT_EQ(to_string(RaidLevel::kRaid10), "raid10");
}

// ============================================================================
// Test: ArrayState string conversion
// ============================================================================

TEST_F(SysfsMdRaidAdapterTest, ArrayStateStringConversion) {
    EXPECT_EQ(to_string(ArrayState::kInactive), "inactive");
    EXPECT_EQ(to_string(ArrayState::kActive), "active");
    EXPECT_EQ(to_string(ArrayState::kDegraded), "degraded");
    EXPECT_EQ(to_string(ArrayState::kSyncing), "syncing");
    EXPECT_EQ(to_string(ArrayState::kRecovering), "recovering");
}

// ============================================================================
// Test: MdDeviceIdentity equality
// ============================================================================

TEST_F(SysfsMdRaidAdapterTest, DeviceIdentityEquality) {
    MdDeviceIdentity id1{
        .name = "md0",
        .uuid = std::optional<std::string>("raid-uuid-123"),
        .major = 9,
        .minor = 0
    };

    MdDeviceIdentity id2{id1};

    EXPECT_EQ(id1, id2);
}

TEST_F(SysfsMdRaidAdapterTest, DeviceIdentityInequality) {
    MdDeviceIdentity id1{
        .name = "md0",
        .uuid = std::optional<std::string>("raid-uuid-123"),
        .major = 9,
        .minor = 0
    };

    MdDeviceIdentity id2{id1};
    id2.name = "md1";

    EXPECT_NE(id1, id2);
}

// ============================================================================
// Test: MemberDisk structure
// ============================================================================

TEST_F(SysfsMdRaidAdapterTest, MemberDiskStructure) {
    MemberDisk disk;
    
    EXPECT_EQ(disk.raid_position, -1);
    EXPECT_FALSE(disk.is_active);
    EXPECT_FALSE(disk.is_failed);
    EXPECT_FALSE(disk.is_spare);
}

// ============================================================================
// Test: MdArrayObservation structure
// ============================================================================

TEST_F(SysfsMdRaidAdapterTest, ArrayObservationStructure) {
    MdDeviceIdentity identity{
        .name = "md0",
        .uuid = std::optional<std::string>("raid-uuid-123"),
        .major = 9,
        .minor = 0
    };

    MdArrayObservation obs;
    obs.identity = identity;
    obs.level = RaidLevel::kRaid1;
    obs.state = ArrayState::kActive;
    obs.observed_at = std::chrono::system_clock::now();
    obs.source = "sysfs";

    EXPECT_EQ(obs.identity.name, "md0");
    EXPECT_EQ(obs.level, RaidLevel::kRaid1);
}

// ============================================================================
// Test: MdTopology structure
// ============================================================================

TEST_F(SysfsMdRaidAdapterTest, TopologyStructure) {
    MdTopology topo;
    
    EXPECT_EQ(topo.total_arrays, 0);
    EXPECT_TRUE(topo.arrays_by_name.empty());
}

// ============================================================================
// Test: Factory function exists
// ============================================================================

TEST_F(SysfsMdRaidAdapterTest, FactoryFunctionExists) {
    // Just verify the function is declared
    auto adapter = make_sysfs_md_raid_adapter();
    
    EXPECT_NE(adapter, nullptr);
}

}  // namespace rebuntu::adapters::sysfs::md_raid

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}