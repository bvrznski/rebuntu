#pragma once

#include <string>
#include <vector>

namespace rebuntu::planning::operational_prediction_forward_simulation::resolution {

// Structural vocabulary for this responsibility. Behavioral semantics are
// implemented only when the owning phase requirements are satisfied.
struct Descriptor {
    std::string id;
    std::string kind;
    std::vector<std::string> evidence;
};

} // namespace rebuntu::planning::operational_prediction_forward_simulation::resolution
