#pragma once
#include <string>
#include <vector>
namespace rebuntu::observation::system_observation_inventory_discovery::events::types {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
