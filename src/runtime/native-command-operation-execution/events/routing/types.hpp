#pragma once
#include <string>
#include <vector>
namespace rebuntu::runtime::native_command_operation_execution::events::routing {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
