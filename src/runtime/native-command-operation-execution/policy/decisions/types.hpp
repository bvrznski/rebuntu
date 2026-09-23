#pragma once
#include <string>
#include <vector>
namespace rebuntu::runtime::native_command_operation_execution::policy::decisions {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
