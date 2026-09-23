#pragma once

#include <string>
#include <vector>

namespace rebuntu::runtime::configuration_and_profiles::desired_state {

// Structural vocabulary for this responsibility. Behavioral semantics are
// implemented only when the owning phase requirements are satisfied.
struct Descriptor {
    std::string id;
    std::string kind;
    std::vector<std::string> evidence;
};

} // namespace rebuntu::runtime::configuration_and_profiles::desired_state
