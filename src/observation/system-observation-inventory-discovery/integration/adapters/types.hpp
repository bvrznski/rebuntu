#pragma once
#include <string>
#include <vector>
namespace rebuntu::observation::system_observation_inventory_discovery::integration::adapters {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
