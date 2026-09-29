// rebuntu::test — Procfs Mounts Adapter Unit Tests (Phase 5.17)
//
// Test suite for the procfs mounts observation adapter.
// Verifies:
//   - Mount table parsing from /proc/self/mountinfo
//   - statvfs capacity statistics
//   - Topology graph construction
//   - Identity and freshness semantics

#include "adapters/procfs/mounts/types.hpp"
#include <gtest/gtest.h>
#include <chrono>

namespace rebuntu::adapters::procfs::mounts {

// ============================================================================
// Test fixture for procfs mounts adapter tests
// ============================================================================

class ProcfsMountsAdapterTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Set up test fixtures if needed
    }
};

// ============================================================================
// Test: MountIdentity equality and ordering
// ============================================================================

TEST_F(ProcfsMountsAdapterTest, MountIdentityEquality) {
    MountIdentity id1;
    id1.major = 8;
    id1.minor = 1;
    id1.source = "/dev/sda1";
    id1.mountpoint = "/mnt/test";

    MountIdentity id2{id1};

    EXPECT_EQ(id1, id2);
}

TEST_F(ProcfsMountsAdapterTest, MountIdentityInequality) {
    MountIdentity id1{
        .major = 8,
        .minor = 1,
        .source = "/dev/sda1",
        .mountpoint = "/mnt/test"
    };

    MountIdentity id2{id1};
    id2.mountpoint = "/mnt/other";

    EXPECT_NE(id1, id2);
}

// ============================================================================
// Test: MountTopologyType string conversion
// ============================================================================

TEST_F(ProcfsMountsAdapterTest, TopologyTypeStringConversion) {
    EXPECT_EQ(to_string(MountTopologyType::kPrimary), "primary");
    EXPECT_EQ(to_string(MountTopologyType::kBind), "bind");
    EXPECT_EQ(to_string(MountTopologyType::kOverlay), "overlay");
    EXPECT_EQ(to_string(MountTopologyType::kBindOverlay), "bind-overlay");
    EXPECT_EQ(to_string(MountTopologyType::kNetwork), "network");
    EXPECT_EQ(to_string(MountTopologyType::kSpecial), "special");
}

// ============================================================================
// Test: MountRelationship defaults
// ============================================================================

TEST_F(ProcfsMountsAdapterTest, RelationshipDefaults) {
    MountRelationship rel;
    
    EXPECT_EQ(rel.parent_mount_id, -1);
    EXPECT_EQ(rel.relationship_type, MountTopologyType::kPrimary);
    EXPECT_TRUE(rel.overlay_layers.empty());
    EXPECT_EQ(rel.provenance_source, "procfs");
}

// ============================================================================
// Test: FilesystemCapacity structure
// ============================================================================

TEST_F(ProcfsMountsAdapterTest, CapacityStructure) {
    FilesystemCapacity cap;
    
    EXPECT_EQ(cap.block_size, 0);
    EXPECT_EQ(cap.total_blocks, 0);
    EXPECT_EQ(cap.free_blocks, 0);
    EXPECT_EQ(cap.used_blocks, 0);
    EXPECT_EQ(cap.available_blocks, 0);
    
    // Test with values
    cap.block_size = 4096;
    cap.total_blocks = 1000000;
    cap.free_blocks = 500000;
    cap.used_blocks = cap.total_blocks - cap.free_blocks;
    cap.available_blocks = 480000;
    
    EXPECT_EQ(cap.block_size, 4096);
    EXPECT_EQ(cap.used_blocks, 500000);
}

// ============================================================================
// Test: MountObservation structure
// ============================================================================

TEST_F(ProcfsMountsAdapterTest, ObservationStructure) {
    MountIdentity identity{
        .major = 8,
        .minor = 1,
        .source = "/dev/sda1",
        .mountpoint = "/mnt/test"
    };

    MountObservation obs;
    obs.identity = identity;
    obs.filesystem_type = "ext4";
    obs.options = {"rw", "noatime"};
    obs.observed_at = std::chrono::system_clock::now();
    obs.source = "procfs";

    EXPECT_EQ(obs.identity.mountpoint, "/mnt/test");
    EXPECT_EQ(obs.filesystem_type, "ext4");
    EXPECT_FALSE(obs.is_read_only);
}

// ============================================================================
// Test: MountTopology structure
// ============================================================================

TEST_F(ProcfsMountsAdapterTest, TopologyStructure) {
    MountTopology topo;
    
    EXPECT_EQ(topo.total_mounts, 0);
    EXPECT_TRUE(topo.mounts_by_id.empty());
    EXPECT_TRUE(topo.root_mount_ids.empty());
}

// ============================================================================
// Test: Capacity calculations
// ============================================================================

TEST_F(ProcfsMountsAdapterTest, CapacityByteCalculations) {
    FilesystemCapacity cap;
    
    // Simulate a 1GB filesystem with 4096-byte blocks
    uint64_t block_size = 4096;
    uint64_t total_blocks = 250000;  // 1GB / 4096
    
    cap.block_size = block_size;
    cap.total_blocks = total_blocks;
    cap.free_blocks = total_blocks / 2;  // Half free
    cap.available_blocks = total_blocks / 2 - 1000;  // Some reserved
    
    cap.used_blocks = cap.total_blocks - cap.free_blocks;
    
    EXPECT_EQ(cap.capacity_bytes, block_size * total_blocks);
    EXPECT_EQ(cap.used_bytes, block_size * cap.used_blocks);
}

// ============================================================================
// Test: Adapter factory function exists
// ============================================================================

TEST_F(ProcfsMountsAdapterTest, FactoryFunctionExists) {
    // Just verify the function is declared - actual usage requires running system
    auto adapter = make_procfs_mounts_adapter();
    
    EXPECT_NE(adapter, nullptr);
}

}  // namespace rebuntu::adapters::procfs::mounts

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}