// rebuntu::tests::unit::cross_domain_references — Unit Tests (Phase 5.46)
//
// Test suite for Cross-Domain Entity References types and interface.

#include "interfaces/cross_domain_references.hpp"

#include <gtest/gtest.h>

namespace rebuntu::interfaces {

// ============================================================================
// CrossDomainEntityId Tests
// ============================================================================

TEST(CrossDomainReferences, CrossDomainEntityId_ConstructsValidFromStrings) {
    CrossDomainEntityId id{"process", "1234@boot-789"};
    
    EXPECT_EQ(id.domain, "process");
    EXPECT_EQ(id.identifier, "1234@boot-789");
    EXPECT_TRUE(id.is_valid());
}

TEST(CrossDomainReferences, CrossDomainEntityId_ConstructsValidViaStaticMethods) {
    auto id = CrossDomainEntityId::cgroup("/system.slice/foo.service");
    
    EXPECT_EQ(id.domain, "cgroup");
    EXPECT_EQ(id.identifier, "/system.slice/foo.service");
    EXPECT_TRUE(id.is_valid());
}

TEST(CrossDomainReferences, CrossDomainEntityId_ProcessIdentity) {
    auto id = CrossDomainEntityId::process("1234@boot-789");
    
    EXPECT_EQ(id.domain, "process");
    EXPECT_EQ(id.identifier, "1234@boot-789");
}

TEST(CrossDomainReferences, CrossDomainEntityId_ServiceIdentity) {
    auto id = CrossDomainEntityId::service("ssh.service", "service");
    
    EXPECT_EQ(id.domain, "service");
    EXPECT_EQ(id.identifier, "ssh.service");
}

TEST(CrossDomainReferences, CrossDomainEntityId_NetworkInterface) {
    auto id = CrossDomainEntityId::network_interface("eth0");
    
    EXPECT_EQ(id.domain, "interface");
    EXPECT_EQ(id.identifier, "eth0");
}

// ============================================================================
// Stable Identity Test
// ============================================================================

TEST(CrossDomainReferences, CrossDomainEntityId_NetworkInterfaceStable) {
    auto id = CrossDomainEntityId::network_interface_stable(1234, "00:11:22:33:44:55");
    
    EXPECT_EQ(id.domain, "interface");
    EXPECT_EQ(id.identifier, "1234@00:11:22:33:44:55");
}

TEST(CrossDomainReferences, CrossDomainEntityId_NetworkInterfaceStable_Equality) {
    auto id1 = CrossDomainEntityId::network_interface_stable(1234, "aa:bb:cc:dd:ee:ff");
    auto id2 = CrossDomainEntityId::network_interface_stable(1234, "aa:bb:cc:dd:ee:ff");
    
    EXPECT_EQ(id1, id2);
}

TEST(CrossDomainReferences, CrossDomainEntityId_NetworkInterfaceStable_DifferentIfindex) {
    auto id1 = CrossDomainEntityId::network_interface_stable(1234, "aa:bb:cc:dd:ee:ff");
    auto id2 = CrossDomainEntityId::network_interface_stable(5678, "aa:bb:cc:dd:ee:ff");
    
    EXPECT_NE(id1, id2);
}

TEST(CrossDomainReferences, CrossDomainEntityId_NetworkInterfaceStable_DifferentMac) {
    auto id1 = CrossDomainEntityId::network_interface_stable(1234, "aa:bb:cc:dd:ee:ff");
    auto id2 = CrossDomainEntityId::network_interface_stable(1234, "00:11:22:33:44:55");
    
    EXPECT_NE(id1, id2);
}

TEST(CrossDomainReferences, CrossDomainEntityId_IpAddress) {
    auto id = CrossDomainEntityId::ip_address("192.168.1.1", "ipv4");
    
    EXPECT_EQ(id.domain, "address");
    EXPECT_EQ(id.identifier, "192.168.1.1");
}

TEST(CrossDomainReferences, CrossDomainEntityId_IsValidChecksBothFields) {
    // Empty domain is invalid
    CrossDomainEntityId id1{"", "foo"};
    EXPECT_FALSE(id1.is_valid());
    
    // Empty identifier is invalid  
    CrossDomainEntityId id2{"process", ""};
    EXPECT_FALSE(id2.is_valid());
    
    // Both empty is invalid
    CrossDomainEntityId id3{"", ""};
    EXPECT_FALSE(id3.is_valid());
}

TEST(CrossDomainReferences, CrossDomainEntityId_Equality) {
    CrossDomainEntityId a{"process", "1234@boot-789"};
    CrossDomainEntityId b{"process", "1234@boot-789"};
    CrossDomainEntityId c{"process", "5678@boot-100"};
    CrossDomainEntityId d{"cgroup", "/system.slice/foo"};
    
    EXPECT_EQ(a, b);
    EXPECT_NE(a, c);
    EXPECT_NE(a, d);
}

TEST(CrossDomainReferences, CrossDomainEntityId_Hash) {
    CrossDomainEntityId id1{"process", "1234@boot-789"};
    CrossDomainEntityId id2{"process", "1234@boot-789"};
    CrossDomainEntityId id3{"cgroup", "/system.slice/foo"};
    
    std::hash<CrossDomainEntityId> hasher;
    
    // Same IDs should have same hash
    EXPECT_EQ(hasher(id1), hasher(id2));
    
    // Different IDs likely have different hashes (not required but expected)
    // We can't guarantee different hashes, just that hashing doesn't crash
    auto h3 = hasher(id3);
    (void)h3;  // Suppress unused warning
}

// ============================================================================
// RelationshipType Tests
// ============================================================================

TEST(CrossDomainReferences, RelationshipType_ConvertsToString) {
    EXPECT_EQ(to_string(RelationshipType::kBelongsTo), "belongs-to");
    EXPECT_EQ(to_string(RelationshipType::kManages), "manages");
    EXPECT_EQ(to_string(RelationshipType::kDependsOn), "depends-on");
    EXPECT_EQ(to_string(RelationshipType::kRunsOn), "runs-on");
    EXPECT_EQ(to_string(RelationshipType::kResidesOn), "resides-on");
    EXPECT_EQ(to_string(RelationshipType::kAssignedTo), "assigned-to");
    EXPECT_EQ(to_string(RelationshipType::kMemberOf), "member-of");
}

// ============================================================================
// EntityReference Tests
// ============================================================================

TEST(CrossDomainReferences, EntityReference_ConstructsValid) {
    EntityReference ref{
        .target = CrossDomainEntityId{"process", "1234@boot-789"},
        .relationship = RelationshipType::kBelongsTo,
        .provenance_source = "procfs:/proc/1234/cgroup",
    };
    
    EXPECT_TRUE(ref.is_valid());
}

TEST(CrossDomainReferences, EntityReference_IsValidRequiresTargetAndProvenance) {
    // Missing provenance
    EntityReference ref1{
        .target = CrossDomainEntityId{"process", "1234@boot-789"},
        .relationship = RelationshipType::kBelongsTo,
        .provenance_source = "",
    };
    EXPECT_FALSE(ref1.is_valid());
    
    // Missing target (invalid ID)
    EntityReference ref2{
        .target = CrossDomainEntityId{"", ""},
        .relationship = RelationshipType::kBelongsTo,
        .provenance_source = "test",
    };
    EXPECT_FALSE(ref2.is_valid());
}

// ============================================================================
// CrossDomainQuery Tests
// ============================================================================

TEST(CrossDomainReferences, CrossDomainQuery_Make) {
    auto query = CrossDomainQuery::make("test-query-1");
    
    EXPECT_EQ(query.id, "test-query-1");
    EXPECT_GT(query.created_at.time_since_epoch().count(), 0ULL);
    EXPECT_EQ(query.freshness_threshold_ms.count(), 60000);  // default
    EXPECT_EQ(query.max_references, 1000);  // default
}

TEST(CrossDomainReferences, CrossDomainQuery_HasOptionalFilters) {
    auto query = CrossDomainQuery::make("test-query-2");
    
    // Should be std::nullopt by default
    EXPECT_FALSE(query.target_domain.has_value());
    EXPECT_FALSE(query.relationship_type.has_value());
    EXPECT_FALSE(query.source_entity.has_value());
}

// ============================================================================
// CrossDomainReferenceResult Tests
// ============================================================================

TEST(CrossDomainReferences, CrossDomainReferenceResult_InitializesCorrectly) {
    CrossDomainReferenceResult result;
    
    EXPECT_EQ(result.status, core::SemanticStatus::kUnknown);
    EXPECT_EQ(result.total_references, 0U);
}

}  // namespace rebuntu::interfaces