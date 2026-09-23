#pragma once
#include <string>
#include <vector>
namespace rebuntu::distributed::fleet_infrastructure_management::recovery::strategy {
struct Descriptor { std::string id; std::vector<std::string> tags; };
}
