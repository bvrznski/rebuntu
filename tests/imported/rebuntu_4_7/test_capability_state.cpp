// Rebuntu — Linux Capabilities Tests (Phase 2.5)
//
// Test the capability state model:
//   - Capability enumeration
//   - Bitmask operations
//   - /proc/self/status parsing

#include <system/environment/capability_state.hpp>

#include <iostream>
#include <set>

namespace {
int g_failures = 0;
#define CHECK(cond) do { if (!(cond)) { std::cerr << "CHECK failed: " << #cond << " (line " << __LINE__ << ")\n"; ++g_failures; } } while(0)
}  // namespace

int main() {
    using rebuntu::environment::capability_state::discover_capability_state;
    using rebuntu::environment::capability_state::has_effective_capability;
    using rebuntu::environment::capability_state::get_permitted_set;
    using rebuntu::environment::capability_state::getBoundingSet;
    using rebuntu::environment::capability_state::Capability;
    
    std::cout << "Testing Linux Capabilities (Phase 2.5)...\n";
    
    // Test 1: Discover capability state
    auto state = discover_capability_state();
    CHECK(state.pid == 0);  // Current process
    std::cout << "  - Capability discovery successful\n";
    
    // Test 2: Check that sets are valid (should always be initialized)
    // Note: Non-root processes may have empty permitted sets, which is valid
    bool has_any_set = state.sets.permitted[0] != 0 || state.sets.permitted[1] != 0 ||
                       state.sets.effective[0] != 0 || state.sets.effective[1] != 0;
    if (has_any_set) {
        std::cout << "  - Some capability set has bits set\n";
    } else {
        std::cout << "  - No capabilities active (valid for non-root non-elevated process)\n";
    }
    
    // Test 3: Capability enumeration
    auto cap_name = rebuntu::environment::capability_state::to_string(Capability::kChown);
    CHECK(std::string(cap_name) == "chown");
    
    cap_name = rebuntu::environment::capability_state::to_string(Capability::kDacOverride);
    CHECK(std::string(cap_name) == "dac_override");
    std::cout << "  - Capability enumeration works\n";

    
    // Test 4: from_string conversion
    auto opt_cap = rebuntu::environment::capability_state::from_string("chown");
    CHECK(opt_cap.has_value());
    CHECK(opt_cap.value() == Capability::kChown);
    
    opt_cap = rebuntu::environment::capability_state::from_string("invalid_cap");
    CHECK(!opt_cap.has_value());
    std::cout << "  - String conversion works\n";
    
    // Test 5: Bitmask operations
    auto empty_mask = rebuntu::environment::capability_state::make_empty_bitmask();
    CHECK(empty_mask[0] == 0);
    CHECK(empty_mask[1] == 0);
    
    auto full_mask = rebuntu::environment::capability_state::make_full_bitmask();
    CHECK(full_mask[0] != 0 || full_mask[1] != 0);
    std::cout << "  - Bitmask operations work\n";
    
    // Test 6: has_capability
    bool cap_has = rebuntu::environment::capability_state::has_capability(empty_mask, Capability::kChown);
    CHECK(!cap_has);
    
    cap_has = rebuntu::environment::capability_state::has_capability(full_mask, Capability::kChown);
    CHECK(cap_has);
    std::cout << "  - has_capability works\n";
    
    // Test 7: get_permitted_set
    auto permitted = get_permitted_set();
    std::cout << "  - Permitted set contains " << permitted.size() << " capabilities\n";
    
    // Test 8: getBoundingSet
    auto bounding = getBoundingSet();
    std::cout << "  - Bounding set contains " << bounding.size() << " capabilities\n";
    
    // Test 9: has_effective_capability (observable test)
    bool effective = has_effective_capability(Capability::kChown);
    if (!effective) {
        std::cout << "  - Current process does not have CAP_CHOWN (expected for non-root)\n";
    } else {
        std::cout << "  - Current process has CAP_CHOWN\n";
    }
    
    // Summary
    std::cout << "\nLinux Capabilities Tests Complete\n";
    if (g_failures > 0) {
        std::cerr << g_failures << " test(s) failed.\n";
        return 1;
    }
    std::cout << "All tests passed.\n";
    return 0;
}