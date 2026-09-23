#pragma once

#include <string>
#include <vector>

namespace rebuntu::security::multi_lattice_mandatory_information_control_flow_security_system::contracts {

// Structural vocabulary for this responsibility. Behavioral semantics are
// implemented only when the owning phase requirements are satisfied.
struct Descriptor {
    std::string id;
    std::string kind;
    std::vector<std::string> evidence;
};

} // namespace rebuntu::security::multi_lattice_mandatory_information_control_flow_security_system::contracts
