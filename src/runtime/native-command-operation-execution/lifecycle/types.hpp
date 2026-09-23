#pragma once

#include <string>
#include <vector>

namespace rebuntu::runtime::native_command_operation_execution::lifecycle {

// Structural vocabulary for this responsibility. Behavioral semantics are
// implemented only when the owning phase requirements are satisfied.
struct Descriptor {
    std::string id;
    std::string kind;
    std::vector<std::string> evidence;
};

} // namespace rebuntu::runtime::native_command_operation_execution::lifecycle
