#pragma once

#include <string>
#include <vector>

namespace rebuntu::providers::kernel_driver_hardware_evolution::verification {

// Structural vocabulary for this responsibility. Behavioral semantics are
// implemented only when the owning phase requirements are satisfied.
struct Descriptor {
    std::string id;
    std::string kind;
    std::vector<std::string> evidence;
};

} // namespace rebuntu::providers::kernel_driver_hardware_evolution::verification
