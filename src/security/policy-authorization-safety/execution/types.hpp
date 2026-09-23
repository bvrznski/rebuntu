#pragma once

#include <string>
#include <vector>

namespace rebuntu::security::policy_authorization_safety::execution {

// Structural vocabulary for this responsibility. Behavioral semantics are
// implemented only when the owning phase requirements are satisfied.
struct Descriptor {
    std::string id;
    std::string kind;
    std::vector<std::string> evidence;
};

} // namespace rebuntu::security::policy_authorization_safety::execution
