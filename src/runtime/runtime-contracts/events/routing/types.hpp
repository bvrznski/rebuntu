#pragma once
#include <string>
#include <vector>
namespace rebuntu::runtime::runtime_contracts::events::routing {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
