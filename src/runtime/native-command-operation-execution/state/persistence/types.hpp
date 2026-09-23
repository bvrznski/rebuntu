#pragma once
#include <string>
#include <vector>
namespace rebuntu::runtime::native_command_operation_execution::state::persistence {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
