#pragma once
#include <string>
#include <vector>
namespace rebuntu::runtime::unified_search_command_system::events::sources {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
