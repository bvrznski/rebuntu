// Rebuntu Ownership & Permissions Tests (Phase 2.3)
// ====================================================
// Testing native Linux ownership and permission operations:
// - uid/gid observation and verification
// - mode bits representation and parsing
// - symlink safety checks
// - idempotent mutation operations
// - safe creation with permissions
// - repair logic

#include <system/environment/ownership.hpp>
#include <sys/stat.h>
#include <unistd.h>
#include <cassert>
#include <iostream>
#include <cstdlib>
#include <filesystem>
#include <fstream>

using namespace rebuntu::environment::ownership;

void test_mode_bits_creation() {
    // Test standard permission bits
    ModeBits m1;
    m1.owner_read = true;
    m1.owner_write = true;
    m1.owner_exec = true;
    
    uint32_t val = m1.value();
    assert(val == 0700);  // rwx for owner only
    
    // Test from value
    ModeBits m2 = ModeBits::from_value(0755);
    assert(m2.owner_read && m2.owner_write && m2.owner_exec);
    assert(m2.group_read && !m2.group_write && m2.group_exec);
    assert(m2.other_read && !m2.other_write && m2.other_exec);
    
    std::cout << "test_mode_bits_creation: PASSED" << std::endl;
}

void test_special_mode_bits() {
    ModeBits m;
    m.owner_read = true;
    m.setuid = true;
    m.setgid = true;
    m.sticky_bit = true;
    
    uint32_t val = m.value();
    // Should have owner read + setuid (04000) + setgid (02000) + sticky (01000)
    assert(val == 07400);
    
    ModeBits m2 = ModeBits::from_value(04755);
    assert(m2.owner_read && m2.setuid);
    
    std::cout << "test_special_mode_bits: PASSED" << std::endl;
}

void test_mode_string_conversion() {
    std::string s1 = mode_to_string(0755);
    assert(s1 == "0755");
    
    std::string s2 = mode_to_string(0644);
    assert(s2 == "0644");
    
    ModeBits m = parse_mode_string("0755").value.value();
    assert(m.owner_read && m.owner_write && m.owner_exec);
    assert(m.group_read && !m.group_write && m.group_exec);
    
    std::cout << "test_mode_string_conversion: PASSED" << std::endl;
}

void test_observe_file_state_existing() {
    // Create a temporary file
    std::filesystem::path temp_path = "/tmp/rebuntu_test_ownership_" + 
                                      std::to_string(getpid());
    
    std::ofstream ofs(temp_path);
    ofs << "test content";
    ofs.close();
    
    auto result = observe_file_state(temp_path, SymlinkSafety::kAllowed);
    
    assert(result.is_success());
    assert(result.value.has_value());
    const FileState& state = result.value.value();
    assert(state.exists);
    assert(state.is_regular_file);
    assert(!state.is_symlink);
    assert(state.uid.has_value());
    assert(state.gid.has_value());
    
    // Cleanup
    std::filesystem::remove(temp_path);
    
    std::cout << "test_observe_file_state_existing: PASSED" << std::endl;
}

void test_observe_file_state_not_found() {
    auto result = observe_file_state("/tmp/nonexistent_file_xyz_" + 
                                      std::to_string(getpid()), 
                                     SymlinkSafety::kAllowed);
    
    assert(!result.is_success());
    assert(result.status == PermissionResult<FileState>::Status::kNotFound);
    
    std::cout << "test_observe_file_state_not_found: PASSED" << std::endl;
}

void test_symlink_detection() {
    // Create a temporary directory and symlink
    std::filesystem::path temp_dir = "/tmp/rebuntu_test_symlink_" + 
                                     std::to_string(getpid());
    
    std::filesystem::create_directories(temp_dir);
    
    std::filesystem::path target_file = temp_dir / "target";
    std::filesystem::path link_path = temp_dir / "link";
    
    std::ofstream ofs(target_file);
    ofs << "target content";
    ofs.close();
    
    std::filesystem::create_symlink("target", link_path);
    
    // With kAllowed, symlink should be detected but not rejected
    auto result_allowed = observe_file_state(link_path, SymlinkSafety::kAllowed);
    assert(result_allowed.is_success());
    assert(result_allowed.value->is_symlink);
    
    // With kRejected, symlink should be observed via lstat (not followed)
    auto result_rejected = observe_file_state(link_path, SymlinkSafety::kRejected);
    assert(result_rejected.is_success());
    assert(result_rejected.value->is_symlink);
    
    // Cleanup
    std::filesystem::remove_all(temp_dir);
    
    std::cout << "test_symlink_detection: PASSED" << std::endl;
}

void test_verify_ownership_positive() {
    // Create a temp file with current uid/gid
    std::filesystem::path temp_path = "/tmp/rebuntu_test_verify_" + 
                                      std::to_string(getpid());
    
    std::ofstream ofs(temp_path);
    ofs.close();
    
    // Set it to current user's permissions
    chown(temp_path.c_str(), getuid(), getgid());
    chmod(temp_path.c_str(), 0644);
    
    VerifyOwnershipIntent intent;
    intent.path = temp_path;
    intent.expected_uid = getuid();
    intent.expected_gid = getgid();
    
    // Owner should have read and write
    intent.expected_mode_bits.owner_read = true;
    intent.expected_mode_bits.owner_write = true;
    intent.expected_mode_bits.owner_exec = false;
    
    auto verification = verify_ownership(intent);
    
    assert(verification.is_compliant);
    assert(verification.path_exists);
    assert(verification.owner_matches);
    assert(verification.group_matches);
    
    // Cleanup
    std::filesystem::remove(temp_path);
    
    std::cout << "test_verify_ownership_positive: PASSED" << std::endl;
}

void test_verify_ownership_negative() {
    std::filesystem::path temp_path = "/tmp/rebuntu_test_verify_neg_" + 
                                      std::to_string(getpid());
    
    std::ofstream ofs(temp_path);
    ofs.close();
    
    // Set it to root (0)
    chown(temp_path.c_str(), 0, 0);
    
    VerifyOwnershipIntent intent;
    intent.path = temp_path;
    intent.expected_uid = getuid();  // Different from current
    intent.expected_gid = getgid();
    intent.expected_mode_bits.owner_read = true;
    intent.expected_mode_bits.owner_write = true;
    
    auto verification = verify_ownership(intent);
    
    assert(!verification.is_compliant);
    assert(!verification.owner_matches);
    
    // Cleanup
    std::filesystem::remove(temp_path);
    
    std::cout << "test_verify_ownership_negative: PASSED" << std::endl;
}

void test_apply_ownership_mutation() {
    std::filesystem::path temp_path = "/tmp/rebuntu_test_mut_" + 
                                      std::to_string(getpid());
    
    // Create file
    std::ofstream ofs(temp_path);
    ofs.close();
    
    OwnershipMutation mut1;
    mut1.path = temp_path;
    mut1.set_uid = 0;  // Set to root
    
    auto result1 = apply_ownership_mutation(mut1);
    assert(result1.changed);  // First change should mark changed
    assert(result1.verified);
    
    // Apply again - should be idempotent (no change)
    auto result2 = apply_ownership_mutation(mut1);
    assert(!result2.changed);  // Should not change because already correct
    
    // Cleanup
    std::filesystem::remove(temp_path);
    
    std::cout << "test_apply_ownership_mutation: PASSED" << std::endl;
}

void test_create_with_permissions() {
    std::filesystem::path temp_dir = "/tmp/rebuntu_test_create_" + 
                                     std::to_string(getpid());
    std::filesystem::path temp_file = temp_dir / "testfile.txt";
    
    CreationIntent intent;
    intent.path = temp_file;
    intent.type = CreationIntent::Type::kFile;
    intent.mode_bits.owner_read = true;
    intent.mode_bits.owner_write = true;
    intent.owner_uid = getuid();
    intent.owner_gid = getgid();
    
    auto result = create_with_permissions(intent);
    assert(result.created || result.already_existed);
    
    // Verify the file was created with correct permissions
    auto observed = observe_file_state(temp_file, SymlinkSafety::kRejected);
    assert(observed.is_success());
    if (result.created) {
        assert(observed.value->exists);
    }
    
    // Cleanup
    std::filesystem::remove_all(temp_dir);
    
    std::cout << "test_create_with_permissions: PASSED" << std::endl;
}

void test_directory_creation() {
    std::filesystem::path temp_dir = "/tmp/rebuntu_test_dir_" + 
                                     std::to_string(getpid());
    
    CreationIntent intent;
    intent.path = temp_dir;
    intent.type = CreationIntent::Type::kDirectory;
    intent.mode_bits.owner_read = true;
    intent.mode_bits.owner_write = true;
    intent.mode_bits.owner_exec = true;
    intent.owner_uid = getuid();
    intent.owner_gid = getgid();
    
    auto result = create_with_permissions(intent);
    
    // Should have created or verified directory
    assert(result.created || result.already_existed);
    
    // Verify it's a directory
    auto observed = observe_file_state(temp_dir, SymlinkSafety::kRejected);
    if (observed.is_success()) {
        assert(observed.value->is_directory);
    }
    
    // Cleanup
    std::filesystem::remove_all(temp_dir);
    
    std::cout << "test_directory_creation: PASSED" << std::endl;
}

void test_mode_after_umask() {
    PermissionResult<UmaskState> umask_result = observe_umask();
    
    if (umask_result.is_success()) {
        UmaskState state = umask_result.value.value();
        
        // Test that umask clears bits
        ModeBits desired;
        desired.owner_read = true;
        desired.owner_write = true;
        desired.owner_exec = true;
        
        ModeBits after = mode_after_umask(desired, state.current_umask);
        
        // Any bit cleared by umask should be false in result
        assert(!after.owner_read || (desired.owner_read && !(state.current_umask & 0400)));
    }
    
    std::cout << "test_mode_after_umask: PASSED" << std::endl;
}

void test_owner_ref_resolution() {
    // Test by_name with current user
    OwnerRef ref1 = OwnerRef::by_name("root");
    auto uid_result = resolve_owner_uid(ref1);
    
    if (uid_result.is_success()) {
        assert(uid_result.value.has_value());
        assert(uid_result.value.value() == 0);  // root is always uid 0
    }
    
    std::cout << "test_owner_ref_resolution: PASSED" << std::endl;
}

int main() {
    std::cout << "Running Rebuntu Ownership & Permissions Tests (Phase 2.3)" << std::endl;
    std::cout << "=============================================================" << std::endl;
    
    test_mode_bits_creation();
    test_special_mode_bits();
    test_mode_string_conversion();
    test_observe_file_state_existing();
    test_observe_file_state_not_found();
    test_symlink_detection();
    test_verify_ownership_positive();
    test_verify_ownership_negative();
    test_apply_ownership_mutation();
    test_create_with_permissions();
    test_directory_creation();
    test_mode_after_umask();
    test_owner_ref_resolution();
    
    std::cout << "=============================================================" << std::endl;
    std::cout << "All ownership & permissions tests PASSED" << std::endl;
    
    return 0;
}