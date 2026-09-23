#pragma once

#include <string>
#include <vector>

namespace rebuntu::knowledge::operational_learning::scheduling {

// Structural vocabulary for this responsibility. Behavioral semantics are
// implemented only when the owning phase requirements are satisfied.
struct Descriptor {
    std::string id;
    std::string kind;
    std::vector<std::string> evidence;
};

} // namespace rebuntu::knowledge::operational_learning::scheduling
