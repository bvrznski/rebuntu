#pragma once
#include <string>
#include <vector>
namespace rebuntu::observation::system_observation_inventory_discovery::model::value_objects {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
