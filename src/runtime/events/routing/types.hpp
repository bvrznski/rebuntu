#pragma once
#include <string>
#include <vector>
namespace rebuntu::runtime::events::routing {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
