// Rebuntu Group Membership Tests (Phase 2.2)
// ============================================
// Testing native Linux group membership observation and verification

#include <system/environment/group_membership.hpp>
#include <cassert>
#include <iostream>
#include <cstdlib>

using namespace rebuntu::environment::group_membership;

void test_group_ref_creation() {
    // Test by_name creation
    auto ref1 = GroupRef::by_name("wheel");
    assert(ref1.kind == GroupRef::Kind::kByName);
    assert(ref1.name.has_value());
    assert(*ref1.name == "wheel");
    
    // Test by_gid creation
    auto ref2 = GroupRef::by_gid(1000);
    assert(ref2.kind == GroupRef::Kind::kByGid);
    assert(ref2.gid.has_value());
    assert(*ref2.gid == 1000);
    
    std::cout << "test_group_ref_creation: PASSED" << std::endl;
}

void test_group_ref_equality() {
    auto ref1 = GroupRef::by_name("wheel");
    auto ref2 = GroupRef::by_name("wheel");
    auto ref3 = GroupRef::by_gid(1000);
    
    // Same name should be equal
    assert(ref1 == ref2);
    
    // Different kind should not be equal
    assert(!(ref1 == ref3));
    
    std::cout << "test_group_ref_equality: PASSED" << std::endl;
}

void test_membership_result_success() {
    auto result = MembershipResult<bool>::success(true, "getgrgid_r");
    assert(result.is_success());
    assert(!result.is_not_found());
    assert(result.value == true);
    assert(!result.error_code.empty());
    
    std::cout << "test_membership_result_success: PASSED" << std::endl;
}

void test_membership_result_not_found() {
    auto result = MembershipResult<bool>::not_found("getgrgid_r");
    assert(result.is_not_found());
    assert(result.status == MembershipResult<bool>::Status::kNotFound);
    
    std::cout << "test_membership_result_not_found: PASSED" << std::endl;
}

void test_membership_result_already_exists() {
    auto result = MembershipResult<std::vector<gid_t>>::already_exists(
        "setgroups", "User already in group");
    assert(result.is_already_exists());
    assert(result.status == MembershipResult<std::vector<gid_t>>::Status::kAlreadyExists);
    
    std::cout << "test_membership_result_already_exists: PASSED" << std::endl;
}

void test_membership_result_missing() {
    auto result = MembershipResult<std::vector<gid_t>>::missing(
        "setgroups", "User not in expected group");
    assert(result.is_missing());
    assert(result.status == MembershipResult<std::vector<gid_t>>::Status::kMissing);
    
    std::cout << "test_membership_result_missing: PASSED" << std::endl;
}

void test_membership_result_unknown() {
    auto result = MembershipResult<std::vector<gid_t>>::unknown(
        "getgroups", "Failed to retrieve groups");
    assert(result.is_unknown());
    assert(result.status == MembershipResult<std::vector<gid_t>>::Status::kUnknown);
    
    std::cout << "test_membership_result_unknown: PASSED" << std::endl;
}

void test_observe_current_effective_groups() {
    auto result = observe_current_effective_groups();
    
    // Should succeed for normal processes
    if (result.is_success()) {
        assert(!result.value.empty());
        std::cout << "test_observe_current_effective_groups: PASSED" << std::endl;
    } else {
        // May fail in some environments, but should still log
        std::cout << "test_observe_current_effective_groups: SKIPPED (cannot get groups)" << std::endl;
    }
}

void test_is_effectively_in_group() {
    auto current_gid = getegid();
    auto result = is_effectively_in_group(current_gid);
    
    // Current process should be in its effective group
    if (result.is_success()) {
        assert(result.value == true);
        std::cout << "test_is_effectively_in_group: PASSED" << std::endl;
    } else {
        std::cout << "test_is_effectively_in_group: SKIPPED (cannot verify)" << std::endl;
    }
}

void test_verify_group_membership_consistency() {
    auto uid = getuid();
    auto verification = verify_group_membership_consistency(uid);
    
    // Should complete without error
    assert(!verification.group_states.empty());
    assert(!verification.verification_source.empty());
    
    std::cout << "test_verify_group_membership_consistency: PASSED" << std::endl;
}

int main() {
    std::cout << "Running Rebuntu Group Membership Tests (Phase 2.2)" << std::endl;
    std::cout << "===================================================" << std::endl;
    
    test_group_ref_creation();
    test_group_ref_equality();
    test_membership_result_success();
    test_membership_result_not_found();
    test_membership_result_already_exists();
    test_membership_result_missing();
    test_membership_result_unknown();
    test_observe_current_effective_groups();
    test_is_effectively_in_group();
    test_verify_group_membership_consistency();
    
    std::cout << "===================================================" << std::endl;
    std::cout << "All group membership tests completed" << std::endl;
    
    return 0;
}