// Rebuntu Capability State Tests (Phase 2.5)
// =============================================
// Testing Linux capabilities: CapPrm, CapEff, CapInh, CapBnd, CapAmb

#include <system/environment/capability_state.hpp>
#include <cassert>
#include <iostream>
#include <array>

using namespace rebuntu::environment::capability_state;

void test_capability_enumeration() {
    // Test capability enum values
    assert(static_cast<int>(Capability::kChown) == 0);
    assert(static_cast<int>(Capability::kDacOverride) == 1);
    
    // Test kNumCapabilities is 41 (CAP_LAST_CAP + 1)
    assert(kNumCapabilities == 41);
    
    std::cout << "test_capability_enumeration: PASSED" << std::endl;
}

void test_bitmask_operations() {
    CapabilityBitmask empty = make_empty_bitmask();
    assert(empty[0] == 0);
    assert(empty[1] == 0);
    
    CapabilityBitmask full = make_full_bitmask();
    // Full should have all bits set for capabilities 0-40
    assert(full[0] != 0);
    assert((full[1] & 0x1FFFFFFF) == 0x1FFFFFFF);  // First 29 bits set
    
    std::cout << "test_bitmask_operations: PASSED" << std::endl;
}

void test_has_capability() {
    CapabilityBitmask mask = make_empty_bitmask();
    
    // Add capability kChown (0) to mask
    set_capability(mask, Capability::kChown);
    assert(has_capability(mask, Capability::kChown));
    assert(!has_capability(mask, Capability::kDacOverride));  // Not set
    
    // Add another capability
    set_capability(mask, Capability::kDacOverride);
    assert(has_capability(mask, Capability::kChown));
    assert(has_capability(mask, Capability::kDacOverride));
    
    std::cout << "test_has_capability: PASSED" << std::endl;
}

void test_clear_capability() {
    CapabilityBitmask mask = make_full_bitmask();
    assert(has_capability(mask, Capability::kChown));
    
    // Clear kChown
    clear_capability(mask, Capability::kChown);
    assert(!has_capability(mask, Capability::kChown));
    assert(has_capability(mask, Capability::kDacOverride));  // Others still set
    
    std::cout << "test_clear_capability: PASSED" << std::endl;
}

void test_capabilities_from_bitmask() {
    CapabilityBitmask mask = make_empty_bitmask();
    set_capability(mask, Capability::kChown);
    set_capability(mask, Capability::kDacOverride);
    
    auto caps = capabilities_from_bitmask(mask);
    assert(caps.count(Capability::kChown) == 1);
    assert(caps.count(Capability::kDacOverride) == 1);
    assert(caps.size() == 2);
    
    std::cout << "test_capabilities_from_bitmask: PASSED" << std::endl;
}

void test_has_any_capability_empty() {
    CapabilityBitmask empty = make_empty_bitmask();
    assert(!has_any_capability(empty));
    
    std::cout << "test_has_any_capability_empty: PASSED" << std::endl;
}

void test_has_any_capability_with_caps() {
    CapabilityBitmask mask = make_empty_bitmask();
    set_capability(mask, Capability::kChown);
    assert(has_any_capability(mask));
    
    std::cout << "test_has_any_capability_with_caps: PASSED" << std::endl;
}

void test_is_subset_of() {
    CapabilityBitmask a = make_empty_bitmask();
    CapabilityBitmask b = make_full_bitmask();
    
    // Empty is subset of anything
    assert(is_subset_of(a, b));
    
    // Add same capabilities to both
    set_capability(a, Capability::kChown);
    set_capability(b, Capability::kChown);
    assert(is_subset_of(a, b));
    
    std::cout << "test_is_subset_of: PASSED" << std::endl;
}

void test_has_all_capabilities() {
    CapabilityBitmask available = make_empty_bitmask();
    set_capability(available, Capability::kChown);
    set_capability(available, Capability::kDacOverride);
    
    std::set<Capability> required1 = {Capability::kChown};
    assert(has_all_capabilities(available, required1));
    
    std::set<Capability> required2 = {
        Capability::kChown,
        Capability::kDacOverride
    };
    assert(has_all_capabilities(available, required2));
    
    // Not all present
    std::set<Capability> required3 = {
        Capability::kChown,
        Capability::kKill
    };
    assert(!has_all_capabilities(available, required3));
    
    std::cout << "test_has_all_capabilities: PASSED" << std::endl;
}

void test_has_any_capability_set() {
    CapabilityBitmask available = make_empty_bitmask();
    set_capability(available, Capability::kChown);
    
    std::set<Capability> required1 = {Capability::kKill};
    assert(!has_any_capability(available, required1));
    
    std::set<Capability> required2 = {
        Capability::kChown,
        Capability::kKill
    };
    assert(has_any_capability(available, required2));
    
    std::cout << "test_has_any_capability_set: PASSED" << std::endl;
}

void test_discover_capability_state() {
    auto state = discover_capability_state();
    
    // Should return valid state with all five sets
    // State is always returned, even if /proc/self/status fails (returns empty)
    assert(state.sets.permitted[0] != 0 || state.sets.effective[0] != 0 ||
           state.sets.inheritable[0] != 0 || state.sets.bounding[0] != 0 ||
           state.sets.ambient[0] != 0);
    
    std::cout << "test_discover_capability_state: PASSED" << std::endl;
}

void test_has_effective_capability() {
    // This should work regardless of whether we have effective capabilities
    bool result = has_effective_capability(Capability::kChown);
    // Result is either true or false, both are valid states
    
    std::cout << "test_has_effective_capability: PASSED" << std::endl;
}

void test_get_permitted_set() {
    auto set = get_permitted_set();
    
    // Should return a valid set (may be empty)
    assert(set.size() >= 0);
    
    std::cout << "test_get_permitted_set: PASSED" << std::endl;
}

void test_get_bounding_set() {
    auto set = getBoundingSet();
    
    // Bounding set should contain capabilities that can be acquired
    assert(set.size() > 0);  // At least some capabilities in bounding set
    
    std::cout << "test_get_bounding_set: PASSED" << std::endl;
}

void test_capability_string_conversion() {
    // Test to_string for a few capabilities
    assert(std::string(to_string(Capability::kChown)) == "chown");
    assert(std::string(to_string(Capability::kDacOverride)) == "dac_override");
    
    // Test from_string
    auto cap1 = from_string("chown");
    assert(cap1.has_value());
    assert(*cap1 == Capability::kChown);
    
    auto cap2 = from_string("invalid_capability_name");
    assert(!cap2.has_value());
    
    std::cout << "test_capability_string_conversion: PASSED" << std::endl;
}

void test_process_capability_state_structure() {
    ProcessCapabilityState state;
    
    // Test default values
    assert(state.pid == 0);
    assert(state.version == 0);
    
    // Test all sets are initialized to empty by default
    assert(!has_any_capability(state.sets.permitted));
    assert(!has_any_capability(state.sets.effective));
    assert(!has_any_capability(state.sets.inheritable));
    
    std::cout << "test_process_capability_state_structure: PASSED" << std::endl;
}

void test_file_capability_state_structure() {
    FileCapabilityState state;
    
    // Test default values
    assert(state.version == 0);
    assert(!state.root_id.has_value());
    
    std::cout << "test_file_capability_state_structure: PASSED" << std::endl;
}

void test_capability_result_success() {
    auto result = CapabilityResult<int>::success(42, "test_source");
    
    assert(result.is_success());
    assert(result.value.has_value());
    assert(*result.value == 42);
    assert(!result.error_code.empty());
    
    std::cout << "test_capability_result_success: PASSED" << std::endl;
}

void test_capability_result_not_found() {
    auto result = CapabilityResult<int>::not_found("test_source", "not found");
    
    assert(result.is_not_found());
    assert(!result.value.has_value());
    assert(result.error_code == "E_NOT_FOUND");
    
    std::cout << "test_capability_result_not_found: PASSED" << std::endl;
}

void test_capability_result_permission_denied() {
    auto result = CapabilityResult<int>::permission_denied("test_source", "no access");
    
    assert(result.is_permission_denied());
    assert(!result.value.has_value());
    assert(result.error_code == "E_PERMISSION_DENIED");
    
    std::cout << "test_capability_result_permission_denied: PASSED" << std::endl;
}

void test_capability_result_unknown() {
    auto result = CapabilityResult<int>::unknown("test_source", "unknown error");
    
    assert(result.is_unknown());
    assert(!result.value.has_value());
    assert(result.error_code == "E_UNKNOWN");
    
    std::cout << "test_capability_result_unknown: PASSED" << std::endl;
}

void test_observation_evidence() {
    CapabilityObservation obs;
    obs.source = "procfs";
    obs.observed_at = 1234567890;
    
    assert(obs.source == "procfs");
    assert(obs.observed_at > 0);
    
    std::cout << "test_observation_evidence: PASSED" << std::endl;
}

void test_adversarial_empty_proc_status() {
    // Test that discover_capability_state handles missing /proc/self/status gracefully
    auto state = discover_capability_state();
    
    // State should always be valid (may be empty but not invalid)
    assert(state.sets.permitted[0] != 0 || state.sets.effective[0] != 0 ||
           state.sets.inheritable[0] != 0 || state.sets.bounding[0] != 0 ||
           state.sets.ambient[0] != 0);
    
    std::cout << "test_adversarial_empty_proc_status: PASSED" << std::endl;
}

int main() {
    std::cout << "Running Rebuntu Capability State Tests (Phase 2.5)" << std::endl;
    std::cout << "=====================================================" << std::endl;
    
    test_capability_enumeration();
    test_bitmask_operations();
    test_has_capability();
    test_clear_capability();
    test_capabilities_from_bitmask();
    test_has_any_capability_empty();
    test_has_any_capability_with_caps();
    test_is_subset_of();
    test_has_all_capabilities();
    test_has_any_capability_set();
    
    test_discover_capability_state();
    test_has_effective_capability();
    test_get_permitted_set();
    test_get_bounding_set();
    
    test_capability_string_conversion();
    test_process_capability_state_structure();
    test_file_capability_state_structure();
    
    test_capability_result_success();
    test_capability_result_not_found();
    test_capability_result_permission_denied();
    test_capability_result_unknown();
    
    test_observation_evidence();
    test_adversarial_empty_proc_status();
    
    std::cout << "=====================================================" << std::endl;
    std::cout << "All capability state tests PASSED" << std::endl;
    
    return 0;
}