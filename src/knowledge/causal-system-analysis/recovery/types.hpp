#pragma once

#include <string>
#include <vector>

namespace rebuntu::knowledge::causal_system_analysis::recovery {

// Structural vocabulary for this responsibility. Behavioral semantics are
// implemented only when the owning phase requirements are satisfied.
struct Descriptor {
    std::string id;
    std::string kind;
    std::vector<std::string> evidence;
};

} // namespace rebuntu::knowledge::causal_system_analysis::recovery
