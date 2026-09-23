#pragma once

#include <string>
#include <vector>

namespace rebuntu::runtime::system_state_and_events::policy {

// Structural vocabulary for this responsibility. Behavioral semantics are
// implemented only when the owning phase requirements are satisfied.
struct Descriptor {
    std::string id;
    std::string kind;
    std::vector<std::string> evidence;
};

} // namespace rebuntu::runtime::system_state_and_events::policy
