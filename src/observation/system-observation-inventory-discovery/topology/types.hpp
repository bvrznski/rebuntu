#pragma once

#include <string>
#include <vector>

namespace rebuntu::observation::system_observation_inventory_discovery::topology {

// Structural vocabulary for this responsibility. Behavioral semantics are
// implemented only when the owning phase requirements are satisfied.
struct Descriptor {
    std::string id;
    std::string kind;
    std::vector<std::string> evidence;
};

} // namespace rebuntu::observation::system_observation_inventory_discovery::topology
