#pragma once
#include <string>
#include <vector>
namespace rebuntu::distributed::fleet_infrastructure_management::integration::adapters {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
