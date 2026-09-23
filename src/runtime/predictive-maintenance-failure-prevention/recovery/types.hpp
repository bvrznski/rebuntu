#pragma once

#include <string>
#include <vector>

namespace rebuntu::runtime::predictive_maintenance_failure_prevention::recovery {

// Structural vocabulary for this responsibility. Behavioral semantics are
// implemented only when the owning phase requirements are satisfied.
struct Descriptor {
    std::string id;
    std::string kind;
    std::vector<std::string> evidence;
};

} // namespace rebuntu::runtime::predictive_maintenance_failure_prevention::recovery
