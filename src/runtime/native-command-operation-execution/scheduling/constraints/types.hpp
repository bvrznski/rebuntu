#pragma once
#include <string>
#include <vector>
namespace rebuntu::runtime::native_command_operation_execution::scheduling::constraints {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
