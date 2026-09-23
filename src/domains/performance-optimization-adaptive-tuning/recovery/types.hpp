#pragma once

#include <string>
#include <vector>

namespace rebuntu::domains::performance_optimization_adaptive_tuning::recovery {

// Structural vocabulary for this responsibility. Behavioral semantics are
// implemented only when the owning phase requirements are satisfied.
struct Descriptor {
    std::string id;
    std::string kind;
    std::vector<std::string> evidence;
};

} // namespace rebuntu::domains::performance_optimization_adaptive_tuning::recovery
