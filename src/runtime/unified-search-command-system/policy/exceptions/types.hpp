#pragma once
#include <string>
#include <vector>
namespace rebuntu::runtime::unified_search_command_system::policy::exceptions {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
