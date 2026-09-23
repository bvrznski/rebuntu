#pragma once

#include <string>
#include <vector>

namespace rebuntu::domains::user_identity_management::credentials {

// Structural vocabulary for this responsibility. Behavioral semantics are
// implemented only when the owning phase requirements are satisfied.
struct Descriptor {
    std::string id;
    std::string kind;
    std::vector<std::string> evidence;
};

} // namespace rebuntu::domains::user_identity_management::credentials
