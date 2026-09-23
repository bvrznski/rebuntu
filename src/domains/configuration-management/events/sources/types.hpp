#pragma once
#include <string>
#include <vector>
namespace rebuntu::domains::configuration_management::events::sources {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
