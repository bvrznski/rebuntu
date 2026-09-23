#pragma once
#include <string>
#include <vector>
namespace rebuntu::domains::network_management::events::routing {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
